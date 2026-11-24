//========================================================================
// FILE          : Comm.c
// TITLE         : CAN Communication Source File
//========================================================================
/* Copyright (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Created by    : Ricky
* Created date  : 2023.7.12
* Version       : v1.0
* Descriptions  :
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
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
* @file         Comm.c
* @brief        CAN Communication function
* @details
* @author       Ricky
* @date         2023.7.12
* @version      v1.0
* @copyright    (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* @attention
* MCU:              TMS320F2837xD \n
* Environment:      CCS v10.4.0
* @par Log Information:
* <table>
* <tr><th>Date         <th>Version       <th>Author       <th>Description
* <tr><td>2023.7.12    <td>1.0           <td>Ricky        <td>Initial Version
* </table>
*
**************************************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//=====================================================
//    Include Header Files
//=====================================================
#include "Com.h"

//=====================================================
//    Variable Definition
//=====================================================
#if(1U == FLG_CPU2_UPD_EN)
#pragma DATA_SECTION(stPrmC1ToC2, "Cpu1ToCpu2MsgRAM");
#pragma DATA_SECTION(stPrmC2ToC1, "Cpu2ToCpu1MsgRAM");
ST_C1_TO_C2_PRM stPrmC1ToC2;
ST_C2_TO_C1_PRM stPrmC2ToC1;
#endif

ST_COM stCom;
ST_COM_TBL stComTbl;

#if (1U == COM_DBG)
ST_COM stComDbg;
#endif

ST_COM_LOC stComLoc;

//=====================================================
//    Function definition
//=====================================================

/**
* @brief   CAN Initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_Com_Init(void)
{
    v_Com_PrmInit();    ///< Parameter Initial

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_Com_Init() is running****\r\n");
#endif
}

/**
* @brief   Com 100ms Process function
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
void v_Com_100ms(void)
{
    v_Com_Tsk_PfcZeroAdj_100ms();

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_Com_100ms() is running****\r\n");
    }
#endif
}
#endif
/**
* @brief   Com 1s Process function
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
void v_Com_1s(void)
{
    stComLoc.stPrmExt.uiComFailCntr++;

    /* Vout Interval Counter */
    if(stComLoc.BattVolt.uiCntrIntl > 0U)
    {
        stComLoc.BattVolt.uiCntrIntl--;
    }
    /* Vout Down Interval Counter */
    if(stComLoc.BattDnVolt.uiCntrIntl > 0U)
    {
        stComLoc.BattDnVolt.uiCntrIntl--;
    }
    /* Iout Interval Counter */
    if(stComLoc.BattCurr.uiCntrIntl > 0U)
    {
        stComLoc.BattCurr.uiCntrIntl--;
    }
    /* Iout Down Interval Counter */
    if(stComLoc.BattDnCurr.uiCntrIntl > 0U)
    {
        stComLoc.BattDnCurr.uiCntrIntl--;
    }

    /* Self test */
    if(FCN_ENABLE == stCom.uiEnaSelfTest)    ///< stComLoc.stPrmExt.uiEnaSelfTest
    {
        stComLoc.uiSelfTestCnt++;
        if(stComLoc.uiSelfTestCnt > SELF_TEST_OVER_TIME)
        {
            stComLoc.stPrmExt.uiFltSelfTest = 1U;
        }

        if((1U == stComLoc.stPrmExt.uiFltSelfTest) || (SELF_TEST_STS_END == stPfcGridCtrl.stGridDet.uiStsSelfTest))
        {
            stCom.uiEnaSelfTest = FCN_DISABLE;    ///< stComLoc.stPrmExt.uiEnaSelfTest
            stComLoc.uiSelfTestCnt = 0U;
        }
    }
    else
    {
        stComLoc.uiSelfTestCnt = 0U;
    }

    if((1U == stComLoc.stPrmExt.uiFltSelfTest) && (SYS_FLT_RESET_IS_ON))
    {
        stComLoc.stPrmExt.uiFltSelfTest = 0U;
    }

    /* Global Signal*/
#if (1U == COM_DBG)
    stCom.uiComFailCntr = stComDbg.uiComFailCntr;
    stCom.uiFltSelfTest = stComDbg.uiFltSelfTest;
#else
    stCom.uiComFailCntr = stComLoc.stPrmExt.uiComFailCntr;
    stCom.uiFltSelfTest = stComLoc.stPrmExt.uiFltSelfTest;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1s)
    {
        printf("****SWIT DynamicTest: function v_Com_1s() is running****\r\n");
    }
#endif
}
#endif
/**
* @brief   Non erasable parameter initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_Com_NonEraPrm_Init(void)
{
    ///< Calibration Initial
#if(3U != GRID_PHASE_NUMBER)
    stComLoc.stPrmExt.ftCoeffKBattVoltCal         = 1.0f;
    stComLoc.stPrmExt.ftCoeffBBattVoltCal         = 0.0f;
    stComLoc.stPrmExt.ftCoeffKBattCurrCal         = 1.0f;
    stComLoc.stPrmExt.ftCoeffBBattCurrCal         = 0.0f;
    stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal      = 1.0f;
    stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal      = 0.0f;
    stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal      = 1.0f;
    stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal      = 0.0f;
#else
    stComLoc.stPrmExt.ftCoeffKBattVoltCal         = 1.018802f;    ///< B2:1.018802
    stComLoc.stPrmExt.ftCoeffBBattVoltCal         = 0.472763f;    ///< B2:0.472763
    stComLoc.stPrmExt.ftCoeffKBattCurrCal         = 1.036817f;    ///< B2:1.036817
    stComLoc.stPrmExt.ftCoeffBBattCurrCal         = 2.878298f;    ///< B2:2.878298
    stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal      = 1.014885f;    ///< B2:1.014885
    stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal      = -0.1352844f;  ///< B2:-0.1352844
    stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal      = 0.9618717f;   ///< B2:0.9618717
    stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal      = 1.054497f;    ///< B2:1.054497
#endif	
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftInK      = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaInvK   = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbInvK   = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVBusK    = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVPosBusK = 1.0f;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVNegBusK = 1.0f;

    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siBusVoltZero    = AD_BIAS_BUS_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siPosBusVoltZero = AD_BIAS_BUS_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siNegBusVoltZero = AD_BIAS_BUS_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_A       = AD_BIAS_GRID_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_B       = AD_BIAS_GRID_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_C       = AD_BIAS_GRID_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_A    = AD_BIAS_GRID_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_B    = AD_BIAS_GRID_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_A       = AD_BIAS_GRID_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_B       = AD_BIAS_GRID_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_C       = AD_BIAS_GRID_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_N       = AD_BIAS_GRID_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_A     = AD_BIAS_DC_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_B     = AD_BIAS_DC_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_C     = AD_BIAS_DC_VOLT;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A     = AD_BIAS_DC_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B     = AD_BIAS_DC_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C     = AD_BIAS_DC_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A_N   = AD_BIAS_DC_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B_N   = AD_BIAS_DC_CURR;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C_N   = AD_BIAS_DC_CURR;

    //Battery Voltage Initial
    stComLoc.BattVolt.ftRatRxPrm  = RECPR_COEFF_VOLT_ARM;
    stComLoc.BattVolt.ftCoeffK    = stComLoc.stPrmExt.ftCoeffKBattVoltCal;    ///< Need After Read EEprom
    stComLoc.BattVolt.ftCoeffB    = stComLoc.stPrmExt.ftCoeffBBattVoltCal;

    stComLoc.BattVolt.ftCoeffKMax = ADJ_COFK_MAX;                 ///< Max Coeffk
    stComLoc.BattVolt.ftCoeffKMin = ADJ_COFK_MIN;                 ///< Min Coeffk
    stComLoc.BattVolt.ftCoeffBMax = VOLT_ADJ_COFB_MAX;            ///< Max CoeffB
    stComLoc.BattVolt.ftCoeffBMin = VOLT_ADJ_COFB_MIN;            ///< Min CoeffB

    stComLoc.BattVolt.uiAddrCoeffK = VOUT_ADJ_COFK_NUM;           ///< Coeffk address
    stComLoc.BattVolt.uiAddrCoeffB = VOUT_ADJ_COFB_NUM;           ///< CoeffB address
    stComLoc.BattVolt.uiCntrIntl   = 0U;

    //Battery Down Voltage Initial
    stComLoc.BattDnVolt.ftRatRxPrm = RECPR_COEFF_VOLT_ARM;
    stComLoc.BattDnVolt.ftCoeffK   = stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal;
    stComLoc.BattDnVolt.ftCoeffB   = stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal;

    stComLoc.BattDnVolt.ftCoeffKMax = ADJ_COFK_MAX;               ///< Max Coeffk
    stComLoc.BattDnVolt.ftCoeffKMin = ADJ_COFK_MIN;               ///< Min Coeffk
    stComLoc.BattDnVolt.ftCoeffBMax = VOLT_ADJ_COFB_MAX;          ///< Max CoeffB
    stComLoc.BattDnVolt.ftCoeffBMin = VOLT_ADJ_COFB_MIN;          ///< Min CoeffB

    stComLoc.BattDnVolt.uiAddrCoeffK = VOUT_DN_ADJ_COFK_NUM;      ///< Coeffk address
    stComLoc.BattDnVolt.uiAddrCoeffB = VOUT_DN_ADJ_COFB_NUM;      ///< CoeffB address
    stComLoc.BattDnVolt.uiCntrIntl   = 0U;

    //Battery Current Initial
    stComLoc.BattCurr.ftRatRxPrm = RECPR_COEFF_CURR_ARM;
    stComLoc.BattCurr.ftCoeffK   = stComLoc.stPrmExt.ftCoeffKBattCurrCal;
    stComLoc.BattCurr.ftCoeffB   = stComLoc.stPrmExt.ftCoeffBBattCurrCal;

    stComLoc.BattCurr.ftCoeffKMax = ADJ_COFK_MAX;                 ///< Max Coeffk
    stComLoc.BattCurr.ftCoeffKMin = ADJ_COFK_MIN;                 ///< Min Coeffk
    stComLoc.BattCurr.ftCoeffBMax = CURR_ADJ_COFB_MAX;            ///< Max CoeffB
    stComLoc.BattCurr.ftCoeffBMin = CURR_ADJ_COFB_MIN;            ///< Min CoeffB

    stComLoc.BattCurr.uiAddrCoeffK = IOUT_ADJ_COFK_NUM;           ///< Coeffk address
    stComLoc.BattCurr.uiAddrCoeffB = IOUT_ADJ_COFB_NUM;           ///< CoeffB address
    stComLoc.BattCurr.uiCntrIntl   = 0U;

    //Battery Down Current Initial
    stComLoc.BattDnCurr.ftRatRxPrm = RECPR_COEFF_CURR_ARM;
    stComLoc.BattDnCurr.ftCoeffK   = stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal;
    stComLoc.BattDnCurr.ftCoeffB   = stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal;

    stComLoc.BattDnCurr.ftCoeffKMax = ADJ_COFK_MAX;               ///< Max Coeffk
    stComLoc.BattDnCurr.ftCoeffKMin = ADJ_COFK_MIN;               ///< Min Coeffk
    stComLoc.BattDnCurr.ftCoeffBMax = CURR_ADJ_COFB_MAX;          ///< Max CoeffB
    stComLoc.BattDnCurr.ftCoeffBMin = CURR_ADJ_COFB_MIN;          ///< Min CoeffB

    stComLoc.BattDnCurr.uiAddrCoeffK = IOUT_DN_ADJ_COFK_NUM;      ///< Coeffk address
    stComLoc.BattDnCurr.uiAddrCoeffB = IOUT_DN_ADJ_COFB_NUM;      ///< CoeffB address
    stComLoc.BattDnCurr.uiCntrIntl   = 0U;

    stComLoc.stPrmExt.ftCurrAcRmsLim = RATED_AC_CURR_RMS;         ///< AC current RMS limit
#if(1U == GRID_PHASE_NUMBER)
    stComLoc.stPrmExt.uiTypeGrid     = TYPE_GRID_AN;
    /* Grid standard */
#if(GB_GRID_STD == GRID_STD_ID)
    stComLoc.stPrmExt.uiStdGridSet = NBT32004;                  ///< GB
#else
    stComLoc.stPrmExt.uiStdGridSet = EN50549;                   ///< EN50549
#endif

#elif(2U == GRID_PHASE_NUMBER)
    stComLoc.stPrmExt.uiTypeGrid   = TYPE_GRID_ABN;
    stComLoc.stPrmExt.uiStdGridSet = IEEE1547;                  ///< IEEE1547
#else
    stComLoc.stPrmExt.uiTypeGrid   = TYPE_GRID_ABCN;
    /* Grid standard */
#if(GB_GRID_STD == GRID_STD_ID)
    stComLoc.stPrmExt.uiStdGridSet = NBT32004;                  ///< GB
#else
    stComLoc.stPrmExt.uiStdGridSet = VDE4105;                   ///< VDE4105
#endif
#endif

    /* Output parameter */
#if (1U == COM_DBG)
    stComDbg.ftCoeffKBattVoltCal            = stComLoc.stPrmExt.ftCoeffKBattVoltCal;
    stComDbg.ftCoeffBBattVoltCal            = stComLoc.stPrmExt.ftCoeffBBattVoltCal;
    stComDbg.ftCoeffKBattCurrCal            = stComLoc.stPrmExt.ftCoeffKBattCurrCal;
    stComDbg.ftCoeffBBattCurrCal            = stComLoc.stPrmExt.ftCoeffBBattCurrCal;
    stComDbg.ftCoeffKBattDwnVoltCal         = stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal;
    stComDbg.ftCoeffBBattDwnVoltCal         = stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal;
    stComDbg.ftCoeffKBattDwnCurrCal         = stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal;
    stComDbg.ftCoeffBBattDwnCurrCal         = stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal;
    stComDbg.stPrmPfcAdjCoeff.ftVaK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK;
    stComDbg.stPrmPfcAdjCoeff.ftIaK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK;
    stComDbg.stPrmPfcAdjCoeff.ftVbK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK;
    stComDbg.stPrmPfcAdjCoeff.ftIbK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK;
    stComDbg.stPrmPfcAdjCoeff.ftVcK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK;
    stComDbg.stPrmPfcAdjCoeff.ftIcK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK;
    stComDbg.stPrmPfcAdjCoeff.ftInK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftInK;
    stComDbg.stPrmPfcAdjCoeff.ftVaInvK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaInvK;
    stComDbg.stPrmPfcAdjCoeff.ftVbInvK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbInvK;
    stComDbg.stPrmPfcAdjCoeff.ftVBusK          = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVBusK;
    stComDbg.stPrmPfcAdjCoeff.ftVPosBusK       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVPosBusK;
    stComDbg.stPrmPfcAdjCoeff.ftVNegBusK       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVNegBusK;
    stComDbg.stPrmPfcAdjCoeff.siBusVoltZero    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siBusVoltZero;
    stComDbg.stPrmPfcAdjCoeff.siPosBusVoltZero = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siPosBusVoltZero;
    stComDbg.stPrmPfcAdjCoeff.siNegBusVoltZero = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siNegBusVoltZero;
    stComDbg.stPrmPfcAdjCoeff.siVgZero_A       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_A;
    stComDbg.stPrmPfcAdjCoeff.siVgZero_B       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_B;
    stComDbg.stPrmPfcAdjCoeff.siVgZero_C       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_C;
    stComDbg.stPrmPfcAdjCoeff.siVgInvZero_A    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_A;
    stComDbg.stPrmPfcAdjCoeff.siVgInvZero_B    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_B;
    stComDbg.stPrmPfcAdjCoeff.siIgZero_A       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_A;
    stComDbg.stPrmPfcAdjCoeff.siIgZero_B       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_B;
    stComDbg.stPrmPfcAdjCoeff.siIgZero_C       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_C;
    stComDbg.stPrmPfcAdjCoeff.siVgDcZero_A     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_A;
    stComDbg.stPrmPfcAdjCoeff.siVgDcZero_B     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_B;
    stComDbg.stPrmPfcAdjCoeff.siVgDcZero_C     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_C;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_A     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_B     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_C     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_A_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A_N;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_B_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B_N;
    stComDbg.stPrmPfcAdjCoeff.siIgDcZero_C_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C_N;
    stComDbg.uiStdGridSet                      = stComLoc.stPrmExt.uiStdGridSet;
    stComDbg.ftCurrAcRmsLim                    = stComLoc.stPrmExt.ftCurrAcRmsLim;
    stComDbg.uiTypeGrid                        = stComLoc.stPrmExt.uiTypeGrid;

    stCom.ftCoeffKBattVoltCal               = stComDbg.ftCoeffKBattVoltCal;
    stCom.ftCoeffBBattVoltCal               = stComDbg.ftCoeffBBattVoltCal;
    stCom.ftCoeffKBattCurrCal               = stComDbg.ftCoeffKBattCurrCal;
    stCom.ftCoeffBBattCurrCal               = stComDbg.ftCoeffBBattCurrCal;
    stCom.ftCoeffKBattDwnVoltCal            = stComDbg.ftCoeffKBattDwnVoltCal;
    stCom.ftCoeffBBattDwnVoltCal            = stComDbg.ftCoeffBBattDwnVoltCal;
    stCom.ftCoeffKBattDwnCurrCal            = stComDbg.ftCoeffKBattDwnCurrCal;
    stCom.ftCoeffBBattDwnCurrCal            = stComDbg.ftCoeffBBattDwnCurrCal;
    stCom.stPrmPfcAdjCoeff.ftVaK            = stComDbg.stPrmPfcAdjCoeff.ftVaK;
    stCom.stPrmPfcAdjCoeff.ftIaK            = stComDbg.stPrmPfcAdjCoeff.ftIaK;
    stCom.stPrmPfcAdjCoeff.ftVbK            = stComDbg.stPrmPfcAdjCoeff.ftVbK;
    stCom.stPrmPfcAdjCoeff.ftIbK            = stComDbg.stPrmPfcAdjCoeff.ftIbK;
    stCom.stPrmPfcAdjCoeff.ftVcK            = stComDbg.stPrmPfcAdjCoeff.ftVcK;
    stCom.stPrmPfcAdjCoeff.ftIcK            = stComDbg.stPrmPfcAdjCoeff.ftIcK;
    stCom.stPrmPfcAdjCoeff.ftInK            = stComDbg.stPrmPfcAdjCoeff.ftInK;
    stCom.stPrmPfcAdjCoeff.ftVaInvK         = stComDbg.stPrmPfcAdjCoeff.ftVaInvK;
    stCom.stPrmPfcAdjCoeff.ftVbInvK         = stComDbg.stPrmPfcAdjCoeff.ftVbInvK;
    stCom.stPrmPfcAdjCoeff.ftVBusK          = stComDbg.stPrmPfcAdjCoeff.ftVBusK;
    stCom.stPrmPfcAdjCoeff.ftVPosBusK       = stComDbg.stPrmPfcAdjCoeff.ftVPosBusK;
    stCom.stPrmPfcAdjCoeff.ftVNegBusK       = stComDbg.stPrmPfcAdjCoeff.ftVNegBusK;
    stCom.stPrmPfcAdjCoeff.siBusVoltZero    = stComDbg.stPrmPfcAdjCoeff.siBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siPosBusVoltZero = stComDbg.stPrmPfcAdjCoeff.siPosBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siNegBusVoltZero = stComDbg.stPrmPfcAdjCoeff.siNegBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siVgZero_A       = stComDbg.stPrmPfcAdjCoeff.siVgZero_A;
    stCom.stPrmPfcAdjCoeff.siVgZero_B       = stComDbg.stPrmPfcAdjCoeff.siVgZero_B;
    stCom.stPrmPfcAdjCoeff.siVgZero_C       = stComDbg.stPrmPfcAdjCoeff.siVgZero_C;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_A    = stComDbg.stPrmPfcAdjCoeff.siVgInvZero_A;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_B    = stComDbg.stPrmPfcAdjCoeff.siVgInvZero_B;
    stCom.stPrmPfcAdjCoeff.siIgZero_A       = stComDbg.stPrmPfcAdjCoeff.siIgZero_A;
    stCom.stPrmPfcAdjCoeff.siIgZero_B       = stComDbg.stPrmPfcAdjCoeff.siIgZero_B;
    stCom.stPrmPfcAdjCoeff.siIgZero_C       = stComDbg.stPrmPfcAdjCoeff.siIgZero_C;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_A     = stComDbg.stPrmPfcAdjCoeff.siVgDcZero_A;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_B     = stComDbg.stPrmPfcAdjCoeff.siVgDcZero_B;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_C     = stComDbg.stPrmPfcAdjCoeff.siVgDcZero_C;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A     = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_A;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B     = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_B;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C     = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_C;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N   = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_A_N;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N   = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_B_N;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N   = stComDbg.stPrmPfcAdjCoeff.siIgDcZero_C_N;
    stCom.uiStdGridSet                      = stComDbg.uiStdGridSet;
    stCom.ftCurrAcRmsLim                    = stComDbg.ftCurrAcRmsLim;
    stCom.uiTypeGrid                        = stComDbg.uiTypeGrid;
