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
File        : MOTION_MovingWindow.c
Purpose     : Shows how to use simple motion support
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)

/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
#include "WM.h"

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  int Axis;
  int Speed;
} PARA;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const PARA _aPara[] = {
  { GUI_COORD_X, +100 },
  { GUI_COORD_Y, +100 },
  { GUI_COORD_X, -100 },
  { GUI_COORD_Y, -100 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbWin0
*/
static void _cbWin0(WM_MESSAGE * pMsg) {
  int xSize, ySize;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    xSize = LCD_GetXSize();
    ySize = LCD_GetYSize();
    GUI_DrawGradientV(0, 0, xSize, ySize, GUI_BLUE, GUI_BLACK);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringHCenterAt("WM_Motion - Sample", 160, 5);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbWin1
*/
static void _cbWin1(WM_MESSAGE * pMsg) {
  int xSize, ySize;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    xSize = WM_GetWindowSizeX(pMsg->hWin);
    ySize = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DrawGradientV(0, 0, xSize, ySize, GUI_DARKGREEN, GUI_DARKRED);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringHCenterAt("I am a window", xSize >> 1, 5);
    GUI_DispStringHCenterAt("Try to catch me", xSize >> 1, 15);
    GUI_DispStringAt("xPos: ", 20, 30);
    GUI_DispDec(WM_GetWindowOrgX(pMsg->hWin), 3);
    GUI_DispStringAt("yPos: ", 20, 40);
    GUI_DispDec(WM_GetWindowOrgY(pMsg->hWin), 3);
    GUI_SetColor(GUI_GRAY);
    GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
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
  WM_HWIN  hWin0;
  WM_HWIN  hWin1;
  int      xSize, ySize;
  unsigned i;

  WM_SetCreateFlags(WM_CF_MEMDEV);
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_MOTION_Enable(1);
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  hWin0 = WM_CreateWindowAsChild(0, 0, xSize, ySize, WM_HBKWIN, WM_CF_SHOW, _cbWin0, 0);
  hWin1 = WM_CreateWindowAsChild(10, 30, 120, 60, hWin0, WM_CF_SHOW | WM_CF_MOTION_X | WM_CF_MOTION_Y, _cbWin1, 0);
  while (1) {
    for (i = 0; i < GUI_COUNTOF(_aPara); i++) {
      WM_MOTION_SetSpeed(hWin1, _aPara[i].Axis, _aPara[i].Speed);
      GUI_Delay(1000);
      WM_MOTION_SetDeceleration(hWin1, _aPara[i].Axis, 100);
      GUI_Delay(1000);
    }
  }
}

/*************************** End of file ****************************/
