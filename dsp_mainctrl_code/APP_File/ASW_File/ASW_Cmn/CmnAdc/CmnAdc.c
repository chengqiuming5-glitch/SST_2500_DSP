//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnAdc.c
 * @brief
 * The source file of common Adc is designed to realize common signals sample.
 *
 * Module      :                       \n
 * CmnAdc
 *
 * Module Task :                       \n
 * v_CmnAdc_Init()                     \n
 * v_CmnAdc_1ms()                      \n
 * v_CmnAdc_100ms()                    \n
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
#include "CmnAdc.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_CMN_ADC stCmnAdc;                  ///< Common ADC global struct

#if (1U == CMN_ADC_DBG)
ST_CMN_ADC stCmnAdcDbg;               ///< Common ADC debug global struct
#endif

static ST_CMN_ADC_LOC stCmnAdcLoc;    ///< Common ADC local struct

static int16 siAirTempAdTbl[AIR_Temp_TBL_CNT] =
{
 141,   144,   147,   150,   154,   157,   161,   165,   169,   173,
 177,   182,   187,   192,   197,   203,   209,   215,   221,   228,
 234,   242,   249,   257,   265,   273,   282,   291,   300,   309,
 319,   330,   340,   351,   363,   374,   386,   399,   412,   425,
 439,   453,   468,   483,   498,   514,   530,   547,   564,   582,
 600,   618,   637,   657,   677,   697,   718,   740,   761,   784,
 806,   830,   853,   877,   902,   927,   952,   978,  1004,  1030,
1057,  1085,  1112,  1140,  1168,  1197,  1226,  1255,  1284,  1314,
1344,  1374,  1404,  1435,  1465,  1496,  1527,  1558,  1589,  1620,
1651,  1683,  1714,  1745,  1777,  1808,  1839,  1871,  1902,  1933,
1964,  1995,  2025,  2056,  2086,  2117,  2147,  2177,  2207,  2236,
2265,  2294,  2324,  2352,  2381,  2409,  2437,  2464,  2492,  2519,
2546,  2572,  2598,  2624,  2650,  2675,  2700,  2724,  2749,  2772,
2796,  2814,  2843,  2865,  2887,  2910,  2931,  2952,  2974,  2994,
3015,  3035,  3054,  3074,  3092,  3111,  3129,  3148,  3165,  3183,
3199,  3216,  3232,  3248,  3264,  3280,  3295,  3310,  3325,  3338,
3352,  3366,  3379,  3392,  3405,  3417,
};

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Common ADC initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnAdc_Init(void)
{
    /* Local Signal*/
//    stCmnAdcLoc.ftADDspBdTemp = 0.0f;
    stCmnAdcLoc.uiFlgAdcChSel = 0U;

    stCmnAdcLoc.stPrmExt.ftTempDspCore           = 0.0f;
    stCmnAdcLoc.stPrmExt.ftTempDspBd             = 0.0f;
    stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times = 0;       ///< Initialize to 0
    stCmnAdcLoc.stPrmExt.stAux12V.uiErr1000Times = 0U;      ///< Initialize to 0
    stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times = 0;       ///< Initialize to 0
    stCmnAdcLoc.stPrmExt.stAux1V5.uiErr1000Times = 0U;      ///< Initialize to 0
	
#if(3U == GRID_PHASE_NUMBER)
	AD_SW_TEMP;                                             ///< switch to DSP board temperature sample AD
#endif
    /* Global Signal*/
#if (1U == CMN_ADC_DBG)
    stCmnAdcDbg.ftTempDspCore           = stCmnAdcLoc.stPrmExt.ftTempDspCore;
    stCmnAdcDbg.ftTempDspBd             = stCmnAdcLoc.stPrmExt.ftTempDspBd;
    stCmnAdcDbg.stAux12V.siVal1000Times = stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times;
    stCmnAdcDbg.stAux12V.uiErr1000Times = stCmnAdcLoc.stPrmExt.stAux12V.uiErr1000Times;
    stPfcAdcDbg.stAux1V5.siVal1000Times = stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times;
    stCmnAdcDbg.stAux1V5.uiErr1000Times = stCmnAdcLoc.stPrmExt.stAux1V5.uiErr1000Times;

    stCmnAdc.ftTempDspCore              = stCmnAdcDbg.ftTempDspCore;
    stCmnAdc.ftTempDspBd                = stCmnAdcDbg.ftTempDspBd;
    stCmnAdc.stAux12V.siVal1000Times    = stCmnAdcDbg.stAux12V.siVal1000Times;
    stCmnAdc.stAux12V.uiErr1000Times    = stCmnAdcDbg.stAux12V.uiErr1000Times;
    stCmnAdc.stAux1V5.siVal1000Times    = stCmnAdcDbg.stAux1V5.siVal1000Times;
    stCmnAdc.stAux1V5.uiErr1000Times    = stCmnAdcDbg.stAux1V5.uiErr1000Times;
#else
    stCmnAdc.ftTempDspCore           	= stCmnAdcLoc.stPrmExt.ftTempDspCore;
    stCmnAdc.ftTempDspBd             	= stCmnAdcLoc.stPrmExt.ftTempDspBd;
    stCmnAdc.stAux12V.siVal1000Times 	= stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times;
    stCmnAdc.stAux12V.uiErr1000Times 	= stCmnAdcLoc.stPrmExt.stAux12V.uiErr1000Times;
    stCmnAdc.stAux1V5.siVal1000Times 	= stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times;
    stCmnAdc.stAux1V5.uiErr1000Times 	= stCmnAdcLoc.stPrmExt.stAux1V5.uiErr1000Times;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_CmnAdc_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Common ADC 1ms task: Temperature LPF
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnAdc_1ms(void)
{
    v_CmnAdc_Aux1V5_1ms();

#ifndef SST_1250kW
    if(0U == stCmnAdcLoc.uiFlgAdcChSel)
    {
        /* Temperature AD 1ms LPF */
        v_CmnAdc_TempADLpf_1ms();

        /* switch to 1V5 reference sample AD */
        stCmnAdcLoc.uiFlgAdcChSel = 1U;
        AD_SW_P1V5;
    }
    else if(1U == stCmnAdcLoc.uiFlgAdcChSel)
    {
        /* Aux 1V5 1ms AD/LPF */
        v_CmnAdc_Aux1V5_1ms();

        /* switch to 12V auxiliary power sample AD */
        stCmnAdcLoc.uiFlgAdcChSel = 2U;
        AD_SW_P12V;
    }
    else if(2U == stCmnAdcLoc.uiFlgAdcChSel)
    {
        /* Aux 12V 1ms AD/LPF */
        v_CmnAdc_Aux12V_1ms();

        /* switch to DSP board temperature sample AD */
        stCmnAdcLoc.uiFlgAdcChSel = 0U;
        AD_SW_TEMP;
    }
    else
    {
        ///< Do nothing
    }
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_CmnAdc_1ms() is running****\r\n");
    }
#endif

}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnAdc_100ms(void)
{
#ifndef  _SIMULATION_NO_DSP_
#if(0U == FLG_SWUT_EN)
#ifndef SST_1250kW
    stCmnAdcLoc.stPrmExt.ftTempDspCore = (float32)GetTemperatureC((int16)stAdcDrv.uiADDspCoreTemp);
#endif
#endif
    stCmnAdcLoc.stPrmExt.ftTempDspBd   = ft_CmnAdc_TempTblLU((int16)stCmnAdcLoc.ftADDspBdTemp, &siAirTempAdTbl[0], AIR_Temp_TBL_CNT, AIR_Temp_TBL_BIAS);
#endif

    /* Output Signal*/
#if (1U == CMN_ADC_DBG)
    stCmnAdc.ftTempDspCore     = stCmnAdcDbg.ftTempDspCore;
    stCmnAdc.ftTempDspBd       = stCmnAdcDbg.ftTempDspBd;
#else
    stCmnAdc.ftTempDspCore     = stCmnAdcLoc.stPrmExt.ftTempDspCore;
    stCmnAdc.ftTempDspBd       = stCmnAdcLoc.stPrmExt.ftTempDspBd;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_CmnAdc_100ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Temperature AD 1ms LPF function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnAdc_TempADLpf_1ms(void)
{
#ifndef SST_1250kW
    float32 l_ftADTmp = 0.0f;

    /* DSP board temperature */
    l_ftADTmp = (float32)stAdcDrv.uiADDspBdTemp;
    vFcn_1stOrdLPF(&stCmnAdcLoc.ftADDspBdTemp, l_ftADTmp, COEFF_LPF_1HZ_3MS);
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Common ADC 1ms task: Aux-power 12V detection
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnAdc_Aux12V_1ms(void)
{
#ifndef SST_1250kW
    int16  l_siADAux12V = 0;
    int16  l_siADAux12V1000Times = 0;
    float32 l_ftValAux12V = 0.0f;
    static float32 sl_ftValAux12VLpf = 12.0f * COEFF_AUX_ARM;

#ifndef _SIMULATION_NO_DSP_
    l_siADAux12V  = (int16)stAdcDrv.uiADAux12V - AD_BIAS_AUX_12V;
    l_ftValAux12V = (float32)(l_siADAux12V) * COEFF_AUX_12V_AD * COEFF_AUX_ARM;
    vFcn_1stOrdLPF(&sl_ftValAux12VLpf, l_ftValAux12V, COEFF_LPF_1HZ_3MS);          ///< 12V value 1000 times Lpf
    stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times = (int16)sl_ftValAux12VLpf;
#endif
    l_siADAux12V1000Times = stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times - AUX_12V_1000TIMES;
    stCmnAdcLoc.stPrmExt.stAux12V.uiErr1000Times = ABS_INT(l_siADAux12V1000Times);

    /* Global Signal*/
#if (1U == CMN_ADC_DBG)
    stCmnAdc.stAux12V.siVal1000Times = stPfcAdcDbg.stAux12V.siVal1000Times;
    stCmnAdc.stAux12V.uiErr1000Times = stPfcAdcDbg.stAux12V.uiErr1000Times;
#else
    stCmnAdc.stAux12V.siVal1000Times = stCmnAdcLoc.stPrmExt.stAux12V.siVal1000Times;
    stCmnAdc.stAux12V.uiErr1000Times = stCmnAdcLoc.stPrmExt.stAux12V.uiErr1000Times;
#endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Common ADC 1ms task: Aux-power 1V5 detection
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnAdc_Aux1V5_1ms(void)
{
    int16  l_siADAux1V5 = 0;
    int16  l_siADAux1V51000Times = 0;
    float32 l_ftValAux1V5 = 0.0f;
    static float32 sl_ftValAux1V5Lpf = 1.5f * COEFF_AUX_ARM;

#ifndef _SIMULATION_NO_DSP_
    l_siADAux1V5  = (int16)stAdcDrv.uiADAux1V5 - AD_BIAS_AUX_1V5;
    l_ftValAux1V5 = (float32)(l_siADAux1V5) * COEFF_AUX_1V5_AD * COEFF_AUX_ARM;
    vFcn_1stOrdLPF(&sl_ftValAux1V5Lpf, l_ftValAux1V5, COEFF_LPF_1HZ_1MS);         ///< 1V5 value 1000 times Lpf
    stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times = (int16)sl_ftValAux1V5Lpf;
#endif
    l_siADAux1V51000Times = stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times - AUX_1V5_1000TIMES;
    stCmnAdcLoc.stPrmExt.stAux1V5.uiErr1000Times = ABS_INT(l_siADAux1V51000Times);

    /* Global Signal*/
#if (1U == CMN_ADC_DBG)
    stCmnAdc.stAux1V5.siVal1000Times = stPfcAdcDbg.stAux1V5.siVal1000Times;
    stCmnAdc.stAux1V5.uiErr1000Times = stPfcAdcDbg.stAux1V5.uiErr1000Times;
#else
    stCmnAdc.stAux1V5.siVal1000Times = stCmnAdcLoc.stPrmExt.stAux1V5.siVal1000Times;
    stCmnAdc.stAux1V5.uiErr1000Times = stCmnAdcLoc.stPrmExt.stAux1V5.uiErr1000Times;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Temperature Table Look-Up function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static float32 ft_CmnAdc_TempTblLU(int16 siTempAD, int16 *sipTable, Uint16 uiTblCnt, int16 siTempBias)
{
    int16   l_siHigh = 0;       ///< High location
    int16   l_siLow  = 0;       ///< Low location
    int16   i = 0;
    float32 l_ftTemp = 0.0f;    ///< Temperature
    int16   l_siTmp  = 0;
    int16   l_siTmp1 = 0;
    Uint16  l_uiTmp  = 0U;
    float32 l_ftTmp  = 0.0f;

    l_siHigh = (int16)uiTblCnt - 1;
    l_siLow  = 0;

    l_uiTmp = uiTblCnt>>1;
    i = (int16)l_uiTmp;

    if(siTempAD >= *sipTable)
    {
        while(l_siHigh - l_siLow > 1)
        {
            if(siTempAD < *(sipTable + i))    ///< AD result is less than current value
            {
                l_siHigh = i;
            }
            else if(siTempAD > *(sipTable + i))    ///< AD result is more than current value
            {
                l_siLow = i;
            }
            else    ///< AD result is equal to current value
            {
                l_siHigh = i;
                l_siLow  = i;
            }

            l_uiTmp = ((Uint16)l_siHigh + (Uint16)l_siLow)>>1;
            i = (int16)l_uiTmp;
        }

        /* Interpolation method */
        if(siTempAD <= *(sipTable + l_siLow))
        {
            l_siTmp = l_siLow + siTempBias;
            l_ftTemp = (float32)l_siTmp;
        }
        else if(siTempAD >= *(sipTable + l_siHigh))
        {
            l_siTmp = l_siHigh + siTempBias;
            l_ftTemp = (float32)l_siTmp;
        }
        else
        {
            l_siTmp = *(sipTable + l_siLow) - siTempAD;
            l_siTmp1 = *(sipTable + l_siLow) - *(sipTable + l_siHigh);
            l_ftTmp = (float32)l_siTmp / (float32)l_siTmp1;
            l_ftTemp = (float32)l_siLow + (float32)siTempBias + l_ftTmp;
        }
    }
    else        ///< Exceed the minimum temperature range
    {
        l_ftTemp = (float32)AIR_Temp_TBL_BIAS - 0.1f;
    }

    return l_ftTemp;
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

