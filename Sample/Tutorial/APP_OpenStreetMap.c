/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software  has been licensed to  Cypress Semiconductor Corporation,
whose registered  office is situated  at 198 Champion Ct. San Jose, CA 
95134 USA  solely for the  purposes of creating  libraries for Cypress
PSoC3 and  PSoC5 processor-based devices,  sublicensed and distributed
under  the  terms  and  conditions  of  the  Cypress  End User License
Agreement.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Microcontroller Systems LLC
Licensed to:              Cypress Semiconductor Corp, 198 Champion Ct., San Jose, CA 95134, USA
Licensed SEGGER software: emWin
License number:           GUI-00319
License model:            Services and License Agreement, signed June 10th, 2009
Licensed platform:        Any Cypress platform (Initial targets are: PSoC3, PSoC5)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : OpenStreetMap.c
Purpose     : Drawing a map using the tile server of OpenStreetMap
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - (x)
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SKIP_TEST
#ifdef WIN32
  #include <winsock2.h>
#else
  #include <stdlib.h>

  #include "RTOS.h"
  #include "BSP.h"
  #include "IP.h"

  #define SOCKET U32
  #define SOCKADDR_IN struct sockaddr_in
  #define SOCKADDR    struct sockaddr
  #define IPPROTO_TCP SOL_SOCKET
  #define SD_BOTH 2

#endif

#include <math.h>
#include <stdio.h>

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define RECV_BUFFER_SIZE 2048

#define M_PI 3.1415926f

#define TILE_SERVER_URL "a.tile.openstreetmap.org"
#define TILE_SERVER_DIR ""

#define SERVER_PORT 80

#define S_CONTENT_LENGTH "Content-Length: "
#define S_EOF_HEADER     "\r\n\r\n"

#define TILE_SIZE 256

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 250)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
enum STATE {
  STATE_CREATESOCK = 0,
  STATE_REQUESTIMAGE,
  STATE_GETHEADER,
  STATE_GETIMAGE,
  STATE_DRAW,
  STATE_DONE
};

typedef struct TILE TILE;

