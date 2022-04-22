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
File        : LCD_X_8080_16.c
Purpose     : Port routines 8080 interface, 16 bit data bus
----------------------------------------------------------------------
*/

#include "GUI.h"

#include "LCD_X_8080_16.h"

/*********************************************************************
*
*       Defines: Configuration
*
**********************************************************************
  Needs to be adapted to custom hardware.
*/
#define Chip_30600
#include <IOM16C.H>

#define LCD_CLR_RESET()   P7 &= ~(1<<0)
#define LCD_SET_RESET()   P7 |=  (1<<0)
#define LCD_CLR_A0()      P8 &= ~(1<<0)
#define LCD_SET_A0()      P8 |=  (1<<0)
#define LCD_CLR_WR()      P8 &= ~(1<<1)
#define LCD_SET_WR()      P8 |=  (1<<1)
#define LCD_CLR_RD()      P8 &= ~(1<<2)
#define LCD_SET_RD()      P8 |=  (1<<2)
#define LCD_CLR_CS()      P8 &= ~(1<<4)
#define LCD_SET_CS()      P8 |=  (1<<4)
#define LCD_DATA_IN_L     P10
#define LCD_DATA_IN_H     P1
#define LCD_DATA_OUT_L    P10
#define LCD_DATA_OUT_H    P1
#define LCD_SET_DIR_IN()  P1D = 0;    P10D = 0
#define LCD_SET_DIR_OUT() P1D = 0xff; P10D = 0xff
#define LCD_DELAY(ms)     GUI_X_Delay(ms)

/*********************************************************************
*
*       Defines: Common
*
**********************************************************************
  Usually, there is no need to modify these macros.
  It should be sufficient ot modify the low-level macros
  above.
*/
#define LCD_X_READ(c)                            \
  LCD_SET_DIR_IN();                              \
  LCD_CLR_CS();                                  \
  LCD_CLR_RD();                                  \
  c = LCD_DATA_IN_L | ((U16)LCD_DATA_IN_H << 8); \
  LCD_SET_CS();                                  \
  LCD_SET_RD();                                  \
  LCD_SET_DIR_OUT()

#define LCD_X_WRITE(c)                           \
  LCD_DATA_OUT_L = (unsigned char)c;             \
  LCD_DATA_OUT_H = c >> 8;                       \
  LCD_CLR_CS();                                  \
  LCD_CLR_WR();                                  \
  LCD_SET_WR();                                  \
  LCD_SET_CS()

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_8080_16_Init
*
* Purpose:
*   This routine should be called from your application program
*   to set port pins to their initial values.
*   
*/
void LCD_X_8080_16_Init(void) {
  LCD_SET_CS();
  LCD_SET_RD();
  LCD_SET_WR();
  LCD_CLR_RESET();
  LCD_DELAY(5);
  LCD_SET_RESET();
  LCD_DELAY(5);
  LCD_SET_DIR_OUT();
}

/*********************************************************************
*
*       LCD_X_8080_16_Write00_16
*
* Purpose:
*   Write to controller, with A0 = 0
*/
void LCD_X_8080_16_Write00_16(U16 c) {
  LCD_CLR_A0();
  LCD_X_WRITE(c);
}

/*********************************************************************
*
*       LCD_X_8080_16_Write01_16
*
* Purpose:
*   Write to controller, with A0 = 1
*/
void LCD_X_8080_16_Write01_16(U16 c) {
  LCD_SET_A0();
  LCD_X_WRITE(c);
}

/*********************************************************************
*
*       LCD_X_8080_16_WriteM01_16
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 1
*/
void LCD_X_8080_16_WriteM01_16(U16 * pData, int NumWords) {
  LCD_SET_A0();
  for (; NumWords; NumWords--) {
    LCD_X_WRITE(*pData);
    pData++;
  }
}

/*********************************************************************
*
*       LCD_X_8080_16_WriteM00_16
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 0
*/
void LCD_X_8080_16_WriteM00_16(U16 * pData, int NumWords) {
  LCD_CLR_A0();
  for (; NumWords; NumWords--) {
    LCD_X_WRITE(*pData);
    pData++;
  }
}

/*********************************************************************
*
*       LCD_X_8080_16_Read00_16
*
* Purpose:
*   Read from controller, with A0 = 0
*/
U16 LCD_X_8080_16_Read00_16(void) {
  U16 c;
  LCD_CLR_A0();
  LCD_X_READ(c);
  return c;
}

/*********************************************************************
*
*       LCD_X_8080_16_Read01_16
*
* Purpose:
*   Read from controller, with A0 = 1
*/
U16 LCD_X_8080_16_Read01_16(void) {
  U16 c;
  LCD_SET_A0();
  LCD_X_READ(c);
  return c;
}

/*********************************************************************
*
*       LCD_X_8080_16_ReadM00_16
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 0
*/
void LCD_X_8080_16_ReadM00_16(U16 * pData, int NumWords) {
  LCD_CLR_A0();
  for (; NumWords; NumWords--) {
    LCD_X_READ(*pData);
    pData++;
  }
}

/*********************************************************************
*
*       LCD_X_8080_16_ReadM01_16
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 1
*/
void LCD_X_8080_16_ReadM01_16(U16 * pData, int NumWords) {
  LCD_SET_A0();
  for (; NumWords; NumWords--) {
    LCD_X_READ(*pData);
    pData++;
  }
}

/*************************** End of file ****************************/
