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
File        : 2DGL_DrawScale.c
Purpose     : Drawing a scale using GUI-functions
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - (x)
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"
#include <math.h>
#include <stddef.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define SPEED 1100

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       static code
*
********************************************************************
*/
/*******************************************************************
*
*       _DrawScale
*
* Function description
*   Drawing a scale using GUI-functions
*/
static void _DrawScale(void) {
  int XSize;
  int XMid; 
  int i;
  int r1;
  int r2;
  int rt;
  int y ;
  int step;
  int r;

  XSize = LCD_GetXSize();
  XMid  = XSize / 2;
  r1    = 110;
  r2    = 140;
  rt    = 100;
  y     = 240;
  step  =  15;
  r     = (r1 + r2) / 2;
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_SetTextAlign(GUI_TA_HCENTER);
  GUI_DispStringAt("DrawScale - Sample", 160, 5);
  while (1) {
    int c = 0;
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font8x16);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_Delay(SPEED / 2);
    GUI_DispStringAtCEOL("using", 5, 40);
    GUI_DispStringAtCEOL("GUI_AA_DrawArc", 5, 55);
    GUI_Delay(SPEED * 2);
    GUI_SetPenSize(r2 - r1);
    GUI_SetColor(GUI_MAKE_COLOR(0x0000AA));
    GUI_AA_DrawArc(XMid, y, r, r, 45, 60);
    GUI_Delay(SPEED);
    GUI_SetColor(GUI_MAKE_COLOR(0x00AA00));
    GUI_AA_DrawArc(XMid, y, r, r, 60, 90);
    GUI_Delay(SPEED);
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_WHITE);
    GUI_AA_DrawArc(XMid, y, r1, r1, 45, 135);
    GUI_Delay(SPEED);
    GUI_AA_DrawArc(XMid, y, r2, r2, 45, 135);
    GUI_Delay(SPEED);
    GUI_DispStringAtCEOL("", 5, 55);
    GUI_Delay(200);
    GUI_DispStringAtCEOL("using", 5, 40);
    GUI_DispStringAtCEOL("GUI_AA_DrawLine & GUI_DispCharAt", 5, 55);
    GUI_Delay(SPEED * 3);
    for (i = 45; i <= 135; i += step) {
      float co = cos(i * 3.1415926 / 180);
      float si = sin(i * 3.1415926 / 180);
      int   x1 = XMid - (int)(r1 * co);
      int   y1 = y    - (int)(r1 * si);
      int   x2 = XMid - (int)((r2 - 1) * co);
      int   y2 = y    - (int)((r2 - 1) * si);
      int   xt = XMid - (int)(rt * co);
      int   yt = y    - (int)(rt * si);
      GUI_SetColor(GUI_WHITE);
      GUI_SetPenSize(2);
      GUI_AA_DrawLine(x1, y1, x2, y2);
      GUI_SetColor(GUI_GREEN);
      GUI_SetFont(&GUI_Font8x8);
      GUI_DispCharAt('0' + c++, xt - 4, yt - 4);
      GUI_Delay(SPEED / 2);
    }
    GUI_Delay(SPEED * 3);
    GUI_ClearRect(0, 30, 320, 240);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  _DrawScale();
  while(1); 
}

/*************************** End of file ****************************/

