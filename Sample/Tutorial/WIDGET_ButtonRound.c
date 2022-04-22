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
File        : WIDGET_ButtonRound.c
Purpose     : Demonstrates how to create and use a round button
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/
#include <stddef.h>
#include <string.h>
#include "WM.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _Color;
static int _Font;
static int _Pressed;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Round button sample", 0,      50,  60, 200, 120, FRAMEWIN_CF_MOVEABLE },
  { BUTTON_CreateIndirect,   "Button",   GUI_ID_BUTTON0,   100,  10,  80,  80 },
  { BUTTON_CreateIndirect,   "Callback", GUI_ID_BUTTON1,    10,  10,  60,  20 },
  { BUTTON_CreateIndirect,   "Font",     GUI_ID_BUTTON2,    10,  30,  60,  20 },
  { BUTTON_CreateIndirect,   "Color",    GUI_ID_BUTTON3,    10,  50,  60,  20 },
  { BUTTON_CreateIndirect,   "Cancel",   GUI_ID_CANCEL,     10,  70,  60,  20 }
};

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnPaint
*
* Function description
*   Paints the owner drawn button
*/
static void _OnPaint(BUTTON_Handle hObj) {
  int Index;
  char ac[50];
  GUI_RECT Rect;

  Index = (WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED) ? 1 : 0;
  WM_GetClientRect(&Rect);
  //
  // Draw filled ellipse with button background color
  //
  GUI_SetColor(BUTTON_GetBkColor(hObj, Index));
  GUI_FillEllipse(Rect.x1 / 2, Rect.y1 / 2, Rect.x1 / 2, Rect.y1 / 2);
  //
  // Draw black shape
  //
  GUI_SetColor(GUI_BLACK);
  GUI_DrawEllipse(Rect.x1 / 2, Rect.y1 / 2, Rect.x1 / 2, Rect.y1 / 2);
  //
  // Draw button text with widget attributes
  //
  GUI_SetColor(BUTTON_GetTextColor(hObj, Index));
  GUI_SetBkColor(BUTTON_GetBkColor(hObj, Index));
  GUI_SetFont(BUTTON_GetFont(hObj));
  BUTTON_GetText(hObj, ac, sizeof(ac));
  if (_Pressed) {
    strcpy(ac + strlen(ac), "\npressed");
  }
  GUI_DispStringInRect(ac, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

/*********************************************************************
*
*       _cbButton
*
* Function description 
*  1. Calls the owner draw function if the WM_PAINT message has been send
*  2. Calls the original callback for further messages
*  3. After processing the messages the function evaluates the pressed-state
*     if the WM_TOUCH message has been send
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_PAINT:
      _OnPaint(pMsg->hWin);
      break;
    default:
      BUTTON_Callback(pMsg); // The original callback
      break;
  }
  if (pMsg->MsgId == WM_TOUCH) {
    if (BUTTON_IsPressed(pMsg->hWin)) {
      if (!_Pressed) {
        _Pressed = 1;
      }
    } else {
      _Pressed = 0;
    }
  }
}

/*********************************************************************
*
*       _cbDialog
*
* Function description
*   Dialog callback routine
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  int           NCode;
  int           Id;
  WM_HWIN       hDlg;
  BUTTON_Handle hButton;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_PAINT:
      WM_DefaultProc(pMsg); // Handle dialog items
      //
      // After drawing the dialog items add some user drawn items to the window
      //
      GUI_SetPenSize(10);
      GUI_SetColor(GUI_GREEN);
      GUI_DrawLine( 95,  5, 185, 95);
      GUI_SetColor(GUI_RED);
      GUI_DrawLine( 95, 95, 185,  5);
      break;
    case WM_INIT_DIALOG:
      hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
      WM_SetHasTrans(hButton);              // Set transparency flag for button
      break;
    case WM_KEY:
      switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
        case GUI_KEY_ESCAPE:
          GUI_EndDialog(hDlg, 1);
          break;
        case GUI_KEY_ENTER:
          GUI_EndDialog(hDlg, 0);
          break;
      }
      break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
      NCode = pMsg->Data.v;                 // Notification code
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:      // React only if released
          hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
          if (Id == GUI_ID_BUTTON1) {       // Toggle callback
            if (WM_GetCallback(hButton) == _cbButton) {
              WM_SetCallback(hButton, BUTTON_Callback);
            } else {
              WM_SetCallback(hButton, _cbButton);
            }
            WM_InvalidateWindow(hButton);
          }
          if (Id == GUI_ID_BUTTON2) {       // Toggle font
            if (_Font) {
              BUTTON_SetFont(hButton, &GUI_Font13_1);
            } else {
              BUTTON_SetFont(hButton, &GUI_Font8x16);
            }
            _Font ^= 1;
          }
          if (Id == GUI_ID_BUTTON3) {       // Toggle color
            if (_Color) {
              BUTTON_SetBkColor(hButton, 0, GUI_MAKE_COLOR(0xaaaaaa));
              BUTTON_SetBkColor(hButton, 1, GUI_WHITE);
              BUTTON_SetTextColor(hButton, 0, GUI_BLACK);
              BUTTON_SetTextColor(hButton, 1, GUI_BLACK);
            } else {
              BUTTON_SetBkColor(hButton, 0, GUI_BLUE);
              BUTTON_SetBkColor(hButton, 1, GUI_RED);
              BUTTON_SetTextColor(hButton, 0, GUI_WHITE);
              BUTTON_SetTextColor(hButton, 1, GUI_YELLOW);
            }
            _Color ^= 1;
          }
          if (Id == GUI_ID_OK) {            // OK Button
            GUI_EndDialog(hDlg, 0);
          }
          if (Id == GUI_ID_CANCEL) {        // Cancel Button
            GUI_EndDialog(hDlg, 1);
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
  //
  // Use memory devices for all windows
  //
  #if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
    WM_EnableMemdev(WM_HBKWIN);
  #endif
  WM_SetDesktopColor(GUI_GREEN);
  while(1) {
    _Font = _Color = 0;
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, 0, 0, 0);
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/
