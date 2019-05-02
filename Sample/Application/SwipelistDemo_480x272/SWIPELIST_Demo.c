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
File    : SWIPELIST_Demo.c
Purpose : Demonstrate the SWIPELIST Widget and ANIMATION module of
          emWin. Presenting different SEGGER products.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include <stdlib.h>
#include "DIALOG.h"
#include "SWIPELIST.h"

//
// Choose proper bitmaps depending on color format
//
extern GUI_CONST_STORAGE GUI_BITMAP bmBackgroundWindow_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBackground_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmSeparator_218x21;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Production_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_OS_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_JLink_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_GUI_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_FS_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Cpp_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Connectivity_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Compress_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Cloud_SSL_64x64;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_BootLoader_64x64;

#define BM_BACKGROUND_WIN bmBackgroundWindow_480x272
#define BM_BACKGROUND     bmBackground_480x272
#define BM_SEPARATOR      bmSeparator_218x21
#define BM_PRODUCTION     bmIcon_Production_64x64
#define BM_OS             bmIcon_OS_64x64
#define BM_JLINK          bmIcon_JLink_64x64
#define BM_GUI            bmIcon_GUI_64x64
#define BM_FS             bmIcon_FS_64x64
#define BM_CPP            bmIcon_Cpp_64x64
#define BM_CONNECT        bmIcon_Connectivity_64x64
#define BM_COMPRESS       bmIcon_Compress_64x64
#define BM_SECURITY       bmIcon_Cloud_SSL_64x64
#define BM_BOOTLOAD       bmIcon_BootLoader_64x64

//
// Define fonts for easy exchange
//
#define FONT_REG   GUI_Font16_1
#define FONT_BOLD  GUI_Font16B_1
//
// ID defines for identification
//
#define ID_BUTTON_0             (GUI_ID_USER + 0x01)
#define ID_SWIPELIST_0          (GUI_ID_USER + 0x02)
#define ID_SWIPELIST_ITEM_0     (GUI_ID_USER + 0x03)
//
// Color definitions, macro converts them depending on color format
//
#define COLOR_GREEN      GUI_MAKE_COLOR(0x0014b6a9)
#define COLOR_BLUE       GUI_MAKE_COLOR(0x00623700)
#define COLOR_LIGHTBLUE  GUI_MAKE_COLOR(0x00aa7d67)
#define COLOR_WHITE      GUI_MAKE_COLOR(0x00F2F2F2)
#define COLOR_LEMON      GUI_MAKE_COLOR(0x0000d6d3)
#define COLOR_CPP        GUI_MAKE_COLOR(0x0035048c)
#define COLOR_JLINK      GUI_MAKE_COLOR(0x002d27c1)
#define COLOR_OS         GUI_MAKE_COLOR(0x00275bea)
#define COLOR_FS         GUI_MAKE_COLOR(0x002292f3)
#define COLOR_COMPR      GUI_MAKE_COLOR(0x003caff8)
#define COLOR_BOOTLOAD   GUI_MAKE_COLOR(0x0000d7d3)
#define COLOR_CONNECT    GUI_MAKE_COLOR(0x0000bdeb)
#define COLOR_SECURITY   GUI_MAKE_COLOR(0x0000bdeb)
#define COLOR_GUI        GUI_MAKE_COLOR(0x0000c7db)
#define COLOR_PRODUCTION GUI_MAKE_COLOR(0x001ac39d)
//
// Y-Size of separators and items
//
#define SWIPE_SEPERATOR_SIZE  20
#define SWIPE_ITEM_SIZE       35
//
// Index values for separators
//
#define SWIPE_SEP_INDEX0         0
#define SWIPE_SEP_INDEX1         1
#define SWIPE_SEP_INDEX2         2
#define SWIPE_SEP_INDEX3         3
//
// IDs for items
//
#define SWIPE_ITEM_ID0         0 
#define SWIPE_ITEM_ID1         1 
#define SWIPE_ITEM_ID2         2 
#define SWIPE_ITEM_ID3         3 
#define SWIPE_ITEM_ID4         4 
#define SWIPE_ITEM_ID5         5 
#define SWIPE_ITEM_ID6         6 
#define SWIPE_ITEM_ID7         7 
#define SWIPE_ITEM_ID8         8 
#define SWIPE_ITEM_ID9         9 
#define SWIPE_ITEM_ID10        10
#define SWIPE_ITEM_ID11        11
#define SWIPE_ITEM_ID12        12
#define SWIPE_ITEM_ID13        13
#define SWIPE_ITEM_ID14        14
#define SWIPE_ITEM_ID15        15
#define SWIPE_ITEM_ID16        16

