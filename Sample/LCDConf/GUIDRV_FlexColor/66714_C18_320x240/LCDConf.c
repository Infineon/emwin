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
Purpose     : Sample display controller configuration

              Controller:     Solomon SSD2119
              Display driver: GUIDRV_FlexColor
              Operation mode: 18bpp, 9 bit interface

---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
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
#define COLOR_CONVERSION GUICC_M666_9

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Buffers / VScreens
//
#define NUM_BUFFERS   1
#define NUM_VSCREENS  1

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
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION 0
#endif

/*********************************************************************
*
*       Hardware interface
*
**********************************************************************
*/
#define BC_SSD2119_BASE      0x88000000 /**< TFT Controller base address */
#define BC_REGISTER_BASE     0x8c000000 /**< Board Controller registers base address */

#define BC_BUS_CFG_EBI                       (1) /**< EBI drives bus */
#define BC_BUS_CFG           ((volatile U16 *)(BC_REGISTER_BASE + sizeof(U16) * 0x0a)) /**< BUS config */

#define DMD_SSD2119_DEVICE_CODE_READ                        0x00
#define DMD_SSD2119_OSCILLATION_START                       0x00
#define DMD_SSD2119_OSCILLATION_START_OSCEN                 0x0001

#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL                   0x01
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL                0x4000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_REV               0x2000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_GD                0x1000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_BGR               0x0800
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_SM                0x0400
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB                0x0200
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_MUX_SHIFT         0

#define DMD_SSD2119_LCD_AC_CONTROL                          0x02
#define DMD_SSD2119_LCD_AC_CONTROL_FLC                      0x1000
#define DMD_SSD2119_LCD_AC_CONTROL_ENWS                     0x0800
#define DMD_SSD2119_LCD_AC_CONTROL_BC                       0x0400
#define DMD_SSD2119_LCD_AC_CONTROL_EOR                      0x0200
#define DMD_SSD2119_LCD_AC_CONTROL_WSMD                     0x0100
#define DMD_SSD2119_LCD_AC_CONTROL_NW_SHIFT                 0

#define DMD_SSD2119_POWER_CONTROL_1                         0x03
#define DMD_SSD2119_POWER_CONTROL_1_DCT_SHIFT               12
#define DMD_SSD2119_POWER_CONTROL_1_BT_SHIFT                9
#define DMD_SSD2119_POWER_CONTROL_1_DC_SHIFT                4
#define DMD_SSD2119_POWER_CONTROL_1_AP_SHIFT                1

#define DMD_SSD2119_DISPLAY_CONTROL                         0x07
#define DMD_SSD2119_DISPLAY_CONTROL_PT1                     0x1000
#define DMD_SSD2119_DISPLAY_CONTROL_PT0                     0x0800
#define DMD_SSD2119_DISPLAY_CONTROL_VLE2                    0x0400
#define DMD_SSD2119_DISPLAY_CONTROL_VLE1                    0x0200
#define DMD_SSD2119_DISPLAY_CONTROL_SPT                     0x0100
#define DMD_SSD2119_DISPLAY_CONTROL_GON                     0x0020
#define DMD_SSD2119_DISPLAY_CONTROL_DTE                     0x0010
#define DMD_SSD2119_DISPLAY_CONTROL_CM                      0x0008
#define DMD_SSD2119_DISPLAY_CONTROL_D1                      0x0002
#define DMD_SSD2119_DISPLAY_CONTROL_D0                      0x0001

#define DMD_SSD2119_FRAME_CYCLE_CONTROL                     0x0B
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_NO_SHIFT            14
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SDT_SHIFT           12
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_EQ_SHIFT            8
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_SHIFT           6
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_1               0x0
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_2               0x1
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_4               0x2
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_8               0x3
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SDIV                0x0020
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SRTN                0x0010
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_RTN_SHIFT           0

