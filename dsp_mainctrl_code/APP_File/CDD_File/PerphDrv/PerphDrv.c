//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphDrv.c
 * @brief
 * Source file of Perph drive.
 *
 * Module      :                       \n
 * PerphDrv
 *
 * Module Task :                       \n
 * v_PerphDrv_Init()                   \n
 * v_PerphDrv_Isr()                    \n
 * v_PerphDrv_1ms()                    \n
 * v_PerphDrv_10ms()                   \n
 * v_PerphDrv_100ms()                  \n
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
#include "PerphDrv.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
#if(2U == GRID_PHASE_NUMBER)
static ST_PERPH_DRV_LOC stPerphDrvLoc;       ///< PerphDrv local struct
#endif

//==============================================================================================
//    Function definition
//==============================================================================================

/***********************************************************************************************
* @Type         : Module function
* @brief        : Peripheral drive initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PerphDrv_Init(void)
{
#ifndef SST_1250kW
    v_PerphDrv_AcRly_Init();                ///< AC relay drive initialization task
    v_PerphDrv_SPRly_Init();                ///< Series parallel relay drive initialization task
    v_PerphDrv_Bld_Init();                  ///< Bleeder resister drive initialization task
    v_PerphDrv_V2LAuxPow_Init();            ///< Bleeder resister drive initialization task
#endif

	v_PerphDrv_Led_Init();                  ///< Led drive initialization task

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PerphDrv_Init() is running****\r\n");
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Peripheral drive 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PerphDrv_1ms(void)
{
	v_PerphDrv_Bld(); ///< sst no use
    v_PerphDrv_V2LAuxPow(); ///< sst no use
#if(1U != GRID_PHASE_NUMBER)
	v_PerphDrv_AcRly();
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PerphDrv_1ms() is running****\r\n");
    }
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Peripheral drive 10ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PerphDrv_10ms(void)
{
#if(1U == GRID_PHASE_NUMBER)
    v_PerphDrv_AcRly();
#endif

#ifndef SST_1250kW
	v_PerphDrv_SPRly();
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_PerphDrv_10ms() is running****\r\n");
    }
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Peripheral drive 100ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PerphDrv_100ms(void)
{
	v_PerphDrv_Led();
	
#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_PerphDrv_100ms() is running****\r\n");
    }
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : AC relay drive initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#ifndef SST_1250kW
static void v_PerphDrv_AcRly_Init(void)
{
#if(1U == GRID_PHASE_NUMBER)
    PFC_RELAY_PWM.CMPA.bit.CMPA = 0U;   ///< Turn off pfc_Relay Pwm
#else
    PFC_RELAY_A_OFF;
    PFC_RELAY_B_OFF;
    PFC_RELAY_C_OFF;
    PFC_RELAY_N_OFF;
    AUXPOWER12V_OFF;
#endif

#if(2U == GRID_PHASE_NUMBER)
    stPerphDrvLoc.uiCntrRlyOn = 0U;
#endif
}
#endif
/***********************************************************************************************
* @Type         : Module function
* @brief        : Series parallel relay drive initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#ifndef SST_1250kW
static void v_PerphDrv_SPRly_Init(void)
{
    SP_RLY_SER_OFF;     ///< Turn off Output Series Relay
    SP_RLY_PARA_OFF;    ///< Turn off Output Parallel Relay
}
#endif
/***********************************************************************************************
* @Type         : Module function
* @brief        : Unit function: V2L Aux power in initial task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#ifndef SST_1250kW
static void v_PerphDrv_V2LAuxPow_Init(void)
{
    V2L_AUX_POW_OFF;        ///< Turn off 12 to 1000V
}
#endif
/***********************************************************************************************
* @Type         : Module function
* @brief        : Bleeder resister drive initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#ifndef SST_1250kW
static void v_PerphDrv_Bld_Init(void)
{
	D2D_BLEED_RES_OFF;        ///< Turn off Output Bleed Resistor
}
#endif
/***********************************************************************************************
* @Type         : Module function
* @brief        : Led drive initialization task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_Led_Init(void)
{
    DSP_RUN_LED_ON;        ///< DSP Run Status LED initialization
    DSP_FAULT_LED_OFF;     ///< DSP Fault State LED initialization
#ifndef SST_1250kW
	D2D_RUN_STS_LED_ON;    ///< D2D Run Status LED initialization
	PFC_RUN_STS_LED_ON;    ///< PFC Run Status LED initialization
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : AC relay drive
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#if(2U == GRID_PHASE_NUMBER)
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_PerphDrv_Isr, ".TI.ramfunc");
#endif
void v_PerphDrv_Isr(void)
{
    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyA)
    {
        if(stPerphDrvLoc.uiCntrRlyOn++ < 5000U)
        {
            PFC_RELAY_A_ON;            ///< Keep normally open
        }
        else
        {
            stPerphDrvLoc.uiCntrRlyOn = 5001U;
            PFC_RELAY_A_PWM;           ///< PWM Mode
        }

    }
    else
    {
        stPerphDrvLoc.uiCntrRlyOn = 0U;
        PFC_RELAY_A_OFF;               ///< close
    }
}
#endif

/***********************************************************************************************
* @Type         : Module function
* @brief        : AC relay drive
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_AcRly(void)
{
#ifndef   SST_1250kW
#if(1U == GRID_PHASE_NUMBER)
    PFC_RELAY_PWM.CMPA.bit.CMPA = stPerphCtrl.stAcRly.uiCmpPwm;   ///< 7.4kW PFC relay pwm control
#else
    #if(3U == GRID_PHASE_NUMBER)
    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyA)   ///< Phase A relay IO signal set
    {
        PFC_RELAY_A_ON;
    }
    else
    {
        PFC_RELAY_A_OFF;
    }

    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyB)   ///< Phase B relay IO signal set
    {
        PFC_RELAY_B_ON;
    }
    else
    {
        PFC_RELAY_B_OFF;
    }

    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyC)   ///< Phase C relay IO signal set
    {
        PFC_RELAY_C_ON;
    }
    else
    {
        PFC_RELAY_C_OFF;
    }

    if(1U == stPfcStMac.unGPIOCmd.bit.uiRlyN)   ///< Phase N relay IO signal set
    {
        PFC_RELAY_N_ON;
    }
    else
    {
        PFC_RELAY_N_OFF;
    }

    if(1U == stPfcDiag.uiCmdRstHW)   ///< Hardware fault reset IO signal
    {
        PFC_HW_FLT_RESET_EN;
    }
    else
    {
        PFC_HW_FLT_RESET_DS;
    }
    #endif
    if(((1U == stPfcStMac.unGPIOCmd.bit.uiAuxRly) && (FCN_DISABLE == stComIf.uiFlgPfcTz)) || (FCN_ENABLE == stCom.unCmdFct.bit.uiEnaAuxPwr))
    {
#if(2U == GRID_PHASE_NUMBER)
        if(GET_HWVERS_VAL == HWVERS_04)
        {
            AUXPOWER12V_ON_B;                ///< B sample Bus auxiliary power enable
        }
        else
        {
            AUXPOWER12V_ON;                  ///< Bus auxiliary power enable
        }
#else
     	AUXPOWER12V_ON;	                     ///< Bus auxiliary power enable
#endif
    }
    else
    {
#if(2U == GRID_PHASE_NUMBER)
        if(GET_HWVERS_VAL == HWVERS_04)
        {
            AUXPOWER12V_OFF_B;               ///< B sample Bus auxiliary power disable
        }
        else
        {
            AUXPOWER12V_OFF;                 ///< Bus auxiliary power disable
        }
#else
     	AUXPOWER12V_OFF;                     ///< Bus auxiliary power disable
#endif
    }
#endif
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Series parallel relay drive
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_SPRly(void)
{
#ifndef SST_1250kW
	if(SP_RLY_PARL_ST == stPerphCtrl.stSPRly.uiCmd)
	{
        SP_RLY_SER_OFF;     ///< Turn off Output Series Relay
        SP_RLY_PARA_ON;     ///< Turn on Output Parallel Relay
	}
	else if(SP_RLY_SERIES_ST == stPerphCtrl.stSPRly.uiCmd)
	{
        SP_RLY_PARA_OFF;    ///< Turn off Output Parallel Relay
        SP_RLY_SER_ON;      ///< Turn on Output Series Relay
	}
	else
	{
        SP_RLY_SER_OFF;     ///< Turn off Output Series Relay
        SP_RLY_PARA_OFF;    ///< Turn off Output Parallel Relay
	}
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : V2 Aux Pow
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_V2LAuxPow(void)
{
#ifndef SST_1250kW
	if((FCN_DISABLE == stPerphCtrl.stV2LAuxPow.uiCmd) && (FCN_DISABLE == stCom.unCmdFct.bit.uiEnaV2L))
	{
	    V2L_AUX_POW_OFF;          ///< Turn off 12 to 1000V
	}
	else
	{
	    V2L_AUX_POW_ON;           ///< Turn on 12 to 1000V
	}
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Bleeder resister drive
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_Bld(void)
{
#ifndef SST_1250kW
	if((FCN_DISABLE == stPerphCtrl.stBld.uiCmd) && (FCN_DISABLE == stCom.unCmdFct.bit.uiEnaBld))
	{
		D2D_BLEED_RES_OFF;        ///< Turn off Output Bleed Resistor
	}
	else
	{
		D2D_BLEED_RES_ON;         ///< Turn on Output Bleed Resistor
	}
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Led drive
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PerphDrv_Led(void)
{
    /* DSP Run LED */
    if(1U == stPerphCtrl.stLed.uiCmdDspRun)
    {
        DSP_RUN_LED_ON;         ///< Turn on DSP Run LED
    //    WATCHDAG_ON;
    }
    else
    {
        DSP_RUN_LED_OFF;        ///< Turn off DSP Run LED
   //     WATCHDAG_OFF;
    }
#ifndef SST_1250kW
    /* PFC Run Status LED */
    if(1U == stPerphCtrl.stLed.uiCmdPfcRunSt)
    {
        PFC_RUN_STS_LED_ON;     ///< Turn on PFC Run Status LED
    }
    else
    {
        PFC_RUN_STS_LED_OFF;    ///< Turn off PFC Run Status LED
    }

    /* D2D Run Status LED */
	if(1U == stPerphCtrl.stLed.uiCmdD2dRunSt)
	{
		D2D_RUN_STS_LED_ON;     ///< Turn on D2D Run Status LED
	}
	else
	{
		D2D_RUN_STS_LED_OFF;    ///< Turn off D2D Run Status LED
	}
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
