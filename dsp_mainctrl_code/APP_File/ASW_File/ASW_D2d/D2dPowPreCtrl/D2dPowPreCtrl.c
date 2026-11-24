//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowPreCtrl.c
 * @brief
 * The source file of D2d power pre-control is designed to realize preparation for loop control.
 *
 * Module      :                       \n
 * D2dPowPreCtrl                       \n
 *
 * Unit        :                       \n
 * PrmUpd                              \n
 * Ramp                                \n
 * FrqJit                              \n
 *
 * Module Task :                       \n
 * v_D2dPowPreCtrl_Init()              \n
 * v_D2dPowPreCtrl_1ms()               \n
 *
 * Unit Task   :                       \n
 * v_D2dPowPreCtrl_PrmUpd_Init()       \n
 * v_D2dPowPreCtrl_PrmUpd_1ms()        \n
 *
 * v_D2dPowPreCtrl_Ramp_Init ()        \n
 * v_D2dPowPreCtrl_Ramp_1ms()          \n
 *
 * v_D2dPowPreCtrl_FrqJit_Init()       \n
 * v_D2dPowPreCtrl_FrqJit_1ms()
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
#include "D2dPowPreCtrl.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_D2D_POW_PRE_CTRL stD2dPowPreCtrl;                  ///< D2D power pre-control global struct

#if (1U == D2D_POW_PRE_CTRL_DBG)
ST_D2D_POW_PRE_CTRL stD2dPowPreCtrlDbg;               ///< D2D power pre-control debug global struct
#endif

