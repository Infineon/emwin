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
File        : CALENDAR_Basics.c
Purpose     : Shows how to use CALENDAR widget

Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "DIALOG.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const char * _apMonths[] = {
  "Januar",
  "Februar",
  "März",
  "April",
  "Mai",
  "Juni",
  "Juli",
  "August",
  "September",
  "Oktober",
  "November",
  "Dezember",
};

static const char * _apDays[] = {
  "Sa",
  "So",
  "Mo",
  "Di",
  "Mi",
  "Do",
  "Fr",
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetDate
*/
static void _SetDate(WM_HWIN hItem, CALENDAR_DATE * pDate) {
  do {
    if (pDate->Month > 12) {
      pDate->Year++;
      pDate->Month = 1;
    } else if (pDate->Month < 1) {
      pDate->Year--;
      pDate->Month = 12;
    }
    if (pDate->Day > CALENDAR_GetDaysOfMonth(pDate)) {
      pDate->Month++;
      pDate->Day = 1;
      continue;
    } else if (pDate->Day == 0) {
      pDate->Month--;
      pDate->Day = CALENDAR_GetDaysOfMonth(pDate);
      continue;
    }
  } while (0);
  CALENDAR_SetSel(hItem, pDate);
}

/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  int NCode, Id;
  WM_HWIN hItem;
  CALENDAR_DATE Date;

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (Id) {
    case GUI_ID_CALENDAR0:
      switch (NCode) {
      case CALENDAR_NOTIFICATION_MONTH_CLICKED:
        // TBD: Do something...
        break;
      case CALENDAR_NOTIFICATION_MONTH_RELEASED:
        // TBD: Do something...
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
        // TBD: Do something...
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // TBD: Do something...
        break;
      case WM_NOTIFICATION_CLICKED:
        // TBD: Do something...
        break;
      case WM_NOTIFICATION_RELEASED:
        // TBD: Do something...
        break;
      }
      break;
    case GUI_ID_BUTTON0:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Day++;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON1:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Day--;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON2:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Month++;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON3:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Month--;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON4:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Year++;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON5:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        Date.Year--;
        _SetDate(hItem, &Date);
        break;
      }
      break;
    case GUI_ID_BUTTON6:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CALENDAR0);
        CALENDAR_GetSel(hItem, &Date);
        CALENDAR_SetDate(hItem, &Date);
        break;
      }
      break;
    }
    break;
  case WM_PAINT:
    GUI_DrawGradientV(0, 0, LCD_GetXSize() - 1, LCD_GetYSize() - 1, GUI_MAKE_COLOR(0xA02020), GUI_BLACK);
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
  WM_HWIN hWin;
  GUI_RECT Rect;

#if GUI_SUPPORT_MEMDEV
  WM_SetCreateFlags(WM_CF_MEMDEV);  // Remove if multibuffers or driver cache is available
#endif
  GUI_Init();
  WM_SetCallback(WM_HBKWIN, _cbBk);
  CALENDAR_SetDefaultDays(_apDays);
  CALENDAR_SetDefaultMonths(_apMonths);
  CALENDAR_SetDefaultBkColor(CALENDAR_CI_WEEKEND, GUI_INVALID_COLOR);
  CALENDAR_SetDefaultBkColor(CALENDAR_CI_WEEKDAY, GUI_INVALID_COLOR);
  CALENDAR_SetDefaultColor(CALENDAR_CI_WEEKDAY, GUI_WHITE);
  CALENDAR_SetDefaultColor(CALENDAR_CI_WEEKEND, GUI_GRAY);
  CALENDAR_SetDefaultColor(CALENDAR_CI_LABEL, GUI_LIGHTBLUE);
  CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_X, 35);
  CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_Y, 25);
  CALENDAR_SetDefaultSize(CALENDAR_SI_HEADER, 40);
  CALENDAR_SetDefaultFont(CALENDAR_FI_CONTENT, GUI_FONT_COMIC18B_1);
  CALENDAR_SetDefaultFont(CALENDAR_FI_HEADER, GUI_FONT_COMIC18B_1);
  hWin = CALENDAR_Create(WM_HBKWIN, 10, 10, 2017, 9, 14, 2, GUI_ID_CALENDAR0, WM_CF_HASTRANS);
  WM_GetWindowRectEx(hWin, &Rect);
  WM_SetHasTrans(hWin);
  hWin = BUTTON_CreateUser(Rect.x1 + 20, Rect.y0, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON0, 0);
  BUTTON_SetText(hWin, "Day +");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON1, 0);
  BUTTON_SetText(hWin, "Day -");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON2, 0);
  BUTTON_SetText(hWin, "Month +");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON3, 0);
  BUTTON_SetText(hWin, "Month -");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON4, 0);
  BUTTON_SetText(hWin, "Year +");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON5, 0);
  BUTTON_SetText(hWin, "Year -");
  WM_GetWindowRectEx(hWin, &Rect);
  hWin = BUTTON_CreateUser(Rect.x0, Rect.y1 + 1 + 5, 80, 20, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON6, 0);
  BUTTON_SetText(hWin, "Set date");
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