#define DMD_SSD2119_POWER_CONTROL_2                         0x0C
#define DMD_SSD2119_POWER_CONTROL_2_VRC_SHIFT               0

#define DMD_SSD2119_POWER_CONTROL_3                         0x0D
#define DMD_SSD2119_POWER_CONTROL_3_VRH_SHIFT               0

#define DMD_SSD2119_POWER_CONTROL_4                         0x0E
#define DMD_SSD2119_POWER_CONTROL_4_VCOMG                   0x2000
#define DMD_SSD2119_POWER_CONTROL_4_VDV_SHIFT               8

#define DMD_SSD2119_GATE_SCAN_START_POSITION                0x0F

#define DMD_SSD2119_SLEEP_MODE_1                            0x10
#define DMD_SSD2119_SLEEP_MODE_1_SLP                        0x0001

#define DMD_SSD2119_ENTRY_MODE                              0x11
#define DMD_SSD2119_ENTRY_MODE_VSMODE                       0x8000
#define DMD_SSD2119_ENTRY_MODE_DFM_SHIFT                    13
#define DMD_SSD2119_ENTRY_MODE_DFM_65K                      0x3
#define DMD_SSD2119_ENTRY_MODE_DFM_262K                     0x2
#define DMD_SSD2119_ENTRY_MODE_DENMODE                      0x0800
#define DMD_SSD2119_ENTRY_MODE_WMODE                        0x0400
#define DMD_SSD2119_ENTRY_MODE_NOSYNC                       0x0200
#define DMD_SSD2119_ENTRY_MODE_DMODE                        0x0100
#define DMD_SSD2119_ENTRY_MODE_TY_SHIFT                     6
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_A                    0x0
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_B                    0x1
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_C                    0x2
#define DMD_SSD2119_ENTRY_MODE_ID1                          0x0020
#define DMD_SSD2119_ENTRY_MODE_ID0                          0x0010
#define DMD_SSD2119_ENTRY_MODE_AM                           0x0008

#define DMD_SSD2119_SLEEP_MODE_2                            0x12
#define DMD_SSD2119_SLEEP_MODE_2_DSLP                       0x2000
#define DMD_SSD2119_SLEEP_MODE_2_HVCI                       0x4000

#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL               0x15
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVDOT        0x0008
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVDEN        0x0004
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVHS         0x0002
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVVS         0x0001

#define DMD_SSD2119_POWER_CONTROL_5                         0x1E
#define DMD_SSD2119_POWER_CONTROL_5_NOTP                    0x0080
#define DMD_SSD2119_POWER_CONTROL_5_VCM_SHIFT               0

#define DMD_SSD2119_ACCESS_DATA                             0x22

#define DMD_SSD2119_FRAME_FREQUENCY_CONTROL                 0x25
#define DMD_SSD2119_FRAME_FREQUENCY_CONTROL_OSC_SHIFT       12

#define DMD_SSD2119_VCOM_OTP_1                              0x28
#define DMD_SSD2119_VCOM_OTP_2                              0x29

#define DMD_SSD2119_GAMMA_1                                 0x30
#define DMD_SSD2119_GAMMA_1_PKP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_1_PKP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_2                                 0x31
#define DMD_SSD2119_GAMMA_2_PKP3_SHIFT                      8
#define DMD_SSD2119_GAMMA_2_PKP2_SHIFT                      0

#define DMD_SSD2119_GAMMA_3                                 0x32
#define DMD_SSD2119_GAMMA_3_PKP5_SHIFT                      8
#define DMD_SSD2119_GAMMA_3_PKP4_SHIFT                      0

#define DMD_SSD2119_GAMMA_4                                 0x33
#define DMD_SSD2119_GAMMA_4_PRP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_4_PRP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_5                                 0x34
#define DMD_SSD2119_GAMMA_5_PKN1_SHIFT                      8
#define DMD_SSD2119_GAMMA_5_PKN0_SHIFT                      0

