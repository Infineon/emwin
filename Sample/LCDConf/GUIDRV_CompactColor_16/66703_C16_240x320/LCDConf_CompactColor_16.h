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
#define LCD_CONTROLLER      66703

#define LCD_BITSPERPIXEL       16

#define LCD_MIRROR_X            1

/*********************************************************************
*
*       Simple bus configuration
*
**********************************************************************
*/
void LCD_X_Write01 (unsigned char c);
void LCD_X_Write00 (unsigned char c);
void LCD_X_WriteM01(unsigned char * pData, int NumBytes);
void LCD_X_WriteM00(unsigned char * pData, int NumBytes);
void LCD_X_ReadM01 (unsigned char * pData, int NumBytes);

#define LCD_WRITE_A1(Byte)         LCD_X_Write01(Byte)
#define LCD_WRITE_A0(Byte)         LCD_X_Write00(Byte)
#define LCD_WRITEM_A1(p, NumBytes) LCD_X_WriteM01(p, NumBytes)
#define LCD_WRITEM_A0(p, NumBytes) LCD_X_WriteM00(p, NumBytes)
#define LCD_READM_A1(p, NumBytes)  LCD_X_ReadM01(p, NumBytes)

#endif /* LCDCONF_COMPACTCOLOR_16_H */
