//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dDiag.c
 * @brief
 * The source file of D2D diagnosis is designed to realize D2d diagnosis function.
 *
 * Module      :                       \n
 * D2dDiag                             \n
 *
 * Unit        :                       \n
 * BattUV                              \n
 * BattUVAndSC                         \n
 * BattCurrImbal                       \n
 * BattVoltImbal                       \n
 * BldCtrl                             \n
 * SPRlyOT                             \n
 * RstFlt                              \n
 * XInt4Isr                            \n
 * XInt5Isr                            \n
 * Epwm6Isr                            \n
 * Epwm7TzIsr                          \n
 *
 * Module Task :                       \n
 * v_D2dDiag_Init()                    \n
 * v_D2dDiag_1ms()                     \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattUV_Init()             \n
 * v_D2dDiag_BattUV_1ms()              \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattUVAndSC_Init()        \n
 * v_D2dDiag_BattUVAndSC_1ms()         \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattCurrImbal_Init()      \n
 * v_D2dDiag_BattCurrImbal_1ms()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattVoltImbal_Init()      \n
 * v_D2dDiag_BattVoltImbal_1ms()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BldCtrl_1ms()             \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_Bld_Init()                \n
 * v_D2dDiag_Bld_1ms()                 \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_RstFlt_1ms()              \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_XInt_PriUpOC_Isr()        \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_XInt_PriDwnOC_Isr()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_EpwmTz_Hw_Isr()           \n
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
#include "D2dDiag.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_D2D_DIAG stD2dDiag;       			///< D2D diagnose global struct

#if (1U == D2D_DIAG_DBG)
ST_D2D_DIAG stD2dDiagDbg;    			///< D2D diagnose debug global struct
#endif

