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
File        : WIDGET_Multipage.c
Purpose     : Demonstrates the use of the MULTIPAGE widget
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"
#include "MULTIPAGE.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       Dialog resource
*
*  These tables contain the information required to create the dialogs.
*  It has been created manually, but could also be created by the GUIBuilder.
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = {
  { WINDOW_CreateIndirect,    "Dialog 1", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { BUTTON_CreateIndirect,    "Button",   GUI_ID_BUTTON0,      5,  30,  80,  20, 0},
  { TEXT_CreateIndirect,      "Dialog 1", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate2[] = {
  { WINDOW_CreateIndirect,    "Dialog 2", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { CHECKBOX_CreateIndirect,  "",         GUI_ID_CHECK0,       5,  30,   0,   0, 0},
  { CHECKBOX_CreateIndirect,  "",         GUI_ID_CHECK1,       5,  50,   0,   0, 0},
  { TEXT_CreateIndirect,      "Select 0", GUI_ID_TEXT0,       25,  30,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Select 1", GUI_ID_TEXT1,       25,  50,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Dialog 2", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate3[] = {
  { WINDOW_CreateIndirect,    "Dialog 3", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { RADIO_CreateIndirect,     "",         GUI_ID_RADIO0,       5,  30,   0,   0, 0, 3},
  { TEXT_CreateIndirect,      "Option 1", GUI_ID_TEXT0,       25,  30,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Option 2", GUI_ID_TEXT1,       25,  50,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Option 3", GUI_ID_TEXT2,       25,  70,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Dialog 3", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
  { WINDOW_CreateIndirect,    "Dialog 4", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { MULTIEDIT_CreateIndirect, "Text",     GUI_ID_MULTIEDIT0,   5,  30, 200,  40  },
  { TEXT_CreateIndirect,      "Dialog 4", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate5[] = {
  { WINDOW_CreateIndirect,    "Dialog 5", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { SLIDER_CreateIndirect,    "",         GUI_ID_SLIDER0,      5,  30, 200,  40  },
  { TEXT_CreateIndirect,      "Dialog 5", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate6[] = {
  { WINDOW_CreateIndirect,    "Dialog 6", 0,                   0,   0, 260, 100, FRAMEWIN_CF_MOVEABLE },
  { SCROLLBAR_CreateIndirect, "",         GUI_ID_SCROLLBAR0,   5,  30, 200,  40  },
  { TEXT_CreateIndirect,      "Dialog 6", 0,                   5,  10,  50,  20, TEXT_CF_LEFT }
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialog4
*/
static void _cbDialog4(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hDlg;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
    MULTIEDIT_SetText(hItem, "MULTIEDIT widget");
    MULTIEDIT_SetInsertMode(hItem, 1);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbBkWindow
*
*  Function description
*    Callback routine of the background window.
*    It shows the sample title and draws the background.
*/
static void _cbBkWindow(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WIDGET_Multipage - Sample", 160, 5);
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
  WM_HWIN hMultiPage;
  WM_HWIN hFrameWin;
  WM_HWIN hDialog;

  //
  // Enable use of memory devices
  //
  WM_SetCreateFlags(WM_CF_MEMDEV);
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  //
  // Create the frame window
  //
  hFrameWin = FRAMEWIN_Create("FrameWindow", NULL, WM_CF_SHOW, 40, 44, 240, 152);
  FRAMEWIN_SetClientColor(hFrameWin, GUI_GREEN);
  FRAMEWIN_SetActive(hFrameWin, 1);
  FRAMEWIN_SetMoveable(hFrameWin, 1);
  //
  // Create the MULTIPAGE widget
  //
  hMultiPage = MULTIPAGE_CreateEx(7, 6, 220, 120, WM_GetClientWindow(hFrameWin), WM_CF_SHOW, 0, 0);
  GUI_Delay(500);
  //
  // Create and attach the MULTIPAGE dialog windows
  //
  hDialog = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), NULL,       WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 1");
  GUI_Delay(500);
  hDialog = GUI_CreateDialogBox(_aDialogCreate2, GUI_COUNTOF(_aDialogCreate2), NULL,       WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 2");
  GUI_Delay(500);
  hDialog = GUI_CreateDialogBox(_aDialogCreate3, GUI_COUNTOF(_aDialogCreate3), NULL,       WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 3");
  GUI_Delay(500);
  hDialog = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbDialog4, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 4");
  GUI_Delay(500);
  hDialog = GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), NULL,       WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 5");
  GUI_Delay(500);
  hDialog = GUI_CreateDialogBox(_aDialogCreate6, GUI_COUNTOF(_aDialogCreate6), NULL,       WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialog, "Page 6");
  GUI_Delay(500);
  //
  // Demonstrate the use of MULTIPAGE_SetAlign
  //
  MULTIPAGE_SetAlign(hMultiPage, MULTIPAGE_ALIGN_RIGHT);
  GUI_Delay(500);
  MULTIPAGE_SetAlign(hMultiPage, MULTIPAGE_ALIGN_RIGHT | MULTIPAGE_ALIGN_BOTTOM);
  GUI_Delay(500);
  MULTIPAGE_SetAlign(hMultiPage, MULTIPAGE_ALIGN_LEFT | MULTIPAGE_ALIGN_BOTTOM);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
