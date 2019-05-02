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
File        : BASIC_Performance.c
Purpose     : Performance test program

              It checks the performance of the entire system, outputing one
              result value per second. Higher values are better.
              The program computes the first 1000 prime numbers in a loop.
              The value output is the number of times this could be performed
              in a second.
              Please note that this test does not check the driver performance.
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <string.h>
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       Static data
*
********************************************************************
*/
static char _aIsPrime[1000];
static int  _NumPrimes;

/*******************************************************************
*
*       Static Code
*
********************************************************************
*/
/*********************************************************************
*
*       _CalcPrimes
*/
static void _CalcPrimes(int NumItems) {
  int i;

  //
  // Mark all as potential prime numbers
  //
  memset(_aIsPrime, 1, NumItems);
  //
  // 2 deserves a special treatment
  //
  for (i = 4; i < NumItems; i += 2) {
    _aIsPrime[i] = 0;        // Cross it out: not a prime
  }
  //
  // Cross out multiples of every prime starting at 3. Crossing out starts at i^2.
  //
  for (i = 3; i * i < NumItems; i++) {
    if (_aIsPrime[i]) {
      int j;

      j = i * i;             // The square of this prime is the first we need to cross out
      do {
        _aIsPrime[j] = 0;    // Cross it out: not a prime
        j += 2 * i;          // Skip even multiples (only 3*, 5*, 7* etc)
      } while (j < NumItems);
    }
  }
  //
  // Count prime numbers
  //
  _NumPrimes = 0;
  for (i = 2; i < NumItems; i++) {
    if (_aIsPrime[i]) {
      _NumPrimes++;
    }
  }
}

/*********************************************************************
*
*       _PrintDec
*/
static void _PrintDec(int v) {
  int Digit;
  int r;

  Digit = 10;
  while (Digit < v) {
    Digit *= 10;
  }
  do {
    Digit /= 10;
    r = v / Digit;
    v -= r * Digit;
    GUI_DispChar(r + '0');
  } while (v | (Digit > 1));
}

/*********************************************************************
*
*       _PrintResult
*/
static void _PrintResult(int Cnt) {
  if (_NumPrimes != 168) {
    GUI_DispString("Error");
  } else {
    GUI_DispString("Loops/sec: ");
    _PrintDec(Cnt);
  }
  GUI_DispString("\n");
}

/*******************************************************************
*
*       Public Code
*
********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void);
void MainTask(void) {
  int Cnt;
  int TestTime;

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  while(1) {
    Cnt = 0;
    TestTime = GUI_GetTime() + 1000;
    while ((TestTime - GUI_GetTime()) >= 0) {
      _CalcPrimes(sizeof(_aIsPrime));
      Cnt++;
    }
    _PrintResult(Cnt);
  }
}

/*************************** End of file ****************************/
