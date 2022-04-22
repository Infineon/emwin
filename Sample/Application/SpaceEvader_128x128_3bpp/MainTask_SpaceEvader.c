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
-------------------------- END-OF-HEADER -----------------------------
File    : MainTask_SpaceEvader.c
Purpose : Spaceship game, evade the asteroids.
Literature:
Notes:
Additional information:
  Preperations:
    Works out-of-the-box.
  Expected behavior:
    Starts a simple game.
  Sample output:
    Starts a simple game which can be played by the user.
*/

#include "GUI.h"
#include "GUI_Private.h"
#include "WM.h"

#include "stdlib.h"

/*********************************************************************
*
*       External dependencies
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipTop_43x41_3bpp;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipLeft_43x41_3bpp;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipRight_43x41_3bpp;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShip_128x113_3bpp;
extern GUI_CONST_STORAGE GUI_BITMAP bmAsteroid_20x20_3bpp;
extern GUI_CONST_STORAGE GUI_BITMAP bmBang_128x88_3bpp;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define XSIZE_DISPLAY LCD_GetXSize()
#define YSIZE_DISPLAY LCD_GetYSize()

#define PERIOD_GAME  20000
#define PERIOD_INTRO  2000

#define YSIZE_BAR 12

#define DIR_NONE   0
#define DIR_LEFT   1
#define DIR_RIGHT  2

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  int xPos;
  int yPos;
  GUI_CONST_STORAGE GUI_BITMAP * pBitmap;
} SHIP;

typedef struct {
  int xPos;
  int yPos;
} ASTEROID;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetDirection()
*
*  Function description:
*    This function returns the direction the space ship should fly.
*    It might be necessary to adapt this function depending on the
*    hardware used.
*
*    CONTROL_TYPE_PID:
*      Use the PID input to move the ship left or right. The ship
*      will move to the left if clicked left of the ship and to the
*      right if clicked right of it.
*
*    CONTROL_TYPE_JOY:
*      Use this if the pid buffer gets filled by a joystick.
*      If State.x is bigger than 0 the stick is pushed to the right.
*      If State.x is smaler than 0 the stick is pushed to the left.
*      This was originally for the SEGGER emPower evaluation board.
*/
static int _GetDirection(SHIP * pShip) {
#ifdef WIN32
  //
  // CONTROL_TYPE_PID
  //
  GUI_PID_STATE State;
  int           Direction;
  int           Center;
  
  GUI_PID_GetState(&State);                              // Get the current PID state
  Direction = DIR_NONE;
  if (pShip) {                                           // If we have a ship
    if (State.Pressed) {                                 // Check if it is pressed
      Center = pShip->xPos + pShip->pBitmap->XSize / 2;  // If pressed get the center of the ship
      if (State.x > Center) {                            // Pressed right of the ship
        Direction = DIR_RIGHT;
      } else if (State.x < Center) {                     // Pressed left of the ship
        Direction = DIR_LEFT;
      }
    }
  } else {                                               // We have no ship
    if (State.Pressed == 1) {                            // Anyway, if pressed return a value
      Direction = DIR_LEFT;
    }
  }
  return Direction;
#else
  //
  // CONTROL_TYPE_KEY
  //
  GUI_PID_STATE State;
  int           Direction;
  
  GUI_PID_GetState(&State);    // Get the current PID state
  if (pShip) {                 // If we have a ship
    if (State.x > 0) {         // Pressed right of the ship
      Direction = DIR_RIGHT;
    } else if (State.x < 0) {  // Pressed left of the ship
      Direction = DIR_LEFT;
    } else {
      Direction = DIR_NONE;    // No pressed state
    }
  } else {                     // We have no ship
    if (State.x != 0) {        // Anyway, if pressed return a value
      Direction = DIR_LEFT;
    } else {
      Direction = DIR_NONE;
    }
  }
  return Direction;
#endif
}

/*********************************************************************
*
*       _Game()
*/
static void _Game(SHIP * pShip) {
  int Direction;
  //
  // Clear previous shape
  //
  GUI_ClearRect(pShip->xPos, pShip->yPos, pShip->xPos + pShip->pBitmap->XSize - 1, pShip->yPos + pShip->pBitmap->YSize - 1);
  //
  // Check which direction
  //
  Direction = _GetDirection(pShip);
  switch (Direction) {
  case DIR_RIGHT:
    //
    // Set the proper bitmap
    //
    pShip->pBitmap = &bmSpaceShipRight_43x41_3bpp;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos,     pShip->yPos,
                  pShip->xPos + 5, pShip->yPos + bmSpaceShipTop_43x41_3bpp.YSize);
    //
    // Set new x-position
    //
    pShip->xPos += (pShip->xPos + 5 < LCD_GetXSize() - bmSpaceShipTop_43x41_3bpp.XSize) ? 5 : 0;
    break;
  case DIR_LEFT:
    //
    // Set the proper bitmap
    //
    pShip->pBitmap = &bmSpaceShipLeft_43x41_3bpp;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos + bmSpaceShipTop_43x41_3bpp.XSize - 5, pShip->yPos,
                  pShip->xPos + bmSpaceShipTop_43x41_3bpp.XSize,     pShip->yPos + bmSpaceShipTop_43x41_3bpp.YSize);
    //
    // Set new x-position
    //
    pShip->xPos -= (pShip->xPos - 5 > 0) ? 5 : 0;
    break;
  default:
    //
    // No button is pressed, set the default bitmap
    //
    pShip->pBitmap = &bmSpaceShipTop_43x41_3bpp;
    break;
  }
  //
  // Draw bitmap
  //
  GUI_DrawBitmap(pShip->pBitmap, pShip->xPos, pShip->yPos);
}

