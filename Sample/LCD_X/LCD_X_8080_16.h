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
File        : LCD_X_8080_16.h
Purpose     : Interface definition:
              Port routines 8080 interface, 16 bit data bus
----------------------------------------------------------------------
*/

#ifndef LCD_X_8080_16_H
#define LCD_X_8080_16_H

/*********************************************************************
*
*       Public routines
*/
void LCD_X_8080_16_Init       (void);
void LCD_X_8080_16_Write00_16 (U16 c);
void LCD_X_8080_16_Write01_16 (U16 c);
void LCD_X_8080_16_WriteM01_16(U16 * pData, int NumWords);
void LCD_X_8080_16_WriteM00_16(U16 * pData, int NumWords);
U16  LCD_X_8080_16_Read00_16  (void);
U16  LCD_X_8080_16_Read01_16  (void);
void LCD_X_8080_16_ReadM00_16 (U16 * pData, int NumWords);
void LCD_X_8080_16_ReadM01_16 (U16 * pData, int NumWords);

#endif /* LCD_X_8080_16_H */

/*************************** End of file ****************************/
