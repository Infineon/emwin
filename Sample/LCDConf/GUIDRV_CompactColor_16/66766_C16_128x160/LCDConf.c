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
#define XSIZE_PHYS 128
#define YSIZE_PHYS 160

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

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
  LCD_X_Init();                                                                                                                       
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x00); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* start oscillation                                                                 */ 
  _Delay(100);
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x13); /* CMS=0 COM1-COM176 SGS=0 SEG1-SEG396, driver output control 1/160 DUTY NL4-0=10011 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RST=0 B/C=0 EOR=0, B pattern waveform NW5-0=000000                                */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x04); LCD_WRITE_A1(0x06); LCD_WRITE_A1(0x64); /* VR2-0=110, contrast control ct6-ct0:1111000                                       */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x65); LCD_WRITE_A1(0x78); /* BS3-0=0110 BT3-BT0=0101, 1/10 bias dc2-0=111 ap1-0=10 SLP=0 STB=0                 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0C); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x05); /* vc2-0=101 0.73VCC                                                                 */ 
  _Delay(100);
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x4D); LCD_WRITE_A1(0x78); /* BS3-0=0100 BT3-BT0=1101, 1/10 bias dc2-0=111 ap1-0=10 SLP=0 STB=0                 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x30); /* spr=0 65K,hwm=0,id1-0=11,am=0,lg2-0=000                                           */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* CP7-0=00H                                                                         */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x01); /* no scrol, no screen-division,not reversal,display off                             */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x0B); LCD_WRITE_A1(0x01); LCD_WRITE_A1(0x00); /* frame cycle control                                                               */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* VERTICAL SCROLL CONTROLL                                                          */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x14); LCD_WRITE_A1(0xA0); LCD_WRITE_A1(0x00); /* se17-10=00h ss17-10=160h(com1-160)                                                */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x15); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* se27-20=00h ss27-20=00h(com1-160)                                                 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x16); LCD_WRITE_A1(0x7F); LCD_WRITE_A1(0x00); /* hea7-0=7fh(end address),hsa7-0=00h(start address)                                 */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x17); LCD_WRITE_A1(0x9F); LCD_WRITE_A1(0x00); /* vea7-0=9fh,vsa7-0=00h                                                             */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x20); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x00); /* RAM MASK                                                                          */ 
  LCD_WRITE_A0(0x00); LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x00); LCD_WRITE_A1(0x03); /* no scrol, no screen-division,not reversal,display ON                              */
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

