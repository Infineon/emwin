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
  LCD_X_Init();
  LCD_WRITE_A0(0x03); LCD_WRITE_A1(0x01); /* Soft reset                                                */
  _Delay(1);
  LCD_WRITE_A0(0x0A); LCD_WRITE_A1(0x12); /* I/F Mode setting 8bit-I/F(8/8 transfer,16bit color depth) */
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x0B); /* Select main panel                                         */
  LCD_WRITE_A0(0x07); LCD_WRITE_A1(0x01); /* Osillator ON                                              */
  _Delay(30);
  LCD_WRITE_A0(0x91); LCD_WRITE_A1(0x01); /* RAM setting                                               */
  LCD_WRITE_A0(0x05); LCD_WRITE_A1(0x00); /* Panel type select                                         */
  LCD_WRITE_A0(0x06); LCD_WRITE_A1(0x02); /* Display RAM power ON                                      */
  LCD_WRITE_A0(0x8D); LCD_WRITE_A1(0x00); /*                                                           */
  LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x17); /* Adjust the oscillator frequency                           */
  LCD_WRITE_A0(0x20); LCD_WRITE_A1(0x00); /*                                                           */
  LCD_WRITE_A0(0x47); LCD_WRITE_A1(0x05); /* Set the phase delay time of SCK,SCKB,SSPB                 */
  LCD_WRITE_A0(0x66); LCD_WRITE_A1(0x50); /* Vcom voltage adjustment                                   */
  LCD_WRITE_A0(0x64); LCD_WRITE_A1(0x00); /* Analog setting time of analog outputs                     */
  LCD_WRITE_A0(0x59); LCD_WRITE_A1(0x01); /* Select output level of the EXT1 output                    */
  LCD_WRITE_A0(0x40); LCD_WRITE_A1(0x19); /* Set rising timing of the GOE output                       */
  LCD_WRITE_A0(0x41); LCD_WRITE_A1(0x10); /* Set falling timing of the GOE output                      */
  LCD_WRITE_A0(0x42); LCD_WRITE_A1(0x14); /* Set inversion time of the COM output                      */
  LCD_WRITE_A0(0x45); LCD_WRITE_A1(0x14); /* Set rising time of the GCK output                         */
  LCD_WRITE_A0(0x46); LCD_WRITE_A1(0x18); /* Set falling time of the GCK output                        */
  LCD_WRITE_A0(0x50); LCD_WRITE_A1(0x03); /* Set the vertical blank period                             */
  LCD_WRITE_A0(0x51); LCD_WRITE_A1(0x09); /* Set the horizonal blank period                            */
  LCD_WRITE_A0(0x60); LCD_WRITE_A1(0x30); /* Setup upper reference voltage(VPH)of the positive DAC     */
  LCD_WRITE_A0(0x61); LCD_WRITE_A1(0x1C); /* Setup upper reference voltage(VNH)of the negative DAC     */
  LCD_WRITE_A0(0x62); LCD_WRITE_A1(0x1C); /* Setup lower reference voltage(VPL)of the positive DAC     */
  LCD_WRITE_A0(0x63); LCD_WRITE_A1(0x0F); /* Setup lower reference voltage(VNL)of the negative DAC     */
  LCD_WRITE_A0(0x6A); LCD_WRITE_A1(0x50); /* Control the pumping frequency                             */
  LCD_WRITE_A0(0x58); LCD_WRITE_A1(0x60); /* PVOUT setting                                             */
  LCD_WRITE_A0(0x02); LCD_WRITE_A1(0x03); /* Specify the gate /source scan direction                   */
  LCD_WRITE_A0(0x09); LCD_WRITE_A1(0x01); /* VAL                                                       */
  LCD_WRITE_A0(0x75); LCD_WRITE_A1(0x01); /* Assingn the 00h-3Fh of an EEPROM to a gamma tabe          */
  LCD_WRITE_A0(0x6C); LCD_WRITE_A1(0xAD); /* DC/DC setting                                             */
  LCD_WRITE_A0(0x68); LCD_WRITE_A1(0x41); /* VDC0 ON                                                   */
  _Delay(10);
  LCD_WRITE_A0(0x68); LCD_WRITE_A1(0x47); /* VDC,VDC2 ON                                               */
  _Delay(10);
  LCD_WRITE_A0(0x69); LCD_WRITE_A1(0x01); /* VDC3 ON                                                   */
  _Delay(10);
  LCD_WRITE_A0(0x69); LCD_WRITE_A1(0x05); /* VDC4 ON                                                   */
  _Delay(10);
  LCD_WRITE_A0(0x69); LCD_WRITE_A1(0x15); /* VDC5 ON                                                   */
  _Delay(10);
  LCD_WRITE_A0(0x15); LCD_WRITE_A1(0x00); /* RAM X-Y position portrait                                 */
  LCD_WRITE_A0(0x16); LCD_WRITE_A1(0x00); /* X RAM Start address                                       */
  LCD_WRITE_A0(0x17); LCD_WRITE_A1(0x00); /* Y RAM Start address                                       */
  LCD_WRITE_A0(0x18); LCD_WRITE_A1(0x00); /* Y RAM Start address                                       */
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x0A); /* COM operation start                                       */
  LCD_WRITE_A0(0x04); LCD_WRITE_A1(0x10); /* Panel control signal output                               */
  _Delay(10);
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x08); /* Black mask release                                        */
  LCD_WRITE_A0(0x75); LCD_WRITE_A1(0x01); /* Assingn the 00h-3Fh of an EEPROM to a gamma tabe          */
  LCD_WRITE_A0(0x74); LCD_WRITE_A1(0x41); /* Start read address of the EEPROM                          */
  LCD_WRITE_A0(0x71); LCD_WRITE_A1(0x06); /* EEPROM Read                                               */
  _Delay(10);
  LCD_WRITE_A0(0x74); LCD_WRITE_A1(0x00); /* Start read address of the EEPROM                          */
  LCD_WRITE_A0(0x71); LCD_WRITE_A1(0x06); /* EEPROM Read                                               */
  _Delay(10);
  LCD_WRITE_A0(0x19); LCD_WRITE_A1(0x01); /* Window access mode                                        */
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