/*********************************************************************
*
*       _Asteroid()
*/
static void _Asteroid(ASTEROID * pAsteroid) {
  //
  // Clear a rectangle above the bitmap
  //
  GUI_ClearRect(pAsteroid->xPos,                    pAsteroid->yPos,
                pAsteroid->xPos + bmAsteroid_20x20_3bpp.XSize, pAsteroid->yPos + 10);
  //
  // Set a new y-position
  //
  pAsteroid->yPos += 5;
  //
  // Draw the bitmap
  //
  GUI_DrawBitmap(&bmAsteroid_20x20_3bpp, pAsteroid->xPos, pAsteroid->yPos);
  //
  // If the bitmap is no longer visible, set a new x- and y-position
  //
  if (pAsteroid->yPos >= LCD_GetYSize()) {
    pAsteroid->xPos = rand() % (XSIZE_DISPLAY - bmAsteroid_20x20_3bpp.XSize);
    pAsteroid->yPos = (int)bmAsteroid_20x20_3bpp.YSize * -1;
  }
}

/*********************************************************************
*
*       _CheckCollision()
*/
static int _CheckCollision(ASTEROID * pAsteroid, ASTEROID * pAsteroid2, SHIP * pShip) {
  GUI_RECT RectShip, RectAsteroid;
  int xPos, yPos;
  int i, r;
  LCD_PIXELINDEX Index;

  r = 0;
  RectShip.x0 = pShip->xPos;
  RectShip.y0 = pShip->yPos;
  RectShip.x1 = RectShip.x0 + pShip->pBitmap->XSize - 1;
  RectShip.y1 = RectShip.y0 + pShip->pBitmap->YSize - 1;
  RectAsteroid.x0 = pAsteroid->xPos;
  RectAsteroid.y0 = pAsteroid->yPos;
  RectAsteroid.x1 = RectAsteroid.x0 + bmAsteroid_20x20_3bpp.XSize - 1;
  RectAsteroid.y1 = RectAsteroid.y0 + bmAsteroid_20x20_3bpp.YSize - 1;
  //
  // First a simple check if rectangles of bitmaps overlap
  //
  if (GUI_RectsIntersect(&RectShip, &RectAsteroid)) {
    //
    // Check if lower row of asteroid collides with plane
    //
    yPos = RectAsteroid.y0 - RectShip.y0 + bmAsteroid_20x20_3bpp.YSize - 1;
    if (yPos < pShip->pBitmap->XSize) {
      for (i = 0; i < bmAsteroid_20x20_3bpp.XSize; i++) {
        xPos = RectAsteroid.x0 - RectShip.x0 + i;
        if ((xPos >= 0) && (xPos < pShip->pBitmap->XSize)) {
          Index = GUI_GetBitmapPixelIndex(pShip->pBitmap, xPos, yPos);
          Index = GUI_Index2Color(Index);
          if (Index != GUI_WHITE)  {
            GUI_Clear();
            GUI_DrawBitmap(&bmBang_128x88_3bpp, 0, 20);
            LCD_ControlCache(LCD_CC_UNLOCK);
            LCD_ControlCache(LCD_CC_LOCK);
            GUI_Delay(1000);
            GUI_Clear();
            pAsteroid->yPos = pAsteroid2->yPos - YSIZE_DISPLAY / 2;
            r = 1;
            break;
          }
        }
      }
    }
  }
  return r;
}

/*********************************************************************
*
*       _ShowTitle
*/
static void _ShowTitle(void) {
  GUI_Clear();
  GUI_DispStringHCenterAt("emWin Space Evader", XSIZE_DISPLAY / 2, 2);
  GUI_DrawHLine(YSIZE_BAR - 1, 0, XSIZE_DISPLAY - 1);
}

/*********************************************************************
*
*       _Intro
*/
static void _Intro(void) {
  int t0, tEnd, tNow, tUsed;
  int yPos;

  _ShowTitle();
  t0 = GUI_GetTime();
  tEnd = t0 + PERIOD_INTRO;
  do {
    tNow = GUI_GetTime();
    tUsed = tNow - t0;
    tUsed = (tUsed > PERIOD_INTRO) ? PERIOD_INTRO : tUsed;
    yPos = YSIZE_DISPLAY - (tUsed * (YSIZE_DISPLAY - YSIZE_BAR)) / PERIOD_INTRO;
    GUI_DrawBitmap(&bmSpaceShip_128x113_3bpp, (XSIZE_DISPLAY - bmSpaceShip_128x113_3bpp.XSize) / 2, yPos);
  } while (tNow < tEnd);
  GUI_Delay(1000);
  GUI_Clear();
}

