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
#include "GUIDRV_Lin.h"

#ifndef WIN32
  #include "RTOS.h"
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Layer configuration (to be modified)
*/
//
// Physical display size
//
#define XSIZE_PHYS 800
#define YSIZE_PHYS 480

//
// Color conversion
//
#if (GUI_USE_ARGB)
  #define COLOR_CONVERSION GUICC_M8888I
#else
  #define COLOR_CONVERSION GUICC_8888
#endif

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_LIN_32

//
// Buffers / VScreens
//
#define NUM_BUFFERS  3 // Number of multiple buffers to be used
#define NUM_VSCREENS 1 // Number of virtual screens to be used

/*********************************************************************
*
*       Configuration checking
*/
#ifndef   VRAM_ADDR
  #define VRAM_ADDR 0 // TBD by customer: This has to be the frame buffer start address
#endif
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
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif

#ifndef WIN32

/*********************************************************************
*
*       Display parameters
*/
#define HBP 80 // Horizontal back porch
#define HFP 48 // Horizontal front porch
#define HSW 32 // HSync signal width
#define VBP 15 // Vertical back porch
#define VFP 2  // Vertical front porch
#define VSW 6  // VSync signal width

/*********************************************************************
*
*       SFRs
*/
#define HWREG(x) (*((volatile unsigned long *)(x)))

