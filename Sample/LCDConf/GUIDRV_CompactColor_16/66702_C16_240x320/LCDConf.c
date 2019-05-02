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
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Oscillation Start */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Sleep mode */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x33); /* Display control */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x68); LCD_WRITE_A1(0x33); /* Entry mode */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x2B); LCD_WRITE_A1(0x3F); /* Driver output control */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x00); /* LCD drive AC control */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x66); LCD_WRITE_A1(0x64); /* Power control (1) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x15); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00);
                                          LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x91);
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0B); LCD_WRITE_A1(0x53); LCD_WRITE_A1(0x08); /* Frame cycle control */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0C); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x07); /* Power control (2) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0D); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x06); /* Power control (3) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0F); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gate scan start position */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x1E); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x1E); /* Power control (5) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0E); LCD_WRITE_A1(0x2A); LCD_WRITE_A1(0x00); /* Power control (4) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x25); LCD_WRITE_A1(0xE0); LCD_WRITE_A1(0x00); /* Frame Frequency */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x30); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gamma control (1) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x31); LCD_WRITE_A1(0x04); LCD_WRITE_A1(0x05); /* Gamma control (2) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x32); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gamma control (3) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x33); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x00); /* Gamma control (4) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x34); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* Gamma control (5) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x35); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control (6) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x36); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x04); /* Gamma control (7) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x37); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* Gamma control (8) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x3A); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x00); /* Gamma control (9) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x3B); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x03); /* Gamma control (10) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x22);                                         /* RAM access */
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

