//==============================================================================================
//    File description
//==============================================================================================
/**@file         ComIf.c
 * @brief
 * The source file of communication interface is designed to realize interface between customer and platform .
 *
 * Module      :                       \n
 * ComIf                               \n
 *
 * Unit        :                       \n
 * D2dRunMod                           \n
 * D2dRunCmd                           \n
 * ChrgReq                             \n
 * DchaReq                             \n
 * OLReq                               \n
 * PowCtrl                             \n
 * ArmFlt                              \n
 * BldReq                              \n
 *
 * Module Task :                       \n
 * v_ComIf_Init()                      \n
 * v_ComIf_1ms()                       \n
 *
 * Unit Task   :                       \n
 * v_ComIf_D2dRunMod_1ms()             \n
 * v_ComIf_RunCmd_D2d_1ms()            \n
 * v_ComIf_D2dReq_Chrg_1ms()           \n
 * v_ComIf_D2dReq_Dcha_1ms()           \n
 * v_ComIf_D2dReq_OL_1ms()             \n
 * v_ComIf_PowCtrl_1ms()               \n
 * v_ComIf_ArmFlt_1ms()                \n
 * v_ComIf_ArmReq_10ms()                \n
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
#include "ComIf.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_COM_IF stComIf;                                    ///< Communication interface global struct

#if (1U == COM_IF_DBG)
ST_COM_IF stComIfDbg;                                 ///< Communication interface debug global struct
#endif

static ST_COM_IF_LOC stComIfLoc;                      ///< Communication interface local struct

static float32 ftACOLTimeTbl[AC_OL_TI_TBL_CNT] =
{
 36000.0f, 12472.1f, 9750.6f, 7640.2f, 6000.0f,
  4722.2f,  3724.5f, 2943.8f, 2331.6f, 1850.4f,
  1471.5f,  1172.5f,  936.0f,  748.7f,  600.0f,
   481.7f,   387.4f,  312.6f,  251.9f,  203.7f,
   165.0f,   133.8f,  108.7f,   88.5f,   72.2f,
};

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        Communication interface initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ComIf_Init(void)
{
    /* Local Signal*/
	stComIfLoc.stPrmExt.uiModRun          = CHG_ONGRID_MODE;            ///< Initialize to CHG_ONGRID_MODE
	stComIfLoc.stPrmExt.uiModPfcRun       = CHG_ONGRID_MODE;            ///< Initialize to CHG_ONGRID_MODE
	stComIfLoc.stPrmExt.uiModD2dRun       = CHG_ONGRID_MODE;            ///< Initialize to CHG_ONGRID_MODE
	stComIfLoc.stPrmExt.uiCmdRun          = STOP_CMD;                   ///< Initialize to STOP_CMD
	stComIfLoc.stPrmExt.uiCmdPfcRun       = STOP_CMD;                   ///< Initialize to STOP_CMD
	stComIfLoc.stPrmExt.uiCmdD2dRun       = STOP_CMD;                   ///< Initialize to STOP_CMD
	
    stComIfLoc.stPrmExt.uiModPfcPhaLoss   = PHASE_FULL_RUN_MODE;        ///< Initialize to phase full run mode
    stComIfLoc.stPrmExt.uiModPfcNonPhaN   = PHASE_N_NONE_MODE;         ///< Initialize to exist phase N mode
    stComIfLoc.stPrmExt.uiFlgPfcTz        = FCN_DISABLE;                ///< Initialize to disable
    stComIfLoc.stPrmExt.uiFlgPfcTzToDC    = FCN_DISABLE;                ///< Initialize to disable
#ifndef _SIMULATION_NO_DSP_
    stComIfLoc.stPrmExt.uiFlgPowOn        = 0U;                         ///< Initialize to 0U
#else
    stComIfLoc.stPrmExt.uiFlgPowOn        = 1U;
#endif
    stComIfLoc.stPrmExt.uiFlgBldPtd       = 0U;                         ///< Initialize to 0U
    stComIfLoc.stPrmExt.uiCmdV2LAuxPow    = 0U;                         ///< Initialize to 0U
    stComIfLoc.stPrmExt.uiFlgFltRst       = FCN_DISABLE;                ///< Initialize to disable
	stComIfLoc.stPrmExt.ftVoltBattChrgReq = VOLT_BATT_REQ_MIN;          ///< Battery charge voltage request
	stComIfLoc.stPrmExt.ftCurrBattChrgReq = CURR_BATT_SERIES_MAX;       ///< Battery charge current request
	stComIfLoc.stPrmExt.ftVoltBattDchaReq = VOLT_BATT_SERIES_MIN;       ///< Battery discharge voltage request
	stComIfLoc.stPrmExt.ftCurrBattDchaReq = -CURR_BATT_SERIES_MAX;      ///< Battery discharge current request
	stComIfLoc.stPrmExt.ftOutpOLReq       = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftPwrChrgReq      = POW_BATT_MAX * 1.1f;        ///< Charge active power request
    stComIfLoc.stPrmExt.ftPaReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftPbReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftPcReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftQaReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftQbReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftQcReq           = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftVoltBattBms     = VOLT_BATT_MAX;
    stComIfLoc.stPrmExt.ftVoltBattBmsMax  = VOLT_BATT_MAX;
    stComIfLoc.stPrmExt.ftCoeffBusPreChrg = 1.414f;
    stComIfLoc.stPrmExt.ftTempArmBd       = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc0        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc1        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc2        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc3        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc4        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc5        = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftTempNtc6        = 0.0f;                       ///< Initialize to 0.0f

    stComIfLoc.stPrmExt.uiEnaAcOvLoad     = 0U;                         ///< Initialize to 0U
    stComIfLoc.stPrmExt.ftRatSumTiOvLoad  = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.stPrmExt.ftPAcMax          = POW_AC_RTD;
    stComIfLoc.stPrmExt.ftCurrAcRmsMax    = MAX_AC_CURR_RMS;
    stComIfLoc.stPrmExt.ftIdAcMax         = CON_SQRT_2 * MAX_AC_CURR_RMS;
    stComIfLoc.stPrmExt.ftPOnePhaMax      = POW_AC_RTD * ONE_PHASE_COEFF;
    stComIfLoc.uiCntrCmdRst               = 0U;                         ///< Initialize to 0U
    stComIfLoc.uiFlgPowOnFltRst           = 0U;                         ///< Initialize to 0U
    stComIfLoc.uiCntrPfcRecy              = 0U;                         ///< Initialize to 0U
    stComIfLoc.ftPwrActvReq               = 0.0f;                       ///< Initialize to 0.0f
    stComIfLoc.uiCntrPowOn                = 0U;                         ///< Initialize to 0U
    stComIfLoc.ftPowStepUp                = POW_PFC_V2H_1MS_STEP;       ///< Initialize to V2H mode power step
    stComIfLoc.ftPowStepDwn               = POW_PFC_V2H_1MS_STEP;       ///< Initialize to V2H mode power step
    stComIfLoc.uiFlagRunOk                = 0U;
#if(3U != GRID_PHASE_NUMBER)
    stComIfLoc.ftFrqOLAbs                 = D2D_FRQ_MAX;                ///< Open-loop frequency absolute
    stComIfLoc.ftOutpOLAbsReq             = 0.0f;                       ///< Open-loop request output absolute
