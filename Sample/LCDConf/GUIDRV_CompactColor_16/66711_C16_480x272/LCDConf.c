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
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272

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
*       Register definitions
*
**********************************************************************
*/
#define REG_SYSTEM_BASE              0x00       ///< SYSTEM REGISTERS
#define REG00_PRODINFO               0x00       ///< Revision Code Register [READONLY]
#define REG02_CFGPINS                0x02       ///< Configuration Readback Register [READONLY]
#define REG_SYSTEM_END               0x03      

#define REG_CLOCK_BASE               0x04       ///< CLOCK REGISTERS
#define REG04_PLLMDIV                0x04       ///< PLL M-Divider Register 0
#define REG06_PLL0                   0x06       ///< PLL Setting Register 0
#define REG08_PLL1                   0x08       ///< PLL Setting Register 1
#define REG0A_PLL2                   0x0A       ///< PLL Setting Register 2
#define REG0C_PLL3                   0x0C       ///< PLL Setting Register 3
#define REG0E_PLL4                   0x0E       ///< PLL Setting Register 4
#define REG12_CLKSRC                 0x12       ///< Clock Source Select Register
#define REG_CLOCK_END                0x13      

#define REG_LCD_BASE                 0x14       ///< LCD REGISTERS
#define REG14_PNLTYPE                0x14       ///< Panel Type Register
#define REG16_HDISP                  0x16       ///< Horizontal Display Width Register
#define REG18_HNDP                   0x18       ///< Horizontal Non-Display Period Register
#define REG1A_VDISP0                 0x1A       ///< Vertical Display Height Register 0
#define REG1C_VDISP1                 0x1C       ///< Vertical Display Height Register 1
#define REG1E_VNDP                   0x1E       ///< Vertical Non-Display Period Register
#define REG20_HSW                    0x20       ///< HS Pulse Width Register
#define REG22_HPS                    0x22       ///< HS Pulse Start Position Register 0
#define REG24_VSW                    0x24       ///< VS Pulse Width Register
#define REG26_VPS                    0x26       ///< VS Pulse Start Position Register 0
#define REG28_PCLKPOL                0x28       ///< PCLK Polarity Register
#define REG_LCD_END                  0x29      

#define REG_INPUT_BASE               0x2A       ///< INPUT REGISTERS
#define REG2A_INMODE                 0x2A       ///< Input Mode Register
#define REG2C_YUVTRANS0              0x2C       ///< Input YUV/RGB Translate Mode Register 0
#define REG2E_YUVTRANS1              0x2E       ///< YUV/RGB Translate Mode Register 1
#define REG30_UDATAFIX               0x30       ///< U Data Fix Register
#define REG32_VDATAFIX               0x32       ///< V Data Fix Register
#define REG_INPUT_END                0x33      

#define REG_DISPLAY_BASE             0x34       ///< DISPLAY REGISTERS
#define REG34_DISPMODE               0x34       ///< Display Mode Register
#define REG36_EFFECTS                0x36       ///< Special Effects Register
#define REG_DISPLAY_END              0x37      

#define REG_WINDOW_BASE              0x38       ///< WINDOW REGISTERS
#define REG38_WINXSPOS0              0x38       ///< Window X Start Position Register 0
#define REG3A_WINXSPOS1              0x3A       ///< Window X Start Position Register 1
#define REG3C_WINYSPOS0              0x3C       ///< Window Y Start Position Register 0
#define REG3E_WINYSPOS1              0x3E       ///< Window Y Start Position Register 1
#define REG40_WINXEPOS0              0x40       ///< Window X End Position Register 0
#define REG42_WINXEPOS1              0x42       ///< Window X End Position Register 1
#define REG44_WINYEPOS0              0x44       ///< Window Y End Position Register 0
#define REG46_WINYEPOS1              0x46       ///< Window Y End Position Register 1
#define REG_WINDOW_END               0x47      

#define REG_MEMORY_BASE              0x48       ///< MEMORY REGISTERS
#define REG48_MEMPORT0               0x48       ///< Memory Data Port Register 0
#define REG49_MEMPORT1               0x49       ///< Memory Data Port Register 1
#define REG4A_MEMRDADDR0             0x4A       ///< Memory Read Address Register 0
#define REG4C_MEMRDADDR1             0x4C       ///< Memory Read Address Register 1
#define REG4E_MEMRDADDR2             0x4E       ///< Memory Read Address Register 2
#define REG_MEMORY_END               0x4F      

#define REG_GAMMA_BASE               0x50       ///< GAMMA REGISTERS
#define REG50_GAMMAEN                0x50       ///< Gamma Correction Enable Register
#define REG52_GAMMATBLIDX            0x52       ///< Gamma Correction Table Index Register
#define REG54_GAMMATBLDATA           0x54       ///< Gamma Correction Table Data Register
#define REG_GAMMA_END                0x55      

#define REG_MISC_BASE                0x56       ///< MISC REGISTERS
#define REG56_PWRSAVE                0x56       ///< Power Save Register
#define REG58_NDPCTRL                0x58       ///< Non-Display Period Control / Status Register
#define REG_MISC_END                 0x59      

