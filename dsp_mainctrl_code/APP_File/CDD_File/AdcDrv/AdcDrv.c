//==============================================================================================
//    File description
//==============================================================================================
/**@file         AdcDrv.c
 * @brief
 * Source file of ADC drive.
 *
 * Module      :                       \n
 * AdcDrv
 *
 * Module Task :                       \n
 * v_AdcDrv_Init()                     \n
 * v_AdcDrv_1ms()                      \n
 * v_AdcDrv_Isr()                      \n
 * v_AdcDrv_Adc_Isr()                  \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2023/11/22
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD     \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2023/11/22  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "AdcDrv.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_ADC_DRV stAdcDrv;                    ///< ADC drive global struct
#if (1U == FLG_SWUT_EN)
struct DAC_REGS DacaRegsUnitTest;
#endif
#if (1U == ADC_DRV_DBG)
ST_ADC_DRV stAdcDrvDbg;                 ///< ADC drive debug global struct
#endif

static ST_ADC_DRV_LOC stAdcDrvLoc;      ///< ADC drive local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        ADC drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_AdcDrv_Init(void)
{
    /* Local Signal*/
    stAdcDrvLoc.stPrmExt.uiADVgA         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgA         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgB         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgB         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgC         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgC         = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADIgN         = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgDcA       = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgDcA       = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgDcB       = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgDcB       = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgDcC       = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADIgDcC       = 0U;    ///< Initialize to 0U
	stAdcDrvLoc.stPrmExt.uiADVgInvA      = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADVgInvB      = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADVbus        = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADVbusPos     = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADVbusNeg     = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADDspBdTemp   = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADDspCoreTemp = 0U;    ///< Initialize to 0U
//    stAdcDrvLoc.stPrmExt.uiADAux12V      = 0U;    ///< Initialize to 0U
    stAdcDrvLoc.stPrmExt.uiADAux1V5      = 0U;    ///< Initialize to 0U

    /* Global Signal*/
