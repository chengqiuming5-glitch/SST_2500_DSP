//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_AcRly.c
 * @brief
 * The source file of AC relay control is designed to realize function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_AcRly_Init()            \n
 * v_PerphCtrl_AcRly_10ms()            \n
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
#include "PerphCtrl_AcRly.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_ACRLY_LOC stAcRlyLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: AC relay control in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_AcRly_Init(void)
{
    /* Local Signal*/
    stAcRlyLoc.stPrmExt.uiStMac   = STB_AC_RLY_ST_MAC;
    stAcRlyLoc.stPrmExt.uiCmpPwm  = 0U;
    stAcRlyLoc.uiCntrEn           = 0U;

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrlDbg.stAcRly.uiStMac  = stAcRlyLoc.stPrmExt.uiStMac;
    stPerphCtrlDbg.stAcRly.uiCmpPwm = stAcRlyLoc.stPrmExt.uiCmpPwm;

	stPerphCtrl.stAcRly.uiStMac     = stPerphCtrlDbg.stAcRly.uiStMac;
    stPerphCtrl.stAcRly.uiCmpPwm    = stPerphCtrlDbg.stAcRly.uiCmpPwm;
#else
	stPerphCtrl.stAcRly.uiStMac     = stAcRlyLoc.stPrmExt.uiStMac;
    stPerphCtrl.stAcRly.uiCmpPwm    = stAcRlyLoc.stPrmExt.uiCmpPwm;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: AC relay control in 10ms task
 * @param [in]   null
 * @param [out]  stPerphCtrl..
 * @param [out]  stPerphCtrl..
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_AcRly_10ms(void)
{
    switch(stAcRlyLoc.stPrmExt.uiStMac)
    {
        case STB_AC_RLY_ST_MAC:
            v_PerphCtrl_AcRly_StMacStb_10ms();    ///< AC relay control state machine Standby state
            break;

        case EN_AC_RLY_ST_MAC:
            v_PerphCtrl_AcRly_StMacEn_10ms();     ///< AC relay control state machine Enable state
            break;

        case PWM_AC_RLY_ST_MAC:
            v_PerphCtrl_AcRly_StMacPwm_10ms();    ///< AC relay control state machine PWM state
            break;

        default:
            ///< Do nothing
            break;
    }

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrl.stAcRly.uiStMac     = stPerphCtrlDbg.stAcRly.uiStMac;
    stPerphCtrl.stAcRly.uiCmpPwm    = stPerphCtrlDbg.stAcRly.uiCmpPwm;
#else
    stPerphCtrl.stAcRly.uiStMac     = stAcRlyLoc.stPrmExt.uiStMac;
    stPerphCtrl.stAcRly.uiCmpPwm    = stAcRlyLoc.stPrmExt.uiCmpPwm;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: AC relay control state machine Standby state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_AcRly_StMacStb_10ms(void)
{
    /* Condition (transition from state "STB_AC_RLY_ST_MAC" to state "EN_AC_RLY_ST_MAC")  */
    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyA)
    {
        /* Entry (state "EN_AC_RLY_ST_MAC")  */
        stAcRlyLoc.uiCntrEn = 0U;
        stAcRlyLoc.stPrmExt.uiCmpPwm = PRD_AC_RLY_PWM;
        /* Switch to state "EN_AC_RLY_ST_MAC"  */
        stAcRlyLoc.stPrmExt.uiStMac = EN_AC_RLY_ST_MAC;
    }
    /* Static (state "D2D_ST_MAC_STB") */
    else
    {
        stAcRlyLoc.stPrmExt.uiCmpPwm = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: AC relay control state machine enable state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_AcRly_StMacEn_10ms(void)
{
    /* Condition (transition from state "EN_AC_RLY_ST_MAC" to state "D2D_ST_MAC_STB")  */
    if(0U == stPfcStMac.unGPIOCmd.bit.uiRlyA)
    {
        /* Entry (state "STB_AC_RLY_ST_MAC") */
        stAcRlyLoc.uiCntrEn          = 0U;
        stAcRlyLoc.stPrmExt.uiCmpPwm = 0U;
        /* Switch to state "STB_AC_RLY_ST_MAC" */
        stAcRlyLoc.stPrmExt.uiStMac  = STB_AC_RLY_ST_MAC;
    }
    /* Static (state "EN_AC_RLY_ST_MAC") */
    else
    {
        /* Static (state "D2D_ST_MAC_STB") */
        stAcRlyLoc.stPrmExt.uiCmpPwm = PRD_AC_RLY_PWM;
        if(PWM_MOD_AC_RLY == stComTbl.stPrmPerphCtrl.uiModAcRly)    ///< PWM mode
        {
            /* Condition (transition from state "EN_AC_RLY_ST_MAC" to state "PWM_AC_RLY_ST_MAC")  */
            stAcRlyLoc.uiCntrEn++;
            if(stAcRlyLoc.uiCntrEn > DURN_ACRLY_EN_ST)
            {
                /* Entry (state "PWM_AC_RLY_ST_MAC")  */
                stAcRlyLoc.uiCntrEn = 0U;
                /* Switch to state "PWM_AC_RLY_ST_MAC"  */
                stAcRlyLoc.stPrmExt.uiStMac = PWM_AC_RLY_ST_MAC;
            }
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: AC relay control state machine PWM state
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_AcRly_StMacPwm_10ms(void)
{
    float32 l_ftCmpPwm = 0.0f;
    int16 l_siCmpDelta = 0;

    /* Condition (transition from state "PWM_AC_RLY_ST_MAC" to state "D2D_ST_MAC_STB")  */
    if(0U == stPfcStMac.unGPIOCmd.bit.uiRlyA)
    {
        /* Entry (state "STB_AC_RLY_ST_MAC") */
        stAcRlyLoc.stPrmExt.uiCmpPwm = 0U;
        /* Switch to state "STB_AC_RLY_ST_MAC" */
        stAcRlyLoc.stPrmExt.uiStMac  = STB_AC_RLY_ST_MAC;
    }
    /* Condition (transition from state "PWM_AC_RLY_ST_MAC" to state "EN_AC_RLY_ST_MAC")  */
    else if(LEVEL_MOD_AC_RLY == stComTbl.stPrmPerphCtrl.uiModAcRly)    ///< Level mode
    {
        /* Entry (state "EN_AC_RLY_ST_MAC")  */
        stAcRlyLoc.stPrmExt.uiCmpPwm = PRD_AC_RLY_PWM;
        /* Switch to state "EN_AC_RLY_ST_MAC"  */
        stAcRlyLoc.stPrmExt.uiStMac = EN_AC_RLY_ST_MAC;
    }
    /* Static (state "PWM_AC_RLY_ST_MAC") */
    else        ///< PWM mode
    {
        l_ftCmpPwm = stComTbl.stPrmPerphCtrl.ftDutyAcRlyPwm * (float32)PRD_AC_RLY_PWM;
        l_siCmpDelta = (int16)stAcRlyLoc.stPrmExt.uiCmpPwm - (int16)l_ftCmpPwm;
        if(l_siCmpDelta < -10)
        {
            stAcRlyLoc.stPrmExt.uiCmpPwm += 10U;
        }
        else if(l_siCmpDelta > 10)
        {
            stAcRlyLoc.stPrmExt.uiCmpPwm -= 10U;
        }
        else
        {
            stAcRlyLoc.stPrmExt.uiCmpPwm = (Uint16)(int16)l_ftCmpPwm;
        }
    }
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
