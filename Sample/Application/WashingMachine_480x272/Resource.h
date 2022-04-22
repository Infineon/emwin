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
File        : Resource.h
Content     : Main resource header file of weather forecast demo
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RESOURCE_H
#define RESOURCE_H

//
// Bitmaps
//
extern GUI_CONST_STORAGE GUI_BITMAP bmBkCotton_B_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBkEco_B_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBkSilk_B_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBkSpin_B_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBkSynthetic_B_480x272;
extern GUI_CONST_STORAGE GUI_BITMAP bmBkWoll_B_480x272;

//
// Fonts
//
extern GUI_CONST_STORAGE GUI_FONT GUI_Font_AA4_19_L;
extern GUI_CONST_STORAGE GUI_FONT GUI_Font_AA4_26_R;

//
// Colors
//
#define COLOR_GREEN  GUI_MAKE_COLOR(0x0014b6a9)
#define COLOR_BLUE   GUI_MAKE_COLOR(0x00623700)
#define COLOR_RED    GUI_MAKE_COLOR(0x000000ff)
#define COLOR_WHITE  GUI_MAKE_COLOR(0x00F2F2F2)

//
// Positions and sizes
//
#define WIN0_XPOS       14
#define WIN0_XSIZE      99
#define WIN1_XPOS       114
#define WIN1_XSIZE      59
#define WIN2_XPOS       174
#define WIN2_XSIZE      59
#define WIN3_XPOS       234
#define WIN3_XSIZE      101
#define WIN4_XPOS       336
#define WIN4_XSIZE      64
#define WIN_BAR_XSIZE   424
#define WIN_BAR_YSIZE   90
#define BUTTON_XSIZE    80
#define BUTTON_YSIZE    20
#define WIN_START_YSIZE 30
#define WIN_DESCR_YSIZE 30
#define TEXT_XSIZE      80
#define TEXT_YSIZE      30

//
// Default time
//
#define DEFAULT_HOUR    19
#define DEFAULT_MIN     15

//
// Define the fonts
//
#define FONT_SELECTION    &GUI_Font_AA4_26_R
#define FONT_DESCRIPTION  &GUI_Font_AA4_19_L

//
// Animation data
//
typedef struct {
  WM_HWIN hWin;
  int     Value;
} ANIM_DATA;

//
// Window data
//
typedef struct {
  WM_HWIN       hWin;
  const char ** ppText;
  int           NumItems;
  int           Align;
} WIN_DATA;

#endif // RESOURCE_H

/*************************** End of file ****************************/
