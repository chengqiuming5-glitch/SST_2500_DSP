//========================================================================
// FILE          : PfcAdc.c
// TITLE         : PFC ADC Source File
//========================================================================
/* Copyright (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.09
* Version       : V1.0
* Descriptions  :
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
**************************************************************************
*/

/*
**************************************************************************
* Module        : PfcAdc
* 1st Unit      :
* 2nd Unit      :
* 3nd Unit      :
*
* Module Task   : v_PfcAdc_Init()
*
*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
**************************************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcAdc.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_ADC stPfcAdc;       ///< PFC ADC global struct

#if (1U == PFC_ADC_DBG)
ST_PFC_ADC stPfcAdcDbg;    ///< PFC ADC debug global struct
#endif

static ST_PFC_ADC_LOC stPfcAdcLoc;    ///< PFC ADC local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC ADC initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcAdc_Init(void)
{
    /* Local Signal*/
    stPfcAdcLoc.stPrmExt.stVg.ftVal_A              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVg.ftVal_B              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVg.ftVal_C              = 0.0f;     ///< Initialize to 0
#ifndef SST_1250kW
    stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A           = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B           = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_A   = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_B   = 0.0f;     ///< Initialize to 0
#endif
    stPfcAdcLoc.stPrmExt.stIg.ftVal_A              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftVal_B              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftVal_C              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftVal_N              = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbus.ftVal_A            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A         = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A         = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_C            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C            = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A  = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B  = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C  = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N      = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A    = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbusPos.ftValLpf10kHz_A = 0.0f;     ///< Initialize to 0
    stPfcAdcLoc.stPrmExt.stVbusNeg.ftValLpf10kHz_A = 0.0f;     ///< Initialize to 0

    /* Global Signal*/
