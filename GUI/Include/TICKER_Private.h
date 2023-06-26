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
File        : TICKER.h
Purpose     : TICKER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef TICKER_PRIVATE_H
#define TICKER_PRIVATE_H

#include "WM_Intern.h"
#include "TICKER.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  const GUI_FONT * pFont;
  GUI_COLOR        TextColor;
  GUI_COLOR        BkColor;
  GUI_COLOR        FrameColor;
  U16              TickerDist;
  int              AnimPeriod;
  U16              AnimDist;
} TICKER_PROPS;

typedef struct {
  WIDGET           Widget;
  TICKER_PROPS     Props;
  I16              Align;
  I16              xOffTicker;
  I16              yOffTicker;
  U16              StringDist;
  U16              NumStrings;
  U8               Consecutive;
  GUI_ARRAY        ItemArray;
  void           (*pfPaint)    (TICKER_Handle hObj);
  void           (*pfStartAnim)(TICKER_Handle hObj, int Restart);
  int              Dist2NextItem;
  U16              CurrentItem;
  U16              LastItem;
  GUI_ANIM_HANDLE  hAnim;
  GUI_HMEM         hAnimData;
  U8               Mode;
  U8               Dir;
  U8               Auto;
  WM_HTIMER        hTimer;
  U8               WrapMode;
  U16              ClickedItem;
} TICKER_OBJ;

typedef struct {
  U32       Offset;
  U32       Length;
  char      acText[1];  // This needs to be always the last member as we copy a string to address: &acText[0]
} TICKER_ITEM;

typedef struct {
  int       NewPos;
  int       Dist;
} TICKER_ANIM_DATA;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define TICKER_INIT_ID(p) p->Widget.DebugId = WIDGET_TYPE_TICKER
#else
  #define TICKER_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  TICKER_OBJ * TICKER_LockH(TICKER_Handle h);
  #define TICKER_LOCK_H(h)   TICKER_LockH(h)
#else
  #define TICKER_LOCK_H(h)   (TICKER_OBJ *)WM_LOCK_H(h)
#endif

#define TICKER_AUTO            (1 << 0)
#define TICKER_SHOW_PREVITEM   (1 << 7)

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/
extern TICKER_PROPS TICKER__DefaultProps;

#endif   /* if GUI_WINSUPPORT */
#endif   /* TICKER_PRIVATE_H */

/*************************** End of file ****************************/
