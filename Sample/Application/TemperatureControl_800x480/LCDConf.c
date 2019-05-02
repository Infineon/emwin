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
  INIT_LAYER aLayer[GUI_NUM_LAYERS];
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
  // TemperatureControl
  //
  3,  // Number of layers
  {
    { 3, GUIDRV_WIN32, GUICC_M565,   800, 480, 0, 0, },
    { 3, GUIDRV_WIN32, GUICC_M8888I, 200, 200, 500, 139, },
    { 3, GUIDRV_WIN32, GUICC_M8888I, 175, 175, 514, 154, },
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
  int i;
  GUI_DEVICE * pDevice;

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
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  return 0;
}
/*************************** End of file ****************************/
