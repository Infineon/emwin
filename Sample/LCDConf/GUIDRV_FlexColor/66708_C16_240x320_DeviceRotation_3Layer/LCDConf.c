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
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Private.h"
#include "WM.h"
#include "GUIDRV_FlexColor.h"
#include "LCDConf.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define PERIPH_BASE                            ((U32)0x40000000) // Peripheral base address in the alias region

#define AHB1PERIPH_BASE                        (PERIPH_BASE + 0x00020000)

#define RCC_BASE                               (AHB1PERIPH_BASE + 0x3800)

#define RCC                                    ((RCC_TypeDef *) RCC_BASE)

#define BCR_MBKEN_SET                          ((U32)0x00000001)
#define BCR_MBKEN_RESET                        ((U32)0x000FFFFE)

#define RCC_AHB3Periph_FSMC                    ((U32)0x00000001)

#define FSMC_R_BASE                            ((U32)0xA0000000) // FSMC registers base address

#define FSMC_Bank1_R_BASE                      (FSMC_R_BASE + 0x0000)
#define FSMC_Bank1E_R_BASE                     (FSMC_R_BASE + 0x0104)

#define FSMC_Bank1_NORSRAM3                    ((U32)0x00000004)

#define FSMC_Bank1E                            ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)
#define FSMC_Bank1                             ((FSMC_Bank1_TypeDef *)  FSMC_Bank1_R_BASE)

#define FSMC_AccessMode_A                      ((U32)0x00000000)
#define FSMC_Bank1_NORSRAM2                    ((U32)0x00000002)
#define FSMC_DataAddressMux_Disable            ((U32)0x00000000)
#define FSMC_MemoryType_SRAM                   ((U32)0x00000000)
#define FSMC_MemoryDataWidth_16b               ((U32)0x00000010)
#define FSMC_BurstAccessMode_Disable           ((U32)0x00000000)
#define FSMC_AsynchronousWait_Disable          ((U32)0x00000000)
#define FSMC_WaitSignalPolarity_Low            ((U32)0x00000000)
#define FSMC_WrapMode_Disable                  ((U32)0x00000000)
#define FSMC_WaitSignalActive_BeforeWaitState  ((U32)0x00000000)
#define FSMC_WriteOperation_Enable             ((U32)0x00001000)
#define FSMC_WaitSignal_Disable                ((U32)0x00000000)
#define FSMC_ExtendedMode_Disable              ((U32)0x00000000)
#define FSMC_WriteBurst_Disable                ((U32)0x00000000)
#define FSMC_MemoryType_NOR                    ((U32)0x00000008)
#define FSMC_ExtendedMode_Enable               ((U32)0x00004000)

#define BCR_FACCEN_SET                         ((U32)0x00000040)

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef struct
{
  volatile U32 BTCR[8];    // NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C
} FSMC_Bank1_TypeDef;

typedef struct
{
  volatile U32 BWTR[7];    // NOR/PSRAM write timing registers, Address offset: 0x104-0x11C
} FSMC_Bank1E_TypeDef;

typedef struct
{
  volatile U32 MODER;    // GPIO port mode register,               Address offset: 0x00     
  volatile U32 OTYPER;   // GPIO port output type register,        Address offset: 0x04     
  volatile U32 OSPEEDR;  // GPIO port output speed register,       Address offset: 0x08     
  volatile U32 PUPDR;    // GPIO port pull-up/pull-down register,  Address offset: 0x0C     
  volatile U32 IDR;      // GPIO port input data register,         Address offset: 0x10     
  volatile U32 ODR;      // GPIO port output data register,        Address offset: 0x14     
  volatile U16 BSRRL;    // GPIO port bit set/reset low register,  Address offset: 0x18     
  volatile U16 BSRRH;    // GPIO port bit set/reset high register, Address offset: 0x1A     
  volatile U32 LCKR;     // GPIO port configuration lock register, Address offset: 0x1C     
  volatile U32 AFR[2];   // GPIO alternate function registers,     Address offset: 0x20-0x24
} GPIO_TypeDef;

