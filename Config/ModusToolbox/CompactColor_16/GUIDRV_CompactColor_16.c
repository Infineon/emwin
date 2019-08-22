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
File        : GUIDRV_CompactColor_16.c
Purpose     : Driver for the following display controllers:

              - 1 x Ampire:         FSA506
              - 3 x Epson:          S1D13742, S1D13743, S1D19122
              - 1 x FocalTech:      FT1509
              - 8 x Himax:          HX8301, HX8312A, HX8347, HX8340, HX8352, HX8352B, HX8353, HX8325A
              - 3 x Hitachi:        HD66766, HD66772, HD66789
              - 8 x Ilitek:         ILI9161, ILI9220, ILI9221, ILI9320, ILI9325, ILI9326, ILI9328, ILI9342
              - 2 x LG Electronics: LGDP4531, LGDP4551
              - 1 x MagnaChip:      D54E4PA7551
              - 2 x Novatek:        NT39122, NT7573
              - 4 x OriseTech:      SPFD5408, SPFD5420A, SPFD5414D, SPFD54124C
              - 5 x Renesas:        R61505, R61509, R61516, R61526, R61580, R63401
              - 3 x Samsung:        S6D0110A, S6D0117, S6D0129
              - 2 x Sharp:          LR38825, LCY-A06003
              - 6 x Sitronix:       ST7712, ST7628, ST7637, ST7687, ST7735, ST7787, ST7715
              - 7 x Solomon:        SSD1289, SSD1298, SSD1355, SSD1963, SSD2119, SSD1284, SSD1961
              - 1 x Toshiba:        JBT6K71
              
              Configuration of LCD_CONTROLLER:
              
              - 66700: Sharp LR38825
              - 66701: Renesas R63401, R61509
                       OriseTech SPFD5420A
                       Ilitek ILI9326
              - 66702: Solomon SSD1284, SSD1289, SSD1298
              - 66703: Toshiba JBT6K71
              - 66704: Sharp LCY-A06003
              - 66705: Samsung S6D0129
              - 66706: MagnaChip D54E4PA7551
              - 66707: Himax HX8312A
              - 66708: FocalTech FT1509
                       Ilitek ILI9320, ILI9325, ILI9328
                       LG Electronics LGDP4531, LGDP4551
                       OriseTech SPFD5408
                       Renesas R61505, R61580
              - 66709: Epson S1D19122
                       Himax HX8353, HX8325A
                       Ilitek ILI9342
                       Novatek NT39122
                       Orisetech SPFD54124C, SPFD5414D
                       Renesas R61516, R61526
                       Sitronix ST7628, ST7637, ST7687, ST7735, ST7715
                       Solomon SSD1355, SSD1961, SSD1963
              - 66710: Novatek NT7573
              - 66711: Epson S1D13742, S1D13743
              - 66712: Himax HX8347, HX8352
              - 66713: Himax HX8340
              - 66714: Solomon SSD2119
              - 66715: Himax HX8352B
              - 66716: Ampire FSA506
              - 66717: Sitronix ST7787
              - 66766: Hitachi HD66766
                       Samsung S6D0110A
                       Ilitek ILI9161
              - 66772: Hitachi HD66772
                       Samsung S6D0117
                       Sitronix ST7712
                       Himax HX8301
                       Ilitek ILI9220, ILI9221
              - 66789: Hitachi HD66789
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "LCD_Private.h"      /* private module definitions & config */
#include "GUI_Private.h"

#include "GUIDRV_CompactColor_16.h"

//
// Define display driver API table name
//
#ifndef   DISPLAY_DRIVER_API
  #define DISPLAY_DRIVER_API GUIDRV_CompactColor_16_API
#endif

