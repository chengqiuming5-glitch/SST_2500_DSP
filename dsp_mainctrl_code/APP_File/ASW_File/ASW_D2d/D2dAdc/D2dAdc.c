//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dAdc.c
 * @brief
 * The source file of D2d ADC is designed to realize various related sampling.
 *
 * Module      :                       \n
 * D2dAdc                              \n
 *
 * Unit        :                       \n
 * PrmUpd                              \n
 * Ramp                                \n
 * FrqJit                              \n
 *
 * Module Task :                       \n
 * v_D2dAdc_Init()                     \n
 * v_D2dAdc_1ms()                      \n
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
#include "D2dAdc.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_D2D_ADC stD2dAdc;                            ///< D2D ADC global struct

#if (1U == D2D_ADC_DBG)
ST_D2D_ADC stD2dAdcDbg;                         ///< D2D ADC debug global struct
#endif /* 1U == D2D_ADC_DBG */

static ST_D2D_ADC_LOC stD2dAdcLoc;              ///< D2D ADC local struct
//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        D2D ADC initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dAdc_Init(void)
{
    /* Local Signal*/
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf5kHz       = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf100Hz      = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf100HzEquiv = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf10Hz       = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf10HzEquiv  = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattUpLpf10Hz     = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftVoltBattDwnLpf10Hz    = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftCurrBattLpf5kHz       = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftCurrBattLpf10Hz       = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftCurrBattUpLpf10Hz     = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftCurrBattDwnLpf10Hz    = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.stPrmExt.ftCurrBattComp          = 0.0f;    ///< Initialize to 0
	stD2dAdcLoc.uiCntrComp                       = 0U;      ///< Initialize to 0
    /* Global Signal*/
#if (1U == D2D_ADC_DBG)
	stD2dAdcDbg.ftVoltBattLpf5kHz       = stD2dAdcLoc.stPrmExt.ftVoltBattLpf5kHz;          ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattLpf100Hz      = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100Hz;         ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattLpf100HzEquiv = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100HzEquiv;    ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattLpf10Hz       = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10Hz;          ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattLpf10HzEquiv  = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10HzEquiv;     ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattUpLpf10Hz     = stD2dAdcLoc.stPrmExt.ftVoltBattUpLpf10Hz;        ///< Initialize to 0
	stD2dAdcDbg.ftVoltBattDwnLpf10Hz    = stD2dAdcLoc.stPrmExt.ftVoltBattDwnLpf10Hz;       ///< Initialize to 0
	stD2dAdcDbg.ftCurrBattLpf5kHz       = stD2dAdcLoc.stPrmExt.ftCurrBattLpf5kHz;          ///< Initialize to 0
	stD2dAdcDbg.ftCurrBattLpf10Hz       = stD2dAdcLoc.stPrmExt.ftCurrBattLpf10Hz;          ///< Initialize to 0
	stD2dAdcDbg.ftCurrBattUpLpf10Hz     = stD2dAdcLoc.stPrmExt.ftCurrBattUpLpf10Hz;        ///< Initialize to 0
	stD2dAdcDbg.ftCurrBattDwnLpf10Hz    = stD2dAdcLoc.stPrmExt.ftCurrBattDwnLpf10Hz;       ///< Initialize to 0
    stD2dAdcDbg.ftCurrBattComp          = stD2dAdcLoc.stPrmExt.ftCurrBattComp;             ///< Initialize to 0

	stD2dAdc.ftVoltBattLpf5kHz          = stD2dAdcDbg.ftVoltBattLpf5kHz;                   ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf100Hz         = stD2dAdcDbg.ftVoltBattLpf100Hz;                  ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf100HzEquiv    = stD2dAdcDbg.ftVoltBattLpf100HzEquiv;             ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf10Hz          = stD2dAdcDbg.ftVoltBattLpf10Hz;                   ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf10HzEquiv     = stD2dAdcDbg.ftVoltBattLpf10HzEquiv;              ///< Initialize to 0
	stD2dAdc.ftVoltBattUpLpf10Hz        = stD2dAdcDbg.ftVoltBattUpLpf10Hz;                 ///< Initialize to 0
	stD2dAdc.ftVoltBattDwnLpf10Hz       = stD2dAdcDbg.ftVoltBattDwnLpf10Hz;                ///< Initialize to 0
	stD2dAdc.ftCurrBattLpf5kHz          = stD2dAdcDbg.ftCurrBattLpf5kHz;                   ///< Initialize to 0
	stD2dAdc.ftCurrBattLpf10Hz          = stD2dAdcDbg.ftCurrBattLpf10Hz;                   ///< Initialize to 0
	stD2dAdc.ftCurrBattUpLpf10Hz        = stD2dAdcDbg.ftCurrBattUpLpf10Hz;                 ///< Initialize to 0
	stD2dAdc.ftCurrBattDwnLpf10Hz       = stD2dAdcDbg.ftCurrBattDwnLpf10Hz;                ///< Initialize to 0
    stD2dAdc.ftCurrBattComp             = stD2dAdcDbg.ftCurrBattComp;                      ///< Initialize to 0
#else
	stD2dAdc.ftVoltBattLpf5kHz          = stD2dAdcLoc.stPrmExt.ftVoltBattLpf5kHz;          ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf100Hz         = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100Hz;         ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf100HzEquiv    = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100HzEquiv;    ///< Initialize to 0
    stD2dAdc.ftVoltBattLpf10Hz          = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10Hz;          ///< Initialize to 0
	stD2dAdc.ftVoltBattLpf10HzEquiv     = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10HzEquiv;     ///< Initialize to 0
    stD2dAdc.ftVoltBattUpLpf10Hz        = stD2dAdcLoc.stPrmExt.ftVoltBattUpLpf10Hz;        ///< Initialize to 0
	stD2dAdc.ftVoltBattDwnLpf10Hz       = stD2dAdcLoc.stPrmExt.ftVoltBattDwnLpf10Hz;       ///< Initialize to 0
    stD2dAdc.ftCurrBattLpf5kHz          = stD2dAdcLoc.stPrmExt.ftCurrBattLpf5kHz;          ///< Initialize to 0
	stD2dAdc.ftCurrBattLpf10Hz          = stD2dAdcLoc.stPrmExt.ftCurrBattLpf10Hz;          ///< Initialize to 0
    stD2dAdc.ftCurrBattUpLpf10Hz        = stD2dAdcLoc.stPrmExt.ftCurrBattUpLpf10Hz;        ///< Initialize to 0
	stD2dAdc.ftCurrBattDwnLpf10Hz       = stD2dAdcLoc.stPrmExt.ftCurrBattDwnLpf10Hz;       ///< Initialize to 0
    stD2dAdc.ftCurrBattComp             = stD2dAdcLoc.stPrmExt.ftCurrBattComp;             ///< Initialize to 0
#endif /* D2D_ADC_DBG */

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_D2dAdc_Init() is running****\r\n");
#endif /* 1U == FLG_SWIT_EN */
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D ADC 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dAdc_1ms(void)
{
    Uint16 i = 0U;
    float32 l_ftVoltCellBusSumA = 0.0f;
    float32 l_ftVoltCellBusSumB = 0.0f;
    float32 l_ftVoltCellBusSumC = 0.0f;
#if 1U == GRID_PHASE_NUMBER
    if(++stD2dAdcLoc.uiCntrComp >= 100U)       ///< 100ms period
    {
        stD2dAdcLoc.uiCntrComp = 0U;
        v_D2dAdc_CurrBattComp();
    }
#endif /* 1U == GRID_PHASE_NUMBER */
#if 1U == FLG_D2D_POWCTRL_EN
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf5kHz       = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattLpf5kHz;          ///< Battery voltage 5kHz LPF
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf100Hz      = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattLpf100Hz;         ///< Battery voltage 100Hz LPF
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf100HzEquiv = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattLpf100HzEquiv;    ///< Battery voltage 100Hz equivalent
    stD2dAdcLoc.stPrmExt.ftVoltBattLpf10Hz       = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattLpf10Hz;          ///< Battery voltage 10Hz LPF
	stD2dAdcLoc.stPrmExt.ftVoltBattLpf10HzEquiv  = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattLpf10HzEquiv;     ///< Battery voltage 10Hz equivalent
    stD2dAdcLoc.stPrmExt.ftVoltBattUpLpf10Hz     = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattUpLpf10Hz;        ///< Battery voltage Up 10Hz LPF
	stD2dAdcLoc.stPrmExt.ftVoltBattDwnLpf10Hz    = stD2dPowCtrlClaToCpu.stAdc.ftVoltBattDwnLpf10Hz;       ///< Battery voltage down 10Hz LPF
    stD2dAdcLoc.stPrmExt.ftCurrBattLpf5kHz       = stD2dPowCtrlClaToCpu.stAdc.ftCurrBattLpf5kHz;          ///< Battery current 5kHz LPF
	stD2dAdcLoc.stPrmExt.ftCurrBattLpf10Hz       = stD2dPowCtrlClaToCpu.stAdc.ftCurrBattLpf10Hz;          ///< Battery current 10Hz LPF
    stD2dAdcLoc.stPrmExt.ftCurrBattUpLpf10Hz     = stD2dPowCtrlClaToCpu.stAdc.ftCurrBattUpLpf10Hz;        ///< Battery current Up 10Hz LPF
	stD2dAdcLoc.stPrmExt.ftCurrBattDwnLpf10Hz    = stD2dPowCtrlClaToCpu.stAdc.ftCurrBattDwnLpf10Hz;       ///< Battery current down 10Hz LPF
#endif
	for(i = 0;i < NUM_PHA_POW_CELL;i++)
	{
	    l_ftVoltCellBusSumA += stPfcAdc.ftVbusCell[0][i];    ///< Phase A power cell bus voltage sum
	    l_ftVoltCellBusSumB += stPfcAdc.ftVbusCell[1][i];    ///< Phase B power cell bus voltage sum
	    l_ftVoltCellBusSumC += stPfcAdc.ftVbusCell[2][i];    ///< Phase C power cell bus voltage sum

	    stD2dAdcLoc.stPrmExt.ftVoltCellBatt[0][i] = (float32)stEmif.siVoltDabCell[0][i] * COEFF_AD_VBATT;
	    stD2dAdcLoc.stPrmExt.ftVoltCellBatt[1][i] = (float32)stEmif.siVoltDabCell[1][i] * COEFF_AD_VBATT;
	    stD2dAdcLoc.stPrmExt.ftVoltCellBatt[2][i] = (float32)stEmif.siVoltDabCell[2][i] * COEFF_AD_VBATT;
	    stD2dAdcLoc.stPrmExt.ftCurrCellBatt[0][i] = (float32)(stEmif.siCurrDabCell[0][i]-2048) * COEFF_AD_IBATT;
        stD2dAdcLoc.stPrmExt.ftCurrCellBatt[1][i] = (float32)(stEmif.siCurrDabCell[1][i]-2048) * COEFF_AD_IBATT;
        stD2dAdcLoc.stPrmExt.ftCurrCellBatt[2][i] = (float32)(stEmif.siCurrDabCell[2][i]-2048) * COEFF_AD_IBATT;

        stD2dAdc.ftVoltCellBatt[0][i]  = stD2dAdcLoc.stPrmExt.ftVoltCellBatt[0][i];
        stD2dAdc.ftVoltCellBatt[1][i]  = stD2dAdcLoc.stPrmExt.ftVoltCellBatt[1][i];
        stD2dAdc.ftVoltCellBatt[2][i]  = stD2dAdcLoc.stPrmExt.ftVoltCellBatt[2][i];
        stD2dAdc.ftCurrCellBatt[0][i]  = stD2dAdcLoc.stPrmExt.ftCurrCellBatt[0][i];
        stD2dAdc.ftCurrCellBatt[1][i]  = stD2dAdcLoc.stPrmExt.ftCurrCellBatt[1][i];
        stD2dAdc.ftCurrCellBatt[2][i]  = stD2dAdcLoc.stPrmExt.ftCurrCellBatt[2][i];
	}

    stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[0] = l_ftVoltCellBusSumA;
    stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[1] = l_ftVoltCellBusSumB;
    stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[2] = l_ftVoltCellBusSumC;
    /* Output Signal*/
#if (1U == D2D_ADC_DBG)
    stD2dAdc.ftVoltBattLpf5kHz          = stD2dAdcDbg.ftVoltBattLpf5kHz;
    stD2dAdc.ftVoltBattLpf100Hz         = stD2dAdcDbg.ftVoltBattLpf100Hz;
    stD2dAdc.ftVoltBattLpf100HzEquiv    = stD2dAdcDbg.ftVoltBattLpf100HzEquiv;
    stD2dAdc.ftVoltBattLpf10Hz          = stD2dAdcDbg.ftVoltBattLpf10Hz;
    stD2dAdc.ftVoltBattLpf10HzEquiv     = stD2dAdcDbg.ftVoltBattLpf10HzEquiv;
    stD2dAdc.ftVoltBattUpLpf10Hz        = stD2dAdcDbg.ftVoltBattUpLpf10Hz;
    stD2dAdc.ftVoltBattDwnLpf10Hz       = stD2dAdcDbg.ftVoltBattDwnLpf10Hz;
    stD2dAdc.ftCurrBattLpf5kHz          = stD2dAdcDbg.ftCurrBattLpf5kHz;
    stD2dAdc.ftCurrBattLpf10Hz          = stD2dAdcDbg.ftCurrBattLpf10Hz;
    stD2dAdc.ftCurrBattUpLpf10Hz        = stD2dAdcDbg.ftCurrBattUpLpf10Hz;
    stD2dAdc.ftCurrBattDwnLpf10Hz       = stD2dAdcDbg.ftCurrBattDwnLpf10Hz;
#else
    stD2dAdc.ftVoltBattLpf5kHz          = stD2dAdcLoc.stPrmExt.ftVoltBattLpf5kHz;
    stD2dAdc.ftVoltBattLpf100Hz         = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100Hz;
    stD2dAdc.ftVoltBattLpf100HzEquiv    = stD2dAdcLoc.stPrmExt.ftVoltBattLpf100HzEquiv;
    stD2dAdc.ftVoltBattLpf10Hz          = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10Hz;
    stD2dAdc.ftVoltBattLpf10HzEquiv     = stD2dAdcLoc.stPrmExt.ftVoltBattLpf10HzEquiv;
    stD2dAdc.ftVoltBattUpLpf10Hz        = stD2dAdcLoc.stPrmExt.ftVoltBattUpLpf10Hz;
    stD2dAdc.ftVoltBattDwnLpf10Hz       = stD2dAdcLoc.stPrmExt.ftVoltBattDwnLpf10Hz;
    stD2dAdc.ftCurrBattLpf5kHz          = stD2dAdcLoc.stPrmExt.ftCurrBattLpf5kHz;
    stD2dAdc.ftCurrBattLpf10Hz          = stD2dAdcLoc.stPrmExt.ftCurrBattLpf10Hz;
    stD2dAdc.ftCurrBattUpLpf10Hz        = stD2dAdcLoc.stPrmExt.ftCurrBattUpLpf10Hz;
    stD2dAdc.ftCurrBattDwnLpf10Hz       = stD2dAdcLoc.stPrmExt.ftCurrBattDwnLpf10Hz;
    stD2dAdc.ftVoltCellBusSum[0]        = stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[0];
    stD2dAdc.ftVoltCellBusSum[1]        = stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[1];
    stD2dAdc.ftVoltCellBusSum[2]        = stD2dAdcLoc.stPrmExt.ftVoltCellBusSum[2];

#endif /* D2D_ADC_DBG */

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_D2dAdc_1ms() is running****\r\n");
    }
#endif /* 1U == FLG_SWIT_EN */
}
/********************************************End***********************************************/

