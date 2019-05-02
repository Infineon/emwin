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
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x08); LCD_WRITE_A1(0x08); /* Display control2                    */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x13); /* Panel Interface control 1           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x00); /* Panel Interface control 2           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x12); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x01); /* Panel Interface control 3           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x0A); LCD_WRITE_A1(0x03); /* Panel Interface control 4           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x14); LCD_WRITE_A1(0x0A); LCD_WRITE_A1(0x0E); /* Panel Interface control 5           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x15); LCD_WRITE_A1(0x0A); LCD_WRITE_A1(0x19); /* Panel Interface control 6           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x16); LCD_WRITE_A1(0x24); LCD_WRITE_A1(0x02); /* Panel Interface control 7           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x18); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* VCOM Change position                */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x90); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x21); /* Interface & Gate Scan Direction     */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 1 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x02); /* Gamma control 2 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x03); /* Gamma control 3 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 4 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x04); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x00); /* Gamma control 5 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x07); /* Gamma control 6 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x17); LCD_WRITE_A1(0x19); /* Gamma control 7 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 8 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x02); /* Gamma control 9 (Red)               */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x09); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x03); /* Gamma control 10 (Red)              */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x0A); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 11 (Red)              */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x0B); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x00); /* Gamma control 12 (Red)              */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x0C); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x07); /* Gamma control 13 (Red)              */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x0D); LCD_WRITE_A1(0x17); LCD_WRITE_A1(0x19); /* Gamma control 14 (Red)              */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 15 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x04); /* Gamma control 16 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x12); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x05); /* Gamma control 17 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 18 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x14); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* Gamma control 19 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x15); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x07); /* Gamma control 20 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x16); LCD_WRITE_A1(0x17); LCD_WRITE_A1(0x19); /* Gamma control 21 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x17); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 22 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x18); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x04); /* Gamma control 23 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x19); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x05); /* Gamma control 24 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x1A); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 25 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x1B); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* Gamma control 26 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x1C); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x07); /* Gamma control 27 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x1D); LCD_WRITE_A1(0x17); LCD_WRITE_A1(0x19); /* Gamma control 28 (Green)            */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x20); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x07); /* Gamma control 29 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x21); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Gamma control 30 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x22); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x01); /* Gamma control 31 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x23); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 32 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x24); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x00); /* Gamma control 33 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x25); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 34 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x26); LCD_WRITE_A1(0x1F); LCD_WRITE_A1(0x19); /* Gamma control 35 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x27); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x07); /* Gamma control 36 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x28); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Gamma control 37 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x29); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x01); /* Gamma control 38 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x2A); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* Gamma control 39 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x2B); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x00); /* Gamma control 40 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x2C); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x07); /* Gamma control 41 (Blue)             */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x2D); LCD_WRITE_A1(0x1F); LCD_WRITE_A1(0x19); /* Gamma control 42 (Blue)             */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x1D); /* Driver output control               */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Base Image Display control          */
  LCD_WRITE_A0(0x02); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x60); /* RAM write timing                    */
  /*---------------------------------------------------------------------------------------------------------------------*/
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Display control1 (D=1)              */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x31); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x71); /* SOUTPL1,5,6,7=1                     */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x10); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Power control10 (PSE=1)             */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x17); LCD_WRITE_A1(0xB0); /* Power control1 (APE=1,SAP=1)        */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x20); /* Power control2 (DC0=2,DC1=2,VC=0)   */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x9B); /* Power control3 (PON=1,VRH=9,VCMR=0) */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x12); LCD_WRITE_A1(0x00); /* Power control4 (VCM,VDV)            */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x03); /* Power control6 (VLMT2=3)            */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x05); /* Power control7 (VLMT3=5)            */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x21); /* Display control1 (GON=1)            */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0xBD); /* Power control3 (PSON=1)             */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x10); /* Driver output1 (SS=1,GMM=1)         */
  /*---------------------------------------------------------------------------------------------------------------------*/
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x05); LCD_WRITE_A1(0x00); /*  (B/C0=1)                           */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x31); /*  (VON=0,DTE=1,D1-0=01)              */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x30); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x07); /*  (SEN1-3=1)                         */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x30); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0xFF); /*  (SEN4-10=1)                        */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x72); /*  (VON=1,DTE=1,D1-0=10)              */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x73); /*  (VON=1,DTE=1,D1-0=11)              */
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