#if defined(LCD_USE_COMPACT_COLOR_16) && \
    (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

//
// Rename simulation routines
//
#define SIM_SetVRAMSize   SIM_CompactColor_16_SetVRAMSize
#define SIM_WriteMA1C0    SIM_CompactColor_16_WriteMA1C0
#define SIM_WriteMA0C0    SIM_CompactColor_16_WriteMA0C0
#define SIM_ReadMA1C0     SIM_CompactColor_16_ReadMA1C0
#define SIM_WriteA0C0     SIM_CompactColor_16_WriteA0C0
#define SIM_WriteA1C0     SIM_CompactColor_16_WriteA1C0
#define SIM_WriteMA1C0_16 SIM_CompactColor_16_WriteMA1C0_16
#define SIM_WriteMA0C0_16 SIM_CompactColor_16_WriteMA0C0_16
#define SIM_ReadMA1C0_16  SIM_CompactColor_16_ReadMA1C0_16
#define SIM_WriteA0C0_16  SIM_CompactColor_16_WriteA0C0_16
#define SIM_WriteA1C0_16  SIM_CompactColor_16_WriteA1C0_16

//
// Rename LCD_L0_xxx
//
#define LCD_L0_SetPixelIndex LCD_L0_CompactColor_16_SetPixelIndex
#define LCD_L0_GetPixelIndex LCD_L0_CompactColor_16_GetPixelIndex
#define LCD_L0_XorPixel      LCD_L0_CompactColor_16_XorPixel     
#define LCD_L0_DrawHLine     LCD_L0_CompactColor_16_DrawHLine    
#define LCD_L0_DrawVLine     LCD_L0_CompactColor_16_DrawVLine    
#define LCD_L0_FillRect      LCD_L0_CompactColor_16_FillRect     
#define LCD_L0_DrawBitmap    LCD_L0_CompactColor_16_DrawBitmap   
#define LCD_L0_SetOrg        LCD_L0_CompactColor_16_SetOrg       
#define LCD_L0_On            LCD_L0_CompactColor_16_On           
#define LCD_L0_Off           LCD_L0_CompactColor_16_Off          
#define LCD_L0_Init          LCD_L0_CompactColor_16_Init         
#define LCD_L0_SetLUTEntry   LCD_L0_CompactColor_16_SetLUTEntry  
#define LCD_L0_GetDevFunc    LCD_L0_CompactColor_16_GetDevFunc   
#define LCD_L0_ControlCache  LCD_L0_CompactColor_16_ControlCache
#define LCD_L0_Refresh       LCD_L0_CompactColor_16_Refresh

//
// Include driver specific configuration file
//
#include "LCDConf_CompactColor_16.h"

//
// Include software adapter
//
#include "GUIDRV_Generic.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#ifndef   LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif
#ifndef   LCD_CACHE
  #define LCD_CACHE           0
#else
  #if (LCD_SWAP_XY)
    #error Cache can only be used without swapping X and Y!
  #endif
#endif
#ifndef   LCD_SET_ORG
  #define LCD_SET_ORG(x, y) GUI_USE_PARA(x); GUI_USE_PARA(y)
#endif
#ifndef   LCD_WRITE_BUFFER_SIZE
  #define LCD_WRITE_BUFFER_SIZE 500
#endif
#ifndef   LCD_USE_SERIAL_3PIN
  #define LCD_USE_SERIAL_3PIN 0
#endif
#ifndef   LCD_USE_PARALLEL_16
  #define LCD_USE_PARALLEL_16 0
#endif
#ifndef   LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif
#ifndef   LCD_SUPPORT_CACHECONTROL
  #define LCD_SUPPORT_CACHECONTROL 0
#endif
#ifndef   LCD_NUM_DUMMY_READS
  #if   (LCD_CONTROLLER == 66702)                               /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66705) && (LCD_USE_PARALLEL_16 == 0) /* Samsung S6D0129 */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66706) && (LCD_USE_PARALLEL_16 == 0) /* MagnaChip D54E4PA7551 */
    #define LCD_NUM_DUMMY_READS 0
  #elif (LCD_CONTROLLER == 66707) && (LCD_USE_PARALLEL_16 == 1) /* Himax HX8312A */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66708) && (LCD_USE_PARALLEL_16 == 1)
    #define LCD_NUM_DUMMY_READS 1 /* Dummy reads currently need to be managed by HW routine!!! */
  #elif (LCD_CONTROLLER == 66709)                               /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66712)                               /* Himax HX8347, Himax HX8352 */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66713)                               /* Himax HX8340 */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66714)                               /* Solomon SSD2119 */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66715)                               /* Himax HX8352B */
    #define LCD_NUM_DUMMY_READS 1
  #elif (LCD_CONTROLLER == 66716)                               /* Ampire FSA506 */
    #define LCD_NUM_DUMMY_READS 0
  #elif (LCD_CONTROLLER == 66717)                               /* Sitronix ST7787 */
    #define LCD_NUM_DUMMY_READS 1
  #else
    #define LCD_NUM_DUMMY_READS 2 /* If parallel interface is used most of 
                                     the supported controllers need 2 dummy reads (default).
                                     If serial interface is used most controllers need 5 dummy reads */
  #endif
#endif

#if LCD_USE_PARALLEL_16 && LCD_USE_SERIAL_3PIN
  #error Illegal bus configuration!
#endif

/*********************************************************************
*
*       Macros for simulation
*/
#ifdef WIN32
  #if   LCD_DISPLAY_INDEX == 1
    #define SIM_WriteMA1C0 SIM_WriteMA1C0_1
    #define SIM_WriteMA0C0 SIM_WriteMA0C0_1
    #define SIM_ReadMA1C0  SIM_ReadA1C0_1
    #define SIM_WriteA0C0  SIM_WriteA0C0_1
    #define SIM_WriteA1C0  SIM_WriteA1C0_1
  #elif LCD_DISPLAY_INDEX == 2
    #define SIM_WriteMA1C0 SIM_WriteMA1C0_2
    #define SIM_WriteMA0C0 SIM_WriteMA0C0_2
    #define SIM_ReadMA1C0  SIM_ReadA1C0_2
    #define SIM_WriteA0C0  SIM_WriteA0C0_2
    #define SIM_WriteA1C0  SIM_WriteA1C0_2
  #elif LCD_DISPLAY_INDEX == 3
    #define SIM_WriteMA1C0 SIM_WriteMA1C0_3
    #define SIM_WriteMA0C0 SIM_WriteMA0C0_3
    #define SIM_ReadMA1C0  SIM_ReadA1C0_3
    #define SIM_WriteA0C0  SIM_WriteA0C0_3
    #define SIM_WriteA1C0  SIM_WriteA1C0_3
  #elif LCD_DISPLAY_INDEX == 4
    #define SIM_WriteMA1C0 SIM_WriteMA1C0_4
    #define SIM_WriteMA0C0 SIM_WriteMA0C0_4
    #define SIM_ReadMA1C0  SIM_ReadA1C0_4
    #define SIM_WriteA0C0  SIM_WriteA0C0_4
    #define SIM_WriteA1C0  SIM_WriteA1C0_4
  #elif LCD_DISPLAY_INDEX == 5
    #define SIM_WriteMA1C0 SIM_WriteMA1C0_5
    #define SIM_WriteMA0C0 SIM_WriteMA0C0_5
    #define SIM_ReadMA1C0  SIM_ReadA1C0_5
    #define SIM_WriteA0C0  SIM_WriteA0C0_5
    #define SIM_WriteA1C0  SIM_WriteA1C0_5
  #endif
  #undef LCD_SET_ORG
  #define LCD_SET_ORG(x, y)          GUI_USE_PARA(x); GUI_USE_PARA(y)
  #if LCD_USE_SERIAL_3PIN
    #undef LCD_SETCS
    #undef LCD_CLRCS
    #undef LCD_WRITEM
    #undef LCD_READM
    void SIM_WriteMC0(U8 * pData, int NumBytes);
    void SIM_ReadMC0 (U8 * pData, int NumBytes);
    void SIM_SetCS(void);
    void SIM_ClrCS(void);
    #define LCD_WRITEM(p, NumBytes) SIM_WriteMC0(p, NumBytes) 
    #define LCD_READM(p, NumBytes)  SIM_ReadMC0(p, NumBytes) 
    #define LCD_SETCS()             SIM_SetCS()
    #define LCD_CLRCS()             SIM_ClrCS()
  #elif LCD_USE_PARALLEL_16
    #undef LCD_WRITEM_A0
    #undef LCD_WRITEM_A1
    #undef LCD_READM_A1
    #undef LCD_WRITE_A0
    #undef LCD_WRITE_A1
    void SIM_WriteMA1C0_16(U16 * pData, int NumBytes);
    void SIM_WriteMA0C0_16(U16 * pData, int NumBytes);
    void SIM_ReadMA1C0_16 (U16 * pData, int NumBytes);
    void SIM_WriteA0C0_16 (U16 Byte);
    void SIM_WriteA1C0_16 (U16 Byte);
    #define LCD_WRITEM_A1(p, NumBytes) SIM_WriteMA1C0_16(p, NumBytes) 
    #define LCD_WRITEM_A0(p, NumBytes) SIM_WriteMA0C0_16(p, NumBytes) 
    #define LCD_READM_A1(p, NumBytes)  SIM_ReadMA1C0_16(p, NumBytes) 
    #define LCD_WRITE_A0(Byte)         SIM_WriteA0C0_16(Byte)
    #define LCD_WRITE_A1(Byte)         SIM_WriteA1C0_16(Byte)
  #else
    #undef LCD_WRITEM_A0
    #undef LCD_WRITEM_A1
    #undef LCD_READM_A1
    #undef LCD_WRITE_A0
    #undef LCD_WRITE_A1
    void SIM_WriteMA1C0(U8 * pData, int NumBytes);
    void SIM_WriteMA0C0(U8 * pData, int NumBytes);
    void SIM_ReadMA1C0 (U8 * pData, int NumBytes);
    void SIM_WriteA0C0 (U8 Byte);
    void SIM_WriteA1C0 (U8 Byte);
    #define LCD_WRITEM_A1(p, NumBytes) SIM_WriteMA1C0(p, NumBytes) 
    #define LCD_WRITEM_A0(p, NumBytes) SIM_WriteMA0C0(p, NumBytes) 
    #define LCD_READM_A1(p, NumBytes)  SIM_ReadMA1C0(p, NumBytes) 
    #define LCD_WRITE_A0(Byte)         SIM_WriteA0C0(Byte)
    #define LCD_WRITE_A1(Byte)         SIM_WriteA1C0(Byte)
  #endif
#endif

/*********************************************************************
*
*       Remap hardware access macros
*/
#if (GUI_NUM_LAYERS > 1) && (!defined(WIN32))
  #ifdef   LCD_WRITE_A0
    #undef LCD_WRITE_A0
  #endif
  #ifdef   LCD_WRITE_A1
    #undef LCD_WRITE_A1
  #endif
  #ifdef   LCD_WRITEM_A1
    #undef LCD_WRITEM_A1
  #endif
  #ifdef   LCD_READ_A0
    #undef LCD_READ_A0
  #endif
  #ifdef   LCD_READ_A1
    #undef LCD_READ_A1
  #endif
  #if   LCD_DISPLAY_INDEX == 0
    #define LCD_WRITE_A0    LCD_WRITE_A0_0
    #define LCD_WRITE_A1    LCD_WRITE_A1_0
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_0
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_0
    #define LCD_READ_A0     LCD_READ_A0_0
    #define LCD_READ_A1     LCD_READ_A1_0
    #define LCD_READM_A1    LCD_READM_A1_0
  #elif   LCD_DISPLAY_INDEX == 1
    #define LCD_WRITE_A0    LCD_WRITE_A0_1
    #define LCD_WRITE_A1    LCD_WRITE_A1_1
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_1
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_1
    #define LCD_READ_A0     LCD_READ_A0_1
    #define LCD_READ_A1     LCD_READ_A1_1
    #define LCD_READM_A1    LCD_READM_A1_1
  #elif LCD_DISPLAY_INDEX == 2
    #define LCD_WRITE_A0    LCD_WRITE_A0_2
    #define LCD_WRITE_A1    LCD_WRITE_A1_2
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_2
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_2
    #define LCD_READ_A0     LCD_READ_A0_2
    #define LCD_READ_A1     LCD_READ_A1_2
    #define LCD_READM_A1    LCD_READM_A1_2
  #elif LCD_DISPLAY_INDEX == 3
    #define LCD_WRITE_A0    LCD_WRITE_A0_3
    #define LCD_WRITE_A1    LCD_WRITE_A1_3
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_3
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_3
    #define LCD_READ_A0     LCD_READ_A0_3
    #define LCD_READ_A1     LCD_READ_A1_3
    #define LCD_READM_A1    LCD_READM_A1_3
  #elif LCD_DISPLAY_INDEX == 4
    #define LCD_WRITE_A0    LCD_WRITE_A0_4
    #define LCD_WRITE_A1    LCD_WRITE_A1_4
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_4
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_4
    #define LCD_READ_A0     LCD_READ_A0_4
    #define LCD_READ_A1     LCD_READ_A1_4
    #define LCD_READM_A1    LCD_READM_A1_4
  #elif LCD_DISPLAY_INDEX == 5
    #define LCD_WRITE_A0    LCD_WRITE_A0_5
    #define LCD_WRITE_A1    LCD_WRITE_A1_5
    #define LCD_WRITEM_A0   LCD_WRITEM_A0_5
    #define LCD_WRITEM_A1   LCD_WRITEM_A1_5
    #define LCD_READ_A0     LCD_READ_A0_5
    #define LCD_READ_A1     LCD_READ_A1_5
    #define LCD_READM_A1    LCD_READM_A1_5
  #else
    #error This display index not yet supported
  #endif
#else
  #define LCD_READDATA0   LCD_READ_A1
  #define LCD_WRITECMD0   LCD_WRITE_A0
  #define LCD_WRITEDATA0  LCD_WRITE_A1
#endif

#if LCD_CACHE
  #define READ_DATA() _ReadData()
#else
  #define READ_DATA() _ReadU16_A1()
#endif

/*********************************************************************
*
*       Macros for serial interface
*/
#if LCD_USE_SERIAL_3PIN
  /* Config macros */
  #ifndef   LCD_SERIAL_ID
    #define LCD_SERIAL_ID 0
  #endif
  /* Start byte definitions */
  #define START_BYTE_READ_DATA  ((14 << 3) | (LCD_SERIAL_ID << 2) | (1 << 1) | (1 << 0))
  #define START_BYTE_WRITE_DATA ((14 << 3) | (LCD_SERIAL_ID << 2) | (1 << 1) | (0 << 0))
  #define START_BYTE_WRITE_CMD  ((14 << 3) | (LCD_SERIAL_ID << 2) | (0 << 1) | (0 << 0))
  /* Macro mapping */
  #define WRITEM_A1(p, NumBytes) _WriteM_A1(p, NumBytes)
  #define WRITEM_A0(p, NumBytes) _WriteM_A0(p, NumBytes)
  #define READM_A1(p, NumBytes)  _ReadM_A1(p, NumBytes)

/*********************************************************************
*
*       Macros for parallel interface
*/
#else
  #define WRITEM_A1(p, NumBytes) LCD_WRITEM_A1(p, NumBytes)
  #define WRITEM_A0(p, NumBytes) LCD_WRITEM_A0(p, NumBytes)
  #define READM_A1(p, NumBytes)  LCD_READM_A1(p, NumBytes)
#endif

/*********************************************************************
*
*       Pixel access macros depending on cache settings
*/
#if LCD_CACHE
  #define PUSH_RECT 0
  #define POP_RECT  1

  #define SET_PIXEL_INDEX(x, y, Index)    _WriteCache(x, y, Index)
  #define GET_PIXEL_INDEX(x, y)           _ReadCache(x, y)
  #define _SET_CACHE_RECT(x0, y0, x1, y1) _SetCacheRect(x0, y0, x1, y1)
  #define _SET_CACHE_ADDR(x, y)           _SetCacheAddr(x, y)
  #define SET_SUB_RECT(x0, y0, x1, y1)    _SetSubRect(x0, y0, x1, y1)
  #define CLR_SUB_RECT()                  _ManageRect(POP_RECT)

  #if (LCD_SUPPORT_CACHECONTROL == 1)
    #define ADD_CACHE_RECT() _AddCacheRect()
  #else
    #define ADD_CACHE_RECT()
  #endif

#else
  #define SET_PIXEL_INDEX(x, y, Index)    LCD_L0_SetPixelIndex(x, y, Index)
  #define GET_PIXEL_INDEX(x, y)           LCD_L0_GetPixelIndex(x, y)
  #define _SET_CACHE_RECT(x0, y0, x1, y1)
  #define _SET_CACHE_ADDR(x, y)
  #define SET_SUB_RECT(x0, y0, x1, y1)    _SetRect(x0, y0, x1, y1)
  #define CLR_SUB_RECT()
#endif

/*********************************************************************
*
*       Register definitions
*/
#if   (LCD_CONTROLLER == 66766)    /* Hitachi HD66766, Samsung S6D0110A */
  /* Register definitions */
  #define REG_INC_MODE      0x05   /* - Entry mode */
  #define REG_SET_HRAM_POS  0x16   /* - Horizontal start-end address */
  #define REG_SET_VRAM_POS  0x17   /* - Vertical   start-end address */
  #define REG_RAM_ADDR_SET  0x21   /* - RAM address set */
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */
  /* Cache offset */
  #define CACHE_OFFSET      132

#elif (LCD_CONTROLLER == 66772) || /* Hitachi HD66772, Samsung S6D0117, Sitronix ST7712, Himax HX8301, Ilitek ILI9220, Ilitek ILI9221 */ \
      (LCD_CONTROLLER == 66789)    /* Hitachi HD66789 */
  /* Register definitions */
  #define REG_INC_MODE      0x03   /* - Entry mode */
  #define REG_SET_HRAM_POS  0x44   /* - Horizontal start-end address */
  #define REG_SET_VRAM_POS  0x45   /* - Vertical   start-end address */  
  #define REG_RAM_ADDR_SET  0x21   /* - RAM address set */      
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */

#elif (LCD_CONTROLLER == 66700)    /* Sharp LR38825 */
  /* Register definitions */
  #define REG_INC_MODE      0x18   /* - Entry mode */
  #define REG_SET_HRAM_S    0x12   /* - Horizontal start address */
  #define REG_SET_HRAM_E    0x15   /* - Horizontal end   address */
  #define REG_SET_VRAM_S    0x13   /* - Vertical   start address */
  #define REG_SET_VRAM_E    0x16   /* - Vertical   end address */
  #define REG_RAM_ADDR_H    0x14   /* - Horizontal RAM address */
  #define REG_RAM_ADDR_V    0x17   /* - Vertical   RAM address */

#elif (LCD_CONTROLLER == 66701)    /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */
  /* Register definitions */
  #define REG_INC_MODE      0x003  /* - Entry mode */
  #define REG_SET_HRAM_S    0x210  /* - Horizontal start address */ 
  #define REG_SET_HRAM_E    0x211  /* - Horizontal end   address */   
  #define REG_SET_VRAM_S    0x212  /* - Vertical   start address */ 
  #define REG_SET_VRAM_E    0x213  /* - Vertical   end address */   
  #define REG_RAM_ADDR_H    0x200  /* - Horizontal RAM address */   
  #define REG_RAM_ADDR_V    0x201  /* - Vertical   RAM address */   
  #define REG_RAM_ACCESS    0x202  /* - RAM access mode */
  /* Cache offset */
  #define CACHE_OFFSET      320

#elif (LCD_CONTROLLER == 66702)    /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */
  /* Register definitions */
  #define REG_INC_MODE      0x11   /* - Entry mode */
  #define REG_SET_HRAM_POS  0x44   /* - Horizontal start-end address */
  #define REG_SET_VRAM_S    0x45   /* - Vertical   start address */
  #define REG_SET_VRAM_E    0x46   /* - Vertical   end   address */  
  #define REG_RAM_ADDR_H    0x4E   /* - Horizontal RAM address */  
  #define REG_RAM_ADDR_V    0x4F   /* - Vertical   RAM address */  
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */         

#elif (LCD_CONTROLLER == 66703)    /* Toshiba JBT6K71 */
  /* Register definitions */
  #define REG_INC_MODE      0x003  /* - Entry mode */
  #define REG_SET_HRAM_S    0x406  /* - Horizontal start address */
  #define REG_SET_HRAM_E    0x407  /* - Horizontal end   address */  
  #define REG_SET_VRAM_S    0x408  /* - Vertical   start address */
  #define REG_SET_VRAM_E    0x409  /* - Vertical   end address */  
  #define REG_RAM_ADDR_H    0x200  /* - Horizontal RAM address */  
  #define REG_RAM_ADDR_V    0x201  /* - Vertical   RAM address */  
  #define REG_RAM_ACCESS    0x202  /* - RAM access mode */         

#elif (LCD_CONTROLLER == 66704)    /* Sharp LCY-A06003 */
  /* Register definitions */
  #define REG_INC_MODE      0x15   /* - Entry mode */
  #define REG_SET_HRAM_S    0x1A   /* - Horizontal start address */
  #define REG_SET_HRAM_E    0x1D   /* - Horizontal end   address */  
  #define REG_SET_VRAM_S_LB 0x1B   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x1C   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x1E   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x1F   /* - Vertical   end   address, high byte */
  #define REG_RAM_ADDR_H    0x16   /* - Horizontal RAM address */
  #define REG_RAM_ADDR_V_LB 0x17   /* - Vertical   RAM address, low  byte */  
  #define REG_RAM_ADDR_V_HB 0x18   /* - Vertical   RAM address, high byte */
  #define REG_RAM_ACCESS    0x0D   /* - RAM access mode */         

#elif (LCD_CONTROLLER == 66705)    /* Samsung S6D0129 */
  /* Register definitions */
  #define REG_INC_MODE      0x03   /* - Entry mode */
  #define REG_SET_HRAM_POS  0x46   /* - Horizontal start-end address */
  #define REG_SET_VRAM_S    0x48   /* - Vertical   start address */
  #define REG_SET_VRAM_E    0x47   /* - Vertical   end address */  
  #define REG_RAM_ADDR_LB   0x20   /* - RAM Address, low  byte */
  #define REG_RAM_ADDR_HB   0x21   /* - RAM Address, high byte */
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */

#elif (LCD_CONTROLLER == 66706)    /* MagnaChip D54E4PA7551 */
  /* Register definitions */
  #define REG_INC_MODE      0x1D   /* - Entry mode */                         
  #define REG_SET_HRAM_S    0x13   /* - Horizontal start address */           
  #define REG_SET_HRAM_E    0x16   /* - Horizontal end   address */           
  #define REG_SET_VRAM_S_LB 0x14   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x15   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x17   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x18   /* - Vertical   end   address, high byte */
  #define REG_RAM_ADDR_H    0x1A   /* - Horizontal RAM address */             
  #define REG_RAM_ADDR_V_LB 0x1B   /* - Vertical   RAM address, low  byte */  
  #define REG_RAM_ADDR_V_HB 0x1C   /* - Vertical   RAM address, high byte */  
  #define REG_RAM_ACCESS    0x03   /* - RAM access mode */                    

#elif (LCD_CONTROLLER == 66707)    /* Himax HX8312A */
  /* Register definitions */
  #define REG_INC_MODE_1    0x01   /* - Entry mode REG 0x01 */
  #define REG_INC_MODE_5    0x05   /* - Entry mode REG 0x05 */
  #define REG_SET_HRAM_S    0x45   /* - Horizontal start address */           
  #define REG_SET_HRAM_E    0x46   /* - Horizontal end   address */           
  #define REG_SET_VRAM_S_LB 0x48   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x47   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x4A   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x49   /* - Vertical   end   address, high byte */
  #define REG_RAM_ADDR_H    0x42   /* - Horizontal RAM address */             
  #define REG_RAM_ADDR_V_LB 0x44   /* - Vertical   RAM address, low  byte */  
  #define REG_RAM_ADDR_V_HB 0x43   /* - Vertical   RAM address, high byte */  

#elif (LCD_CONTROLLER == 66708)    /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */
  /* Register definitions */
  #define REG_INC_MODE      0x03   /* - Entry mode */              
  #define REG_SET_HRAM_S    0x50   /* - Horizontal start address */
  #define REG_SET_HRAM_E    0x51   /* - Horizontal end   address */
  #define REG_SET_VRAM_S    0x52   /* - Vertical   start address */
  #define REG_SET_VRAM_E    0x53   /* - Vertical   end address */  
  #define REG_RAM_ADDR_H    0x20   /* - Horizontal RAM address */  
  #define REG_RAM_ADDR_V    0x21   /* - Vertical   RAM address */  
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */         

#elif (LCD_CONTROLLER == 66709) || /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */ \
      (LCD_CONTROLLER == 66717)    /* Sitronix ST7787 */
  /* Register definitions */
  #define REG_INC_MODE      0x36   /* - Entry mode */              
  #define REG_CASET         0x2A   /* - Column address set */
  #define REG_RASET         0x2B   /* - Row    address set */
  #define REG_RAM_ACCESS_W  0x2C   /* - RAM write mode */         
  #define REG_RAM_ACCESS_R  0x2E   /* - RAM read  mode */         
  #define RAM_ADDR_SET         0   /* Display controller does not support
                                    * setting a RAM address. It always starts 
                                    * from XS/YS reading and writing! */
  #define MANAGE_ORIENTATION   0   /* - Orientation managed completely by controller */

#elif (LCD_CONTROLLER == 66710)    /* Novatek NT7573 */
  /* Register definitions */
  #define REG_INC_MODE      0x40   /* - Entry mode */
  #define REG_CASET         0x43   /* - Column address set */
  #define REG_RASET         0x42   /* - Row    address set */
  /* Cache offset */
  #define CACHE_OFFSET       132
  #define RAM_ADDR_SET         0   /* Display controller does not support
                                    * setting a RAM address. It always starts 
                                    * from XS/YS reading and writing! */

#elif (LCD_CONTROLLER == 66711)    /* Epson S1D13742, S1D13743 */
  /* Register definitions */
  #define REG_SET_HRAM_S_LB 0x38   /* - Horizontal start address, low  byte */
  #define REG_SET_HRAM_S_HB 0x3A   /* - Horizontal start address, high byte */
  #define REG_SET_HRAM_E_LB 0x40   /* - Horizontal end   address, low  byte */
  #define REG_SET_HRAM_E_HB 0x42   /* - Horizontal end   address, high byte */
  #define REG_SET_VRAM_S_LB 0x3C   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x3E   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x44   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x46   /* - Vertical   end   address, high byte */
  #define REG_MEM_DATA_PORT 0x48   /* - RAM access mode, write */
  #define REG_READ_ADDR_R0  0x4A   /* - RAM access mode, read, address register 0 */
  #define REG_READ_ADDR_R1  0x4C   /* - RAM access mode, read, address register 1 */
  #define REG_READ_ADDR_R2  0x4E   /* - RAM access mode, read, address register 2 */

#elif (LCD_CONTROLLER == 66712) || /* Himax HX8347, Himax HX8352 */ \
      (LCD_CONTROLLER == 66713) || /* Himax HX8340 */ \
      (LCD_CONTROLLER == 66715)    /* Himax HX8352B */
  /* Register definitions */
  #define REG_INC_MODE      0x16   /* - Entry mode */              
  #define REG_SET_HRAM_S_LB 0x03   /* - Horizontal start address, low  byte */
  #define REG_SET_HRAM_S_HB 0x02   /* - Horizontal start address, high byte */
  #define REG_SET_HRAM_E_LB 0x05   /* - Horizontal end   address, low  byte */
  #define REG_SET_HRAM_E_HB 0x04   /* - Horizontal end   address, high byte */
  #define REG_SET_VRAM_S_LB 0x07   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x06   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x09   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x08   /* - Vertical   end   address, high byte */
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */         
  #define MANAGE_ORIENTATION   0   /* - Orientation managed completely by controller */
  /* Please note that the HX8352B requires setting of additional registers (row- and column address counters) */
  #if (LCD_CONTROLLER == 66715)    /* Himax HX8352B */
    #define REG_CAC2        0x80
    #define REG_CAC1        0x81
    #define REG_RAC2        0x82
    #define REG_RAC1        0x83
  #endif

#elif (LCD_CONTROLLER == 66714)    /* Solomon SSD2119 */
  /* Register definitions */
  #define REG_INC_MODE      0x11   /* - Entry mode */
  #define REG_SET_VRAM_POS  0x44   /* - Horizontal start-end address */
  #define REG_SET_HRAM_S    0x45   /* - Vertical   start address */
  #define REG_SET_HRAM_E    0x46   /* - Vertical   end   address */  
  #define REG_RAM_ADDR_H    0x4E   /* - Horizontal RAM address */  
  #define REG_RAM_ADDR_V    0x4F   /* - Vertical   RAM address */  
  #define REG_RAM_ACCESS    0x22   /* - RAM access mode */         
  #define CACHE_OFFSET       320

#elif (LCD_CONTROLLER == 66716)    /* Ampire FSA506 */
  /* Register definitions */
  #define REG_SET_HRAM_S_LB 0x01   /* - Horizontal start address, low  byte */
  #define REG_SET_HRAM_S_HB 0x00   /* - Horizontal start address, high byte */
  #define REG_SET_HRAM_E_LB 0x03   /* - Horizontal end   address, low  byte */
  #define REG_SET_HRAM_E_HB 0x02   /* - Horizontal end   address, high byte */
  #define REG_SET_VRAM_S_LB 0x05   /* - Vertical   start address, low  byte */
  #define REG_SET_VRAM_S_HB 0x04   /* - Vertical   start address, high byte */
  #define REG_SET_VRAM_E_LB 0x07   /* - Vertical   end   address, low  byte */
  #define REG_SET_VRAM_E_HB 0x06   /* - Vertical   end   address, high byte */
  #define REG_RAM_ACCESS    0xC1   /* - RAM access mode */         
  #define MANAGE_ORIENTATION   0   /* - Orientation managed completely by controller */
  #define CACHE_OFFSET         0

#else
  #error Unsupported display controller!
#endif

#ifndef   MANAGE_ORIENTATION
  #define MANAGE_ORIENTATION 1
#endif

#ifndef   CACHE_OFFSET
  #define CACHE_OFFSET 0x100
#endif

#ifndef   RAM_ADDR_SET
  #define RAM_ADDR_SET 1
#endif

/*********************************************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*/
#if (MANAGE_ORIENTATION == 1)
  #if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) x
      #define LOG2PHYS_Y(x, y) y
    #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) y
      #define LOG2PHYS_Y(x, y) x
    #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) x
      #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
    #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) y
      #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
    #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
      #define LOG2PHYS_Y(x, y) y
    #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
      #define LOG2PHYS_Y(x, y) x
    #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
      #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
    #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
      #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
      #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
    #endif
  #else
    #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
      #define LOG2PHYS_X(x, y) x
      #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
    #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
      #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
      #define LOG2PHYS_Y(x, y) y
    #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
      #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
      #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
    #endif
  #endif
#else
  #define LOG2PHYS_X(x, y) x
  #define LOG2PHYS_Y(x, y) y
#endif

/*********************************************************************
*
*       Increment mode, contents of entry mode register
*/
#if (LCD_CONTROLLER == 66766) || /* HD66766, Samsung S6D0110A */ \
    (LCD_CONTROLLER == 66772) || /* Hitachi HD66772, Samsung S6D0117, Sitronix ST7712, Himax HX8301, Ilitek ILI9220, Ilitek ILI9221 */ \
    (LCD_CONTROLLER == 66789) || /* Hitachi HD66789 */ \
    (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
    (LCD_CONTROLLER == 66702) || /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */ \
    (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
    (LCD_CONTROLLER == 66705) || /* Samsung S6D0129 */ \
    (LCD_CONTROLLER == 66708) || /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */ \
    (LCD_CONTROLLER == 66714)    /* Solomon SSD2119 */
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB __XX____
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB __X_____
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ___X____
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ________
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB __XXX___
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB __X_X___
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB ___XX___
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB ____X___
  #endif
  #if (LCD_CONTROLLER == 66702) || (LCD_CONTROLLER == 66714)
    #define INC_MODE_HB _XX_X___
  #else
    #define INC_MODE_HB ________
  #endif
#elif (LCD_CONTROLLER == 66700) || /* Sharp LR38825 */ \
      (LCD_CONTROLLER == 66704)    /* Sharp LCY-A06003 */
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ________
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB _______X
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ______X_
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ______XX
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____X__
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____X_X
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____XX_
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____XXX
  #endif
#elif (LCD_CONTROLLER == 66706) /* MagnaChip D54E4PA7551 */
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ________
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB _____X__
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ______X_
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB _____XX_
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _______X
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____X_X
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB ______XX
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _____XXX
  #endif
#elif (LCD_CONTROLLER == 66707) /* Himax HX8312A */
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_R1 ________
    #define INC_MODE_R5 ___X____
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_R1 X_______
    #define INC_MODE_R5 ___X____
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_R1 _X______
    #define INC_MODE_R5 ___X____
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_R1 XX______
    #define INC_MODE_R5 ___X____
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_R1 ________
    #define INC_MODE_R5 ___X_X__
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_R1 X_______
    #define INC_MODE_R5 ___X_X__
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_R1 _X______
    #define INC_MODE_R5 ___X_X__
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_R1 XX______
    #define INC_MODE_R5 ___X_X__
  #endif
#elif (LCD_CONTROLLER == 66709) || /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */ \
      (LCD_CONTROLLER == 66712) || /* Himax HX8347, Himax HX8352 */ \
      (LCD_CONTROLLER == 66713) || /* Himax HX8340 */ \
      (LCD_CONTROLLER == 66715) || /* Himax HX8352B */ \
      (LCD_CONTROLLER == 66717)    /* Sitronix ST7787 */

  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB ________
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB _X______
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB X_______
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE_LB XX______
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB __X_____
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB _XX_____
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB X_X_____
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE_LB XXX_____
  #endif
#elif (LCD_CONTROLLER == 66710) /* Novatek NT7573 */
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE ________
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE ____X___
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE _____X__
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define INC_MODE ____XX__
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE ______X_
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE ____X_X_
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE _____XX_
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define INC_MODE ____XXX_
  #endif
  #if LCD_USE_PARALLEL_16
    #define INC_MODE_LB (INC_MODE | X_______)
  #else
    #define INC_MODE_LB (INC_MODE)
  #endif
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#if LCD_CACHE
  static U16 * _pVRam;
  static int _xPos, _yPos;
#endif

#if LCD_WRITE_BUFFER_SIZE

  #if LCD_USE_PARALLEL_16
    static U16 _WriteBuffer[LCD_WRITE_BUFFER_SIZE / 2];
  #else
    static U8 _WriteBuffer[LCD_WRITE_BUFFER_SIZE];
  #endif

  static int _NumPixelsInBuffer;

  #if LCD_USE_PARALLEL_16
    static U16 * _pBuffer;
  #else
    static U8  * _pBuffer;
  #endif

#endif

#if (LCD_USE_PARALLEL_16 == 0)
  static U8   _aPair[3 + LCD_NUM_DUMMY_READS];
#endif

#if (RAM_ADDR_SET || LCD_CACHE)
  static int  _x0, _y0, _x1, _y1;
#endif

#if LCD_CACHE
  static U32  _Addr;
#endif

static U16 _IndexMask;
static U16 * _pLineBuffer;

#if LCD_USE_SERIAL_3PIN
  static const U8 _StartByteReadData = START_BYTE_READ_DATA;
  #if LCD_CACHE
    static const U8 _StartByteWriteData = START_BYTE_WRITE_DATA;
  #endif
#endif

#if (LCD_CONTROLLER == 66711)
  static int _PhysRAMAddrX;
  static int _PhysRAMAddrY;
#endif

#if (LCD_SUPPORT_CACHECONTROL == 1)
  static int _CacheLocked;
  static int _CacheStat;
  static GUI_RECT _CacheRect;
#endif

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
#if LCD_USE_SERIAL_3PIN
/*********************************************************************
*
*       _WriteM_A1
*/
static void _WriteM_A1(U8 * p, int NumBytes) {
  #if LCD_CACHE
    LCD_CLRCS();
    LCD_WRITEM((U8 *)&_StartByteWriteData, 1);
    LCD_WRITEM(p, NumBytes);
    LCD_SETCS();
  #else
    *--p = START_BYTE_WRITE_DATA;
    LCD_CLRCS();
    LCD_WRITEM(p, NumBytes + 1);
    LCD_SETCS();
  #endif
}

/*********************************************************************
*
*       _WriteM_A0
*/
static void _WriteM_A0(U8 * p, int NumBytes) {
  *--p = START_BYTE_WRITE_CMD;
  LCD_CLRCS();
  LCD_WRITEM(p, NumBytes + 1);
  LCD_SETCS();
}

/*********************************************************************
*
*       _ReadM_A1
*/
static void _ReadM_A1(U8 * p, int NumBytes) {
  LCD_CLRCS();
  LCD_WRITEM((U8 *)&_StartByteReadData, 1);
  LCD_READM(p, NumBytes);
  LCD_SETCS();
}
#endif

/*********************************************************************
*
*       Static functions (common)
*
**********************************************************************
*/
/*********************************************************************
*
*       _WriteU16_A1
*/
static void _WriteU16_A1(U16 Word) {
  #if LCD_USE_PARALLEL_16
    WRITEM_A1(&Word, 1);
  #else
    _aPair[1] = Word >> 8;
    _aPair[2] = Word & 0xff;
    WRITEM_A1((U8 *)&_aPair[1], 2);
  #endif
}

/*********************************************************************
*
*       _WriteU16_A0
*/
static void _WriteU16_A0(U16 Word) {
  #if LCD_USE_PARALLEL_16
    WRITEM_A0(&Word, 1);
  #else
    _aPair[1] = Word >> 8;
    _aPair[2] = Word & 0xff;
    WRITEM_A0((U8 *)&_aPair[1], 2);
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#if (LCD_CONTROLLER == 66766) || /* HD66766, Samsung S6D0110A */ \
    (LCD_CONTROLLER == 66772) || /* Hitachi HD66772, Samsung S6D0117, Sitronix ST7712, Himax HX8301, Ilitek ILI9220, Ilitek ILI9221 */ \
    (LCD_CONTROLLER == 66789) || /* Hitachi HD66789 */ \
    (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
    (LCD_CONTROLLER == 66702) || /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */ \
    (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
    (LCD_CONTROLLER == 66705) || /* Samsung S6D0129 */ \
    (LCD_CONTROLLER == 66708) || /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */ \
    (LCD_CONTROLLER == 66710) || /* Novatek NT7573 */ \
    (LCD_CONTROLLER == 66714)    /* Solomon SSD2119 */
static U16 _ReadU16_A1(void) {
  #if LCD_USE_PARALLEL_16
    U16 aData[1 + LCD_NUM_DUMMY_READS];
    READM_A1(aData, 1 + LCD_NUM_DUMMY_READS);
    #if LCD_SWAP_RB
      return (aData[LCD_NUM_DUMMY_READS] & 0x07E0) | ((aData[LCD_NUM_DUMMY_READS] & 0x001F) << 11) | ((aData[LCD_NUM_DUMMY_READS] & 0xF800) >> 11);
    #else
      return aData[LCD_NUM_DUMMY_READS];
    #endif
  #else
    U16 Data;
    READM_A1((U8 *)_aPair, 2 + LCD_NUM_DUMMY_READS);
    Data = ((U16)_aPair[LCD_NUM_DUMMY_READS] << 8) | _aPair[LCD_NUM_DUMMY_READS + 1];
    return Data;
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66712)    /* Himax HX8347, Himax HX8352 */
static U16 _ReadU16_A1(void) {
  #if LCD_USE_PARALLEL_16
    /*
      Input:               Output:
      (written to ...)     (read from ...)

      0b0000000000000001   0x0000 0000 0008
      0b0000000000000010   0x0000 0000 0010
      0b0000000000000100   0x0000 0000 0020
      0b0000000000001000   0x0000 0000 0040
      0b0000000000010000   0x0000 0000 0084
      0b0000000000100000   0x0000 0004 0000
      0b0000000001000000   0x0000 0008 0000
      0b0000000010000000   0x0000 0010 0000
      0b0000000100000000   0x0000 0020 0000
      0b0000001000000000   0x0000 0040 0000
      0b0000010000000000   0x0000 0080 0000
      0b0000100000000000   0x0008 0000 0000
      0b0001000000000000   0x0010 0000 0000
      0b0010000000000000   0x0020 0000 0000
      0b0100000000000000   0x0040 0000 0000
      0b1000000000000000   0x0084 0000 0000

      Please note that this display controller does only support a color depth
      of 16bpp in combination with a 16 bit data bus interface.
    */
    U16 aData[3 + LCD_NUM_DUMMY_READS];
    U16 Result;

    READM_A1(aData, 3 + LCD_NUM_DUMMY_READS);
    Result  = (aData[LCD_NUM_DUMMY_READS + 2] & 0xF8) >> 3;
    Result |= (aData[LCD_NUM_DUMMY_READS + 1] & 0xFC) << 3;
    Result |= (aData[LCD_NUM_DUMMY_READS + 0] & 0xF8) << 8;
    return Result;
  #else
    U16 Data;
    READM_A1((U8 *)_aPair, 3 + LCD_NUM_DUMMY_READS);
    Data  = ((     _aPair[LCD_NUM_DUMMY_READS + 0]  & 0xF8) >> 3);
    Data |= (((U16)_aPair[LCD_NUM_DUMMY_READS + 1]  & 0xFC) << 3);
    Data |= (((U16)_aPair[LCD_NUM_DUMMY_READS + 2]  & 0xF8) << 8);
    return Data;
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66715)    /* Himax HX8352B */
static U16 _ReadU16_A1(void) {
  #if LCD_USE_PARALLEL_16
    U16 aData[2 + LCD_NUM_DUMMY_READS];
    U16 Result;

    READM_A1(aData, 2 + LCD_NUM_DUMMY_READS);
    Result  = (aData[LCD_NUM_DUMMY_READS + 0] & 0xF800);
    Result |= (aData[LCD_NUM_DUMMY_READS + 0] & 0x00FC) << 3;
    Result |= (aData[LCD_NUM_DUMMY_READS + 1] & 0xF800) >> 11;
    return Result;
  #else
    #error Currently not supported!
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66713)    /* Himax HX8340 */
static U16 _ReadU16_A1(void) {
  #if LCD_USE_PARALLEL_16
    U16 aData[3 + LCD_NUM_DUMMY_READS];
    U16 Result;

    READM_A1(aData, 3 + LCD_NUM_DUMMY_READS);
    Result  = (aData[LCD_NUM_DUMMY_READS + 2] & 0xF8) >> 3;
    Result |= (aData[LCD_NUM_DUMMY_READS + 0] & 0xFC) << 3;
    Result |= (aData[LCD_NUM_DUMMY_READS + 1] & 0xF8) << 8;
    return Result;
  #else
    /*
      This version of the driver has not been tested with the 8 bit bus
      interface. Please note that the documentation (V01 from 10/2007)
      contained nothing about reading data in 16bpp mode with an 8 bit bus.
    */
    #error This mode is currently not supported. Please contact support.
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66700) /* Sharp LR38825 */
static U16 _ReadU16_A1(void) {
  /* Reading format of LR38825 is fixed to 18 bit, so conversion to 16 bit format is required */
  #if LCD_USE_PARALLEL_16
    U16 aData[2 + LCD_NUM_DUMMY_READS], Result, Data;
    READM_A1(aData, 2 + LCD_NUM_DUMMY_READS);
    Data = aData[LCD_NUM_DUMMY_READS];
    Result = ((Data & 0xfff) >> 1) | ((Data & 0xe000) >> 2) | (aData[LCD_NUM_DUMMY_READS + 1] << 14);
    return Result;
  #else
    U8 aData[3 + LCD_NUM_DUMMY_READS];
    U16 Result;
    READM_A1(aData, 3 + LCD_NUM_DUMMY_READS);
    Result  = (((U16)aData[LCD_NUM_DUMMY_READS + 0] & 0xfe) >>  1);
    Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 1] & 0x0f) <<  7);
    Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 1] & 0xe0) <<  6);
    Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 2] & 0x03) << 14);
    return Result;
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66704) /* Sharp LCY-A06003 */
static U16 _ReadU16_A1(void) {
  U8 aData[3 + LCD_NUM_DUMMY_READS];
  U16 Result;
  READM_A1(aData, 3 + LCD_NUM_DUMMY_READS);
  Result  = (((U16)aData[LCD_NUM_DUMMY_READS + 0]       ) >>  1);
  Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 2]       ) <<  5);
  Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 1] & 0x3E) << 10);
  return Result;
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66706) /* MagnaChip D54E4PA7551 */
static U16 _ReadU16_A1(void) {
  U8 aData[3 + LCD_NUM_DUMMY_READS];
  U16 Result;
  READM_A1((U8 *)aData, 3 + LCD_NUM_DUMMY_READS);
  Result  = (((U16)aData[LCD_NUM_DUMMY_READS + 2]       ) >>  1);
  Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 1]       ) <<  5);
  Result |= (((U16)aData[LCD_NUM_DUMMY_READS + 0] & 0x3E) << 10);
  return Result;
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66707) /* Himax HX8312A */
static U16 _ReadU16_A1(void) {
  /* Reading the HX8312A with 16-bit serial interface selected (MPU9 Type) does
     not serve all required bits. So it is not possible to read back the exact
     value which has been written to a memory location in each case:
     
     Input:               Output:
     (written to HX8312A) (read from HX8312A)

     0b0000000000000001   0b0000010000000000
     0b0000000000000010   0b0000100000000000
     0b0000000000000100   0b0001000000000000
     0b0000000000001000   0b0010000000000000
     0b0000000000010000   0b1100000000000000
     0b0000000000100000   0b0000000000010000
     0b0000000001000000   0b0000000000100000
     0b0000000010000000   0b0000000001000000
     0b0000000100000000   0b0000000010000000
     0b0000001000000000   0b0000000100000000
     0b0000010000000000   0b0000001000000000
     0b0000100000000000   0b0000000000000000
     0b0001000000000000   0b0000000000000001
     0b0010000000000000   0b0000000000000010
     0b0100000000000000   0b0000000000000100
     0b1000000000000000   0b0000000000001000
  */
  #if LCD_USE_PARALLEL_16
    U16 aData[1 + LCD_NUM_DUMMY_READS] = {0};
    U16 Result;
    READM_A1(aData, 1 + LCD_NUM_DUMMY_READS);
    Result  = (((U16)aData[LCD_NUM_DUMMY_READS] & 0x000F) << 12);
    Result |= (((U16)aData[LCD_NUM_DUMMY_READS] & 0x03F0) <<  1);
    Result |= (((U16)aData[LCD_NUM_DUMMY_READS] & 0xFC00) >> 10);
    if (Result & 0x8000) {
      Result |= 0x0800;
    }
    return Result;
  #else
    #error Currently not supported. Please contact support.
  #endif
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66709) /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */

