/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2022  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.32 - Graphical user interface for embedded applications **
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
SUA period:               2009-06-12 - 2023-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : GUI_GCache_Private.h
Purpose     : Private header
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_GCACHE_PRIVATE_H
#define GUI_GCACHE_PRIVATE_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define DRIVER_CONTEXT DRIVER_CONTEXT_GCACHE

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       DRIVER_CONTEXT
*/
typedef struct {
  int x0, y0, x1, y1, IsDirty;
  int xSize, ySize;
  int CacheLocked;
  int MemSize;
  int BitsPerPixel;
  int BytesPerLine;
  //
  // Line buffer for reading operation
  //
  LCD_PIXELINDEX * pLineBuffer;
  //
  // Palette for drawing 'cache bitmap'
  //
  LCD_PIXELINDEX * pPalette;
  //
  // Cache management
  //
  void (* pfReadRect)     (GUI_DEVICE * pDevice, int _x0, int _y0, int _x1, int _y1, LCD_PIXELINDEX * pBuffer);
  void (* pfSendCacheRect)(GUI_DEVICE * pDevice);
  U32 * pVMEM;
  //
  // Drawing functions
  //
  void           (* pfDrawBitmap   )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int xsize, int ysize, int _BitsPerPixel, int _BytesPerLine, const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans);
  void           (* pfDrawHLine    )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int _x1);
  void           (* pfDrawVLine    )(GUI_DEVICE *  pDevice,  int _x , int _y0, int _y1);
  void           (* pfFillRect     )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int _x1, int _y1);
  LCD_PIXELINDEX (* pfGetPixelIndex)(GUI_DEVICE *  pDevice,  int _x, int _y);
  void           (* pfSetPixelIndex)(GUI_DEVICE *  pDevice,  int _x, int _y, LCD_PIXELINDEX ColorIndex);
  void           (* pfXorPixel     )(GUI_DEVICE *  pDevice,  int _x, int _y);
  //
  // GetData function
  //
  void          *(* pfGetDevData   )(GUI_DEVICE *  pDevice,  int Index);
} DRIVER_CONTEXT;

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
GUI_DEVICE * GUI_GCACHE__CreateEx(int LayerIndex, const LCD_API_COLOR_CONV * pColorConvAPI, int BitsPerPixel);

#endif

/*************************** End of file ****************************/