#endif 

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIfDbg.uiModRun          = stComIfLoc.stPrmExt.uiModRun;
    stComIfDbg.uiModPfcRun       = stComIfLoc.stPrmExt.uiModPfcRun;
    stComIfDbg.uiModD2dRun       = stComIfLoc.stPrmExt.uiModD2dRun;
    stComIfDbg.uiCmdRun          = stComIfLoc.stPrmExt.uiCmdRun;
    stComIfDbg.uiCmdPfcRun       = stComIfLoc.stPrmExt.uiCmdPfcRun;
    stComIfDbg.uiCmdD2dRun       = stComIfLoc.stPrmExt.uiCmdD2dRun;
    stComIfDbg.uiModPfcPhaLoss   = stComIfLoc.stPrmExt.uiModPfcPhaLoss;
    stComIfDbg.uiModPfcNonPhaN   = stComIfLoc.stPrmExt.uiModPfcNonPhaN;
    stComIfDbg.uiFlgPfcTz        = stComIfLoc.stPrmExt.uiFlgPfcTz;
    stComIfDbg.uiFlgPfcTzToDC    = stComIfLoc.stPrmExt.uiFlgPfcTzToDC;
    stComIfDbg.uiFlgPowOn        = stComIfLoc.stPrmExt.uiFlgPowOn;
    stComIfDbg.uiFlgBldPtd       = stComIfLoc.stPrmExt.uiFlgBldPtd;
    stComIfDbg.uiCmdV2LAuxPow    = stComIfLoc.stPrmExt.uiCmdV2LAuxPow;
	stComIfDbg.uiFlgFltRst       = stComIfLoc.stPrmExt.uiFlgFltRst;
    stComIfDbg.ftVoltBattChrgReq = stComIfLoc.stPrmExt.ftVoltBattChrgReq;
    stComIfDbg.ftCurrBattChrgReq = stComIfLoc.stPrmExt.ftCurrBattChrgReq;
    stComIfDbg.ftVoltBattDchaReq = stComIfLoc.stPrmExt.ftVoltBattDchaReq;
    stComIfDbg.ftCurrBattDchaReq = stComIfLoc.stPrmExt.ftCurrBattDchaReq;
    stComIfDbg.ftOutpOLReq       = stComIfLoc.stPrmExt.ftOutpOLReq;
    stComIfDbg.ftPwrChrgReq      = stComIfLoc.stPrmExt.ftPwrChrgReq;
    stComIfDbg.ftPaReq           = stComIfLoc.stPrmExt.ftPaReq;
    stComIfDbg.ftPbReq           = stComIfLoc.stPrmExt.ftPbReq;
    stComIfDbg.ftPcReq           = stComIfLoc.stPrmExt.ftPcReq;
    stComIfDbg.ftQaReq           = stComIfLoc.stPrmExt.ftQaReq;
    stComIfDbg.ftQbReq           = stComIfLoc.stPrmExt.ftQbReq;
    stComIfDbg.ftQcReq           = stComIfLoc.stPrmExt.ftQcReq;
    stComIfDbg.ftVoltBattBms     = stComIfLoc.stPrmExt.ftVoltBattBms;
    stComIfDbg.ftVoltBattBmsMax  = stComIfLoc.stPrmExt.ftVoltBattBmsMax;
    stComIfDbg.ftCoeffBusPreChrg = stComIfLoc.stPrmExt.ftCoeffBusPreChrg;
    stComIfDbg.ftTempArmBd       = stComIfLoc.stPrmExt.ftTempArmBd;
    stComIfDbg.ftTempNtc0        = stComIfLoc.stPrmExt.ftTempNtc0;
    stComIfDbg.ftTempNtc1        = stComIfLoc.stPrmExt.ftTempNtc1;
    stComIfDbg.ftTempNtc2        = stComIfLoc.stPrmExt.ftTempNtc2;
    stComIfDbg.ftTempNtc3        = stComIfLoc.stPrmExt.ftTempNtc3;
    stComIfDbg.ftTempNtc4        = stComIfLoc.stPrmExt.ftTempNtc4;
    stComIfDbg.ftTempNtc5        = stComIfLoc.stPrmExt.ftTempNtc5;
    stComIfDbg.ftTempNtc6        = stComIfLoc.stPrmExt.ftTempNtc6;
    stComIfDbg.uiEnaAcOvLoad     = stComIfLoc.stPrmExt.uiEnaAcOvLoad;
    stComIfDbg.ftRatSumTiOvLoad  = stComIfLoc.stPrmExt.ftRatSumTiOvLoad;
    stComIfDbg.ftPAcMax          = stComIfLoc.stPrmExt.ftPAcMax;
    stComIfDbg.ftPOnePhaMax      = stComIfLoc.stPrmExt.ftPOnePhaMax;
    stComIfDbg.ftCurrAcRmsMax    = stComIfLoc.stPrmExt.ftCurrAcRmsMax;
    stComIfDbg.ftIdAcMax         = stComIfLoc.stPrmExt.ftIdAcMax;

    stComIf.uiModRun          = stComIfDbg.uiModRun;
    stComIf.uiModPfcRun       = stComIfDbg.uiModPfcRun;
    stComIf.uiModD2dRun       = stComIfDbg.uiModD2dRun;
    stComIf.uiCmdRun          = stComIfDbg.uiCmdRun;
    stComIf.uiCmdPfcRun       = stComIfDbg.uiCmdPfcRun;
    stComIf.uiCmdD2dRun       = stComIfDbg.uiCmdD2dRun;
    stComIf.uiModPfcPhaLoss   = stComIfDbg.uiModPfcPhaLoss;
    stComIf.uiModPfcNonPhaN   = stComIfDbg.uiModPfcNonPhaN;
    stComIf.uiFlgPfcTz        = stComIfDbg.uiFlgPfcTz;
    stComIf.uiFlgPfcTzToDC    = stComIfDbg.uiFlgPfcTzToDC;
	stComIf.uiFlgPowOn        = stComIfDbg.uiFlgPowOn;
    stComIf.uiFlgBldPtd       = stComIfDbg.uiFlgBldPtd;
    stComIf.uiCmdV2LAuxPow    = stComIfDbg.uiCmdV2LAuxPow;
	stComIf.uiFlgFltRst       = stComIfDbg.uiFlgFltRst;
    stComIf.ftVoltBattChrgReq = stComIfDbg.ftVoltBattChrgReq;
    stComIf.ftCurrBattChrgReq = stComIfDbg.ftCurrBattChrgReq;
    stComIf.ftVoltBattDchaReq = stComIfDbg.ftVoltBattDchaReq;
    stComIf.ftCurrBattDchaReq = stComIfDbg.ftCurrBattDchaReq;
    stComIf.ftOutpOLReq       = stComIfDbg.ftOutpOLReq;
    stComIf.ftPwrChrgReq      = stComIfDbg.ftPwrChrgReq;
    stComIf.ftPaReq           = stComIfDbg.ftPaReq;
    stComIf.ftPbReq           = stComIfDbg.ftPbReq;
    stComIf.ftPcReq           = stComIfDbg.ftPcReq;
    stComIf.ftQaReq           = stComIfDbg.ftQaReq;
    stComIf.ftQbReq           = stComIfDbg.ftQbReq;
    stComIf.ftQcReq           = stComIfDbg.ftQcReq;
    stComIf.ftVoltBattBms     = stComIfDbg.ftVoltBattBms;
    stComIf.ftVoltBattBmsMax  = stComIfDbg.ftVoltBattBmsMax;
    stComIf.ftCoeffBusPreChrg = stComIfDbg.ftCoeffBusPreChrg;
    stComIf.ftTempArmBd       = stComIfDbg.ftTempArmBd;
    stComIf.ftTempNtc0        = stComIfDbg.ftTempNtc0;
    stComIf.ftTempNtc1        = stComIfDbg.ftTempNtc1;
    stComIf.ftTempNtc2        = stComIfDbg.ftTempNtc2;
    stComIf.ftTempNtc3        = stComIfDbg.ftTempNtc3;
    stComIf.ftTempNtc4        = stComIfDbg.ftTempNtc4;
    stComIf.ftTempNtc5        = stComIfDbg.ftTempNtc5;
    stComIf.ftTempNtc6        = stComIfDbg.ftTempNtc6;
    stComIf.uiEnaAcOvLoad     = stComIfDbg.uiEnaAcOvLoad;
    stComIf.ftRatSumTiOvLoad  = stComIfDbg.ftRatSumTiOvLoad;
    stComIf.ftPAcMax          = stComIfDbg.ftPAcMax;
    stComIf.ftPOnePhaMax      = stComIfDbg.ftPOnePhaMax;
    stComIf.ftCurrAcRmsMax    = stComIfDbg.ftCurrAcRmsMax;
    stComIf.ftIdAcMax         = stComIfDbg.ftIdAcMax;
