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
#define XSIZE_PHYS 176
#define YSIZE_PHYS 220

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

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
  GUI_X_Delay(100);
  /* Gamma setting */
  LCD_WRITE_A0(0x40); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x41); LCD_WRITE_A1(0x40);
  LCD_WRITE_A0(0x42); LCD_WRITE_A1(0x45);
  LCD_WRITE_A0(0x43); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(0x44); LCD_WRITE_A1(0x60);
  LCD_WRITE_A0(0x45); LCD_WRITE_A1(0x05);
  LCD_WRITE_A0(0x46); LCD_WRITE_A1(0x0C);
  LCD_WRITE_A0(0x47); LCD_WRITE_A1(0xD1);
  LCD_WRITE_A0(0x48); LCD_WRITE_A1(0x05);
  LCD_WRITE_A0(0x50); LCD_WRITE_A1(0x75);
  LCD_WRITE_A0(0x51); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(0x52); LCD_WRITE_A1(0x67);
  LCD_WRITE_A0(0x53); LCD_WRITE_A1(0x14);
  LCD_WRITE_A0(0x54); LCD_WRITE_A1(0xF2);
  LCD_WRITE_A0(0x55); LCD_WRITE_A1(0x07);
  LCD_WRITE_A0(0x56); LCD_WRITE_A1(0x03);
  LCD_WRITE_A0(0x57); LCD_WRITE_A1(0x49);
  LCD_WRITE_A0(0x1F); LCD_WRITE_A1(0x03);
  LCD_WRITE_A0(0x20); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(0x24); LCD_WRITE_A1(0x20);
  LCD_WRITE_A0(0x25); LCD_WRITE_A1(0x52);
  LCD_WRITE_A0(0x23); LCD_WRITE_A1(0x2F);
  LCD_WRITE_A0(0x18); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x21); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x1C); LCD_WRITE_A1(0x03);
  LCD_WRITE_A0(0x19); LCD_WRITE_A1(0x06);
  LCD_WRITE_A0(0x26); LCD_WRITE_A1(0x84);
  GUI_X_Delay(100);
  LCD_WRITE_A0(0x26); LCD_WRITE_A1(0xB8);
  GUI_X_Delay(100);
  LCD_WRITE_A0(0x26); LCD_WRITE_A1(0xBC);
  LCD_WRITE_A0(0x17); LCD_WRITE_A1(0x15);
  LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x04); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x05); LCD_WRITE_A1(0xAF);
  LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(0x09); LCD_WRITE_A1(0xDB);
  LCD_WRITE_A0(0x16); LCD_WRITE_A1(0x88);
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