#else
    stCom.ftCoeffKBattVoltCal               = stComLoc.stPrmExt.ftCoeffKBattVoltCal;
    stCom.ftCoeffBBattVoltCal               = stComLoc.stPrmExt.ftCoeffBBattVoltCal;
    stCom.ftCoeffKBattCurrCal               = stComLoc.stPrmExt.ftCoeffKBattCurrCal;
    stCom.ftCoeffBBattCurrCal               = stComLoc.stPrmExt.ftCoeffBBattCurrCal;
    stCom.ftCoeffKBattDwnVoltCal            = stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal;
    stCom.ftCoeffBBattDwnVoltCal            = stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal;
    stCom.ftCoeffKBattDwnCurrCal            = stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal;
    stCom.ftCoeffBBattDwnCurrCal            = stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal;

    stCom.stPrmPfcAdjCoeff.ftVaK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK;
    stCom.stPrmPfcAdjCoeff.ftIaK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK;
    stCom.stPrmPfcAdjCoeff.ftVbK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK;
    stCom.stPrmPfcAdjCoeff.ftIbK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK;
    stCom.stPrmPfcAdjCoeff.ftVcK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK;
    stCom.stPrmPfcAdjCoeff.ftIcK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK;
    stCom.stPrmPfcAdjCoeff.ftInK            = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftInK;
    stCom.stPrmPfcAdjCoeff.ftVaInvK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaInvK;
    stCom.stPrmPfcAdjCoeff.ftVbInvK         = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbInvK;
    stCom.stPrmPfcAdjCoeff.ftVBusK          = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVBusK;
    stCom.stPrmPfcAdjCoeff.ftVPosBusK       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVPosBusK;
    stCom.stPrmPfcAdjCoeff.ftVNegBusK       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVNegBusK;
    stCom.stPrmPfcAdjCoeff.siBusVoltZero    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siPosBusVoltZero = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siPosBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siNegBusVoltZero = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siNegBusVoltZero;
    stCom.stPrmPfcAdjCoeff.siVgZero_A       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_A;
    stCom.stPrmPfcAdjCoeff.siIgZero_A       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_A;
    stCom.stPrmPfcAdjCoeff.siVgZero_B       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_B;
    stCom.stPrmPfcAdjCoeff.siIgZero_B       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_B;
    stCom.stPrmPfcAdjCoeff.siVgZero_C       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_C;
    stCom.stPrmPfcAdjCoeff.siIgZero_C       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_C;
    stCom.stPrmPfcAdjCoeff.siIgZero_N       = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_N;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_A    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_A;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_B    = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_B;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_A     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_A;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A_N;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_B     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_B;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B_N;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_C     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_C;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C     = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N   = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C_N;
    stCom.uiStdGridSet                      = stComLoc.stPrmExt.uiStdGridSet;
    stCom.ftCurrAcRmsLim                    = stComLoc.stPrmExt.ftCurrAcRmsLim;
    stCom.uiTypeGrid                        = stComLoc.stPrmExt.uiTypeGrid;
#endif
}

/**
* @brief   EEPROM related parameter update
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
void v_Com_Rx_Tsk_EepPrmUpd(void)
{
    v_Com_EepPrmUpd();
}
#endif

/**
* @brief   CAN Initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_PrmInit(void)
{
    Uint16 i = 0U;

    /* Local Signal */
	stComLoc.stPrmExt.uiModRunReq       = CHG_ONGRID_MODE;           ///< Run mode request
	stComLoc.stPrmExt.uiCmdRunReq       = STOP_CMD;                  ///< Run command request
	stComLoc.stPrmExt.uiStgRunEnReq     = PFC_EN_D2D_EN;             ///< Run stage enable request
    stComLoc.stPrmExt.uiModeReactv      = REACTV_POW_QT_MODE;        ///< Reactive power mode
	stComLoc.stPrmExt.uiStArm           = ARM_DC_RLY_STA;            ///< ARM state
    stComLoc.stPrmExt.uiFlgUpgProg      = 0U;                        ///< Program upgrade flag
    stComLoc.stPrmExt.uiComFailCntr     = 0U;                        ///< Communication fail counter
	stComLoc.stPrmExt.ftVoltBattChrgReq = VOLT_BATT_REQ_MIN;         ///< Charge battery voltage request
	stComLoc.stPrmExt.ftCurrBattChrgReq = CURR_BATT_PARL_MAX;        ///< Charge battery current request
	stComLoc.stPrmExt.ftVoltBattDchaReq = VOLT_BATT_MIN;
	stComLoc.stPrmExt.ftCurrBattDchaReq = -CURR_BATT_SERIES_MAX;     ///< Discharge battery current request
    stComLoc.stPrmExt.ftPwrChrgReq      = POW_BATT_MAX * 1.1f;       ///< Charge power request
    stComLoc.stPrmExt.ftPwrActvReq      = 0.0f;                      ///< Active power request
	stComLoc.stPrmExt.ftPFReq           = 1.0f;                      ///< PF request
    stComLoc.stPrmExt.ftPwrReactvReq    = 0.0f;                      ///< Reactive power request
	stComLoc.stPrmExt.ftVoltAcV2LReq    = RATED_AC_VOLT_RMS;         ///< V2L voltage request
	stComLoc.stPrmExt.ftFrqAcV2LReq     = RATED_AC_FRQ;              ///< V2L frequency request
	stComLoc.stPrmExt.ftVoltBattBms     = VOLT_BATT_MAX;             ///< Battery voltage from BMS
	stComLoc.stPrmExt.ftVoltBattBmsMax  = VOLT_BATT_MAX;             ///< Max battery voltage from BMS
    stComLoc.stPrmExt.ftPaAcReq         = 0.0f;
    stComLoc.stPrmExt.ftPbAcReq         = 0.0f;
    stComLoc.stPrmExt.ftPcAcReq         = 0.0f;
    stComLoc.stPrmExt.ftQaAcReq         = 0.0f;
    stComLoc.stPrmExt.ftQbAcReq         = 0.0f;
    stComLoc.stPrmExt.ftQcAcReq         = 0.0f;
    stComLoc.stPrmExt.ftTempArmBd       = 0.0f;
    stComLoc.stPrmExt.ftTempNtc0        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc1        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc2        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc3        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc4        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc5        = 0.0f;
    stComLoc.stPrmExt.ftTempNtc6        = 0.0f;
    stComLoc.stPrmExt.uiCmdPfcADZeroAdj = AD_BIAS_ADJUST_OVER;
    stComLoc.stPrmExt.uiEnaSelfTest     = 0U;
    stComLoc.stPrmExt.uiFltSelfTest     = 0U;
    stComLoc.stPrmExt.uiFlgTxMsg        = 0U;
    stComLoc.stPrmExt.unIDMaskTx.all    = CAN_TX_ID;    ///< Initialize to 0x1770FF00UL SRC Address-0x00; DST Address-0xFF; CMD-0x70;
    stComLoc.stPrmExt.unModPfcPow.all   = 0U;
    stComLoc.stPrmExt.unModPfcPow.bit.uiModPowCtrl       = PFC_PWR_GRID_STD_MODE;           ///< Initialize to grid standard mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModActvImbal     = PFC_BAL_RUN_MODE;                ///< Initialize to balance run mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModActvArmCtrl   = PFC_ARM_CTRL_ACTV_POW_MODE;      ///< Initialize to power ARM control mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvImbal   = PFC_BAL_RUN_MODE;                ///< Initialize to balance run mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvArmCtrl = PFC_ARM_CTRL_REACTV_POW_MODE;    ///< Initialize to power ARM control mode
    stComLoc.stPrmExt.unCmdFct.all                       = FCN_DISABLE;                     ///< Initialize to FCT Command
    stComLoc.stPrmExt.unTiSys.all                        = 0U;
    stComLoc.stPrmExt.unTiReq.all                        = 0U;
    stComLoc.stPrmExt.uiFlgReadReq                       = 0U;
	
    stComLoc.stCpldBoot.ulCodLen        = 0UL;        ///< Initialize to Code length
    stComLoc.stCpldBoot.ulSumNumFrm     = 0UL;        ///< Initialize to Sum Frame Number
    stComLoc.stCpldBoot.ulCurrNumFrm    = 0UL;        ///< Initialize to Current Frame Number
    stComLoc.stCpldBoot.ulCpldFlashAddr = 0UL;        ///< Initialize to Cpld Flash address
    stComLoc.stCpldBoot.uiFlgChk        = 0U;         ///< Initialize to Check flag
    stComLoc.stCpldBoot.uiFlgEraseOK    = 0U;         ///< Initialize to Erase ok flag
    stComLoc.stCpldBoot.uiSubNumFrm     = 0U;         ///< Initialize to Sub Frame Number
    stComLoc.stCpldBoot.uiFlgWrFlt      = 0U;         ///< Initialize to Write fault flag
    for(i = 0U; i < SIZE_WR_FRM_CPLDUPD; i++)
    {
        stComLoc.stCpldBoot.uiFrmWordWrBuf[i] = 0U;   ///< Frame Word Buffer
        stComLoc.stCpldBoot.uiFrmWordRdBuf[i] = 0U;   ///< Frame Word Read Buffer
    }

    for(i = 0U; i < 8U; i++)
    {
        stComLoc.stCanParam.uiTxWord[i] = 0U;         ///< Send word
        stComLoc.stPrmExt.uiByteTx[i]   = 0U;         ///< Initialize Can TX Byte to 0U
        stCom.uiByteTx[i]               = 0U;         ///< Initialize Can TX Byte to 0U
    }

    for(i = 0U; i < 40U; i++)
    {
        stComLoc.stCanParam.uiRxTabData[i] = 0U;
    }

    for(i = 0U; i < NUM_EEPROM_DATA_QUE_OPER; i++)
    {
        stComLoc.uiIdxAry[i] = 0U;
    }

    stComLoc.stCanParam.uiCmdCode             = 0U;
    stComLoc.stCanParam.uiSrcAddr             = 0U;
    stComLoc.stCanParam.uiTxEndFlg            = 1U;
    stComLoc.stCanParam.uiGroupNum            = 0U;
    stComLoc.stCanParam.uiBitNum              = 0U;
    stComLoc.stCanParam.uiDataType            = 0U;
    stComLoc.stCanParam.uiFrameNum            = 0U;
    stComLoc.stCanParam.uiFrameOverFlg        = 0U;
    stComLoc.uiFrmNrOpData                    = 0U;
    stComLoc.uiFrmNrSelfTest                  = 0U;
    stComLoc.uiSelfTestCnt                    = 0U;

    /* structure stPrmPfcRtd2 */
    stComTbl.stPrmPfcRtd2.ftCurrIabcCBC       = IAC_CBC_CURR;
    stComTbl.stPrmPfcRtd2.ftCurrInCBC         = IN_CBC_CURR;

    /* structure stPrmPfcHw */
    stComTbl.stPrmPfcHw.uiSwtFrqIabc          = FRQ_PFC_SWITCH;
    stComTbl.stPrmPfcHw.ulSwtFrqIn            = FRQ_BAL_SWITCH;
    stComTbl.stPrmPfcHw.uiDeadTiIabc          = PFC_PWM_DEADTIME;
    stComTbl.stPrmPfcHw.uiDeadTiIn            = BAL_PWM_DEADTIME;

    /* Fault Initialization */
    stComTbl.unWordPfcFlt1.all                = 0U;
    stComTbl.unWordPfcFltSts1.all             = 0U;
    stComTbl.unWordPfcFltMask1.all            = 0U;
    stComTbl.unWordPfcFlt2.all                = 0U;
    stComTbl.unWordPfcFltSts2.all             = 0U;
    stComTbl.unWordPfcFltMask2.all            = 0U;
    stComTbl.unWordPfcFlt3.all                = 0U;
    stComTbl.unWordPfcFltSts3.all             = 0U;
    stComTbl.unWordPfcFltMask3.all            = 0U;
    stComTbl.unWordSysFlt.all                 = 0U;
    stComTbl.unWordSysFltSts.all              = 0U;
    stComTbl.unWordSysFltMask.all             = 0U;

    /* structure stPrmFltRstrt */
    stComTbl.stPrmFltRstrt.uiEnaFltRstrt         = FCN_ENABLE;
    stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt1.all = 0xFFFFU;
    stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt2.all = 0xFFFFU;
    stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt3.all = 0xFFFFU;
    stComTbl.stPrmFltRstrt.unEnaSysFltRstrt.all  = 0xFFFFU;
    stComTbl.stPrmFltRstrt.uiEnaD2dFltCpuRstrt   = (~FLT_D2D_BATT_SC);    ///< Short-circuit fault can't restart
    stComTbl.stPrmFltRstrt.uiEnaD2dFltClaRstrt   = 0xFFFFU;

    /* structure stPrmOffGridCtrl */
    stComTbl.stPrmOffGridCtrl.ftFrqAcDbgSet   = RATED_AC_FRQ;
    stComTbl.stPrmOffGridCtrl.ftVoltAcDbgSet  = 50.0f;

    /* structure stPrmOffGridCtrl */
#if(3U == GRID_PHASE_NUMBER)
    stComTbl.stPrmBalBrdg.ftVoltBalEna        = 10.0f;
#else
    stComTbl.stPrmBalBrdg.ftVoltBalEna        = 5.0f;
#endif

    /* structure stRtdPrm */
    stComTbl.stRtdPrm.ftCurrBattParlMax       = CURR_BATT_PARL_MAX;             ///< Max parallel output current
    stComTbl.stRtdPrm.ftCurrAcRmsRtd          = RATED_AC_CURR_RMS;              ///< Rated AC current RMS

    /* Module ComIf */
#if(3U != GRID_PHASE_NUMBER)
    stComTbl.stPrmComIf.ftFrqOLReq            = D2D_FRQ_MAX;                    ///< D2D open-loop frequency request
#else
    stComTbl.stPrmComIf.ftDs1OLReq            = 0.0f;
#endif

    /* Module CmnAdc */
    stComTbl.stPrmCmnAdc.uiDacCh              = 0U;
    stComTbl.stPrmCmnAdc.siAux12VZero         = AD_BIAS_AUX_12V;
    stComTbl.stPrmCmnAdc.siAux1V5Zero         = AD_BIAS_AUX_1V5;

    /* Module CmnDiag */
    stComTbl.stPrmCmnDiag.uiFltSys            = 0U;                             ///< System fault No Check
    stComTbl.stPrmCmnDiag.ftOverTemp          = TEMP_UP_POW_LIM_HT + 1.0f;      ///< Over temperature protection
    stComTbl.stPrmCmnDiag.ftUnderTemp         = TEMP_UNDER_PROTN;               ///< Under temperature protection; POW_LMT_LOW_TEMP_DN - 1.0f

    /* Module D2dDiag */
    stComTbl.stPrmD2dDiag.ftCurrBattImbal     = PROTN_D2D_BATT_IMBAL_CURR;      ///< Battery Imbalance current protection
    stComTbl.stPrmD2dDiag.ftVoltBattImbal     = PROTN_D2D_BATT_IMBAL_VOLT;      ///< Battery Imbalance voltage protection
    stComTbl.stPrmD2dDiag.ftVoltBattUV        = PROTN_D2D_PARL_BATT_UV;         ///< Battery UV protection
    stComTbl.stPrmD2dDiag.uiFltCpuNC          = 0U;                             ///< D2D CPU fault No Check

    /* Module PowLim */
    stComTbl.stPrmPowLim.unCmd.bit.uiEnaHTPowLim 	 = FCN_ENABLE;
    stComTbl.stPrmPowLim.unCmd.bit.uiEnaLTPowLim 	 = FCN_ENABLE;
    stComTbl.stPrmPowLim.ftVoltBusPfcReq         	 = VOLT_BUS_TGT_MIN;        ///< PFC bus voltage request
    stComTbl.stPrmPowLim.ftVoltBusD2dReq         	 = VOLT_BUS_TGT_MIN;        ///< D2D bus voltage request
    stComTbl.stPrmPowLim.ftVoltBusMax            	 = VOLT_BUS_TGT_MAX;        ///< Max limited value of bus voltage
    stComTbl.stPrmPowLim.ftVoltBusMin            	 = VOLT_BUS_TGT_MIN;        ///< Min limited value of bus voltage
    stComTbl.stPrmPowLim.ftVoltBusAdd            	 = 40.0f;
    stComTbl.stPrmPowLim.ftCoeffBusPreChg3P      	 = COEFF_BUS_PRE_CHRG_3P;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc1PowLim  = 0.0f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc2PowLim  = 74.5f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc3PowLim  = 75.2f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc4PowLim  = 74.7f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc5PowLim  = 74.6f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempArmBdPowlim = 110.0f;
    stComTbl.stPrmPowLim.stChrgPrm.ftTempNtc1PowLim  = 0.0f;
    stComTbl.stPrmPowLim.stDchaPrm.ftTempNtc2PowLim  = 74.6f;
    stComTbl.stPrmPowLim.stDchaPrm.ftTempNtc3PowLim  = 78.3f;
    stComTbl.stPrmPowLim.stDchaPrm.ftTempNtc4PowLim  = 77.5f;
    stComTbl.stPrmPowLim.stDchaPrm.ftTempNtc5PowLim  = 75.1f;
    stComTbl.stPrmPowLim.stDchaPrm.ftTempArmBdPowlim = 110.0f;
    stComTbl.stPrmPowLim.ftCoeffBusPreChg1P          = COEFF_BUS_PRE_CHRG_1P;

    /* Module Grid */
    stComTbl.stPrmDcCpt.ftKpVdcCtrl           = KP_AC_VOLT_DC_LOOP;
    stComTbl.stPrmDcCpt.ftKiVdcCtrl           = KI_AC_VOLT_DC_LOOP;
    stComTbl.stPrmDcCpt.ftOutpLimtVdcCtrl     = LMT_AC_VOLT_DC_LOOP;
    stComTbl.stPrmDcCpt.ftKpIdcCtrl           = KP_AC_CURR_DC_LOOP;
    stComTbl.stPrmDcCpt.ftKiIdcCtrl           = KI_AC_CURR_DC_LOOP;
    stComTbl.stPrmDcCpt.ftOutpLimIdcCtrl      = LMT_AC_CURR_DC_LOOP;

    /* Module PerphCtrl */
    stComTbl.stPrmPerphCtrl.uiModAcRly        = PWM_MOD_AC_RLY;        ///< Initialize to PWM mode
    stComTbl.stPrmPerphCtrl.ftDutyAcRlyPwm    = DUTY_AC_RLY_PWM;

    /* Module PfcPowCtrl */
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.all                   = 0U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.all                   = 0U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR1st     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR2nd     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR3rd     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR5th     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR7th     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR9th     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR15th    = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnVoltPR1st     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnVoltPR3rd     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnVoltPR5th     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnVoltPR7th     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroVoltPR1st = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroVoltPR3rd = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroCurrPR1st = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroCurrPR3rd = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroCurrPR5th = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnBalBrdg       = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnCurrNeg3P     = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnCurrThd3P     = 1U;
#if 2U == GRID_PHASE_NUMBER
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LRep        = 0U;
#else
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LRep        = 1U;
#endif
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LNegVolt    = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeBal      = SVPWM;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeImBal    = SPWM;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF         = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnBusMid        = 1U;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LThdCtrl    = FCN_ENABLE;
    stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModV2LThdCtrl   = AC_VOLT_REP_CTRL_MODE;         ///< Initialize to repeat control mode

    stComTbl.stPrmPfcPowCtrl.ftThetaCompPll     = COMP_PLL_THETA;
    stComTbl.stPrmPfcPowCtrl.ftKpPllInit        = KP_PLL_INIT;
    stComTbl.stPrmPfcPowCtrl.ftKiPllInit        = KI_PLL_INIT;
    stComTbl.stPrmPfcPowCtrl.ftKpPll            = KP_PLL;
    stComTbl.stPrmPfcPowCtrl.ftKiPll            = KI_PLL;
    stComTbl.stPrmPfcPowCtrl.ftCoeffVbusNotchBw = COEFF_NOTCH_BW;

    stComTbl.stPrmPfcPowCtrl.ftKpVbusLoop       = KP_PFC_BUS_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiVbusLoop       = KI_PFC_BUS_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxVbusLoop      = MAX_PFC_BUS_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinVbusLoop      = MIN_PFC_BUS_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKpCurrLoop       = KP_CURR_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiCurrLoop       = KI_CURR_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoop      = MAX_CURR_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoop      = MIN_CURR_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR1st  = KR_CURR_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR1st  = WC_CURR_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR1st = MAX_CURR_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR1st = MIN_CURR_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR3rd  = KR_CURR_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR3rd  = WC_CURR_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR3rd = MAX_CURR_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR3rd = MIN_CURR_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR5th  = KR_CURR_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR5th  = WC_CURR_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR5th = MAX_CURR_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR5th = MIN_CURR_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR7th  = KR_CURR_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR7th  = WC_CURR_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR7th = MAX_CURR_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR7th = MIN_CURR_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR9th  = KR_CURR_LOOP_9TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR9th  = WC_CURR_LOOP_9TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR9th = MAX_CURR_LOOP_9TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR9th = MIN_CURR_LOOP_9TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrCurrLoopPR15th  = KR_CURR_LOOP_15TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcCurrLoopPR15th  = WC_CURR_LOOP_15TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoopPR15th = MAX_CURR_LOOP_15TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinCurrLoopPR15th = MIN_CURR_LOOP_15TH_PR;

    stComTbl.stPrmPfcPowCtrl.ftQzVacLoopRep        = QZ_AC_VOLT_LOOP_REP;
    stComTbl.stPrmPfcPowCtrl.ftKrCompVacLoopRep    = KR_COMP_AC_VOLT_LOOP_REP;
    stComTbl.stPrmPfcPowCtrl.uiNrPhaCompVacLoopRep = NR_COMP_AC_VOLT_LOOP_REP;
    stComTbl.stPrmPfcPowCtrl.ftOutpMaxVacLoopRep   = MAX_AC_VOLT_LOOP_REP;

    /* FPGA CMD parameter */
    stComTbl.stPrmPfcPowCtrl.uiEnaFrqJit           = 1U;
    stComTbl.stPrmPfcPowCtrl.uiFrqJitRng           = 2800U;   ///< 2800Hz

#if(1U == GRID_PHASE_NUMBER)
    stComTbl.stPrmPfcPowCtrl.ftKpVacLoop           = KP_AC_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiVacLoop           = KI_AC_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxVacLoop          = MAX_AC_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinVacLoop          = MIN_AC_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKrVacLoopPR1st      = KR_AC_VOLT_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcVacLoopPR1st      = WC_AC_VOLT_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxVacLoopPR1st     = MAX_AC_VOLT_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinVacLoopPR1st     = MIN_AC_VOLT_LOOP_1ST_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrVacLoopPR3rd      = KR_AC_VOLT_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcVacLoopPR3rd      = WC_AC_VOLT_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxVacLoopPR3rd     = MAX_AC_VOLT_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinVacLoopPR3rd     = MIN_AC_VOLT_LOOP_3RD_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrVacLoopPR5th      = KR_AC_VOLT_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcVacLoopPR5th      = WC_AC_VOLT_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxVacLoopPR5th     = MAX_AC_VOLT_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinVacLoopPR5th     = MIN_AC_VOLT_LOOP_5TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftKrVacLoopPR7th      = KR_AC_VOLT_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftWcVacLoopPR7th      = WC_AC_VOLT_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMaxVacLoopPR7th     = MAX_AC_VOLT_LOOP_7TH_PR;
    stComTbl.stPrmPfcPowCtrl.ftMinVacLoopPR7th     = MIN_AC_VOLT_LOOP_7TH_PR;
