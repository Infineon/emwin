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
#define XSIZE_PHYS 320
#define YSIZE_PHYS 240

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M666  // GUICC_M888 does not work!!!

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
//#define DISPLAY_ORIENTATION (0)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)
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
  U8 Status;

  LCD_X_8080_8_Init();
  LCD_X_8080_8_Write00(0x01);            //Software Reset
  GUI_X_Delay(10);

  LCD_X_8080_8_Write00(0xe2);            //Configure PLL
  LCD_X_8080_8_Write01(0x1d);
  LCD_X_8080_8_Write01(0x02);
  LCD_X_8080_8_Write01(0x54);

  LCD_X_8080_8_Write00(0xe0);     //START PLL
  LCD_X_8080_8_Write01(0x01);
  GUI_X_Delay(5);

  // Verify PLL has locked
  do {
    LCD_X_8080_8_Write00(0xe4);
    Status = LCD_X_8080_8_Read01();
  } while (!(Status & 0x04));

  LCD_X_8080_8_Write00(0xe0);     //LOCK PLL
  LCD_X_8080_8_Write01(0x03);

  LCD_X_8080_8_Write00(0x01);            //Software Reset

  LCD_X_8080_8_Write00(0xb0);            //SET LCD MODE  SET TFT 24Bits MODE
  LCD_X_8080_8_Write01(0x2c);               //SET TFT MODE & hsync+Vsync+DEN MODE
  LCD_X_8080_8_Write01(0x00);               //SET TFT MODE & hsync+Vsync+DEN MODE
  LCD_X_8080_8_Write01(0x01);               //SET horizontal size=320-1 HightByte
  LCD_X_8080_8_Write01(0x3f);               //SET horizontal size=320-1 LowByte
  LCD_X_8080_8_Write01(0x00);               //SET vertical size=240-1 HightByte
  LCD_X_8080_8_Write01(0xef);               //SET vertical size=240-1 LowByte
  LCD_X_8080_8_Write01(0x00);               //SET even/odd line RGB seq.=RGB

  LCD_X_8080_8_Write00(0xb4);            //SET HBP,
  LCD_X_8080_8_Write01(0x01);               //SET HSYNC Total 440
  LCD_X_8080_8_Write01(0xb8);
  LCD_X_8080_8_Write01(0x00);               //SET HBP 68
  LCD_X_8080_8_Write01(0x44);
  LCD_X_8080_8_Write01(0x0f);               //SET VBP 16=15+1
  LCD_X_8080_8_Write01(0x00);               //SET Hsync pulse start position
  LCD_X_8080_8_Write01(0x00);
  LCD_X_8080_8_Write01(0x00);               //SET Hsync pulse subpixel start position

  LCD_X_8080_8_Write00(0xf0);     //SET pixel data I/F format=8bit
  LCD_X_8080_8_Write01(0x00);

  LCD_X_8080_8_Write00(0xb6);            //SET VBP,
  LCD_X_8080_8_Write01(0x01);               //SET Vsync total 265=264+1
  LCD_X_8080_8_Write01(0x08);
  LCD_X_8080_8_Write01(0x00);               //SET VBP=19
  LCD_X_8080_8_Write01(0x13);
  LCD_X_8080_8_Write01(0x07);               //SET Vsync pulse 8=7+1
  LCD_X_8080_8_Write01(0x00);               //SET Vsync pulse start position
  LCD_X_8080_8_Write01(0x00);

  LCD_X_8080_8_Write00(0xe6);            //SET PCLK freq; pixel clock frequency
  LCD_X_8080_8_Write01(0x00);
  LCD_X_8080_8_Write01(0xe7);
  LCD_X_8080_8_Write01(0x4f);

  //
  // Test
  //
  if (0) {
    int x, y;

    LCD_X_8080_8_Write00(0x29);
    //
    // Set rect
    //
    LCD_X_8080_8_Write00(0x2a);
    LCD_X_8080_8_Write01(0x00);
    LCD_X_8080_8_Write01(0x00);
    LCD_X_8080_8_Write01(0x01);
    LCD_X_8080_8_Write01(0x3f);
    LCD_X_8080_8_Write00(0x2b);
    LCD_X_8080_8_Write01(0x00);
    LCD_X_8080_8_Write01(0x00);
    LCD_X_8080_8_Write01(0x00);
    LCD_X_8080_8_Write01(0xef);
    LCD_X_8080_8_Write00(0x2c);
    //
    // Simple gray gradient using 8 bits does not work!!!
    //
    for (y = 0; y < 240; y++) {
      for (x = 0; x < 320; x++) {
        LCD_X_8080_8_Write01(y);
        LCD_X_8080_8_Write01(y);
        LCD_X_8080_8_Write01(y);
      }
    }
    while (1);
  }
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
  // Display size configuration
  //
  LCD_SetSizeEx (0, XSIZE_PHYS,  YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Function selection, hardware routines (PortAPI) and operation mode (bus, bpp and cache)
  //
  PortAPI.pfWrite8_A0  = LCD_X_8080_8_Write00;
  PortAPI.pfWrite8_A1  = LCD_X_8080_8_Write01;
  PortAPI.pfWriteM8_A1 = LCD_X_8080_8_WriteM01;
  PortAPI.pfReadM8_A1  = LCD_X_8080_8_ReadM01;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66720, GUIDRV_FLEXCOLOR_M24C0B8);
  //
  // Set dummy reads to 0 (-1 required to do that!)
  //
  Config.NumDummyReads = -1;
  Config.Orientation   = DISPLAY_ORIENTATION;
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
  case LCD_X_OFF: {
    LCD_X_8080_8_Write00(0x28);
    break;
  }
  case LCD_X_ON: {
    LCD_X_8080_8_Write00(0x29);
    break;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