#if LCD_USE_PARALLEL_16
  #define DATA_2_INDEX(pData, Index) Index = ((*(pData + 1) & 0x00f8) >> 3) | /* 5 bits of red   */ \
                                             ((*(pData + 1) & 0xfc00) >> 5) | /* 6 bits of green */ \
                                             ((*(pData + 0) & 0x00f8) << 8)   /* 5 bits of blue  */
#else
  #define DATA_2_INDEX(pData, Index) Index = (     (*(pData + 2) >> 3)      ) | /* 5 bits of red   */ \
                                             ((U16)(*(pData + 1) >> 2) <<  5) | /* 6 bits of green */ \
                                             ((U16)(*(pData + 0) >> 3) << 11)   /* 5 bits of blue  */
#endif

static U16 _ReadU16_A1(void) {
  U16 Result;
  #if LCD_USE_PARALLEL_16
    /*
      Input:               Output:
      (written to ...)     (read from ...)

      0b0000000000000001   0x0000 0000 0008
      0b0000000000000010   0x0000 0000 0010
      0b0000000000000100   0x0000 0000 0020
      0b0000000000001000   0x0000 0000 0040
      0b0000000000010000   0x0000 0000 0084
      0b0000000000100000   0x0000 0000 0400
      0b0000000001000000   0x0000 0000 0800
      0b0000000010000000   0x0000 0000 1000
      0b0000000100000000   0x0000 0000 2000
      0b0000001000000000   0x0000 0000 4000
      0b0000010000000000   0x0000 0000 8000
      0b0000100000000000   0x0000 0008 0000
      0b0001000000000000   0x0000 0010 0000
      0b0010000000000000   0x0000 0020 0000
      0b0100000000000000   0x0000 0040 0000
      0b1000000000000000   0x0000 0084 0000
    */
    U16 aData[2 + LCD_NUM_DUMMY_READS] = {0};
    /*
    * Switch to RAM read mode
    */
    LCD_WRITE_A0(REG_RAM_ACCESS_R); /* RAM read mode */
    /*
    * Read 1 dummy word and 2 words of color information
    */
    READM_A1((unsigned short *)aData, 2 + LCD_NUM_DUMMY_READS);
  #else
    /*
      Input:               Output:
      (written to ...)     (read from ...)

      0b0000000000000001   0x00 00 00 08
      0b0000000000000010   0x00 00 00 10
      0b0000000000000100   0x00 00 00 20
      0b0000000000001000   0x00 00 00 40
      0b0000000000010000   0x00 00 00 84
      0b0000000000100000   0x00 00 04 00
      0b0000000001000000   0x00 00 08 00
      0b0000000010000000   0x00 00 10 00
      0b0000000100000000   0x00 00 20 00
      0b0000001000000000   0x00 00 40 00
      0b0000010000000000   0x00 00 80 00
      0b0000100000000000   0x00 08 00 00
      0b0001000000000000   0x00 10 00 00
      0b0010000000000000   0x00 20 00 00
      0b0100000000000000   0x00 40 00 00
      0b1000000000000000   0x00 84 00 00
    */
    U8 aData[3 + LCD_NUM_DUMMY_READS];
    /*
    * Switch to RAM read mode
    */
    LCD_WRITE_A0(REG_RAM_ACCESS_R); /* RAM read mode */
    /*
    * Read 1 dummy byte and 3 bytes color information
    */
    READM_A1((U8 *)aData, 3 + LCD_NUM_DUMMY_READS);
  #endif
  /*
  * Convert color information into 565 index value
  */
  DATA_2_INDEX(&aData[1], Result);
  return Result;
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66711) /* Epson S1D13742, S1D13743 */
static U16 _ReadU16_A1(void) {
  U16 Result;
  U32 Off;
  U32 Addr0; /* Used for red/green components located at memory offset 0x00000 */
  U32 Addr1; /* Used for blue      component  located at memory offset 0x4C000 */
  unsigned short Data;
  /*
    Address offset 0x00000 (red/green)

    Input:               Output:
    (written to ...)     (read from ...)
    (green)
    0b0000000000100000   0x0004
    0b0000000001000000   0x0008
    0b0000000010000000   0x0010
    0b0000000100000000   0x0020
    0b0000001000000000   0x0041
    0b0000010000000000   0x0082
    (red)
    0b0000100000000000   0x0800
    0b0001000000000000   0x1000
    0b0010000000000000   0x2100
    0b0100000000000000   0x4200
    0b1000000000000000   0x8400

    Address offset 0x4C000 (blue)

    (written to ...)     (read from ...)
    (blue)
    0b0000000000000001   0x0008
    0b0000000000000010   0x0010
    0b0000000000000100   0x0021
    0b0000000000001000   0x0042
    0b0000000000010000   0x0084
  */
  Off   = LCD_XSIZE * _PhysRAMAddrY + _PhysRAMAddrX;
  Addr0 = Off << 1;
  Addr1 = Off + 0x4C000;
  /* Getting red/green */
  LCD_WRITE_A0(REG_READ_ADDR_R0);
  LCD_WRITE_A1(((Addr0      ) & 0xff));
  LCD_WRITE_A0(REG_READ_ADDR_R1);
  LCD_WRITE_A1(((Addr0 >>  8) & 0xff));
  LCD_WRITE_A0(REG_READ_ADDR_R2);
  LCD_WRITE_A1(((Addr0 >> 16) & 0xff));
  LCD_WRITE_A0(REG_MEM_DATA_PORT);
  READM_A1(&Data, 1);
  Result  = (Data & 0xf800)     ; /* Red   RRRRRggggggbbbbb */
  Result |= (Data & 0x00fc) << 3; /* Green rrrrrGGGGGGbbbbb */
  /* Getting blue */
  LCD_WRITE_A0(REG_READ_ADDR_R0);
  LCD_WRITE_A1(((Addr1      ) & 0xff));
  LCD_WRITE_A0(REG_READ_ADDR_R1);
  LCD_WRITE_A1(((Addr1 >>  8) & 0xff));
  LCD_WRITE_A0(REG_READ_ADDR_R2);
  LCD_WRITE_A1(((Addr1 >> 16) & 0xff));
  LCD_WRITE_A0(REG_MEM_DATA_PORT);
  READM_A1(&Data, 1);
  if (_PhysRAMAddrX & 1) {
    Result |= (Data & 0xf800) >> 11; /* Blue  rrrrrggggggBBBBB */
  } else {
    Result |= (Data & 0x00f8) >>  3; /* Blue  rrrrrggggggBBBBB */
  }
  return Result;
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66716) /* Ampire FSA506 */
static U16 _ReadU16_A1(void) {
  U8 aData[2 + LCD_NUM_DUMMY_READS];
  U16 Result;
  
  READM_A1((U8 *)aData, 2 + LCD_NUM_DUMMY_READS);
  Result = aData[LCD_NUM_DUMMY_READS + 1] | ((U16)aData[LCD_NUM_DUMMY_READS + 0] << 8);
  return Result;
}

