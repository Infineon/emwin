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
File        : iTypeBasics.c
Purpose     : Demonstrates the use of TTF font files and iType features
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - (x)
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

#include <windows.h>

#include "GUI.h"

#if 0 // Please set to 1 if iType is available

#include "GUI_iType.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define PAGE_DELAY  2000
#define FONT_COUNT     5

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static unsigned       _aHeight [] = {26};     // Array of heights used to show text
static GUI_ITYPE_CS   _aCS     [FONT_COUNT];  // Each GUI font needs its own GUI_ITYPE_CS structure
static GUI_FONT       _aFont   [FONT_COUNT];  // Array of GUI fonts
static char           _acFamily[200];
static char           _acStyle [200];

static const char   * _acFontExt[] = {        // Font file extensions. Files with other extensions will not be read.
  "ttf",
  "ltt",
  "ttc",
  "ccc",
  0
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ShowFeatures
*/
static void _ShowFeatures(void) {
  int i;

  GUI_Clear();
  i = 0;
  GUI_ITYPE_GetFamilyName(&_aFont[i], _acFamily, sizeof(_acFamily));
  GUI_ITYPE_GetStyleName (&_aFont[i], _acStyle,  sizeof(_acStyle));
  GUI_SetFont(&GUI_Font20_1);
  GUI_DispString("     Standard font:  ");
  GUI_DispString(_acFamily);
  GUI_DispString(", ");
  GUI_DispString(_acStyle);
  GUI_DispNextLine();
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  //
  // Unattributed bitmap / graymap output
  //
  GUI_SetFont(&_aFont[i]);
  GUI_DispString("** iType Text Special Effects **");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Turn off all effects
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_BITMAP);               // Bitmap output
  GUI_DispString("\nUnattributed bitmap text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_GRAYMAP4);             // Graymap output
  GUI_DispString("Unattributed 4 bpp graymap text\n");
  //
  // Italic / Bold / Bold-Italic output
  //
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_ITALIC);               // Italic on
  GUI_DispString("Italic text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_REGULAR_BOLD);         // Bold on
  GUI_DispString("Regular bold italic text\n");
  GUI_ITYPE_SetItalicAngle(&_aFont[i], &_aCS[i], 0);                               // Italic off
  GUI_DispString("Regular bold text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_BOLD);              // Bold off
  //
  // Filled / Unfilled outline output
  //
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_OUTLINED_FILLED);      // Filled outline on
  GUI_DispString("Filled outline\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Filled outline off
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_OUTLINED_UNFILLED);    // Unfilled outline on
  GUI_DispString("Unfilled outline\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Unfilled outline off
  //
  // Embossed / Engraved output
  //
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_EMBOSSED);             // Embossed on
  GUI_DispString("Embossed text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Embossed off
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_ENGRAVED);             // Engraved on
  GUI_DispString("Engraved text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Engraved off
  //
  // Shadow / Glow output
  //
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_SHADOW);               // Shadow on
  GUI_DispString("Shadow text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Shadow off
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_GLOW);                 // Glow on
  GUI_DispString("Glow text\n");
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);            // Glow off
  GUI_Delay(PAGE_DELAY);
}

