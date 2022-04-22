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
* Source file: Icon_emMQTT_64x64                                     *
* Dimensions:  64 * 64                                               *
* NumColors:   127                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_emMQTT_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_emMQTT_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x00A95C00, 0x001C1718,
  0x001B1D1D, 0x00FAFAFA, 0x00CB9D66, 0x002A2C2C,
  0x00A4A5A5, 0x00484949, 0x00545656, 0x00787979,
  0x00858686, 0x00393B3B, 0x005C5E5E, 0x00DFC2A0,
  0x00EFE0CF, 0x001F1A1B, 0x00E3C9AB, 0x00EBD9C4,
  0x00EFE2D1, 0x00F3F2F2, 0x001D1414, 0x00272223,
  0x00AA5F04, 0x00E0C4A2, 0x00ECDBC6, 0x00F1E5D6,
  0x00F4F4F4, 0x00F5F5F5, 0x00FCF9F5, 0x001D1819,
  0x001D1F1F, 0x001F2121, 0x00AB6007, 0x00B06915,
  0x00CDA16C, 0x00CEA36F, 0x00CFA572, 0x00D0A775,
  0x008C8D8D, 0x009C9D9D, 0x00E9D5BE, 0x00D0D0D0,
  0x00EAD7C0, 0x00F2E5D7, 0x00E1E2E2, 0x00FAF5EF,
  0x001C1E1E, 0x00252021, 0x00222424, 0x00252727,
  0x00262828, 0x00272929, 0x00302B2C, 0x00322D2F,
  0x002F3030, 0x00313333, 0x00373233, 0x00323434,
  0x00383334, 0x003A313A, 0x00373838, 0x00393A3A,
  0x003A3C3C, 0x007C4F18, 0x00494B4B, 0x00525454,
  0x00535555, 0x005A5C5C, 0x005D5F5F, 0x005E5F5F,
  0x005F6060, 0x00686969, 0x00767777, 0x00777878,
  0x007C7E7E, 0x007D7E7E, 0x007E7F7F, 0x0082541D,
  0x00AB5F05, 0x00AE660F, 0x00AE6610, 0x00B06914,
  0x00B06A16, 0x00875922, 0x008A5D26, 0x00956730,
  0x009A6D36, 0x00807D7E, 0x00CEA26E, 0x00CFA470,
  0x00CFA471, 0x00D0A673, 0x007F8080, 0x00808181,
  0x00838081, 0x00858283, 0x00868384, 0x008A8B8B,
  0x00949595, 0x00A1A2A2, 0x00BEBEBE, 0x00E0C4A3,
  0x00E3CBAD, 0x00E4CBAE, 0x00C9CACA, 0x00D8D8D8,
  0x00DBDCDC, 0x00DCDCDC, 0x00DEDEDE, 0x00EBD9C3,
  0x00EEE0CE, 0x00EFE1D0, 0x00F0E3D3, 0x00F0E4D4,
  0x00F2E6D8, 0x00F4EBDF, 0x00E0E0E0, 0x00E2E3E3,
  0x00EAEBEB, 0x00ECECEC, 0x00F5EBE0, 0x00F2F3F3,
  0x00FCF9F6, 0x00FDFDFD, 0x00FEFEFE
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF005CA9, 0xFF18171C,
  0xFF1D1D1B, 0xFFFAFAFA, 0xFF669DCB, 0xFF2C2C2A,
  0xFFA5A5A4, 0xFF494948, 0xFF565654, 0xFF797978,
  0xFF868685, 0xFF3B3B39, 0xFF5E5E5C, 0xFFA0C2DF,
  0xFFCFE0EF, 0xFF1B1A1F, 0xFFABC9E3, 0xFFC4D9EB,
  0xFFD1E2EF, 0xFFF2F2F3, 0xFF14141D, 0xFF232227,
  0xFF045FAA, 0xFFA2C4E0, 0xFFC6DBEC, 0xFFD6E5F1,
  0xFFF4F4F4, 0xFFF5F5F5, 0xFFF5F9FC, 0xFF19181D,
  0xFF1F1F1D, 0xFF21211F, 0xFF0760AB, 0xFF1569B0,
  0xFF6CA1CD, 0xFF6FA3CE, 0xFF72A5CF, 0xFF75A7D0,
  0xFF8D8D8C, 0xFF9D9D9C, 0xFFBED5E9, 0xFFD0D0D0,
  0xFFC0D7EA, 0xFFD7E5F2, 0xFFE2E2E1, 0xFFEFF5FA,
  0xFF1E1E1C, 0xFF212025, 0xFF242422, 0xFF272725,
  0xFF282826, 0xFF292927, 0xFF2C2B30, 0xFF2F2D32,
  0xFF30302F, 0xFF333331, 0xFF333237, 0xFF343432,
  0xFF343338, 0xFF3A313A, 0xFF383837, 0xFF3A3A39,
  0xFF3C3C3A, 0xFF184F7C, 0xFF4B4B49, 0xFF545452,
  0xFF555553, 0xFF5C5C5A, 0xFF5F5F5D, 0xFF5F5F5E,
  0xFF60605F, 0xFF696968, 0xFF777776, 0xFF787877,
  0xFF7E7E7C, 0xFF7E7E7D, 0xFF7F7F7E, 0xFF1D5482,
  0xFF055FAB, 0xFF0F66AE, 0xFF1066AE, 0xFF1469B0,
  0xFF166AB0, 0xFF225987, 0xFF265D8A, 0xFF306795,
  0xFF366D9A, 0xFF7E7D80, 0xFF6EA2CE, 0xFF70A4CF,
  0xFF71A4CF, 0xFF73A6D0, 0xFF80807F, 0xFF818180,
  0xFF818083, 0xFF838285, 0xFF848386, 0xFF8B8B8A,
  0xFF959594, 0xFFA2A2A1, 0xFFBEBEBE, 0xFFA3C4E0,
  0xFFADCBE3, 0xFFAECBE4, 0xFFCACAC9, 0xFFD8D8D8,
  0xFFDCDCDB, 0xFFDCDCDC, 0xFFDEDEDE, 0xFFC3D9EB,
  0xFFCEE0EE, 0xFFD0E1EF, 0xFFD3E3F0, 0xFFD4E4F0,
  0xFFD8E6F2, 0xFFDFEBF4, 0xFFE0E0E0, 0xFFE3E3E2,
  0xFFEBEBEA, 0xFFECECEC, 0xFFE0EBF5, 0xFFF3F3F2,
  0xFFF6F9FC, 0xFFFDFDFD, 0xFFFEFEFE
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_emMQTT_64x64 = {
  127,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_emMQTT_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_emMQTT_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x3D, 0x3C, 0x11, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x03, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x11, 0x3A, 0x16, 0x37, 0x62, 0x1D, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x1C, 0x61, 0x17, 0x11, 0x15, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x15, 0x1F, 0x03, 0x05, 
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
  /* RLE: 027 Pixels @ 002,015 */ 27, 0x01, 
  /* ABS: 006 Pixels @ 029,015 */ 0, 6, 0x2E, 0x65, 0x5F, 0x5E, 0x29, 0x6C, 
  /* RLE: 027 Pixels @ 035,015 */ 27, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 025 Pixels @ 002,016 */ 25, 0x01, 
  /* ABS: 003 Pixels @ 027,016 */ 0, 3, 0x78, 0x49, 0x20, 
  /* RLE: 005 Pixels @ 030,016 */ 5, 0x04, 
  /* ABS: 002 Pixels @ 035,016 */ 0, 2, 0x46, 0x77, 
  /* RLE: 025 Pixels @ 037,016 */ 25, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 024 Pixels @ 002,017 */ 24, 0x01, 
  /* ABS: 002 Pixels @ 026,017 */ 0, 2, 0x6D, 0x3B, 
  /* RLE: 008 Pixels @ 028,017 */ 8, 0x04, 
  /* ABS: 002 Pixels @ 036,017 */ 0, 2, 0x07, 0x2B, 
  /* RLE: 024 Pixels @ 038,017 */ 24, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,018 */ 23, 0x01, 
  /* ABS: 002 Pixels @ 025,018 */ 0, 2, 0x1D, 0x3F, 
  /* RLE: 010 Pixels @ 027,018 */ 10, 0x04, 
  /* ABS: 002 Pixels @ 037,018 */ 0, 2, 0x38, 0x79, 
  /* RLE: 023 Pixels @ 039,018 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 023 Pixels @ 002,019 */ 23, 0x01, 
  /* RLE: 001 Pixels @ 025,019 */ 1, 0x28, 
  /* RLE: 012 Pixels @ 026,019 */ 12, 0x04, 
  /* RLE: 001 Pixels @ 038,019 */ 1, 0x4B, 
  /* RLE: 023 Pixels @ 039,019 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,020 */ 22, 0x01, 
  /* ABS: 002 Pixels @ 024,020 */ 0, 2, 0x7D, 0x39, 
  /* RLE: 012 Pixels @ 026,020 */ 12, 0x04, 
  /* ABS: 002 Pixels @ 038,020 */ 0, 2, 0x34, 0x1D, 
  /* RLE: 022 Pixels @ 040,020 */ 22, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 022 Pixels @ 002,021 */ 22, 0x01, 
  /* RLE: 001 Pixels @ 024,021 */ 1, 0x6E, 
  /* RLE: 014 Pixels @ 025,021 */ 14, 0x04, 
  /* RLE: 001 Pixels @ 039,021 */ 1, 0x6A, 
  /* RLE: 022 Pixels @ 040,021 */ 22, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,022 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,022 */ 1, 0x48, 
  /* RLE: 011 Pixels @ 013,022 */ 11, 0x07, 
  /* RLE: 001 Pixels @ 024,022 */ 1, 0x35, 
  /* RLE: 014 Pixels @ 025,022 */ 14, 0x04, 
  /* RLE: 001 Pixels @ 039,022 */ 1, 0x33, 
  /* RLE: 011 Pixels @ 040,022 */ 11, 0x07, 
  /* RLE: 001 Pixels @ 051,022 */ 1, 0x44, 
  /* RLE: 010 Pixels @ 052,022 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,023 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,023 */ 0, 2, 0x0A, 0x43, 
  /* RLE: 010 Pixels @ 014,023 */ 10, 0x08, 
  /* RLE: 001 Pixels @ 024,023 */ 1, 0x63, 
  /* RLE: 014 Pixels @ 025,023 */ 14, 0x04, 
  /* RLE: 001 Pixels @ 039,023 */ 1, 0x4C, 
  /* RLE: 010 Pixels @ 040,023 */ 10, 0x08, 
  /* ABS: 002 Pixels @ 050,023 */ 0, 2, 0x45, 0x09, 
  /* RLE: 010 Pixels @ 052,023 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,024 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,024 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 010 Pixels @ 014,024 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 024,024 */ 0, 2, 0x7B, 0x21, 
  /* RLE: 013 Pixels @ 026,024 */ 13, 0x04, 
  /* RLE: 001 Pixels @ 039,024 */ 1, 0x2E, 
  /* RLE: 010 Pixels @ 040,024 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 050,024 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,024 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,025 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,025 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 011 Pixels @ 014,025 */ 11, 0x01, 
  /* RLE: 001 Pixels @ 025,025 */ 1, 0x47, 
  /* RLE: 012 Pixels @ 026,025 */ 12, 0x04, 
  /* RLE: 001 Pixels @ 038,025 */ 1, 0x42, 
  /* RLE: 011 Pixels @ 039,025 */ 11, 0x01, 
  /* ABS: 002 Pixels @ 050,025 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,025 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,026 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,026 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 011 Pixels @ 014,026 */ 11, 0x01, 
  /* ABS: 002 Pixels @ 025,026 */ 0, 2, 0x2B, 0x20, 
  /* RLE: 011 Pixels @ 027,026 */ 11, 0x04, 
  /* RLE: 001 Pixels @ 038,026 */ 1, 0x66, 
  /* RLE: 011 Pixels @ 039,026 */ 11, 0x01, 
  /* ABS: 002 Pixels @ 050,026 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,026 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,027 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,027 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 012 Pixels @ 014,027 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 026,027 */ 1, 0x64, 
  /* RLE: 010 Pixels @ 027,027 */ 10, 0x04, 
  /* RLE: 001 Pixels @ 037,027 */ 1, 0x4E, 
  /* RLE: 012 Pixels @ 038,027 */ 12, 0x01, 
  /* ABS: 002 Pixels @ 050,027 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,027 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,028 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,028 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 013 Pixels @ 014,028 */ 13, 0x01, 
  /* ABS: 002 Pixels @ 027,028 */ 0, 2, 0x29, 0x32, 
  /* RLE: 006 Pixels @ 029,028 */ 6, 0x04, 
  /* ABS: 003 Pixels @ 035,028 */ 0, 3, 0x21, 0x28, 0x7E, 
  /* RLE: 012 Pixels @ 038,028 */ 12, 0x01, 
  /* ABS: 002 Pixels @ 050,028 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,028 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,029 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,029 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 014 Pixels @ 014,029 */ 14, 0x01, 
  /* ABS: 008 Pixels @ 028,029 */ 0, 8, 0x76, 0x4D, 0x40, 0x30, 0x04, 0x3E, 0x4A, 0x6B, 
  /* RLE: 014 Pixels @ 036,029 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 050,029 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,029 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,030 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,030 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,030 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,030 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,030 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,030 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,030 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,031 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,031 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,031 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,031 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,031 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,031 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,031 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,032 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,032 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,032 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,032 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,032 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,032 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,032 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,033 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,033 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,033 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,033 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,033 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,033 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,033 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,034 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,034 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,034 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,034 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,034 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,034 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,034 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,035 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,035 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,035 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,035 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,035 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,035 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,035 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,036 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,036 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,036 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,036 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,036 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,036 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,036 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,037 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,037 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,037 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,037 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,037 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,037 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,037 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 010 Pixels @ 002,038 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 012,038 */ 0, 2, 0x0A, 0x0B, 
  /* RLE: 017 Pixels @ 014,038 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 031,038 */ 0, 2, 0x0E, 0x0D, 
  /* RLE: 017 Pixels @ 033,038 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 050,038 */ 0, 2, 0x0C, 0x09, 
  /* RLE: 010 Pixels @ 052,038 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,039 */ 4, 0x01, 
  /* ABS: 002 Pixels @ 006,039 */ 0, 2, 0x1B, 0x27, 
  /* RLE: 004 Pixels @ 008,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 012,039 */ 0, 2, 0x55, 0x57, 
  /* RLE: 004 Pixels @ 014,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 018,039 */ 0, 2, 0x25, 0x2C, 
  /* RLE: 005 Pixels @ 020,039 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 025,039 */ 0, 2, 0x71, 0x5D, 
  /* RLE: 004 Pixels @ 027,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 031,039 */ 0, 2, 0x56, 0x41, 
  /* RLE: 004 Pixels @ 033,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 037,039 */ 0, 2, 0x5B, 0x1A, 
  /* RLE: 005 Pixels @ 039,039 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 044,039 */ 0, 2, 0x2C, 0x25, 
  /* RLE: 004 Pixels @ 046,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 050,039 */ 0, 2, 0x58, 0x4F, 
  /* RLE: 004 Pixels @ 052,039 */ 4, 0x06, 
  /* ABS: 002 Pixels @ 056,039 */ 0, 2, 0x27, 0x1B, 
  /* RLE: 004 Pixels @ 058,039 */ 4, 0x01, 
  /* ABS: 009 Pixels @ 062,039 */ 0, 9, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x1E, 0x23, 
  /* RLE: 012 Pixels @ 007,040 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 019,040 */ 0, 7, 0x50, 0x74, 0x01, 0x01, 0x01, 0x2F, 0x52, 
  /* RLE: 012 Pixels @ 026,040 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 038,040 */ 0, 7, 0x22, 0x7A, 0x01, 0x01, 0x01, 0x2D, 0x18, 
  /* RLE: 012 Pixels @ 045,040 */ 12, 0x02, 
  /* ABS: 013 Pixels @ 057,040 */ 0, 13, 0x54, 0x7C, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x14, 
  /* RLE: 014 Pixels @ 006,041 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,041 */ 0, 5, 0x67, 0x01, 0x01, 0x01, 0x1A, 
  /* RLE: 014 Pixels @ 025,041 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,041 */ 0, 5, 0x69, 0x01, 0x01, 0x01, 0x19, 
  /* RLE: 014 Pixels @ 044,041 */ 14, 0x02, 
  /* ABS: 012 Pixels @ 058,041 */ 0, 12, 0x14, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 014 Pixels @ 006,042 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,042 */ 0, 5, 0x0F, 0x01, 0x01, 0x01, 0x13, 
  /* RLE: 014 Pixels @ 025,042 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,042 */ 0, 5, 0x12, 0x01, 0x01, 0x01, 0x0F, 
  /* RLE: 014 Pixels @ 044,042 */ 14, 0x02, 
  /* ABS: 012 Pixels @ 058,042 */ 0, 12, 0x10, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 014 Pixels @ 006,043 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,043 */ 0, 5, 0x0F, 0x01, 0x01, 0x01, 0x13, 
  /* RLE: 014 Pixels @ 025,043 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,043 */ 0, 5, 0x12, 0x01, 0x01, 0x01, 0x0F, 
  /* RLE: 014 Pixels @ 044,043 */ 14, 0x02, 
  /* ABS: 012 Pixels @ 058,043 */ 0, 12, 0x10, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 014 Pixels @ 006,044 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,044 */ 0, 5, 0x0F, 0x01, 0x01, 0x01, 0x13, 
  /* RLE: 014 Pixels @ 025,044 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,044 */ 0, 5, 0x12, 0x01, 0x01, 0x01, 0x0F, 
  /* RLE: 014 Pixels @ 044,044 */ 14, 0x02, 
  /* ABS: 012 Pixels @ 058,044 */ 0, 12, 0x10, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x10, 
  /* RLE: 014 Pixels @ 006,045 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,045 */ 0, 5, 0x0F, 0x01, 0x01, 0x01, 0x13, 
  /* RLE: 014 Pixels @ 025,045 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,045 */ 0, 5, 0x12, 0x01, 0x01, 0x01, 0x0F, 
  /* RLE: 014 Pixels @ 044,045 */ 14, 0x02, 
  /* ABS: 012 Pixels @ 058,045 */ 0, 12, 0x10, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x14, 
  /* RLE: 014 Pixels @ 006,046 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 020,046 */ 0, 5, 0x19, 0x01, 0x01, 0x01, 0x1A, 
  /* RLE: 014 Pixels @ 025,046 */ 14, 0x02, 
  /* ABS: 005 Pixels @ 039,046 */ 0, 5, 0x68, 0x01, 0x01, 0x01, 0x19, 
  /* RLE: 014 Pixels @ 044,046 */ 14, 0x02, 
  /* ABS: 013 Pixels @ 058,046 */ 0, 13, 0x14, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 0x01, 0x01, 0x01, 0x1E, 0x53, 
  /* RLE: 012 Pixels @ 007,047 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 019,047 */ 0, 7, 0x18, 0x2D, 0x01, 0x01, 0x01, 0x2F, 0x51, 
  /* RLE: 012 Pixels @ 026,047 */ 12, 0x02, 
  /* ABS: 007 Pixels @ 038,047 */ 0, 7, 0x22, 0x75, 0x01, 0x01, 0x01, 0x1B, 0x18, 
  /* RLE: 012 Pixels @ 045,047 */ 12, 0x02, 
  /* ABS: 009 Pixels @ 057,047 */ 0, 9, 0x23, 0x1E, 0x01, 0x01, 0x01, 0x05, 0x03, 0x03, 0x05, 
  /* RLE: 004 Pixels @ 002,048 */ 4, 0x01, 
  /* ABS: 002 Pixels @ 006,048 */ 0, 2, 0x72, 0x26, 
  /* RLE: 010 Pixels @ 008,048 */ 10, 0x06, 
  /* ABS: 002 Pixels @ 018,048 */ 0, 2, 0x24, 0x2A, 
  /* RLE: 005 Pixels @ 020,048 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 025,048 */ 0, 2, 0x70, 0x5C, 
  /* RLE: 010 Pixels @ 027,048 */ 10, 0x06, 
  /* ABS: 002 Pixels @ 037,048 */ 0, 2, 0x5A, 0x6F, 
  /* RLE: 005 Pixels @ 039,048 */ 5, 0x01, 
  /* ABS: 002 Pixels @ 044,048 */ 0, 2, 0x2A, 0x24, 
  /* RLE: 010 Pixels @ 046,048 */ 10, 0x06, 
  /* ABS: 002 Pixels @ 056,048 */ 0, 2, 0x26, 0x73, 
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
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x05, 0x03, 0x11, 0x15, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x15, 0x1F, 0x36, 0x60, 0x1C, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x1C, 0x59, 0x17, 0x16, 0x17, 0x11, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x03, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x11, 0x31, 0x16, 
  0
};  // 1238 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_emMQTT_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_emMQTT_64x64,  // Pointer to picture data (indices)
  &_PalIcon_emMQTT_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/
