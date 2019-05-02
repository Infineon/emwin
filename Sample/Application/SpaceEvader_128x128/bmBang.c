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
File        : bmBang.c
Purpose     : 128 * 88 pixels, 2 colors
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmBang;

/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsBang[] = {
  0x000000, 0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalBang = {
  2,  // Number of entries
  0,  // No transparency
  &_ColorsBang[0]
};

static GUI_CONST_STORAGE unsigned char _acBang[] = {
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXX_XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XX__XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XX__XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, XXXXXXXX, XXXXXXXX, XX__XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, _XXXXXXX, XXXXXXXX, XX__XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, _XXXXXXX, XXXXXXXX, X___XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _XXXXXXX, XXXXXXXX, X___XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, __XXXXXX, XXXXXXXX, X____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, __XXXXXX, XXXXXXXX, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, __XXXXXX, XXXXXXXX, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXX___, ___XXXXX, XXXXXXXX, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXX___, ___XXXXX, XXXXXXXX, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_XXXXXX, XXXXX___, ___XXXXX, X_XXXXX_, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X__XXXXX, XXXXX___, ____XXXX, X__XXXX_, _____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X____XXX, XXXX____, ____XXXX, X__XXXX_, ______XX, XXXXXXXX, XXXXX__X, XXXXXXXX, XXXXXXXX, __XXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_____XX, XXXX____, ____XXXX, ___XXX__, ______XX, XXX__XXX, XXXX___X, XXXXXXXX, XXXXXX__, _XXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X______X, XXXX____, _____XXX, ____XX__, ______XX, X____XXX, XXX____X, XXXXXXXX, XXXXX___, _XXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, XXX_____, _____XX_, ____XX__, ______XX, _____XXX, XX_____X, XXXXXXXX, XXX_____, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, _XX_____, _____XX_, ____X___, ________, _____XXX, X______X, XXXXXXXX, X______X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, __X_____, _____XX_, ________, ________, _____XXX, _______X, XXXXXXX_, _______X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, ________, ________, ________, ________, _____XX_, _______X, XXXXX___, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, X__XXXXX, XXXXXXXX, XXXXXXXX, X_______, ________, ________, ________, ________, ________, _______X, XXX_____, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, X_______, XXXXXXXX, XX___XXX, X_______, ________, ________, ________, ________, ________, _______X, XX______, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XX______, ____XXXX, XX_____X, X_______, ________, ________, ________, ________, ________, _______X, ________, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXX_____, ________, _X______, ________, ________, ________, ________, ________, ________, ________, ________, ___XXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXX____, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, __XXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXX___, ________, ________, ________, ________, ______XX, XXXX____, ________, XX______, ________, ________, __XXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXX__, ________, ________, ________, ________, ______XX, XXXXX___, _______X, XXXX____, ________, ________, _XXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXX__, ________, ________, ________, ________, ______XX, XXXXX___, _______X, XXXX____, ________, ________, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXX_, ________, _____XXX, XXXXXX__, ________, ______XX, XXXXXX__, _______X, XXXX____, ________, ________, XX____XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, _XXXXXXX, XXXXXXXX, ________, _______X, XXXXXX__, _______X, XXXX____, ________, ________, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, XXXXXXXX, XXXXXXXX, X_______, _______X, XXXXXXX_, _______X, XXXX____, ________, ________, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XX______, XXXXXXXX, XXXXXXXX, X______X, X______X, XXXXXXXX, _______X, XXXX____, ____XXXX, ________, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXX_____, XXXXXXXX, XXXXXXXX, XX_____X, XX_____X, XXXXXXXX, _______X, XXXX____, __XXXXXX, XX______, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXX____, XXXXXXXX, XXXXXXXX, XX_____X, XX______, XXXXXXXX, X______X, XXXX____, __XXXXXX, XXX_____, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXX____, _XXXX___, ____XXXX, XX_____X, XXX_____, XXXXXXXX, X______X, XXXX____, _XXXXXXX, XXXX____, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXX___, _XXXX___, ____XXXX, XX____XX, XXX_____, XXXXXXXX, XX_____X, XXXX____, XXXXXXXX, XXXXX___, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, _XXXX___, ___XXXXX, X_____XX, XXX_____, XXXXXXXX, XX_____X, XXXX____, XXXXXX_X, XXXXX___, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXX__, ________, _XXXXX__, ___XXXXX, X_____XX, XXX_____, _XXXXXXX, XXX____X, XXXX___X, XXXXX___, XXXXXX__, ________, _XXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXX_, ________, __XXXXX_, _XXXXXXX, ______XX, XXXX____, _XXXXXXX, XXX____X, XXXX___X, XXXX____, _XXXXX__, ________, _______X, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, __XXXXXX, XXXXXXX_, ______XX, XXXX____, _XXXXXXX, XXXX___X, XXXX___X, XXX_____, _XXXXX__, ________, ________, ____XXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XX______, __XXXXXX, XXXXXX__, _____XXX, XXXX____, __XXXXXX, XXXXX__X, XXXX__XX, XXX_____, _XXXX___, ________, ________, _______X,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXX_____, __XXXXXX, XXXXX___, _____XXX, XXXX____, __XXXXXX, XXXXX__X, XXX___XX, XX______, ________, ________, ________, ____XXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXX_, ________, ___XXXXX, XXXXXX__, _____XXX, XXXX____, __XXXXX_, XXXXXX_X, XXX___XX, XX______, ________, ________, ________, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXX_____, ________, ___XXXXX, XXXXXXX_, _____XXX, XXXXX___, __XXXXX_, XXXXXX_X, XXX___XX, XX______, ________, ________, _____XXX, XXXXXXXX,
  XXXXXXXX, XXXXXXX_, ________, ________, ___XXXXX, XXXXXXXX, _____XXX, XXXXX___, ___XXXXX, _XXXXXXX, XXX___XX, XX______, ________, ________, _XXXXXXX, XXXXXXXX,
  XXXXXXXX, XXX_____, ________, ________, ____XXXX, XXXXXXXX, ____XXXX, XXXXX___, ___XXXXX, _XXXXXXX, XXX__XXX, XX______, ________, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXX_, ________, ________, ________, ____XXXX, XXXXXXXX, X___XXXX, XXXXX___, ___XXXXX, _XXXXXXX, XXX__XXX, XX______, ________, ___XXXXX, XXXXXXXX, XXXXXXXX,
  XX______, ________, ________, ________, ____XXXX, XX_XXXXX, X___XXXX, XXXXXX__, ___XXXXX, __XXXXXX, XXX__XXX, XX______, ________, ___XXXXX, XXXXXXXX, XXXXXXXX,
  XXXX____, ________, ________, ________, ____XXXX, ____XXXX, X___XXXX, _XXXXX__, ___XXXXX, X_XXXXXX, XXX__XXX, XX____XX, XXXX____, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXX___, ________, ________, _____XXX, _____XXX, X___XXXX, __XXXX__, ____XXXX, X__XXXXX, XXX___XX, XX____XX, XXXX____, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXX__, ________, _____XXX, X____XXX, X___XXXX, __XXXX__, ____XXXX, X__XXXXX, XXX___XX, XX____XX, XXXX____, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _____XXX, X____XXX, X__XXXXX, __XXXX__, ____XXXX, X___XXXX, XXX___XX, XX_____X, XXXX____, _______X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _____XXX, X___XXXX, ___XXXXX, __XXXXX_, ____XXXX, X___XXXX, XXX___XX, XX______, XXXX____, ________, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXX___, ______XX, XXXXXXXX, ___XXXXX, ___XXXX_, _____XXX, X____XXX, XXX___XX, XXX_____, XXXX____, ________, _XXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXX____, ______XX, XXXXXXX_, ___XXXX_, ___XXXX_, _____XXX, XX___XXX, XXX____X, XXX_____, XXX_____, _______X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXX_____, ______XX, XXXXXX__, ___XXXXX, ___XXXX_, _____XXX, XX____XX, XX_____X, XXXX___X, XXX_____, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XX______, ______XX, XXXXXX__, ___XXXXX, XXXXXXX_, ______XX, XX_____X, XX_____X, XXXXX__X, XXX_____, __XXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XX______, _______X, XXXXX___, __XXXXXX, XXXXXXXX, ______XX, XX______, ________, XXXXXXXX, XX______, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, _______X, XXXX____, __XXXXXX, XXXXXXXX, ________, ________, ________, XXXXXXXX, XX______, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, _______X, X______X, XX______, __XXXXXX, XXXXXXXX, ________, ________, ________, _XXXXXXX, X_______, _XXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXX_, ___XXXXX, X______X, X_______, __XXXXX_, ___XXXXX, ________, ________, ________, __XXXXXX, X_______, _XXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXX_X, XXXXXXXX, X_______, ________, __XXXX__, ___XXXXX, ________, ________, ________, ___XXXXX, ________, __XXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, X_______, ________, __XXXX__, ____XXXX, ________, ________, ________, ________, ________, __XXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, ________, ___XXX__, ____XXXX, X_______, ________, ________, ________, ________, ___XXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, ________, ________, ____XXXX, ________, ________, ________, ________, ________, ___XXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, ________, ________, ________, ________, ________, ________, ________, ________, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, ___X____, ________, ________, ________, ________, ________, ________, ________, ____XXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, __XX____, ________, ________, ________, ________, ________, ________, ________, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________, _XXX____, ________, ________, ________, ________, ________, ________, ___X____, _____XXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, ________, XXXX____, ________, ________, ________, ________, _X______, _X______, ___XXX__, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, _______X, XXXX____, ________, ________, XX______, ________, _XX_____, _XX_____, ___XXXXX, ______XX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, _____XXX, XXX_____, ___XXXX_, ________, XXX_____, X_______, _XXX____, XXX_____, ___XXXXX, XX_____X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, ____XXXX, XXX_____, XXXXXXX_, _______X, XXXX___X, XX______, _XXXX___, XXXX____, ___XXXXX, XXXX___X, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, ___XXXXX, XXX__XXX, XXXXXXX_, ______XX, XXXX__XX, XXX_____, XXXXXX__, XXXXX___, ____XXXX, XXXXXXX_, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, __XXXXXX, XXXXXXXX, XXXXXXX_, _____XXX, XXXXX_XX, XXX_____, XXXXXX__, XXXXXX__, ____XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _XXXXXXX, XXXXXXXX, XXXXXXXX, _____XXX, XXXXXXXX, XXXX____, XXXXXXXX, XXXXXX__, ____XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, XXXXXXXX, XXXXXXXX, XXXXXXXX, ____XXXX, XXXXXXXX, XXXX____, XXXXXXXX, XXXXXXX_, ____XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ___XXXXX, XXXXXXXX, XXXXX___, XXXXXXXX, XXXXXXXX, ____XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, __XXXXXX, XXXXXXXX, XXXXXX__, XXXXXXXX, XXXXXXXX, ____XXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _XXXXXXX, XXXXXXXX, XXXXXX__, XXXXXXXX, XXXXXXXX, X____XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXX_, XXXXXXXX, XXXXXXXX, XX___XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XX___XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXX__XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXX_XXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXX_XX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX
};

GUI_CONST_STORAGE GUI_BITMAP bmBang = {
  128,         // xSize
  88,          // ySize
  16,          // BytesPerLine
  1,           // BitsPerPixel
  _acBang,     // Pointer to picture data (indices)
  &_PalBang,   // Pointer to palette
  NULL
};

/*************************** End of file ****************************/