#else
    stComIf.uiModRun          = stComIfLoc.stPrmExt.uiModRun;
    stComIf.uiModPfcRun       = stComIfLoc.stPrmExt.uiModPfcRun;
    stComIf.uiModD2dRun       = stComIfLoc.stPrmExt.uiModD2dRun;
    stComIf.uiCmdRun          = stComIfLoc.stPrmExt.uiCmdRun;
    stComIf.uiCmdD2dRun       = stComIfLoc.stPrmExt.uiCmdD2dRun;
    stComIf.uiCmdPfcRun       = stComIfLoc.stPrmExt.uiCmdPfcRun;
    stComIf.uiModPfcPhaLoss   = stComIfLoc.stPrmExt.uiModPfcPhaLoss;
    stComIf.uiModPfcNonPhaN   = stComIfLoc.stPrmExt.uiModPfcNonPhaN;
    stComIf.uiFlgPfcTz        = stComIfLoc.stPrmExt.uiFlgPfcTz;
    stComIf.uiFlgPfcTzToDC    = stComIfLoc.stPrmExt.uiFlgPfcTzToDC;
    stComIf.uiFlgPowOn        = stComIfLoc.stPrmExt.uiFlgPowOn;
    stComIf.uiFlgBldPtd       = stComIfLoc.stPrmExt.uiFlgBldPtd;
    stComIf.uiCmdV2LAuxPow    = stComIfLoc.stPrmExt.uiCmdV2LAuxPow;
    stComIf.uiFlgFltRst       = stComIfLoc.stPrmExt.uiFlgFltRst;     ///< Initialize to 0
    stComIf.ftVoltBattChrgReq = stComIfLoc.stPrmExt.ftVoltBattChrgReq;
    stComIf.ftCurrBattChrgReq = stComIfLoc.stPrmExt.ftCurrBattChrgReq;
    stComIf.ftVoltBattDchaReq = stComIfLoc.stPrmExt.ftVoltBattDchaReq;
    stComIf.ftCurrBattDchaReq = stComIfLoc.stPrmExt.ftCurrBattDchaReq;
    stComIf.ftOutpOLReq       = stComIfLoc.stPrmExt.ftOutpOLReq;
    stComIf.ftPwrChrgReq      = stComIfLoc.stPrmExt.ftPwrChrgReq;
    stComIf.ftPaReq           = stComIfLoc.stPrmExt.ftPaReq;
    stComIf.ftPbReq           = stComIfLoc.stPrmExt.ftPbReq;
    stComIf.ftPcReq           = stComIfLoc.stPrmExt.ftPcReq;
    stComIf.ftQaReq           = stComIfLoc.stPrmExt.ftQaReq;
    stComIf.ftQbReq           = stComIfLoc.stPrmExt.ftQbReq;
    stComIf.ftQcReq           = stComIfLoc.stPrmExt.ftQcReq;
    stComIf.ftVoltBattBms     = stComIfLoc.stPrmExt.ftVoltBattBms;
    stComIf.ftVoltBattBmsMax  = stComIfLoc.stPrmExt.ftVoltBattBmsMax;
    stComIf.ftCoeffBusPreChrg = stComIfLoc.stPrmExt.ftCoeffBusPreChrg;
    stComIf.ftTempArmBd       = stComIfLoc.stPrmExt.ftTempArmBd;
    stComIf.ftTempNtc0        = stComIfLoc.stPrmExt.ftTempNtc0;
    stComIf.ftTempNtc1        = stComIfLoc.stPrmExt.ftTempNtc1;
    stComIf.ftTempNtc2        = stComIfLoc.stPrmExt.ftTempNtc2;
    stComIf.ftTempNtc3        = stComIfLoc.stPrmExt.ftTempNtc3;
    stComIf.ftTempNtc4        = stComIfLoc.stPrmExt.ftTempNtc4;
    stComIf.ftTempNtc5        = stComIfLoc.stPrmExt.ftTempNtc5;
    stComIf.ftTempNtc6        = stComIfLoc.stPrmExt.ftTempNtc6;
    stComIf.uiEnaAcOvLoad     = stComIfLoc.stPrmExt.uiEnaAcOvLoad;
    stComIf.ftRatSumTiOvLoad  = stComIfLoc.stPrmExt.ftRatSumTiOvLoad;
    stComIf.ftPAcMax          = stComIfLoc.stPrmExt.ftPAcMax;
    stComIf.ftPOnePhaMax      = stComIfLoc.stPrmExt.ftPOnePhaMax;
    stComIf.ftCurrAcRmsMax    = stComIfLoc.stPrmExt.ftCurrAcRmsMax;
    stComIf.ftIdAcMax         = stComIfLoc.stPrmExt.ftIdAcMax;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_ComIf_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Communication interface 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ComIf_1ms(void)
{
    /* Run mode update */
	v_ComIf_RunMod_1ms();
    /* Run command update */
	v_ComIf_RunCmd_1ms();
    /* PFC grid control power update */
    v_ComIf_PfcPwrReq_1ms();
    /* D2D request update */
    v_ComIf_D2dReq_1ms();  ///< sst no use

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_ComIf_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Communication interface in 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ComIf_10ms(void)
{
    /* Fault Reset*/
    v_ComIf_RstFlt_10ms();
    /* Bleed Request*/
    v_ComIf_ArmReq_10ms(); ///< sst no use
    /* Bms state*/
    v_ComIf_Bms_10ms(); ///< sst no use
#if(3U == GRID_PHASE_NUMBER)
    /* PFC Request*/
    v_ComIf_PfcReq_10ms();
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_ComIf_10ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Communication interface 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ComIf_100ms(void)
{
    /* Power On Judge*/
	v_ComIf_PowOnJudg_100ms();
	/* Temperature Handle*/
	v_ComIf_Temp_100ms();  ///< sst no use
	/* AC over load handle */
	v_ComIf_AcOvLoad_100ms();

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_ComIf_100ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D run mode update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_RunMod_1ms(void)
{
    /* Run Mode Update*/
    if(stComIfLoc.stPrmExt.uiModRun != stCom.uiModRunReq)    ///< Inconsistent with the current run mode
    {
        if(START_CMD == stCom.uiCmdRunReq)
        {
            if((stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_CHK) && (stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB))    ///< Standby or fault state
            {
                stComIfLoc.stPrmExt.uiModRun = stCom.uiModRunReq;    ///< Update run mode
            }
        }
        else
        {
            stComIfLoc.stPrmExt.uiModRun = stCom.uiModRunReq;    ///< Update run mode
        }

        if(stComIfLoc.stPrmExt.uiModRun == stCom.uiModRunReq)
        {
            /* Update grid protection parameter */
            v_PfcGridCtrl_PrmUpd_Eep();
#if(1U == GRID_PHASE_NUMBER)
            /* Update PFC slow MOS EPWM configuration */
            v_EPwmCfg_Pfc_Slow_CBC_Cfg();
#endif
        }
    }

    switch(stComIfLoc.stPrmExt.uiModRun)
    {
        case CHG_ONGRID_MODE:
        case BIDIR_ONGRID_MODE:
        case OFFGRID_MODE:
        case OPENLOOP_MODE:
            stComIfLoc.stPrmExt.uiModPfcRun = stComIfLoc.stPrmExt.uiModRun;
            stComIfLoc.stPrmExt.uiModD2dRun = stComIfLoc.stPrmExt.uiModRun;
            break;

        case PFC_OL_D2D_DISCH_MODE:
            stComIfLoc.stPrmExt.uiModPfcRun = OPENLOOP_MODE;
            stComIfLoc.stPrmExt.uiModD2dRun = OFFGRID_MODE;
            break;

        case PFC_CHG_D2D_OL_MODE:
            stComIfLoc.stPrmExt.uiModPfcRun = CHG_ONGRID_MODE;
            stComIfLoc.stPrmExt.uiModD2dRun = OPENLOOP_MODE;
            break;

        default:
            // No code
            break;
    }

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiModRun    = stComIfDbg.uiModRun;
    stComIf.uiModPfcRun = stComIfDbg.uiModPfcRun;
    stComIf.uiModD2dRun = stComIfDbg.uiModD2dRun;
#else
    stComIf.uiModRun    = stComIfLoc.stPrmExt.uiModRun;
    stComIf.uiModPfcRun = stComIfLoc.stPrmExt.uiModPfcRun;
    stComIf.uiModD2dRun = stComIfLoc.stPrmExt.uiModD2dRun;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Run command update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_RunCmd_1ms(void)
{
    /* To be modified */
    if(((D2D_FLT_IS_SET) && (PFC_EN_D2D_DIS != stCom.uiStgRunEnReq)) \
       || ((PFC_FLT_IS_SET) && (PFC_DIS_D2D_EN != stCom.uiStgRunEnReq)) \
       || (SYS_FLT_IS_SET) \
       || (SYS_FLT_RESET_IS_ON) \
       || (FCN_DISABLE == stComTbl.stPrmPwrCtrl.uiEnaEntrSrv) \
       || (FCN_ENABLE == stCom.uiEnaSelfTest) \
       || ((0U != stCom.unCmdFct.all) && (OPENLOOP_MODE != stComIfLoc.stPrmExt.uiModRun))
#ifndef _SIMULATION_NO_DSP_
       || (0U == stComIf.uiFlgPowOn)
       || (1U == stComIfLoc.uiFlagRunOk)
#endif
#if 1U == FLG_FLT_DATA_REC_EN
       || (SPI_STATE_WRITE == stSpi.uiStSpi)
#endif
      )
    {
        stComIfLoc.stPrmExt.uiCmdRun = STOP_CMD;
    }
    else
    {
        stComIfLoc.stPrmExt.uiCmdRun = stCom.uiCmdRunReq;
    }
#if 1
    if((stComIfLoc.stPrmExt.uiCmdRun == START_CMD) \
        && (((stComIf.uiModRun == BIDIR_ONGRID_MODE) && (stPfcStMac.unPFCSts.bit.uiMacSt == PFC_ST_MAC_NORMRUN)) \
            ||((stComIf.uiModRun == CHG_ONGRID_MODE) && (stD2dStMac.uiStD2dRun == D2D_ST_MAC_NORMRUN))))
    {
        stComIfLoc.uiCntrRunTime++;
        if(stComIfLoc.uiCntrRunTime == stComIf.uiValRunTimeMs)
        {
            stComIfLoc.stPrmExt.uiCmdRun = STOP_CMD;
            stComIfLoc.uiFlagRunOk = 1U;
            stComIfLoc.uiCntrRunTime = 0U;
        }
    }
    else
    {
        stComIfLoc.uiCntrRunTime = 0U;
    }

    if(stCom.uiCmdRunReq == STOP_CMD)
    {
        stComIfLoc.uiFlagRunOk = 0U;
    }
#endif
    /* PFC run command update */
    v_ComIf_RunCmd_Pfc_1ms();
    /* D2D run command update */
    v_ComIf_RunCmd_D2d_1ms();

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiCmdRun    = stComIfDbg.uiCmdRun;
#else
    stComIf.uiCmdRun    = stComIfLoc.stPrmExt.uiCmdRun;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC run command update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_RunCmd_Pfc_1ms(void)
{
    /* PFC operate command manage */
    if((START_CMD == stComIfLoc.stPrmExt.uiCmdRun) && \
       (AD_BIAS_ADJUST_OVER == stCom.uiCmdPfcADZeroAdj) && \
       ((1U == ui_ComIf_RunCmd_Pfc_Chrg_1ms()) || (1U == ui_ComIf_RunCmd_Pfc_BiDir_1ms()) || (1U == ui_ComIf_RunCmd_Pfc_OffGrid_1ms()) || (1U == ui_ComIf_RunCmd_Pfc_OL_1ms())))
    {
        stComIfLoc.stPrmExt.uiCmdPfcRun = START_CMD;
    }
    else
    {
        stComIfLoc.stPrmExt.uiCmdPfcRun = STOP_CMD;
    }
    /* Standby 0A mode trigger */
    if((BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModRun) \
        && (((fabsf(stCom.ftCurrBattChrgReq) < CON_ZERO_DELTA) && (stComIfLoc.ftPwrActvReq > -CON_ZERO_DELTA)) \
            || ((fabsf(stCom.ftCurrBattDchaReq) < CON_ZERO_DELTA) && (stComIfLoc.ftPwrActvReq < CON_ZERO_DELTA))))
	{
		stComIfLoc.stPrmExt.uiFlgPfcTz     = FCN_ENABLE;
		stComIfLoc.stPrmExt.uiFlgPfcTzToDC = FCN_ENABLE;
		stComIfLoc.uiCntrPfcRecy = 0U;
	}
	else
	{
		stComIfLoc.stPrmExt.uiFlgPfcTzToDC = FCN_DISABLE;
	}
    /* Wait for bus voltage set up */
#if 1U == FLG_PFC_POWCTRL_EN
	if((FCN_ENABLE == stComIfLoc.stPrmExt.uiFlgPfcTz) && (FCN_DISABLE == stComIfLoc.stPrmExt.uiFlgPfcTzToDC)\
	  && ((stPfcPowCtrl.ftVbusNotch > (stPowLim.ftVoltBusLim - 5.0f)) || (BIDIR_ONGRID_MODE != stComIfLoc.stPrmExt.uiModRun)))
#else
	    ///< To be modified
#endif
	{
	    if(stComIfLoc.uiCntrPfcRecy++ >= 50U)
	    {
	        stComIfLoc.stPrmExt.uiFlgPfcTz = FCN_DISABLE;
	        stComIfLoc.uiCntrPfcRecy = 0U;
	    }
	}

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiCmdPfcRun    = stComIfDbg.uiCmdPfcRun;
    stComIf.uiFlgPfcTz     = stComIfDbg.uiFlgPfcTz;
    stComIf.uiFlgPfcTzToDC = stComIfDbg.uiFlgPfcTzToDC;
#else
    stComIf.uiCmdPfcRun    = stComIfLoc.stPrmExt.uiCmdPfcRun;
    stComIf.uiFlgPfcTz     = stComIfLoc.stPrmExt.uiFlgPfcTz;
    stComIf.uiFlgPfcTzToDC = stComIfLoc.stPrmExt.uiFlgPfcTzToDC;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC charge mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_Pfc_Chrg_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;
#if 0
    if((CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && (PFC_DIS_D2D_EN != stCom.uiStgRunEnReq))
#else
    if((CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && \
       (((PFC_EN_D2D_EN == stCom.uiStgRunEnReq) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun)) || \
        (PFC_EN_D2D_DIS == stCom.uiStgRunEnReq)))
#endif
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC Bi-Directional mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_Pfc_BiDir_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;
#if 0
    if((BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && \
       (FCN_ENABLE == stPfcGridCtrl.stActvCtrl.uiFlgGridChkOk) && \
       (((PFC_EN_D2D_EN == stCom.uiStgRunEnReq) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun)) || \
        (PFC_EN_D2D_DIS == stCom.uiStgRunEnReq)))
#else
    if((BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && \
       (((PFC_EN_D2D_EN == stCom.uiStgRunEnReq) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun)) || \
        (PFC_EN_D2D_DIS == stCom.uiStgRunEnReq)))
#endif
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC Off-Grid mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_Pfc_OffGrid_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;

    if((OFFGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && \
       (((PFC_EN_D2D_EN == stCom.uiStgRunEnReq) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun)) || \
        (PFC_EN_D2D_DIS == stCom.uiStgRunEnReq)))
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC OpenLoop mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_Pfc_OL_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;

    if((OPENLOOP_MODE == stComIfLoc.stPrmExt.uiModPfcRun) && \
       ((PFC_EN_D2D_DIS == stCom.uiStgRunEnReq) || \
        ((PFC_OL_D2D_DISCH_MODE == stComIfLoc.stPrmExt.uiModRun) && (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun))))
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D run command update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_RunCmd_D2d_1ms(void)
{
    if( (START_CMD == stComIfLoc.stPrmExt.uiCmdRun) \
        && (D2D_FLT_IS_CLR) \
        && ((1U == ui_ComIf_RunCmd_D2d_Chrg_1ms()) || (1U == ui_ComIf_RunCmd_D2d_Bidir_1ms()) || (1U == ui_ComIf_RunCmd_D2d_OL_1ms())) \
        && (stComIfLoc.stPrmExt.uiModRun == stCom.uiModRunReq))
    {
        stComIfLoc.stPrmExt.uiCmdD2dRun = START_CMD;
    }
    else
    {
        stComIfLoc.stPrmExt.uiCmdD2dRun = STOP_CMD;    ///< Stop D2D
    }

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiCmdD2dRun = stComIfDbg.uiCmdD2dRun;
#else
    stComIf.uiCmdD2dRun = stComIfLoc.stPrmExt.uiCmdD2dRun;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D charge mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_D2d_Chrg_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;
#if 0
    if((CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun) && \
       (((PFC_EN_D2D_EN == stCom.uiStgRunEnReq) && (FCN_ENABLE == stPfcStMac.unPFCSts.bit.uiFlgRunOk)) || \
        (PFC_DIS_D2D_EN == stCom.uiStgRunEnReq)))
#else
    if(((CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun) || (OFFGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun)) && \
       (PFC_EN_D2D_DIS != stCom.uiStgRunEnReq))
#endif
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D Bi-Directional mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_D2d_Bidir_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;

    if(((BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun) || (OFFGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun)) && \
       (PFC_EN_D2D_DIS != stCom.uiStgRunEnReq))
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D open-loop mode command condition
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_ComIf_RunCmd_D2d_OL_1ms(void)
{
    Uint16 l_uiRetTmp = 0U;

    if((OPENLOOP_MODE == stComIfLoc.stPrmExt.uiModD2dRun) && \
       ((PFC_DIS_D2D_EN == stCom.uiStgRunEnReq) || \
        ((PFC_CHG_D2D_OL_MODE == stComIfLoc.stPrmExt.uiModRun) && (FCN_ENABLE == stPfcStMac.unPFCSts.bit.uiFlgRunOk))))
    {
        l_uiRetTmp = 1U;
    }
    else
    {
        l_uiRetTmp = 0U;
    }

    return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC grid power request update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_PfcPwrReq_1ms(void)
{
#ifdef SIMULATION_PFC
//    stComIfLoc.stPrmExt.uiModPfcRun = stCom.uiModRunReq;
//    stComIf.uiModPfcRun             = stCom.uiModRunReq;
//    stComIf.uiModRun                = stCom.uiModRunReq;
//    stComIf.uiCmdPfcRun             = stCom.uiCmdRunReq;
//    stComIf.uiCmdRun                = stCom.uiCmdRunReq;
#endif

#if(1U == GRID_PHASE_NUMBER)
    stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_FULL_RUN_MODE;
    stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_EXIST_MODE;
#elif(2U == GRID_PHASE_NUMBER)
    if(TYPE_GRID_ABN == stCom.uiTypeGrid)
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_FULL_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_EXIST_MODE;
    }
    else if(TYPE_GRID_AB == stCom.uiTypeGrid)
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_FULL_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_NONE_MODE;
    }
    else if((TYPE_GRID_AN == stCom.uiTypeGrid) || (TYPE_GRID_BN == stCom.uiTypeGrid))
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_LOSS_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_EXIST_MODE;
    }
    else
    {
        ///< Do nothing, report error in PfcDiag module
    }
#else
    if(TYPE_GRID_ABCN == stCom.uiTypeGrid)
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_FULL_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_EXIST_MODE;
    }
    else if(TYPE_GRID_ABC == stCom.uiTypeGrid)
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_FULL_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_NONE_MODE;
    }
    else if((TYPE_GRID_AN == stCom.uiTypeGrid) || (TYPE_GRID_BN == stCom.uiTypeGrid) || (TYPE_GRID_CN == stCom.uiTypeGrid))
    {
        stComIfLoc.stPrmExt.uiModPfcPhaLoss = PHASE_LOSS_RUN_MODE;
        stComIfLoc.stPrmExt.uiModPfcNonPhaN = PHASE_N_EXIST_MODE;
    }
    else
    {
        ///< Do nothing, report error in PfcDiag module
    }
#endif

    if(CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun)     ///< CHG_ONGRID_MODE == stComIfLoc.stPrmExt.uiModRun
    {
        v_ComIf_PfcPwrReq_Chrg_1ms();
    }
    else if(BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModPfcRun)
    {
        v_ComIf_PfcPwrReq_Bidir_1ms();
    }
    else
    {
        // Do nothing
    }

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiModPfcPhaLoss = stComIfDbg.uiModPfcPhaLoss;
    stComIf.uiModPfcNonPhaN = stComIfDbg.uiModPfcNonPhaN;
#else
    stComIf.uiModPfcPhaLoss = stComIfLoc.stPrmExt.uiModPfcPhaLoss;
    stComIf.uiModPfcNonPhaN = stComIfLoc.stPrmExt.uiModPfcNonPhaN;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC grid power request in charge mode
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_PfcPwrReq_Chrg_1ms(void)
{
#if 1U == GRID_PHASE_NUMBER
    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance mode
    {
        stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPwrChrgReq;
    }
    else    ///< Active power imbalance mode
    {
        stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPaAcReq;
    }
#elif 2U == GRID_PHASE_NUMBER
    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
    {
        stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPwrChrgReq;
    }
    else
    {
        if(PHASE_FULL_RUN_MODE == stComIfLoc.stPrmExt.uiModPfcPhaLoss)    ///< Phase full run mode
        {
            stComIfLoc.stPrmExt.ftPwrChrgReq = (ftFcn_MinOfTwo(stCom.ftPaAcReq, stCom.ftPbAcReq)) * (float32)GRID_PHASE_NUMBER;
        }
        else
        {
            if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPbAcReq;
            }
            else
            {
                stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPaAcReq;
            }
        }
    }
#elif 3U == GRID_PHASE_NUMBER
    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
    {
        stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPwrChrgReq;
    }
    else
    {
        if(PHASE_FULL_RUN_MODE == stComIfLoc.stPrmExt.uiModPfcPhaLoss)    ///< Phase full run mode
        {
            stComIfLoc.stPrmExt.ftPwrChrgReq = (ftFcn_MinOfThree(stCom.ftPaAcReq, stCom.ftPbAcReq, stCom.ftPcAcReq)) * (float32)GRID_PHASE_NUMBER;
        }
        else
        {
            if(TYPE_GRID_AN == stCom.uiTypeGrid)
            {
                stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPaAcReq;
            }
            else if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPbAcReq;
            }
            else
            {
                stComIfLoc.stPrmExt.ftPwrChrgReq = stCom.ftPcAcReq;
            }
        }
    }
#endif

    DOWN_LIMIT(stComIfLoc.stPrmExt.ftPwrChrgReq, 0.0f);

    /* Global parameter */
#if (1U == COM_IF_DBG)
    stComIf.ftPwrChrgReq      = stComIfDbg.ftPwrChrgReq;
#else
    stComIf.ftPwrChrgReq      = stComIfLoc.stPrmExt.ftPwrChrgReq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC grid power request update  in bidiraction mode
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_PfcPwrReq_Bidir_1ms(void)
{
    float32 l_ftActvPwr   = 0.0f;    ///< Active power sum of all phase
    float32 l_ftReactvPwr = 0.0f;    ///< Reactive power sum of all phase
    float32 l_ftPaReq = 0.0f;        ///< Phase A power request
#if GRID_PHASE_NUMBER > 1U
    float32 l_ftPbReq = 0.0f;        ///< Phase B power request
#if GRID_PHASE_NUMBER > 2U
    float32 l_ftPcReq = 0.0f;        ///< Phase C power request
#endif
#endif

	l_ftActvPwr   = stCom.ftPwrActvReq;                   ///< Active power request from PfcGridCtrl module, negative - discharge
	l_ftReactvPwr = stCom.ftPwrReactvReq;                 ///< Reactive power request from PfcGridCtrl module
#ifdef _SIMULATION_NO_DSP_
    if(PFC_PWR_ARM_CTRL_MODE == stCom.unModPfcPow.bit.uiModPowCtrl)    ///< ARM control mode
    {
        stComIfLoc.ftPowStepUp  = POW_PFC_V2H_1MS_STEP;    ///< V2H mode power step
        stComIfLoc.ftPowStepDwn = POW_PFC_V2H_1MS_STEP;    ///< V2H mode power step
    }
    else    ///< Grid standard mode
    {
        stComIfLoc.ftPowStepUp  = stPfcGridCtrl.stActvCtrl.ftRatePwrUp * COEFF_PFC_POW_RAT_1MS_STEP * stComTbl.stPrmPfcRtd1.ftPowRtd * ONE_PHASE_COEFF;     ///< Calculate active power up step
        stComIfLoc.ftPowStepDwn = stPfcGridCtrl.stActvCtrl.ftRatePwrDwn * COEFF_PFC_POW_RAT_1MS_STEP * stComTbl.stPrmPfcRtd1.ftPowRtd * ONE_PHASE_COEFF;    ///< Calculate active power down step
    }
#else
    if(PFC_PWR_ARM_CTRL_MODE == stCom.unModPfcPow.bit.uiModPowCtrl)    ///< ARM control mode
    {
        stComIfLoc.ftPowStepUp  = POW_PFC_V2H_1MS_STEP;    ///< V2H mode power step
        stComIfLoc.ftPowStepDwn = POW_PFC_V2H_1MS_STEP;    ///< V2H mode power step
    }
    else    ///< Grid standard mode
    {
        stComIfLoc.ftPowStepUp  = 6000.0f * COEFF_PFC_POW_RAT_1MS_STEP * stComTbl.stPrmPfcRtd1.ftPowRtd * ONE_PHASE_COEFF;     ///< Calculate active power up step
        stComIfLoc.ftPowStepDwn = 6000.0f * COEFF_PFC_POW_RAT_1MS_STEP * stComTbl.stPrmPfcRtd1.ftPowRtd * ONE_PHASE_COEFF;    ///< Calculate active power down step
    }
#endif


#if 1U == GRID_PHASE_NUMBER
	/* Active power */
	if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
	{
	    l_ftPaReq = l_ftActvPwr;
	}
	else    ///< Active power imbalance run mode
	{
	    l_ftPaReq = stCom.ftPaAcReq;
	}
	vFcn_FtUpDwnLim(&l_ftPaReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);

    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC run state
    {
        vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPaReq, l_ftPaReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
    }
    else
    {
        stComIfLoc.stPrmExt.ftPaReq = 0.0f;
    }
    stComIfLoc.stPrmExt.ftPbReq = 0.0f;
    stComIfLoc.stPrmExt.ftPcReq = 0.0f;

    /* Reactive power */
    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)    ///< Reactive power balance run mode
    {
        stComIfLoc.stPrmExt.ftQaReq = l_ftReactvPwr;
    }
    else    ///< Reactive power imbalance run mode
    {
        stComIfLoc.stPrmExt.ftQaReq = stCom.ftQaAcReq;
    }

    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQaReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
    stComIfLoc.stPrmExt.ftQbReq = 0.0f;
    stComIfLoc.stPrmExt.ftQcReq = 0.0f;
#elif 2U == GRID_PHASE_NUMBER
	if(PHASE_FULL_RUN_MODE == stComIfLoc.stPrmExt.uiModPfcPhaLoss)    ///< Phase full run mode
	{
	    /* Active power */
	    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
		{
	        l_ftPaReq = l_ftActvPwr * ONE_PHASE_COEFF;
	        l_ftPbReq = l_ftPaReq;
		}
	    else    ///< Active power imbalance run mode
		{
			if(PHASE_N_EXIST_MODE == stComIfLoc.stPrmExt.uiModPfcNonPhaN)    ///< Exist phase N mode
			{
			    l_ftPaReq = stCom.ftPaAcReq;
			    l_ftPbReq = stCom.ftPbAcReq;
			}
			else    ///< None phase N mode
			{
			    if((stCom.ftPaAcReq > 0.0f) && (stCom.ftPbAcReq > 0.0f))         ///< Both phase requests are positive
			    {
			        l_ftPaReq = ftFcn_MinOfTwo(stCom.ftPaAcReq, stCom.ftPbAcReq);
			    }
			    else if((stCom.ftPaAcReq < 0.0f) && (stCom.ftPbAcReq < 0.0f))    ///< Both phase requests are negative
			    {
			        l_ftPaReq = ftFcn_MaxOfTwo(stCom.ftPaAcReq, stCom.ftPbAcReq);
			    }
			    else
			    {
			        l_ftPaReq = 0.0f;
			    }
			    l_ftPbReq = l_ftPaReq;
			}
		}

	    /* Reactive power */
	    if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)    ///< Reactive power balance run mode
        {
	        stComIfLoc.stPrmExt.ftQaReq = l_ftReactvPwr * ONE_PHASE_COEFF;
            stComIfLoc.stPrmExt.ftQbReq = stComIfLoc.stPrmExt.ftQaReq;
        }
	    else    ///< Reactive power imbalance run mode
        {
            if(PHASE_N_EXIST_MODE == stComIfLoc.stPrmExt.uiModPfcNonPhaN)    ///< Exist phase N mode
            {
                stComIfLoc.stPrmExt.ftQaReq = stCom.ftQaAcReq;
                stComIfLoc.stPrmExt.ftQbReq = stCom.ftQbAcReq;
            }
            else    ///< None phase N mode
            {
                if((stCom.ftQaAcReq > 0.0f) && (stCom.ftQbAcReq > 0.0f))         ///< Both phase requests are positive
                {
                    stComIfLoc.stPrmExt.ftQaReq = ftFcn_MinOfTwo(stCom.ftQaAcReq, stCom.ftQbAcReq);
                }
                else if((stCom.ftQaAcReq < 0.0f) && (stCom.ftQbAcReq < 0.0f))    ///< Both phase requests are negative
                {
                    stComIfLoc.stPrmExt.ftQaReq = ftFcn_MaxOfTwo(stCom.ftQaAcReq, stCom.ftQbAcReq);
                }
                else
                {
                    stComIfLoc.stPrmExt.ftQaReq = 0.0f;
                }
                stComIfLoc.stPrmExt.ftQbReq = stComIfLoc.stPrmExt.ftQaReq;
            }
        }
	}
	else    ///< Phase loss run mode
	{
        if(TYPE_GRID_AN == stCom.uiTypeGrid)
        {
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
            {
                l_ftPaReq = l_ftActvPwr;
            }
            else                                               ///< Active power balance run mode
            {
                l_ftPaReq = stCom.ftPaAcReq;
            }
            l_ftPbReq = 0.0f;
			
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)  ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQaReq = l_ftReactvPwr;
            }
            else                                               ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQaReq = stCom.ftQaAcReq;
            }
            stComIfLoc.stPrmExt.ftQbReq = 0.0f;
        }
	    else
	    {
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
            {
                l_ftPbReq = l_ftActvPwr;
            }
            else                                               ///< Active power balance run mode
            {
                l_ftPbReq = stCom.ftPbAcReq;
            }
            l_ftPaReq = 0.0f;
			
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)  ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQbReq = l_ftReactvPwr;
            }
            else                                               ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQbReq = stCom.ftQbAcReq;
            }
            stComIfLoc.stPrmExt.ftQaReq = 0.0f;
	    }
	}

	if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC run state
    {
	    vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPaReq, l_ftPaReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
	    vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPbReq, l_ftPbReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
    }
    else
    {
        stComIfLoc.stPrmExt.ftPaReq = 0.0f;
        stComIfLoc.stPrmExt.ftPbReq = 0.0f;
    }

	vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftPaReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);
	vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftPbReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);
	vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQaReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
	vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQbReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
    stComIfLoc.stPrmExt.ftPcReq = 0.0f;
    stComIfLoc.stPrmExt.ftQcReq = 0.0f;
