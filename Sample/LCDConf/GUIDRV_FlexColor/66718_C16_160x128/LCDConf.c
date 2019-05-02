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

              Controller:     Syncoam SEPS525
              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 8 bit interface

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
#define XSIZE_PHYS 160
#define YSIZE_PHYS 128

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_SWAP_XY)

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
#define REG_OSC_CTL                 0x02
#define REG_CLOCK_DIV               0x03
#define REG_REDUCE_CURRENT          0x04
#define REG_DISP_ON_OFF             0x06
#define REG_PRECHARGE_TIME_R        0x08
#define REG_PRECHARGE_TIME_G        0x09
#define REG_PRECHARGE_TIME_B        0x0A
#define REG_PRECHARGE_Current_R     0x0B
#define REG_PRECHARGE_Current_G     0x0C
#define REG_PRECHARGE_Current_B     0x0D
#define REG_DRIVING_CURRENT_R       0x10
#define REG_DRIVING_CURRENT_G       0x11
#define REG_DRIVING_CURRENT_B       0x12
#define REG_DISPLAY_MODE_SET        0x13
#define REG_RGB_IF                  0x14
#define REG_MEMORY_WRITE_MODE       0x16
#define REG_MX1_ADDR                0x17
#define REG_MX2_ADDR                0x18
#define REG_MY1_ADDR                0x19
#define REG_MY2_ADDR                0x1A
#define REG_MEMORY_ACCESS_POINTER_X 0x20
#define REG_MEMORY_ACCESS_POINTER_Y 0x21
#define REG_DDRAM_DATA_ACCESS_PORT  0x22
#define REG_DUTY                    0x28
#define REG_DSL                     0x29
#define REG_D1_DDRAM_FAC            0x2E
#define REG_D1_DDRAM_FAR            0x2F
#define REG_D2_DDRAM_SAC            0x31
#define REG_D2_DDRAM_SAR            0x32
#define REG_SCR1_FX1                0x33
#define REG_SCR1_FX2                0x34
#define REG_SCR1_FY1                0x35
#define REG_SCR1_FY2                0x36
#define REG_SCR2_SX1                0x37
#define REG_SCR2_SX2                0x38
#define REG_SCR2_SY1                0x39
#define REG_SCR2_SY2                0x3A
#define REG_SCREEN_SAVER_CONTEROL   0x3B
#define REG_SCREEN_SAVER_MODE       0x3D
#define REG_SS_SCR1_FU              0x3E
#define REG_SS_SCR1_MXY             0x3F
#define REG_SS_SCR2_FU              0x40
#define REG_SS_SCR2_MXY             0x41
#define REG_SS_SCR2_SX1             0x47
#define REG_SS_SCR2_SX2             0x48
#define REG_SS_SCR2_SY1             0x49
#define REG_SS_SCR2_SY2             0x4A
#define REG_IREF                    0x80

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _WriteCommand
*/
static void _WriteCommand(U16 Reg, U16 Para) {
  LCD_X_8080_8_Write00(Reg);
  LCD_X_8080_8_Write01(Para);
}

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
  LCD_X_8080_8_Init();
  _WriteCommand(REG_REDUCE_CURRENT, 0x03);
  GUI_X_Delay(0x10);
  _WriteCommand(REG_REDUCE_CURRENT, 0x00);          // Reg:04h Action: Normal current and PS OFF
  GUI_X_Delay(0x10);
  _WriteCommand(REG_SCREEN_SAVER_CONTEROL, 0x00);   // Reg:3Bh Action: Screen Saver OFF
  _WriteCommand(REG_OSC_CTL, 0x01);                 // Reg:02h Action: Export1 internal clock/OSC with external resister/Internal OSC ON
  _WriteCommand(REG_CLOCK_DIV, 0x90);               // Reg:03h Action: FR=120Hz DIV=1
  _WriteCommand(REG_IREF, 0x00);                    // Reg:80h Action: PDAC OFF, DDAC OFF/Reference Volt.control with external resister
  _WriteCommand(REG_PRECHARGE_TIME_R, 0x03);        // Reg:08h Action: set color R precharge time
  _WriteCommand(REG_PRECHARGE_TIME_G, 0x05);        // Reg:09h Action: set color G precharge time
  _WriteCommand(REG_PRECHARGE_TIME_B, 0x05);        // Reg:0Ah Action: set color B precharge tiem
  _WriteCommand(REG_PRECHARGE_Current_R, 0x0a);     // Reg:0Bh Action: set color R precharge current
  _WriteCommand(REG_PRECHARGE_Current_G, 0x0a);     // Reg:0Ch Action: set color G precharge current
  _WriteCommand(REG_PRECHARGE_Current_B, 0x0a);     // Reg:0Dh Action: set color B precharge current
  _WriteCommand(REG_DRIVING_CURRENT_R, 0x56);       // Reg:10h Action: set color R dot driving current
  _WriteCommand(REG_DRIVING_CURRENT_G, 0x4D);       // Reg:11h Action: set color G dot driving current
  _WriteCommand(REG_DRIVING_CURRENT_B, 0x46);       // Reg:12h Action: set color B dot driving current
  _WriteCommand(REG_DISPLAY_MODE_SET, 0x00);        // Reg:13h Action: Col D0 to D159/col normal display
  _WriteCommand(REG_RGB_IF, 0x31);                  // Reg:14h Action: MPU mode
  _WriteCommand(REG_MEMORY_WRITE_MODE, 0x66);       // Reg:16h Action: 8bits dual transfer, 65K support
  _WriteCommand(REG_MX1_ADDR, 0x00);                // Reg:17h Action: Memory addr.X start
  _WriteCommand(REG_MX2_ADDR, 0x9f);                // Reg:18h Action: Memory addr.X end
  _WriteCommand(REG_MY1_ADDR, 0x00);                // Reg:18h Action: Memory addr.Y start
  _WriteCommand(REG_MY2_ADDR, 0x7f);                // Reg:1Ah Action: Memory addr.Y end
  _WriteCommand(REG_MEMORY_ACCESS_POINTER_X, 0x00); // Reg:20h Action: Memory X start addr.
  _WriteCommand(REG_MEMORY_ACCESS_POINTER_Y, 0x00); // Reg:21h Action: Memory Y start addr.
  _WriteCommand(REG_DUTY, 0x7f);                    // Reg:28h Action: Display duty ratio
  _WriteCommand(REG_DSL, 0x00);                     // Reg:29h Action: Display start line
  _WriteCommand(REG_D1_DDRAM_FAC, 0x00);            // Reg:2Eh Action: Display First screen X start point
  _WriteCommand(REG_D1_DDRAM_FAR, 0x00);            // Reg:2Fh Action: Display First screen Y start point
  _WriteCommand(REG_D2_DDRAM_SAC, 0x00);            // Reg:31h Action: Display Second screen X start point
  _WriteCommand(REG_D2_DDRAM_SAR, 0x00);            // Reg:32h Action: Display Second screen Y start point
  _WriteCommand(REG_SCR1_FX1, 0x00);                // Reg:33h Action: Display size X start
  _WriteCommand(REG_SCR1_FX2, 0x9f);                // Reg:34h Action: Display size X end
  _WriteCommand(REG_SCR1_FY1, 0x00);                // Reg:35h Action: Display size Y start
  _WriteCommand(REG_SCR1_FY2, 0x7f);                // Reg:36h Action: Display size Y end
  _WriteCommand(REG_DISP_ON_OFF, 0x01);             // Reg:06h Action: Scan signal is high level at precharge period/Dispaly ON
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
  PortAPI.pfRead8_A1   = LCD_X_8080_8_Read01;
  PortAPI.pfReadM8_A1  = LCD_X_8080_8_ReadM01;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66718, GUIDRV_FLEXCOLOR_M16C1B8);
  //
  // Orientation
  //
  Config.Orientation  = DISPLAY_ORIENTATION;
  Config.RegEntryMode = 0x60;
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