#else
    stComTbl.stPrmPfcPowCtrl.ftKpVoltLoop       = KP_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiVoltLoop       = KI_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxVoltLoop      = MAX_VOLT_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinVoltLoop      = MIN_VOLT_LOOP;

    stComTbl.stPrmPfcPowCtrl.ftKpIdPosLoop      = KP_CURR_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiIdPosLoop      = KI_CURR_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxIdPosLoop     = MAX_CURR_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinIdPosLoop     = MIN_CURR_D_P_LOOP;

    stComTbl.stPrmPfcPowCtrl.ftKpIdNegLoop      = KP_CURR_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiIdNegLoop      = KI_CURR_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxIdNegLoop     = MAX_CURR_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinIdNegLoop     = MIN_CURR_D_N_LOOP;

    stComTbl.stPrmPfcPowCtrl.ftKpVdPosLoop      = KP_VOLT_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiVdPosLoop      = KI_VOLT_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxVdPosLoop     = MAX_VOLT_D_P_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinVdPosLoop     = MIN_VOLT_D_P_LOOP;

    stComTbl.stPrmPfcPowCtrl.ftKpVdNegLoop      = KP_VOLT_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftKiVdNegLoop      = KI_VOLT_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMaxVdNegLoop     = MAX_VOLT_D_N_LOOP;
    stComTbl.stPrmPfcPowCtrl.ftMinVdNegLoop     = MIN_VOLT_D_N_LOOP;
#endif

    /* Module D2dPowPreCtrl */
	stComTbl.stPrmD2dPowPreCtrl.uiFlgFrqJitEn   = 1U;
	stComTbl.stPrmD2dPowPreCtrl.uiPerdFrqJit    = 10U;
    stComTbl.stPrmD2dPowPreCtrl.ftGainFrqJitRng = 0.025f;

    /* Module D2dPowCtrl */ 
    stComTbl.stPrmD2dPowCtrl.ftCurrInduLeakSwt       = 6.0f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattVoltChrgKp     = 0.001f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattVoltChrgKi     = 0.0002f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattCurrChrgKp     = 0.0075f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattCurrChrgKi     = 0.00002f;
    stComTbl.stPrmD2dPowCtrl.ftFacBusVoltBidirKp     = 1.0f;
    stComTbl.stPrmD2dPowCtrl.ftFacBusVoltBidirKi     = 0.0001f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattCurrBidirKp    = 0.0075f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattCurrBidirKi    = 0.00002f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattVoltPRKr       = 0.015f;
    stComTbl.stPrmD2dPowCtrl.ftFacBattCurrPRKr       = 0.05f;
    stComTbl.stPrmD2dPowCtrl.ftOutpChrgDirDzCmp      = 0.046f;
    stComTbl.stPrmD2dPowCtrl.ftCurrBattBidirRefStep  = 0.5f;
    stComTbl.stPrmD2dPowCtrl.ftCurrBattOCPThd        = 25.0f;
    stComTbl.stPrmD2dPowCtrl.ftVoltBattOVPThd        = 540.0f;
    stComTbl.stPrmD2dPowCtrl.ftVoltBusOVPThd         = 890.0f;
    stComTbl.stPrmD2dPowCtrl.uiFlgChrgPREn           = 0U;
    stComTbl.stPrmD2dPowCtrl.uiFlgDzCmpEn            = 0U;
    stComTbl.stPrmD2dPowCtrl.uiFltClaNC              = 0U;
    stComTbl.stPrmD2dPowCtrl.uiFlgBidirDynKiEn       = 1U;
    stComTbl.stPrmD2dPowCtrl.ftD2dPwmValDutyPowCell  = 450.0f;

    /*FPGA CMD DATA*/
    stComTbl.stPrmToFpga.uiHandControl           = 0U;
    stComTbl.stPrmToFpga.uiClearRedFlt           = 0U;
    stComTbl.stPrmToFpga.uiOTAModulFpga          = 0U;
    stComTbl.stPrmToFpga.uiCloseRely             = 0U;
    stComTbl.stPrmToFpga.ftD2dPwmDeadTimePowCell = 19.0f;    ///<dead time 380ns
    stComTbl.stPrmToFpga.ftD2dPwmPeriodPowCell   = 900.0f;   ///< 55kHz
    stComTbl.stPrmToFpga.uiPeriodCHB             = 4159U;  ///< 24999£º500Hz     4159£º3K
    stComTbl.stPrmToFpga.ftPwmDutyTarget         = 0.5f;  ///< 50%
    stComTbl.stPrmToFpga.uiDischargeVolCHBA      = 4095;
    stComTbl.stPrmToFpga.uiDischargeVolCHBB      = 4095;
    stComTbl.stPrmToFpga.uiDischargeVolCHBC      = 4095;
    stComTbl.stPrmToFpga.ftSUMOCPValue           = 30;
    stComTbl.stPrmToFpga.uiRedundantA            = 0x000F;
    stComTbl.stPrmToFpga.uiRedundantB            = stComTbl.stPrmToFpga.uiRedundantA;
    stComTbl.stPrmToFpga.uiRedundantC            = stComTbl.stPrmToFpga.uiRedundantB;
    stComTbl.stPrmToFpga.uiRunAEnable            = 0x0007;//0x003F
    stComTbl.stPrmToFpga.uiRunBEnable            = 0x0007;
    stComTbl.stPrmToFpga.uiRunCEnable            = 0x0007;

    stComLoc.uiModGrid                        = 0U;
    stComLoc.uiNumSelfTest                    = 0U;
    stComLoc.ftCoeffReactv                    = RATED_AC_REACTV_COEFF;
    stComLoc.stPrmExt.ftPowBattMax            = POW_BATT_MAX;
    stComLoc.stPrmExt.ftQAcMax                = stComLoc.ftCoeffReactv * POW_AC_RTD;
    stComLoc.stPrmExt.ftIdAcRtd               = CON_SQRT_2 * stComTbl.stRtdPrm.ftCurrAcRmsRtd;
    stComLoc.stPrmExt.ftIqAcRtd               = CON_SQRT_2 * stComLoc.ftCoeffReactv * stComTbl.stRtdPrm.ftCurrAcRmsRtd + CURR_LMT_X_CAP_COMP;
    stComLoc.stPrmExt.ftQOnePhaMax            = stComLoc.stPrmExt.ftQAcMax * ONE_PHASE_COEFF;
    stComLoc.stPrmExt.ftCurrBattMaxChrg       = stComTbl.stRtdPrm.ftCurrBattParlMax;             ///< Max battery current in charge mode
    stComLoc.stPrmExt.ftCurrBattMaxBidir      = CURR_BATT_PARL_MAX;                              ///< Max battery current in bi-direction mode
    stComLoc.stPrmExt.uiCmdCode   = 0U;
    /* Global Signal*/
#if (1U == COM_DBG)
    stComDbg.unModPfcPow.all        = stComLoc.stPrmExt.unModPfcPow.all;
    stComDbg.unCmdFct.all           = stComLoc.stPrmExt.unCmdFct.all;
    stComDbg.unTiSys.all            = stComLoc.stPrmExt.unTiSys.all;
    stComDbg.unTiReq.all            = stComLoc.stPrmExt.unTiReq.all;
    stComDbg.uiFlgReadReq           = stComLoc.stPrmExt.uiFlgReadReq;
	stComDbg.uiModRunReq            = stComLoc.stPrmExt.uiModRunReq;
	stComDbg.uiCmdRunReq            = stComLoc.stPrmExt.uiCmdRunReq;
	stComDbg.uiStgRunEnReq          = stComLoc.stPrmExt.uiStgRunEnReq;
	stComDbg.uiModeReactv           = stComLoc.stPrmExt.uiModeReactv;
    stComDbg.ftPwrChrgReq           = stComLoc.stPrmExt.ftPwrChrgReq;
    stComDbg.ftPwrActvReq           = stComLoc.stPrmExt.ftPwrActvReq;
    stComDbg.ftPFReq                = stComLoc.stPrmExt.ftPFReq;
    stComDbg.ftVoltAcV2LReq         = stComLoc.stPrmExt.ftVoltAcV2LReq;
    stComDbg.ftFrqAcV2LReq          = stComLoc.stPrmExt.ftFrqAcV2LReq;
	stComDbg.uiStArm                = stComLoc.stPrmExt.uiStArm;
	stComDbg.uiFlgUpgProg           = stComLoc.stPrmExt.uiFlgUpgProg;
    stComDbg.uiComFailCntr          = stComLoc.stPrmExt.uiComFailCntr;
	stComDbg.ftVoltBattChrgReq      = stComLoc.stPrmExt.ftVoltBattChrgReq;
	stComDbg.ftCurrBattChrgReq      = stComLoc.stPrmExt.ftCurrBattChrgReq;
	stComDbg.ftVoltBattDchaReq      = stComLoc.stPrmExt.ftVoltBattDchaReq;
	stComDbg.ftCurrBattDchaReq      = stComLoc.stPrmExt.ftCurrBattDchaReq;
	stComDbg.ftVoltBattBms          = stComLoc.stPrmExt.ftVoltBattBms;
	stComDbg.ftVoltBattBmsMax       = stComLoc.stPrmExt.ftVoltBattBmsMax;
	stComDbg.ftPaAcReq              = stComLoc.stPrmExt.ftPaAcReq;
	stComDbg.ftPbAcReq              = stComLoc.stPrmExt.ftPbAcReq;
	stComDbg.ftPcAcReq              = stComLoc.stPrmExt.ftPcAcReq;
    stComDbg.ftQaAcReq              = stComLoc.stPrmExt.ftQaAcReq;
    stComDbg.ftQbAcReq              = stComLoc.stPrmExt.ftQbAcReq;
    stComDbg.ftQcAcReq              = stComLoc.stPrmExt.ftQcAcReq;
	stComDbg.ftTempArmBd            = stComLoc.stPrmExt.ftTempArmBd;
	stComDbg.ftTempNtc0             = stComLoc.stPrmExt.ftTempNtc0;
	stComDbg.ftTempNtc1             = stComLoc.stPrmExt.ftTempNtc1;
	stComDbg.ftTempNtc2             = stComLoc.stPrmExt.ftTempNtc2;
	stComDbg.ftTempNtc3             = stComLoc.stPrmExt.ftTempNtc3;
	stComDbg.ftTempNtc4             = stComLoc.stPrmExt.ftTempNtc4;
	stComDbg.ftTempNtc5             = stComLoc.stPrmExt.ftTempNtc5;
	stComDbg.ftTempNtc6             = stComLoc.stPrmExt.ftTempNtc6;
	stComDbg.uiCmdPfcADZeroAdj      = stComLoc.stPrmExt.uiCmdPfcADZeroAdj;
	stComDbg.ftPowBattMax           = stComLoc.stPrmExt.ftPowBattMax;
    stComDbg.ftQAcMax               = stComLoc.stPrmExt.ftQAcMax;
    stComDbg.ftQOnePhaMax           = stComLoc.stPrmExt.ftQOnePhaMax;
    stComDbg.ftIdAcRtd              = stComLoc.stPrmExt.ftIdAcRtd;
    stComDbg.ftIqAcRtd              = stComLoc.stPrmExt.ftIqAcRtd;
    stComDbg.ftCurrBattMaxChrg      = stComLoc.stPrmExt.ftCurrBattMaxChrg;
    stComDbg.ftCurrBattMaxBidir     = stComLoc.stPrmExt.ftCurrBattMaxBidir;
    stComDbg.uiEnaSelfTest          = stComLoc.stPrmExt.uiEnaSelfTest;
    stComDbg.uiFltSelfTest          = stComLoc.stPrmExt.uiFltSelfTest;
    stComDbg.uiFlgTxMsg             = stComLoc.stPrmExt.uiFlgTxMsg;
    stComDbg.unIDMaskTx.all         = stComLoc.stPrmExt.unIDMaskTx.all;

    stCom.unModPfcPow.all        = stComDbg.unModPfcPow.all;
    stCom.unCmdFct.all           = stComDbg.unCmdFct.all;
    stCom.unTiSys.all            = stComDbg.unTiSys.all;
    stCom.unTiReq.all            = stComDbg.unTiReq.all;
    stCom.uiFlgReadReq           = stComDbg.uiFlgReadReq;
	stCom.uiModRunReq            = stComDbg.uiModRunReq;
	stCom.uiCmdRunReq            = stComDbg.uiCmdRunReq;
	stCom.uiStgRunEnReq          = stComDbg.uiStgRunEnReq;
    stCom.uiModeReactv           = stComDbg.uiModeReactv;
    stCom.ftPwrChrgReq           = stComDbg.ftPwrChrgReq;
    stCom.ftPwrActvReq           = stComDbg.ftPwrActvReq;
    stCom.ftPFReq                = stComDbg.ftPFReq;
    stCom.ftVoltAcV2LReq         = stComDbg.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq          = stComDbg.ftFrqAcV2LReq;
	stCom.uiStArm                = stComDbg.uiStArm;
	stCom.uiFlgUpgProg           = stComDbg.uiFlgUpgProg;
    stCom.uiComFailCntr          = stComDbg.uiComFailCntr;
	stCom.ftVoltBattChrgReq      = stComDbg.ftVoltBattChrgReq;
	stCom.ftCurrBattChrgReq      = stComDbg.ftCurrBattChrgReq;
	stCom.ftVoltBattDchaReq      = stComDbg.ftVoltBattDchaReq;
	stCom.ftCurrBattDchaReq      = stComDbg.ftCurrBattDchaReq;
	stCom.ftVoltBattBms          = stComDbg.ftVoltBattBms;
	stCom.ftVoltBattBmsMax       = stComDbg.ftVoltBattBmsMax;
    stCom.ftPaAcReq              = stComDbg.ftPaAcReq;
    stCom.ftPbAcReq              = stComDbg.ftPbAcReq;
    stCom.ftPcAcReq              = stComDbg.ftPcAcReq;
    stCom.ftQaAcReq              = stComDbg.ftQaAcReq;
    stCom.ftQbAcReq              = stComDbg.ftQbAcReq;
    stCom.ftQcAcReq              = stComDbg.ftQcAcReq;
    stCom.ftTempArmBd            = stComDbg.ftTempArmBd;
    stCom.ftTempNtc0             = stComDbg.ftTempNtc0;
    stCom.ftTempNtc1             = stComDbg.ftTempNtc1;
    stCom.ftTempNtc2             = stComDbg.ftTempNtc2;
    stCom.ftTempNtc3             = stComDbg.ftTempNtc3;
    stCom.ftTempNtc4             = stComDbg.ftTempNtc4;
    stCom.ftTempNtc5             = stComDbg.ftTempNtc5;
    stCom.ftTempNtc6             = stComDbg.ftTempNtc6;
    stCom.uiCmdPfcADZeroAdj      = stComDbg.uiCmdPfcADZeroAdj;
    stCom.ftPowBattMax           = stComDbg.ftPowBattMax;
    stCom.ftQAcMax               = stComDbg.ftQAcMax;
    stCom.ftQOnePhaMax           = stComDbg.ftQOnePhaMax;
    stCom.ftIdAcRtd              = stComDbg.ftIdAcRtd;
    stCom.ftIqAcRtd              = stComDbg.ftIqAcRtd;
    stCom.ftCurrBattMaxChrg      = stComDbg.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir     = stComDbg.ftCurrBattMaxBidir;
    stCom.uiEnaSelfTest          = stComDbg.uiEnaSelfTest;
    stCom.uiFltSelfTest          = stComDbg.uiFltSelfTest;
    stCom.uiFlgTxMsg             = stComDbg.uiFlgTxMsg;
    stCom.unIDMaskTx.all         = stComDbg.unIDMaskTx.all;
#else
    stCom.unModPfcPow.all        = stComLoc.stPrmExt.unModPfcPow.all;
    stCom.unCmdFct.all           = stComLoc.stPrmExt.unCmdFct.all;
    stCom.unTiSys.all            = stComLoc.stPrmExt.unTiSys.all;
    stCom.unTiReq.all            = stComLoc.stPrmExt.unTiReq.all;
    stCom.uiFlgReadReq           = stComLoc.stPrmExt.uiFlgReadReq;
	stCom.uiModRunReq            = stComLoc.stPrmExt.uiModRunReq;
	stCom.uiCmdRunReq            = stComLoc.stPrmExt.uiCmdRunReq;
	stCom.uiStgRunEnReq          = stComLoc.stPrmExt.uiStgRunEnReq;
    stCom.uiModeReactv           = stComLoc.stPrmExt.uiModeReactv;
    stCom.ftPwrChrgReq           = stComLoc.stPrmExt.ftPwrChrgReq;
    stCom.ftPwrActvReq           = stComLoc.stPrmExt.ftPwrActvReq;
    stCom.ftPFReq                = stComLoc.stPrmExt.ftPFReq;
    stCom.ftPwrReactvReq         = stComLoc.stPrmExt.ftPwrReactvReq;
    stCom.ftVoltAcV2LReq         = stComLoc.stPrmExt.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq          = stComLoc.stPrmExt.ftFrqAcV2LReq;
	stCom.uiStArm                = stComLoc.stPrmExt.uiStArm;
	stCom.uiFlgUpgProg           = stComLoc.stPrmExt.uiFlgUpgProg;
    stCom.uiComFailCntr          = stComLoc.stPrmExt.uiComFailCntr;
	stCom.ftVoltBattChrgReq      = stComLoc.stPrmExt.ftVoltBattChrgReq;
	stCom.ftCurrBattChrgReq      = stComLoc.stPrmExt.ftCurrBattChrgReq;
	stCom.ftVoltBattDchaReq      = stComLoc.stPrmExt.ftVoltBattDchaReq;
	stCom.ftCurrBattDchaReq      = stComLoc.stPrmExt.ftCurrBattDchaReq;
	stCom.ftVoltBattBms          = stComLoc.stPrmExt.ftVoltBattBms;
	stCom.ftVoltBattBmsMax       = stComLoc.stPrmExt.ftVoltBattBmsMax;
    stCom.ftPaAcReq              = stComLoc.stPrmExt.ftPaAcReq;
    stCom.ftPbAcReq              = stComLoc.stPrmExt.ftPbAcReq;
    stCom.ftPcAcReq              = stComLoc.stPrmExt.ftPcAcReq;
    stCom.ftQaAcReq              = stComLoc.stPrmExt.ftQaAcReq;
    stCom.ftQbAcReq              = stComLoc.stPrmExt.ftQbAcReq;
    stCom.ftQcAcReq              = stComLoc.stPrmExt.ftQcAcReq;
    stCom.ftTempArmBd            = stComLoc.stPrmExt.ftTempArmBd;
    stCom.ftTempNtc0             = stComLoc.stPrmExt.ftTempNtc0;
    stCom.ftTempNtc1             = stComLoc.stPrmExt.ftTempNtc1;
    stCom.ftTempNtc2             = stComLoc.stPrmExt.ftTempNtc2;
    stCom.ftTempNtc3             = stComLoc.stPrmExt.ftTempNtc3;
    stCom.ftTempNtc4             = stComLoc.stPrmExt.ftTempNtc4;
    stCom.ftTempNtc5             = stComLoc.stPrmExt.ftTempNtc5;
    stCom.ftTempNtc6             = stComLoc.stPrmExt.ftTempNtc6;
    stCom.uiCmdPfcADZeroAdj      = stComLoc.stPrmExt.uiCmdPfcADZeroAdj;
    stCom.ftPowBattMax           = stComLoc.stPrmExt.ftPowBattMax;
    stCom.ftQAcMax               = stComLoc.stPrmExt.ftQAcMax;
    stCom.ftQOnePhaMax           = stComLoc.stPrmExt.ftQOnePhaMax;
    stCom.ftIdAcRtd              = stComLoc.stPrmExt.ftIdAcRtd;
    stCom.ftIqAcRtd              = stComLoc.stPrmExt.ftIqAcRtd;
    stCom.ftCurrBattMaxChrg      = stComLoc.stPrmExt.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir     = stComLoc.stPrmExt.ftCurrBattMaxBidir;
    stCom.uiEnaSelfTest          = stComLoc.stPrmExt.uiEnaSelfTest;
    stCom.uiFltSelfTest          = stComLoc.stPrmExt.uiFltSelfTest;
    stCom.uiFlgTxMsg             = stComLoc.stPrmExt.uiFlgTxMsg;
    stCom.unIDMaskTx.all         = stComLoc.stPrmExt.unIDMaskTx.all;
    stCom.uiCmdCode             = stComLoc.stPrmExt.uiCmdCode;
#endif
}

