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
File        : LCD_X_6800.c
Purpose     : Port routines
----------------------------------------------------------------------
*/

/*********************************************************************
*
*           Hardware configuration
*
**********************************************************************
  Needs to be adapted to your target hardware.
*/

/* Configuration example:

#include <IOM16C.H>      // Include port definitions

#define LCD_CLR_A0()      P8 &= ~(1<<0)
#define LCD_SET_A0()      P8 |=  (1<<0) 
#define LCD_CLR_RW()      P8 &= ~(1<<1)
#define LCD_SET_RW()      P8 |=  (1<<1) 
#define LCD_CLR_E()       P8 &= ~(1<<2)
#define LCD_SET_E()       P8 |=  (1<<2) 
#define LCD_CLR_CS0()     P8 &= ~(1<<3)
#define LCD_SET_CS0()     P8 |=  (1<<3)
#define LCD_CLR_CS1()     P8 &= ~(1<<4)
#define LCD_SET_CS1()     P8 |=  (1<<4)
#define LCD_DATA_IN       P7
#define LCD_DATA_OUT      P7
#define LCD_SET_DIR_IN()  P7D = 0
#define LCD_SET_DIR_OUT() P7D = 0xff
#define LCD_DELAY(ms)     GUI_Delay(ms)
*/

/*********************************************************************
*
*           Defaults
*
**********************************************************************
*/

#ifndef LCD_CLR_RW
  #define LCD_CLR_RW()
#endif
#ifndef LCD_SET_RW
  #define LCD_SET_RW()
#endif
#ifndef LCD_SET_CS0
  #define LCD_SET_CS0()
#endif
#ifndef LCD_SET_CS1
  #define LCD_SET_CS1()
#endif
#ifndef LCD_SET_CS2
  #define LCD_SET_CS2()
#endif

#ifndef LCD_SET_DIR_IN
  #define LCD_SET_DIR_IN()
#endif
#ifndef LCD_SET_DIR_OUT
  #define LCD_SET_DIR_OUT()
#endif

/*********************************************************************
*
*           High level LCD access macros
*
**********************************************************************
  Usually, there is no need to modify these macros.
  It should be sufficient ot modify the low-level macros
  above.
*/

#if 1 /* Works faster for writing data */

#define LCD_X_READ()      \
  LCD_SET_DIR_IN();       \
  LCD_SET_RW();           \
  LCD_SET_E();            \
  c = LCD_DATA_IN;        \
  LCD_CLR_E();            \
  LCD_CLR_RW();           \
  LCD_SET_DIR_OUT()

#define LCD_X_WRITE(Data) \
  LCD_DATA_OUT = Data;    \
  LCD_SET_E();            \
  LCD_CLR_E();            \
  LCD_SET_RW()

#else /* Works faster for reading data */

#define LCD_X_READ()      \
  LCD_SET_RW();           \
  LCD_SET_E();            \
  c = LCD_DATA_IN;        \
  LCD_CLR_E()

#define LCD_X_WRITE(Data) \
  LCD_CLR_RW();           \
  LCD_SET_DIR_OUT();      \
  LCD_DATA_OUT = Data;    \
  LCD_SET_E();            \
  LCD_CLR_E();            \
  LCD_SET_DIR_IN();       \
  LCD_SET_RW()

#endif


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
  LCD_SET_E();
  LCD_CLR_RW();
  LCD_SET_A0();
  LCD_SET_CS0();
  LCD_SET_CS1();
  LCD_SET_CS2();
  LCD_SET_RESET();
}

/*********************************************************************
*
*           Access routines, controller 0
*
**********************************************************************
  Usually, there is no need to modify these routines.
  It should be sufficient ot modify the low-level macros
  above.
*/

/* Read from controller 0, with A0 = 0, CS0 = 0, CS1 = 1 */
unsigned char LCD_X_Read00(void) {
  unsigned char c;
  LCD_CLR_CS0();
  LCD_CLR_A0();
  LCD_X_READ();
  LCD_SET_CS0();
  return c;
}

/* Read from controller 0, with A0 = 1, CS0 = 0, CS1 = 1 */
unsigned char LCD_X_Read01(void) {
  unsigned char c;
  LCD_CLR_CS0();
  LCD_SET_A0();
  LCD_X_READ();
  LCD_SET_CS0();
  return c;
}