#if (1U == PFC_ADC_DBG)
    stPfcAdcDbg.stVg.ftVal_A              = stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
    stPfcAdcDbg.stVg.ftVal_B              = stPfcAdcLoc.stPrmExt.stVg.ftVal_B;
    stPfcAdcDbg.stVg.ftVal_C              = stPfcAdcLoc.stPrmExt.stVg.ftVal_C;
    stPfcAdcDbg.stVgInv.ftVal_A           = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A;
    stPfcAdcDbg.stVgInv.ftVal_B           = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B;
    stPfcAdcDbg.stIg.ftVal_A              = stPfcAdcLoc.stPrmExt.stIg.ftVal_A;
    stPfcAdcDbg.stIg.ftVal_B              = stPfcAdcLoc.stPrmExt.stIg.ftVal_B;
    stPfcAdcDbg.stIg.ftVal_C              = stPfcAdcLoc.stPrmExt.stIg.ftVal_C;
    stPfcAdcDbg.stIg.ftVal_N              = stPfcAdcLoc.stPrmExt.stIg.ftVal_N;
    stPfcAdcDbg.stVbus.ftVal_A            = stPfcAdcLoc.stPrmExt.stVbus.ftVal_A;
    stPfcAdcDbg.stVbusPos.ftVal_A         = stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A;
    stPfcAdcDbg.stVbusNeg.ftVal_A         = stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A;
    stPfcAdcDbg.stVgDc.ftVal_A            = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A;
    stPfcAdcDbg.stVgDc.ftVal_B            = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B;
    stPfcAdcDbg.stVgDc.ftVal_C            = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_C;
    stPfcAdcDbg.stIgDc.ftVal_A            = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A;
    stPfcAdcDbg.stIgDc.ftVal_B            = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B;
    stPfcAdcDbg.stIgDc.ftVal_C            = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C;
    stPfcAdcDbg.stVg.ftValLpf10kHz_A      = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A;
    stPfcAdcDbg.stVg.ftValLpf10kHz_B      = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B;
    stPfcAdcDbg.stVg.ftValLpf10kHz_C      = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C;
    stPfcAdcDbg.stVgInv.ftValLpf10kHz_A   = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_A;
    stPfcAdcDbg.stVgInv.ftValLpf10kHz_B   = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_B;
    stPfcAdcDbg.stIg.ftValLpf10kHz_A      = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdcDbg.stIg.ftValLpf10kHz_B      = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B;
    stPfcAdcDbg.stIg.ftValLpf10kHz_C      = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C;
    stPfcAdcDbg.stIg.ftValLpf10kHz_N      = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N;
    stPfcAdcDbg.stVbus.ftValLpf10kHz_A    = stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A;
    stPfcAdcDbg.stVbusPos.ftValLpf10kHz_A = stPfcAdcLoc.stPrmExt.stVbusPos.ftValLpf10kHz_A;
    stPfcAdcDbg.stVbusNeg.ftValLpf10kHz_A = stPfcAdcLoc.stPrmExt.stVbusNeg.ftValLpf10kHz_A;

    stPfcAdc.stVg.ftVal_A               = stPfcAdcDbg.stVg.ftVal_A;
    stPfcAdc.stVg.ftVal_B               = stPfcAdcDbg.stVg.ftVal_B;
    stPfcAdc.stVg.ftVal_C               = stPfcAdcDbg.stVg.ftVal_C;
    stPfcAdc.stVgInv.ftVal_A            = stPfcAdcDbg.stVgInv.ftVal_A;
    stPfcAdc.stVgInv.ftVal_B            = stPfcAdcDbg.stVgInv.ftVal_B;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcDbg.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcDbg.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcDbg.stIg.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcDbg.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftVal_A             = stPfcAdcDbg.stVbus.ftVal_A;
    stPfcAdc.stVbusPos.ftVal_A          = stPfcAdcDbg.stVbusPos.ftVal_A;
    stPfcAdc.stVbusNeg.ftVal_A          = stPfcAdcDbg.stVbusNeg.ftVal_A;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcDbg.stVgDc.ftVal_A;
    stPfcAdc.stVgDc.ftVal_B             = stPfcAdcDbg.stVgDc.ftVal_B;
    stPfcAdc.stVgDc.ftVal_C             = stPfcAdcDbg.stVgDc.ftVal_C;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcDbg.stIgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_B             = stPfcAdcDbg.stIgDc.ftVal_B;
    stPfcAdc.stIgDc.ftVal_C             = stPfcAdcDbg.stIgDc.ftVal_C;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcDbg.stVg.ftValLpf10kHz_A;
    stPfcAdc.stVg.ftValLpf10kHz_B       = stPfcAdcDbg.stVg.ftValLpf10kHz_B;
    stPfcAdc.stVg.ftValLpf10kHz_C       = stPfcAdcDbg.stVg.ftValLpf10kHz_C;
    stPfcAdc.stVgInv.ftValLpf10kHz_A    = stPfcAdcDbg.stVgInv.ftValLpf10kHz_A;
    stPfcAdc.stVgInv.ftValLpf10kHz_B    = stPfcAdcDbg.stVgInv.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcDbg.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcDbg.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcDbg.stIg.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcDbg.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftValLpf10kHz_A     = stPfcAdcDbg.stVbus.ftValLpf10kHz_A;
    stPfcAdc.stVbusPos.ftValLpf10kHz_A  = stPfcAdcDbg.stVbusPos.ftValLpf10kHz_A;
    stPfcAdc.stVbusNeg.ftValLpf10kHz_A  = stPfcAdcDbg.stVbusNeg.ftValLpf10kHz_A;
#else
    stPfcAdc.stVg.ftVal_A               = stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
    stPfcAdc.stVg.ftVal_B               = stPfcAdcLoc.stPrmExt.stVg.ftVal_B;
    stPfcAdc.stVg.ftVal_C               = stPfcAdcLoc.stPrmExt.stVg.ftVal_C;
#ifndef SST_1250kW
    stPfcAdc.stVgInv.ftVal_A            = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A;
    stPfcAdc.stVgInv.ftVal_B            = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B;
#endif
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftVal_A             = stPfcAdcLoc.stPrmExt.stVbus.ftVal_A;
    stPfcAdc.stVbusPos.ftVal_A          = stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A;
    stPfcAdc.stVbusNeg.ftVal_A          = stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A;
    stPfcAdc.stVgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B;
    stPfcAdc.stVgDc.ftVal_C             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_C;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B;
    stPfcAdc.stIgDc.ftVal_C             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A;
    stPfcAdc.stVg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B;
    stPfcAdc.stVg.ftValLpf10kHz_C       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C;
