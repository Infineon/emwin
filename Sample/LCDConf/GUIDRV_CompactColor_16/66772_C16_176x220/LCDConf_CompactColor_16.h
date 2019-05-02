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
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_COMPACTCOLOR_16_H
#define LCDCONF_COMPACTCOLOR_16_H

/*********************************************************************
*
*       General configuration of LCD
*
**********************************************************************
*/
#define LCD_CONTROLLER      66772

#define LCD_BITSPERPIXEL       16

#define LCD_MIRROR_X            1

#define LCD_NUM_DUMMY_READS     5

#define LCD_USE_SERIAL_3PIN     1

#define LCD_SERIAL_ID           0

/*********************************************************************
*
*       Simple bus configuration
*
**********************************************************************
*/
void LCD_X_WriteM(unsigned char * pData, int NumBytes);
void LCD_X_ReadM (unsigned char * pData, int NumBytes);
void LCD_X_ClrCS (void);
void LCD_X_SetCS (void);

#define LCD_WRITEM(Byte, NumBytes) LCD_X_WriteM(Byte, NumBytes)
#define LCD_READM(Byte, NumBytes)  LCD_X_ReadM(Byte, NumBytes)
#define LCD_SETCS()                LCD_X_SetCS()
#define LCD_CLRCS()                LCD_X_ClrCS()

#endif /* LCDCONF_COMPACTCOLOR_16_H */