/*********************************************************************
*
*       _ReadU16_A1
*/
#elif (LCD_CONTROLLER == 66717) /* Sitronix ST7787 */

#define DATA_2_INDEX(pData, Index) Index = ((*(pData + 1) & 0xF800) >> 11) | \
                                           ((*(pData + 0) & 0x00FC) <<  3) | \
                                           ((*(pData + 1) & 0x00F8) <<  8)

static U16 _ReadU16_A1(void) {
  U16 Result;
  #if LCD_USE_PARALLEL_16
    /*
      Input:               Output:
      (written to ...)     (read from ...)

      0b0000000000000001   0x0000 0000 0C00 // Blue
      0b0000000000000010   0x0000 0000 1400
      0b0000000000000100   0x0000 0000 2400
      0b0000000000001000   0x0000 0000 4400
      0b0000000000010000   0x0000 0000 8400
      0b0000000000100000   0x0000 0004 0000 // Green
      0b0000000001000000   0x0000 0008 0000
      0b0000000010000000   0x0000 0010 0000
      0b0000000100000000   0x0000 0020 0000
      0b0000001000000000   0x0000 0040 0000
      0b0000010000000000   0x0000 0080 0000
      0b0000100000000000   0x0000 0C00 000C // Red
      0b0001000000000000   0x0000 1400 0014
      0b0010000000000000   0x0000 2400 0024
      0b0100000000000000   0x0000 4400 0044
      0b1000000000000000   0x0000 8400 0084
    */
    U16 aData[2 + LCD_NUM_DUMMY_READS] = {0};
    //
    // Switch to RAM read mode
    //
    LCD_WRITE_A0(REG_RAM_ACCESS_R); /* RAM read mode */
    //
    // Read 1 dummy word and 2 words of color information
    //
    READM_A1((unsigned short *)aData, 2 + LCD_NUM_DUMMY_READS);
  #else
    #error The Sitronix ST7787 currently can only be used with 16 bit interface. Please contact support on demand.
  #endif
  //
  // Calculate result
  //
  DATA_2_INDEX(&aData[1], Result);
  return Result;
}

#endif

#if LCD_CACHE

/*********************************************************************
*
*       _CalcCacheAddr
*/
static void _CalcCacheAddr(void) {
  #if   (CACHE_OFFSET == 256)
    _Addr = (_yPos << 8) + _xPos;                /* Avoid multiplication */
  #elif (CACHE_OFFSET == 132)
    _Addr = (_yPos << 7) + (_yPos << 2) + _xPos; /* Avoid multiplication */
  #elif (CACHE_OFFSET == 320)
    _Addr = (_yPos << 8) + (_yPos << 6) + _xPos; /* Avoid multiplication */
  #else
    {
      int CacheSize;

      #if (CACHE_OFFSET)
        CacheSize = CACHE_OFFSET;
      #else
        CacheSize = _xSize;
      #endif
      _Addr = (U32)_yPos * CacheSize + _xPos;
    }
  #endif
}

/*********************************************************************
*
*       _IncX
*/
static void _IncX(void) {
  #if (LCD_MIRROR_X == 0)
    /* Horizontal increment */
    if (_xPos < _x1) {
      _xPos++;
    } else {
      _xPos = _x0;
    }
  #else
    /* Horizontal decrement */
    if (_xPos > _x0) {
      _xPos--;
    } else {
      _xPos = _x1;
    }
  #endif
}

/*********************************************************************
*
*       _IncY
*/
static void _IncY(void) {
  #if (LCD_MIRROR_Y == 0)
    /* Vertical increment */
    if (_yPos < _y1) {
      _yPos++;
    } else {
      _yPos = _y0;
    }
  #else
    /* Vertical decrement */
    if (_yPos > _y0) {
      _yPos--;
    } else {
      _yPos = _y1;
    }
  #endif
}

/*********************************************************************
*
*       _IncrementCursor
*/
static void _IncrementCursor(void) {
  #if (LCD_SWAP_XY == 0)
    /* Horizontal */
    #if (LCD_MIRROR_X == 0)
      /* Horizontal increment */
      if (_xPos < _x1) {
        _xPos++;
      } else {
        _xPos = _x0;
        _IncY();
      }
    #else
      /* Horizontal decrement */
      if (_xPos > _x0) {
        _xPos--;
      } else {
        _xPos = _x1;
        _IncY();
      }
    #endif
  #else
    /* Vertical */
    #if (LCD_MIRROR_Y == 0)
      /* Vertical increment */
      if (_yPos < _y1) {
        _yPos++;
      } else {
        _yPos = _y0;
        _IncX();
      }
    #else
      /* Vertical decrement */
      if (_yPos > _y0) {
        _yPos--;
      } else {
        _yPos = _y1;
        _IncX();
      }
    #endif
  #endif
  _CalcCacheAddr();
}