struct TILE {
  SOCKET hSock;
  //
  // Image data
  //
  U8 * pImage;
  U32 SizeOfImage;
  int xPos, yPos;
  //
  // Coordinates for URL
  //
  int x, y, Zoom;
  //
  // Data for nonblocking receiving
  //
  U32 NumBytes;
  int State;
  //
  // Concatenation
  //
  TILE * pNext;
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#ifndef WIN32
enum {
   TASK_PRIO_IP_CLIENT = 150
  ,TASK_PRIO_IP_TASK          // Priority must be higher as all IP application tasks.
};

static OS_STACKPTR int _IPStack[768/sizeof(int)];       // Stack of the IP_Task.
static OS_TASK         _IPTCB;                          // Task-Control-Block of the IP_Task.
static int             _IFaceId;
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _TileX2Long (currently not used)
*
*  Function description
*    Calculates the langitude for the given x number of the tile and the zoom factor
*    
*/
#if 0
static double _TileX2Long(int x, int z) {
  double lon;

  lon = x / pow(2.0, z) * 360.0 - 180;
	return lon;
}
#endif

/*********************************************************************
*
*       _TileY2Lat (currently not used)
*
*  Function description
*    Calculates the latitude for the given y number of the tile and the zoom factor
*    
*/
#if 0
static double _TileY2Lat(int y, int z) {
  double lat, n;

	n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
  lat = 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
	return lat;
}
#endif

/*********************************************************************
*
*       _Long2TileX
*
*  Function description
*    Calculates the tile number in x for the given langitude and zoom factor
*/
static int _Long2TileX(double lon, int z) {
  int x;

  x = (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
  return x;
}

/*********************************************************************
*
*       _Lat2TileY
*
*  Function description
*    Calculates the tile number in y for the given latitude and zoom factor
*/
static int _Lat2TileY(double lat, int z) {
  int y;

  y = (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
  return y;
}

/*********************************************************************
*
*       _GetIPAddr
*
*  Function description
*    Translates the given URL to an IP address.
*/
static U32 _GetIPAddr(char * acURL) {
  struct hostent * pHostEnt;
  U32 IPAddr = 0;

  pHostEnt = gethostbyname(acURL);
  if (pHostEnt) {
    if (pHostEnt->h_addr_list) {
      IPAddr = htonl(*(U32*)(*pHostEnt->h_addr_list));
    }
  }
  return IPAddr;
}

/*********************************************************************
*
*       _CreateAndConnectSocket
*
*  Function description
*    Creates and connects a socket to the given IP address and activates
*    'non blocking'.
*/
static SOCKET _CreateAndConnectSocket(U32 IPAddr) {
  SOCKET hSock;
  SOCKADDR_IN SIn = {0};
  char acAddr[16];
  #ifdef WIN32
    U32 ULong;
  #endif

  sprintf(acAddr, "%i.%i.%i.%i", IPAddr >> 24, (IPAddr >> 16) & 0xFF, (IPAddr >>  8) & 0xFF, IPAddr & 0xFF);
  hSock = socket(AF_INET, SOCK_STREAM, 0);
  if (hSock == INVALID_SOCKET ) {
    return 0; // Error
  }
  SIn.sin_family      = AF_INET;                 // Using TCP-IP
  SIn.sin_port        = htons((U16)SERVER_PORT); // Connecting on port
  SIn.sin_addr.s_addr = htonl(IPAddr);
  if (connect(hSock, (SOCKADDR *)&SIn, sizeof(SIn)) == SOCKET_ERROR) {
    return 0; // Error
  }
  //
  // Set socket non-blocking.
  //
  #ifdef WIN32
    if (ioctlsocket(hSock, FIONBIO, &ULong)) {
      return 0; // Error
    }
  #else
    if (setsockopt(hSock, SOL_SOCKET, SO_NBIO, NULL, 0)) {
      return 0; // Error
    }
  #endif
  return hSock; // OK
}

/*********************************************************************
*
*       _OnError
*
*  Function description
*    Closes a socket and avoids further activities with the tile.
*/
static void _OnError(TILE * pTile) {
  if (pTile->hSock) {
    shutdown(pTile->hSock, SD_BOTH);
    closesocket(pTile->hSock);
  }
  pTile->State = STATE_DONE;
}

/*********************************************************************
*
*       _ReceiveTile
*
*  Function description
*    State machine for receiving a tile from a tile server. It first send
*    a GET request and then receives the data by using non blocking sockets.
*    Non blocking is used here to be able to manage several tile requests
*    simultaneously.
*/
static void _ReceiveTile(TILE * pTile, U32 IPAddr) {
  char acTile[50] = {0};
  char acGET[128] = {0};
  char acBuffer[RECV_BUFFER_SIZE];
  U32 NumBytes, Len;
  U32 Cnt = 0;
  #ifdef WIN32
    U32 Error;
  #else
    I32 Error;
  #endif

  switch (pTile->State) {
  case STATE_CREATESOCK:
    //
    // Create and connect socket
    //
    pTile->hSock = _CreateAndConnectSocket(IPAddr);
    if (pTile->hSock) {
      pTile->State++;
    } else {
      _OnError(pTile);
    }
    break;
  case STATE_REQUESTIMAGE:
    //
    // Send GET request to tile server
    //
    sprintf(acTile, "%s/%i/%i/%i.png", TILE_SERVER_DIR, pTile->Zoom, pTile->x, pTile->y);
    sprintf(acGET,
            "GET %s HTTP/1.1\r\n"
            "User-Agent: MyApp\r\n\r\n"
            , acTile);
    Len = strlen(acGET);
    NumBytes = send(pTile->hSock, acGET, Len, 0);
    if (NumBytes == Len) {
      pTile->State++;
    } else {
      _OnError(pTile);
    }
    break;
  case STATE_GETHEADER:
    //
    // Receive header containing the PNG size and perhaps the first part of the PNG itself
    //
    NumBytes = recv(pTile->hSock, acBuffer, RECV_BUFFER_SIZE, 0);
    if (NumBytes == SOCKET_ERROR) {
      //
      // WSAEWOULDBLOCK/IP_ERR_WOULD_BLOCK are ok here because we use non blocking sockets
      //
      #ifdef WIN32
        Error = WSAGetLastError();
        if (Error != WSAEWOULDBLOCK) {
          _OnError(pTile);
        }
      #else
        getsockopt(pTile->hSock, SOL_SOCKET, SO_ERROR, &Error, sizeof(Error));
        if (Error != IP_ERR_WOULD_BLOCK) {
          _OnError(pTile);
        }
      #endif
      return;
    }
    if (NumBytes) {
      //
      // Extract PNG size (Content-Length) from first part of data
      //
      Len = strlen(S_CONTENT_LENGTH);
      while (strncmp(acBuffer + Cnt, S_CONTENT_LENGTH, Len) != 0) {
        if (++Cnt == NumBytes) {
          _OnError(pTile);
          return;
        }
      }
      pTile->SizeOfImage = atoi(acBuffer + Cnt + Len);
      //
      // Allocate buffer for PNG file
      //
      pTile->pImage      = malloc(pTile->SizeOfImage);
      if (pTile->pImage == NULL) {
        _OnError(pTile);
        return;
      }
      Len = strlen(S_EOF_HEADER);
      while (strncmp(acBuffer + Cnt, S_EOF_HEADER, Len) != 0) {
        if (++Cnt == NumBytes) {
          _OnError(pTile);
          return;
        }
      }
      Cnt += Len;
      //
      // If more data than the header is available, process data as part of PNG
      //
      if (NumBytes > Cnt) {
        memcpy(pTile->pImage, acBuffer + Cnt, NumBytes - Cnt);
        pTile->NumBytes = NumBytes - Cnt;
      }
      if (pTile->pImage) {
        pTile->State++;
      } else {
        _OnError(pTile);
      }
    }
    break;
  case STATE_GETIMAGE:
    //
    // Receive PNG data
    //
    NumBytes = recv(pTile->hSock, (char *)pTile->pImage + pTile->NumBytes, pTile->SizeOfImage - pTile->NumBytes, 0);
    if (NumBytes == SOCKET_ERROR) {
      //
      // WSAEWOULDBLOCK/IP_ERR_WOULD_BLOCK are ok here because we use non blocking sockets
      //
      #ifdef WIN32
        Error = WSAGetLastError();
        if (Error != WSAEWOULDBLOCK) {
          _OnError(pTile);
        }
      #endif
      return;
    }
    if (NumBytes) {
      //
      // Remember pointer to data
      //
      pTile->NumBytes += NumBytes;
      //
      // Check if we are ready and close socket
      //
      if (pTile->NumBytes == pTile->SizeOfImage) {
        shutdown(pTile->hSock, SD_BOTH);
        closesocket(pTile->hSock);
        pTile->State++;
      }
    }
    break;
  }
}

/*********************************************************************
*
*       _TileScreen
*
*  Function description
*    Fills the screen with PNG-tiles from an OpenStreetMap-server.
*    Receiving the tiles works asynchronous with non blocking sockets.
*    Tiles are requested by the following GET request:
*
*    "GET <URL of TileServer>/<Zoom factor>/<X-value>/<Y-value>.png\r\nUser-Agent: xxx\r\n\r\n"
*
*  Parameters:
*    x    - X-value for URL of tile calculated by longitude and zoom factor
*    y    - Y-value for URL of tile calculated by latitude and zoom factor
*    Zoom - A value between 1-16 where 16
*/
static void _TileScreen(int x, int y, int Zoom) {
  TILE * pTileFirst;
  TILE * pTile;
  int xSize, ySize, xPos, yPos, nx, ny, i, j, Ready;
  U32 IPAddr;

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  xPos = (xSize - TILE_SIZE) / 2;
  yPos = (ySize - TILE_SIZE) / 2;
  nx = ny = 1;
  while (xPos > 0) {
    nx += 2;
    xPos -= TILE_SIZE;
    x--;
  }
  while (yPos > 0) {
    ny += 2;
    yPos -= TILE_SIZE;
    y--;
  }
  pTileFirst = NULL;
  //
  // Create list of all tiles
  //
  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      pTile = calloc(1, sizeof(TILE));
      if (pTileFirst == NULL) {
        pTileFirst = pTile;
      } else {
        pTile->pNext = pTileFirst;
        pTileFirst = pTile;
      }
      pTileFirst->x = x + i;
      pTileFirst->y = y + j;
      pTileFirst->Zoom = Zoom;
      pTileFirst->xPos = xPos + i * TILE_SIZE;
      pTileFirst->yPos = yPos + j * TILE_SIZE;
    }
  }
  //
  // Request and drawing of all tiles
  //
  IPAddr = _GetIPAddr(TILE_SERVER_URL);
  do {
    Ready = 1;
    for (pTile = pTileFirst; pTile; pTile = pTile->pNext) {
      if (pTile->State < STATE_DRAW) {
        //
        // Tile not available: Keep receiving
        //
        _ReceiveTile(pTile, IPAddr);
        Ready = 0;
      } else {
        if (pTile->State == STATE_DRAW) {
          //
          // Tile already received: Draw and remove
          //
          GUI_PNG_Draw(pTile->pImage, pTile->SizeOfImage, pTile->xPos, pTile->yPos);
          free(pTile->pImage);
          pTile->State = STATE_DONE;
          Ready = 0;
        }
      }
    }
  } while (Ready == 0);
  //
  // Remove tiles
  //
  while (pTileFirst) {
    pTile = pTileFirst;
    pTileFirst = pTileFirst->pNext;
    free(pTile);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  #ifdef WIN32
    WSADATA WSAData;
  #endif
  double lon  =  6.9158935; // Longitude
  double lat  = 51.1793436; // Latitude
  int x, y, Zoom;

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  #ifdef WIN32
    WSACleanup();
    if (WSAStartup(MAKEWORD(2,0), &WSAData) != 0) {
      return;
    }
  #else
    IP_Init();
    IP_AddLogFilter(IP_MTYPE_APPLICATION);
    _IFaceId = IP_INFO_GetNumInterfaces() - 1;                               // Get the last registered interface ID as this is most likely the interface we want to use in this sample.
    OS_SetPriority(OS_GetTaskID(), TASK_PRIO_IP_TASK);                       // For now, this task has highest prio except IP management tasks.
    OS_CREATETASK(&_IPTCB, "IP_Task", IP_Task, TASK_PRIO_IP_TASK, _IPStack); // Start the IP_Task.
    IP_Connect(_IFaceId);                                                    // Connect the interface if necessary.
    OS_SetPriority(OS_GetTaskID(), TASK_PRIO_IP_CLIENT);                     // Important: Client task priority must be less than priority of IP task!!!
    while (IP_IFaceIsReadyEx(_IFaceId) == 0) {
      OS_Delay(50);
    }
  #endif
  Zoom = 16;
  x = _Long2TileX(lon, Zoom);
  y = _Lat2TileY(lat, Zoom);
  _TileScreen(x, y, Zoom);
  while(1) {
    GUI_Delay(20);
  }
}

#endif

/*************************** End of file ****************************/