//
// Define some names for the separator items
//
static char * _aTextSeparator[] = {
  "Developing Software",
  "Debug Probes",
  "Middleware",
  "Production",
};

//
// This are the different entries below the seperators
//
static char * _aTextHeader[] = {
  //
  // Developing Software
  //
  "Embedded Studio",
  "SystemView",
  "J-Link Debugger",
  //
  // Debug Probes
  //
  "J-Link/J-Trace",
  //
  // Middleware
  //
  "embOS",
  "emFile",
  "emUSB Device/Host",
  "emCompress",
  "embOS/IP",
  "emSecure",
  "emSSL",
  "emWin",
  //
  // Production
  //
  "Flasher"
};

typedef struct {
  char             * pHeadline;
  const GUI_BITMAP * pBitmap;
  GUI_COLOR          Color;
} ITEM_INFO;

//
// Description of the entries above
//
static ITEM_INFO _aItemInfo[] = {
  { "Embedded Studio",   &BM_CPP,        COLOR_CPP},
  { "SystemView",        &BM_CPP,        COLOR_CPP},
  { "J-Link Debugger",   &BM_CPP,        COLOR_CPP},
  { "J-Link/J-Trace",    &BM_JLINK,      COLOR_JLINK},
  { "embOS",             &BM_OS,         COLOR_OS},
  { "emFile",            &BM_FS,         COLOR_FS},
  { "emUSB Device/Host", &BM_CONNECT,    COLOR_CONNECT},
  { "emCompress",        &BM_COMPRESS,   COLOR_COMPR},
  { "embOS/IP",          &BM_CONNECT,    COLOR_CONNECT},
  { "emSecure",          &BM_SECURITY,   COLOR_SECURITY},
  { "emSSL",             &BM_SECURITY,   COLOR_SECURITY},
  { "emWin",             &BM_GUI,        COLOR_GUI},
  { "Flasher",           &BM_PRODUCTION, COLOR_PRODUCTION}
};

//
// Description for different products
//
static char * _aDescription[] = {
  "- Free for Education\n- Cross-Platform Support\n- Target Support\n- Powerful Project Manager\n- Compiler included\n- Feature-packed Debugger\n- First-Class Editor",
  "- Minimal intrusive\n- Free tool\n- No license costs\n- RTOS tracing\n- Interrupt tracing\n- Real-time recording\n- Live analysis of captured data\n- Works on any CPU.\n",
  "- C code source level debugging\n- Assembly instruction debugging\n- High-speed programming of\n  the application into the target\n- Fully customizable windows\n- Debug Information Windows\n  for any purpose\n- Direct use of J-Link features",
  "- Over 400,000 units sold\n- Up to 3 MB/s Download speed\n- Multi core debugging\n- All CPU families supported\n- Internal trace buffer supported\n- Multiple target interfaces\n  (JTAG, SWD, FINE, SPD, ...)",
  "- Available for all popular cores,\n  compiler and development tools\n- Kernel awareness plugins\n- Unlimited number of tasks\n  and priorities\n- Power management\n- Precise time measurement\n- Zero latency interrupts",
  "- Windows-compatible FAT12,\n  FAT16 and FAT32 support\n- Long file name support\n- Multiple device driver support\n- Multiple media support\n- NOR- and NAND-flash driver\n- RAID 1 support",
  "- Optimized for embOS but\n  works even without RTOS\n- No custom USB host driver necessary\n- Hardware abstraction layer\n  allows rapid addition of support\n  for new devices\n- Runs out-of-the-box",
  "- Highly efficient compression\n- Small decompressor ROM\n  footprint\n- Fixed decompressor RAM use\n- Wide range of codecs\n- Automatic selection of best\n  codec for each file\n- Royalty free",
  "- High performance\n- Small footprint\n- Runs out-of-the-box\n- No configuration required\n- Works with any RTOS\n- Zero data copy for\n  ultra fast performance\n- PPP/PPPOE available",
  "- Asymmetric algorithms\n- Different algorithms available\n- Hardware-independent\n- High performance,\n  small memory footprint\n- Applicable for new and\n  existing products\n- Full source code",
  "- Secures your connection\n- Compatible with any server\n- Easy to understand\n- Simple to integrate\n- No additional hardware required\n- No royalties",
  "- Any CPU\n- Any LCD and LCD-controller\n- Works without LCD\n- Wide range of PC tools\n- Routines are optimized for speed and size\n- Small memory footprint\n- Highly configurable",
  "- Stand-alone JTAG/SWD\n  programmer\n- Non-authorized access\n  protection\n- Wide range of supported CPUs\n- Power over USB\n- Portable version\n- Ethernet interface"
};

