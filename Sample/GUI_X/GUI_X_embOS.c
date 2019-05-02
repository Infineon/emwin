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
File        : GUI_X_embOS.c
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "RTOS.h"               /* embOS include */
#include "GUI.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static OS_RSEMA  _RSema;
static OS_TASK * _pGUITask;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnExit
*/
static void _OnExit(void) {
  OS_DeleteRSema(&_RSema);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*      Timing:
*                 GUI_GetTime()
*                 GUI_Delay(int)

  Some timing dependent routines require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

GUI_TIMER_TIME GUI_X_GetTime(void) {
  return (GUI_TIMER_TIME)OS_GetTime();
}

void GUI_X_Delay(int Period) {
  OS_Delay(Period);
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*
*/
void GUI_X_ExecIdle(void) {
  OS_Delay(1);
}

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()
*
* Note:
*   The following routines are required only if emWin is used in a
*   true multi task environment, which means you have more than one
*   thread using the emWin API.
*   In this case the
*                       #define GUI_OS 1
*  needs to be in GUIConf.h
*/

void GUI_X_Unlock(void) { 
  OS_Unuse(&_RSema);
}

void GUI_X_Lock(void) {
  OS_Use(&_RSema);
}

U32  GUI_X_GetTaskId(void) {
  return (U32)OS_GetTaskID();
}

void GUI_X_InitOS(void) { 
  static GUI_REGISTER_EXIT RegisterExit;
  OS_CreateRSema(&_RSema);
  RegisterExit.pfVoid = _OnExit;
  GUI__RegisterExit(&RegisterExit);
}

/*********************************************************************
*
*      Event driving (optional with multitasking)
*
*                 GUI_X_WaitEvent()
*                 GUI_X_WaitEventTimed()
*                 GUI_X_SignalEvent()
*/

void GUI_X_WaitEvent(void)    {
  _pGUITask = OS_GetpCurrentTask();
  OS_WaitEvent(1);
}

void GUI_X_SignalEvent(void)    {
  if (_pGUITask) {
    OS_SignalEvent(1, _pGUITask);
  }
}

void GUI_X_WaitEventTimed(int Period) {
  static OS_TIMER Timer;
  static int Initialized;
  
  if (Period > 0) {
    if (Initialized != 0) {
      OS_DeleteTimer(&Timer);
    }
    Initialized = 1;
    OS_CreateTimer(&Timer, GUI_X_SignalEvent, Period);
    OS_StartTimer(&Timer);
    GUI_X_WaitEvent();
  }
}

/*********************************************************************
*
*      Keyboard input from serial input
*
* Note:
*   If embOS is used, characters typed into the log window will be placed
*   in the keyboard buffer. This is a neat feature which allows you to
*   operate your target system without having to use or even to have
*   a keyboard connected to it. (nice for demos !)
*/

static void _OnRx(OS_U8 Data) {
  #if 0
    int Key;
    switch (Data) {
    case 'y':
      Key = GUI_KEY_LEFT;
      break;
    case 'x':
      Key = GUI_KEY_RIGHT;
      break;
    case 'q':
      Key = GUI_KEY_UP;
      break;
    case 'a':
      Key = GUI_KEY_DOWN;
      break;
    case 'w':
      Key = GUI_KEY_BACKSPACE;
      break;
    default:
      Key = Data;
    }
    GUI_StoreKeyMsg(Key, 1);
  #else
    GUI_StoreKeyMsg(Data, 1);
  #endif
}

void GUI_X_Init(void) {
  OS_SetRxCallback(_OnRx);
}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically).
  If you want to use logging remove the GUI_USE_PARA macros and call
  proper logging functions (e.g. printf()).
  
*/
void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*************************** End of file ****************************/
