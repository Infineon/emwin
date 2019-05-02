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
File        : LCDConf_GammaCorrection.c
Purpose     : Shows how gamma correction can be achieved
---------------------------END-OF-HEADER------------------------------
*/

#include <math.h>

#include "GUI.h"
#include "GUIDRV_Lin.h"

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

//
// Gamma correction
//
#define GAMMA 1.5f

static const LCD_API_COLOR_CONV * pColorConv;

static U8 a0[256];
static U8 a1[256];

/*********************************************************************
*
*       _CreateGammaArray
*/
static void _CreateGammaArray(float gamma, U8 * p0, U8 * p1) {
  int i;

  for (i = 0; i < 256; i++) {
    *(p0 + i) = (U8)((255 * pow((float)i / 255, gamma / 1.0f)) + 0.5f);
    *(p1 + i) = (U8)((255 * pow((float)i / 255, 1.0f / gamma)) + 0.5f);
  }
}

/*********************************************************************
*
*       _Color2Gamma
*/
static U32 _Color2Gamma(U32 Color) {
  U32 Gamma;

  Gamma = (a0[(Color & 0x000000FF) >>  0] <<  0) |
          (a0[(Color & 0x0000FF00) >>  8] <<  8) |
          (a0[(Color & 0x00FF0000) >> 16] << 16) |
          (    Color & 0xFF000000              );
  return Gamma;
}

/*********************************************************************
*
*       _Gamma2Color
*/
static U32 _Gamma2Color(U32 Gamma) {
  U32 Color;
  Color = (a1[(Gamma & 0x000000FF) >>  0] <<  0) |
          (a1[(Gamma & 0x0000FF00) >>  8] <<  8) |
          (a1[(Gamma & 0x00FF0000) >> 16] << 16) |
          (    Gamma & 0xFF000000              );
  return Color;
}

/*********************************************************************
*
*       _Index2Color
*/
static LCD_COLOR _Index2Color(unsigned Index) {
  U32 Color;

  Color = pColorConv->pfIndex2Color(Index);
  Color = _Gamma2Color(Color);
  return Color;
}

/*********************************************************************
*
*       _Color2Index
*/
static unsigned _Color2Index(LCD_COLOR Color) {
  U32 Gamma;
  
  Gamma = _Color2Gamma(Color);
  return pColorConv->pfColor2Index(Gamma);
}

/*********************************************************************
*
*       _GetIndexMask
*/
static unsigned _GetIndexMask(void) {
  return pColorConv->pfGetIndexMask();
}

/*********************************************************************
*
*       _ColorConv
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV _ColorConv = {
  _Color2Index,
  _Index2Color,
  _GetIndexMask,
  0,
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;

  //
  // Create arrays for fast conversion
  //
  _CreateGammaArray(GAMMA, a0, a1);
  //
  // Set pointer do desired color conversion
  //
  pColorConv = COLOR_CONVERSION;
  //
  // Standard display driver configuration
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, &_ColorConv, 0, 0);
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * 1, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * 1);
  }
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
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
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
