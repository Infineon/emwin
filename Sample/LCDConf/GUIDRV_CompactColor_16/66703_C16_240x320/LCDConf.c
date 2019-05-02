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
void LCD_X_Sync(void); // LCD_X_8080.c contains a sample for this routine which is required to synchronize the communication
static void _InitController(void) {
  #ifndef WIN32
  LCD_X_Init();
  /* Deep standby out */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00);
  _Delay(1);
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00);
  _Delay(1);
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00);
  _Delay(1);
  /* Standby out */
  LCD_WRITE_A0(0x05); LCD_WRITE_A0(0xff); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* NOP */
  LCD_X_Sync();
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x1d); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x05); /* Mode setting */
  _Delay(1);
  /* Initialization */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Oscillator on */
  /* Display control */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x27); /* Display size 320 lines */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* AC conversion */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x40); LCD_WRITE_A1(0x04); /* Display mode */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0d); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x11); /* FR period adjustment setting */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0f); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* External display signal setting (3) */
  /* LTPS control settings */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x12); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x03); /* LTPS control setting (1) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x13); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x02); /* LTPS control setting (2) */
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x1c); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Amplifier capability setting */
  /* Power settings */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0xf6); /* Power supply control (1) */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x07); /* Power Supply Control (2) */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x11); /* Power supply control (4) */
  /* Gray scale settings (gamma corrections for 2.2) */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x02); LCD_WRITE_A1(0x00); /* Gray scale setting */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x02); /* Gray scale setting */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Gray scale setting */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x03); LCD_WRITE_A1(0x00); /* Gray scale setting */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x04); LCD_WRITE_A1(0x07); LCD_WRITE_A1(0x00); /* Gray scale setting */
  LCD_WRITE_A0(0x03); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x70); /* Setting for Gray scale offset amounts */
  /* RAM access settings */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* First screen drive position (1) */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x3f); /* First screen drive position (2) */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Horizontal RAM address location (1) */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0xef); /* Horizontal RAM address location (2) */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* Vertical RAM address location (1) */
  LCD_WRITE_A0(0x04); LCD_WRITE_A0(0x09); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x3f); /* Vertical RAM address location (2) */
  LCD_WRITE_A0(0x02); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0xef); /* RAM address setting (1) */
  LCD_WRITE_A0(0x02); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RAM address setting (2) */
  LCD_WRITE_A0(0x02); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00);
  /* Display on */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0xc0); LCD_WRITE_A1(0x10); /* Display Control */
  _Delay(255);
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* Auto sequence Control */
  LCD_WRITE_A0(0x01); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0xf7); LCD_WRITE_A1(0xfe); /* Display Control */
  _Delay(255);
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
