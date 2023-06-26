/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2022  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.32 - Graphical user interface for embedded applications **
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
SUA period:               2009-06-12 - 2023-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : GAUGE.h
Purpose     : GAUGE public header file (API)
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef GAUGE_H
#define GAUGE_H

#include "WM.h"
#include "DIALOG_Type.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       GAUGE curved flags
*
*  Description
*    With these flags the drawing of the widget's arc lines can be set to have
*    round edges. The flags can be used upon creation of the GAUGE widget.
*/
#define GAUGE_CURVED_VALUE  (1 << 0)  // The arc that is drawn for the GAUGE's value will have a
                                      // curved edge on the beginning and end of the line.
#define GAUGE_CURVED_END    (1 << 1)  // The background arc will be drawn with a curved edge on the
                                      // beginning and end of the line.
#define GAUGE_DIRECTION_CCW (1 << 2)  // Widget works counterclockwise

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef WM_HMEM GAUGE_Handle;

/*********************************************************************
*
*       Create function(s)

  Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions
*/
GAUGE_Handle GAUGE_CreateUser    (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, int NumExtraBytes);
GAUGE_Handle GAUGE_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void GAUGE_Callback(WM_MESSAGE *pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/
void GAUGE_EnableCCW      (GAUGE_Handle hObj, int OnOff);
I32  GAUGE_GetValue       (GAUGE_Handle hObj);
void GAUGE_GetRange       (GAUGE_Handle hObj, I32 * pAng0, I32 * pAng1);
void GAUGE_SetAlign       (GAUGE_Handle hObj, int Align);
void GAUGE_SetBkColor     (GAUGE_Handle hObj, GUI_COLOR BkColor);
void GAUGE_SetColor       (GAUGE_Handle hObj, unsigned Index, GUI_COLOR Color);
void GAUGE_SetWidth       (GAUGE_Handle hObj, unsigned Index, int Width);
void GAUGE_SetOffset      (GAUGE_Handle hObj, int xOff, int yOff);
void GAUGE_SetRadius      (GAUGE_Handle hObj, int Radius);
void GAUGE_SetRange       (GAUGE_Handle hObj, I32 Ang0, I32 Ang1);
void GAUGE_SetRoundedEnd  (GAUGE_Handle hObj, int OnOff);
void GAUGE_SetRoundedValue(GAUGE_Handle hObj, int OnOff);
void GAUGE_SetValueRange  (GAUGE_Handle hObj, I32 Min, I32 Max);
void GAUGE_SetValue       (GAUGE_Handle hObj, I32 Value);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // GAUGE_H

/*************************** End of file ****************************/

