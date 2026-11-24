//========================================================================
// FILE          : PfcPowPreCtrl.c
// TITLE         : PFC Power Pre-Control Source File
//========================================================================
/* Copyright (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
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
* Module        : PfcPowPreCtrl
* 1st Unit      : PfcPowPreCtrl_PrmUpd
* 2nd Unit      : PfcPowPreCtrl_RefRamp
*
* Module Task   : v_PfcPowPreCtrl_Init()
*                 v_PfcPowPreCtrl_1ms()
*
* 1st Unit Task : v_PfcPowPreCtrl_PrmUpd_Init()
*                 v_PfcPowPreCtrl_PrmUpd_10ms()
* 2nd Unit Task : v_PfcPowPreCtrl_RefRamp_Init()
*                 v_PfcPowPreCtrl_RefRamp_1ms()
*
**************************************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcPowPreCtrl.h"
#include "PrmDisp.h"
//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_POW_PRE_CTRL stPfcPowPreCtrl;    ///< PFC power pre-control global struct

#if (1U == PFC_POW_PRE_CTRL_FLG_DBG)
ST_PFC_POW_PRE_CTRL stPfcPowPreCtrlDbg;    ///< PFC power pre-control debug global struct
#endif

static ST_PFC_POW_PRE_CTRL_LOC stPfcPowPreCtrlLoc;    ///< PFC power pre-control local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC power pre-control initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowPreCtrl_Init(void)
{
	v_PfcPowPreCtrl_PrmUpd_Init();     ///< PFC power pre-control parameter update initialization task
	v_PfcPowPreCtrl_RefRamp_Init();    ///< PFC power pre-control reference ramp calculation initial task

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcPowPreCtrl_Init() is running****\r\n");
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC power pre-control 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowPreCtrl_1ms(void)
{
	v_PfcPowPreCtrl_RefRamp_1ms();    ///< PFC power pre-control reference ramp calculation 1ms task

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PfcPowPreCtrl_1ms() is running****\r\n");
    }
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC power pre-control 10ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowPreCtrl_10ms(void)
{
    v_PfcPowPreCtrl_PrmUpd_10ms();    ///< PFC power pre-control parameter update 10ms task

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_PfcPowPreCtrl_10ms() is running****\r\n");
    }
#endif
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control parameter update initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_PrmUpd_Init(void)
{
    /* Local Signal*/
	stPfcPowPreCtrlLoc.ftTi1stOrdLpfResp = 10.0f;                   ///< 1st order LPF response time initialize to 10s
	stPfcPowPreCtrlLoc.ftTc1stOrdLpf     = 0.33333f * stPfcPowPreCtrlLoc.ftTi1stOrdLpfResp;    ///< Initialize 1st order LPF time constant
	stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf  = stPfcPowPreCtrlLoc.ftTc1stOrdLpf / (stPfcPowPreCtrlLoc.ftTc1stOrdLpf + PFC_RAMP_CTRL_CYC);    ///< Initialize 1st order LPF coefficient
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control parameter update 10ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_PrmUpd_10ms(void)
{
    if(FLOAT_PRM_IS_NOT_EQUAL(stPfcGridCtrl.stReactv.ftTi1stOrdLpfResp, stPfcPowPreCtrlLoc.ftTi1stOrdLpfResp))    ///< Reactive power first order LPF response time change
    {
        stPfcPowPreCtrlLoc.ftTi1stOrdLpfResp = stPfcGridCtrl.stReactv.ftTi1stOrdLpfResp;
        stPfcPowPreCtrlLoc.ftTc1stOrdLpf     = 0.33333f * stPfcPowPreCtrlLoc.ftTi1stOrdLpfResp;
        stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf  = stPfcPowPreCtrlLoc.ftTc1stOrdLpf / (stPfcPowPreCtrlLoc.ftTc1stOrdLpf + PFC_RAMP_CTRL_CYC);
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation initial task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_Init(void)
{
    /* Local Signal*/
    stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef     = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef     = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp  = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPc    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPc    = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftVoltRms                 = PFC_VOLT_AC_RMS_POW_CAL_MIN;      ///< Initialize to 5.0
    stPfcPowPreCtrlLoc.ftCoeffVoltRecpr          = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftPaRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftPbRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftPcRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftQaRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftQbRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftQcRef                   = 0.0f;                             ///< Initialize to 0
    stPfcPowPreCtrlLoc.ftVoltBusStep             = PFC_VOLT_BUS_1MS_STEP;            ///< Initialize to 0.5
    stPfcPowPreCtrlLoc.ftVoltAcAmpStep           = PFC_VOLT_AC_AMP_1MS_STEP;         ///< Initialize to 3.25
    /* Initialize power compensation PI */
    vFcn_InitPIPrm(&stPfcPowPreCtrlLoc.stPaCompPI);
    stPfcPowPreCtrlLoc.stPaCompPI.ftKp           = KP_POW_COMP;
    stPfcPowPreCtrlLoc.stPaCompPI.ftKi           = KI_POW_COMP;
    stPfcPowPreCtrlLoc.stPaCompPI.ftOutpMax      = MAX_POW_COMP;
    stPfcPowPreCtrlLoc.stPaCompPI.ftOutpMin      = MIN_POW_COMP;
    vFcn_InitPIPrm(&stPfcPowPreCtrlLoc.stQaCompPI);
    stPfcPowPreCtrlLoc.stQaCompPI.ftKp           = KP_POW_COMP;
    stPfcPowPreCtrlLoc.stQaCompPI.ftKi           = KI_POW_COMP;
    stPfcPowPreCtrlLoc.stQaCompPI.ftOutpMax      = MAX_POW_COMP;
    stPfcPowPreCtrlLoc.stQaCompPI.ftOutpMin      = MIN_POW_COMP;

    /* Output Signal*/
#if (1U == PFC_POW_PRE_CTRL_FLG_DBG)
    stPfcPowPreCtrlDbg.ftVoltBusRef     = stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef;
    stPfcPowPreCtrlDbg.ftIaActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
    stPfcPowPreCtrlDbg.ftIbActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef;
    stPfcPowPreCtrlDbg.ftIcActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef;
    stPfcPowPreCtrlDbg.ftIaReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;
    stPfcPowPreCtrlDbg.ftIbReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef;
    stPfcPowPreCtrlDbg.ftIcReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef;
    stPfcPowPreCtrlDbg.ftVoltAcAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef;
    stPfcPowPreCtrlDbg.ftDutyAmpRef     = stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef;
    stPfcPowPreCtrlDbg.ftReactvPowComp  = stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp;

    stPfcPowPreCtrl.ftVoltBusRef     = stPfcPowPreCtrlDbg.ftVoltBusRef;
    stPfcPowPreCtrl.ftIaActvAmpRef   = stPfcPowPreCtrlDbg.ftIaActvAmpRef;
    stPfcPowPreCtrl.ftIbActvAmpRef   = stPfcPowPreCtrlDbg.ftIbActvAmpRef;
    stPfcPowPreCtrl.ftIcActvAmpRef   = stPfcPowPreCtrlDbg.ftIcActvAmpRef;
    stPfcPowPreCtrl.ftIaReactvAmpRef = stPfcPowPreCtrlDbg.ftIaReactvAmpRef;
    stPfcPowPreCtrl.ftIbReactvAmpRef = stPfcPowPreCtrlDbg.ftIbReactvAmpRef;
    stPfcPowPreCtrl.ftIcReactvAmpRef = stPfcPowPreCtrlDbg.ftIcReactvAmpRef;
    stPfcPowPreCtrl.ftVoltAcAmpRef   = stPfcPowPreCtrlDbg.ftVoltAcAmpRef;
    stPfcPowPreCtrl.ftDutyAmpRef     = stPfcPowPreCtrlDbg.ftDutyAmpRef;
    stPfcPowPreCtrl.ftReactvPowComp  = stPfcPowPreCtrlDbg.ftReactvPowComp;
#else
    stPfcPowPreCtrl.ftVoltBusRef     = stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef;
    stPfcPowPreCtrl.ftIaActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
    stPfcPowPreCtrl.ftIbActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef;
    stPfcPowPreCtrl.ftIcActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef;
    stPfcPowPreCtrl.ftIaReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;
    stPfcPowPreCtrl.ftIbReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef;
    stPfcPowPreCtrl.ftIcReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef;
    stPfcPowPreCtrl.ftVoltAcAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef;
    stPfcPowPreCtrl.ftDutyAmpRef     = stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef;
    stPfcPowPreCtrl.ftReactvPowComp  = stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp;
#endif
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_1ms(void)
{
    /* X-CAP reactive power compensation */
    v_PfcPowPreCtrl_XCapComp();  ///< sst no use

    switch(stComIf.uiModPfcRun)
    {
    	case CHG_ONGRID_MODE:
    		v_PfcPowPreCtrl_RefRamp_Chrg();         ///< PFC power pre-control reference ramp calculation function in charge mode
    		break;

    	case BIDIR_ONGRID_MODE:
    		v_PfcPowPreCtrl_RefRamp_Bidir();        ///< PFC power pre-control reference ramp calculation function in bidirection mode
    		break;

    	case OFFGRID_MODE:
    		v_PfcPowPreCtrl_RefRamp_OffGrid();      ///< PFC power pre-control reference ramp calculation function in off-grid mode
    		break;

    	case OPENLOOP_MODE:
    		v_PfcPowPreCtrl_RefRamp_OL();           ///< PFC power pre-control reference ramp calculation function in open-loop mode
    		break;

    	default:
    		///< Do nothing
    		break;
    }

    /* Output Signal*/
#if (1U == PFC_POW_PRE_CTRL_FLG_DBG)
    stPfcPowPreCtrl.ftVoltBusRef     = stPfcPowPreCtrlDbg.ftVoltBusRef;
    stPfcPowPreCtrl.ftIaActvAmpRef   = stPfcPowPreCtrlDbg.ftIaActvAmpRef;
    stPfcPowPreCtrl.ftIbActvAmpRef   = stPfcPowPreCtrlDbg.ftIbActvAmpRef;
    stPfcPowPreCtrl.ftIcActvAmpRef   = stPfcPowPreCtrlDbg.ftIcActvAmpRef;
    stPfcPowPreCtrl.ftIaReactvAmpRef = stPfcPowPreCtrlDbg.ftIaReactvAmpRef;
    stPfcPowPreCtrl.ftIbReactvAmpRef = stPfcPowPreCtrlDbg.ftIbReactvAmpRef;
    stPfcPowPreCtrl.ftIcReactvAmpRef = stPfcPowPreCtrlDbg.ftIcReactvAmpRef;
    stPfcPowPreCtrl.ftVoltAcAmpRef   = stPfcPowPreCtrlDbg.ftVoltAcAmpRef;
    stPfcPowPreCtrl.ftDutyAmpRef     = stPfcPowPreCtrlDbg.ftDutyAmpRef;
    stPfcPowPreCtrl.ftReactvPowComp  = stPfcPowPreCtrlDbg.ftReactvPowComp;
#else
    stPfcPowPreCtrl.ftVoltBusRef     = stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef;
    stPfcPowPreCtrl.ftIaActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
    stPfcPowPreCtrl.ftIbActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef;
    stPfcPowPreCtrl.ftIcActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef;
    stPfcPowPreCtrl.ftIaReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;
    stPfcPowPreCtrl.ftIbReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef;
    stPfcPowPreCtrl.ftIcReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef;
    stPfcPowPreCtrl.ftVoltAcAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef;
    stPfcPowPreCtrl.ftDutyAmpRef     = stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef;
    stPfcPowPreCtrl.ftReactvPowComp  = stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp;
#endif
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control X-CAP reactive power compensation
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_XCapComp(void)
{
    stPfcPowPreCtrlLoc.ftVoltRms = stPfcDataCalc.stMeasParm.ftVgAvgRms;
    DOWN_LIMIT(stPfcPowPreCtrlLoc.ftVoltRms, PFC_VOLT_AC_RMS_POW_CAL_MIN);              ///< Down limit to 5.0f
    stPfcPowPreCtrlLoc.ftCoeffVoltRecpr = CON_SQRT_2 / stPfcPowPreCtrlLoc.ftVoltRms;    ///< 1.414f / ftVacRms

    stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp = SQUARE(stPfcPowPreCtrlLoc.ftVoltRms) * AC_INPUT_CAP_COEFF * stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF;    ///< Reactive power compensation
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation in charge mode
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_Chrg(void)
{
    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC running state
    {
        /* Bus voltage Reference Step */
        vFcn_RampSameSlope(&stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef, stPowLim.ftVoltBusLim, stPfcPowPreCtrlLoc.ftVoltBusStep);

    	/* X-CAP reactive current compensation calculation */
#if 0
        stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftReactvPowComp * stPfcPowPreCtrlLoc.ftCoeffVoltRecpr;
#endif
    }
    else    ///< PFC standby state
    {
#if 1U == FLG_PFC_POWCTRL_EN
    	stPfcPowPreCtrlLoc.stPrmExt.ftVoltBusRef     = stPfcAdc.ftVbusCellAvg;
#endif
    	stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef = 0.0f;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation in bidirection mode
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_Bidir(void)
{
    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC running state
    {
#if 1U == GRID_PHASE_NUMBER    ///< Single phase system
        /* Power limitation according to battery current request */
        v_PfcPowPreCtrl_CurrBattLim();

        /* Phase A reactive and active power ramp */
        vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQaRef, stPowLim.ftQaAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);
        if((0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt))
        {
            stPfcPowPreCtrlLoc.ftPaRef = stPowLim.ftPaAcLim;
            vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa);    ///< According to battery current limitation
            stPfcPowPreCtrlLoc.ftPaRef += PFC_ACTV_POW_COMP;    ///< Active power compensation for AuxPower
        }
        else if(0U == stPfcGridCtrl.stVrt.uiFlgIdRcvVrt)    ///< Not VRT Id recovery state
        {
            stPfcPowPreCtrlLoc.ftQaRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVaRms * RECPR_CON_SQRT_2;
        }
        else
        {
            ///< Do nothing
        }

        /* Phase A active and reactive power compensation: stPfcDataCalc.stMeasParm.slActvPowerLPF is positive in discharge mode*/
        v_PfcPowPreCtrl_PowComp(&stPfcPowPreCtrlLoc.ftPaRef, &stPfcPowPreCtrlLoc.ftQaRef, \
                                (float32)(-stPfcDataCalc.stMeasParm.slActvPowerLPF), (float32)(-(stPfcDataCalc.stMeasParm.slRePowerLPF)), \
                                &stPfcPowPreCtrlLoc.stPaCompPI, &stPfcPowPreCtrlLoc.stQaCompPI);

		/* Phase A active current and reactive reference calculation */
   		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVaRms, (stPfcPowPreCtrlLoc.ftPaRef + stPfcPowPreCtrlLoc.stPaCompPI.ftOutp), (stPfcPowPreCtrlLoc.ftQaRef + stPfcPowPreCtrlLoc.stQaCompPI.ftOutp), \
   		                            &stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef);
#elif 2U == GRID_PHASE_NUMBER    ///< Two phases system
        /* Power limitation according to battery current request */
        v_PfcPowPreCtrl_CurrBattLim();

        /* Phase A reactive and active power ramp */
        vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQaRef, stPowLim.ftQaAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);
        if((0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt))
        {
            stPfcPowPreCtrlLoc.ftPaRef = stPowLim.ftPaAcLim;
            vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa);    ///< According to battery current limitation
        }
        else if(0U == stPfcGridCtrl.stVrt.uiFlgIdRcvVrt)    ///< Not VRT Id recovery state
        {
            if((PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal) && (PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal))    ///< Balance run mode
            {
                stPfcPowPreCtrlLoc.ftQaRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVgAvgRms * RECPR_CON_SQRT_2;
            }
            else
            {
                stPfcPowPreCtrlLoc.ftQaRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVaRms * RECPR_CON_SQRT_2;
            }
        }
        else
        {
            ///< Do nothing
        }

    	if((PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal) && (PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal))    ///< Balance run mode
    	{
    		/* Phase A active and reactive current reference calculation */
       		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVgAvgRms, stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.ftQaRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef);
    		/* Phase B active and reactive current reference calculation */
        	stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
        	stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;
    	}
    	else
    	{
            /* Phase A active and reactive current reference calculation */
            v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVaRms, stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.ftQaRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef);

            /* Phase B reactive and active power ramp */
            vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQbRef, stPowLim.ftQbAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);
            if((0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt))
            {
                stPfcPowPreCtrlLoc.ftPbRef = stPowLim.ftPbAcLim;
                vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPbRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb);    ///< According to battery current limitation
            }
            else if(0U == stPfcGridCtrl.stVrt.uiFlgIdRcvVrt)    ///< Not Id recovery state of VRT
            {
                stPfcPowPreCtrlLoc.ftQbRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVbRms * RECPR_CON_SQRT_2;
            }
            else
            {
                ///< Do nothing
            }
            /* Phase B active and reactive current reference calculation */
            v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVbRms, stPfcPowPreCtrlLoc.ftPbRef, stPfcPowPreCtrlLoc.ftQbRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef);
    	}