/**
* @brief   CAN Communication Receive function
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
void v_Com_Rx(void)
{
    Uint16 l_uiDstAddr  = 0U;    ///< Destination Address
    Uint16 l_uiFrameNum = 0U;

    /* Clear transmit message flag */
    stComLoc.stPrmExt.uiFlgTxMsg = 0U;

    if(1U == stComDrv.uiFlgRxOk)    ///< The data has been received
    {
        stComLoc.stPrmExt.uiComFailCntr = 0U;    ///< CAN communication fault counter cleared to zero

        if((1U == stComLoc.stCanParam.uiTxEndFlg) || (CAN_RUN_ORD_CMD == stComDrv.unIDMaskRx.bit.DATACMD))        ///< Transmit before receiving, unless it is an on/off command
        {
            l_uiDstAddr = stComDrv.unIDMaskRx.bit.DSTADDR;    ///< Destination Address
            stComLoc.stCanParam.uiCmdCode = stComDrv.unIDMaskRx.bit.DATACMD;    ///< Function Code
            stComLoc.stCanParam.uiSrcAddr = stComDrv.unIDMaskRx.bit.SRCADDR;    ///< Source Address
            stComLoc.stPrmExt.uiCmdCode = stComLoc.stCanParam.uiCmdCode;

            if((CAN_PARAM_SET_CMD == stComLoc.stCanParam.uiCmdCode) || (CAN_PARAM_READ_CMD == stComLoc.stCanParam.uiCmdCode))
            {
                /* 1-int16  2-Uint16 3-int32  4-Uint32 5-float 6-string 0-else */
                stComLoc.stCanParam.uiDataType = (stComDrv.uiByteRx[1] & 0x1CU) >> 2;   ///< Data Type
                stComLoc.stCanParam.uiFrameNum = ((stComDrv.uiByteRx[0] & 0x7FU) << 1) + ((stComDrv.uiByteRx[1] & 0x80U) >> 7);    ///< Current Frame Number
                stComLoc.stCanParam.uiFrameOverFlg = (stComDrv.uiByteRx[0] & 0x80U) >> 7;      ///< End flag of Frame

                stComLoc.stCanParam.uiGroupNum = stComDrv.uiByteRx[2];    ///< Group Number
                stComLoc.stCanParam.uiBitNum   = stComDrv.uiByteRx[3];    ///< Bit Number

                if((stComLoc.stCanParam.uiFrameNum <= 10U) && (stComLoc.stCanParam.uiFrameNum > 0U))    ///< The maximum frames number is 10
                {
                    l_uiFrameNum = (stComLoc.stCanParam.uiFrameNum - 1U) * 4U;
                    stComLoc.stCanParam.uiRxTabData[l_uiFrameNum]      = stComDrv.uiByteRx[4];
                    stComLoc.stCanParam.uiRxTabData[l_uiFrameNum + 1U] = stComDrv.uiByteRx[5];
                    stComLoc.stCanParam.uiRxTabData[l_uiFrameNum + 2U] = stComDrv.uiByteRx[6];
                    stComLoc.stCanParam.uiRxTabData[l_uiFrameNum + 3U] = stComDrv.uiByteRx[7];
                }
            }

            if((CAN_SRC_ARM == stComLoc.stCanParam.uiSrcAddr) || (CAN_SRC_PC == stComLoc.stCanParam.uiSrcAddr))    ///< Source Address
            {
                if((CAN_DST_DSP == l_uiDstAddr) || (CAN_DST_GROUP == l_uiDstAddr))    ///< Destination Address
                {
                    v_Com_Rx_Tsk(stComLoc.stCanParam.uiCmdCode, stComLoc.stCanParam.uiFrameOverFlg);    ///< Receive data process
                    v_Com_Tx_Tsk(stComLoc.stCanParam.uiCmdCode, stComLoc.stCanParam.uiGroupNum, stComLoc.stCanParam.uiBitNum);    ///< Send data
                }
            }
        }
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiFlgTxMsg         = stComDbg.uiFlgTxMsg;
#else
    stCom.uiFlgTxMsg         = stComLoc.stPrmExt.uiFlgTxMsg;
    stCom.uiCmdCode         = stComLoc.stPrmExt.uiCmdCode;
#endif

    /* On grid switch to off grid flag happen, modify the run mode to off-grid mode */
    if(1U == stOnOffGridSwt.uiFlgSwt)
    {
        stComLoc.stPrmExt.uiModRunReq = OFFGRID_MODE;
        stCom.uiModRunReq             = stComLoc.stPrmExt.uiModRunReq;
    }
}
#endif
/**
* @brief   CAN Communication Send function
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
void v_Com_Tx(void)
{
    if((1U == stComDrv.uiFlgTxOk) || ((CAN_DATA_RECORD_CMD == stComLoc.stCanParam.uiCmdCode) && (0U == stSpi.uiFlgReadCmpl)))    ///< Transmission OK
    {
        if(0U == stComLoc.stCanParam.uiTxEndFlg)      ///< Data is not Sent over
        {
            v_Com_Tx_Tsk(stComLoc.stCanParam.uiCmdCode, stComLoc.stCanParam.uiGroupNum, stComLoc.stCanParam.uiBitNum);    ///< Continue to send data
        }
    }
}
#endif
/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk(Uint16 uiDataCmd, Uint16 uiFramesEndFlg)
{
    switch(uiDataCmd)
    {
        /* Run Mode and Order Command */
        case CAN_RUN_ORD_CMD:
            v_Com_Rx_Tsk_RunOrd();
            break;

        /* Voltage and Current Command From BMS */
        case CAN_VOLT_CURR_CMD:
            v_Com_Rx_Tsk_VoltCurr();
            break;

        /* Grid Control Parameter Setting */
        case CAN_GRID_CTRL_CMD:
            v_Com_Rx_Tsk_GridCtrl();
            break;

        /* Operation Data Read */
        case CAN_OP_DATA_READ_CMD:
            v_Com_Rx_Tsk_OpData();
            break;

        /* Three phase power command */
        case CAN_THREE_PHASE_ACTV_POW_CMD:
            v_Com_Rx_Tsk_ThreePhaActvPow();
            break;

        /* Three phase power command */
        case CAN_THREE_PHASE_REACTV_POW_CMD:
            v_Com_Rx_Tsk_ThreePhaReactvPow();
            break;

        /* Italy self test command */
        case CAN_TEST_DATA_READ_CMD:
            v_Com_Rx_Tsk_SelfTest();
            break;

        /* Temperature1 command */
        case CAN_TEMP1_CMD:
            v_Com_Rx_Tsk_Temp1();
            break;

        /* Temperature2 command */
        case CAN_TEMP2_CMD:
            v_Com_Rx_Tsk_Temp2();
            break;

        /* Parameter Setting command */
        case CAN_PARAM_SET_CMD:
            v_Com_Rx_Tsk_PrmSet(uiFramesEndFlg);
            break;

        /* Output Voltage Adjusting */
        case CAN_OUT_VOLT_ADJ_CMD:
            v_Com_Rx_Tsk_BattVoltAdj();
            break;

        /* Output Current Adjusting */
        case CAN_OUT_CURR_ADJ_CMD:
            v_Com_Rx_Tsk_BattCurrAdj();
            break;

        /* Down Output Voltage Adjusting */
        case CAN_OUT_VOLT_DN_ADJ_CMD:
            v_Com_Rx_Tsk_BattDnVoltAdj();
            break;

        /* Down Output Current Adjusting */
        case CAN_OUT_CURR_DN_ADJ_CMD:
            v_Com_Rx_Tsk_BattDnCurrAdj();
            break;

        /* AC Voltage Adjusting */
        case CAN_AC_VOLT_ADJ_CMD:
            v_Com_Rx_Tsk_AcVoltAdj();
            break;

        /* AC Current Adjusting */
        case CAN_AC_CURR_ADJ_CMD:
            v_Com_Rx_Tsk_AcCurrAdj();
            break;

        /* PFC Zero Adjusting */
        case CAN_PFC_ZERO_ADJ_CMD:
            v_Com_Rx_Tsk_PfcZeroAdj();
            break;

        /* PFC STD Command */
        case CAN_PFC_STD_CMD:
            v_Com_Rx_Tsk_PfcStd();
            break;

        /* Grid Type Command */
        case CAN_GRID_TYPE_CMD:
            v_Com_Rx_Tsk_GridType();
            break;

        /* Main DSP upgrade command */
        case CAN_MAIN_DSP_UPG_CMD:
            v_Com_Rx_Tsk_MainDspUpg();
            break;

        /* FCT Command */
        case CAN_FCT_CMD:
            v_Com_Rx_Tsk_Fct();
            break;

        /* Time Sync Command */
        case CAN_TIME_SYCN_CMD:
            v_Com_Rx_Tsk_TiSync();
            break;
			
#if(1U == FLG_CPU2_UPD_EN)
        case CAN_CPU2_UPG1_CMD:
        case CAN_CPU2_UPG2_CMD:
        case CAN_CPU2_UPG3_CMD:
        case CAN_CPU2_UPG4_CMD:
        case CAN_CPU2_UPG5_CMD:		
            v_Com_Rx_Tsk_Cpu2Upg();
            break;
#endif

#if 1U == FLG_FLT_DATA_REC_EN
        /* Fault data record command */
        case CAN_DATA_RECORD_CMD:
            v_Com_Rx_Tsk_TiFltData();
            break;
#endif

#if 2U == GRID_PHASE_NUMBER
        /* CPLD upgrade command */
        case CAN_CPLDUPD_RDY_CMD:
        case CAN_CPLDUPD_NOTICE_CMD:
        case CAN_CPLDUPD_ERASE_CMD:
        case CAN_CPLDUPD_RX_CMD:
        case CAN_CPLDUPD_CHK_CMD:
        case CAN_CPLDUPD_STOP_CMD:
            v_Com_Rx_Tsk_CpldUpd();
            break;
#endif

        default:
            ///< No code
            break;
    }
}

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
#ifndef _SIMULATION_NO_DSP_
static void v_Com_Tx_Tsk(Uint16 uiFuncCode, Uint16 uiGroupNum, Uint16 uiBitNum)
{
    stComLoc.stPrmExt.unIDMaskTx.bit.DATACMD = uiFuncCode;
    stComLoc.stPrmExt.unIDMaskTx.bit.DSTADDR = stComLoc.stCanParam.uiSrcAddr;

    switch(uiFuncCode)
    {
        case CAN_VAC_READ_CMD:
            v_Com_Tx_Tsk_InvVolt();         ///< Inverter voltage order
            break;

        case CAN_PARAM_READ_CMD:
            v_Com_Tx_Tsk_PrmRead(uiGroupNum,uiBitNum);    ///< Parameter read
            break;

        case CAN_VOLT_CURR_CMD:
            v_Com_Tx_Tsk_VoltCurr();        ///< Voltage & current order
            break;

        case CAN_OP_DATA_READ_CMD:
            v_Com_Tx_Tsk_OpData();          ///< Operation data
            break;

        case CAN_TEST_DATA_READ_CMD:
            v_Com_Tx_Tsk_SelfTest();        ///< Italy self-test
            break;

#if 1U == FLG_FLT_DATA_REC_EN
        case CAN_DATA_RECORD_CMD:
            v_Com_Tx_Tsk_FltDataRec();      ///< Fault data record
            break;
#endif

        case CAN_TABLE_VER_CMD:
            v_Com_Tx_Tsk_TblVers();         ///< Version
            break;
			
#if(1U == FLG_CPU2_UPD_EN)
        case CAN_CPU2_UPG1_CMD:
        case CAN_CPU2_UPG2_CMD:
        case CAN_CPU2_UPG3_CMD:
        case CAN_CPU2_UPG4_CMD:
        case CAN_CPU2_UPG5_CMD:
            v_Com_Tx_Tsk_Cpu2Upd();
            break;
#endif
			
#if 2U == GRID_PHASE_NUMBER
        case CAN_CPLDUPD_RDY_CMD:
            v_Com_Tx_Tsk_Dft();             ///< Return to received data
            break;

        case CAN_CPLDUPD_NOTICE_CMD:
            v_Com_Tx_Tsk_CpldUpd_Notice();  ///< CpldUpd Notice
            break;

        case CAN_CPLDUPD_ERASE_CMD:
            v_Com_Tx_Tsk_CpldUpd_Erase();   ///< CpldUpd Erase
            break;

        case CAN_CPLDUPD_RX_CMD:
            v_Com_Tx_Tsk_CpldUpd_Rx();      ///< CpldUpd Receive
            break;

        case CAN_CPLDUPD_CHK_CMD:
            v_Com_Tx_Tsk_CpldUpd_Chk();     ///< CpldUpd Check
            break;

        case CAN_CPLDUPD_STOP_CMD:
            v_Com_Tx_Tsk_CpldUpd_Stop();    ///< CpldUpd Stop
            break;
#endif

        default:
            v_Com_Tx_Tsk_Dft();             ///< Return to received data
            break;
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.unIDMaskTx.all     = stComDbg.unIDMaskTx.all;
    stCom.uiFlgTxMsg         = stComDbg.uiFlgTxMsg;
#else
    stCom.unIDMaskTx.all     = stComLoc.stPrmExt.unIDMaskTx.all;
    stCom.uiFlgTxMsg         = stComLoc.stPrmExt.uiFlgTxMsg;
#endif
}
#endif
/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_RunOrd(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);    ///< Run Stage: 0-PFC enable D2D enable; 1-PFC enable PFC disable; 2-PFC disable D2D enable
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);    ///< Run Mode: 0-Charge OnGrid; 1-Bidirection OnGrid; 2-OffGrid; 3-Openloop
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);    ///< Run Command: 0-Stop; 1-Start

    if((PFC_EN_D2D_EN != l_uiDataRxTmp0) || (OPENLOOP_MODE != l_uiDataRxTmp1))    ///< Avoid to sending PFC_EN_D2D_EN and OPENLOOP_MODE commands at the same time
    {
        if(l_uiDataRxTmp0 <= PFC_EN_D2D_DIS)
        {
            stComLoc.stPrmExt.uiStgRunEnReq = l_uiDataRxTmp0;
        }
        if(l_uiDataRxTmp1 <= PFC_OL_D2D_DISCH_MODE)
        {
            stComLoc.stPrmExt.uiModRunReq = l_uiDataRxTmp1;
        }
        if(l_uiDataRxTmp2 <= START_CMD)
        {
            stComLoc.stPrmExt.uiCmdRunReq = l_uiDataRxTmp2;
        }
    }

	if(START_CMD == stComIf.uiCmdRun)
	{
		if(stComLoc.stPrmExt.uiStgRunEnReq != stCom.uiStgRunEnReq)
		{
			stComLoc.stPrmExt.uiStgRunEnReq = stCom.uiStgRunEnReq;
		}

	    /* If Target mode is CHG_ONGRID_MODE,Current mode is BIDIR_ONGRID_MODE
	     * Or Target mode is BIDIR_ONGRID_MODE,Current mode is CHG_ONGRID_MODE , then switching mode*/
		if( ( (CHG_ONGRID_MODE == stComLoc.stPrmExt.uiModRunReq) && (BIDIR_ONGRID_MODE == stComIf.uiModRun) ) \
				|| ( (BIDIR_ONGRID_MODE == stComLoc.stPrmExt.uiModRunReq) && (CHG_ONGRID_MODE == stComIf.uiModRun) ) )
		{
			///< No code
		}
		else
		{
			stComLoc.stPrmExt.uiModRunReq = stComIf.uiModRun;
		}
	}

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiStgRunEnReq = stComDbg.uiStgRunEnReq;
    stCom.uiModRunReq   = stComDbg.uiModRunReq;
    stCom.uiCmdRunReq   = stComDbg.uiCmdRunReq;
#else
    stCom.uiStgRunEnReq = stComLoc.stPrmExt.uiStgRunEnReq;
    stCom.uiModRunReq   = stComLoc.stPrmExt.uiModRunReq;
    stCom.uiCmdRunReq   = stComLoc.stPrmExt.uiCmdRunReq;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_VoltCurr(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);    ///< Receive Data
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);    ///< Receive Data
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);    ///< Receive Data
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);    ///< Receive Data

    stComLoc.stPrmExt.ftVoltBattChrgReq = (float32)((int16)l_uiDataRxTmp0) * 0.1f;
    stComLoc.stPrmExt.ftCurrBattChrgReq = (float32)((int16)l_uiDataRxTmp1) * 0.01f;
    stComLoc.stPrmExt.ftVoltBattDchaReq = (float32)((int16)l_uiDataRxTmp2) * 0.1f;
    stComLoc.stPrmExt.ftCurrBattDchaReq = -(float32)((int16)l_uiDataRxTmp3) * 0.01f;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftVoltBattChrgReq = stComDbg.ftVoltBattChrgReq;
    stCom.ftCurrBattChrgReq = stComDbg.ftCurrBattChrgReq;
    stCom.ftVoltBattDchaReq = stComDbg.ftVoltBattDchaReq;
    stCom.ftCurrBattDchaReq = stComDbg.ftCurrBattDchaReq;