//
// Animation data structure
//
typedef struct {
  WM_HWIN hWin;
  int Dir;
} ANIM_DATA;
//
// Information structure for window
//
typedef struct {
  GUI_ANIM_HANDLE hAnim;
  ANIM_DATA       Data;
  int             ActiveItem;
} WINDOW_DATA;

//
// Some static data
//
static GUI_ANIM_HANDLE _hAnim;
static ANIM_DATA       _Data;
static WINDOW_DATA     _aDataWindow;
static int             _DoAnimation;
static int             _SwitchDrawing;

/*********************************************************************
*
*       _AnimSwipeInOut
*/
static void _AnimSwipeInOut(GUI_ANIM_INFO * pInfo, void * pVoid) {
  int xPos;
  int yPos;
  int xSize;
  int ySize;
  
  GUI_USE_PARA(pVoid);
  //
  // Calculate a new y position and set the window properly
  //
  if (_Data.Dir) {
    yPos = ((262 * pInfo->Pos) / GUI_ANIM_RANGE);
  } else {
    yPos = 262 - ((262 * pInfo->Pos) / GUI_ANIM_RANGE);
  }
  xPos  = WM_GetWindowOrgX(_Data.hWin);
  xSize = WM_GetWindowSizeX(_Data.hWin); 
  ySize = WM_GetWindowSizeY(_Data.hWin); 
  WM_SetWindowPos(_Data.hWin, xPos, yPos, xSize, ySize);
}

/*********************************************************************
*
*       _AnimMoveWindows
*/
static void _AnimMoveWindows(GUI_ANIM_INFO * pInfo, void * pVoid) {
  int xPos;
  int yPos;
  int xSize;
  int ySize;
  ANIM_DATA * pData;
  
  pData = (ANIM_DATA *) pVoid;
  //
  // Calculate a new x position and set the window properly
  //
  if (pData->Dir) {
    xPos = (LCD_GetXSize() / 2) + (((LCD_GetXSize() / 2) * pInfo->Pos) / GUI_ANIM_RANGE);
  } else {
    xPos = (LCD_GetXSize() - ((LCD_GetXSize() / 2) * pInfo->Pos) / GUI_ANIM_RANGE);
  }
  yPos = WM_GetWindowOrgY(pData->hWin);
  xSize = WM_GetWindowSizeX(pData->hWin); 
  ySize = WM_GetWindowSizeY(pData->hWin); 
  WM_SetWindowPos(pData->hWin, xPos, yPos, xSize, ySize);
}

/*********************************************************************
*
*       _AnimExec
*/
static void _AnimExec(GUI_ANIM_HANDLE * pAnim, ANIM_DATA * pData) {
  while (GUI_ANIM_Exec(*pAnim) == 0) {
    GUI_Delay(5);
  }
  //
  // Clean up after the animation has been completed
  //
  pData->Dir = (pData->Dir) ? 0 : 1;
  GUI_ANIM_Delete(*pAnim);
  *pAnim = 0;
}