/*********************************************************************
*
*       _ReadData
*/
static U16 _ReadData(void) {
  U16 Index;
  Index = *(_pVRam + _Addr);
  #if !LCD_USE_PARALLEL_16
    Index = (Index >> 8) | (Index << 8);
  #endif
  return Index;
}

/*********************************************************************
*
*       _AddCacheRect
*/
#if (LCD_SUPPORT_CACHECONTROL)
static void _AddCacheRect(void) {
  if (_CacheLocked) {
    _CacheStat = 1;
    if (_CacheRect.x0 > _x0) {
      _CacheRect.x0 = _x0;
    }
    if (_CacheRect.y0 > _y0) {
      _CacheRect.y0 = _y0;
    }
    if (_CacheRect.x1 < _x1) {
      _CacheRect.x1 = _x1;
    }
    if (_CacheRect.y1 < _y1) {
      _CacheRect.y1 = _y1;
    }
  }
}
#endif /* LCD_SUPPORT_CACHECONTROL */
#endif /* LCD_CACHE */

/*********************************************************************
*
*       _WriteData
*/
static void _WriteData(unsigned PixelIndex) {
  #if LCD_CACHE
    #if LCD_USE_PARALLEL_16
      *(_pVRam + _Addr) = PixelIndex;
    #else
      *(_pVRam + _Addr) = (PixelIndex >> 8) | (PixelIndex << 8);
    #endif
    _IncrementCursor();
  #else
    #if LCD_USE_PARALLEL_16
      U16 Data;
      Data = (U16)PixelIndex;
      WRITEM_A1(&Data, 1);
    #else
      _WriteU16_A1(PixelIndex);
    #endif
  #endif
}

/*********************************************************************
*
*       _WriteDataM
*
* Purpose:
*   Writes multiple pixels of the given index value. If available
*   it uses a buffer to speed up performance. 
*/
static void _WriteDataM(unsigned PixelIndex, U32 NumPixels) {
  #if LCD_CACHE
    U16 Value;
    #if LCD_USE_PARALLEL_16
      Value = PixelIndex;
    #else
      Value = (PixelIndex >> 8) | (PixelIndex << 8);
    #endif
    while (NumPixels--) {
      *(_pVRam + _Addr) = Value;
      _IncrementCursor();
    }
  #else
    #if LCD_WRITE_BUFFER_SIZE
      #if LCD_USE_PARALLEL_16
        int FillBuffer = 1;
        while (NumPixels) {
          U32 NumWords;
          NumWords = NumPixels;
          if (NumWords > (LCD_WRITE_BUFFER_SIZE / 2)) {
            NumWords = (LCD_WRITE_BUFFER_SIZE / 2);
          }
          if (FillBuffer) {
            FillBuffer = 0;
            GUI__memset16(_WriteBuffer, PixelIndex, NumWords);
          }
          WRITEM_A1(_WriteBuffer, NumWords);
          NumPixels -= NumWords;
        }
      #else
        U8 Byte0, Byte1;
        int FillBuffer = 1;
        Byte0 = PixelIndex >> 8;
        Byte1 = PixelIndex & 0xFF;
        while (NumPixels) {
          U32 NumWords = NumPixels;
          if (NumWords > ((LCD_WRITE_BUFFER_SIZE - 2) / 2)) {
            NumWords = ((LCD_WRITE_BUFFER_SIZE - 2) / 2);
          }
          if (FillBuffer) {
            U8 * p;
            int Cnt;
            p = &_WriteBuffer[1];
            FillBuffer = 0;
            Cnt = NumWords;
            while (Cnt--) {
              *(p + 0) = Byte0;
              *(p + 1) = Byte1;
              p += 2;
            }
          }
          WRITEM_A1((U8 *)&_WriteBuffer[1], NumWords * 2);
          NumPixels -= NumWords;
        }
      #endif
    #else
      while (NumPixels--) {
        _WriteU16_A1(PixelIndex);
      }
    #endif
  #endif
}

/*********************************************************************
*
*       _WriteDataMP
*
* Purpose:
*   Writes the index values pointed by pData. If available it uses a
*   buffer to speed up performance.
*/
static void _WriteDataMP(U16 * pData, int NumPixels) {
  #if LCD_CACHE
    U16 PixelIndex;
    while (NumPixels--) {
      PixelIndex = *pData++;
      #if !LCD_USE_PARALLEL_16
        PixelIndex = (PixelIndex >> 8) | (PixelIndex << 8);
      #endif
      *(_pVRam + _Addr) = PixelIndex;
      _IncrementCursor();
    }
  #else
    #if LCD_USE_PARALLEL_16
      WRITEM_A1(pData, NumPixels);
    #else
      #if LCD_WRITE_BUFFER_SIZE
        _NumPixelsInBuffer = 0;
        _pBuffer = _WriteBuffer;
        while (NumPixels--) {
          U16 PixelIndex;
          PixelIndex = *pData++;
          *_pBuffer++ = PixelIndex >> 8;
          *_pBuffer++ = PixelIndex & 0xFF;
          _NumPixelsInBuffer++;
          if (_NumPixelsInBuffer == (LCD_WRITE_BUFFER_SIZE / 2)) {
            WRITEM_A1(_WriteBuffer, (_NumPixelsInBuffer << 1));
            _NumPixelsInBuffer = 0;
            _pBuffer = _WriteBuffer;
          }
        }
        if (_NumPixelsInBuffer) {
          WRITEM_A1(_WriteBuffer, (_NumPixelsInBuffer << 1));
          _NumPixelsInBuffer = 0;
          _pBuffer = _WriteBuffer;
        }
      #else
      {
        U8 aBuffer[2];
        while (NumPixels--) {
          U16 PixelIndex;
          PixelIndex = *pData++;
          aBuffer[0] = PixelIndex >> 8;
          aBuffer[1] = PixelIndex & 0xFF;
          WRITEM_A1((U8 *)&aBuffer[0], 2);
        }
      }
      #endif
    #endif
  #endif
}

/*********************************************************************
*
*       _CalcPhysAddr
*/
static U32 _CalcPhysAddr(int x, int y) {
  U32 Addr;
  Addr = ((U32)(y + LCD_FIRSTCOM0) << 8) + x + LCD_FIRSTSEG0;
  return Addr;
}

/*********************************************************************
*
*       _SetCacheAddr
*/
#if LCD_CACHE
static void _SetCacheAddr(int x, int y) {
  _xPos = x;
  _yPos = y;
  _CalcCacheAddr();
}

/*********************************************************************
*
*       _CalcCacheEdge
*/
static void _CalcCacheEdge(void) {
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    _SetCacheAddr(_x0, _y0);
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    _SetCacheAddr(_x1, _y0);
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    _SetCacheAddr(_x0, _y1);
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    _SetCacheAddr(_x1, _y1);
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    _SetCacheAddr(_y0, _x0);
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    _SetCacheAddr(_y0, _x1);
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    _SetCacheAddr(_y1, _x0);
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    _SetCacheAddr(_y1, _x1);
  #endif
}

/*********************************************************************
*
*       _SetCacheRect
*/
static void _SetCacheRect(int x0, int y0, int x1, int y1) {
  _x0 = x0; _y0 = y0; _x1 = x1; _y1 = y1;
  _CalcCacheEdge();
}
#endif

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Hitachi  HD66766, HD66772, HD66789
*       - Samsung  S6D0110A, S6D0117
*       - Sitronix ST7712
*       - Himax    HX8301
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#if (LCD_CONTROLLER == 66766) || /* Hitachi HD66766, Samsung S6D0110A */ \
    (LCD_CONTROLLER == 66772) || /* Hitachi HD66772, Samsung S6D0117, Sitronix ST7712, Himax HX8301, Ilitek ILI9220, Ilitek ILI9221 */ \
    (LCD_CONTROLLER == 66789)    /* Hitachi HD66789 */
