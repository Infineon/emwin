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
File        : CHECKBOX_Private.h
Purpose     : CHECKBOX private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHECKBOX_PRIVATE_H
#define CHECKBOX_PRIVATE_H

#include "WM_Intern.h"
#include "WM.h"
#include "WIDGET.h"
#include "CHECKBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#ifndef   CHECKBOX_BKCOLOR0_DEFAULT
  #define CHECKBOX_BKCOLOR0_DEFAULT 0x808080           /* Inactive color */
#endif

#ifndef   CHECKBOX_BKCOLOR1_DEFAULT
  #define CHECKBOX_BKCOLOR1_DEFAULT GUI_WHITE          /* Active color */
#endif

#ifndef   CHECKBOX_FGCOLOR0_DEFAULT
  #define CHECKBOX_FGCOLOR0_DEFAULT 0x101010
#endif

#ifndef   CHECKBOX_FGCOLOR1_DEFAULT
  #define CHECKBOX_FGCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef   CHECKBOX_DEFAULT_SIZE
  #define CHECKBOX_DEFAULT_SIZE          15
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  unsigned              (* pfGetButtonSize)(void);
  WIDGET_DRAW_ITEM_FUNC  * pfDrawSkin;
} CHECKBOX_SKIN_PRIVATE;

typedef struct {
  const GUI_FONT      * pFont;
  GUI_COLOR             aBkColorBox[2]; /* Colors used to draw the box background */
  GUI_COLOR             BkColor;        /* Widget background color */
  GUI_COLOR             TextColor;
  GUI_COLOR             FocusColor;
  CHECKBOX_SKIN_PRIVATE SkinPrivate;
  I16                   Align;
  U8                    Spacing;
  const GUI_BITMAP    * apBm[6];
} CHECKBOX_PROPS;

typedef struct {
  WIDGET              Widget;
  CHECKBOX_PROPS      Props;
  WIDGET_SKIN const * pWidgetSkin;
  U8                  NumStates;
  U8                  CurrentState;
  WM_HMEM             hpText;
  U32                 ButtonSize;
} CHECKBOX_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define CHECKBOX_INIT_ID(p) (p->Widget.DebugId = WIDGET_TYPE_CHECKBOX)
#else
  #define CHECKBOX_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  CHECKBOX_Obj * CHECKBOX_LockH(CHECKBOX_Handle h);
  #define CHECKBOX_LOCK_H(h)   CHECKBOX_LockH(h)
#else
  #define CHECKBOX_LOCK_H(h)   (CHECKBOX_Obj *)WM_LOCK_H(h)
#endif

/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
unsigned CHECKBOX__GetButtonSize(void);

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern CHECKBOX_PROPS      CHECKBOX__DefaultProps;

extern const WIDGET_SKIN   CHECKBOX__SkinClassic;
extern       WIDGET_SKIN   CHECKBOX__Skin;

extern WIDGET_SKIN const * CHECKBOX__pSkinDefault;

/*********************************************************************
*
*       Extern data
*
**********************************************************************
*/
extern const GUI_BITMAP    CHECKBOX__abmCheck[2];

#endif   /* GUI_WINSUPPORT */
#endif   /* CHECKBOX_PRIVATE_H */

/*************************** End of file ****************************/