/* CLKSEL_LCDC_PIXEL_CLK */
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK                                   (0x34)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL                            (0x00000003u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SHIFT                      (0x00000000u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL1                       (0x0u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL2                       (0x1u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL3                       (0x2u)
#define CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL4                       (0x3u)

/* L3S_CLKSTCTRL */
#define CM_PER_L3S_CLKSTCTRL                                            (0x4)
#define CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK                       (0x00000008u)
#define CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK_SHIFT                 (0x00000003u)
#define CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK_ACT                   (0x1u)
#define CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK_INACT                 (0x0u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL                                  (0x00000003u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SHIFT                            (0x00000000u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_HW_AUTO                          (0x3u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                         (0x0u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                         (0x1u)
#define CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP                          (0x2u)

/* L3_CLKSTCTRL */
#define CM_PER_L3_CLKSTCTRL                                             (0xc)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_CPTS_RFT_GCLK                   (0x00000040u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_CPTS_RFT_GCLK_SHIFT             (0x00000006u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_CPTS_RFT_GCLK_ACT               (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_CPTS_RFT_GCLK_INACT             (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_EMIF_GCLK                       (0x00000004u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_EMIF_GCLK_SHIFT                 (0x00000002u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_EMIF_GCLK_ACT                   (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_EMIF_GCLK_INACT                 (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK                         (0x00000010u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK_SHIFT                   (0x00000004u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK_ACT                     (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK_INACT                   (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MCASP_GCLK                      (0x00000080u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MCASP_GCLK_SHIFT                (0x00000007u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MCASP_GCLK_ACT                  (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MCASP_GCLK_INACT                (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MMC_FCLK                        (0x00000008u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MMC_FCLK_SHIFT                  (0x00000003u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MMC_FCLK_ACT                    (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKACTIVITY_MMC_FCLK_INACT                  (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL                                   (0x00000003u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SHIFT                             (0x00000000u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL_HW_AUTO                           (0x3u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                          (0x0u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                          (0x1u)
#define CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP                           (0x2u)

/* L3_INSTR_CLKCTRL */
#define CM_PER_L3_INSTR_CLKCTRL                                         (0xdc)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST                                  (0x00030000u)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST_SHIFT                            (0x00000010u)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST_DISABLE                          (0x3u)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST_FUNC                             (0x0u)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST_IDLE                             (0x2u)
#define CM_PER_L3_INSTR_CLKCTRL_IDLEST_TRANS                            (0x1u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE                              (0x00000003u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_SHIFT                        (0x00000000u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_DISABLED                     (0x0u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE                       (0x2u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED                     (0x3u)
#define CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED_1                   (0x1u)

/* L3_CLKCTRL */
#define CM_PER_L3_CLKCTRL                                               (0xe0)
#define CM_PER_L3_CLKCTRL_IDLEST                                        (0x00030000u)
#define CM_PER_L3_CLKCTRL_IDLEST_SHIFT                                  (0x00000010u)
#define CM_PER_L3_CLKCTRL_IDLEST_DISABLE                                (0x3u)
#define CM_PER_L3_CLKCTRL_IDLEST_FUNC                                   (0x0u)
#define CM_PER_L3_CLKCTRL_IDLEST_IDLE                                   (0x2u)
#define CM_PER_L3_CLKCTRL_IDLEST_TRANS                                  (0x1u)
#define CM_PER_L3_CLKCTRL_MODULEMODE                                    (0x00000003u)
#define CM_PER_L3_CLKCTRL_MODULEMODE_SHIFT                              (0x00000000u)
#define CM_PER_L3_CLKCTRL_MODULEMODE_DISABLED                           (0x0u)
#define CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE                             (0x2u)
#define CM_PER_L3_CLKCTRL_MODULEMODE_RESERVED                           (0x3u)
#define CM_PER_L3_CLKCTRL_MODULEMODE_RESERVED_1                         (0x1u)

/* OCPWP_L3_CLKSTCTRL */
#define CM_PER_OCPWP_L3_CLKSTCTRL                                       (0x12c)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK             (0x00000010u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK_SHIFT       (0x00000004u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK_ACT         (0x1u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK_INACT       (0x0u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK             (0x00000020u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK_SHIFT       (0x00000005u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK_ACT         (0x1u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK_INACT       (0x0u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL                             (0x00000003u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SHIFT                       (0x00000000u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_HW_AUTO                     (0x3u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                    (0x0u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                    (0x1u)
#define CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP                     (0x2u)

/* L4LS_CLKSTCTRL */
#define CM_PER_L4LS_CLKSTCTRL                                           (0x0)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_CAN_CLK                       (0x00000800u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_CAN_CLK_SHIFT                 (0x0000000Bu)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_CAN_CLK_ACT                   (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_CAN_CLK_INACT                 (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK                 (0x00080000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK_SHIFT           (0x00000013u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK_ACT             (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK_INACT           (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_2_GDBCLK                 (0x00100000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_2_GDBCLK_SHIFT           (0x00000014u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_2_GDBCLK_ACT             (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_2_GDBCLK_INACT           (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_3_GDBCLK                 (0x00200000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_3_GDBCLK_SHIFT           (0x00000015u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_3_GDBCLK_ACT             (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_GPIO_3_GDBCLK_INACT           (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK                      (0x01000000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK_SHIFT                (0x00000018u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK_ACT                  (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK_INACT                (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK                     (0x00000100u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK_SHIFT               (0x00000008u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK_ACT                 (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK_INACT               (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK                     (0x00020000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK_SHIFT               (0x00000011u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK_ACT                 (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK_INACT               (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_SPI_GCLK                      (0x02000000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_SPI_GCLK_SHIFT                (0x00000019u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_SPI_GCLK_ACT                  (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_SPI_GCLK_INACT                (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK                   (0x00004000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK_SHIFT             (0x0000000Eu)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK                   (0x00008000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK_SHIFT             (0x0000000Fu)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK                   (0x00010000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK_SHIFT             (0x00000010u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK                   (0x08000000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK_SHIFT             (0x0000001Bu)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK                   (0x10000000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK_SHIFT             (0x0000001Cu)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK                   (0x00002000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK_SHIFT             (0x0000000Du)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK_ACT               (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK_INACT             (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_UART_GFCLK                    (0x00000400u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_UART_GFCLK_SHIFT              (0x0000000Au)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_UART_GFCLK_ACT                (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_UART_GFCLK_INACT              (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL                                 (0x00000003u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SHIFT                           (0x00000000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_HW_AUTO                         (0x3u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                        (0x0u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                        (0x1u)
#define CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP                         (0x2u)

/* L4LS_CLKCTRL */
#define CM_PER_L4LS_CLKCTRL                                             (0x60)
#define CM_PER_L4LS_CLKCTRL_IDLEST                                      (0x00030000u)
#define CM_PER_L4LS_CLKCTRL_IDLEST_SHIFT                                (0x00000010u)
#define CM_PER_L4LS_CLKCTRL_IDLEST_DISABLE                              (0x3u)
#define CM_PER_L4LS_CLKCTRL_IDLEST_FUNC                                 (0x0u)
#define CM_PER_L4LS_CLKCTRL_IDLEST_IDLE                                 (0x2u)
#define CM_PER_L4LS_CLKCTRL_IDLEST_TRANS                                (0x1u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE                                  (0x00000003u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE_SHIFT                            (0x00000000u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE_DISABLED                         (0x0u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE                           (0x2u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE_RESERVED                         (0x3u)
#define CM_PER_L4LS_CLKCTRL_MODULEMODE_RESERVED_1                       (0x1u)

/* LCDC_CLKCTRL */
#define CM_PER_LCDC_CLKCTRL                                             (0x18)
#define CM_PER_LCDC_CLKCTRL_IDLEST                                      (0x00030000u)
#define CM_PER_LCDC_CLKCTRL_IDLEST_SHIFT                                (0x00000010u)
#define CM_PER_LCDC_CLKCTRL_IDLEST_DISABLE                              (0x3u)
#define CM_PER_LCDC_CLKCTRL_IDLEST_FUNC                                 (0x0u)
#define CM_PER_LCDC_CLKCTRL_IDLEST_IDLE                                 (0x2u)
#define CM_PER_LCDC_CLKCTRL_IDLEST_TRANS                                (0x1u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE                                  (0x00000003u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE_SHIFT                            (0x00000000u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE_DISABLED                         (0x0u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE                           (0x2u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE_RESERVED                         (0x3u)
#define CM_PER_LCDC_CLKCTRL_MODULEMODE_RESERVED_1                       (0x1u)
#define CM_PER_LCDC_CLKCTRL_STBYST                                      (0x00040000u)
#define CM_PER_LCDC_CLKCTRL_STBYST_SHIFT                                (0x00000012u)
#define CM_PER_LCDC_CLKCTRL_STBYST_FUNC                                 (0x0u)
#define CM_PER_LCDC_CLKCTRL_STBYST_STANDBY                              (0x1u)

/* CONF_GPMC_AD */
#define CONTROL_CONF_GPMC_AD(n)                                         (0x800 + (n * 4))

/* CONF_LCD_DATA0 */
#define CONTROL_CONF_LCD_DATA(n)                                        (0x8a0 + (n * 4))
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA1 */
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA2 */
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA3 */
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA4 */
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA5 */
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA6 */
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA7 */
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA8 */
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA9 */
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_DATA10 */
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA11 */
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA12 */
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA13 */
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA14 */
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA15 */
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA16 */
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA17 */
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA18 */
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA19 */
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA20 */
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA21 */
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA22 */
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_DATA23 */
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_MMODE                   (0x00000007u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_MMODE_SHIFT             (0x00000000u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUDEN                   (0x00000008u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUDEN_SHIFT             (0x00000003u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUTYPESEL               (0x00000010u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUTYPESEL_SHIFT         (0x00000004u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RSVD                    (0x000FFF80u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RSVD_SHIFT              (0x00000007u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RXACTIVE                (0x00000020u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RXACTIVE_SHIFT          (0x00000005u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_SLEWCTRL                (0x00000040u)
#define CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_SLEWCTRL_SHIFT          (0x00000006u)

/* CONF_LCD_VSYNC */
#define CONTROL_CONF_LCD_VSYNC                                          (0x8e0)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_HSYNC */
#define CONTROL_CONF_LCD_HSYNC                                          (0x8e4)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_MMODE                     (0x00000007u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_MMODE_SHIFT               (0x00000000u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUDEN                     (0x00000008u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUDEN_SHIFT               (0x00000003u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUTYPESEL                 (0x00000010u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUTYPESEL_SHIFT           (0x00000004u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RSVD                      (0x000FFF80u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RSVD_SHIFT                (0x00000007u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RXACTIVE                  (0x00000020u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RXACTIVE_SHIFT            (0x00000005u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_SLEWCTRL                  (0x00000040u)
#define CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_SLEWCTRL_SHIFT            (0x00000006u)

/* CONF_LCD_PCLK */
#define CONTROL_CONF_LCD_PCLK                                           (0x8e8)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_MMODE                       (0x00000007u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_MMODE_SHIFT                 (0x00000000u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUDEN                       (0x00000008u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUDEN_SHIFT                 (0x00000003u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUTYPESEL                   (0x00000010u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUTYPESEL_SHIFT             (0x00000004u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RSVD                        (0x000FFF80u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RSVD_SHIFT                  (0x00000007u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RXACTIVE                    (0x00000020u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RXACTIVE_SHIFT              (0x00000005u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_SLEWCTRL                    (0x00000040u)
#define CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_SLEWCTRL_SHIFT              (0x00000006u)

/* CONF_LCD_AC_BIAS_EN */
#define CONTROL_CONF_LCD_AC_BIAS_EN                                     (0x8ec)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_MMODE           (0x00000007u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_MMODE_SHIFT     (0x00000000u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUDEN           (0x00000008u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUDEN_SHIFT     (0x00000003u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUTYPESEL       (0x00000010u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUTYPESEL_SHIFT (0x00000004u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RSVD            (0x000FFF80u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RSVD_SHIFT      (0x00000007u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RXACTIVE        (0x00000020u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RXACTIVE_SHIFT  (0x00000005u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_SLEWCTRL        (0x00000040u)
#define CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_SLEWCTRL_SHIFT  (0x00000006u)

/* CLKC_ENABLE */
#define LCDC_CLKC_ENABLE                                                (0x6C)
#define LCDC_CLKC_ENABLE_CORE                                           (0x00000001u)
#define LCDC_CLKC_ENABLE_CORE_SHIFT                                     (0x00000000u)
#define LCDC_CLKC_ENABLE_CORE_DISABLE                                   (0x0u)
#define LCDC_CLKC_ENABLE_CORE_ENABLE                                    (0x1u)
#define LCDC_CLKC_ENABLE_DMA                                            (0x00000004u)
#define LCDC_CLKC_ENABLE_DMA_SHIFT                                      (0x00000002u)
#define LCDC_CLKC_ENABLE_DMA_DISABLE                                    (0x0u)
#define LCDC_CLKC_ENABLE_DMA_ENABLE                                     (0x1u)
#define LCDC_CLKC_ENABLE_LIDD                                           (0x00000002u)
#define LCDC_CLKC_ENABLE_LIDD_SHIFT                                     (0x00000001u)
#define LCDC_CLKC_ENABLE_LIDD_DISABLE                                   (0x0u)
#define LCDC_CLKC_ENABLE_LIDD_ENABLE                                    (0x1u)

/* LCD_CTRL */
#define LCDC_LCD_CTRL                                                   (0x4)
#define LCDC_LCD_CTRL_AUTO_UFLOW_RESTART                                (0x00000002u)
#define LCDC_LCD_CTRL_AUTO_UFLOW_RESTART_SHIFT                          (0x00000001u)
#define LCDC_LCD_CTRL_AUTO_UFLOW_RESTART_AUTO                           (0x1u)
#define LCDC_LCD_CTRL_AUTO_UFLOW_RESTART_MANUAL                         (0x0u)
#define LCDC_LCD_CTRL_CLKDIV                                            (0x0000FF00u)
#define LCDC_LCD_CTRL_CLKDIV_SHIFT                                      (0x00000008u)
#define LCDC_LCD_CTRL_MODESEL                                           (0x00000001u)
#define LCDC_LCD_CTRL_MODESEL_SHIFT                                     (0x00000000u)
#define LCDC_LCD_CTRL_MODESEL_LIDD                                      (0x0u)
#define LCDC_LCD_CTRL_MODESEL_RASTER                                    (0x1u)

/* RASTER_CTRL */
#define LCDC_RASTER_CTRL                                                (0x28)
#define LCDC_RASTER_CTRL_ACTVID_EN_VBLANK                               (0x08000000u)
#define LCDC_RASTER_CTRL_ACTVID_EN_VBLANK_SHIFT                         (0x0000001Bu)
#define LCDC_RASTER_CTRL_ACTVID_EN_VBLANK_NOACTVID                      (0x0u)
#define LCDC_RASTER_CTRL_ACTVID_EN_VBLANK_TOGGLEACTVID                  (0x1u)
#define LCDC_RASTER_CTRL_FIFO_DMA_DELAY                                 (0x000FF000u)
#define LCDC_RASTER_CTRL_FIFO_DMA_DELAY_SHIFT                           (0x0000000Cu)
#define LCDC_RASTER_CTRL_FIFO_DMA_DELAY_DISABLED                        (0x0u)
#define LCDC_RASTER_CTRL_MONO8B                                         (0x00000200u)
#define LCDC_RASTER_CTRL_MONO8B_SHIFT                                   (0x00000009u)
#define LCDC_RASTER_CTRL_MONO8B_4PIXEL                                  (0x0u)
#define LCDC_RASTER_CTRL_MONO8B_8PIXEL                                  (0x1u)
#define LCDC_RASTER_CTRL_MONO_COLOR                                     (0x00000002u)
#define LCDC_RASTER_CTRL_MONO_COLOR_SHIFT                               (0x00000001u)
#define LCDC_RASTER_CTRL_MONO_COLOR_COLOR                               (0x0u)
#define LCDC_RASTER_CTRL_MONO_COLOR_MONO                                (0x1u)
#define LCDC_RASTER_CTRL_NIB_MODE                                       (0x00400000u)
#define LCDC_RASTER_CTRL_NIB_MODE_SHIFT                                 (0x00000016u)
#define LCDC_RASTER_CTRL_NIB_MODE_DISABLED                              (0x0u)
#define LCDC_RASTER_CTRL_NIB_MODE_ENABLED                               (0x1u)
#define LCDC_RASTER_CTRL_PLM                                            (0x00300000u)
#define LCDC_RASTER_CTRL_PLM_SHIFT                                      (0x00000014u)
#define LCDC_RASTER_CTRL_PLM_DATA                                       (0x00000002u)
#define LCDC_RASTER_CTRL_PLM_PALETTE                                    (0x00000001u)
#define LCDC_RASTER_CTRL_PLM_PALETTE_DATA                               (0x00000000u)
#define LCDC_RASTER_CTRL_RASTER_EN                                      (0x00000001u)
#define LCDC_RASTER_CTRL_RASTER_EN_SHIFT                                (0x00000000u)
#define LCDC_RASTER_CTRL_RASTER_EN_DISABLED                             (0x0u)
#define LCDC_RASTER_CTRL_RASTER_EN_ENABLED                              (0x1u)
#define LCDC_RASTER_CTRL_RD_ORDER                                       (0x00000100u)
#define LCDC_RASTER_CTRL_RD_ORDER_SHIFT                                 (0x00000008u)
#define LCDC_RASTER_CTRL_RD_ORDER_H2L                                   (0x1u)
#define LCDC_RASTER_CTRL_RD_ORDER_L2H                                   (0x0u)
#define LCDC_RASTER_CTRL_STN_565                                        (0x01000000u)
#define LCDC_RASTER_CTRL_STN_565_SHIFT                                  (0x00000018u)
#define LCDC_RASTER_CTRL_STN_565_12BPP                                  (0x0u)
#define LCDC_RASTER_CTRL_STN_565_16BPP                                  (0x1u)
#define LCDC_RASTER_CTRL_TFT24                                          (0x02000000u)
#define LCDC_RASTER_CTRL_TFT24_SHIFT                                    (0x00000019u)
#define LCDC_RASTER_CTRL_TFT24_OFF                                      (0x0u)
#define LCDC_RASTER_CTRL_TFT24_ON                                       (0x1u)
#define LCDC_RASTER_CTRL_TFT24UNPACKED                                  (0x04000000u)
#define LCDC_RASTER_CTRL_TFT24UNPACKED_SHIFT                            (0x0000001Au)
#define LCDC_RASTER_CTRL_TFT24UNPACKED_PACKED                           (0x0u)
#define LCDC_RASTER_CTRL_TFT24UNPACKED_UNPACKED                         (0x1u)
#define LCDC_RASTER_CTRL_TFT_ALT_MAP                                    (0x00800000u)
#define LCDC_RASTER_CTRL_TFT_ALT_MAP_SHIFT                              (0x00000017u)
#define LCDC_RASTER_CTRL_TFT_ALT_MAP_565                                (0x1u)
#define LCDC_RASTER_CTRL_TFT_ALT_MAP_ALIGN                              (0x0u)
#define LCDC_RASTER_CTRL_TFT_STN                                        (0x00000080u)
#define LCDC_RASTER_CTRL_TFT_STN_SHIFT                                  (0x00000007u)
#define LCDC_RASTER_CTRL_TFT_STN_STN                                    (0x0u)
#define LCDC_RASTER_CTRL_TFT_STN_TFT                                    (0x1u)
#define LCDC_RASTER_CTRL_FUF_EN                                         (0x00000040u)
#define LCDC_RASTER_CTRL_FUF_EN_SHIFT                                   (0x00000006u)
#define LCDC_RASTER_CTRL_SL_EN                                          (0x00000020u)
#define LCDC_RASTER_CTRL_SL_EN_SHIFT                                    (0x00000005u)
#define LCDC_RASTER_CTRL_PL_EN                                          (0x00000010u)
#define LCDC_RASTER_CTRL_PL_EN_SHIFT                                    (0x00000004u)
#define LCDC_RASTER_CTRL_DONE_EN                                        (0x00000008u)
#define LCDC_RASTER_CTRL_DONE_EN_SHIFT                                  (0x00000003u)
#define LCDC_RASTER_CTRL_AC_EN                                          (0x00000004u)
#define LCDC_RASTER_CTRL_AC_EN_SHIFT                                    (0x00000002u)

/* LCDDMA_CTRL */
#define LCDC_LCDDMA_CTRL                                                (0x40)
#define LCDC_LCDDMA_CTRL_BIGENDIAN                                      (0x00000002u)
#define LCDC_LCDDMA_CTRL_BIGENDIAN_SHIFT                                (0x00000001u)
#define LCDC_LCDDMA_CTRL_EOF_INTEN                                      (0x00000004)
#define LCDC_LCDDMA_CTRL_EOF_INTEN_SHIFT                                (0x00000002u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE                                     (0x00000070u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT                               (0x00000004u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_EIGHT                               (0x00000003u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_FOUR                                (0x00000002u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_ONE                                 (0x00000000u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_SIXTEEN                             (0x00000004u)
#define LCDC_LCDDMA_CTRL_BURST_SIZE_TWO                                 (0x00000001u)
#define LCDC_LCDDMA_CTRL_BYTE_SWAP                                      (0x00000008u)
#define LCDC_LCDDMA_CTRL_BYTE_SWAP_SHIFT                                (0x00000003u)
#define LCDC_LCDDMA_CTRL_DMA_MASTER_PRIO                                (0x00070000u)
#define LCDC_LCDDMA_CTRL_DMA_MASTER_PRIO_SHIFT                          (0x00000010u)
#define LCDC_LCDDMA_CTRL_FRAME_MODE                                     (0x00000001u)
#define LCDC_LCDDMA_CTRL_FRAME_MODE_SHIFT                               (0x00000000u)
#define LCDC_LCDDMA_CTRL_FRAME_MODE_ONE                                 (0x0u)
#define LCDC_LCDDMA_CTRL_FRAME_MODE_TWO                                 (0x1u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY                                  (0x00000700u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT                            (0x00000008u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_EIGHT                            (0x00000000u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_FIVE_TWELVE                      (0x00000006u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_ONE_TWENTY_EIGHT                 (0x00000004u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_SIXTEEN                          (0x00000001u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_SIXTY_FOUR                       (0x00000003u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_THIRTY_TWO                       (0x00000002u)
#define LCDC_LCDDMA_CTRL_TH_FIFO_READY_TWO_FIFTY_SIX                    (0x00000005u)

/* RASTER_TIMING_0 */
#define LCDC_RASTER_TIMING_0                                            (0x2C)
#define LCDC_RASTER_TIMING_0_HBP                                        (0xFF000000u)
#define LCDC_RASTER_TIMING_0_HBP_SHIFT                                  (0x00000018u)
#define LCDC_RASTER_TIMING_0_HFP                                        (0x00FF0000u)
#define LCDC_RASTER_TIMING_0_HFP_SHIFT                                  (0x00000010u)
#define LCDC_RASTER_TIMING_0_HSW                                        (0x0000FC00u)
#define LCDC_RASTER_TIMING_0_HSW_SHIFT                                  (0x0000000Au)
#define LCDC_RASTER_TIMING_0_PPL                                        (0x000003F0u)
#define LCDC_RASTER_TIMING_0_PPL_SHIFT                                  (0x00000004u)
#define LCDC_RASTER_TIMING_0_PPLMSB                                     (0x00000008u)
#define LCDC_RASTER_TIMING_0_PPLMSB_SHIFT                               (0x00000003u)

/* RASTER_TIMING_1 */
#define LCDC_RASTER_TIMING_1                                            (0x30)
#define LCDC_RASTER_TIMING_1_LPP                                        (0x000003FFu)
#define LCDC_RASTER_TIMING_1_LPP_SHIFT                                  (0x00000000u)
#define LCDC_RASTER_TIMING_1_VBP                                        (0xFF000000u)
#define LCDC_RASTER_TIMING_1_VBP_SHIFT                                  (0x00000018u)
#define LCDC_RASTER_TIMING_1_VFP                                        (0x00FF0000u)
#define LCDC_RASTER_TIMING_1_VFP_SHIFT                                  (0x00000010u)
#define LCDC_RASTER_TIMING_1_VSW                                        (0x0000FC00u)
#define LCDC_RASTER_TIMING_1_VSW_SHIFT                                  (0x0000000Au)

/* RASTER_TIMING_2 */
#define LCDC_RASTER_TIMING_2                                            (0x34)
#define LCDC_RASTER_TIMING_2_ACB                                        (0x0000FF00u)
#define LCDC_RASTER_TIMING_2_ACB_SHIFT                                  (0x00000008u)
#define LCDC_RASTER_TIMING_2_ACB_I                                      (0x000F0000u)
#define LCDC_RASTER_TIMING_2_ACB_I_SHIFT                                (0x00000010u)
#define LCDC_RASTER_TIMING_2_BIAS                                       (0x00800000u)
#define LCDC_RASTER_TIMING_2_BIAS_SHIFT                                 (0x00000017u)
#define LCDC_RASTER_TIMING_2_BIAS_ACTIVE_HIGH                           (0x0u)
#define LCDC_RASTER_TIMING_2_BIAS_ACTIVE_LOW                            (0x1u)
#define LCDC_RASTER_TIMING_2_HBP_HIGHBITS                               (0x00000030u)
#define LCDC_RASTER_TIMING_2_HBP_HIGHBITS_SHIFT                         (0x00000006u)
#define LCDC_RASTER_TIMING_2_HFP_HIGHBITS                               (0x00000003u)
#define LCDC_RASTER_TIMING_2_HFP_HIGHBITS_SHIFT                         (0x00000000u)
#define LCDC_RASTER_TIMING_2_IEO                                        (0x00800000u)
#define LCDC_RASTER_TIMING_2_IEO_SHIFT                                  (0x00000017u)
#define LCDC_RASTER_TIMING_2_IEO_ACTIVE_HIGH                            (0x0u)
#define LCDC_RASTER_TIMING_2_IEO_ACTIVE_LOW                             (0x1u)
#define LCDC_RASTER_TIMING_2_IHS                                        (0x00200000u)
#define LCDC_RASTER_TIMING_2_IHS_SHIFT                                  (0x00000015u)
#define LCDC_RASTER_TIMING_2_IHS_ACTIVE_HIGH                            (0x0u)
#define LCDC_RASTER_TIMING_2_IHS_ACTIVE_LOW                             (0x1u)
#define LCDC_RASTER_TIMING_2_IPC                                        (0x00400000u)
#define LCDC_RASTER_TIMING_2_IPC_SHIFT                                  (0x00000016u)
#define LCDC_RASTER_TIMING_2_IPC_FALLING                                (0x1u)
#define LCDC_RASTER_TIMING_2_IPC_RISING                                 (0x0u)
#define LCDC_RASTER_TIMING_2_IVS                                        (0x00100000u)
#define LCDC_RASTER_TIMING_2_IVS_SHIFT                                  (0x00000014u)
#define LCDC_RASTER_TIMING_2_IVS_ACTIVE_HIGH                            (0x0u)
#define LCDC_RASTER_TIMING_2_IVS_ACTIVE_LOW                             (0x1u)
#define LCDC_RASTER_TIMING_2_LPP_B10                                    (0x04000000u)
#define LCDC_RASTER_TIMING_2_LPP_B10_SHIFT                              (0x0000001Au)
#define LCDC_RASTER_TIMING_2_PHSVS_ON_OFF                               (0x02000000u)
#define LCDC_RASTER_TIMING_2_PHSVS_ON_OFF_SHIFT                         (0x00000019u)
#define LCDC_RASTER_TIMING_2_PHSVS_ON_OFF_BIT24                         (0x1u)
#define LCDC_RASTER_TIMING_2_PHSVS_ON_OFF_OPPOSITE_EDGE                 (0x0u)
#define LCDC_RASTER_TIMING_2_PHSVS_RF                                   (0x01000000u)
#define LCDC_RASTER_TIMING_2_PHSVS_RF_SHIFT                             (0x00000018u)
#define LCDC_RASTER_TIMING_2_PHSVS_RF_FALLING                           (0x0u)
#define LCDC_RASTER_TIMING_2_PHSVS_RF_RISING                            (0x1u)
#define LCDC_RASTER_TIMING_2_SYNC_CTRL                                  (0x02000000u)
#define LCDC_RASTER_TIMING_2_SYNC_CTRL_SHIFT                            (0x00000019u)
#define LCDC_RASTER_TIMING_2_SYNC_CTRL_BIT24                            (0x1u)
#define LCDC_RASTER_TIMING_2_SYNC_CTRL_OPPOSITE_EDGE                    (0x0u)
#define LCDC_RASTER_TIMING_2_SYNC_EDGE                                  (0x01000000u)
#define LCDC_RASTER_TIMING_2_SYNC_EDGE_SHIFT                            (0x00000018u)
#define LCDC_RASTER_TIMING_2_SYNC_EDGE_FALLING                          (0x0u)
#define LCDC_RASTER_TIMING_2_SYNC_EDGE_RISING                           (0x1u)

/* LCDDMA_FB0_BASE */
#define LCDC_LCDDMA_FB0_BASE                                            (0x44)
#define LCDC_LCDDMA_FB0_BASE_FB0_BASE                                   (0xFFFFFFFCu)
#define LCDC_LCDDMA_FB0_BASE_FB0_BASE_SHIFT                             (0x00000002u)

/* LCDDMA_FB0_CEILING */
#define LCDC_LCDDMA_FB0_CEILING                                         (0x48)
#define LCDC_LCDDMA_FB0_CEILING_FB0_CEIL                                (0xFFFFFFFCu)
#define LCDC_LCDDMA_FB0_CEILING_FB0_CEIL_SHIFT                          (0x00000002u)

/* LCDDMA_FB1_BASE */
#define LCDC_LCDDMA_FB1_BASE                                            (0x4C)
#define LCDC_LCDDMA_FB1_BASE_FB1_BASE                                   (0xFFFFFFFCu)
#define LCDC_LCDDMA_FB1_BASE_FB1_BASE_SHIFT                             (0x00000002u)

/* LCDDMA_FB1_CEILING */
#define LCDC_LCDDMA_FB1_CEILING                                         (0x50)
#define LCDC_LCDDMA_FB1_CEILING_FB1_CEIL                                (0xFFFFFFFCu)
#define LCDC_LCDDMA_FB1_CEILING_FB1_CEIL_SHIFT                          (0x00000002u)

#define LCDC_IRQENABLE_SET                                              (0x60)
#define LCDC_IRQENABLE_SET_EOF0                                         (0x00000100u)
#define LCDC_IRQENABLE_SET_EOF1                                         (0x00000200u)

#define LCDC_IRQSTATUS                                                  (0x5C)
#define LCDC_IRQSTATUS_EOF0                                             (0x00000100u)
#define LCDC_IRQSTATUS_EOF1                                             (0x00000200u)

#define SOC_PRCM_REGS                                                   (0x44E00000)
#define SOC_CM_DPLL_REGS                                                (SOC_PRCM_REGS + 0x500)
#define SOC_CONTROL_REGS                                                (0x44E10000)
#define SOC_LCDC_0_REGS                                                 (0x4830E000)

// RasterModeConfig, displayType
#define RASTER_DISPLAY_MODE_TFT                                         (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)
#define RASTER_DISPLAY_MODE_STN                                         0
#define RASTER_DISPLAY_MODE_TFT_PACKED                                  (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)|\
                                                                        (1 << LCDC_RASTER_CTRL_TFT24_SHIFT)
#define RASTER_DISPLAY_MODE_TFT_UNPACKED                                (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)|\
                                                                        (1 << LCDC_RASTER_CTRL_TFT24_SHIFT) |\
                                                                        (1 << LCDC_RASTER_CTRL_TFT24UNPACKED_SHIFT)

// RasterModeConfig, paletteMode
#define RASTER_PALETTE_DATA                                               0
#define RASTER_PALETTE                                                  (1 << LCDC_RASTER_CTRL_PLM_SHIFT)
#define RASTER_DATA                                                     (2 << LCDC_RASTER_CTRL_PLM_SHIFT)

// RasterModeConfig, displayMode
#define RASTER_COLOR                                                    0
#define RASTER_MONOCHROME                                               (1 << LCDC_RASTER_CTRL_MONO_COLOR_SHIFT)

// RasterModeConfig, signal mappping
#define RASTER_RIGHT_ALIGNED                                            0
#define RASTER_EXTRAPOLATE                                              (1 << LCDC_RASTER_CTRL_TFT_ALT_MAP_SHIFT)

// RasterModeConfig, number of bits for each pixel clock
#define RASTER_MONO8B                                                   (1 << LCDC_RASTER_CTRL_MONO8B_SHIFT)
#define RASTER_MONO4B                                                   0

// RasterDMAConfig, single frame buffer or double frame buffer
#define RASTER_SINGLE_FRAME_BUFFER                                      0
#define RASTER_DOUBLE_FRAME_BUFFER                                      LCDC_LCDDMA_CTRL_FRAME_MODE

// RasterDMAConfig, endianess
#define RASTER_BIG_ENDIAN_ENABLE                                        (1 << LCDC_LCDDMA_CTRL_BIGENDIAN_SHIFT)
#define RASTER_BIG_ENDIAN_DISABLE                                       0

// RasterDMAConfig, burst size
#define RASTER_BURST_SIZE_1                                             0
#define RASTER_BURST_SIZE_2                                             (1 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)
#define RASTER_BURST_SIZE_4                                             (2 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)
#define RASTER_BURST_SIZE_8                                             (3 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)
#define RASTER_BURST_SIZE_16                                            (4 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)

// RasterDMAConfig, DMA fifo threshold
#define RASTER_FIFO_THRESHOLD_8                                         (0 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_16                                        (1 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_32                                        (2 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_64                                        (3 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_128                                       (4 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_256                                       (5 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_512                                       (6 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)

// RasterTiming2Configure
#define RASTER_FRAME_CLOCK_HIGH                                         0
#define RASTER_FRAME_CLOCK_LOW                                          LCDC_RASTER_TIMING_2_IVS
#define RASTER_LINE_CLOCK_HIGH                                          0
#define RASTER_LINE_CLOCK_LOW                                           LCDC_RASTER_TIMING_2_IHS
#define RASTER_PIXEL_CLOCK_HIGH                                         0
#define RASTER_PIXEL_CLOCK_LOW                                          LCDC_RASTER_TIMING_2_IPC
#define RASTER_AC_BIAS_HIGH                                             0
#define RASTER_AC_BIAS_LOW                                              LCDC_RASTER_TIMING_2_BIAS
#define RASTER_SYNC_EDGE_RISING                                         0
#define RASTER_SYNC_EDGE_FALLING                                        LCDC_RASTER_TIMING_2_SYNC_EDGE
#define RASTER_SYNC_CTRL_ACTIVE                                         LCDC_RASTER_TIMING_2_SYNC_CTRL
#define RASTER_SYNC_CTRL_INACTIVE                                       0

// RasterIntEnable
#define RASTER_ACBIAS_COUNT_INT                                         LCDC_IRQENABLE_SET_ACB
#define RASTER_FRAME_DONE_INT                                           LCDC_IRQENABLE_SET_DONE
#define RASTER_PALETTE_LOADED_INT                                       LCDC_IRQENABLE_SET_PL
#define RASTER_SYNC_LOST_INT                                            LCDC_IRQENABLE_SET_SYNC
#define RASTER_FIFO_UNDRFLOW_INT                                        LCDC_IRQENABLE_SET_FUF
#define RASTER_DONE_INT                                                 LCDC_IRQENABLE_SET_RECURRENT_RASTER
#define RASTER_END_OF_FRAME0_INT                                        LCDC_IRQENABLE_SET_EOF0
#define RASTER_END_OF_FRAME1_INT                                        LCDC_IRQENABLE_SET_EOF1

// RasterIntSatus
#define RASTER_FRAME_DONE_INT_STAT                                      LCDC_IRQSTATUS_DONE
#define RASTER_SYNC_LOST_INT_STAT                                       LCDC_IRQSTATUS_SYNC
#define RASTER_ACBIAS_COUNT_INT_STAT                                    LCDC_IRQSTATUS_ACB
#define RASTER_FIFO_UNDERFLOW_INT_STAT                                  LCDC_IRQSTATUS_FUF
#define RASTER_PALETTE_LOADED_INT_STAT                                  LCDC_IRQSTATUS_PL
#define RASTER_END_OF_FRAME0_INT_STAT                                   LCDC_IRQSTATUS_EOF0
#define RASTER_END_OF_FRAME1_INT_STAT                                   LCDC_IRQSTATUS_EOF1

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _PendingBuffer;

_Pragma("location=\"VRAM\"")

static unsigned long _aVRAM[XSIZE_PHYS * YSIZE_PHYS * NUM_VSCREENS * NUM_BUFFERS];

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _LCDModuleClkConfig
*/
static void _LCDModuleClkConfig(void) {
  HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL)      |= CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKTRCTRL)
                                                   != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
  HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL)       |= CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKTRCTRL)
                                                   != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
  HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL)   |= CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) & CM_PER_L3_INSTR_CLKCTRL_MODULEMODE)
                                                   != CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);
  HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL)         |= CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) & CM_PER_L3_CLKCTRL_MODULEMODE)
                                                   != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);
  HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |= CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
  while((HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL)
                                                   != CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
  HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL)     |= CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL)
                                                   != CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
  HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL)       |= CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;
  while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) & CM_PER_L4LS_CLKCTRL_MODULEMODE)
                                                   != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);
  //
  // lcd pixel clock is derived from peripheral pll
  //
  HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_LCDC_PIXEL_CLK) = CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL3;
  HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) |= CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE;
  while( (HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) & CM_PER_LCDC_CLKCTRL_MODULEMODE) != CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE);
  while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));
  while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));
  while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK | CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));
  while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK | CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK)));
}


