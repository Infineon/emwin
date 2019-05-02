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
#include "GUIDRV_FlexColor.h"
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
#define COLOR_CONVERSION GUICC_565

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

/*********************************************************************
*
*       Register definitions
*
**********************************************************************
*/
#define _DRVR_OUT_CTRL          0x01
#define _LCD_WAVE_CTRL          0x02
#define _ENTRY_MODE             0x03

#define _DISPLAY_CTRL_1         0x07
#define _DISPLAY_CTRL_2         0x08
#define _DISPLAY_CTRL_3         0x09
#define _DISPLAY_CTRL_4         0x0A

#define _PWR_CTRL_1             0x10
#define _PWR_CTRL_2             0x11
#define _PWR_CTRL_3             0x12
#define _PWR_CTRL_4             0x13

#define _REGULATOR_CTRL         0x15

#define _ADDR_SET_H             0x20
#define _ADDR_SET_V             0x21
#define _DATA_SET               0x22

#define _GAMMA_CTRL_1           0x30
#define _GAMMA_CTRL_2           0x31
#define _GAMMA_CTRL_3           0x32
#define _GAMMA_CTRL_4           0x33
#define _GAMMA_CTRL_5           0x34
#define _GAMMA_CTRL_6           0x35
#define _GAMMA_CTRL_7           0x36
#define _GAMMA_CTRL_8           0x37
#define _GAMMA_CTRL_9           0x38
#define _GAMMA_CTRL_10          0x39

#define _EPROM_CTRL_REG_1       0x40
#define _EPROM_CTRL_REG_2       0x41
#define _EPROM_CTRL_REG_3       0x42

#define _DRVR_OUT_CTRL_X        0x60
#define _BASE_IMG_DIS_CTRL      0x61

#define _PANEL_INTERFACE_CTRL_1 0x90
#define _PANEL_INTERFACE_CTRL_2 0x92
#define _PANEL_INTERFACE_CTRL_3 0x93
#define _PANEL_INTERFACE_CTRL_4 0x95
#define _PANEL_INTERFACE_CTRL_5 0x97
#define _PANEL_INTERFACE_CTRL_6 0x98

#define _TEST_REG_1             0xA0
#define _TEST_REG_2             0xA1
#define _TEST_REG_3             0xA2

/********************************************************************
*
*       _SetReg
*/
#ifndef WIN32
static void _SetReg(U16 Reg, U16 Data) {
  LCD_X_8080_16_Write00_16(Reg);
  LCD_X_8080_16_Write01_16(Data);
}
#endif

/********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes the LCD controller
*
*/
#ifndef WIN32
static void _InitController(void) {
  _SetReg(_PWR_CTRL_1,             0x0628);
  _SetReg(_PWR_CTRL_3,             0x0006);
  _SetReg(_PWR_CTRL_4,             0x0A32);
  _SetReg(_PWR_CTRL_2,             0x0040);
  _SetReg(_REGULATOR_CTRL,         0x0050);
  _SetReg(_PWR_CTRL_3,             0x0016);
  GUI_X_Delay(15);                    
  _SetReg(_PWR_CTRL_1,             0x5660);
  GUI_X_Delay(15);                    
  _SetReg(_PWR_CTRL_4,             0x2A4E);
  _SetReg(_DRVR_OUT_CTRL,          0x0100);
  _SetReg(_LCD_WAVE_CTRL,          0x0300);
  _SetReg(_ENTRY_MODE,             0x1038);
  _SetReg(_DISPLAY_CTRL_2,         0x0202);
  _SetReg(_DISPLAY_CTRL_4,         0x0000);
  _SetReg(_GAMMA_CTRL_1,           0x0000);
  _SetReg(_GAMMA_CTRL_2,           0x0402);
  _SetReg(_GAMMA_CTRL_3,           0x0106);
  _SetReg(_GAMMA_CTRL_4,           0x0700);
  _SetReg(_GAMMA_CTRL_5,           0x0104);
  _SetReg(_GAMMA_CTRL_6,           0x0301);
  _SetReg(_GAMMA_CTRL_7,           0x0707);
  _SetReg(_GAMMA_CTRL_8,           0x0305);
  _SetReg(_GAMMA_CTRL_9,           0x0208);
  _SetReg(_GAMMA_CTRL_10,          0x0F0B);
  GUI_X_Delay(15);
  _SetReg(_EPROM_CTRL_REG_2,       0x0002);
  _SetReg(_DRVR_OUT_CTRL_X,        0x2700);
  _SetReg(_BASE_IMG_DIS_CTRL,      0x0001);
  _SetReg(_PANEL_INTERFACE_CTRL_1, 0x0119);
  _SetReg(_PANEL_INTERFACE_CTRL_2, 0x010A);
  _SetReg(_PANEL_INTERFACE_CTRL_3, 0x0004);
  _SetReg(_TEST_REG_1,             0x0100);
  _SetReg(_DISPLAY_CTRL_1,         0x0001);
  GUI_X_Delay(15);
  _SetReg(_DISPLAY_CTRL_1,         0x0021); 
  GUI_X_Delay(15);
  _SetReg(_DISPLAY_CTRL_1,         0x0023);
  GUI_X_Delay(15);
  _SetReg(_DISPLAY_CTRL_1,         0x0033);
  GUI_X_Delay(15);
  _SetReg(_DISPLAY_CTRL_1,         0x0133);
  GUI_X_Delay(15);
  _SetReg(_TEST_REG_1,             0x0000);
  GUI_X_Delay(20);
}
#endif

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
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  LCD_SetSizeEx    (0, XSIZE_PHYS,   YSIZE_PHYS);
  LCD_SetVSizeEx   (0, VXSIZE_PHYS,  VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.Orientation   = GUI_MIRROR_X | GUI_SWAP_XY;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  #ifndef WIN32
  PortAPI.pfWrite16_A0  = LCD_X_8080_16_Write00_16;
  PortAPI.pfWrite16_A1  = LCD_X_8080_16_Write01_16;
  PortAPI.pfWriteM16_A1 = LCD_X_8080_16_WriteM01_16;
  PortAPI.pfReadM16_A1  = LCD_X_8080_16_ReadM01_16;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
  #endif
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
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;

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
    // ...
    #ifndef WIN32
    _InitController();
    #endif
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
