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
File    : DEMO_IPStats.c
Purpose : This demo shows some stats of network the hardware is
          connected to. Further it allows the user to start a VNC
          thread.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "DIALOG.h"

#include "GUIDEV_NormalMapping.h"

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_BITMAP  bmLightSource_400x400;                // Light source
extern const unsigned short          _acNormalMap_800x480[];               // Normal map
extern const unsigned char           _acBackground_800x480[100670UL + 1];  // Image (JPEG)

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ABS(v) ((v > 0) ? v : -(v))

#define NORMAL_MAP          _acNormalMap_800x480
#define BM_IMAGE            _acBackground_800x480
#define BM_LIGHT            &bmLightSource_400x400

#define Y_POS  76

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/
typedef struct {
  int xSize, ySize;
  int xPos, yPos;
  WM_HWIN hWin;
} WIN_DATA;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       _SliceInfo
*/
static void _SliceInfo(int State, void * pVoid) {
  GUI_USE_PARA(State);
  WM_InvalidateWindow(((WIN_DATA *)pVoid)->hWin);
}

/*********************************************************************
*
*       _AnimY
*/
static void _AnimY(GUI_ANIM_INFO * pInfo, void * pVoid) {
  WIN_DATA * pData;
  I32 SinHQ;
  I32 Ang;
  int yh, ya;

  pData = (WIN_DATA *)pVoid;
  Ang = (pInfo->Pos * 360) / GUI_ANIM_RANGE;
  SinHQ = GUI__SinHQ(Ang * 1000);
  yh = pData->ySize / 2;
  ya = (yh * 3) / 4;
  pData->yPos = yh + ((SinHQ * ya) >> 16);
}

/*********************************************************************
*
*       _AnimXAB
*/
static void _AnimXAB(GUI_ANIM_INFO * pInfo, void * pVoid, int v) {
  WIN_DATA * pData;
  int xh, xa;

  pData = (WIN_DATA *)pVoid;
  xh = pData->xSize / 2;
  xa = (xh * 3) / 4;
  pData->xPos = xh + v * xa - v * (pInfo->Pos * xa * 2) / GUI_ANIM_RANGE;
}

/*********************************************************************
*
*       _AnimX01
*/
static void _AnimX01(GUI_ANIM_INFO * pInfo, void * pVoid, int v) {
  WIN_DATA * pData;
  I32 CosHQ;
  I32 Ang;
  int xh, xa;

  pData = (WIN_DATA *)pVoid;
  Ang = (pInfo->Pos * 360) / GUI_ANIM_RANGE;
  CosHQ = GUI__CosHQ(Ang * 1000);
  xh = pData->xSize / 2;
  xa = (xh * 3) / 4;
  pData->xPos = xh + v * ((CosHQ * xa) >> 16);
}

/*********************************************************************
*
*       _AnimXA
*/
static void _AnimXA(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimXAB(pInfo, pVoid, +1);
}

/*********************************************************************
*
*       _AnimXB
*/
static void _AnimXB(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimXAB(pInfo, pVoid, -1);
}

/*********************************************************************
*
*       _AnimX0
*/
static void _AnimX0(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimX01(pInfo, pVoid, +1);
}

/*********************************************************************
*
*       _AnimX1
*/
static void _AnimX1(GUI_ANIM_INFO * pInfo, void * pVoid) {
  _AnimX01(pInfo, pVoid, -1);
}

/*********************************************************************
*
*       _StartAnim
*/
static void _StartAnim(WIN_DATA * pData, GUI_ANIM_HANDLE * pAnim0, GUI_ANIM_HANDLE * pAnim1) {
  U32 Duration;

  Duration = 8000;
  *pAnim0 = GUI_ANIM_Create(Duration, 20, pData, _SliceInfo);
  GUI_ANIM_AddItem(*pAnim0, 0, Duration, ANIM_LINEAR, pData, _AnimY);
  GUI_ANIM_StartEx(*pAnim0, -1, NULL);
  Duration = 7000;
  *pAnim1 = GUI_ANIM_Create(Duration * 6, 20, pData, _SliceInfo);
  GUI_ANIM_AddItem(*pAnim1, Duration * 0, Duration * 1, ANIM_ACCEL, pData, _AnimX0);
  GUI_ANIM_AddItem(*pAnim1, Duration * 1, Duration * 2, ANIM_DECEL, pData, _AnimX0);
  GUI_ANIM_AddItem(*pAnim1, Duration * 2, Duration * 3, ANIM_ACCELDECEL, pData, _AnimXA);
  GUI_ANIM_AddItem(*pAnim1, Duration * 3, Duration * 4, ANIM_ACCEL, pData, _AnimX1);
  GUI_ANIM_AddItem(*pAnim1, Duration * 4, Duration * 5, ANIM_DECEL, pData, _AnimX1);
  GUI_ANIM_AddItem(*pAnim1, Duration * 5, Duration * 6, ANIM_ACCELDECEL, pData, _AnimXB);
  GUI_ANIM_StartEx(*pAnim1, -1, NULL);
}