/*********************************************************************
*
*       _LCDPinMuxSetup
*/
static void _LCDPinMuxSetup(void) {
  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(0)) =    (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA0_CONF_LCD_DATA0_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(1)) =    (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA1_CONF_LCD_DATA1_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(2)) =    (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA2_CONF_LCD_DATA2_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(3)) =    (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA3_CONF_LCD_DATA3_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(4)) =    (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA4_CONF_LCD_DATA4_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(5)) =    (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA5_CONF_LCD_DATA5_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(6)) =    (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA6_CONF_LCD_DATA6_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(7)) =    (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA7_CONF_LCD_DATA7_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(8)) =    (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA8_CONF_LCD_DATA8_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(9)) =    (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA9_CONF_LCD_DATA9_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(10)) =   (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_MMODE_SHIFT)    |
                                                          (1 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUDEN_SHIFT)    |
                                                          (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_PUTYPESEL_SHIFT)|
                                                          (1 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_RXACTIVE_SHIFT) |
                                                          (0 << CONTROL_CONF_LCD_DATA10_CONF_LCD_DATA10_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(11)) =   (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_MMODE_SHIFT)     |
                                                          (1 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA11_CONF_LCD_DATA11_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(12)) =   (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_MMODE_SHIFT)     |
                                                          (1 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA12_CONF_LCD_DATA12_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(13)) =   (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_MMODE_SHIFT)     |
                                                          (1 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA13_CONF_LCD_DATA13_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(14)) =   (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_MMODE_SHIFT)     |
                                                          (1 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA14_CONF_LCD_DATA14_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(15)) =   (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_MMODE_SHIFT)     |
                                                          (1 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA15_CONF_LCD_DATA15_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(15) ) =   (1 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA16_CONF_LCD_DATA16_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(14) ) =   (1 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_PUTYPESEL_SHIFT) |
                                                          (1<< CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_RXACTIVE_SHIFT)   |
                                                          (0 << CONTROL_CONF_LCD_DATA17_CONF_LCD_DATA17_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(13) ) =   (1 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA18_CONF_LCD_DATA18_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(12) ) =   (1 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_PUTYPESEL_SHIFT) |
                                                          (1<< CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_RXACTIVE_SHIFT)   |
                                                          (0 << CONTROL_CONF_LCD_DATA19_CONF_LCD_DATA19_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(11) ) =   (1 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_PUTYPESEL_SHIFT) |
                                                          (1<< CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_RXACTIVE_SHIFT)   |
                                                          (0 << CONTROL_CONF_LCD_DATA20_CONF_LCD_DATA20_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(10) ) =   (1 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA21_CONF_LCD_DATA21_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(9) ) =    (1 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA22_CONF_LCD_DATA22_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(8) ) =    (1 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_DATA23_CONF_LCD_DATA23_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_VSYNC) =      (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_VSYNC_CONF_LCD_VSYNC_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_HSYNC) =      (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_HSYNC_CONF_LCD_HSYNC_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_PCLK) =       (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_PCLK_CONF_LCD_PCLK_SLEWCTRL_SHIFT);

  HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_AC_BIAS_EN) = (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_MMODE_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUDEN_SHIFT)     |
                                                          (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_PUTYPESEL_SHIFT) |
                                                          (1 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_RXACTIVE_SHIFT)  |
                                                          (0 << CONTROL_CONF_LCD_AC_BIAS_EN_CONF_LCD_AC_BIAS_EN_SLEWCTRL_SHIFT);
}