#elif 3U == GRID_PHASE_NUMBER
    if(PHASE_FULL_RUN_MODE == stComIfLoc.stPrmExt.uiModPfcPhaLoss)    ///< Phase full run mode
    {
        /* Active power */
        if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
        {
            l_ftPaReq = l_ftActvPwr * ONE_PHASE_COEFF;
            l_ftPbReq = l_ftPaReq;
            l_ftPcReq = l_ftPaReq;
        }
        else    ///< Active power imbalance run mode
        {
            if(PHASE_N_EXIST_MODE == stComIfLoc.stPrmExt.uiModPfcNonPhaN)    ///< Exist phase N mode
            {
                l_ftPaReq = stCom.ftPaAcReq;
                l_ftPbReq = stCom.ftPbAcReq;
                l_ftPcReq = stCom.ftPcAcReq;
            }
            else    ///< None phase N mode
            {
                if((stCom.ftPaAcReq > 0.0f) && (stCom.ftPbAcReq > 0.0f) && (stCom.ftPcAcReq > 0.0f))         ///< Both phase requests are positive
                {
                    l_ftPaReq = ftFcn_MinOfThree(stCom.ftPaAcReq, stCom.ftPbAcReq, stCom.ftPcAcReq);
                }
                else if((stCom.ftPaAcReq < 0.0f) && (stCom.ftPbAcReq < 0.0f) && (stCom.ftPcAcReq < 0.0f))    ///< Both phase requests are negative
                {
                    l_ftPaReq = ftFcn_MaxOfThree(stCom.ftPaAcReq, stCom.ftPbAcReq, stCom.ftPcAcReq);
                }
                else
                {
                    l_ftPaReq = 0.0f;
                }
                l_ftPbReq = l_ftPaReq;
                l_ftPcReq = l_ftPaReq;
            }
        }
		
        /* Reactive power */
        if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)    ///< Reactive power balance run mode
        {
            stComIfLoc.stPrmExt.ftQaReq = l_ftReactvPwr * ONE_PHASE_COEFF;
            stComIfLoc.stPrmExt.ftQbReq = stComIfLoc.stPrmExt.ftQaReq;
            stComIfLoc.stPrmExt.ftQcReq = stComIfLoc.stPrmExt.ftQaReq;
        }
        else    ///< Reactive power imbalance run mode
        {
            if(PHASE_N_EXIST_MODE == stComIfLoc.stPrmExt.uiModPfcNonPhaN)    ///< Exist phase N mode
            {
                stComIfLoc.stPrmExt.ftQaReq = stCom.ftQaAcReq;
                stComIfLoc.stPrmExt.ftQbReq = stCom.ftQbAcReq;
                stComIfLoc.stPrmExt.ftQcReq = stCom.ftQcAcReq;
            }
            else    ///< None phase N mode
            {
                if((stCom.ftQaAcReq > 0.0f) && (stCom.ftQbAcReq > 0.0f) && (stCom.ftQcAcReq > 0.0f))         ///< Both phase requests are positive
                {
                    stComIfLoc.stPrmExt.ftQaReq = ftFcn_MinOfThree(stCom.ftQaAcReq, stCom.ftQbAcReq, stCom.ftQcAcReq);
                }
                else if((stCom.ftQaAcReq < 0.0f) && (stCom.ftQbAcReq < 0.0f) && (stCom.ftQcAcReq < 0.0f))    ///< Both phase requests are negative
                {
                    stComIfLoc.stPrmExt.ftQaReq = ftFcn_MaxOfThree(stCom.ftQaAcReq, stCom.ftQbAcReq, stCom.ftQcAcReq);
                }
                else
                {
                    stComIfLoc.stPrmExt.ftQaReq = 0.0f;
                }
                stComIfLoc.stPrmExt.ftQbReq = stComIfLoc.stPrmExt.ftQaReq;
                stComIfLoc.stPrmExt.ftQcReq = stComIfLoc.stPrmExt.ftQaReq;
            }
        }
    }
    else    ///< Phase loss run mode
    {
        if(TYPE_GRID_AN == stCom.uiTypeGrid)
        {
		    /* Active power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
            {
                l_ftPaReq = l_ftActvPwr;
            }
            else                                               ///< Active power imbalance run mode
            {
                l_ftPaReq = stCom.ftPaAcReq;
            }
            l_ftPbReq = 0.0f;
            l_ftPcReq = 0.0f;
			
			/* Reactive power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)  ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQaReq = l_ftReactvPwr;
            }
            else                                               ///< Reactive power imbalance run mode
            {
                stComIfLoc.stPrmExt.ftQaReq = stCom.ftQaAcReq;
            }
            stComIfLoc.stPrmExt.ftQbReq = 0.0f;
            stComIfLoc.stPrmExt.ftQcReq = 0.0f;
        }
        else if(TYPE_GRID_BN == stCom.uiTypeGrid)
        {
		    /* Active power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
            {
                l_ftPbReq = l_ftActvPwr;
            }
            else                                               ///< Active power imbalance run mode
            {
                l_ftPbReq = stCom.ftPbAcReq;
            }
            l_ftPaReq = 0.0f;
            l_ftPcReq = 0.0f;
			
			/* Reactive power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)  ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQbReq = l_ftReactvPwr;
            }
            else                                               ///< Reactive power imbalance run mode
            {
                stComIfLoc.stPrmExt.ftQbReq = stCom.ftQbAcReq;
            }
            stComIfLoc.stPrmExt.ftQaReq = 0.0f;
            stComIfLoc.stPrmExt.ftQcReq = 0.0f;
        }
        else
        {
		    /* Active power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal)    ///< Active power balance run mode
            {
                l_ftPcReq = l_ftActvPwr;
            }
            else                                               ///< Active power imbalance run mode
            {
                l_ftPcReq = stCom.ftPcAcReq;
            }
            l_ftPaReq = 0.0f;
            l_ftPbReq = 0.0f;
			
			/* Reactive power */
            if(PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)  ///< Reactive power balance run mode
            {
                stComIfLoc.stPrmExt.ftQcReq = l_ftReactvPwr;
            }
            else                                               ///< Reactive power imbalance run mode
            {
                stComIfLoc.stPrmExt.ftQcReq = stCom.ftQcAcReq;
            }
            stComIfLoc.stPrmExt.ftQaReq = 0.0f;
            stComIfLoc.stPrmExt.ftQbReq = 0.0f;
        }
    }

    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC run state
    {
        vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPaReq, l_ftPaReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
        vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPbReq, l_ftPbReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
        vFcn_BidirRampDiffSlope(&stComIfLoc.stPrmExt.ftPcReq, l_ftPcReq, stComIfLoc.ftPowStepUp, stComIfLoc.ftPowStepDwn);
    }
    else
    {
        stComIfLoc.stPrmExt.ftPaReq = 0.0f;
        stComIfLoc.stPrmExt.ftPbReq = 0.0f;
        stComIfLoc.stPrmExt.ftPcReq = 0.0f;
    }

    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftPaReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);
    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftPbReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);
    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftPcReq, stComIfLoc.stPrmExt.ftPOnePhaMax, -stComIfLoc.stPrmExt.ftPOnePhaMax);
    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQaReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQbReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
    vFcn_FtUpDwnLim(&stComIfLoc.stPrmExt.ftQcReq, stCom.ftQOnePhaMax, -stCom.ftQOnePhaMax);