#define REG_GPIO_BASE                0x5A       ///< GPIO REGISTERS
#define REG5A_GPIOCNF0               0x5A       ///< General Purpose IO Pins Configuration Register 0
#define REG5C_GPIOSTAT0              0x5C       ///< General Purpose IO Pins Status/Control Register 0
#define REG5E_GPIOPOSINT             0x5E       ///< GPIO Positive Edge Interrupt Trigger Register
#define REG60_GPIONEGINT             0x60       ///< GPIO Negative Edge Interrupt Trigger Register
#define REG62_GPIOINTSTAT            0x62       ///< GPIO Interrupt Status Register
#define REG64_GPIOPDCTRL0            0x64       ///< GPIO Pull Down Control Register 0
#define REG_GPIO_END                 0x65      

// SPECIAL FLAGS
#define REGFLAG_BASE                 0xF0       ///< Special reserved flags beyond this point
#define REGFLAG_DELAY                0xFC       ///< Delay (in us)
#define REGFLAG_OFFDELAY             0xFD       ///< LCD Panel Power Off Delay (in ms)
#define REGFLAG_ONDELAY              0xFE       ///< LCD Panel Power On Delay (in ms)
#define REGFLAG_ENDOFTABLE           0xFF       ///< End of Registers Marker

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
static void _InitController(void) {
  #ifndef WIN32
  LCD_WRITE_A0(REG56_PWRSAVE     ); LCD_WRITE_A1(0x02);
  LCD_WRITE_A0(REG04_PLLMDIV     ); LCD_WRITE_A1(0x03);
  LCD_WRITE_A0(REG06_PLL0        ); LCD_WRITE_A1(0xF8);
  LCD_WRITE_A0(REG08_PLL1        ); LCD_WRITE_A1(0x80);
  LCD_WRITE_A0(REG0A_PLL2        ); LCD_WRITE_A1(0x28);
  LCD_WRITE_A0(REG0C_PLL3        ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG0E_PLL4        ); LCD_WRITE_A1(0x3B);
  LCD_WRITE_A0(REG12_CLKSRC      ); LCD_WRITE_A1(0x49);
  LCD_WRITE_A0(REG56_PWRSAVE     ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REGFLAG_DELAY     ); LCD_WRITE_A1(0x0A);
  LCD_WRITE_A0(REG14_PNLTYPE     ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG16_HDISP       ); LCD_WRITE_A1(0x3C);
  LCD_WRITE_A0(REG18_HNDP        ); LCD_WRITE_A1(0x2D);
  LCD_WRITE_A0(REG1A_VDISP0      ); LCD_WRITE_A1(0x10);
  LCD_WRITE_A0(REG1C_VDISP1      ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG1E_VNDP        ); LCD_WRITE_A1(0x10);
  LCD_WRITE_A0(REG20_HSW         ); LCD_WRITE_A1(0x29);
  LCD_WRITE_A0(REG22_HPS         ); LCD_WRITE_A1(0x02);
  LCD_WRITE_A0(REG24_VSW         ); LCD_WRITE_A1(0x0A);
  LCD_WRITE_A0(REG26_VPS         ); LCD_WRITE_A1(0x04);
  LCD_WRITE_A0(REG28_PCLKPOL     ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG2A_INMODE      ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG2C_YUVTRANS0   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG2E_YUVTRANS1   ); LCD_WRITE_A1(0x05);
  LCD_WRITE_A0(REG30_UDATAFIX    ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG32_VDATAFIX    ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG34_DISPMODE    ); LCD_WRITE_A1(0x08);
  LCD_WRITE_A0(REG36_EFFECTS     ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG38_WINXSPOS0   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG3A_WINXSPOS1   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG3C_WINYSPOS0   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG3E_WINYSPOS1   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG40_WINXEPOS0   ); LCD_WRITE_A1(0xDF);
  LCD_WRITE_A0(REG42_WINXEPOS1   ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG44_WINYEPOS0   ); LCD_WRITE_A1(0x0F);
  LCD_WRITE_A0(REG46_WINYEPOS1   ); LCD_WRITE_A1(0x01);
  LCD_WRITE_A0(REG4A_MEMRDADDR0  ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG4C_MEMRDADDR1  ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG4E_MEMRDADDR2  ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG50_GAMMAEN     ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG52_GAMMATBLIDX ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG54_GAMMATBLDATA); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG58_NDPCTRL     ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG5A_GPIOCNF0    ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG5C_GPIOSTAT0   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG5E_GPIOPOSINT  ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG60_GPIONEGINT  ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG62_GPIOINTSTAT ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REG64_GPIOPDCTRL0 ); LCD_WRITE_A1(0xFF);
  LCD_WRITE_A0(REGFLAG_ONDELAY   ); LCD_WRITE_A1(0x00);
  LCD_WRITE_A0(REGFLAG_ENDOFTABLE); LCD_WRITE_A1(0x00);
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

