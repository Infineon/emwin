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
* Source file: Icon_emNet_64x64                                      *
* Dimensions:  64 * 64                                               *
* NumColors:   113                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_emNet_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_emNet_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x00A95C00, 0x001C1718,
  0x00000000, 0x00FAFAFA, 0x00333333, 0x00444444,
  0x00C28C4B, 0x00CFA470, 0x007E7E7E, 0x00F5F5F5,
  0x00AFAFAF, 0x00C2C2C2, 0x00666666, 0x00BE833D,
  0x00C38D4C, 0x00999999, 0x001F1A1B, 0x00282828,
  0x00909090, 0x00E0C4A2, 0x00E0C5A3, 0x00F3F2F2,
  0x001D1414, 0x00272223, 0x005F3400, 0x00F4F4F4,
  0x001D1819, 0x00414141, 0x00AA5D02, 0x00976C38,
  0x00BE833E, 0x00C28C4C, 0x00C38D4D, 0x00C59254,
  0x00CBA06C, 0x00CFA471, 0x00CFA472, 0x00979797,
  0x00DBBB95, 0x00DEC19E, 0x00E3C9AB, 0x00FEFEFD,
  0x00010101, 0x00090909, 0x00232323, 0x00252021,
  0x00272727, 0x00292929, 0x002D2D2D, 0x002F2F2F,
  0x00302B2C, 0x00322D2F, 0x00373233, 0x00343434,
  0x00383334, 0x003A313A, 0x005E5E5E, 0x00696969,
  0x006A6A6A, 0x00757575, 0x007C7C7C, 0x00AF6914,
  0x00B06914, 0x00B57223, 0x00B67325, 0x00807D7E,
  0x00AC814D, 0x00BF8540, 0x00BF8640, 0x00B48955,
  0x00C48F4F, 0x00C48F50, 0x00CA9A61, 0x00CA9C63,
  0x00CDA06A, 0x00CDA16B, 0x00CFA572, 0x00D1A774,
  0x00D1A876, 0x00D3AA7A, 0x00D3AB7B, 0x00838081,
  0x00838383, 0x00858283, 0x00868384, 0x00929292,
  0x00959595, 0x009D9D9D, 0x00B8B8B8, 0x00D6B186,
  0x00D6B287, 0x00E0C5A4, 0x00E1C5A5, 0x00E2C8AA,
  0x00E2CAAB, 0x00C5C5C5, 0x00D9D9D9, 0x00DDDDDD,
  0x00F1E3D4, 0x00F1E5D6, 0x00F5EBE1, 0x00F5EDE2,
  0x00F9F2EB, 0x00F9F2EC, 0x00F9F4EE, 0x00F1F1F1,
  0x00FAF5F0, 0x00FBF8F3, 0x00FCF8F5, 0x00FEFEFE,
  0x00FFFEFE
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF005CA9, 0xFF18171C,
  0xFF000000, 0xFFFAFAFA, 0xFF333333, 0xFF444444,
  0xFF4B8CC2, 0xFF70A4CF, 0xFF7E7E7E, 0xFFF5F5F5,
  0xFFAFAFAF, 0xFFC2C2C2, 0xFF666666, 0xFF3D83BE,
  0xFF4C8DC3, 0xFF999999, 0xFF1B1A1F, 0xFF282828,
  0xFF909090, 0xFFA2C4E0, 0xFFA3C5E0, 0xFFF2F2F3,
  0xFF14141D, 0xFF232227, 0xFF00345F, 0xFFF4F4F4,
  0xFF19181D, 0xFF414141, 0xFF025DAA, 0xFF386C97,
  0xFF3E83BE, 0xFF4C8CC2, 0xFF4D8DC3, 0xFF5492C5,
  0xFF6CA0CB, 0xFF71A4CF, 0xFF72A4CF, 0xFF979797,
  0xFF95BBDB, 0xFF9EC1DE, 0xFFABC9E3, 0xFFFDFEFE,
  0xFF010101, 0xFF090909, 0xFF232323, 0xFF212025,
  0xFF272727, 0xFF292929, 0xFF2D2D2D, 0xFF2F2F2F,
  0xFF2C2B30, 0xFF2F2D32, 0xFF333237, 0xFF343434,
  0xFF343338, 0xFF3A313A, 0xFF5E5E5E, 0xFF696969,
  0xFF6A6A6A, 0xFF757575, 0xFF7C7C7C, 0xFF1469AF,
  0xFF1469B0, 0xFF2372B5, 0xFF2573B6, 0xFF7E7D80,
  0xFF4D81AC, 0xFF4085BF, 0xFF4086BF, 0xFF5589B4,
  0xFF4F8FC4, 0xFF508FC4, 0xFF619ACA, 0xFF639CCA,
  0xFF6AA0CD, 0xFF6BA1CD, 0xFF72A5CF, 0xFF74A7D1,
  0xFF76A8D1, 0xFF7AAAD3, 0xFF7BABD3, 0xFF818083,
  0xFF838383, 0xFF838285, 0xFF848386, 0xFF929292,
  0xFF959595, 0xFF9D9D9D, 0xFFB8B8B8, 0xFF86B1D6,
  0xFF87B2D6, 0xFFA4C5E0, 0xFFA5C5E1, 0xFFAAC8E2,
  0xFFABCAE2, 0xFFC5C5C5, 0xFFD9D9D9, 0xFFDDDDDD,
  0xFFD4E3F1, 0xFFD6E5F1, 0xFFE1EBF5, 0xFFE2EDF5,
  0xFFEBF2F9, 0xFFECF2F9, 0xFFEEF4F9, 0xFFF1F1F1,
  0xFFF0F5FA, 0xFFF3F8FB, 0xFFF5F8FC, 0xFFFEFEFE,
  0xFFFEFEFF
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_emNet_64x64 = {
  113,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_emNet_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_emNet_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x39, 0x38, 0x12, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x03, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x12, 0x36, 0x18, 0x35, 0x56, 0x0B, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x1B, 0x55, 0x19, 0x12, 0x17, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x17, 0x1C, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,003 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,003 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,004 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,004 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,005 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,005 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,006 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,006 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,007 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,007 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,008 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,008 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,009 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,009 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,010 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,010 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,011 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,011 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,012 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,012 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,013 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,013 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,014 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,014 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,015 */ 23, 0x01, 
  /* ABS: 002 Pixels @ 025,015 */ 0, 2, 0x0C, 0x3C, 
  /* RLE: 010 Pixels @ 027,015 */ 10, 0x0E, 
  /* ABS: 002 Pixels @ 037,015 */ 0, 2, 0x54, 0x6B, 
  /* RLE: 023 Pixels @ 039,015 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,016 */ 22, 0x01, 
  /* ABS: 002 Pixels @ 024,016 */ 0, 2, 0x61, 0x2C, 
  /* RLE: 012 Pixels @ 026,016 */ 12, 0x04, 
  /* RLE: 001 Pixels @ 038,016 */ 1, 0x3A, 
  /* RLE: 023 Pixels @ 039,016 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,017 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,017 */ 1, 0x57, 
  /* RLE: 013 Pixels @ 025,017 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,017 */ 1, 0x31, 
  /* RLE: 023 Pixels @ 039,017 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,018 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,018 */ 1, 0x14, 
  /* RLE: 013 Pixels @ 025,018 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,018 */ 1, 0x13, 
  /* RLE: 023 Pixels @ 039,018 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,019 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,019 */ 1, 0x14, 
  /* RLE: 013 Pixels @ 025,019 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,019 */ 1, 0x13, 
  /* RLE: 023 Pixels @ 039,019 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,020 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,020 */ 1, 0x14, 
  /* RLE: 013 Pixels @ 025,020 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,020 */ 1, 0x13, 
  /* RLE: 023 Pixels @ 039,020 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,021 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,021 */ 1, 0x14, 
  /* RLE: 013 Pixels @ 025,021 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,021 */ 1, 0x13, 
  /* RLE: 023 Pixels @ 039,021 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,022 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,022 */ 1, 0x58, 
  /* RLE: 013 Pixels @ 025,022 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 038,022 */ 1, 0x32, 
  /* RLE: 023 Pixels @ 039,022 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,023 */ 22, 0x01, 
  /* ABS: 002 Pixels @ 024,023 */ 0, 2, 0x62, 0x2D, 
  /* RLE: 012 Pixels @ 026,023 */ 12, 0x04, 
  /* RLE: 001 Pixels @ 038,023 */ 1, 0x3E, 
  /* RLE: 023 Pixels @ 039,023 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,024 */ 23, 0x01, 
  /* ABS: 008 Pixels @ 025,024 */ 0, 8, 0x63, 0x59, 0x11, 0x11, 0x11, 0x3D, 0x04, 0x3B, 
  /* RLE: 004 Pixels @ 033,024 */ 4, 0x11, 
  /* ABS: 002 Pixels @ 037,024 */ 0, 2, 0x5A, 0x6F, 
  /* RLE: 023 Pixels @ 039,024 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,025 */ 28, 0x01, 
  /* ABS: 003 Pixels @ 030,025 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 029 Pixels @ 033,025 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,026 */ 28, 0x01, 
  /* ABS: 003 Pixels @ 030,026 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 029 Pixels @ 033,026 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,027 */ 28, 0x01, 
  /* ABS: 003 Pixels @ 030,027 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 029 Pixels @ 033,027 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,028 */ 28, 0x01, 
  /* ABS: 003 Pixels @ 030,028 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 029 Pixels @ 033,028 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,029 */ 28, 0x01, 
  /* ABS: 003 Pixels @ 030,029 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 029 Pixels @ 033,029 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,030 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,030 */ 1, 0x27, 
  /* RLE: 017 Pixels @ 013,030 */ 17, 0x06, 
  /* ABS: 003 Pixels @ 030,030 */ 0, 3, 0x30, 0x04, 0x2E, 
  /* RLE: 018 Pixels @ 033,030 */ 18, 0x06, 
  /* RLE: 001 Pixels @ 051,030 */ 1, 0x27, 
  /* RLE: 010 Pixels @ 052,030 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,031 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,031 */ 0, 3, 0x0A, 0x04, 0x1D, 
  /* RLE: 015 Pixels @ 015,031 */ 15, 0x07, 
  /* ABS: 003 Pixels @ 030,031 */ 0, 3, 0x37, 0x04, 0x33, 
  /* RLE: 016 Pixels @ 033,031 */ 16, 0x07, 
  /* ABS: 003 Pixels @ 049,031 */ 0, 3, 0x1D, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,031 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,032 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,032 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,032 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,032 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,032 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,032 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,032 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,033 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,033 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,033 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,033 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,033 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,033 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,033 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,034 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,034 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,034 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,034 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,034 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,034 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,034 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,035 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,035 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,035 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,035 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,035 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,035 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,035 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,036 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,036 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,036 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,036 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,036 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,036 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,036 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,037 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,037 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,037 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,037 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,037 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,037 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,037 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,038 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 012,038 */ 0, 3, 0x0A, 0x04, 0x0B, 
  /* RLE: 015 Pixels @ 015,038 */ 15, 0x01, 
  /* ABS: 003 Pixels @ 030,038 */ 0, 3, 0x0D, 0x04, 0x0C, 
  /* RLE: 016 Pixels @ 033,038 */ 16, 0x01, 
  /* ABS: 003 Pixels @ 049,038 */ 0, 3, 0x0B, 0x04, 0x0A, 
  /* RLE: 010 Pixels @ 052,038 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,039 */ 4, 0x01, 
  /* ABS: 002 Pixels @ 006,039 */ 0, 2, 0x2B, 0x28, 
  /* RLE: 004 Pixels @ 008,039 */ 4, 0x09, 
  /* ABS: 008 Pixels @ 012,039 */ 0, 8, 0x1F, 0x1A, 0x24, 0x09, 0x09, 0x09, 0x26, 0x29, 
  /* RLE: 005 Pixels @ 020,039 */ 5, 0x01, 
  /* ABS: 008 Pixels @ 025,039 */ 0, 8, 0x64, 0x51, 0x09, 0x09, 0x09, 0x47, 0x1A, 0x44, 
  /* RLE: 004 Pixels @ 033,039 */ 4, 0x09, 
  /* ABS: 002 Pixels @ 037,039 */ 0, 2, 0x52, 0x65, 
  /* RLE: 004 Pixels @ 039,039 */ 4, 0x01, 
  /* ABS: 009 Pixels @ 043,039 */ 0, 9, 0x70, 0x29, 0x26, 0x09, 0x09, 0x09, 0x24, 0x1A, 0x1F, 
  /* RLE: 004 Pixels @ 052,039 */ 4, 0x09, 
  /* ABS: 002 Pixels @ 056,039 */ 0, 2, 0x28, 0x2B, 
  /* RLE: 004 Pixels @ 058,039 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,039 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,040 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,040 */ 1, 0x4F, 
  /* RLE: 012 Pixels @ 007,040 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 019,040 */ 0, 7, 0x1E, 0x5C, 0x01, 0x01, 0x01, 0x6A, 0x41, 
  /* RLE: 012 Pixels @ 026,040 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 038,040 */ 0, 7, 0x42, 0x6C, 0x01, 0x01, 0x01, 0x5B, 0x1E, 
  /* RLE: 012 Pixels @ 045,040 */ 12, 0x02, 
  /* RLE: 001 Pixels @ 057,040 */ 1, 0x50, 
  /* RLE: 004 Pixels @ 058,040 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,040 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,041 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,041 */ 1, 0x45, 
  /* RLE: 013 Pixels @ 007,041 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,041 */ 0, 5, 0x49, 0x01, 0x01, 0x01, 0x5F, 
  /* RLE: 014 Pixels @ 025,041 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,041 */ 0, 5, 0x60, 0x01, 0x01, 0x01, 0x48, 
  /* RLE: 013 Pixels @ 044,041 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,041 */ 1, 0x46, 
  /* RLE: 004 Pixels @ 058,041 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,041 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,042 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,042 */ 1, 0x0F, 
  /* RLE: 013 Pixels @ 007,042 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,042 */ 0, 5, 0x10, 0x01, 0x01, 0x01, 0x15, 
  /* RLE: 014 Pixels @ 025,042 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,042 */ 0, 5, 0x16, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 013 Pixels @ 044,042 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,042 */ 1, 0x0F, 
  /* RLE: 004 Pixels @ 058,042 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,042 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,043 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,043 */ 1, 0x0F, 
  /* RLE: 013 Pixels @ 007,043 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,043 */ 0, 5, 0x10, 0x01, 0x01, 0x01, 0x15, 
  /* RLE: 014 Pixels @ 025,043 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,043 */ 0, 5, 0x16, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 013 Pixels @ 044,043 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,043 */ 1, 0x0F, 
  /* RLE: 004 Pixels @ 058,043 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,043 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,044 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,044 */ 1, 0x0F, 
  /* RLE: 013 Pixels @ 007,044 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,044 */ 0, 5, 0x10, 0x01, 0x01, 0x01, 0x15, 
  /* RLE: 014 Pixels @ 025,044 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,044 */ 0, 5, 0x16, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 013 Pixels @ 044,044 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,044 */ 1, 0x0F, 
  /* RLE: 004 Pixels @ 058,044 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,044 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,045 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,045 */ 1, 0x0F, 
  /* RLE: 013 Pixels @ 007,045 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,045 */ 0, 5, 0x10, 0x01, 0x01, 0x01, 0x15, 
  /* RLE: 014 Pixels @ 025,045 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,045 */ 0, 5, 0x16, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 013 Pixels @ 044,045 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,045 */ 1, 0x0F, 
  /* RLE: 004 Pixels @ 058,045 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,045 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,046 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,046 */ 1, 0x20, 
  /* RLE: 013 Pixels @ 007,046 */ 13, 0x02, 
  /* ABS: 005 Pixels @ 020,046 */ 0, 5, 0x22, 0x01, 0x01, 0x01, 0x5D, 
  /* RLE: 014 Pixels @ 025,046 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,046 */ 0, 5, 0x5E, 0x01, 0x01, 0x01, 0x22, 
  /* RLE: 013 Pixels @ 044,046 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,046 */ 1, 0x20, 
  /* RLE: 004 Pixels @ 058,046 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,046 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,047 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 006,047 */ 1, 0x4A, 
  /* RLE: 013 Pixels @ 007,047 */ 13, 0x02, 
  /* ABS: 006 Pixels @ 020,047 */ 0, 6, 0x4E, 0x01, 0x01, 0x01, 0x66, 0x3F, 
  /* RLE: 012 Pixels @ 026,047 */ 12, 0x02, 
  /* ABS: 006 Pixels @ 038,047 */ 0, 6, 0x40, 0x67, 0x01, 0x01, 0x01, 0x25, 
  /* RLE: 013 Pixels @ 044,047 */ 13, 0x02, 
  /* RLE: 001 Pixels @ 057,047 */ 1, 0x4B, 
  /* RLE: 004 Pixels @ 058,047 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,047 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,048 */ 4, 0x01, 
  /* ABS: 002 Pixels @ 006,048 */ 0, 2, 0x68, 0x4C, 
  /* RLE: 010 Pixels @ 008,048 */ 10, 0x08, 
  /* ABS: 003 Pixels @ 018,048 */ 0, 3, 0x21, 0x25, 0x6E, 
  /* RLE: 004 Pixels @ 021,048 */ 4, 0x01, 
  /* ABS: 002 Pixels @ 025,048 */ 0, 2, 0x2A, 0x23, 
  /* RLE: 010 Pixels @ 027,048 */ 10, 0x08, 
  /* ABS: 002 Pixels @ 037,048 */ 0, 2, 0x23, 0x2A, 
  /* RLE: 004 Pixels @ 039,048 */ 4, 0x01, 
  /* ABS: 003 Pixels @ 043,048 */ 0, 3, 0x6D, 0x09, 0x21, 
  /* RLE: 010 Pixels @ 046,048 */ 10, 0x08, 
  /* ABS: 002 Pixels @ 056,048 */ 0, 2, 0x4D, 0x69, 
  /* RLE: 004 Pixels @ 058,048 */ 4, 0x01, 
  /* ABS: 004 Pixels @ 062,048 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,049 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,049 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,050 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,050 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,051 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,051 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,052 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,052 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,053 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,053 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,054 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,054 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,055 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,055 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,056 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,056 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,057 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,057 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,058 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,058 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,059 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,059 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,060 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x05, 0x03, 0x12, 0x17, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x17, 0x1C, 0x34, 0x53, 0x1B, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x1B, 0x43, 0x19, 0x18, 0x19, 0x12, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x03, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x12, 0x2F, 0x18, 
  0
};  // 1145 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_emNet_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_emNet_64x64,  // Pointer to picture data (indices)
  &_PalIcon_emNet_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/
