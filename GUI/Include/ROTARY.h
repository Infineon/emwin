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

** emWin V6.26 - Graphical user interface for embedded applications **
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
                          and Amendment Number Three, signed May 2nd, 2022 and May 5th, 2022
Licensed platform:        Any Cypress platform (Initial targets are: PSoC3, PSoC5)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : ROTARY.h
Purpose     : ROTARY include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef ROTARY_H
#define ROTARY_H

#include "WM.h"
#include "DIALOG_Type.h"      // Req. for Create indirect data structure
#include "WIDGET.h"

#if (GUI_SUPPORT_MEMDEV && GUI_WINSUPPORT)

#if defined(__cplusplus)
  extern "C" {                  // Make sure we have C-declarations in C++ programs
#endif

/*********************************************************************
*
*       Public Types
*
**********************************************************************
*/
typedef WM_HMEM ROTARY_Handle;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/
ROTARY_Handle ROTARY_CreateEx      (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int Id);
ROTARY_Handle ROTARY_CreateUser    (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int Id, int NumExtraBytes);
ROTARY_Handle ROTARY_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void ROTARY_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/
void ROTARY_AddValue     (ROTARY_Handle hObj, I32 Delta);
void ROTARY_AddAngle     (ROTARY_Handle hObj, I32 Delta);
void ROTARY_EnableLQ     (ROTARY_Handle hObj, int OnOff);
I32  ROTARY_GetAngle     (ROTARY_Handle hObj);
int  ROTARY_GetImageSize (ROTARY_Handle hObj, int * pxSize, int * pySize);
int  ROTARY_GetMarkerSize(ROTARY_Handle hObj, int * pxSize, int * pySize);
int  ROTARY_GetUserData  (ROTARY_Handle hObj, void * pDest, int NumBytes);
I32  ROTARY_GetValue     (ROTARY_Handle hObj);
void ROTARY_SetAlign     (ROTARY_Handle hObj, int Align, int xOff, int yOff);
void ROTARY_SetAngle     (ROTARY_Handle hObj, I32 Pos);
void ROTARY_SetBitmap    (ROTARY_Handle hObj, const GUI_BITMAP * pBitmap);
void ROTARY_SetBitmapObj (ROTARY_Handle hObj, GUI_DRAW_HANDLE hDrawObj);
void ROTARY_SetDoRotate  (ROTARY_Handle hObj, U8 DoRotate);
void ROTARY_SetMarker    (ROTARY_Handle hObj, const GUI_BITMAP * pBitmap, int Radius, I32 AngleOffset, U8 DoRotate);
void ROTARY_SetMarkerObj (ROTARY_Handle hObj, GUI_DRAW_HANDLE hDrawObjMarker, GUI_DRAW_HANDLE hDrawObjMarkerHR, int Radius, I32 Offset, U8 DoRotate);
void ROTARY_SetOffset    (ROTARY_Handle hObj, int Offset);
void ROTARY_SetPeriod    (ROTARY_Handle hObj, I32 Period);
void ROTARY_SetRadius    (ROTARY_Handle hObj, int Radius);
void ROTARY_SetRange     (ROTARY_Handle hObj, U32 AngPositive, U32 AngNegative);
void ROTARY_SetSnap      (ROTARY_Handle hObj, I32 Snap);
void ROTARY_SetTickSize  (ROTARY_Handle hObj, I32 TickSize);
int  ROTARY_SetUserData  (ROTARY_Handle hObj, const void * pSrc, int NumBytes);
void ROTARY_SetValue     (ROTARY_Handle hObj, I32 Value);
int  ROTARY_SetValueRange(ROTARY_Handle hObj, I32 Min, I32 Max);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

#if defined(__cplusplus)
  }
#endif

#endif  // (GUI_SUPPORT_MEMDEV && GUI_WINSUPPORT)
#endif  // ROTARY_H

/*************************** End of file ****************************/