static ST_D2D_POW_PRE_CTRL_LOC stD2dPowPreCtrlLoc;    ///< D2D power pre-control local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: D2D power pre-control in Init task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dPowPreCtrl_Init(void)
{
	v_D2dPowPreCtrl_RefRamp_Init();        ///< D2D power pre-control reference ramp calculation initial task
    v_D2dPowPreCtrl_PrmUpd_Init();         ///< D2D power pre-control parameter update initialization task
#if(3U == GRID_PHASE_NUMBER)
	v_D2dPowPreCtrl_FrqJit_Init();
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_D2dPowPreCtrl_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: D2D power pre-control in 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dPowPreCtrl_1ms(void)
{
	v_D2dPowPreCtrl_RefRamp_1ms();    ///< Reference ramp task
    v_D2dPowPreCtrl_PrmUpd_1ms();     ///< Parameter update task
#if(3U == GRID_PHASE_NUMBER)
	v_D2dPowPreCtrl_FrqJit_1ms();     ///< Frequency jitter task (sst no use)
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_D2dPowPreCtrl_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Parameter update in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dPowPreCtrl_ParlPrmUpd(void)
{
    stD2dPowPreCtrlLoc.ftVoltBattChrgStep       = VOLT_BATT_PARL_STEP;
    stD2dPowPreCtrlLoc.ftVoltBattBurstMax       = VOLT_BATT_BURST_PARL_MAX;
    stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst = CURR_BATT_BURST_PARL_MAX;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Parameter update in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dPowPreCtrl_SeriesPrmUpd(void)
{
    stD2dPowPreCtrlLoc.ftVoltBattChrgStep       = VOLT_BATT_SERIES_STEP;
    stD2dPowPreCtrlLoc.ftVoltBattBurstMax       = VOLT_BATT_BURST_SERIES_MAX;
    stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst = CURR_BATT_BURST_SERIES_MAX;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Parameter update in initial task
 * @param [in]   null
 * @param [out]  stD2dPowPreCtrl.ftVoltBattBurst
 * @param [out]  stD2dPowPreCtrl.ftCurrBattBurst
 * @param [out]  stD2dPowPreCtrl.ftVoltBusBurst
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_PrmUpd_Init(void)
{
    /* Local Signal*/
    stD2dPowPreCtrlLoc.ftVoltBattChrgStep       = VOLT_BATT_SERIES_STEP;
    stD2dPowPreCtrlLoc.ftVoltBattBurstMax       = VOLT_BATT_BURST_SERIES_MAX;
    stD2dPowPreCtrlLoc.ftVoltBattBurstDelta     = VOLT_BATT_BURST_DELTA_MAX;
    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattBurst = VOLT_BATT_BURST_SERIES_MAX;
    stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst = CURR_BATT_BURST_SERIES_MAX;
    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusBurst  = VOLT_BUS_D2D_BURST_MAX;

    /* Global Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrlDbg.ftVoltBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattBurst;
    stD2dPowPreCtrlDbg.ftCurrBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst;
    stD2dPowPreCtrlDbg.ftVoltBusBurst  = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusBurst;

    stD2dPowPreCtrl.ftVoltBattBurst = stD2dPowPreCtrlDbg.ftVoltBattBurst;
    stD2dPowPreCtrl.ftCurrBattBurst = stD2dPowPreCtrlDbg.ftCurrBattBurst;
    stD2dPowPreCtrl.ftVoltBusBurst  = stD2dPowPreCtrlDbg.ftVoltBusBurst;
#else
    stD2dPowPreCtrl.ftVoltBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattBurst;
    stD2dPowPreCtrl.ftCurrBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst;
    stD2dPowPreCtrl.ftVoltBusBurst  = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusBurst;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Parameter update in 1ms task
 * @param [in]   stPerphCtrl.uiStSPRly
 * @param [in]   stPowLim.ftVoltBattChrgLim
 * @param [out]  stD2dPowPreCtrl.ftVoltBattBurst
 * @param [out]  stD2dPowPreCtrl.ftCurrBattBurst
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_PrmUpd_1ms(void)
{
	float32 l_ftPrmTmp = 0.0f;

	/* Calculate the Battery burst voltage */
    stD2dPowPreCtrlLoc.ftVoltBattBurstDelta = stPowLim.ftVoltBattChrgLim * 0.05f;
    UP_LIMIT(stD2dPowPreCtrlLoc.ftVoltBattBurstDelta , VOLT_BATT_BURST_DELTA_MAX);
    l_ftPrmTmp = stPowLim.ftVoltBattChrgLim + stD2dPowPreCtrlLoc.ftVoltBattBurstDelta;
    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattBurst = ftFcn_MinOfTwo(l_ftPrmTmp, stD2dPowPreCtrlLoc.ftVoltBattBurstMax);
    /* Calculate the bus burst voltage */
    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusBurst = ftFcn_MinOfTwo((stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusRef + BURST_BUS_VOLT_DELTA), VOLT_BUS_BURST_MAX);
    if(stPowLim.ftVoltBusAcLim > stPowLim.ftVoltBusBattLim)
    {
        stD2dPowPreCtrlLoc.ftVoltBusStep = VOLT_BUS_D2D_FAST_STEP;
    }
    else
    {
        stD2dPowPreCtrlLoc.ftVoltBusStep = VOLT_BUS_D2D_SLOW_STEP;
    }
    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftVoltBattBurst = stD2dPowPreCtrlDbg.ftVoltBattBurst;
    stD2dPowPreCtrl.ftCurrBattBurst = stD2dPowPreCtrlDbg.ftCurrBattBurst;
    stD2dPowPreCtrl.ftVoltBusBurst  = stD2dPowPreCtrlDbg.ftVoltBusBurst;
#else
    stD2dPowPreCtrl.ftVoltBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattBurst;  ///< sst no use
    stD2dPowPreCtrl.ftCurrBattBurst = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattBurst;  ///< sst no use
    stD2dPowPreCtrl.ftVoltBusBurst  = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusBurst;  ///< sst no use
#endif

    stD2dPowPreCtrlLoc.ftPwmDutyTarget = stComTbl.stPrmToFpga.ftPwmDutyTarget * 2.0;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Reference ramp in init task
 * @param [in]   null
 * @param [out]  stD2dPowPreCtrl.ftVoltBattChrgRef
 * @param [out]  stD2dPowPreCtrl.ftCurrBattChrgRef
 * @param [out]  stD2dPowPreCtrl.ftVoltBusRef
 * @param [out]  stD2dPowPreCtrl.ftDp3OLRef
 * @param [out]  stD2dPowPreCtrl.ftOutpOLRef
 * @param [out]  stD2dPowPreCtrl.uiFlgRampDone
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_RefRamp_Init(void)
{
    /* Local Signal*/
    stD2dPowPreCtrlLoc.ftCurrBattChrgStep = CURR_BATT_STEP;
    stD2dPowPreCtrlLoc.ftVoltBusStep      = VOLT_BUS_D2D_SLOW_STEP;
    stD2dPowPreCtrlLoc.uiCntrBusVoltOk    = 0U;
    stD2dPowPreCtrlLoc.ftOutpOLStep       = STEP_D2D_OL;
    stD2dPowPreCtrlLoc.ftPwmDutyStep      = STEP_POW_CELL_PWM_DUTY;
    stD2dPowPreCtrlLoc.ftPwmDutyTarget    = LIM_POW_CELL_PWM_DUTY;

    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = 0.0f;
    stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef = CURR_BATT_TGT_MIN;
    stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusRef      = 0.0f;
    stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef       = 0.0f;
    stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone     = 0U;

#if(3U == GRID_PHASE_NUMBER)
	stD2dPowPreCtrlLoc.ftDp3OLStep        = STEP_D2D_OL;
	stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef  = 0.0f;                            ///< set 0.0f when initial
    stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone   = 0U;                         ///< set false when initial
#endif

    /* Global Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrlDbg.ftVoltBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef;
    stD2dPowPreCtrlDbg.ftCurrBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef;
    stD2dPowPreCtrlDbg.ftVoltBusRef      = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusRef;
    stD2dPowPreCtrlDbg.ftOutpOLRef       = stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef;
    stD2dPowPreCtrlDbg.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
    #if(3U == GRID_PHASE_NUMBER)
    stD2dPowPreCtrlDbg.ftDp3OLRef            = stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef;
	stD2dPowPreCtrlDbg.uiFlgDp3OLDone        = stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone;
    #endif

    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlDbg.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftCurrBattChrgRef = stD2dPowPreCtrlDbg.ftCurrBattChrgRef;
    stD2dPowPreCtrl.ftVoltBusRef      = stD2dPowPreCtrlDbg.ftVoltBusRef;
    stD2dPowPreCtrl.ftOutpOLRef       = stD2dPowPreCtrlDbg.ftOutpOLRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlDbg.uiFlgRampDone;
    #if(3U == GRID_PHASE_NUMBER)
    stD2dPowPreCtrl.ftDp3OLRef        = stD2dPowPreCtrlDbg.ftDp3OLRef;
    stD2dPowPreCtrl.uiFlgDp3OLDone    = stD2dPowPreCtrlDbg.uiFlgDp3OLDone;
    #endif
#else
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftCurrBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef;
    stD2dPowPreCtrl.ftVoltBusRef      = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBusRef;
    stD2dPowPreCtrl.ftOutpOLRef       = stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
    #if(3U == GRID_PHASE_NUMBER)
	stD2dPowPreCtrl.ftDp3OLRef        = stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef;
	stD2dPowPreCtrl.uiFlgDp3OLDone    = stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone;
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Reference ramp in 1ms task
 * @param [in]   stComIf.uiModD2dRun
 * @param [out]  stD2dPowPreCtrl.ftVoltBattChrgRef
 * @param [out]  stD2dPowPreCtrl.ftCurrBattChrgRef
 * @param [out]  stD2dPowPreCtrl.ftVoltBusRef
 * @param [out]  stD2dPowPreCtrl.ftDp3OLRef
 * @param [out]  stD2dPowPreCtrl.ftOutpOLRef
 * @param [out]  stD2dPowPreCtrl.uiFlgRampDone
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_RefRamp_1ms(void)
{
    switch(stComIf.uiModD2dRun)
    {
#if 1
        case CHG_ONGRID_MODE:
        	v_D2dPowPreCtrl_RefRamp_Chrg();
            break;
#else
        case CHG_ONGRID_MODE:
#endif

        case BIDIR_ONGRID_MODE:
        case OFFGRID_MODE:
        	v_D2dPowPreCtrl_RefRamp_Bidir();
            break;

        case OPENLOOP_MODE:
        	v_D2dPowPreCtrl_RefRamp_OL();
            break;

        default:
    		// Do nothing
            break;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Reference ramp in charge mode 1ms task
 * @param [in]   stD2dStMac.uiStD2dRun
 * @param [in]   stPowLim.ftVoltBattChrgLim
 * @param [in]   stPowLim.ftCurrBattChrgLim
 * @param [in]   stPowLim.ftCurrBattChrgLim
 * @param [in]   stD2dAdc.ftVoltBattLpf5kHz
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_RefRamp_Chrg(void)
{
#if 0
    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN)
    {
        /* Battery Voltage Reference Step */
        vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef, stPowLim.ftVoltBattChrgLim, stD2dPowPreCtrlLoc.ftVoltBattChrgStep);

        if(D2D_ST_MAC_SOFTSTRT == stD2dStMac.uiStD2dRun)
        {
            /* Consider CC mode, ftVoltBattChrgRef is always larger than actual voltage */
            if(fabsf(stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef - stPowLim.ftVoltBattChrgLim) < CON_ZERO_DELTA)
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;    ///< Ramp Flag
            }
            else
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;
            }
        }

        /* Battery Current Reference Step */
        vFcn_UnbidirRampDiffSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef, stPowLim.ftCurrBattChrgLim, stD2dPowPreCtrlLoc.ftCurrBattChrgStep, CURR_BATT_DWN_STEP);
    }
    else
    {
        /* Before startup, ftVoltBattChrgRef is sum of ftVoltBattLpf5kHz and 10.0f/0.0f*/
        stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = stD2dAdc.ftVoltBattLpf5kHz;
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;
        stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef = CURR_BATT_CHRG_REF_MIN;
    }

    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlDbg.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftCurrBattChrgRef = stD2dPowPreCtrlDbg.ftCurrBattChrgRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlDbg.uiFlgRampDone;
#else
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftCurrBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftCurrBattChrgRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
#endif
#else
    float32 l_ftVoltCellBusSumLim = 0.0f;

    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_SOFTSTRT)
    {
#ifndef _SIMULATION_NO_DSP_
        if(stComTbl.stPrmToFpga.uiHandControl == 0U)
        {
            l_ftVoltCellBusSumLim = 0.0f;
        }
        else
        {
            l_ftVoltCellBusSumLim = 10.0f; //stPfcDataCalc.stMeasParm.ftVgMaxRms * stComIf.ftCoeffBusPreChrg;
        }
#else
        l_ftVoltCellBusSumLim = 0.0f;
#endif
        /* Cell PWM duty Step*/
        vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty, stD2dPowPreCtrlLoc.ftPwmDutyTarget, stD2dPowPreCtrlLoc.ftPwmDutyStep);
        if(D2D_ST_MAC_SOFTSTRT == stD2dStMac.uiStD2dRun)
        {
            if(1U == stOnOffGridSwt.uiFlgSwt)    ///< On&off grid quickly switch
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
            }
            else if((stD2dAdc.ftVoltCellBusSum[0] > l_ftVoltCellBusSumLim) \
                    && (stD2dAdc.ftVoltCellBusSum[1] > l_ftVoltCellBusSumLim)\
                    && (stD2dAdc.ftVoltCellBusSum[2] > l_ftVoltCellBusSumLim)
                    && (stD2dPowPreCtrlLoc.ftPwmDutyTarget == stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty))
            {
                /* Increase robustness */
                stD2dPowPreCtrlLoc.uiCntrBusVoltOk++;
                if(stD2dPowPreCtrlLoc.uiCntrBusVoltOk >= DURN_BUS_VOLT_D2D_OK)    ///< Last 200ms
                {
                    stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
                }
            }
            else if(stD2dPowPreCtrlLoc.uiCntrBusVoltOk > 0U)
            {
                stD2dPowPreCtrlLoc.uiCntrBusVoltOk--;               ///< clear counter
            }
            else
            {
                ///< No code
            }
        }

        /* Battery Voltage Reference */
        stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = stPowLim.ftVoltBattChrgLim;
    }
    else
    {
        /* Before startup, ftVoltBusRef is stPfcPowCtrl.ftVbusNotch */
#if 1U == FLG_PFC_POWCTRL_EN
        stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty      = 0.0f;    ///< Duty Init to 0
#endif
        stD2dPowPreCtrlLoc.uiCntrBusVoltOk            = 0U;                                  ///< clear counter
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone     = 0U;                                  ///< Reset flag
        /* Battery Voltage Reference */
        stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = stD2dAdc.ftVoltBattLpf5kHz;
    }

    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlDbg.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftVoltBusRef      = stD2dPowPreCtrlDbg.ftVoltBusRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlDbg.uiFlgRampDone;