typedef struct
{
  volatile U32 CR;            // RCC clock control register,                                  Address offset: 0x00
  volatile U32 PLLCFGR;       // RCC PLL configuration register,                              Address offset: 0x04
  volatile U32 CFGR;          // RCC clock configuration register,                            Address offset: 0x08
  volatile U32 CIR;           // RCC clock interrupt register,                                Address offset: 0x0C
  volatile U32 AHB1RSTR;      // RCC AHB1 peripheral reset register,                          Address offset: 0x10
  volatile U32 AHB2RSTR;      // RCC AHB2 peripheral reset register,                          Address offset: 0x14
  volatile U32 AHB3RSTR;      // RCC AHB3 peripheral reset register,                          Address offset: 0x18
  U32      RESERVED0;         // Reserved, 0x1C                                                                   
  volatile U32 APB1RSTR;      // RCC APB1 peripheral reset register,                          Address offset: 0x20
  volatile U32 APB2RSTR;      // RCC APB2 peripheral reset register,                          Address offset: 0x24
  U32      RESERVED1[2];      // Reserved, 0x28-0x2C                                                              
  volatile U32 AHB1ENR;       // RCC AHB1 peripheral clock register,                          Address offset: 0x30
  volatile U32 AHB2ENR;       // RCC AHB2 peripheral clock register,                          Address offset: 0x34
  volatile U32 AHB3ENR;       // RCC AHB3 peripheral clock register,                          Address offset: 0x38
  U32      RESERVED2;         // Reserved, 0x3C                                                                   
  volatile U32 APB1ENR;       // RCC APB1 peripheral clock enable register,                   Address offset: 0x40
  volatile U32 APB2ENR;       // RCC APB2 peripheral clock enable register,                   Address offset: 0x44
  U32      RESERVED3[2];      // Reserved, 0x48-0x4C                                                              
  volatile U32 AHB1LPENR;     // RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
  volatile U32 AHB2LPENR;     // RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
  volatile U32 AHB3LPENR;     // RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
  U32      RESERVED4;         // Reserved, 0x5C                                                                   
  volatile U32 APB1LPENR;     // RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
  volatile U32 APB2LPENR;     // RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
  U32      RESERVED5[2];      // Reserved, 0x68-0x6C                                                              
  volatile U32 BDCR;          // RCC Backup domain control register,                          Address offset: 0x70
  volatile U32 CSR;           // RCC clock control & status register,                         Address offset: 0x74
  U32      RESERVED6[2];      // Reserved, 0x78-0x7C                                                              
  volatile U32 SSCGR;         // RCC spread spectrum clock generation register,               Address offset: 0x80
  volatile U32 PLLI2SCFGR;    // RCC PLLI2S configuration register,                           Address offset: 0x84

#ifdef STM32F427X
  U32      RESERVED7;         // Reserved, 0x88                                                                   
  volatile U32 DCKCFGR;       // RCC Dedicated Clocks configuration register,                 Address offset: 0x8C
#endif // STM32F427X
  
} RCC_TypeDef;

typedef struct
{
  U32 FSMC_AddressSetupTime;       // Defines the number of HCLK cycles to configure
                                   //          the duration of the address setup time.
                                   //          This parameter can be a value between 0 and 0xF.
                                   //          @note This parameter is not used with synchronous NOR Flash memories.

  U32 FSMC_AddressHoldTime;        // Defines the number of HCLK cycles to configure
                                   //          the duration of the address hold time.
                                   //          This parameter can be a value between 0 and 0xF.
                                   //          @note This parameter is not used with synchronous NOR Flash memories.

  U32 FSMC_DataSetupTime;          // Defines the number of HCLK cycles to configure
                                   //          the duration of the data setup time.
                                   //          This parameter can be a value between 0 and 0xFF.
                                   //          @note This parameter is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories.

  U32 FSMC_BusTurnAroundDuration;  // Defines the number of HCLK cycles to configure
                                   //          the duration of the bus turnaround.
                                   //          This parameter can be a value between 0 and 0xF.
                                   //          @note This parameter is only used for multiplexed NOR Flash memories.

  U32 FSMC_CLKDivision;            // Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                   //          This parameter can be a value between 1 and 0xF.
                                   //          @note This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses.

  U32 FSMC_DataLatency;            // Defines the number of memory clock cycles to issue
                                   //          to the memory before getting the first data.
                                   //          The parameter value depends on the memory type as shown below:
                                   //           - It must be set to 0 in case of a CRAM
                                   //           - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                   //           - It may assume a value between 0 and 0xF in NOR Flash memories
                                   //             with synchronous burst mode enable

  U32 FSMC_AccessMode;             // Specifies the asynchronous access mode.
                                   //          This parameter can be a value of @ref FSMC_Access_Mode
}FSMC_NORSRAMTimingInitTypeDef;

