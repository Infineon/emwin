/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2021  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.24 - Graphical user interface for embedded applications **
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
License model:            Cypress Services and License Agreement, signed June 9th/10th, 2009
                          and Amendment Number One, signed June 28th, 2019 and July 2nd, 2019
                          and Amendment Number Two, signed September 13th, 2021 and September 18th, 2021
Licensed platform:        Any Cypress platform (Initial targets are: PSoC3, PSoC5)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : MainTask.c
Purpose     : Weather forecast demo using multiple layers
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "DIALOG.h"

#include "Resource.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define XOFF_TEXT0       50
#define XOFF_TEXT1       55
#define YOFF_TEXT1       20
#define XOFF_IMAGE       10
#define YOFF_IMAGE       10

#define JOB_ANIM_IN      1
#define JOB_ANIM_IN_DROP 2
#define JOB_ANIM_OUT     3
#define JOB_ANIM_IDLE    4

#define YPOS_DROP        150
#define YPOS_FORECAST    350
#define YSIZE_FORECAST    60

#define XPOS_TEXT        100
#define YPOS_TEXT         50
#define XSIZE_TEXT       280
#define YSIZE_TEXT       135

#define INDICATOR_R      5
#define INDICATOR_XDIST  20

#define TIME_IDLE        5000

#define COLOR_BLUE       GUI_MAKE_COLOR(0x00B56D30)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (24 * 1024) // Should be adapted, value is too less

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
//
// Indices for _apBmSym
//
typedef enum {
  INDEX_SYM_PARTLY_CLOUDY = 0,
  INDEX_SYM_CLOUD_LIGHTING,
  INDEX_SYM_RAIN,
  INDEX_SYM_CHANCE_OF_STORM,
  INDEX_SYM_SUN
} INDEX_SYM;

//
// Indices for images in _apBmBack
//
typedef enum {
  INDEX_BK_BERLIN = 0,
  INDEX_BK_MOSCOW,
  INDEX_BK_NY,
  INDEX_BK_TOKYO
} INDEX_BK;

//
// Positioning data for animated icons
//
typedef struct PARA PARA;
typedef struct WINDOW_DATA WINDOW_DATA;

struct PARA {
  int           xPos;
  int           xSizeScreen;
  int           xSize;
  WINDOW_DATA * pData;
  int           Index;
  int           DynXPos;
};

