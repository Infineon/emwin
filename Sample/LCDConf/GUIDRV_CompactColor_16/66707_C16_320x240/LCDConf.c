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
  LCD_X_Init();
  /* Oscillator on */
  LCD_WRITE_A0(0x0110);
  LCD_WRITE_A0(0x00A0);
  LCD_WRITE_A0(0x0301);
  _Delay(1);
  LCD_WRITE_A0(0x0300);
  LCD_WRITE_A0(0x2B04);
  LCD_WRITE_A0(0x2818);
  LCD_WRITE_A0(0x1A05);
  LCD_WRITE_A0(0x2505);
  LCD_WRITE_A0(0x1900);
  /* LCD Power On */
  LCD_WRITE_A0(0x1C73);
  LCD_WRITE_A0(0x2474);
  LCD_WRITE_A0(0x1E01);
  LCD_WRITE_A0(0x18C1);
  _Delay(1);
  LCD_WRITE_A0(0x18E1);
  LCD_WRITE_A0(0x18F1);
  _Delay(6);
  LCD_WRITE_A0(0x18F5);
  _Delay(6);
  LCD_WRITE_A0(0x1B09);
  _Delay(1);
  LCD_WRITE_A0(0x1F11);
  LCD_WRITE_A0(0x200E);
  LCD_WRITE_A0(0x1E81);
  _Delay(1);
  /* Chip Set */
  LCD_WRITE_A0(0x9D00);
  LCD_WRITE_A0(0xC000);
  LCD_WRITE_A0(0x0E00);
  LCD_WRITE_A0(0x0F00);
  LCD_WRITE_A0(0x1000);
  LCD_WRITE_A0(0x1100);
  LCD_WRITE_A0(0x1200);
  LCD_WRITE_A0(0x1300);
  LCD_WRITE_A0(0x1400);
  LCD_WRITE_A0(0x1500);
  LCD_WRITE_A0(0x1600);
  LCD_WRITE_A0(0x1700);
  LCD_WRITE_A0(0x3401);
  LCD_WRITE_A0(0x3500);
  LCD_WRITE_A0(0x4B00);
  LCD_WRITE_A0(0x4C00);
  LCD_WRITE_A0(0x4E00);
  LCD_WRITE_A0(0x4F00);
  LCD_WRITE_A0(0x5000);
  LCD_WRITE_A0(0x3C00);
  LCD_WRITE_A0(0x3D00);
  LCD_WRITE_A0(0x3E01);
  LCD_WRITE_A0(0x3F3F);
  LCD_WRITE_A0(0x4002);
  LCD_WRITE_A0(0x4102);
  LCD_WRITE_A0(0x4200);
  LCD_WRITE_A0(0x4300);
  LCD_WRITE_A0(0x4400);
  LCD_WRITE_A0(0x4500);
  LCD_WRITE_A0(0x46EF);
  LCD_WRITE_A0(0x4700);
  LCD_WRITE_A0(0x4800);
  LCD_WRITE_A0(0x4901);
  LCD_WRITE_A0(0x4A3F);
  LCD_WRITE_A0(0x1D08);
  LCD_WRITE_A0(0x8600);
  LCD_WRITE_A0(0x8730);
  LCD_WRITE_A0(0x8802);
  LCD_WRITE_A0(0x8905);
  LCD_WRITE_A0(0x8D01);
  LCD_WRITE_A0(0x8B20);
  LCD_WRITE_A0(0x3301);
  LCD_WRITE_A0(0x3701);
  LCD_WRITE_A0(0x7600);
  /* Gamma Set */
  LCD_WRITE_A0(0x8F10);
  LCD_WRITE_A0(0x9067);
  LCD_WRITE_A0(0x9107);
  LCD_WRITE_A0(0x9265);
  LCD_WRITE_A0(0x9307);
  LCD_WRITE_A0(0x9401);
  LCD_WRITE_A0(0x9576);
  LCD_WRITE_A0(0x9656);
  LCD_WRITE_A0(0x9700);
  LCD_WRITE_A0(0x9806);
  LCD_WRITE_A0(0x9903);
  LCD_WRITE_A0(0x9A00);
  /* Display On */
  LCD_WRITE_A0(0x0150);
  LCD_WRITE_A0(0x3B01);
  _Delay(4);
  LCD_WRITE_A0(0x0020);
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
