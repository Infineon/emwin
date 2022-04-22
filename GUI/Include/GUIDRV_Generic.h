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
File        : GUIDRV_Generic.h
Purpose     : Adapter to be able to use the display drivers with simple
              bus interface from emWin V4.18
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_ConfDefaults.h"

#if defined(LCD_CONTROLLER)

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Remap old configuration macros to static data
*/
#define LCD_XSIZE       _xSize
#define LCD_YSIZE       _ySize
#define LCD_VXSIZE      _vxSize
#define LCD_VYSIZE      _vySize
#define LCD_XSIZE_PHYS  _xSizePhys
#define LCD_YSIZE_PHYS  _ySizePhys
#define LCD_NUM_COLORS  _NumColors

/*********************************************************************
*
*       Required renaming operations
*/
#define LCD_On  LCD_L0_On
#define LCD_Off LCD_L0_Off

/*********************************************************************
*
*       Map undefined optional functions to dummy routines
*/
#ifndef   LCD_L0_GetDevData
  #define LCD_L0_GetDevData __GetDevDataDummy
#endif

/*********************************************************************
*
*       Prototypes of LCD_L0_xxx - functions
*/
void           LCD_L0_SetPixelIndex(int x, int y, LCD_PIXELINDEX PixelIndex);
LCD_PIXELINDEX LCD_L0_GetPixelIndex(int x, int y);
void           LCD_L0_XorPixel     (int x, int y);
void           LCD_L0_DrawHLine    (int x0, int y,  int x1);
void           LCD_L0_DrawVLine    (int x, int y0,  int y1);
void           LCD_L0_FillRect     (int x0, int y0, int x1, int y1);
void           LCD_L0_DrawBitmap   (int x0, int y0, int xsize, int ysize, int BitsPerPixel,  int BytesPerLine, const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans);
void           LCD_L0_SetOrg       (int x, int y);
void           LCD_L0_On           (void);
void           LCD_L0_Off          (void);
int            LCD_L0_Init         (void);
void           LCD_L0_SetLUTEntry  (U8 Pos, LCD_COLOR Color);
void        (* LCD_L0_GetDevFunc   (int Index))(void);
static void  * LCD_L0_GetDevData   (GUI_DEVICE * pDevice, int Index);
int            LCD_L0_ControlCache (int Cmd);
void           LCD_L0_Refresh      (void);

/*********************************************************************
*
*       Prototypes of SIM_xxx - functions
*/
void SIM_SetVRAMSize(int LayerIndex, int xSize, int ySize);

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _xSize;
static int _ySize;
static int _vxSize;
static int _vySize;
static int _xSizePhys;
static int _ySizePhys;
static int _NumColors;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       __GetDevDataDummy
*/
static void * __GetDevDataDummy(GUI_DEVICE * pDevice, int Index) {
  GUI_USE_PARA(pDevice);
  GUI_USE_PARA(Index);
  return NULL;
}

/*********************************************************************
*
*       __SetPixelIndex
*/
static void __SetPixelIndex(GUI_DEVICE * pDevice, int x, int y, LCD_PIXELINDEX PixelIndex) {
  GUI_USE_PARA(pDevice);
  LCD_L0_SetPixelIndex(x, y, PixelIndex);
}

/*********************************************************************
*
*       __GetPixelIndex
*/
static LCD_PIXELINDEX __GetPixelIndex(GUI_DEVICE * pDevice, int x, int y) {
  GUI_USE_PARA(pDevice);
  return LCD_L0_GetPixelIndex(x, y);
}

/*********************************************************************
*
*       __XorPixel
*/
static void __XorPixel(GUI_DEVICE * pDevice, int x, int y) {
  GUI_USE_PARA(pDevice);
  LCD_L0_XorPixel(x, y);
}

/*********************************************************************
*
*       __DrawHLine
*/
static void __DrawHLine(GUI_DEVICE * pDevice, int x0, int y,  int x1) {
  GUI_USE_PARA(pDevice);
  LCD_L0_DrawHLine(x0, y, x1);
}

/*********************************************************************
*
*       __DrawVLine, not optimized
*/
static void __DrawVLine(GUI_DEVICE * pDevice, int x, int y0,  int y1) {
  GUI_USE_PARA(pDevice);
  LCD_L0_DrawVLine(x, y0, y1);
}