/* Write to controller 0, with A0 = 0, CS0 = 0, CS1 = 1 */
void LCD_X_Write00(unsigned char c) {
  LCD_CLR_A0();
  LCD_CLR_CS0();
  LCD_X_WRITE(c);
  LCD_SET_CS0();
}

/* Write to controller 0, with A0 = 1, CS0 = 0, CS1 = 1 */
void LCD_X_Write01(unsigned char c) {
  LCD_SET_A0();
  LCD_CLR_CS0();
  LCD_X_WRITE(c);
  LCD_SET_CS0();
}

/* Write multiple bytes to controller 0, with A0 = 1, CS0 = 0, CS1 = 1 */
void LCD_X_WriteM01(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  LCD_CLR_CS0();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
  LCD_SET_CS0();
}

/*********************************************************************
*
*           Access routines, controller 1
*
**********************************************************************
  Usually, there is no need to modify these routines.
  It should be sufficient ot modify the low-level macros
  above.
*/

/* Read from controller 1, with A0 = 0, CS0 = 1, CS1 = 0 */

#ifdef LCD_CLR_CS1

unsigned char LCD_X_Read10(void) {
  unsigned char c;
  LCD_CLR_CS1();
  LCD_CLR_A0();
  LCD_X_READ();
  LCD_SET_CS1();
  return c;
}

/* Read from controller 1, with A0 = 1, CS0 = 1, CS1 = 0 */
unsigned char LCD_X_Read11(void) {
  unsigned char c;
  LCD_CLR_CS1();
  LCD_SET_A0();
  LCD_X_READ();
  LCD_SET_CS1();
  return c;
}

/* Write to controller 1, with A0 = 0, CS0 = 1, CS1 = 0 */
void LCD_X_Write10(unsigned char c) {
  LCD_CLR_A0();
  LCD_CLR_CS1();
  LCD_X_WRITE(c);
  LCD_SET_CS1();
}

/* Write to controller 1, with A0 = 1, CS0 = 1, CS1 = 0 */
void LCD_X_Write11(unsigned char c) {
  LCD_SET_A0();
  LCD_CLR_CS1();
  LCD_X_WRITE(c);
  LCD_SET_CS1();
}

/* Write multiple bytes to controller 1, with A0 = 1, CS0 = 0, CS1 = 1 */
void LCD_X_WriteM11(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  LCD_CLR_CS1();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
  LCD_SET_CS1();
}

#endif /* LCD_CLR_CS1 */

/*********************************************************************
*
*           Access routines, controller 2
*
**********************************************************************
  Usually, there is no need to modify these routines.
  It should be sufficient ot modify the low-level macros
  above.
*/

#ifdef LCD_CLR_CS2

/* Read from controller 2, with A0 = 0, CS0 = 1, CS1 = 1 */
unsigned char LCD_X_Read20(void) {
  unsigned char c;
  LCD_CLR_CS2();
  LCD_CLR_A0();
  LCD_X_READ();
  LCD_SET_CS2();
  return c;
}

/* Read from controller 2, with A0 = 1, CS0 = 1, CS1 = 1 */
unsigned char LCD_X_Read21(void) {
  unsigned char c;
  LCD_CLR_CS2();
  LCD_SET_A0();
  LCD_X_READ();
  LCD_SET_CS2();
  return c;
}

/* Write to controller 2, with A0 = 0, CS0 = 1, CS1 = 1 */
void LCD_X_Write20(unsigned char c) {
  LCD_CLR_A0();
  LCD_CLR_CS2();
  LCD_X_WRITE(c);
  LCD_SET_CS2();
}

/* Write to controller 2, with A0 = 1, CS0 = 1, CS1 = 1 */
void LCD_X_Write21(unsigned char c) {
  LCD_SET_A0();
  LCD_CLR_CS2();
  LCD_X_WRITE(c);
  LCD_SET_CS2();
}

/* Write multiple bytes to controller 2, with A0 = 1, CS0 = 0, CS1 = 1 */
void LCD_X_WriteM21(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  LCD_CLR_CS2();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
  LCD_SET_CS2();
}

#endif /* LCD_CLR_CS2 */

