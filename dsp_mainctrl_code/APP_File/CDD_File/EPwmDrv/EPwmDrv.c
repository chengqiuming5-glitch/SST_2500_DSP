//==============================================================================================
//    File description
//==============================================================================================
/**@file         EPwmDrv.c
 * @brief
 * Source file of EPwm drive.
 *
 * Module      :                       \n
 * EPwmDrv
 *
 * Module Task :                       \n
 * v_EPwmDrv_Init()                    \n
 * v_EPwmDrv_Isr()                     \n
 * v_EPwmDrv_1ms()                     \n
 * v_EPwmDrv_Pfc_TurnOff()             \n
 * v_EPwmDrv_Pfc_ClrTzFlg()            \n
 * v_EPwmDrv_D2d_TurnOff()             \n
 * v_EPwmDrv_D2d_ClrTzFlg()            \n
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
#include "EPwmDrv.h"
#include "F2837xD_Examples.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_EPWM_DRV stEPwmDrv;                  ///< EPwm drive global struct

#if (1U == EPWM_DRV_DBG)
ST_EPWM_DRV stEPwmDrvDbg;               ///< EPwm drive debug global struct
#endif
#if(1U == FLG_SWUT_EN)
struct ECAP_REGS ECap6RegsUnitTest;
struct EPWM_REGS EPwm5RegsUnitTest;
struct EPWM_REGS EPwm12RegsUnitTest;
#endif
//static ST_EPWM_DRV_LOC stEPwmDrvLoc;    ///< ADC drive local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        EPwm drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_EPwmDrv_Init(void)
{
#ifndef SST_1250kW
    stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm    = PERIOD_PFC_PWM;
    stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone = 0U;        ///< Initialize to 0U
    stEPwmDrvLoc.uiCntrCmp               = 0U;        ///< Initialize to 0U
    stEPwmDrvLoc.uiDirModln              = 0U;        ///< Initialize to 0U
    stEPwmDrvLoc.uiCntrDriveEn           = 0U;        ///< Initialize to 0U
	stEPwmDrvLoc.uiCntrBalEn             = 0U;		  ///< Initialize to 0U
	stEPwmDrvLoc.uiPrdMaxFast            = PERIOD_PFC_PWM;
	stEPwmDrvLoc.uiPrdMinFast            = PERIOD_PFC_PWM;

    /* Global Signal*/
#if (1U == EPWM_DRV_DBG)
    stEPwmDrvDbg.uiFlgClrTzDone = stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone;
    stEPwmDrvDbg.uiPrdPfcPwm    = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;

    stEPwmDrv.uiFlgClrTzDone    = stEPwmDrvDbg.uiFlgClrTzDone;
    stEPwmDrv.uiPrdPfcPwm       = stEPwmDrvDbg.uiPrdPfcPwm;
#else
    stEPwmDrv.uiFlgClrTzDone    = stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone;
    stEPwmDrv.uiPrdPfcPwm       = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
#endif
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_EPwmDrv_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        EPwm drive task in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#ifndef SST_1250kW
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Isr, ".TI.ramfunc");
#endif
void v_EPwmDrv_Isr(void)
{
    v_EPwmDrv_Pfc_Isr();    ///< PFC EPwm drive task in ISR
    v_EPwmDrv_D2d_Isr();    ///< D2D EPwm drive task in ISR

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr) 
    {
        printf("****SWIT DynamicTest: function v_EPwmDrv_Isr() is running****\r\n");
    }
#endif
}
#endif
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        EPwm drive 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_EPwmDrv_1ms(void)
{
#ifndef SST_1250kW
    if(D2D_ST_MAC_PWMENPRE == stD2dStMac.uiStD2dRun)
    {
        if(0U == stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone)
        {
            v_EPwmDrv_D2d_ClrTzFlg();    ///< Clear EPWM D2D TZ Flag
#if(3U == GRID_PHASE_NUMBER)
    #ifndef _SIMULATION_NO_DSP_
            EALLOW;
            Cla1Regs.MIFRC.bit.INT2 = 1U;        ///< Software trigger Cla_Task2
            EDIS;
    #else
            v_D2dPowCtrl_Cla1Tsk2();
    #endif
#endif
            stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone = 1U;
        }
    }
    else
    {
        stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone = 0U;
    }

#if(1U == GRID_PHASE_NUMBER)
    v_EPwmDrv_PfcFrqJit_1ms();
#endif

    /* Global Signal*/
#if (1U == EPWM_DRV_DBG)
    stEPwmDrv.uiFlgClrTzDone    = stEPwmDrvDbg.uiFlgClrTzDone;
    stEPwmDrv.uiPrdPfcPwm       = stEPwmDrvDbg.uiPrdPfcPwm;
#else
    stEPwmDrv.uiFlgClrTzDone    = stEPwmDrvLoc.stPrmExt.uiFlgClrTzDone;
    stEPwmDrv.uiPrdPfcPwm       = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_EPwmDrv_1ms() is running****\r\n");
    }