static void _SetPhysRAMAddr(int x, int y) {
  U32 Addr;
  Addr = _CalcPhysAddr(x, y);
  _WriteU16_A0(REG_RAM_ADDR_SET);
  _WriteU16_A1(Addr);
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    /* Use easy version if default orientation is used */
    _SET_CACHE_RECT(x0, y0, x1, y1);
    _WriteU16_A0(REG_SET_HRAM_POS);
    _WriteU16_A1(((x1 + LCD_FIRSTSEG0) << 8) | (x0 + LCD_FIRSTSEG0));
    _WriteU16_A0(REG_SET_VRAM_POS);
    _WriteU16_A1(((y1 + LCD_FIRSTCOM0) << 8) | (y0 + LCD_FIRSTCOM0));
    _SetPhysRAMAddr(x0, y0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys;
    U32 Addr;
    /* First calculate the physical positions */
    x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys = LOG2PHYS_X(x1, y1);
    y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys = LOG2PHYS_Y(x1, y1);
    /* Calculate the address of the first pixel */
    Addr = _CalcPhysAddr(x0Phys, y0Phys);
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    /* Set horizontal and vertical range */
    _WriteU16_A0(REG_SET_HRAM_POS);
    _WriteU16_A1(((x1Phys + LCD_FIRSTSEG0) << 8) | (x0Phys + LCD_FIRSTSEG0));
    _WriteU16_A0(REG_SET_VRAM_POS);
    _WriteU16_A1(((y1Phys + LCD_FIRSTCOM0) << 8) | (y0Phys + LCD_FIRSTCOM0));
    /* Set the address of the first pixel */
    _WriteU16_A0(REG_RAM_ADDR_SET);
    _WriteU16_A1(Addr);
    /* Set RAM access mode */
    _WriteU16_A0(REG_RAM_ACCESS);
  #endif
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Sharp LR38825
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66700)
static void _SetPhysRAMAddr(int x, int y) {
  _WriteU16_A0((REG_RAM_ADDR_H << 8) | (x + LCD_FIRSTSEG0));
  _WriteU16_A0((REG_RAM_ADDR_V << 8) | (y + LCD_FIRSTCOM0));
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    _SET_CACHE_RECT(x0, y0, x1, y1);
    _WriteU16_A0((REG_SET_HRAM_S << 8) + x0 + LCD_FIRSTSEG0);
    _WriteU16_A0((REG_SET_VRAM_S << 8) + y0 + LCD_FIRSTCOM0);
    _WriteU16_A0((REG_SET_HRAM_E << 8) + x1 + LCD_FIRSTSEG0);
    _WriteU16_A0((REG_SET_VRAM_E << 8) + y1 + LCD_FIRSTCOM0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys;
    x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys = LOG2PHYS_X(x1, y1);
    y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys = LOG2PHYS_Y(x1, y1);
    _WriteU16_A0((REG_SET_HRAM_S << 8) + x0Phys + LCD_FIRSTSEG0);
    _WriteU16_A0((REG_SET_VRAM_S << 8) + y0Phys + LCD_FIRSTCOM0);
    _WriteU16_A0((REG_SET_HRAM_E << 8) + x1Phys + LCD_FIRSTSEG0);
    _WriteU16_A0((REG_SET_VRAM_E << 8) + y1Phys + LCD_FIRSTCOM0);
    #if LCD_CACHE
      /* Swap if necessary */
      if (x1Phys < x0Phys) {
        int temp = x1Phys;
        x1Phys = x0Phys;
        x0Phys = temp;
      }
      if (y1Phys < y0Phys) {
        int temp = y1Phys;
        y1Phys = y0Phys;
        y0Phys = temp;
      }
      _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    #endif
  #endif
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326
*       - Solomon SSD1284, Solomon SSD1289, Solomon SSD1298
*       - Toshiba JBT6K71
*       - Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
      (LCD_CONTROLLER == 66702) || /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */ \
      (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
      (LCD_CONTROLLER == 66708)    /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */
static void _SetPhysRAMAddr(int x, int y) {
  _WriteU16_A0(REG_RAM_ADDR_H);
  _WriteU16_A1(x);
  _WriteU16_A0(REG_RAM_ADDR_V);
  _WriteU16_A1(y);
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    /* Use easy version if default orientation is used */
    _SET_CACHE_RECT(x0, y0, x1, y1);
    #if   (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
          (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
          (LCD_CONTROLLER == 66708)    /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */
      _WriteU16_A0(REG_SET_HRAM_S);
      _WriteU16_A1(x0 + LCD_FIRSTSEG0);
      _WriteU16_A0(REG_SET_HRAM_E);
      _WriteU16_A1(x1 + LCD_FIRSTSEG0);
    #elif (LCD_CONTROLLER == 66702)    /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */
      _WriteU16_A0(REG_SET_HRAM_POS);
      _WriteU16_A1(((x1 + LCD_FIRSTSEG0) << 8) | (x0 + LCD_FIRSTSEG0));
    #endif
    _WriteU16_A0(REG_SET_VRAM_S);
    _WriteU16_A1(y0 + LCD_FIRSTCOM0);
    _WriteU16_A0(REG_SET_VRAM_E);
    _WriteU16_A1(y1 + LCD_FIRSTCOM0);
    _WriteU16_A0(REG_RAM_ADDR_H);
    _WriteU16_A1(x0 + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_RAM_ADDR_V);
    _WriteU16_A1(y0 + LCD_FIRSTCOM0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys, xs, ys;
    /* First calculate the physical positions */
    xs = x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys      = LOG2PHYS_X(x1, y1);
    ys = y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys      = LOG2PHYS_Y(x1, y1);
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    #if LCD_CACHE
      _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    #else
      _x0 = x0Phys; _y0 = y0Phys; _x1 = x1Phys; _y1 = y1Phys;
    #endif
    /* Set horizontal and vertical range */
    #if   (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
          (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
          (LCD_CONTROLLER == 66708)    /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */
      _WriteU16_A0(REG_SET_HRAM_S);
      _WriteU16_A1(x0Phys + LCD_FIRSTSEG0);
      _WriteU16_A0(REG_SET_HRAM_E);
      _WriteU16_A1(x1Phys + LCD_FIRSTSEG0);
    #elif (LCD_CONTROLLER == 66702)    /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */
      _WriteU16_A0(REG_SET_HRAM_POS);
      _WriteU16_A1(((x1Phys + LCD_FIRSTSEG0) << 8) | (x0Phys + LCD_FIRSTSEG0));
    #endif
    _WriteU16_A0(REG_SET_VRAM_S);
    _WriteU16_A1(y0Phys + LCD_FIRSTCOM0);
    _WriteU16_A0(REG_SET_VRAM_E);
    _WriteU16_A1(y1Phys + LCD_FIRSTCOM0);
    /* Set the address of the first pixel */
    _WriteU16_A0(REG_RAM_ADDR_H);
    _WriteU16_A1(xs + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_RAM_ADDR_V);
    _WriteU16_A1(ys + LCD_FIRSTCOM0);
  #endif
  /* Set RAM access mode */
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Sharp LCY-A06003
*       - MagnaChip D54E4PA7551
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66704) || /* Sharp LCY-A06003 */ \
      (LCD_CONTROLLER == 66706)    /* MagnaChip D54E4PA7551 */
static void _SetPhysRAMAddr(int x, int y) {
  x -= _x0;
  y -= _y0;
  LCD_WRITE_A0(REG_RAM_ADDR_H);
  LCD_WRITE_A1(x);
  LCD_WRITE_A0(REG_RAM_ADDR_V_LB);
  LCD_WRITE_A1(y & 0xff);
  LCD_WRITE_A0(REG_RAM_ADDR_V_HB);
  LCD_WRITE_A1(y >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (LCD_CONTROLLER == 66704) && (LCD_SWAP_XY)
    /*
      The LCY-A06003 can not manage swapping X/Y because of insufficient registers.
      When swapping the axes also the meaning of the window registers are swapped.
      With other words the registers for defining the X-positions should be used
      for the Y-position when using swapping (INC=1). But unfortunately there are
      only 8 bit available in these registers!
    */
    #error This option does not work with the LCY-A06003!
  #endif
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    /* Use easy version if default orientation is used */
    #if (LCD_CACHE == 0)
      _x0 = x0; _y0 = y0; _x1 = x1; _y1 = y1;
    #else
      _SET_CACHE_RECT(x0, y0, x1, y1);
    #endif
    LCD_WRITE_A0(REG_SET_HRAM_S);                /* Horizontal start addr */
    LCD_WRITE_A1((x0 + LCD_FIRSTSEG0));
    LCD_WRITE_A0(REG_SET_VRAM_S_LB);             /* Vertical   start addr low  byte */
    LCD_WRITE_A1(((y0 + LCD_FIRSTCOM0) & 0xff));
    LCD_WRITE_A0(REG_SET_VRAM_S_HB);             /* Vertical   start addr high byte */
    LCD_WRITE_A1(((y0 + LCD_FIRSTCOM0) >> 8));
    LCD_WRITE_A0(REG_SET_HRAM_E);                /* Horizontal end   addr */
    LCD_WRITE_A1((x1 + LCD_FIRSTSEG0));
    LCD_WRITE_A0(REG_SET_VRAM_E_LB);             /* Vertical   end   addr low  byte */
    LCD_WRITE_A1(((y1 + LCD_FIRSTCOM0) & 0xff));
    LCD_WRITE_A0(REG_SET_VRAM_E_HB);             /* Vertical   end   addr high byte */
    LCD_WRITE_A1(((y1 + LCD_FIRSTCOM0) >> 8));
    _SetPhysRAMAddr(x0, y0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys, xs, ys;
    /* First calculate the physical positions */
    x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys = LOG2PHYS_X(x1, y1);
    y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys = LOG2PHYS_Y(x1, y1);
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    #if (LCD_MIRROR_X)
      xs = x1Phys;
    #else
      xs = x0Phys;
    #endif
    #if (LCD_MIRROR_Y)
      ys = y1Phys;
    #else
      ys = y0Phys;
    #endif
    #if (LCD_CACHE == 0)
      _x0 = x0Phys; _y0 = y0Phys; _x1 = x1Phys; _y1 = y1Phys;
    #else
      _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    #endif
    /* Set horizontal and vertical range */
    LCD_WRITE_A0(REG_SET_HRAM_S);                /* Horizontal start addr */
    LCD_WRITE_A1((x0Phys + LCD_FIRSTSEG0));
    LCD_WRITE_A0(REG_SET_VRAM_S_LB);             /* Vertical   start addr low  byte */
    LCD_WRITE_A1(((y0Phys + LCD_FIRSTCOM0) & 0xff));
    LCD_WRITE_A0(REG_SET_VRAM_S_HB);             /* Vertical   start addr high byte */
    LCD_WRITE_A1(((y0Phys + LCD_FIRSTCOM0) >> 8));
    LCD_WRITE_A0(REG_SET_HRAM_E);                /* Horizontal end   addr */
    LCD_WRITE_A1((x1Phys + LCD_FIRSTSEG0));
    LCD_WRITE_A0(REG_SET_VRAM_E_LB);             /* Vertical   end   addr low  byte */
    LCD_WRITE_A1(((y1Phys + LCD_FIRSTCOM0) & 0xff));
    LCD_WRITE_A0(REG_SET_VRAM_E_HB);             /* Vertical   end   addr high byte */
    LCD_WRITE_A1(((y1Phys + LCD_FIRSTCOM0) >> 8));
    /* Set the address of the first pixel */
    _SetPhysRAMAddr(xs, ys);
  #endif
  /* Set RAM access mode */
  LCD_WRITE_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Samsung S6D0129
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66705)
static void _SetPhysRAMAddr(int x, int y) {
  _WriteU16_A0(REG_RAM_ADDR_LB);
  _WriteU16_A1(x);
  _WriteU16_A0(REG_RAM_ADDR_HB);
  _WriteU16_A1(y);
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y)
    _SET_CACHE_RECT(x0, y0, x1, y1);
    _WriteU16_A0(REG_SET_HRAM_POS);
    _WriteU16_A1(((x1 + LCD_FIRSTSEG0) << 8) | (x0 + LCD_FIRSTSEG0));
    _WriteU16_A0(REG_SET_VRAM_S);
    _WriteU16_A1((y0 + LCD_FIRSTCOM0));
    _WriteU16_A0(REG_SET_VRAM_E);
    _WriteU16_A1((y1 + LCD_FIRSTCOM0));
    _SetPhysRAMAddr(x0, y0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys, xs, ys;
    /* First calculate the physical positions */
    x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys = LOG2PHYS_X(x1, y1);
    y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys = LOG2PHYS_Y(x1, y1);
    /* Remember the address of the first pixel */
    xs = x0Phys;
    ys = y0Phys;
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    /* Set horizontal and vertical range */
    _WriteU16_A0(REG_SET_HRAM_POS);
    _WriteU16_A1(((x1Phys + LCD_FIRSTSEG0) << 8) | (x0Phys + LCD_FIRSTSEG0));
    _WriteU16_A0(REG_SET_VRAM_S);
    _WriteU16_A1((y0Phys + LCD_FIRSTCOM0));
    _WriteU16_A0(REG_SET_VRAM_E);
    _WriteU16_A1((y1Phys + LCD_FIRSTCOM0));
    /* Set the address of the first pixel */
    _WriteU16_A0(REG_RAM_ADDR_LB);
    _WriteU16_A1(xs);
    _WriteU16_A0(REG_RAM_ADDR_HB);
    _WriteU16_A1(ys);
    _WriteU16_A0(REG_RAM_ACCESS);
    /* Set RAM access mode */
    _WriteU16_A0(REG_RAM_ACCESS);
  #endif
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Himax HX8312A
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66707)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0((REG_RAM_ADDR_H    << 8) | x);
  LCD_WRITE_A0((REG_RAM_ADDR_V_LB << 8) | (y & 0xff));
  LCD_WRITE_A0((REG_RAM_ADDR_V_HB << 8) | (y >> 8));
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    /* Use easy version if default orientation is used */
    _x0 = x0; _y0 = y0; _x1 = x1; _y1 = y1;
    LCD_WRITE_A0((REG_SET_HRAM_S    << 8) |  (x0 + LCD_FIRSTSEG0));         /* Horizontal start addr */
    LCD_WRITE_A0((REG_SET_VRAM_S_LB << 8) | ((y0 + LCD_FIRSTCOM0) & 0xff)); /* Vertical   start addr low  byte */
    LCD_WRITE_A0((REG_SET_VRAM_S_HB << 8) | ((y0 + LCD_FIRSTCOM0) >> 8));   /* Vertical   start addr high byte */
    LCD_WRITE_A0((REG_SET_HRAM_E    << 8) |  (x1 + LCD_FIRSTSEG0));         /* Horizontal end   addr */
    LCD_WRITE_A0((REG_SET_VRAM_E_LB << 8) | ((y1 + LCD_FIRSTCOM0) & 0xff)); /* Vertical   end   addr low  byte */
    LCD_WRITE_A0((REG_SET_VRAM_E_HB << 8) | ((y1 + LCD_FIRSTCOM0) >> 8));   /* Vertical   end   addr high byte */
    _SetPhysRAMAddr(x0 + LCD_FIRSTSEG0, y0 + LCD_FIRSTCOM0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys, xs, ys;
    /* First calculate the physical positions */
    xs = x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys      = LOG2PHYS_X(x1, y1);
    ys = y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys      = LOG2PHYS_Y(x1, y1);
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    _x0 = x0Phys; _y0 = y0Phys; _x1 = x1Phys; _y1 = y1Phys;
    LCD_WRITE_A0((REG_SET_HRAM_S    << 8) |  (x0Phys + LCD_FIRSTSEG0));         /* Horizontal start addr */
    LCD_WRITE_A0((REG_SET_VRAM_S_LB << 8) | ((y0Phys + LCD_FIRSTCOM0) & 0xff)); /* Vertical   start addr low  byte */
    LCD_WRITE_A0((REG_SET_VRAM_S_HB << 8) | ((y0Phys + LCD_FIRSTCOM0) >> 8));   /* Vertical   start addr high byte */
    LCD_WRITE_A0((REG_SET_HRAM_E    << 8) |  (x1Phys + LCD_FIRSTSEG0));         /* Horizontal end   addr */
    LCD_WRITE_A0((REG_SET_VRAM_E_LB << 8) | ((y1Phys + LCD_FIRSTCOM0) & 0xff)); /* Vertical   end   addr low  byte */
    LCD_WRITE_A0((REG_SET_VRAM_E_HB << 8) | ((y1Phys + LCD_FIRSTCOM0) >> 8));   /* Vertical   end   addr high byte */
    _SetPhysRAMAddr(xs + LCD_FIRSTSEG0, ys + LCD_FIRSTCOM0);
  #endif
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7787, Solomon SSD1355, Solomon SSD1963
*       Sitronix ST7787
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66709) || (LCD_CONTROLLER == 66717)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0(REG_CASET); /* Column address set */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xff);
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xff);
  LCD_WRITE_A0(REG_RASET); /* Row    address set */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xff);
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xff);
  LCD_WRITE_A0(REG_RAM_ACCESS_W); /* RAM write mode */
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  _SET_CACHE_RECT(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_CASET); /* Column address set */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) & 0xff);
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) & 0xff);
  LCD_WRITE_A0(REG_RASET); /* Row    address set */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) & 0xff);
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) & 0xff);
  LCD_WRITE_A0(REG_RAM_ACCESS_W); /* RAM write mode */
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Novatek NT7573
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66710)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0(REG_CASET); /* Column address set */
  LCD_WRITE_A0(x + LCD_FIRSTSEG0);
  LCD_WRITE_A0(x + LCD_FIRSTSEG0);
  LCD_WRITE_A0(REG_RASET); /* Row    address set */
  LCD_WRITE_A0(y + LCD_FIRSTCOM0);
  LCD_WRITE_A0(y + LCD_FIRSTCOM0);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  _SET_CACHE_RECT(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_CASET); /* Column address set */
  LCD_WRITE_A0(x0 + LCD_FIRSTSEG0);
  LCD_WRITE_A0(x1 + LCD_FIRSTSEG0);
  LCD_WRITE_A0(REG_RASET); /* Row    address set */
  LCD_WRITE_A0(y0 + LCD_FIRSTCOM0);
  LCD_WRITE_A0(y1 + LCD_FIRSTCOM0);
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Epson S1D13742, S1D13743
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66711)
static void _SetPhysRAMAddr(int x, int y) {
  _PhysRAMAddrX = x;
  _PhysRAMAddrY = y;
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_MEM_DATA_PORT); /* Memory Data Port Register 0 */
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    _x0 = x0; _y0 = y0; _x1 = x1; _y1 = y1;
    _SET_CACHE_RECT(x0, y0, x1, y1);
    LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
    LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) & 0xFF);
    LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
    LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) >> 8);
    LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
    LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) & 0xFF);
    LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
    LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) >> 8);
    LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
    LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) & 0xFF);
    LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
    LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) >> 8);
    LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
    LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) & 0xFF);
    LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
    LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) >> 8);
    LCD_WRITE_A0(REG_MEM_DATA_PORT); /* Memory Data Port Register 0 */
  #else
    #error Please use the Swivel function of the display controller for rotationg the display!
  #endif
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Himax HX8347, Himax HX8352
*       - Himax HX8340
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66712) || (LCD_CONTROLLER == 66713)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  _SET_CACHE_RECT(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Himax HX8352B
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66715)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0(REG_RAC2);
  LCD_WRITE_A1((x >> 8));
  LCD_WRITE_A0(REG_RAC1);
  LCD_WRITE_A1((x & 0xFF));
  LCD_WRITE_A0(REG_CAC2);
  LCD_WRITE_A1((y >> 8));
  LCD_WRITE_A0(REG_CAC1);
  LCD_WRITE_A1((y & 0xFF));
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  _SET_CACHE_RECT(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Solomon SSD2119
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66714) /* Solomon SSD2119 */
static void _SetPhysRAMAddr(int x, int y) {
  _WriteU16_A0(REG_RAM_ADDR_H);
  _WriteU16_A1(x);
  _WriteU16_A0(REG_RAM_ADDR_V);
  _WriteU16_A1(y);
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    /* Use easy version if default orientation is used */
    _SET_CACHE_RECT(x0, y0, x1, y1);
    _WriteU16_A0(REG_SET_VRAM_POS);
    _WriteU16_A1(((y1 + LCD_FIRSTCOM0) << 8) | (y0 + LCD_FIRSTCOM0));
    _WriteU16_A0(REG_SET_HRAM_S);
    _WriteU16_A1(x0 + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_SET_HRAM_E);
    _WriteU16_A1(x1 + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_RAM_ADDR_H);
    _WriteU16_A1(x0 + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_RAM_ADDR_V);
    _WriteU16_A1(y0 + LCD_FIRSTCOM0);
  #else
    int x0Phys, y0Phys, x1Phys, y1Phys, xs, ys;
    /* First calculate the physical positions */
    xs = x0Phys = LOG2PHYS_X(x0, y0);
    x1Phys      = LOG2PHYS_X(x1, y1);
    ys = y0Phys = LOG2PHYS_Y(x0, y0);
    y1Phys      = LOG2PHYS_Y(x1, y1);
    /* Swap if necessary */
    if (x1Phys < x0Phys) {
      int temp = x1Phys;
      x1Phys = x0Phys;
      x0Phys = temp;
    }
    if (y1Phys < y0Phys) {
      int temp = y1Phys;
      y1Phys = y0Phys;
      y0Phys = temp;
    }
    #if LCD_CACHE
      _SET_CACHE_RECT(x0Phys, y0Phys, x1Phys, y1Phys);
    #else
      _x0 = x0Phys; _y0 = y0Phys; _x1 = x1Phys; _y1 = y1Phys;
    #endif
    /* Set horizontal and vertical range */
    _WriteU16_A0(REG_SET_VRAM_POS);
    _WriteU16_A1(((y1Phys + LCD_FIRSTCOM0) << 8) | (y0Phys + LCD_FIRSTCOM0));
    _WriteU16_A0(REG_SET_HRAM_S);
    _WriteU16_A1(x0Phys + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_SET_HRAM_E);
    _WriteU16_A1(x1Phys + LCD_FIRSTSEG0);
    /* Set the address of the first pixel */
    _WriteU16_A0(REG_RAM_ADDR_H);
    _WriteU16_A1(xs + LCD_FIRSTSEG0);
    _WriteU16_A0(REG_RAM_ADDR_V);
    _WriteU16_A1(ys + LCD_FIRSTCOM0);
  #endif
  /* Set RAM access mode */
  _WriteU16_A0(REG_RAM_ACCESS);
}