#endif

#if 1U == GRID_PHASE_NUMBER
    stComIfLoc.ftPwrActvReq = l_ftPaReq;
#elif 2U == GRID_PHASE_NUMBER
    stComIfLoc.ftPwrActvReq = l_ftPaReq + l_ftPbReq;
#elif 3U == GRID_PHASE_NUMBER
    stComIfLoc.ftPwrActvReq = l_ftPaReq + l_ftPbReq + l_ftPcReq;
#endif

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.ftPaReq = stComIfDbg.ftPaReq;
    stComIf.ftPbReq = stComIfDbg.ftPbReq;
    stComIf.ftPcReq = stComIfDbg.ftPcReq;
    stComIf.ftQaReq = stComIfDbg.ftQaReq;
    stComIf.ftQbReq = stComIfDbg.ftQbReq;
    stComIf.ftQcReq = stComIfDbg.ftQcReq;
#else
    stComIf.ftPaReq = stComIfLoc.stPrmExt.ftPaReq;
    stComIf.ftPbReq = stComIfLoc.stPrmExt.ftPbReq;
    stComIf.ftPcReq = stComIfLoc.stPrmExt.ftPcReq;
    stComIf.ftQaReq = stComIfLoc.stPrmExt.ftQaReq;
    stComIf.ftQbReq = stComIfLoc.stPrmExt.ftQbReq;
    stComIf.ftQcReq = stComIfLoc.stPrmExt.ftQcReq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D request update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_D2dReq_1ms(void)
{
    /* D2D Charge request update */
    v_ComIf_D2dReq_Chrg_1ms();
    /* D2D Discharge request update */
    v_ComIf_D2dReq_Dcha_1ms();
    /* Open-loop request update */
    v_ComIf_D2dReq_OL_1ms();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D Charge request update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_D2dReq_Chrg_1ms(void)
{
    /* D2D charge voltage request update */
    if(stCom.ftVoltBattChrgReq > VOLT_BATT_REQ_MAX)
    {
        stComIfLoc.stPrmExt.ftVoltBattChrgReq = VOLT_BATT_REQ_MAX;
    }
    else if((stCom.ftVoltBattChrgReq < VOLT_BATT_MIN) && (PFC_EN_D2D_EN == stCom.uiStgRunEnReq))
    {
        stComIfLoc.stPrmExt.ftVoltBattChrgReq = VOLT_BATT_MIN;
    }
    else
    {
        stComIfLoc.stPrmExt.ftVoltBattChrgReq = stCom.ftVoltBattChrgReq;
    }
    /* D2D charge current request update */
    if(stCom.ftCurrBattChrgReq > CURR_BATT_TGT_MAX)
    {
        stComIfLoc.stPrmExt.ftCurrBattChrgReq = CURR_BATT_TGT_MAX;
    }
    else if(stCom.ftCurrBattChrgReq < CURR_BATT_TGT_MIN)
    {
        stComIfLoc.stPrmExt.ftCurrBattChrgReq = CURR_BATT_TGT_MIN;
    }
    else
    {
        stComIfLoc.stPrmExt.ftCurrBattChrgReq = stCom.ftCurrBattChrgReq;
    }

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.ftVoltBattChrgReq = stComIfDbg.ftVoltBattChrgReq;
    stComIf.ftCurrBattChrgReq = stComIfDbg.ftCurrBattChrgReq;
#else
    stComIf.ftVoltBattChrgReq = stComIfLoc.stPrmExt.ftVoltBattChrgReq;
    stComIf.ftCurrBattChrgReq = stComIfLoc.stPrmExt.ftCurrBattChrgReq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D Discharge request update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_D2dReq_Dcha_1ms(void)
{
    /* D2D discharge voltage request update */
    if(stCom.ftVoltBattDchaReq > VOLT_BATT_MAX)
    {
        stComIfLoc.stPrmExt.ftVoltBattDchaReq = VOLT_BATT_MAX;
    }
    else if(stCom.ftVoltBattDchaReq < VOLT_BATT_REQ_MIN)
    {
        stComIfLoc.stPrmExt.ftVoltBattDchaReq = VOLT_BATT_REQ_MIN;
    }
    else
    {
        stComIfLoc.stPrmExt.ftVoltBattDchaReq = stCom.ftVoltBattDchaReq;
    }
    /* D2D discharge current request update */
    if(stCom.ftCurrBattDchaReq < -CURR_BATT_TGT_MAX)
    {
        stComIfLoc.stPrmExt.ftCurrBattDchaReq = -CURR_BATT_TGT_MAX;
    }
    else if(stCom.ftCurrBattDchaReq > -CURR_BATT_TGT_MIN)
    {
        stComIfLoc.stPrmExt.ftCurrBattDchaReq = -CURR_BATT_TGT_MIN;
    }
    else
    {
        stComIfLoc.stPrmExt.ftCurrBattDchaReq = stCom.ftCurrBattDchaReq;
    }

    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.ftVoltBattDchaReq = stComIfDbg.ftVoltBattDchaReq;
    stComIf.ftCurrBattDchaReq = stComIfDbg.ftCurrBattDchaReq;
#else
    stComIf.ftVoltBattDchaReq = stComIfLoc.stPrmExt.ftVoltBattDchaReq;
    stComIf.ftCurrBattDchaReq = stComIfLoc.stPrmExt.ftCurrBattDchaReq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D Open-loop request update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_D2dReq_OL_1ms(void)
{
    if(OPENLOOP_MODE == stComIfLoc.stPrmExt.uiModD2dRun)
    {
#if(3U != GRID_PHASE_NUMBER)
        /* D2D open-loop request update */
        stComIfLoc.ftFrqOLAbs = fabsf(stComTbl.stPrmComIf.ftFrqOLReq);

        if(stComIfLoc.ftFrqOLAbs < D2D_FRQ_MIN)    ///< D2D Min Frequency; 48000.0f
        {
            stComIfLoc.ftOutpOLAbsReq = 1.0f;
        }
        else if(stComIfLoc.ftFrqOLAbs < D2D_FRQ_MAX)    ///< D2D Max Frequency
        {
            stComIfLoc.ftOutpOLAbsReq = D2D_FRQ_MIN / stComIfLoc.ftFrqOLAbs;
        }
        else if(stComIfLoc.ftFrqOLAbs < FRQ_D2D_OPEN_LOOP_BURST_MAX)    ///< Open-loop Max Burst Freq
        {
            stComIfLoc.ftOutpOLAbsReq = COEFF_D2D_FRQ_MAX * (1.0f - COEFF_D2D_OPEN_LOOP_BURST * (stComIfLoc.ftFrqOLAbs - D2D_FRQ_MAX));
        }
        else
        {
            stComIfLoc.ftOutpOLAbsReq = 0.0f;
        }

        if(stComTbl.stPrmComIf.ftFrqOLReq > 0.0f)
        {
            stComIfLoc.stPrmExt.ftOutpOLReq = stComIfLoc.ftOutpOLAbsReq;
        }
        else
        {
            stComIfLoc.stPrmExt.ftOutpOLReq = -stComIfLoc.ftOutpOLAbsReq;
        }
#else
        if(stComTbl.stPrmComIf.ftDs1OLReq > OUTP_DAB_OL_MAX)
        {
            stComIfLoc.stPrmExt.ftOutpOLReq = OUTP_DAB_OL_MAX;
        }
        else if(stComTbl.stPrmComIf.ftDs1OLReq < OUTP_DAB_OL_MIN)
        {
            stComIfLoc.stPrmExt.ftOutpOLReq = OUTP_DAB_OL_MIN;
        }
        else
        {
            stComIfLoc.stPrmExt.ftOutpOLReq = stComTbl.stPrmComIf.ftDs1OLReq;
        }
#endif
    }
    /* Global Signal*/
#if (1U == COM_IF_DBG)
    stComIf.ftOutpOLReq = stComIfDbg.ftOutpOLReq;
#else
    stComIf.ftOutpOLReq = stComIfLoc.stPrmExt.ftOutpOLReq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_RstFlt_10ms(void)
{
    if(0U == stComIfLoc.uiFlgPowOnFltRst)    ///<  Flag of fault reset after power on is not set
    {
        if(1U == stComIf.uiFlgPowOn)
        {
            if(stComIfLoc.uiCntrCmdRst < 20U)
            {
                stComIfLoc.uiCntrCmdRst++;
                stComIfLoc.stPrmExt.uiFlgFltRst = FCN_ENABLE;
            }
            else
            {
                stComIfLoc.uiCntrCmdRst = 0U;
                stComIfLoc.uiFlgPowOnFltRst     = 1U;    ///< Set flag of fault reset after power on
                stComIfLoc.stPrmExt.uiFlgFltRst = FCN_DISABLE;
            }
        }
    }
    else    ///< Flag of fault reset after power on is set
    {
        if((SYS_FLT_RESET_IS_ON) || (FCN_ENABLE == stFltRstrt.uiCmdFltRstrt))    ///< Fault reset command || Fault restart conmmand
        {
            if(stComIfLoc.uiCntrCmdRst < 20U)
            {
                stComIfLoc.uiCntrCmdRst++;
                stComIfLoc.stPrmExt.uiFlgFltRst = FCN_ENABLE;
            }
            else
            {
                stComIfLoc.stPrmExt.uiFlgFltRst = FCN_DISABLE;
            }
        }
        else
        {
            stComIfLoc.uiCntrCmdRst = 0U;
            stComIfLoc.stPrmExt.uiFlgFltRst = FCN_DISABLE;
        }
    }

    /* Output Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiFlgFltRst = stComIfDbg.uiFlgFltRst;
#else
    stComIf.uiFlgFltRst = stComIfLoc.stPrmExt.uiFlgFltRst;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_ArmReq_10ms(void)
{
    if(OFFGRID_MODE == stComIfLoc.stPrmExt.uiModD2dRun)
    {
	    /* V2L Aux-power command judgment  */
        stComIfLoc.stPrmExt.uiCmdV2LAuxPow = (Uint16)((V2L_AUXPOW_EN_IS_ON) && (STOP_CMD == stCom.uiCmdRunReq));
        /* Bleed permitted flag judgment */
#if 0
        if(OUT_RLY_IS_OFF && \
           (((1U == stPerphCtrl.stV2LAuxPow.uiFlgEn) && INS_DET_ST_IS_OFF) \
            || ((0U == stPerphCtrl.stV2LAuxPow.uiFlgEn) && INS_DET_ST_IS_OFF)))
#else
        if(OUT_RLY_IS_OFF && INS_DET_ST_IS_OFF)
#endif
        {
            stComIfLoc.stPrmExt.uiFlgBldPtd = 1U;       ///< Set bleed permitted flag
        }
        else
        {
            stComIfLoc.stPrmExt.uiFlgBldPtd = 0U;       ///< Clear bleed permitted flag
        }
    }
    else
    {
        stComIfLoc.stPrmExt.uiCmdV2LAuxPow = 0U;        ///< Clear V2L Aux-power command flag
        /* Bleed permitted flag judgment */
        if((OUT_RLY_IS_OFF) || (INS_DET_ST_IS_ON))
        {
            stComIfLoc.stPrmExt.uiFlgBldPtd = 1U;       ///< Flag of bleed permitted
        }
        else
        {
            stComIfLoc.stPrmExt.uiFlgBldPtd = 0U;
        }
    }

#if (1U == COM_IF_DBG)
    stComIf.uiCmdV2LAuxPow = stComIfDbg.uiCmdV2LAuxPow;
    stComIf.uiFlgBldPtd    = stComIfDbg.uiFlgBldPtd;
#else
    stComIf.uiCmdV2LAuxPow = stComIfLoc.stPrmExt.uiCmdV2LAuxPow;
    stComIf.uiFlgBldPtd    = stComIfLoc.stPrmExt.uiFlgBldPtd;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_Bms_10ms(void)
{
    stComIfLoc.stPrmExt.ftVoltBattBms = stCom.ftVoltBattBms;
    stComIfLoc.stPrmExt.ftVoltBattBmsMax = stCom.ftVoltBattBmsMax;

#if (1U == COM_IF_DBG)
    stComIf.ftVoltBattBms        = stComIfDbg.ftVoltBattBms;
    stComIf.ftVoltBattBmsMax     = stComIfDbg.ftVoltBattBmsMax;
#else
    stComIf.ftVoltBattBms        = stComIfLoc.stPrmExt.ftVoltBattBms;
    stComIf.ftVoltBattBmsMax     = stComIfLoc.stPrmExt.ftVoltBattBmsMax;
#endif
}
/*********************************************End**********************************************/

#if(3U == GRID_PHASE_NUMBER)
/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_PfcReq_10ms(void)
{
    if(PHASE_LOSS_RUN_MODE == stComIfLoc.stPrmExt.uiModPfcPhaLoss)
    {
        stComIfLoc.stPrmExt.ftCoeffBusPreChrg = stComTbl.stPrmPowLim.ftCoeffBusPreChg1P;
    }
    else
    {
        stComIfLoc.stPrmExt.ftCoeffBusPreChrg = stComTbl.stPrmPowLim.ftCoeffBusPreChg3P;
    }

#if (1U == COM_IF_DBG)
    stComIf.ftCoeffBusPreChrg = stComIfDbg.ftCoeffBusPreChrg;
#else
    stComIf.ftCoeffBusPreChrg = stComIfLoc.stPrmExt.ftCoeffBusPreChrg;
#endif
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_AcOvLoad_100ms(void)
{
#ifndef _SIMULATION_NO_DSP_
    /* AC over load time accumulation */
    if((BIDIR_ONGRID_MODE == stComIfLoc.stPrmExt.uiModRun) || (OFFGRID_MODE == stComIfLoc.stPrmExt.uiModRun))
    {
        v_ComIf_AcOvLoad_TiAcm(stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax, &stComIfLoc.stPrmExt.ftRatSumTiOvLoad);

        if(stComIfLoc.stPrmExt.ftRatSumTiOvLoad > 1.0f)
        {
            stComIfLoc.stPrmExt.uiEnaAcOvLoad = 0U;                      ///< Clear AC over load enable flag
        }
        else if(stComIfLoc.stPrmExt.ftRatSumTiOvLoad < CON_ZERO_DELTA)
        {
            stComIfLoc.stPrmExt.uiEnaAcOvLoad = 1U;                      ///< Set AC over load enable flag
        }
        else
        {
            ///< Do nothing
        }
    }
    else
    {
        stComIfLoc.stPrmExt.ftRatSumTiOvLoad = 0.0f;
        stComIfLoc.stPrmExt.uiEnaAcOvLoad    = 0U;
    }
#endif
    /* Update AC&DC maximum power */
    if(1U == stComIfLoc.stPrmExt.uiEnaAcOvLoad)
    {
        stComIfLoc.stPrmExt.ftPAcMax = stComTbl.stPrmPfcRtd1.ftRatAcOvLoad * stComTbl.stPrmPfcRtd1.ftPowRtd;   ///< Max AC power
    }
    else
    {
        stComIfLoc.stPrmExt.ftPAcMax = stComTbl.stPrmPfcRtd1.ftPowRtd;                                         ///< Max battery power
    }

    /* Update AC current limit */
    if(stComTbl.stPrmPfcRtd1.ftVoltGrid > 1.0f)
    {
        stComIfLoc.stPrmExt.ftCurrAcRmsMax = COEFF_AC_CURR_CALC * (stComIfLoc.stPrmExt.ftPAcMax * ONE_PHASE_COEFF / stComTbl.stPrmPfcRtd1.ftVoltGrid);
        UP_LIMIT(stComIfLoc.stPrmExt.ftCurrAcRmsMax, stCom.ftCurrAcRmsLim);
    }
    stComIfLoc.stPrmExt.ftIdAcMax = stComIfLoc.stPrmExt.ftCurrAcRmsMax * CON_SQRT_2;
    stComIfLoc.stPrmExt.ftPOnePhaMax = stComIfLoc.stPrmExt.ftPAcMax * ONE_PHASE_COEFF;

    /* Output Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiEnaAcOvLoad      = stComIfDbg.uiEnaAcOvLoad;
    stComIf.ftRatSumTiOvLoad   = stComIfDbg.ftRatSumTiOvLoad;
    stComIf.ftPAcMax           = stComIfDbg.ftPAcMax;
    stComIf.ftPOnePhaMax       = stComIfDbg.ftPOnePhaMax;
    stComIf.ftCurrAcRmsMax     = stComIfDbg.ftCurrAcRmsMax;
    stComIf.ftIdAcMax          = stComIfDbg.ftIdAcMax;
#else
    stComIf.uiEnaAcOvLoad      = stComIfLoc.stPrmExt.uiEnaAcOvLoad;
    stComIf.ftRatSumTiOvLoad   = stComIfLoc.stPrmExt.ftRatSumTiOvLoad;
    stComIf.ftPAcMax           = stComIfLoc.stPrmExt.ftPAcMax;
    stComIf.ftPOnePhaMax       = stComIfLoc.stPrmExt.ftPOnePhaMax;
    stComIf.ftCurrAcRmsMax     = stComIfLoc.stPrmExt.ftCurrAcRmsMax;
    stComIf.ftIdAcMax          = stComIfLoc.stPrmExt.ftIdAcMax;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_AcOvLoad_TiAcm(float32 ftAprtPwr, float32 *ftRatSumTi)
{
    float32 l_ftRatAprtPwr = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftTiRunLim   = 0.0f;   ///< Initialize to 0.0f
    /* Enter apparent power ratio */
    l_ftRatAprtPwr = ftAprtPwr * stPfcDataCalc.stSysParm.ftPwrRtdRecpr * (float32)GRID_PHASE_NUMBER;
    /* AC over load inverse time limit curve */
#if (0)
    if(l_ftRatAprtPwr < RAT_AC_OV_LOAD_STRT)
    {
        l_ftTiRunLim = -TI_AC_OV_LOAD_RCV;
    }
    else
    {
        l_ftTiRunLim = TI_1MIN_BASE_100MS * INV_TI_CURVE_K / powf(l_ftRatAprtPwr, INV_TI_CURVE_R);   ///< 48us
    }
#else
    if(l_ftRatAprtPwr < RAT_AC_OV_LOAD_STRT)
    {
        l_ftTiRunLim = -TI_AC_OV_LOAD_RCV;
    }
    else
    {
        l_ftTiRunLim = ft_ComIf_AcOL_Time(l_ftRatAprtPwr, &ftACOLTimeTbl[0]);
    }
#endif
    /* AC over load time accumulation */
    if(FLOAT_PRM_IS_NOT_EQUAL(l_ftTiRunLim, 0.0f))
    {
        *ftRatSumTi += (1.0f / l_ftTiRunLim);
        DOWN_LIMIT(*ftRatSumTi, 0.0f);
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static float32 ft_ComIf_AcOL_Time(float32 ftRatAprtPwr, float32 *ftpTable)
{
    int16   l_siHigh = 0;       ///< High location
    int16   l_siLow  = 0;       ///< Low location
    float32 l_ftTmp  = 0.0f;
    float32 l_ftTmp1 = 0.0f;
    float32 l_ftTmp2 = 0.0f;
    float32 l_ftTime = 0.0f;

    if(ftRatAprtPwr <= RAT_AC_OV_LOAD_STRT + 0.01f)
    {
        l_ftTime = ftACOLTimeTbl[0];
    }
    else if(ftRatAprtPwr < RAT_AC_OV_LOAD_END)
    {
        l_ftTmp = (ftRatAprtPwr - RAT_AC_OV_LOAD_STRT) * AC_OL_TI_K - 1.0f;
        l_siLow = (int16)l_ftTmp;
        if(l_ftTmp - (float32)l_siLow < CON_ZERO_DELTA)
        {
            l_ftTime = *(ftpTable + l_siLow);
        }
        else
        {
            l_siHigh = l_siLow + 1;

            /* Interpolation method */
            l_ftTmp1 = l_ftTmp - (float32)l_siLow;
            l_ftTmp2 = *(ftpTable + l_siHigh) - *(ftpTable + l_siLow);
            l_ftTime = *(ftpTable + l_siLow) + l_ftTmp1 * l_ftTmp2;
        }
    }
    else
    {
        l_ftTime = ftACOLTimeTbl[AC_OL_TI_TBL_CNT - 1U];
    }

    return l_ftTime;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_PowOnJudg_100ms(void)
{
#ifndef _SIMULATION_NO_DSP_
    if(0U == stComIfLoc.stPrmExt.uiFlgPowOn)
    {
        stComIfLoc.uiCntrPowOn++;

        if(stComIfLoc.uiCntrPowOn >= 20U)           ///< Counter
        {
            stComIfLoc.uiCntrPowOn = 20U;
            stComIfLoc.stPrmExt.uiFlgPowOn = 1U;    ///< Power on flag
        }
    }
#else
    stComIfLoc.stPrmExt.uiFlgPowOn = 1U;
#endif

    /* Output Signal*/
#if (1U == COM_IF_DBG)
    stComIf.uiFlgPowOn = stComIfDbg.uiFlgPowOn;
#else
    stComIf.uiFlgPowOn = stComIfLoc.stPrmExt.uiFlgPowOn;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function:
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_ComIf_Temp_100ms(void)
{
    stComIfLoc.stPrmExt.ftTempArmBd = stCom.ftTempArmBd;    ///< ARM board temperature
    stComIfLoc.stPrmExt.ftTempNtc0 = stCom.ftTempNtc0;      ///< NTC0 temperature;
    stComIfLoc.stPrmExt.ftTempNtc1 = stCom.ftTempNtc1;      ///< NTC1 temperature;
    stComIfLoc.stPrmExt.ftTempNtc2 = stCom.ftTempNtc2;      ///< NTC2 temperature;
    stComIfLoc.stPrmExt.ftTempNtc3 = stCom.ftTempNtc3;      ///< NTC3 temperature;
    stComIfLoc.stPrmExt.ftTempNtc4 = stCom.ftTempNtc4;      ///< NTC4 temperature;
    stComIfLoc.stPrmExt.ftTempNtc5 = stCom.ftTempNtc5;      ///< NTC5 temperature;
    stComIfLoc.stPrmExt.ftTempNtc6 = stCom.ftTempNtc6;      ///< NTC6 temperature;

    /* Output Signal*/
#if (1U == COM_IF_DBG)
    stComIf.ftTempArmBd       = stComIfDbg.ftTempArmBd;
    stComIf.ftTempNtc0        = stComIfDbg.ftTempNtc0;
    stComIf.ftTempNtc1        = stComIfDbg.ftTempNtc1;
    stComIf.ftTempNtc2        = stComIfDbg.ftTempNtc2;
    stComIf.ftTempNtc3        = stComIfDbg.ftTempNtc3;
    stComIf.ftTempNtc4        = stComIfDbg.ftTempNtc4;
    stComIf.ftTempNtc5        = stComIfDbg.ftTempNtc5;
    stComIf.ftTempNtc6        = stComIfDbg.ftTempNtc6;
#else
    stComIf.ftTempArmBd       = stComIfLoc.stPrmExt.ftTempArmBd;
    stComIf.ftTempNtc0        = stComIfLoc.stPrmExt.ftTempNtc0;
    stComIf.ftTempNtc1        = stComIfLoc.stPrmExt.ftTempNtc1;
    stComIf.ftTempNtc2        = stComIfLoc.stPrmExt.ftTempNtc2;
    stComIf.ftTempNtc3        = stComIfLoc.stPrmExt.ftTempNtc3;
    stComIf.ftTempNtc4        = stComIfLoc.stPrmExt.ftTempNtc4;
    stComIf.ftTempNtc5        = stComIfLoc.stPrmExt.ftTempNtc5;
    stComIf.ftTempNtc6        = stComIfLoc.stPrmExt.ftTempNtc6;
#endif
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