/*********************************************************************
*
*       _ShowLanguages
*/
static void _ShowLanguages(void) {
  const char Bopomofo_string[]     = { "\nBopomofo: \xe3\x84\x85 \xe3\x84\x86 \xe3\x84\x87 \xe3\x84\x88 \xe3\x84\x89 \xe3\x84\x8a \xe3\x84\x8b \xe3\x84\x8c \xe3\x84\x8d \xe3\x84\x8e \xe3\x84\x8f \xe3\x84\x90 \xe3\x84\x91 \xe3\x84\x92 \xe3\x84\x93\n"                        };
  const char Simplified_Chinese[]  = { "\nSimplified: \xe5\x9f\xba\xe6\x9c\xac\xe4\xb8\x8a\xe8\xae\xa1\xe7\xae\x97\xe6\x9c\xba\xe5\x8f\xaa\xe6\x98\xaf\xe5\xa4\x84\xe7\x90\x86\xe6\x95\xb0\xe5\xad\x97\xe5\xae\x83\xe4\xbb\xac\xe6\x8c\x87\xe5\xae\x9a\n"                        };
  const char Traditional_Chinese[] = { "\nTraditional: \xe9\x80\x99\xe4\xba\x9b\xe7\xb7\xa8\xe7\xa2\xbc\xe7\xb3\xbb\xe7\xb5\xb1\xe4\xb9\x9f\xe6\x9c\x83\xe4\xba\x92\xe7\x9b\xb8\xe8\xa1\x9d\xe7\xaa\x81\xe4\xb9\x9f\xe5\xb0\xb1\xe6\x98\xaf\xe8\xaa\xaa\xe5\x85\xa9\xe7\xa8\xae" };
  int        i;

  GUI_Clear();
  i = 0;
  GUI_ITYPE_GetFamilyName(&_aFont[i], _acFamily, sizeof(_acFamily));
  GUI_ITYPE_GetStyleName(&_aFont[i],  _acStyle,  sizeof(_acStyle));
  GUI_SetFont(&GUI_Font20_1);
  GUI_DispString("     Linked font:  ");
  GUI_DispString(_acFamily);
  GUI_DispString(", ");
  GUI_DispString(_acStyle);
  GUI_DispNextLine();
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  //
  // Show alphabet strings
  //
  GUI_SetFont(&_aFont[i]);
  GUI_DispString("** iType User Defined Linked Font **");
  GUI_UC_SetEncodeUTF8();
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);  // Turn off all effects
  GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_GRAYMAP4);   // Graymap output
  GUI_DispString("\nabcdefghijklmnopqrstuvwxyz\n");
  GUI_DispString("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
  //
  // Show language strings
  //
  GUI_DispString(Bopomofo_string);
  GUI_DispString(Simplified_Chinese);
  GUI_DispString(Traditional_Chinese);
  GUI_UC_SetEncodeNone();

  GUI_Delay(PAGE_DELAY);
}

