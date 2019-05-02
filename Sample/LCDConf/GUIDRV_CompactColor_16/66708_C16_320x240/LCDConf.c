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
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf_CompactColor_16.h"

#include "GUIDRV_CompactColor_16.h"

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS 320
#define YSIZE_PHYS 240

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_COMPACT_COLOR_16

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Delay
*
* Purpose:
*   Waits a while...
*/
static void _Delay(int Cnt) {
  volatile I32 i, j; 
  j = Cnt << 8; 
  for (i = 0; i < j; i++);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void) {
  #ifndef WIN32
  LCD_X_Init();                            \
  /* Start Initial Sequence */             \
  LCD_WRITE_A0(229); LCD_WRITE_A1(0x8000); \
  LCD_WRITE_A0(  0); LCD_WRITE_A1(0x0001); \
  LCD_WRITE_A0(  1); LCD_WRITE_A1(0x0100); \
  LCD_WRITE_A0(  2); LCD_WRITE_A1(0x0700); \
  LCD_WRITE_A0(  3); LCD_WRITE_A1(0x1030); \
  LCD_WRITE_A0(  4); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(  8); LCD_WRITE_A1(0x0202); \
  LCD_WRITE_A0(  9); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 10); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 12); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 13); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 15); LCD_WRITE_A1(0x0000); \
  /* Power On sequence */                  \
  LCD_WRITE_A0( 16); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 17); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 18); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 19); LCD_WRITE_A1(0x0000); \
  _Delay(20);                           \
  LCD_WRITE_A0( 16); LCD_WRITE_A1(0x17B0); \
  LCD_WRITE_A0( 17); LCD_WRITE_A1(0x0137); \
  _Delay(5);                            \
  LCD_WRITE_A0( 18); LCD_WRITE_A1(0x0139); \
  _Delay(5);                            \
  LCD_WRITE_A0( 19); LCD_WRITE_A1(0x1d00); \
  LCD_WRITE_A0( 41); LCD_WRITE_A1(0x0013); \
  _Delay(5);                            \
  LCD_WRITE_A0( 32); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 33); LCD_WRITE_A1(0x0000); \
  /* Adjust the Gamma Curve */             \
  LCD_WRITE_A0( 48); LCD_WRITE_A1(0x0006); \
  LCD_WRITE_A0( 49); LCD_WRITE_A1(0x0101); \
  LCD_WRITE_A0( 50); LCD_WRITE_A1(0x0003); \
  LCD_WRITE_A0( 53); LCD_WRITE_A1(0x0106); \
  LCD_WRITE_A0( 54); LCD_WRITE_A1(0x0b02); \
  LCD_WRITE_A0( 55); LCD_WRITE_A1(0x0302); \
  LCD_WRITE_A0( 56); LCD_WRITE_A1(0x0707); \
  LCD_WRITE_A0( 57); LCD_WRITE_A1(0x0007); \
  LCD_WRITE_A0( 60); LCD_WRITE_A1(0x0600); \
  LCD_WRITE_A0( 61); LCD_WRITE_A1(0x020b); \
  /* Set GRAM area */                      \
  LCD_WRITE_A0( 80); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 81); LCD_WRITE_A1(0x00EF); \
  LCD_WRITE_A0( 82); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0( 83); LCD_WRITE_A1(0x013F); \
  LCD_WRITE_A0( 96); LCD_WRITE_A1(0x2700); \
  LCD_WRITE_A0( 97); LCD_WRITE_A1(0x0001); \
  LCD_WRITE_A0(106); LCD_WRITE_A1(0x0000); \
  /* Partial Display Control */            \
  LCD_WRITE_A0(128); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(129); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(130); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(131); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(132); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(133); LCD_WRITE_A1(0x0000); \
  /* Panel Control */                      \
  LCD_WRITE_A0(144); LCD_WRITE_A1(0x0010); \
  LCD_WRITE_A0(146); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(147); LCD_WRITE_A1(0x0003); \
  LCD_WRITE_A0(149); LCD_WRITE_A1(0x0110); \
  LCD_WRITE_A0(151); LCD_WRITE_A1(0x0000); \
  LCD_WRITE_A0(152); LCD_WRITE_A1(0x0000);
  #endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
void LCD_X_Config(void) {
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
  }
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
