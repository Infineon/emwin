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
File        : SLIDER_Private.h
Purpose     : SLIDER private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef SLIDER_PRIVATE_H
#define SLIDER_PRIVATE_H

#include "WM_Intern.h"
#include "WIDGET.h"
#include "SLIDER.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Flags
//
#define SLIDER_FLAG_DRAW_FOCUS_RECT  (1 << 0)
#define SLIDER_FLAG_INVERT_DIRECTION (1 << 1)

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  WIDGET_DRAW_ITEM_FUNC * pfDrawSkin;
} SLIDER_SKIN_PRIVATE;

typedef struct {
  U8                  Flags;
  GUI_COLOR           BkColor;
  GUI_COLOR           BarColor;
  GUI_COLOR           FocusColor;
  GUI_COLOR           TickColor;
  SLIDER_SKIN_PRIVATE SkinPrivate;
} SLIDER_PROPS;

typedef struct {
  WIDGET              Widget;
  SLIDER_PROPS        Props;
  WIDGET_SKIN const * pWidgetSkin;
  int                 NumTicks;
  int                 Max;
  int                 Min;
  int                 v;
  I16                 Width;
} SLIDER_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define SLIDER_INIT_ID(p) (p->Widget.DebugId = WIDGET_TYPE_SLIDER)
#else
  #define SLIDER_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  SLIDER_Obj * SLIDER_LockH(SLIDER_Handle h);
  #define SLIDER_LOCK_H(h)  SLIDER_LockH(h)
#else
  #define SLIDER_LOCK_H(h)  (SLIDER_Obj *)WM_LOCK_H(h)
#endif

#ifndef   SLIDER_SUPPORT_TRANSPARENCY
  #define SLIDER_SUPPORT_TRANSPARENCY WM_SUPPORT_TRANSPARENCY
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern       SLIDER_PROPS   SLIDER__DefaultProps;
extern const WIDGET_SKIN    SLIDER__SkinClassic;
extern       WIDGET_SKIN    SLIDER__Skin;
extern const WIDGET_SKIN  * SLIDER__pSkinDefault;

#endif  // GUI_WINSUPPORT
#endif  // SLIDER_PRIVATE_H

/*************************** End of file ****************************/