#else
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftOutpPwmDuty      = stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
#endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Reference ramp in bi-directional mode 1ms task
 * @param [in]   stD2dStMac.uiStD2dRun
 * @param [in]   stPowLim.ftVoltBusLim
 * @param [in]   stPfcPowCtrl.ftVbusNotch
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_RefRamp_Bidir(void)
{
    float32 l_ftVoltCellBusSumLim = 0.0f;

    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_SOFTSTRT)
    {
#ifndef _SIMULATION_NO_DSP_
        if(stComTbl.stPrmToFpga.uiHandControl == 0U)
        {
            l_ftVoltCellBusSumLim = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2;
        }
        else
        {
            l_ftVoltCellBusSumLim = -1.0f;
        }
#else
        l_ftVoltCellBusSumLim = 0.0f;
#endif
        /* Cell PWM duty Step*/
        vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty, stD2dPowPreCtrlLoc.ftPwmDutyTarget, stD2dPowPreCtrlLoc.ftPwmDutyStep);
        if(D2D_ST_MAC_SOFTSTRT == stD2dStMac.uiStD2dRun)
        {
            if(1U == stOnOffGridSwt.uiFlgSwt)    ///< On&off grid quickly switch
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
            }
            else if((stD2dAdc.ftVoltCellBusSum[0] > l_ftVoltCellBusSumLim) \
                    && (stD2dAdc.ftVoltCellBusSum[1] > l_ftVoltCellBusSumLim)\
                    && (stD2dAdc.ftVoltCellBusSum[2] > l_ftVoltCellBusSumLim)
                    && (stD2dPowPreCtrlLoc.ftPwmDutyTarget == stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty))
            {
				/* Increase robustness */
            	stD2dPowPreCtrlLoc.uiCntrBusVoltOk++;
            	if(stD2dPowPreCtrlLoc.uiCntrBusVoltOk >= DURN_BUS_VOLT_D2D_OK)    ///< Last 200ms
            	{
            		stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
            	}
            }
            else if(stD2dPowPreCtrlLoc.uiCntrBusVoltOk > 0U)
            {
            	stD2dPowPreCtrlLoc.uiCntrBusVoltOk--;			    ///< clear counter
            }
            else
            {
                ///< No code
            }
        }

        /* Battery Voltage Reference */
        stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = stPowLim.ftVoltBattChrgLim;
    }
    else
    {
		/* Before startup, ftVoltBusRef is stPfcPowCtrl.ftVbusNotch */
#if 1U == FLG_PFC_POWCTRL_EN
        stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty      = 0.0f;    ///< Duty Init to 0
#endif
        stD2dPowPreCtrlLoc.uiCntrBusVoltOk            = 0U;							         ///< clear counter
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone     = 0U;								     ///< Reset flag
		/* Battery Voltage Reference */
    	stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef = stD2dAdc.ftVoltBattLpf5kHz;
    }

    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlDbg.ftVoltBattChrgRef;
    stD2dPowPreCtrl.ftVoltBusRef      = stD2dPowPreCtrlDbg.ftVoltBusRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlDbg.uiFlgRampDone;
