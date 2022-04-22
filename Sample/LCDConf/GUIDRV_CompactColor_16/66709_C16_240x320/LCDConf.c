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
#define XSIZE_PHYS 240
#define YSIZE_PHYS 320

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
  LCD_WRITE_A0(0xb0); /* MANUFACTURER COMMAND ACCESS PROTECT */
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0xb3); /* FRAME MEMORY ACCESS & INTERFACE SETTING */
  LCD_WRITE_A1(0x03);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(0xb4); /* DISPLAY MODE & FRAME MEMORY WRITE MODE SETTING */
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0xc0); /* PANEL DRIVING SETTING */
  LCD_WRITE_A1(0x0f);
  LCD_WRITE_A1(0x4f);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x33);
  LCD_WRITE_A0(0xc1); /* DISPLAY TIMING SETTING FOR NORMAL MODE */
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A0(0xc2); /* DISPLAY TIMING SETTING FOR PARTIAL MODE */
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A0(0xc3); /* DISPLAY TIMING SETTING FOR IDLE MODE */
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A1(0x08);
  LCD_WRITE_A0(0xc4); /* SOURCE/VCOM/GATE DRIVING TIMING SETTING */
  LCD_WRITE_A1(0x21);
  LCD_WRITE_A1(0x02);
  LCD_WRITE_A1(0x73);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x35); /* TEARING EFFECT ON */
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x36); /* SET ADDRESS MODE */
  LCD_WRITE_A1(0x80);
  LCD_WRITE_A0(0x3a); /* SET PIXEL FORMAT */
  LCD_WRITE_A1(0x55);
  LCD_WRITE_A0(0xc8); /* SET GAMMA A */
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x0f);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0xad);
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x03);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0xb5);
  LCD_WRITE_A1(0x0a);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0x0f);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x10);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0xc9); /* SET GAMMA B */
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x0a);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0xce);
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x03);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0xc5);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0x0a);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x10);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0xca); /* SET GAMMA C */
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x0a);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0xce);
  LCD_WRITE_A1(0x04);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x03);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0x19);
  LCD_WRITE_A1(0xc5);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0x0c);
  LCD_WRITE_A1(0x0a);
  LCD_WRITE_A1(0x1f);
  LCD_WRITE_A1(0x10);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0xd0); /* POWER SETTING(COMMON) */
  LCD_WRITE_A1(0x07);
  LCD_WRITE_A1(0xc3);
  LCD_WRITE_A1(0xd9);
  LCD_WRITE_A0(0xd1); /* VCOM SETTING */
  LCD_WRITE_A1(0x5b);
  LCD_WRITE_A1(0x13);
  LCD_WRITE_A1(0x03);
  LCD_WRITE_A0(0xd2); /* POWER SETTING FOR NORMAL MODE */
  LCD_WRITE_A1(0x63);
  LCD_WRITE_A1(0x24);
  LCD_WRITE_A0(0xd3); /* POWER SETTING FOR PARTIAL MODE */
  LCD_WRITE_A1(0x63);
  LCD_WRITE_A1(0x24);
  LCD_WRITE_A0(0xd4); /* POWER SETTING FOR IDLE MODE */
  LCD_WRITE_A1(0x63);
  LCD_WRITE_A1(0x24);
  LCD_WRITE_A0(0x11); /* EXIT SLEEP MODE */
  LCD_WRITE_A0(0x2a); /* SET COLUMN ADDRESS */
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0xef);
  LCD_WRITE_A0(0x2b); /* SET PAGE ADDRESS */
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x00);
  LCD_WRITE_A1(0x01);
  LCD_WRITE_A1(0x3f);
  LCD_WRITE_A0(0x2c); /* RAM (IMAGE) DATA WRITE */
  LCD_WRITE_A0(0x29); /* DISPLAY ON */
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
