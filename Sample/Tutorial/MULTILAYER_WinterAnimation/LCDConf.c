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

#include <stddef.h>

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#if (GUI_USE_ARGB == 1)
  #define COLOR_CONV GUICC_M8888I
#else
  #define COLOR_CONV GUICC_8888
#endif

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
  struct INIT_LAYER {
    const GUI_DEVICE_API * pDriver;
    const LCD_API_COLOR_CONV * pColorConv;
    int xSize, ySize;
    int xPos, yPos;
    int NumScreens;
  } aInitLayer[] = {
    {
      GUIDRV_WIN32, // DisplayDriver
      COLOR_CONV,   // ColorMode
      800, 480,     // LayerSize
      0,   0,       // LayerPosition
      1
    },
    {
      GUIDRV_WIN32, // DisplayDriver
      COLOR_CONV,   // ColorMode
      800, 200,     // LayerSize
      0,   200,     // LayerPosition
      1
    },
    {
      GUIDRV_WIN32, // DisplayDriver
      COLOR_CONV,   // ColorMode
      800, 480,     // LayerSize
      0,   0,       // LayerPosition
      1
    },
  };
  int i;
  
  for (i = 0; i < GUI_COUNTOF(aInitLayer); i++) {
    pDevice = GUI_DEVICE_CreateAndLink(aInitLayer[i].pDriver, aInitLayer[i].pColorConv, 0, i);
    LCD_SetSizeEx (i, aInitLayer[i].xSize, aInitLayer[i].ySize);
    LCD_SetVSizeEx(i, aInitLayer[i].xSize, aInitLayer[i].ySize * aInitLayer[i].NumScreens);
    LCD_SetPosEx(i, aInitLayer[i].xPos, aInitLayer[i].yPos);
    LCD_SetVisEx(i, 1);
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
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
