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
File        : LCDConf_CustomColorConversion.c
Purpose     : Shows how custom color conversion can be achieved
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

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
#define COLOR_CONVERSION &_CustomColorConversion

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_TEMPLATE // To be replaced with the desired driver

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
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
*       Static code, Custom Color Conversion
*
*       ----------AAAAAABBBBBGGGGGGRRRRR
*
**********************************************************************
*/

#define R_BITS 5
#define G_BITS 6
#define B_BITS 5
#define A_BITS 6

#define R_MASK ((1 << R_BITS) - 1)
#define G_MASK ((1 << G_BITS) - 1)
#define B_MASK ((1 << B_BITS) - 1)
#define A_MASK ((1 << A_BITS) - 1)

/*********************************************************************
*
*       _Color2Index
*/
static unsigned _Color2Index(LCD_COLOR Color) {
  int r, g, b, a;
  r = (Color >> (8  - R_BITS)) & R_MASK;
  g = (Color >> (16 - G_BITS)) & G_MASK;
  b = (Color >> (24 - B_BITS)) & B_MASK;
  a = (Color >> (32 - A_BITS)) & A_MASK;
  return r + (g << R_BITS) + (b << (R_BITS + G_BITS)) + (a << (R_BITS + G_BITS + B_BITS));
}

/*********************************************************************
*
*       _Index2Color
*/
static LCD_COLOR _Index2Color(unsigned Index) {
  unsigned r, g, b, a;
  
  //
  // Seperate the color masks
  //
  r = Index                                           & R_MASK;
  g = (Index >> R_BITS)                               & G_MASK;
  b = ((unsigned)Index >> (R_BITS + G_BITS))          & B_MASK;
  a = ((unsigned)Index >> (R_BITS + G_BITS + B_BITS)) & A_MASK;
  //
  // Convert the color masks
  //
  r = r * 255 / R_MASK;
  g = g * 255 / G_MASK;
  b = b * 255 / B_MASK;
  a = a * 255 / A_MASK;
  return r + (g << 8) + (((U32)b) << 16) + (((U32)a) << 24);
}

/*********************************************************************
*
*       _GetIndexMask
*/
static unsigned _GetIndexMask(void) {
  return (unsigned)0x3FFFFF; // 22 bits (LSB) used
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       _CustomColorConversion
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV _CustomColorConversion = {
  _Color2Index,
  _Index2Color,
  _GetIndexMask
};

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
  // TBD by customer...
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
  LCD_SetSizeEx    (0, XSIZE_PHYS,   YSIZE_PHYS);
  LCD_SetVSizeEx   (0, VXSIZE_PHYS,  VYSIZE_PHYS);
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
