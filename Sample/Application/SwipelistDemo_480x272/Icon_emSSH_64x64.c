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
* Source file: Icon_emSSH_64x64                                      *
* Dimensions:  64 * 64                                               *
* NumColors:   147                                                   *
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_emSSH_64x64;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsIcon_emSSH_64x64[] = {
#if (GUI_USE_ARGB == 0)
  0x00FFFFFF, 0x00FFFFFF, 0x00A95C00, 0x001D1817,
  0x00FAFAFA, 0x00D6B185, 0x00C99960, 0x00D7B388,
  0x00C69255, 0x00E2C9AA, 0x001B1D1D, 0x00BA7D33,
  0x00585959, 0x00D1D2D2, 0x00B06915, 0x00C08743,
  0x00E3C9AB, 0x00F2E7D9, 0x00201B1A, 0x001D1414,
  0x00272322, 0x00AD640D, 0x00BF8540, 0x00F3F2F2,
  0x00F4F4F4, 0x00FDFCFA, 0x001E1918, 0x001F2121,
  0x00222424, 0x00272929, 0x00333535, 0x00393A3A,
  0x00484949, 0x004F5050, 0x00676868, 0x00AA5D02,
  0x00AA5E03, 0x00B06A16, 0x00B16C19, 0x00B47020,
  0x00B7772B, 0x00BA7B31, 0x00C18946, 0x00C38D4C,
  0x00CA9B62, 0x00CC9E68, 0x00A4A5A5, 0x00B3B4B4,
  0x00B4B5B5, 0x00DBBB94, 0x00DDBE99, 0x00DEC19E,
  0x00DFC3A1, 0x00E0C5A4, 0x00E5CEB3, 0x00E8D4BC,
  0x00C5C5C5, 0x00CDCDCD, 0x00D8D8D8, 0x00DDDDDD,
  0x00ECDBC6, 0x00EAEBEB, 0x00F8F2EB, 0x00F3F3F3,
  0x00FDFBF9, 0x00FCFCFC, 0x00FEFEFE, 0x00211B1A,
  0x00252120, 0x00232525, 0x00312C2B, 0x00352C2C,
  0x00342F2E, 0x00373332, 0x00393433, 0x00424444,
  0x00505151, 0x005C5E5E, 0x00777878, 0x00787979,
  0x007F7C7C, 0x00A95D01, 0x00AA5F04, 0x00AB5F05,
  0x00AB6007, 0x00AE6610, 0x00B36F1D, 0x00B47222,
  0x00B57223, 0x00B57324, 0x00B67426, 0x00B97A2F,
  0x00BB7F36, 0x00BC8038, 0x00BD823B, 0x00BF8641,
  0x00BF8642, 0x0083807E, 0x00C18947, 0x00C28C4B,
  0x00C38E4E, 0x00C7965A, 0x00C8975C, 0x00CA9B63,
  0x00CFA470, 0x00D0A775, 0x00D2AA7A, 0x00858281,
  0x00868483, 0x00919292, 0x00929393, 0x00969797,
  0x009B9C9C, 0x009C9D9D, 0x00A0A1A1, 0x00D7B287,
  0x00D7B489, 0x00D8B58C, 0x00D9B78E, 0x00DCBD97,
  0x00DEC09C, 0x00E4CCAF, 0x00E5CEB2, 0x00E6CFB4,
  0x00E7D1B7, 0x00E7D2B9, 0x00CACBCB, 0x00CFCFCF,
  0x00D6D6D6, 0x00EAD7C0, 0x00EBD9C4, 0x00EDDDCA,
  0x00F0E2D2, 0x00F2E5D7, 0x00F2E6D8, 0x00F5EBE0,
  0x00F9F3EC, 0x00F0F0F0, 0x00F2F1F1, 0x00F6F6F6,
  0x00F7F7F7, 0x00FBF7F2, 0x00FCF9F6, 0x00FBFBFB,
  0x00FDFDFD, 0x00FEFEFD, 0x00FFFEFE
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFF005CA9, 0xFF17181D,
  0xFFFAFAFA, 0xFF85B1D6, 0xFF6099C9, 0xFF88B3D7,
  0xFF5592C6, 0xFFAAC9E2, 0xFF1D1D1B, 0xFF337DBA,
  0xFF595958, 0xFFD2D2D1, 0xFF1569B0, 0xFF4387C0,
  0xFFABC9E3, 0xFFD9E7F2, 0xFF1A1B20, 0xFF14141D,
  0xFF222327, 0xFF0D64AD, 0xFF4085BF, 0xFFF2F2F3,
  0xFFF4F4F4, 0xFFFAFCFD, 0xFF18191E, 0xFF21211F,
  0xFF242422, 0xFF292927, 0xFF353533, 0xFF3A3A39,
  0xFF494948, 0xFF50504F, 0xFF686867, 0xFF025DAA,
  0xFF035EAA, 0xFF166AB0, 0xFF196CB1, 0xFF2070B4,
  0xFF2B77B7, 0xFF317BBA, 0xFF4689C1, 0xFF4C8DC3,
  0xFF629BCA, 0xFF689ECC, 0xFFA5A5A4, 0xFFB4B4B3,
  0xFFB5B5B4, 0xFF94BBDB, 0xFF99BEDD, 0xFF9EC1DE,
  0xFFA1C3DF, 0xFFA4C5E0, 0xFFB3CEE5, 0xFFBCD4E8,
  0xFFC5C5C5, 0xFFCDCDCD, 0xFFD8D8D8, 0xFFDDDDDD,
  0xFFC6DBEC, 0xFFEBEBEA, 0xFFEBF2F8, 0xFFF3F3F3,
  0xFFF9FBFD, 0xFFFCFCFC, 0xFFFEFEFE, 0xFF1A1B21,
  0xFF202125, 0xFF252523, 0xFF2B2C31, 0xFF2C2C35,
  0xFF2E2F34, 0xFF323337, 0xFF333439, 0xFF444442,
  0xFF515150, 0xFF5E5E5C, 0xFF787877, 0xFF797978,
  0xFF7C7C7F, 0xFF015DA9, 0xFF045FAA, 0xFF055FAB,
  0xFF0760AB, 0xFF1066AE, 0xFF1D6FB3, 0xFF2272B4,
  0xFF2372B5, 0xFF2473B5, 0xFF2674B6, 0xFF2F7AB9,
  0xFF367FBB, 0xFF3880BC, 0xFF3B82BD, 0xFF4186BF,
  0xFF4286BF, 0xFF7E8083, 0xFF4789C1, 0xFF4B8CC2,
  0xFF4E8EC3, 0xFF5A96C7, 0xFF5C97C8, 0xFF639BCA,
  0xFF70A4CF, 0xFF75A7D0, 0xFF7AAAD2, 0xFF818285,
  0xFF838486, 0xFF929291, 0xFF939392, 0xFF979796,
  0xFF9C9C9B, 0xFF9D9D9C, 0xFFA1A1A0, 0xFF87B2D7,
  0xFF89B4D7, 0xFF8CB5D8, 0xFF8EB7D9, 0xFF97BDDC,
  0xFF9CC0DE, 0xFFAFCCE4, 0xFFB2CEE5, 0xFFB4CFE6,
  0xFFB7D1E7, 0xFFB9D2E7, 0xFFCBCBCA, 0xFFCFCFCF,
  0xFFD6D6D6, 0xFFC0D7EA, 0xFFC4D9EB, 0xFFCADDED,
  0xFFD2E2F0, 0xFFD7E5F2, 0xFFD8E6F2, 0xFFE0EBF5,
  0xFFECF3F9, 0xFFF0F0F0, 0xFFF1F1F2, 0xFFF6F6F6,
  0xFFF7F7F7, 0xFFF2F7FB, 0xFFF6F9FC, 0xFFFBFBFB,
  0xFFFDFDFD, 0xFFFDFEFE, 0xFFFEFEFF
#endif

};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon_emSSH_64x64 = {
  147,  // Number of entries
  1,    // Has transparency
  &_ColorsIcon_emSSH_64x64[0]
};

