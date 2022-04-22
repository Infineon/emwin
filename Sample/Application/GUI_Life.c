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
File    : GUI_Life.c
Purpose : An implementation of Conway's Game of Life.
Literature:
Notes:
Additional information:
  Preparations:
    Works out-of-the-box.
  Expected behavior:
    This sample displays a number of life generations.
---------------------------END-OF-HEADER------------------------------
*/

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/

#include "GUI.h"
#include "SEGGER.h"
#include <stdlib.h>
#include <string.h>

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

#define CELL_X_MAX    200
#define CELL_Y_MAX    80
#define P_LIFE        0.25f   // probability an initial square contains a living cell.

/*********************************************************************
*
*       Local types
*
**********************************************************************
*/

typedef struct {
  unsigned char aCell[CELL_X_MAX+1][CELL_Y_MAX+1];
} SLIDE;

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/

static const U32 _aSpectrumColors[] = {
  0xFF0000,
  0xFFFF00,
  0x00FF00,
  0x00FFFF,
  0x0000F0,
  0xFF00FF
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static SLIDE _ThisGeneration;
static SLIDE _NextGeneration;
static float _Dx;
static float _Dy;
static float _Dd;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _Interpolate()
*
*  Function description
*    Interpolate between colors.
*
*  Parameters
*    Color0 - First 24-bit color.
*    Color1 - Second 24-bit color.
*    Shift  - Number of bits to shift to extract channel.
*    Pos    - Value (0 to 1) for position along interpolated line.
*
*  Return value
*    Interpolated color.
*/
static unsigned _Interpolate(unsigned Color0,
                             unsigned Color1,
                             unsigned Shift,
                             float    Pos) {
  unsigned C0;
  unsigned C1;
  //
  C0 = (Color0 >> Shift) & 0xFF;
  C1 = (Color1 >> Shift) & 0xFF;
  //
  return (((unsigned)((int)(C1 - C0) * Pos) + C0) & 0xFF) << Shift;
}

/*********************************************************************
*
*       _ShowCell()
*
*  Function description
*    Write cell to LCD.
*
*  Parameters
*    x     - X cell index.
*    y     - Y cell index.
*    Color - Color to display in.
*/
static void _ShowCell(unsigned x, unsigned y, unsigned Color) {
  unsigned Index;
  float    Pos;
  unsigned Color1;
  unsigned Color2;
  //
  if (Color) {
    Pos = (float)rand() / RAND_MAX;
    Pos   *= 6;
    Index  = (int)Pos;
    Pos   -= (float)Index;
    Color1 = _aSpectrumColors[Index];
    Color2 = _aSpectrumColors[(Index+1) % 6];
    Color  = _Interpolate(Color1, Color2, 16, Pos) +
             _Interpolate(Color1, Color2,  8, Pos) +
             _Interpolate(Color1, Color2,  0, Pos);
    Color &= 0xFFFFFF;
#if GUI_USE_ARGB
    Color |= 0xFF000000;  // Completely opaque
#else
    Color  = GUI_MAKE_COLOR(Color);
#endif
    GUI_SetColor(Color);
  } else {
    GUI_SetColor(GUI_BLACK);
  }
  GUI_FillRect(x * _Dd, y * _Dd, x * _Dd + _Dd - 2, y * _Dd + _Dd - 2);
}

/*********************************************************************
*
*       _InitializeSlide()
*
*  Function description
*    Initialize slide with life.
*/
static void _InitializeSlide(void) {
  int x;
  int y;
  //
  memset(&_ThisGeneration, 0, sizeof(_ThisGeneration));
  memset(&_NextGeneration, 0, sizeof(_NextGeneration));
  //
  for (x = 1; x < _Dx; ++x) {
    for (y = 1; y < _Dy; ++y) {
      _ThisGeneration.aCell[x][y] = ((float)rand() / RAND_MAX) < P_LIFE;
      _ShowCell(x, y, _ThisGeneration.aCell[x][y]);
    }
  }
}

/*********************************************************************
*
*       _StirSlide()
*
*  Function description
*    If the pointer is down, add some random life at the touch
*    position.
*/
static void _StirSlide(void) {
  GUI_PID_STATE State;
  int           Tx;
  int           Ty;
  int           x;
  int           y;
  //
  GUI_PID_GetState(&State);
  if (State.Pressed) {
    Tx = State.x / _Dd;
    Ty = State.y / _Dd;
    //
    for (x = Tx-5; x <= Tx+5; ++x) {
      for (y = Ty-5; y <= Ty+5; ++y) {
        if (1 <= x && x < _Dx && 1 <= y && y < _Dy) {
          _ThisGeneration.aCell[x][y] = ((float)rand() / RAND_MAX) < P_LIFE;
          _ShowCell(x, y, _ThisGeneration.aCell[x][y]);
        }
      }
    }
  }
}

/*********************************************************************
*
*       _NextSlide()
*
*  Function description
*    Run a life generation.
*/
static void _NextSlide(void) {
  int x;
  int y;
  int NeighborCount;
  //
  for (x = 1; x < _Dx; ++x) {
    for (y = 1; y < _Dy; ++y) {
      NeighborCount = _ThisGeneration.aCell[x-1][y-1] + _ThisGeneration.aCell[x][y-1] + _ThisGeneration.aCell[x+1][y-1] 
                    + _ThisGeneration.aCell[x-1][y  ] +                                 _ThisGeneration.aCell[x+1][y  ] 
                    + _ThisGeneration.aCell[x-1][y+1] + _ThisGeneration.aCell[x][y+1] + _ThisGeneration.aCell[x+1][y+1];
      //
      _NextGeneration.aCell[x][y] = (NeighborCount == 3) || (_ThisGeneration.aCell[x][y] && NeighborCount == 2);
      if (_NextGeneration.aCell[x][y] != _ThisGeneration.aCell[x][y]) {
        _ShowCell(x, y, _NextGeneration.aCell[x][y]);
      }
    }
  }
  _ThisGeneration = _NextGeneration;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       MainTask()
*
*  Function description
*    Run life.
*/
void MainTask(void);
void MainTask(void) {
  GUI_Init();
  //
  _Dy = CELL_Y_MAX;
  _Dx = (float)LCD_GetXSize() / LCD_GetYSize() * _Dy;
  _Dd = SEGGER_MIN(LCD_GetXSize(), LCD_GetYSize()) / _Dy;
  if (_Dx > CELL_X_MAX) {
    _Dx = CELL_X_MAX;
  }
  //
  _InitializeSlide();
  for (;;) {
    _NextSlide();
    _StirSlide();
  }
}

/*************************** End of file ****************************/
