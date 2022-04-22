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
* Source file: Icon_emUSBH_64x64                                     *
* Dimensions:  64 * 64                                               *
* NumColors:   142                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_emUSBH_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_emUSBH_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x001C1718, 0x00A95C00,
  0x00FAFAFA, 0x001B1D1D, 0x00D1A877, 0x00F9F4EE,
  0x00C28B49, 0x00E2C7A8, 0x002A2C2C, 0x00393B3B,
  0x00B77629, 0x00A95D01, 0x00BC8039, 0x00F0F0F0,
  0x001F1A1B, 0x00585959, 0x00858686, 0x00C2C3C3,
  0x00FBFBFB, 0x001C1E1E, 0x00494A4A, 0x00C18947,
  0x00F3F2F2, 0x00F4F4F4, 0x00FAF6F1, 0x00FDFDFD,
  0x001D1414, 0x00272223, 0x00B2B3B3, 0x001D1819,
  0x00202222, 0x00262828, 0x00272929, 0x00292B2B,
  0x00393A3A, 0x00484949, 0x00B7772B, 0x00838484,
  0x008C8D8D, 0x009FA0A0, 0x00A6A6A6, 0x00B3B4B4,
  0x00E6CFB4, 0x00DEDEDE, 0x00E1E1E1, 0x00E1E2E2,
  0x00F5F5F5, 0x00F7F7F7, 0x00F9F9F9, 0x00FCFCFC,
  0x00FEFDFC, 0x00FEFEFE, 0x001D1F1F, 0x001E2020,
  0x001F2121, 0x00212323, 0x00252021, 0x00222424,
  0x00232525, 0x00282929, 0x00302B2C, 0x00322D2F,
  0x00303131, 0x00303232, 0x00313333, 0x00373233,
  0x00323434, 0x00343636, 0x00353737, 0x00383334,
  0x003A313A, 0x00373838, 0x003C3E3E, 0x003F4040,
  0x00414242, 0x00414343, 0x00424444, 0x00474848,
  0x00494B4B, 0x00525353, 0x00525454, 0x00565757,
  0x005A5C5C, 0x005E5F5F, 0x00606161, 0x00636464,
  0x00686969, 0x00696A6A, 0x006C6E6E, 0x006D6F6F,
  0x00707171, 0x00767777, 0x007C7D7D, 0x00AC6209,
  0x00B57223, 0x00807D7E, 0x00BC8038, 0x00C18A48,
  0x00C9995F, 0x00CFA471, 0x00D3AC7D, 0x00838081,
  0x00858283, 0x00868384, 0x00878888, 0x008B8C8C,
  0x008D8E8E, 0x008F9090, 0x00939494, 0x00959696,
  0x009B9C9C, 0x009C9D9D, 0x009D9E9E, 0x00A5A5A5,
  0x00AFB0B0, 0x00B6B6B6, 0x00B8B9B9, 0x00BCBDBD,
  0x00C0C1C1, 0x00C4C5C5, 0x00C8C9C9, 0x00C9CACA,
  0x00CACBCB, 0x00D1D2D2, 0x00D3D4D4, 0x00D4D4D4,
  0x00D6D6D6, 0x00D9D9D9, 0x00DADBDB, 0x00DCDCDC,
  0x00DFDFDF, 0x00EAD7C1, 0x00F3E8DB, 0x00E4E4E4,
  0x00E6E6E6, 0x00EAEBEB, 0x00ECECEC, 0x00EDEDED,
  0x00FCF9F6, 0x00FEFCFB
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF18171C, 0xFF005CA9,
  0xFFFAFAFA, 0xFF1D1D1B, 0xFF77A8D1, 0xFFEEF4F9,
  0xFF498BC2, 0xFFA8C7E2, 0xFF2C2C2A, 0xFF3B3B39,
  0xFF2976B7, 0xFF015DA9, 0xFF3980BC, 0xFFF0F0F0,
  0xFF1B1A1F, 0xFF595958, 0xFF868685, 0xFFC3C3C2,
  0xFFFBFBFB, 0xFF1E1E1C, 0xFF4A4A49, 0xFF4789C1,
  0xFFF2F2F3, 0xFFF4F4F4, 0xFFF1F6FA, 0xFFFDFDFD,
  0xFF14141D, 0xFF232227, 0xFFB3B3B2, 0xFF19181D,
  0xFF222220, 0xFF282826, 0xFF292927, 0xFF2B2B29,
  0xFF3A3A39, 0xFF494948, 0xFF2B77B7, 0xFF848483,
  0xFF8D8D8C, 0xFFA0A09F, 0xFFA6A6A6, 0xFFB4B4B3,
  0xFFB4CFE6, 0xFFDEDEDE, 0xFFE1E1E1, 0xFFE2E2E1,
  0xFFF5F5F5, 0xFFF7F7F7, 0xFFF9F9F9, 0xFFFCFCFC,
  0xFFFCFDFE, 0xFFFEFEFE, 0xFF1F1F1D, 0xFF20201E,
  0xFF21211F, 0xFF232321, 0xFF212025, 0xFF242422,
  0xFF252523, 0xFF292928, 0xFF2C2B30, 0xFF2F2D32,
  0xFF313130, 0xFF323230, 0xFF333331, 0xFF333237,
  0xFF343432, 0xFF363634, 0xFF373735, 0xFF343338,
  0xFF3A313A, 0xFF383837, 0xFF3E3E3C, 0xFF40403F,
  0xFF424241, 0xFF434341, 0xFF444442, 0xFF484847,
  0xFF4B4B49, 0xFF535352, 0xFF545452, 0xFF575756,
  0xFF5C5C5A, 0xFF5F5F5E, 0xFF616160, 0xFF646463,
  0xFF696968, 0xFF6A6A69, 0xFF6E6E6C, 0xFF6F6F6D,
  0xFF717170, 0xFF777776, 0xFF7D7D7C, 0xFF0962AC,
  0xFF2372B5, 0xFF7E7D80, 0xFF3880BC, 0xFF488AC1,
  0xFF5F99C9, 0xFF71A4CF, 0xFF7DACD3, 0xFF818083,
  0xFF838285, 0xFF848386, 0xFF888887, 0xFF8C8C8B,
  0xFF8E8E8D, 0xFF90908F, 0xFF949493, 0xFF969695,
  0xFF9C9C9B, 0xFF9D9D9C, 0xFF9E9E9D, 0xFFA5A5A5,
  0xFFB0B0AF, 0xFFB6B6B6, 0xFFB9B9B8, 0xFFBDBDBC,
  0xFFC1C1C0, 0xFFC5C5C4, 0xFFC9C9C8, 0xFFCACAC9,
  0xFFCBCBCA, 0xFFD2D2D1, 0xFFD4D4D3, 0xFFD4D4D4,
  0xFFD6D6D6, 0xFFD9D9D9, 0xFFDBDBDA, 0xFFDCDCDC,
  0xFFDFDFDF, 0xFFC1D7EA, 0xFFDBE8F3, 0xFFE4E4E4,
  0xFFE6E6E6, 0xFFEBEBEA, 0xFFECECEC, 0xFFEDEDED,
  0xFFF6F9FC, 0xFFFBFCFE
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_emUSBH_64x64 = {
  142,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_emUSBH_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_emUSBH_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x48, 0x47, 0x10, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x02, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x10, 0x43, 0x1C, 0x3F, 0x69, 0x30, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x19, 0x68, 0x1D, 0x10, 0x18, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x18, 0x1F, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,003 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,003 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,004 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,004 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,005 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,005 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,006 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,006 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,007 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,007 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 032 Pixels @ 002,008 */ 32, 0x01, 
  /* ABS: 004 Pixels @ 034,008 */ 0, 4, 0x31, 0x2A, 0x6F, 0x2E, 
  /* RLE: 024 Pixels @ 038,008 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,008 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 031 Pixels @ 002,009 */ 31, 0x01, 
  /* ABS: 006 Pixels @ 033,009 */ 0, 6, 0x35, 0x11, 0x05, 0x05, 0x21, 0x83, 
  /* RLE: 023 Pixels @ 039,009 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,009 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 024 Pixels @ 002,010 */ 24, 0x01, 
  /* ABS: 003 Pixels @ 026,010 */ 0, 3, 0x88, 0x11, 0x39, 
  /* RLE: 009 Pixels @ 029,010 */ 9, 0x05, 
  /* RLE: 001 Pixels @ 038,010 */ 1, 0x6A, 
  /* RLE: 023 Pixels @ 039,010 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,010 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 023 Pixels @ 002,011 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 025,011 */ 0, 4, 0x0F, 0x4D, 0x05, 0x49, 
  /* RLE: 004 Pixels @ 029,011 */ 4, 0x16, 
  /* ABS: 006 Pixels @ 033,011 */ 0, 6, 0x25, 0x15, 0x05, 0x05, 0x05, 0x6E, 
  /* RLE: 023 Pixels @ 039,011 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,011 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 022 Pixels @ 002,012 */ 22, 0x01, 
  /* ABS: 005 Pixels @ 024,012 */ 0, 5, 0x31, 0x51, 0x05, 0x5B, 0x1B, 
  /* RLE: 005 Pixels @ 029,012 */ 5, 0x01, 
  /* ABS: 005 Pixels @ 034,012 */ 0, 5, 0x12, 0x05, 0x05, 0x4E, 0x0F, 
  /* RLE: 023 Pixels @ 039,012 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,012 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 021 Pixels @ 002,013 */ 21, 0x01, 
  /* ABS: 005 Pixels @ 023,013 */ 0, 5, 0x33, 0x57, 0x05, 0x54, 0x14, 
  /* RLE: 007 Pixels @ 028,013 */ 7, 0x01, 
  /* ABS: 003 Pixels @ 035,013 */ 0, 3, 0x82, 0x7C, 0x32, 
  /* RLE: 024 Pixels @ 038,013 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,013 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 021 Pixels @ 002,014 */ 21, 0x01, 
  /* ABS: 004 Pixels @ 023,014 */ 0, 4, 0x5E, 0x05, 0x50, 0x19, 
  /* RLE: 035 Pixels @ 027,014 */ 35, 0x01, 
  /* ABS: 004 Pixels @ 062,014 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 008 Pixels @ 002,015 */ 8, 0x01, 
  /* ABS: 005 Pixels @ 010,015 */ 0, 5, 0x77, 0x58, 0x55, 0x28, 0x8B, 
  /* RLE: 007 Pixels @ 015,015 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 022,015 */ 0, 4, 0x28, 0x05, 0x4A, 0x8A, 
  /* RLE: 036 Pixels @ 026,015 */ 36, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 007 Pixels @ 002,016 */ 7, 0x01, 
  /* RLE: 001 Pixels @ 009,016 */ 1, 0x27, 
  /* RLE: 004 Pixels @ 010,016 */ 4, 0x05, 
  /* ABS: 002 Pixels @ 014,016 */ 0, 2, 0x41, 0x2D, 
  /* RLE: 005 Pixels @ 016,016 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 021,016 */ 0, 4, 0x29, 0x05, 0x42, 0x2F, 
  /* RLE: 025 Pixels @ 025,016 */ 25, 0x01, 
  /* ABS: 003 Pixels @ 050,016 */ 0, 3, 0x33, 0x2A, 0x1B, 
  /* RLE: 009 Pixels @ 053,016 */ 9, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 006 Pixels @ 002,017 */ 6, 0x01, 
  /* ABS: 002 Pixels @ 008,017 */ 0, 2, 0x79, 0x15, 
  /* RLE: 005 Pixels @ 010,017 */ 5, 0x05, 
  /* ABS: 009 Pixels @ 015,017 */ 0, 9, 0x53, 0x01, 0x01, 0x01, 0x1B, 0x71, 0x15, 0x3D, 0x7F, 
  /* RLE: 026 Pixels @ 024,017 */ 26, 0x01, 
  /* ABS: 004 Pixels @ 050,017 */ 0, 4, 0x14, 0x05, 0x25, 0x7A, 
  /* RLE: 008 Pixels @ 054,017 */ 8, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 006 Pixels @ 002,018 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,018 */ 1, 0x5D, 
  /* RLE: 007 Pixels @ 009,018 */ 7, 0x05, 
  /* ABS: 007 Pixels @ 016,018 */ 0, 7, 0x0B, 0x44, 0x0A, 0x3B, 0x05, 0x05, 0x22, 
  /* RLE: 027 Pixels @ 023,018 */ 27, 0x0B, 
  /* ABS: 006 Pixels @ 050,018 */ 0, 6, 0x24, 0x05, 0x05, 0x15, 0x59, 0x87, 
  /* RLE: 006 Pixels @ 056,018 */ 6, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 006 Pixels @ 002,019 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,019 */ 1, 0x5A, 
  /* RLE: 007 Pixels @ 009,019 */ 7, 0x05, 
  /* RLE: 001 Pixels @ 016,019 */ 1, 0x23, 
  /* RLE: 009 Pixels @ 017,019 */ 9, 0x0A, 
  /* RLE: 001 Pixels @ 026,019 */ 1, 0x38, 
  /* RLE: 004 Pixels @ 027,019 */ 4, 0x05, 
  /* RLE: 001 Pixels @ 031,019 */ 1, 0x23, 
  /* RLE: 019 Pixels @ 032,019 */ 19, 0x0A, 
  /* RLE: 003 Pixels @ 051,019 */ 3, 0x05, 
  /* ABS: 002 Pixels @ 054,019 */ 0, 2, 0x56, 0x2D, 
  /* RLE: 006 Pixels @ 056,019 */ 6, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 006 Pixels @ 002,020 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,020 */ 1, 0x29, 
  /* RLE: 006 Pixels @ 009,020 */ 6, 0x05, 
  /* ABS: 002 Pixels @ 015,020 */ 0, 2, 0x24, 0x1B, 
  /* RLE: 010 Pixels @ 017,020 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 027,020 */ 0, 5, 0x35, 0x7E, 0x46, 0x05, 0x27, 
  /* RLE: 018 Pixels @ 032,020 */ 18, 0x01, 
  /* ABS: 004 Pixels @ 050,020 */ 0, 4, 0x14, 0x05, 0x4C, 0x78, 
  /* RLE: 008 Pixels @ 054,020 */ 8, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 006 Pixels @ 002,021 */ 6, 0x01, 
  /* ABS: 002 Pixels @ 008,021 */ 0, 2, 0x14, 0x4F, 
  /* RLE: 004 Pixels @ 010,021 */ 4, 0x05, 
  /* ABS: 002 Pixels @ 014,021 */ 0, 2, 0x15, 0x1E, 
  /* RLE: 013 Pixels @ 016,021 */ 13, 0x01, 
  /* ABS: 004 Pixels @ 029,021 */ 0, 4, 0x2F, 0x45, 0x05, 0x70, 
  /* RLE: 017 Pixels @ 033,021 */ 17, 0x01, 
  /* ABS: 003 Pixels @ 050,021 */ 0, 3, 0x14, 0x72, 0x14, 
  /* RLE: 009 Pixels @ 053,021 */ 9, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 007 Pixels @ 002,022 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,022 */ 0, 6, 0x0F, 0x5C, 0x20, 0x05, 0x4B, 0x75, 
  /* RLE: 015 Pixels @ 015,022 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 030,022 */ 0, 4, 0x81, 0x0A, 0x36, 0x74, 
  /* RLE: 028 Pixels @ 034,022 */ 28, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 009 Pixels @ 002,023 */ 9, 0x01, 
  /* ABS: 002 Pixels @ 011,023 */ 0, 2, 0x32, 0x30, 
  /* RLE: 018 Pixels @ 013,023 */ 18, 0x01, 
  /* ABS: 004 Pixels @ 031,023 */ 0, 4, 0x7B, 0x3C, 0x20, 0x13, 
  /* RLE: 027 Pixels @ 035,023 */ 27, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 030 Pixels @ 002,024 */ 30, 0x01, 
  /* ABS: 004 Pixels @ 032,024 */ 0, 4, 0x76, 0x37, 0x22, 0x7D, 
  /* RLE: 006 Pixels @ 036,024 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 042,024 */ 1, 0x2E, 
  /* RLE: 004 Pixels @ 043,024 */ 4, 0x13, 
  /* RLE: 001 Pixels @ 047,024 */ 1, 0x89, 
  /* RLE: 014 Pixels @ 048,024 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 031 Pixels @ 002,025 */ 31, 0x01, 
  /* ABS: 004 Pixels @ 033,025 */ 0, 4, 0x73, 0x05, 0x40, 0x84, 
  /* RLE: 005 Pixels @ 037,025 */ 5, 0x01, 
  /* RLE: 001 Pixels @ 042,025 */ 1, 0x6C, 
  /* RLE: 004 Pixels @ 043,025 */ 4, 0x05, 
  /* RLE: 001 Pixels @ 047,025 */ 1, 0x2B, 
  /* RLE: 014 Pixels @ 048,025 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 032 Pixels @ 002,026 */ 32, 0x01, 
  /* ABS: 004 Pixels @ 034,026 */ 0, 4, 0x6D, 0x05, 0x0A, 0x52, 
  /* RLE: 004 Pixels @ 038,026 */ 4, 0x11, 
  /* RLE: 001 Pixels @ 042,026 */ 1, 0x0B, 
  /* RLE: 004 Pixels @ 043,026 */ 4, 0x05, 
  /* RLE: 001 Pixels @ 047,026 */ 1, 0x2B, 
  /* RLE: 014 Pixels @ 048,026 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 033 Pixels @ 002,027 */ 33, 0x01, 
  /* ABS: 002 Pixels @ 035,027 */ 0, 2, 0x6B, 0x21, 
  /* RLE: 010 Pixels @ 037,027 */ 10, 0x05, 
  /* RLE: 001 Pixels @ 047,027 */ 1, 0x1E, 
  /* RLE: 014 Pixels @ 048,027 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 035 Pixels @ 002,028 */ 35, 0x01, 
  /* RLE: 005 Pixels @ 037,028 */ 5, 0x0F, 
  /* RLE: 001 Pixels @ 042,028 */ 1, 0x12, 
  /* RLE: 004 Pixels @ 043,028 */ 4, 0x05, 
  /* RLE: 001 Pixels @ 047,028 */ 1, 0x1E, 
  /* RLE: 014 Pixels @ 048,028 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 040 Pixels @ 002,029 */ 40, 0x01, 
  /* RLE: 001 Pixels @ 042,029 */ 1, 0x13, 
  /* RLE: 004 Pixels @ 043,029 */ 4, 0x12, 
  /* RLE: 001 Pixels @ 047,029 */ 1, 0x80, 
  /* RLE: 014 Pixels @ 048,029 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,030 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,031 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,032 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,033 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,034 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,035 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,036 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,037 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,038 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,039 */ 5, 0x01, 
  /* RLE: 001 Pixels @ 007,039 */ 1, 0x34, 
  /* RLE: 048 Pixels @ 008,039 */ 48, 0x07, 
  /* RLE: 001 Pixels @ 056,039 */ 1, 0x34, 
  /* RLE: 005 Pixels @ 057,039 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,039 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,040 */ 5, 0x01, 
  /* RLE: 001 Pixels @ 007,040 */ 1, 0x17, 
  /* RLE: 048 Pixels @ 008,040 */ 48, 0x03, 
  /* RLE: 001 Pixels @ 056,040 */ 1, 0x63, 
  /* RLE: 005 Pixels @ 057,040 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,040 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,041 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,041 */ 0, 3, 0x0C, 0x5F, 0x65, 
  /* RLE: 044 Pixels @ 010,041 */ 44, 0x06, 
  /* ABS: 003 Pixels @ 054,041 */ 0, 3, 0x64, 0x03, 0x0C, 
  /* RLE: 005 Pixels @ 057,041 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,041 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,042 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,042 */ 0, 2, 0x0C, 0x62, 
  /* RLE: 046 Pixels @ 009,042 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,042 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,042 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,042 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,043 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,043 */ 0, 2, 0x0C, 0x0E, 
  /* RLE: 046 Pixels @ 009,043 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,043 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,043 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,043 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,044 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,044 */ 0, 2, 0x0C, 0x0E, 
  /* RLE: 046 Pixels @ 009,044 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,044 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,044 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,044 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,045 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,045 */ 0, 2, 0x0C, 0x0E, 
  /* RLE: 046 Pixels @ 009,045 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,045 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,045 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,045 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,046 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,046 */ 0, 2, 0x0C, 0x0E, 
  /* RLE: 046 Pixels @ 009,046 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,046 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,046 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,046 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,047 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 007,047 */ 0, 2, 0x0C, 0x0E, 
  /* RLE: 046 Pixels @ 009,047 */ 46, 0x01, 
  /* ABS: 002 Pixels @ 055,047 */ 0, 2, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,047 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,047 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,048 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,048 */ 0, 3, 0x0C, 0x0E, 0x8D, 
  /* RLE: 043 Pixels @ 010,048 */ 43, 0x09, 
  /* ABS: 004 Pixels @ 053,048 */ 0, 4, 0x85, 0x01, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,048 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,048 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,049 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,049 */ 0, 3, 0x0C, 0x0E, 0x1A, 
  /* RLE: 043 Pixels @ 010,049 */ 43, 0x03, 
  /* ABS: 004 Pixels @ 053,049 */ 0, 4, 0x17, 0x01, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,049 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,049 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,050 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,050 */ 0, 3, 0x0C, 0x0E, 0x1A, 
  /* RLE: 043 Pixels @ 010,050 */ 43, 0x03, 
  /* ABS: 004 Pixels @ 053,050 */ 0, 4, 0x17, 0x01, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,050 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,050 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,051 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,051 */ 0, 3, 0x0C, 0x0E, 0x1A, 
  /* RLE: 043 Pixels @ 010,051 */ 43, 0x03, 
  /* ABS: 004 Pixels @ 053,051 */ 0, 4, 0x17, 0x01, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,051 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,051 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,052 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,052 */ 0, 3, 0x0C, 0x0E, 0x8C, 
  /* RLE: 043 Pixels @ 010,052 */ 43, 0x08, 
  /* ABS: 004 Pixels @ 053,052 */ 0, 4, 0x66, 0x01, 0x0D, 0x0C, 
  /* RLE: 005 Pixels @ 057,052 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,052 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,053 */ 5, 0x01, 
  /* ABS: 003 Pixels @ 007,053 */ 0, 3, 0x0C, 0x60, 0x1A, 
  /* RLE: 044 Pixels @ 010,053 */ 44, 0x01, 
  /* ABS: 003 Pixels @ 054,053 */ 0, 3, 0x86, 0x03, 0x0C, 
  /* RLE: 005 Pixels @ 057,053 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,053 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,054 */ 5, 0x01, 
  /* RLE: 001 Pixels @ 007,054 */ 1, 0x26, 
  /* RLE: 048 Pixels @ 008,054 */ 48, 0x03, 
  /* RLE: 001 Pixels @ 056,054 */ 1, 0x26, 
  /* RLE: 005 Pixels @ 057,054 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,054 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 005 Pixels @ 002,055 */ 5, 0x01, 
  /* RLE: 001 Pixels @ 007,055 */ 1, 0x2C, 
  /* RLE: 048 Pixels @ 008,055 */ 48, 0x06, 
  /* RLE: 001 Pixels @ 056,055 */ 1, 0x2C, 
  /* RLE: 005 Pixels @ 057,055 */ 5, 0x01, 
  /* ABS: 004 Pixels @ 062,055 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,056 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,056 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,057 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,057 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,058 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,058 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,059 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,059 */ 0, 4, 0x04, 0x02, 0x02, 0x04, 
  /* RLE: 060 Pixels @ 002,060 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x04, 0x02, 0x10, 0x18, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x18, 0x1F, 0x3E, 0x67, 0x19, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x19, 0x61, 0x1D, 0x1C, 0x1D, 0x10, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x02, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x10, 0x3A, 0x1C, 
  0
};  // 1098 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_emUSBH_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_emUSBH_64x64,  // Pointer to picture data (indices)
  &_PalIcon_emUSBH_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/