#if 1U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Battery Current compensation by DSP board temperature
 * @param [in]   stCmnAdcLoc.stPrmExt.ftTempDspBd
 * @param [out]  stCmnAdcLoc.stPrmExt.ftCurrBattComp
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dAdc_CurrBattComp(void)
{
    if(stCmnAdc.ftTempDspBd < TEMP_LOW_CURR_BATT_COMP)
    {
        stD2dAdcLoc.stPrmExt.ftCurrBattComp = COEFF_K_CURR_BATT_COMP_LOW * stCmnAdc.ftTempDspBd + COEFF_B_CURR_BATT_COMP_LOW;       ///< Compensation in low temperature
    }
    else if(stCmnAdc.ftTempDspBd <= TEMP_HIGH_CURR_BATT_COMP)
    {
        stD2dAdcLoc.stPrmExt.ftCurrBattComp = 0.0f;      ///< No compensation
    }
    else
    {
        stD2dAdcLoc.stPrmExt.ftCurrBattComp = COEFF_K_CURR_BATT_COMP_HIGH * stCmnAdc.ftTempDspBd + COEFF_B_CURR_BATT_COMP_HIGH;     ///< Compensation in high temperature
    }

    vFcn_FtUpDwnLim(&stD2dAdcLoc.stPrmExt.ftCurrBattComp, 0.75f, -0.75f);    ///< Output limitation

    /* Output Signal*/
#if (1U == D2D_ADC_DBG)
    stD2dAdc.ftCurrBattComp = stD2dAdcDbg.ftCurrBattComp;
#else
    stD2dAdc.ftCurrBattComp = stD2dAdcLoc.stPrmExt.ftCurrBattComp;
#endif /* D2D_ADC_DBG */
}
/*********************************************End**********************************************/
#endif /* 1U == GRID_PHASE_NUMBER */

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
