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
File        : GUI_X_FreeRTOS.c
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "GUI.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static SemaphoreHandle_t _Semaphore;

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

int GUI_X_GetTime(void) {
  return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void GUI_X_Delay(int Period) {
  vTaskDelay(Period / portTICK_PERIOD_MS);
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*
*/
void GUI_X_ExecIdle(void) {
  vTaskDelay(1 / portTICK_PERIOD_MS);
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
void GUI_X_InitOS(void)    { _Semaphore = xSemaphoreCreateMutex(); }
void GUI_X_Unlock(void)    { xSemaphoreGive(_Semaphore); }
void GUI_X_Lock(void)      { xSemaphoreTake(_Semaphore, portMAX_DELAY);  }
U32  GUI_X_GetTaskId(void) { return (U32)xTaskGetCurrentTaskHandle(); }

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/
#define OS_SendString(s) GUI_USE_PARA(s)
void GUI_X_Log     (const char *s) { printf(s); }
void GUI_X_Warn    (const char *s) { printf(s); }
void GUI_X_ErrorOut(const char *s) { printf(s); }

/*********************************************************************
*
*      GUI_X_Init()
*
* Note:
*   This routine is called from GUI_Init() in any case whether there
*   is an RTOS or not. You can use it for additional initializations
*   needed.
*/

void GUI_X_Init(void) {
}

/*************************** End of file ****************************/