typedef struct
{
  U32 FSMC_Bank;                // Specifies the NOR/SRAM memory bank that will be used.
                                //          This parameter can be a value of @ref FSMC_NORSRAM_Bank

  U32 FSMC_DataAddressMux;      // Specifies whether the address and data values are
                                //          multiplexed on the data bus or not.
                                //          This parameter can be a value of @ref FSMC_Data_Address_Bus_Multiplexing

  U32 FSMC_MemoryType;          // Specifies the type of external memory attached to
                                //          the corresponding memory bank.
                                //          This parameter can be a value of @ref FSMC_Memory_Type

  U32 FSMC_MemoryDataWidth;     // Specifies the external memory device width.
                                //          This parameter can be a value of @ref FSMC_Data_Width

  U32 FSMC_BurstAccessMode;     // Enables or disables the burst access mode for Flash memory,
                                //          valid only with synchronous burst Flash memories.
                                //          This parameter can be a value of @ref FSMC_Burst_Access_Mode

  U32 FSMC_AsynchronousWait;    // Enables or disables wait signal during asynchronous transfers,
                                //         valid only with asynchronous Flash memories.
                                //         This parameter can be a value of @ref FSMC_AsynchronousWait

  U32 FSMC_WaitSignalPolarity;  // Specifies the wait signal polarity, valid only when accessing
                                //          the Flash memory in burst mode.
                                //          This parameter can be a value of @ref FSMC_Wait_Signal_Polarity

  U32 FSMC_WrapMode;            // Enables or disables the Wrapped burst access mode for Flash
                                //          memory, valid only when accessing Flash memories in burst mode.
                                //          This parameter can be a value of @ref FSMC_Wrap_Mode

  U32 FSMC_WaitSignalActive;    // Specifies if the wait signal is asserted by the memory one
                                //          clock cycle before the wait state or during the wait state,
                                //          valid only when accessing memories in burst mode.
                                //          This parameter can be a value of @ref FSMC_Wait_Timing

  U32 FSMC_WriteOperation;      // Enables or disables the write operation in the selected bank by the FSMC.
                                //          This parameter can be a value of @ref FSMC_Write_Operation

  U32 FSMC_WaitSignal;          // Enables or disables the wait state insertion via wait
                                //          signal, valid for Flash memory access in burst mode.
                                //          This parameter can be a value of @ref FSMC_Wait_Signal

  U32 FSMC_ExtendedMode;        // Enables or disables the extended mode.
                                //          This parameter can be a value of @ref FSMC_Extended_Mode

  U32 FSMC_WriteBurst;          // Enables or disables the write burst operation.
                                //          This parameter can be a value of @ref FSMC_Write_Burst

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct; // Timing Parameters for write and read access if the  Extended Mode is not used

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;     // Timing Parameters for write access if the  Extended Mode is used
}FSMC_NORSRAMInitTypeDef;

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS 240
#define YSIZE_PHYS 320

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

//
// FSMC Bank_1_NORSRAM3 address for communication with the LCD controller
//
#define ADDR_C 0x68000000
#define ADDR_D 0x68000002

#define SET_REG(x) *(U16 *)ADDR_C = x
#define GET_REG(x) x = *(U16 *)ADDR_C
#define SET_DTA(x) *(U16 *)ADDR_D = x
#define GET_DTA(x) x = *(U16 *)ADDR_D

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/****/  // typdefs and static varaible below are important
//
// A structure which contains information about the different drivers
//
typedef struct {
  GUI_DEVICE       * pDevice;
  CONFIG_FLEXCOLOR   Config;
}DRIVER_STRUCT;