/*********************************************************************
*
*       _RasterClocksEnable
*/
static void _RasterClocksEnable(unsigned int baseAddr) {
  HWREG(baseAddr + LCDC_CLKC_ENABLE) = ( LCDC_CLKC_ENABLE_CORE | LCDC_CLKC_ENABLE_DMA  | LCDC_CLKC_ENABLE_LIDD );
}

/*********************************************************************
*
*       _RasterClkConfig
*
* Purpose:
*   This function configures clkdiv to generate required frequency of
*   of pixel clock and selects the raster control.
*
* Parameters:
*   baseAddr -  Memory address of LCD
*   pClk     -  Required Pixel Clock frequency
*   modulck  -  Input clk to LCD module from PLL
*
*/
static void _RasterClkConfig(unsigned int baseAddr, unsigned int pClk, unsigned int moduleClk) {
    unsigned int clkDiv;

    clkDiv = moduleClk / pClk ;
    HWREG(baseAddr + LCDC_LCD_CTRL) = LCDC_LCD_CTRL_MODESEL;
    HWREG(baseAddr + LCDC_LCD_CTRL) |= (clkDiv <<  LCDC_LCD_CTRL_CLKDIV_SHIFT);
}

/*********************************************************************
*
*       _RasterDMAConfig
*
* Purpose:
*   Configures DMA present inside LCD controller.
*
* Parameters:
*   baseAddr - Memory address of LCD module.
*
*   frmMode  - Value which detemines either to use single frame
*              or double frame buffer
*
*              RASTER_SINGLE_FRAME_BUFFER - single frame buffer
*              RASTER_DOUBLE_FRAME_BUFFER - double frame buffer
*
*   bustSz   - Value which detemines burst size of DMA
*
*              RASTER_BURST_SIZE_1   -  burst size of DMA is one
*              RASTER_BURST_SIZE_2   -  burst size of DMA is two
*              RASTER_BURST_SIZE_4   -  burst size of DMA is four
*              RASTER_BURST_SIZE_16  -  burst size of DMA is sixteen
*
*   fifoTh   - Value which detemines when the input FIFO can be
*              read by raster controller
*
*              RASTER_FIFO_THRESHOLD_8    -   DMA FIFO Threshold is eight
*              RASTER_FIFO_THRESHOLD_16   -   DMA FIFO Threshold is sixteen
*              RASTER_FIFO_THRESHOLD_32   -   DMA FIFO Threshold is thirtytwo
*              RASTER_FIFO_THRESHOLD_64   -   DMA FIFO Threshold is sixtyfour
*              RASTER_FIFO_THRESHOLD_128  -   DMA FIFO Threshold is one twenty eight
*              RASTER_FIFO_THRESHOLD_256  -   DMA FIFO Threshold is two fifty six
*              RASTER_FIFO_THRESHOLD_512  -   DMA FIFO Threshold is five twelve
*
*   endian   - Value determines whether to use big endian for data
*              reordering or not
*
*              RASTER_BIG_ENDIAN_ENABLE - big endian enabled
*              RASTER_BIG_ENDIAN_ENABLE - big endian disabled
*/
static void _RasterDMAConfig(unsigned int baseAddr, unsigned int frmMode,  unsigned int bustSz, unsigned int fifoTh, unsigned int endian) {
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) = frmMode | bustSz | fifoTh | endian;
}