#endif
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        EPwm drive 1ms task- PFC frequency jitter
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(1U == GRID_PHASE_NUMBER)
static void v_EPwmDrv_PfcFrqJit_1ms(void)
{
    Uint16  l_uiPrdMax            = 0U;
    Uint16  l_uiPrdMin            = 0U;
    Uint32  l_ulFrq               = 0UL;
    float32 l_ftFrq               = 0.0f;
    static Uint16 sl_uiDirFrqJit  = 0U;
    static Uint16 sl_uiPrdPre     = PERIOD_PFC_PWM;
    static Uint16 sl_uiCntr       = 0U;

    if(PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        if((NRS_097 != stCom.uiStdGridSet) || (FCN_DISABLE == stComTbl.stPrmPfcPowCtrl.uiEnaFrqJit))
        {
            l_uiPrdMax = stPfcDataCalc.stSysParm.uiPerdPwmABC;
            l_uiPrdMin = stPfcDataCalc.stSysParm.uiPerdPwmABC;
        }
        else
        {
            l_uiPrdMax = stEPwmDrvLoc.uiPrdMaxFast;
            l_uiPrdMin = stEPwmDrvLoc.uiPrdMinFast;
        }

        if(sl_uiCntr++ >= PERD_FRQ_JIT)
        {
            sl_uiCntr = 0U;
            if(0U == sl_uiDirFrqJit)
            {
                ///< Frequency increase
                stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm += 1U;
            }
            else
            {
                ///< Frequency decrease
                stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm -= 1U;
            }
        }

        if(stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm > l_uiPrdMax)
        {
            stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm = l_uiPrdMax;
            sl_uiDirFrqJit = 1U;
        }
        else if(stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm < l_uiPrdMin)
        {
            stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm = l_uiPrdMin;
            sl_uiDirFrqJit = 0U;
        }
        else
        {
            ///< Do nothing
        }

        /* PFC fast bridge ePWM module update */
        if(sl_uiPrdPre != stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm)
        {
            PFC_FAST_PWM.TBPRD = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
        }

        sl_uiPrdPre = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
    }
    else
    {
        sl_uiCntr = 0U;
        l_ftFrq = (float32)stComTbl.stPrmPfcHw.uiSwtFrqIabc + (float32)stComTbl.stPrmPfcPowCtrl.uiFrqJitRng;
        UP_LIMIT(l_ftFrq, (float32)FRQ_PFC_SWITCH_MAX);
        l_ulFrq = (Uint32)l_ftFrq;
        stEPwmDrvLoc.uiPrdMinFast = (Uint16)((FRQ_PWMCLK / l_ulFrq) >> 1);
        l_ftFrq = (float32)stComTbl.stPrmPfcHw.uiSwtFrqIabc - (float32)stComTbl.stPrmPfcPowCtrl.uiFrqJitRng;
        DOWN_LIMIT(l_ftFrq, (float32)FRQ_PFC_SWITCH_MIN);
        l_ulFrq = (Uint32)l_ftFrq;
        stEPwmDrvLoc.uiPrdMaxFast = (Uint16)((FRQ_PWMCLK / l_ulFrq) >> 1);

        stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm = stPfcDataCalc.stSysParm.uiPerdPwmABC;
        /* PFC fast bridge ePWM module update */
        if(sl_uiPrdPre != stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm)
        {
            PFC_FAST_PWM.TBPRD = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
        }
        sl_uiPrdPre = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm;
    }
}
#endif
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC EPwm drive task in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Pfc_Isr, ".TI.ramfunc");
#endif
static void v_EPwmDrv_Pfc_Isr(void)
{
#ifndef SST_1250kW
#if 1U == FLG_PFC_POWCTRL_EN
#if(1U == GRID_PHASE_NUMBER)
    if(stPfcPowCtrl.siOutpPwmModln <= -8)
    {
        stEPwmDrvLoc.uiCntrCmp  = (Uint16)(-stPfcPowCtrl.siOutpPwmModln);
        stEPwmDrvLoc.uiDirModln = 1U;        ///< Set negative direction
    }
    else if(stPfcPowCtrl.siOutpPwmModln < 8)
    {
    #if 1U
        stEPwmDrvLoc.uiCntrCmp = 8U;
    #else
        if(0U == stEPwmDrvLoc.uiDirModln)    ///< Positive direction
        {
            if(stPfcPowCtrl.siOutpPwmModln >= 0)
            {
                stEPwmDrvLoc.uiCntrCmp  = (Uint16)stPfcPowCtrl.siOutpPwmModln;
            }
            else
            {
                stEPwmDrvLoc.uiCntrCmp  = 0U;
            }
        }
        else    ///< Negative direction
        {
            if(stPfcPowCtrl.siOutpPwmModln < 0)
            {
                stEPwmDrvLoc.uiCntrCmp  = (Uint16)(-stPfcPowCtrl.siOutpPwmModln);
            }
            else
            {
                stEPwmDrvLoc.uiCntrCmp  = 0U;
            }
        }

    #endif
    }
    else
    {
        stEPwmDrvLoc.uiCntrCmp  = (Uint16)stPfcPowCtrl.siOutpPwmModln;
        stEPwmDrvLoc.uiDirModln = 0U;        ///< Set positive direction
    }

    if(0U == stEPwmDrvLoc.uiDirModln)        ///< Positive direction
    {
        PFC_FAST_PWM.CMPA.bit.CMPA  = stEPwmDrvLoc.stPrmExt.uiPrdPfcPwm - stEPwmDrvLoc.uiCntrCmp;
        PFC_SLOW_PWM.AQCTLA.bit.CAU = AQ_CLEAR;
		PFC_SLOW_PWM.AQCTLA.bit.CBU = AQ_CLEAR;
        PFC_SLOW_PWM.AQCTLA.bit.CAD = AQ_SET;    ///< To be deleted
    }
    else                                    ///< Negative direction
    {
        PFC_FAST_PWM.CMPA.bit.CMPA  = stEPwmDrvLoc.uiCntrCmp;
        PFC_SLOW_PWM.AQCTLA.bit.CAU = AQ_SET;
		PFC_SLOW_PWM.AQCTLA.bit.CBU = AQ_SET;
        PFC_SLOW_PWM.AQCTLA.bit.CAD = AQ_CLEAR;   ///< To be deleted
    }
#elif(2U == GRID_PHASE_NUMBER)
    Uint16 l_uiCmpA1 = 0U;
    Uint16 l_uiCmpA2 = 0U;
    Uint16 l_uiCmpB1 = 0U;
    Uint16 l_uiCmpB2 = 0U;
    float32 l_ftBalCompReg = 0.0f;
    float32 l_ftCmpTmp = 0.0f;
	
    l_ftCmpTmp = (ftFcn_MaxOfTwo(stPfcPowCtrl.ftOutpPwmModlnA, 0.0f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC);
    l_uiCmpA1  = (Uint16)l_ftCmpTmp;
    l_ftCmpTmp = ((ftFcn_MinOfTwo(stPfcPowCtrl.ftOutpPwmModlnA, 0.0f) + 1.0f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC);
    l_uiCmpA2  = (Uint16)l_ftCmpTmp;
    l_ftCmpTmp = (ftFcn_MaxOfTwo(stPfcPowCtrl.ftOutpPwmModlnB, 0.0f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC);
    l_uiCmpB1  = (Uint16)l_ftCmpTmp;
    l_ftCmpTmp = ((ftFcn_MinOfTwo(stPfcPowCtrl.ftOutpPwmModlnB, 0.0f) + 1.0f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC);
    l_uiCmpB2  = (Uint16)l_ftCmpTmp;

///<    PWM_BAL_COMP_REG         = (Uint16)((stPfcPowCtrl.ftOutpPwmModlnN + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmN);
    l_ftBalCompReg    = ((stPfcPowCtrl.ftOutpPwmModlnN + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmN);
    PWM_BAL_COMP_REG  = (Uint32)l_ftBalCompReg;
    PWM_L1A1_REG.CMPA.bit.CMPA = l_uiCmpA1;               ///<    L1
    PWM_L1A2_REG.CMPA.bit.CMPA = l_uiCmpA2;
    PWM_L2A1_REG.CMPA.bit.CMPA = l_uiCmpB1;               ///<    L2
    PWM_L2A2_REG.CMPA.bit.CMPA = l_uiCmpB2;

    PWM_L1B1_REG.CMPA.bit.CMPA = stPfcDataCalc.stSysParm.uiPerdPwmABC - l_uiCmpA1;
    PWM_L1B2_REG.CMPA.bit.CMPA = stPfcDataCalc.stSysParm.uiPerdPwmABC - l_uiCmpA2;
    PWM_L2B1_REG.CMPA.bit.CMPA = stPfcDataCalc.stSysParm.uiPerdPwmABC - l_uiCmpB1;
    PWM_L2B2_REG.CMPA.bit.CMPA = stPfcDataCalc.stSysParm.uiPerdPwmABC - l_uiCmpB2;
#elif(3U == GRID_PHASE_NUMBER)
    float32 l_ftCmpTmp = 0.0f;

    if((PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss) && (OFFGRID_MODE != stComIf.uiModPfcRun))
    {
        if(TYPE_GRID_AN == stCom.uiTypeGrid)
        {
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnA + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_A_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare A value
        }
        else if(TYPE_GRID_BN == stCom.uiTypeGrid)
        {
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnB + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_B_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare B value
        }
        else
        {
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnC + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_C_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare C value
        }
        l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnN + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmN;
        PWM_N_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;        ///< Set compare N value
    }
    else
    {
        l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnA + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
        PWM_A_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;        ///< Set compare A value
        l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnN + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmN;
        PWM_N_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;        ///< Set compare N value

        if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)
        {
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnB + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_B_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare B value
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnC + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_C_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare C value
        }
        else
        {
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnC + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_B_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare B value
            l_ftCmpTmp = (stPfcPowCtrl.ftOutpPwmModlnB + 0.5f) * (float32)stPfcDataCalc.stSysParm.uiPerdPwmABC;
            PWM_C_REG.CMPA.bit.CMPA = (Uint16)l_ftCmpTmp;    ///< Set compare C value
        }
    }
#endif
    /* PFC PWM enbale/disable */
    if(FCN_ENABLE == stPfcPowCtrl.uiFlgPwmEn)
    {
        v_EPwmDrv_Pfc_PwmEn();           ///<PFC EPwm enable
    }
    else
    {
        v_EPwmDrv_Pfc_PwmDis();          ///<PFC EPwm disable
    }

#if(1U != GRID_PHASE_NUMBER)
    /* Balance bridge PWM enbale/disable */
    if(OPENLOOP_MODE != stComIf.uiModPfcRun)
    {
        if(FCN_ENABLE == stPfcPowCtrl.uiEnaBalBrdgPwm)
        {
            v_EPwmDrv_Bal_PwmEn();           ///<Balance bridge PWM enable function ISR task
        }
        else
        {
            v_EPwmDrv_Bal_PwmDis();         ///<Balance bridge PWM disable function ISR task
        }
    }
#endif
#endif
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D EPwm drive task in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_D2d_Isr, ".TI.ramfunc");
#endif
static void v_EPwmDrv_D2d_Isr(void)
{
#if 1U == FLG_D2D_POWCTRL_EN
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;
    if((stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN) && \
       (0U == stD2dDiag.uiFltCpu) && (0U == stD2dPowCtrlClaToCpu.stFlt.uiFltCla))
    {
        switch(stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dUpEpwm)    ///< D2D Up Bridge EPWM command
        {
            case EPWM_PRI_DIS_SEC_DIS:      ///< Disable Primary EPWM & Disable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_UP_BDG);
                DISABLE_EPWM(EPWM_SEC_UP_BDGL);
                DISABLE_EPWM(EPWM_SEC_UP_BDGR);
                break;

            case EPWM_PRI_EN_SEC_DIS:       ///< Enable Primary EPWM & Disable Secondary EPWM
                ENABLE_EPWM(EPWM_PRI_UP_BDG);
                DISABLE_EPWM(EPWM_SEC_UP_BDGL);
                DISABLE_EPWM(EPWM_SEC_UP_BDGR);
                break;

            case EPWM_PRI_DIS_SEC_EN:       ///< Disable Primary EPWM & Enable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_UP_BDG);
                ENABLE_EPWM(EPWM_SEC_UP_BDGL);
                ENABLE_EPWM(EPWM_SEC_UP_BDGR);
                break;

            default:
                ///< No code
                break;
        }

        switch(stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dDwnEpwm)   ///< Down Bridge
        {
            case EPWM_PRI_DIS_SEC_DIS:      ///< Disable Primary EPWM & Disable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_DN_BDG);
                DISABLE_EPWM(EPWM_SEC_DN_BDGL);
                DISABLE_EPWM(EPWM_SEC_DN_BDGR);
                break;

            case EPWM_PRI_EN_SEC_DIS:       ///< Enable Primary EPWM & Disable Secondary EPWM
                ENABLE_EPWM(EPWM_PRI_DN_BDG);
                DISABLE_EPWM(EPWM_SEC_DN_BDGL);
                DISABLE_EPWM(EPWM_SEC_DN_BDGR);
                break;

            case EPWM_PRI_DIS_SEC_EN:      ///< Disable Primary EPWM & Enable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_DN_BDG);
                ENABLE_EPWM(EPWM_SEC_DN_BDGL);
                ENABLE_EPWM(EPWM_SEC_DN_BDGR);
                break;

            default:
                ///< No code
                break;
        }
    }
    else
    {
        DISABLE_EPWM(EPWM_PRI_UP_BDG);
        DISABLE_EPWM(EPWM_SEC_UP_BDGL);
        DISABLE_EPWM(EPWM_SEC_UP_BDGR);
        DISABLE_EPWM(EPWM_PRI_DN_BDG);
        DISABLE_EPWM(EPWM_SEC_DN_BDGL);
        DISABLE_EPWM(EPWM_SEC_DN_BDGR);
    }
    EDIS;	
#elif(2U == GRID_PHASE_NUMBER)
    EALLOW;
    if((stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN) && \
        (0U == stD2dDiag.uiFltCpu) && (0U == stD2dPowCtrlClaToCpu.stFlt.uiFltCla))
    {
        switch(stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dUpEpwm)    ///< Up Bridge
        {
            case EPWM_PRI_DIS_SEC_DIS:      ///< Disable Primary EPWM & Disable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_UP_BDG);
                DISABLE_EPWM(EPWM_SEC_UP_BDG);
                break;

            case EPWM_PRI_EN_SEC_DIS:       ///< Enable Primary EPWM & Disable Secondary EPWM
                ENABLE_EPWM(EPWM_PRI_UP_BDG);
                DISABLE_EPWM(EPWM_SEC_UP_BDG);
                break;

            case EPWM_PRI_DIS_SEC_EN:       ///< Disable Primary EPWM & Enable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_UP_BDG);
                ENABLE_EPWM(EPWM_SEC_UP_BDG);
                break;

            default:
                ///< No code
                break;
        }

        switch(stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dDwnEpwm)   ///< Down Bridge
        {
            case EPWM_PRI_DIS_SEC_DIS:      ///< Disable Primary EPWM & Disable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_DN_BDG);
                DISABLE_EPWM(EPWM_SEC_DN_BDG);
                break;

            case EPWM_PRI_EN_SEC_DIS:       ///< Enable Primary EPWM & Disable Secondary EPWM
                ENABLE_EPWM(EPWM_PRI_DN_BDG);
                DISABLE_EPWM(EPWM_SEC_DN_BDG);
                break;

            case EPWM_PRI_DIS_SEC_EN:      ///< Disable Primary EPWM & Enable Secondary EPWM
                DISABLE_EPWM(EPWM_PRI_DN_BDG);
                ENABLE_EPWM(EPWM_SEC_DN_BDG);
                break;

            default:
                ///< No code
                break;
        }
    }
    else
    {
        DISABLE_EPWM(EPWM_PRI_UP_BDG);
        DISABLE_EPWM(EPWM_SEC_UP_BDG);
        DISABLE_EPWM(EPWM_PRI_DN_BDG);
        DISABLE_EPWM(EPWM_SEC_DN_BDG);
    }
    EDIS;
#elif(3U == GRID_PHASE_NUMBER)
    #ifndef _SIMULATION_NO_DSP_
    EALLOW;
    if((stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN) && (EPWM_PRI_DIS_SEC_DIS != stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dEpwm) && \
       (0U == stD2dDiag.uiFltCpu) && (0U == stD2dPowCtrlClaToCpu.stFlt.uiFltCla))
    {
        ENABLE_EPWM(EPWM_PRI_BDGL);
        ENABLE_EPWM(EPWM_PRI_BDGR);
        if(EPWM_PRI_EN_SEC_EN == stD2dPowCtrlClaToCpu.stCtrl.uiCmdD2dEpwm)
        {
            ENABLE_EPWM(EPWM_SEC_UP_BDGL);
            ENABLE_EPWM(EPWM_SEC_UP_BDGR);
            ENABLE_EPWM(EPWM_SEC_DN_BDGL);
            ENABLE_EPWM(EPWM_SEC_DN_BDGR);
        }
        else
        {
            DISABLE_EPWM(EPWM_SEC_UP_BDGL);
            DISABLE_EPWM(EPWM_SEC_UP_BDGR);
            DISABLE_EPWM(EPWM_SEC_DN_BDGL);
            DISABLE_EPWM(EPWM_SEC_DN_BDGR);
        }
    }
    else
    {
        DISABLE_EPWM(EPWM_PRI_BDGL);
        DISABLE_EPWM(EPWM_PRI_BDGR);
        DISABLE_EPWM(EPWM_SEC_UP_BDGL);
        DISABLE_EPWM(EPWM_SEC_UP_BDGR);
        DISABLE_EPWM(EPWM_SEC_DN_BDGL);
        DISABLE_EPWM(EPWM_SEC_DN_BDGR);
    }
    EDIS;
    #endif
#endif
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC EPwm drive turn off
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Pfc_TurnOff, ".TI.ramfunc");
#endif
void v_EPwmDrv_Pfc_TurnOff(void)
{
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;
    PFC_FAST_PWM.TZFRC.bit.OST = 1U;    ///< Disable PFC fast MOS drive
    PFC_SLOW_PWM.TZFRC.bit.OST = 1U;    ///< Disable PFC slow MOS drive
    EDIS;
#elif(2U == GRID_PHASE_NUMBER)
    EALLOW;
    /*Force a One-Short Trip via Software*/
    PWM_L1A1_REG.TZFRC.bit.OST = 1;    ///< Disable PFC L1 MOS drive
    PWM_L1A2_REG.TZFRC.bit.OST = 1;
    PWM_L1B1_REG.TZFRC.bit.OST = 1;
    PWM_L1B2_REG.TZFRC.bit.OST = 1;

    PWM_L2A1_REG.TZFRC.bit.OST = 1;    ///< Disable PFC L2 MOS drive
    PWM_L2A2_REG.TZFRC.bit.OST = 1;
    PWM_L2B1_REG.TZFRC.bit.OST = 1;
    PWM_L2B2_REG.TZFRC.bit.OST = 1;
    EDIS;
#elif(3U == GRID_PHASE_NUMBER)
    EALLOW;
    PWM_A_REG.TZFRC.bit.OST = 1U;
    PWM_B_REG.TZFRC.bit.OST = 1U;
    PWM_C_REG.TZFRC.bit.OST = 1U;
    PWM_N_REG.TZFRC.bit.OST = 1U;
    EDIS;
#endif
}
/********************************************End***********************************************/

#if(3U == GRID_PHASE_NUMBER)
/********************************************Begin*********************************************/
/**
 * @brief        Clear PFC TZ Flag
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Pfc_ClrTzFlg, ".TI.ramfunc");
#endif
void v_EPwmDrv_Pfc_ClrTzFlg(void)
{
   if(PFC_TZ_HW_SUM_PWM_REG.TZFLG.bit.INT == 1U)    ///< PFC_TZ signal happen
   {
       PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.INT  = 1U;   ///< Clear TZ register
       PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.OST  = 1U;
       PFC_TZ_HW_SUM_PWM_REG.TZOSTCLR.bit.OST1  = 1U;
       PFC_TZ_HW_SUM_PWM_REG.TZOSTCLR.bit.OST2  = 1U;
   }
}
/********************************************End***********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        PFC EPwm enable
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
//#pragma CODE_SECTION(v_EPwmDrv_Pfc_PwmEn, ".TI.ramfunc");
#endif
static void v_EPwmDrv_Pfc_PwmEn(void)
{
#ifndef SST_1250kW
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;
    /* Clear PFC TZ one-shot flag */
    PFC_FAST_PWM.TZCLR.bit.OST = 1U;
    PFC_SLOW_PWM.TZCLR.bit.OST = 1U;
    /* Clear PFC TZ DCEVT2 flag */
    PFC_FAST_PWM.TZCLR.bit.DCAEVT2 = 1U;
    PFC_FAST_PWM.TZCLR.bit.DCBEVT2 = 1U;
    PFC_SLOW_PWM.TZCLR.bit.DCAEVT2 = 1U;
    PFC_SLOW_PWM.TZCLR.bit.DCBEVT2 = 1U;
    /* Clear PFC TZ CBC flag */
    PFC_FAST_PWM.TZCLR.bit.CBC = 1U;
    PFC_SLOW_PWM.TZCLR.bit.CBC = 1U;
    EDIS;
#elif(2U == GRID_PHASE_NUMBER)
    #ifndef _SIMULATION_NO_DSP_
    if(3U == stEPwmDrvLoc.uiCntrDriveEn)
    {
        EALLOW;
        /* Force PFC TZ CBC flag */
        PWM_L1A1_REG.TZFRC.bit.CBC = 1U;
        PWM_L1A2_REG.TZFRC.bit.CBC = 1U;
        PWM_L1B1_REG.TZFRC.bit.CBC = 1U;
        PWM_L1B2_REG.TZFRC.bit.CBC = 1U;

        PWM_L2A1_REG.TZFRC.bit.CBC = 1U;
        PWM_L2A2_REG.TZFRC.bit.CBC = 1U;
        PWM_L2B1_REG.TZFRC.bit.CBC = 1U;
        PWM_L2B2_REG.TZFRC.bit.CBC = 1U;

        if((TYPE_GRID_AN == stCom.uiTypeGrid) || (TYPE_GRID_AB == stCom.uiTypeGrid) || (TYPE_GRID_ABN == stCom.uiTypeGrid))
        {
            /* Clear PFC TZ one-shot flag */
            PWM_L1A1_REG.TZCLR.bit.OST = 1U;       ///< Enable PFC L1 MOS drive
            PWM_L1A2_REG.TZCLR.bit.OST = 1U;
            PWM_L1B1_REG.TZCLR.bit.OST = 1U;
            PWM_L1B2_REG.TZCLR.bit.OST = 1U;
            /* Clear PFC TZ CBC flag */
            PWM_L1A1_REG.TZCLR.bit.CBC = 1U;
            PWM_L1A2_REG.TZCLR.bit.CBC = 1U;
            PWM_L1B1_REG.TZCLR.bit.CBC = 1U;
            PWM_L1B2_REG.TZCLR.bit.CBC = 1U;
        }

        if((TYPE_GRID_BN == stCom.uiTypeGrid) || (TYPE_GRID_AB == stCom.uiTypeGrid) || (TYPE_GRID_ABN == stCom.uiTypeGrid))
        {
            /* Clear PFC TZ one-shot flag */
            PWM_L2A1_REG.TZCLR.bit.OST = 1U;        ///< Enable PFC L2 MOS drive
            PWM_L2A2_REG.TZCLR.bit.OST = 1U;
            PWM_L2B1_REG.TZCLR.bit.OST = 1U;
            PWM_L2B2_REG.TZCLR.bit.OST = 1U;
            /* Clear PFC TZ CBC flag */
            PWM_L2A1_REG.TZCLR.bit.CBC = 1U;
            PWM_L2A2_REG.TZCLR.bit.CBC = 1U;
            PWM_L2B1_REG.TZCLR.bit.CBC = 1U;
            PWM_L2B2_REG.TZCLR.bit.CBC = 1U;
        }
        EDIS;

        if(OPENLOOP_MODE == stComIf.uiModPfcRun)
        {
            UNLOCK_BALANCE_PWM();                  ///< Enable Balance MOS drive
        }
    }

    if (stEPwmDrvLoc.uiCntrDriveEn < 6U)
    {
        stEPwmDrvLoc.uiCntrDriveEn ++;
    }
    #else
    if (stEPwmDrvLoc.uiCntrDriveEn++>3)
    {
        PWM_drive_EN  = 0U;
        stEPwmDrvLoc.uiCntrDriveEn = 10U;
    }
    #endif
#elif(3U == GRID_PHASE_NUMBER)
    if(3U == stEPwmDrvLoc.uiCntrDriveEn)
    {
        EALLOW;

        if((PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss) && (OFFGRID_MODE != stComIf.uiModPfcRun))
        {
            if(TYPE_GRID_AN == stCom.uiTypeGrid)
            {
                PWM_A_REG.TZCLR.bit.OST = 1U;
            }
            else if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                PWM_B_REG.TZCLR.bit.OST = 1U;
            }
            else
            {
               PWM_C_REG.TZCLR.bit.OST = 1U;
            }
        }
        else
        {
            PWM_A_REG.TZCLR.bit.OST = 1U;
            PWM_B_REG.TZCLR.bit.OST = 1U;
            PWM_C_REG.TZCLR.bit.OST = 1U;
        }
        if(OPENLOOP_MODE == stComIf.uiModPfcRun)
        {
            PWM_N_REG.TZCLR.bit.OST = 1U;
        }

        PWM_A_REG.TZCLR.bit.DCAEVT2 = 1U;
        PWM_A_REG.TZCLR.bit.DCBEVT2 = 1U;
        PWM_B_REG.TZCLR.bit.DCAEVT2 = 1U;
        PWM_B_REG.TZCLR.bit.DCBEVT2 = 1U;
        PWM_C_REG.TZCLR.bit.DCAEVT2 = 1U;
        PWM_C_REG.TZCLR.bit.DCBEVT2 = 1U;

        EDIS;
    }

    if(stEPwmDrvLoc.uiCntrDriveEn < 6U)
    {
        stEPwmDrvLoc.uiCntrDriveEn++;
    }
#endif
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PFC EPwm disable
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Pfc_PwmDis, ".TI.ramfunc");
#endif
static void v_EPwmDrv_Pfc_PwmDis(void)
{
#ifndef SST_1250kW
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;
    /* Force CBC and OST flag */
    PFC_FAST_PWM.TZFRC.bit.CBC = 1U;
    PFC_SLOW_PWM.TZFRC.bit.CBC = 1U;

    PFC_FAST_PWM.TZFRC.bit.OST = 1U;
    PFC_SLOW_PWM.TZFRC.bit.OST = 1U;

    /* Clear PFC hardware sum fault TZ flag */
    if((1U == PFC_TZ_HW_SUM_PWM_REG.TZFLG.bit.INT) && (0U == stPfcDiag.unFlt.bit.uiTzHwSum))
    {
        PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.INT     = 1U;
        PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.OST     = 1U;
        PFC_TZ_HW_SUM_PWM_REG.TZOSTCLR.bit.OST1 = 1U;
    }
    /* Clear PFC CAP EVT status and interrupt status */
    if((1U == PFC_HW_NEG_OC_ECAP_REG.ECFLG.bit.INT) && (0U == stPfcDiag.unFlt.bit.uiGridHwNegOC))
    {
        PFC_HW_NEG_OC_ECAP_REG.ECCLR.bit.CEVT1 = 1U;
        PFC_HW_NEG_OC_ECAP_REG.ECCLR.bit.CEVT2 = 1U;
        PFC_HW_NEG_OC_ECAP_REG.ECCLR.bit.INT   = 1U;
    }
    EDIS;
#elif (2U == GRID_PHASE_NUMBER)
    stEPwmDrvLoc.uiCntrDriveEn = 0U;
    stEPwmDrvLoc.uiCntrBalEn   = 0U;
    #ifndef _SIMULATION_NO_DSP_
    LOCK_BALANCE_PWM();
    EALLOW;
    /* Force PFC TZ OST flag */
    PWM_L1A1_REG.TZFRC.bit.OST = 1U;     ///< Disable PFC L1 MOS drive
    PWM_L1A2_REG.TZFRC.bit.OST = 1U;
    PWM_L1B1_REG.TZFRC.bit.OST = 1U;
    PWM_L1B2_REG.TZFRC.bit.OST = 1U;

    PWM_L2A1_REG.TZFRC.bit.OST = 1U;     ///< Disable PFC L2 MOS drive
    PWM_L2A2_REG.TZFRC.bit.OST = 1U;
    PWM_L2B1_REG.TZFRC.bit.OST = 1U;
    PWM_L2B2_REG.TZFRC.bit.OST = 1U;

    if(0U == stPfcDiag.unFlt.bit.uiNegBusHwOV)
    {
        if(1U == PFC_HW_NEG_OV_ECAP_REG.ECFLG.bit.INT)         ///<ECap6Regs
        {
            /* Clear PFC CAP EVT status and interrupt status */
            PFC_HW_NEG_OV_ECAP_REG.ECCLR.bit.CEVT1 = 1U;
            PFC_HW_NEG_OV_ECAP_REG.ECCLR.bit.CEVT2 = 1U;
            PFC_HW_NEG_OV_ECAP_REG.ECCLR.bit.INT = 1U;
        }
    }
    EDIS;
    #else
    PWM_drive_EN = 1U;
    #endif
#elif(3U == GRID_PHASE_NUMBER)
    stEPwmDrvLoc.uiCntrDriveEn = 0U;
    stEPwmDrvLoc.uiCntrBalEn   = 0U;

    EALLOW;
    PWM_A_REG.TZFRC.bit.OST = 1U;
    PWM_B_REG.TZFRC.bit.OST = 1U;
    PWM_C_REG.TZFRC.bit.OST = 1U;
    PWM_N_REG.TZFRC.bit.OST = 1U;

    if((0U == stPfcDiag.unFlt.bit.uiPosBusHwOV) && (0U == stPfcDiag.unFlt.bit.uiBusHwOV))
    {
        if(1U == PFC_TZ_HW_SUM_PWM_REG.TZFLG.bit.INT)
        {
            PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.INT     = 1U;
            PFC_TZ_HW_SUM_PWM_REG.TZCLR.bit.OST     = 1U;
            PFC_TZ_HW_SUM_PWM_REG.TZOSTCLR.bit.OST1 = 1U;
            PFC_TZ_HW_SUM_PWM_REG.TZOSTCLR.bit.OST2 = 1U;
        }
    }
    EDIS;
#endif
#endif
}
/********************************************End***********************************************/

 #if(1U != GRID_PHASE_NUMBER)
/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Balance bridge PWM enable function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Bal_PwmEn, ".TI.ramfunc");
#endif
static void v_EPwmDrv_Bal_PwmEn(void)
{
#ifndef SST_1250kW
    if(3U == stEPwmDrvLoc.uiCntrBalEn)    ///< 3 interrupt period delay
    {
#if(2U == GRID_PHASE_NUMBER)
        UNLOCK_BALANCE_PWM();             ///< Enable Balance bridge pwm drive
#else
        EALLOW;
        PWM_N_REG.TZCLR.bit.OST = 1U;     ///< Enable Balance bridge pwm drive
        PWM_N_REG.TZCLR.bit.DCAEVT2 = 1U;
        PWM_N_REG.TZCLR.bit.DCBEVT2 = 1U;
        EDIS;
#endif		
    }

    if(stEPwmDrvLoc.uiCntrBalEn < 6U)
    {
        stEPwmDrvLoc.uiCntrBalEn++;
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Balance bridge PWM disable function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_EPwmDrv_Bal_PwmDis, ".TI.ramfunc");
#endif
static void v_EPwmDrv_Bal_PwmDis(void)
{
#ifndef SST_1250kW
#if(2U == GRID_PHASE_NUMBER)
    stEPwmDrvLoc.uiCntrBalEn   = 0U;
    LOCK_BALANCE_PWM();            ///< Disable Balance bridge pwm drive
#else
    EALLOW;
    PWM_N_REG.TZFRC.bit.OST = 1U;
    EDIS;
#endif	
#endif
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        D2D EPwm drive turn off
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_EPwmDrv_D2d_TurnOff(void)
{
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;
    DISABLE_EPWM(EPWM_PRI_UP_BDG);     ///< Disable D2D primary up bridge PWM
    DISABLE_EPWM(EPWM_SEC_UP_BDGL);    ///< Disable D2D secondary up left bridge PWM
    DISABLE_EPWM(EPWM_SEC_UP_BDGR);    ///< Disable D2D secondary up right bridge PWM
    DISABLE_EPWM(EPWM_PRI_DN_BDG);     ///< Disable D2D primary down bridge PWM
    DISABLE_EPWM(EPWM_SEC_DN_BDGL);    ///< Disable D2D secondary down left bridge PWM
    DISABLE_EPWM(EPWM_SEC_DN_BDGR);    ///< Disable D2D secondary down right bridge PWM
    EDIS;
#elif(2U == GRID_PHASE_NUMBER)
    EALLOW;
    DISABLE_EPWM(EPWM_PRI_UP_BDG);              ///< Disable Primary Up Bridge EPWM
    DISABLE_EPWM(EPWM_SEC_UP_BDG);              ///< Disable Secondary Up Bridge EPWM
    DISABLE_EPWM(EPWM_PRI_DN_BDG);              ///< Disable Primary Dn Bridge EPWM
    DISABLE_EPWM(EPWM_SEC_DN_BDG);              ///< Disable Secondary Dn Bridge EPWM
    EDIS;
#elif(3U == GRID_PHASE_NUMBER)
    EALLOW;
    DISABLE_EPWM(EPWM_PRI_BDGL);
    DISABLE_EPWM(EPWM_PRI_BDGR);
    DISABLE_EPWM(EPWM_SEC_UP_BDGL);
    DISABLE_EPWM(EPWM_SEC_UP_BDGR);
    DISABLE_EPWM(EPWM_SEC_DN_BDGL);
    DISABLE_EPWM(EPWM_SEC_DN_BDGR);
    EDIS;
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D EPwm drive clear TZ flag
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_EPwmDrv_D2d_ClrTzFlg(void)
{
#if(1U == GRID_PHASE_NUMBER)
    EALLOW;

    /* Clear Primary Up Bridge PWM TZ_Flag */
    EPWM_PRI_UP_BDG.TZCLR.bit.DCAEVT1 = 1U;                   ///< Clear Flag for DCAEVT1
    EPWM_PRI_UP_BDG.TZCLR.bit.DCBEVT1 = 1U;                   ///< Clear Flag for DCBEVT1
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;                ///< Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;                ///< Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.OST1 = 1U;                   ///< Clear Flag for OST1 Trip Latch

    /* Clear Primary Down Bridge PWM TZ_Flag */
    EPWM_PRI_DN_BDG.TZCLR.bit.DCAEVT1 = 1U;                   ///< Clear Flag for DCAEVT1
    EPWM_PRI_DN_BDG.TZCLR.bit.DCBEVT1 = 1U;                   ///< Clear Flag for DCBEVT1
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;                ///< Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;                ///< Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.OST1 = 1U;                   ///< Clear Flag for OST1 Trip Latch

    /* Clear Secondary Up Left Bridge PWM TZ_Flag */
    EPWM_SEC_UP_BDGL.TZCLR.bit.DCAEVT1 = 1U;                  ///< Clear Flag for DCAEVT1
    EPWM_SEC_UP_BDGL.TZCLR.bit.DCBEVT1 = 1U;                  ///< Clear Flag for DCBEVT1
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.DCAEVT1 = 1U;               ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.DCBEVT1 = 1U;               ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.OST1 = 1U;                  ///< Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Up Right Bridge PWM TZ_Flag */
    EPWM_SEC_UP_BDGR.TZCLR.bit.DCAEVT1 = 1U;                  ///< Clear Flag for DCAEVT1
    EPWM_SEC_UP_BDGR.TZCLR.bit.DCBEVT1 = 1U;                  ///< Clear Flag for DCBEVT1
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.DCAEVT1 = 1U;               ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.DCBEVT1 = 1U;               ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.OST1 = 1U;                  ///< Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Down Left Bridge PWM TZ_Flag */
    EPWM_SEC_DN_BDGL.TZCLR.bit.DCAEVT1 = 1U;                  ///< Clear Flag for DCAEVT1
    EPWM_SEC_DN_BDGL.TZCLR.bit.DCBEVT1 = 1U;                  ///< Clear Flag for DCBEVT1
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.DCAEVT1 = 1U;               ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.DCBEVT1 = 1U;               ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.OST1 = 1U;                  ///< Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Down Right Bridge PWM TZ_Flag */
    EPWM_SEC_DN_BDGR.TZCLR.bit.DCAEVT1 = 1U;                  ///< Clear Flag for DCAEVT1
    EPWM_SEC_DN_BDGR.TZCLR.bit.DCBEVT1 = 1U;                  ///< Clear Flag for DCBEVT1
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.DCAEVT1 = 1U;               ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.DCBEVT1 = 1U;               ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.OST1 = 1U;                  ///< Clear Flag for OST1 Trip Latch

    /* Clear EPWM6_TZ flag for next INT */
    EPWM_PRI_UP_BDG.TZCLR.bit.INT = 1U;

    /* Clear CMPSS Flag */
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.HLATCHCLR = 1U;         ///< Clear CMPSS8 High Comparator Output Status
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.LLATCHCLR = 1U;         ///< Clear CMPSS8 Low Comparator Output Status

    /* Clear X-BAR Flag */
    XbarRegs.XBARCLR1.bit.CMPSS8_CTRIPH = 1U;                 ///< Clear CMPSS8_CTRIPH Flag in X-BAR
    XbarRegs.XBARCLR1.bit.CMPSS8_CTRIPL = 1U;                 ///< Clear CMPSS8_CTRIPL Flag in X-BAR

    EDIS;
#elif(2U == GRID_PHASE_NUMBER)
    EALLOW;

    /* Clear Primary Up Bridge PWM TZ_Flag */
    EPWM_PRI_UP_BDG.TZCLR.bit.DCAEVT1 = 1U;                   ///< Clear Flag for DCAEVT1
    EPWM_PRI_UP_BDG.TZCLR.bit.DCBEVT1 = 1U;                   ///< Clear Flag for DCBEVT1
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;                ///< Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;                ///< Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_UP_BDG.TZOSTCLR.bit.OST1 = 1U;                   ///< Clear Flag for OST1 Trip Latch

    /* Clear Primary Down Bridge PWM TZ_Flag */
    EPWM_PRI_DN_BDG.TZCLR.bit.DCAEVT1 = 1U;                   ///< Clear Flag for DCAEVT1
    EPWM_PRI_DN_BDG.TZCLR.bit.DCBEVT1 = 1U;                   ///< Clear Flag for DCBEVT1
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;                ///< Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;                ///< Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_DN_BDG.TZOSTCLR.bit.OST1 = 1U;                   ///< Clear Flag for OST1 Trip Latch

    /* Clear Secondary Up Bridge PWM TZ_Flag */
    EPWM_SEC_UP_BDG.TZCLR.bit.DCAEVT1 = 1U;                  ///< Clear Flag for DCAEVT1
    EPWM_SEC_UP_BDG.TZCLR.bit.DCBEVT1 = 1U;                  ///< Clear Flag for DCBEVT1
    EPWM_SEC_UP_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;               ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_UP_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;               ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_UP_BDG.TZOSTCLR.bit.OST1 = 1U;                  ///< Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Down  Bridge PWM TZ_Flag */
    EPWM_SEC_DN_BDG.TZCLR.bit.DCAEVT1 = 1U;                ///< Clear Flag for DCAEVT1
    EPWM_SEC_DN_BDG.TZCLR.bit.DCBEVT1 = 1U;                ///< Clear Flag for DCBEVT1
    EPWM_SEC_DN_BDG.TZOSTCLR.bit.DCAEVT1 = 1U;             ///< Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_DN_BDG.TZOSTCLR.bit.DCBEVT1 = 1U;             ///< Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_DN_BDG.TZOSTCLR.bit.OST1 = 1U;                ///< Clear Flag for OST1 Trip Latch

    /* Clear EPWM3_TZ flag for next INT */
    EPWM_PRI_UP_BDG.TZCLR.bit.INT = 1U;

    /* Clear CMPSS Flag */
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.HLATCHCLR = 1U;     ///< Clear CMPSS3 High Comparator Output Status
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.LLATCHCLR = 1U;     ///< Clear CMPSS3 Low Comparator Output Status

    /* Clear X-BAR Flag */
    XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPH = 1U;            ///< Clear CMPSS3_CTRIPH Flag in X-BAR
    XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPL = 1U;            ///< Clear CMPSS3_CTRIPL Flag in X-BAR

    EDIS;
#elif(3U == GRID_PHASE_NUMBER)
    EALLOW;
    /* Clear Primary Up Bridge PWM TZ_Flag */
    EPWM_PRI_BDGL.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_PRI_BDGL.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_PRI_BDGL.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_BDGL.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_BDGL.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear Primary Down Bridge PWM TZ_Flag */
    EPWM_PRI_BDGR.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_PRI_BDGR.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_PRI_BDGR.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_PRI_BDGR.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_PRI_BDGR.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear Secondary Up Left Bridge PWM TZ_Flag */
    EPWM_SEC_UP_BDGL.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_SEC_UP_BDGL.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_UP_BDGL.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Up Right Bridge PWM TZ_Flag */
    EPWM_SEC_UP_BDGR.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_SEC_UP_BDGR.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_UP_BDGR.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Down Left Bridge PWM TZ_Flag */
    EPWM_SEC_DN_BDGL.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_SEC_DN_BDGL.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_DN_BDGL.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear  Secondary Down Right Bridge PWM TZ_Flag */
    EPWM_SEC_DN_BDGR.TZCLR.bit.DCAEVT1 = 1U;       // Clear Flag for DCAEVT1
    EPWM_SEC_DN_BDGR.TZCLR.bit.DCBEVT1 = 1U;       // Clear Flag for DCBEVT1
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.DCAEVT1 = 1U;    // Clear flag for DCAEVT1 selected for OST
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.DCBEVT1 = 1U;    // Clear flag for DCBEVT1 selected for OST
    EPWM_SEC_DN_BDGR.TZOSTCLR.bit.OST1 = 1U;       // Clear Flag for OST1 Trip Latch

    /* Clear EPWM7_TZ flag for next INT */
    EPwm7Regs.TZCLR.bit.INT = 1U;
    /* Clear CMPSS Flag */
    Cmpss6Regs.COMPSTSCLR.bit.HLATCHCLR = 1U;         // Clear CMPSS6 High Comparator Output Status
    Cmpss6Regs.COMPSTSCLR.bit.LLATCHCLR = 1U;         // Clear CMPSS6 Low Comparator Output Status

    /* Clear X-BAR Flag */
    XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPH = 1U;         // Clear CMPSS6_CTRIPH Flag in X-BAR
    XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPL = 1U;         // Clear CMPSS6_CTRIPL Flag in X-BAR
    EDIS;
#endif	
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