#else
    stCom.ftVoltBattChrgReq = stComLoc.stPrmExt.ftVoltBattChrgReq;
    stCom.ftCurrBattChrgReq = stComLoc.stPrmExt.ftCurrBattChrgReq;
    stCom.ftVoltBattDchaReq = stComLoc.stPrmExt.ftVoltBattDchaReq;
    stCom.ftCurrBattDchaReq = stComLoc.stPrmExt.ftCurrBattDchaReq;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_GridCtrl(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3
    float32 l_ftVoltTmp = 0.0f;     ///< Temporary voltage
    float32 l_ftFrqTmp  = 0.0f;     ///< Temporary frequency

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

    stComLoc.uiModGrid = l_uiDataRxTmp0;

    if(CAN_V2G_MODE_PRM == stComLoc.uiModGrid)
    {
        stComLoc.stPrmExt.unModPfcPow.bit.uiModPowCtrl     = PFC_PWR_GRID_STD_MODE;     ///< PFC power grid standard mode
        stComLoc.stPrmExt.unModPfcPow.bit.uiModActvImbal   = PFC_BAL_RUN_MODE;          ///< Active power balance run mode
        stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvImbal = PFC_BAL_RUN_MODE;          ///< PFC balance run mode

    	switch(stComDrv.uiByteRx[2])
    	{
			case ACTV_POW_RAT_SET_MODE:
				stComLoc.stPrmExt.ftPwrActvReq = ((float32)(int16)l_uiDataRxTmp2) * 0.0001f * stComTbl.stPrmPfcRtd1.ftPowRtd;
				break;

			case ACTV_POW_VAL_SET_MODE:
				stComLoc.stPrmExt.ftPwrActvReq = (float32)(int16)l_uiDataRxTmp2;
				break;

			default:
				///< do nothing
				break;
    	}

    	switch(stComDrv.uiByteRx[3])
    	{
			case REACTV_POW_PF_MODE:
				stComLoc.stPrmExt.uiModeReactv = REACTV_POW_PF_MODE;
                stComLoc.stPrmExt.ftPFReq = (float32)((int16)l_uiDataRxTmp3) * 0.0001f;
				break;

			case REACTV_POW_QU_MODE:
				stComLoc.stPrmExt.uiModeReactv = REACTV_POW_QU_MODE;
				break;

			case REACTV_POW_QP_MODE:
				stComLoc.stPrmExt.uiModeReactv = REACTV_POW_QP_MODE;
				break;

			case REACTV_POW_QT_MODE:
				stComLoc.stPrmExt.uiModeReactv = REACTV_POW_QT_MODE;
				stComLoc.stPrmExt.ftPwrReactvReq = (float32)((int16)l_uiDataRxTmp3) * 0.0001f * stCom.ftQAcMax;
				break;

			default:
			    stComLoc.stPrmExt.uiModeReactv = REACTV_POW_QT_MODE;
				break;
    	}
    }
    else if(CAN_V2L_MODE_PRM == stComLoc.uiModGrid)
    {
        l_ftVoltTmp = (float32)((int16)l_uiDataRxTmp1) * RECPR_COEFF_VOLT_ARM * stPfcDataCalc.stSysParm.ftVoltRtdRecpr;
        l_ftFrqTmp  = (float32)((int16)l_uiDataRxTmp2) * RECPR_COEFF_FRQ_ARM;
        if((l_ftVoltTmp < stComTbl.stPrmGridVoltProt.ftValOver1) && (l_ftVoltTmp > stComTbl.stPrmGridVoltProt.ftValUnder1) \
           && (l_ftFrqTmp < stComTbl.stPrmGridFrqProt.ftValOver1) && (l_ftFrqTmp > stComTbl.stPrmGridFrqProt.ftValUnder1))
        {
    	    stComLoc.stPrmExt.ftVoltAcV2LReq = l_ftVoltTmp * stComTbl.stPrmPfcRtd1.ftVoltGrid;
    	    stComLoc.stPrmExt.ftFrqAcV2LReq  = l_ftFrqTmp;
        }
    }
    else
    {
        ///< no code
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.unModPfcPow.all     = stComDbg.unModPfcPow.all;
    stCom.uiModeReactv        = stComDbg.uiModeReactv;
    stCom.ftPwrActvReq        = stComDbg.ftPwrActvReq;
    stCom.ftPFReq             = stComDbg.ftPFReq;
    stCom.ftVoltAcV2LReq      = stComDbg.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq       = stComDbg.ftFrqAcV2LReq;
#else
    stCom.unModPfcPow.all     = stComLoc.stPrmExt.unModPfcPow.all;
    stCom.uiModeReactv        = stComLoc.stPrmExt.uiModeReactv;
    stCom.ftPwrActvReq        = stComLoc.stPrmExt.ftPwrActvReq;
    stCom.ftPFReq             = stComLoc.stPrmExt.ftPFReq;
    stCom.ftPwrReactvReq      = stComLoc.stPrmExt.ftPwrReactvReq;
    stCom.ftVoltAcV2LReq      = stComLoc.stPrmExt.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq       = stComLoc.stPrmExt.ftFrqAcV2LReq;
#endif
}

/**
* @brief   CAN Receive three phase active power Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_ThreePhaActvPow(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

    stComLoc.stPrmExt.unModPfcPow.bit.uiModPowCtrl     = PFC_PWR_ARM_CTRL_MODE;     ///< PFC power ARM control mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModActvImbal   = (l_uiDataRxTmp3 & 0x0001U);
    stComLoc.stPrmExt.unModPfcPow.bit.uiModActvArmCtrl = (l_uiDataRxTmp3 & 0x0006U)>>1;

    /* Three-phase Power Command */
    if(PFC_BAL_RUN_MODE == stComLoc.stPrmExt.unModPfcPow.bit.uiModActvImbal)      ///< Active balance run mode
    {
        stComLoc.stPrmExt.ftPwrActvReq = (float32)(int16)l_uiDataRxTmp0;
        stComLoc.stPrmExt.ftPwrChrgReq = stComLoc.stPrmExt.ftPwrActvReq;
    }
    else    ///< PFC imbalance run mode
    {
        stComLoc.stPrmExt.ftPaAcReq = (float32)(int16)l_uiDataRxTmp0;
        stComLoc.stPrmExt.ftPbAcReq = (float32)(int16)l_uiDataRxTmp1;
        stComLoc.stPrmExt.ftPcAcReq = (float32)(int16)l_uiDataRxTmp2;
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.unModPfcPow.all   = stComDbg.unModPfcPow.all;
    stCom.ftPwrActvReq      = stComDbg.ftPwrActvReq;
    stCom.ftPwrChrgReq      = stComDbg.ftPwrChrgReq;
    stCom.ftPaAcReq         = stComDbg.ftPaAcReq;
    stCom.ftPbAcReq         = stComDbg.ftPbAcReq;
    stCom.ftPcAcReq         = stComDbg.ftPcAcReq;
#else
    stCom.unModPfcPow.all   = stComLoc.stPrmExt.unModPfcPow.all;
    stCom.ftPwrActvReq      = stComLoc.stPrmExt.ftPwrActvReq;
    stCom.ftPwrChrgReq      = stComLoc.stPrmExt.ftPwrChrgReq;
    stCom.ftPaAcReq         = stComLoc.stPrmExt.ftPaAcReq;
    stCom.ftPbAcReq         = stComLoc.stPrmExt.ftPbAcReq;
    stCom.ftPcAcReq         = stComLoc.stPrmExt.ftPcAcReq;
#endif
}

/**
* @brief   CAN Receive three phase reactive power Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_ThreePhaReactvPow(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

    stComLoc.stPrmExt.unModPfcPow.bit.uiModPowCtrl       = PFC_PWR_ARM_CTRL_MODE;     ///< PFC power ARM control mode
    stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvImbal   = (l_uiDataRxTmp3 & 0x0001U);
    stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvArmCtrl = (l_uiDataRxTmp3 & 0x0006U)>>1;

    /* Three-phase Power Command */
    if(PFC_BAL_RUN_MODE == stComLoc.stPrmExt.unModPfcPow.bit.uiModReactvImbal)    ///< PFC balance run mode
    {
        stComLoc.stPrmExt.ftPwrReactvReq = (float32)(int16)l_uiDataRxTmp0;
    }
    else    ///< PFC imbalance run mode
    {
        stComLoc.stPrmExt.ftQaAcReq = (float32)(int16)l_uiDataRxTmp0;
        stComLoc.stPrmExt.ftQbAcReq = (float32)(int16)l_uiDataRxTmp1;
        stComLoc.stPrmExt.ftQcAcReq = (float32)(int16)l_uiDataRxTmp2;
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.unModPfcPow.all     = stComDbg.unModPfcPow.all;
    stCom.ftPwrReactvReq      = stComDbg.ftPwrReactvReq;
    stCom.ftQaAcReq           = stComDbg.ftQaAcReq;
    stCom.ftQbAcReq           = stComDbg.ftQbAcReq;
    stCom.ftQcAcReq           = stComDbg.ftQcAcReq;
#else
    stCom.unModPfcPow.all     = stComLoc.stPrmExt.unModPfcPow.all;
    stCom.ftPwrReactvReq      = stComLoc.stPrmExt.ftPwrReactvReq;
    stCom.ftQaAcReq           = stComLoc.stPrmExt.ftQaAcReq;
    stCom.ftQbAcReq           = stComLoc.stPrmExt.ftQbAcReq;
    stCom.ftQcAcReq           = stComLoc.stPrmExt.ftQcAcReq;
#endif
}

/**
* @brief   CAN Receive Italy self test command Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_SelfTest(void)
{
    /* Italy Self Test Command */
    if(stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_STB)
    {
        stComLoc.uiNumSelfTest = stComDrv.uiByteRx[0];

        if(stComDrv.uiByteRx[1] <= 1U)
        {
            stComLoc.stPrmExt.uiEnaSelfTest = stComDrv.uiByteRx[1];
        }
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiEnaSelfTest = stComDbg.uiEnaSelfTest;
#else
    stCom.uiEnaSelfTest = stComLoc.stPrmExt.uiEnaSelfTest;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_OpData(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);

    if(CAN_SRC_ARM == stComLoc.stCanParam.uiSrcAddr)    ///< Source is ARM
    {
        stComLoc.stPrmExt.uiStArm = l_uiDataRxTmp0;
    }
    else
    {
        if(0U == (l_uiDataRxTmp0 & ARM_SYS_FLT_RESET))    ///< If source is PC, select fault reset only
        {
        	stComLoc.stPrmExt.uiStArm &= ~ARM_SYS_FLT_RESET;
        }
        else
        {
        	stComLoc.stPrmExt.uiStArm |= ARM_SYS_FLT_RESET;
        }
        stComLoc.stPrmExt.uiStArm |= ARM_DC_RLY_STA;
    }

    if(l_uiDataRxTmp1 > 0U)
    {
    	stComLoc.stPrmExt.ftVoltBattBms    = (float32)(int16)l_uiDataRxTmp1 * 0.1f;
    }
    if(l_uiDataRxTmp2 > 0U)
    {
    	stComLoc.stPrmExt.ftVoltBattBmsMax = (float32)(int16)l_uiDataRxTmp2 * 0.1f;
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiStArm          = stComDbg.uiStArm;
    stCom.ftVoltBattBms    = stComDbg.ftVoltBattBms;
    stCom.ftVoltBattBmsMax = stComDbg.ftVoltBattBmsMax;
#else
    stCom.uiStArm          = stComLoc.stPrmExt.uiStArm;
    stCom.ftVoltBattBms    = stComLoc.stPrmExt.ftVoltBattBms;
    stCom.ftVoltBattBmsMax = stComLoc.stPrmExt.ftVoltBattBmsMax;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Temp1(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    if(CAN_SRC_ARM == stComLoc.stCanParam.uiSrcAddr)    ///< Source is ARM
    {
        /* Receive Data From Can */
        l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
        l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
        l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
        l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

        /* Temperature Data Handle*/
        stComLoc.stPrmExt.ftTempArmBd = (float32)((int16)l_uiDataRxTmp0) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc0  = (float32)((int16)l_uiDataRxTmp1) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc1  = (float32)((int16)l_uiDataRxTmp2) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc2  = (float32)((int16)l_uiDataRxTmp3) * RECPR_COEFF_TEMP_ARM;
    }
    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftTempArmBd = stComDbg.ftTempArmBd;
    stCom.ftTempNtc0  = stComDbg.ftTempNtc0;
    stCom.ftTempNtc1  = stComDbg.ftTempNtc1;
    stCom.ftTempNtc2  = stComDbg.ftTempNtc2;
#else
    stCom.ftTempArmBd = stComLoc.stPrmExt.ftTempArmBd;
    stCom.ftTempNtc0  = stComLoc.stPrmExt.ftTempNtc0;
    stCom.ftTempNtc1  = stComLoc.stPrmExt.ftTempNtc1;
    stCom.ftTempNtc2  = stComLoc.stPrmExt.ftTempNtc2;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Temp2(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    if(CAN_SRC_ARM == stComLoc.stCanParam.uiSrcAddr)    ///< Source is ARM
    {
        /* Receive Data From Can */
        l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
        l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
        l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
        l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

        /* Temperature Data Handle*/
        stComLoc.stPrmExt.ftTempNtc3 = (float32)((int16)l_uiDataRxTmp0) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc4 = (float32)((int16)l_uiDataRxTmp1) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc5 = (float32)((int16)l_uiDataRxTmp2) * RECPR_COEFF_TEMP_ARM;
        stComLoc.stPrmExt.ftTempNtc6 = (float32)((int16)l_uiDataRxTmp3) * RECPR_COEFF_TEMP_ARM;
    }
    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftTempNtc3 = stComDbg.ftTempNtc3;
    stCom.ftTempNtc4 = stComDbg.ftTempNtc4;
    stCom.ftTempNtc5 = stComDbg.ftTempNtc5;
    stCom.ftTempNtc6 = stComDbg.ftTempNtc6;
#else
    stCom.ftTempNtc3 = stComLoc.stPrmExt.ftTempNtc3;
    stCom.ftTempNtc4 = stComLoc.stPrmExt.ftTempNtc4;
    stCom.ftTempNtc5 = stComLoc.stPrmExt.ftTempNtc5;
    stCom.ftTempNtc6 = stComLoc.stPrmExt.ftTempNtc6;
#endif
}

/**
* @brief   User CAN parameter storage function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_PrmSet_PrmSto(Uint16 uiGroupNum, Uint16 uiBitNum, Uint16 uiDataType)
{
    Uint16 i = 0U;
    Uint16 l_siDataTmp1 = 0U;    ///< Temporary Data1
    Uint16 l_uiDataTmp2 = 0U;    ///< Temporary Data2

    /* Data Type Judgment And Storage*/
    if(TYPE_INT16 == uiDataType)            ///< int16 Type
    {
        l_siDataTmp1 = (stComLoc.stCanParam.uiRxTabData[2]<<8 | stComLoc.stCanParam.uiRxTabData[3]);
        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr) = l_siDataTmp1;
    }
    else if(TYPE_UINT16 == uiDataType)      ///< uint16 Type
    {
        l_uiDataTmp2 = (stComLoc.stCanParam.uiRxTabData[2]<<8 | stComLoc.stCanParam.uiRxTabData[3]);
        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr) = l_uiDataTmp2;
    }
    else if(TYPE_INT32 == uiDataType)       ///< int32 Type
    {
        l_siDataTmp1 = (stComLoc.stCanParam.uiRxTabData[0] << 8 | stComLoc.stCanParam.uiRxTabData[1]);
        l_uiDataTmp2 = (stComLoc.stCanParam.uiRxTabData[2] << 8 | stComLoc.stCanParam.uiRxTabData[3]);

        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr) = l_uiDataTmp2;
        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr + 1) = l_siDataTmp1;

    }
    else if(TYPE_UINT32 == uiDataType)       ///< Uint32 Type
    {
        l_siDataTmp1 = (stComLoc.stCanParam.uiRxTabData[0] << 8 | stComLoc.stCanParam.uiRxTabData[1]);
        l_uiDataTmp2 = (stComLoc.stCanParam.uiRxTabData[2] << 8 | stComLoc.stCanParam.uiRxTabData[3]);

        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr) = l_uiDataTmp2;
        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr + 1) = l_siDataTmp1;
    }
    else if(TYPE_FLOAT32 == uiDataType)      ///< float Type
    {
        l_siDataTmp1 = (stComLoc.stCanParam.uiRxTabData[0] << 8 | stComLoc.stCanParam.uiRxTabData[1]);
        l_uiDataTmp2 = (stComLoc.stCanParam.uiRxTabData[2] << 8 | stComLoc.stCanParam.uiRxTabData[3]);

        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr) = l_uiDataTmp2;
        *(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr + 1) = l_siDataTmp1;
    }
    else if(TYPE_STRING == uiDataType)       ///< string Type, Fixed Length is 40
    {
        for(i = 0U; i < 40U; i++)
        {
            *(Uint16 *)(sFuncCode[sGroup[uiGroupNum].puiGroupName[uiBitNum]].ParaAddr + i) = stComLoc.stCanParam.uiRxTabData[i];
        }
    }
    else
    {
        //no code
    }
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_PrmSet_StoChk(void)
{
    Uint16  l_uiDataSaveFlg = 0U;    ///< The Data need to be saved
    Uint16  l_uiDataSrc = 0U;        ///< Data Source

    /* Check whether the data needs to be saved to EEPROM */
    l_uiDataSaveFlg = (sFuncCode[sGroup[stComLoc.stCanParam.uiGroupNum].puiGroupName[stComLoc.stCanParam.uiBitNum]].uiModifyAndDataType & 0x0002U) >> 1U;    ///< Save Flag: 1-Save to EEPROM
    l_uiDataSrc = (sFuncCode[sGroup[stComLoc.stCanParam.uiGroupNum].puiGroupName[stComLoc.stCanParam.uiBitNum]].uiModifyAndDataType & 0x0C00U) >> 10U;       ///< Data Source: 1- Master DSP 0x0C00U
    stComLoc.uiIdxAry[0] = sGroup[stComLoc.stCanParam.uiGroupNum].puiGroupName[stComLoc.stCanParam.uiBitNum];

    if((1U == l_uiDataSaveFlg) && (1U == l_uiDataSrc))   ///< Data need to be saved and is from Master
    {
        v_Com_Rx_Tsk_EepPrmUpd();    ///< EEPROM related parameter update
        (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    }
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_PrmSet(Uint16 uiFramesEndFlg)
{
	Uint16  l_uiIndex = 0U;

    if(1U == uiFramesEndFlg)       ///< The data frame transmission is complete
    {
        l_uiIndex = (stComLoc.stCanParam.uiGroupNum << 8U) + stComLoc.stCanParam.uiBitNum;
        if((stComLoc.stCanParam.uiGroupNum <= GROUP_NUM) && (stComLoc.stCanParam.uiBitNum <= (sGroup[stComLoc.stCanParam.uiGroupNum].uiLength)) \
        && (l_uiIndex > CON_ZERO))
        {
            v_Com_Rx_Tsk_PrmSet_PrmSto(stComLoc.stCanParam.uiGroupNum, stComLoc.stCanParam.uiBitNum, stComLoc.stCanParam.uiDataType);
            v_Com_Rx_Tsk_PrmSet_StoChk();    ///< Check whether the data needs to be saved to EEPROM
        }
    }
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Adj_Cal(ST_COM_CAL *pCal)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3
    float32 l_ftDataRxTmp0 = 0.0f;
    float32 l_ftDataRxTmp1 = 0.0f;
    float32 l_ftDataRxTmp2 = 0.0f;
    float32 l_ftDataRxTmp3 = 0.0f;
    float32 l_ftAdjCofKTmp = 1.0f;
    float32 l_ftAdjCofBTmp = 0.0f;

    if(0U == pCal->uiCntrIntl)    ///< Prevent continuous transmission
    {
        /* Receive Data From Can */
        l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
        l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
        l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
        l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);
        l_ftDataRxTmp0 = ((float32)l_uiDataRxTmp0) * pCal->ftRatRxPrm;    ///< Actual Value1
        l_ftDataRxTmp1 = ((float32)l_uiDataRxTmp1) * pCal->ftRatRxPrm;    ///< Display Value1
        l_ftDataRxTmp2 = ((float32)l_uiDataRxTmp2) * pCal->ftRatRxPrm;    ///< Actual Value2
        l_ftDataRxTmp3 = ((float32)l_uiDataRxTmp3) * pCal->ftRatRxPrm;    ///< Display Value2

        /* Calibration Calculate */
        if(((l_ftDataRxTmp1 > l_ftDataRxTmp3)||(l_ftDataRxTmp1 < l_ftDataRxTmp3)) && (pCal->ftCoeffK > 0.0f))
        {
            l_ftAdjCofKTmp = pCal->ftCoeffK*(l_ftDataRxTmp0 - l_ftDataRxTmp2)/(l_ftDataRxTmp1 - l_ftDataRxTmp3);
            l_ftAdjCofBTmp = l_ftDataRxTmp0 - l_ftAdjCofKTmp*(l_ftDataRxTmp1 - pCal->ftCoeffB)/pCal->ftCoeffK;
            if((l_ftAdjCofKTmp > pCal->ftCoeffKMin) && (l_ftAdjCofKTmp < pCal->ftCoeffKMax) && (l_ftAdjCofBTmp > pCal->ftCoeffBMin) \
                    && (l_ftAdjCofBTmp < pCal->ftCoeffBMax))
            {
                pCal->ftCoeffK = l_ftAdjCofKTmp;
                pCal->ftCoeffB = l_ftAdjCofBTmp;
            }
        }

        pCal->uiCntrIntl = ADJ_INTL_NUM;
    }
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Adj_Sto(Uint16 uiAddrCoeffK, Uint16 uiAddrCoeffB)
{
    /* Store calibration coefficients */
    stComLoc.uiIdxAry[0] = uiAddrCoeffK;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);

    stComLoc.uiIdxAry[0] = uiAddrCoeffB;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_BattVoltAdj(void)
{
    /* Calibration Calculate */
	stComLoc.BattVolt.ftCoeffK =  stCom.ftCoeffKBattVoltCal;
	stComLoc.BattVolt.ftCoeffB =  stCom.ftCoeffBBattVoltCal;
    v_Com_Rx_Tsk_Adj_Cal(&stComLoc.BattVolt);

    stComLoc.stPrmExt.ftCoeffKBattVoltCal = stComLoc.BattVolt.ftCoeffK;
    stComLoc.stPrmExt.ftCoeffBBattVoltCal = stComLoc.BattVolt.ftCoeffB;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftCoeffKBattVoltCal = stComDbg.ftCoeffKBattVoltCal;
    stCom.ftCoeffBBattVoltCal = stComDbg.ftCoeffBBattVoltCal;
#else
    stCom.ftCoeffKBattVoltCal = stComLoc.stPrmExt.ftCoeffKBattVoltCal;
    stCom.ftCoeffBBattVoltCal = stComLoc.stPrmExt.ftCoeffBBattVoltCal;
#endif

    /* Parameter Change Storage*/
    v_Com_Rx_Tsk_Adj_Sto(stComLoc.BattVolt.uiAddrCoeffK,stComLoc.BattVolt.uiAddrCoeffB);
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_BattCurrAdj(void)
{
    /* Calibration Calculate */
	stComLoc.BattCurr.ftCoeffK =  stCom.ftCoeffKBattCurrCal;
	stComLoc.BattCurr.ftCoeffB =  stCom.ftCoeffBBattCurrCal;
    v_Com_Rx_Tsk_Adj_Cal(&stComLoc.BattCurr);

    stComLoc.stPrmExt.ftCoeffKBattCurrCal = stComLoc.BattCurr.ftCoeffK;
    stComLoc.stPrmExt.ftCoeffBBattCurrCal = stComLoc.BattCurr.ftCoeffB;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftCoeffKBattCurrCal = stComDbg.ftCoeffKBattCurrCal;
    stCom.ftCoeffBBattCurrCal = stComDbg.ftCoeffBBattCurrCal;
#else
    stCom.ftCoeffKBattCurrCal = stComLoc.stPrmExt.ftCoeffKBattCurrCal;
    stCom.ftCoeffBBattCurrCal = stComLoc.stPrmExt.ftCoeffBBattCurrCal;
#endif

    /* Parameter Change Storage*/
    v_Com_Rx_Tsk_Adj_Sto(stComLoc.BattCurr.uiAddrCoeffK, stComLoc.BattCurr.uiAddrCoeffB);
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_BattDnVoltAdj(void)
{
    /* Calibration Calculate */
	stComLoc.BattDnVolt.ftCoeffK =  stCom.ftCoeffKBattDwnVoltCal;
	stComLoc.BattDnVolt.ftCoeffB =  stCom.ftCoeffBBattDwnVoltCal;
    v_Com_Rx_Tsk_Adj_Cal(&stComLoc.BattDnVolt);

    stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal = stComLoc.BattDnVolt.ftCoeffK;
    stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal = stComLoc.BattDnVolt.ftCoeffB;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftCoeffKBattDwnVoltCal = stComDbg.ftCoeffKBattDwnVoltCal;
    stCom.ftCoeffBBattDwnVoltCal = stComDbg.ftCoeffBBattDwnVoltCal;
#else
    stCom.ftCoeffKBattDwnVoltCal = stComLoc.stPrmExt.ftCoeffKBattDwnVoltCal;
    stCom.ftCoeffBBattDwnVoltCal = stComLoc.stPrmExt.ftCoeffBBattDwnVoltCal;
#endif

    /* Parameter Change Storage*/
    v_Com_Rx_Tsk_Adj_Sto(stComLoc.BattDnVolt.uiAddrCoeffK,stComLoc.BattDnVolt.uiAddrCoeffB);
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_BattDnCurrAdj(void)
{
    /* Calibration Calculate */
	stComLoc.BattDnCurr.ftCoeffK =  stCom.ftCoeffKBattDwnCurrCal;
	stComLoc.BattDnCurr.ftCoeffB =  stCom.ftCoeffBBattDwnCurrCal;
    v_Com_Rx_Tsk_Adj_Cal(&stComLoc.BattDnCurr);

    stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal = stComLoc.BattDnCurr.ftCoeffK;
    stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal = stComLoc.BattDnCurr.ftCoeffB;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftCoeffKBattDwnCurrCal = stComDbg.ftCoeffKBattDwnCurrCal;
    stCom.ftCoeffBBattDwnCurrCal = stComDbg.ftCoeffBBattDwnCurrCal;
#else
    stCom.ftCoeffKBattDwnCurrCal = stComLoc.stPrmExt.ftCoeffKBattDwnCurrCal;
    stCom.ftCoeffBBattDwnCurrCal = stComLoc.stPrmExt.ftCoeffBBattDwnCurrCal;
#endif

    /* Parameter Change Storage*/
    v_Com_Rx_Tsk_Adj_Sto(stComLoc.BattDnCurr.uiAddrCoeffK, stComLoc.BattDnCurr.uiAddrCoeffB);
}

/**
* @brief   CAN AC voltage adjusting Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_AcVoltAdj(void)
{
    float32 l_ftVoltDisp = 0.0f;    // Display voltage
    Uint16  l_uiDataRxTmp0 = 0U;    // Temporary Data0
#if GRID_PHASE_NUMBER > 1U
    Uint16  l_uiDataRxTmp1 = 0U;    // Temporary Data1
#if GRID_PHASE_NUMBER > 2U
    Uint16  l_uiDataRxTmp2 = 0U;    // Temporary Data2
#endif
#endif

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
#if GRID_PHASE_NUMBER > 1U
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
#if GRID_PHASE_NUMBER > 2U
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
#endif
#endif

    /* Calibration Calculate */
    l_ftVoltDisp = (float32)l_uiDataRxTmp0 * RECPR_COEFF_VOLT_ARM;

    /* Calibration Calculate */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK = stCom.stPrmPfcAdjCoeff.ftVaK;
    v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK, stPfcDataCalc.stMeasParm.ftVaRmsLPF, l_ftVoltDisp);
#if GRID_PHASE_NUMBER > 1U
    l_ftVoltDisp = (float32)l_uiDataRxTmp1 * RECPR_COEFF_VOLT_ARM;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK = stCom.stPrmPfcAdjCoeff.ftVbK;
    v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK, stPfcDataCalc.stMeasParm.ftVbRmsLPF, l_ftVoltDisp);
#if GRID_PHASE_NUMBER > 2U
    l_ftVoltDisp = (float32)l_uiDataRxTmp2 * RECPR_COEFF_VOLT_ARM;
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK = stCom.stPrmPfcAdjCoeff.ftVcK;
    v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK, stPfcDataCalc.stMeasParm.ftVcRmsLPF, l_ftVoltDisp);
#endif
#endif

#if (1U == COM_DBG)
    stCom.stPrmPfcAdjCoeff.ftVaK = stComDbg.stPrmPfcAdjCoeff.ftVaK;
    stCom.stPrmPfcAdjCoeff.ftVbK = stComDbg.stPrmPfcAdjCoeff.ftVbK;
    stCom.stPrmPfcAdjCoeff.ftVcK = stComDbg.stPrmPfcAdjCoeff.ftVcK;
#else
    stCom.stPrmPfcAdjCoeff.ftVaK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVaK;
    stCom.stPrmPfcAdjCoeff.ftVbK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVbK;
    stCom.stPrmPfcAdjCoeff.ftVcK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftVcK;
#endif

    /* Store Data */
    stComLoc.uiIdxAry[0] = VA_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    stComLoc.uiIdxAry[0] = VB_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 2U
    stComLoc.uiIdxAry[0] = VC_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
#endif
}

/**
* @brief   CAN AC current adjusting Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_AcCurrAdj(void)
{
    float32 l_ftCurrDisp = 0.0f;    // Display current
    Uint16  l_uiDataRxTmp0 = 0U;    // Temporary Data0
#if GRID_PHASE_NUMBER > 1U
    Uint16  l_uiDataRxTmp1 = 0U;    // Temporary Data1
#if GRID_PHASE_NUMBER > 2U
    Uint16  l_uiDataRxTmp2 = 0U;    // Temporary Data2
#endif
#endif

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
#if GRID_PHASE_NUMBER > 1U
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
#if GRID_PHASE_NUMBER > 2U
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
#endif
#endif

    /* Calibration Calculate */
    if(PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        l_ftCurrDisp = (float32)l_uiDataRxTmp0 * RECPR_COEFF_CURR_ARM;
        stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK = stCom.stPrmPfcAdjCoeff.ftIaK;
        v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK, stPfcDataCalc.stMeasParm.ftIaRmsLPF, l_ftCurrDisp);
#if GRID_PHASE_NUMBER > 1U
        l_ftCurrDisp = (float32)l_uiDataRxTmp1 * RECPR_COEFF_CURR_ARM;
        stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK = stCom.stPrmPfcAdjCoeff.ftIbK;
        v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK, stPfcDataCalc.stMeasParm.ftIbRmsLPF, l_ftCurrDisp);