//    stPfcAdc.stVgLine.ftValLpf10kHz_A   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A;
//    stPfcAdc.stVgLine.ftValLpf10kHz_B   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B;
//    stPfcAdc.stVgLine.ftValLpf10kHz_C   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C;
//    stPfcAdc.stVgInv.ftValLpf10kHz_A    = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_A;
//    stPfcAdc.stVgInv.ftValLpf10kHz_B    = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftValLpf10kHz_A     = stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A;
    stPfcAdc.stVbusPos.ftValLpf10kHz_A  = stPfcAdcLoc.stPrmExt.stVbusPos.ftValLpf10kHz_A;
    stPfcAdc.stVbusNeg.ftValLpf10kHz_A  = stPfcAdcLoc.stPrmExt.stVbusNeg.ftValLpf10kHz_A;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcAdc_Init() is running****\r\n");
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC ADC task in ISR
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcAdc_Isr, ".TI.ramfunc");
#endif
void v_PfcAdc_Isr(void)
{
    int16 l_siADTmp = 0;           ///< Temporary AD
    float32 l_ftVbusAvgTmp = 0.0f;

#if(2U == GRID_PHASE_NUMBER)
    float32 l_ftDataTmp = 0.0f;    ///< Temporary data
#endif

    /* Value calculation */
#if(1U == GRID_PHASE_NUMBER)
    #ifndef _SIMULATION_NO_DSP_
    /* Vg_a */
    l_siADTmp = (int16)stAdcDrv.uiADVgA - stCom.stPrmPfcAdjCoeff.siVgZero_A;
    stPfcAdcLoc.stPrmExt.stVg.ftVal_A = (float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVaK;
    /* Ig_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgA - stCom.stPrmPfcAdjCoeff.siIgZero_A;
    stPfcAdcLoc.stPrmExt.stIg.ftVal_A = -(float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIaK;    ///< Direction: from inverter to grid; 0.995f is for power accuracy
    /* Vbus */
    l_siADTmp = (int16)stAdcDrv.uiADVbus - stCom.stPrmPfcAdjCoeff.siBusVoltZero;
    stPfcAdcLoc.stPrmExt.stVbus.ftVal_A = (float32)l_siADTmp * COEFF_AD_VBUS * stCom.stPrmPfcAdjCoeff.ftVBusK;
    /* VgDc_a */
    l_siADTmp = (int16)stAdcDrv.uiADVgDcA - stCom.stPrmPfcAdjCoeff.siVgDcZero_A;
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_VGDC;
    /* IgDc_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcA - stCom.stPrmPfcAdjCoeff.siIgDcZero_A;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_IGDC;
    #endif
    /* LPF */
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stIg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVbus.ftVal_A, LPF_10KHZ_ISR_COEFF);
#elif(2U == GRID_PHASE_NUMBER)
    #ifndef _SIMULATION_NO_DSP_
    /* Vg_a */
    l_siADTmp = (int16)stAdcDrv.uiADVgA - stCom.stPrmPfcAdjCoeff.siVgZero_A;
    stPfcAdcLoc.stPrmExt.stVg.ftVal_A = (float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVaK;
    /* Vg_b */
    l_siADTmp = (int16)stAdcDrv.uiADVgB - stCom.stPrmPfcAdjCoeff.siVgZero_B;
    stPfcAdcLoc.stPrmExt.stVg.ftVal_B = (float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVbK;
    /* VgInv_a */
    l_siADTmp = (int16)stAdcDrv.uiADVgInvA - stCom.stPrmPfcAdjCoeff.siVgInvZero_A;
    stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A = (float32)l_siADTmp * COEFF_AD_VGINV * stCom.stPrmPfcAdjCoeff.ftVaInvK;
    /* VgInv_b */
    l_siADTmp = (int16)stAdcDrv.uiADVgInvB - stCom.stPrmPfcAdjCoeff.siVgInvZero_B;
    stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B = (float32)l_siADTmp * COEFF_AD_VGINV * stCom.stPrmPfcAdjCoeff.ftVbInvK;
    /* Ig_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgA - stCom.stPrmPfcAdjCoeff.siIgZero_A;
    stPfcAdcLoc.stPrmExt.stIg.ftVal_A = -(float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIaK;
    /* Ig_b */
    l_siADTmp = (int16)stAdcDrv.uiADIgB - stCom.stPrmPfcAdjCoeff.siIgZero_B;
    stPfcAdcLoc.stPrmExt.stIg.ftVal_B = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIbK;
    /* Ig_n */
    l_siADTmp = (int16)stAdcDrv.uiADIgN - stCom.stPrmPfcAdjCoeff.siIgZero_N;
    stPfcAdcLoc.stPrmExt.stIg.ftVal_N = -(float32)l_siADTmp * COEFF_AD_IGN * stCom.stPrmPfcAdjCoeff.ftInK;
    /* VbusPos */
    l_siADTmp = (int16)stAdcDrv.uiADVbusPos - stCom.stPrmPfcAdjCoeff.siPosBusVoltZero;
    stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A = (float32)l_siADTmp * COEFF_AD_VBUSPOS * stCom.stPrmPfcAdjCoeff.ftVPosBusK;
    /* VbusNeg */
    l_siADTmp = (int16)stAdcDrv.uiADVbusNeg - stCom.stPrmPfcAdjCoeff.siNegBusVoltZero;
    stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A = (float32)l_siADTmp * COEFF_AD_VBUSNEG * stCom.stPrmPfcAdjCoeff.ftVNegBusK;
    /* Vbus */
    stPfcAdcLoc.stPrmExt.stVbus.ftVal_A = stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A + stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A;
    /* VgDc_a */
    l_siADTmp = (int16)stAdcDrv.uiADVgDcA - stCom.stPrmPfcAdjCoeff.siVgDcZero_A;
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_VGDC;
    /* VgDc_b */
    l_siADTmp = (int16)stAdcDrv.uiADVgDcB - stCom.stPrmPfcAdjCoeff.siVgDcZero_B;
    stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_VGDC;
    /* IgDc_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcA - stCom.stPrmPfcAdjCoeff.siIgDcZero_A;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_IGDC;
    /* IgDc_b */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcB - stCom.stPrmPfcAdjCoeff.siIgDcZero_B;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_IGDC;

    if(TYPE_GRID_AB == stCom.uiTypeGrid)
    {
        l_ftDataTmp = stPfcAdcLoc.stPrmExt.stVg.ftVal_A - stPfcAdcLoc.stPrmExt.stVg.ftVal_B;
        stPfcAdcLoc.stPrmExt.stVg.ftVal_A = l_ftDataTmp * 0.5f;
        stPfcAdcLoc.stPrmExt.stVg.ftVal_B = -stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
        l_ftDataTmp = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A - stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B;
        stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A = l_ftDataTmp * 0.5f;
        stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B = -stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A;
        l_ftDataTmp = stPfcAdcLoc.stPrmExt.stIg.ftVal_A - stPfcAdcLoc.stPrmExt.stIg.ftVal_B;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_A = l_ftDataTmp * 0.5f;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_B = -stPfcAdcLoc.stPrmExt.stIg.ftVal_A;
    }

    /* LPF */
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stVg.ftVal_B, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stIg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stIg.ftVal_B, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N, stPfcAdcLoc.stPrmExt.stIg.ftVal_N, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVbus.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVbusPos.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVbusNeg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B, LPF_10KHZ_ISR_COEFF);

    /* Line voltage Vab calculation */
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)
    {
        stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A \
                                                        - stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B;
    }
    #endif
#elif(3U == GRID_PHASE_NUMBER)
    //#ifndef _SIMULATION_NO_DSP_
    /* Vgline_ab */
    l_siADTmp = (int16)stAdcDrv.uiADVgA - stCom.stPrmPfcAdjCoeff.siVgZero_A;
    stPfcAdcLoc.stPrmExt.stVgLine.ftVal_A = -1.0*(float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVaK; //Vba -> Vab
    /* Vgline_bc */
    l_siADTmp = (int16)stAdcDrv.uiADVgB - stCom.stPrmPfcAdjCoeff.siVgZero_B;
    stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B = -1.0*(float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVbK; //Vcb -> Vbc
    /* Vgline_ca */
    l_siADTmp = (int16)stAdcDrv.uiADVgC - stCom.stPrmPfcAdjCoeff.siVgZero_C;
    stPfcAdcLoc.stPrmExt.stVgLine.ftVal_C = -1.0*(float32)l_siADTmp * COEFF_AD_VG * stCom.stPrmPfcAdjCoeff.ftVcK; //Vac -> Vca

    /* Ig_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgA - stCom.stPrmPfcAdjCoeff.siIgZero_A;
    stPfcAdcLoc.stPrmExt.stIg.ftVal_A = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIaK;

    /* Vg_a */
    stPfcAdcLoc.stPrmExt.stVg.ftVal_A = (stPfcAdcLoc.stPrmExt.stVgLine.ftVal_A - stPfcAdcLoc.stPrmExt.stVgLine.ftVal_C) * RECPR_CON_3;


    if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)
    {
        /* Ig_b */
        l_siADTmp = (int16)stAdcDrv.uiADIgB - stCom.stPrmPfcAdjCoeff.siIgZero_B;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_B = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIbK;
        /* Ig_c */
        l_siADTmp = (int16)stAdcDrv.uiADIgC - stCom.stPrmPfcAdjCoeff.siIgZero_C;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_C = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIcK;
        /* Vg_b */
        stPfcAdcLoc.stPrmExt.stVg.ftVal_B = (stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B - stPfcAdcLoc.stPrmExt.stVgLine.ftVal_A) * RECPR_CON_3;
        /* Vg_c */
        stPfcAdcLoc.stPrmExt.stVg.ftVal_C = (stPfcAdcLoc.stPrmExt.stVgLine.ftVal_C - stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B) * RECPR_CON_3;
    }
    else
    {
        /* Ig_c */
        l_siADTmp = (int16)stAdcDrv.uiADIgB - stCom.stPrmPfcAdjCoeff.siIgZero_B;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_C = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIbK;
        /* Ig_b */
        l_siADTmp = (int16)stAdcDrv.uiADIgC - stCom.stPrmPfcAdjCoeff.siIgZero_C;
        stPfcAdcLoc.stPrmExt.stIg.ftVal_B = (float32)l_siADTmp * COEFF_AD_IG * stCom.stPrmPfcAdjCoeff.ftIcK;
        /* Vg_b */
        stPfcAdcLoc.stPrmExt.stVg.ftVal_B = (stPfcAdcLoc.stPrmExt.stVgLine.ftVal_C - stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B) * RECPR_CON_3;
        /* Vg_c */
        stPfcAdcLoc.stPrmExt.stVg.ftVal_C = (stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B - stPfcAdcLoc.stPrmExt.stVgLine.ftVal_A) * RECPR_CON_3;
    }


    l_ftVbusAvgTmp = (float32)stEmifDma1.siVbusUpA[0] + (float32)stEmifDma1.siVbusUpB[0] + (float32)stEmifDma1.siVbusUpC[0] +\
                     (float32)stEmifDma1.siVbusDnA[0] + (float32)stEmifDma1.siVbusDnB[0] + (float32)stEmifDma1.siVbusDnC[0] +\
                     (float32)stEmifDma1.siVbusUpA[1] + (float32)stEmifDma1.siVbusUpB[1] + (float32)stEmifDma1.siVbusUpC[1] +\
                     (float32)stEmifDma1.siVbusDnA[1] + (float32)stEmifDma1.siVbusDnB[1] + (float32)stEmifDma1.siVbusDnC[1] +\
                     (float32)stEmifDma1.siVbusUpA[2] + (float32)stEmifDma1.siVbusUpB[2] + (float32)stEmifDma1.siVbusUpC[2] +\
                     (float32)stEmifDma1.siVbusDnA[2] + (float32)stEmifDma1.siVbusDnB[2] + (float32)stEmifDma1.siVbusDnC[2];

    stPfcAdcLoc.stPrmExt.ftVbusCellAvg = l_ftVbusAvgTmp * RECPR_CON_3 * COEFF_AD_VBUS / NUM_PHA_POW_CELL;

#if 0
    if(OFFGRID_MODE == stComIf.uiModPfcRun)
    {
        /* VgDc_a */
        l_siADTmp = (int16)stAdcDrv.uiADVgDcA - stCom.stPrmPfcAdjCoeff.siVgDcZero_A;
        stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_VGDC;
        /* VgDc_b */
        l_siADTmp = (int16)stAdcDrv.uiADVgDcB - stCom.stPrmPfcAdjCoeff.siVgDcZero_B;
        stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_VGDC;
        /* VgDc_c */
        l_siADTmp = (int16)stAdcDrv.uiADVgDcC - stCom.stPrmPfcAdjCoeff.siVgDcZero_C;
        stPfcAdcLoc.stPrmExt.stVgDc.ftVal_C = (float32)l_siADTmp * COEFF_AD_VGDC;
    }
    else
    {
        if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyN)
        {
            /* IgDc_a */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcA - stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_IGDC;
            /* IgDc_b */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcB - stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_IGDC;
            /* IgDc_c */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcC - stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C = (float32)l_siADTmp * COEFF_AD_IGDC;
        }
        else
        {
            /* IgDc_a */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcA - stCom.stPrmPfcAdjCoeff.siIgDcZero_A;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_IGDC;
            /* IgDc_b */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcB - stCom.stPrmPfcAdjCoeff.siIgDcZero_B;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_IGDC;
            /* IgDc_c */
            l_siADTmp = (int16)stAdcDrv.uiADIgDcC - stCom.stPrmPfcAdjCoeff.siIgDcZero_C;
            stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C = (float32)l_siADTmp * COEFF_AD_IGDC;
        }
    }
#else
    /* IgDc_a */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcA - stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A = (float32)l_siADTmp * COEFF_AD_IGDC;
    /* IgDc_b */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcB - stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B = (float32)l_siADTmp * COEFF_AD_IGDC;
    /* IgDc_c */
    l_siADTmp = (int16)stAdcDrv.uiADIgDcC - stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N;
    stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C = (float32)l_siADTmp * COEFF_AD_IGDC;
#endif



    /* LPF */
//    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVgLine.ftVal_A, LPF_10KHZ_ISR_COEFF);
//    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stVgLine.ftVal_B, LPF_10KHZ_ISR_COEFF);
//    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C, stPfcAdcLoc.stPrmExt.stVgLine.ftVal_C, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stVg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stVg.ftVal_B, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C, stPfcAdcLoc.stPrmExt.stVg.ftVal_C, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A, stPfcAdcLoc.stPrmExt.stIg.ftVal_A, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B, stPfcAdcLoc.stPrmExt.stIg.ftVal_B, LPF_10KHZ_ISR_COEFF);
    vFcn_1stOrdLPF(&stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C, stPfcAdcLoc.stPrmExt.stIg.ftVal_C, LPF_10KHZ_ISR_COEFF);
    //stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A = (stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A - stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C) * RECPR_CON_3;
    //stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B = (stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B - stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A) * RECPR_CON_3;
    //stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C = (stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C - stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B) * RECPR_CON_3;
    //#endif
#endif

    /* Global Signal*/
#if (1U == PFC_ADC_DBG)
    stPfcAdc.stVg.ftVal_A               = stPfcAdcDbg.stVg.ftVal_A;
    stPfcAdc.stVg.ftVal_B               = stPfcAdcDbg.stVg.ftVal_B;
    stPfcAdc.stVg.ftVal_C               = stPfcAdcDbg.stVg.ftVal_C;
    stPfcAdc.stVgInv.ftVal_A            = stPfcAdcDbg.stVgInv.ftVal_A;
    stPfcAdc.stVgInv.ftVal_B            = stPfcAdcDbg.stVgInv.ftVal_B;
    stPfcAdc.stIg.ftVal_A               = stPfcAdcDbg.stIg.ftVal_A;
    stPfcAdc.stIg.ftVal_B               = stPfcAdcDbg.stIg.ftVal_B;
    stPfcAdc.stIg.ftVal_C               = stPfcAdcDbg.stIg.ftVal_C;
    stPfcAdc.stIg.ftVal_N               = stPfcAdcDbg.stIg.ftVal_N;
    stPfcAdc.stVbus.ftVal_A             = stPfcAdcDbg.stVbus.ftVal_A;
    stPfcAdc.stVbusPos.ftVal_A          = stPfcAdcDbg.stVbusPos.ftVal_A;
    stPfcAdc.stVbusNeg.ftVal_A          = stPfcAdcDbg.stVbusNeg.ftVal_A;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcDbg.stVgDc.ftVal_A;
    stPfcAdc.stVgDc.ftVal_B             = stPfcAdcDbg.stVgDc.ftVal_B;
    stPfcAdc.stVgDc.ftVal_C             = stPfcAdcDbg.stVgDc.ftVal_C;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcDbg.stIgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_B             = stPfcAdcDbg.stIgDc.ftVal_B;
    stPfcAdc.stIgDc.ftVal_C             = stPfcAdcDbg.stIgDc.ftVal_C;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcDbg.stVg.ftValLpf10kHz_A;
    stPfcAdc.stVg.ftValLpf10kHz_B       = stPfcAdcDbg.stVg.ftValLpf10kHz_B;
    stPfcAdc.stVg.ftValLpf10kHz_C       = stPfcAdcDbg.stVg.ftValLpf10kHz_C;
    stPfcAdc.stVgInv.ftValLpf10kHz_A    = stPfcAdcDbg.stVgInv.ftValLpf10kHz_A;
    stPfcAdc.stVgInv.ftValLpf10kHz_B    = stPfcAdcDbg.stVgInv.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcDbg.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcDbg.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcDbg.stIg.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcDbg.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftValLpf10kHz_A     = stPfcAdcDbg.stVbus.ftValLpf10kHz_A;
    stPfcAdc.stVbusPos.ftValLpf10kHz_A  = stPfcAdcDbg.stVbusPos.ftValLpf10kHz_A;
    stPfcAdc.stVbusNeg.ftValLpf10kHz_A  = stPfcAdcDbg.stVbusNeg.ftValLpf10kHz_A;
#else
#if(1U == GRID_PHASE_NUMBER)
    stPfcAdc.stVg.ftVal_A               = stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
    stPfcAdc.stIg.ftVal_A               = stPfcAdcLoc.stPrmExt.stIg.ftVal_A;
    stPfcAdc.stVbus.ftVal_A             = stPfcAdcLoc.stPrmExt.stVbus.ftVal_A;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdc.stVbus.ftValLpf10kHz_A     = stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A;
#elif(2U == GRID_PHASE_NUMBER)
    stPfcAdc.stVg.ftVal_A               = stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
    stPfcAdc.stVg.ftVal_B               = stPfcAdcLoc.stPrmExt.stVg.ftVal_B;
    stPfcAdc.stVgInv.ftVal_A            = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_A;
    stPfcAdc.stVgInv.ftVal_B            = stPfcAdcLoc.stPrmExt.stVgInv.ftVal_B;
    stPfcAdc.stIg.ftVal_A               = stPfcAdcLoc.stPrmExt.stIg.ftVal_A;
    stPfcAdc.stIg.ftVal_B               = stPfcAdcLoc.stPrmExt.stIg.ftVal_B;
    stPfcAdc.stIg.ftVal_N               = stPfcAdcLoc.stPrmExt.stIg.ftVal_N;
    stPfcAdc.stVbus.ftVal_A             = stPfcAdcLoc.stPrmExt.stVbus.ftVal_A;
    stPfcAdc.stVbusPos.ftVal_A          = stPfcAdcLoc.stPrmExt.stVbusPos.ftVal_A;
    stPfcAdc.stVbusNeg.ftVal_A          = stPfcAdcLoc.stPrmExt.stVbusNeg.ftVal_A;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A;
    stPfcAdc.stVgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A;
    stPfcAdc.stVg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B;
    stPfcAdc.stVgLine.ftValLpf10kHz_A   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A;
    stPfcAdc.stVgInv.ftValLpf10kHz_A    = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_A;
    stPfcAdc.stVgInv.ftValLpf10kHz_B    = stPfcAdcLoc.stPrmExt.stVgInv.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N;
    stPfcAdc.stVbus.ftValLpf10kHz_A     = stPfcAdcLoc.stPrmExt.stVbus.ftValLpf10kHz_A;
    stPfcAdc.stVbusPos.ftValLpf10kHz_A  = stPfcAdcLoc.stPrmExt.stVbusPos.ftValLpf10kHz_A;
    stPfcAdc.stVbusNeg.ftValLpf10kHz_A  = stPfcAdcLoc.stPrmExt.stVbusNeg.ftValLpf10kHz_A;
#elif(3U == GRID_PHASE_NUMBER)
    stPfcAdc.stVg.ftVal_A               = stPfcAdcLoc.stPrmExt.stVg.ftVal_A;
    stPfcAdc.stVg.ftVal_B               = stPfcAdcLoc.stPrmExt.stVg.ftVal_B;
    stPfcAdc.stVg.ftVal_C               = stPfcAdcLoc.stPrmExt.stVg.ftVal_C;
    stPfcAdc.stIg.ftVal_A               = stPfcAdcLoc.stPrmExt.stIg.ftVal_A;
    stPfcAdc.stIg.ftVal_B               = stPfcAdcLoc.stPrmExt.stIg.ftVal_B;
    stPfcAdc.stIg.ftVal_C               = stPfcAdcLoc.stPrmExt.stIg.ftVal_C;
    stPfcAdc.stIg.ftVal_N               = stPfcAdcLoc.stPrmExt.stIg.ftVal_N;
    stPfcAdc.stVgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_A;
    stPfcAdc.stVgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_B;
    stPfcAdc.stVgDc.ftVal_C             = stPfcAdcLoc.stPrmExt.stVgDc.ftVal_C;
    stPfcAdc.stIgDc.ftVal_A             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_A;
    stPfcAdc.stIgDc.ftVal_B             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_B;
    stPfcAdc.stIgDc.ftVal_C             = stPfcAdcLoc.stPrmExt.stIgDc.ftVal_C;
    stPfcAdc.stVg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_A;
    stPfcAdc.stVg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_B;
    stPfcAdc.stVg.ftValLpf10kHz_C       = stPfcAdcLoc.stPrmExt.stVg.ftValLpf10kHz_C;
//    stPfcAdc.stVgLine.ftValLpf10kHz_A   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_A;
//    stPfcAdc.stVgLine.ftValLpf10kHz_B   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_B;
//    stPfcAdc.stVgLine.ftValLpf10kHz_C   = stPfcAdcLoc.stPrmExt.stVgLine.ftValLpf10kHz_C;
    stPfcAdc.stIg.ftValLpf10kHz_A       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_A;
    stPfcAdc.stIg.ftValLpf10kHz_B       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_B;
    stPfcAdc.stIg.ftValLpf10kHz_C       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_C;
//    stPfcAdc.stIg.ftValLpf10kHz_N       = stPfcAdcLoc.stPrmExt.stIg.ftValLpf10kHz_N;
    stPfcAdc.ftVbusCellAvg              = stPfcAdcLoc.stPrmExt.ftVbusCellAvg;

#endif
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr)
    {
        printf("****SWIT DynamicTest: function v_PfcAdc_Isr() is running****\r\n");
    }
