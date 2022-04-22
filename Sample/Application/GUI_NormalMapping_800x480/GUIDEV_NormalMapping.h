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
File    : GUIDEV_NormalMapping.h
Purpose : Header for normal mapping of memory devices.
--------  END-OF-HEADER  ---------------------------------------------
*/
#ifndef GUIDEV_NORMALMAPPING_H
#define GUIDEV_NORMALMAPPING_H

#include "GUI.h"

/*********************************************************************
*
*       Typedef
*
**********************************************************************
*/
typedef struct {
  GUI_MEMDEV_Handle   hMemDest;
  const U16         * pNMap;
  const GUI_BITMAP  * pBmImage;
  GUI_MEMDEV_Handle   hMemImage;
  const GUI_BITMAP  * pbmLight;
  int                 xSize;
  int                 ySize;
} GUI_MAPPING_CONTEXT;

/*********************************************************************
*
*       Prototype
*
**********************************************************************
*/
int GUI_MEMDEV_NormalMapping(GUI_MAPPING_CONTEXT * pContext, int xPosLight, int yPosLight);

#endif

/****** End of File *************************************************/