/*********************************************************************
*
*       _SetPhysRAMAddr and _SetRect for the following display controllers:
*
*       - Ampire FSA506
*/
/*********************************************************************
*
*       _SetPhysRAMAddr
*/
#elif (LCD_CONTROLLER == 66716)
static void _SetPhysRAMAddr(int x, int y) {
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

/*********************************************************************
*
*       _SetRect
*/
static void _SetRect(int x0, int y0, int x1, int y1) {
  _SET_CACHE_RECT(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_SET_HRAM_S_LB); /* Window X Start Position Register 0 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_S_HB); /* Window X Start Position Register 1 */
  LCD_WRITE_A1((x0 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_S_LB); /* Window Y Start Position Register 0 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_S_HB); /* Window Y Start Position Register 1 */
  LCD_WRITE_A1((y0 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_SET_HRAM_E_LB); /* Window X End Position Register 0 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) & 0xFF);
  LCD_WRITE_A0(REG_SET_HRAM_E_HB); /* Window X End Position Register 1 */
  LCD_WRITE_A1((x1 + LCD_FIRSTSEG0) >> 8);
  LCD_WRITE_A0(REG_SET_VRAM_E_LB); /* Window Y End Position Register 0 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) & 0xFF);
  LCD_WRITE_A0(REG_SET_VRAM_E_HB); /* Window Y End Position Register 1 */
  LCD_WRITE_A1((y1 + LCD_FIRSTCOM0) >> 8);
  LCD_WRITE_A0(REG_RAM_ACCESS);    /* Memory access */
}

#endif

#if LCD_CACHE
/*********************************************************************
*
*       _ManageRect
*/
static void _ManageRect(int Cmd) {
  static int HasPushed, x0, y0, x1, y1, Addr;
  switch (Cmd) {
  case PUSH_RECT:
    if (HasPushed == 0) {
      HasPushed = 1;
      x0   = _x0;
      y0   = _y0;
      x1   = _x1;
      y1   = _y1;
      Addr = _Addr;
    }
    break;
  case POP_RECT:
    if (HasPushed == 1) {
      HasPushed = 0;
      _x0   = x0;
      _y0   = y0;
      _x1   = x1;
      _y1   = y1;
      _Addr = Addr;
    }
    break;
  }
}

/*********************************************************************
*
*       _SetSubRect
*/
static void _SetSubRect(int x0, int y0, int x1, int y1) {
  _ManageRect(PUSH_RECT);
  _SetCacheRect(x0, y0, x1, y1);
}

/*********************************************************************
*
*       _WriteCache
*/
static void _WriteCache(int x, int y, int PixelIndex) {
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  _SET_CACHE_ADDR(xPhys, yPhys);
  _WriteData(PixelIndex);
}

/*********************************************************************
*
*       _ReadCache
*/
static unsigned int _ReadCache(int x, int y) {
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  LCD_PIXELINDEX PixelIndex;
  _SET_CACHE_ADDR(xPhys, yPhys);
  PixelIndex = READ_DATA();
  return PixelIndex;
}
#endif

/*********************************************************************
*
*       _SendCacheRect
*/
#if LCD_CACHE
static void _SendCacheRect(int x0, int y0, int x1, int y1) {
  #if (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    U16 * pCache;
    int NumBytes, y, CacheSize;
    #if LCD_SUPPORT_CACHECONTROL
      if (_CacheLocked) {
        ADD_CACHE_RECT();
        return;
      }
    #endif
    NumBytes = x1 - x0 + 1;
    #if (LCD_USE_PARALLEL_16 == 0)
      NumBytes <<= 1;
    #endif
    #if (CACHE_OFFSET)
      CacheSize = CACHE_OFFSET;
    #else
      CacheSize = _xSize;
    #endif
    pCache = _pVRam + (CacheSize * (U32)y0 + x0);
    for (y = y0; y <= y1; pCache += CacheSize, y++) {
      #if (LCD_USE_PARALLEL_16)
        WRITEM_A1((U16 *)pCache, NumBytes);
      #else
        WRITEM_A1((U8 *)pCache, NumBytes);
      #endif
    }
  #else
    U32 NumPixels;
    _CalcCacheEdge();
    NumPixels = (U32)(x1 - x0 + 1) * (U32)(y1 - y0 + 1);
    while (NumPixels--) {
      #if (LCD_USE_PARALLEL_16)
        WRITEM_A1((U16 *)(_pVRam + _Addr), 1);
      #else
        WRITEM_A1((U8 *)(_pVRam + _Addr), 2);
      #endif
      _IncrementCursor();
    }
  #endif
}

/*********************************************************************
*
*       _FlushCache
*/
#if LCD_SUPPORT_CACHECONTROL
static void _FlushCache(void) {
  /*
  * Set rectangle of modified area
  */
  _SetRect(_CacheRect.x0, _CacheRect.y0, _CacheRect.x1, _CacheRect.y1);
  /*
  * Send cache data
  */
  _SendCacheRect(_CacheRect.x0, _CacheRect.y0, _CacheRect.x1, _CacheRect.y1);
  /*
  * Invalidate rectangle
  */
  _CacheRect.x0 = _CacheRect.y0 =  9999;
  _CacheRect.x1 = _CacheRect.y1 = -9999;
}
#endif /* LCD_SUPPORT_CACHECONTROL */
#endif /* LCD_CACHE */

/*********************************************************************
*
*       Draw Bitmap 1 BPP
*/
static void  _DrawBitLine1BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Index0;
  LCD_PIXELINDEX Index1;
  int WriteState;
  int x0, x1, NumPixelsInBuffer, PixelIndex;
  U16 * pBuffer;

  Index0 = *(pTrans + 0);
  Index1 = *(pTrans + 1);
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      _WriteData((*p & (0x80 >> Diff)) ? Index1 : Index0);
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    WriteState = NumPixelsInBuffer = 0;
    do {
      if (*p & (0x80 >> Diff)) {
        if (WriteState == 0) {
          WriteState = 1;
          x0 = x;
          pBuffer = _pLineBuffer;
        }
        *pBuffer++ = (U16)(Index1);
        NumPixelsInBuffer++;
      } else {
        if (WriteState == 1) {
          x1 = x - 1;
          WriteState = 0;
          SET_SUB_RECT(x0, y, x1, y);
          _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
          NumPixelsInBuffer = 0;
        }
      }
      x++;
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
    } while (--xsize);
    if (NumPixelsInBuffer) {
      x1 = x - 1;
      SET_SUB_RECT(x0, y, x1, y);
      _SetRect(x0, y, x1, y);
      _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
    }
    CLR_SUB_RECT();
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    do {
      if (*p & (0x80 >> Diff)) {
        PixelIndex = GET_PIXEL_INDEX(x, y);
        PixelIndex ^= _IndexMask;
        SET_PIXEL_INDEX(x, y, PixelIndex);
      }
      x++;
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 2 BPP
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void  _DrawBitLine2BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, WriteState, Shift, Index;
  int x0, x1, NumPixelsInBuffer;
  U16 * pBuffer;

  if (pTrans == NULL) {
    return; /* Makes no sense */
  }
  Pixels = *p;
  CurrentPixel = Diff;
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Shift = (3 - CurrentPixel) << 1;
      Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
      PixelIndex = *(pTrans + Index);
      _WriteData(PixelIndex);
      if (++CurrentPixel == 4) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    WriteState = NumPixelsInBuffer = 0;
    do {
      Shift = (3 - CurrentPixel) << 1;
      Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
      if (Index) {
        if (WriteState == 0) {
          WriteState = 1;
          x0 = x;
          pBuffer = _pLineBuffer;
        }
        PixelIndex = *(pTrans + Index);
        *pBuffer++ = (U16)(PixelIndex);
        NumPixelsInBuffer++;
      } else {
        if (WriteState == 1) {
          x1 = x - 1;
          WriteState = 0;
          SET_SUB_RECT(x0, y, x1, y);
          _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
          NumPixelsInBuffer = 0;
        }
      }
      x++;
      if (++CurrentPixel == 4) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
    } while (--xsize);
    if (NumPixelsInBuffer) {
      x1 = x - 1;
      SET_SUB_RECT(x0, y, x1, y);
      _SetRect(x0, y, x1, y);
      _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
    }
    CLR_SUB_RECT();
    break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 4 BPP
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  _DrawBitLine4BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, WriteState, Shift, Index;
  int x0, x1, NumPixelsInBuffer;
  U16 * pBuffer;

  if (pTrans == NULL) {
    return; /* Makes no sense */
  }
  Pixels = *p;
  CurrentPixel = Diff;
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Shift = (1 - CurrentPixel) << 2;
      Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
      PixelIndex = *(pTrans + Index);
      _WriteData(PixelIndex);
      if (++CurrentPixel == 2) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    WriteState = NumPixelsInBuffer = 0;
    do {
      Shift = (1 - CurrentPixel) << 2;
      Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
      if (Index) {
        if (WriteState == 0) {
          WriteState = 1;
          x0 = x;
          pBuffer = _pLineBuffer;
        }
        PixelIndex = *(pTrans + Index);
        *pBuffer++ = (U16)(PixelIndex);
        NumPixelsInBuffer++;
      } else {
        if (WriteState == 1) {
          x1 = x - 1;
          WriteState = 0;
          SET_SUB_RECT(x0, y, x1, y);
          _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
          NumPixelsInBuffer = 0;
        }
      }
      x++;
      if (++CurrentPixel == 2) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
    } while (--xsize);
    if (NumPixelsInBuffer) {
      x1 = x - 1;
      SET_SUB_RECT(x0, y, x1, y);
      _SetRect(x0, y, x1, y);
      _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
    }
    CLR_SUB_RECT();
    break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 8 BPP
*/
#if (LCD_MAX_LOG_COLORS > 16)
static void  _DrawBitLine8BPP(int x, int y, U8 const * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  int WriteState;
  int x0, x1, NumPixelsInBuffer;
  U16 * pBuffer;

  if (pTrans == NULL) {
    return; /* Makes no sense */
  }
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    for (; xsize > 0; xsize--, p++) {
      Pixel = *p;
      _WriteData(*(pTrans + Pixel));
    }
    break;
  case LCD_DRAWMODE_TRANS:
    WriteState = NumPixelsInBuffer = 0;
    do {
      Pixel = *p++;
      if (Pixel) {
        if (WriteState == 0) {
          WriteState = 1;
          x0 = x;
          pBuffer = _pLineBuffer;
        }
        *pBuffer++ = (U16)(*(pTrans + Pixel));
        NumPixelsInBuffer++;
      } else {
        if (WriteState == 1) {
          x1 = x - 1;
          WriteState = 0;
          SET_SUB_RECT(x0, y, x1, y);
          _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
          NumPixelsInBuffer = 0;
        }
      }
      x++;
    } while (--xsize);
    if (NumPixelsInBuffer) {
      x1 = x - 1;
      SET_SUB_RECT(x0, y, x1, y);
      _SetRect(x0, y, x1, y);
      _WriteDataMP(_pLineBuffer, NumPixelsInBuffer);
    }
    CLR_SUB_RECT();
    break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 16 BPP
*/
#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(int x, int y, U16 const * p, int xsize) {
  LCD_PIXELINDEX pixel;
  if ((GUI_pContext->DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    _WriteDataMP((U16 *)p, xsize);
  } else {
    for (; xsize > 0; xsize--, x++, p++) {
      pixel = *p;
      SET_PIXEL_INDEX(x, y, pixel);
    }
  }
}
#endif

#if (GUI_VERSION >= 41200)

/*********************************************************************
*
*       _NextPixel_FlushBuffer
*/
#if LCD_WRITE_BUFFER_SIZE
static void _NextPixel_FlushBuffer(void) {
  #if LCD_USE_PARALLEL_16
    WRITEM_A1(_WriteBuffer, _NumPixelsInBuffer);
  #else
    WRITEM_A1(_WriteBuffer, (_NumPixelsInBuffer << 1));
  #endif
  _NumPixelsInBuffer = 0;
  _pBuffer = _WriteBuffer;
}

/*********************************************************************
*
*       _NextPixel_WriteBuffer
*/
static void _NextPixel_WriteBuffer(LCD_PIXELINDEX PixelIndex) {
  #if LCD_USE_PARALLEL_16
    *(_pBuffer++) = (U16)PixelIndex;
  #else
    U8 Byte0, Byte1;
    Byte0 = PixelIndex >> 8;
    Byte1 = PixelIndex & 0xFF;
    *(_pBuffer + 0) = Byte0;
    *(_pBuffer + 1) = Byte1;
    _pBuffer += 2;
  #endif
  _NumPixelsInBuffer++;
  if (_NumPixelsInBuffer == (LCD_WRITE_BUFFER_SIZE / 2)) {
    _NextPixel_FlushBuffer();
  }
}
#endif

/*********************************************************************
*
*       _NextPixel_Start
*/
static int _NextPixel_Start(int x0, int y0, int x1, int y1) {
  _SetRect(x0, y0, x1, y1);
  #if LCD_WRITE_BUFFER_SIZE
    _pBuffer = _WriteBuffer;
    _NumPixelsInBuffer = 0;
  #endif
  return 0;
}

/*********************************************************************
*
*       _NextPixel_SetPixel
*/
static void _NextPixel_SetPixel(LCD_PIXELINDEX PixelIndex) {
  #if LCD_WRITE_BUFFER_SIZE
    _NextPixel_WriteBuffer(PixelIndex);
  #else
    _WriteData(PixelIndex);
  #endif
}

/*********************************************************************
*
*       _NextPixel_NextLine
*/
static void _NextPixel_NextLine(void) {
  /* Nothing to do */
}

/*********************************************************************
*
*       _NextPixel_End
*/
static void _NextPixel_End(void) {
  #if LCD_WRITE_BUFFER_SIZE
    _NextPixel_FlushBuffer();
  #endif
}

/*********************************************************************
*
*       _NextPixel_API
*/
static LCD_API_NEXT_PIXEL _NextPixel_API = {
  _NextPixel_Start,
  _NextPixel_SetPixel,
  _NextPixel_NextLine,
  _NextPixel_End
};

#endif /* (GUI_VERSION >= 41200) */

/*********************************************************************
*
*       _ReadRect
*/
#if (LCD_CONTROLLER == 66709) && (LCD_CACHE == 0) /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */
static void _ReadRect(int x0, int y0, int x1, int y1, void * p) {
  #if LCD_USE_PARALLEL_16
    U16 aData[2];
  #else
    U8 aData[3];
  #endif
  U16 * pBuffer;
  U32 NumPixels;
  U16 Result;
  pBuffer = (U16 *)p;
  NumPixels = (x1 - x0 + 1) * (y1 - y0 + 1);
  _SetRect(x0, y0, x1, y1);
  LCD_WRITE_A0(REG_RAM_ACCESS_R);       /* RAM read mode */
  READM_A1(aData, LCD_NUM_DUMMY_READS); /* Required dummy read(s) */
  do {
    READM_A1(aData, GUI_COUNTOF(aData));
    DATA_2_INDEX(aData, Result);
    *pBuffer++ = Result;
  } while (--NumPixels);
}
#endif

/*********************************************************************
*
*       _ReadRect
*/
#if (LCD_CONTROLLER == 66716) && (LCD_CACHE == 0) /* Ampire FSA506 */
static void _ReadRect(int x0, int y0, int x1, int y1, void * p) {
  #if LCD_USE_PARALLEL_16
    #if LCD_NUM_DUMMY_READS
      U16 aData[LCD_NUM_DUMMY_READS + 1];
    #endif
    U16 * pBuffer;
    U32 NumPixels;
    U16 Result;
    
    pBuffer = (U16 *)p;
    NumPixels = (x1 - x0 + 1) * (y1 - y0 + 1);
    _SetRect(x0, y0, x1, y1);
    #if LCD_NUM_DUMMY_READS
      READM_A1(aData, LCD_NUM_DUMMY_READS); /* Required dummy read(s) */
    #endif
    READM_A1(pBuffer, NumPixels);
  #else
    U8 aData[LCD_NUM_DUMMY_READS + 2];
    U16 * pBuffer;
    U32 NumPixels;
    U16 Result;
    
    pBuffer = (U16 *)p;
    NumPixels = (x1 - x0 + 1) * (y1 - y0 + 1);
    _SetRect(x0, y0, x1, y1);
    #if LCD_NUM_DUMMY_READS
      READM_A1(aData, LCD_NUM_DUMMY_READS); /* Required dummy read(s) */
    #endif
    do {
      READM_A1(aData, GUI_COUNTOF(aData));
      Result = aData[LCD_NUM_DUMMY_READS + 1] | ((U16)aData[LCD_NUM_DUMMY_READS + 0] << 8);
      *pBuffer++ = Result;
    } while (--NumPixels);
  #endif
}
#endif

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_L0_SetPixelIndex
*
* Purpose:
*   Sets the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
void LCD_L0_SetPixelIndex(int x, int y, LCD_PIXELINDEX PixelIndex) {
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if (LCD_SWAP_XY | LCD_MIRROR_X | LCD_MIRROR_Y)
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  #if RAM_ADDR_SET
    if ((xPhys < _x0) | (xPhys > _x1) | (yPhys < _y0) | (yPhys > _y1)) {
      _SetRect(0, 0, LCD_XSIZE - 1, LCD_YSIZE - 1);
    }
    _SetPhysRAMAddr(xPhys, yPhys);
    _SET_CACHE_ADDR(xPhys, yPhys);
  #else
    _SetPhysRAMAddr(xPhys, yPhys);
    _SET_CACHE_ADDR(xPhys, yPhys);
  #endif
  #if LCD_CACHE
    ADD_CACHE_RECT();
    _WriteU16_A1((U16)PixelIndex);
  #endif
  _WriteData(PixelIndex);
}

/*********************************************************************
*
*       LCD_L0_GetPixelIndex
*
* Purpose:
*   Returns the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
LCD_PIXELINDEX LCD_L0_GetPixelIndex(int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  #if RAM_ADDR_SET
    /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
    #if (LCD_SWAP_XY | LCD_MIRROR_X | LCD_MIRROR_Y)
      int xPhys = LOG2PHYS_X(x, y);
      int yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    if ((xPhys < _x0) | (xPhys > _x1) | (yPhys < _y0) | (yPhys > _y1)) {
      _SetRect(0, 0, LCD_XSIZE - 1, LCD_YSIZE - 1);
    }
    #if LCD_CACHE
      _SET_CACHE_ADDR(xPhys, yPhys);
    #else
      _SetPhysRAMAddr(xPhys, yPhys);
    #endif
  #else
    #if LCD_CACHE
      _SET_CACHE_ADDR(x, y);
    #else
      _SetPhysRAMAddr(x, y);
    #endif
  #endif
  PixelIndex = READ_DATA();
  return PixelIndex;
}

/*********************************************************************
*
*       LCD_L0_XorPixel
*/
void LCD_L0_XorPixel(int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  
  PixelIndex = LCD_L0_GetPixelIndex(x, y);
  PixelIndex ^= _IndexMask;
  LCD_L0_SetPixelIndex(x, y, PixelIndex);
}

/*********************************************************************
*
*       LCD_L0_DrawHLine
*/
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_pContext->DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    LCD_L0_FillRect(x0, y, x1, y);
  }
}

/*********************************************************************
*
*       LCD_L0_DrawVLine
*/
void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_pContext->DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    LCD_L0_FillRect(x, y0, x, y1);
  }
}

/*********************************************************************
*
*       LCD_L0_FillRect
*/
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  if (GUI_pContext->DrawMode & LCD_DRAWMODE_XOR) {
    #if LCD_CACHE
      U32 NumPixels;
      LCD_PIXELINDEX Mask;
      Mask = _IndexMask;
      _SetRect(x0, y0, x1, y1);
      NumPixels = (U32)(x1 - x0 + 1) * (U32)(y1 - y0 + 1);
      while (NumPixels--) {
        *(_pVRam + _Addr) ^= Mask;
        _IncrementCursor();
      }
      _SendCacheRect(x0, y0, x1, y1);
    #else
      for (; y0 <= y1; y0++) {
        int x = x0;
        for (; x <= x1; x++) {
          LCD_L0_XorPixel(x, y0);
        }
      }
    #endif
  } else {
    U32 NumPixels;
    NumPixels = (U32)(x1 - x0 + 1) * (U32)(y1 - y0 + 1);
    _SetRect(x0, y0, x1, y1);
    _WriteDataM(LCD_COLORINDEX, NumPixels);
    #if LCD_CACHE
      _SendCacheRect(x0, y0, x1, y1);
    #endif
  }
}