/*********************************************************************
*
*       _ShowEdgeWeights
*/
static void _ShowEdgeWeights(void) {
  const char * Weight_name[]    = { "\nlight:      ", "\nsemi-light: ", "\nregular:    ", "\nsemi-bold:  ", "\nbold:       " };
  const char   Chinese_string[] = { "\xe5\x9f\xba\xe6\x9c\xac\xe4\xb8\x8a\xe8\xae\xa1\xe7\xae\x97\xe6\x9c\xba\xe5\x8f\xaa\xe6\x98\xaf\xe5\xa4\x84\xe7\x90\x86\xe6\x95\xb0\xe5\xad\x97\xe5\xae\x83\xe4\xbb\xac\xe6\x8c\x87\xe5\xae\x9a\xe4\xb8\x80\xe4\xb8\xaa\n" };
  const char   Weight_order[]   = { 0, 3, 1, 2, 4 };
  int          i;
  int          j;

  GUI_Clear();
  i = 0;
  GUI_ITYPE_GetFamilyName(&_aFont[i], _acFamily, sizeof(_acFamily));
  GUI_ITYPE_GetStyleName(&_aFont[i],  _acStyle,  sizeof(_acStyle));
  GUI_SetFont(&GUI_Font20_1);
  GUI_DispString("     Edge font:  ");
  GUI_DispString(_acFamily);
  GUI_DispString(", ");
  GUI_DispString(_acStyle);
  GUI_DispNextLine();
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  GUI_SetFont(&_aFont[1]);
  GUI_ITYPE_SetOutputStyle(&_aFont[1], &_aCS[1], (long)ITYPE_NO_EFFECT);        // Turn off all effects
  GUI_ITYPE_SetOutputStyle(&_aFont[1], &_aCS[1], (long)ITYPE_GRAYMAP4);         // Edge graymap output
  GUI_DispString("** iType Edge CSM tuning, 5 weights in the same font **");
  for (j = 0; j < 5; j++){
    i = Weight_order[j];
    GUI_SetFont(&_aFont[i]);
    GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_NO_EFFECT);      // Turn off all effects
    GUI_ITYPE_SetOutputStyle(&_aFont[i], &_aCS[i], (long)ITYPE_EDGE_GRAYMAP4);  // Edge graymap output
    GUI_DispNextLine();
    GUI_DispString(Weight_name[j]);
    GUI_UC_SetEncodeUTF8();
    GUI_DispString(Chinese_string);
    GUI_UC_SetEncodeNone();
  }
  GUI_Delay(PAGE_DELAY);
}
/*********************************************************************
*
*       _ShowDynamicCSM
*
*  Function description
*    Shows 5 different weights of the same font by applying dynamic CSM adjustments.
*/
static void _ShowDynamicCSM(void) {
  double Alpha;
  double S0;
  double S1;
  double T0;
  double T1;
  double R;
  int    i;
  int    j;
  int    N;
  
  N = 5;
  GUI_Clear();
  i = 0;
  GUI_ITYPE_GetFamilyName(&_aFont[i], _acFamily, sizeof(_acFamily));
  GUI_ITYPE_GetStyleName(&_aFont[i],  _acStyle,  sizeof(_acStyle));
  GUI_SetFont(&GUI_Font20_1);
  GUI_DispString("     Edge font:  ");
  GUI_DispString(_acFamily);
  GUI_DispString(", ");
  GUI_DispString(_acStyle);
  GUI_DispNextLine();
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  GUI_UC_SetEncodeUTF8();
  GUI_SetFont(&_aFont[0]);
  GUI_ITYPE_SetOutputStyle(&_aFont[0], &_aCS[0], (long)ITYPE_NO_EFFECT);      // Turn off all effects
  GUI_ITYPE_SetOutputStyle(&_aFont[0], &_aCS[0], (long)ITYPE_EDGE_GRAYMAP4);  // Edge graymap output
  GUI_DispString("** iType Dynamic CSM tuning **\n");
  GUI_DispNextLine();
  //  
  // Parameters for adjustments
  //
  R  = 1.4;
  S0 = 0.0;
  S1 = -0.001;
  T0 = 0.01;
  T1 = 0.007;
  //
  // Make 5 sets of adjustments which range from -R to R.
  //
  for (j = 0; j < N; j++){
    Alpha = R * (2 * j / (N - 1) - 1);
    GUI_ITYPE_SetCSMAdjustments(&_aFont[i], &_aCS[i], (FS_FIXED)(Alpha*S0*65536), (FS_FIXED)(Alpha*S1*65536), (FS_FIXED)(Alpha*T0*65536), (FS_FIXED)(Alpha*T1*65536));
    GUI_DispString("\xe5\x9f\xba\xe6\x9c\xac\xe4\xb8\x8a\xe8\xae\xa1\xe7\xae\x97\xe6\x9c\xba\xe5\x8f\xaa\xe6\x98\xaf\xe5\xa4\x84\xe7\x90\x86\xe6\x95\xb0\xe5\xad\x97\xe5\xae\x83\xe4\xbb\xac\xe6\x8c\x87\xe5\xae\x9a\xe4\xb8\x80\xe4\xb8\xaa\n");
  }
  GUI_Delay(PAGE_DELAY);
}