#elif 3U == GRID_PHASE_NUMBER    ///< Three phases system
        /* Power limitation according to battery current request */
        v_PfcPowPreCtrl_CurrBattLim();

        /* Phase A reactive and active power ramp */
        vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQaRef, stPowLim.ftQaAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);
        if((0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt))
        {
            stPfcPowPreCtrlLoc.ftPaRef = stPowLim.ftPaAcLim;
            vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa);    ///< According to battery current limitation

        }
        else if(0U == stPfcGridCtrl.stVrt.uiFlgIdRcvVrt)    ///< Not VRT Id recovery state
        {
            if((PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal) && (PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal))    ///< Balance run mode
            {
                stPfcPowPreCtrlLoc.ftQaRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVgAvgRms * RECPR_CON_SQRT_2;
            }
            else
            {
                stPfcPowPreCtrlLoc.ftQaRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVaRms * RECPR_CON_SQRT_2;
            }
        }
        else
        {
            ///< Do nothing
        }

        if((PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal) && (PFC_BAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal))    ///< Balance run mode
    	{
    		/* Phase A active and reactive current reference calculation */
       		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVgAvgRms, stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.ftQaRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef);
    		/* Phase B active and reactive current reference calculation */
        	stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
        	stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;
    		/* Phase C active and reactive current reference calculation */
        	stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef   = stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef;
        	stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef = stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef;

    	}
    	else
    	{
    		/* Phase A active and reactive current reference calculation */
       		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVaRms, stPfcPowPreCtrlLoc.ftPaRef, stPfcPowPreCtrlLoc.ftQaRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef);

       		/* Phase B reactive power ramp */
       		vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQbRef, stPowLim.ftQbAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);
            /* Phase C reactive power ramp */
       		vFcn_1stOrdLPF(&stPfcPowPreCtrlLoc.ftQcRef, stPowLim.ftQcAcLim, stPfcPowPreCtrlLoc.ftCoeff1stOrdLpf);

            if((0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt))
            {
                /* Phase B active power ramp */
                stPfcPowPreCtrlLoc.ftPbRef = stPowLim.ftPbAcLim;
                vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPbRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb);    ///< According to battery current limitation

                /* Phase C active power ramp */
                stPfcPowPreCtrlLoc.ftPcRef = stPowLim.ftPcAcLim;
                vFcn_FtUpDwnLim(&stPfcPowPreCtrlLoc.ftPcRef, stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPc, stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPc);    ///< According to battery current limitation
            }
            else if(0U == stPfcGridCtrl.stVrt.uiFlgIdRcvVrt)    ///< Not Id recovery state of VRT
            {
                stPfcPowPreCtrlLoc.ftQbRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVbRms * RECPR_CON_SQRT_2;
                stPfcPowPreCtrlLoc.ftQcRef = stPfcGridCtrl.stVrt.ftIqPosRef * stPfcDataCalc.stMeasParm.ftVcRms * RECPR_CON_SQRT_2;
            }
            else
            {
                ///< Do nothing
            }

    		/* Phase B active and reactive current reference calculation */
      		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVbRms, stPfcPowPreCtrlLoc.ftPbRef, stPfcPowPreCtrlLoc.ftQbRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef);
    		/* Phase C active and reactive current reference calculation */
      		v_PfcPowPreCtrl_CurrRefCalc(stPfcDataCalc.stMeasParm.ftVcRms, stPfcPowPreCtrlLoc.ftPcRef, stPfcPowPreCtrlLoc.ftQcRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef, &stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef);
     	}
