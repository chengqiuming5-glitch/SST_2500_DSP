//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_SPRly.c
 * @brief
 * The source file of SP relay control is designed to realize SP relay function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_SPRly_Init()            \n
 * v_PerphCtrl_SPRly_10ms()            \n
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
#include "PerphCtrl_SPRly.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_SPRLY_LOC stSPRlyLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: SP Relay control in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_SPRly_Init(void)
{
    /* Local Signal*/
	stSPRlyLoc.stPrmExt.uiCmd   = SP_RLY_NC_ST;
	stSPRlyLoc.stPrmExt.uiSt    = SP_RLY_NC_ST;
	stSPRlyLoc.stPrmExt.uiFlgOk = 0U;
	stSPRlyLoc.uiCmdSPRly       = SP_RLY_SERIES_ST;
	stSPRlyLoc.uiCntrParlRly    = 0U;
	stSPRlyLoc.uiCntrSeriesRly  = 0U;
	stSPRlyLoc.uiCntrSPRlySwt   = 0U;

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrlDbg.stSPRly.uiCmd   = stSPRlyLoc.stPrmExt.uiCmd;
	stPerphCtrlDbg.stSPRly.uiSt    = stSPRlyLoc.stPrmExt.uiSt;
	stPerphCtrlDbg.stSPRly.uiFlgOk = stSPRlyLoc.stPrmExt.uiFlgOk;

	stPerphCtrl.stSPRly.uiCmd   = stPerphCtrlDbg.stSPRly.uiCmd;
	stPerphCtrl.stSPRly.uiSt    = stPerphCtrlDbg.stSPRly.uiSt;
	stPerphCtrl.stSPRly.uiFlgOk = stPerphCtrlDbg.stSPRly.uiFlgOk;
#else
	stPerphCtrl.stSPRly.uiCmd   = stSPRlyLoc.stPrmExt.uiCmd;
	stPerphCtrl.stSPRly.uiSt    = stSPRlyLoc.stPrmExt.uiSt;
	stPerphCtrl.stSPRly.uiFlgOk = stSPRlyLoc.stPrmExt.uiFlgOk;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: SP Relay control in 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_SPRly_10ms(void)
{
    if(1U == stComIf.uiFlgPowOn)    // Control Power On
    {
        /* Relay command state update*/
    	v_PerphCtrl_SPRly_Cmd_10ms();

        /* Relay control */
    	v_PerphCtrl_SPRly_Ctrl_10ms();
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
	stPerphCtrl.stSPRly.uiCmd   = stPerphCtrlDbg.stSPRly.uiCmd;
    stPerphCtrl.stSPRly.uiSt    = stPerphCtrlDbg.stSPRly.uiSt;
    stPerphCtrl.stSPRly.uiFlgOk = stPerphCtrlDbg.stSPRly.uiFlgOk;
#else
	stPerphCtrl.stSPRly.uiCmd   = stSPRlyLoc.stPrmExt.uiCmd;
	stPerphCtrl.stSPRly.uiSt    = stSPRlyLoc.stPrmExt.uiSt;
	stPerphCtrl.stSPRly.uiFlgOk = stSPRlyLoc.stPrmExt.uiFlgOk;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Command of SP Relay control
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_SPRly_Cmd_10ms(void)
{
	float32 l_ftVoltMax = 0.0f;

#ifndef _SIMULATION_NO_DSP_

#if 0U == SP_SWITCH_MODE
	if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)    // Fault or Standby Status
	{
		if(stComIf.ftVoltBattChrgReq > VOLT_BATT_PARL_MAX)    // The maximum charging voltage is greater than Parallel Nominal Voltage
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
		}
		else
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // Parallel Command
		}
	}
	#if 1U == SP_SWITCH_ON_RUN_EN
	else if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_NORMRUN)    // Running Status
	{
		if(stComIf.ftVoltBattBms < VOLT_BATT_SERIES_MIN)    // The Battery Voltage is less than series Min Voltage
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // Parallel Command
		}
		else if(stComIf.ftVoltBattBms > VOLT_BATT_PARL_MAX)    // The Battery Voltage is greater than Parallel Max Voltage
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
		}
		else
		{
			// None Code
		}
	}
	else
	{
		// None Code
	}
	#endif
#elif 1U == SP_SWITCH_MODE
	l_ftVoltMax = ftFcn_MaxOfTwo(stComIf.ftVoltBattBmsMax, stComIf.ftVoltBattChrgReq);

	if(INS_DET_ST_IS_ON)    ///< Insulation status
	{
		if(l_ftVoltMax <= VOLT_BATT_PARL_MAX)    // The maximum voltage is less than Parallel Nominal Voltage
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // Parallel Command
		}
		else
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
		}
	}
	else
	{
		if(stD2dStMac.uiStD2dRun < D2D_ST_MAC_NORMRUN)    // Running Status
		{
			if((l_ftVoltMax <= VOLT_BATT_PARL_MAX) || (stComIf.ftVoltBattBms < SP_RLY_SER_SWITCH_VOLT))    // The maximum voltage is less than Parallel Nominal Voltage || the battery voltage is less than 410V
			{
				stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // PARA Command
			}
			else
			{
				stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
			}
		}
	#if 1U == SP_SWITCH_ON_RUN_EN
		else
		{
			if((SP_RLY_PARL_ST == stSPRlyLoc.stPrmExt.uiSt) && (stComIf.ftVoltBattBms > VOLT_BATT_PARL_MAX))    // PARA status && battery voltage is more than PARA_VOLT_MAX
			{
				stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
			}
			else if((SP_RLY_SERIES_ST == stSPRlyLoc.stPrmExt.uiSt) && (stComIf.ftVoltBattBms < VOLT_BATT_SERIES_MIN))    // Series status && battery voltage is less than SER_VOLT_MIN
			{
				stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // PARA Command
			}
			else
			{
				// No code
			}
		}
    #endif
	}