/*********************************************************************
*
*       _CreateAnim
*/
static void _CreateAnim(GUI_ANIM_HANDLE * pAnim, ANIM_DATA * pData, GUI_ANIMATION_FUNC * pfAnim) {
  if (*pAnim == 0) {
    *pAnim = GUI_ANIM_Create(300, 10, pData, 0);
    GUI_ANIM_AddItem(*pAnim, 10, 300, ANIM_ACCEL, pData, pfAnim);
    GUI_ANIM_Start(*pAnim);
  }
}

/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DrawBitmap(&BM_BACKGROUND, 0, 0);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWindows
*/
static void _cbWindows(WM_MESSAGE * pMsg) {
  GUI_RECT   Rect;
  GUI_RECT   TRect;
  int        NCode;
  static int Index;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetClientRect(&Rect);
    //
    // Draw a Bitmap as background
    //
    GUI_DrawBitmap(&BM_BACKGROUND_WIN, 0, 0);
    //
    // Just draw something if an item has been selected
    //
    if (_aDataWindow.ActiveItem > 0) {
      //
      // Just draw on a switch of content
      //
      if (_SwitchDrawing) {
        Index = _aDataWindow.ActiveItem - ID_SWIPELIST_ITEM_0;
      }
      GUI_EnableAlpha(1);
      GUI_DrawGradientH(Rect.x0 + 1, Rect.y0 + BM_SEPARATOR.YSize, Rect.x1 - 2, Rect.y0 + BM_SEPARATOR.YSize + 10, GUI_TRANSPARENT, _aItemInfo[Index].Color);
      GUI_EnableAlpha(0);
      //
      // Set text color and mode
      //
      GUI_SetTextMode(GUI_TM_TRANS);
      GUI_SetColor(COLOR_WHITE);
      //
      // If we have a pointer to a headline text, draw it
      //
      if (_aItemInfo[Index].pHeadline) {
        GUI_SetFont(&FONT_BOLD);
        TRect.x0 = Rect.x0 + 10;
        TRect.y0 = Rect.y0;
        TRect.x1 = BM_SEPARATOR.XSize;
        TRect.y1 = BM_SEPARATOR.YSize;
        GUI_DispStringInRect(_aItemInfo[Index].pHeadline, &TRect, GUI_TA_LEFT | GUI_TA_VCENTER);
      }
      //
      // Draw the proper icon
      //
      if (_aItemInfo[Index].pBitmap) {
        GUI_DrawBitmap(_aItemInfo[Index].pBitmap, Rect.x0 + 10, Rect.y0 + BM_SEPARATOR.YSize + 5);
      }
      //
      // If we have a pointer to a description text, draw it
      //
      if (_aDescription[Index]) {
        GUI_SetFont(&FONT_REG);
        TRect.y0 += _aItemInfo[Index].pBitmap->YSize + BM_SEPARATOR.YSize + 10;
        TRect.x1 = Rect.x1 - 10;
        TRect.y1 = Rect.y1 - 20;
        GUI_DispStringInRect(_aDescription[Index], &TRect, GUI_TA_LEFT | GUI_TA_TOP);
      }
    }
    break;
  case WM_NOTIFY_PARENT:
    //
    // If the button gets released we start an animation
    //
    NCode = pMsg->Data.v;
    switch(NCode) {
    case WM_NOTIFICATION_RELEASED:
      if (_aDataWindow.Data.Dir) {
        if (_aDataWindow.hAnim == 0) {
          _CreateAnim(&_aDataWindow.hAnim, &_aDataWindow.Data, _AnimMoveWindows);
          _AnimExec(&_aDataWindow.hAnim, &_aDataWindow.Data);
          //
          // The window isn't visible any longer, no item active
          //
          _aDataWindow.ActiveItem = -1;
        }
      }
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWin
*/
static void _cbWin(WM_MESSAGE * pMsg) {
  GUI_RECT   Rect;
  int        Id;
  int        NCode;
  int        ReleasedItem;
  int        ActiveWindow;
  
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Draw a thin black frame around the SWIPELIST
    //
    WM_GetClientRect(&Rect);
    GUI_SetColor(GUI_BLACK);
    GUI_AA_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, 5);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    //
    // If the button gets released we start an animation
    //
    case ID_BUTTON_0:
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
        _CreateAnim(&_hAnim, &_Data, _AnimSwipeInOut);
        break;
      }
      break;
    case ID_SWIPELIST_0:
      switch (NCode) {
      //
      // An item has been reeleased
      //
      case WM_NOTIFICATION_RELEASED:
        //
        // Receive the ID of the item which has been released
        //
        ReleasedItem = SWIPELIST_GetReleasedItem(pMsg->hWinSrc);
        ActiveWindow = SWIPELIST_GetItemUserData(pMsg->hWinSrc, ReleasedItem);
        //
        // if it is different to the active window or not present
        //
        if ((_aDataWindow.ActiveItem != ActiveWindow) || (_aDataWindow.Data.Dir == 0)) {
          _DoAnimation = 1;
          //
          // If it is not displayed already, create an animation
          //
          if (_aDataWindow.Data.Dir == 0) {
            _CreateAnim(&_aDataWindow.hAnim, &_aDataWindow.Data, _AnimMoveWindows);
          }
          //
          // Remeber the active window
          //
          _aDataWindow.ActiveItem = ActiveWindow;
        }
        break;
      }
    break;
    }
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _OwnerDraw
*/
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  GUI_COLOR Color;
  GUI_RECT  rInside;
  int       Height;
  int       Width;
    
  //
  // Distinguish between different commands
  //
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    WM_GetInsideRectEx(pDrawItemInfo->hWin, &rInside);
    Width = rInside.x1;
    return Width;
  case WIDGET_ITEM_GET_YSIZE:
    Height = GUI_GetFontDistY() + 40;
    return Height;
  case WIDGET_ITEM_DRAW_FRAME:
    //
    // Skip this part, we do not want to draw this one
    //
    break;
  case WIDGET_ITEM_DRAW:
    //
    // Skip this part, we do not want to draw this one
    //
    break;
  case WIDGET_ITEM_DRAW_SEP:
    //
    // Skip this part, we do not want to draw this one
    //
    break;
  case WIDGET_ITEM_DRAW_TEXT:
    //
    // Just set a text mode but let the default owner draw routine handle the rest
    //
    GUI_SetTextMode(GUI_TM_TRANS);
    SWIPELIST_OwnerDraw(pDrawItemInfo);
    break;
  case WIDGET_ITEM_DRAW_BITMAP:
    //
    // Skip this part, we do not want to draw this one
    //
    break;
  case WIDGET_ITEM_DRAW_BACKGROUND:
    //
    // Handle drawing of the background of the items
    //
    switch (pDrawItemInfo->ItemIndex) {
    case SWIPE_ITEM_ID0:
      //
      // the first entry in the SWIPELIST needs special treatment
      //
      GUI_SetColor(GUI_DARKGRAY);
      GUI_DrawLine(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x1, pDrawItemInfo->y0);
    case SWIPE_ITEM_ID4:
    case SWIPE_ITEM_ID6:
    case SWIPE_ITEM_ID15:
      //
      // Case 0, 4, 8 and 12 are the separator items, here we handle their drawing
      //
      GUI_SetColor(GUI_BLACK);
      GUI_FillRect(pDrawItemInfo->x0, pDrawItemInfo->y1 - 3, pDrawItemInfo->x1, pDrawItemInfo->y1);
      GUI_DrawBitmap(&BM_SEPARATOR, pDrawItemInfo->x0, pDrawItemInfo->y0);
      break;
    case SWIPE_ITEM_ID1:
    case SWIPE_ITEM_ID5:
    case SWIPE_ITEM_ID7:
    case SWIPE_ITEM_ID16:
      //
      // These cases are the entries below the seperators, those need special treatment as well
      //
      if (pDrawItemInfo->ItemIndex == SWIPELIST_GetSelItem(pDrawItemInfo->hWin)) {
        Color = COLOR_GREEN;
      } else {
        Color = COLOR_BLUE;
      }
      GUI_SetColor(Color);
      GUI_FillRect(pDrawItemInfo->x0, pDrawItemInfo->y0 + 1, pDrawItemInfo->x1, pDrawItemInfo->y1);
      GUI_DrawGradientV(pDrawItemInfo->x0, pDrawItemInfo->y0,
                        pDrawItemInfo->x1, pDrawItemInfo->y1 - ((pDrawItemInfo->y1 - pDrawItemInfo->y0) / 2), GUI_BLACK, Color);
      break;
    default:
      //
      // All other items are getting drawn the same way
      //
      if (pDrawItemInfo->ItemIndex == SWIPELIST_GetSelItem(pDrawItemInfo->hWin)) {
        Color = COLOR_GREEN;
      } else {
        Color = COLOR_BLUE;
      }
      GUI_SetColor(Color);
      GUI_FillRect(pDrawItemInfo->x0, pDrawItemInfo->y0, pDrawItemInfo->x1, pDrawItemInfo->y1);
      break;
    }
    break;
  default:
    //
    // Anything we do not catch in this routine gets handled by the default owner draw
    //
    return SWIPELIST_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

