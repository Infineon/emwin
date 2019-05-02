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
File        : Setup.c
Purpose     : TBD
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "Main.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Dialog IDs
*/
#define ID_FRAMEWIN              1

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static char    _IsInited;
static WM_HWIN _hDlg;
static WM_HWIN _hPrevWin;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Setup",   ID_FRAMEWIN,     0, 240, 320, 240, 0},
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK0,  50,  40, 150,   0 },
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK1,  50,  70, 150,   0 },
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK2,  50, 100, 150,   0 },
  { TEXT_CreateIndirect,     "User ID:",0,              50, 130,  40,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { EDIT_CreateIndirect,     NULL,      GUI_ID_EDIT0,   95, 130, 100,  20 },
  { BUTTON_CreateIndirect,   "OK",      GUI_ID_OK,     230, 140,  60,  20 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hDlg, hWinSrc, hItem;
  int Id, NCode;
  hWinSrc = pMsg->hWinSrc;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    FRAMEWIN_SetFont(hDlg, &GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hDlg, GUI_TA_HCENTER);
    FRAMEWIN_SetClientColor(hDlg, GUI_RED);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK0); CHECKBOX_SetText(hItem, "Enable alarm");
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK1); CHECKBOX_SetText(hItem, "Enable display lighting");
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK2); CHECKBOX_SetText(hItem, "Enable color mode");
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    if (NCode == WM_NOTIFICATION_RELEASED) {      /* React only if released */
      if (Id == GUI_ID_OK) {            /* OK Button */
        GUI_SetOrg(0, 0);
        WM_SetFocus(_hPrevWin);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _Init
*/
static void _Init(void) {
  if (_IsInited) {
    return;
  }
  _IsInited = 1;
  CHECKBOX_SetDefaultTextColor(GUI_WHITE);
  CHECKBOX_SetDefaultBkColor(GUI_INVALID_COLOR);
  CHECKBOX_SetDefaultFocusColor(GUI_WHITE);
  TEXT_SetDefaultTextColor(GUI_WHITE);
  _hDlg = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       ExecSetup
*/
void ExecSetup(void) {
  _hPrevWin = WM_GetFocussedWindow();
  _Init();
  GUI_SetOrg(0, 240);
  WM_SetFocus(_hDlg);
}


