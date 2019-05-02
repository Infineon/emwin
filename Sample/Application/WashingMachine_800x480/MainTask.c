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
File        : MainTask_WashingMachine.c
Purpose     : Multilayer-WashingMachine-Demo 800x480
---------------------------END-OF-HEADER------------------------------
*/

#include "LCDConf.h"

#include "WM.h"
#include "DIALOG.h"
#include "Resource.h"

#include "stdio.h"

/*********************************************************************
*
*       Configuration
*
* Set this define to one if using a configuration for softlayer.
*
**********************************************************************
*/
#define USE_SOFTLAYER  0

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define IMAGE_FRAME_Y   6  // y-frame within bmBar_776x173
#define IMAGE_SIZE_Y  157  // y-size (opaque part) within bmBar_776x173

#define LAYER_BACKGROUND 0
#define LAYER_SLIDER     1
#define LAYER_BAR        2
#define LAYER_START      3

#define PERIOD_FADE  150
#define PERIOD_STAY 3000
#define PERIOD_ANIM  250
#define PERIOD_SNAP  150

#define INDEX_PROGRAM     0
#define INDEX_HOUR        4
#define INDEX_MINUTE      5

#define FONT_DURATION &GUI_Font23SL_AA4
#define FONT_LABEL    &GUI_Font27SL_AA4
#define FONT_SCROLLW  &GUI_Font32SL_AA4
#define FONT_MAG      &GUI_Font39SL_AA4
#define FONT_MAG_TIME &GUI_Font60SL_AA4
#define FONT_START    &GUI_Font39SL_AA4

#define MARGIN_LEFT      16
#define MARGIN_LEFT_MAG   8
#define YPOS_LABEL       10
#define YPOS_DURATION   110

#define ANIM_START_LAYER_DIST 110

#define COLOR_GREEN  GUI_MAKE_COLOR(0x0014b6a9)
#define COLOR_BLUE   GUI_MAKE_COLOR(0x00623700)
#define COLOR_RED    GUI_MAKE_COLOR(0x000000ff)
#define COLOR_WHITE  GUI_MAKE_COLOR(0x00F2F2F2)

#define ALPHA_ACTIVE 0x10000000
#define ALPHA_BAR    0x0D000000

#define APP_SET_INTENS (WM_USER + 0)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  //
  // Initialized at the beginning, not changed later on
  //
  int Index;                   // Index # of parameters
  int Start;                   // Initially selected value
  int n;                       // Number of items
  int xPos;                    // X-position of window
  int xSize;                   // X-size of window
  const char ** apTextSingle;  // Single line text for scroll window
  const char ** apTextDouble;  // Optional double line text for bar
  const char * pLabel;         // Label
  //
  // Dynamically calculated values
  //
  int yPos;    // Value changed by motion support
  int Active;  // If set to 1 labels should not be drawn
  //
  // Used in animation...
  //
  int PosStart;
  int PosDiff;
} PARA;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// Duration text for different programs
//
static const char * _apDuration[] = { "2h 32min", "1h 45min", "2h 15min", "1h 20min", "1h 10min", "15min" };