struct WINDOW_DATA {
  int             xSize;
  int             ySize;
  int             xPos;
  int             yOff;
  WM_HTIMER       hTimer;
  WM_HWIN         hWin;
  WM_HWIN         hText;
  WM_HWIN         hBar;
  GUI_ANIM_HANDLE hAnimSymbol;
  GUI_ANIM_HANDLE hAnimBackground;
  PARA            aPara[5];
  GUI_TIMER_TIME  TimeLastTouch;
  int             Job;
  int             LastJob;
  int             IndexCity;
  int             IndexAnimIn;
  int             IndexAnimOut;
  int             HasStopped;
  int             Diff;
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
GUI_CONST_STORAGE GUI_BITMAP * _apBmBack[] = {
  &bmBerlin_800x480,
  &bmMoscow_800x480,
  &bmNewYork_800x480,
  &bmTokyo_800x480,
};

static GUI_CONST_STORAGE GUI_BITMAP * _apBmSym[] = {
  &bmpartly_cloudy_day40x40,
  &bmcloud_lighting40x40,
  &bmrain40x40,
  &bmchance_of_storm40x40,
  &bmsun40x40,
};

static const char * _pDays[] = { "MON", "TUE", "WED", "THU", "FRI" };

static const struct CITY {
  const char * pName;
  const char * pTime;
  int Temperature;
  int Weather;
  const unsigned aForeCast[5];
  const unsigned aTemp[5];
} _aCity[] = {
  {
    "BERLIN",
    "15:20",
    26,
    INDEX_BK_BERLIN,
    {
      INDEX_SYM_CHANCE_OF_STORM,
      INDEX_SYM_CLOUD_LIGHTING,
      INDEX_SYM_RAIN,
      INDEX_SYM_SUN,
      INDEX_SYM_PARTLY_CLOUDY,
    },
    { 28, 24, 25, 29, 30 },
  },
  {
    "TOKYO",
    "23:20",
    22,
    INDEX_BK_TOKYO,
    {
      INDEX_SYM_PARTLY_CLOUDY,
      INDEX_SYM_CLOUD_LIGHTING,
      INDEX_SYM_RAIN,
      INDEX_SYM_CHANCE_OF_STORM,
      INDEX_SYM_SUN,
    },
    { 20, 18, 16, 19, 23 },
  },
  {
    "MOSCOW",
    "17:20",
    18,
    INDEX_BK_MOSCOW,
    {
      INDEX_SYM_SUN,
      INDEX_SYM_PARTLY_CLOUDY,
      INDEX_SYM_SUN,
      INDEX_SYM_CLOUD_LIGHTING,
      INDEX_SYM_RAIN,
    },
    { 21, 18, 16, 14, 14 },
  },
  {
    "NEW YORK",
    "10:20",
    25,
    INDEX_BK_NY,
    {
      INDEX_SYM_RAIN,
      INDEX_SYM_PARTLY_CLOUDY,
      INDEX_SYM_SUN,
      INDEX_SYM_SUN,
      INDEX_SYM_SUN,
    },
    { 28, 30, 32, 33, 30 },
  },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AnimDrawSym
*/
static void _AnimDrawSym(PARA * pPara, int xPos, int IndexCity) {
  GUI_DrawBitmap(_apBmSym[_aCity[IndexCity].aForeCast[pPara->Index]], xPos + XOFF_IMAGE, YOFF_IMAGE);
  GUI_SetFont(&GUI_Font20_AA4);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetColor(COLOR_BLUE);
  GUI_AA_PreserveTrans(1);
  GUI_DispStringAt(_pDays[pPara->Index], xPos + XOFF_TEXT0, YOFF_IMAGE);
  GUI_GotoXY(xPos + XOFF_TEXT1, YOFF_IMAGE + YOFF_TEXT1);
  GUI_DispDecMin(_aCity[IndexCity].aTemp[pPara->Index]);
  GUI_DispString("\xb0""C");
  GUI_AA_PreserveTrans(0);
}

/*********************************************************************
*
*       _DrawIndicators
*/
static void _DrawIndicators(WINDOW_DATA * pData) {
  int i, Index, NumItems, mx, my;
  U32 Color;

  Index = pData->xPos / pData->xSize;
  NumItems = GUI_COUNTOF(_apBmBack);
  mx = (pData->xSize  - (INDICATOR_XDIST * (NumItems - 1))) / 2;
  my = YPOS_FORECAST + YSIZE_FORECAST + (pData->ySize - (YPOS_FORECAST + YSIZE_FORECAST)) / 2;
  GUI_AA_PreserveTrans(1);
  for (i = 0; i < NumItems; i++) {
    Color = (Index == i) ? GUI_WHITE : COLOR_BLUE;
    GUI_SetColor(Color);
    GUI_AA_FillCircle(mx + i * INDICATOR_XDIST, my, INDICATOR_R);
  }
  GUI_AA_PreserveTrans(0);
}

/*********************************************************************
*
*       _AnimSymbolFlyIn
*/
static void _AnimSymbolFlyIn(GUI_ANIM_INFO * pInfo, void * pVoid) {
  PARA * pPara;
  int Dyn, Fix;

  pPara          = (PARA *)pVoid;
  Fix            = pPara->xSizeScreen + pPara->xPos - pPara->xSize / 2;
  Dyn            = (pPara->xSizeScreen * pInfo->Pos) / GUI_ANIM_RANGE;
  pPara->DynXPos = Fix - Dyn;
  WM_Invalidate(pPara->pData->hBar);
}

/*********************************************************************
*
*       _AnimSymbolFlyOut
*/
static void _AnimSymbolFlyOut(GUI_ANIM_INFO * pInfo, void * pVoid) {
  PARA * pPara;
  int Dyn, Fix;

  pPara          = (PARA *)pVoid;
  Fix            = pPara->xPos - pPara->xSize / 2 - pPara->xSizeScreen;
  Dyn            = (pPara->xSizeScreen * (GUI_ANIM_RANGE - pInfo->Pos)) / GUI_ANIM_RANGE;
  pPara->DynXPos = Fix + Dyn;
  WM_Invalidate(pPara->pData->hBar);
}

/*********************************************************************
*
*       _AnimDropIn
*
* Purpose:
*   Dropping text animation
*/
static void _AnimDropIn(GUI_ANIM_INFO * pInfo, void * pVoid) {
  WINDOW_DATA * pData;

  pData = (WINDOW_DATA *)pVoid;
  //
  // Only calculation of text position and invalidation required
  //
  pData->yOff = YPOS_DROP - (YPOS_DROP * pInfo->Pos) / GUI_ANIM_RANGE;
  WM_InvalidateWindow(pData->hText);
}

/*********************************************************************
*
*       _AnimDropOut
*
* Purpose:
*   Dropping text animation
*/
static void _AnimDropOut(GUI_ANIM_INFO * pInfo, void * pVoid) {
  WINDOW_DATA * pData;

  pData = (WINDOW_DATA *)pVoid;
  //
  // Only calculation of text position and invalidation required
  //
  pData->yOff = (YPOS_DROP * pInfo->Pos) / GUI_ANIM_RANGE;
  WM_InvalidateWindow(pData->hText);
}

/*********************************************************************
*
*       _AnimBackground
*
* Purpose:
*   Animation of background pictures. Done by feeding the PID buffer.
*/
static void _AnimBackground(GUI_ANIM_INFO * pInfo, void * pVoid) {
  WINDOW_DATA * pData;
  GUI_PID_STATE State;
  static int    Sign;

  //
  // Get current data and decide in which direction to move
  //
  pData = (WINDOW_DATA *)pVoid;
  pData->TimeLastTouch = GUI_GetTime();
  if (pInfo->State == GUI_ANIM_START) {
    Sign = ((GUI_GetTime() & 1) * 2) - 1;
  }
  State.Layer = 0;
  State.Pressed = 1;
  switch (Sign) {
  case -1:
    State.x = ((pData->xSize / 2 + 10) * pInfo->Pos) / GUI_ANIM_RANGE;
    break;
  case +1:
    State.x = ((pData->xSize / 2 + 10) * (GUI_ANIM_RANGE - pInfo->Pos)) / GUI_ANIM_RANGE;
    break;
  }
  State.y = 0;
  //
  // Fake touch input to move the background.
  //
  GUI_PID_StoreState(&State);
  if (pInfo->State == GUI_ANIM_END) {
    State.Pressed = 0;
    GUI_PID_StoreState(&State);
  }
}

/*********************************************************************
*
*       _OnDeleteAnimBackground
*
* Purpose:
*   This function is called immediately before the animation object
*   will be destroyed. It has only to set the animation handle to
*   zero which is used in the application to check if the animation
*   is running or not.
*/
static void _OnDeleteAnimBackground(void * pVoid) {
  WINDOW_DATA * pData;
  
  pData = (WINDOW_DATA *)pVoid;
  pData->hAnimBackground = 0;
}

/*********************************************************************
*
*       _OnDeleteAnimSymbol
*
* Purpose:
*   (same as above...)
*/
static void _OnDeleteAnimSymbol(void * pVoid) {
  WINDOW_DATA * pData;
  
  pData = (WINDOW_DATA *)pVoid;
  pData->hAnimSymbol = 0;
}

/*********************************************************************
*
*       _OnTimer
*/
static void _OnTimer(WINDOW_DATA * pData) {
  int NumItems, IndexCity, i;

  if (pData->hAnimSymbol == 0) {
    if (GUI_GetTime() >= (pData->TimeLastTouch + TIME_IDLE)) {
      pData->Job = JOB_ANIM_IDLE;
    } else {
      if (pData->HasStopped) {
        //
        // After last move add 'Fly in of symbols' animation
        //
        if ((pData->LastJob != JOB_ANIM_IN) && (pData->LastJob != JOB_ANIM_IN_DROP)) {
          IndexCity = pData->xPos / pData->xSize;
          IndexCity = (IndexCity >= (int)GUI_COUNTOF(_aCity)) ? (int)GUI_COUNTOF(_aCity) - 1 : IndexCity;
          pData->IndexAnimIn = pData->IndexCity;
          if (pData->IndexCity != IndexCity) {
            pData->Job = JOB_ANIM_IN_DROP;
            pData->IndexCity   = IndexCity;
            pData->IndexAnimIn = IndexCity;
          } else {
            pData->Job = JOB_ANIM_IN;
          }
          WM_InvalidateWindow(pData->hWin);
        }
      }
    }
    //
    // Create animations on demand
    //
    NumItems = GUI_COUNTOF(pData->aPara);
    switch (pData->Job) {
    case JOB_ANIM_IDLE:
      if (pData->hAnimBackground == 0) {
        pData->hAnimBackground = GUI_ANIM_Create(750, 25, pData, NULL);
        GUI_ANIM_AddItem(pData->hAnimBackground, 0, 750, ANIM_ACCEL, pData, _AnimBackground);
        GUI_ANIM_StartEx(pData->hAnimBackground, 1, _OnDeleteAnimBackground);
        pData->Job = 0;
      }
      break;
    case JOB_ANIM_IN_DROP:
    case JOB_ANIM_IN:
      if (pData->hAnimSymbol == 0) {
        pData->hAnimSymbol = GUI_ANIM_Create(1000, 25, pData, NULL);
        //
        // Add 'Fly in of symbols' to animation
        //
        for (i = 0; i < NumItems; i++) {
          GUI_ANIM_AddItem(pData->hAnimSymbol, i * 100, i * 100 + 500, ANIM_DECEL, &pData->aPara[i], _AnimSymbolFlyIn);
        }
        //
        // Add 'Drop in text' to animation
        //
        GUI_ANIM_AddItem(pData->hAnimSymbol, 0, 300, ANIM_DECEL, pData, _AnimDropIn);
        GUI_ANIM_StartEx(pData->hAnimSymbol, 1, _OnDeleteAnimSymbol);
        pData->LastJob = pData->Job;
        pData->Job = 0;
      }
      break;
    case JOB_ANIM_OUT:
      if (pData->hAnimSymbol == 0) {
        pData->hAnimSymbol = GUI_ANIM_Create(1000, 25, pData, NULL);
        //
        // Add 'Fly out of symbols' to animation
        //
        for (i = 0; i < NumItems; i++) {
          GUI_ANIM_AddItem(pData->hAnimSymbol, i * 100, i * 100 + 500, ANIM_ACCEL, &pData->aPara[i], _AnimSymbolFlyOut);
        }
        GUI_ANIM_AddItem(pData->hAnimSymbol, 0, 300, ANIM_ACCEL, pData, _AnimDropOut);
        GUI_ANIM_StartEx(pData->hAnimSymbol, 1, _OnDeleteAnimSymbol);
        pData->LastJob = pData->Job;
        pData->Job = 0;
      }
      break;
    }
  }
  WM_RestartTimer(pData->hTimer, 25);
}

/*********************************************************************
*
*       _cbText
*
* Purpose:
*   Callback function of text window responsible for drawing
*   city, time and temperature
*/
static void _cbText(WM_MESSAGE * pMsg) {
  GUI_COLOR aColor[] = {
    GUI_DARKGRAY, GUI_WHITE
  };
  unsigned int i;
  WINDOW_DATA * pData;

  WM_GetUserData(pMsg->hWin, &pData, sizeof(WINDOW_DATA *));
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Draw text with 3D effect
    //
    GUI_SetTextMode(GUI_TM_TRANS);
    for (i = 0; i < GUI_COUNTOF(aColor); i++) {
      GUI_SetColor(aColor[i]);
      GUI_SetFont(&GUI_Font32_AA4);
      GUI_GotoXY(XPOS_TEXT + 1 + !i, YPOS_TEXT + 1 + !i - pData->yOff);
      GUI_DispString(_aCity[pData->IndexCity].pName);
      GUI_GotoXY(XPOS_TEXT + 1 + !i, YPOS_TEXT + 1 + 30 - pData->yOff + !i);
      GUI_SetFont(&GUI_Font20_AA4);
      GUI_DispString(_aCity[pData->IndexCity].pTime);
      GUI_DispString(" SUNDAY 23 APR");
      GUI_SetFont(&GUI_Font60_AA4);
      GUI_GotoXY(XPOS_TEXT + 1 + 200 + !i, YPOS_TEXT + 1 - 5 - pData->yOff + !i);
      GUI_DispDecMin(_aCity[pData->IndexCity].Temperature);
      GUI_DispString("\xb0");
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbBar
*/
static void _cbBar(WM_MESSAGE * pMsg) {
  WINDOW_DATA * pData;
  int i;

  WM_GetUserData(pMsg->hWin, &pData, sizeof(WINDOW_DATA *));
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Draw the forecast symbols according to the position calculated
    // by the animation functions .
    //
    if (pData) {
      for (i = 0; i < 5; i++) {
        _AnimDrawSym(&pData->aPara[i], pData->aPara[i].DynXPos, pData->IndexAnimIn);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbWin
*/
static void _cbWin(WM_MESSAGE * pMsg) {
  WM_MOTION_INFO * pInfo;
  WM_HWIN hWin;
  WINDOW_DATA * pData;
  GUI_PID_STATE State;
  int i, x0, Index, NumItems;

  hWin = pMsg->hWin;
  NumItems = GUI_COUNTOF(_apBmBack);
  WM_GetUserData(hWin, &pData, sizeof(WINDOW_DATA *));
  if (pData) {
    if (pData->hTimer == 0) {
      pData->hTimer = WM_CreateTimer(hWin, 0, 0, 0);
      pData->Job = JOB_ANIM_IN_DROP;
    }
  }
  switch (pMsg->MsgId) {
  //
  // Draw background image(s)
  //
  case WM_PAINT:
    for (i = 0; i <= NumItems; i++) {
      Index = (i == NumItems) ? 0 : i;
      x0 = pData->xPos - i * pData->xSize;
      if ((x0 > -(int)pData->xSize) && (x0 < (int)pData->xSize)) {
        GUI_DrawBitmap(_apBmBack[_aCity[Index].Weather], x0, 0);
      }
    }
    _DrawIndicators(pData);
    break;
  //
  // Timer keeps the demo alive
  //
  case WM_TIMER:
    _OnTimer(pData);
    break;
  //
  // React on window motion messages
  //
  case WM_MOTION:
    //
    // Stop idle animation if it is currently running
    //
    GUI_PID_GetCurrentState(&State);
    if (State.Pressed) {
      if (State.y != 0) {
        if (pData->hAnimBackground) {
          GUI_ANIM_Stop(pData->hAnimBackground);
          GUI_ANIM_Delete(pData->hAnimBackground);
          pData->hAnimBackground = 0;
        }
      }
    }
    //
    // Remember moment of last touch event
    //
    pData->TimeLastTouch = GUI_GetTime();
    //
    // Process motion commands
    //
    pInfo = (WM_MOTION_INFO *)pMsg->Data.p;
    switch (pInfo->Cmd) {
    case WM_MOTION_INIT:
      //
      // Tell motion support that window manages motion messages by itself
      //
      pInfo->Flags  = WM_MOTION_MANAGE_BY_WINDOW;
      pInfo->SnapX  = pData->xSize;
      pInfo->Period = 300;
      break;
    case WM_MOTION_MOVE:
      //
      // Manage motion message
      //
      pData->xPos += pInfo->dx;
      if (pData->xPos >= (int)(NumItems * pData->xSize)) {
        pData->xPos -= NumItems * pData->xSize;
      }
      if (pData->xPos < 0) {
        pData->xPos += NumItems * pData->xSize;
      }
      //
      // Calculate distance
      //
      pData->Diff = pData->xPos - pData->IndexCity * pData->xSize;
      if ((pData->IndexCity == 0) && (pData->Diff > pData->xSize)) {
        pData->Diff -= pData->xSize * NumItems;
      }
      pData->Diff = (pData->Diff > 0) ? pData->Diff : -pData->Diff;
      WM_InvalidateWindow(pData->hText);
      if (pInfo->FinalMove) {
        //
        // After last move timer method should show forecast
        //
        pData->HasStopped = 1;
        _DrawIndicators(pData);
      } else {
        //
        // On first move hide forecast
        //
        pData->HasStopped = 0;
        if (pData->Diff > (pData->xSize / 3)) {
          if (pData->LastJob != JOB_ANIM_OUT) {
            pData->IndexAnimOut = pData->IndexCity;
            pData->Job = JOB_ANIM_OUT;
          }
        }
      }
      //
      // Make sure that WM redraws window
      //
      WM_Invalidate(hWin);
      break;
    case WM_MOTION_GETPOS:
      //
      // Return current xPos on request
      //
      pInfo->xPos = pData->xPos;
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _InitData
*/
static void _InitData(WINDOW_DATA * pData) {
  int i, NumItems, xSizeScreen, xSize;

  //
  // Set up data
  //
  NumItems = GUI_COUNTOF(pData->aPara);
  xSizeScreen = LCD_GetXSize();
  xSize = xSizeScreen / NumItems;
  for (i = 0; i < NumItems; i++) {
    pData->aPara[i].xSizeScreen = xSizeScreen;
    pData->aPara[i].xSize       = xSize;
    pData->aPara[i].xPos        = (xSize * i) + xSize / 2;
    pData->aPara[i].pData       = pData;
    pData->aPara[i].Index       = i;
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
  WINDOW_DATA * pData;
  static WINDOW_DATA Data;

  pData = &Data;
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available.");
    return;
  }
  //
  // Set up used tools
  //
  WM_MULTIBUF_Enable(1);
  WM_MOTION_Enable(1);
  //
  // Shrink desktop window
  //
  Data.xSize = LCD_GetXSize();
  Data.ySize = LCD_GetYSize();
  Data.TimeLastTouch = GUI_GetTime();
  WM_SetSize(WM_HBKWIN, Data.xSize, Data.ySize);
  //
  // Create background window
  //
  pData->hWin = WM_CreateWindowAsChild(0, 0, Data.xSize, Data.ySize, WM_HBKWIN, WM_CF_MOTION_X | WM_CF_SHOW, _cbWin, sizeof(WINDOW_DATA *));
  //
  // Create text window
  //
  pData->hText = WM_CreateWindowAsChild(XPOS_TEXT * 4, 0, XSIZE_TEXT, YSIZE_TEXT, pData->hWin, WM_CF_SHOW | WM_CF_HASTRANS, _cbText, sizeof(WINDOW_DATA *));
  //
  // Create forecast window
  //
  pData->hBar = WM_CreateWindowAsChild(0, YPOS_FORECAST, Data.xSize, YSIZE_FORECAST, pData->hWin, WM_CF_SHOW | WM_CF_HASTRANS, _cbBar, sizeof(WINDOW_DATA *));
  //
  // Initialize animation data
  //
  _InitData(pData);
  //
  // Make WINDOW_DATA available for windows
  //
  WM_SetUserData(pData->hWin,  &pData, sizeof(WINDOW_DATA *));
  WM_SetUserData(pData->hText, &pData, sizeof(WINDOW_DATA *));
  WM_SetUserData(pData->hBar,  &pData, sizeof(WINDOW_DATA *));
  //
  // Super loop
  //
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