#if (1U == ADC_DRV_DBG)
    stAdcDrvDbg.uiADVgA         = stAdcDrvLoc.stPrmExt.uiADVgA;
    stAdcDrvDbg.uiADIgA         = stAdcDrvLoc.stPrmExt.uiADIgA;
    stAdcDrvDbg.uiADVgB         = stAdcDrvLoc.stPrmExt.uiADVgB;
    stAdcDrvDbg.uiADIgB         = stAdcDrvLoc.stPrmExt.uiADIgB;
    stAdcDrvDbg.uiADVgC         = stAdcDrvLoc.stPrmExt.uiADVgC;
    stAdcDrvDbg.uiADIgC         = stAdcDrvLoc.stPrmExt.uiADIgC;
    stAdcDrvDbg.uiADIgN         = stAdcDrvLoc.stPrmExt.uiADIgN;
    stAdcDrvDbg.uiADVgDcA       = stAdcDrvLoc.stPrmExt.uiADVgDcA;
    stAdcDrvDbg.uiADIgDcA       = stAdcDrvLoc.stPrmExt.uiADIgDcA;
    stAdcDrvDbg.uiADVgDcB       = stAdcDrvLoc.stPrmExt.uiADVgDcB;
    stAdcDrvDbg.uiADIgDcB       = stAdcDrvLoc.stPrmExt.uiADIgDcB;
    stAdcDrvDbg.uiADVgDcC       = stAdcDrvLoc.stPrmExt.uiADVgDcC;
    stAdcDrvDbg.uiADIgDcC       = stAdcDrvLoc.stPrmExt.uiADIgDcC;
    stAdcDrvDbg.uiADVgInvA      = stAdcDrvLoc.stPrmExt.uiADVgInvA;
    stAdcDrvDbg.uiADVgInvB      = stAdcDrvLoc.stPrmExt.uiADVgInvB;
    stAdcDrvDbg.uiADVbus        = stAdcDrvLoc.stPrmExt.uiADVbus;
    stAdcDrvDbg.uiADVbusPos     = stAdcDrvLoc.stPrmExt.uiADVbusPos;
	stAdcDrvDbg.uiADVbusNeg     = stAdcDrvLoc.stPrmExt.uiADVbusNeg;
    stAdcDrvDbg.uiADDspBdTemp   = stAdcDrvLoc.stPrmExt.uiADDspBdTemp;
    stAdcDrvDbg.uiADDspCoreTemp = stAdcDrvLoc.stPrmExt.uiADDspCoreTemp;
    stAdcDrvDbg.uiADAux12V      = stAdcDrvLoc.stPrmExt.uiADAux12V;
    stAdcDrvDbg.uiADAux1V5      = stAdcDrvLoc.stPrmExt.uiADAux1V5;

    stAdcDrv.uiADVgA         = stAdcDrvDbg.uiADVgA;
    stAdcDrv.uiADIgA         = stAdcDrvDbg.uiADIgA;
    stAdcDrv.uiADVgB         = stAdcDrvDbg.uiADVgB;
    stAdcDrv.uiADIgB         = stAdcDrvDbg.uiADIgB;
    stAdcDrv.uiADVgC         = stAdcDrvDbg.uiADVgC;
    stAdcDrv.uiADIgC         = stAdcDrvDbg.uiADIgC;
    stAdcDrv.uiADIgN         = stAdcDrvDbg.uiADIgN;
    stAdcDrv.uiADVgDcA       = stAdcDrvDbg.uiADVgDcA;
    stAdcDrv.uiADIgDcA       = stAdcDrvDbg.uiADIgDcA;
    stAdcDrv.uiADVgDcB       = stAdcDrvDbg.uiADVgDcB;
    stAdcDrv.uiADIgDcB       = stAdcDrvDbg.uiADIgDcB;
    stAdcDrv.uiADVgDcC       = stAdcDrvDbg.uiADVgDcC;
    stAdcDrv.uiADIgDcC       = stAdcDrvDbg.uiADIgDcC;
    stAdcDrv.uiADVbus        = stAdcDrvDbg.uiADVbus;
    stAdcDrv.uiADVbusPos     = stAdcDrvDbg.uiADVbusPos;
    stAdcDrv.uiADDspBdTemp   = stAdcDrvDbg.uiADDspBdTemp;
    stAdcDrv.uiADDspCoreTemp = stAdcDrvDbg.uiADDspCoreTemp;
    stAdcDrv.uiADAux12V      = stAdcDrvDbg.uiADAux12V;
    stAdcDrv.uiADAux1V5      = stAdcDrvDbg.uiADAux1V5;
#else
    stAdcDrv.uiADVgA         = stAdcDrvLoc.stPrmExt.uiADVgA;
    stAdcDrv.uiADIgA         = stAdcDrvLoc.stPrmExt.uiADIgA;
    stAdcDrv.uiADVgB         = stAdcDrvLoc.stPrmExt.uiADVgB;
    stAdcDrv.uiADIgB         = stAdcDrvLoc.stPrmExt.uiADIgB;
    stAdcDrv.uiADVgC         = stAdcDrvLoc.stPrmExt.uiADVgC;
    stAdcDrv.uiADIgC         = stAdcDrvLoc.stPrmExt.uiADIgC;
#ifndef SST_1250kW
    stAdcDrv.uiADIgN         = stAdcDrvLoc.stPrmExt.uiADIgN;
    stAdcDrv.uiADDspBdTemp   = stAdcDrvLoc.stPrmExt.uiADDspBdTemp;
    stAdcDrv.uiADDspCoreTemp = stAdcDrvLoc.stPrmExt.uiADDspCoreTemp;
    stAdcDrv.uiADAux12V      = stAdcDrvLoc.stPrmExt.uiADAux12V;
    stAdcDrv.uiADVbus        = stAdcDrvLoc.stPrmExt.uiADVbus;
    stAdcDrv.uiADVbusPos     = stAdcDrvLoc.stPrmExt.uiADVbusPos;
    stAdcDrv.uiADVbusNeg     = stAdcDrvLoc.stPrmExt.uiADVbusNeg;
