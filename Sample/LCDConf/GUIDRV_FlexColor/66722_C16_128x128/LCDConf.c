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

#ifndef WIN32
  #include "LCD_X_6800_8.h"
#endif

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
#define XSIZE_PHYS 128
#define YSIZE_PHYS 128

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation (choose one of the following options)
//
//#define DISPLAY_ORIENTATION (0)
#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
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
*       Display controller register definitions
*
**********************************************************************
*/

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
  LCD_X_6800_8_Init();
  GUI_X_Delay(10);
  LCD_X_6800_8_Write00(0xAE); // Display OFF (enable sleep mode)
  LCD_X_6800_8_Write00(0xFD); // Command Lock
  LCD_X_6800_8_Write01(0x12); // Unlock general commands
  //------------LOCKED COMMANDS BY (0xFD, 0xB1)---------------
  LCD_X_6800_8_Write00(0xFD); // Command Lock
  LCD_X_6800_8_Write01(0xB1); // Unlock commands A2, B1, B3, BB, BE, C1
  LCD_X_6800_8_Write00(0xA2); // Set display line offset
  LCD_X_6800_8_Write01(0x00); // A[6:0]=00h (Range 0-127)
  LCD_X_6800_8_Write00(0xB1); // Set Reset (Phase1) / Precharge (Phase2) period
  LCD_X_6800_8_Write01(0x32); // 0x32...A[7:4]=0011b (Phase 2 period = 7 DCLKs), A[3:0]=0010b (Phase 1 period = 5 DCLKs)
  LCD_X_6800_8_Write00(0xB3); // Set Oscillator Frequency / Front Clock Divider		Note: Divider changed from 2 (default) to 1 to reduce EMI on supply/sensor!
  LCD_X_6800_8_Write01(0xE0); // A[7:4]=1110b (Oscillator frequency, default 1101b), A[3:0]=0000b (divide by 1, default=0010b)
  LCD_X_6800_8_Write00(0xBB); // Set First Precharge Voltage
  LCD_X_6800_8_Write01(0x17); // A[4:0]=10111b (Range 0-31, corresponding to 0.2-0.6 x VCC)
  LCD_X_6800_8_Write00(0xBE); // Set VcomH voltage
  LCD_X_6800_8_Write01(0x03); // A[2:0]=011b (Range 0-7, corresponding to 0.72-0.86 x VCC)
  LCD_X_6800_8_Write00(0xC1); // Set Contrast current for individual colors (all inc'd by 70% after F_osc doubling)
  LCD_X_6800_8_Write01(0xEA); // For Color A (default/reset=8Ah) //B4 for settings: freq 0xD0
  LCD_X_6800_8_Write01(0x88); // For Color B (default/reset=51h) //69
  LCD_X_6800_8_Write01(0xEA); // For Color C (default/reset=8Ah) //B4
  LCD_X_6800_8_Write00(0xFD); // Command lock
  LCD_X_6800_8_Write01(0xB0); // Lock commands A2, B1, B3, BB, BE, C1 from accidental change
  //------------End of LOCKED COMMANDS BY (0xFD, 0xB1)---------------
  LCD_X_6800_8_Write00(0xA0);
  LCD_X_6800_8_Write01(0xF3); // Set re-map and color depth (horizontal address increment)
  LCD_X_6800_8_Write00(0xAB); // Function Selection
  LCD_X_6800_8_Write01(0x01); // A[7:6]=00b (8-bit parallel), A[0]=1b (Enable internal VDD regulator)
  // VSL changes have no apparent effect on display...
  LCD_X_6800_8_Write00(0xB4); // Set segment low voltage (VSL)
  LCD_X_6800_8_Write01(0xA0); // A[1:0]=00b (External VSL)   // A[1:0]=10 (Internal VSL)
  LCD_X_6800_8_Write01(0xB5);
  LCD_X_6800_8_Write01(0x55);
  LCD_X_6800_8_Write00(0xCA); // Set MUX Ratio
  LCD_X_6800_8_Write01(0x7F); // Range 15-127
  LCD_X_6800_8_Write00(0xB6); // Set Second Precharge Period
  LCD_X_6800_8_Write01(0x01); // A[3:0]=0001b (1 DCLKs)
  LCD_X_6800_8_Write00(0xC7); // Master contrast current control
  LCD_X_6800_8_Write00(0x0F); // Set contrast level
  // reduce output currents for all colors to... A[3:0]=1111b (no reduction)
  LCD_X_6800_8_Write00(0xB5); // Set GPIO
  LCD_X_6800_8_Write01(0x00); // A[3:2]=00b (GPIO1 input disabled, HiZ), A[1:0]=00b (GPIO0 input disabled, HiZ)
  LCD_X_6800_8_Write00(0xA1); // Set display start line
  LCD_X_6800_8_Write01(0x00); // A[6:0]=00h (Range 0-127)
  LCD_X_6800_8_Write00(0xB9); // Load built-in linear look-up table for gray scale
  LCD_X_6800_8_Write00(0x96); // Set horizontal scroll
  LCD_X_6800_8_Write01(0x01); // A[6:0]=0x01 (scroll towards SEG127 with 1 column offset)
  LCD_X_6800_8_Write01(0x00); // B[6:0]=0x00 (start row address)
  LCD_X_6800_8_Write01(0x7F); // C[7:0]=0x7F (number of rows to be H-scrolled). Requirement: B+C <= 128
  LCD_X_6800_8_Write01(0x00); // D[6:0] reserved
  LCD_X_6800_8_Write01(0x00); // E[1:0]=0x00 (scrolling time interval - test mode)
  LCD_X_6800_8_Write00(0x9E); // stop scrolling (Rewrite GDDRAM after scrolling has been stopped!)
  LCD_X_6800_8_Write00(0xA6); // Set display mode to normal display
  LCD_X_6800_8_Write00(0xAF); // Display ON (disable sleep mode)
  GUI_X_Delay(100);
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
  // Display size configuration
  //
  LCD_SetSizeEx (0, XSIZE_PHYS,  YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Function selection, hardware routines (PortAPI) and operation mode (bus, bpp and cache)
  //
  #ifndef WIN32
  PortAPI.pfWrite8_A0  = LCD_X_6800_8_Write00;
  PortAPI.pfWrite8_A1  = LCD_X_6800_8_Write01;
  PortAPI.pfWriteM8_A1 = LCD_X_6800_8_WriteM01;
  PortAPI.pfReadM8_A1  = LCD_X_6800_8_ReadM01;
  #endif
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66722, GUIDRV_FLEXCOLOR_M16C0B8);
  //
  // Orientation
  //
  Config.Orientation  = DISPLAY_ORIENTATION; // Please configure orientation at the top of this file
  Config.RegEntryMode = 0x20;                // Enable COM Split Odd Even
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
