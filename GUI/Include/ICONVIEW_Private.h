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

** emWin V6.24 - Graphical user interface for embedded applications **
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
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : ICONVIEW_Private.h
Purpose     : ICONVIEW private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef ICONVIEW_PRIVATE_H
#define ICONVIEW_PRIVATE_H

#include "GUI_Private.h"
#include "WM_Intern.h"
#include "GUI_ARRAY.h"
#include "ICONVIEW.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {             // Make sure we have C-declarations in C++ programs
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  const GUI_FONT * pFont;
  GUI_COLOR        aBkColor[3];
  GUI_COLOR        aTextColor[3];
  int              FrameX, FrameY;
  int              SpaceX, SpaceY;
  int              TextAlign;
  int              IconAlign;
  GUI_WRAPMODE     WrapMode;
} ICONVIEW_PROPS;

typedef struct {
  WIDGET                  Widget;
  WM_SCROLL_STATE         ScrollStateV;
  WM_SCROLL_STATE         ScrollStateH;
  ICONVIEW_PROPS          Props;
  GUI_ARRAY               ItemArray;
  int                     xSizeItems;
  int                     ySizeItems;
  int                     Sel;
  U16                     Flags;
  WIDGET_DRAW_ITEM_FUNC * pfDrawItem;
  int                     ReleasedItem;
} ICONVIEW_OBJ;

typedef void tDrawImage    (const void * pData, GUI_GET_DATA_FUNC * pfGetData, int xPos, int yPos);
typedef void tDrawText     (ICONVIEW_OBJ * pObj, GUI_RECT * pRect, const char * s);
typedef void tGetImageSizes(const void * pData, GUI_GET_DATA_FUNC * pfGetData, int * xSize, int * ySize);

typedef struct {
  tDrawImage        * pfDrawImage;
  tDrawText         * pfDrawText;
  tGetImageSizes    * pfGetImageSizes;
  GUI_GET_DATA_FUNC * pfGetData;
  const void        * pData;
  U32                 UserData;
  int                 SizeOfData;
  char                acText[1];
} ICONVIEW_ITEM;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define ICONVIEW_INIT_ID(p) (p->Widget.DebugId = ICONVIEW_ID)
#else
  #define ICONVIEW_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  ICONVIEW_OBJ * ICONVIEW_LockH(ICONVIEW_Handle h);
  #define ICONVIEW_LOCK_H(h)   ICONVIEW_LockH(h)
#else
  #define ICONVIEW_LOCK_H(h)   (ICONVIEW_OBJ *)WM_LOCK_H(h)
#endif

/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
void ICONVIEW__DrawText        (ICONVIEW_OBJ    * pObj, GUI_RECT * pRect, const char * pText);
void ICONVIEW__ManageAutoScroll(ICONVIEW_Handle   hObj);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // ICONVIEW_H

/*************************** End of file ****************************/