#if GRID_PHASE_NUMBER > 2U
        l_ftCurrDisp = (float32)l_uiDataRxTmp2 * RECPR_COEFF_CURR_ARM;
        stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK = stCom.stPrmPfcAdjCoeff.ftIcK;
        v_Com_Rx_Tsk_AcCoeff(&stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK, stPfcDataCalc.stMeasParm.ftIcRmsLPF, l_ftCurrDisp);
#endif
#endif
    }

#if (1U == COM_DBG)
    stCom.stPrmPfcAdjCoeff.ftIaK = stComDbg.stPrmPfcAdjCoeff.ftIaK;
    stCom.stPrmPfcAdjCoeff.ftIbK = stComDbg.stPrmPfcAdjCoeff.ftIbK;
    stCom.stPrmPfcAdjCoeff.ftIcK = stComDbg.stPrmPfcAdjCoeff.ftIcK;
#else
    stCom.stPrmPfcAdjCoeff.ftIaK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIaK;
    stCom.stPrmPfcAdjCoeff.ftIbK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIbK;
    stCom.stPrmPfcAdjCoeff.ftIcK = stComLoc.stPrmExt.stPrmPfcAdjCoeff.ftIcK;
#endif
    /* Store Data */
    stComLoc.uiIdxAry[0] = IA_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    stComLoc.uiIdxAry[0] = IB_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1);
#if GRID_PHASE_NUMBER > 2U
    stComLoc.uiIdxAry[0] = IC_ADJ_COFK_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1);
#endif
#endif
}

/**
* @brief   CAN AC coefficient adjusting Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_AcCoeff(float32 *pftCoeff, float32 ftDisp, float32 ftAct)
{
    float32 l_ftCoeffTmp = 1.0f;

    l_ftCoeffTmp = *pftCoeff;

    /* Coefficient calculation */
    if(ftDisp > 0.0f)
    {
        *pftCoeff = l_ftCoeffTmp * ftAct / ftDisp;
        vFcn_FtUpDwnLim(&(*pftCoeff), ADJ_COFK_MAX, ADJ_COFK_MIN);
    }
}

/**
* @brief   CAN Receive PFC AD zero adjusting Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_PfcZeroAdj(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    // Temporary Data0

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);

    stComLoc.stPrmExt.uiCmdPfcADZeroAdj = l_uiDataRxTmp0;

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiCmdPfcADZeroAdj = stComDbg.uiCmdPfcADZeroAdj;
#else
    stCom.uiCmdPfcADZeroAdj = stComLoc.stPrmExt.uiCmdPfcADZeroAdj;
#endif
}

/**
* @brief   PFC AD zero adjusting 100ms Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tsk_PfcZeroAdj_100ms(void)
{
#if 1U
    if((AD_BIAS_ADJUST_OVER != stCom.uiCmdPfcADZeroAdj) && (1U == stPfcDataCalc.stMeasParm.uiFlgADBiasOK))
#else
    if((AD_BIAS_ADJUST_OVER != stCom.uiCmdPfcADZeroAdj) && (stComIf.uiCmdRun == 0U))
#endif

    {
        /* Grid voltage bias adjust */
        if(0U != (stCom.uiCmdPfcADZeroAdj & VG_BIAS_ADJUST_BIT))
        {
            v_Com_Tsk_PfcZeroAdj_Vg();
        }

        /* Grid current bias adjust */
        if(0U != (stCom.uiCmdPfcADZeroAdj & IG_BIAS_ADJUST_BIT))
        {
            v_Com_Tsk_PfcZeroAdj_Ig();
        }

        /* Grid voltage DC bias adjust */
        if(0U != (stCom.uiCmdPfcADZeroAdj & VG_BIAS_DC_ADJUST_BIT))
        {
            v_Com_Tsk_PfcZeroAdj_VgDc();
        }

        /* Grid current DC bias adjust */
        if(0U != (stCom.uiCmdPfcADZeroAdj & IG_BIAS_DC_ADJUST_BIT))
        {
            v_Com_Tsk_PfcZeroAdj_IgDc();
        }

        stComLoc.stPrmExt.uiCmdPfcADZeroAdj = AD_BIAS_ADJUST_OVER;
        stCom.uiCmdPfcADZeroAdj             = stComLoc.stPrmExt.uiCmdPfcADZeroAdj;
    }
}

/**
* @brief   PFC Vg AD zero adjusting task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tsk_PfcZeroAdj_Vg(void)
{
    /* Phase A voltage AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_A = stPfcDataCalc.stMeasParm.siVaADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgZero_A             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_A;
    /* Phase A voltage AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VA_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    /* Phase B voltage AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_B = stPfcDataCalc.stMeasParm.siVbADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgZero_B             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_B;
    /* Phase B voltage AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VB_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 2U
    /* Phase C voltage AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_C = stPfcDataCalc.stMeasParm.siVcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgZero_C             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgZero_C;
    /* Phase C voltage AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
#endif
#if 2U == GRID_PHASE_NUMBER
    /* Phase A inv voltage AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_A = stPfcDataCalc.stMeasParm.siVaInvADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_A             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_A;
    /* Phase A inv voltage AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VAINV_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    /* Phase B inv voltage AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_B = stPfcDataCalc.stMeasParm.siVbInvADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgInvZero_B             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgInvZero_B;
    /* Phase B inv voltage AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VBINV_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
}

/**
* @brief   PFC Ig AD zero adjusting task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tsk_PfcZeroAdj_Ig(void)
{
    /* Phase A current AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_A = stPfcDataCalc.stMeasParm.siIaADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgZero_A             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_A;
    /* Phase A current AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IA_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    /* Phase B current AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_B = stPfcDataCalc.stMeasParm.siIbADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgZero_B             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_B;
    /* Phase B current AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IB_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    /* Balance bridge current AD zero adjust */
#ifndef SST_1250kW
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_N = stPfcDataCalc.stMeasParm.siInADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgZero_N             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_N;
#endif
    /* Balance bridge current AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IN_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 2U
    /* Phase C current AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_C = stPfcDataCalc.stMeasParm.siIcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgZero_C             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgZero_C;
    /* Phase C current AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
#endif
}

/**
* @brief   PFC VgDc AD zero adjusting task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tsk_PfcZeroAdj_VgDc(void)
{
    /* Phase A voltage DC component AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_A = stPfcDataCalc.stMeasParm.siVaDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_A             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_A;
    /* Phase A voltage DC component AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VA_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    /* Phase B voltage DC component AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_B = stPfcDataCalc.stMeasParm.siVbDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_B             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_B;
    /* Phase B voltage DC component AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VB_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 2U
    /* Phase C voltage DC component AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_C = stPfcDataCalc.stMeasParm.siVcDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siVgDcZero_C             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siVgDcZero_C;
    /* Phase C voltage DC component AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = VC_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
#endif
}

/**
* @brief   PFC IgDc AD zero adjusting task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tsk_PfcZeroAdj_IgDc(void)
{
    /* Phase A current DC component(N line relay open) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A = stPfcDataCalc.stMeasParm.siIaDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A;
    /* Phase A current DC component(N line relay open) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IA_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 1U
    /* Phase B current DC component(N line relay open) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B = stPfcDataCalc.stMeasParm.siIbDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B;
    /* Phase B current DC component(N line relay open) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IB_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#if GRID_PHASE_NUMBER > 2U
    /* Phase C current DC component(N line relay open) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C = stPfcDataCalc.stMeasParm.siIcDcADBiasLPF;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C;
    /* Phase C current DC component(N line relay open) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IC_DC_ADJ_ZERO_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);

    /* Phase A current DC component(N line relay close) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A_N = stPfcDataCalc.stMeasParm.siIaDcADBiasLPF_N;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_A_N;
    /* Phase A current DC component(N line relay close) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IA_DC_ADJ_ZERO_N_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    /* Phase B current DC component(N line relay close) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B_N = stPfcDataCalc.stMeasParm.siIbDcADBiasLPF_N;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_B_N;
    /* Phase B current DC component(N line relay close) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IB_DC_ADJ_ZERO_N_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    /* Phase C current DC component(N line relay close) AD zero adjust */
    stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C_N = stPfcDataCalc.stMeasParm.siIcDcADBiasLPF_N;
    stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N             = stComLoc.stPrmExt.stPrmPfcAdjCoeff.siIgDcZero_C_N;
    /* Phase C current DC component(N line relay close) AD zero write Eeprom */
    stComLoc.uiIdxAry[0] = IC_DC_ADJ_ZERO_N_NUM;
    (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
#endif
#endif
}

/**
* @brief   CAN PFC standard Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_PfcStd(void)
{
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);

    /* Receive Data From Can */
    if((l_uiDataRxTmp0 != stComLoc.stPrmExt.uiStdGridSet) && (STOP_CMD == stComLoc.stPrmExt.uiCmdRunReq))
    {
		stComLoc.stPrmExt.uiStdGridSet = l_uiDataRxTmp0;
		vFcn_UiUpDwnLim(&stComLoc.stPrmExt.uiStdGridSet, GRID_STD_SUM_NUM-1U, 0U);
		stComLoc.uiIdxAry[0] = GRID_STD_NUM;
		(void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiStdGridSet    = stComDbg.uiStdGridSet;
#else
    stCom.uiStdGridSet    = stComLoc.stPrmExt.uiStdGridSet;
#endif
}

/**
* @brief   CAN Grid type Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_GridType(void)
{
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);

    /* Receive Data From Can */
    if((l_uiDataRxTmp0 != stComLoc.stPrmExt.uiTypeGrid) && (STOP_CMD == stComLoc.stPrmExt.uiCmdRunReq))
    {
        stComLoc.stPrmExt.uiTypeGrid = l_uiDataRxTmp0;
        stComLoc.uiIdxAry[0] = GRID_TYPE_NUM;
        (void)ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stComLoc.uiIdxAry[0], 1U);
    }

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiTypeGrid      = stComDbg.uiTypeGrid;
#else
    stCom.uiTypeGrid      = stComLoc.stPrmExt.uiTypeGrid;
#endif
}

/**
* @brief   CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_MainDspUpg(void)
{
    if(0U == stComLoc.stPrmExt.uiFlgUpgProg)
    {
        stComLoc.stPrmExt.uiCmdRunReq  = STOP_CMD;  ///< Run command request

        stComLoc.stPrmExt.uiFlgUpgProg = 1U;    ///< Program upgrade flag
    }

#if (1U == COM_DBG)
	stCom.uiFlgUpgProg = stComDbg.uiFlgUpgProg;
    stCom.uiCmdRunReq  = stComDbg.uiCmdRunReq;
#else
	stCom.uiFlgUpgProg = stComLoc.stPrmExt.uiFlgUpgProg;
	stCom.uiCmdRunReq  = stComLoc.stPrmExt.uiCmdRunReq;
#endif
}

/**
* @brief   CAN Receive Task of FCT
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Fct(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);

    stComLoc.stPrmExt.unCmdFct.all = l_uiDataRxTmp0;

#if(1U != GRID_PHASE_NUMBER)
    if(1U == stComLoc.stPrmExt.unCmdFct.bit.uiEnFctPwm)
    {
        v_PieCfg_Cmn_FctPwm();       ///< Clear PFC interrupt enable bit
        v_CmpssCfg_D2d_FctPwm();     ///< Disable D2d comparator function
        v_EPwmCfg_D2d_FctPwm();      ///< Disable D2d EPWM TZ function
        v_EPwmDrv_D2d_ClrTzFlg();    ///< Clear D2D EPWM TZ Flag

        v_CmpssCfg_Pfc_FctPwm();     ///< Disable PFC comparator function
        v_EPwmCfg_Pfc_FctPwm();      ///< Disable PFC epwm function
    #if(3U == GRID_PHASE_NUMBER)
        v_EPwmDrv_Pfc_ClrTzFlg();    ///< Clear PFC EPWM TZ Flag
    #endif
        /* Set Fault No check */
        //v_D2dPowCtrl_FctPwm();       ///< Set D2D CLA fault No check parameter
        stComTbl.unWordPfcFltMask1.all   = 0xFFFFU;
        stComTbl.unWordPfcFltMask2.all   = 0xFFFFU;
        stComTbl.unWordPfcFltMask3.all   = 0xFFFFU;
        stComTbl.stPrmD2dDiag.uiFltCpuNC = 0xFFFFU;
        stComTbl.unWordSysFltMask.all    = 0xFFFFU;
    }
#endif

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.unCmdFct.all  = stComDbg.unCmdFct.all;
#else
    stCom.unCmdFct.all  = stComLoc.stPrmExt.unCmdFct.all;
#endif
}

/**
* @brief   CAN Time Synchronization Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_TiSync(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3    

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);    
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);    
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);    

    /* Combine the received data into a 64-bit time value */
    stComLoc.stPrmExt.unTiSys.all = ((Uint64)l_uiDataRxTmp0 << 48U) | ((Uint64)l_uiDataRxTmp1 << 32U) | ((Uint64)l_uiDataRxTmp2 << 16U) | (Uint64)l_uiDataRxTmp3;
    
    /* Output Signal */
#if (1U == COM_DBG)
    stCom.unTiSys.all = stComDbg.unTiSys.all;
#else
    stCom.unTiSys.all = stComLoc.stPrmExt.unTiSys.all;
#endif
}

#if 1U == FLG_FLT_DATA_REC_EN
/**
* @brief   CAN Time Synchronization Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_TiFltData(void)
{
    Uint16  l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16  l_uiDataRxTmp1 = 0U;    ///< Temporary Data1
    Uint16  l_uiDataRxTmp2 = 0U;    ///< Temporary Data2
    Uint16  l_uiDataRxTmp3 = 0U;    ///< Temporary Data3

    /* Receive Data From Can */
    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8 | stComDrv.uiByteRx[3]);
    l_uiDataRxTmp2 = (stComDrv.uiByteRx[4] << 8 | stComDrv.uiByteRx[5]);
    l_uiDataRxTmp3 = (stComDrv.uiByteRx[6] << 8 | stComDrv.uiByteRx[7]);

    /* Combine the received data into a 64-bit time value */
    stComLoc.stPrmExt.unTiReq.all  = ((Uint64)l_uiDataRxTmp0 << 48U) | ((Uint64)l_uiDataRxTmp1 << 32U) | ((Uint64)l_uiDataRxTmp2 << 16U) | (Uint64)l_uiDataRxTmp3;
    stComLoc.stPrmExt.uiFlgReadReq = 1U;    ///< Set read request flag
    stComLoc.uiFrameFltDataRead    = 0U;    ///< Clear read count
    
    /* Output Signal */
#if (1U == COM_DBG)
    stCom.unTiReq.all  = stComDbg.unTiReq.all;
    stCom.uiFlgReadReq = stComDbg.uiFlgReadReq;
#else
    stCom.unTiReq.all  = stComLoc.stPrmExt.unTiReq.all;
    stCom.uiFlgReadReq = stComLoc.stPrmExt.uiFlgReadReq;
#endif
}
#endif

#if 2U == GRID_PHASE_NUMBER
/**
* @brief   CpldUpd Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_CpldUpd(void)
{
    stComLoc.stPrmExt.uiCmdRunReq  = STOP_CMD;  ///< Run command request
		
#if (1U == COM_DBG)
    stCom.uiCmdRunReq  = stComDbg.uiCmdRunReq;
#else
    stCom.uiCmdRunReq  = stComLoc.stPrmExt.uiCmdRunReq;
#endif
}
#endif

#if(1U == FLG_CPU2_UPD_EN)
/**
* @brief   CPU2 Upgrade CAN Receive Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Rx_Tsk_Cpu2Upg(void)
{
    Uint16 i;

    if(0U == IpcRegs.IPCFLG.bit.IPC5)
    {
        IpcRegs.IPCCLR.all = 0xFFFFFFFFUL;   ///< Clear IPC register
        /* Send message to CPU2 */
        IpcRegs.IPCSENDCOM = stComLoc.stCanParam.uiCmdCode;
        for(i=0U; i<8U; i++)
        {
            stPrmC1ToC2.uiCpu2UpdByte[i] = stComDrv.uiByteRx[i];
        }
        IpcRegs.IPCSET.bit.IPC5 = 1U;
    }

    stComLoc.stPrmExt.uiCmdRunReq  = STOP_CMD;  ///< Run command request
    stCom.uiCmdRunReq  = stComLoc.stPrmExt.uiCmdRunReq;
}

/**
* @brief   CPU2 Upgrade CAN Send Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_Cpu2Upd(void)
{
    Uint16 i;
    Uint32 l_ulCntrWait = 0UL;

    /* Wait CPU2 response */
    while(1U == IpcRegs.IPCFLG.bit.IPC5)
    {
        /* Jumping out after timeout */
        if(l_ulCntrWait++ >= IPC_COM_OVER_TI)
        {
            break;
        }
    }
    /* CPU2 response */
    for(i=0U; i<8U; i++)
    {
        stCom.uiByteTx[i] = stPrmC2ToC1.uiCpu2UpdBack[i];
    }

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg   = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}
#endif

