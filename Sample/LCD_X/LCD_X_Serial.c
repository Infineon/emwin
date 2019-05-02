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
File        : LCD_X_SERIAL_1.c
Purpose     : Port routines
----------------------------------------------------------------------
*/

#ifndef LCD_DELAY
  #define LCD_DELAY(x)
#endif

#ifndef LCD_SET_CS
  #define LCD_SET_CS()
  #define LCD_CLR_CS()
#endif

/*********************************************************************
*
*           Hardware configuration
*
**********************************************************************

  Needs to be adapted to your target hardware.
*/

/* Configuration example:

#define LCD_CLR_A0()      P7 &= ~(1<<1)
#define LCD_SET_A0()      P7 |=  (1<<1) 
#define LCD_CLR_RESET()   P7 &= ~(1<<2)
#define LCD_SET_RESET()   P7 |=  (1<<2) 
#define LCD_CLR_CLK()     P7 &= ~(1<<3)
#define LCD_SET_CLK()     P7 |=  (1<<3) 
#define LCD_CLR_DATA()    P7 &= ~(1<<4)
#define LCD_SET_DATA()    P7 |=  (1<<4) 
#define LCD_SET_DIR_OUT() P7D = 0xff
#define LCD_CLR_CS()      P7 &= ~(1<<0)      // Optional
#define LCD_SET_CS()      P7 |=  (1<<0)      // Optional
#define LCD_CLR_CS1()     P7 &= ~(1<<5)      // Optional (only for mult. controllers)
#define LCD_SET_CS1()     P7 |=  (1<<5)      // Optional (only for mult. controllers)
#define LCD_DELAY(ms)     GUI_Delay(ms)      // Optional

*/

/*********************************************************************
*
*           Initialisation
*
**********************************************************************
  This routine should be called from your application program
  to set port pins to their initial values
*/

void LCD_X_Init(void) {
  LCD_CLR_RESET();
  LCD_SET_DIR_OUT();
  LCD_SET_CS();
  #ifdef LCD_SET_CS1
    LCD_SET_CS1();
  #endif
  LCD_SET_A0();
  LCD_SET_RESET();
  LCD_SET_CLK();
  LCD_SET_DATA();
  LCD_DELAY(20);
  LCD_SET_RESET();
  LCD_DELAY(20);
}

/*********************************************************************
*
*           Send1 routine
*
**********************************************************************

  Usually, there is no need to modify this routine.
  It should be sufficient ot modify the low-level macros above or
  in a configuration file.
*/

/* Write 1 byte, MSB first */
static void Send1(unsigned char Data) {
  if ((Data >> 7) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 6) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 5) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 4) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 3) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 2) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 1) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
  if ((Data >> 0) & 1) LCD_SET_DATA(); else LCD_CLR_DATA(); LCD_CLR_CLK(); LCD_SET_CLK();
}

/*********************************************************************
*
*           Read1 routine
*
**********************************************************************
*/

/* Read 1 byte, MSB first */
static unsigned char Read1(void) {
  unsigned char Data = 0;
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 7);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 6);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 5);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 4);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 3);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 2);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 1);
  LCD_CLR_CLK(); LCD_SET_CLK(); if (LCD_SDO()) Data |= (1 << 0);
  return Data;
}

/*********************************************************************
*
*           Controller 0
*
**********************************************************************

*/

/* Write to controller, with A0 = 1 */
void LCD_X_Write01(unsigned char Data) {
  LCD_CLR_CS();
  LCD_SET_A0();
  Send1(Data);
  LCD_SET_CS();
}

/* Write multiple bytes to controller, with A0 = 1 */
void LCD_X_WriteM01(unsigned char * pData, int NumBytes) {
  LCD_CLR_CS();
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    Send1(*pData++);
  }
  LCD_SET_CS();
}

/* Write to controller, with A0 = 0 */
void LCD_X_Write00(unsigned char Cmd) {
  LCD_CLR_CS();
  LCD_CLR_A0();
  Send1(Cmd);
  LCD_SET_CS();
}

/* Read from controller, with A0 = 1 */
unsigned char LCD_X_Read01(void) {
  unsigned char Data;
  LCD_CLR_CS();
  LCD_CLR_A0();
  Data = Read1();
  LCD_SET_CS();
  return Data;
}

/*********************************************************************
*
*           Controller 1 (optional)
*
**********************************************************************

*/

#ifdef LCD_SET_CS1
/* Write to controller, with A0 = 1 */
void LCD_X_Write11(unsigned char Data) {
  LCD_CLR_CS1();
  LCD_SET_A0();
  Send1(Data);
  LCD_SET_CS1();
}

/* Write multiple bytes to controller, with A0 = 1 */
void LCD_X_WriteM11(unsigned unsigned char * pData, int NumBytes) {
  LCD_CLR_CS1();
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    Send1(*pData++);
  }
  LCD_SET_CS1();
}

/* Write to controller, with A0 = 0 */
void LCD_X_Write10(unsigned char Cmd) {
  LCD_CLR_CS1();
  LCD_CLR_A0();
  Send1(Cmd);
  LCD_SET_CS1();
}
#endif

