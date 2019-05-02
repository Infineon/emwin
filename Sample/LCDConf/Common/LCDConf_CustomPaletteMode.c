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
Purpose     : Sample file for custom palette mode
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

#include "GUIDRV_Lin.h"

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
#define COLOR_CONVERSION GUICC_0

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_LIN_8

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
*       Static data
*
**********************************************************************
*/
static const LCD_COLOR _aColors_256[] = {
  0x000000, 0x240000, 0x480000, 0x6D0000, 0x910000, 0xB60000, 0xDA0000, 0xFF0000, 
  0x005500, 0x245500, 0x485500, 0x6D5500, 0x915500, 0xB65500, 0xDA5500, 0xFF5500, 
  0x00AA00, 0x24AA00, 0x48AA00, 0x6DAA00, 0x91AA00, 0xB6AA00, 0xDAAA00, 0xFFAA00, 
  0x00FF00, 0x24FF00, 0x48FF00, 0x6DFF00, 0x91FF00, 0xB6FF00, 0xDAFF00, 0xFFFF00, 
  0x000024, 0x240024, 0x480024, 0x6D0024, 0x910024, 0xB60024, 0xDA0024, 0xFF0024, 
  0x005524, 0x245524, 0x485524, 0x6D5524, 0x915524, 0xB65524, 0xDA5524, 0xFF5524, 
  0x00AA24, 0x24AA24, 0x48AA24, 0x6DAA24, 0x91AA24, 0xB6AA24, 0xDAAA24, 0xFFAA24, 
  0x00FF24, 0x24FF24, 0x48FF24, 0x6DFF24, 0x91FF24, 0xB6FF24, 0xDAFF24, 0xFFFF24, 
  0x000048, 0x240048, 0x480048, 0x6D0048, 0x910048, 0xB60048, 0xDA0048, 0xFF0048, 
  0x005548, 0x245548, 0x485548, 0x6D5548, 0x915548, 0xB65548, 0xDA5548, 0xFF5548, 
  0x00AA48, 0x24AA48, 0x48AA48, 0x6DAA48, 0x91AA48, 0xB6AA48, 0xDAAA48, 0xFFAA48, 
  0x00FF48, 0x24FF48, 0x48FF48, 0x6DFF48, 0x91FF48, 0xB6FF48, 0xDAFF48, 0xFFFF48, 
  0x00006D, 0x24006D, 0x48006D, 0x6D006D, 0x91006D, 0xB6006D, 0xDA006D, 0xFF006D, 
  0x00556D, 0x24556D, 0x48556D, 0x6D556D, 0x91556D, 0xB6556D, 0xDA556D, 0xFF556D, 
  0x00AA6D, 0x24AA6D, 0x48AA6D, 0x6DAA6D, 0x91AA6D, 0xB6AA6D, 0xDAAA6D, 0xFFAA6D, 
  0x00FF6D, 0x24FF6D, 0x48FF6D, 0x6DFF6D, 0x91FF6D, 0xB6FF6D, 0xDAFF6D, 0xFFFF6D, 
  0x000091, 0x240091, 0x480091, 0x6D0091, 0x910091, 0xB60091, 0xDA0091, 0xFF0091, 
  0x005591, 0x245591, 0x485591, 0x6D5591, 0x915591, 0xB65591, 0xDA5591, 0xFF5591, 
  0x00AA91, 0x24AA91, 0x48AA91, 0x6DAA91, 0x91AA91, 0xB6AA91, 0xDAAA91, 0xFFAA91, 
  0x00FF91, 0x24FF91, 0x48FF91, 0x6DFF91, 0x91FF91, 0xB6FF91, 0xDAFF91, 0xFFFF91, 
  0x0000B6, 0x2400B6, 0x4800B6, 0x6D00B6, 0x9100B6, 0xB600B6, 0xDA00B6, 0xFF00B6, 
  0x0055B6, 0x2455B6, 0x4855B6, 0x6D55B6, 0x9155B6, 0xB655B6, 0xDA55B6, 0xFF55B6, 
  0x00AAB6, 0x24AAB6, 0x48AAB6, 0x6DAAB6, 0x91AAB6, 0xB6AAB6, 0xDAAAB6, 0xFFAAB6, 
  0x00FFB6, 0x24FFB6, 0x48FFB6, 0x6DFFB6, 0x91FFB6, 0xB6FFB6, 0xDAFFB6, 0xFFFFB6, 
  0x0000DA, 0x2400DA, 0x4800DA, 0x6D00DA, 0x9100DA, 0xB600DA, 0xDA00DA, 0xFF00DA, 
  0x0055DA, 0x2455DA, 0x4855DA, 0x6D55DA, 0x9155DA, 0xB655DA, 0xDA55DA, 0xFF55DA, 
  0x00AADA, 0x24AADA, 0x48AADA, 0x6DAADA, 0x91AADA, 0xB6AADA, 0xDAAADA, 0xFFAADA, 
  0x00FFDA, 0x24FFDA, 0x48FFDA, 0x6DFFDA, 0x91FFDA, 0xB6FFDA, 0xDAFFDA, 0xFFFFDA, 
  0x0000FF, 0x2400FF, 0x4800FF, 0x6D00FF, 0x9100FF, 0xB600FF, 0xDA00FF, 0xFF00FF, 
  0x0055FF, 0x2455FF, 0x4855FF, 0x6D55FF, 0x9155FF, 0xB655FF, 0xDA55FF, 0xFF55FF, 
  0x00AAFF, 0x24AAFF, 0x48AAFF, 0x6DAAFF, 0x91AAFF, 0xB6AAFF, 0xDAAAFF, 0xFFAAFF, 
  0x00FFFF, 0x24FFFF, 0x48FFFF, 0x6DFFFF, 0x91FFFF, 0xB6FFFF, 0xDAFFFF, 0xFFFFFF,
};

static const LCD_PHYSPALETTE _aPalette_256 = {
  GUI_COUNTOF(_aColors_256), _aColors_256
};

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
static void _InitController(void) {
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetLUTEntry
*
* Purpose:
*   Should set the desired LUT entry
*/
static void _SetLUTEntry(LCD_COLOR Color, U8 Pos) {
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
  LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  LCD_SetLUTEx(0, &_aPalette_256);
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
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    _InitController();
    return 0;
  }
  case LCD_X_SETLUTENTRY: {
    LCD_X_SETLUTENTRY_INFO * p;
    p = (LCD_X_SETLUTENTRY_INFO *)pData;
    _SetLUTEntry(p->Color, p->Pos);
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