#endif
    }
    else
    {
    	stPfcPowPreCtrlLoc.ftPaRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.ftQaRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIaActvAmpRef   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIaReactvAmpRef = 0.0f;
    	stPfcPowPreCtrlLoc.ftPbRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.ftQbRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIbActvAmpRef   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIbReactvAmpRef = 0.0f;
    	stPfcPowPreCtrlLoc.ftPcRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.ftQcRef                   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIcActvAmpRef   = 0.0f;
    	stPfcPowPreCtrlLoc.stPrmExt.ftIcReactvAmpRef = 0.0f;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference power limitation according to battery current request
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_CurrBattLim(void)
{
    float32 l_ftPowLimSum   = 1.0f;    ///< Total AC active power limitation
    float32 l_ftCoeffPowLim = 1.0f;    ///< Coefficient of active power limitation

    l_ftPowLimSum = stPowLim.ftPaAcLim + stPowLim.ftPbAcLim + stPowLim.ftPcAcLim;    ///< Total AC active power limitation of three phase
    if(l_ftPowLimSum > CON_ZERO_DELTA)    ///< Total AC active power limitation is greater than 0
    {
        l_ftCoeffPowLim = 1.0f / l_ftPowLimSum;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa = fabsf(stPowLim.ftPaAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrChrgLim;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb = fabsf(stPowLim.ftPbAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrChrgLim;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPc = fabsf(stPowLim.ftPcAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrChrgLim;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa = -stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb = -stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPc = -stComIf.ftPOnePhaMax;
    }
    else if(l_ftPowLimSum < (-CON_ZERO_DELTA))    ///< Total AC active power limitation is less than 0
    {
        l_ftCoeffPowLim = 1.0f / l_ftPowLimSum;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPc = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa = fabsf(stPowLim.ftPaAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrDchaLim;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb = fabsf(stPowLim.ftPbAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrDchaLim;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPc = fabsf(stPowLim.ftPcAcLim * l_ftCoeffPowLim) * stPowLim.ftPowBattCurrDchaLim;
    }
    else    ///< Total AC active power limitation is 0
    {
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPa = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPb = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattChrgLim.ftPc = stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPa = -stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPb = -stComIf.ftPOnePhaMax;
        stPfcPowPreCtrlLoc.stCurrBattDchaLim.ftPc = -stComIf.ftPOnePhaMax;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation in off-grid mode
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_OffGrid(void)
{
    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC running state
    {
        vFcn_RampSameSlope(&stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef, stPowLim.ftVoltAcAmpLim, stPfcPowPreCtrlLoc.ftVoltAcAmpStep);
    }
    else
    {
    	stPfcPowPreCtrlLoc.stPrmExt.ftVoltAcAmpRef = 0.0f;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation in open-loop mode
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_RefRamp_OL(void)
{
    if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)    ///< PFC running state
    {
#if(1U == GRID_PHASE_NUMBER)
        vFcn_RampSameSlope(&stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef, 1.0f, PFC_DUTY_AMP_STEP);
#else
        vFcn_RampSameSlope(&stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef, stComTbl.stPrmOffGridCtrl.ftVoltAcDbgSet, PFC_DUTY_AMP_STEP);
#endif
    }
    else
    {
    	stPfcPowPreCtrlLoc.stPrmExt.ftDutyAmpRef = 0.0f;
    }
}

#if(1U == GRID_PHASE_NUMBER)
/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control power compensation in bidirection mode
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_PowComp(float32 *ftPRef, float32 *ftQRef, float32 ftP,  float32 ftQ, ST_PI_PRM *stPCompPI, ST_PI_PRM *stQCompPI)
{
    static Uint16 sl_uiPowCompCntr = 0U;    ///< 1ms counter

    sl_uiPowCompCntr++;
    if(sl_uiPowCompCntr >= 100U)    ///< Execute per 100ms
    {
        if(PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt)
        {
            /* Active power compensation */
            (*stPCompPI).ftInp = *ftPRef - ftP;       ///< *ftPRef is negative in discharge mode
            vFcn_PosnPICtrl(&(*stPCompPI));                      ///< PI control
            /* Active power compensation */
            (*stQCompPI).ftInp = *ftQRef - ftQ;
            vFcn_PosnPICtrl(&(*stQCompPI));                      ///< PI control
        }
        else
        {
            /* Initialize active power compensation PI parameter */
            vFcn_InitPIPrm(&(*stPCompPI));
            /* Initialize reactive power compensation PI parameter */
            vFcn_InitPIPrm(&(*stQCompPI));
        }

        sl_uiPowCompCntr = 0U;    ///< Clear counter
    }
}
#endif

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power pre-control reference ramp calculation in open-loop mode
* @Signal [in]  : ftVacRms
* @Signal [in]  : ftPRef
* @Signal [in]  : ftQRef
* @Signal [out] : ftIActvAmpRef
* @Signal [out] : ftIReactvAmpRef
* @return       : null
***********************************************************************************************/
static void v_PfcPowPreCtrl_CurrRefCalc(float32 ftVacRms, float32 ftPRef, float32 ftQRef, float32 *ftIActvAmpRef, float32 *ftIReactvAmpRef)
{
    float32 l_ftISq   = 0.0f;    ///< Square of Apparent current
    float32 l_ftIdLim = 0.0f;    ///< Active power limitation
    float32 l_ftTmp   = 0.0f;    ///< Temporary variable
    float32 l_ftILim  = 0.0f;

	stPfcPowPreCtrlLoc.ftVoltRms = ftVacRms;
	DOWN_LIMIT(stPfcPowPreCtrlLoc.ftVoltRms, PFC_VOLT_AC_RMS_POW_CAL_MIN);              ///< Down limit to 5.0f
	stPfcPowPreCtrlLoc.ftCoeffVoltRecpr = CON_SQRT_2 / stPfcPowPreCtrlLoc.ftVoltRms;    ///< 1.414f / ftVacRms
	/* Phase reactive and active current calculation */
    *ftIReactvAmpRef = ftQRef * stPfcPowPreCtrlLoc.ftCoeffVoltRecpr;
    if((1U == stPfcGridCtrl.stVrt.uiFlgHvrt) || (1U == stPfcGridCtrl.stVrt.uiFlgLvrt))
	{
	    *ftIActvAmpRef = -stPfcGridCtrl.stVrt.ftIdPosRef;
	}
	else
	{
	    *ftIActvAmpRef = ftPRef * stPfcPowPreCtrlLoc.ftCoeffVoltRecpr;    ///< Active current reference
	}

	/* Phase active current limitation */
    vFcn_FtUpDwnLim(&(*ftIReactvAmpRef), stCom.ftIqAcRtd, -stCom.ftIqAcRtd);    ///< Phase reactive current limitation
	l_ftISq = SQUARE(*ftIReactvAmpRef) + SQUARE(*ftIActvAmpRef);
	l_ftILim = stComIf.ftIdAcMax * stPowLim.ftCoeffTemp;

	if(l_ftISq > SQUARE(l_ftILim))               ///< Apparent power current is lager than rated current
	{
	    l_ftTmp = SQUARE(l_ftILim) - SQUARE(*ftIReactvAmpRef);
	    if(l_ftTmp > 0.0f)
	    {
	        l_ftIdLim = sqrtf(l_ftTmp);
	    }
	    else
	    {
	        vFcn_FtUpDwnLim(&(*ftIReactvAmpRef), l_ftILim, -l_ftILim);
	        l_ftIdLim = 0.0f;
	    }
	}
	else
	{
	    l_ftIdLim = stComIf.ftIdAcMax;
	}
	vFcn_FtUpDwnLim(&(*ftIActvAmpRef), l_ftIdLim, -l_ftIdLim);    ///< Limitation process
	
    /* Phase reactive current calculation and limitation */
    l_ftTmp = CON_SQRT_2 * stPfcPowPreCtrlLoc.ftVoltRms * AC_INPUT_CAP_COEFF * stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF;    ///< X-cap reactive power compensation
    *ftIReactvAmpRef += l_ftTmp;
    vFcn_FtUpDwnLim(&(*ftIReactvAmpRef), stCom.ftIqAcRtd, -stCom.ftIqAcRtd);
#if 0U == AI_DSTBC_VG_ZERO_MODE
    *ftIReactvAmpRef += stPfcGridCtrl.stDstbc.ftIqAiDstbc;
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
