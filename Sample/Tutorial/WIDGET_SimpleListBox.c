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
File        : WIDGET_SimpleListBox.c
Purpose     : Example demonstrating the LISTBOX widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "LISTBOX.h"
#include <stddef.h>

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

/*******************************************************************
*
*       Static data
*
********************************************************************
*/
static const GUI_ConstString _ListBox[] = {
  "English", "Deutsch", "Français", "Japanese", "Italiano", NULL
};

/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*******************************************************************
*
*       _DemoListBox
*/
static void _DemoListBox(void) {
  int            i;
  int            Entries;
  int            ySize;
  LISTBOX_Handle hListBox;
  
  Entries = GUI_COUNTOF(_ListBox) - 1;
  ySize   = GUI_GetYDistOfFont(&GUI_Font13B_1) * Entries;
  //
  // Create the listbox
  //
  hListBox = LISTBOX_Create(_ListBox, 130, 80, 60, ySize, WM_CF_SHOW);
  //
  // Change current selection of the listbox
  //
  for (i = 0; i < Entries-1; i++) {
    GUI_Delay(500);
    LISTBOX_IncSel(hListBox);
    WM_ExecIdle();
	}
  for (i = 0; i < Entries-1; i++) {
    GUI_Delay(500);
    LISTBOX_DecSel(hListBox);
    WM_ExecIdle();
	}
  GUI_Delay(750);
  //
  // Delete listbox widget
  //
  WM_DeleteWindow(hListBox);
  GUI_ClearRect(0, 50, 319, 239);
  GUI_Delay(750);
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
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WIDGET_SimpleListBox - Sample", 160, 5);
  while(1) {
    _DemoListBox();
  }
}

/*************************** End of file ****************************/

