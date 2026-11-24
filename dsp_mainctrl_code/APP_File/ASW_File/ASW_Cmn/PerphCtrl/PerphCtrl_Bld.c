//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_Bld.c
 * @brief
 * The source file of bleed control is designed to realize bleed function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Bld_Init()              \n
 * v_PerphCtrl_Bld_1ms()               \n
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
#include "PerphCtrl_Bld.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_BLD_LOC stBldLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: bleed control in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_Bld_Init(void)
{
    /* Local Signal*/
	stBldLoc.stPrmExt.uiStMac       = BLD_ST_MAC_STB;    ///< Initialize to BLD_ST_MAC_STB
	stBldLoc.stPrmExt.uiCmd         = FCN_DISABLE;
	stBldLoc.stPrmExt.uiFlgDone     = 0U;
    stBldLoc.stPrmExt.ftVoltBattRec = 0.0f;
	stBldLoc.uiCntr                 = 0U;
	stBldLoc.uiFlgDoneV2LAuxPow     = 0U;

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrlDbg.stBld.uiStMac   = stBldLoc.stPrmExt.uiStMac;
	stPerphCtrlDbg.stBld.uiCmd     = stBldLoc.stPrmExt.uiCmd;
	stPerphCtrlDbg.stBld.uiFlgDone = stBldLoc.stPrmExt.uiFlgDone;
    stPerphCtrlDbg.stBld.ftVoltBattRec = stBldLoc.stPrmExt.ftVoltBattRec;

	stPerphCtrl.stBld.uiStMac   = stPerphCtrlDbg.stBld.uiStMac;
	stPerphCtrl.stBld.uiCmd     = stPerphCtrlDbg.stBld.uiCmd;
	stPerphCtrl.stBld.uiFlgDone = stPerphCtrlDbg.stBld.uiFlgDone;
    stPerphCtrl.stBld.ftVoltBattRec = stPerphCtrlDbg.stBld.ftVoltBattRec;
#else
	stPerphCtrl.stBld.uiStMac   = stBldLoc.stPrmExt.uiStMac;
	stPerphCtrl.stBld.uiCmd     = stBldLoc.stPrmExt.uiCmd;
	stPerphCtrl.stBld.uiFlgDone = stBldLoc.stPrmExt.uiFlgDone;
    stPerphCtrl.stBld.ftVoltBattRec = stBldLoc.stPrmExt.ftVoltBattRec;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: bleed control in 1ms task
 * @param [in]   null
 * @param [out]  stPerphCtrl.stBld.uiStMac
 * @param [out]  stPerphCtrl.stBld.uiCmd
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_Bld_1ms(void)
{
    switch(stBldLoc.stPrmExt.uiStMac)
    {
        case BLD_ST_MAC_STB:
            v_PerphCtrl_Bld_StMacStb_1ms();  ///< Bleed state machine Standby state
            break;

        case BLD_ST_MAC_EN:
            v_PerphCtrl_Bld_StMacEn_1ms();   ///< Bleed state machine Enable state
            break;

        case BLD_ST_MAC_V2L:
            v_PerphCtrl_Bld_StMacV2L_1ms();   ///< Bleed state machine V2L state
            break;

        default:
            ///< do nothing
            break;
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrl.stBld.uiStMac   = stPerphCtrlDbg.stBld.uiStMac;
	stPerphCtrl.stBld.uiCmd     = stPerphCtrlDbg.stBld.uiCmd;
	stPerphCtrl.stBld.uiFlgDone = stPerphCtrlDbg.stBld.uiFlgDone;
    stPerphCtrl.stBld.ftVoltBattRec = stPerphCtrlDbg.stBld.ftVoltBattRec;
#else
	stPerphCtrl.stBld.uiStMac   = stBldLoc.stPrmExt.uiStMac;
	stPerphCtrl.stBld.uiCmd     = stBldLoc.stPrmExt.uiCmd;
	stPerphCtrl.stBld.uiFlgDone = stBldLoc.stPrmExt.uiFlgDone;
    stPerphCtrl.stBld.ftVoltBattRec = stBldLoc.stPrmExt.ftVoltBattRec;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Bleeder resister state machine Standby state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Bld_StMacStb_1ms(void)
{
    /* No V2L Aux-power on stage */
    if(0U == stComIf.uiCmdV2LAuxPow)
    {
        /* Condition (transition from state "BLD_ST_MAC_STB" to state "BLD_ST_MAC_EN")  */
        if((stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB) \
            && ((0U == stBldLoc.stPrmExt.uiFlgDone) || (FCN_ENABLE == stD2dDiag.uiFlgBldCmd)) \
            && (1U == stComIf.uiFlgBldPtd) \
            && (stD2dAdc.ftVoltBattLpf10Hz > VOLT_BATT_BLD_ON))
        {
            /* Exit (state "BLD_ST_MAC_STB")  */
            ///< No code
            /* Entry (state "BLD_ST_MAC_EN")  */
            stBldLoc.uiCntr = 0U;
            stBldLoc.stPrmExt.ftVoltBattRec = stD2dAdc.ftVoltBattLpf10Hz;    ///< Battery voltage record
            /* Switch to state "BLD_ST_MAC_EN"  */
            stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_EN;
        }
        /* Static (state "BLD_ST_MAC_STB") */
        else
        {
            stBldLoc.stPrmExt.uiCmd   = FCN_DISABLE;
            if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMENPRE)
            {
                stBldLoc.stPrmExt.uiFlgDone = 0U;
            }
        }

        stBldLoc.uiFlgDoneV2LAuxPow = 0U;    ///< Clear V2L Aux power done flag
    }
    /* V2L Aux-power on stage */
    else
    {
        /* Condition (transition from state "BLD_ST_MAC_STB" to state "BLD_ST_MAC_V2L")  */
        if((1U == stComIf.uiFlgBldPtd) && (stD2dAdc.ftVoltBattLpf100Hz > (stComIf.ftVoltBattChrgReq + VOLT_ERR_V2L_AUX_POW_BLD_ON)) \
           && (0U == stBldLoc.uiFlgDoneV2LAuxPow))
        {
            /* Exit (state "BLD_ST_MAC_STB")  */
            ///< No code
            /* Entry (state "BLD_ST_MAC_V2L")  */
            stBldLoc.uiCntr = 0U;
            /* Switch to state "BLD_ST_MAC_V2L"  */
            stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_V2L;
        }
        /* Static (state "BLD_ST_MAC_STB") */
        else
        {
            stBldLoc.stPrmExt.uiCmd = FCN_DISABLE;
        }
    }
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Bleeder resister state machine Enable state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Bld_StMacEn_1ms(void)
{
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 1st)  */
    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMENPRE)
    {
        /* Exit (state "BLD_ST_MAC_EN")  */
        stBldLoc.stPrmExt.uiCmd     = FCN_DISABLE;
        stBldLoc.stPrmExt.uiFlgDone = 0U;
        /* Entry (state "D2D_ST_MAC_STB")  */
        ///< No code
        /* Switch to state "D2D_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 2nd)  */
    else if(0U != (stD2dDiag.uiFltCpu & FLT_D2D_BLD_RES))
    {
        /* Exit (state "BLD_ST_MAC_EN")  */
        stBldLoc.stPrmExt.uiCmd     = FCN_DISABLE;
        stBldLoc.stPrmExt.uiFlgDone = 1U;
        /* Entry (state "BLD_ST_MAC_STB")  */
        ///< No code
        /* Switch to state "BLD_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 3rd)  */
    else if(stD2dAdc.ftVoltBattLpf10Hz <= VOLT_BATT_BLD_ON)
    {
        stBldLoc.uiCntr++;

        if(stBldLoc.uiCntr >= 500U)    ///< Continue 500ms
        {
            /* Exit (state "BLD_ST_MAC_EN") */
            stBldLoc.stPrmExt.uiCmd     = FCN_DISABLE;
            stBldLoc.stPrmExt.uiFlgDone = 1U;
            stBldLoc.uiCntr             = 0U;
            /* Entry (state "D2D_ST_MAC_STB")  */
            ///< No code
            /* Switch to state "D2D_ST_MAC_STB"  */
            stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
        }
    }
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 4th)  */
    else if(1U == stComIf.uiCmdV2LAuxPow)
    {
        /* Exit (state "BLD_ST_MAC_V2L") */
        ///< No code
        /* Entry (state "D2D_ST_MAC_STB") */
        ///< No code
        /* Switch to state "D2D_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Static (state "BLD_ST_MAC_EN") */
    else
    {
        stBldLoc.stPrmExt.uiCmd = FCN_ENABLE;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Bleeder resister state machine V2L state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Bld_StMacV2L_1ms(void)
{
    stBldLoc.uiCntr++;
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 1st) */
    if(0U == stComIf.uiCmdV2LAuxPow)
    {
        /* Exit (state "BLD_ST_MAC_V2L") */
        ///< No code
        /* Entry (state "D2D_ST_MAC_STB") */
        ///< No code
        /* Switch to state "D2D_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 2nd) */
    else if(stD2dAdc.ftVoltBattLpf100Hz < (stComIf.ftVoltBattChrgReq - VOLT_ERR_V2L_AUX_POW_BLD_ON))
    {
        /* Exit (state "BLD_ST_MAC_EN") */
        stBldLoc.stPrmExt.uiCmd     = FCN_DISABLE;
        stBldLoc.uiFlgDoneV2LAuxPow = 1U;    ///< Set V2L Aux power done flag
        /* Entry (state "D2D_ST_MAC_STB") */
        ///< No code
        /* Switch to state "D2D_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Condition (transition from state "BLD_ST_MAC_EN" to state "BLD_ST_MAC_STB" with priority 3rd) */
    else if(stBldLoc.uiCntr >= 2000U)    ///< Continue 2s
    {
        /* Exit (state "BLD_ST_MAC_EN") */
        stBldLoc.stPrmExt.uiCmd     = FCN_DISABLE;
        stBldLoc.uiFlgDoneV2LAuxPow = 1U;    ///< Set V2L Aux power done flag
        stBldLoc.uiCntr             = 0U;
        /* Entry (state "D2D_ST_MAC_STB")  */
        ///< No code
        /* Switch to state "D2D_ST_MAC_STB"  */
        stBldLoc.stPrmExt.uiStMac = BLD_ST_MAC_STB;
    }
    /* Static (state "BLD_ST_MAC_EN") */
    else
    {
        stBldLoc.stPrmExt.uiCmd = FCN_ENABLE;
    }
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