#endif
}

#pragma CODE_SECTION(v_PfcAdc_1ms, ".TI.ramfunc");
void v_PfcAdc_1ms(void)
{
    Uint16 i = 0U;
    /* Cell Bus voltage */
    for(i = 0;i < NUM_PHA_POW_CELL;i++)
    {
#ifndef _SIMULATION_NO_DSP_
        stPfcAdcLoc.stPrmExt.ftVbusPosCell[0][i] =  (float32)stEmifDma1.siVbusUpA[i] * COEFF_AD_VBUSPOS;
        stPfcAdcLoc.stPrmExt.ftVbusPosCell[1][i] =  (float32)stEmifDma1.siVbusUpB[i] * COEFF_AD_VBUSPOS;
        stPfcAdcLoc.stPrmExt.ftVbusPosCell[2][i] =  (float32)stEmifDma1.siVbusUpC[i] * COEFF_AD_VBUSPOS;
        stPfcAdcLoc.stPrmExt.ftVbusNegCell[0][i] =  (float32)stEmifDma1.siVbusDnA[i] * COEFF_AD_VBUSNEG;
        stPfcAdcLoc.stPrmExt.ftVbusNegCell[1][i] =  (float32)stEmifDma1.siVbusDnB[i] * COEFF_AD_VBUSNEG;
        stPfcAdcLoc.stPrmExt.ftVbusNegCell[2][i] =  (float32)stEmifDma1.siVbusDnC[i] * COEFF_AD_VBUSNEG;
#endif
        stPfcAdcLoc.stPrmExt.ftVbusCell[0][i]    = stPfcAdcLoc.stPrmExt.ftVbusPosCell[0][i] + \
                                                   stPfcAdcLoc.stPrmExt.ftVbusNegCell[0][i];
        stPfcAdcLoc.stPrmExt.ftVbusCell[1][i]    = stPfcAdcLoc.stPrmExt.ftVbusPosCell[1][i] + \
                                                   stPfcAdcLoc.stPrmExt.ftVbusNegCell[1][i];
        stPfcAdcLoc.stPrmExt.ftVbusCell[2][i]    = stPfcAdcLoc.stPrmExt.ftVbusPosCell[2][i] + \
                                                   stPfcAdcLoc.stPrmExt.ftVbusNegCell[2][i];

    }
    /* Cell Bus average voltage */

    /* Cell Bus voltage */
    for(i = 0;i < NUM_PHA_POW_CELL;i++)
    {
        stPfcAdc.ftVbusPosCell[0][i] =  stPfcAdcLoc.stPrmExt.ftVbusPosCell[0][i];
        stPfcAdc.ftVbusPosCell[1][i] =  stPfcAdcLoc.stPrmExt.ftVbusPosCell[1][i];
        stPfcAdc.ftVbusPosCell[2][i] =  stPfcAdcLoc.stPrmExt.ftVbusPosCell[2][i];
        stPfcAdc.ftVbusNegCell[0][i] =  stPfcAdcLoc.stPrmExt.ftVbusNegCell[0][i];
        stPfcAdc.ftVbusNegCell[1][i] =  stPfcAdcLoc.stPrmExt.ftVbusNegCell[1][i];
        stPfcAdc.ftVbusNegCell[2][i] =  stPfcAdcLoc.stPrmExt.ftVbusNegCell[2][i];
        stPfcAdc.ftVbusCell[0][i]    =  stPfcAdcLoc.stPrmExt.ftVbusCell[0][i];
        stPfcAdc.ftVbusCell[1][i]    =  stPfcAdcLoc.stPrmExt.ftVbusCell[1][i] ;
        stPfcAdc.ftVbusCell[2][i]    =  stPfcAdcLoc.stPrmExt.ftVbusCell[2][i];
    }

}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
