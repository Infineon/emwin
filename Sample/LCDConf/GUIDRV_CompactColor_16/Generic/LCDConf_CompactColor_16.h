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
File        : LCDConf_CompactColor_16.h
Purpose     : CompactColor_16 driver configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_COMPACTCOLOR_16_H
#define LCDCONF_COMPACTCOLOR_16_H

#include "GUI_Type.h"

/*********************************************************************
*
*       General configuration of LCD
*
**********************************************************************
*/
#define LCD_CONTROLLER          66709

#define LCD_BITSPERPIXEL        16

//
// Data bus width selection
//
#define LCD_USE_PARALLEL_16     0

//
// LCD orientation settings
//
#define LCD_MIRROR_X            0
#define LCD_MIRROR_Y            1
#define LCD_SWAP_XY             1

/*********************************************************************
*
*       Simple bus configuration
*
**********************************************************************
*/

void Display_WriteM8_A1(U8 *wrData, int numbytes);
void Display_WriteM8_A0(U8 *wrData, int numbytes);
void Display_ReadM8_A1(U8 *rdData, int numbytes);
void Display_Write8_A0(U8 byte);
void Display_Write8_A1(U8 byte);

#warning Define display access API and remove this line. For details on driver configuration refer to emWin user manual.

#define LCD_WRITEM_A1(p, numbytes)  Display_WriteM8_A1(p, numbytes)
#define LCD_WRITEM_A0(p, numbytes)  Display_WriteM8_A0(p, numbytes)
#define LCD_READM_A1(p, numbytes)   Display_ReadM8_A1(p, numbytes)
#define LCD_WRITE_A0(byte)          Display_Write8_A0(byte)
#define LCD_WRITE_A1(byte)          Display_Write8_A1(byte)

#endif /* LCDCONF_COMPACTCOLOR_16_H */

/*************************** End of file ****************************/
