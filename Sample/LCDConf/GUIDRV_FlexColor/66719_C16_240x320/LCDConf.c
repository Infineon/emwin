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
Purpose     : Sample display controller configuration

              Controller:     Samsung S6E63D6
              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 16 bit interface

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

#include "GUIDRV_FLEXCOLOR.h"

#ifndef WIN32
  #include "LCD_X_8080_16.h"
#endif

/*********************************************************************
*
*       Layer configuration (to be modified)
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
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
#define DISPLAY_ORIENTATION GUI_SWAP_XY | GUI_MIRROR_X | GUI_MIRROR_Y

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
*       _InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void) {
#ifndef WIN32
  LCD_X_8080_16_Init();                                         // Reset controller and initialize port lines
  LCD_X_8080_16_Write00(0x0023);                                // Select 18/16-Bit Data Bus Interface 262K color D17~D10 D8~D1
	LCD_X_8080_16_Write00(0x0005); LCD_X_8080_16_Write01(0x0000); // R05 - Display Off
	LCD_X_8080_16_Write00(0x0012); LCD_X_8080_16_Write01(0x0008); // R12 - Power Gen 1 VC[3:0] - 1000 = 2.5V
	LCD_X_8080_16_Write00(0x0013); LCD_X_8080_16_Write01(0x146A); // R13 - Power Gen 2 VINT3_0=0101 [-2V], VGH3_0=0011 [5.2V], VGL3_0=1010 [-7V]
	LCD_X_8080_16_Write00(0x0014); LCD_X_8080_16_Write01(0x4200); // R14 - Power step up control 1 DC22_0=100, DC12_0=010, BT1_0=00
	LCD_X_8080_16_Write00(0x0018); LCD_X_8080_16_Write01(0x0010); // R18 - Start oscillation RADJ5_0=01111 [x1]  
	LCD_X_8080_16_Write00(0x0002); LCD_X_8080_16_Write01(0x0000); // R02 - RM(IB8)=0 DM(IB7)=0 -  System interface, Internal clock operation
	LCD_X_8080_16_Write00(0x0003); LCD_X_8080_16_Write01(0x0130); // R03 - ENTRY MODE RM(IB8)=0 DM(IB7)=0 -  System interface, Internal clock operation
	LCD_X_8080_16_Write00(0x0010); LCD_X_8080_16_Write01(0x0000); // R10 - STAND BY // STB(IB0) STB = "0" - Standby mode cancel;  STB = "1", S6E63D6 enters Standby mode
	LCD_X_8080_16_Write00(0x0004); LCD_X_8080_16_Write01(0x0000); // R04 - CLOCK CONTROL  00 - DOTCLK/4 
  LCD_X_8080_16_Write00(0x0005); LCD_X_8080_16_Write01(0x0001); // R05 - Display On
  LCD_X_8080_16_On(1);
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
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  #ifndef WIN32
    CONFIG_FLEXCOLOR Config = {0};
    GUI_PORT_API PortAPI = {0};
  #endif

  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display size configuration
  //
  #ifndef WIN32
    LCD_SetSizeEx (0, XSIZE_PHYS,  YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS,  YSIZE_PHYS);
  #else
    #if (DISPLAY_ORIENTATION & GUI_SWAP_XY)
      LCD_SetSizeEx (0, YSIZE_PHYS,  XSIZE_PHYS);
      LCD_SetVSizeEx(0, YSIZE_PHYS,  XSIZE_PHYS);
    #else
      LCD_SetSizeEx (0, XSIZE_PHYS,  YSIZE_PHYS);
      LCD_SetVSizeEx(0, XSIZE_PHYS,  YSIZE_PHYS);
    #endif
  #endif
  #ifndef WIN32
    //
    // Orientation
    //
    Config.Orientation   = DISPLAY_ORIENTATION;
    Config.NumDummyReads = 1;
    GUIDRV_FlexColor_Config(pDevice, &Config);
    //
    // Driver configuration
    //
    PortAPI.pfWrite16_A0  = LCD_X_8080_16_Write00;
    PortAPI.pfWrite16_A1  = LCD_X_8080_16_Write01;
    PortAPI.pfWriteM16_A1 = LCD_X_8080_16_WriteM01;
    PortAPI.pfReadM16_A1  = LCD_X_8080_16_ReadM01;
    GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66719, GUIDRV_FLEXCOLOR_M16C0B16);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
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