/*********************************************************************
*
*       _RasterModeConfig
* Purpose:
*   This function will configures LCD to MonoChrome or color mode,
*   TFT or STN mode and palette loading mode.
*
* Parameters:
*   baseAddr    - Memory address of the LCD
*   displayMode - Value to select either TFT or STN mode
*
*                 RASTER_DISPLAY_MODE_TFT  -  TFT mode is selected
*                 RASTER_DISPLAY_MODE_STN  -  STN mode is selected
*                 RASTER_DISPLAY_MODE_TFT_PACKED   - TFT mode is selected with
*                                                     24 bit packed data support.
*                 RASTER_DISPLAY_MODE_TFT_UNPACKED - TFT mode is selected with
*                                                    24 bit unpacked data support
*
*   displayType - Value to select either color or monochrome mode
*
*                 RASTER_MONOCHROME  - monochrome mode is selected
*                 RASTER_COLOR       - color mode is selected
*
*   paletteMode - Value to select type of palette loading
*
*                 RASTER_PALETTE_DATA   - palette and data is loaded
*                 RASTER_PALETTE        - only palette is loaded
*                 RASTER_DATA           - only data is loaded
*
*   flag        - Optional argument depending on the display mode and type
*
*                 RASTER_RIGHT_ALIGNED - Right aligned output pixel data
*                 RASTER_EXTRAPOLATE   - Extrapolated (to RGB565) output pixel data
*                 RASTER_MONO8B        - Output 8 bit mono pixel data
*                 RASTER_MONO4B        - Output 4 bit mono pixel data
*/
static void _RasterModeConfig(unsigned int baseAddr, unsigned int displayMode, unsigned int paletteMode, unsigned int displayType, unsigned flag) {
  //
  // Configures raster to TFT or STN Mode
  //
  HWREG(baseAddr + LCDC_RASTER_CTRL) = displayMode | paletteMode | displayType;
  if(displayMode ==  RASTER_DISPLAY_MODE_TFT) {
    if(flag == RASTER_RIGHT_ALIGNED) {
      //
      // Output pixel data for 1, 2, 4 and 8 bpp is converted to 565 format
      //
      HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~(LCDC_RASTER_CTRL_TFT_ALT_MAP);
    } else {
      //
      // Output pixel data for 1, 2, 4 and 8 bpp will be right aligned
      //
      HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_TFT_ALT_MAP;
    }
  } else {
    if(flag ==  RASTER_MONO8B) {
      HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_MONO8B;
    } else {
      HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_MONO8B;
    }
  }
}