/*********************************************************************
*
*       _cbWin
*/
static void _cbMapping(WM_MESSAGE * pMsg) {
  GUI_PID_STATE             * pState;
  GUI_MEMDEV_Handle           hMemDest;
  GUI_MEMDEV_Handle           hMemImage;
  int                         xSize;
  int                         ySize;
  static int                  Pressed;
  static GUI_ANIM_HANDLE      hAnim0;
  static GUI_ANIM_HANDLE      hAnim1;
  static GUI_MAPPING_CONTEXT  Context;
  static WIN_DATA           * pData;
  static int                  xPos;
  static int                  yPos;
  static int                  xOff;
  static int                  yOff;
  static int                  xOld;
  static int                  yOld;
  int                         x;
  int                         y;
  int                         xAbs;
  int                         yAbs;
  WM_PID_STATE_CHANGED_INFO * pStateChange;
  static WM_HTIMER            hTimer;
  static WIN_DATA             Data;
  GUI_JPEG_INFO               Info;

  switch (pMsg->MsgId) {
  case WM_CREATE:
    xOld = 0;
    yOld = 0;
    //
    // Get screen dimension
    //
    GUI_JPEG_GetInfo(BM_IMAGE, (int)sizeof(BM_IMAGE), &Info);
    xSize = Info.XSize;
    ySize = Info.YSize;
    
    Pressed = 0;
    //
    // Create memory devices depending on Bpp and choose the proper shading routine
    //
    hMemDest   = GUI_MEMDEV_CreateFixed(0, 0, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_16, GUICC_M565);
    hMemImage  = GUI_MEMDEV_CreateFixed(0, 0, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_16, GUICC_M565);
    //
    // Fill memdev with image data
    //
    GUI_MEMDEV_Select(hMemImage);
    GUI_JPEG_Draw(BM_IMAGE, (int)sizeof(BM_IMAGE), 0, 0);
    GUI_MEMDEV_Select(0);
    Context.hMemDest  = hMemDest;
    Context.hMemImage = hMemImage;
    Context.pbmLight  = NULL;
    Context.pNMap     = NORMAL_MAP;
    Context.xSize     = xSize;
    Context.ySize     = ySize;
    GUI_MEMDEV_NormalMapping(&Context, Data.xPos, Data.yPos);
    Context.pbmLight  = BM_LIGHT;
    //
    // Set up animation
    //
    pData = &Data;
    pData->xSize = xSize;
    pData->ySize = ySize;
    pData->hWin = pMsg->hWin;
    _StartAnim(pData, &hAnim0, &hAnim1);
    break;
  case WM_USER_DATA:
    WM_GetUserData(pMsg->hWin, &pData, sizeof(pData));
    break;
  case WM_TIMER:
    if (xOff || yOff) {
      xOff = (xOff * 900) / 1000;
      yOff = (yOff * 900) / 1000;
      WM_RestartTimer(hTimer, 0);
    } else {
      if (hTimer) {
        WM_DeleteTimer(hTimer);
        hTimer = 0;
      }
    }
    break;
  case WM_TOUCH:
    pState = (GUI_PID_STATE *)pMsg->Data.p;
    if (pState) {
      if (pState->Pressed) {
        xPos = pState->x;
        yPos = pState->y;
      } else {
        Pressed = 0;
        xOff = pState->x - pData->xPos;
        yOff = pState->y - pData->yPos;
        hTimer = WM_CreateTimer(pMsg->hWin, 0, 20, 0);
      }
    }
    break;
  case WM_PID_STATE_CHANGED:
    pStateChange = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
    if ((pStateChange->State == 1) && (pStateChange->StatePrev == 0)) {
      xPos = pStateChange->x;
      yPos = pStateChange->y;
      Pressed = 1;
      WM_SetCapture(pMsg->hWin, 1);
    }
    break;
  case WM_PAINT:
    if (Pressed) {
      x = xPos;
      y = yPos;
    } else {
      x = pData->xPos + xOff;
      y = pData->yPos + yOff;
    }
    if (x && y) {
      xAbs = ABS(x - xOld);
      yAbs = ABS(y - yOld);
      if ((xAbs > 64) || (yAbs > 64)) {
        Context.pbmLight  = NULL;
        GUI_MEMDEV_NormalMapping(&Context, Data.xPos, Data.yPos);
        Context.pbmLight  = BM_LIGHT;
      }
      GUI_MEMDEV_NormalMapping(&Context, x, y);
    }
    xOld = x;
    yOld = y;
    x = WM_GetWindowOrgX(pMsg->hWin);
    y = WM_GetWindowOrgY(pMsg->hWin);
    GUI_MEMDEV_WriteAt(Context.hMemDest, x, y);
    break;
  case WM_DELETE:
    GUI_ANIM_Stop(hAnim0);
    GUI_ANIM_Stop(hAnim1);
    GUI_ANIM_Delete(hAnim0);
    GUI_ANIM_Delete(hAnim1);
    GUI_MEMDEV_Delete(Context.hMemDest);
    GUI_MEMDEV_Delete(Context.hMemImage);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
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
  int xSize, ySize;

  GUI_Init();
  WM_MULTIBUF_Enable(1);
  //
  // Set hook function to change layer of PID input within range of KNOB-layer
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  WM_CreateWindowAsChild(0, 0, xSize, ySize, WM_HBKWIN, WM_CF_SHOW, _cbMapping, 0);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
