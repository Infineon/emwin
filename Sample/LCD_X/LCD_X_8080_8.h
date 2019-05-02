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
File        : LCD_X_8080_8.h
Purpose     : Interface definition:
              Port routines 8080 interface, 8 bit data bus
----------------------------------------------------------------------
*/

#ifndef LCD_X_8080_8_H
#define LCD_X_8080_8_H

/*********************************************************************
*
*       Public routines
*/
void          LCD_X_8080_8_Init(void);
void          LCD_X_8080_8_Sync(void);
void          LCD_X_8080_8_Write00(unsigned char c);
void          LCD_X_8080_8_Write01(unsigned char c);
void          LCD_X_8080_8_WriteM01(unsigned char * pData, int NumBytes);
void          LCD_X_8080_8_WriteM00(unsigned char * pData, int NumBytes);
unsigned char LCD_X_8080_8_Read00(void);
unsigned char LCD_X_8080_8_Read01(void);
void          LCD_X_8080_8_ReadM00(unsigned char * pData, int NumBytes);
void          LCD_X_8080_8_ReadM01(unsigned char * pData, int NumBytes);

#endif /* LCD_X_8080_8_H */

/*************************** End of file ****************************/