static GUI_CONST_STORAGE unsigned char _acIcon_emSSH_64x64[] = {
  /* ABS: 003 Pixels @ 000,000 */ 0, 3, 0x47, 0x4A, 0x12, 
  /* RLE: 058 Pixels @ 003,000 */ 58, 0x03, 
  /* ABS: 006 Pixels @ 061,000 */ 0, 6, 0x12, 0x49, 0x13, 0x48, 0x6C, 0x18, 
  /* RLE: 058 Pixels @ 003,001 */ 58, 0x01, 
  /* ABS: 005 Pixels @ 061,001 */ 0, 5, 0x18, 0x6B, 0x14, 0x12, 0x17, 
  /* RLE: 060 Pixels @ 002,002 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,002 */ 0, 4, 0x17, 0x1A, 0x03, 0x04, 
  /* RLE: 060 Pixels @ 002,003 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,003 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 060 Pixels @ 002,004 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,004 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 025 Pixels @ 002,005 */ 25, 0x01, 
  /* ABS: 010 Pixels @ 027,005 */ 0, 10, 0x87, 0x31, 0x2C, 0x63, 0x29, 0x5C, 0x64, 0x2D, 0x34, 0x88, 
  /* RLE: 025 Pixels @ 037,005 */ 25, 0x01, 
  /* ABS: 004 Pixels @ 062,005 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 022 Pixels @ 002,006 */ 22, 0x01, 
  /* ABS: 003 Pixels @ 024,006 */ 0, 3, 0x91, 0x35, 0x29, 
  /* RLE: 009 Pixels @ 027,006 */ 9, 0x02, 
  /* ABS: 003 Pixels @ 036,006 */ 0, 3, 0x24, 0x5F, 0x37, 
  /* RLE: 023 Pixels @ 039,006 */ 23, 0x01, 
  /* ABS: 004 Pixels @ 062,006 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 021 Pixels @ 002,007 */ 21, 0x01, 
  /* ABS: 002 Pixels @ 023,007 */ 0, 2, 0x81, 0x5B, 
  /* RLE: 014 Pixels @ 025,007 */ 14, 0x02, 
  /* ABS: 002 Pixels @ 039,007 */ 0, 2, 0x2A, 0x85, 
  /* RLE: 021 Pixels @ 041,007 */ 21, 0x01, 
  /* ABS: 004 Pixels @ 062,007 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 020 Pixels @ 002,008 */ 20, 0x01, 
  /* ABS: 002 Pixels @ 022,008 */ 0, 2, 0x32, 0x53, 
  /* RLE: 016 Pixels @ 024,008 */ 16, 0x02, 
  /* ABS: 002 Pixels @ 040,008 */ 0, 2, 0x15, 0x79, 
  /* RLE: 020 Pixels @ 042,008 */ 20, 0x01, 
  /* ABS: 004 Pixels @ 062,008 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 019 Pixels @ 002,009 */ 19, 0x01, 
  /* RLE: 001 Pixels @ 021,009 */ 1, 0x2D, 
  /* RLE: 019 Pixels @ 022,009 */ 19, 0x02, 
  /* ABS: 002 Pixels @ 041,009 */ 0, 2, 0x23, 0x31, 
  /* RLE: 019 Pixels @ 043,009 */ 19, 0x01, 
  /* ABS: 004 Pixels @ 062,009 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 018 Pixels @ 002,010 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 020,010 */ 1, 0x73, 
  /* RLE: 007 Pixels @ 021,010 */ 7, 0x02, 
  /* ABS: 008 Pixels @ 028,010 */ 0, 8, 0x58, 0x68, 0x34, 0x7C, 0x7B, 0x78, 0x67, 0x25, 
  /* RLE: 006 Pixels @ 036,010 */ 6, 0x02, 
  /* ABS: 002 Pixels @ 042,010 */ 0, 2, 0x24, 0x36, 
  /* RLE: 018 Pixels @ 044,010 */ 18, 0x01, 
  /* ABS: 004 Pixels @ 062,010 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 017 Pixels @ 002,011 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 019,011 */ 0, 2, 0x36, 0x23, 
  /* RLE: 005 Pixels @ 021,011 */ 5, 0x02, 
  /* ABS: 002 Pixels @ 026,011 */ 0, 2, 0x28, 0x7A, 
  /* RLE: 007 Pixels @ 028,011 */ 7, 0x01, 
  /* ABS: 003 Pixels @ 035,011 */ 0, 3, 0x19, 0x32, 0x26, 
  /* RLE: 005 Pixels @ 038,011 */ 5, 0x02, 
  /* ABS: 002 Pixels @ 043,011 */ 0, 2, 0x15, 0x86, 
  /* RLE: 017 Pixels @ 045,011 */ 17, 0x01, 
  /* ABS: 004 Pixels @ 062,011 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 016 Pixels @ 002,012 */ 16, 0x01, 
  /* ABS: 002 Pixels @ 018,012 */ 0, 2, 0x40, 0x59, 
  /* RLE: 005 Pixels @ 020,012 */ 5, 0x02, 
  /* ABS: 002 Pixels @ 025,012 */ 0, 2, 0x65, 0x8E, 
  /* RLE: 010 Pixels @ 027,012 */ 10, 0x01, 
  /* ABS: 002 Pixels @ 037,012 */ 0, 2, 0x3E, 0x60, 
  /* RLE: 005 Pixels @ 039,012 */ 5, 0x02, 
  /* RLE: 001 Pixels @ 044,012 */ 1, 0x2B, 
  /* RLE: 017 Pixels @ 045,012 */ 17, 0x01, 
  /* ABS: 004 Pixels @ 062,012 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 016 Pixels @ 002,013 */ 16, 0x01, 
  /* RLE: 001 Pixels @ 018,013 */ 1, 0x76, 
  /* RLE: 005 Pixels @ 019,013 */ 5, 0x02, 
  /* RLE: 001 Pixels @ 024,013 */ 1, 0x2C, 
  /* RLE: 013 Pixels @ 025,013 */ 13, 0x01, 
  /* ABS: 002 Pixels @ 038,013 */ 0, 2, 0x40, 0x16, 
  /* RLE: 005 Pixels @ 040,013 */ 5, 0x02, 
  /* RLE: 001 Pixels @ 045,013 */ 1, 0x37, 
  /* RLE: 016 Pixels @ 046,013 */ 16, 0x01, 
  /* ABS: 004 Pixels @ 062,013 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,014 */ 15, 0x01, 
  /* ABS: 002 Pixels @ 017,014 */ 0, 2, 0x92, 0x56, 
  /* RLE: 004 Pixels @ 019,014 */ 4, 0x02, 
  /* ABS: 002 Pixels @ 023,014 */ 0, 2, 0x5D, 0x19, 
  /* RLE: 014 Pixels @ 025,014 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 039,014 */ 0, 2, 0x3E, 0x25, 
  /* RLE: 004 Pixels @ 041,014 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 045,014 */ 1, 0x2B, 
  /* RLE: 016 Pixels @ 046,014 */ 16, 0x01, 
  /* ABS: 004 Pixels @ 062,014 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,015 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,015 */ 1, 0x83, 
  /* RLE: 004 Pixels @ 018,015 */ 4, 0x02, 
  /* ABS: 002 Pixels @ 022,015 */ 0, 2, 0x51, 0x82, 
  /* RLE: 016 Pixels @ 024,015 */ 16, 0x01, 
  /* RLE: 001 Pixels @ 040,015 */ 1, 0x77, 
  /* RLE: 004 Pixels @ 041,015 */ 4, 0x02, 
  /* ABS: 002 Pixels @ 045,015 */ 0, 2, 0x54, 0x8D, 
  /* RLE: 015 Pixels @ 047,015 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,015 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,016 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,016 */ 1, 0x6A, 
  /* RLE: 004 Pixels @ 018,016 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,016 */ 1, 0x5E, 
  /* RLE: 017 Pixels @ 023,016 */ 17, 0x01, 
  /* ABS: 002 Pixels @ 040,016 */ 0, 2, 0x19, 0x55, 
  /* RLE: 004 Pixels @ 042,016 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,016 */ 1, 0x09, 
  /* RLE: 015 Pixels @ 047,016 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,016 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,017 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,017 */ 1, 0x2A, 
  /* RLE: 004 Pixels @ 018,017 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,017 */ 1, 0x75, 
  /* RLE: 018 Pixels @ 023,017 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,017 */ 1, 0x66, 
  /* RLE: 004 Pixels @ 042,017 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,017 */ 1, 0x69, 
  /* RLE: 015 Pixels @ 047,017 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,017 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,018 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,018 */ 1, 0x5A, 
  /* RLE: 004 Pixels @ 018,018 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,018 */ 1, 0x7D, 
  /* RLE: 018 Pixels @ 023,018 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,018 */ 1, 0x74, 
  /* RLE: 004 Pixels @ 042,018 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,018 */ 1, 0x08, 
  /* RLE: 015 Pixels @ 047,018 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,018 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,019 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,019 */ 1, 0x26, 
  /* RLE: 004 Pixels @ 018,019 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,019 */ 1, 0x84, 
  /* RLE: 018 Pixels @ 023,019 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,019 */ 1, 0x35, 
  /* RLE: 004 Pixels @ 042,019 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,019 */ 1, 0x62, 
  /* RLE: 015 Pixels @ 047,019 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,019 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,020 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,020 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,020 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,020 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,020 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,020 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,020 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,020 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,020 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,020 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,021 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,021 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,021 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,021 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,021 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,021 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,021 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,021 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,021 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,021 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,022 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,022 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,022 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,022 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,022 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,022 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,022 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,022 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,022 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,022 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,023 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,023 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,023 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,023 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,023 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,023 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,023 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,023 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,023 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,023 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,024 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,024 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,024 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,024 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,024 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,024 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,024 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,024 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,024 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,024 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,025 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,025 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,025 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,025 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,025 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,025 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,025 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,025 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,025 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,025 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 015 Pixels @ 002,026 */ 15, 0x01, 
  /* RLE: 001 Pixels @ 017,026 */ 1, 0x0E, 
  /* RLE: 004 Pixels @ 018,026 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,026 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 023,026 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 041,026 */ 1, 0x10, 
  /* RLE: 004 Pixels @ 042,026 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,026 */ 1, 0x0F, 
  /* RLE: 015 Pixels @ 047,026 */ 15, 0x01, 
  /* ABS: 004 Pixels @ 062,026 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,027 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,027 */ 1, 0x33, 
  /* RLE: 004 Pixels @ 013,027 */ 4, 0x0B, 
  /* RLE: 001 Pixels @ 017,027 */ 1, 0x52, 
  /* RLE: 004 Pixels @ 018,027 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 022,027 */ 1, 0x28, 
  /* RLE: 018 Pixels @ 023,027 */ 18, 0x0B, 
  /* RLE: 001 Pixels @ 041,027 */ 1, 0x57, 
  /* RLE: 004 Pixels @ 042,027 */ 4, 0x02, 
  /* RLE: 001 Pixels @ 046,027 */ 1, 0x15, 
  /* RLE: 004 Pixels @ 047,027 */ 4, 0x0B, 
  /* RLE: 001 Pixels @ 051,027 */ 1, 0x33, 
  /* RLE: 010 Pixels @ 052,027 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,027 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,028 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,028 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,028 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,028 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,028 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,028 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,029 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,029 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,029 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,029 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,029 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,029 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,030 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,030 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,030 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,030 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,030 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,030 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,031 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,031 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x16, 
  /* RLE: 030 Pixels @ 017,031 */ 30, 0x09, 
  /* ABS: 005 Pixels @ 047,031 */ 0, 5, 0x16, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,031 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,031 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,032 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,032 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 030 Pixels @ 017,032 */ 30, 0x01, 
  /* ABS: 005 Pixels @ 047,032 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,032 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,032 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,033 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,033 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 030 Pixels @ 017,033 */ 30, 0x01, 
  /* ABS: 005 Pixels @ 047,033 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,033 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,033 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,034 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,034 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 004 Pixels @ 017,034 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 021,034 */ 1, 0x8F, 
  /* RLE: 025 Pixels @ 022,034 */ 25, 0x01, 
  /* ABS: 005 Pixels @ 047,034 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,034 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,034 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,035 */ 10, 0x01, 
  /* ABS: 012 Pixels @ 012,035 */ 0, 12, 0x05, 0x02, 0x02, 0x02, 0x06, 0x01, 0x01, 0x01, 0x71, 0x1C, 0x4F, 0x3D, 
  /* RLE: 023 Pixels @ 024,035 */ 23, 0x01, 
  /* ABS: 005 Pixels @ 047,035 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,035 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,035 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,036 */ 10, 0x01, 
  /* ABS: 014 Pixels @ 012,036 */ 0, 14, 0x05, 0x02, 0x02, 0x02, 0x06, 0x01, 0x01, 0x01, 0x30, 0x1B, 0x0A, 0x1D, 0x6E, 0x8C, 
  /* RLE: 021 Pixels @ 026,036 */ 21, 0x01, 
  /* ABS: 005 Pixels @ 047,036 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,036 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,036 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,037 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,037 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 004 Pixels @ 017,037 */ 4, 0x01, 
  /* ABS: 007 Pixels @ 021,037 */ 0, 7, 0x3B, 0x22, 0x0A, 0x0A, 0x1E, 0x2E, 0x41, 
  /* RLE: 019 Pixels @ 028,037 */ 19, 0x01, 
  /* ABS: 005 Pixels @ 047,037 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,037 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,037 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,038 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,038 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 006 Pixels @ 017,038 */ 6, 0x01, 
  /* ABS: 006 Pixels @ 023,038 */ 0, 6, 0x39, 0x21, 0x0A, 0x0A, 0x20, 0x38, 
  /* RLE: 018 Pixels @ 029,038 */ 18, 0x01, 
  /* ABS: 005 Pixels @ 047,038 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,038 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,038 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,039 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,039 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 007 Pixels @ 017,039 */ 7, 0x01, 
  /* ABS: 007 Pixels @ 024,039 */ 0, 7, 0x42, 0x2F, 0x1F, 0x0A, 0x0A, 0x0C, 0x3A, 
  /* RLE: 016 Pixels @ 031,039 */ 16, 0x01, 
  /* ABS: 005 Pixels @ 047,039 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,039 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,039 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,040 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,040 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 009 Pixels @ 017,040 */ 9, 0x01, 
  /* ABS: 006 Pixels @ 026,040 */ 0, 6, 0x89, 0x4B, 0x0A, 0x0A, 0x45, 0x7E, 
  /* RLE: 015 Pixels @ 032,040 */ 15, 0x01, 
  /* ABS: 005 Pixels @ 047,040 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,040 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,040 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,041 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,041 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 007 Pixels @ 017,041 */ 7, 0x01, 
  /* ABS: 007 Pixels @ 024,041 */ 0, 7, 0x42, 0x2F, 0x1F, 0x0A, 0x0A, 0x0C, 0x3A, 
  /* RLE: 016 Pixels @ 031,041 */ 16, 0x01, 
  /* ABS: 005 Pixels @ 047,041 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,041 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,041 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,042 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,042 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 006 Pixels @ 017,042 */ 6, 0x01, 
  /* ABS: 006 Pixels @ 023,042 */ 0, 6, 0x39, 0x21, 0x0A, 0x0A, 0x20, 0x38, 
  /* RLE: 018 Pixels @ 029,042 */ 18, 0x01, 
  /* ABS: 005 Pixels @ 047,042 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,042 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,042 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,043 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,043 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 004 Pixels @ 017,043 */ 4, 0x01, 
  /* ABS: 007 Pixels @ 021,043 */ 0, 7, 0x3B, 0x22, 0x0A, 0x0A, 0x1E, 0x2E, 0x41, 
  /* RLE: 019 Pixels @ 028,043 */ 19, 0x01, 
  /* ABS: 005 Pixels @ 047,043 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,043 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,043 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,044 */ 10, 0x01, 
  /* ABS: 014 Pixels @ 012,044 */ 0, 14, 0x05, 0x02, 0x02, 0x02, 0x06, 0x01, 0x01, 0x01, 0x30, 0x1B, 0x0A, 0x1D, 0x6D, 0x8B, 
  /* RLE: 021 Pixels @ 026,044 */ 21, 0x01, 
  /* ABS: 005 Pixels @ 047,044 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,044 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,044 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,045 */ 10, 0x01, 
  /* ABS: 012 Pixels @ 012,045 */ 0, 12, 0x05, 0x02, 0x02, 0x02, 0x06, 0x01, 0x01, 0x01, 0x70, 0x1C, 0x4E, 0x3D, 
  /* RLE: 023 Pixels @ 024,045 */ 23, 0x01, 
  /* ABS: 005 Pixels @ 047,045 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,045 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,045 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,046 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,046 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 004 Pixels @ 017,046 */ 4, 0x01, 
  /* RLE: 001 Pixels @ 021,046 */ 1, 0x04, 
  /* RLE: 025 Pixels @ 022,046 */ 25, 0x01, 
  /* ABS: 005 Pixels @ 047,046 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,046 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,046 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,047 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,047 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 014 Pixels @ 017,047 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 031,047 */ 0, 2, 0x7F, 0x4D, 
  /* RLE: 011 Pixels @ 033,047 */ 11, 0x0C, 
  /* ABS: 008 Pixels @ 044,047 */ 0, 8, 0x72, 0x01, 0x01, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,047 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,047 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,048 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,048 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 014 Pixels @ 017,048 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 031,048 */ 1, 0x6F, 
  /* RLE: 012 Pixels @ 032,048 */ 12, 0x0A, 
  /* ABS: 008 Pixels @ 044,048 */ 0, 8, 0x4C, 0x01, 0x01, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,048 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,048 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,049 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,049 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 014 Pixels @ 017,049 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 031,049 */ 0, 2, 0x90, 0x80, 
  /* RLE: 011 Pixels @ 033,049 */ 11, 0x0D, 
  /* ABS: 008 Pixels @ 044,049 */ 0, 8, 0x18, 0x01, 0x01, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,049 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,049 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,050 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,050 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 030 Pixels @ 017,050 */ 30, 0x01, 
  /* ABS: 005 Pixels @ 047,050 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,050 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,050 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,051 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,051 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 030 Pixels @ 017,051 */ 30, 0x01, 
  /* ABS: 005 Pixels @ 047,051 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,051 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,051 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,052 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,052 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x06, 
  /* RLE: 030 Pixels @ 017,052 */ 30, 0x01, 
  /* ABS: 005 Pixels @ 047,052 */ 0, 5, 0x06, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,052 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,052 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,053 */ 10, 0x01, 
  /* ABS: 005 Pixels @ 012,053 */ 0, 5, 0x05, 0x02, 0x02, 0x02, 0x27, 
  /* RLE: 030 Pixels @ 017,053 */ 30, 0x08, 
  /* ABS: 005 Pixels @ 047,053 */ 0, 5, 0x27, 0x02, 0x02, 0x02, 0x05, 
  /* RLE: 010 Pixels @ 052,053 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,053 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,054 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,054 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,054 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,054 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,054 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,054 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,055 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,055 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,055 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,055 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,055 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,055 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,056 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,056 */ 1, 0x05, 
  /* RLE: 038 Pixels @ 013,056 */ 38, 0x02, 
  /* RLE: 001 Pixels @ 051,056 */ 1, 0x05, 
  /* RLE: 010 Pixels @ 052,056 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,056 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 010 Pixels @ 002,057 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 012,057 */ 1, 0x3C, 
  /* RLE: 038 Pixels @ 013,057 */ 38, 0x07, 
  /* RLE: 001 Pixels @ 051,057 */ 1, 0x3C, 
  /* RLE: 010 Pixels @ 052,057 */ 10, 0x01, 
  /* ABS: 004 Pixels @ 062,057 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 060 Pixels @ 002,058 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,058 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 060 Pixels @ 002,059 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,059 */ 0, 4, 0x04, 0x03, 0x03, 0x04, 
  /* RLE: 060 Pixels @ 002,060 */ 60, 0x01, 
  /* ABS: 004 Pixels @ 062,060 */ 0, 4, 0x04, 0x03, 0x12, 0x17, 
  /* RLE: 060 Pixels @ 002,061 */ 60, 0x01, 
  /* ABS: 005 Pixels @ 062,061 */ 0, 5, 0x8A, 0x1A, 0x46, 0x61, 0x3F, 
  /* RLE: 058 Pixels @ 003,062 */ 58, 0x01, 
  /* ABS: 006 Pixels @ 061,062 */ 0, 6, 0x3F, 0x50, 0x14, 0x13, 0x14, 0x12, 
  /* RLE: 058 Pixels @ 003,063 */ 58, 0x03, 
  /* ABS: 003 Pixels @ 061,063 */ 0, 3, 0x43, 0x44, 0x13, 
  0
};  // 1524 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmIcon_emSSH_64x64 = {
  64, // xSize
  64, // ySize
  64, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acIcon_emSSH_64x64,  // Pointer to picture data (indices)
  &_PalIcon_emSSH_64x64,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/