#endif
    stAdcDrv.uiADVgDcA       = stAdcDrvLoc.stPrmExt.uiADVgDcA;
    stAdcDrv.uiADIgDcA       = stAdcDrvLoc.stPrmExt.uiADIgDcA;
    stAdcDrv.uiADVgDcB       = stAdcDrvLoc.stPrmExt.uiADVgDcB;
    stAdcDrv.uiADIgDcB       = stAdcDrvLoc.stPrmExt.uiADIgDcB;
    stAdcDrv.uiADVgDcC       = stAdcDrvLoc.stPrmExt.uiADVgDcC;
    stAdcDrv.uiADIgDcC       = stAdcDrvLoc.stPrmExt.uiADIgDcC;	
    stAdcDrv.uiADVgInvA      = stAdcDrvLoc.stPrmExt.uiADVgInvA;
    stAdcDrv.uiADVgInvB      = stAdcDrvLoc.stPrmExt.uiADVgInvB;
    stAdcDrv.uiADAux1V5      = stAdcDrvLoc.stPrmExt.uiADAux1V5;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_AdcDrv_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        ADC drive task in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_AdcDrv_Isr, ".TI.ramfunc");
#endif
void v_AdcDrv_Isr(void)
{
    v_AdcDrv_Adc_Isr();            ///< Read ADC register result in ISR
#if(1U == GRID_PHASE_NUMBER)
    v_AdcDrv_Dac_Isr();            ///< DAC in ISR
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr) 
    {
        printf("****SWIT DynamicTest: function v_AdcDrv_Isr() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Read ADC register result in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_AdcDrv_Adc_Isr, ".TI.ramfunc");
#endif
static void v_AdcDrv_Adc_Isr(void)
{
#if(1U == GRID_PHASE_NUMBER)
    Uint16 l_uiADTmp0 = 0U;
    Uint16 l_uiADTmp1 = 0U;

    l_uiADTmp0 = VG_AD_RESULT1;
    l_uiADTmp1 = VG_AD_RESULT2;
    stAdcDrvLoc.stPrmExt.uiADVgA     = (l_uiADTmp0 + l_uiADTmp1)>>1;    ///< Vg_A AD result
    l_uiADTmp0 = IG_AD_RESULT1;
    l_uiADTmp1 = IG_AD_RESULT2;
    stAdcDrvLoc.stPrmExt.uiADIgA     = (l_uiADTmp0 + l_uiADTmp1)>>1;    ///< Ig_A AD result
    l_uiADTmp0 = VBUS_AD_RESULT1;
    l_uiADTmp1 = VBUS_AD_RESULT2;
    stAdcDrvLoc.stPrmExt.uiADVbus    = (l_uiADTmp0 + l_uiADTmp1)>>1;    ///< Vbus AD result
    stAdcDrvLoc.stPrmExt.uiADVgDcA   = VG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADIgDcA   = IG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
#elif(2U == GRID_PHASE_NUMBER)
    stAdcDrvLoc.stPrmExt.uiADVgA     = VG_AD_A_RESULT;                  ///< Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADVgB     = VG_AD_B_RESULT;                  ///< Vg_B AD result

    stAdcDrvLoc.stPrmExt.uiADIgA     = IG_AD_A_RESULT;                  ///< Ig_A AD result
    stAdcDrvLoc.stPrmExt.uiADIgB     = IG_AD_B_RESULT;                  ///< Ig_B AD result
    stAdcDrvLoc.stPrmExt.uiADIgN     = IG_AD_D_RESULT;                  ///< Ig_N AD result
    stAdcDrvLoc.stPrmExt.uiADVgInvA  = VG_INV_AD_A_RESULT;              ///< VgInv_A AD result
    stAdcDrvLoc.stPrmExt.uiADVgInvB  = VG_INV_AD_B_RESULT;              ///< VgInv_B AD result

    stAdcDrvLoc.stPrmExt.uiADVbusPos = VBUSPOS_AD_RESULT;               ///< Vbus AD result
    stAdcDrvLoc.stPrmExt.uiADVbusNeg = VBUSNEG_AD_RESULT;               ///< Vbus AD result

    stAdcDrvLoc.stPrmExt.uiADVgDcA   = VG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
	stAdcDrvLoc.stPrmExt.uiADIgDcA   = IG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADVgDcB   = VG_DC_AD_B_RESULT;               ///< DC of Vg_B AD result
    stAdcDrvLoc.stPrmExt.uiADIgDcB   = IG_DC_AD_B_RESULT;               ///< DC of Vg_B AD result
#else
    stAdcDrvLoc.stPrmExt.uiADVgA     = VG_AD_AB_RESULT;                  ///< Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADIgA     = IG_AD_A_RESULT;                  ///< Ig_A AD result
    stAdcDrvLoc.stPrmExt.uiADVgB     = VG_AD_BC_RESULT;                  ///< Vg_B AD result
    stAdcDrvLoc.stPrmExt.uiADIgB     = IG_AD_B_RESULT;                  ///< Ig_B AD result
    stAdcDrvLoc.stPrmExt.uiADVgC     = VG_AD_CA_RESULT;                  ///< Vg_C AD result
    stAdcDrvLoc.stPrmExt.uiADIgC     = IG_AD_C_RESULT;                  ///< Ig_C AD result
    stAdcDrvLoc.stPrmExt.uiADVgDcA   = VG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADIgDcA   = IG_DC_AD_A_RESULT;               ///< DC of Vg_A AD result
    stAdcDrvLoc.stPrmExt.uiADVgDcB   = VG_DC_AD_B_RESULT;               ///< DC of Vg_B AD result
    stAdcDrvLoc.stPrmExt.uiADIgDcB   = IG_DC_AD_B_RESULT;               ///< DC of Vg_B AD result
    stAdcDrvLoc.stPrmExt.uiADVgDcC   = VG_DC_AD_C_RESULT;               ///< DC of Vg_C AD result
    stAdcDrvLoc.stPrmExt.uiADIgDcC   = IG_DC_AD_C_RESULT;               ///< DC of Vg_C AD result
    stAdcDrvLoc.stPrmExt.uiADPt1Temp = TEMP_PT1_AD_RESULT;              ///< Temp of PT_1 AD result
    stAdcDrvLoc.stPrmExt.uiADPt2Temp = TEMP_PT2_AD_RESULT;              ///< Temp of PT_1 AD result
#endif

    /* Global Signal*/
#if (1U == ADC_DRV_DBG)
    stAdcDrv.uiADVgA                 = stAdcDrvDbg.uiADVgA;
    stAdcDrv.uiADIgA                 = stAdcDrvDbg.uiADIgA;
	stAdcDrv.uiADVgB                 = stAdcDrvDbg.uiADVgB;
    stAdcDrv.uiADIgB                 = stAdcDrvDbg.uiADIgB;
	stAdcDrv.uiADVgC                 = stAdcDrvDbg.uiADVgC;
    stAdcDrv.uiADIgC                 = stAdcDrvDbg.uiADIgC;
    stAdcDrv.uiADVgInvA              = stAdcDrvDbg.uiADVgInvA;
    stAdcDrv.uiADVgInvB              = stAdcDrvDbg.uiADVgInvB;
    stAdcDrv.uiADVbus                = stAdcDrvDbg.uiADVbus;
    stAdcDrv.uiADVbusPos             = stAdcDrvDbg.uiADVbusPos;
    stAdcDrv.uiADVbusNeg             = stAdcDrvDbg.uiADVbusNeg;
    stAdcDrv.uiADVgDcA               = stAdcDrvDbg.uiADVgDcA;
    stAdcDrv.uiADIgDcA               = stAdcDrvDbg.uiADIgDcA;
	stAdcDrv.uiADVgDcB               = stAdcDrvDbg.uiADVgDcB;
    stAdcDrv.uiADIgDcB               = stAdcDrvDbg.uiADIgDcB;
    stAdcDrv.uiADVgDcC               = stAdcDrvDbg.uiADVgDcC;
    stAdcDrv.uiADIgDcC               = stAdcDrvDbg.uiADIgDcC;
#else		
#if(1U == GRID_PHASE_NUMBER)
    stAdcDrv.uiADVgA                 = stAdcDrvLoc.stPrmExt.uiADVgA;
	stAdcDrv.uiADIgA                 = stAdcDrvLoc.stPrmExt.uiADIgA;
    stAdcDrv.uiADVgDcA               = stAdcDrvLoc.stPrmExt.uiADVgDcA;
    stAdcDrv.uiADIgDcA               = stAdcDrvLoc.stPrmExt.uiADIgDcA;
	stAdcDrv.uiADVbus                = stAdcDrvLoc.stPrmExt.uiADVbus;
#elif(2U == GRID_PHASE_NUMBER)
    stAdcDrv.uiADVgA                 = stAdcDrvLoc.stPrmExt.uiADVgA;
	stAdcDrv.uiADIgA                 = stAdcDrvLoc.stPrmExt.uiADIgA;
    stAdcDrv.uiADVgDcA               = stAdcDrvLoc.stPrmExt.uiADVgDcA;
    stAdcDrv.uiADIgDcA               = stAdcDrvLoc.stPrmExt.uiADIgDcA;
    stAdcDrv.uiADVgB                 = stAdcDrvLoc.stPrmExt.uiADVgB;
	stAdcDrv.uiADIgB                 = stAdcDrvLoc.stPrmExt.uiADIgB;
    stAdcDrv.uiADVgDcB               = stAdcDrvLoc.stPrmExt.uiADVgDcB;
	stAdcDrv.uiADIgDcB               = stAdcDrvLoc.stPrmExt.uiADIgDcB;
	stAdcDrv.uiADIgN                 = stAdcDrvLoc.stPrmExt.uiADIgN;
	stAdcDrv.uiADVgInvA              = stAdcDrvLoc.stPrmExt.uiADVgInvA;
    stAdcDrv.uiADVgInvB              = stAdcDrvLoc.stPrmExt.uiADVgInvB;
	stAdcDrv.uiADVbusPos             = stAdcDrvLoc.stPrmExt.uiADVbusPos;
    stAdcDrv.uiADVbusNeg             = stAdcDrvLoc.stPrmExt.uiADVbusNeg;
#elif(3U == GRID_PHASE_NUMBER)
    stAdcDrv.uiADVgA                 = stAdcDrvLoc.stPrmExt.uiADVgA;
	stAdcDrv.uiADIgA                 = stAdcDrvLoc.stPrmExt.uiADIgA;
    stAdcDrv.uiADVgDcA               = stAdcDrvLoc.stPrmExt.uiADVgDcA;
    stAdcDrv.uiADIgDcA               = stAdcDrvLoc.stPrmExt.uiADIgDcA;
    stAdcDrv.uiADVgB                 = stAdcDrvLoc.stPrmExt.uiADVgB;
	stAdcDrv.uiADIgB                 = stAdcDrvLoc.stPrmExt.uiADIgB;
    stAdcDrv.uiADVgDcB               = stAdcDrvLoc.stPrmExt.uiADVgDcB;
	stAdcDrv.uiADIgDcB               = stAdcDrvLoc.stPrmExt.uiADIgDcB;
	stAdcDrv.uiADVgC                 = stAdcDrvLoc.stPrmExt.uiADVgC;
	stAdcDrv.uiADIgC                 = stAdcDrvLoc.stPrmExt.uiADIgC;
	stAdcDrv.uiADVgDcC               = stAdcDrvLoc.stPrmExt.uiADVgDcC;
	stAdcDrv.uiADIgDcC               = stAdcDrvLoc.stPrmExt.uiADIgDcC;
	stAdcDrv.uiADPt1Temp             = stAdcDrvLoc.stPrmExt.uiADPt1Temp;
	stAdcDrv.uiADPt2Temp             = stAdcDrvLoc.stPrmExt.uiADPt2Temp;
#ifndef SST_1250kW
	stAdcDrv.uiADIgN                 = stAdcDrvLoc.stPrmExt.uiADIgN;
    stAdcDrv.uiADVbus                = stAdcDrvLoc.stPrmExt.uiADVbus;
    stAdcDrv.uiADVbusPos             = stAdcDrvLoc.stPrmExt.uiADVbusPos;
#endif

#endif	
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        DAC task in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(1U == GRID_PHASE_NUMBER)
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_AdcDrv_Dac_Isr, ".TI.ramfunc");
#endif
static void v_AdcDrv_Dac_Isr(void)
{
    switch(stComTbl.stPrmCmnAdc.uiDacCh)
    {
        case 1U:
            DACA_REG.DACVALS.all = (Uint16)stPfcAdc.stVg.ftVal_A;       ///< Phase A Vg value
            break;

        case 2U:
            DACA_REG.DACVALS.all = (Uint16)stPfcAdc.stIg.ftVal_A;       ///< Phase A Ig value
            break;

        case 3U:
            DACA_REG.DACVALS.all = (Uint16)stPfcAdc.stVbus.ftVal_A;     ///< Phase A Vbus value
            break;

        case 4U:
            DACA_REG.DACVALS.all = (Uint16)stPfcAdc.stIgDc.ftVal_A;     ///< Phase A Ig Dc value
            break;

        case 5U:
            DACA_REG.DACVALS.all = PFC_FAST_PWM.CMPA.bit.CMPA;          ///< PFC Fast Mos CompareA value
            break;

        default:
            ///< Do nothing
            break;
    }
}
#endif
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        ADC drive 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_AdcDrv_1ms(void)
{
#ifndef SST_1250kW
    stAdcDrvLoc.stPrmExt.uiADDspBdTemp   = BOARD_TEMP_AD_RESULT;       ///< DSP board temperature AD result SST NO USE
    stAdcDrvLoc.stPrmExt.uiADDspCoreTemp = DSP_CORE_TEMP_AD_RESULT;    ///< DSP core temperature AD result SST NO USE
    stAdcDrvLoc.stPrmExt.uiADAux12V      = AUX_12V_AD_RESULT;          ///< 12V AD result SST NO USE
#endif
    stAdcDrvLoc.stPrmExt.uiADAux1V5      = AUX_1V5_AD_RESULT;          ///< 1V5 AD result

    /* Global Signal*/
#if (1U == ADC_DRV_DBG)
    stAdcDrv.uiADDspBdTemp   = stAdcDrvDbg.uiADDspBdTemp;
    stAdcDrv.uiADDspCoreTemp = stAdcDrvDbg.uiADDspCoreTemp;
    stAdcDrv.uiADAux12V      = stAdcDrvDbg.uiADAux12V;
    stAdcDrv.uiADAux1V5      = stAdcDrvDbg.uiADAux1V5;
#else
#ifndef SST_1250kW
    stAdcDrv.uiADDspBdTemp   = stAdcDrvLoc.stPrmExt.uiADDspBdTemp;   ///< SST NO USE
    stAdcDrv.uiADDspCoreTemp = stAdcDrvLoc.stPrmExt.uiADDspCoreTemp; ///< SST NO USE
    stAdcDrv.uiADAux12V      = stAdcDrvLoc.stPrmExt.uiADAux12V;      ///< SST NO USE
#endif
    stAdcDrv.uiADAux1V5      = stAdcDrvLoc.stPrmExt.uiADAux1V5;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_AdcDrv_1ms() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