//
// Text to be used in slider layer
//
static const char * _apText0_Single[] = { "Eco Wash", "Synthetics", "Cotton", "Wool", "Silk", "Spin" };
static const char * _apText1_Single[] = { "90�", "60�", "40�", "30�", "COLD" };
static const char * _apText2_Single[] = { "1600", "1400", "1200", "800", "400", "none" };
static const char * _apText3_Single[] = { "None",     "Short",    "Extra Spinning",    "Pre-Washing",    "Extra Rinsing",    "Wrinkle Resitance" };
static const char * _apText3_Double[] = { NULL, NULL, NULL, NULL, "Extra", "Spinning", "Pre-","Washing", "Extra", "Rinsing", "Wrinkle", "Resitance" };
static const char * _apText4_Single[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
                                          "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                                          "20", "21", "22", "23" };
static const char * _apText5_Single[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
                                          "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                                          "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
                                          "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
                                          "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
                                          "50", "51", "52", "53", "54", "55", "56", "57", "58", "59" };

//
// Bar segment definitions to be shown in slider layer
//
static PARA _aPara[] = {
  { 0,  0, GUI_COUNTOF(_apText0_Single),   5, 165, _apText0_Single, NULL,            "Program"},
  { 1,  3, GUI_COUNTOF(_apText1_Single), 171, 105, _apText1_Single, NULL,            "Temp."},
  { 2,  0, GUI_COUNTOF(_apText2_Single), 277,  90, _apText2_Single, NULL,            "U/min"},
  { 3,  2, GUI_COUNTOF(_apText3_Single), 368, 225, _apText3_Single, _apText3_Double, "Options"},
  { 4, 19, GUI_COUNTOF(_apText4_Single), 594,  75, _apText4_Single, NULL,            "Start"},
  { 5, 15, GUI_COUNTOF(_apText5_Single), 670,  75, _apText5_Single, NULL,            ""}
};
//
// Pointers to be attached to the bar segment windows
//
static PARA * _apPara[GUI_COUNTOF(_aPara)];

//
// Handles of bar segment windows
//
static WM_HWIN _ahWinBarSegment[GUI_COUNTOF(_aPara)];

//
// Image index to be shown in the background
//
static int _IndexImage;

//
// Array of background images
//
static const GUI_BITMAP * _apBitmapBk[] = {
  &bmBkEco_800x480,
  &bmBkSynthetic_800x480,
  &bmBkCotton_800x480,
  &bmBkWoll_800x480,
  &bmBkSilk_800x480,
  &bmBkSpin_800x480,
};

//
// Common...
//
static int     _Fading;
static int     _IndexActive;
static WM_HWIN _hWinActive;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbRefresh
*/
static int _cbRefresh(int TimeRem, void * pVoid) {
  GUI_USE_PARA(pVoid);
  GUI_USE_PARA(TimeRem);
#if USE_SOFTLAYER
  GUI_SOFTLAYER_Refresh();
#endif
  return 0;
}

/*********************************************************************
*
*       _cbButton
*
* Purpose:
*   Callback function for 'ghost' buttons which only have to react
*   on input and shows nothing
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    break;
  default:
    BUTTON_Callback(pMsg);
  }
}

/*********************************************************************
*
*       _cbBk_BACKGROUND
*
* Purpose:
*   Callback of window showing the background image and a message
*   when pressing the 'Start' button
*/
static void _cbBk_BACKGROUND(WM_MESSAGE * pMsg) {
  int xSize, ySize;
  static GUI_MEMDEV_Handle hMemMessage;
  static U8 IntensMessage;
  const GUI_RECT RectMessage = { 0, 450, 799, 479 };

  switch (pMsg->MsgId) {
  case APP_SET_INTENS:
    IntensMessage = pMsg->Data.v;
    WM_InvalidateRect(pMsg->hWin, &RectMessage);
    break;
  case WM_PAINT:
    if (hMemMessage == 0) {
      xSize = LCD_GetXSize();
      ySize = LCD_GetYSize();
      hMemMessage = GUI_MEMDEV_CreateFixed32(0, ySize - 30, xSize, 30);
      GUI_MEMDEV_Select(hMemMessage);
      GUI_SetBkColor(COLOR_GREEN);
      GUI_ClearRect(0, ySize - 30, xSize - 1, ySize - 1);
      GUI_SetFont(&GUI_Font23SL_AA4);
      GUI_SetTextMode(GUI_TM_TRANS);
      GUI_SetColor(GUI_WHITE);
      GUI_DispStringHCenterAt("Please note that this demo could not wash your clothes!", xSize / 2, ySize - 27);
      GUI_MEMDEV_Select(0);
    }
    GUI_DrawBitmap(_apBitmapBk[_IndexImage], 0, 0);
    if (IntensMessage) {
      if (IntensMessage < 255) {
        GUI_MEMDEV_WriteAlpha(hMemMessage, IntensMessage);
      } else {
        GUI_MEMDEV_Write(hMemMessage);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _ManageBackgroundPicture
*
* NOTE: THE HARDWARE IS NOT ABLE TO FADE A LAYER IF THERE ARE OTHER
*       FUNCTIONS WITH EXTENDED MEMORY BUS ACCESS ARE RUNNING SIMULTANEOUSLY.
*       DISPLAY FLICKERS IN THAT CASE. BECAUSE OF THAT THE FUNCTION CURRENTLY
*       DOES NOT FADE:
*/
static void _ManageBackgroundPicture(void) {
  int IndexNew, FontSize;

  //
  // Calculate new index and check if fading is required
  //
  FontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
  IndexNew = (_aPara[0].yPos + (FontSize / 2)) / FontSize;
  if (_IndexImage == IndexNew) {
    return;
  }
  _IndexImage = IndexNew;
  WM_InvalidateWindow(WM_GetDesktopWindowEx(LAYER_BACKGROUND));
}

/*********************************************************************
*
*       _SliceInfo
*/
static void _SliceInfo(int State, void * pVoid) {
  GUI_USE_PARA(pVoid);

  //
  // Avoid flickering of layer 2 during animation
  //
  switch (State) {
  case GUI_ANIM_START:
    GUI_MULTIBUF_BeginEx(LAYER_SLIDER);
    break;
  case GUI_ANIM_END:
    GUI_MULTIBUF_EndEx(LAYER_SLIDER);
    break;
  }
}

/*********************************************************************
*
*       _InvalidateBarSegment
*/
static void _InvalidateBarSegment(unsigned Index) {
  if (Index < GUI_COUNTOF(_aPara)) {
    WM_InvalidateWindow(_ahWinBarSegment[Index]);
    if (Index == INDEX_HOUR) {
      WM_InvalidateWindow(_ahWinBarSegment[INDEX_MINUTE]);
    }
    if (Index == INDEX_MINUTE) {
      WM_InvalidateWindow(_ahWinBarSegment[INDEX_HOUR]);
    }
  }
}

/*********************************************************************
*
*       _AnimMoveToPosSub
*/
static void _AnimMoveToPosSub(GUI_ANIM_INFO * pInfo, void * pVoid) {
  WM_HWIN hWin;
  PARA * pPara;

  hWin = (WM_HWIN)pVoid;
  WM_GetUserData(hWin, &pPara, sizeof(pPara));
  pPara->yPos = pPara->PosStart + (pInfo->Pos * pPara->PosDiff) / GUI_ANIM_RANGE;
  WM_InvalidateWindow(hWin);
  _InvalidateBarSegment(pPara->Index);
  //
  // Change background picture
  //
  if (pInfo->State == GUI_ANIM_END) {
    _ManageBackgroundPicture();/**/
  }
}

/*********************************************************************
*
*       _AnimMoveToPos
*/
static void _AnimMoveToPos(WM_HWIN hWin, int Pos) {
  PARA * pPara;
  GUI_ANIM_HANDLE hAnim;

  WM_GetUserData(hWin, &pPara, sizeof(pPara));
  pPara->PosStart = pPara->yPos;
  pPara->PosDiff = Pos - pPara->PosStart;
  hAnim = GUI_ANIM_Create(PERIOD_ANIM, 25, NULL, _SliceInfo);
  GUI_ANIM_AddItem(hAnim, 0, PERIOD_ANIM, ANIM_ACCELDECEL, (void *)hWin, _AnimMoveToPosSub);
  GUI_ANIM_StartEx(hAnim, 1, NULL);
}

/*********************************************************************
*
*       _GetBarPosAndFontSize
*/
static void _GetBarPosAndFontSize(int * py0Bar, int * py1Bar, int * pFontSize) {
  int yPosLayerBar, yPosLayerSlider;

  LCDCONF_GetLayerPos(LAYER_BAR,    NULL, &yPosLayerBar);
  LCDCONF_GetLayerPos(LAYER_SLIDER, NULL, &yPosLayerSlider);
  *py0Bar = yPosLayerBar - yPosLayerSlider + IMAGE_FRAME_Y;  // First opaque pixel of bar
  *py1Bar = *py0Bar + IMAGE_SIZE_Y;                          // Last opaque pixel of bar
  *pFontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
}

/*********************************************************************
*
*       _cbAnimLayerUp
*/
static int _cbAnimLayerUp(int TimeRem, void * pVoid) {
  int xPos, yPos, Off;

  GUI_USE_PARA(pVoid);
  if (TimeRem < 0) {
    TimeRem = 0;
  }
  LCDCONF_GetLayerPos(LAYER_START, &xPos, &yPos);
  Off = (TimeRem * ANIM_START_LAYER_DIST) / PERIOD_FADE;
  LCD_SetPosEx(LAYER_START, xPos, yPos + Off);
#if USE_SOFTLAYER
  GUI_SOFTLAYER_Refresh();
#endif
  return 0;
}

/*********************************************************************
*
*       _ReplaceWindowWithButton
*/
static void _ReplaceWindowWithButton(void) {
  int xSize, ySize, FontSize, Index, yPosNew;
  PARA * pPara;
  WM_HWIN hButton;
  GUI_RECT Rect;

  if (_hWinActive == 0) {
    return; // error
  }
  WM_GetUserData(_hWinActive, &pPara, sizeof(pPara));
  Rect.x0 = WM_GetWindowOrgX(_hWinActive);
  Rect.y0 = WM_GetWindowOrgY(_hWinActive);
  xSize = WM_GetWindowSizeX(_hWinActive);
  ySize = WM_GetWindowSizeY(_hWinActive);
  Rect.x1 = Rect.x0 + xSize;
  Rect.y1 = Rect.y0 + ySize;
  //
  // Round up position
  //
  FontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
  Index = pPara->yPos / FontSize;
  yPosNew = Index * FontSize;
  if (yPosNew != pPara->yPos) {
    pPara->yPos = yPosNew;
  }
  //
  // Set callback function used for moving start layer
  //
  if ((pPara->Index == INDEX_HOUR) || (pPara->Index == INDEX_MINUTE)) {
    GUI_MEMDEV_SetAnimationCallback(_cbAnimLayerUp, NULL);
  } else {
    GUI_MEMDEV_SetAnimationCallback(_cbRefresh, NULL);
  }
  //
  // Fade out current window
  //
  _Fading = 1;
  GUI_MEMDEV_FadeOutWindow(_hWinActive, PERIOD_FADE);
  _Fading = 0;
  //
  // Delete window and create button
  //
  WM_DeleteWindow(_hWinActive);
  hButton = BUTTON_CreateUser(Rect.x0, Rect.y0, xSize, ySize, WM_HBKWIN, WM_CF_HASTRANS | WM_CF_SHOW, 0, GUI_ID_BUTTON0 + pPara->Index, 0);
  WM_SetCallback(hButton, _cbButton);
  _hWinActive = 0;
  _IndexActive = -1;
}

/*********************************************************************
*
*       _OnPaintActive
*/
static void _OnPaintActive(WM_HWIN hWin, PARA * pPara) {
  int Index, FontSize, y0Bar, y1Bar;
  GUI_RECT Rect;
  GUI_RECT RectClip;

  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();

  _GetBarPosAndFontSize(&y0Bar, &y1Bar, &FontSize);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetFont(FONT_SCROLLW);
  GUI_SetBkColor(ALPHA_ACTIVE | COLOR_GREEN);
  //
  // Reduce paint area to upper part
  //
  WM_GetWindowRect(&RectClip);
  RectClip.x1 -= RectClip.x0;
  RectClip.y1 -= RectClip.y0;
  RectClip.x0 = RectClip.y0 = 0;
  RectClip.y1 = y0Bar - 1;
  WM_SetUserClipRect(&RectClip);
  //
  // Draw upper part
  //
  Index = 0;
  Rect.y0 = y0Bar - pPara->yPos;
  Rect.y1 = Rect.y0 + FontSize - 1;
  Rect.x0 = 0;
  Rect.x1 = WM_GetWindowSizeX(hWin);
  while (Rect.y0 < y0Bar) {
    if (Index < pPara->n) {
      GUI_ClearRectEx(&Rect);
      GUI_SetTextAlign(GUI_TA_LEFT | GUI_TA_TOP);
      GUI_AA_PreserveTrans(1);
      GUI_DispStringAt(pPara->apTextSingle[Index], MARGIN_LEFT, Rect.y0);
      GUI_AA_PreserveTrans(0);
    }
    GUI_MoveRect(&Rect, 0, FontSize);
    Index++;
  }
  WM_SetUserClipRect(NULL);
  //
  // Reduce paint area to lower part
  //
  WM_GetWindowRect(&RectClip);
  RectClip.x1 -= RectClip.x0;
  RectClip.y1 -= RectClip.y0;
  RectClip.x0 = RectClip.y0 = 0;
  RectClip.y0 = y1Bar + 1;
  WM_SetUserClipRect(&RectClip);
  //
  // Draw lower part
  //
  Index = 1;
  Rect.y0 = y1Bar - pPara->yPos;
  Rect.y1 = Rect.y0 + FontSize - 1;
  Rect.x0 = 0;
  Rect.x1 = WM_GetWindowSizeX(hWin);
  do {
    if ((Index < pPara->n) && (Rect.y0 > y0Bar)) {
      GUI_ClearRectEx(&Rect);
      GUI_SetTextAlign(GUI_TA_LEFT | GUI_TA_TOP);
      GUI_AA_PreserveTrans(1);
      GUI_DispStringAt(pPara->apTextSingle[Index], MARGIN_LEFT, Rect.y0);
      GUI_AA_PreserveTrans(0);
    }
    GUI_MoveRect(&Rect, 0, FontSize);
    Index++;
  } while (Index < pPara->n);
  WM_SetUserClipRect(NULL);
}

/*********************************************************************
*
*       _SetActive
*/
static void _SetActive(PARA * pPara, int Active) {
  pPara->Active = Active;
  WM_InvalidateWindow(_ahWinBarSegment[pPara->Index]);
  if (pPara->Index == INDEX_HOUR) {
    _aPara[INDEX_MINUTE].Active = _aPara[INDEX_HOUR].Active;
  } else if (pPara->Index == INDEX_MINUTE) {
    _aPara[INDEX_HOUR].Active = _aPara[INDEX_MINUTE].Active;
  }
}

/*********************************************************************
*
*       _cbWinActive
*/
static void _cbWinActive(WM_MESSAGE * pMsg) {
  WM_PID_STATE_CHANGED_INFO * pInfoPID;
  GUI_PID_STATE * pInfo;
  WM_MOTION_INFO * pInfoMotion;
  PARA * pPara;
  WM_HWIN hWin;
  static int NoMove = 1;
  static int MotionActive;
  static WM_HTIMER hTimer;
  int y0Bar, y1Bar, SelNew, Add, FontSize, SelOld, yPos;

  hWin = pMsg->hWin;
  WM_GetUserData(hWin, &pPara, sizeof(pPara));
  switch (pMsg->MsgId) {
  case WM_TIMER:
    if (hTimer) {
      WM_DeleteTimer(hTimer);
      hTimer = 0;
    }
    if (hWin != _hWinActive) {
      return; // never reach, error
    }
    //
    // Delete window and create (invisible) button on same position
    //
    _ReplaceWindowWithButton();
    break;
  case WM_CREATE:
    hTimer = WM_CreateTimer(hWin, 0, PERIOD_STAY, 0);
    break;
  case WM_TOUCH:
    pInfo = (GUI_PID_STATE *)pMsg->Data.p;
    if (pInfo) {
      //
      // If touch is released before motion is started...
      //
      if (pInfo->Pressed == 0) {
        if (MotionActive == 0) {
          _SetActive(pPara, 0);
          WM_Invalidate(hWin);
          _InvalidateBarSegment(pPara->Index);
        }
        //
        // Special case: Slider is released exactly on a new position without
        // need to move with motion or animation.
        //
        if (pPara->Index == INDEX_PROGRAM) {
          FontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
          yPos = pPara->yPos;
          if (((yPos / FontSize) * FontSize) == yPos) {
            _ManageBackgroundPicture();
          }
        }
      }
    }
    break;
  case WM_PAINT:
    _OnPaintActive(hWin, pPara);
    break;
  case WM_DELETE:
    _SetActive(pPara, 0);
    break;
  case WM_PID_STATE_CHANGED:
    pInfoPID = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
    if ((pInfoPID->State == 1) && (pInfoPID->StatePrev == 0)) {
      _SetActive(pPara, 1);
      NoMove = 1;
    } else if ((pInfoPID->State == 0) && (pInfoPID->StatePrev == 1)) {
      if (NoMove) {
        _SetActive(pPara, 0);
        _GetBarPosAndFontSize(&y0Bar, &y1Bar, &FontSize);
        yPos = WM_GetWindowOrgY(hWin) + pInfoPID->y;
        if (yPos < y0Bar) {
          //
          // Upper area
          //
          Add = (yPos - y0Bar - FontSize) / FontSize;  // Result negative...
        } else if (yPos > y1Bar) {
          //
          // Lower area
          //
          Add = (yPos - y1Bar + FontSize) / FontSize;  // Result positive...
        } else {
          Add = 0;
        }
        if (Add) {
          SelOld = pPara->yPos / FontSize;
          SelNew = SelOld + Add;
          if (SelNew < 0) {
            SelNew = 0;
          } else if (SelNew >= pPara->n) {
            SelNew = pPara->n - 1;
          }
          //
          // If selection has changed...
          //
          if (SelNew != SelOld) {
            _AnimMoveToPos(hWin, SelNew * FontSize);
            if (pPara->Index == INDEX_PROGRAM) {
              _InvalidateBarSegment(INDEX_HOUR);
            }
          }
        }
      }
    }
    break;
  case WM_MOTION:
    //
    // Trigger timer
    //
    if (hTimer) {
      WM_RestartTimer(hTimer, PERIOD_STAY);
    }
    //
    // Process motion info
    //
    pInfoMotion = (WM_MOTION_INFO *)pMsg->Data.p;
    FontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
    switch (pInfoMotion->Cmd) {
    case WM_MOTION_INIT:
      pInfoMotion->Flags  = WM_MOTION_MANAGE_BY_WINDOW;
      pInfoMotion->SnapY  = FontSize;
      pInfoMotion->Period = PERIOD_SNAP;
      break;
    case WM_MOTION_MOVE:
      MotionActive = 1;
      NoMove = 0;
      pPara->yPos -= pInfoMotion->dy;
      if (pPara->yPos < 0) {
        pPara->yPos = 0;
      } else if (pPara->yPos > (pPara->n - 1) * FontSize) {
        pPara->yPos = (pPara->n - 1) * FontSize;
      }
      WM_InvalidateWindow(hWin);
      _InvalidateBarSegment(pPara->Index);
      if (pInfoMotion->FinalMove) {
        _SetActive(pPara, 0);
        MotionActive = 0;
        if (pPara->Index == INDEX_PROGRAM) {
          _ManageBackgroundPicture();
          _InvalidateBarSegment(INDEX_HOUR);
        }
      } else {
        _SetActive(pPara, 1);
      }
      break;
    case WM_MOTION_GETPOS:
      pInfoMotion->yPos = -pPara->yPos;
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbBarSegment
*/
static void _cbBarSegment(WM_MESSAGE * pMsg) {
  unsigned Index;
  int i, yPos, x0, FontSizeScroll, FontSizeText, DrawDouble, xOff;
  GUI_CONST_STORAGE GUI_FONT * pFont;
  PARA * pPara;

  xOff = 0;
  WM_GetUserData(pMsg->hWin, &pPara, sizeof(pPara));
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(ALPHA_BAR | COLOR_WHITE);
    GUI_Clear();
    if (pPara->Index < INDEX_HOUR) {
      GUI_SetColor(GUI_WHITE);
      GUI_DrawVLine(pPara->xSize, IMAGE_FRAME_Y, IMAGE_FRAME_Y + IMAGE_SIZE_Y - 1);
    }
    pFont = (pPara->Index >= INDEX_HOUR) ? FONT_MAG_TIME : FONT_MAG;
    GUI_SetFont(pFont);
    GUI_SetColor(COLOR_GREEN);
    FontSizeScroll = GUI_GetYSizeOfFont(FONT_SCROLLW);
    FontSizeText = GUI_GetYSizeOfFont(pFont);
    if (pPara->Index == INDEX_HOUR) {
      GUI_DispStringAt(":", pPara->xSize - 8, IMAGE_FRAME_Y + IMAGE_SIZE_Y / 2 - FontSizeText / 2 - 10);
    }
    Index = pPara->yPos / FontSizeScroll;
    yPos = (Index * FontSizeScroll - pPara->yPos) * 4 + IMAGE_SIZE_Y / 2;
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_AA_PreserveTrans(1);
    x0 = MARGIN_LEFT_MAG;
    //
    // Draw scroll window data
    //
    GUI_SetFont(pFont);
    GUI_SetColor(COLOR_GREEN);
    for (i = 0; i < 2; i++) {
      if (Index < (unsigned)pPara->n) {
        GUI_SetTextAlign(GUI_TA_VCENTER);
        DrawDouble = 0;
        if (pPara->apTextDouble) {
          if (pPara->apTextDouble[Index * 2]) {
            DrawDouble = 1;
          }
        }
        if (DrawDouble) {
          GUI_DispStringAt(pPara->apTextDouble[Index * 2 + 0], x0, yPos - FontSizeText / 2);
          GUI_DispStringAt(pPara->apTextDouble[Index * 2 + 1], x0, yPos + FontSizeText / 2);
        } else {
          GUI_DispStringAt(pPara->apTextSingle[Index], x0, yPos);
        }
      }
      yPos += FontSizeScroll * 4;
      Index++;
    }
    //
    // Draw label(s). pPara->Active could be used to hide labels during window is touched
    //
    GUI_SetFont(FONT_LABEL);
    GUI_SetColor(COLOR_BLUE);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt(pPara->pLabel, x0, 10);
    //
    // Duration
    //
    if (pPara->Index >= INDEX_HOUR) {
      switch (pPara->Index) {
      case INDEX_HOUR:
        xOff = 0;
        break;
      case INDEX_MINUTE:
        xOff = _aPara[INDEX_HOUR].xPos - _aPara[INDEX_MINUTE].xPos;
        break;
      }
      GUI_SetFont(FONT_DURATION);
      GUI_SetColor(COLOR_BLUE);
      GUI_DispStringAt("Duration:", x0 + xOff, YPOS_DURATION);
      Index = _aPara[INDEX_PROGRAM].yPos / FontSizeScroll;
      if (Index < GUI_COUNTOF(_apDuration)) {
        GUI_DispStringAt(_apDuration[Index], x0 + xOff, YPOS_DURATION + 22);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _CreateBarSegmentWindows
*/
static void _CreateBarSegmentWindows(void) {
  int OldLayer, xPosLayerBar, xPosLayerSlider, xOff;
  unsigned i;

  LCDCONF_GetLayerPos(LAYER_BAR,    &xPosLayerBar,    NULL);
  LCDCONF_GetLayerPos(LAYER_SLIDER, &xPosLayerSlider, NULL);
  OldLayer = GUI_SelectLayer(LAYER_BAR);
  xOff = xPosLayerSlider - xPosLayerBar;
  for (i = 0; i < GUI_COUNTOF(_aPara); i++) {
    _ahWinBarSegment[i] = WM_CreateWindowAsChild(_aPara[i].xPos + xOff, IMAGE_FRAME_Y, _aPara[i].xSize + 1, IMAGE_SIZE_Y, WM_HBKWIN, WM_CF_HASTRANS | WM_CF_SHOW, _cbBarSegment, sizeof(PARA *));
    WM_SetUserData(_ahWinBarSegment[i], &_apPara[i], sizeof(PARA *));
  }
  GUI_SelectLayer(OldLayer);
}

/*********************************************************************
*
*       _cbAnimLayerDown
*/
static int _cbAnimLayerDown(int TimeRem, void * pVoid) {
  int xPos, yPos, Off;

  GUI_USE_PARA(pVoid);
  if (TimeRem < 0) {
    TimeRem = 0;
  }
  LCDCONF_GetLayerPos(LAYER_START, &xPos, &yPos);
  Off = ANIM_START_LAYER_DIST - (TimeRem * ANIM_START_LAYER_DIST) / PERIOD_FADE;
  LCD_SetPosEx(LAYER_START, xPos, yPos + Off);
#if USE_SOFTLAYER
  GUI_SOFTLAYER_Refresh();
#endif
  return 0;
}

/*********************************************************************
*
*       _cbBk_SLIDER
*/
static void _cbBk_SLIDER(WM_MESSAGE * pMsg) {
  int xSize, ySize, xPos, yPos, Id, NCode;
  unsigned int Index;

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    Index = Id - GUI_ID_BUTTON0;
    switch (NCode) {
    case WM_NOTIFICATION_CLICKED:
      if ((_IndexActive != (int)Index) && (_IndexActive < (int)GUI_COUNTOF(_aPara))) {
        if (_hWinActive) {
          //
          // Delete window and create (invisible) button on same position
          //
          _ReplaceWindowWithButton();
        }
        //
        // Delete button and create data window on same position
        //
        xPos = WM_GetWindowOrgX(pMsg->hWinSrc);
        yPos = WM_GetWindowOrgY(pMsg->hWinSrc);
        xSize = WM_GetWindowSizeX(pMsg->hWinSrc);
        ySize = WM_GetWindowSizeY(pMsg->hWinSrc);
        WM_DeleteWindow(pMsg->hWinSrc);
        _hWinActive = WM_CreateWindowAsChild(xPos, yPos, xSize, ySize, pMsg->hWin, WM_CF_MOTION_Y | WM_CF_HASTRANS, _cbWinActive, sizeof(PARA *));
        _IndexActive = Index;
        _apPara[Index]->Active = 1;
        WM_SetUserData(_hWinActive, &_apPara[Index], sizeof(PARA *));
        //
        // Set callback function used for moving start layer
        //
        if ((_apPara[Index]->Index == INDEX_HOUR) || (_apPara[Index]->Index == INDEX_MINUTE)) {
          GUI_MEMDEV_SetAnimationCallback(_cbAnimLayerDown, NULL);
        } else {
          GUI_MEMDEV_SetAnimationCallback(_cbRefresh, NULL);
        }
        //
        // Fade in new window
        //
        _Fading = 1;
        GUI_MEMDEV_FadeInWindow(_hWinActive, PERIOD_FADE);
        _Fading = 0;
        //
        // Make sure background is filled with transparency
        //
        WM_Invalidate(WM_GetDesktopWindowEx(LAYER_SLIDER));
      }
      break;
    }
    break;
  case WM_PAINT:
    if (_Fading) {
      //
      // A non transparent background is required for fading operation
      //
      LCDCONF_GetLayerPos(LAYER_SLIDER, &xPos, &yPos);
      GUI_DrawBitmap(_apBitmapBk[_IndexImage], -xPos, -yPos);
    } else {
      //
      // Default behavior
      //
      GUI_SetBkColor(GUI_TRANSPARENT);
      GUI_Clear();
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _DrawBarBk
*/
static void _DrawBarBk(void) {
  int OldLayer, xPosLayerBar, xPosLayerSlider;

  LCDCONF_GetLayerPos(LAYER_BAR,    &xPosLayerBar,    NULL);
  LCDCONF_GetLayerPos(LAYER_SLIDER, &xPosLayerSlider, NULL);
  OldLayer = GUI_SelectLayer(LAYER_BAR);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_AA_PreserveTrans(1);
  GUI_DrawBitmap(&bmBar_776x173, 0, 0);
  GUI_AA_PreserveTrans(0);
  GUI_SetColor(GUI_WHITE);
  GUI_SelectLayer(OldLayer);
}

/*********************************************************************
*
*       _CreateButtons
*/
static void _CreateButtons(void) {
  int ySize, OldLayer;
  unsigned i;
  WM_HWIN hButton;

  OldLayer = GUI_SelectLayer(LAYER_SLIDER);
  ySize = LCD_GetYSize();
  for (i = 0; i < GUI_COUNTOF(_aPara); i++) {
    hButton = BUTTON_CreateUser(_aPara[i].xPos, 0, _aPara[i].xSize, ySize, WM_HBKWIN, WM_CF_HASTRANS | WM_CF_SHOW, 0, GUI_ID_BUTTON0 + i, 0);
    WM_SetCallback(hButton, _cbButton);
  }
  GUI_SelectLayer(OldLayer);
}

/*********************************************************************
*
*       _AnimMessage
*/
static void _AnimMessage(int Pos, void * pVoid) {
  WM_HWIN hDesktop;
  WM_MESSAGE Message;
  
  Message.Data.v = (Pos * 255) / GUI_ANIM_RANGE;
  Message.MsgId = APP_SET_INTENS;
  hDesktop = WM_GetDesktopWindowEx(LAYER_BACKGROUND);
  WM_SendMessage(hDesktop, &Message);
  GUI_USE_PARA(pVoid);
}

/*********************************************************************
*
*       _AnimHideMessage
*/
static void _AnimHideMessage(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimMessage(GUI_ANIM_RANGE - pInfo->Pos, pVoid);
}

/*********************************************************************
*
*       _AnimShowMessage
*/
static void _AnimShowMessage(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimMessage(pInfo->Pos, pVoid);
}

/*********************************************************************
*
*       _OnDeleteAnimMessage
*/
static void _OnDeleteAnimMessage(void * pVoid) {
  GUI_ANIM_HANDLE * phAnim;

  phAnim = (GUI_ANIM_HANDLE *)pVoid;
  *phAnim = 0;
}

/*********************************************************************
*
*       _StartAnimMessage
*/
static void _StartAnimMessage(void) {
  static GUI_ANIM_HANDLE hAnim;

  if (hAnim == 0) {
    hAnim = GUI_ANIM_Create(2500, 25, &hAnim, NULL);
    GUI_ANIM_AddItem(hAnim,    0,  300, ANIM_LINEAR, NULL, _AnimShowMessage);
    GUI_ANIM_AddItem(hAnim, 2200, 2500, ANIM_LINEAR, NULL, _AnimHideMessage);
    GUI_ANIM_StartEx(hAnim, 1, _OnDeleteAnimMessage);
  }
}

/*********************************************************************
*
*       _cbBk_START
*/
static void _cbBk_START(WM_MESSAGE * pMsg) {
  int Id, NCode;

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case GUI_ID_BUTTON0:
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
        _StartAnimMessage();
        break;
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
*       _InitStart
*/
static void _InitStart(void) {
  int OldLayer;
  GUI_RECT Rect = {0};
  WM_HWIN hButton;

  //
  // Select layer to be used
  //
  OldLayer = GUI_SelectLayer(LAYER_START);
  //
  // Fill the layer with content of start button
  //
  GUI_AA_PreserveTrans(1);
  Rect.x1 = LCD_GetXSize() - 1;
  Rect.y1 = LCD_GetYSize() - 1;
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_SetColor(COLOR_RED);
  GUI_AA_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, 10);
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(FONT_START);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringInRect("Start", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_AA_PreserveTrans(0);
  //
  // Create 'ghost' button, does not draw anything, reacts on release event only
  //
  hButton = BUTTON_Create(0, 0, Rect.x1 + 1, Rect.y1 + 1, GUI_ID_BUTTON0, WM_CF_SHOW);
  WM_SetCallback(hButton, _cbButton);
  //
  // Switch back to previous layer
  //
  GUI_SelectLayer(OldLayer);
}

/*********************************************************************
*
*       _PID_Hook
*
* Purpose:
*   Redirects input from layer 1 to layer 4 on demand
*/
static void _PID_Hook(GUI_PID_STATE * pState) {
  int xPos, yPos, xSize, ySize;

  pState->Layer = 1;
  LCD_GetPosEx(LAYER_START, &xPos, &yPos);
  xSize = LCD_GetXSizeEx(LAYER_START);
  ySize = LCD_GetYSizeEx(LAYER_START);
  if ((pState->x >= xPos) && (pState->y >= yPos) && (pState->x < (xPos + xSize)) && (pState->y < (yPos + ySize))) {
    pState->Layer = LAYER_START;
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
  int xSize, ySize, FontSize;
  unsigned i;

  _IndexActive = -1;
  GUI_Init();
  //
  // Set hook function to change layer of PID input within range of KNOB-layer
  //
  GUI_PID_SetHook(_PID_Hook);
  //
  // Initialize data and pointers
  //
  FontSize = GUI_GetYSizeOfFont(FONT_SCROLLW);
  for (i = 0; i < GUI_COUNTOF(_aPara); i++) {
    _aPara[i].yPos = _aPara[i].Start * FontSize;
    _aPara[i].Index = i;
    _apPara[i] = &_aPara[i];
  }
  //
  // Enable multi buffering and motion support
  //
  WM_MULTIBUF_Enable(1);
  WM_MOTION_Enable(1);
  //
  // Set callback functions for desktop windows
  //
  WM_SetCallback(WM_GetDesktopWindowEx(LAYER_BACKGROUND), _cbBk_BACKGROUND);
  WM_SetCallback(WM_GetDesktopWindowEx(LAYER_SLIDER),     _cbBk_SLIDER);
  WM_SetCallback(WM_GetDesktopWindowEx(LAYER_START),      _cbBk_START);
  //
  // Set size of desktop windows to layer size
  //
  for (i = 0; i < 4; i++) {
    GUI_SelectLayer(i);
    xSize = LCD_GetXSize();
    ySize = LCD_GetYSize();
    WM_SetSize(WM_HBKWIN, xSize, ySize);
  }
  GUI_SelectLayer(0);
  //
  // Initialize content of layers
  //
  _DrawBarBk();
  _InitStart();
  //
  // Create bar segment windows and buttons
  //
  _CreateBarSegmentWindows();
  _CreateButtons();
  //
  // Fade in
  //
  GUI_Exec();
  //
  // Superloop
  //
  while (1) {
    GUI_Delay(5);
  }
}

/*************************** End of file ****************************/
