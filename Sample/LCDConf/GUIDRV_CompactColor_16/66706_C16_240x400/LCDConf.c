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
#define YSIZE_PHYS 400

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
static void _InitController(void) {
  #ifndef WIN32
  _Delay(10);
  LCD_X_Init();
  _Delay(10);
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x00); /* Internal EEPROM */
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x02); /* Internal EEPROM */
  _Delay(10);
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x00); /* Internal EEPROM */
  LCD_WRITE_A0(0x68); LCD_WRITE_A1(0x41); /* COM-pp */
  LCD_WRITE_A0(0x69); LCD_WRITE_A1(0x7D); /* COM-center */
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x02); /* 8bit 8/8 transfer */
  LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x00); /* Normally black */
  LCD_WRITE_A0(0x10); LCD_WRITE_A1(0xF0); /* Panel X-size=240 */
  LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x90); /* Panel Y-size=400 */
  LCD_WRITE_A0(0x12); LCD_WRITE_A1(0x01); /* Panel Y-size=400 */
  LCD_WRITE_A0(0x1E); LCD_WRITE_A1(0x50); /* Number of vertical line=400 */
  LCD_WRITE_A0(0x1D); LCD_WRITE_A1(0x07); /* RAM write direction :landscape */
  LCD_WRITE_A0(0x1A); LCD_WRITE_A1(0xEF); /* RAM pointer X */
  LCD_WRITE_A0(0x1B); LCD_WRITE_A1(0x8F); /* RAM pointer Y */
  LCD_WRITE_A0(0x1C); LCD_WRITE_A1(0x01); /* RAM pointer Y */
  LCD_WRITE_A0(0x30); LCD_WRITE_A1(0x81); /* Select the display-RAM data */
  LCD_WRITE_A0(0x33); LCD_WRITE_A1(0x02); /* Non-display data color */
  LCD_WRITE_A0(0x42); LCD_WRITE_A1(0x70); /* Vertical front poach=112h */
  LCD_WRITE_A0(0x43); LCD_WRITE_A1(0x01); /* Vertical back poach=1h */
  LCD_WRITE_A0(0x44); LCD_WRITE_A1(0x3F); /* H scan interval=96clock */
  LCD_WRITE_A0(0x45); LCD_WRITE_A1(0x14); /* GSP start position=10clock */
  LCD_WRITE_A0(0x46); LCD_WRITE_A1(0x0F); /* GCK start position=15clock */
  LCD_WRITE_A0(0x48); LCD_WRITE_A1(0x03); /* COM inversion position=3clock */
  LCD_WRITE_A0(0x4A); LCD_WRITE_A1(0x01); /* Signal setting */
  LCD_WRITE_A0(0x4B); LCD_WRITE_A1(0xA8); /* SSD setting */
  LCD_WRITE_A0(0x4C); LCD_WRITE_A1(0x12); /* ASW start position=18clock */
  LCD_WRITE_A0(0x5A); LCD_WRITE_A1(0x00); /* Battery pull-out detection off */
  LCD_WRITE_A0(0x62); LCD_WRITE_A1(0x52); /* ASW width10, interval2clock */
  LCD_WRITE_A0(0x65); LCD_WRITE_A1(0x02); /* AMP bias current setting */
  LCD_WRITE_A0(0x66); LCD_WRITE_A1(0x06); /* VGM5.2V */
  LCD_WRITE_A0(0x6A); LCD_WRITE_A1(0x02); /* VCOM output */
  LCD_WRITE_A0(0x81); LCD_WRITE_A1(0x44); /* VR,VS boost clock setting */
  LCD_WRITE_A0(0x82); LCD_WRITE_A1(0x2D); /* DCK,DCKB timing setting */
  LCD_WRITE_A0(0x83); LCD_WRITE_A1(0x25); /* DCDC Dual, AVR,5.2V,DCDC drivability=min */
  LCD_WRITE_A0(0x84); LCD_WRITE_A1(0x17); /* VR setting */
  LCD_WRITE_A0(0x85); LCD_WRITE_A1(0x27); /* DCDC Dual, AVS5.4V,DCDC drivability=min */
  LCD_WRITE_A0(0x86); LCD_WRITE_A1(0x17); /* VS setting */
  LCD_WRITE_A0(0x90); LCD_WRITE_A1(0x25); /* Auto ON timing setting */
  LCD_WRITE_A0(0x91); LCD_WRITE_A1(0x05); /* Auto ON/OFF setting(1V) */
  LCD_WRITE_A0(0x92); LCD_WRITE_A1(0x15); /* Auto OFF timing setting */
  LCD_WRITE_A0(0x31); LCD_WRITE_A1(0x01); /* VAL */
  LCD_WRITE_A0(0x19); LCD_WRITE_A1(0x01); /* Window access mode */
  LCD_WRITE_A0(0x3E); LCD_WRITE_A1(0x01); /* Auto ON sequence */
  _Delay(120);
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
