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
File        : SIMConf.c
Purpose     : Simulation configuration for softlayers.
---------------------------END-OF-HEADER------------------------------
*/

#ifdef WIN32

#include <windows.h>

#include "LCD_SIM.h"
#include "GUI_SIM_Win32.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       SIM_X_Config
*
* Function description
*   Called during the initialization process in order to configure
*   the simulator.
*/
void SIM_X_Config() {
  SIM_GUI_SetCompositeSize(480, 272);  // Set size of composite window
  SIM_GUI_SetTransMode(1, GUI_TRANSMODE_PIXELALPHA);
  SIM_GUI_SetTransMode(2, GUI_TRANSMODE_PIXELALPHA);
  SIM_GUI_SetTransMode(3, GUI_TRANSMODE_PIXELALPHA);
  SIM_GUI_ShowDevice(1);
}

#else

void SIMConf_C(void); // Avoid empty object files
void SIMConf_C(void) {}

#endif

/*************************** End of file ****************************/
