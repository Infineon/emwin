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
File        : Calibration.c
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
static WM_HWIN _hPrevWin;
static int     _aSlider[4];

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Calibration",  ID_FRAMEWIN,        0, 480, 320, 240, 0},
  { TEXT_CreateIndirect,     "Horizontal min:",0,               20,  40,  70,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,     "Horizontal max:",0,               20,  70,  70,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,     "Vertical   min:",0,               20, 100,  70,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { TEXT_CreateIndirect,     "Vertical   max:",0,               20, 130,  70,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { SLIDER_CreateIndirect,   NULL,             GUI_ID_SLIDER0, 100,  40, 100,  20 },
  { SLIDER_CreateIndirect,   NULL,             GUI_ID_SLIDER1, 100,  70, 100,  20 },
  { SLIDER_CreateIndirect,   NULL,             GUI_ID_SLIDER2, 100, 100, 100,  20 },
  { SLIDER_CreateIndirect,   NULL,             GUI_ID_SLIDER3, 100, 130, 100,  20 },
  { EDIT_CreateIndirect,     NULL ,            GUI_ID_EDIT0,   210,  40,  60,  20, 0, 0},
  { EDIT_CreateIndirect,     NULL ,            GUI_ID_EDIT1,   210,  70,  60,  20, 0, 0},
  { EDIT_CreateIndirect,     NULL ,            GUI_ID_EDIT2,   210, 100,  60,  20, 0, 0},
  { EDIT_CreateIndirect,     NULL ,            GUI_ID_EDIT3,   210, 130,  60,  20, 0, 0},
  { BUTTON_CreateIndirect,   "OK",             GUI_ID_OK,      230, 180,  60,  20 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnValueChanged
*/
static void _OnValueChanged(WM_HWIN hDlg, int Id) {
  unsigned Index, v;
  WM_HWIN hItem;
  if ((Id >= GUI_ID_SLIDER0) && (Id <= GUI_ID_SLIDER3)) {
    Index = Id - GUI_ID_SLIDER0;
    /* SLIDER-widget has changed, update EDIT-widget */
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0 + Index);
    v = SLIDER_GetValue(hItem);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + Index);
    EDIT_SetValue(hItem, v);
    _aSlider[Index] = v;
  }
}

/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hDlg, hWinSrc, hItem;
  int Id, NCode, i;
  hWinSrc = pMsg->hWinSrc;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    WM_MakeModal(hDlg);
    FRAMEWIN_SetFont(hDlg, &GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hDlg, GUI_TA_HCENTER);
    FRAMEWIN_SetClientColor(hDlg, GUI_YELLOW);
    for (i = 0; i < 4; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0 + i);
      SLIDER_SetRange(hItem, 0, 999); 
      SLIDER_SetValue(hItem, _aSlider[i]);
      hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + i);
      EDIT_SetDecMode(hItem, _aSlider[i], 0, 999, 0, 0);
      WM_DisableWindow(hItem);
    }
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(hWinSrc);                    /* Id of widget */
    NCode = pMsg->Data.v;                         /* Notification code */
    if (NCode == WM_NOTIFICATION_RELEASED) {      /* React only if released */
      if (Id == GUI_ID_OK) {                      /* OK Button */
        GUI_EndDialog(hDlg, 0);
        WM_SetFocus(_hPrevWin);
      }
    }
    if (NCode == WM_NOTIFICATION_VALUE_CHANGED) {
      _OnValueChanged(hDlg, Id);
    }
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
*       ExecCalibration
*/
void ExecCalibration(void) {
  _hPrevWin = WM_GetFocussedWindow();
  GUI_SetOrg(0, 480);
  TEXT_SetDefaultTextColor(GUI_BLACK);
  GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
  GUI_SetOrg(0, 0);
}


