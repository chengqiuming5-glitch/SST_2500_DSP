//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_V2LAuxPow.c
 * @brief
 * The source file of V2L Aux power is designed to realize V2L Aux power control.
 *
 * Unit        :                       \n
 * V2LAuxPow                           \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_V2LAuxPow_Init()        \n
 * v_PerphCtrl_V2LAuxPow_1ms()         \n
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
#include "PerphCtrl_V2LAuxPow.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_V2L_AUX_POW_LOC stV2LAuxPowLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: V2L Aux power control in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_V2LAuxPow_Init(void)
{
    /* Local Signal*/
    stV2LAuxPowLoc.stPrmExt.uiCmd       = FCN_DISABLE;
	stV2LAuxPowLoc.stPrmExt.uiFlgEn     = 0U;

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrlDbg.stV2LAuxPow.uiCmd       = stV2LAuxPowLoc.stPrmExt.uiCmd;
	stPerphCtrlDbg.stV2LAuxPow.uiFlgEn     = stV2LAuxPowLoc.stPrmExt.uiFlgEn;

	stPerphCtrl.stV2LAuxPow.uiCmd          = stPerphCtrlDbg.stV2LAuxPow.uiCmd;
	stPerphCtrl.stV2LAuxPow.uiFlgEn        = stPerphCtrlDbg.stV2LAuxPow.uiFlgEn;
#else
	stPerphCtrl.stV2LAuxPow.uiCmd          = stV2LAuxPowLoc.stPrmExt.uiCmd;
	stPerphCtrl.stV2LAuxPow.uiFlgEn        = stV2LAuxPowLoc.stPrmExt.uiFlgEn;
#endif
}

/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: V2L Aux power control in 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_V2LAuxPow_1ms(void)
{
    float32 l_ftVoltMax = 0.0f;

    l_ftVoltMax = ftFcn_MaxOfTwo(stComIf.ftVoltBattBmsMax, stComIf.ftVoltBattChrgReq);
    if((1U == stComIf.uiCmdV2LAuxPow) && (D2D_ST_MAC_STB == stD2dStMac.uiStD2dRun))
    {
        if(((l_ftVoltMax > VOLT_BATT_PARL_MAX) && (SP_RLY_SERIES_ST == stPerphCtrl.stSPRly.uiSt)) || \
           ((l_ftVoltMax <= VOLT_BATT_PARL_MAX) && (SP_RLY_PARL_ST  == stPerphCtrl.stSPRly.uiSt)) )
        {
            if(stD2dAdc.ftVoltBattLpf5kHz < (stComIf.ftVoltBattChrgReq - 1.0f))
            {
                stV2LAuxPowLoc.stPrmExt.uiCmd = FCN_ENABLE;
            }
            else if(stD2dAdc.ftVoltBattLpf5kHz > (stComIf.ftVoltBattChrgReq + 1.0f))
            {
                stV2LAuxPowLoc.stPrmExt.uiCmd = FCN_DISABLE;
            }
            else
            {
                //No code
            }
        }
        else
        {
            stV2LAuxPowLoc.stPrmExt.uiCmd = FCN_DISABLE;
        }
        stV2LAuxPowLoc.stPrmExt.uiFlgEn = 1U;
    }
    else
    {
        stV2LAuxPowLoc.stPrmExt.uiCmd = FCN_DISABLE;
        stV2LAuxPowLoc.stPrmExt.uiFlgEn = 0U;
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrl.stV2LAuxPow.uiCmd          = stPerphCtrlDbg.stV2LAuxPow.uiCmd;
    stPerphCtrl.stV2LAuxPow.uiFlgEn        = stPerphCtrlDbg.stV2LAuxPow.uiFlgEn;
#else
    stPerphCtrl.stV2LAuxPow.uiCmd          = stV2LAuxPowLoc.stPrmExt.uiCmd;
    stPerphCtrl.stV2LAuxPow.uiFlgEn        = stV2LAuxPowLoc.stPrmExt.uiFlgEn;
#endif
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
