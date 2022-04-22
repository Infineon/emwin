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
File        : WIDGET_Spinbox.c
Purpose     : Shows how to use the SPINBOX widget.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "DIALOG.h"

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

#define COLOR_GREEN     GUI_MAKE_COLOR(0x14FF39)  // Define a color
#define NUM_SEPARATORS  3                         // Number of available separators
#define NUM_ITEMS       5                         // Number of available items

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// This array contains information about each item
//
static const char * paItemText[3][5] = {
  {
  "Wifi",
  "Mobile Data",
  "Bluetooth",
  "Hot Spot",
  "Mobil",
  },
  {
  "Brightness",
  "Background",
  "Idle",
  "Night Mode",
  "Font Size",
  },
  {
  "Account",
  "Sound",
  "Memory",
  "Alert",
  "Clock",
  },
};

//
// Information about the separators
//
static const char * paSeperatorText[] = {
  "Network",
  "Display",
  "Settings"
};

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_HWIN hSwipelist;
  WM_HWIN hItem;
  int     i;
  int     j;

#ifdef WIN32
  WM_SetCreateFlags(WM_CF_MEMDEV);  // Automatic use of memory devices in simulation
#else
  WM_MULTIBUF_Enable(1);            // Automatic use of multi buffering on hardware
#endif
  GUI_Init();                       // Initialize the GUI
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_MOTION_Enable(1);              // Enable motion support
  WM_SetBkWindowColor(GUI_BLACK);   // Set a default background color
  //
  // Set default color for selected items and separators
  //
  SWIPELIST_SetDefaultBkColor(SWIPELIST_CI_BK_ITEM_SEL, COLOR_GREEN);
  SWIPELIST_SetDefaultBkColor(SWIPELIST_CI_BK_SEP_ITEM, GUI_DARKGRAY);
  //
  // Create a swipelist
  //
  hSwipelist = SWIPELIST_CreateEx(10, 10, 200, 220, WM_HBKWIN, WM_CF_SHOW, 0, 0);
  WM_MOTION_SetMoveable(hSwipelist, WM_CF_MOTION_Y, 1);
  //
  // Add separators and five items under each
  //
  for (j = 0; j < NUM_SEPARATORS; j++) {
    SWIPELIST_AddSepItem(hSwipelist, paSeperatorText[j], 35);
    for (i = 0; i < NUM_ITEMS; i++) {
      SWIPELIST_AddItem(hSwipelist, paItemText[j][i], 35);
    }
  }
  //
  // Attaching a checkbox to each of the first five items
  //
  for (i = 0; i < 5; i++) {
    hItem = CHECKBOX_Create(0, 0, 15, 15, WM_HBKWIN, 0, WM_CF_SHOW);
    SWIPELIST_ItemAttachWindow(hSwipelist, 1 + i, hItem, 180, 10);
  }
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/

