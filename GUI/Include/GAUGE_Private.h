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
File        : GAUGE.h
Purpose     : GAUGE include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef GAUGE_PRIVATE_H
#define GAUGE_PRIVATE_H

#include "WM_Intern.h"
#include "GAUGE.h"

#if (GUI_WINSUPPORT)

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define PRE_VOID                   \
  {                                \
    GAUGE_OBJ * pObj;              \
    if (hObj) {                    \
      GUI_LOCK();                  \
      pObj = GAUGE_LOCK_H(hObj); {

#define POST_VOID_INVALIDATE       \
        WM_InvalidateWindow(hObj); \
      } GUI_UNLOCK_H(pObj);        \
      GUI_UNLOCK();                \
    }                              \
  }

#define POST_VOID                  \
      } GUI_UNLOCK_H(pObj);        \
      GUI_UNLOCK();                \
    }                              \
  }

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  GUI_COLOR aColor[2];
  GUI_COLOR BkColor;
  I16       Align;
  I16       xOff, yOff;
} GAUGE_PROPS;

typedef struct {
  WIDGET      Widget;             // (obvious)
  GAUGE_PROPS Props;              // (obvious)
  int         Radius;             // 
  int         aWidth[2];          // 
  I32         Value;              // 
  I32         Ang0;               // 
  I32         Ang1;               // 
  I32         Angle;              // Current angle within the given range (Ang0 & Ang1)
  I32         MinVRange;          // Minimum of value range
  I32         MaxVRange;          // Maximum of value range
  U8          CurvedFlags;
} GAUGE_OBJ;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define GAUGE_INIT_ID(p) (p->Widget.DebugId = WIDGET_TYPE_GAUGE)
#else
  #define GAUGE_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  GAUGE_OBJ * GAUGE_LockH(GAUGE_Handle h);
  #define GAUGE_LOCK_H(h) GAUGE_LockH(h)
#else
  #define GAUGE_LOCK_H(h) (GAUGE_OBJ *)WM_LOCK_H(h)
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern GAUGE_PROPS GAUGE__DefaultProps;

#endif  // (GUI_SUPPORT_MEMDEV && GUI_WINSUPPORT)
#endif  // GAUGE_PRIVATE_H