//
// Five devices, one at the top, one at the bottom and three in the middle
//
static DRIVER_STRUCT _aDriver[6];
//
// An array which holds different orientations
//
static int _aOrientation[] = {
  0,
  GUI_SWAP_XY  | GUI_MIRROR_X,
  GUI_MIRROR_X | GUI_MIRROR_Y,
  GUI_SWAP_XY  | GUI_MIRROR_Y
};
//
// Variable to the remember the last used orientation
//
static int _LastOrientationIndex;
//
// This array points to the currently selected driver for the different layers (0 - 2)
//
static DRIVER_STRUCT * _apDriver[3];
//
// Variable to store the last set orientation
//
static int _Orientation = -1;
//
// Forward declaration of _SetOrientation()
//
static void _SetOrientation(int Orientation);

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _RCC_AHB3PeriphClockCmd
*/
static void _RCC_AHB3PeriphClockCmd(U32 RCC_AHB3Periph, FunctionalState NewState) {
  if (NewState != DISABLE) {
    RCC->AHB3ENR |= RCC_AHB3Periph;
  } else {
    RCC->AHB3ENR &= ~RCC_AHB3Periph;
  }
}

/*********************************************************************
*
*       _FSMC_NORSRAMInit
*/
static void _FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct) {
  //
  // Bank1 NOR/SRAM control register configuration
  //
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] =
            (U32)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
            FSMC_NORSRAMInitStruct->FSMC_MemoryType |
            FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
            FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
            FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
            FSMC_NORSRAMInitStruct->FSMC_WrapMode |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
            FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
            FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
            FSMC_NORSRAMInitStruct->FSMC_WriteBurst;
  if(FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR) {
    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (U32)BCR_FACCEN_SET;
  }
  //
  // Bank1 NOR/SRAM timing register configuration
  //
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank+1] =
            (U32)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
             FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;
  //
  // Bank1 NOR/SRAM timing register for write configuration, if extended mode is used
  //
  if(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable) {
    FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] =
              (U32)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4 )|
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision << 20) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency << 24) |
               FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;
  } else {
    FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
  }
}

/*********************************************************************
*
*       _FSMC_NORSRAMCmd
*/
static void _FSMC_NORSRAMCmd(U32 FSMC_Bank, FunctionalState NewState) {
  if (NewState != DISABLE) {
    //
    // Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register
    //
    FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_SET;
  } else {
    //
    // Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register
    //
    FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_RESET;
  }
}

