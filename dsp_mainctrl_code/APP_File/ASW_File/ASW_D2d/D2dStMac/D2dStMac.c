//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dStMac.c
 * @brief
 * The source file of D2d state machine is designed to judge D2d running state.
 *
 * Module      :        \n
 * D2dStMac
 *
 * Unit        :        \n
 * null
 *
 * Module Task :        \n
 * v_D2dStMac_Init()    \n
 * v_D2dStMac_1ms()
 *
 * Unit Task   :        \n
 * null
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
#include "D2dStMac.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_D2D_ST_MAC stD2dStMac;                   ///< D2D state machine global struct

#if (1U == D2D_ST_MAC_DBG)
ST_D2D_ST_MAC stD2dStMacDbg;                ///< D2D state machine debug global struct
#endif

static ST_D2D_ST_MAC_LOC stD2dStMacLoc;     ///< D2D state machine local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: D2D state machine Init task
 * @param [in]   null
 * @param [out]  stD2dStMac.uiStD2dRun
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dStMac_Init(void)
{
    /* Local Signal*/
	stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;    ///< Initialize to standby status

    /* Global Signal*/
#if (1U == D2D_ST_MAC_DBG)
    stD2dStMacDbg.uiStD2dRun = stD2dStMacLoc.stPrmExt.uiStD2dRun;   ///< Initialize to standby status
    stD2dStMac.uiStD2dRun = stD2dStMacDbg.uiStD2dRun;               ///< Initialize to standby status
#else
    stD2dStMac.uiStD2dRun = stD2dStMacLoc.stPrmExt.uiStD2dRun;      ///< Initialize to standby status
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_D2dStMac_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: D2D state machine 1ms task
 * @param [in]   null
 * @param [out]  stD2dStMac.uiStD2dRun
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dStMac_1ms(void)
{
    switch(stD2dStMacLoc.stPrmExt.uiStD2dRun)
    {
        case D2D_ST_MAC_FLT:
        	///> Fault state
            v_D2dStMac_Flt_1ms();
            break;

        case D2D_ST_MAC_STB:
        	///> Standby state
            v_D2dStMac_Stb_1ms();
            break;
#ifndef SST_1250kW
        case D2D_ST_MAC_PWMENPRE:
        	///> PwmEn Pre state
            v_D2dStMac_PwmEnPre_1ms();
            break;

        case D2D_ST_MAC_PWMEN:
        	///> Pwm Enable state
            v_D2dStMac_PwmEn_1ms();
            break;
#endif
        case D2D_ST_MAC_SOFTSTRT:
        	///> Soft Start state
            v_D2dStMac_SoftStrt_1ms();
            break;

        case D2D_ST_MAC_NORMRUN:
        	///> Normal Run state
            v_D2dStMac_NormRun_1ms();
            break;

        default:
        	stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
            break;
    }
stPrmDisp.siPrm5 = stD2dStMacLoc.stPrmExt.uiStD2dRun;
    /* Output Signal*/
#if (1U == D2D_ST_MAC_DBG)
    stD2dStMac.uiStD2dRun = stD2dStMacDbg.uiStD2dRun;
#else
    stD2dStMac.uiStD2dRun = stD2dStMacLoc.stPrmExt.uiStD2dRun;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_D2dStMac_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D fault state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_Flt_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_FLT" to state "D2D_ST_MAC_STB" with priority 1st)  */
    if(D2D_FLT_IS_CLR)    // No fault
    {
        /* Switch to state "D2D_ST_MAC_STB" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
    }
    /* Static (state "D2D_ST_MAC_FLT") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D standby state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [in]   stComIf.uiCmdD2dRun
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_Stb_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_STB" to state "D2D_ST_MAC_FLT" with priority 1st)  */
    if(D2D_FLT_IS_SET)
    {
        /* Switch to state "D2D_ST_MAC_FLT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_FLT;
    }
    /* Condition (transition from state "D2D_ST_MAC_STB" to state "D2D_ST_MAC_PWMENPRE" with priority 2nd)  */
    else if(START_CMD == stComIf.uiCmdD2dRun)
    {
        /* Switch to state "D2D_ST_MAC_PWMENPRE" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_SOFTSTRT;
    }
    /* Static (state "D2D_ST_MAC_STB") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        PwmEn Pre state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [in]   stComIf.uiCmdD2dRun
 * @param [in]   stPerphCtrl.uiStBldCtrl
 * @param [in]   stEPwmDrv.uiFlgClrTzDone
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_PwmEnPre_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_PWMENPRE" to state "D2D_ST_MAC_FLT" with priority 1st)  */
    if(D2D_FLT_IS_SET)
    {
        /* Switch to state "D2D_ST_MAC_FLT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_FLT;
    }
    /* Condition (transition from state "D2D_ST_MAC_PWMENPRE" to state "D2D_ST_MAC_STB" with priority 2nd)  */
    else if(STOP_CMD == stComIf.uiCmdD2dRun)
    {
        /* Switch to state "D2D_ST_MAC_STB" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
    }
    /* Condition (transition from state "D2D_ST_MAC_PWMENPRE" to state "D2D_ST_MAC_PWMEN" with priority 3rd)  */
    else if((FCN_DISABLE == stPerphCtrl.stBld.uiCmd) && (1U == stEPwmDrv.uiFlgClrTzDone))
    {
        /* Switch to state "D2D_ST_MAC_PWMEN" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_PWMEN;
    }
    /* Static (state "D2D_ST_MAC_PWMENPRE") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D Pwm Enable state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [in]   stD2dDiag.uiFlgPwmEnJdgDone
 * @param [in]   stComIf.uiCmdD2dRun
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_PwmEn_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_PWMEN" to state "D2D_ST_MAC_FLT" with priority 1st)  */
    if(D2D_FLT_IS_SET)
    {
        /* Switch to state "D2D_ST_MAC_FLT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_FLT;
    }
    /* Condition (transition from state "D2D_ST_MAC_PWMEN" to state "D2D_ST_MAC_STB" with priority 2nd)  */
    else if(STOP_CMD == stComIf.uiCmdD2dRun)
    {
        /* Switch to state "D2D_ST_MAC_STB" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
    }
    /* Condition (transition from state "D2D_ST_MAC_PWMEN" to state "D2D_ST_MAC_SOFTSTRT" with priority 3rd)  */
    else if(1U == ui_D2dStMac_PwmEn_CellCheck())
    {
        /* Switch to state "D2D_ST_MAC_SOFTSTRT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_SOFTSTRT;
    }
    /* Static (state "D2D_ST_MAC_PWMEN") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D soft start state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [in]   stComIf.uiCmdD2dRun
 * @param [in]   stD2dPowPreCtrl.uiFlgRampDone
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_SoftStrt_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_SOFTSTRT" to state "D2D_ST_MAC_FLT" with priority 1st)  */
    if(D2D_FLT_IS_SET)
    {
        /* Switch to state "D2D_ST_MAC_FLT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_FLT;
    }
    /* Condition (transition from state "D2D_ST_MAC_SOFTSTRT" to state "D2D_ST_MAC_STB" with priority 2nd)  */
    else if(STOP_CMD == stComIf.uiCmdD2dRun)
    {
        /* Switch to state "D2D_ST_MAC_STB" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
    }
    /* Condition (transition from state "D2D_ST_MAC_SOFTSTRT" to state "D2D_ST_MAC_NORMRUN" with priority 3rd)  */
    else if(1U == stD2dPowPreCtrl.uiFlgRampDone)
    {
        /* Switch to state "D2D_ST_MAC_NORMRUN" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_NORMRUN;
    }
    /* Static (state "D2D_ST_MAC_SOFTSTRT") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        D2D normal run state
 * @param [in]   stD2dDiag.uiFltCpu
 * @param [in]   stD2dDiag.uiFltCla
 * @param [in]   stComIf.uiCmdD2dRun
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dStMac_NormRun_1ms(void)
{
    /* Condition (transition from state "D2D_ST_MAC_NORMRUN" to state "D2D_ST_MAC_FAULT" with priority 1st) */
    if(D2D_FLT_IS_SET)
    {
        /* Switch to state "D2D_ST_MAC_FLT" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_FLT;
    }
    /* Condition (transition from state "D2D_ST_MAC_NORMRUN" to state "D2D_ST_MAC_STB" with priority 2nd) */
    else if(STOP_CMD == stComIf.uiCmdD2dRun)
    {
        /* Switch to state "D2D_ST_MAC_STB" */
        stD2dStMacLoc.stPrmExt.uiStD2dRun = D2D_ST_MAC_STB;
    }
    /* Static (state "D2D_ST_MAC_NORMRUN") */
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Check Cell PWM output
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       1-OK£¬0-
 * @see          SWDD-xxxx
 */
static Uint16 ui_D2dStMac_PwmEn_CellCheck(void)
{
    Uint16 l_uiReturnValue = 0U;
#if(NUM_PHA_POW_CELL > 0U)
    l_uiReturnValue = stEmifDma1.unRunStateA1_4.uiPu1DabFPwm && stEmifDma1.unRunStateA1_4.uiPu1DabBPwm;
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB1_4.uiPu1DabFPwm && stEmifDma1.unRunStateB1_4.uiPu1DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC1_4.uiPu1DabFPwm && stEmifDma1.unRunStateC1_4.uiPu1DabBPwm);
#endif

#if(NUM_PHA_POW_CELL > 1U)
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateA1_4.uiPu2DabFPwm && stEmifDma1.unRunStateA1_4.uiPu2DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB1_4.uiPu2DabFPwm && stEmifDma1.unRunStateB1_4.uiPu2DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC1_4.uiPu2DabFPwm && stEmifDma1.unRunStateC1_4.uiPu2DabBPwm);
#endif

#if(NUM_PHA_POW_CELL > 2U)
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateA1_4.uiPu3DabFPwm && stEmifDma1.unRunStateA1_4.uiPu3DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB1_4.uiPu3DabFPwm && stEmifDma1.unRunStateB1_4.uiPu3DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC1_4.uiPu3DabFPwm && stEmifDma1.unRunStateC1_4.uiPu3DabBPwm);
#endif

#if(NUM_PHA_POW_CELL > 3U)
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateA1_4.uiPu4DabFPwm && stEmifDma1.unRunStateA1_4.uiPu4DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB1_4.uiPu4DabFPwm && stEmifDma1.unRunStateB1_4.uiPu4DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC1_4.uiPu4DabFPwm && stEmifDma1.unRunStateC1_4.uiPu4DabBPwm);
#endif

#if(NUM_PHA_POW_CELL > 4U)
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateA5_6.uiPu5DabFPwm && stEmifDma1.unRunStateA5_6.uiPu5DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB5_6.uiPu5DabFPwm && stEmifDma1.unRunStateB5_6.uiPu5DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC5_6.uiPu5DabFPwm && stEmifDma1.unRunStateC5_6.uiPu5DabBPwm);
#endif

#if(NUM_PHA_POW_CELL > 5U)
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateA5_6.uiPu6DabFPwm && stEmifDma1.unRunStateA5_6.uiPu6DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateB5_6.uiPu6DabFPwm && stEmifDma1.unRunStateB5_6.uiPu6DabBPwm);
    l_uiReturnValue = l_uiReturnValue && (stEmifDma1.unRunStateC5_6.uiPu6DabFPwm && stEmifDma1.unRunStateC5_6.uiPu6DabBPwm);
#endif

#ifdef _SIMULATION_NO_DSP_
    l_uiReturnValue = 1U;
#endif

    return l_uiReturnValue;

}

/*********************************************End**********************************************/
#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
