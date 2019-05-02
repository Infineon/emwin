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
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Start oscillation */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x1a); LCD_WRITE_A1(0x00); /* Power control 2 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x14); LCD_WRITE_A1(0x20); LCD_WRITE_A1(0x20); /* Power control 4 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x09); LCD_WRITE_A1(0x00); /* Power control 1 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x40); /* Power control 3 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x60); /* Power control 3 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x70); /* Power control 3 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x1a); LCD_WRITE_A1(0x04); /* Power control 2 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x2f); LCD_WRITE_A1(0x00); /* Power control 1 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x27); /* Driver output control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x00); /* LCD-Driving-waveform control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x30); /* Entry mode */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Display control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x08); LCD_WRITE_A1(0x08); /* Display control 2 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x09); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gate non display area control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0b); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Frame cycle control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0c); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* External interface control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x40); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gate scan position */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x41); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Vertical scroll control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x42); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x3f); /* 1st screen driving position */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x43); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* 1st screen driving position */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x44); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0xef); /* 2nd screen driving position */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x45); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* 2nd screen driving position */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x46); LCD_WRITE_A1(0xef); LCD_WRITE_A1(0x00); /* Horizontal window address */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x47); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x3f); /* Vertical window Address */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x48); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Vertical window Address  */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x14); /* Display control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x16); /* Display control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x17); /* Display control */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x20); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RAM address set */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x21); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RAM address set */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x22); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RAM access */
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