/*********************************************************************
*
*       _CreateFonts
*/
static int _CreateFonts(const U8 * pData, U32 NumBytes) {
  GUI_TTF_DATA TTF_Data;         // Only one GUI_TTF_DATA structure is used per font face
  int          i;

  TTF_Data.pData    = pData;     // Set pointer to file data
  TTF_Data.NumBytes = NumBytes;  // Set size of file
  for (i = 0; i < GUI_COUNTOF(_aHeight); i++) {
    //
    // Initialize GUI_ITYPE_CS members
    //
    _aCS[i].PixelHeight = _aHeight[0];
    _aCS[i].pTTF        = &TTF_Data;
    _aCS[i].FaceIndex   = i;
    //
    // Create GUI font
    //
    if (GUI_ITYPE_CreateFont(&_aFont[i], &_aCS[i])) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _CreateEdgeFonts
*/
static int _CreateEdgeFonts(const U8 * pData, U32 NumBytes) {
  GUI_TTF_DATA TTF_Data;         // Only one GUI_TTF_DATA structure is used per font face
  int          i;

  TTF_Data.pData    = pData;     // Set pointer to file data
  TTF_Data.NumBytes = NumBytes;  // Set size of file
  for (i = 0; i < 5; i++) {
    //
    // Initialize GUI_ITYPE_CS members
    //
    _aCS[i].PixelHeight = _aHeight[0];
    _aCS[i].pTTF        = &TTF_Data;
    _aCS[i].FaceIndex   = i;
    //
    // Create GUI font
    //
    if (GUI_ITYPE_CreateFont(&_aFont[i], &_aCS[i])) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _DeleteFonts
*/
static int _DeleteFonts() {
  int i;

  for (i = 0; i < GUI_COUNTOF(_aHeight); i++) {
    GUI_ITYPE_DeleteFont(&_aCS[i]);
  }
  return 0;
}

/*********************************************************************
*
*       _DeleteEdgeFonts
*/
static int _DeleteEdgeFonts() {
  int i;

  for (i = 0; i < 5; i++) {
    GUI_ITYPE_DeleteFont(&_aCS[i]);
  }
  return 0;
}

/*********************************************************************
*
*       _PageOne
*
* Function description
*   The function uses the given pointer to a true type font for creating
*   a couple of GUI fonts and showing the outline of the TTF font.
*
* Parameters:
*   pData    - Location of font file
*   NumBytes - Size of font file
*/
static void _PageOne(const U8 * pData, U32 NumBytes) {
  if(_CreateFonts(pData, NumBytes)) {      // Create fonts. A return value here means fonts were not created, need to bail
    return;
  }
  _ShowFeatures();                         // Show some text
  _DeleteFonts();
}

/*********************************************************************
*
*       _PageTwo
*/
static void _PageTwo(const U8 * pData, U32 NumBytes) {
  if(_CreateFonts(pData, NumBytes)) {      // Create fonts. A return value here means fonts were not created, need to bail
    return;
  }
  _ShowLanguages();                        // Show some text
  _DeleteFonts();
}

/*********************************************************************
*
*       _PageThree
*/
static void _PageThree(const U8 * pData, U32 NumBytes) {
  if(_CreateEdgeFonts(pData, NumBytes)) {  // Create fonts. A return value here means fonts were not created, need to bail
    return;
  }
  _ShowEdgeWeights();                      // Show some text
  _DeleteEdgeFonts();
}

/*********************************************************************
*
*       _PageFour
*/
static void _PageFour(const U8 * pData, U32 NumBytes) {
  if(_CreateFonts(pData, NumBytes)) {      // Create fonts. A return value here means fonts were not created, need to bail
    return;
  }
  _ShowDynamicCSM();                       // Show some text
  _DeleteFonts();
}

/*********************************************************************
*
*       _CheckPath
*/
static int _CheckPath(const char * sFolder) {
  WIN32_FIND_DATA Context;
  HANDLE          hFind;
  char            acMask[_MAX_PATH];
  int             r;

  r = 1;
  sprintf(acMask, "%s\\*.*", sFolder);
  hFind = FindFirstFile(acMask, &Context);
  if (hFind != INVALID_HANDLE_VALUE) {
    r = 0;
    FindClose(hFind);
  }
  return r;
}

/*********************************************************************
*
*       _IsFontFile
*
* Function description
*   Compare the given file name with the font file extensions
*   stored in _acFontExt.
*/
static U8 _IsFontFile(const char * acFile) {
  const char ** ppExtSupported;
  const char *  pExtFile;
  int           Len;

  //
  // Determine file extension in acFile
  //
  Len = strlen(acFile) - 1;
  pExtFile = &acFile[Len];
  while (*pExtFile != '.') {
    pExtFile--;
    Len--;
    if (Len == 0) {
      return 0;
    }
  }
  pExtFile++;
  //
  // Compare the given file extension with the supported ones.
  //
  ppExtSupported = _acFontExt;
  while (*ppExtSupported) {
    if (strcmp(*ppExtSupported, pExtFile) == 0) {
      return 1;
    }
    ppExtSupported++;
  }
  return 0;
}

/*********************************************************************
*
*       _IterateOverAllFiles
*
* Function description
*   The function iterates over all files of the given folder and the
*   given mask, reads the contents of the file and calls the function
*   pfDoSomething() with location and size of file data.
*   Can be used under Win32 environment only.
*/
static void _IterateOverAllFiles(const char * sFolder, const char * sMask, void (* pfDoSomething)(const U8 * pData, U32 NumBytes)) {
  WIN32_FIND_DATA   Context;
  HANDLE            hFile;
  HANDLE            hFind;
  DWORD             NumBytesRead;
  DWORD             NumBytes;
  BOOL              NextFile;
  char              acFile[_MAX_PATH];
  char              acMask[_MAX_PATH];
  U8              * pData;

  sprintf(acMask, "%s\\%s", sFolder, sMask);
  hFind = FindFirstFile(acMask, &Context);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      sprintf(acFile, "%s\\%s", sFolder, (const char *)&Context.cFileName);
      if (_IsFontFile(acFile) == 0) {
        NextFile = FindNextFile(hFind, &Context);
        if (NextFile) {
          continue;
        } else {
          break;
        }
      }
      hFile = CreateFile(acFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      if (hFile != INVALID_HANDLE_VALUE) {
        NumBytes = GetFileSize(hFile, NULL);
        pData    = (U8 *)malloc(NumBytes);
        ReadFile(hFile, pData, NumBytes, &NumBytesRead, NULL);
        pfDoSomething(pData, NumBytes);
        free(pData);  
      }
      CloseHandle(hFile);
    } while (FindNextFile(hFind, &Context));
    FindClose(hFind);
  }
}

/*********************************************************************
*
*       _GetPathToFontData
*/
static int _GetPathToFontData(char * pPath) {
  char acPath[_MAX_PATH];
  char acDrive[_MAX_PATH];
  char acDir[_MAX_PATH];

  strcpy(pPath, "C:\\Work\\emWin\\ThirdParty\\iType");
  strcpy(acPath, pPath);
  strcat(acPath, "\\FontData\\Standard");
  if (_CheckPath(acPath)) {
    GetModuleFileName(0, pPath, _MAX_PATH);
    _splitpath(pPath, acDrive, acDir, NULL, NULL);
    _makepath(pPath, acDrive, acDir, NULL, NULL);
    *(pPath + strlen(pPath) - 1) = 0;
    strcpy(acPath, pPath);
    strcat(acPath, "\\FontData\\Standard");
    if (_CheckPath(acPath)) {
      MessageBox(0, acPath, "Path not found:", MB_OK);
      return 1;
    }
  }
  return 0;
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
  char acPath[_MAX_PATH];
  char acCpyPath[_MAX_PATH];

  GUI_Init();
  //
  // Set colors and text mode
  //
  GUI_SetBkColor (GUI_WHITE);
  GUI_SetColor   (GUI_BLACK);
  GUI_SetTextMode(GUI_TM_TRANS);
  //
  // Get base path to font data
  //
  if (_GetPathToFontData(acPath) == 0) {
    //
    // Show features
    //
    while (1) {
      //
      // Get the local .\FontData\Standard directory of fonts
      //
      strcpy(acCpyPath, acPath);
      strcat(acCpyPath, "\\FontData\\Standard");
      //
      // Page 1 - iType features
      //
      _IterateOverAllFiles(acCpyPath, "*.*", _PageOne);
      //
      // Page 2 - Linked font
      //
      // Get the local .\FontData\Linked directory of fonts
      //
      strcpy(acCpyPath, acPath);
      strcat(acCpyPath, "\\FontData\\Linked");
      _IterateOverAllFiles(acCpyPath, "*.ltt", _PageTwo);
      //
      // Page 3 - Edge Font
      //
      // Get the local \FontData\Edge directory of fonts
      //
      strcpy(acCpyPath, acPath);
      strcat(acCpyPath, "\\FontData\\Edge");
      _IterateOverAllFiles(acCpyPath, "*.ttc", _PageThree);
      //
      // Page 4 - Dynamic CSM adjustment
      //
      // Get the local \FontData\Edge directory of fonts
      //
      strcpy(acCpyPath, acPath);
      strcat(acCpyPath, "\\FontData\\Edge");
      _IterateOverAllFiles(acCpyPath, "*.ccc", _PageFour);
    }
    GUI_ITYPE_Done();
  }
}

#else

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_Init();
  GUI_DispString("iType not available");
  GUI_Delay(1000);
}

#endif  // #if 0 // Please set to 1 if iType is available

#endif  // #ifndef SKIP_TEST

/*************************** End of file ****************************/
