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

#include <stddef.h>

#ifndef WIN32
  #include "LCD_X_8080_16.h"
#endif

#include "GUI.h"
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
#define YSIZE_PHYS 320

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
//#define DISPLAY_ORIENTATION (0)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y | GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y | GUI_SWAP_XY)

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
  LCD_X_8080_16_Init();
  GUI_X_Delay(10);

  LCD_X_8080_16_Write00(0x01); //Soft Reset
  GUI_X_Delay(30);
  LCD_X_8080_16_Write00(0x28); //Display OFF

  LCD_X_8080_16_Write00(0xf7);
  LCD_X_8080_16_Write01(0x20);

  LCD_X_8080_16_Write00(0xea);
  LCD_X_8080_16_Write01(0x00);
  LCD_X_8080_16_Write01(0x00);

  LCD_X_8080_16_Write00(0xc0); //PWCTR1
  LCD_X_8080_16_Write01(0x26);    //VRH: 4.75V

  LCD_X_8080_16_Write00(0xc1); //PWCTR2
  LCD_X_8080_16_Write01(0x11);    //AVDD: VCIx2, VGH: VCIx7, VGL: -VCIx3

  LCD_X_8080_16_Write00(0xc5); //VMCTR1
  LCD_X_8080_16_Write01(0x35);    //4.025V VCOMH
  LCD_X_8080_16_Write01(0x3e);    //-0.95V VCOML

  LCD_X_8080_16_Write00(0xc7); //VMCTR2
  LCD_X_8080_16_Write01(0xbe);    //VMF: VMH–2, VML–2

  LCD_X_8080_16_Write00(0x3a); //Pixel Format Set
  LCD_X_8080_16_Write01(0x55);    //

  LCD_X_8080_16_Write00(0xb1); //Frame Control (Normal mode)
  LCD_X_8080_16_Write01(0x00);    //Default: 0x00
  LCD_X_8080_16_Write01(0x1B);    //Default: 0x1B

  LCD_X_8080_16_Write00(0x26); //Gamma Set
  LCD_X_8080_16_Write01(0x01);    //Default: 0x01

  LCD_X_8080_16_Write00(0x11); //Sleep OUT
  GUI_X_Delay(100);
  LCD_X_8080_16_Write00(0x29); //Display ON
  GUI_X_Delay(100);
  #endif
}

/*********************************************************************
*
*       _ReadPixel
*/
static U16 _ReadPixel(int LayerIndex) {
  #ifndef WIN32
  U16 aData[3];
  U16 Index;

  GUI_USE_PARA(LayerIndex);
  //
  // Switch to read mode
  //
  LCD_X_8080_16_Write00(0x2E);
  //
  // Dummy- and data read
  //
  LCD_X_8080_16_ReadM01(aData, GUI_COUNTOF(aData));
  //
  // Convert to index
  //
  Index = (aData[2] >> 11) | ((aData[1] & 0xfc) << 3) | (aData[1] & 0xf800);
  #else
  U16 Index;

  GUI_USE_PARA(LayerIndex);
  Index = 0;
  #endif
  return Index;
}

/*********************************************************************
*
*       _ReadMPixels
*/
static void _ReadMPixels(int LayerIndex, U16 * pBuffer, U32 NumPixels) {
  #ifndef WIN32
  U16 Data;
  U16 Index;
  int State;

  GUI_USE_PARA(LayerIndex);
  //
  // Switch to read mode
  //
  LCD_X_8080_16_Write00(0x2E);
  //
  // Dummy- read
  //
  LCD_X_8080_16_Read01();
  for (State = 0; NumPixels; NumPixels--, State ^= 1) {
    switch (State) {
    case 0:
      Data = LCD_X_8080_16_Read01();
      Index  =  Data & 0xf800;        // blue
      Index |= (Data & 0x00fc) <<  3; // green
      Data = LCD_X_8080_16_Read01();
      Index |= (Data & 0xf800) >> 11; // red
      break;
    case 1:
      Index  = (Data & 0x00f8) <<  8; // blue
      Data = LCD_X_8080_16_Read01();
      Index |= (Data & 0xfc00) >>  5; // green
      Index |= (Data & 0x00f8) >>  3; // red
      break;
    }
    *pBuffer++ = Index;
  }
  #else
  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(pBuffer);
  GUI_USE_PARA(NumPixels);
  #endif
  return;
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
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B16);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set custom reading function(s)
  //
  LCD_SetDevFunc(0, LCD_DEVFUNC_READPIXEL,   (void(*)(void))_ReadPixel);
  LCD_SetDevFunc(0, LCD_DEVFUNC_READMPIXELS, (void(*)(void))_ReadMPixels);
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