#define DMD_SSD2119_GAMMA_6                                 0x35
#define DMD_SSD2119_GAMMA_6_PKN3_SHIFT                      8
#define DMD_SSD2119_GAMMA_6_PKN2_SHIFT                      0

#define DMD_SSD2119_GAMMA_7                                 0x36
#define DMD_SSD2119_GAMMA_7_PKN5_SHIFT                      8
#define DMD_SSD2119_GAMMA_7_PKN4_SHIFT                      0

#define DMD_SSD2119_GAMMA_8                                 0x37
#define DMD_SSD2119_GAMMA_8_PRN1_SHIFT                      8
#define DMD_SSD2119_GAMMA_8_PRN0_SHIFT                      0

#define DMD_SSD2119_GAMMA_9                                 0x3A
#define DMD_SSD2119_GAMMA_9_VRP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_9_VRP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_10                                0x3B
#define DMD_SSD2119_GAMMA_10_VRN1_SHIFT                     8
#define DMD_SSD2119_GAMMA_10_VRN0_SHIFT                     0

#define DMD_SSD2119_VERTICAL_SCROLL_CONTROL_1               0x41
#define DMD_SSD2119_VERTICAL_SCROLL_CONTROL_2               0x42

#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS                0x44
#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS_END_SHIFT      8
#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS_START_SHIFT    0

#define DMD_SSD2119_HORIZONTAL_RAM_ADDRESS_START_POS        0x45
#define DMD_SSD2119_HORIZONTAL_RAM_ADDRESS_END_POS          0x46

#define DMD_SSD2119_FIRST_WINDOW_START                      0x48
#define DMD_SSD2119_FIRST_WINDOW_END                        0x49

#define DMD_SSD2119_SECOND_WINDOW_START                     0x4A
#define DMD_SSD2119_SECOND_WINDOW_END                       0x4B

#define DMD_SSD2119_SET_X_ADDRESS_COUNTER                   0x4E
#define DMD_SSD2119_SET_Y_ADDRESS_COUNTER                   0x4F

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static volatile U16 * pRegCmd;
static volatile U16 * pRegData;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetReg
*/
static void _SetReg(U16 Reg) {
  *pRegCmd = Reg << 1;
}

/*********************************************************************
*
*       _WriteData
*/
static void _WriteData(U16 Data) {
  *pRegData = Data << 1;
}

/*********************************************************************
*
*       _WriteDataM
*/
static void _WriteDataM(U16 * pData, int NumItems) {
  do {
    *pRegData = *pData++;
  } while (--NumItems);
}

/*********************************************************************
*
*       _ReadDataM
*/
static void _ReadDataM(U16 * pData, int NumItems) {
  do {
    *pData++ = *pRegData;
  } while (--NumItems);
}

/*********************************************************************
*
*       _ReadData
*/
static U16 _ReadData(void) {
  return *pRegData;
}