/*********************************************************************
*
*       _RasterTiming2Configure
*
* Purpose:
*   Configures the polartiy of various timing parameters of LCD Controller
*
* Parameters:
*   baseAddr - Memory Address of the LCD Module.
*
*   flag     - Value which detemines polarity of various timing
*              parameter of LCD controller
*
*              RASTER_FRAME_CLOCK_HIGH - active high frame clock
*              RASTER_FRAME_CLOCK_LOW  - active low frame clock
*              RASTER_LINE_CLOCK_HIGH  - active high line clock
*              RASTER_LINE_CLOCK_LOW   - active low line clock
*              RASTER_PIXEL_CLOCK_HIGH - active high pixel clock
*              RASTER_PIXEL_CLOCK_LOW  - active low pixel clock
*              RASTER_AC_BIAS_HIGH     - active high ac bias
*              RASTER_AC_BIAS_LOW      - active low ac bias
*              RASTER_SYNC_EDGE_RISING - rising sync edge
*              RASTER_SYNC_EDGE_FALLING- falling sync edge
*              RASTER_SYNC_CTRL_ACTIVE - active sync control
*              RASTER_SYNC_CTRL_INACTIVE-inactive sync control
*
*   acb_i    - Value which specify the number of AC Bias
*              (LCD_AC_ENB_CS) output transition counts before
*              setting the AC bias interrupt bit in register LCD_STAT
*
*   acb      - Value which defines the number of Line Clock
*              (LCD_HSYNC) cycles to count before transitioning
*              signal LCD_AC_ENB_CS
*/
static void _RasterTiming2Configure(unsigned int baseAddr, unsigned int flag, unsigned int acb_i, unsigned int acb) {
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= flag;
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb_i << LCDC_RASTER_TIMING_2_ACB_I_SHIFT);
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb   << LCDC_RASTER_TIMING_2_ACB_SHIFT);
}

