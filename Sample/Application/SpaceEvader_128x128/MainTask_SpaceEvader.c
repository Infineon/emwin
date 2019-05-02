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
File        : MainTask_SpaceEvader.c
Purpose     : Spaceship game, evade the asteroids.
---------------------------END-OF-HEADER------------------------------
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
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipTop_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipLeft_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipRight_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShipBottom_Small;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpaceShip;
extern GUI_CONST_STORAGE GUI_BITMAP bmAsteroid;
extern GUI_CONST_STORAGE GUI_BITMAP bmBang;

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

#define CONTROL_TYPE_PID 0
#define CONTROL_TYPE_JOY 1
#define CONTROL_TYPE     CONTROL_TYPE_PID

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
#if (CONTROL_TYPE == CONTROL_TYPE_PID)
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
#elif (CONTROL_TYPE == CONTROL_TYPE_JOY)
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
    pShip->pBitmap = &bmSpaceShipRight_Small;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos,     pShip->yPos,
                  pShip->xPos + 5, pShip->yPos + bmSpaceShipTop_Small.YSize);
    //
    // Set new x-position
    //
    pShip->xPos += (pShip->xPos + 5 < LCD_GetXSize() - bmSpaceShipTop_Small.XSize) ? 5 : 0;
    break;
  case DIR_LEFT:
    //
    // Set the proper bitmap
    //
    pShip->pBitmap = &bmSpaceShipLeft_Small;
    //
    // Clear a rectangle left of the bitmap
    //
    GUI_ClearRect(pShip->xPos + bmSpaceShipTop_Small.XSize - 5, pShip->yPos,
                  pShip->xPos + bmSpaceShipTop_Small.XSize,     pShip->yPos + bmSpaceShipTop_Small.YSize);
    //
    // Set new x-position
    //
    pShip->xPos -= (pShip->xPos - 5 > 0) ? 5 : 0;
    break;
  default:
    //
    // No button is pressed, set the default bitmap
    //
    pShip->pBitmap = &bmSpaceShipTop_Small;
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
                pAsteroid->xPos + bmAsteroid.XSize, pAsteroid->yPos + 10);
  //
  // Set a new y-position
  //
  pAsteroid->yPos += 5;
  //
  // Draw the bitmap
  //
  GUI_DrawBitmap(&bmAsteroid, pAsteroid->xPos, pAsteroid->yPos);
  //
  // If the bitmap is no longer visible, set a new x- and y-position
  //
  if (pAsteroid->yPos >= LCD_GetYSize()) {
    pAsteroid->xPos = rand() % (XSIZE_DISPLAY - bmAsteroid.XSize);
    pAsteroid->yPos = -((int)bmAsteroid.YSize);
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
  RectAsteroid.x1 = RectAsteroid.x0 + bmAsteroid.XSize - 1;
  RectAsteroid.y1 = RectAsteroid.y0 + bmAsteroid.YSize - 1;
  //
  // First a simple check if rectangles of bitmaps overlap
  //
  if (GUI_RectsIntersect(&RectShip, &RectAsteroid)) {
    //
    // Check if lower row of asteroid collides with plane
    //
    yPos = RectAsteroid.y0 - RectShip.y0 + bmAsteroid.YSize - 1;
    if (yPos < pShip->pBitmap->XSize) {
      for (i = 0; i < bmAsteroid.XSize; i++) {
        xPos = RectAsteroid.x0 - RectShip.x0 + i;
        if ((xPos >= 0) && (xPos < pShip->pBitmap->XSize)) {
          Index = GUI_GetBitmapPixelIndex(pShip->pBitmap, xPos, yPos);
          if ((Index > 0) && (Index < 255))  {
            GUI_Clear();
            GUI_DrawBitmap(&bmBang, 0, 20);
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
*       _Intro()
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
    GUI_DrawBitmap(&bmSpaceShip, (XSIZE_DISPLAY - bmSpaceShip.XSize) / 2, yPos);
  } while (tNow < tEnd);
  GUI_Delay(1000);
  GUI_Clear();
}

/*********************************************************************
*
*       _Explain()
*/
static void _Explain(void) {
  int yPos, ySizeFont;
  unsigned i;
  const char * apText[] = {
    "Use buttons PB0",
    "and PB1 for moving",
    "the starship.",
    "",
    "Remaining time is",
    "shown in the the",
    "lower right edge",
    "of the display.",
  };
  int Direction;

  _ShowTitle();
  ySizeFont = GUI_GetFontSizeY() + 2;
  yPos = (YSIZE_DISPLAY - ySizeFont * GUI_COUNTOF(apText)) / 2;
  for (i = 0; i < GUI_COUNTOF(apText); i++) {
    GUI_DispStringHCenterAt(apText[i], XSIZE_DISPLAY / 2, yPos);
    yPos += ySizeFont;
  }
  GUI_DispStringHCenterAt("PRESS BUTTON TO START", XSIZE_DISPLAY / 2, YSIZE_DISPLAY - 10);
  do {
    Direction = _GetDirection(NULL);
    if (Direction) {
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
  // Explanation
  //
  _Explain();
  //
  // Run forever...
  //
  while (1) {
    //
    // Initialize some structures
    //
    Ship.xPos = (XSIZE_DISPLAY - bmSpaceShipTop_Small.XSize) / 2;
    Ship.yPos = YSIZE_DISPLAY - bmSpaceShipTop_Small.YSize - 5;
    Ship.pBitmap = &bmSpaceShipTop_Small;
    for (i = 0; i < GUI_COUNTOF(aAsteroid); i++) {
      aAsteroid[i].xPos = rand() % (XSIZE_DISPLAY - bmAsteroid.XSize);
      aAsteroid[i].yPos = -((int)bmAsteroid.YSize) - i * 64;
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