/*********************************************************************
*
*       _InitController
*/
static void _InitController(void) {
  U16 Data;

  //
  // Interface
  //
  pRegCmd  = (U16 *)BC_SSD2119_BASE;
  pRegData = (U16 *)BC_SSD2119_BASE + 1;
  *(BC_BUS_CFG) = BC_BUS_CFG_EBI;
  //
  // Initialization sequence, see UMSH-8252MD-T page 13
  //
  _SetReg(DMD_SSD2119_VCOM_OTP_1);
  _WriteData(0x0006);
  //
  // Start oscillation
  //
  Data = DMD_SSD2119_OSCILLATION_START_OSCEN;
  _SetReg(DMD_SSD2119_OSCILLATION_START);
  _WriteData(Data);
  //
  // Exit sleep mode
  //
  Data = 0;
  _SetReg(DMD_SSD2119_SLEEP_MODE_1);
  _WriteData(Data);
  //
  // Display control
  //
  Data  = DMD_SSD2119_DISPLAY_CONTROL_DTE;
  Data |= DMD_SSD2119_DISPLAY_CONTROL_GON;
  Data |= DMD_SSD2119_DISPLAY_CONTROL_D1;
  Data |= DMD_SSD2119_DISPLAY_CONTROL_D0;
  _SetReg(DMD_SSD2119_DISPLAY_CONTROL);
  _WriteData(Data);
  //
  // Entry mode
  //
  Data  = DMD_SSD2119_ENTRY_MODE_DFM_262K << DMD_SSD2119_ENTRY_MODE_DFM_SHIFT;
  Data |= DMD_SSD2119_ENTRY_MODE_DENMODE;
  Data |= DMD_SSD2119_ENTRY_MODE_WMODE;
  Data |= DMD_SSD2119_ENTRY_MODE_NOSYNC;
  Data |= DMD_SSD2119_ENTRY_MODE_TY_TYPE_B << DMD_SSD2119_ENTRY_MODE_TY_SHIFT;
  Data |= DMD_SSD2119_ENTRY_MODE_ID1;
  Data |= DMD_SSD2119_ENTRY_MODE_ID0;
  _SetReg(DMD_SSD2119_ENTRY_MODE);
  _WriteData(Data);
  //
  // LCD AC control
  //
  Data  = DMD_SSD2119_LCD_AC_CONTROL_BC;
  Data |= DMD_SSD2119_LCD_AC_CONTROL_EOR;
  _SetReg(DMD_SSD2119_LCD_AC_CONTROL);
  _WriteData(Data);
  //
  // Power control
  //
  Data  = 0x06 << DMD_SSD2119_POWER_CONTROL_1_DCT_SHIFT;
  Data |= 0x05 << DMD_SSD2119_POWER_CONTROL_1_BT_SHIFT;
  Data |= 0x03 << DMD_SSD2119_POWER_CONTROL_1_DC_SHIFT;
  Data |= 0x04 << DMD_SSD2119_POWER_CONTROL_1_AP_SHIFT;
  _SetReg(DMD_SSD2119_POWER_CONTROL_1);
  _WriteData(Data);
  //
  // Driver output control
  //
  Data                  = DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL;
  Data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_REV;
  Data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_GD;
  Data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB;
  Data                 |= (YSIZE_PHYS - 1) << DMD_SSD2119_DRIVER_OUTPUT_CONTROL_MUX_SHIFT;
  _SetReg(DMD_SSD2119_DRIVER_OUTPUT_CONTROL);
  _WriteData(Data);
  //
  // Power Control
  //
  Data = 0x05 << DMD_SSD2119_POWER_CONTROL_2_VRC_SHIFT;
  _SetReg(DMD_SSD2119_POWER_CONTROL_2);
  _WriteData(Data);
  Data = 0x0D << DMD_SSD2119_POWER_CONTROL_3_VRH_SHIFT;
  _SetReg(DMD_SSD2119_POWER_CONTROL_3);
  _WriteData(Data);
  Data  = DMD_SSD2119_POWER_CONTROL_4_VCOMG;
  Data |= 0x0D << DMD_SSD2119_POWER_CONTROL_4_VDV_SHIFT;
  _SetReg(DMD_SSD2119_POWER_CONTROL_4);
  _WriteData(Data);
  Data  = DMD_SSD2119_POWER_CONTROL_5_NOTP;
  Data |= 0x3E << DMD_SSD2119_POWER_CONTROL_5_VCM_SHIFT;
  _SetReg(DMD_SSD2119_POWER_CONTROL_5);
  _WriteData(Data);
  Data = 0x0058;
  _SetReg(DMD_SSD2119_GENERIC_INTERFACE_CONTROL);
  _WriteData(Data);
  //
  // Gamma settings
  //
  Data  = 0x00 << DMD_SSD2119_GAMMA_1_PKP1_SHIFT;
  Data |= 0x00 << DMD_SSD2119_GAMMA_1_PKP0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_1);
  _WriteData(Data);
  Data  = 0x01 << DMD_SSD2119_GAMMA_2_PKP3_SHIFT;
  Data |= 0x01 << DMD_SSD2119_GAMMA_2_PKP2_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_2);
  _WriteData(Data);
  Data  = 0x01 << DMD_SSD2119_GAMMA_3_PKP5_SHIFT;
  Data |= 0x00 << DMD_SSD2119_GAMMA_3_PKP4_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_3);
  _WriteData(Data);
  Data  = 0x03 << DMD_SSD2119_GAMMA_4_PRP1_SHIFT;
  Data |= 0x05 << DMD_SSD2119_GAMMA_4_PRP0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_4);
  _WriteData(Data);
  Data  = 0x07 << DMD_SSD2119_GAMMA_5_PKN1_SHIFT;
  Data |= 0x07 << DMD_SSD2119_GAMMA_5_PKN0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_5);
  _WriteData(Data);
  Data  = 0x03 << DMD_SSD2119_GAMMA_6_PKN3_SHIFT;
  Data |= 0x05 << DMD_SSD2119_GAMMA_6_PKN2_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_6);
  _WriteData(Data);
  Data  = 0x07 << DMD_SSD2119_GAMMA_7_PKN5_SHIFT;
  Data |= 0x07 << DMD_SSD2119_GAMMA_7_PKN4_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_7);
  _WriteData(Data);
  Data  = 0x02 << DMD_SSD2119_GAMMA_8_PRN1_SHIFT;
  Data |= 0x01 << DMD_SSD2119_GAMMA_8_PRN0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_8);
  _WriteData(Data);
  Data  = 0x12 << DMD_SSD2119_GAMMA_9_VRP1_SHIFT;
  Data |= 0x00 << DMD_SSD2119_GAMMA_9_VRP0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_9);
  _WriteData(Data);
  Data  = 0x09 << DMD_SSD2119_GAMMA_10_VRN1_SHIFT;
  Data |= 0x00 << DMD_SSD2119_GAMMA_10_VRN0_SHIFT;
  _SetReg(DMD_SSD2119_GAMMA_10);
  _WriteData(Data);
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
  
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Common display driver configuration
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
  //
  // Configuration of GUIDRV_FLEX_COLOR
  //
  if (DISPLAY_DRIVER == GUIDRV_FLEXCOLOR) {
    CONFIG_FLEXCOLOR Config = {0};
    GUI_PORT_API PortAPI = {0}; 

    GUIDRV_FlexColor_Config(pDevice, &Config);
    //
    // Orientation
    //
    Config.Orientation   = DISPLAY_ORIENTATION;
    Config.RegEntryMode  = DMD_SSD2119_ENTRY_MODE_DFM_262K << DMD_SSD2119_ENTRY_MODE_DFM_SHIFT;
    Config.RegEntryMode |= DMD_SSD2119_ENTRY_MODE_DENMODE;
    Config.RegEntryMode |= DMD_SSD2119_ENTRY_MODE_WMODE;
    Config.RegEntryMode |= DMD_SSD2119_ENTRY_MODE_NOSYNC;
    Config.RegEntryMode |= DMD_SSD2119_ENTRY_MODE_TY_TYPE_B << DMD_SSD2119_ENTRY_MODE_TY_SHIFT;
    GUIDRV_FlexColor_Config(pDevice, &Config);
    //
    // Set controller and operation mode
    //
    PortAPI.pfWrite16_A0  = _SetReg;
    PortAPI.pfWrite16_A1  = _WriteData;
    PortAPI.pfWriteM16_A1 = _WriteDataM;
    PortAPI.pfRead16_A1   = _ReadData;
    PortAPI.pfReadM16_A1  = _ReadDataM;
    GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66714, GUIDRV_FLEXCOLOR_M18C0B9);
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
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - OK
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