/*********************************************************************
*
*       _RasterHparamConfig
*
* Purpose:
*   Configuers horizontal timing parametes and number of pixel per line
*
* Parameters:
*   baseAddr - Memory address of the LCD module
*   numOfppl - Value which determine no of pixel required per line
*   hsw      - Value which detemines the width of HSYNC
*   hfp      - Horizontal front porch
*   hbp      - Horizontal back porch
*/
static void _RasterHparamConfig(unsigned int baseAddr, unsigned int numOfppl, unsigned int hsw, unsigned int hfp, unsigned hbp) {
  unsigned int ppl;

  ppl = numOfppl - 1;
  ppl = (ppl & 0x000003f0) | ((ppl & 0x00000400) >> 7);
  HWREG(baseAddr + LCDC_RASTER_TIMING_0) = ppl;
  HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= (hsw - 1) << LCDC_RASTER_TIMING_0_HSW_SHIFT;
  HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= (hfp - 1) << LCDC_RASTER_TIMING_0_HFP_SHIFT;
  HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= (hbp - 1) << LCDC_RASTER_TIMING_0_HBP_SHIFT;
}

/*********************************************************************
*
*       _RasterVparamConfig
*
* Purpose:
*   Configuers vertical timing parameters and number of lines per panel
*
* Parameters:
*   baseAddr - Memory address of the LCD module
*   lpp      - Value which determine the lines per panel
*   vsw      - Value which detemines the width of VSYNC
*   vfp      - Vertical front porch
*   vbp      - Vertical back porch
*/
static void _RasterVparamConfig(unsigned int baseAddr, unsigned int lpp, unsigned int vsw, unsigned int vfp, unsigned vbp) {
  HWREG(baseAddr + LCDC_RASTER_TIMING_1) = (lpp - 1) & 0x3ff;
  HWREG(baseAddr + LCDC_RASTER_TIMING_2) &= 0xfbffffff;
  HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (((lpp - 1) & 0x400) >> 10) << LCDC_RASTER_TIMING_2_LPP_B10_SHIFT;
  HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vsw - 1)                   << LCDC_RASTER_TIMING_1_VSW_SHIFT;
  HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= vfp                         << LCDC_RASTER_TIMING_1_VFP_SHIFT;
  HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= vbp                         << LCDC_RASTER_TIMING_1_VBP_SHIFT;
}