static ST_D2D_DIAG_LOC stD2dDiagLoc;    ///< D2D diagnose local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dDiag_Init(void)
{
    /* Local Signal*/
	stD2dDiagLoc.stPrmExt.uiFltCpu          = 0U;          ///< Initialize to 0
	stD2dDiagLoc.stPrmExt.uiFltCla          = 0U;          ///< Initialize to 0

	v_D2dDiag_BusUV_Init();                                ///< Bus under voltage diagnosis
	v_D2dDiag_BattUV_Init();                               ///< Battery under voltage diagnosis
	v_D2dDiag_BattUVAndSC_Init();                          ///< Battery under voltage and short current diagnosis
	v_D2dDiag_BattCurrImbal_Init();                        ///< Battery imbalance current diagnosis
	v_D2dDiag_BattVoltImbal_Init();                        ///< Battery imbalance voltage diagnosis
	v_D2dDiag_Bld_Init();                                  ///< Bleeder diagnosis
	v_D2dDiag_SPRly_Init();                                ///< SP Relay diagnosis

    /* Global Signal*/
#if (1U == D2D_DIAG_DBG)
	stD2dDiagDbg.uiFltCpu          = stD2dDiagLoc.stPrmExt.uiFltCpu;             ///< Initialize to 0
	stD2dDiagDbg.uiFltCla          = stD2dDiagLoc.stPrmExt.uiFltCla;             ///< Initialize to 0
	stD2dDiagDbg.uiFlgPwmEnJdgDone = stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone;    ///< Initialize to 0
	stD2dDiagDbg.uiFlgBldCmd       = stD2dDiagLoc.stPrmExt.uiFlgBldCmd;          ///< Initialize to disable command

	stD2dDiag.uiFltCpu          = stD2dDiagDbg.uiFltCpu;                         ///< Initialize to 0
	stD2dDiag.uiFltCla          = stD2dDiagDbg.uiFltCla;                         ///< Initialize to 0
	stD2dDiag.uiFlgPwmEnJdgDone = stD2dDiagDbg.uiFlgPwmEnJdgDone;                ///< Initialize to 0
	stD2dDiag.uiFlgBldCmd       = stD2dDiagDbg.uiFlgBldCmd;                      ///< Initialize to disable command
#else
	stD2dDiag.uiFltCpu          = stD2dDiagLoc.stPrmExt.uiFltCpu;                ///< Initialize to 0
	stD2dDiag.uiFltCla          = stD2dDiagLoc.stPrmExt.uiFltCla;                ///< Initialize to 0
	stD2dDiag.uiFlgPwmEnJdgDone = stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone;       ///< Initialize to 0
	stD2dDiag.uiFlgBldCmd       = stD2dDiagLoc.stPrmExt.uiFlgBldCmd;             ///< Initialize to disable command
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_D2dDiag_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dDiag_1ms(void)
{
#if 1U == FLG_D2D_POWCTRL_EN
    stD2dDiagLoc.stPrmExt.uiFltCla = stD2dPowCtrlClaToCpu.stFlt.uiFltCla;
#endif
#if 0
#if 0U == FLG_SWUT_EN
    if(0U == stCom.unCmdFct.bit.uiEnFctPwm)
    {
        v_D2dDiag_HwFltDet();                   ///< HW fault diagnosis
    }
#endif
    v_D2dDiag_BusUV_1ms();                  ///< Bus under voltage diagnosis
    v_D2dDiag_BattUV_1ms();                 ///< Battery under voltage diagnosis
    v_D2dDiag_BattUVAndSC_1ms();            ///< Battery under voltage and short current diagnosis
    v_D2dDiag_BattCurrImbal_1ms();          ///< Battery imbalance current diagnosis
    v_D2dDiag_BattVoltImbal_1ms();          ///< Battery imbalance voltage diagnosis
    v_D2dDiag_Bld_1ms();                    ///< Bleed diagnosis
#endif
    v_D2dDiag_RstFlt_1ms();                 ///< Reset fault

    /* Output Signal*/
#if (1U == D2D_DIAG_DBG)
    stD2dDiag.uiFltCpu          = stD2dDiagDbg.uiFltCpu;
    stD2dDiag.uiFltCla          = stD2dDiagDbg.uiFltCla;
    stD2dDiag.uiFlgPwmEnJdgDone = stD2dDiagDbg.uiFlgPwmEnJdgDone;
#else
    stD2dDiag.uiFltCpu          = stD2dDiagLoc.stPrmExt.uiFltCpu;
    stD2dDiag.uiFltCla          = stD2dDiagLoc.stPrmExt.uiFltCla;
    stD2dDiag.uiFlgPwmEnJdgDone = stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_D2dDiag_1ms() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D diagnose 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dDiag_10ms(void)
{
#if 0
    v_D2dDiag_SPRly_10ms();             ///< SP relay over time diagnosis
#endif

    /* Output Signal*/
#if (1U == D2D_DIAG_DBG)
    stD2dDiag.uiFltCpu    = stD2dDiagDbg.uiFltCpu;
    stD2dDiag.uiFlgBldCmd = stD2dDiagDbg.uiFlgBldCmd;
#else
    stD2dDiag.uiFltCpu    = stD2dDiagLoc.stPrmExt.uiFltCpu;
    stD2dDiag.uiFlgBldCmd = stD2dDiagLoc.stPrmExt.uiFlgBldCmd;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_D2dDiag_10ms() is running****\r\n");
    }
#endif

}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BusUV_Init(void)
{
    stD2dDiagLoc.uiCntrBusUV   = 0U;                    ///< Initialize to 0
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BusUV_1ms(void)
{
    /* BUS UV Fault */
    if((0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BUS_SLOW_UV)) \
            && (CHG_ONGRID_MODE != stComIf.uiModD2dRun) && (OPENLOOP_MODE != stComIf.uiModD2dRun))    ///< Not openLoop mode && No charge mode
    {
#if 1U == FLG_PFC_POWCTRL_EN
        if((stPfcPowCtrl.ftVbusNotch < (stPowLim.ftVoltBusLim - 5.0f)) \
        		&& (0U == (stD2dDiagLoc.stPrmExt.uiFltCpu & FLT_D2D_BUS_SLOW_UV)) \
                && (stD2dStMac.uiStD2dRun >= D2D_ST_MAC_NORMRUN) \
                && (0U == stComIf.uiFlgPfcTzToDC))
#else
        if(1U) ///< To be modified
#endif
        {
            if(stD2dDiagLoc.uiCntrBusUV < DURN_DCHA_BUS_UV_SLOW)
            {
                stD2dDiagLoc.uiCntrBusUV++;
            }
            else
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BUS_SLOW_UV;
            }
        }
        else if(stD2dDiagLoc.uiCntrBusUV > 0U)
        {
            stD2dDiagLoc.uiCntrBusUV--;
        }
        else
        {
            ///< No Code
        }
    }
}
/********************************************End***********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattUV_Init(void)
{
    stD2dDiagLoc.uiStBattUV       = D2D_ST_MAC_NORMRUN;    ///< Initialize to normalRun state
    stD2dDiagLoc.uiDurnBattUV     = DURN_CHRG_BATT_UV;     ///< Initialize to charge battery UV protection number
    stD2dDiagLoc.uiCntrBattUV     = 0U;                    ///< Initialize to 0U
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattUV_1ms(void)
{
    /* Output UV Fault */
    if((0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BATT_UV)) && (OPENLOOP_MODE != stComIf.uiModD2dRun))    // Not OpenLoop Mode
    {
        if(CHG_ONGRID_MODE == stComIf.uiModD2dRun)
        {
            stD2dDiagLoc.uiDurnBattUV = DURN_CHRG_BATT_UV;     ///< Charge mode protect number: 150ms
            stD2dDiagLoc.uiStBattUV = D2D_ST_MAC_NORMRUN;      ///< Charge mode protect state: normal run state
        }
        else
        {
            stD2dDiagLoc.uiDurnBattUV = DURN_BIDIR_BATT_UV;    ///< Non-charge mode protect number: 3ms
            stD2dDiagLoc.uiStBattUV = D2D_ST_MAC_PWMEN;        ///< Non-charge mode protect state: PWM_EN state
        }

        if((stD2dAdc.ftVoltBattLpf5kHz < stComTbl.stPrmD2dDiag.ftVoltBattUV) \
                && (0U == (stD2dDiagLoc.stPrmExt.uiFltCpu & FLT_D2D_BATT_UV)) \
                && (stD2dStMac.uiStD2dRun >= stD2dDiagLoc.uiStBattUV))
        {

            if(stD2dDiagLoc.uiCntrBattUV < stD2dDiagLoc.uiDurnBattUV)
            {
                stD2dDiagLoc.uiCntrBattUV++;
            }
            else
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BATT_UV;
            }
        }
        else if(stD2dDiagLoc.uiCntrBattUV > 0U)
        {
            stD2dDiagLoc.uiCntrBattUV--;
        }
        else
        {
            // None Code
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattUVAndSC_Init(void)
{
	stD2dDiagLoc.uiFlgBattUVAndSCEn         = 0U;                    ///< Initialize to 0U
    stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 0U;                    ///< Initialize to 0U
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattUVAndSC_1ms(void)
{
    /* To be modified */
    if(D2D_ST_MAC_PWMEN == stD2dStMac.uiStD2dRun)
    {
       if(CHG_ONGRID_MODE == stComIf.uiModD2dRun)
        {
           if(stD2dPowPreCtrl.ftVoltBattChrgRef >= VOLT_BATT_MIN)
           {
               stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 1U;
               stD2dDiagLoc.uiFlgBattUVAndSCEn = 1U;
           }
        }
#if(3U != GRID_PHASE_NUMBER)
       else
       {
           stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 1U;
           stD2dDiagLoc.uiFlgBattUVAndSCEn = 0U;
       }
#else
        else if(OPENLOOP_MODE == stComIf.uiModD2dRun)
        {
            stD2dDiagLoc.uiFlgBattUVAndSCEn = 0U;

            if(1U == stD2dPowPreCtrl.uiFlgDp3OLDone)
            {
                stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 1U;
            }
        }
        else
        {
            stD2dDiagLoc.uiFlgBattUVAndSCEn = 0U;
            stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 1U;
        }
#endif
    }
    else
    {
        stD2dDiagLoc.stPrmExt.uiFlgPwmEnJdgDone = 0U;
        stD2dDiagLoc.uiFlgBattUVAndSCEn = 0U;
    }

	if(1U == stD2dDiagLoc.uiFlgBattUVAndSCEn)
	{
        if(stD2dAdc.ftVoltBattLpf5kHz < VOLT_BATT_TH_SC)    ///< less than Vout Threshold
        {
            if(stD2dAdc.ftCurrBattLpf5kHz > 0.3f)    ///< if output current greater than threshold, short circuit fault
            {
                if(0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BATT_SC))
                {
                    stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BATT_SC;
                }
            }
            else    ///< if output current less than threshold, under voltage fault
            {
                if(0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BATT_UV))
                {
                    stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BATT_UV;
                }
            }
        }
	}
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattCurrImbal_Init(void)
{
    stD2dDiagLoc.uiCntrBattCurrImbal    = 0U;                    ///< Initialize to 0
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattCurrImbal_1ms(void)
{
    float32 l_ftImbalTmp = 0.0f;
    float32 l_ftDataTmp  = 0.0f;
    float32 l_ftDurnTmp = 0.0f;

    /* Imbalance Current Protection */
    if(0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BATT_IMBAL_CURR))
    {
        l_ftImbalTmp = fabsf(stD2dAdc.ftCurrBattUpLpf10Hz - stD2dAdc.ftCurrBattDwnLpf10Hz);
        if((l_ftImbalTmp > stComTbl.stPrmD2dDiag.ftCurrBattImbal) && (0U == (stD2dDiagLoc.stPrmExt.uiFltCpu & FLT_D2D_BATT_IMBAL_CURR)) \
                && (stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN))
        {
            l_ftDataTmp = l_ftImbalTmp - stComTbl.stPrmD2dDiag.ftCurrBattImbal;
            if(l_ftDataTmp >= CURR_BATT_IMBAL_DELTA)
            {
                l_ftDataTmp = CURR_BATT_IMBAL_DELTA;
            }
            l_ftDurnTmp = DURN_BATT_CURR_IMBAL_MAX - COEFF_BATT_CURR_IMBAL * l_ftDataTmp;

            if(stD2dDiagLoc.uiCntrBattCurrImbal < (Uint16)l_ftDurnTmp)
            {
                stD2dDiagLoc.uiCntrBattCurrImbal++;
            }
            else
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BATT_IMBAL_CURR;
            }
        }
        else if(stD2dDiagLoc.uiCntrBattCurrImbal > 0U)
        {
            stD2dDiagLoc.uiCntrBattCurrImbal--;
        }
        else
        {
            ///< No Code
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattVoltImbal_Init(void)
{
    stD2dDiagLoc.uiCntrBattVoltImbal    = 0U;                    ///< Initialize to 0
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_BattVoltImbal_1ms(void)
{
    float32 l_ftImbalTmp = 0.0f;
    float32 l_ftDataTmp  = 0.0f;
    float32 l_ftDurnTmp = 0.0f;

    /* Imbalance Voltage Protection */
    if(0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BATT_IMBAL_VOLT))
    {
        l_ftImbalTmp = fabsf(stD2dAdc.ftVoltBattUpLpf10Hz - stD2dAdc.ftVoltBattDwnLpf10Hz);
        if((l_ftImbalTmp > stComTbl.stPrmD2dDiag.ftVoltBattImbal) && (0U == (stD2dDiagLoc.stPrmExt.uiFltCpu & FLT_D2D_BATT_IMBAL_VOLT)) \
                && (stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN))
        {
            l_ftDataTmp = l_ftImbalTmp - stComTbl.stPrmD2dDiag.ftVoltBattImbal;
            if(l_ftDataTmp >= VOLT_BATT_IMBAL_DELTA)
            {
                l_ftDataTmp = VOLT_BATT_IMBAL_DELTA;
            }
            l_ftDurnTmp = DURN_BATT_VOLT_IMBAL_MAX - COEFF_BATT_VOLT_IMBAL * l_ftDataTmp;

            if(stD2dDiagLoc.uiCntrBattVoltImbal < (Uint16)l_ftDurnTmp)
            {
                stD2dDiagLoc.uiCntrBattVoltImbal++;
            }
            else
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BATT_IMBAL_VOLT;
            }
        }
        else if(stD2dDiagLoc.uiCntrBattVoltImbal > 0U)
        {
            stD2dDiagLoc.uiCntrBattVoltImbal--;
        }
        else
        {
            // None Code
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_Bld_Init(void)
{
    stD2dDiagLoc.uiCntrBldOT         = 0U;                    ///< Initialize to 0
    stD2dDiagLoc.uiCntrBldVoltFlt    = 0U;                    ///< Initialize to 0
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_Bld_1ms(void)
{
    if((BLD_ST_MAC_EN == stPerphCtrl.stBld.uiStMac) && (0U == stComIf.uiCmdV2LAuxPow))
    {
        stD2dDiagLoc.uiCntrBldOT++;
        if((stPerphCtrl.stBld.ftVoltBattRec > 200.0f) && ((stPerphCtrl.stBld.ftVoltBattRec - stD2dAdc.ftVoltBattLpf10Hz) < 20.0f))    ///< Voltage drop less than 20V
        {
            stD2dDiagLoc.uiCntrBldVoltFlt++;
        }

        if((stD2dDiagLoc.uiCntrBldOT >= DURN_BLD_OT) || (stD2dDiagLoc.uiCntrBldVoltFlt >= DURN_BLD_VOLT_FLT))
        {
            if(0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_BLD_RES))
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_BLD_RES;       ///< Bleed Resistor Fault
            }
        }
    }
    else
    {
        stD2dDiagLoc.uiCntrBldOT      = 0U;
        stD2dDiagLoc.uiCntrBldVoltFlt = 0U;
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_RstFlt_1ms(void)
{
    /* D2D fault reset */
    if((1U == stComIf.uiFlgFltRst) && (0U != stD2dDiagLoc.stPrmExt.uiFltCpu))
    {
        stD2dDiagLoc.stPrmExt.uiFltCpu = 0U;
#ifndef _SIMULATION_NO_DSP_
        v_EPwmDrv_D2d_ClrTzFlg();
#endif
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_SPRly_Init(void)
{
    stD2dDiagLoc.uiCntrSPRlyOT              = 0U;                    ///< Initialize to 0
    stD2dDiagLoc.stPrmExt.uiFlgBldCmd       = FCN_DISABLE;           ///< Initialize to disable command
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dDiag_SPRly_10ms(void)
{
    /* SP relay overtime fault */
    if((0U == (stD2dDiagLoc.stPrmExt.uiFltCpu & FLT_D2D_SP_RLY)) && (0U == (stComTbl.stPrmD2dDiag.uiFltCpuNC & FLT_D2D_SP_RLY)))    ///< No SP Relay Fault
    {
        if(0U == stPerphCtrl.stSPRly.uiFlgOk)
        {
            stD2dDiagLoc.uiCntrSPRlyOT++;
            if(DURN_SP_RLY_CMD_BLD == stD2dDiagLoc.uiCntrSPRlyOT)
            {
                stD2dDiagLoc.stPrmExt.uiFlgBldCmd = FCN_ENABLE;
            }
            else if(DURN_SP_RLY_OT == stD2dDiagLoc.uiCntrSPRlyOT)
            {
                stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_D2D_SP_RLY;    ///< Set SP Relay Fault bit

                stD2dDiagLoc.uiCntrSPRlyOT        = 0U;
                stD2dDiagLoc.stPrmExt.uiFlgBldCmd = FCN_DISABLE;
            }
            else
            {
                ///< No code
            }
        }
        else
        {
            stD2dDiagLoc.uiCntrSPRlyOT        = 0U;
            stD2dDiagLoc.stPrmExt.uiFlgBldCmd = FCN_DISABLE;
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_D2dDiag_EpwmTz_Hw_Isr, ".TI.ramfunc");
__interrupt void v_D2dDiag_EpwmTz_Hw_Isr(void)
#else
void v_D2dDiag_EpwmTz_Hw_Isr(void)
#endif
{
	Uint16 l_uiTmp1 = 0U;
	Uint16 l_uiTmp2 = 0U;

#ifndef _SIMULATION_NO_DSP_
#if(0U == FLG_SWUT_EN)
	v_D2dDiag_HwFltDet();
    l_uiTmp1 = FLG_CMPSS_XBAR_BATT_OC_POS;
    l_uiTmp2 = FLG_CMPSS_XBAR_BATT_OC_NEG;
    if((0U == l_uiTmp1) && (0U == l_uiTmp2))    // CMPSSx_H or CMPSSx_H has not occurred
    {
    	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_SUM;
    }
#endif

#if(0U == FLG_SWUT_EN)
    v_EPwmDrv_D2d_TurnOff();

    PieCtrlRegs.PIEACK.bit.ACK2 = 1U;    // Acknowledge this int to receive more int from group 3
#endif
#endif

    /* Output Signal*/
#if (1U == D2D_DIAG_DBG)
	stD2dDiag.uiFltCpu    = stD2dDiagDbg.uiFltCpu;
#else
	stD2dDiag.uiFltCpu    = stD2dDiagLoc.stPrmExt.uiFltCpu;
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        XINT4 ISR function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_D2dDiag_XInt_PriUpOC_Isr, ".TI.ramfunc");
__interrupt void v_D2dDiag_XInt_PriUpOC_Isr(void)
#else
void v_D2dDiag_XInt_PriUpOC_Isr(void)
#endif
{
	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_PRI_UP_OC;

#if(0U == FLG_SWUT_EN)
#ifndef _SIMULATION_NO_DSP_
	v_EPwmDrv_D2d_TurnOff();
    PieCtrlRegs.PIEACK.bit.ACK12 = 1U;    ///< Acknowledge this INT to receive more INT from group 12
#endif
#endif
    /* Output Signal*/
#if (1U == D2D_DIAG_DBG)
	stD2dDiag.uiFltCpu    = stD2dDiagDbg.uiFltCpu;
#else
	stD2dDiag.uiFltCpu    = stD2dDiagLoc.stPrmExt.uiFltCpu;
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        XINT5 ISR function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if((1U == GRID_PHASE_NUMBER) || (2U == GRID_PHASE_NUMBER))
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_D2dDiag_XInt_PriDwnOC_Isr, ".TI.ramfunc");
__interrupt void v_D2dDiag_XInt_PriDwnOC_Isr(void)
#else
void v_D2dDiag_XInt_PriDwnOC_Isr(void)
#endif
{
	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_PRI_DN_OC;

#if(0U == FLG_SWUT_EN)
#ifndef _SIMULATION_NO_DSP_
	v_EPwmDrv_D2d_TurnOff();
    PieCtrlRegs.PIEACK.bit.ACK12 = 1U;    // Acknowledge this int to receive more int from group 12
#endif
#endif
    /* Output Signal*/
#if (1U == D2D_DIAG_DBG)
	stD2dDiag.uiFltCpu    = stD2dDiagDbg.uiFltCpu;
#else
	stD2dDiag.uiFltCpu    = stD2dDiagLoc.stPrmExt.uiFltCpu;
#endif
}
#endif
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Hardware fault detect function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_D2dDiag_HwFltDet, ".TI.ramfunc");
#endif
static void v_D2dDiag_HwFltDet(void)
{
#if(0U == FLG_SWUT_EN)
	Uint16 l_uiTmp1 = 0U;
	Uint16 l_uiTmp2 = 0U;

    if(1U == stComIf.uiFlgPowOn)    // Control Power delay
    {
#ifndef _SIMULATION_NO_DSP_
        /* CMPSS8 FLT_CMPSS_D2D_BATT_OC FAULT*/
    	l_uiTmp1 = FLG_CMPSS_XBAR_BATT_OC_POS;
    	l_uiTmp2 = FLG_CMPSS_XBAR_BATT_OC_NEG;
        if((1U == l_uiTmp1) || (1U == l_uiTmp2))    // CMPSSx_H or CMPSSx_H has occurred
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_CMPSS_D2D_BATT_OC;
        }

        /* Sum Hardware Fault */
        if(D2D_SUM_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_SUM;
        }
        /* D2D Output OV Hardware Fault */
        if(D2D_OUT_OV_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BATT_OV;
        }
        #if((1U == GRID_PHASE_NUMBER)||(2U == GRID_PHASE_NUMBER))
        /* D2D Output Down OV Hardware Fault */
        if(D2D_OUT_DN_OV_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BATT_DN_OV;
        }
        #endif
        /* D2D Positive Output OC Hardware Fault */
        if(D2D_POS_OUT_OC_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BATT_OC_POS;
        }
        /* D2D Negative Output OC Hardware Fault */
        if(D2D_NEG_OUT_OC_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BATT_OC_NEG;
        }
        /* D2D Primary Up OC Hardware Fault */
        if(D2D_PRI_UP_OC_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_PRI_UP_OC;
        }
        #if(1U == GRID_PHASE_NUMBER)
        /* D2D Primary Down OC Hardware Fault */
        if(D2D_PRI_DN_OC_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_PRI_DN_OC;
        }
        /* D2D Bus OV Hardware Fault */
        if(D2D_BUS_OV_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BUS_OV;
        }
        #endif
		
        #if(2U == GRID_PHASE_NUMBER)
        /* D2D Primary Down OC Hardware Fault */
        if(D2D_PRI_DN_OC_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_PRI_DN_OC;
        }
        /* D2D Bus OV Hardware Fault */
        if(D2D_BUS_L_OV_HW_FLT_IS_ON)
        {
        	stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BUS_OV;
        }
        if(D2D_BUS_H_OV_HW_FLT_IS_ON)
        {
            stD2dDiagLoc.stPrmExt.uiFltCpu |= FLT_HW_D2D_BUS_OV;
        }
        #endif
#endif
    }
#endif
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