/*********************************************************************
*
*       _Explain
*/
static void _Explain(void) {
  int yPos, ySizeFont;
  unsigned i;
  const char * apText[] = {
    "Use Stick for moving",
    "the starship.",
    "",
    "Remaining time is",
    "shown in the the",
    "lower right edge",
    "of the display.",
  };
  GUI_PID_STATE State;

  _ShowTitle();
  ySizeFont = GUI_GetFontSizeY() + 2;
  yPos = (YSIZE_DISPLAY - ySizeFont * GUI_COUNTOF(apText)) / 2;
  for (i = 0; i < GUI_COUNTOF(apText); i++) {
    GUI_DispStringHCenterAt(apText[i], XSIZE_DISPLAY / 2, yPos);
    yPos += ySizeFont;
  }
  GUI_DispStringHCenterAt("PRESS LEFT/RIGHT TO START", XSIZE_DISPLAY / 2, YSIZE_DISPLAY - 10);
  do {
    GUI_PID_GetState(&State);
    if (State.x > 0) {
      break;
    }
    if (State.x < 0) {
      break;
    }
    GUI_X_Delay(10);
  } while (1);
  GUI_Clear();
  GUI_DispStringHCenterAt("Good luck...", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 4);
  GUI_Delay(1000);
  GUI_Clear();
}

/*********************************************************************
*
*       _ShowResult
*/
static void _ShowResult(unsigned Cnt) {
  _ShowTitle();
  if (Cnt) {
    GUI_DispStringHCenterAt("Ships lost in space:\n\n", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 10);
    GUI_GotoXY(XSIZE_DISPLAY / 2 - 4, YSIZE_DISPLAY / 2);
    GUI_DispDecMin(Cnt);
  } else {
    GUI_DispStringHCenterAt("CONGRATULATIONS\n\nNo ship lost", XSIZE_DISPLAY / 2, YSIZE_DISPLAY / 2 - 10);
  }
  GUI_Delay(2000);
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
*/
void MainTask(void) {
  SHIP Ship;
  ASTEROID aAsteroid[2];
  unsigned i, Cnt;
  GUI_TIMER_TIME t0, tEnd, tNow;

  //
  // Initialize GUI
  //
  GUI_Init();
  //
  // Set foreground color to black
  //
  GUI_SetColor(GUI_BLACK);
  GUI_SetBkColor(GUI_WHITE);
  //
  // Run forever...
  //
  while (1) {
    //
    // Explanation
    //
    _Explain();
    //
    // Initialize some structures
    //
    Ship.xPos = (XSIZE_DISPLAY - bmSpaceShipTop_43x41_3bpp.XSize) / 2;
    Ship.yPos = YSIZE_DISPLAY - bmSpaceShipTop_43x41_3bpp.YSize - 5;
    Ship.pBitmap = &bmSpaceShipTop_43x41_3bpp;
    for (i = 0; i < GUI_COUNTOF(aAsteroid); i++) {
      aAsteroid[i].xPos = rand() % (XSIZE_DISPLAY - bmAsteroid_20x20_3bpp.XSize);
      aAsteroid[i].yPos = ((int)bmAsteroid_20x20_3bpp.YSize * -1) - i * 64;
    }
    //
    // Intro
    //
    _Intro();
    //
    // The game
    //
    t0 = GUI_GetTime();
    tEnd = t0 + PERIOD_GAME;
    Cnt = 0;
    do {
      //
      // Lock cache, output is written to cache only
      //
      LCD_ControlCache(LCD_CC_LOCK);
      //
      // Handle drawing of the ship
      //
      _Game(&Ship);
      //
      // Handle drawing of the asteroid
      //
      for (i = 0; i < GUI_COUNTOF(aAsteroid); i++) {
        _Asteroid(&aAsteroid[i]);
        //
        // Check collision
        //
        if (_CheckCollision(&aAsteroid[i], &aAsteroid[1 - i], &Ship)) {
          Cnt++;
        }
      }
      tNow = GUI_GetTime();
      //
      // Show remaining time
      //
      GUI_GotoXY(XSIZE_DISPLAY - 12 - 1, YSIZE_DISPLAY - 8 - 1);
      GUI_DispDecSpace((tEnd - tNow + 1000) / 1000, 2);
      //
      // Show content of cache
      //
      LCD_ControlCache(LCD_CC_UNLOCK);
      //
      // Wait a while...
      //
      GUI_Delay(50);
    } while (GUI_GetTime() < tEnd);
    //
    // Show result
    //
    _ShowResult(Cnt);
  }
}

/****** End of File *************************************************/
