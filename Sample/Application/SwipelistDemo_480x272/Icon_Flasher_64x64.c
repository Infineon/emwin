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
* Source file: Icon_Flasher_64x64                                    *
* Dimensions:  64 * 64                                               *
* NumColors:   126                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Flasher_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_Flasher_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x00000000, 0x001D1817,
  0x00A65D00, 0x00FAFAFA, 0x00030303, 0x00888888,
  0x00999999, 0x00DBBE99, 0x00BE8844, 0x00B27323,
  0x00F5EDE2, 0x006E6E6E, 0x00A96309, 0x00AE6B16,
  0x00E7D4BB, 0x00F0E4D5, 0x00E6E6E6, 0x00F3F3F3,
  0x00201B1A, 0x00272727, 0x008F8F8F, 0x00E5CFB4,
  0x00F5EDE3, 0x00171717, 0x00353535, 0x00373737,
  0x00474747, 0x00575757, 0x005E5E5E, 0x00686868,
  0x00787878, 0x007E7E7E, 0x00A86107, 0x00B37424,
  0x00878787, 0x009F9F9F, 0x00AFAFAF, 0x00BFBFBF,
  0x00CFCFCF, 0x00EFEFEF, 0x00F6F6F6, 0x001D1414,
  0x00272322, 0x00959595, 0x00E8D4BC, 0x00DADADA,
  0x00ECECEC, 0x00EEEEEE, 0x00F3F2F2, 0x00F8F8F8,
  0x001E1918, 0x00383838, 0x00484848, 0x00555555,
  0x00626262, 0x007B7B7B, 0x00A9630A, 0x00B47729,
  0x00808080, 0x008D8D8D, 0x009A9A9A, 0x00A1A1A1,
  0x00A4A4A4, 0x00A7A7A7, 0x00B4B4B4, 0x00C0C0C0,
  0x00CDCDCD, 0x00D7D7D7, 0x00F4F4F4, 0x00211B1A,
  0x00252120, 0x00292929, 0x002D2D2D, 0x002E2E2E,
  0x00312C2B, 0x00352C2C, 0x00342F2E, 0x00373332,
  0x00393433, 0x004B4B4B, 0x00585858, 0x00646464,
  0x00707070, 0x007D7D7D, 0x007F7C7C, 0x00AB650D,
  0x0083807E, 0x00C39254, 0x00828282, 0x00858281,
  0x00868483, 0x008A8A8A, 0x00969696, 0x00979797,
  0x009B9B9B, 0x00A2A2A2, 0x00A8A8A8, 0x00B5B5B5,
  0x00D3AE80, 0x00DFC5A3, 0x00C1C1C1, 0x00CECECE,
  0x00DBDBDB, 0x00DEDEDE, 0x00E0E0E0, 0x00E3E3E3,
  0x00E5E5E5, 0x00E7E7E7, 0x00E8E8E8, 0x00E9E9E9,
  0x00EAEAEA, 0x00EBEBEB, 0x00EDEDED, 0x00F4EBE0,
  0x00F7F0E7, 0x00F0F0F0, 0x00F2F1F1, 0x00F5F5F5,
  0x00F9F9F9, 0x00FEFCFB, 0x00FCFCFC, 0x00FDFDFD,
  0x00FEFEFD, 0x00FEFEFE
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0xFF17181D,
  0xFF005DA6, 0xFFFAFAFA, 0xFF030303, 0xFF888888,
  0xFF999999, 0xFF99BEDB, 0xFF4488BE, 0xFF2373B2,
  0xFFE2EDF5, 0xFF6E6E6E, 0xFF0963A9, 0xFF166BAE,
  0xFFBBD4E7, 0xFFD5E4F0, 0xFFE6E6E6, 0xFFF3F3F3,
  0xFF1A1B20, 0xFF272727, 0xFF8F8F8F, 0xFFB4CFE5,
  0xFFE3EDF5, 0xFF171717, 0xFF353535, 0xFF373737,
  0xFF474747, 0xFF575757, 0xFF5E5E5E, 0xFF686868,
  0xFF787878, 0xFF7E7E7E, 0xFF0761A8, 0xFF2474B3,
  0xFF878787, 0xFF9F9F9F, 0xFFAFAFAF, 0xFFBFBFBF,
  0xFFCFCFCF, 0xFFEFEFEF, 0xFFF6F6F6, 0xFF14141D,
  0xFF222327, 0xFF959595, 0xFFBCD4E8, 0xFFDADADA,
  0xFFECECEC, 0xFFEEEEEE, 0xFFF2F2F3, 0xFFF8F8F8,
  0xFF18191E, 0xFF383838, 0xFF484848, 0xFF555555,
  0xFF626262, 0xFF7B7B7B, 0xFF0A63A9, 0xFF2977B4,
  0xFF808080, 0xFF8D8D8D, 0xFF9A9A9A, 0xFFA1A1A1,
  0xFFA4A4A4, 0xFFA7A7A7, 0xFFB4B4B4, 0xFFC0C0C0,
  0xFFCDCDCD, 0xFFD7D7D7, 0xFFF4F4F4, 0xFF1A1B21,
  0xFF202125, 0xFF292929, 0xFF2D2D2D, 0xFF2E2E2E,
  0xFF2B2C31, 0xFF2C2C35, 0xFF2E2F34, 0xFF323337,
  0xFF333439, 0xFF4B4B4B, 0xFF585858, 0xFF646464,
  0xFF707070, 0xFF7D7D7D, 0xFF7C7C7F, 0xFF0D65AB,
  0xFF7E8083, 0xFF5492C3, 0xFF828282, 0xFF818285,
  0xFF838486, 0xFF8A8A8A, 0xFF969696, 0xFF979797,
  0xFF9B9B9B, 0xFFA2A2A2, 0xFFA8A8A8, 0xFFB5B5B5,
  0xFF80AED3, 0xFFA3C5DF, 0xFFC1C1C1, 0xFFCECECE,
  0xFFDBDBDB, 0xFFDEDEDE, 0xFFE0E0E0, 0xFFE3E3E3,
  0xFFE5E5E5, 0xFFE7E7E7, 0xFFE8E8E8, 0xFFE9E9E9,
  0xFFEAEAEA, 0xFFEBEBEB, 0xFFEDEDED, 0xFFE0EBF4,
  0xFFE7F0F7, 0xFFF0F0F0, 0xFFF1F1F2, 0xFFF5F5F5,
  0xFFF9F9F9, 0xFFFBFCFE, 0xFFFCFCFC, 0xFFFDFDFD,
  0xFFFDFEFE, 0xFFFEFEFE
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_Flasher_64x64 = {
  126,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_Flasher_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_Flasher_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x4D, 0x50, 0x14, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x03, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x14, 0x4F, 0x2B, 0x4E, 0x5C, 0x46, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x46, 0x5B, 0x2C, 0x14, 0x32, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x32, 0x34, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,003 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,003 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,004 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,004 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,005 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,005 */ 1, 0x59, 
  /* RLE: 010 Pixels @ 028,005 */ 10, 0x0A, 
  /* RLE: 001 Pixels @ 038,005 */ 1, 0x73, 
  /* RLE: 023 Pixels @ 039,005 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,005 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,006 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,006 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,006 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,006 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,006 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,006 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,007 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,007 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,007 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,007 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,007 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,007 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,008 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,008 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,008 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,008 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,008 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,008 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,009 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,009 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,009 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,009 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,009 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,009 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,010 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,010 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,010 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,010 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,010 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,010 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,011 */ 25, 0x01, 
  /* RLE: 001 Pixels @ 027,011 */ 1, 0x0F, 
  /* RLE: 010 Pixels @ 028,011 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,011 */ 1, 0x11, 
  /* RLE: 023 Pixels @ 039,011 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,011 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 017 Pixels @ 002,012 */ 17, 0x01, 
  /* RLE: 001 Pixels @ 019,012 */ 1, 0x10, 
  /* RLE: 007 Pixels @ 020,012 */ 7, 0x09, 
  /* RLE: 001 Pixels @ 027,012 */ 1, 0x57, 
  /* RLE: 010 Pixels @ 028,012 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 038,012 */ 1, 0x64, 
  /* RLE: 006 Pixels @ 039,012 */ 6, 0x09, 
  /* ABS: 002 Pixels @ 045,012 */ 0, 2, 0x65, 0x7C, 
  /* RLE: 015 Pixels @ 047,012 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,012 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 017 Pixels @ 002,013 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 019,013 */ 0, 2, 0x74, 0x3B, 
  /* RLE: 023 Pixels @ 021,013 */ 23, 0x04, 
  /* ABS: 002 Pixels @ 044,013 */ 0, 2, 0x3A, 0x2E, 
  /* RLE: 016 Pixels @ 046,013 */ 16, 0x01, 
  /* ABS: 004 Pixels @ 062,013 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 018 Pixels @ 002,014 */ 18, 0x01, 
  /* ABS: 002 Pixels @ 020,014 */ 0, 2, 0x18, 0x23, 
  /* RLE: 021 Pixels @ 022,014 */ 21, 0x04, 
  /* ABS: 002 Pixels @ 043,014 */ 0, 2, 0x3A, 0x2E, 
  /* RLE: 017 Pixels @ 045,014 */ 17, 0x01, 
  /* ABS: 004 Pixels @ 062,014 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 019 Pixels @ 002,015 */ 19, 0x01, 
  /* ABS: 002 Pixels @ 021,015 */ 0, 2, 0x18, 0x23, 
  /* RLE: 019 Pixels @ 023,015 */ 19, 0x04, 
  /* ABS: 002 Pixels @ 042,015 */ 0, 2, 0x0E, 0x2E, 
  /* RLE: 018 Pixels @ 044,015 */ 18, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 020 Pixels @ 002,016 */ 20, 0x01, 
  /* ABS: 002 Pixels @ 022,016 */ 0, 2, 0x18, 0x23, 
  /* RLE: 017 Pixels @ 024,016 */ 17, 0x04, 
  /* ABS: 002 Pixels @ 041,016 */ 0, 2, 0x0E, 0x10, 
  /* RLE: 019 Pixels @ 043,016 */ 19, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 021 Pixels @ 002,017 */ 21, 0x01, 
  /* ABS: 002 Pixels @ 023,017 */ 0, 2, 0x18, 0x23, 
  /* RLE: 015 Pixels @ 025,017 */ 15, 0x04, 
  /* ABS: 002 Pixels @ 040,017 */ 0, 2, 0x0E, 0x10, 
  /* RLE: 020 Pixels @ 042,017 */ 20, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,018 */ 22, 0x01, 
  /* ABS: 002 Pixels @ 024,018 */ 0, 2, 0x18, 0x0B, 
  /* RLE: 013 Pixels @ 026,018 */ 13, 0x04, 
  /* ABS: 002 Pixels @ 039,018 */ 0, 2, 0x0E, 0x10, 
  /* RLE: 021 Pixels @ 041,018 */ 21, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,019 */ 23, 0x01, 
  /* ABS: 002 Pixels @ 025,019 */ 0, 2, 0x0C, 0x0B, 
  /* RLE: 011 Pixels @ 027,019 */ 11, 0x04, 
  /* ABS: 002 Pixels @ 038,019 */ 0, 2, 0x0E, 0x10, 
  /* RLE: 022 Pixels @ 040,019 */ 22, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 024 Pixels @ 002,020 */ 24, 0x01, 
  /* ABS: 002 Pixels @ 026,020 */ 0, 2, 0x0C, 0x0B, 
  /* RLE: 009 Pixels @ 028,020 */ 9, 0x04, 
  /* ABS: 002 Pixels @ 037,020 */ 0, 2, 0x0E, 0x10, 
  /* RLE: 023 Pixels @ 039,020 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,021 */ 25, 0x01, 
  /* ABS: 002 Pixels @ 027,021 */ 0, 2, 0x0C, 0x0B, 
  /* RLE: 007 Pixels @ 029,021 */ 7, 0x04, 
  /* ABS: 002 Pixels @ 036,021 */ 0, 2, 0x22, 0x17, 
  /* RLE: 024 Pixels @ 038,021 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 026 Pixels @ 002,022 */ 26, 0x01, 
  /* ABS: 002 Pixels @ 028,022 */ 0, 2, 0x0C, 0x0B, 
  /* RLE: 005 Pixels @ 030,022 */ 5, 0x04, 
  /* ABS: 002 Pixels @ 035,022 */ 0, 2, 0x22, 0x17, 
  /* RLE: 025 Pixels @ 037,022 */ 25, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 027 Pixels @ 002,023 */ 27, 0x01, 
  /* ABS: 007 Pixels @ 029,023 */ 0, 7, 0x0C, 0x0B, 0x04, 0x04, 0x04, 0x22, 0x17, 
  /* RLE: 026 Pixels @ 036,023 */ 26, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 028 Pixels @ 002,024 */ 28, 0x01, 
  /* ABS: 005 Pixels @ 030,024 */ 0, 5, 0x0C, 0x0B, 0x04, 0x22, 0x17, 
  /* RLE: 027 Pixels @ 035,024 */ 27, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 029 Pixels @ 002,025 */ 29, 0x01, 
  /* ABS: 003 Pixels @ 031,025 */ 0, 3, 0x0C, 0x3B, 0x17, 
  /* RLE: 028 Pixels @ 034,025 */ 28, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 030 Pixels @ 002,026 */ 30, 0x01, 
  /* RLE: 001 Pixels @ 032,026 */ 1, 0x79, 
  /* RLE: 029 Pixels @ 033,026 */ 29, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,027 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,028 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,029 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,030 */ 12, 0x01, 
  /* ABS: 002 Pixels @ 014,030 */ 0, 2, 0x31, 0x40, 
  /* RLE: 032 Pixels @ 016,030 */ 32, 0x08, 
  /* ABS: 002 Pixels @ 048,030 */ 0, 2, 0x40, 0x31, 
  /* RLE: 012 Pixels @ 050,030 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,031 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 014,031 */ 1, 0x4A, 
  /* RLE: 034 Pixels @ 015,031 */ 34, 0x02, 
  /* RLE: 001 Pixels @ 049,031 */ 1, 0x4B, 
  /* RLE: 012 Pixels @ 050,031 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,032 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 014,032 */ 1, 0x06, 
  /* RLE: 034 Pixels @ 015,032 */ 34, 0x02, 
  /* RLE: 001 Pixels @ 049,032 */ 1, 0x06, 
  /* RLE: 012 Pixels @ 050,032 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,033 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,033 */ 0, 6, 0x6C, 0x1D, 0x1D, 0x39, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,033 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,033 */ 0, 6, 0x06, 0x01, 0x39, 0x1D, 0x1D, 0x55, 
  /* RLE: 007 Pixels @ 055,033 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,034 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,034 */ 0, 6, 0x31, 0x16, 0x16, 0x41, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,034 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,034 */ 0, 6, 0x06, 0x01, 0x41, 0x16, 0x16, 0x62, 
  /* RLE: 007 Pixels @ 055,034 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,035 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,035 */ 0, 6, 0x72, 0x24, 0x24, 0x3F, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,035 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,035 */ 0, 6, 0x06, 0x01, 0x3F, 0x24, 0x24, 0x61, 
  /* RLE: 007 Pixels @ 055,035 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,036 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,036 */ 0, 6, 0x12, 0x1E, 0x1E, 0x3C, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,036 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,036 */ 0, 6, 0x06, 0x01, 0x3C, 0x1E, 0x1E, 0x5A, 
  /* RLE: 007 Pixels @ 055,036 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,037 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,037 */ 0, 6, 0x33, 0x28, 0x28, 0x2F, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,037 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,037 */ 0, 6, 0x06, 0x01, 0x2F, 0x28, 0x28, 0x2F, 
  /* RLE: 007 Pixels @ 055,037 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,038 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,038 */ 0, 6, 0x68, 0x19, 0x19, 0x36, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,038 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,038 */ 0, 6, 0x06, 0x01, 0x36, 0x19, 0x19, 0x51, 
  /* RLE: 007 Pixels @ 055,038 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,039 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 014,039 */ 1, 0x06, 
  /* RLE: 034 Pixels @ 015,039 */ 34, 0x02, 
  /* RLE: 001 Pixels @ 049,039 */ 1, 0x06, 
  /* RLE: 012 Pixels @ 050,039 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,039 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,040 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,040 */ 0, 6, 0x45, 0x02, 0x02, 0x1A, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,040 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,040 */ 0, 6, 0x06, 0x01, 0x1A, 0x02, 0x02, 0x35, 
  /* RLE: 007 Pixels @ 055,040 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,040 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,041 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,041 */ 0, 6, 0x7A, 0x12, 0x12, 0x30, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,041 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,041 */ 0, 6, 0x06, 0x01, 0x30, 0x12, 0x12, 0x30, 
  /* RLE: 007 Pixels @ 055,041 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,041 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,042 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,042 */ 0, 6, 0x6B, 0x1C, 0x1C, 0x0D, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,042 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,042 */ 0, 6, 0x06, 0x01, 0x0D, 0x1C, 0x1C, 0x54, 
  /* RLE: 007 Pixels @ 055,042 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,042 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,043 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,043 */ 0, 6, 0x75, 0x25, 0x25, 0x42, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,043 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,043 */ 0, 6, 0x06, 0x01, 0x42, 0x25, 0x25, 0x63, 
  /* RLE: 007 Pixels @ 055,043 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,043 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,044 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,044 */ 0, 6, 0x70, 0x20, 0x20, 0x2D, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,044 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,044 */ 0, 6, 0x06, 0x01, 0x2D, 0x20, 0x20, 0x5F, 
  /* RLE: 007 Pixels @ 055,044 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,044 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,045 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,045 */ 0, 6, 0x6F, 0x0D, 0x0D, 0x3D, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,045 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,045 */ 0, 6, 0x06, 0x01, 0x3D, 0x0D, 0x0D, 0x16, 
  /* RLE: 007 Pixels @ 055,045 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,045 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,046 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,046 */ 0, 6, 0x77, 0x27, 0x27, 0x44, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,046 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,046 */ 0, 6, 0x06, 0x01, 0x44, 0x27, 0x27, 0x67, 
  /* RLE: 007 Pixels @ 055,046 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,046 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,047 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,047 */ 0, 6, 0x69, 0x15, 0x15, 0x37, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,047 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,047 */ 0, 6, 0x06, 0x01, 0x37, 0x15, 0x15, 0x52, 
  /* RLE: 007 Pixels @ 055,047 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,047 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,048 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,048 */ 0, 6, 0x7B, 0x29, 0x29, 0x13, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,048 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,048 */ 0, 6, 0x06, 0x01, 0x13, 0x29, 0x29, 0x13, 
  /* RLE: 007 Pixels @ 055,048 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,048 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,049 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,049 */ 0, 6, 0x45, 0x02, 0x02, 0x1A, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,049 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,049 */ 0, 6, 0x06, 0x01, 0x1A, 0x02, 0x02, 0x35, 
  /* RLE: 007 Pixels @ 055,049 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,049 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,050 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,050 */ 0, 6, 0x7D, 0x2A, 0x2A, 0x33, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,050 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,050 */ 0, 6, 0x06, 0x01, 0x33, 0x2A, 0x2A, 0x78, 
  /* RLE: 007 Pixels @ 055,050 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,050 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,051 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,051 */ 0, 6, 0x6A, 0x1B, 0x1B, 0x38, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,051 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,051 */ 0, 6, 0x06, 0x01, 0x38, 0x1B, 0x1B, 0x53, 
  /* RLE: 007 Pixels @ 055,051 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,051 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,052 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,052 */ 0, 6, 0x13, 0x26, 0x26, 0x43, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,052 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,052 */ 0, 6, 0x06, 0x01, 0x43, 0x26, 0x26, 0x66, 
  /* RLE: 007 Pixels @ 055,052 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,052 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,053 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,053 */ 0, 6, 0x6E, 0x1F, 0x1F, 0x07, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,053 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,053 */ 0, 6, 0x06, 0x01, 0x07, 0x1F, 0x1F, 0x5D, 
  /* RLE: 007 Pixels @ 055,053 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,053 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 007 Pixels @ 002,054 */ 7, 0x01, 
  /* ABS: 006 Pixels @ 009,054 */ 0, 6, 0x71, 0x21, 0x21, 0x3E, 0x01, 0x06, 
  /* RLE: 034 Pixels @ 015,054 */ 34, 0x02, 
  /* ABS: 006 Pixels @ 049,054 */ 0, 6, 0x06, 0x01, 0x3E, 0x21, 0x21, 0x60, 
  /* RLE: 007 Pixels @ 055,054 */ 7, 0x01, 
  /* ABS: 004 Pixels @ 062,054 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,055 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 014,055 */ 1, 0x06, 
  /* RLE: 034 Pixels @ 015,055 */ 34, 0x02, 
  /* RLE: 001 Pixels @ 049,055 */ 1, 0x06, 
  /* RLE: 012 Pixels @ 050,055 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,055 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,056 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 014,056 */ 1, 0x15, 
  /* RLE: 034 Pixels @ 015,056 */ 34, 0x02, 
  /* RLE: 001 Pixels @ 049,056 */ 1, 0x49, 
  /* RLE: 012 Pixels @ 050,056 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,056 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 012 Pixels @ 002,057 */ 12, 0x01, 
  /* ABS: 002 Pixels @ 014,057 */ 0, 2, 0x12, 0x5E, 
  /* RLE: 032 Pixels @ 016,057 */ 32, 0x07, 
  /* ABS: 002 Pixels @ 048,057 */ 0, 2, 0x2D, 0x6D, 
  /* RLE: 012 Pixels @ 050,057 */ 12, 0x01, 
  /* ABS: 004 Pixels @ 062,057 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,058 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,058 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,059 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,059 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 060 Pixels @ 002,060 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x05, 0x03, 0x14, 0x32, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x76, 0x34, 0x4C, 0x58, 0x13, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x13, 0x56, 0x2C, 0x2B, 0x2C, 0x14, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x03, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x47, 0x48, 0x2B, 
  0
};  // 1231 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_Flasher_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_Flasher_64x64,  // Pointer to picture data (indices)
  &_PalIcon_Flasher_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/
