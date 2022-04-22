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
File        : FONT_ShowXBF.c
Purpose     : Shows how to use (E)xternal (B)inary (F)onts
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Can be used in a MS Windows environment only!
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

#include <windows.h>

#include "GUI.h"
#include "EDIT.h"

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetFileName
*
* Function description
*   Returns the file name of the XBF file to be used
*/
static void _GetFileName(char * pPath, unsigned MaxSize) {
  WM_HWIN hWin;
  
  //
  // Set default value on first call
  //
  if (!strlen(pPath)) {
    strcpy(pPath, "Sample\\Tutorial\\FONT_ShowXBF\\ExtBinFont.xbf");
  }
  // Display small hint
  GUI_SetFont(&GUI_Font10_ASCII);
  GUI_DispStringHCenterAt("Please enter the file name of the XBF-file:", 160, 80);
  //
  // Create edit widget
  //
  hWin = EDIT_Create(10, 120, 300, 20, 0, MaxSize, WM_CF_SHOW);
  EDIT_SetText(hWin, pPath);
  WM_SetFocus(hWin);
  //
  // Wait until GUI_KEY_ENTER has been pressed
  //
  GUI_GetKey();  // Clear key buffer
  do {
    GUI_Delay(300);
  } while (GUI_GetKey() != GUI_KEY_ENTER);
  //
  // Get filename from EDIT widget
  //
  EDIT_GetText(hWin, pPath, MaxSize);
  //
  // Create edit widget
  //
  WM_DeleteWindow(hWin);
  //
  // Clear screen
  //
  GUI_ClearRect(0, 40, 319, 239);
}

/*********************************************************************
*
*       _cbGetData
*
* Function description
*   Callback function for getting font data
*
* Parameters:
*   Off      - Position of XBF file to be read
*   NumBytes - Number of requested bytes
*   pVoid    - Application defined pointer
*   pBuffer  - Pointer to buffer to be filled by the function
*
* Return value:
*   0 on success, 1 on error
*/
static int _cbGetData(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer) {
  HANDLE hFile;
  DWORD  NumBytesRead;

  hFile = *(HANDLE *)pVoid;
  //
  // Set file pointer to the requested position
  //
  if (SetFilePointer(hFile, Off, 0, FILE_BEGIN) == 0xFFFFFFFF) {
    return 1; // Error
  }
  //
  // Read font data
  //
  if (!ReadFile(hFile, pBuffer, NumBytes, &NumBytesRead, 0)) {
    return 1; // Error
  }
  if (NumBytesRead != NumBytes) {
    return 1; // Error
  }
  return 0;   // Ok
}

/*********************************************************************
*
*       _ShowXBF
*
* Function description
*   Small sub routine which creates (and selects) a XBF font,
*   shows 'Hello world!' and waits for a keypress
*/
static void _ShowXBF(void * pVoid) {
  GUI_XBF_DATA XBF_Data;
  GUI_FONT     Font;

  //
  // Create XBF font
  //
  GUI_XBF_CreateFont(&Font,             // Pointer to GUI_FONT structure in RAM
                     &XBF_Data,         // Pointer to GUI_XBF_DATA structure in RAM
                     GUI_XBF_TYPE_PROP, // Font type to be created
                     _cbGetData,        // Pointer to callback function
                     pVoid);            // Pointer to be passed to GetData function
  //
  // Show 'Hello world!'
  //
  GUI_DispStringHCenterAt("Hello world!", 160, 80);
  //
  // Display hint
  //
  GUI_SetFont(&GUI_Font13_ASCII);
  GUI_DispStringHCenterAt("Press any key to continue...", 160, 120);
  //
  // Wait for pressing a key
  //
  GUI_GetKey();  // Clear key buffer
  do {
    GUI_Delay(500);
  } while (!GUI_GetKey());
  //
  // Delete XBF font and clear display
  //
  GUI_XBF_DeleteFont(&Font);
  GUI_ClearRect(0, 40, 319, 239);
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
  HANDLE hFile;
  char   acPath[_MAX_PATH] = {0};

  //
  // Initialize emWin
  //
  GUI_Init(); 
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("External binary font sample", 160, 5);
  while (1) {
    //
    // Get font file name...
    //
    _GetFileName(acPath, sizeof(acPath));
    //
    // ...and open the file
    //
    hFile = CreateFile(acPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile != INVALID_HANDLE_VALUE) {
      //
      // On success call demo routine
      //
      _ShowXBF(&hFile);
      CloseHandle(hFile);
    } else {
      //
      // On error show message box
      //
      GUI_MessageBox("File not found!", "Error", GUI_MESSAGEBOX_CF_MODAL);
      GUI_ClearRect(0, 40, 319, 239);
    }
  }
}

#endif

/*************************** End of file ****************************/