/*********************************************************************
*
*       _CreateWindows
*/
static void _CreateWindows(WM_HWIN hParent) {
  int     xSize;
  int     ySize;
  int     xPos;
  int     yPos;
  
  GUI_USE_PARA(hParent);
  xSize = BM_SEPARATOR.XSize + 2;//LCD_GetXSize() / 2 + 5;
  ySize = LCD_GetYSize() - 20;
  xPos  = LCD_GetXSize() / 2;
  yPos  = 10;
  _aDataWindow.Data.hWin  = WM_CreateWindow(xPos, yPos, xSize, ySize, WM_CF_SHOW | WM_CF_HASTRANS, _cbWindows, 0);
  _aDataWindow.Data.Dir   = 1;
  _aDataWindow.ActiveItem = ID_SWIPELIST_ITEM_0;
  _SwitchDrawing = 1;
}

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_HWIN _hSwipelist;
  WM_HWIN hWin;
  int     xSize;
  int     ySize;
  int     xPos;
  int     yPos;
  int     i;

#ifdef WIN32
  WM_SetCreateFlags(WM_CF_MEMDEV);
#endif
  WM_MOTION_Enable(1);
  WM_MULTIBUF_Enable(1);
  GUI_Init();
  //
  // Set a callback for the background window
  //
  WM_SetCallback(WM_HBKWIN, _cbBk);
  //
  // Create a window which contains the swipelist
  //
  xPos  = 10;
  yPos  = 10;
  xSize = LCD_GetXSize() / 2 - 20;
  ySize = LCD_GetYSize();
  hWin  = WM_CreateWindowAsChild(xPos, yPos, xSize, ySize, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS, _cbWin, 0);
  //
  // Attach SWIPELIST to the window
  //
  xPos  = 1;
  yPos  = 1;//12;
  xSize = WM_GetWindowSizeX(hWin) - 2;
  ySize = WM_GetWindowSizeY(hWin) - 10;
  _hSwipelist = SWIPELIST_CreateEx(xPos, yPos, xSize, ySize, hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_SWIPELIST_0);
  WM_MOTION_SetMoveable(_hSwipelist, WM_CF_MOTION_Y, 1);
  //
  // Configure SWIPELIST
  //
  SWIPELIST_SetOwnerDraw(_hSwipelist, _OwnerDraw);
  SWIPELIST_SetFont(_hSwipelist, SWIPELIST_FI_SEP_ITEM, &FONT_BOLD);
  SWIPELIST_SetFont(_hSwipelist, SWIPELIST_FI_ITEM_HEADER, &FONT_REG);
  SWIPELIST_SetFont(_hSwipelist, SWIPELIST_FI_ITEM_TEXT, &FONT_REG);
  SWIPELIST_SetDefaultSepSize(1);
  SWIPELIST_SetDefaultSepColor(GUI_BLACK);
  SWIPELIST_SetTextColor(_hSwipelist, SWIPELIST_CI_ITEM_HEADER_UNSEL, COLOR_WHITE);
  SWIPELIST_SetTextColor(_hSwipelist, SWIPELIST_CI_ITEM_HEADER_SEL, COLOR_WHITE);
  SWIPELIST_SetTextColor(_hSwipelist, SWIPELIST_CI_ITEM_TEXT_UNSEL, COLOR_WHITE);
  SWIPELIST_SetTextColor(_hSwipelist, SWIPELIST_CI_ITEM_TEXT_SEL, COLOR_WHITE);
  SWIPELIST_SetTextColor(_hSwipelist, SWIPELIST_CI_SEP_ITEM_TEXT, COLOR_WHITE);
  //
  // Fill ANIM_DATA structure
  //
  _Data.Dir  = 0;
  _Data.hWin = hWin;
  //
  // Add Items to the SWIPELIST
  //
  SWIPELIST_AddSepItem(_hSwipelist, _aTextSeparator[SWIPE_SEP_INDEX0], SWIPE_SEPERATOR_SIZE);  // Dev Software
  for (i = 0; i < 3; i++) {
    SWIPELIST_AddItem(_hSwipelist, _aTextHeader[i], SWIPE_ITEM_SIZE);                          // Text to shown under the menu entry above
    SWIPELIST_SetItemUserData(_hSwipelist, i + 1, ID_SWIPELIST_ITEM_0 + i);
  }
  SWIPELIST_AddSepItem(_hSwipelist, _aTextSeparator[SWIPE_SEP_INDEX1], SWIPE_SEPERATOR_SIZE);  // Debug Probes
  for (; i < 4; i++) {
    SWIPELIST_AddItem(_hSwipelist, _aTextHeader[i], SWIPE_ITEM_SIZE);                          // Text to shown under the menu entry above
    SWIPELIST_SetItemUserData(_hSwipelist, i + 2, ID_SWIPELIST_ITEM_0 + i);
  }
  SWIPELIST_AddSepItem(_hSwipelist, _aTextSeparator[SWIPE_SEP_INDEX2], SWIPE_SEPERATOR_SIZE);  // Private
  for (; i < 12; i++) {
    SWIPELIST_AddItem(_hSwipelist, _aTextHeader[i], SWIPE_ITEM_SIZE);                          // Text to shown under the menu entry above
    SWIPELIST_SetItemUserData(_hSwipelist, i + 3, ID_SWIPELIST_ITEM_0 + i);
  }
  SWIPELIST_AddSepItem(_hSwipelist, _aTextSeparator[SWIPE_SEP_INDEX3], SWIPE_SEPERATOR_SIZE);  // System
  for (; i < 13; i++) {
    SWIPELIST_AddItem(_hSwipelist, _aTextHeader[i], SWIPE_ITEM_SIZE);                          // Text to shown under the menu entry above
    SWIPELIST_SetItemUserData(_hSwipelist, i + 4, ID_SWIPELIST_ITEM_0 + i);
  }
  _CreateWindows(WM_HBKWIN);
  //
  // Stay alive loop
  //
  while (1) {
    //
    // If an animation has been created, process it
    //
    if (_hAnim) {
      _AnimExec(&_hAnim, &_Data);
    }
    //
    // Handle Info window animation
    //
    if (_DoAnimation) {  // Animation required ?
      //
      // If it is already present
      //
      if (_aDataWindow.Data.Dir) {
        _SwitchDrawing = 0;
        _CreateAnim(&_aDataWindow.hAnim, &_aDataWindow.Data, _AnimMoveWindows);  // Create an animation for moving out the window
        _AnimExec(&_aDataWindow.hAnim, &_aDataWindow.Data);                      // Execute the animation
        _CreateAnim(&_aDataWindow.hAnim, &_aDataWindow.Data, _AnimMoveWindows);  // Create an animation for moving in again
      }
      //
      // If no window is present but an animation has been created move in the window
      //
      if (_aDataWindow.hAnim) {
        _SwitchDrawing = 1;
        _AnimExec(&_aDataWindow.hAnim, &_aDataWindow.Data);
      }
      //
      // Animation has been processed, reset variable
      //
      _DoAnimation = 0;
    }
    GUI_Delay(50);
  }
}
