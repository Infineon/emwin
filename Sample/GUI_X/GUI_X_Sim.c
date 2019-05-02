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
File        : GUI_X.C
Purpose     : COnfig / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "SIM.h"
#include "GUI.h"
#include "windows.h"


/*********************************************************************
*
*       GUI_X_Init()
*/
void GUI_X_Init(void) {};

/*********************************************************************
*
*       GUI_X_ExecIdle()
*/
void GUI_X_ExecIdle(void) {
  SIM_GUI_ExecIdle();
};


/*********************************************************************
*
*      Timing:
*                 GUI_GetTime()
*                 GUI_Delay(int)

  Some timing dependent routines of the GUI require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

GUI_TIMER_TIME GUI_X_GetTime(void) {
  return SIM_GUI_GetTime();
}

void GUI_X_Delay(int Period) {
  SIM_GUI_Delay(Period);
}

/*********************************************************************
*
*      Multitask interface for Win32
*
*  The folling section consisting of 4 routines is used to make
*  the GUI software thread safe with WIN32
*/

static HANDLE hMutex;
static int _EntranceCnt;   // For debugging only ... Not required

void GUI_X_InitOS(void) {
  hMutex = CreateMutex(NULL, 0, "GUI Simulation - Mutex");
}

U32 GUI_X_GetTaskId(void) {
  return GetCurrentThreadId();
}

void GUI_X_Lock(void) {
  WaitForSingleObject(hMutex, INFINITE);
  if (++_EntranceCnt > 1) {
    SIM_ErrorOut("Error in GUITASK.c module ...");
  }
}

void GUI_X_Unlock(void) {
  _EntranceCnt--;
  ReleaseMutex(hMutex);
}


/*********************************************************************
*
*      Text output for Logging, warnings and errors

  Logging - required only for higher debug levels
*/
void GUI_X_Log     (const char *s)     { SIM_Log(s); }
void GUI_X_Warn    (const char *s)     { SIM_Warn(s); }
void GUI_X_ErrorOut(const char *s)     { SIM_ErrorOut(s); }