#else
    stD2dPowPreCtrl.ftVoltBattChrgRef = stD2dPowPreCtrlLoc.stPrmExt.ftVoltBattChrgRef; ///< sst no use
    stD2dPowPreCtrl.ftOutpPwmDuty      = stD2dPowPreCtrlLoc.stPrmExt.ftOutpPwmDuty;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Reference ramp in open-loop mode 1ms task
 * @param [in]   stD2dStMac.uiStD2dRun
 * @param [in]   stComIf.ftDs1OLReq
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowPreCtrl_RefRamp_OL(void)
{
#if (3U != GRID_PHASE_NUMBER)
    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN)
    {
        /* Open-loop output reference Step*/
        vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef, stComIf.ftOutpOLReq, stD2dPowPreCtrlLoc.ftOutpOLStep);

    	if(stD2dStMac.uiStD2dRun == D2D_ST_MAC_SOFTSTRT)
    	{
            if(fabsf(stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef - stComIf.ftOutpOLReq) < CON_ZERO_DELTA)
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
            }
            else
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;
            }
    	}
    	else
    	{
    		// Do nothing
    	}
    }
    else
    {
    	stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef   = 0.0f;
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;
    }
#else
    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN)
    {
        /* Open-loop DP3 reference Step*/
        vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef, DP3_D2D_DAB_MAX, stD2dPowPreCtrlLoc.ftDp3OLStep);
        if(stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef >= (DP3_D2D_DAB_MAX - CON_ZERO_DELTA))           ///< after DP3 ramp finished
        {
            stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone = 1U;
            /* Open-loop DS1 reference Step after DP3*/
            vFcn_RampSameSlope(&stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef, stComIf.ftOutpOLReq, stD2dPowPreCtrlLoc.ftOutpOLStep);
            if(fabsf(stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef - stComIf.ftOutpOLReq) < CON_ZERO_DELTA) ///< DS1 ramp finished
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 1U;
            }
            else
            {
                stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;                                      ///< Reset flag
            }
        }
    }
    else
    {
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone = 0U;
        stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef = 0.0f;                                              ///< Reset value
        stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef = 0.0f;                                             ///< Reset value
        stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone = 0U;                                             ///< Reset flag
    }
