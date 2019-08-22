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
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "cy_pdl.h"

#include "GUI.h"

/*********************************************************************
*
*       Function Prototypes
*/
void GUI_X_Systick_Init(void);

/*********************************************************************
*
*       Global data
*/
volatile GUI_TIMER_TIME OS_TimeMS;

/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)
*
*   Some timing dependent routines require a GetTime
*   and delay function. Default time unit (tick), normally is
*   1 ms.
*/
GUI_TIMER_TIME GUI_X_GetTime(void) { 
  return OS_TimeMS; 
}

void GUI_X_Delay(int ms) { 
  int tEnd = OS_TimeMS + ms;
  while ((tEnd - OS_TimeMS) > 0);
}

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*/
void GUI_X_Init(void) {
  GUI_X_Systick_Init();
}


/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/
void GUI_X_ExecIdle(void) {}

/*********************************************************************
*
*      Logging: OS dependent
* 
* Note:
*   Logging is used in higher debug levels only. The typical target
*   build does not use logging and does therefor not require any of
*   the logging routines below. For a release build without logging
*   the routines below may be eliminated to save some space.
*   (If the linker is not function aware and eliminates unreferenced
*   functions automatically)
*/
void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*********************************************************************
*
*         Setup Systick for timing
*
*/
/*********************************************************************
*
*       GUI_X_Systick_Intr
*
* Purpose:
*   Interrupt Service Routine for Systick.
*/
void GUI_X_Systick_Intr(void){    
  OS_TimeMS++;
}

/*********************************************************************
*
*       GUI_X_Systick_Init
*
* Purpose:
*   Set up the Systick interrupt and enable it.
*/
void GUI_X_Systick_Init(void){ 
  uint32_t i;
  //
  // Configure the SysTick timer to generate interrupt every 1 ms 
  // and start its operation.
  //
  Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_LF, 32U);
  //
  // Find unused callback slot.
  //
  for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++){
    if (Cy_SysTick_GetCallback(i) == NULL){
      //
      // Set callback
      //
      (void)Cy_SysTick_SetCallback(i, GUI_X_Systick_Intr);
      break;
    }
  }
  //
  // Assert when callback slot not found
  //
  CY_ASSERT(i < CY_SYS_SYST_NUM_OF_CALLBACKS);
  
  Cy_SysTick_Enable();
}

/*************************** End of file ****************************/