/*********************************************************************
*
*       __FillRect
*/
static void __FillRect(GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1) {
  GUI_USE_PARA(pDevice);
  LCD_L0_FillRect(x0, y0, x1, y1);
}

/*********************************************************************
*
*       __DrawBitmap
*/
static void __DrawBitmap(GUI_DEVICE * pDevice, int x0, int y0,
                       int xSize, int ySize,
                       int BitsPerPixel,
                       int BytesPerLine,
                       const U8 * pData, int Diff,
                       const LCD_PIXELINDEX * pTrans) {
  GUI_USE_PARA(pDevice);
  LCD_L0_DrawBitmap(x0, y0, xSize, ySize, BitsPerPixel, BytesPerLine, pData, Diff, pTrans);
}

/*********************************************************************
*
*       __SetOrg
*/
static void __SetOrg(GUI_DEVICE * pDevice, int x, int y) {
  GUI_USE_PARA(pDevice);
  LCD_L0_SetOrg(x, y);
}

/*********************************************************************
*
*       _SetVSize
*/
static void _SetVSize(GUI_DEVICE * pDevice, int xSize, int ySize) {
  LCD_VXSIZE = xSize;
  LCD_VYSIZE = ySize;
  #if defined(WIN32) | defined(LCD_SIMCONTROLLER)
    SIM_SetVRAMSize(pDevice->LayerIndex, xSize, ySize);
  #else
    GUI_USE_PARA(pDevice);
  #endif
}

/*********************************************************************
*
*       _SetSize
*/
static void _SetSize(GUI_DEVICE * pDevice, int xSize, int ySize) {
  GUI_USE_PARA(pDevice);
  LCD_XSIZE = xSize;
  LCD_YSIZE = ySize;
  #if (LCD_SWAP_XY)
    _xSizePhys = ySize;
    _ySizePhys = xSize;
  #else
    _xSizePhys = xSize;
    _ySizePhys = ySize;
  #endif
}

/*********************************************************************
*
*       __ReadRect
*/
static void __ReadRect(GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer) {
  void (* pfReadRect)(int, int, int, int, LCD_PIXELINDEX *);

  GUI_USE_PARA(pDevice);
  pfReadRect = (void (*)(int, int, int, int, LCD_PIXELINDEX *))LCD_L0_GetDevFunc(LCD_DEVFUNC_READRECT);
  pfReadRect(x0, y0, x1, y1, pBuffer);
}

/*********************************************************************
*
*       _GetReadRect
*/
static void (* _GetReadRect(void))(void) {
  if (LCD_L0_GetDevFunc(LCD_DEVFUNC_READRECT)) {
    return (void (*)(void))__ReadRect;
  }
  return NULL;
}

/*********************************************************************
*
*       __ControlCache
*/
static int __ControlCache(GUI_DEVICE * pDevice, int Cmd) {
  int (* pfControlCache)(int);

  GUI_USE_PARA(pDevice);
  pfControlCache = (int (*)(int))LCD_L0_GetDevFunc(LCD_DEVFUNC_CONTROLCACHE);
  return pfControlCache(Cmd);
}

/*********************************************************************
*
*       _GetControlCache
*/
static void (* _GetControlCache(void))(void) {
  if (LCD_L0_GetDevFunc(LCD_DEVFUNC_CONTROLCACHE)) {
    return (void (*)(void))__ControlCache;
  }
  return NULL;
}

/*********************************************************************
*
*       __Refresh
*/
static void __Refresh(GUI_DEVICE * pDevice) {
  void (* pfRefresh)(void);

  GUI_USE_PARA(pDevice);
  pfRefresh = (void (*)(void))LCD_L0_GetDevFunc(LCD_DEVFUNC_REFRESH);
  pfRefresh();
}

/*********************************************************************
*
*       _GetRefresh
*/
static void (* _GetRefresh(void))(void) {
  if (LCD_L0_GetDevFunc(LCD_DEVFUNC_REFRESH)) {
    return (void (*)(void))__Refresh;
  }
  return NULL;
}