/*********************************************************************
*
*       _RasterFIFODMADelayConfig
*/
static void _RasterFIFODMADelayConfig(unsigned int baseAddr, unsigned int delay) {
  HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_FIFO_DMA_DELAY;
  HWREG(baseAddr + LCDC_RASTER_CTRL) |= delay << LCDC_RASTER_CTRL_FIFO_DMA_DELAY_SHIFT;
}

/*********************************************************************
*
*       _RasterDMAFBConfig
*/
static void _RasterDMAFBConfig(unsigned int baseAddr, unsigned int base, unsigned int ceiling, unsigned int flag) {
  if(flag == 0) {
    HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE)    = base - 0x20;
    HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING) = ceiling;
  } else {
    HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE)    = base - 0x20;
    HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING) = ceiling;
  }
}

/*********************************************************************
*
*       _RasterIntEnable
*/
static void _RasterIntEnable(unsigned int baseAddr) {
  HWREG(baseAddr + LCDC_IRQENABLE_SET) |= RASTER_END_OF_FRAME0_INT;
}

/*********************************************************************
*
*       _RasterEnable
*/
static void _RasterEnable(unsigned int baseAddr) {
  HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RASTER_EN;
}

/*********************************************************************
*
*       _LCD_ISR_EndOfFrame
*/
static void _LCD_ISR_EndOfFrame(void) {
  U32 Addr;
  unsigned Status;

  Status = HWREG(SOC_LCDC_0_REGS + LCDC_IRQSTATUS) & (RASTER_END_OF_FRAME0_INT_STAT | RASTER_END_OF_FRAME1_INT_STAT);
  Status = HWREG(SOC_LCDC_0_REGS + LCDC_IRQSTATUS) & Status;
  HWREG(SOC_LCDC_0_REGS + LCDC_IRQSTATUS) = Status;
  if (_PendingBuffer >= 0) {
    Addr = ((U32)&_aVRAM[0] + XSIZE_PHYS * YSIZE_PHYS * _PendingBuffer * (/*LCD_BITSPERPIXEL*/32 >> 3));
    _RasterDMAFBConfig(SOC_LCDC_0_REGS, Addr, Addr + XSIZE_PHYS * YSIZE_PHYS * sizeof(U32), 0);
    GUI_MULTIBUF_Confirm(_PendingBuffer);
    _PendingBuffer = -1;
  }
}

/*********************************************************************
*
*       _InitController
*/
static void _InitController(void) {
  _PendingBuffer = -1;
  //
  // Clock configuration
  //
  _LCDModuleClkConfig();
  //
  // Pin multiplexing
  //
  _LCDPinMuxSetup();
  //
  // Raster controller configuration
  //
  _RasterClocksEnable(SOC_LCDC_0_REGS);
  _RasterClkConfig(SOC_LCDC_0_REGS, XSIZE_PHYS * YSIZE_PHYS * 60, 192000000);
  _RasterDMAConfig(SOC_LCDC_0_REGS, RASTER_SINGLE_FRAME_BUFFER, RASTER_BURST_SIZE_16, RASTER_FIFO_THRESHOLD_8, RASTER_BIG_ENDIAN_DISABLE);
  _RasterModeConfig(SOC_LCDC_0_REGS, RASTER_DISPLAY_MODE_TFT_UNPACKED, RASTER_PALETTE_DATA, RASTER_COLOR, RASTER_RIGHT_ALIGNED);
  _RasterTiming2Configure(SOC_LCDC_0_REGS, RASTER_FRAME_CLOCK_LOW  |
                                           RASTER_LINE_CLOCK_LOW   |
                                           RASTER_PIXEL_CLOCK_HIGH |
                                           RASTER_SYNC_EDGE_RISING |
                                           RASTER_SYNC_CTRL_ACTIVE |
                                           RASTER_AC_BIAS_HIGH,
                                           0, 255);
  _RasterHparamConfig(SOC_LCDC_0_REGS, XSIZE_PHYS, HSW, HFP, HBP);
  _RasterVparamConfig(SOC_LCDC_0_REGS, YSIZE_PHYS, VSW, VFP, VBP);
  _RasterFIFODMADelayConfig(SOC_LCDC_0_REGS, 128);
  _RasterDMAFBConfig(SOC_LCDC_0_REGS, (U32)_aVRAM, (U32)_aVRAM + XSIZE_PHYS * YSIZE_PHYS * sizeof(U32), 0);
  //
  // Install interrupt handler for EndOfFrame-interrupt
  //
  OS_ARM_InstallISRHandler(36, _LCD_ISR_EndOfFrame);
  OS_ARM_EnableISR(36);
  //
  // Enable raster controller
  //
  _RasterIntEnable(SOC_LCDC_0_REGS);
  _RasterEnable(SOC_LCDC_0_REGS);
}

#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
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
  //
  // At first initialize use of multiple buffers on demand
  //
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
  #ifndef WIN32
    LCD_SetVRAMAddrEx(0, (void *)_aVRAM);
  #endif
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
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * p) {
  int r;

  (void)LayerIndex;
  switch (Cmd) {
  case LCD_X_SHOWBUFFER: {
    #ifndef WIN32
      LCD_X_SHOWBUFFER_INFO * pData;

      pData = (LCD_X_SHOWBUFFER_INFO *)p;
      _PendingBuffer = pData->Index;
    #endif
    }
    r = 0;
    break;
  case LCD_X_INITCONTROLLER: {
    #ifndef WIN32
      _InitController();
    #endif
    r = 0;
    break;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