#endif

    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftOutpOLRef       = stD2dPowPreCtrlDbg.ftOutpOLRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlDbg.uiFlgRampDone;
    #if(3U == GRID_PHASE_NUMBER)
    stD2dPowPreCtrl.ftDp3OLRef        = stD2dPowPreCtrlDbg.ftDp3OLRef;
    stD2dPowPreCtrl.uiFlgDp3OLDone   = stD2dPowPreCtrlDbg.uiFlgDp3OLDone;
    #endif

#else
    stD2dPowPreCtrl.ftOutpOLRef       = stD2dPowPreCtrlLoc.stPrmExt.ftOutpOLRef;
    stD2dPowPreCtrl.uiFlgRampDone     = stD2dPowPreCtrlLoc.stPrmExt.uiFlgRampDone;
    #if(3U == GRID_PHASE_NUMBER)
    stD2dPowPreCtrl.ftDp3OLRef        = stD2dPowPreCtrlLoc.stPrmExt.ftDp3OLRef;
    stD2dPowPreCtrl.uiFlgDp3OLDone   = stD2dPowPreCtrlLoc.stPrmExt.uiFlgDp3OLDone;
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Frequency jitter in init task
 * @param [in]   null
 * @param [out]  stD2dPowPreCtrl.ftFrqJit
 * @return       null
 * @see          SWDD-xxxx
 */
