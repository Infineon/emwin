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

              Controller:     Novatek NT39122
              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 8 bit interface

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

#include "LCD_X_8080_8.h"
#include "GUIDRV_FlexColor.h"

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
#define YSIZE_PHYS 160

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)

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
  GUI_X_Delay(10);
  LCD_X_8080_8_Init();
  GUI_X_Delay(10);
  LCD_X_8080_8_Write00(0x11); /* SLPOUT */
  GUI_X_Delay(120);
  LCD_X_8080_8_Write00(0x26); /* GAMSET */
  LCD_X_8080_8_Write01(0x10);
  LCD_X_8080_8_Write00(0x35); /* TEON */
  LCD_X_8080_8_Write01(0x00);
  LCD_X_8080_8_Write00(0x36); /* MADCTL */
  LCD_X_8080_8_Write01(0x08);
  LCD_X_8080_8_Write00(0x3A); /* COLMOD */
  LCD_X_8080_8_Write01(0x55);
  LCD_X_8080_8_Write00(0xB3); /* FRMCTR3 */
  LCD_X_8080_8_Write01(0x54);
  LCD_X_8080_8_Write01(0x3F);
  LCD_X_8080_8_Write00(0xB4); /* INVCTR */
  LCD_X_8080_8_Write01(0x02);
  LCD_X_8080_8_Write00(0xB6); /* DISSET5 */
  LCD_X_8080_8_Write01(0x11);
  LCD_X_8080_8_Write01(0x22);
  LCD_X_8080_8_Write00(0xC0); /* PWCTR1 */
  LCD_X_8080_8_Write01(0x01);
  LCD_X_8080_8_Write00(0xC1); /* PWCTR2 */
  LCD_X_8080_8_Write01(0x06);
  LCD_X_8080_8_Write00(0xC4); /* PWCTR5 */
  LCD_X_8080_8_Write01(0x25);
  LCD_X_8080_8_Write01(0x00);
  LCD_X_8080_8_Write00(0xC5); /* VMCTR1 */
  LCD_X_8080_8_Write01(0x44);
  LCD_X_8080_8_Write01(0x64);
  LCD_X_8080_8_Write00(0x29); /* DISON */
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
  GUI_PORT_API PortAPI;
  CONFIG_FLEXCOLOR Config = {0};

  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    LCD_SetSizeEx (0, YSIZE_PHYS,   XSIZE_PHYS);
    LCD_SetVSizeEx(0, VYSIZE_PHYS,  VXSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
    LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
  }
  //
  // Function selection, hardware routines (PortAPI) and operation mode (bus, bpp and cache)
  //
  PortAPI.pfWrite8_A0  = LCD_X_8080_8_Write00;
  PortAPI.pfWrite8_A1  = LCD_X_8080_8_Write01;
  PortAPI.pfWriteM8_A0 = LCD_X_8080_8_WriteM00;
  PortAPI.pfWriteM8_A1 = LCD_X_8080_8_WriteM01;
  PortAPI.pfRead8_A0   = LCD_X_8080_8_Read00;
  PortAPI.pfRead8_A1   = LCD_X_8080_8_Read01;
  PortAPI.pfReadM8_A0  = LCD_X_8080_8_ReadM00;
  PortAPI.pfReadM8_A1  = LCD_X_8080_8_ReadM01;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C1B8);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION;
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    if (DISPLAY_ORIENTATION & GUI_MIRROR_Y) {
      Config.FirstSEG = 60;
    }
  } else {
    if (DISPLAY_ORIENTATION & GUI_MIRROR_Y) {
      Config.FirstCOM = 60;
    }
  }
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