/**
* @brief   Parameter read Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_PrmRead( Uint16 uiGroupNum, Uint16 uiBitNum)
{
    Uint16 l_uiIndex = 0U;
    Uint16 l_uiDataTmp1 = 0U;    ///< Temporary data1
    Uint16 l_uiDataTmp2 = 0U;    ///< Temporary data2
    Uint16 l_uiDataType = 0U;    ///< Data Type
    Uint16 i = 0U;

    l_uiIndex = sGroup[uiGroupNum].puiGroupName[uiBitNum];

    if((stComLoc.stCanParam.uiGroupNum <= GROUP_NUM) && (stComLoc.stCanParam.uiBitNum <= (sGroup[stComLoc.stCanParam.uiGroupNum].uiLength)) \
    && (CON_ZERO < l_uiIndex) && (ILLEGAL_FUNCTION_CODE_INDEX > l_uiIndex))
    {
        /* 1-int16  2-Uint16 3-int32  4-Uint32 5-float 6-string 0-else */
        l_uiDataType = (sFuncCode[l_uiIndex].uiModifyAndDataType & 0x01C0U)>>6;

        if(l_uiDataType == stComLoc.stCanParam.uiDataType)      ///< Data Type is correct
        {
            if(TYPE_INT16 == l_uiDataType)    ///< int16 Type
            {
                stComLoc.stCanParam.uiTxWord[0] = 0x8000U | 1U<<7 | l_uiDataType<<2;    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;         ///< Group number and Bit number
                stComLoc.stCanParam.uiTxWord[2] = 0U;
                stComLoc.stCanParam.uiTxWord[3] = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr);
                stComLoc.stCanParam.uiTxEndFlg = 1U;
            }
            else if(TYPE_UINT16 == l_uiDataType)    ///< Uint16 Type
            {
                stComLoc.stCanParam.uiTxWord[0] = 0x8000U | 1U<<7 | l_uiDataType<<2;    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;         ///< Group number and Bit number
                stComLoc.stCanParam.uiTxWord[2] = 0U;
                stComLoc.stCanParam.uiTxWord[3] = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr);
                stComLoc.stCanParam.uiTxEndFlg = 1U;
            }
            else if(TYPE_INT32 == l_uiDataType)    ///< int32 Type
            {
                stComLoc.stCanParam.uiTxWord[0] = 0x8000U | 1U<<7 | l_uiDataType<<2;    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;         ///< Group number and Bit number
                for(i = 0U; i <= 1U; i++)
                {
                    stComLoc.stCanParam.uiTxWord[3U-i] = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i);
                }
                stComLoc.stCanParam.uiTxEndFlg = 1U;
            }
            else if(TYPE_UINT32 == l_uiDataType)    ///< Uint32 Type
            {
                stComLoc.stCanParam.uiTxWord[0] = 0x8000U | 1U<<7 | l_uiDataType<<2;    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;         ///< Group number and Bit number
                for(i = 0U; i <= 1U; i++)
                {
                    stComLoc.stCanParam.uiTxWord[3U-i] = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i);
                }
                stComLoc.stCanParam.uiTxEndFlg = 1U;
            }
            else if(TYPE_FLOAT32 == l_uiDataType)    ///< float32 Type
            {
                stComLoc.stCanParam.uiTxWord[0] = 0x8000U | 1U<<7 | l_uiDataType<<2;    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;         ///< Group number and Bit number
                for(i = 0U; i <= 1U; i++)
                {
                    stComLoc.stCanParam.uiTxWord[3U-i] = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i);
                }
                stComLoc.stCanParam.uiTxEndFlg = 1U;
            }
            else if((TYPE_STRING == l_uiDataType) && (stComLoc.stCanParam.uiFrameNum > 0U))    ///< String Type
            {
                stComLoc.stCanParam.uiTxWord[0] = (stComLoc.stCanParam.uiFrameNum << 7) | (l_uiDataType << 2);    ///< Control word
                stComLoc.stCanParam.uiTxWord[1] = (uiGroupNum << 8) | uiBitNum;    ///< Group number and Bit number

                i = 4U*(stComLoc.stCanParam.uiFrameNum - 1U);
                {
                    l_uiDataTmp1 = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i);
                    l_uiDataTmp2 = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i + 1);
                    stComLoc.stCanParam.uiTxWord[2] = l_uiDataTmp1 << 8 | l_uiDataTmp2;
                    l_uiDataTmp1 = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i + 2);
                    l_uiDataTmp2 = *((Uint16*)sFuncCode[l_uiIndex].ParaAddr + i + 3);
                    stComLoc.stCanParam.uiTxWord[3] = l_uiDataTmp1 << 8 | l_uiDataTmp2;
                }

                if(stComLoc.stCanParam.uiFrameNum >= 10U)
                {
                    stComLoc.stCanParam.uiTxWord[0] = 0x8000U | (l_uiDataType << 2) | (stComLoc.stCanParam.uiFrameNum << 7);    ///< Control word: Transmission Over

                    stComLoc.stCanParam.uiTxEndFlg = 1U;
                }
            }
            else
            {
                ///< No code
            }

            /* Collect Data */
            stCom.uiByteTx[1] =  stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;
            stCom.uiByteTx[0] =  (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;
            stCom.uiByteTx[3] =  stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;
            stCom.uiByteTx[2] =  (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;
            stCom.uiByteTx[5] =  stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;
            stCom.uiByteTx[4] =  (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;
            stCom.uiByteTx[7] =  stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;
            stCom.uiByteTx[6] =  (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;

            /* Configure Transmit email Flag*/
            stComLoc.stPrmExt.uiFlgTxMsg = 1U;
        }
    }
}

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_VoltCurr(void)
{
    float32 l_ftDataTmp0 = 0.0f;    ///< Temporary data0
    float32 l_ftDataTmp1 = 0.0f;    ///< Temporary data1
    float32 l_ftDataTmp2 = 0.0f;    ///< Temporary data2
    float32 l_ftDataTmp3 = 0.0f;    ///< Temporary data3

    l_ftDataTmp0 = stCom.ftVoltBattChrgReq * COEFF_VOLT_ARM;
    l_ftDataTmp1 = stCom.ftCurrBattChrgReq * COEFF_CURR_ARM;
    l_ftDataTmp2 = stCom.ftVoltBattDchaReq * COEFF_VOLT_ARM;
    l_ftDataTmp3 = -stCom.ftCurrBattDchaReq * COEFF_CURR_ARM;

    stComLoc.stCanParam.uiTxWord[0] = (Uint16)l_ftDataTmp0;
    stComLoc.stCanParam.uiTxWord[1] = (Uint16)l_ftDataTmp1;
    stComLoc.stCanParam.uiTxWord[2] = (Uint16)l_ftDataTmp2;
    stComLoc.stCanParam.uiTxWord[3] = (Uint16)l_ftDataTmp3;

    /* Collect Data */
    stCom.uiByteTx[1] = stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;
    stCom.uiByteTx[0] = (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;
    stCom.uiByteTx[3] = stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;
    stCom.uiByteTx[2] = (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;
    stCom.uiByteTx[5] = stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;
    stCom.uiByteTx[4] = (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;
    stCom.uiByteTx[7] = stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;
    stCom.uiByteTx[6] = (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;
}

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_InvVolt(void)
{
    float32 l_ftDataTmp0 = 0.0f;    ///< Temporary data0
    float32 l_ftDataTmp1 = 0.0f;    ///< Temporary data1

#if 2U == GRID_PHASE_NUMBER
    l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftVaInvRmsLPF * COEFF_VOLT_ARM;
    l_ftDataTmp1 = stPfcDataCalc.stMeasParm.ftVbInvRmsLPF * COEFF_VOLT_ARM;
#else
    l_ftDataTmp0 = 0.0f;
    l_ftDataTmp1 = 0.0f;
#endif

    stComLoc.stCanParam.uiTxWord[0] = (Uint16)l_ftDataTmp0;
    stComLoc.stCanParam.uiTxWord[1] = (Uint16)l_ftDataTmp1;
    stComLoc.stCanParam.uiTxWord[2] = 0;
    stComLoc.stCanParam.uiTxWord[3] = 0;

    /* Collect Data */
    stCom.uiByteTx[1] = stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;
    stCom.uiByteTx[0] = (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;
    stCom.uiByteTx[3] = stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;
    stCom.uiByteTx[2] = (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;
    stCom.uiByteTx[5] = stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;
    stCom.uiByteTx[4] = (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;
    stCom.uiByteTx[7] = stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;
    stCom.uiByteTx[6] = (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;
}

/**
* @brief   User CAN Data Change function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_OpData_SndData(Uint16 u16FrameNum)
{
    static Uint16 sl_uiTmp1 = 0U;
    float32 l_ftDataTmp0 = 0.0f;    ///< Temporary data0
    float32 l_ftDataTmp1 = 0.0f;    ///< Temporary data1
    float32 l_ftDataTmp2 = 0.0f;    ///< Temporary data2

    switch(u16FrameNum)
    {
        case 0x1U:
            l_ftDataTmp0 = stD2dAdc.ftVoltBattLpf10Hz * COEFF_VOLT_ARM;
            l_ftDataTmp1 = stD2dAdc.ftVoltBattUpLpf10Hz * COEFF_VOLT_ARM;
            l_ftDataTmp2 = stD2dAdc.ftVoltBattDwnLpf10Hz * COEFF_VOLT_ARM;

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< Total Output Voltage
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< Up Output Voltage
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< Down Output Voltage
            break;

        case 0x2U:
            l_ftDataTmp0 = stD2dAdc.ftCurrBattLpf10Hz * COEFF_CURR_ARM;
            l_ftDataTmp1 = stD2dAdc.ftCurrBattUpLpf10Hz * COEFF_CURR_ARM;
            l_ftDataTmp2 = stD2dAdc.ftCurrBattDwnLpf10Hz * COEFF_CURR_ARM;

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< Total Output Current
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< Up Output Current
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< Down Output Current
            break;

        case 0x3U:
            l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftVaRmsLPF * COEFF_VOLT_ARM;
            l_ftDataTmp1 = stPfcDataCalc.stMeasParm.ftVbRmsLPF * COEFF_VOLT_ARM;
            l_ftDataTmp2 = stPfcDataCalc.stMeasParm.ftVcRmsLPF * COEFF_VOLT_ARM;

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)(l_ftDataTmp0);    ///< Phase A voltage
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)(l_ftDataTmp1);    ///< Phase B voltage
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)(l_ftDataTmp2);    ///< Phase C voltage
            break;

        case 0x4U:
            l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftIaRmsLPF * COEFF_CURR_ARM;
            l_ftDataTmp1 = stPfcDataCalc.stMeasParm.ftIbRmsLPF * COEFF_CURR_ARM;
            l_ftDataTmp2 = stPfcDataCalc.stMeasParm.ftIcRmsLPF * COEFF_CURR_ARM;

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)(l_ftDataTmp0);    ///< Phase A current
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)(l_ftDataTmp1);    ///< Phase B current
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)(l_ftDataTmp2);    ///< Phase C current
            break;

        case 0x5U:
            l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftVbusLPF * COEFF_VOLT_ARM;
#if(1U == GRID_PHASE_NUMBER)
            l_ftDataTmp1 = 0.0f;
#else
            l_ftDataTmp1 = stPfcDataCalc.stMeasParm.ftInRmsLPF * COEFF_CURR_ARM;
#endif
            l_ftDataTmp2 = stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF * COEFF_FRQ_ARM;
            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< Bus voltage
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< Phase N current
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< Grid frequency
            break;

        case 0x6U:
#if(1U == GRID_PHASE_NUMBER)
            l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftVbusLPF * COEFF_VOLT_ARM;
            l_ftDataTmp1 = 0.0f;
#else
            l_ftDataTmp0 = stPfcDataCalc.stMeasParm.ftVbusPosLPF * COEFF_VOLT_ARM;
            l_ftDataTmp1 = (stPfcDataCalc.stMeasParm.ftVbusLPF - stPfcDataCalc.stMeasParm.ftVbusPosLPF) * COEFF_VOLT_ARM;
#endif
            l_ftDataTmp2 = stPfcDataCalc.stMeasParm.ftPfLPF * COEFF_PF_ARM;
            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< BusPos voltage
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< BusNeg voltage
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< Power factor
            break;

        case 0x7U:
            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(-stPfcDataCalc.stMeasParm.siPaAvgLPF);    ///< Phase A active power
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(-stPfcDataCalc.stMeasParm.siPbAvgLPF);    ///< Phase B active power
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(-stPfcDataCalc.stMeasParm.siPcAvgLPF);    ///< Phase C active power
            break;

        case 0x8U:
            stComLoc.stCanParam.uiTxWord[1] = (Uint16)stPfcDataCalc.stMeasParm.siQaAvgLPF;    ///< Phase A reactive power
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)stPfcDataCalc.stMeasParm.siQbAvgLPF;    ///< Phase B reactive power
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)stPfcDataCalc.stMeasParm.siQcAvgLPF;    ///< Phase C reactive power
            break;

        case 0x9U:
            l_ftDataTmp0 = stComTbl.stPrmPfcRtd1.ftPowRtd;
            l_ftDataTmp1 = stComTbl.stPrmPfcRtd1.ftPowBattChrgRtd;
            l_ftDataTmp2 = stCmnAdc.ftTempDspBd * COEFF_TEMP_ARM;

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< Rated Input Power
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< Rated Output power
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< DSP board temperature
            break;

        case 0xAU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcStMac.unStsToArm.all;                ///< PFC Status
            sl_uiTmp1 = stPerphCtrl.stBld.uiFlgDone & 0x01U;                            ///<Bleed OK Flag
            sl_uiTmp1 = sl_uiTmp1 | ((stPerphCtrl.stSPRly.uiSt  & 0x03U)<<1U);          ///<SPRelay State
            sl_uiTmp1 = sl_uiTmp1 | ((stPerphCtrl.stSPRly.uiCmd & 0x03U)<<3U);          ///<SPRelay CMD
            sl_uiTmp1 = sl_uiTmp1 | ((stPerphCtrl.stV2LAuxPow.uiFlgEn & 0x01U)<<5U);    ///< AUX Power Flag
            sl_uiTmp1 = sl_uiTmp1 | ((stD2dStMac.uiStD2dRun & 0x07U)<<6U);              ///<D2D Run State
            sl_uiTmp1 = sl_uiTmp1 | ((stCom.uiStArm & ARM_DC_RLY_STA)<<9U);             ///< Battery Relay State
            stComLoc.stCanParam.uiTxWord[2] = sl_uiTmp1;                                ///< D2D Status
            stComLoc.stCanParam.uiTxWord[3] = stComTbl.unWordPfcFlt1.all;               ///< PFC fault1
            break;

        case 0xBU:
            stComLoc.stCanParam.uiTxWord[1] = stComTbl.unWordPfcFlt2.all;    ///< PFC fault2
            stComLoc.stCanParam.uiTxWord[2] = stComTbl.unWordPfcFlt3.all;    ///< PFC fault3
            stComLoc.stCanParam.uiTxWord[3] = stComTbl.unWordSysFlt.all;     ///< System fault
            break;

        case 0xCU:
            stComLoc.stCanParam.uiTxWord[1]   = stD2dDiag.uiFltCpu;    ///< D2D Fault1
            stComLoc.stCanParam.uiTxWord[2]   = stD2dDiag.uiFltCla;    ///< D2D Fault2

            if(stPfcStMac.unPFCSts.bit.uiMacSt >= PFC_ST_MAC_PWMEN)
            {
                sl_uiTmp1 = 0x1U;    ///< PFC PWM ON
            }
            else
            {
                sl_uiTmp1 = 0x0U;    ///< PFC PWM OFF
            }
            if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN)
            {
                sl_uiTmp1 = sl_uiTmp1 | 0x2U;    ///< D2D ON/OFF
            }
            sl_uiTmp1 = sl_uiTmp1 | ((stComIf.uiCmdRun & 0x01U)<<2U);                 ///< Run CMD
            sl_uiTmp1 = sl_uiTmp1 | ((stComIf.uiModPfcRun & 0x07U)<<3U);              ///< PFC Run Mode
            sl_uiTmp1 = sl_uiTmp1 | ((stComIf.uiModD2dRun & 0x07U)<<6U);              ///< D2D Run Mode
            sl_uiTmp1 = sl_uiTmp1 | ((stPfcGridCtrl.stVrt.uiFlgLvrt & 0x01U)<<9U);    ///< 0-Fan disable, 1-Fan Enable
            sl_uiTmp1 = sl_uiTmp1 | ((stPowLim.uiFlgHTLim & 0x01U)<<10U);             ///< 1-High temperature power limitation
            stComLoc.stCanParam.uiTxWord[3] = sl_uiTmp1;                              ///< Run status
            break;

        case 0xDU:
            l_ftDataTmp0 = (stPowLim.ftCurrBattChrgMaxToBms * COEFF_CURR_ARM);
            l_ftDataTmp1 = (stPowLim.ftCurrBattDchaMaxToBms * COEFF_CURR_ARM);
            l_ftDataTmp2 = (stPowLim.ftFanDuty * COEFF_FAN_DUTY_ARM);

            stComLoc.stCanParam.uiTxWord[1] = (Uint16)(int16)l_ftDataTmp0;    ///< Max charge current to BMS
            stComLoc.stCanParam.uiTxWord[2] = (Uint16)(int16)l_ftDataTmp1;    ///< Max discharge current to BMS
            stComLoc.stCanParam.uiTxWord[3] = (Uint16)(int16)l_ftDataTmp2;    ///< Fan Duty to ARM
            break;

        default:
            ///< No code
            break;
    }
}

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_OpData(void)
{
    stComLoc.stCanParam.uiTxEndFlg = 0U;
    stComLoc.uiFrmNrOpData++;

    if(stComLoc.uiFrmNrOpData > 0xDU)
    {
        stComLoc.uiFrmNrOpData = 0U;    ///< Restart count
        stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
    }
    else
    {
        stComLoc.stCanParam.uiTxWord[0] = stComLoc.uiFrmNrOpData;    ///< The current frame number
        v_Com_Tx_Tsk_OpData_SndData(stComLoc.uiFrmNrOpData);         ///< Send Operation data according to the frame number

        /* Collect Data */
        stCom.uiByteTx[0] =  (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[1] =  stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;           ///< Low
        stCom.uiByteTx[2] =  (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[3] =  stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;           ///< Low
        stCom.uiByteTx[4] =  (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[5] =  stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;           ///< Low
        stCom.uiByteTx[6] =  (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[7] =  stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;           ///< Low

        /* Configure Transmit email Flag*/
        stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    }
}

/**
* @brief   CAN Data Italy self test Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_SelfTest(void)
{
    stComLoc.stCanParam.uiTxEndFlg = 0U;
    stComLoc.uiFrmNrSelfTest++;

    if(stComLoc.uiFrmNrSelfTest > 0x13U)
    {
        stComLoc.uiFrmNrSelfTest = 0U;    // Restart count
        stComLoc.stCanParam.uiTxEndFlg = 1U;    // The current frame data transfer is complete
    }
    else
    {
        stComLoc.stCanParam.uiTxWord[0] = stComLoc.uiFrmNrSelfTest;    // The current frame number
        v_Com_Tx_Tsk_SelfTest_SndData(stComLoc.uiFrmNrSelfTest);    // Send Operation data according to the frame number

        /* Collect Data */
        stCom.uiByteTx[0] =  stComLoc.uiFrmNrSelfTest;    //High
        stCom.uiByteTx[1] =  stComLoc.uiNumSelfTest;    //Low
        stCom.uiByteTx[2] =  (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[3] =  stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;           ///< Low
        stCom.uiByteTx[4] =  (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[5] =  stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;           ///< Low
        stCom.uiByteTx[6] =  (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;    ///< High
        stCom.uiByteTx[7] =  stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;           ///< Low

        /* Configure Transmit email Flag*/
        stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    }
}

/**
* @brief   CAN Data Italy self test send data Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_SelfTest_SndData(Uint16 u16FrameNum)
{
    switch(u16FrameNum)
    {
        case 0x01U:
            stComLoc.stCanParam.uiTxWord[1] = stComLoc.stPrmExt.uiFltSelfTest;              ///< Self test fault
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st59S1.uiResult;      ///< Test result of Grid over voltage protection-S1
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st59S2.uiResult;      ///< Test result of Grid over voltage protection-S2
            break;

        case 0x02U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st27S1.uiResult;      ///< Test result of Grid under voltage protection-S1
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st27S2.uiResult;      ///< Test result of Grid under voltage protection-S2
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81OvS1.uiResult;    ///< Test result of Grid over frequency protection-S1
            break;

        case 0x03U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81OvS2.uiResult;    ///< Test result of Grid over frequency protection-S2
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81UnS1.uiResult;    ///< Test result of Grid under frequency protection-S1
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81UnS2.uiResult;    ///< Test result of Grid under frequency protection-S2
            break;

        case 0x04U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st59S1.uiValSet;      ///< Trip value set of Grid over voltage protection-S1
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st59S1.uiTiSet;       ///< Trip time set of Grid over voltage protection-S1
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st59S1.uiValTrip;     ///< Trip value of Grid over voltage protection-S1
            break;

        case 0x05U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st59S1.uiTiTrip;      ///< Trip time of Grid over voltage protection-S1
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st59S1.uiVoltTrip;    ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st59S1.uiFrqTrip;     ///<  Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x06U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st59S2.uiValSet;      ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st59S2.uiTiSet;       ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st59S2.uiValTrip;     ///< Trip value
            break;

        case 0x07U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st59S2.uiTiTrip;      ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st59S2.uiVoltTrip;    ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st59S2.uiFrqTrip;     ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x08U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st27S1.uiValSet;      ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st27S1.uiTiSet;       ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st27S1.uiValTrip;     ///< Trip value
            break;

        case 0x09U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st27S1.uiTiTrip;      ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st27S1.uiVoltTrip;    ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st27S1.uiFrqTrip;     ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x0AU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st27S2.uiValSet;      ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st27S2.uiTiSet;       ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st27S2.uiValTrip;     ///< Trip value
            break;

        case 0x0BU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st27S2.uiTiTrip;      ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st27S2.uiVoltTrip;    ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st27S2.uiFrqTrip;     ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x0CU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81OvS1.uiValSet;    ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81OvS1.uiTiSet;     ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81OvS1.uiValTrip;   ///< Trip value
            break;

        case 0x0DU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81OvS1.uiTiTrip;    ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81OvS1.uiVoltTrip;  ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81OvS1.uiFrqTrip;   ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x0EU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81OvS2.uiValSet;    ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81OvS2.uiTiSet;     ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81OvS2.uiValTrip;   ///< Trip value
            break;

        case 0x0FU:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81OvS2.uiTiTrip;    ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81OvS2.uiVoltTrip;  ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81OvS2.uiFrqTrip;   ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x10U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81UnS1.uiValSet;    ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81UnS1.uiTiSet;     ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81UnS1.uiValTrip;   ///< Trip value
            break;

        case 0x11U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81UnS1.uiTiTrip;    ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81UnS1.uiVoltTrip;  ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81UnS1.uiFrqTrip;   ///< Grid frequency at the trigger moment/0.01Hz
            break;

        case 0x12U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81UnS2.uiValSet;    ///< Trip value set
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81UnS2.uiTiSet;     ///< Trip time set
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81UnS2.uiValTrip;   ///< Trip value
            break;

        case 0x13U:
            stComLoc.stCanParam.uiTxWord[1] = stPfcGridCtrl.stGridDet.st81UnS2.uiTiTrip;    ///< Trip time
            stComLoc.stCanParam.uiTxWord[2] = stPfcGridCtrl.stGridDet.st81UnS2.uiVoltTrip;  ///< Grid voltage at the trigger moment/0.1V
            stComLoc.stCanParam.uiTxWord[3] = stPfcGridCtrl.stGridDet.st81UnS2.uiFrqTrip;   ///< Grid frequency at the trigger moment/0.01Hz
            break;

        default:
            // No code
            break;
    }
}

#if 1U == FLG_FLT_DATA_REC_EN
/**
* @brief   Fault data read task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_FltDataRec(void)
{
    stComLoc.stCanParam.uiTxEndFlg = 0U;

    if(1U == stSpi.uiFlgReadCmpl)
    {
        stComLoc.uiFrameFltDataRead++;

        if(stComLoc.uiFrameFltDataRead > FRAME_FLT_DATA_READ_TOTAL)
        {
            stComLoc.uiFrameFltDataRead = 0U;       ///< Clear read count
            stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
            stComLoc.stPrmExt.uiFlgReadReq = 0U;    ///< Reset read request flag
        }
        else
        {
            stComLoc.stCanParam.uiTxWord[0] = stComLoc.uiFrameFltDataRead;    ///< The current frame number
            v_Com_Tx_Tsk_FltDataRec_SndData();    ///< Send Operation data according to the frame number

            /* Collect Data */
            stCom.uiByteTx[0] =  (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;    ///< High
            stCom.uiByteTx[1] =  stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;           ///< Low
            stCom.uiByteTx[2] =  (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;    ///< High
            stCom.uiByteTx[3] =  stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;           ///< Low
            stCom.uiByteTx[4] =  (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;    ///< High
            stCom.uiByteTx[5] =  stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;           ///< Low
            stCom.uiByteTx[6] =  (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;    ///< High
            stCom.uiByteTx[7] =  stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;           ///< Low

            /* Configure Transmit email Flag*/
            stComLoc.stPrmExt.uiFlgTxMsg = 1U;
        }
    }
    else
    {
        stCom.uiByteTx[0] = stComDrv.uiByteRx[0];    ///< The received data is returned directly
        stCom.uiByteTx[1] = stComDrv.uiByteRx[1];
        stCom.uiByteTx[2] = stComDrv.uiByteRx[2];
        stCom.uiByteTx[3] = stComDrv.uiByteRx[3];
        stCom.uiByteTx[4] = stComDrv.uiByteRx[4];
        stCom.uiByteTx[5] = stComDrv.uiByteRx[5];
        stCom.uiByteTx[6] = stComDrv.uiByteRx[6];
        stCom.uiByteTx[7] = stComDrv.uiByteRx[7];

        /* Configure Transmit email Flag*/
        stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    }

/* Output Signal*/
#if (1U == COM_DBG)
    stCom.uiFlgReadReq = stComDbg.uiFlgReadReq;
#else
    stCom.uiFlgReadReq = stComLoc.stPrmExt.uiFlgReadReq;
#endif
}

/**
* @brief   Fault data read Send data task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_FltDataRec_SndData(void)
{
    Uint16 i, j = 0U;
    Uint16 l_uiIdx = 0U;
    Uint16 l_uiFrameStrt = 0U;
    Uint16 l_uiFrameFltDataRead = 0U;

    l_uiFrameFltDataRead = stComLoc.uiFrameFltDataRead - 1U;
    if(0U == l_uiFrameFltDataRead)
    {
        /* Time data */
        for(i = 0U; i < SIZE_TI_DATA; i++) 
        {
            stComLoc.uiBufFltData[l_uiIdx++] = (Uint16)((stSpi.stFltDataRead.ullTime.all >> (48U-16U * i)) & 0xFFFFU);
        }

        /* Power parameter data */
        for(i = 0U; i < SIZE_POW_PRM_TYP_FLT_REC; i++)
        {
            for(j = 0U; j < SIZE_POW_PRM_NUM_FLT_REC; j++)
            {
                stComLoc.uiBufFltData[l_uiIdx++] = stSpi.stFltDataRead.uiPrmPow[i][j];
            }
        }

        /* Temperature data */
        for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
        {
            stComLoc.uiBufFltData[l_uiIdx++] = (Uint16)stSpi.stFltDataRead.siTemp[i];
        }

        /* Fault word data */
        for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
        {
            stComLoc.uiBufFltData[l_uiIdx++] = stSpi.stFltDataRead.uiWordFlt[i];
        }
    }

    /* Collect data */
    l_uiFrameStrt = l_uiFrameFltDataRead * SIZE_PER_FRAME; ///< Calculate the start index of the frame
#if 0U == NUM_REM_FLT_DATA_READ
    for(i = 0U; i < SIZE_PER_FRAME; i++)
    {
        stComLoc.stCanParam.uiTxWord[i+1U] = stComLoc.uiBufFltData[l_uiFrameStrt + i];  
    }
#else
    if(stComLoc.uiFrameFltDataRead < FRAME_FLT_DATA_READ_TOTAL)
    {
        for(i = 0U; i < SIZE_PER_FRAME; i++)
        {
            stComLoc.stCanParam.uiTxWord[i+1U] = stComLoc.uiBufFltData[l_uiFrameStrt + i];
        }
    }
    else
    {
        for(i = 0U; i < NUM_REM_FLT_DATA_READ; i++)
        {
            stComLoc.stCanParam.uiTxWord[i+1U] = stComLoc.uiBufFltData[l_uiFrameStrt + i];
        }

        for(i = NUM_REM_FLT_DATA_READ; i < SIZE_PER_FRAME; i++)
        {
            stComLoc.stCanParam.uiTxWord[i+1U] = 0U;
        }
    }
#endif
}
#endif

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_TblVers(void)
{
#if 1U == GRID_PHASE_NUMBER
    stComLoc.stCanParam.uiTxWord[0] = (Uint16)TYPE_IEC7K4W;    ///< Version
#elif 2U == GRID_PHASE_NUMBER
    stComLoc.stCanParam.uiTxWord[0] = (Uint16)TYPE_UL19K2W;    ///< Version
#else
    stComLoc.stCanParam.uiTxWord[0] = (Uint16)TYPE_IEC11KW;    ///< Version
#endif
    stComLoc.stCanParam.uiTxWord[1] = PARAM_VER;               ///< Parameter Version
    stComLoc.stCanParam.uiTxWord[2] = 1U;
    stComLoc.stCanParam.uiTxWord[3] = 0U;

    /* Collect Data */
    stCom.uiByteTx[1] =  stComLoc.stCanParam.uiTxWord[0] & 0x00FFU;           ///< Low
    stCom.uiByteTx[0] =  (stComLoc.stCanParam.uiTxWord[0] >> 8) & 0x00FFU;    ///< High
    stCom.uiByteTx[3] =  stComLoc.stCanParam.uiTxWord[1] & 0x00FFU;           ///< Low
    stCom.uiByteTx[2] =  (stComLoc.stCanParam.uiTxWord[1] >> 8) & 0x00FFU;    ///< High
    stCom.uiByteTx[5] =  stComLoc.stCanParam.uiTxWord[2] & 0x00FFU;           ///< Low
    stCom.uiByteTx[4] =  (stComLoc.stCanParam.uiTxWord[2] >> 8) & 0x00FFU;    ///< High
    stCom.uiByteTx[7] =  stComLoc.stCanParam.uiTxWord[3] & 0x00FFU;           ///< Low
    stCom.uiByteTx[6] =  (stComLoc.stCanParam.uiTxWord[3] >> 8) & 0x00FFU;    ///< High

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

#if 2U == GRID_PHASE_NUMBER
/**
* @brief   CPLD upgrade Notice Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_CpldUpd_Notice(void)
{
    stCom.uiByteTx[1] = 0x1U;                                    ///< Low Jump successful
    stCom.uiByteTx[0] = 0x1U;                                    ///< High have programs
    stCom.uiByteTx[3] = 0x0U;                                    ///< Low
    stCom.uiByteTx[2] = 0x0U;                                    ///< High
    stCom.uiByteTx[5] = 0x0U;                                    ///< Low
    stCom.uiByteTx[4] = 0x0U;                                    ///< High
    stCom.uiByteTx[7] = 0x0U;                                    ///< Low
    stCom.uiByteTx[6] = 0x0U;                                    ///< High
    stComLoc.stCpldBoot.uiFlgEraseOK = 0U;                       ///< Flag

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg   = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

/**
* @brief   CPLD upgrade Erase Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_CpldUpd_Erase(void)
{
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0
    Uint16 l_uiDataRxTmp1 = 0U;    ///< Temporary Data1

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8U | stComDrv.uiByteRx[1]);
    l_uiDataRxTmp1 = (stComDrv.uiByteRx[2] << 8U | stComDrv.uiByteRx[3]);
    stComLoc.stCpldBoot.ulCodLen = (((Uint32)l_uiDataRxTmp0)<<16) + l_uiDataRxTmp1;
    stComLoc.stCpldBoot.ulSumNumFrm  = stComLoc.stCpldBoot.ulCodLen>>7U;

    if(0U == stComLoc.stCpldBoot.uiFlgEraseOK)
    {
       /* Erase Primary bit stream */
       v_SpiDrv_Cmn_EraseBlock(BLOCK1_FRIST_ADDR, &SPIC_REG);                 ///< Erase 0 Block
       v_SpiDrv_Cmn_EraseBlock(BLOCK2_FRIST_ADDR, &SPIC_REG);                 ///< Erase 1 Block
       v_SpiDrv_Cmn_EraseBlock(BLOCK3_FRIST_ADDR, &SPIC_REG);                 ///< Erase 2 Block
       v_SpiDrv_Cmn_EraseBlock(BLOCK4_FRIST_ADDR, &SPIC_REG);                 ///< Erase 3 Block

       stComLoc.stCpldBoot.uiFlgWrFlt = 0U;
       stComLoc.stCpldBoot.uiFlgEraseOK = 1U;
    }
    /* Return data*/
    stCom.uiByteTx[1] = stComDrv.uiByteRx[1];                      ///< Low
    stCom.uiByteTx[0] = stComDrv.uiByteRx[0];                      ///< High
    stCom.uiByteTx[3] = stComDrv.uiByteRx[3];                      ///< Low
    stCom.uiByteTx[2] = stComDrv.uiByteRx[2];                      ///< High
    stCom.uiByteTx[5] = 0x0U;                                      ///< Low
    stCom.uiByteTx[4] = 0x0U;                                      ///< High
    stCom.uiByteTx[7] = 0x0U;                                      ///< Low
    stCom.uiByteTx[6] = 0x0U;                                      ///< High

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg   = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

/**
* @brief   CPLD upgrade RX Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_CpldUpd_Rx(void)
{
    Uint16 i = 0U;
    Uint16 l_uiDataTmp    = 0U;    ///< Temporary Data
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8 | stComDrv.uiByteRx[1]);
    stComLoc.stCpldBoot.uiSubNumFrm = ((l_uiDataRxTmp0)&0x001FU);             ///< Sub Num of Frame
    l_uiDataTmp = (l_uiDataRxTmp0>>5U);                                       ///< Current Num of Frame
    stComLoc.stCpldBoot.ulCurrNumFrm = (Uint32)l_uiDataTmp;                   ///< Current Num of Frame
    stComLoc.stCpldBoot.ulCpldFlashAddr = FLASH_CPLD_START_ADDRESS + ((stComLoc.stCpldBoot.ulCurrNumFrm - 1U)<<7U);        ///< 128 * 8bit a frame

    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U)] = stComDrv.uiByteRx[2];
    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U) + 1U] = stComDrv.uiByteRx[3];
    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U) + 2U] = stComDrv.uiByteRx[4];
    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U) + 3U] = stComDrv.uiByteRx[5];
    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U) + 4U] = stComDrv.uiByteRx[6];
    stComLoc.stCpldBoot.uiFrmWordWrBuf[6U * (stComLoc.stCpldBoot.uiSubNumFrm -1U) + 5U] = stComDrv.uiByteRx[7];

    if((NUM_SUB_FRM_WR_EN == stComLoc.stCpldBoot.uiSubNumFrm) && (0U == stComLoc.stCpldBoot.uiFlgWrFlt))
    {
        v_SpiDrv_WrBuf(stComLoc.stCpldBoot.uiFrmWordWrBuf, stComLoc.stCpldBoot.ulCpldFlashAddr, SIZE_WR_FRM_CPLDUPD, &SPIC_REG);
        v_SpiDrv_ReadBuf(stComLoc.stCpldBoot.uiFrmWordRdBuf, stComLoc.stCpldBoot.ulCpldFlashAddr, SIZE_WR_FRM_CPLDUPD, &SPIC_REG);

        for(i = 0U; i < SIZE_WR_FRM_CPLDUPD; i++)
         {
            if(stComLoc.stCpldBoot.uiFrmWordWrBuf[i] != stComLoc.stCpldBoot.uiFrmWordRdBuf[i])
            {
                stComLoc.stCpldBoot.uiFlgWrFlt = 1U;
            }
        }
    }
    else
    {
        ///< No code
    }
    /* Return data */
    stCom.uiByteTx[1] = stComDrv.uiByteRx[1];                                 ///< Low
    stCom.uiByteTx[0] = stComDrv.uiByteRx[0];                                 ///< High
    stCom.uiByteTx[3] = stComDrv.uiByteRx[3];                                 ///< Low
    stCom.uiByteTx[2] = stComDrv.uiByteRx[2];                                 ///< High
    stCom.uiByteTx[5] = stComDrv.uiByteRx[5];                                 ///< Low
    stCom.uiByteTx[4] = stComDrv.uiByteRx[4];                                 ///< High
    stCom.uiByteTx[7] = stComDrv.uiByteRx[7];                                 ///< Low
    stCom.uiByteTx[6] = stComDrv.uiByteRx[6];                                 ///< High

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

/**
* @brief   CPLD upgrade Check Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_CpldUpd_Chk(void)
{
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8U | stComDrv.uiByteRx[1]);
    stComLoc.stCpldBoot.uiSubNumFrm = l_uiDataRxTmp0;                         ///< Sub Num of Frame
    if(3U == stComLoc.stCpldBoot.uiSubNumFrm)                                 ///< After the transmission of the verification frame,  begins verification
    {
     if(1U == stComLoc.stCpldBoot.uiFlgWrFlt)
     {
         stComLoc.stCpldBoot.uiFlgChk = UPGRADE_FAIL;                      ///< Check wrong
     }
     else
     {
         stComLoc.stCpldBoot.uiFlgChk = UPGRADE_SUCCESS;                   ///< Check right
         CPLD_REBOOT_ON;                                                   ///< Reboot load Primary bit stream
         DELAY_US_APP(200.0f);
         CPLD_REBOOT_OFF;                                                  ///< default high
     }

     stCom.uiByteTx[1] = stComLoc.stCpldBoot.uiFlgChk & 0x00FFU;           ///< Low
     stCom.uiByteTx[0] = (stComLoc.stCpldBoot.uiFlgChk >> 8U) & 0x00FFU;   ///< High
     stCom.uiByteTx[3] = 0x0U;                                             ///< Low
     stCom.uiByteTx[2] = 0x0U;                                             ///< High
     stCom.uiByteTx[5] = 0x0U;                                             ///< Low
     stCom.uiByteTx[4] = 0x0U;                                             ///< High
     stCom.uiByteTx[7] = 0x0U;                                             ///< Low
     stCom.uiByteTx[6] = 0x0U;                                             ///< High
    }
    else
    {
     ///< No code
    }

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

/**
* @brief   CPLD upgrade Stop Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_CpldUpd_Stop(void)
{
    Uint16 l_uiDataRxTmp0 = 0U;    ///< Temporary Data0

    l_uiDataRxTmp0 = (stComDrv.uiByteRx[0] << 8U | stComDrv.uiByteRx[1]);
    if(STOP_UPGRADE_CMD == l_uiDataRxTmp0)
    {
        stComLoc.stCpldBoot.uiFlgChk = STOP_SUCCESS;                          ///<  Stop upgrade suceess
    }
    else
    {
        stComLoc.stCpldBoot.uiFlgChk = STOP_FAIL;                             ///<  Stop upgrade fail
    }

    /* Return data */
    stCom.uiByteTx[1] = stComLoc.stCpldBoot.uiFlgChk & 0x00FFU;               ///< Low
    stCom.uiByteTx[0] = (stComLoc.stCpldBoot.uiFlgChk >> 8U) & 0x00FFU;       ///< High
    stCom.uiByteTx[3] = 0x0U;                                                 ///< Low
    stCom.uiByteTx[2] = 0x0U;                                                 ///< High
    stCom.uiByteTx[5] = 0x0U;                                                 ///< Low
    stCom.uiByteTx[4] = 0x0U;                                                 ///< High
    stCom.uiByteTx[7] = 0x0U;                                                 ///< Low
    stCom.uiByteTx[6] = 0x0U;                                                 ///< High
    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg   = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg   = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}
#endif

/**
* @brief   CAN Data Transmit Task
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_Com_Tx_Tsk_Dft(void)
{
    stCom.uiByteTx[0] = stComDrv.uiByteRx[0];    ///< The received data is returned directly
    stCom.uiByteTx[1] = stComDrv.uiByteRx[1];
    stCom.uiByteTx[2] = stComDrv.uiByteRx[2];
    stCom.uiByteTx[3] = stComDrv.uiByteRx[3];
    stCom.uiByteTx[4] = stComDrv.uiByteRx[4];
    stCom.uiByteTx[5] = stComDrv.uiByteRx[5];
    stCom.uiByteTx[6] = stComDrv.uiByteRx[6];
    stCom.uiByteTx[7] = stComDrv.uiByteRx[7];

    /* Configure Transmit email Flag*/
    stComLoc.stPrmExt.uiFlgTxMsg = 1U;
    stComLoc.stCanParam.uiTxEndFlg = 1U;    ///< The current frame data transfer is complete
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Communication EEPROM related parameter update
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Com_EepPrmUpd(void)
{
    stComLoc.stPrmExt.uiStdGridSet = stCom.uiStdGridSet;
    stComLoc.stPrmExt.uiTypeGrid   = stCom.uiTypeGrid;

    /* Rated AC current update */
    if(stComTbl.stPrmPfcRtd1.ftVoltGrid > 1.0f)
    {
        stComTbl.stRtdPrm.ftCurrAcRmsRtd = COEFF_AC_CURR_CALC * (stComTbl.stPrmPfcRtd1.ftPowRtd * ONE_PHASE_COEFF / stComTbl.stPrmPfcRtd1.ftVoltGrid);
    }
    UP_LIMIT(stComTbl.stRtdPrm.ftCurrAcRmsRtd, RATED_AC_CURR_RMS);
    UP_LIMIT(stComTbl.stRtdPrm.ftCurrAcRmsRtd, stCom.ftCurrAcRmsLim);
    /* Rated active power & reactive power update */
    vFcn_FtUpDwnLim(&stComTbl.stPrmPfcRtd1.ftPFMin, 1.0f, AC_PF_MIN);
    stComLoc.ftCoeffReactv      = sqrtf(1.0f - stComTbl.stPrmPfcRtd1.ftPFMin * stComTbl.stPrmPfcRtd1.ftPFMin);    ///< Reactive power coefficient
    stComLoc.stPrmExt.ftQAcMax  = stComLoc.ftCoeffReactv * stComTbl.stPrmPfcRtd1.ftPowRtd;                        ///< Max AC reactive power
    stComLoc.stPrmExt.ftIdAcRtd = CON_SQRT_2 * stComTbl.stRtdPrm.ftCurrAcRmsRtd;                                  ///< Rated AC active current amplitude
    stComLoc.stPrmExt.ftIqAcRtd = CON_SQRT_2 * stComLoc.ftCoeffReactv * stComTbl.stRtdPrm.ftCurrAcRmsRtd + CURR_LMT_X_CAP_COMP;         ///< Rated AC reactive current amplitude
    stComLoc.stPrmExt.ftQOnePhaMax = stComLoc.stPrmExt.ftQAcMax * ONE_PHASE_COEFF;                                ///< One phase Max reactive power
    stComLoc.stPrmExt.ftPowBattMax = stComTbl.stPrmPfcRtd1.ftPowBattChrgRtd + 100.0f;                             ///< Max battery power
    stComTbl.stRtdPrm.ftCurrBattParlMax = stComLoc.stPrmExt.ftPowBattMax / VOLT_BATT_PARL_RTD;                    ///< Max parallel output current

    /* V2L voltage and frequency request update */
    stComLoc.stPrmExt.ftVoltAcV2LReq = stComTbl.stPrmPfcRtd1.ftVoltGrid;                                          ///< V2L voltage request
    stComLoc.stPrmExt.ftFrqAcV2LReq  = stComTbl.stPrmPfcRtd1.ftFrqGrid;                                           ///< V2L frequency request

    /* Output Signal*/
#if (1U == COM_DBG)
    stCom.ftPowBattMax           = stComDbg.ftPowBattMax;
    stCom.ftQAcMax               = stComDbg.ftQAcMax;
    stCom.ftQOnePhaMax           = stComDbg.ftQOnePhaMax;
    stCom.ftIdAcRtd              = stComDbg.ftIdAcRtd;
    stCom.ftIqAcRtd              = stComDbg.ftIqAcRtd;
    stCom.ftVoltAcV2LReq         = stComDbg.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq          = stComDbg.ftFrqAcV2LReq;
#else
    stCom.ftPowBattMax           = stComLoc.stPrmExt.ftPowBattMax;
    stCom.ftQAcMax               = stComLoc.stPrmExt.ftQAcMax;
    stCom.ftQOnePhaMax           = stComLoc.stPrmExt.ftQOnePhaMax;
    stCom.ftIdAcRtd              = stComLoc.stPrmExt.ftIdAcRtd;
    stCom.ftIqAcRtd              = stComLoc.stPrmExt.ftIqAcRtd;
    stCom.ftVoltAcV2LReq         = stComLoc.stPrmExt.ftVoltAcV2LReq;
    stCom.ftFrqAcV2LReq          = stComLoc.stPrmExt.ftFrqAcV2LReq;
#endif

    /* SP relay parameter update */
    if(SP_RLY_PARL_ST == stPerphCtrl.stSPRly.uiSt)    ///< Parallel status
    {
        v_Com_ParlPrmUpd();
    }
    else    ///< Series status
    {
        v_Com_SeriesPrmUpd();
    }

    /* PFC data calculate EEPROM parameter update */
    v_PfcDataCalc_PrmUpd_Eep();

    /* System parameter CBC value update Eeprom task */
    v_CmpssCfg_PrmUpd_Eep();

    /* PFC grid control EEPROM parameter update */
    v_PfcGridCtrl_PrmUpd_Eep();

    /* D2D power pre-control EEPROM parameter update */
#if(3U == GRID_PHASE_NUMBER)
    v_D2dPowPreCtrl_FrqJitPrmUpd();
#endif

    /* PFC power control EEPROM parameter update */
    v_PfcPowCtrl_PrmUpd_Eep();

    /* Power limit EEPROM parameter update */
    v_PowLim_PrmUpd_Eep();

#if 1U == FLG_ON_OFF_GRID_SWT_EN
    /* On&off grid switch parameter update */
    v_OnOffGridSwt_PrmUpd_Eep();
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Communication parallel state related parameter update
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_Com_ParlPrmUpd(void)
{
    stComLoc.stPrmExt.ftCurrBattMaxChrg  = stComTbl.stRtdPrm.ftCurrBattParlMax;
    stComLoc.stPrmExt.ftCurrBattMaxBidir = CURR_BATT_PARL_MAX * EFF_RECPR_PL_DCHA;

#if (1U == COM_DBG)
    stCom.ftCurrBattMaxChrg  = stComDbg.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir = stComDbg.ftCurrBattMaxBidir;
#else
    stCom.ftCurrBattMaxChrg  = stComLoc.stPrmExt.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir = stComLoc.stPrmExt.ftCurrBattMaxBidir;
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Communication series state related parameter update
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_Com_SeriesPrmUpd(void)
{
    stComLoc.stPrmExt.ftCurrBattMaxChrg  = stComTbl.stRtdPrm.ftCurrBattParlMax * 0.5f;
    stComLoc.stPrmExt.ftCurrBattMaxBidir = CURR_BATT_SERIES_MAX * EFF_RECPR_PL_DCHA;

#if (1U == COM_DBG)
    stCom.ftCurrBattMaxChrg  = stComDbg.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir = stComDbg.ftCurrBattMaxBidir;
#else
    stCom.ftCurrBattMaxChrg  = stComLoc.stPrmExt.ftCurrBattMaxChrg;
    stCom.ftCurrBattMaxBidir = stComLoc.stPrmExt.ftCurrBattMaxBidir;
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
