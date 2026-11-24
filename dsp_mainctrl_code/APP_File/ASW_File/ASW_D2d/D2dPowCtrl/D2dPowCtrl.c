//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowCtrl.c
 * @brief
 * Source file of D2d power control.
 *
 * Module      :                       \n
 * D2dPowCtrl                          \n
 *
 * Module Task :                       \n
 * v_D2dPowCtrl_Init()                 \n
 * v_D2dPowCtrl_1ms()                  \n
 * v_D2dPowCtrl_PRPrmUpd()             \n
 * v_D2dPowCtrl_FctPwm()               \n
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
#include "D2dPowCtrl.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_D2D_POW_CTRL stD2dPowCtrl;

#if (1U == D2D_POW_CTRL_DBG)
ST_D2D_POW_CTRL stD2dPowCtrlDbg;
#endif

static ST_D2D_POW_CTRL_LOC stD2dPowCtrlLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/***********************************************************************************************
* @Type         : Module function
* @brief        : D2D power control initial task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_D2dPowCtrl_Init(void)
{
    /* Local Signal*/
    stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell = CELL_D2D_MOD_POWER_OFF;
    stD2dPowCtrlLoc.stPrmExt.ftD2dPwmDeadTimePowCell   = 19.0f;
    stD2dPowCtrlLoc.stPrmExt.ftD2dPwmPeriodPowCell     = 900.0f;
    stD2dPowCtrlLoc.stPrmExt.ftD2dPwmValDutyPowCell    = 450.0f;

    /* Global Signal*/
#if (1U == D2D_POW_CTRL_DBG)
    stD2dPowCtrl.uiRunModPowCell         = stD2dPowCtrlDbg.uiRunModPowCell;
    stD2dPowCtrl.ftD2dPwmDeadTimePowCell = stD2dPowCtrlDbg.uiD2dPwmDeadTimePowCell;
    stD2dPowCtrl.ftD2dPwmPeriodPowCell   = stD2dPowCtrlDbg.ftD2dPwmPeriodPowCell ;
    stD2dPowCtrl.ftD2dPwmValDutyPowCell  = stD2dPowCtrlDbg.ftD2dPwmValDutyPowCell;
#else
    stD2dPowCtrl.uiRunModPowCell         = stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell;
    stD2dPowCtrl.ftD2dPwmDeadTimePowCell = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmDeadTimePowCell;
    stD2dPowCtrl.ftD2dPwmPeriodPowCell   = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmPeriodPowCell ;
    stD2dPowCtrl.ftD2dPwmValDutyPowCell  = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmValDutyPowCell;
#endif
#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_D2dPowCtrl_Init() is running****\r\n");
#endif

}

/**
* @brief       D2D power control in ISR
* @param [in]  null
* @param [out] null
* @return null
*/
void v_D2dPowCtrl_Isr(void)
{


#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr) 
    {
        printf("****SWIT DynamicTest: function v_D2dPowCtrl_Isr() is running****\r\n");
    }
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_D2dPowCtrl_1ms(void)
{
    v_D2dPowCtrl_PrmUpd_1ms();
    v_D2dPowCtrl_Mod_1ms();
#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_D2dPowCtrl_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowCtrl_Mod_1ms(void)
{
    if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)
    {
        if(1U == stComIf.uiFlgFltRst) ///< clear fault
        {
            stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell = CELL_D2D_MOD_CMD_CLEAR_SYS_FAULT;
        }
        else
        {
            stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell = CELL_D2D_MOD_POWER_OFF;
        }
    }
    else if(D2D_ST_MAC_SOFTSTRT == stD2dStMac.uiStD2dRun)
    {
        stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell = CELL_D2D_MOD_SYNC;
    }
    else
    {
        stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell = CELL_D2D_MOD_SYNC; ///< To be Modified
    }
    /* Output Signal*/
#if (1U == D2D_POW_CTRL_DBG)
    stD2dPowCtrl.uiRunModPowCell = stD2dPowCtrlDbg.uiRunModPowCell;
#else
    stD2dPowCtrl.uiRunModPowCell = stD2dPowCtrlLoc.stPrmExt.uiRunModPowCell;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_D2dPowCtrl_PrmUpd_1ms(void)
{
    if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)
    {
        stD2dPowCtrlLoc.stPrmExt.ftD2dPwmDeadTimePowCell   = stComTbl.stPrmToFpga.ftD2dPwmDeadTimePowCell;
        stD2dPowCtrlLoc.stPrmExt.ftD2dPwmPeriodPowCell     = stComTbl.stPrmToFpga.ftD2dPwmPeriodPowCell;
        stD2dPowCtrlLoc.stPrmExt.ftD2dPwmValDutyPowCell    = 0.0f;
    }
    else
    {
        stD2dPowCtrlLoc.stPrmExt.ftD2dPwmValDutyPowCell    = stD2dPowPreCtrl.ftOutpPwmDuty * stComTbl.stPrmToFpga.ftD2dPwmPeriodPowCell * 0.5f;///< do nothing
    }
    /* Output Signal*/
#if (1U == D2D_POW_CTRL_DBG)
    stD2dPowCtrl.ftD2dPwmDeadTimePowCell = stD2dPowCtrlDbg.ftD2dPwmDeadTimePowCell;
    stD2dPowCtrl.ftD2dPwmPeriodPowCell   = stD2dPowCtrlDbg.ftD2dPwmPeriodPowCell ;
    stD2dPowCtrl.ftD2dPwmValDutyPowCell  = stD2dPowCtrlDbg.ftD2dPwmValDutyPowCell;
#else
    stD2dPowCtrl.ftD2dPwmDeadTimePowCell = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmDeadTimePowCell;
    stD2dPowCtrl.ftD2dPwmPeriodPowCell   = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmPeriodPowCell ;
    stD2dPowCtrl.ftD2dPwmValDutyPowCell  = stD2dPowCtrlLoc.stPrmExt.ftD2dPwmValDutyPowCell;
#endif
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