#elif 2U == SP_SWITCH_MODE
	l_ftVoltMax = ftFcn_MaxOfTwo(stComIf.ftVoltBattBmsMax, stComIf.ftVoltBattChrgReq);

	if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)    // Fault or Standby Status
	{
		if(l_ftVoltMax > VOLT_BATT_PARL_MAX)    // The maximum charging voltage is greater than Parallel Nominal Voltage
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_SERIES_ST;    // Series Command
		}
		else
		{
			stSPRlyLoc.uiCmdSPRly = SP_RLY_PARL_ST;    // Parallel Command
		}
	}
#endif

#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Control of SP Relay control
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_SPRly_Ctrl_10ms(void)
{
    if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)    ///< Fault or Standby Status
    {
        if(0U == stSPRlyLoc.stPrmExt.uiFlgOk)      ///< Operation incomplete
        {
            v_PerphCtrl_SPRly_StSwt_10ms();
        }
        else    ///< Operation completed
        {
            if(stSPRlyLoc.uiCmdSPRly != stSPRlyLoc.stPrmExt.uiSt)    ///< Commands is inconsistent with the Status
            {
                stSPRlyLoc.uiCntrSPRlySwt++;
                if(stSPRlyLoc.uiCntrSPRlySwt > DURN_SP_RLY_SWT)
                {
                    stSPRlyLoc.stPrmExt.uiFlgOk = 0U;
                }
            }
            else
            {
                stSPRlyLoc.uiCntrSPRlySwt = 0U;
            }
        }
    }
    else
    {
        stSPRlyLoc.uiCntrSPRlySwt = 0U;    ///< Clear counter
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: State switch of SP Relay control
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_SPRly_StSwt_10ms(void)
{
    /* Relay Action */
    if((stD2dAdc.ftVoltBattLpf10Hz < VOLT_BATT_SP_RLY_ON) && (stD2dAdc.ftVoltBattDwnLpf10Hz < VOLT_BATT_SP_RLY_ON))
    {
        if(SP_RLY_PARL_ST == stSPRlyLoc.uiCmdSPRly)        // Command is Parallel
        {
        	stSPRlyLoc.stPrmExt.uiCmd = SP_RLY_PARL_ST;

            stSPRlyLoc.uiCntrSeriesRly = 0U;    // Clear Series Counter
            stSPRlyLoc.uiCntrParlRly++;         // Add Parallel Counter
        }
        else if(SP_RLY_SERIES_ST == stSPRlyLoc.uiCmdSPRly)    // Command is Series
        {
        	stSPRlyLoc.stPrmExt.uiCmd = SP_RLY_SERIES_ST;

            stSPRlyLoc.uiCntrParlRly = 0U;    // Clear Parallel Counter
            stSPRlyLoc.uiCntrSeriesRly++;     // Add Series Counter
        }
        else
        {
            // None Code
        }

        if((stSPRlyLoc.uiCntrParlRly > DURN_SP_RLY_ON) || (stSPRlyLoc.uiCntrSeriesRly > DURN_SP_RLY_ON))
        {
		#ifndef _SIMULATION_NO_DSP_
        	stSPRlyLoc.stPrmExt.uiCmd = SP_RLY_NC_ST;
		#endif
            stSPRlyLoc.uiCntrSeriesRly  = 0U;      // Clear Series Counter
            stSPRlyLoc.uiCntrParlRly    = 0U;      // Clear Parallel Counter
            stSPRlyLoc.stPrmExt.uiSt    = stSPRlyLoc.uiCmdSPRly;
            stSPRlyLoc.stPrmExt.uiFlgOk = 1U;

            v_PerphCtrl_SPRly_PrmUpd();
        }
    }
    else
    {
    	stSPRlyLoc.uiCntrSeriesRly = 0U;    // Clear Series Counter
        stSPRlyLoc.uiCntrParlRly   = 0U;    // Clear Parallel Counter
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: SP relay related parameter update
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_SPRly_PrmUpd(void)
{
    if(SP_RLY_PARL_ST == stSPRlyLoc.stPrmExt.uiSt)    ///< Parallel status parameter
    {
#ifndef _SIMULATION_NO_DSP_
        OUT_CURR_CMPSS_REG.DACHVALS.bit.DACVAL = (Uint16)CMPSS_OUTPARA_CURR_POS;    ///< Positive current protection value
        OUT_CURR_CMPSS_REG.DACLVALS.bit.DACVAL = (Uint16)CMPSS_OUTPARA_CURR_NEG;    ///< Negative current protection value

        v_Com_ParlPrmUpd();
#endif
        v_D2dPowPreCtrl_ParlPrmUpd();
    }
    else    ///< Series status parameter
    {
#ifndef _SIMULATION_NO_DSP_
        OUT_CURR_CMPSS_REG.DACHVALS.bit.DACVAL = (Uint16)CMPSS_OUTSER_CURR_POS;    ///< Positive current protection value
        OUT_CURR_CMPSS_REG.DACLVALS.bit.DACVAL = (Uint16)CMPSS_OUTSER_CURR_NEG;    ///< Negative current protection value

        v_Com_SeriesPrmUpd();
#endif
        v_D2dPowPreCtrl_SeriesPrmUpd();
    }
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
