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

              Controller:     Raio RA8870
              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 16 bit interface

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

#ifndef WIN32
  #include "LCD_X_8080_16.h"
#endif

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS 640
#define YSIZE_PHYS 480

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

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
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION 0
#endif

//
// Register definitions
//
#define PWRR   0x01
#define PCLK   0x04
#define SYSR   0x10
#define HDWR   0x14
#define HNDFTR 0x15
#define HNDR   0x16
#define HSTR   0x17
#define HPWR   0x18
#define VDHR0  0x19
#define VDHR1  0x1A
#define VNDR0  0x1B
#define VNDR1  0x1C
#define VPWR   0x1F
#define PLLC1  0x88
#define PLLC2  0x89
#define P1CR   0x8A
#define P1DCR  0x8B

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetReg
*/
#ifndef WIN32
static void _SetReg(unsigned Reg, U16 Val) {
  LCD_X_8080_16_Write01(Reg);
  LCD_X_8080_16_Write00(Val);
}
#endif

/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes th e display controller
*/
static void _InitController(void) {
#ifndef WIN32
  LCD_X_8080_16_Init();
  _SetReg(  PCLK, 0x00);                    // Pixel Clock Setting Register
  _SetReg( PLLC1, 0x07);                    // PLL Control Register 1
  GUI_X_Delay(1);
  _SetReg( PLLC2, 0x02);                    // PLL Control Register 2
  GUI_X_Delay(1);
  _SetReg(  PWRR, 0x01);                    // Power and Display Control Register
  _SetReg(  PWRR, 0x00);
  GUI_X_Delay(1);
  _SetReg(  SYSR, 0x3F);                    // System Configuration Register
  GUI_X_Delay(1);
  _SetReg(  VPWR, 0x00);                    // VSYNC Pulse Width Register
  _SetReg(  HDWR, (XSIZE_PHYS / 8) - 1);    // LCD Horizontal Display Width Register
  _SetReg(HNDFTR, 0x00);                    // Horizontal Non-Display Period Fine Tuning Option Register
  _SetReg(  HNDR, 0x0F);                    // Horizontal Non-Display Period Register
  _SetReg(  HSTR, 0x06);                    // HSYNC Start Position register
  _SetReg(  HPWR, 0x00);                    // HSYNC PWM Register
  _SetReg( VDHR0, (YSIZE_PHYS - 1) & 0xFF); // LCD Vertical Display Height Register 0
  _SetReg( VDHR1, (YSIZE_PHYS - 1) >> 8);   // LCD Vertical Display Height Register 1
  _SetReg( VNDR0, 0x12);                    // LCD Vertical Non-Display Period Register 0
  _SetReg( VNDR1, 0x00);                    // LCD Vertical Non-Display Period Register 1
  _SetReg(  P1CR, 0x88);                    // PWM1 Control Register
  _SetReg( P1DCR, 0x80);                    // PWM1 Duty Cycle Register
  _SetReg(  PWRR, 0x80);                    // Power and Display Control Register
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
  GUI_DEVICE * pDevice;
  GUI_PORT_API PortAPI = {0};
  CONFIG_FLEXCOLOR Config = {0};

  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
  //
  // Function selection, hardware routines (PortAPI) and operation mode (bus, bpp and cache)
  //
  #ifndef WIN32
    PortAPI.pfWrite16_A0  = LCD_X_8080_16_Write00;
    PortAPI.pfWrite16_A1  = LCD_X_8080_16_Write01;
    PortAPI.pfWriteM16_A0 = LCD_X_8080_16_WriteM00;
    PortAPI.pfWriteM16_A1 = LCD_X_8080_16_WriteM01;
    PortAPI.pfRead16_A0   = LCD_X_8080_16_Read00;
    PortAPI.pfRead16_A1   = LCD_X_8080_16_Read01;
    PortAPI.pfReadM16_A0  = LCD_X_8080_16_ReadM00;
    PortAPI.pfReadM16_A1  = LCD_X_8080_16_ReadM01;
  #endif
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66721, GUIDRV_FLEXCOLOR_M16C0B16);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION;
  GUIDRV_FlexColor_Config(pDevice, &Config);
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

  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(pData);
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
