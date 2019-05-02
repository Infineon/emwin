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
Purpose     : Sample  configuration file for GUIDRV_FlexColor

Display     : OSD128128P2903 with LD7138 (SP9230) OLED controller

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

#include "LCD_X_SPI4.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE 128
#define YSIZE 128

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
#define DISPLAY_ORIENTATION (0)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y | GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y | GUI_SWAP_XY)

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
  LCD_X_SPI4_Init();
  LCD_X_SPI4_Write0(0x01);  // Software Reset	
  LCD_X_SPI4_Write0(0x02);  // Set Dot Matrix Display ON/OFF		
  LCD_X_SPI4_Write1(0x00);  //  OFF
  LCD_X_SPI4_Write0(0x03);  // Set Dot Matrix Display Stand-by ON/OFF	
  LCD_X_SPI4_Write1(0x00);  //  Indicates the dot oscillator is starting.
  LCD_X_SPI4_Write0(0x04);  // Set OSC Control
  LCD_X_SPI4_Write1(0x04);  //
  LCD_X_SPI4_Write0(0x06);  // Set Row Scan Direction
  LCD_X_SPI4_Write1(0x00);  //
  LCD_X_SPI4_Write0(0x07);  // Set Display Size
  LCD_X_SPI4_Write1(0x00);  //  Xstart 1
  LCD_X_SPI4_Write1(0x00);  //  Xstart 2
  LCD_X_SPI4_Write1(0x07);  //  Xend 1
  LCD_X_SPI4_Write1(0x0f);  //  Xend 2
  LCD_X_SPI4_Write1(0x00);  //  Ystart 1
  LCD_X_SPI4_Write1(0x00);  //  Ystart 2
  LCD_X_SPI4_Write1(0x07);  //  Yend 1
  LCD_X_SPI4_Write1(0x0F);  //  Yend 2
  LCD_X_SPI4_Write0(0x08);  // Set Interface Bus Type
  LCD_X_SPI4_Write1(0x01);  //  8Bit I/F Bus
  LCD_X_SPI4_Write0(0x09);  // Set Masking Data
  LCD_X_SPI4_Write1(0x07);  //  Output Data
  LCD_X_SPI4_Write0(0x0E);  // Set Dot Matrix Current Level		
  LCD_X_SPI4_Write1(0x0f);  //  1th Parameter R
  LCD_X_SPI4_Write1(0x0f);  //  2th Parameter R
  LCD_X_SPI4_Write1(0x07);  //  3rd Parameter G
  LCD_X_SPI4_Write1(0x00);  //  4th Parameter G
  LCD_X_SPI4_Write1(0x0C);  //  5st Parameter B
  LCD_X_SPI4_Write1(0x0f);  //  6nd Parameter B
  LCD_X_SPI4_Write0(0x0F);  // Set Dot Matrix Peak Current Level		
  LCD_X_SPI4_Write1(0x3f);  //  1rd Parameter R	
  LCD_X_SPI4_Write1(0x3f);  //  2nd Parameter G
  LCD_X_SPI4_Write1(0x3f);  //  3st Parameter B
  LCD_X_SPI4_Write0(0x1C);  // Set Pre-Charge Width
  LCD_X_SPI4_Write1(0x03);  //
  LCD_X_SPI4_Write0(0x1D);  // Set Peak Pulse Width
  LCD_X_SPI4_Write1(0x01);  //  R	
  LCD_X_SPI4_Write1(0x01);  //  G
  LCD_X_SPI4_Write1(0x01);  //  B
  LCD_X_SPI4_Write0(0x1E);  // Set Peak Pulse Delay
  LCD_X_SPI4_Write1(0x03);  //
  LCD_X_SPI4_Write0(0x1F);  // Set Row Scan Operation
  LCD_X_SPI4_Write1(0x20);  //
  LCD_X_SPI4_Write0(0x30);  // Internal Regulator for Row Scan
  LCD_X_SPI4_Write1(0x10);  //
  LCD_X_SPI4_Write0(0x3c);  // Set VDD Selection
  LCD_X_SPI4_Write1(0x01);  //  1.8V
  LCD_X_SPI4_Write0(0x02);  // Set Dot Matrix Display ON/OFF		
  LCD_X_SPI4_Write1(0x01);  //  ON
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
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(pData);
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    _InitController();
    return 0;
  }
  default:
    return -1;
  }
}

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
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Common display driver configuration
  //
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    LCD_SetSizeEx (0, YSIZE, XSIZE);
    LCD_SetVSizeEx(0, YSIZE, XSIZE);
  } else {
    LCD_SetSizeEx (0, XSIZE, YSIZE);
    LCD_SetVSizeEx(0, XSIZE, YSIZE);
  }
  //
  // Setup hardware access routines
  //
  #ifndef WIN32
  PortAPI.pfWrite8_A0  = LCD_X_SPI4_Write0;
  PortAPI.pfWrite8_A1  = LCD_X_SPI4_Write1;
  PortAPI.pfWriteM8_A1 = LCD_X_SPI4_WriteM1;
  PortAPI.pfRead8_A1   = LCD_X_SPI4_Read1;
  PortAPI.pfReadM8_A1  = LCD_X_SPI4_ReadM1;
  #endif
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66723, GUIDRV_FLEXCOLOR_M16C1B8);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION;
  GUIDRV_FlexColor_Config(pDevice, &Config);
}

/*************************** End of file ****************************/
