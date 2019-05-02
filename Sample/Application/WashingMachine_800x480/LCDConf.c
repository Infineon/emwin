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
---------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display configuration file
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include <stdlib.h>

#include "GUI.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/
//
// Set this define to 1 if you want to use soft layers. The application
// needs to be configured properly, too.
//
#define USE_SOFTLAYER    0

#if (GUI_USE_ARGB == 1)
  #define COLOR_CONVERSION GUICC_M8888I
#else
  #define COLOR_CONVERSION GUICC_8888
#endif

#define DISPLAY_DRIVER   GUIDRV_WIN32

#define NUM_BUFFERS      3

#define NUM_LAYER        4

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/
#if (USE_SOFTLAYER == 0)
typedef struct {
  int NumBuffers;
  const GUI_DEVICE_API * pDriver;
  const LCD_API_COLOR_CONV * pColorConv;
  int xSize, ySize;
  int xPos, yPos;
} INIT_LAYER;
#endif

typedef struct {
  int NumLayers;
#if USE_SOFTLAYER
  GUI_SOFTLAYER_CONFIG aLayer[NUM_LAYER];
#else
  INIT_LAYER aLayer[NUM_LAYER];
#endif
} INIT_APP;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// Array for initializing layers for applications. Do not change order
//
static INIT_APP _InitApp = {
  //
  // WashingMachine
  //
  NUM_LAYER,  // Number of layers
  {
#if USE_SOFTLAYER
    {   0,   0, 800, 480, 1, },
    {  22,  30, 760, 400, 1, },
    {  12, 153, 776, 173, 1, },
    { 625, 325, 151,  40, 1, },
#else
    { NUM_BUFFERS, DISPLAY_DRIVER, COLOR_CONVERSION, 800, 480,   0,   0, },
    { NUM_BUFFERS, DISPLAY_DRIVER, COLOR_CONVERSION, 760, 400,  22,  30, },
    { NUM_BUFFERS, DISPLAY_DRIVER, COLOR_CONVERSION, 776, 173,  12, 153, },
    { NUM_BUFFERS, DISPLAY_DRIVER, COLOR_CONVERSION, 151,  40, 625, 325, },
#endif
  }
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCDCONF_GetLayerPos
*/
void LCDCONF_GetLayerPos(int LayerIndex, int * pxPos, int * pyPos) {
  if (LayerIndex < _InitApp.NumLayers) {
    if (pxPos) {
      *pxPos = _InitApp.aLayer[LayerIndex].xPos;
    }
    if (pyPos) {
      *pyPos = _InitApp.aLayer[LayerIndex].yPos;
    }
  }
}

/*********************************************************************
*
*       LCD_X_Config
*/
void LCD_X_Config(void) {
  int i;
  GUI_DEVICE * pDevice;

#if USE_SOFTLAYER
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
  #endif
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  if (LCD_GetSwapXYEx(0)) {
    LCD_SetSizeEx (0, _InitApp.aLayer[0].ySize, _InitApp.aLayer[0].xSize);
    LCD_SetVSizeEx(0, _InitApp.aLayer[0].ySize, _InitApp.aLayer[0].xSize);
  } else {
    LCD_SetSizeEx (0, _InitApp.aLayer[0].xSize, _InitApp.aLayer[0].ySize);
    LCD_SetVSizeEx(0, _InitApp.aLayer[0].xSize, _InitApp.aLayer[0].ySize);
  }
  GUI_SOFTLAYER_Enable(_InitApp.aLayer, NUM_LAYER, GUI_DARKBLUE);
#else
  //
  // Multiple buffer configuration, should be the first thing here in that routine
  //
  for (i = 0; i < _InitApp.NumLayers; i++) {
    if (_InitApp.aLayer[i].NumBuffers > 1) {
      GUI_MULTIBUF_ConfigEx(i, _InitApp.aLayer[i].NumBuffers);
    }
  }
  //
  // Set display driver and color conversion for layers
  //
  for (i = 0; i < _InitApp.NumLayers; i++) {
    pDevice = GUI_DEVICE_CreateAndLink(_InitApp.aLayer[i].pDriver, _InitApp.aLayer[i].pColorConv, 0, i);
    if (pDevice == NULL) {
      while (1); // Error
    }
    if (LCD_GetSwapXYEx(i)) {
      LCD_SetSizeEx (i, _InitApp.aLayer[i].ySize, _InitApp.aLayer[i].xSize);
      LCD_SetVSizeEx(i, _InitApp.aLayer[i].ySize, _InitApp.aLayer[i].xSize);
    } else {
      LCD_SetSizeEx (i, _InitApp.aLayer[i].xSize, _InitApp.aLayer[i].ySize);
      LCD_SetVSizeEx(i, _InitApp.aLayer[i].xSize, _InitApp.aLayer[i].ySize);
    }
    LCD_SetPosEx(i, _InitApp.aLayer[i].xPos, _InitApp.aLayer[i].yPos);
    LCD_SetVisEx(i, 1);
  }
#endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  return 0;
}
/*************************** End of file ****************************/
