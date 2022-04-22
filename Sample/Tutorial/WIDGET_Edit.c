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
File        : WIDGET_Edit.c
Purpose     : Example demonstrating the use of a EDIT widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include "GUI.h"
#include "EDIT.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define WM_APP_SHOW_TEXT (WM_USER + 0)
#define TEXT_MAXLEN      40

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  static WM_HWIN hEdit;
  static U8      ShowText;
  char           aBuffer[TEXT_MAXLEN];

  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_DARKGRAY);
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WIDGET_Edit - Sample", 160, 5);
    GUI_SetFont(&GUI_Font8x16);
    if (ShowText) {
      GUI_DispStringHCenterAt("The string you have modified is:", 160, 90);
      EDIT_GetText(hEdit, aBuffer, TEXT_MAXLEN);
      GUI_DispStringHCenterAt(aBuffer, 160, 110);
    } else {
      GUI_DispStringHCenterAt("Use keyboard to modify string...", 160, 90);
    }
    break;
  case WM_APP_SHOW_TEXT:
    if (hEdit == 0) {
      hEdit = pMsg->hWinSrc;
    }
    WM_HideWindow(hEdit);
    ShowText = 1;
    WM_InvalidateWindow(WM_HBKWIN);
    WM_CreateTimer(WM_HBKWIN, 0, 3000, 0);
    break;
  case WM_TIMER:
    ShowText = 0;
    WM_InvalidateWindow(WM_HBKWIN);
    WM_ShowWindow(hEdit);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbEdit
*/
static void _cbEdit(WM_MESSAGE * pMsg) {
  const WM_KEY_INFO * pInfo;
  WM_MESSAGE          Msg;

  switch (pMsg->MsgId) {
  case WM_KEY:
    pInfo = (WM_KEY_INFO *)pMsg->Data.p;
    if (pInfo->Key == GUI_KEY_ENTER) {
      if (pInfo->PressedCnt == 0) {
        Msg.MsgId   = WM_APP_SHOW_TEXT;
        Msg.hWinSrc = pMsg->hWin;
        WM_SendMessage(WM_HBKWIN, &Msg);
        return;
      }
    }
  }
  EDIT_Callback(pMsg);
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
  EDIT_Handle hEdit;

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBk);
  hEdit = EDIT_CreateEx(50, 110, 220, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_EDIT0, TEXT_MAXLEN);
  WM_SetCallback(hEdit, _cbEdit);
  EDIT_SetText(hEdit, "Press <ENTER> when done...");
  EDIT_SetFont(hEdit, &GUI_Font8x16);
  EDIT_SetTextColor(hEdit, 0, GUI_RED);
  EDIT_EnableBlink(hEdit, 300, 1);
  WM_SetFocus(hEdit);
  while (1) {
    GUI_Delay(10);
  }
}

/*************************** End of file ****************************/
