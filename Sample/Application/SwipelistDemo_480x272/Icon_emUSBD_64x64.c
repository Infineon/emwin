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
* Source file: Icon_emUSBD_64x64                                     *
* Dimensions:  64 * 64                                               *
* NumColors:   178                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_emUSBD_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_emUSBD_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x00A95C00, 0x001C1718,
  0x001B1D1D, 0x00FAFAFA, 0x00C2C3C3, 0x00AF6711,
  0x00F9F4EE, 0x00DDBE99, 0x00BC8038, 0x00B16B17,
  0x00959696, 0x00AC6108, 0x00B47222, 0x00BA7C32,
  0x00C59153, 0x00E8D4BB, 0x00BB7D34, 0x00CA9B62,
  0x00858686, 0x00A4A5A5, 0x00676868, 0x001F1A1B,
  0x00E1E1E1, 0x00F4F4F4, 0x001C1E1E, 0x00AFB0B0,
  0x00F3F2F2, 0x001D1414, 0x001E2020, 0x00272223,
  0x00767777, 0x00989999, 0x00F6F6F6, 0x00FDFDFD,
  0x001D1819, 0x00232525, 0x002C2E2E, 0x00303232,
  0x00393A3A, 0x00404141, 0x00494B4B, 0x00565757,
  0x00696A6A, 0x00757777, 0x00787979, 0x00BD823C,
  0x00AEAEAE, 0x00B4B5B5, 0x00B8B9B9, 0x00D6B185,
  0x00C4C5C5, 0x00D6D6D6, 0x00E2E3E3, 0x00ECECEC,
  0x00FBF7F3, 0x00FBFBFB, 0x00FCFCFC, 0x001F2121,
  0x00212323, 0x00252021, 0x00282929, 0x00292B2B,
  0x002B2D2D, 0x00302B2C, 0x00322D2F, 0x00373233,
  0x00323434, 0x00383334, 0x003A313A, 0x00363838,
  0x00373838, 0x003C3E3E, 0x003D3F3F, 0x003F4040,
  0x00424444, 0x00464848, 0x004A4C4C, 0x004B4D4D,
  0x004F5050, 0x00505151, 0x00515252, 0x00525454,
  0x005A5C5C, 0x005D5F5F, 0x00616262, 0x00636464,
  0x00686969, 0x006B6D6D, 0x006C6E6E, 0x00717272,
  0x00727373, 0x00747676, 0x007A7B7B, 0x007D7E7E,
  0x00AB5F05, 0x00AD630B, 0x00AE650E, 0x00B06914,
  0x00B06A16, 0x00B16B18, 0x00B16C19, 0x00B26D1B,
  0x00B26E1C, 0x00B36F1D, 0x00B3701F, 0x00B57223,
  0x00B57324, 0x00B67527, 0x00B77629, 0x00B97B30,
  0x00BB7F36, 0x00807D7E, 0x00BC8039, 0x00BF8540,
  0x00C48F50, 0x00C49051, 0x00C69255, 0x00C69457,
  0x00CA9B63, 0x00CC9E67, 0x00CC9E68, 0x00D1A877,
  0x00D1A978, 0x00838081, 0x00858283, 0x00868384,
  0x00838484, 0x00848585, 0x00868787, 0x00898A8A,
  0x008B8C8C, 0x008D8E8E, 0x008E8F8F, 0x00999A9A,
  0x009B9C9C, 0x009E9E9E, 0x00A3A4A4, 0x00B0B1B1,
  0x00B7B7B7, 0x00BABBBB, 0x00BFBFBF, 0x00D9B68D,
  0x00C0C1C1, 0x00C6C6C6, 0x00C8C8C8, 0x00CACBCB,
  0x00CCCCCC, 0x00CDCDCD, 0x00D1D2D2, 0x00D3D4D4,
  0x00D9D9D9, 0x00DCDCDC, 0x00EDDDCA, 0x00F0E2D2,
  0x00F1E4D5, 0x00F2E7D9, 0x00F4E9DD, 0x00E0E0E0,
  0x00E1E2E2, 0x00E6E6E6, 0x00E9E9E9, 0x00EBEBEB,
  0x00EDEDED, 0x00EEEEEE, 0x00F5ECE2, 0x00F6EEE5,
  0x00F7EFE6, 0x00F8F1E9, 0x00F9F3EC, 0x00F0F0F0,
  0x00F2F3F3, 0x00F5F5F5, 0x00FAF6F1, 0x00FBF8F4,
  0x00F8F8F8, 0x00F9F9F9
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF005CA9, 0xFF18171C,
  0xFF1D1D1B, 0xFFFAFAFA, 0xFFC3C3C2, 0xFF1167AF,
  0xFFEEF4F9, 0xFF99BEDD, 0xFF3880BC, 0xFF176BB1,
  0xFF969695, 0xFF0861AC, 0xFF2272B4, 0xFF327CBA,
  0xFF5391C5, 0xFFBBD4E8, 0xFF347DBB, 0xFF629BCA,
  0xFF868685, 0xFFA5A5A4, 0xFF686867, 0xFF1B1A1F,
  0xFFE1E1E1, 0xFFF4F4F4, 0xFF1E1E1C, 0xFFB0B0AF,
  0xFFF2F2F3, 0xFF14141D, 0xFF20201E, 0xFF232227,
  0xFF777776, 0xFF999998, 0xFFF6F6F6, 0xFFFDFDFD,
  0xFF19181D, 0xFF252523, 0xFF2E2E2C, 0xFF323230,
  0xFF3A3A39, 0xFF414140, 0xFF4B4B49, 0xFF575756,
  0xFF6A6A69, 0xFF777775, 0xFF797978, 0xFF3C82BD,
  0xFFAEAEAE, 0xFFB5B5B4, 0xFFB9B9B8, 0xFF85B1D6,
  0xFFC5C5C4, 0xFFD6D6D6, 0xFFE3E3E2, 0xFFECECEC,
  0xFFF3F7FB, 0xFFFBFBFB, 0xFFFCFCFC, 0xFF21211F,
  0xFF232321, 0xFF212025, 0xFF292928, 0xFF2B2B29,
  0xFF2D2D2B, 0xFF2C2B30, 0xFF2F2D32, 0xFF333237,
  0xFF343432, 0xFF343338, 0xFF3A313A, 0xFF383836,
  0xFF383837, 0xFF3E3E3C, 0xFF3F3F3D, 0xFF40403F,
  0xFF444442, 0xFF484846, 0xFF4C4C4A, 0xFF4D4D4B,
  0xFF50504F, 0xFF515150, 0xFF525251, 0xFF545452,
  0xFF5C5C5A, 0xFF5F5F5D, 0xFF626261, 0xFF646463,
  0xFF696968, 0xFF6D6D6B, 0xFF6E6E6C, 0xFF727271,
  0xFF737372, 0xFF767674, 0xFF7B7B7A, 0xFF7E7E7D,
  0xFF055FAB, 0xFF0B63AD, 0xFF0E65AE, 0xFF1469B0,
  0xFF166AB0, 0xFF186BB1, 0xFF196CB1, 0xFF1B6DB2,
  0xFF1C6EB2, 0xFF1D6FB3, 0xFF1F70B3, 0xFF2372B5,
  0xFF2473B5, 0xFF2775B6, 0xFF2976B7, 0xFF307BB9,
  0xFF367FBB, 0xFF7E7D80, 0xFF3980BC, 0xFF4085BF,
  0xFF508FC4, 0xFF5190C4, 0xFF5592C6, 0xFF5794C6,
  0xFF639BCA, 0xFF679ECC, 0xFF689ECC, 0xFF77A8D1,
  0xFF78A9D1, 0xFF818083, 0xFF838285, 0xFF848386,
  0xFF848483, 0xFF858584, 0xFF878786, 0xFF8A8A89,
  0xFF8C8C8B, 0xFF8E8E8D, 0xFF8F8F8E, 0xFF9A9A99,
  0xFF9C9C9B, 0xFF9E9E9E, 0xFFA4A4A3, 0xFFB1B1B0,
  0xFFB7B7B7, 0xFFBBBBBA, 0xFFBFBFBF, 0xFF8DB6D9,
  0xFFC1C1C0, 0xFFC6C6C6, 0xFFC8C8C8, 0xFFCBCBCA,
  0xFFCCCCCC, 0xFFCDCDCD, 0xFFD2D2D1, 0xFFD4D4D3,
  0xFFD9D9D9, 0xFFDCDCDC, 0xFFCADDED, 0xFFD2E2F0,
  0xFFD5E4F1, 0xFFD9E7F2, 0xFFDDE9F4, 0xFFE0E0E0,
  0xFFE2E2E1, 0xFFE6E6E6, 0xFFE9E9E9, 0xFFEBEBEB,
  0xFFEDEDED, 0xFFEEEEEE, 0xFFE2ECF5, 0xFFE5EEF6,
  0xFFE6EFF7, 0xFFE9F1F8, 0xFFECF3F9, 0xFFF0F0F0,
  0xFFF3F3F2, 0xFFF5F5F5, 0xFFF1F6FA, 0xFFF4F8FB,
  0xFFF8F8F8, 0xFFF9F9F9
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_emUSBD_64x64 = {
  178,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_emUSBD_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_emUSBD_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x46, 0x45, 0x17, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x03, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x17, 0x43, 0x1D, 0x42, 0x7F, 0xAD, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x19, 0x7E, 0x1F, 0x17, 0x1C, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x1C, 0x24, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,003 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,003 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 032 Pixels @ 002,004 */ 32, 0x01, 
  /* ABS: 004 Pixels @ 034,004 */ 0, 4, 0x95, 0x52, 0x4C, 0x21, 
  /* RLE: 024 Pixels @ 038,004 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,004 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,005 */ 25, 0x01, 
  /* ABS: 002 Pixels @ 027,005 */ 0, 2, 0x9F, 0x1B, 
  /* RLE: 005 Pixels @ 029,005 */ 5, 0x15, 
  /* ABS: 005 Pixels @ 034,005 */ 0, 5, 0x26, 0x04, 0x04, 0x04, 0x32, 
  /* RLE: 023 Pixels @ 039,005 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,005 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 024 Pixels @ 002,006 */ 24, 0x01, 
  /* ABS: 002 Pixels @ 026,006 */ 0, 2, 0x30, 0x3B, 
  /* RLE: 010 Pixels @ 028,006 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,006 */ 1, 0x14, 
  /* RLE: 023 Pixels @ 039,006 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,006 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,007 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 025,007 */ 0, 4, 0x34, 0x3C, 0x25, 0x85, 
  /* RLE: 004 Pixels @ 029,007 */ 4, 0x15, 
  /* ABS: 006 Pixels @ 033,007 */ 0, 6, 0x8A, 0x26, 0x04, 0x04, 0x04, 0x32, 
  /* RLE: 023 Pixels @ 039,007 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,007 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,008 */ 22, 0x01, 
  /* ABS: 004 Pixels @ 024,008 */ 0, 4, 0x97, 0x3E, 0x1E, 0x8C, 
  /* RLE: 006 Pixels @ 028,008 */ 6, 0x01, 
  /* ABS: 004 Pixels @ 034,008 */ 0, 4, 0x94, 0x51, 0x29, 0x21, 
  /* RLE: 024 Pixels @ 038,008 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,008 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 021 Pixels @ 002,009 */ 21, 0x01, 
  /* ABS: 004 Pixels @ 023,009 */ 0, 4, 0xA0, 0x27, 0x04, 0x89, 
  /* RLE: 035 Pixels @ 027,009 */ 35, 0x01, 
  /* ABS: 004 Pixels @ 062,009 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 009 Pixels @ 002,010 */ 9, 0x01, 
  /* ABS: 002 Pixels @ 011,010 */ 0, 2, 0x22, 0xA5, 
  /* RLE: 009 Pixels @ 013,010 */ 9, 0x01, 
  /* ABS: 004 Pixels @ 022,010 */ 0, 4, 0x37, 0x49, 0x04, 0x84, 
  /* RLE: 036 Pixels @ 026,010 */ 36, 0x01, 
  /* ABS: 004 Pixels @ 062,010 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,011 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,011 */ 0, 6, 0xA3, 0x16, 0x1E, 0x04, 0x28, 0x8B, 
  /* RLE: 006 Pixels @ 015,011 */ 6, 0x01, 
  /* ABS: 004 Pixels @ 021,011 */ 0, 4, 0x19, 0x4E, 0x04, 0x2D, 
  /* RLE: 026 Pixels @ 025,011 */ 26, 0x01, 
  /* RLE: 001 Pixels @ 051,011 */ 1, 0x23, 
  /* RLE: 010 Pixels @ 052,011 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,011 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 006 Pixels @ 002,012 */ 6, 0x01, 
  /* ABS: 002 Pixels @ 008,012 */ 0, 2, 0xB0, 0x29, 
  /* RLE: 004 Pixels @ 010,012 */ 4, 0x04, 
  /* ABS: 002 Pixels @ 014,012 */ 0, 2, 0x1A, 0x30, 
  /* RLE: 004 Pixels @ 016,012 */ 4, 0x01, 
  /* ABS: 005 Pixels @ 020,012 */ 0, 5, 0x22, 0x2B, 0x04, 0x56, 0x3A, 
  /* RLE: 026 Pixels @ 025,012 */ 26, 0x01, 
  /* ABS: 002 Pixels @ 051,012 */ 0, 2, 0x2A, 0x92, 
  /* RLE: 009 Pixels @ 053,012 */ 9, 0x01, 
  /* ABS: 004 Pixels @ 062,012 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 006 Pixels @ 002,013 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,013 */ 1, 0x87, 
  /* RLE: 006 Pixels @ 009,013 */ 6, 0x04, 
  /* ABS: 009 Pixels @ 015,013 */ 0, 9, 0x47, 0x06, 0x06, 0x06, 0x31, 0x53, 0x04, 0x27, 0x8D, 
  /* RLE: 027 Pixels @ 024,013 */ 27, 0x06, 
  /* ABS: 004 Pixels @ 051,013 */ 0, 4, 0x1A, 0x04, 0x16, 0x36, 
  /* RLE: 007 Pixels @ 055,013 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,013 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 006 Pixels @ 002,014 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,014 */ 1, 0x2C, 
  /* RLE: 045 Pixels @ 009,014 */ 45, 0x04, 
  /* ABS: 002 Pixels @ 054,014 */ 0, 2, 0x25, 0x90, 
  /* RLE: 006 Pixels @ 056,014 */ 6, 0x01, 
  /* ABS: 004 Pixels @ 062,014 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 006 Pixels @ 002,015 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 008,015 */ 1, 0x2D, 
  /* RLE: 006 Pixels @ 009,015 */ 6, 0x04, 
  /* ABS: 002 Pixels @ 015,015 */ 0, 2, 0x1E, 0x80, 
  /* RLE: 008 Pixels @ 017,015 */ 8, 0x14, 
  /* ABS: 007 Pixels @ 025,015 */ 0, 7, 0x5E, 0x20, 0x5D, 0x4F, 0x04, 0x04, 0x5C, 
  /* RLE: 019 Pixels @ 032,015 */ 19, 0x0C, 
  /* ABS: 004 Pixels @ 051,015 */ 0, 4, 0x1A, 0x04, 0x4B, 0x8E, 
  /* RLE: 007 Pixels @ 055,015 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 006 Pixels @ 002,016 */ 6, 0x01, 
  /* ABS: 002 Pixels @ 008,016 */ 0, 2, 0x91, 0x1A, 
  /* RLE: 005 Pixels @ 010,016 */ 5, 0x04, 
  /* RLE: 001 Pixels @ 015,016 */ 1, 0x55, 
  /* RLE: 012 Pixels @ 016,016 */ 12, 0x01, 
  /* ABS: 005 Pixels @ 028,016 */ 0, 5, 0x23, 0x2E, 0x04, 0x28, 0xA2, 
  /* RLE: 018 Pixels @ 033,016 */ 18, 0x01, 
  /* ABS: 003 Pixels @ 051,016 */ 0, 3, 0x40, 0x88, 0x39, 
  /* RLE: 008 Pixels @ 054,016 */ 8, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,017 */ 7, 0x01, 
  /* ABS: 007 Pixels @ 009,017 */ 0, 7, 0x83, 0x1A, 0x04, 0x04, 0x04, 0x48, 0xA1, 
  /* RLE: 013 Pixels @ 016,017 */ 13, 0x01, 
  /* ABS: 005 Pixels @ 029,017 */ 0, 5, 0x23, 0x59, 0x04, 0x4D, 0xAC, 
  /* RLE: 017 Pixels @ 034,017 */ 17, 0x01, 
  /* RLE: 001 Pixels @ 051,017 */ 1, 0xA4, 
  /* RLE: 010 Pixels @ 052,017 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 008 Pixels @ 002,018 */ 8, 0x01, 
  /* ABS: 005 Pixels @ 010,018 */ 0, 5, 0x34, 0x5B, 0x2C, 0x21, 0x19, 
  /* RLE: 015 Pixels @ 015,018 */ 15, 0x01, 
  /* ABS: 005 Pixels @ 030,018 */ 0, 5, 0x39, 0x54, 0x04, 0x2B, 0xB1, 
  /* RLE: 027 Pixels @ 035,018 */ 27, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 029 Pixels @ 002,019 */ 29, 0x01, 
  /* ABS: 005 Pixels @ 031,019 */ 0, 5, 0x22, 0x50, 0x04, 0x57, 0x3A, 
  /* RLE: 026 Pixels @ 036,019 */ 26, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 030 Pixels @ 002,020 */ 30, 0x01, 
  /* ABS: 004 Pixels @ 032,020 */ 0, 4, 0x37, 0x4A, 0x04, 0x5F, 
  /* RLE: 006 Pixels @ 036,020 */ 6, 0x01, 
  /* RLE: 001 Pixels @ 042,020 */ 1, 0x31, 
  /* RLE: 004 Pixels @ 043,020 */ 4, 0x16, 
  /* RLE: 001 Pixels @ 047,020 */ 1, 0x93, 
  /* RLE: 014 Pixels @ 048,020 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 031 Pixels @ 002,021 */ 31, 0x01, 
  /* ABS: 010 Pixels @ 033,021 */ 0, 10, 0x36, 0x44, 0x04, 0x82, 0x35, 0x18, 0x18, 0x98, 0x96, 0x2E, 
  /* RLE: 004 Pixels @ 043,021 */ 4, 0x04, 
  /* RLE: 001 Pixels @ 047,021 */ 1, 0x1B, 
  /* RLE: 014 Pixels @ 048,021 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 032 Pixels @ 002,022 */ 32, 0x01, 
  /* ABS: 002 Pixels @ 034,022 */ 0, 2, 0x35, 0x3F, 
  /* RLE: 011 Pixels @ 036,022 */ 11, 0x04, 
  /* RLE: 001 Pixels @ 047,022 */ 1, 0x1B, 
  /* RLE: 014 Pixels @ 048,022 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 033 Pixels @ 002,023 */ 33, 0x01, 
  /* ABS: 008 Pixels @ 035,023 */ 0, 8, 0x99, 0x81, 0x5A, 0x16, 0x58, 0x20, 0x20, 0x2A, 
  /* RLE: 004 Pixels @ 043,023 */ 4, 0x04, 
  /* RLE: 001 Pixels @ 047,023 */ 1, 0x1B, 
  /* RLE: 014 Pixels @ 048,023 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 040 Pixels @ 002,024 */ 40, 0x01, 
  /* RLE: 001 Pixels @ 042,024 */ 1, 0x86, 
  /* RLE: 004 Pixels @ 043,024 */ 4, 0x04, 
  /* RLE: 001 Pixels @ 047,024 */ 1, 0x1B, 
  /* RLE: 014 Pixels @ 048,024 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 040 Pixels @ 002,025 */ 40, 0x01, 
  /* RLE: 001 Pixels @ 042,025 */ 1, 0xAB, 
  /* RLE: 004 Pixels @ 043,025 */ 4, 0x18, 
  /* RLE: 001 Pixels @ 047,025 */ 1, 0x19, 
  /* RLE: 014 Pixels @ 048,025 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,026 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,027 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,028 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,029 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,030 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 016 Pixels @ 002,031 */ 16, 0x01, 
  /* RLE: 001 Pixels @ 018,031 */ 1, 0xAE, 
  /* RLE: 026 Pixels @ 019,031 */ 26, 0x08, 
  /* RLE: 001 Pixels @ 045,031 */ 1, 0x38, 
  /* RLE: 016 Pixels @ 046,031 */ 16, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,032 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 016,032 */ 0, 2, 0x9B, 0x6D, 
  /* RLE: 028 Pixels @ 018,032 */ 28, 0x02, 
  /* ABS: 002 Pixels @ 046,032 */ 0, 2, 0x0A, 0xA7, 
  /* RLE: 014 Pixels @ 048,032 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,033 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 016,033 */ 1, 0x73, 
  /* RLE: 030 Pixels @ 017,033 */ 30, 0x02, 
  /* RLE: 001 Pixels @ 047,033 */ 1, 0x78, 
  /* RLE: 014 Pixels @ 048,033 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,034 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 016,034 */ 1, 0x65, 
  /* RLE: 005 Pixels @ 017,034 */ 5, 0x02, 
  /* ABS: 002 Pixels @ 022,034 */ 0, 2, 0x64, 0x09, 
  /* RLE: 016 Pixels @ 024,034 */ 16, 0x11, 
  /* ABS: 002 Pixels @ 040,034 */ 0, 2, 0x33, 0x61, 
  /* RLE: 005 Pixels @ 042,034 */ 5, 0x02, 
  /* RLE: 001 Pixels @ 047,034 */ 1, 0x72, 
  /* RLE: 014 Pixels @ 048,034 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,035 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 016,035 */ 1, 0x0B, 
  /* RLE: 004 Pixels @ 017,035 */ 4, 0x02, 
  /* ABS: 002 Pixels @ 021,035 */ 0, 2, 0x6A, 0x9D, 
  /* RLE: 018 Pixels @ 023,035 */ 18, 0x01, 
  /* ABS: 002 Pixels @ 041,035 */ 0, 2, 0x9A, 0x63, 
  /* RLE: 004 Pixels @ 043,035 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 047,035 */ 1, 0x0A, 
  /* RLE: 014 Pixels @ 048,035 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,036 */ 14, 0x01, 
  /* ABS: 006 Pixels @ 016,036 */ 0, 6, 0x0B, 0x02, 0x02, 0x02, 0x6E, 0xA6, 
  /* RLE: 020 Pixels @ 022,036 */ 20, 0x01, 
  /* ABS: 006 Pixels @ 042,036 */ 0, 6, 0x9C, 0x68, 0x02, 0x02, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,036 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,037 */ 14, 0x01, 
  /* ABS: 005 Pixels @ 016,037 */ 0, 5, 0x0B, 0x02, 0x02, 0x70, 0xAA, 
  /* RLE: 022 Pixels @ 021,037 */ 22, 0x01, 
  /* ABS: 005 Pixels @ 043,037 */ 0, 5, 0x9E, 0x6B, 0x02, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,037 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,038 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 016,038 */ 0, 4, 0x0B, 0x02, 0x6C, 0x38, 
  /* RLE: 024 Pixels @ 020,038 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 044,038 */ 0, 4, 0xA8, 0x62, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,038 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,039 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,039 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,039 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,039 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,039 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,039 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,040 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,040 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,040 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,040 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,040 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,040 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,041 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,041 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,041 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,041 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,041 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,041 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,042 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,042 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x2F, 
  /* RLE: 018 Pixels @ 023,042 */ 18, 0x0D, 
  /* ABS: 007 Pixels @ 041,042 */ 0, 7, 0x7A, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,042 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,042 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,043 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,043 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,043 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,043 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,043 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,043 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,044 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,044 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,044 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,044 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,044 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,044 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,045 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,045 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,045 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,045 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,045 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,045 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,046 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,046 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,046 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,046 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,046 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,046 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,047 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,047 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,047 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,047 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,047 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,047 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,048 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,048 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,048 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,048 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,048 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,048 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,049 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,049 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,049 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,049 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,049 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,049 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,050 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,050 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,050 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,050 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,050 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,050 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,051 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,051 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x12, 
  /* RLE: 018 Pixels @ 023,051 */ 18, 0x02, 
  /* ABS: 007 Pixels @ 041,051 */ 0, 7, 0x13, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,051 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,051 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,052 */ 14, 0x01, 
  /* ABS: 007 Pixels @ 016,052 */ 0, 7, 0x0B, 0x02, 0x10, 0x01, 0x01, 0x01, 0x74, 
  /* RLE: 018 Pixels @ 023,052 */ 18, 0x0E, 
  /* ABS: 007 Pixels @ 041,052 */ 0, 7, 0x7C, 0x01, 0x01, 0x01, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,052 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,052 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,053 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,053 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,053 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,053 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,053 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,053 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,054 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,054 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,054 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,054 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,054 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,054 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,055 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,055 */ 0, 3, 0x0B, 0x02, 0x10, 
  /* RLE: 026 Pixels @ 019,055 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,055 */ 0, 3, 0x0F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,055 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,055 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,056 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,056 */ 0, 3, 0x0B, 0x02, 0x75, 
  /* RLE: 026 Pixels @ 019,056 */ 26, 0x01, 
  /* ABS: 003 Pixels @ 045,056 */ 0, 3, 0x6F, 0x02, 0x0A, 
  /* RLE: 014 Pixels @ 048,056 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,056 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,057 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 016,057 */ 0, 4, 0x67, 0x02, 0x07, 0x8F, 
  /* RLE: 024 Pixels @ 020,057 */ 24, 0x09, 
  /* ABS: 004 Pixels @ 044,057 */ 0, 4, 0x33, 0x60, 0x02, 0x2F, 
  /* RLE: 014 Pixels @ 048,057 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,057 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,058 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 016,058 */ 1, 0x76, 
  /* RLE: 030 Pixels @ 017,058 */ 30, 0x02, 
  /* RLE: 001 Pixels @ 047,058 */ 1, 0x7B, 
  /* RLE: 014 Pixels @ 048,058 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,058 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 014 Pixels @ 002,059 */ 14, 0x01, 
  /* ABS: 003 Pixels @ 016,059 */ 0, 3, 0xA9, 0x77, 0x66, 
  /* RLE: 026 Pixels @ 019,059 */ 26, 0x07, 
  /* ABS: 003 Pixels @ 045,059 */ 0, 3, 0x69, 0x79, 0xAF, 
  /* RLE: 014 Pixels @ 048,059 */ 14, 0x01, 
  /* ABS: 004 Pixels @ 062,059 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,060 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x05, 0x03, 0x17, 0x1C, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x1C, 0x24, 0x41, 0x7D, 0x19, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x19, 0x71, 0x1F, 0x1D, 0x1F, 0x17, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x03, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x17, 0x3D, 0x1D, 
  0
};  // 1377 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_emUSBD_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_emUSBD_64x64,  // Pointer to picture data (indices)
  &_PalIcon_emUSBD_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/