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
#define XSIZE_PHYS 176
#define YSIZE_PHYS 220

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
void LCD_L0_WriteU16_A0(U16 Word);
void LCD_L0_WriteU16_A1(U16 Word);
static void _InitController(void) {
  #ifndef WIN32
  LCD_X_Init();                                           /* Init port lines                    */
  GUI_X_Delay(10);                                        /* Wait 10 ms                         */
  LCD_L0_WriteU16_A0(0x0000); LCD_L0_WriteU16_A1(0x0001); /* Start Oscillation                  */
  GUI_X_Delay(10);                                        /* Wait 10 ms                         */
  LCD_L0_WriteU16_A0(0x0014); LCD_L0_WriteU16_A1(0x381F); /* Power Control 5                    : VCOMG = 1, VD4-0 = 11000, VCM4-0 = 11111 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0102); /* Gate driver interface control      : TE = 1, IDX2-0 = 001 */
  LCD_L0_WriteU16_A0(0x0007); LCD_L0_WriteU16_A1(0x0001); /* Display control 1                  : PT1-0 = 00, VLE2-1 = 0, SPT = 0, GON = 0, DTE = 0, CL = 0, REV = 0, D1-0 = 00 */
  LCD_L0_WriteU16_A0(0x0010); LCD_L0_WriteU16_A1(0x0000); /* Power control 1                    : SAP2-0 = 000, BT2-0 = 000, DC2-0 = 000, AP2-0 = 000, SLP = 0, STB = 0 */
  LCD_L0_WriteU16_A0(0x0011); LCD_L0_WriteU16_A1(0x0000); /* Power control 2                    : CAD = 0, VRN4-0 = 00000, VRP4-0 = 00000 */
  LCD_L0_WriteU16_A0(0x0012); LCD_L0_WriteU16_A1(0x0000); /* Power control 3                    : VC2-0 = 000 */
  LCD_L0_WriteU16_A0(0x0013); LCD_L0_WriteU16_A1(0x0608); /* Power control 4                    : VRL3-0 = 0110, PON = 0, VRH3-0 = 1000 */
  LCD_L0_WriteU16_A0(0x0014); LCD_L0_WriteU16_A1(0x300F); /* Power control 5                    : VCOMG=1, VD4-VD0=10000, VCM4-VCM0=01111 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0100); /* Gate driver interface control      : TE=1, IDX2-IDX0=000 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0101); /* Gate driver interface control      : TE=1, IDX2-IDX0=001 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0102); /* Gate driver interface control      : TE=1, IDX2-IDX0=010 */
  LCD_L0_WriteU16_A0(0x0010); LCD_L0_WriteU16_A1(0x0808); /* Power control 1                    : SAP2-0 = 001, BT2-0 = 000, DC2-0 = 000, AP2-0 = 010, SLP = 0, STB = 0 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0100); /* Gate driver interface control      : TE=1, IDX2-IDX0=000 */
  LCD_L0_WriteU16_A0(0x0013); LCD_L0_WriteU16_A1(0x0619); /* Power control 4                    : VRL3-0 = 0110, PON = 1, VRH3-0 = 1001 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0101); /* Gate driver interface control      : TE=1, IDX2-IDX0=001 */
  LCD_L0_WriteU16_A0(0x0001); LCD_L0_WriteU16_A1(0x001B); /* Driver output control              : EPL = 0, GS = 0, SS = 0, NL4-0 = 11011 */
  LCD_L0_WriteU16_A0(0x0002); LCD_L0_WriteU16_A1(0x0700); /* LCD-driving-waveform               : FLD1-0 = 01, B/C = 1, EOR = 1, NW5-0 = 000000 */
  LCD_L0_WriteU16_A0(0x0003); LCD_L0_WriteU16_A1(0x0030); /* Entry mode                         : BGR = 0, HWM = 0, ID1-0 = 11, AM = 0, LG2-0 = 0 */
  LCD_L0_WriteU16_A0(0x0004); LCD_L0_WriteU16_A1(0x0000); /* Compare register 1                 : CP11-6 = 000000, CP5-0 = 000000 */
  LCD_L0_WriteU16_A0(0x0005); LCD_L0_WriteU16_A1(0x0000); /* Compare register 2                 : CP17-12 = 000000 */
  LCD_L0_WriteU16_A0(0x0008); LCD_L0_WriteU16_A1(0x0808); /* Display control 2                  : FP3-0 = 1000, BP3-0 = 1000 */
  LCD_L0_WriteU16_A0(0x0023); LCD_L0_WriteU16_A1(0x0000); /* RAM data write mask 1              : WM11-6 = 000000, WM5-0 = 000000 */
  LCD_L0_WriteU16_A0(0x0024); LCD_L0_WriteU16_A1(0x0000); /* RAM data write mask 2              : WM17-12 = 000000 */
  LCD_L0_WriteU16_A0(0x000B); LCD_L0_WriteU16_A1(0x0005); /* Frame cycle control                : NO1-0 = 00, SDT1-0 = 00, EQ1-0 = 00, DIV1-0 = 00, RTN3-0 = 0101 */
  LCD_L0_WriteU16_A0(0x000C); LCD_L0_WriteU16_A1(0x0000); /* External display interface control : RM = 0, DM1-0 = 00, RIM1-0 = 00 */
  LCD_L0_WriteU16_A0(0x0040); LCD_L0_WriteU16_A1(0x0000); /* Gate scan start position           : SCN4-0 = 00000 */
  LCD_L0_WriteU16_A0(0x0041); LCD_L0_WriteU16_A1(0x0000); /* Vertical scroll control            : VL7-0 = 00000000 */
  LCD_L0_WriteU16_A0(0x0042); LCD_L0_WriteU16_A1(0xEF00); /* 1st screen driving position        : SE17-10 = 11101111, SS17-10 = 00000000 */
  LCD_L0_WriteU16_A0(0x0043); LCD_L0_WriteU16_A1(0xEF00); /* 2nd screen driving position        : SE27-10 = 11101111, SS27-10 = 00000000 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0106); /* Gate driver interface control      : TE=1, IDX2-0=110 */
  LCD_L0_WriteU16_A0(0x0030); LCD_L0_WriteU16_A1(0x0100); /* Gamma Control 1                    : */
  LCD_L0_WriteU16_A0(0x0031); LCD_L0_WriteU16_A1(0x0707); /* Gamma Control 2                    : */
  LCD_L0_WriteU16_A0(0x0032); LCD_L0_WriteU16_A1(0x0102); /* Gamma Control 3                    : */
  LCD_L0_WriteU16_A0(0x0033); LCD_L0_WriteU16_A1(0x0000); /* Gamma Control 4                    : */
  LCD_L0_WriteU16_A0(0x0034); LCD_L0_WriteU16_A1(0x0506); /* Gamma Control 5                    : */
  LCD_L0_WriteU16_A0(0x0035); LCD_L0_WriteU16_A1(0x0000); /* Gamma Control 6                    : */
  LCD_L0_WriteU16_A0(0x0036); LCD_L0_WriteU16_A1(0x0706); /* Gamma Control 7                    : */
  LCD_L0_WriteU16_A0(0x0037); LCD_L0_WriteU16_A1(0x0000); /* Gamma Control 8                    : */
  LCD_L0_WriteU16_A0(0x003F); LCD_L0_WriteU16_A1(0x0000); /* Gamma Control 9                    : */
  LCD_L0_WriteU16_A0(0x0044); LCD_L0_WriteU16_A1(0xAF00); /* Horizontal RAM address position    : HEA7-0 = 10101111, HSA7-0 = 00000000 */
  LCD_L0_WriteU16_A0(0x0045); LCD_L0_WriteU16_A1(0xDB00); /* Vertical RAM address position      : VEA7-0 = 11011011, VSA7-0 = 00000000 */
  LCD_L0_WriteU16_A0(0x0021); LCD_L0_WriteU16_A1(0x0000); /* RAM address set                    : AD15-0 = 0000000000000000 */
  LCD_L0_WriteU16_A0(0x0007); LCD_L0_WriteU16_A1(0x0021); /* Display control 1                  : PT1-0 = 00, VLE2-1 = 0, SPT = 0, GON = 1, DTE = 0, CL = 0, REV = 0, D1-0 = 01 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0100); /* Gate driver interface control      : TE=1, IDX2-IDX0=000 */
  LCD_L0_WriteU16_A0(0x0007); LCD_L0_WriteU16_A1(0x0023); /* Display control 1                  : PT1-0 = 00, VLE2-1 = 0, SPT = 0, GON = 1, DTE = 0, CL = 0, REV = 0, D1-0 = 11 */
  LCD_L0_WriteU16_A0(0x0007); LCD_L0_WriteU16_A1(0x0033); /* Display control 1                  : PT1-0 = 00, VLE2-1 = 0, SPT = 0, GON = 1, DTE = 1, CL = 0, REV = 0, D1-0 = 11 */
  LCD_L0_WriteU16_A0(0x0012); LCD_L0_WriteU16_A1(0x0000); /* Power control 3                    : VC2-0 = 000 */
  LCD_L0_WriteU16_A0(0x000A); LCD_L0_WriteU16_A1(0x0101); /* Gate driver interface control      : TE=1, IDX2-IDX0=001 */
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