/*********************************************************************
*
*       _LCD_FSMCConfig
*/
static void _LCD_FSMCConfig(void) {
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  
  //
  // Enable FSMC clock
  //
  _RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  //
  // FSMC Configuration
  //
  // FSMC_Bank1_NORSRAM3 configuration
  //
  p.FSMC_AddressSetupTime      = 5;
  p.FSMC_AddressHoldTime       = 0;
  p.FSMC_DataSetupTime         = 9;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision           = 0;
  p.FSMC_DataLatency           = 0;
  p.FSMC_AccessMode            = FSMC_AccessMode_A;
  // Color LCD configuration
  // LCD configured as follow:
  //    - Data/Address MUX = Disable
  //    - Memory Type = SRAM
  //    - Data Width = 16bit
  //    - Write Operation = Enable
  //    - Extended Mode = Enable
  //    - Asynchronous Wait = Disable
  FSMC_NORSRAMInitStructure.FSMC_Bank                  = FSMC_Bank1_NORSRAM3;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait      = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &p;
  _FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
  //
  // Enable Bank1_NORSRAM3
  //
  _FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

/*********************************************************************
*
*       _SetReg
*
*  Function description:
*  In general this function tells the LCD controller were we want to 
*  write to or read from.
*  Now it also checks the orientation before drawing and sets a new
*  orientation for LCD controller if necessary. This is might be not
*  the best position. Unfortunately, for now there is no good place
*  in the emWin API to hook in.
*/
/****/
static void _SetReg(U16 Reg) {
  //
  // Check if the layer to be drawn on has the same orientation as the one
  // the LCD controller works with. If this is not the case, change it.
  //
  if (_Orientation != _apDriver[GUI_pContext->SelLayer]->Config.Orientation) {
    //
    // Store last set orientation
    //
    _Orientation = _apDriver[GUI_pContext->SelLayer]->Config.Orientation;
    //
    // Set the orientation of the LCD controller
    //
    _SetOrientation(_apDriver[GUI_pContext->SelLayer]->Config.Orientation);
  }
  SET_REG(Reg);
}

/*********************************************************************
*
*       _SetDta
*/
static void _SetDta(U16 Dta) {
  SET_DTA(Dta);
}

/*********************************************************************
*
*       _SetDtaM
*/
static void _SetDtaM(U16 * pDta, int NumItems) {
  do {
    SET_DTA(*pDta++);
  } while (--NumItems);
}

/*********************************************************************
*
*       _GetDtaM
*/
static void _GetDtaM(U16 * pDta, int NumItems) {
  do {
    GET_DTA(*pDta++);
  } while (--NumItems);
}

/*********************************************************************
*
*       _WriteReg
*/
#ifdef __GNUC__
static void _WriteReg(U8 Reg, U16 Dta) __attribute__((optimize(0))); // Disable GCC optimization only for this function
#endif
static void _WriteReg(U8 Reg, U16 Dta) {
  SET_REG(Reg);
  SET_DTA(Dta);
}

/*********************************************************************
*
*       _Delay
*/
static void _Delay(volatile U32 nCount) {
  volatile U32 index = 0;

  for(index = (100000 * nCount); index != 0; index--);
}

/*********************************************************************
*
*       _Init9320
*/
static void _Init9320(void);
static void _Init9320(void) {
  //
  // Start Initial Sequence
  //
  _WriteReg(229, 0x8000); // Set the internal vcore voltage
  _WriteReg(  0, 0x0001); // Start internal OSC.
  _WriteReg(  1, 0x0100); // set SS and SM bit
  _WriteReg(  2, 0x0700); // set 1 line inversion
  _WriteReg(  3, 0x1030); // set GRAM write direction and BGR=1.
  _WriteReg(  4, 0x0000); // Resize register
  _WriteReg(  8, 0x0202); // set the back porch and front porch
  _WriteReg(  9, 0x0000); // set non-display area refresh cycle ISC[3:0]
  _WriteReg( 10, 0x0000); // FMARK function
  _WriteReg( 12, 0x0000); // RGB interface setting
  _WriteReg( 13, 0x0000); // Frame marker Position
  _WriteReg( 15, 0x0000); // RGB interface polarity
  //
  // Power On sequence
  //
  _WriteReg( 16, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  _WriteReg( 17, 0x0000); // DC1[2:0], DC0[2:0], VC[2:0]
  _WriteReg( 18, 0x0000); // VREG1OUT voltage
  _WriteReg( 19, 0x0000); // VDV[4:0] for VCOM amplitude
  _Delay(20);             // Dis-charge capacitor power voltage (200ms)
  _WriteReg( 16, 0x17B0); // SAP, BT[3:0], AP, DSTB, SLP, STB
  _WriteReg( 17, 0x0137); // DC1[2:0], DC0[2:0], VC[2:0]
  _Delay(5);              // Delay 50 ms
  _WriteReg( 18, 0x0139); // VREG1OUT voltage
  _Delay(5);              // Delay 50 ms
  _WriteReg( 19, 0x1d00); // VDV[4:0] for VCOM amplitude
  _WriteReg( 41, 0x0013); // VCM[4:0] for VCOMH
  _Delay(5);              // Delay 50 ms
  _WriteReg( 32, 0x0000); // GRAM horizontal Address
  _WriteReg( 33, 0x0000); // GRAM Vertical Address
  //
  // Adjust the Gamma Curve
  //
  _WriteReg( 48, 0x0007);
  _WriteReg( 49, 0x0007);
  _WriteReg( 50, 0x0007);
  _WriteReg( 53, 0x0007);
  _WriteReg( 54, 0x0007);
  _WriteReg( 55, 0x0700);
  _WriteReg( 56, 0x0700);
  _WriteReg( 57, 0x0700);
  _WriteReg( 60, 0x0700);
  _WriteReg( 61, 0x1F00);
  //
  // Set GRAM area
  //
  _WriteReg( 80, 0x0000); // Horizontal GRAM Start Address
  _WriteReg( 81, 0x00EF); // Horizontal GRAM End Address
  _WriteReg( 82, 0x0000); // Vertical GRAM Start Address
  _WriteReg( 83, 0x013F); // Vertical GRAM End Address
  _WriteReg( 96, 0x2700); // Gate Scan Line
  _WriteReg( 97, 0x0001); // NDL,VLE, REV
  _WriteReg(106, 0x0000); // set scrolling line
  //
  // Partial Display Control
  //
  _WriteReg(128, 0x0000);
  _WriteReg(129, 0x0000);
  _WriteReg(130, 0x0000);
  _WriteReg(131, 0x0000);
  _WriteReg(132, 0x0000);
  _WriteReg(133, 0x0000);
  //
  // Panel Control
  //
  _WriteReg(144, 0x0010);
  _WriteReg(146, 0x0000);
  _WriteReg(147, 0x0003);
  _WriteReg(149, 0x0110);
  _WriteReg(151, 0x0000);
  _WriteReg(152, 0x0000);
  _WriteReg(  3, 0x1018);
  _WriteReg(  7, 0x0173); // 65K color and display ON
}

/*********************************************************************
*
*       _Init9325
*/
static void _Init9325(void);
static void _Init9325(void) {
  //
  // Start Initial Sequence
  //
  _WriteReg(  0, 0x0001); // Start internal OSC.
  _WriteReg(  1, 0x0100); // Set SS and SM bit
  _WriteReg(  2, 0x0700); // Set 1 line inversion
  _WriteReg(  3, 0x1018); // Set GRAM write direction and BGR=1.
  _WriteReg(  4, 0x0000); // Resize register
  _WriteReg(  8, 0x0202); // Set the back porch and front porch
  _WriteReg(  9, 0x0000); // Set non-display area refresh cycle ISC[3:0]
  _WriteReg( 10, 0x0000); // FMARK function
  _WriteReg( 12, 0x0000); // RGB interface setting
  _WriteReg( 13, 0x0000); // Frame marker Position
  _WriteReg( 15, 0x0000); // RGB interface polarity
  //
  // Power On sequence
  //
  _WriteReg( 16, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  _WriteReg( 17, 0x0000); // DC1[2:0], DC0[2:0], VC[2:0]
  _WriteReg( 18, 0x0000); // VREG1OUT voltage
  _WriteReg( 19, 0x0000); // VDV[4:0] for VCOM amplitude
  _Delay(20);             // Dis-charge capacitor power voltage (200ms)
  _WriteReg( 16, 0x17B0); // SAP, BT[3:0], AP, DSTB, SLP, STB
  _WriteReg( 17, 0x0137); // DC1[2:0], DC0[2:0], VC[2:0]
  _Delay(5);              // Delay 50 ms
  _WriteReg( 18, 0x0139); // VREG1OUT voltage
  _Delay(5);              // Delay 50 ms
  _WriteReg( 19, 0x1d00); // VDV[4:0] for VCOM amplitude
  _WriteReg( 41, 0x0013); // VCM[4:0] for VCOMH
  _Delay(5);              // Delay 50 ms
  _WriteReg( 32, 0x0000); // GRAM horizontal Address
  _WriteReg( 33, 0x0000); // GRAM Vertical Address
  //
  // Adjust the Gamma Curve (ILI9325)
  //
  _WriteReg( 48, 0x0707);
  _WriteReg( 49, 0x0707);
  _WriteReg( 50, 0x0707);
  _WriteReg( 53, 0x0007);
  _WriteReg( 54, 0x0000);
  _WriteReg( 55, 0x0000);
  _WriteReg( 56, 0x0000);
  _WriteReg( 57, 0x0000);
  _WriteReg( 60, 0x0000);
  _WriteReg( 61, 0x0000);
  //
  // Set GRAM area
  //
  _WriteReg( 80, 0x0000); // Horizontal GRAM Start Address
  _WriteReg( 81, 0x00EF); // Horizontal GRAM End Address
  _WriteReg( 82, 0x0000); // Vertical GRAM Start Address
  _WriteReg( 83, 0x013F); // Vertical GRAM End Address
  _WriteReg( 96, 0xA700); // Gate Scan Line(GS=1, scan direction is G320~G1)
  _WriteReg( 97, 0x0001); // NDL,VLE, REV
  _WriteReg(106, 0x0000); // set scrolling line
  //
  // Partial Display Control
  //
  _WriteReg(128, 0x0000);
  _WriteReg(129, 0x0000);
  _WriteReg(130, 0x0000);
  _WriteReg(131, 0x0000);
  _WriteReg(132, 0x0000);
  _WriteReg(133, 0x0000);
  //
  // Panel Control
  //
  _WriteReg(144, 0x0010);
  _WriteReg(146, 0x0000);
  _WriteReg(147, 0x0003);
  _WriteReg(149, 0x0110);
  _WriteReg(151, 0x0000);
  _WriteReg(152, 0x0000);
  _WriteReg(  3, 0x1018);
  _WriteReg(  7, 0x0133); // 65K color and display ON
}

/*********************************************************************
*
*       _InitController
*/
#if defined (__CROSSWORKS_ARM) || defined (__SES_ARM)
  void __attribute__((optimize("O0"))) _InitController(void) {
#else
  static void _InitController(void) {
#endif
  U16 Id;

  SET_REG(0x00);
  GET_DTA(Id);
  switch (Id) {
  case 0x9320:
    _Init9320();
    break;
  case 0x9325:
    _Init9325();
    break;
  default:
    GUI_ErrorOut(__FILE__": Display controller not supported. Execution stopped.");
  }
}

/*********************************************************************
*
*       _SetOrientation
*
*  Function description:
*    This function is from the FlexColor_Func66708. It needs to be
*    adapted for use with FlexColor_Func66709. Simple copy paste
*    the array from _SetOrientation() out of FlexColor_Func66709
*    and adapt the the value for _SetReg() accordingly.
*/
/****/
static void _SetOrientation(int Orientation) {
  const U8 aOrientation[] = {
    __XX____, // (!GUI_MIRROR_X && !GUI_MIRROR_Y && !GUI_SWAP_XY)
    __X_____, // ( GUI_MIRROR_X && !GUI_MIRROR_Y && !GUI_SWAP_XY)
    ___X____, // (!GUI_MIRROR_X &&  GUI_MIRROR_Y && !GUI_SWAP_XY)
    ________, // ( GUI_MIRROR_X &&  GUI_MIRROR_Y && !GUI_SWAP_XY)
    __XXX___, // (!GUI_MIRROR_X && !GUI_MIRROR_Y &&  GUI_SWAP_XY)
    __X_X___, // ( GUI_MIRROR_X && !GUI_MIRROR_Y &&  GUI_SWAP_XY)
    ___XX___, // (!GUI_MIRROR_X &&  GUI_MIRROR_Y &&  GUI_SWAP_XY)
    ____X___, // ( GUI_MIRROR_X &&  GUI_MIRROR_Y &&  GUI_SWAP_XY)
  };

  _SetReg(0x03);
  _SetDta(aOrientation[Orientation]);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_X_SetRotation
*
*  Function description:
*    This function uses the variable _LastOrientationIndex to unlink
*    the last used driver. Then it links the driver with the proper
*    orientation, stores the driver to be used in _apDriver and the
*    orientation in _LastOrientationIndex.
*    After that we invalidate the desktop window of layer 2 and all
*    its child windows.
*/
/****/
void LCD_X_SetRotation(int Orientation) {
  WM_HWIN    hWin;

  //
  // Unlink selected driver
  //
  GUI_DEVICE_Unlink(_aDriver[_LastOrientationIndex].pDevice);
  //
  // Link driver with proper orientation
  //
  GUI_DEVICE_Link(_aDriver[Orientation + 2].pDevice);
  //
  // Set driver at position for layer 2
  //
  _apDriver[2] = &_aDriver[Orientation + 2];
  //
  // Remember the last orientation used
  //
  _LastOrientationIndex = Orientation + 2;
  //
  // Get the desktop handle of layer 2
  //
  hWin = WM_GetDesktopWindowEx(2);
  //
  // Invalidate the desktop window and its child windows
  //
  WM_InvalidateWindowAndDescs(hWin);
}

/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE       * pDevice;
  CONFIG_FLEXCOLOR   Config;
  GUI_PORT_API       PortAPI;
  int                i;

  //
  // Set port API, for every driver the same
  //
  PortAPI.pfWrite16_A0  = _SetReg;   // Function to set a register to write to
  PortAPI.pfWrite16_A1  = _SetDta;   // Function for writing a single data block
  PortAPI.pfWriteM16_A1 = _SetDtaM;  // Function for writing multiple data blocks
  PortAPI.pfReadM16_A1  = _GetDtaM;  // Function for reading multiple data blocks
  //
  // First driver for a small segment at the top of the screen
  //
  _aDriver[0].pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);                       // Create the driver on layer 0
  LCD_SetSizeEx (0, XSIZE_PHYS,  30);                                                                           // Set the size for layer 0
  LCD_SetVSizeEx(0, XSIZE_PHYS,  30);                                                                           // Set a virtual size for layer 0
  _aDriver[0].Config.Orientation = ORIENTATION_0;                                                               // Set to default orientation
  _aDriver[0].Config.FirstSEG    = 0;                                                                           // First pixel in x where the driver writes to
  _aDriver[0].Config.FirstCOM    = 0;                                                                           // First pixel in y where the driver writes to
  GUIDRV_FlexColor_Config(_aDriver[0].pDevice, &_aDriver[0].Config);                                            // Set the configuration
  GUIDRV_FlexColor_SetFunc(_aDriver[0].pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);  // Set function pointers for the driver
  _apDriver[0] = &_aDriver[0];                                                                                  // Store the driver into _apDriver for layer 0
  LCD_Init();                                                                                                   // Call LCD_Init to initialize driver, this function is not documented and should be used carefully
  //
  // Second driver for a small segment at the bottom of the screen
  //
  _aDriver[1].pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 1);                       // Create the driver on layer 1
  LCD_SetSizeEx (1, XSIZE_PHYS,  50);                                                                           // Set the size for layer 1
  LCD_SetVSizeEx(1, XSIZE_PHYS,  50);                                                                           // Set a virtual size for layer 1
  LCD_SetPosEx  (1, 0,  270);                                                                                   // Set the position for layer 1
  _aDriver[1].Config.Orientation = ORIENTATION_0;                                                               // Set to default orientation
  _aDriver[1].Config.FirstSEG    = 0;                                                                           // First pixel in x where the driver writes to
  _aDriver[1].Config.FirstCOM    = 270;                                                                         // First pixel in y where the driver writes to
  GUIDRV_FlexColor_Config(_aDriver[1].pDevice, &_aDriver[1].Config);                                            // Set the configuration
  GUIDRV_FlexColor_SetFunc(_aDriver[1].pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);  // Set function pointers for the driver
  _apDriver[1] = &_aDriver[1];                                                                                  // Store the driver into _apDriver for layer 1
  LCD_Init();                                                                                                   // Call LCD_Init to initialize driver, this function is not documented and should be used carefully
  //
  // Third driver for the center part of the LCD, this part will be rotated.
  // Here we create 4 driver (could also be less driver), one for each orientation
  // and store the pointer of the different driver in the DRIVER_STRUCT array.
  //
  for (i = 2; i < GUI_COUNTOF(_aDriver); i++) {
    _aDriver[i].pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 2);                       // Create the driver on layer 2
    LCD_SetSizeEx (2, XSIZE_PHYS,  XSIZE_PHYS);                                                                   // Set the size for layer 2, XSIZE_PHYS for both axis, the layer is a square
    LCD_SetVSizeEx(2, XSIZE_PHYS,  XSIZE_PHYS);                                                                   // Set a virtual size for layer 2, XSIZE_PHYS for both axis, the layer is a square
    LCD_SetPosEx  (2, 0,  30);                                                                                    // Set the position for layer 2
    _aDriver[i].Config.Orientation = _aOrientation[i - 2];                                                        // Set to default orientation
    _aDriver[i].Config.FirstSEG    = 0;                                                                           // First pixel in x where the driver writes to
    _aDriver[i].Config.FirstCOM    = 30;                                                                          // First pixel in y where the driver writes to
    GUIDRV_FlexColor_Config(_aDriver[i].pDevice, &_aDriver[i].Config);                                            // Set the configuration
    GUIDRV_FlexColor_SetFunc(_aDriver[i].pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);  // Set function pointers for the driver
    _apDriver[2] = &_aDriver[i];                                                                                  // Store the current driver into _apDriver for layer 2
    LCD_Init();                                                                                                   // Call LCD_Init to initialize driver, this function is not documented and should be used carefully
    GUI_DEVICE_Unlink(_aDriver[i].pDevice);                                                                       // Unlink the currently selected driver for layer 2
  }
  //
  // Store the driver which should be used initially in _apDriver
  //
  _apDriver[2] = &_aDriver[2];
  //
  // Remember the orientation which should be used initially
  //
  _LastOrientationIndex = ORIENTATION_0 + 2;
  //
  // Link the driver with the default orientation
  //
  GUI_DEVICE_Link(_aDriver[2].pDevice);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *pData) {
  static int InitOnce = 1;
  int r;

  (void)LayerIndex;
  (void)pData;

  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    if (InitOnce) {
      _LCD_FSMCConfig();
      _InitController();
      InitOnce = 0;
    }
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/****** End Of File *************************************************/
