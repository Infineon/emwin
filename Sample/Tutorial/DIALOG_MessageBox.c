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
File        : DIALOG_MessageBox.c
Purpose     : Example demonstrating GUI_MessageBox
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "WM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 10)

/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_RED);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("DIALOG_MessageBox - Sample", 160, 5);
    break;
  default:
    WM_DefaultProc(pMsg);
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
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  #if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif
  WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
  //
  // Create message box and wait until it is closed
  //
  while (1) {
    GUI_MessageBox("This text is shown\nin a message box",
                   "Caption/Title", GUI_MESSAGEBOX_CF_MOVEABLE);
    GUI_Delay(750);                    // Wait for a short moment ...
    GUI_MessageBox("New message !",
                   "Caption/Title", GUI_MESSAGEBOX_CF_MOVEABLE);
    GUI_Delay(750);
  }
}

/*************************** End of file ****************************/