#if(3U == GRID_PHASE_NUMBER)
static void v_D2dPowPreCtrl_FrqJit_Init(void)
{
    stD2dPowPreCtrlLoc.ftGainFrq       = 1.0f;
    stD2dPowPreCtrlLoc.ftGainFrqMax    = 1.0f;        //calculate max gain of frequency jitter
    stD2dPowPreCtrlLoc.ftGainFrqMin    = 1.0f;        //calculate min gain of frequency jitter
    stD2dPowPreCtrlLoc.ftGainFrqStep   = 0.0f;        //calculate step gain of frequency jitter
    stD2dPowPreCtrlLoc.uiFlgFrqJitDir  = 0U;
    stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit  = FRQ_D2D_DAB_DFT;

    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrlDbg.ftFrqJit = stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit;
    stD2dPowPreCtrl.ftFrqJit = stD2dPowPreCtrlDbg.ftFrqJit;
#else
    stD2dPowPreCtrl.ftFrqJit = stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit;
#endif
}
#endif
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Frequency jitter in 1ms task
 * @param [in]   null
 * @param [out]  stD2dPowPreCtrl.ftFrqJit
 * @return       null
 * @see          SWDD-xxxx
 */
#if(3U == GRID_PHASE_NUMBER)
static void v_D2dPowPreCtrl_FrqJit_1ms(void)
{
    if((FCN_ENABLE == stComTbl.stPrmD2dPowPreCtrl.uiFlgFrqJitEn) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun))
    {
        if(0U == stD2dPowPreCtrlLoc.uiFlgFrqJitDir)
        {
            //Gain increase
            stD2dPowPreCtrlLoc.ftGainFrq += stD2dPowPreCtrlLoc.ftGainFrqStep;
        }
        else
        {
            //Gain decrease
            stD2dPowPreCtrlLoc.ftGainFrq -= stD2dPowPreCtrlLoc.ftGainFrqStep;
        }

        if(stD2dPowPreCtrlLoc.ftGainFrq > stD2dPowPreCtrlLoc.ftGainFrqMax)
        {
            stD2dPowPreCtrlLoc.ftGainFrq      = stD2dPowPreCtrlLoc.ftGainFrqMax;
            stD2dPowPreCtrlLoc.uiFlgFrqJitDir = 1U;
        }
        else if(stD2dPowPreCtrlLoc.ftGainFrq < stD2dPowPreCtrlLoc.ftGainFrqMin)
        {
            stD2dPowPreCtrlLoc.ftGainFrq      = stD2dPowPreCtrlLoc.ftGainFrqMin;
            stD2dPowPreCtrlLoc.uiFlgFrqJitDir = 0U;
        }
        else
        {
            //do nothing
        }

        stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit = FRQ_D2D_DAB_DFT * stD2dPowPreCtrlLoc.ftGainFrq;
    }
    else
    {
    	stD2dPowPreCtrlLoc.ftGainFrq      = 1.0f;
        stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit = FRQ_D2D_DAB_DFT;
    }
    /* Output Signal*/
