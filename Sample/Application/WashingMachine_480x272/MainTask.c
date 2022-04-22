#include "DIALOG.h"
#include "Resource.h"

#include <stdio.h>

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const GUI_BITMAP * _apBitmap[] = {
  &bmBkEco_B_480x272,
  &bmBkSynthetic_B_480x272,
  &bmBkCotton_B_480x272,
  &bmBkWoll_B_480x272,
  &bmBkSilk_B_480x272,
  &bmBkSpin_B_480x272
};

static const int _aTimeProg[] = { 150, 105, 135, 80, 70, 15 };
static const int _aTimeAdd[]  = {   0, -30, +15, +30, +15, +10 };

//
// Text to be used in slider layer
//
static const char * _apText0_Single[] = { "Eco Wash", "Synthetics", "Cotton", "Wool", "Silk", "Spin"};
static const char * _apText1_Single[] = { "90\xb0", "60\xb0", "40\xb0", "30\xb0", "COLD" };
static const char * _apText2_Single[] = { "1600", "1400", "1200", "800", "400", "none" };
static const char * _apText3_Single[] = { "None",     "Short",    "Extra Spinning",    "Pre- Washing",    "Extra Rinsing",    "Wrinkle Resistance" };
static const char * _apText4_Single[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
                                          "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                                          "20", "21", "22", "23" };
static const char * _apText5_Single[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
                                          "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                                          "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
                                          "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
                                          "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
                                          "50", "51", "52", "53", "54", "55", "56", "57", "58", "59" };

static int _ProgIndex;
static int _ProgIndexOld;
static int _AddIndex;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AnimateWin
*/
static void _AnimateWinIn(GUI_ANIM_INFO * pInfo, void * pVoid) {
  ANIM_DATA * pData;

  pData = (ANIM_DATA *)pVoid;
  pData->Value = (0xff * pInfo->Pos) / GUI_ANIM_RANGE;
  WM_InvalidateWindow(pData->hWin);
}

/*********************************************************************
*
*       _AnimateWin
*/
static void _AnimateWinOut(GUI_ANIM_INFO * pInfo, void * pVoid) {
  ANIM_DATA * pData;

  pData = (ANIM_DATA *)pVoid;
  pData->Value = 0xff - (0xff * pInfo->Pos) / GUI_ANIM_RANGE;
  WM_InvalidateWindow(pData->hWin);
}

/*********************************************************************
*
*       _AnimateDelete
*/
static void _AnimateDelete(void * pVoid) {
  ANIM_DATA * pData;
  pData = (ANIM_DATA *)pVoid;
  WM_DeleteWindow(pData->hWin);
}

/*********************************************************************
*
*       _AnimateCreate
*/
static void _AnimateCreate(GUI_ANIM_HANDLE * pAnim, ANIM_DATA * pAnimData) {
  //
  // Set up animation for the hint window
  //
  *pAnim = GUI_ANIM_Create(2000, 25, (void *)pAnimData, 0);
  GUI_ANIM_AddItem(*pAnim, 0, 300, ANIM_ACCELDECEL, (void *)pAnimData, _AnimateWinIn);
  GUI_ANIM_AddItem(*pAnim, 1700, 2000, ANIM_ACCELDECEL, (void *)pAnimData, _AnimateWinOut);
  GUI_ANIM_StartEx(*pAnim, 1, _AnimateDelete);
}

/*********************************************************************
*
*       _GetProgramIndex
*/
static int _GetProgramIndex(int y, int ySizeItem) {
  int yPos;
  int Cnt;

  yPos = 0;
  Cnt  = 0;
  while (yPos > y) {
    yPos -= ySizeItem;
    Cnt++;
  }
  return Cnt;
}

/*********************************************************************
*
*       _cbWinProgram
*/
static void _cbWinProgram(WM_MESSAGE * pMsg) {
  int               i;
  GUI_RECT          Rect;
  int               ySpace;
  WM_MOTION_INFO *  pInfo;
  WIN_DATA       *  pWinData;
  const char     ** ppText;
  int               yPos;
  WM_HWIN           hItem;
  int Time;
  char acBuffer[16];

  switch (pMsg->MsgId) {
  case WM_MOTION:
    WM_GetUserData(pMsg->hWin, &pWinData, sizeof(WIN_DATA*));
    pInfo = (WM_MOTION_INFO *)pMsg->Data.p;
    if (pInfo) {
      switch (pInfo->Cmd) {
      case WM_MOTION_INIT:
        WM_GetClientRectEx(pMsg->hWin, &Rect);
        pInfo->SnapY = (Rect.y1 + 1) / pWinData->NumItems;
        pInfo->Overlap = 20;
        break;
      case WM_MOTION_MOVE:
        //
        // Manage selection of the program (background) and the duration
        //
        if (pInfo->FinalMove) {
          //
          // Only two options are important
          //
          if ((pWinData->ppText == _apText0_Single) || (pWinData->ppText == _apText3_Single)) {
            //
            // Get the current position of the window to distinguish which option is selected
            //
            yPos = WM_GetWindowOrgY(pMsg->hWin) - WM_GetWindowOrgY(WM_GetParent(pMsg->hWin));
            WM_GetClientRectEx(pMsg->hWin, &Rect);
            if (pWinData->ppText == _apText0_Single) {
              //
              // Get program index
              //
              _ProgIndex  = _GetProgramIndex(yPos, (Rect.y1 + 1) / pWinData->NumItems);
            } else if (pWinData->ppText == _apText3_Single){
              //
              // Get time index
              //
              _AddIndex  = _GetProgramIndex(yPos, (Rect.y1 + 1) / pWinData->NumItems);
            }
            //
            // Calculate standard duration for the given program
            //
            Time = _aTimeProg[_ProgIndex];
            //
            // Depending on the extra option add or substract some minutes
            //
            if (_AddIndex == 1) {
              if (Time > 15) {
                Time += _aTimeAdd[_AddIndex];
              }
            } else {
              Time += _aTimeAdd[_AddIndex];
            }
            //
            // Fill buffer and set new TEXT text
            //
            sprintf(acBuffer, "%ih %imin", Time / 60, Time % 60);
            hItem = WM_GetDialogItem(WM_GetParent(pMsg->hWin), GUI_ID_TEXT0);
            TEXT_SetText(hItem, acBuffer);
            WM_InvalidateWindow(hItem);
            //
            // If the program index has changed redraw the bk window
            //
            if (_ProgIndexOld != _ProgIndex) {
              WM_InvalidateWindow(WM_HBKWIN);
            }
            //
            // Remember old index
            //
            _ProgIndexOld = _ProgIndex;
          }
        }
        break;
      }
    }
    break;
  case WM_PAINT:
    //
    // Fill the settings window with content
    //
    // Get user data and set some text properties
    //
    WM_GetUserData(pMsg->hWin, &pWinData, sizeof(WIN_DATA*));
    GUI_SetFont(FONT_SELECTION);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(COLOR_GREEN);
    //
    // Get a rectangle of this window
    //
    WM_GetClientRect(&Rect);
    //
    // Get size of the parent, only one item should be visible at once
    //
    ySpace  = WM_GetWindowSizeY(WM_GetParent(pMsg->hWin));
    //
    // Adapt the bottom of the rect
    //
    Rect.y1 = ySpace;
    //
    // Get pointer to the text
    //
    ppText  = pWinData->ppText;
    //
    // Draw each string into a rect and modify the rect
    //
    for (i = 0; i < pWinData->NumItems; i++) {
      GUI_DispStringInRectWrap(*ppText, &Rect, pWinData->Align, GUI_WRAPMODE_WORD);;
      ppText++;
      Rect.y0 = Rect.y1;
      Rect.y1 += ySpace;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbWinText
*/
static void _cbWinText(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Tell the user what the different settings are for
    //
    GUI_SetFont(FONT_DESCRIPTION);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(COLOR_BLUE);
    //
    Rect.x0 = WIN0_XPOS;
    Rect.y0 = 0;
    Rect.x1 = Rect.x0 + WIN0_XSIZE;
    Rect.y1 = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringInRect("Program", &Rect, GUI_TA_LEFT | GUI_TA_TOP);
    //
    Rect.x0 = WIN1_XPOS;
    Rect.y0 = 0;
    Rect.x1 = Rect.x0 + WIN1_XSIZE;
    GUI_DispStringInRect("Temp.", &Rect, GUI_TA_LEFT | GUI_TA_TOP);
    //
    Rect.x0 = WIN2_XPOS;
    Rect.y0 = 0;
    Rect.x1 = Rect.x0 + WIN2_XSIZE;
    GUI_DispStringInRect("U/min", &Rect, GUI_TA_LEFT | GUI_TA_TOP);
    //
    Rect.x0 = WIN3_XPOS;
    Rect.y0 = 0;
    Rect.x1 = Rect.x0 + WIN3_XSIZE;
    GUI_DispStringInRect("Options", &Rect, GUI_TA_LEFT | GUI_TA_TOP);
    //
    Rect.x0 = WIN4_XPOS;
    Rect.y0 = 0;
    Rect.x1 = Rect.x0 + WIN4_XSIZE;
    GUI_DispStringInRect("Start", &Rect, GUI_TA_LEFT | GUI_TA_TOP);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbScrollWin
*/
static void _cbScrollWin(WM_MESSAGE * pMsg) {
  static WIN_DATA    aWinData[6];
  static WIN_DATA  * apWinData[6];
  int                ySize;
  WM_HWIN            hItem;

  switch (pMsg->MsgId) {
  case WM_CREATE:
    //
    // Set pointer to animation data. apWinData gets passend to WM_SetUserData()
    //
    apWinData[0] = &aWinData[0];
    apWinData[1] = &aWinData[1];
    apWinData[2] = &aWinData[2];
    apWinData[3] = &aWinData[3];
    apWinData[4] = &aWinData[4];
    apWinData[5] = &aWinData[5];
    //
    // Create windows for selecting washing machine setting
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText0_Single);
    aWinData[0].hWin     = WM_CreateWindowAsChild(WIN0_XPOS, 0,  WIN0_XSIZE, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[0].NumItems = GUI_COUNTOF(_apText0_Single);
    aWinData[0].ppText   = _apText0_Single;
    aWinData[0].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[0].hWin, &apWinData[0], sizeof(WIN_DATA *));
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText1_Single);
    aWinData[1].hWin     = WM_CreateWindowAsChild(WIN1_XPOS, 0,  WIN1_XSIZE, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[1].NumItems = GUI_COUNTOF(_apText1_Single);
    aWinData[1].ppText   = _apText1_Single;
    aWinData[1].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[1].hWin, &apWinData[1], sizeof(WIN_DATA *));
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText2_Single);
    aWinData[2].hWin     = WM_CreateWindowAsChild(WIN2_XPOS, 0,  WIN2_XSIZE, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[2].NumItems = GUI_COUNTOF(_apText2_Single);
    aWinData[2].ppText   = _apText2_Single;
    aWinData[2].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[2].hWin, &apWinData[2], sizeof(WIN_DATA *));
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText3_Single);
    aWinData[3].hWin     = WM_CreateWindowAsChild(WIN3_XPOS, 0,  WIN3_XSIZE, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[3].NumItems = GUI_COUNTOF(_apText3_Single);
    aWinData[3].ppText   = _apText3_Single;
    aWinData[3].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[3].hWin, &apWinData[3], sizeof(WIN_DATA *));
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText4_Single);
    aWinData[4].hWin     = WM_CreateWindowAsChild(WIN4_XPOS, -DEFAULT_HOUR * WM_GetWindowSizeY(pMsg->hWin),  WIN4_XSIZE / 2 - 2, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[4].NumItems = GUI_COUNTOF(_apText4_Single);
    aWinData[4].ppText   = _apText4_Single;
    aWinData[4].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[4].hWin, &apWinData[4], sizeof(WIN_DATA *));
    //
    ySize                = WM_GetWindowSizeY(pMsg->hWin) * GUI_COUNTOF(_apText5_Single);
    aWinData[5].hWin     = WM_CreateWindowAsChild(WIN4_XPOS + WIN4_XSIZE / 2 + 2, -DEFAULT_MIN * WM_GetWindowSizeY(pMsg->hWin),  WIN4_XSIZE / 2, ySize, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_MOTION_Y, _cbWinProgram, sizeof(WIN_DATA *));
    aWinData[5].NumItems = GUI_COUNTOF(_apText5_Single);
    aWinData[5].ppText   = _apText5_Single;
    aWinData[5].Align    = GUI_TA_LEFT | GUI_TA_VCENTER;
    WM_SetUserData(aWinData[5].hWin, &apWinData[5], sizeof(WIN_DATA *));
    //
    // Create a window which displays a description of the different settings
    //
    WM_CreateWindowAsChild(0, 0, WM_GetWindowSizeX(pMsg->hWin), WIN_DESCR_YSIZE, pMsg->hWin, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, _cbWinText, 0);
    //
    // Create a TEXT widget to show the duration of the currently selected program and extra options
    //
    hItem = TEXT_CreateEx(WIN4_XPOS, WM_GetWindowSizeY(pMsg->hWin) - TEXT_YSIZE, TEXT_XSIZE, TEXT_YSIZE, pMsg->hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, GUI_ID_TEXT0, "2h 30min");
    TEXT_SetFont     (hItem, FONT_DESCRIPTION);
    TEXT_SetTextColor(hItem, COLOR_BLUE);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);

    break;
  case WM_PAINT:
    //
    // This window is completely transparent except the colon between the two time settings
    //
    GUI_SetFont(FONT_SELECTION);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(COLOR_GREEN);
    GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_DispStringAt(":", WIN4_XPOS + WIN4_XSIZE / 2 - 6, WM_GetWindowSizeY(pMsg->hWin) / 2 - 1);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbButton
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  int                      xPos;
  int                      yPos;
  int                      xSize;
  int                      ySize;
  GUI_RECT                 Rect;
  static GUI_MEMDEV_Handle hMem;

  switch (pMsg->MsgId) {
  case WM_SET_CALLBACK:
    //
    // On setting a callback to this button, create a memdev and fill it.
    //
    xSize = WM_GetWindowSizeX(pMsg->hWin);
    ySize = WM_GetWindowSizeY(pMsg->hWin);
    Rect.x0 = 0;
    Rect.y0 = 0;
    Rect.x1 = xSize - 1;
    Rect.y1 = ySize - 1;
    hMem = GUI_MEMDEV_CreateFixed32(0, 0, xSize, ySize);
    GUI_MEMDEV_Select(hMem);
    GUI_SetBkColor(GUI_TRANSPARENT);
    GUI_Clear();
    GUI_SetColor(COLOR_RED);
    GUI_AA_FillRoundedRectEx(&Rect, 5);
    GUI_SetFont(FONT_DESCRIPTION);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(COLOR_WHITE);
    GUI_DispStringInRect("Start", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_MEMDEV_Select(0);
    break;
  case WM_PAINT:
    //
    // Draw the memdev on the porition of this button
    //
    xPos = WM_GetWindowOrgX(pMsg->hWin);
    yPos = WM_GetWindowOrgY(pMsg->hWin);
    GUI_MEMDEV_WriteAt(hMem, xPos, yPos);
    break;
  default:
    BUTTON_Callback(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbWinStart
*/
static void _cbWinStart(WM_MESSAGE * pMsg) {
  GUI_RECT               Rect;
  static GUI_ANIM_HANDLE hAnim;
  static ANIM_DATA       AnimData;

  switch (pMsg->MsgId) {
  case WM_CREATE:
    //
    // On creation start animation. It makes the window visible, invisible again
    // and deletes the window after the animation has been finished.
    //
    AnimData.Value = 0;
    AnimData.hWin  = pMsg->hWin;
    _AnimateCreate(&hAnim, &AnimData);
    break;
  case WM_PAINT:
    //
    // Fill window and draw text with the given alpha value (gets calculated by animation)
    //
    GUI_EnableAlpha(1);
    GUI_SetAlpha(AnimData.Value);
    GUI_SetBkColor(COLOR_GREEN);
    GUI_Clear();
    GUI_SetFont(FONT_DESCRIPTION);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(COLOR_WHITE);
    WM_GetClientRect(&Rect);
    GUI_DispStringInRect("Please note that this demo can not wash your clothes.", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_SetAlpha(0xff);  // Restore default alpha
    GUI_EnableAlpha(0);  // Disable alpha calculation
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  int Id;
  int NCode;
  static WM_HWIN hWinStart;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Draw a bitmap with the given index into the background
    //
    GUI_DrawBitmap(_apBitmap[_ProgIndex], 0, 0);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (Id) {
    case GUI_ID_BUTTON0:
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        if (WM_IsWindow(hWinStart) == 0) {
          //
          // On release create a window to show a hint (only if not already present)
          //
          hWinStart = WM_CreateWindowAsChild(0, LCD_GetYSize() - WIN_START_YSIZE, LCD_GetXSize(), WIN_START_YSIZE, pMsg->hWin, WM_CF_SHOW, _cbWinStart, 0);
        }
        break;
      }
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
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
  int xPos, yPos;
  int xSize, ySize;
  WM_HWIN hItem;

  GUI_Init();
  //
  // Configure window manager
  //
  WM_MOTION_Enable(1);
  WM_MULTIBUF_Enable(1);
  //
  // Set a callback function for the background window
  //
  WM_SetCallback(WM_HBKWIN, _cbBk);
  //
  // Calculate positions
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  xPos  = (xSize - WIN_BAR_XSIZE) / 2;
  yPos  = (ySize - WIN_BAR_YSIZE) / 2;
  //
  // Create a window as parent for the different washing machine settings
  //
  WM_CreateWindowAsChild(xPos, yPos, WIN_BAR_XSIZE, WIN_BAR_YSIZE, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, _cbScrollWin, 0);
  //
  // Create button to start the washing machine
  //
  hItem = BUTTON_CreateUser(xPos + WIN_BAR_XSIZE - 4 - BUTTON_XSIZE, yPos + WIN_BAR_YSIZE + 10, BUTTON_XSIZE, BUTTON_YSIZE, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON0, WM_CF_SHOW | WM_CF_STAYONTOP);
  // Set callback for button
  WM_SetCallback(hItem, _cbButton);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
