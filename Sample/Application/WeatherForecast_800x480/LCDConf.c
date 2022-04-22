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

** emWin V6.24 - Graphical user interface for embedded applications **
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
Licensed platform:        Any Cypress platform (Initial targets are: PSoC3, PSoC5)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : LCDConf.c
Content     : Display controller configuration for weather forecast demo
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
#define USE_SOFTLAYER    1

#if (USE_SOFTLAYER == 1) 
  #define COLOR_CONVERSION GUICC_8888

  #define DISPLAY_DRIVER   GUIDRV_WIN32

  #define NUM_BUFFERS      3

  #define NUM_LAYER        2
#endif

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/
typedef struct {
  int NumBuffers;
  const GUI_DEVICE_API * pDriver;
  const LCD_API_COLOR_CONV * pColorConv;
  int xSize, ySize;
  int xPos, yPos;
} INIT_LAYER;

typedef struct {
  int NumLayers;
#if (USE_SOFTLAYER == 1)
  GUI_SOFTLAYER_CONFIG aLayer[NUM_LAYER];
#else
  INIT_LAYER aLayer[GUI_NUM_LAYERS];
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
  // WeatherForecast
  //
  NUM_LAYER,  // Number of layers
  {
#if (USE_SOFTLAYER == 1)
    { 0, 0, 800, 480, 1 },
    { 0, 0, 800, 480, 1 },
#else
    { NUM_BUFFERS, GUIDRV_WIN32, GUICC_M565,   800, 480, 0, 0, },
    { NUM_BUFFERS, GUIDRV_WIN32, GUICC_M8888I, 800, 480, 0, 0, },
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
*       LCD_X_Config
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;

#if (USE_SOFTLAYER == 1)
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
  int i;
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