#if (1U == D2D_POW_PRE_CTRL_DBG)
    stD2dPowPreCtrl.ftFrqJit = stD2dPowPreCtrlDbg.ftFrqJit;
#else
    stD2dPowPreCtrl.ftFrqJit = stD2dPowPreCtrlLoc.stPrmExt.ftFrqJit;
#endif
}
#endif
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Frequency jitter parameter update
 * @param [in]   null
 * @param [out]  stD2dPowPreCtrl.ftFrqJit
 * @return       null
 * @see          SWDD-xxxx
 */
#if(3U == GRID_PHASE_NUMBER)
void v_D2dPowPreCtrl_FrqJitPrmUpd(void)
{
    if(FCN_ENABLE == stComTbl.stPrmD2dPowPreCtrl.uiFlgFrqJitEn)
    {
        stD2dPowPreCtrlLoc.ftGainFrqMax    = 1.0f + stComTbl.stPrmD2dPowPreCtrl.ftGainFrqJitRng;        ///< calculate max gain of frequency jitter
        stD2dPowPreCtrlLoc.ftGainFrqMin    = 1.0f - stComTbl.stPrmD2dPowPreCtrl.ftGainFrqJitRng;        ///< calculate min gain of frequency jitter
        stD2dPowPreCtrlLoc.ftGainFrqStep   = 4.0f * stComTbl.stPrmD2dPowPreCtrl.ftGainFrqJitRng / (float32)stComTbl.stPrmD2dPowPreCtrl.uiPerdFrqJit; //calculate step gain of frequency jitter
    }
    else
    {
        stD2dPowPreCtrlLoc.ftGainFrqMax    = 1.0f;
        stD2dPowPreCtrlLoc.ftGainFrqMin    = 1.0f;
        stD2dPowPreCtrlLoc.ftGainFrqStep   = 0.0f;
    }
}
#endif
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