/*********************************************************************
*
*       _Init
*/
static int _Init(GUI_DEVICE * pDevice) {
  GUI_USE_PARA(pDevice);
  return LCD_L0_Init();
}

/*********************************************************************
*
*       __GetDevFunc
*/
static void (* __GetDevFunc(GUI_DEVICE ** ppDevice, int Index))(void) {
  GUI_USE_PARA(ppDevice);
  switch (Index) {
  case LCD_DEVFUNC_CONTROLCACHE:
    return _GetControlCache();
  case LCD_DEVFUNC_REFRESH:
    return _GetRefresh();
  case LCD_DEVFUNC_READRECT:
    return _GetReadRect();
  case LCD_DEVFUNC_SET_VSIZE:
    return (void (*)(void))_SetVSize;
  case LCD_DEVFUNC_SET_SIZE:
    return (void (*)(void))_SetSize;
  case LCD_DEVFUNC_INIT:
    return (void (*)(void))_Init;
  default:
    return (void (*)(void))LCD_L0_GetDevFunc(Index);
  }
}

/*********************************************************************
*
*       __GetDevProp
*/
static I32 __GetDevProp(GUI_DEVICE * pDevice, int Index) {
  GUI_USE_PARA(pDevice);
  switch (Index) {
  case LCD_DEVCAP_XSIZE:
    return LCD_XSIZE;
  case LCD_DEVCAP_YSIZE:
    return LCD_YSIZE;
  case LCD_DEVCAP_VXSIZE:
    return LCD_VXSIZE;
  case LCD_DEVCAP_VYSIZE:
    return LCD_VYSIZE;
  case LCD_DEVCAP_BITSPERPIXEL:
    return LCD_BITSPERPIXEL;
  case LCD_DEVCAP_NUMCOLORS:
    return 1 << LCD_BITSPERPIXEL;
  case LCD_DEVCAP_XMAG:
    return 1;
  case LCD_DEVCAP_YMAG:
    return 1;
  case LCD_DEVCAP_MIRROR_X:
    return LCD_MIRROR_X;
  case LCD_DEVCAP_MIRROR_Y:
    return LCD_MIRROR_Y;
  case LCD_DEVCAP_SWAP_XY:
    return LCD_SWAP_XY;
  case LCD_DEVCAP_SWAP_RB:
    return LCD_SWAP_RB;
  }
  return -1;
}

/*********************************************************************
*
*       __GetDevData
*/
static void * __GetDevData(GUI_DEVICE * pDevice, int Index) {
  GUI_USE_PARA(pDevice);
  switch (Index) {
  #if GUI_SUPPORT_MEMDEV
  case LCD_DEVDATA_MEMDEV:
    #if (LCD_BITSPERPIXEL == 1)
      return (void *)&GUI_MEMDEV_DEVICE_1;
    #elif (LCD_BITSPERPIXEL <= 8)
      return (void *)&GUI_MEMDEV_DEVICE_8;
    #elif (LCD_BITSPERPIXEL <= 16)
      return (void *)&GUI_MEMDEV_DEVICE_16;
    #else
      return (void *)&GUI_MEMDEV_DEVICE_32;
    #endif
  #endif
  default:
    return LCD_L0_GetDevData(pDevice, Index);
  }
}

/*********************************************************************
*
*       __GetRect
*/
static void __GetRect(GUI_DEVICE * pDevice, LCD_RECT * pRect) {
  GUI_USE_PARA(pDevice);
  pRect->x0 = 0;
  pRect->y0 = 0;
  pRect->x1 = LCD_VXSIZE - 1;
  pRect->y1 = LCD_VYSIZE - 1;
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DEVICE_API structure
*/
const GUI_DEVICE_API DISPLAY_DRIVER_API = {
  //
  // Data
  //
  DEVICE_CLASS_DRIVER,
  //
  // Drawing functions
  //
  __DrawBitmap,
  __DrawHLine,
  __DrawVLine,
  __FillRect,
  __GetPixelIndex,
  __SetPixelIndex,
  __XorPixel,
  //
  // Set origin
  //
  __SetOrg,
  //
  // Request information
  //
  __GetDevFunc,
  __GetDevProp,
  __GetDevData,
  __GetRect,
};

#endif

/*************************** End of file ****************************/
