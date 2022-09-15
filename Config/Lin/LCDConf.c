/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2021  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.26 - Graphical user interface for embedded applications **
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
License model:            Cypress Services and License Agreement, signed June 9th/10th, 2009
                          and Amendment Number One, signed June 28th, 2019 and July 2nd, 2019
                          and Amendment Number Two, signed September 13th, 2021 and September 18th, 2021
                          and Amendment Number Three, signed May 2nd, 2022 and May 5th, 2022
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

#include "GUIDRV_Lin.h"

#if defined(__cplusplus)
extern "C"
{
#endif

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
#define COLOR_CONVERSION GUICC_8888

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_LIN_32

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VRAM_ADDR
  #define VRAM_ADDR 0
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
*   Should initialize the display controller
*/
static void _InitController(void)
{
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetVRAMAddr
*
* Purpose:
*   Should set the frame buffer base address
*/
static void _SetVRAMAddr(void * pVRAM)
{
  GUI_USE_PARA(pVRAM);
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetOrg
*
* Purpose:
*   Should set the origin of the display typically by modifying the
*   frame buffer base address register
*/
static void _SetOrg(int xPos, int yPos)
{
  GUI_USE_PARA(xPos);
  GUI_USE_PARA(yPos);
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetLUTEntry
*
* Purpose:
*   Should set the desired LUT entry
*/
static void _SetLUTEntry(LCD_COLOR Color, U8 Pos)
{
  GUI_USE_PARA(Color);
  GUI_USE_PARA(Pos);
  /* TBD by customer */
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
void LCD_X_Config(void)
{
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
  LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
  #endif
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
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData)
{
  int r;

  GUI_USE_PARA(LayerIndex);

  switch (Cmd)
  {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER:
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    r = 0;
    break;

  case LCD_X_SETVRAMADDR:
    //
    // Required for setting the address of the video RAM for drivers
    // with memory mapped video RAM which is passed in the 'pVRAM' element of p
    //
    _SetVRAMAddr(((LCD_X_SETVRAMADDR_INFO *)pData)->pVRAM);
    r = 0;
    break;

  case LCD_X_SETORG:
    //
    // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
    //
    _SetOrg(((LCD_X_SETORG_INFO *)pData)->xPos, ((LCD_X_SETORG_INFO *)pData)->yPos);
    r = 0;
    break;

  case LCD_X_SETLUTENTRY:
    //
    // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
    //
    _SetLUTEntry(((LCD_X_SETLUTENTRY_INFO *)pData)->Color, ((LCD_X_SETLUTENTRY_INFO *)pData)->Pos);
    r = 0;
    break;

  case LCD_X_ON:
    //
    // Required if the display controller should support switching on and off
    //
    r = 0;
    break;

  case LCD_X_OFF:
    //
    // Required if the display controller should support switching on and off
    //
    // ...
    r = 0;
    break;

  default:
    r = -1;
    break;
  }

  return r;
}

#if defined(__cplusplus)
}
#endif


/*************************** End of file ****************************/