/*********************************************************************
*
*       LCD_L0_DrawBitmap
*/
void LCD_L0_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 * pData, int Diff,
                       const LCD_PIXELINDEX * pTrans)
{
  int i;
  if (((BitsPerPixel != 1) && \
       (BitsPerPixel != 2) && \
       (BitsPerPixel != 4) && \
       (BitsPerPixel != 8)) || \
      ((GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) != LCD_DRAWMODE_TRANS)) {
    _SetRect(x0 + Diff, y0, x0 + Diff + xsize - 1, y0 + ysize - 1);
  }
  /* Use _DrawBitLineXBPP */
  for (i = 0; i < ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
  #if LCD_CACHE
    if (((BitsPerPixel == 1) || 
         (BitsPerPixel == 2) || 
         (BitsPerPixel == 4) || 
         (BitsPerPixel == 8)) && 
        ((GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) == LCD_DRAWMODE_TRANS)) {
      _SetRect(x0 + Diff, y0, x0 + Diff + xsize - 1, y0 + ysize - 1);
    }
    _SendCacheRect(x0 + Diff, y0, x0 + Diff + xsize - 1, y0 + ysize - 1);
  #endif
}

/*********************************************************************
*
*       LCD_L0_SetOrg
*/
void LCD_L0_SetOrg(int x, int y) {
  LCD_SET_ORG(x, y);
}

/*********************************************************************
*
*       LCD_On / LCD_Off
*/
void LCD_On (void) {
#ifdef LCD_ON
  LCD_ON();
#endif
}

void LCD_Off (void) {
#ifdef LCD_OFF
  LCD_OFF();
#endif
}

/*********************************************************************
*
*       LCD_L0_Init
*
* Purpose:
*   Initializes the LCD-controller.
*/
int  LCD_L0_Init(void) {
  #if LCD_CACHE
    PTR_ADDR Addr;
    int CacheSize;
  #endif
  GUI_DEVICE * pDevice;
  //
  // Avoid warnings
  //
  void (* volatile pFunc)(void);
  GUI_USE_PARA(_xSizePhys);
  GUI_USE_PARA(_ySizePhys);
  pFunc = (void (*)(void))_WriteU16_A0;
  pFunc = (void (*)(void))_WriteU16_A1;
  pFunc = (void (*)(void))_ReadU16_A1;
  pFunc = (void (*)(void))_CalcPhysAddr;
  #if LCD_CACHE
    pFunc = (void (*)(void))_IncX;
    //
    // Generate 16 bit aligned address for cache
    //
    #if (CACHE_OFFSET)
      CacheSize = CACHE_OFFSET;
    #else
      CacheSize = _xSize;
    #endif
    Addr = (PTR_ADDR)GUI_ALLOC_GetFixedBlock((U32)CacheSize * LCD_VYSIZE * 2 + 1) + 1;
    if (Addr == 0) {
      GUI_DEBUG_ERROROUT("GUIDRV_CompactColor_16.c:\nNo memory for cache available in LCD_L0_Init().");
    }
    Addr &= (U32)~1;
    _pVRam = (U16 *)Addr;
  #endif
  //
  // Get index mask
  //
  pDevice   = GUI_DEVICE__GetpDriver(GUI_pContext->SelLayer);
  _IndexMask = (U16)(pDevice->pColorConvAPI->pfGetIndexMask());
  //
  // Allocate line buffer
  //
  _pLineBuffer = (U16 *)GUI_ALLOC_GetFixedBlock(LCD_VXSIZE * 2);
  if (_pLineBuffer == NULL) {
    GUI_DEBUG_ERROROUT("GUIDRV_CompactColor_16.c:\nNo memory for line buffer available in LCD_L0_Init().");
  }
  //
  // Initialize display controller
  //
  LCD_X_DisplayDriver(LCD_DISPLAY_INDEX, LCD_X_INITCONTROLLER, NULL);
  //
  // Set the entry mode register in dependence of display orientation
  //
  #if   (LCD_CONTROLLER == 66766) || /* Hitachi HD66766, Samsung S6D0110A, Ilitek ILI9161 */ \
        (LCD_CONTROLLER == 66772) || /* Hitachi HD66772, Samsung S6D0117, Sitronix ST7712, Himax HX8301, Ilitek ILI9220 */ \
        (LCD_CONTROLLER == 66789) || /* Hitachi HD66789 */ \
        (LCD_CONTROLLER == 66701) || /* Renesas R63401, Renesas R61509, OriseTech SPFD5420A, Ilitek ILI9326 */ \
        (LCD_CONTROLLER == 66702) || /* Solomon SSD1284, Solomon SSD1289, Solomon SSD1298 */ \
        (LCD_CONTROLLER == 66703) || /* Toshiba JBT6K71 */ \
        (LCD_CONTROLLER == 66705) || /* Samsung S6D0129 */ \
        (LCD_CONTROLLER == 66708) || /* Ilitek ILI9320, Ilitek ILI9325, Ilitek ILI9328, LG Electronics LGDP4531, LG Electronics LGDP4551, OriseTech SPFD5408, Renesas R61505, Renesas R61580 */ \
        (LCD_CONTROLLER == 66714)    /* Solomon SSD2119 */
    _WriteU16_A0(REG_INC_MODE);
    #if defined(LCD_REG_INCMODE)
      _WriteU16_A1(((INC_MODE_HB << 8) | INC_MODE_LB) | LCD_REG_INCMODE);
    #else
      _WriteU16_A1((INC_MODE_HB << 8) | INC_MODE_LB);
    #endif
  #elif (LCD_CONTROLLER == 66704) || /* Sharp LCY-A06003 */ \
        (LCD_CONTROLLER == 66706) || /* MagnaChip D54E4PA7551 */ \
        (LCD_CONTROLLER == 66709) || /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */ \
        (LCD_CONTROLLER == 66712) || /* Himax HX8347, Himax HX8352 */ \
        (LCD_CONTROLLER == 66713) || /* Himax HX8340 */ \
        (LCD_CONTROLLER == 66715) || /* Himax HX8352B */ \
        (LCD_CONTROLLER == 66717)    /* Sitronix ST7787 */
    LCD_WRITE_A0(REG_INC_MODE);
    #if defined(LCD_REG_INCMODE)
      LCD_WRITE_A1(INC_MODE_LB | LCD_REG_INCMODE);
    #else
      LCD_WRITE_A1(INC_MODE_LB);
    #endif
  #elif (LCD_CONTROLLER == 66710)    /* Novatek NT7573 */
    #if (LCD_CACHE == 0)
      LCD_WRITE_A0(REG_INC_MODE);
      LCD_WRITE_A0(INC_MODE_LB);
    #endif
  #elif (LCD_CONTROLLER == 66707)    /* Himax HX8312A */
    _WriteU16_A0((REG_INC_MODE_1 << 8) | INC_MODE_R1 | LCD_REG01);
    _WriteU16_A0((REG_INC_MODE_5 << 8) | INC_MODE_R5);
  #elif (LCD_CONTROLLER == 66700)    /* Sharp LR38825 */
    _WriteU16_A0((REG_INC_MODE << 8) | INC_MODE_LB);
  #endif
  GUI_USE_PARA(pFunc);
  return 0;
}

/*********************************************************************
*
*       LCD_L0_SetLUTEntry
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  GUI_USE_PARA(Pos);
  GUI_USE_PARA(Color);
}

/*********************************************************************
*
*       LCD_L0_ControlCache
*/
#if  (LCD_SUPPORT_CACHECONTROL == 1)
int LCD_L0_ControlCache(int cmd) {
  switch (cmd) {
    case LCD_CC_LOCK:   /* Set Cache to lock state.*/
      _CacheLocked = 1;
      break;
    case LCD_CC_UNLOCK: /* Set Cache to unlock state ... must flush !*/
      _CacheLocked = 0;
    case LCD_CC_FLUSH:  /* Flush cache */
      if (_CacheStat) {
        int OldState;
        OldState     = _CacheLocked;
        _CacheLocked = 0;
        _CacheStat   = 0;
        _FlushCache();
        _CacheLocked = OldState;
      }
  }
  return _CacheStat;
}
#endif

#if (LCD_SUPPORT_CACHECONTROL == 1)
void LCD_L0_Refresh(GUI_DEVICE * pDevice) {
  int OldState;

  OldState      = _CacheLocked;
  _CacheLocked  = 0;
  _CacheStat    = 0;
  _CacheRect.x0 = 0;
  _CacheRect.y0 = 0;
  _CacheRect.x1 = LCD_XSIZE - 1;
  _CacheRect.y1 = LCD_YSIZE - 1;
  _FlushCache();
  _CacheLocked  = OldState;
}
#endif

/*********************************************************************
*
*       LCD_L0_GetDevFunc
*/
void (* LCD_L0_GetDevFunc(int Index))(void) {
  switch (Index) {
  #if (LCD_CACHE == 0) && ( \
        (LCD_CONTROLLER == 66709) || /* Epson S1D19122, Himax HX8353, Novatek NT39122, Orisetech SPFD54124C, Orisetech SPFD5414D, Renesas R61516, Sitronix ST7628, Sitronix ST7637, Sitronix ST7735, Sitronix ST7715, Solomon SSD1355, Solomon SSD1963, Solomon SSD1961, Himax HX8325A */ \
        (LCD_CONTROLLER == 66716)    /* Ampire FSA506 */ \
      )
  case LCD_DEVFUNC_READRECT:
    return (void (*)(void))_ReadRect;
  #endif
  #if (GUI_VERSION >= 41200)
  case LCD_DEVFUNC_NEXT_PIXEL:
    return (void (*)(void))&_NextPixel_API;
  #endif
  #if (LCD_SUPPORT_CACHECONTROL == 1)
  case LCD_DEVFUNC_CONTROLCACHE:
    return (void (*)(void))LCD_L0_ControlCache;
  case LCD_DEVFUNC_REFRESH:
    return (void (*)(void))LCD_L0_Refresh;
  #endif
  }
  return NULL;
}

/*********************************************************************
*
*       LCD_L0_WriteU16_A0
*/
#if (LCD_USE_SERIAL_3PIN)
void LCD_L0_WriteU16_A0(U16 Word);
void LCD_L0_WriteU16_A0(U16 Word) {
  _WriteU16_A0(Word);
}
#endif

/*********************************************************************
*
*       LCD_L0_WriteU16_A1
*/
#if (LCD_USE_SERIAL_3PIN)
void LCD_L0_WriteU16_A1(U16 Word);
void LCD_L0_WriteU16_A1(U16 Word) {
  _WriteU16_A1(Word);
}
#endif

#else

const GUI_DEVICE_API DISPLAY_DRIVER_API;

void GUIDRV_CompactColor_16_c(void);
void GUIDRV_CompactColor_16_c(void) { } /* avoid empty object files */

#endif

/*************************** End of file ****************************/
