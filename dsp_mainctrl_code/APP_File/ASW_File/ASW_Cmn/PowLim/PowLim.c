//==============================================================================================
//    File description
//==============================================================================================
/**@file         PowLim.c
 * @brief
 * The source file of power limitation is designed to realize peripheral function.
 *
 * Module      :                       \n
 * PowLim
 *
 * Unit        :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 *
 * Module Task :                       \n
 * v_PowLim_Init()                     \n
 * v_PowLim_1ms()                      \n
 * v_PowLim_10ms()                     \n
 * v_PowLim_100ms()                    \n
 *
 * Unit Task   :                       \n
 * v_PowLim_BattVolt_1ms()             \n
 * v_PowLim_Curr_1ms()                 \n
 * v_PowLim_BusVolt_1ms()              \n
 *
 * Unit Task   :                       \n
 * v_PowLim_PowComp_100ms()            \n
 * v_PowLim_Temp_100ms()               \n
 * v_PowLim_HTSt_100ms()               \n
 * v_PowLim_FanDutyCal_100ms()         \n
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
#include "PowLim.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_POW_LIM stPowLim;                  ///< Power limitation global struct

#if (1U == POW_LIM_DBG)
ST_POW_LIM stPowLimDbg;               ///< Power limitation debug global struct
#endif

static ST_POW_LIM_LOC stPowLimLoc;    ///< Power limitation local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Power limitation initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PowLim_Init(void)
{
    /* Local Signal*/
	stPowLimLoc.stPrmExt.ftVoltBattChrgLim       = VOLT_BATT_REQ_MAX;           ///< Charge battery voltage limitation
	stPowLimLoc.stPrmExt.ftCurrBattChrgLim       = CURR_BATT_SERIES_MAX;        ///< Charge battery current limitation
	stPowLimLoc.stPrmExt.ftVoltBusLim            = VOLT_BUS_TGT_MIN;            ///< Bus voltage limitation
    stPowLimLoc.stPrmExt.ftVoltBusAcLim          = VOLT_BUS_TGT_MIN;            ///< Bus voltage Ac limitation
    stPowLimLoc.stPrmExt.ftVoltBusBattLim        = VOLT_BUS_TGT_MIN;            ///< Bus voltage Battery limitation
	stPowLimLoc.stPrmExt.ftPowAcChrgLim          = POW_AC_RTD;                  ///< Charge AC power limitation
	stPowLimLoc.stPrmExt.ftPowAcDchaLim          = POW_AC_RTD;                  ///< Discharge AC power limitation
	stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim    = POW_AC_RTD;                  ///< Battery current charge power limitation
    stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim    = -POW_AC_RTD;                 ///< Battery current discharge power limitation
	stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms  = CURR_BATT_SERIES_MAX;        ///< Max charge battery current to BMS
	stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms  = -CURR_BATT_SERIES_MAX;       ///< Max charge battery current to BMS
	stPowLimLoc.stPrmExt.ftPaAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftPbAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftPcAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftQaAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftQbAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftQcAcLim               = 0.0f;
	stPowLimLoc.stPrmExt.ftVoltAcAmpLim          = RATED_AC_VOLT_RMS * CON_SQRT_2;
	stPowLimLoc.stPrmExt.ftTempMax               = 0.0f;
	stPowLimLoc.stPrmExt.ftTempMin               = 0.0f;
	stPowLimLoc.stPrmExt.ftFanDuty               = 0.0f;
	stPowLimLoc.stPrmExt.ftCoeffTemp             = 1.0f;
	stPowLimLoc.stPrmExt.uiFlgHTLim              = 0U;
	
	stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt       = 1.0f;
	stPowLimLoc.stPrmChrgLim.ftPowAcVolt1P       = POW_AC_1P_RTD;     ///< One phase power limitation according to AC voltage
	stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt     = 1.0f;
	stPowLimLoc.stPrmChrgLim.ftCoeffHT           = 1.0f;
	stPowLimLoc.stPrmChrgLim.ftCoeffLT           = 1.0f;
	stPowLimLoc.stPrmChrgLim.ftCoeffLim          = 1.0f;
	stPowLimLoc.stPrmChrgLim.ftPowBattCurr       = POW_BATT_MAX;            ///< Limit power related to DC current
	stPowLimLoc.stPrmChrgLim.ftPowLim            = POW_BATT_MAX;            ///< Limit power
	stPowLimLoc.stPrmChrgLim.ftCurrBattLim       = CURR_BATT_SERIES_MAX;    ///< Limit battery current
	stPowLimLoc.stPrmChrgLim.ftCurrBattReq       = 0.0f;
	stPowLimLoc.stPrmChrgLim.ftPowAcCurrLim      = POW_BATT_MAX;            ///< AC current limit power
    stPowLimLoc.stPrmChrgLim.ftPowOcppLim        = POW_BATT_MAX;            ///< OCPP limit power
	stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt       = 1.0f;
	stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt     = 1.0f;
	stPowLimLoc.stPrmDchaLim.ftCoeffHT           = 1.0f;
	stPowLimLoc.stPrmDchaLim.ftCoeffLT           = 1.0f;
	stPowLimLoc.stPrmDchaLim.ftCoeffLim          = 1.0f;
	stPowLimLoc.stPrmDchaLim.ftPowBattCurr       = POW_AC_RTD;              ///< Limit power related to DC current
	stPowLimLoc.stPrmDchaLim.ftPowLim            = POW_AC_RTD;              ///< Limit power
	stPowLimLoc.stPrmDchaLim.ftCurrBattLim       = CURR_BATT_SERIES_MAX;    ///< Limit battery current
    stPowLimLoc.stPrmDchaLim.ftCurrBattReq       = 0.0f;
	stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt      = VOLT_BUS_TGT_MIN;        ///< Related to AC voltage
	stPowLimLoc.stPrmBusVoltLim.ftPrmBattVolt    = VOLT_BUS_TGT_MIN;        ///< Related to battery voltage
	stPowLimLoc.ftVoltBattCalc                   = VOLT_BATT_MIN;           ///< Power limitation calculate battery voltage
	stPowLimLoc.ftVoltBattRecpr                  = 1.0f/VOLT_BATT_MIN;      ///< Reciprocal of battery voltage
	stPowLimLoc.ftPowAcChrgMax                   = POW_AC_RTD;              ///< Max AC charge power
    stPowLimLoc.ftPowAcDchaMax                   = POW_AC_RTD;              ///< Max AC discharge power
    stPowLimLoc.ftPaAcReq                        = 0.0f;
    stPowLimLoc.ftPbAcReq                        = 0.0f;
    stPowLimLoc.ftPcAcReq                        = 0.0f;
    stPowLimLoc.ftPAcReq                         = 0.0f;
    stPowLimLoc.ftQaAcReq                        = 0.0f;
    stPowLimLoc.ftQbAcReq                        = 0.0f;
    stPowLimLoc.ftQcAcReq                        = 0.0f;
    stPowLimLoc.ftCoeffPAcReq                    = 1.0f;
    stPowLimLoc.ftFanDutyTgt                     = 0.0f;
    stPowLimLoc.ftNtcTempDiffMax                 = 0.0f;
    stPowLimLoc.ftNtcTempMax                     = 0.0f;
    stPowLimLoc.ftCurrBattDchaMax                = CURR_BATT_MAX_TEMP_DWN_DCHA;
    stPowLimLoc.ftTempMaxFanCtrl                 = 0.0f;
    stPowLimLoc.ftCoeffBattLVLim                 = 1.0f;

    /* Initialize Charge power compensation PI according to battery current */
    vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stAcCurrChrgPI);
    stPowLimLoc.stPowComp.stAcCurrChrgPI.ftKp          = KP_POW_COMP_CURR;
    stPowLimLoc.stPowComp.stAcCurrChrgPI.ftKi          = KI_POW_COMP_CURR;
    stPowLimLoc.stPowComp.stAcCurrChrgPI.ftOutpMax     = MAX_POW_COMP_CHRG;
    stPowLimLoc.stPowComp.stAcCurrChrgPI.ftOutpMin     = MIN_POW_COMP_CHRG;
    /* Initialize Charge power compensation PI according to OCPP power request */
    vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stOcppChrgPI);
    stPowLimLoc.stPowComp.stOcppChrgPI.ftKp            = KP_POW_COMP_POW;
    stPowLimLoc.stPowComp.stOcppChrgPI.ftKi            = KI_POW_COMP_POW;
    stPowLimLoc.stPowComp.stOcppChrgPI.ftOutpMax       = MAX_POW_COMP_CHRG;
    stPowLimLoc.stPowComp.stOcppChrgPI.ftOutpMin       = MIN_POW_COMP_CHRG;
    /* Initialize Charge power compensation PI according to battery current */
    vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stBattCurrChrgPI);
    stPowLimLoc.stPowComp.stBattCurrChrgPI.ftKp        = KP_POW_COMP_CURR;
    stPowLimLoc.stPowComp.stBattCurrChrgPI.ftKi        = KI_POW_COMP_CURR;
    stPowLimLoc.stPowComp.stBattCurrChrgPI.ftOutpMax   = MAX_POW_COMP_CHRG;
    stPowLimLoc.stPowComp.stBattCurrChrgPI.ftOutpMin   = MIN_POW_COMP_CHRG;
    /* Initialize Discharge power compensation PI according to battery current */
    vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stBattCurrDchaPI);
    stPowLimLoc.stPowComp.stBattCurrDchaPI.ftKp        = KP_POW_COMP_CURR;
    stPowLimLoc.stPowComp.stBattCurrDchaPI.ftKi        = KI_POW_COMP_CURR;            ///< Ki of 100ms PI
    stPowLimLoc.stPowComp.stBattCurrDchaPI.ftOutpMax   = MAX_POW_COMP_DCHA;
    stPowLimLoc.stPowComp.stBattCurrDchaPI.ftOutpMin   = MIN_POW_COMP_DCHA;

    /* Initialize Charge temperature limitation parameter */
    stPowLimLoc.stTempChrgPrm.ftTempMax                = 0.0f;
    stPowLimLoc.stTempChrgPrm.ftTempMin                = 0.0f;
    stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt             = 1.0f;
    stPowLimLoc.stTempChrgPrm.ftCoeffHT                = 1.0f;
    stPowLimLoc.stTempChrgPrm.ftCoeffLT                = 1.0f;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftDspCore     = TEMP_CMP_DSP_CORE_CHRG;      ///< DSP CORE temperature compensation
    stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_LV_CHRG;     ///< DSP board temperature compensation
    stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_LV_CHRG;     ///< ARM board temperature compensation
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_LV_CHRG;
    stPowLimLoc.stTempChrgPrm.uiLowTempTim             = 0U;
    stPowLimLoc.stTempChrgPrm.enLowTempSts             = LOW_POW_INIT_STS;
    stPowLimLoc.stTempChrgPrm.uiLowTempCnt             = 0U;
    stPowLimLoc.stTempChrgPrm.uiStHTLim                = WAIT_ST_MAC_HT_PL;
    stPowLimLoc.stTempChrgPrm.uiCntHTEntr              = 0U;
    stPowLimLoc.stTempChrgPrm.uiCntHTExit              = 0U;
    /* Initialize Discharge temperature limitation parameter */
    stPowLimLoc.stTempDchaPrm.ftTempMax                = 0.0f;
    stPowLimLoc.stTempDchaPrm.ftTempMin                = 0.0f;
    stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt             = 1.0f;
    stPowLimLoc.stTempDchaPrm.ftCoeffHT                = 1.0f;
    stPowLimLoc.stTempDchaPrm.ftCoeffLT                = 1.0f;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftDspCore     = TEMP_CMP_DSP_CORE_DCHA;       ///< DSP CORE temperature compensation
    stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_LV_DCHA;      ///< DSP board temperature compensation
    stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_LV_DCHA;      ///< ARM board temperature compensation
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_LV_DCHA;
    stPowLimLoc.stTempDchaPrm.uiLowTempTim             = 0U;
    stPowLimLoc.stTempDchaPrm.enLowTempSts             = LOW_POW_INIT_STS;
    stPowLimLoc.stTempDchaPrm.uiLowTempCnt             = 0U;
    stPowLimLoc.stTempDchaPrm.uiStHTLim                = WAIT_ST_MAC_HT_PL;
    stPowLimLoc.stTempDchaPrm.uiCntHTEntr              = 0U;
    stPowLimLoc.stTempDchaPrm.uiCntHTExit              = 0U;
    /* Initialize AC voltage power limitation parameter */
    stPowLimLoc.ftCoeffChrgAcVoltPL_K                  = COEFF_K_VOLT_AC_PL_CHRG;
    stPowLimLoc.ftCoeffChrgAcVoltPL_B                  = COEFF_B_VOLT_AC_PL_CHRG;
    stPowLimLoc.ftCoeffDchaAcVoltPL_K                  = COEFF_K_VOLT_AC_PL_DCHA;
    stPowLimLoc.ftCoeffDchaAcVoltPL_B                  = COEFF_B_VOLT_AC_PL_DCHA;
    /* Initialize battery voltage power limitation parameter */
    stPowLimLoc.ftCoeffChrgBattVoltPL_K                = 0.0f;
    stPowLimLoc.ftCoeffChrgBattVoltPL_B                = 1.0f;
    stPowLimLoc.ftCoeffDchaBattVoltPL_K                = 0.0f;
    stPowLimLoc.ftCoeffDchaBattVoltPL_B                = 1.0f;
    stPowLimLoc.ftRecprRatAcOvLoad                     = 1.0f;

    /* Global Signal*/
#if (1U == POW_LIM_DBG)
	stPowLimDbg.ftVoltBattChrgLim      = stPowLimLoc.stPrmExt.ftVoltBattChrgLim;
	stPowLimDbg.ftCurrBattChrgLim      = stPowLimLoc.stPrmExt.ftCurrBattChrgLim;
	stPowLimDbg.ftVoltBusLim           = stPowLimLoc.stPrmExt.ftVoltBusLim;
    stPowLimDbg.ftVoltBusAcLim         = stPowLimLoc.stPrmExt.ftVoltBusAcLim;
    stPowLimDbg.ftVoltBusBattLim       = stPowLimLoc.stPrmExt.ftVoltBusBattLim;
	stPowLimDbg.ftPowAcChrgLim         = stPowLimLoc.stPrmExt.ftPowAcChrgLim;
	stPowLimDbg.ftPowAcDchaLim         = stPowLimLoc.stPrmExt.ftPowAcDchaLim;
	stPowLimDbg.ftPowBattCurrChrgLim   = stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim;
	stPowLimDbg.ftPowBattCurrDchaLim   = stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim;
	stPowLimDbg.ftCurrBattChrgMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms;
	stPowLimDbg.ftCurrBattDchaMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms;
	stPowLimDbg.ftPaAcLim              = stPowLimLoc.stPrmExt.ftPaAcLim;
	stPowLimDbg.ftPbAcLim              = stPowLimLoc.stPrmExt.ftPbAcLim;
	stPowLimDbg.ftPcAcLim              = stPowLimLoc.stPrmExt.ftPcAcLim;
	stPowLimDbg.ftQaAcLim              = stPowLimLoc.stPrmExt.ftQaAcLim;
	stPowLimDbg.ftQbAcLim              = stPowLimLoc.stPrmExt.ftQbAcLim;
	stPowLimDbg.ftQcAcLim              = stPowLimLoc.stPrmExt.ftQcAcLim;
	stPowLimDbg.ftVoltAcAmpLim         = stPowLimLoc.stPrmExt.ftVoltAcAmpLim;
	stPowLimDbg.ftTempMax              = stPowLimLoc.stPrmExt.ftTempMax;
	stPowLimDbg.ftTempMin              = stPowLimLoc.stPrmExt.ftTempMin;
	stPowLimDbg.ftFanDuty              = stPowLimLoc.stPrmExt.ftFanDuty;
    stPowLimDbg.ftCoeffTemp            = stPowLimLoc.stPrmExt.ftCoeffTemp;
    stPowLimDbg.uiFlgHTLim             = stPowLimLoc.stPrmExt.uiFlgHTLim;

	stPowLim.ftVoltBattChrgLim      = stPowLimDbg.ftVoltBattChrgLim;
	stPowLim.ftCurrBattChrgLim      = stPowLimDbg.ftCurrBattChrgLim;
	stPowLim.ftVoltBusLim           = stPowLimDbg.ftVoltBusLim;
    stPowLim.ftVoltBusAcLim         = stPowLimDbg.ftVoltBusAcLim;
    stPowLim.ftVoltBusBattLim       = stPowLimDbg.ftVoltBusBattLim;
	stPowLim.ftPowAcChrgLim         = stPowLimDbg.ftPowAcChrgLim;
	stPowLim.ftPowAcDchaLim         = stPowLimDbg.ftPowAcDchaLim;
	stPowLim.ftPowBattCurrChrgLim   = stPowLimDbg.ftPowBattCurrChrgLim;
	stPowLim.ftPowBattCurrDchaLim   = stPowLimDbg.ftPowBattCurrDchaLim;
	stPowLim.ftCurrBattChrgMaxToBms = stPowLimDbg.ftCurrBattChrgMaxToBms;
	stPowLim.ftCurrBattDchaMaxToBms = stPowLimDbg.ftCurrBattDchaMaxToBms;
	stPowLim.ftPaAcLim              = stPowLimDbg.ftPaAcLim;
	stPowLim.ftPbAcLim              = stPowLimDbg.ftPbAcLim;
	stPowLim.ftPcAcLim              = stPowLimDbg.ftPcAcLim;
	stPowLim.ftQaAcLim              = stPowLimDbg.ftQaAcLim;
	stPowLim.ftQbAcLim              = stPowLimDbg.ftQbAcLim;
	stPowLim.ftQcAcLim              = stPowLimDbg.ftQcAcLim;
	stPowLim.ftVoltAcAmpLim         = stPowLimDbg.ftVoltAcAmpLim;
    stPowLim.ftTempMax              = stPowLimDbg.ftTempMax;
    stPowLim.ftTempMin              = stPowLimDbg.ftTempMin;
    stPowLim.ftFanDuty              = stPowLimDbg.ftFanDuty;
    stPowLim.ftCoeffTemp            = stPowLimDbg.ftCoeffTemp;
    stPowLim.uiFlgHTLim             = stPowLimDbg.uiFlgHTLim;
#else
	stPowLim.ftVoltBattChrgLim      = stPowLimLoc.stPrmExt.ftVoltBattChrgLim;
	stPowLim.ftCurrBattChrgLim      = stPowLimLoc.stPrmExt.ftCurrBattChrgLim;
	stPowLim.ftVoltBusLim           = stPowLimLoc.stPrmExt.ftVoltBusLim;
    stPowLim.ftVoltBusAcLim         = stPowLimLoc.stPrmExt.ftVoltBusAcLim;
    stPowLim.ftVoltBusBattLim       = stPowLimLoc.stPrmExt.ftVoltBusBattLim;
	stPowLim.ftPowAcChrgLim         = stPowLimLoc.stPrmExt.ftPowAcChrgLim;
	stPowLim.ftPowAcDchaLim         = stPowLimLoc.stPrmExt.ftPowAcDchaLim;
    stPowLim.ftPowBattCurrChrgLim   = stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim;
    stPowLim.ftPowBattCurrDchaLim   = stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim;
	stPowLim.ftCurrBattChrgMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms;
	stPowLim.ftCurrBattDchaMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms;
	stPowLim.ftPaAcLim              = stPowLimLoc.stPrmExt.ftPaAcLim;
	stPowLim.ftPbAcLim              = stPowLimLoc.stPrmExt.ftPbAcLim;
	stPowLim.ftPcAcLim              = stPowLimLoc.stPrmExt.ftPcAcLim;
	stPowLim.ftQaAcLim              = stPowLimLoc.stPrmExt.ftQaAcLim;
	stPowLim.ftQbAcLim              = stPowLimLoc.stPrmExt.ftQbAcLim;
	stPowLim.ftQcAcLim              = stPowLimLoc.stPrmExt.ftQcAcLim;
	stPowLim.ftVoltAcAmpLim         = stPowLimLoc.stPrmExt.ftVoltAcAmpLim;
	stPowLim.ftTempMax              = stPowLimLoc.stPrmExt.ftTempMax;
	stPowLim.ftTempMin              = stPowLimLoc.stPrmExt.ftTempMin;
	stPowLim.ftFanDuty              = stPowLimLoc.stPrmExt.ftFanDuty;
    stPowLim.ftCoeffTemp            = stPowLimLoc.stPrmExt.ftCoeffTemp;
    stPowLim.uiFlgHTLim             = stPowLimLoc.stPrmExt.uiFlgHTLim;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PowLim_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Power limitation 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PowLim_1ms(void)
{
    /* Batter Voltage limitation */
    v_PowLim_BattVolt_1ms();

    /* Power and current limitation */
    v_PowLim_Curr_1ms();

    /* Bus voltage limitation */
    v_PowLim_BusVolt_1ms();

    /* Off-grid AC voltage limitation */
    stPowLimLoc.stPrmExt.ftVoltAcAmpLim = stCom.ftVoltAcV2LReq * CON_SQRT_2;

    /* Output Signal*/
#if (1U == POW_LIM_DBG)
    stPowLim.ftVoltBattChrgLim      = stPowLimDbg.ftVoltBattChrgLim;
    stPowLim.ftCurrBattChrgLim      = stPowLimDbg.ftCurrBattChrgLim;
    stPowLim.ftVoltBusLim           = stPowLimDbg.ftVoltBusLim;
    stPowLim.ftVoltBusAcLim         = stPowLimDbg.ftVoltBusAcLim;
    stPowLim.ftVoltBusBattLim       = stPowLimDbg.ftVoltBusBattLim;
    stPowLim.ftPowAcChrgLim         = stPowLimDbg.ftPowAcChrgLim;
    stPowLim.ftPowAcDchaLim         = stPowLimDbg.ftPowAcDchaLim;
    stPowLim.ftPowBattCurrChrgLim   = stPowLimDbg.ftPowBattCurrChrgLim;
    stPowLim.ftPowBattCurrDchaLim   = stPowLimDbg.ftPowBattCurrDchaLim;
    stPowLim.ftCurrBattChrgMaxToBms = stPowLimDbg.ftCurrBattChrgMaxToBms;
    stPowLim.ftCurrBattDchaMaxToBms = stPowLimDbg.ftCurrBattDchaMaxToBms;
    stPowLim.ftPaAcLim              = stPowLimDbg.ftPaAcLim;
    stPowLim.ftPbAcLim              = stPowLimDbg.ftPbAcLim;
    stPowLim.ftPcAcLim              = stPowLimDbg.ftPcAcLim;
    stPowLim.ftQaAcLim              = stPowLimDbg.ftQaAcLim;
    stPowLim.ftQbAcLim              = stPowLimDbg.ftQbAcLim;
    stPowLim.ftQcAcLim              = stPowLimDbg.ftQcAcLim;
    stPowLim.ftVoltAcAmpLim         = stPowLimDbg.ftVoltAcAmpLim;
    stPowLim.ftCoeffTemp            = stPowLimDbg.ftCoeffTemp;
#else
    stPowLim.ftVoltBattChrgLim      = stPowLimLoc.stPrmExt.ftVoltBattChrgLim; ///< sst no use
    stPowLim.ftCurrBattChrgLim      = stPowLimLoc.stPrmExt.ftCurrBattChrgLim; ///< sst no use
    stPowLim.ftVoltBusLim           = stPowLimLoc.stPrmExt.ftVoltBusLim; ///< for stmac
    stPowLim.ftVoltBusAcLim         = stPowLimLoc.stPrmExt.ftVoltBusAcLim; ///< sst no use
    stPowLim.ftVoltBusBattLim       = stPowLimLoc.stPrmExt.ftVoltBusBattLim; ///< sst no use
    stPowLim.ftPowAcChrgLim         = stPowLimLoc.stPrmExt.ftPowAcChrgLim;  ///< for AC over load fault
    stPowLim.ftPowAcDchaLim         = stPowLimLoc.stPrmExt.ftPowAcDchaLim;  ///< for AC over load fault
    stPowLim.ftPowBattCurrChrgLim   = stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim; ///< for power limit
    stPowLim.ftPowBattCurrDchaLim   = stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim; ///< for power limit
    stPowLim.ftCurrBattChrgMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms; ///< sst no use
    stPowLim.ftCurrBattDchaMaxToBms = stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms; ///< sst no use
    stPowLim.ftPaAcLim              = stPowLimLoc.stPrmExt.ftPaAcLim; ///< for power limit
    stPowLim.ftPbAcLim              = stPowLimLoc.stPrmExt.ftPbAcLim; ///< for power limit
    stPowLim.ftPcAcLim              = stPowLimLoc.stPrmExt.ftPcAcLim; ///< for power limit
    stPowLim.ftQaAcLim              = stPowLimLoc.stPrmExt.ftQaAcLim; ///< for power limit
    stPowLim.ftQbAcLim              = stPowLimLoc.stPrmExt.ftQbAcLim; ///< for power limit
    stPowLim.ftQcAcLim              = stPowLimLoc.stPrmExt.ftQcAcLim; ///< for power limit
    stPowLim.ftVoltAcAmpLim         = stPowLimLoc.stPrmExt.ftVoltAcAmpLim; ///< sst no use
    stPowLim.ftCoeffTemp            = stPowLimLoc.stPrmExt.ftCoeffTemp; ///< for power limit
#endif
#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PowLim_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Power limitation 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PowLim_100ms(void)
{
    /* Power compensation */
    v_PowLim_PowComp_100ms();
    /* Power limitation according to temperature */
    v_PowLim_Temp_100ms(); ///< sst no use
    /* High temperature power limitation flag judgment */
    v_PowLim_HTSt_100ms();
    /* Fan Duty limitation according to Max temperature */
    v_PowLim_FanDutyCal_100ms(); ///< sst no use

    /* Output Signal*/
#if (1U == POW_LIM_DBG)
    stPowLim.ftTempMax                 = stPowLimDbg.ftTempMax;
    stPowLim.ftTempMin                 = stPowLimDbg.ftTempMin;
    stPowLim.uiFlgHTLim                = stPowLimDbg.uiFlgHTLim;
    stPowLim.ftFanDuty                 = stPowLimDbg.ftFanDuty;
#else
    stPowLim.ftTempMax                 = stPowLimLoc.stPrmExt.ftTempMax;
    stPowLim.ftTempMin                 = stPowLimLoc.stPrmExt.ftTempMin;
    stPowLim.uiFlgHTLim                = stPowLimLoc.stPrmExt.uiFlgHTLim;
    stPowLim.ftFanDuty                 = stPowLimLoc.stPrmExt.ftFanDuty; ///< sst no use
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_PowLim_100ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        PowLim module parameter update Eeprom task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PowLim_PrmUpd_Eep(void)
{
    float32 l_ftCoeffChrgAcVoltPL_Dwn = 0.0f;
    float32 l_ftCoeffDchaAcVoltPL_Dwn = 0.0f;

    if(stComTbl.stPrmPfcRtd1.ftVoltGrid > 1.0f)
    {
        /* AC voltage charge power limitation Macro Definition */
        l_ftCoeffChrgAcVoltPL_Dwn         = VOLT_AC_DWN_PL_CHRG / stComTbl.stPrmPfcRtd1.ftVoltGrid;   ///< Down AC voltage power coefficient
        stPowLimLoc.ftCoeffChrgAcVoltPL_K = (COEFF_RTD_VOLT_AC_PL_CHRG - l_ftCoeffChrgAcVoltPL_Dwn) / (stComTbl.stPrmPfcRtd1.ftVoltGrid - VOLT_AC_DWN_PL_CHRG);    ///< AC voltage Charge power limitation CofK
        stPowLimLoc.ftCoeffChrgAcVoltPL_B = COEFF_RTD_VOLT_AC_PL_CHRG - stPowLimLoc.ftCoeffChrgAcVoltPL_K * stComTbl.stPrmPfcRtd1.ftVoltGrid;   ///< AC voltage Charge power limitation CofB
        /* AC voltage discharge power limitation Macro Definition */
        l_ftCoeffDchaAcVoltPL_Dwn         = VOLT_AC_DWN_PL_DCHA / stComTbl.stPrmPfcRtd1.ftVoltGrid;    ///< Down AC voltage power coefficient
        stPowLimLoc.ftCoeffDchaAcVoltPL_K = (COEFF_RTD_VOLT_AC_PL_DCHA - l_ftCoeffDchaAcVoltPL_Dwn) / (stComTbl.stPrmPfcRtd1.ftVoltGrid - VOLT_AC_DWN_PL_DCHA);   ///< AC voltage Discharge power limitation CofK
        stPowLimLoc.ftCoeffDchaAcVoltPL_B = COEFF_RTD_VOLT_AC_PL_DCHA - stPowLimLoc.ftCoeffDchaAcVoltPL_K * stComTbl.stPrmPfcRtd1.ftVoltGrid;   ///< AC voltage Discharge power limitation CofB
    }

    if(stComTbl.stPrmPfcRtd1.ftRatAcOvLoad > 1.0f)
    {
        /* Battery voltage charge power limitation CofK/CofB update */
        stPowLimLoc.ftCoeffChrgBattVoltPL_K = (stComTbl.stPrmPfcRtd1.ftRatAcOvLoad - COEFF_RTD_VOLT_BATT_PL_CHRG) / (VOLT_BATT_PARL_RTD_OV_LOAD - VOLT_BATT_RTD_PL_CHRG);
        stPowLimLoc.ftCoeffChrgBattVoltPL_B = stComTbl.stPrmPfcRtd1.ftRatAcOvLoad - stPowLimLoc.ftCoeffChrgBattVoltPL_K * VOLT_BATT_PARL_RTD_OV_LOAD;
        /* Battery voltage discharge power limitation CofK/CofB update */
        stPowLimLoc.ftCoeffDchaBattVoltPL_K = (stComTbl.stPrmPfcRtd1.ftRatAcOvLoad - COEFF_RTD_VOLT_BATT_PL_DCHA) / (VOLT_BATT_PARL_RTD_OV_LOAD - VOLT_BATT_RTD_PL_DCHA);
        stPowLimLoc.ftCoeffDchaBattVoltPL_B = stComTbl.stPrmPfcRtd1.ftRatAcOvLoad - stPowLimLoc.ftCoeffDchaBattVoltPL_K * VOLT_BATT_PARL_RTD_OV_LOAD;
        /* Reciprocal of AC over load ratio update */
        stPowLimLoc.ftRecprRatAcOvLoad      = 1.0f / stComTbl.stPrmPfcRtd1.ftRatAcOvLoad;
    }
    else
    {
        /* Without AC over load situation */
        stPowLimLoc.ftCoeffChrgBattVoltPL_K = 0.0f;
        stPowLimLoc.ftCoeffChrgBattVoltPL_B = 1.0f;
        stPowLimLoc.ftCoeffDchaBattVoltPL_K = 0.0f;
        stPowLimLoc.ftCoeffDchaBattVoltPL_B = 1.0f;
        stPowLimLoc.ftRecprRatAcOvLoad      = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Current limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_BattVolt_1ms(void)
{
    /* Power limitation depend battery voltage calculation */
    stPowLimLoc.ftVoltBattCalc  = ftFcn_MaxOfTwo(stD2dAdc.ftVoltBattLpf100Hz, VOLT_BATT_MIN);
    stPowLimLoc.ftVoltBattRecpr = 1.0f / stPowLimLoc.ftVoltBattCalc;

    /* Battery voltage limitation */
    if((SP_RLY_PARL_ST == stPerphCtrl.stSPRly.uiSt) && (stComIf.ftVoltBattChrgReq > VOLT_BATT_PARL_MAX))
    {
        stPowLimLoc.stPrmExt.ftVoltBattChrgLim = VOLT_BATT_PARL_MAX;
    }
    else
    {
        stPowLimLoc.stPrmExt.ftVoltBattChrgLim = stComIf.ftVoltBattChrgReq;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Current limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_1ms(void)
{
	switch(stComIf.uiModRun)
	{
		case CHG_ONGRID_MODE:
			/* Charge Power limitation */
			v_PowLim_Curr_Chrg_1ms();
		    /* Battery current limitation */
			v_PowLim_Curr_ChrgChk_1ms();
			break;

		case BIDIR_ONGRID_MODE:
			/* Charge Power limitation */
		    v_PowLim_Curr_Chrg_1ms();
			/* Discharge Power limitation */
			v_PowLim_Curr_Dcha_1ms();
		    /* Power limitation according to battery current limit */
		    v_PowLim_Curr_BattReq_1ms();
		    /* Bi-direction power limitation according to battery Current */
		    v_PowLim_Curr_BidirChk_1ms();
			/* Active power and Reactive power limitation */
			v_PowLim_Curr_AcPow_1ms();
			/* Temperature coefficient Judge */
			v_PowLim_Curr_Temp_1ms();
			break;

		case OFFGRID_MODE:
		    /* Charge power limitation according to battery voltage */
		    v_PowLim_Curr_Chrg_BattVolt_1ms();
		    stPowLimLoc.stPrmChrgLim.ftPowLim = stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt * stComIf.ftPAcMax;
		    /* Discharge power limitation according to battery voltage */
		    v_PowLim_Curr_Dcha_BattVolt_1ms();
		    stPowLimLoc.stPrmDchaLim.ftPowLim = stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt * stComIf.ftPAcMax;
#if 1U == GRID_PHASE_NUMBER
		    /* Can not discharge 7.4kW when battery voltage 300V */
            if((stD2dAdc.ftVoltBattLpf100HzEquiv < VOLT_BATT_SPCL_RTD_PL_DCHA) && (stPowLimLoc.stPrmDchaLim.ftPowLim > POW_ACT_RTD_PL_DCHA))
            {
                stPowLimLoc.stPrmDchaLim.ftPowLim = POW_ACT_RTD_PL_DCHA;
            }
#endif

            /* Bi-direction power limitation according to battery Current */
            v_PowLim_Curr_BidirChk_1ms();
            /* Power limitation according to battery current limit */
            v_PowLim_Curr_BattReq_1ms();

            if(stPowLimLoc.stPrmExt.ftPowAcChrgLim > stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim)
            {
                stPowLimLoc.stPrmExt.ftPowAcChrgLim = stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim;
            }

            if(stPowLimLoc.stPrmExt.ftPowAcDchaLim > -stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim)
            {
                stPowLimLoc.stPrmExt.ftPowAcDchaLim = -stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim;    ///< Positive
            }
			break;

		default:
		    ///< Do nothing
			break;
	}
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Chrg_1ms(void)
{
    /* Charge power limitation according to AC voltage */
	v_PowLim_Curr_Chrg_AcVolt_1ms();
    /* Charge power limitation according to battery voltage */
	v_PowLim_Curr_Chrg_BattVolt_1ms();
	/* Charge power limitation */
	v_PowLim_Curr_Chrg_PowCalc_1ms();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge Power limitation according to AC voltage
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Chrg_AcVolt_1ms(void)
{
	if(PFC_DIS_D2D_EN != stCom.uiStgRunEnReq)
	{
	    /* AC voltage limitation */
		if(stPfcDataCalc.stMeasParm.ftVgMinRms > stComTbl.stPrmPfcRtd1.ftVoltGrid)
		{
			stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt = COEFF_RTD_VOLT_AC_PL_CHRG;
		}
		else
		{
			stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt = stPowLimLoc.ftCoeffChrgAcVoltPL_K * stPfcDataCalc.stMeasParm.ftVgMinRms + stPowLimLoc.ftCoeffChrgAcVoltPL_B;
		}
#ifdef SST_1250kW
    stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt = 1.0f;
#endif
		vFcn_FtUpDwnLim(&stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt, 1.0f, 0.0f);
        stPowLimLoc.stPrmChrgLim.ftPowAcVolt1P = stComIf.ftPOnePhaMax * stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt;    ///< One phase power limitation according to AC voltage

		if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)
		{
		    stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt = stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt * ONE_PHASE_COEFF;
		}
	}
	else
	{
		stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt = 1.0f;
	}
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge Power limitation according to battery voltage
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Chrg_BattVolt_1ms(void)
{
#ifdef ENA_POWLIM_BAT
//#ifndef _SIMULATION_NO_DSP_
	if(PFC_EN_D2D_DIS != stCom.uiStgRunEnReq)
	{
        if(CHG_ONGRID_MODE == stComIf.uiModRun)    ///< Charge mode
        {
            if((SP_RLY_SERIES_ST == stPerphCtrl.stSPRly.uiSt) && \
                    (D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun) && \
                    (stD2dAdc.ftVoltBattLpf100HzEquiv < VOLT_BATT_DWN_PL_CHRG))    ///< Series status && D2D State Machine NormalRun State && Battery voltage equivalent less than 200V
            {
                if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_LO_PL_CHRG)
                {
                    stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = COEFF_K_VOLT_BATT_LO_PL_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_VOLT_BATT_LO_PL_CHRG;
                }
                else
                {
                    stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = COEFF_LO_VOLT_BATT_PL_CHRG;
                }
            }
            else
            {
                stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = 1.0f;
            }
        }
        else    ///< Not charge mode
        {
            if(stD2dAdc.ftVoltBattLpf10Hz > stPowLimLoc.stPrmExt.ftVoltBattChrgLim)
            {
                stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = 0.0f;
            }
            else
            {
                v_PowLim_Chrg_BattVolt_Curve();
            }
        }
        /* Up and down limitation */
        vFcn_FtUpDwnLim(&stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt, 1.0f, 0.0f);
	}
	else
	{
	    /* PFC_EN_D2D_DIS mode, coefficient is Max */
		stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = 1.0f;
	}
#else
	stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = 1.0f;
#endif

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge Power limitation according to battery voltage and AC over load flag
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Chrg_BattVolt_Curve(void)
{
#ifdef ENA_POWLIM_BAT
//#ifndef _SIMULATION_NO_DSP_
    if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_PARL_RTD_OV_LOAD)   ///< Charge power limitation over load DC voltage
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = stComTbl.stPrmPfcRtd1.ftRatAcOvLoad;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_RTD_PL_CHRG)   ///< Charge power limitation rated DC voltage
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = stPowLimLoc.ftCoeffChrgBattVoltPL_K * stD2dAdc.ftVoltBattLpf100HzEquiv + stPowLimLoc.ftCoeffChrgBattVoltPL_B;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_DWN_PL_CHRG)   ///< Charge power limitation down DC voltage
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = COEFF_K_VOLT_BATT_PL_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_VOLT_BATT_PL_CHRG;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_LO_PL_CHRG)
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = COEFF_K_VOLT_BATT_LO_PL_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_VOLT_BATT_LO_PL_CHRG;
    }
    else
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = COEFF_LO_VOLT_BATT_PL_CHRG;
    }
    /* Under AC over load situation, normalize ftCoeffBattVolt to 1.0f */
    if(1U == stComIf.uiEnaAcOvLoad)
    {
        stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt * stPowLimLoc.ftRecprRatAcOvLoad;
    }
#else
    stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt = 1.0f;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Chrg_PowCalc_1ms(void)
{
    /* Comparison of power limiting coefficients */

    stPowLimLoc.stPrmChrgLim.ftCoeffLim = ftFcn_MinOfThree(stPowLimLoc.stPrmChrgLim.ftCoeffAcVolt, stPowLimLoc.stPrmChrgLim.ftCoeffBattVolt, stPowLimLoc.stPrmChrgLim.ftCoeffLT);
    if(CHG_ONGRID_MODE == stComIf.uiModRun)    ///< Charge mode
    {
        stPowLimLoc.stPrmChrgLim.ftPowLim = stPowLimLoc.stPrmChrgLim.ftCoeffLim * stCom.ftPowBattMax;
    }
    else    ///< Not charge mode
    {
        stPowLimLoc.stPrmChrgLim.ftPowLim = stPowLimLoc.stPrmChrgLim.ftCoeffLim * stComIf.ftPAcMax;
    }
}
/********************************************Begin*********************************************/
/**
 * @brief        Charge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_ChrgChk_1ms(void)
{
    float32 l_ftCurrBattLimTmp = 0.0f;    ///< Temporary battery current limitation
    float32 l_ftPwrGridInp     = 0.0f;    ///< Grid control power input

    /* Battery current limitation */
    l_ftCurrBattLimTmp = stPowLimLoc.stPrmChrgLim.ftPowLim * stPowLimLoc.ftVoltBattRecpr;
    stPowLimLoc.stPrmChrgLim.ftCurrBattLim = ftFcn_MinOfTwo(l_ftCurrBattLimTmp, stCom.ftCurrBattMaxChrg) * stPowLimLoc.stPrmChrgLim.ftCoeffHT;
    /* Battery max current to BMS */
    stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms = stPowLimLoc.stPrmChrgLim.ftCurrBattLim;
    stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms = 0.0f;

    /* AC current RMS limitation in charge mode */
    stPowLimLoc.stPrmChrgLim.ftPowAcCurrLim = stPfcDataCalc.stMeasParm.ftVgMinRms * stComIf.ftCurrAcRmsMax * (float32)GRID_PHASE_NUMBER * EFF_PL_CHRG \
            - stPowLimLoc.stPowComp.stAcCurrChrgPI.ftOutp;
    /* OCPP power limitation */
    stPowLimLoc.stPrmChrgLim.ftPowOcppLim = stComIf.ftPwrChrgReq * EFF_PL_CHRG - stPowLimLoc.stPowComp.stOcppChrgPI.ftOutp;
#if(BMW_CUSTUMER == CUSTUMER_ID)
    /* PfcGridCtrl power limitation */
    if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_NORMRUN)        ///< Wait for D2d stable
    {
        l_ftPwrGridInp = -(float32)stPfcGridCtrl.stActvCtrl.siPwrLimLF * EFF_PL_CHRG;
        DOWN_LIMIT(l_ftPwrGridInp, LF_PWR_DWN_LMT_CHRG);
    }
    else
    {
        l_ftPwrGridInp = stComIf.ftPAcMax;
    }
    /* Battery current limitation calculation */
    l_ftCurrBattLimTmp = ftFcn_MinOfThree(l_ftPwrGridInp, stPowLimLoc.stPrmChrgLim.ftPowAcCurrLim, stPowLimLoc.stPrmChrgLim.ftPowOcppLim) * stPowLimLoc.ftVoltBattRecpr;
#else
    /* Battery current limitation calculation */
    l_ftCurrBattLimTmp = ftFcn_MinOfTwo(stPowLimLoc.stPrmChrgLim.ftPowAcCurrLim, stPowLimLoc.stPrmChrgLim.ftPowOcppLim) * stPowLimLoc.ftVoltBattRecpr;
#endif
    stPowLimLoc.stPrmExt.ftCurrBattChrgLim = ftFcn_MinOfThree(stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms, stComIf.ftCurrBattChrgReq, l_ftCurrBattLimTmp);
    DOWN_LIMIT(stPowLimLoc.stPrmExt.ftCurrBattChrgLim, CURR_BATT_TGT_MIN);
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Dcha_1ms(void)
{
    /* Discharge power limitation according to AC voltage */
    v_PowLim_Curr_Dcha_AcVolt_1ms();
    /* Discharge power limitation according to battery voltage */
    v_PowLim_Curr_Dcha_BattVolt_1ms();
#if 1U == GRID_PHASE_NUMBER
    /* Battery low voltage power limitation */
    v_PowLim_Curr_Dcha_Batt_LV_1ms();
#endif
    /* Discharge power limitation */
    v_PowLim_Curr_Dcha_PowCalc_1ms();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge Power limitation according to AC voltage
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Dcha_AcVolt_1ms(void)
{
    if(PFC_DIS_D2D_EN != stCom.uiStgRunEnReq)
    {
        /* AC voltage limitation */
        if(stPfcDataCalc.stMeasParm.ftVgMinRms > stComTbl.stPrmPfcRtd1.ftVoltGrid)
        {
            stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt = COEFF_RTD_VOLT_AC_PL_DCHA;
        }
        else
        {
            stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt = stPowLimLoc.ftCoeffDchaAcVoltPL_K * stPfcDataCalc.stMeasParm.ftVgMinRms + stPowLimLoc.ftCoeffDchaAcVoltPL_B;
        }
        vFcn_FtUpDwnLim(&stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt, 1.0f, 0.0f);
        stPowLimLoc.stPrmDchaLim.ftPowAcVolt1P = stComIf.ftPOnePhaMax * stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt;    ///< One phase power limitation according to AC voltage

        if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)
        {
            stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt = stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt * ONE_PHASE_COEFF;
        }
    }
    else
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge Power limitation according to battery voltage
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Dcha_BattVolt_1ms(void)
{
#ifdef ENA_POWLIM_BAT
//#ifndef _SIMULATION_NO_DSP_
    if(PFC_EN_D2D_DIS != stCom.uiStgRunEnReq)
    {
        if(stD2dAdc.ftVoltBattLpf10Hz < stComIf.ftVoltBattDchaReq)      ///< Discharge Voltage Request Large Than Battery Voltage
        {
            stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = 0.0f;
        }
        else
        {
            v_PowLim_Dcha_BattVolt_Curve();
        }
        vFcn_FtUpDwnLim(&stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt, 1.0f, 0.0f);    ///< Limit Coefficient
    }
    else
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = 1.0f;
    }
#else
    stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = 1.0f;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge Power limitation according to battery voltage and AC over load flag
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Dcha_BattVolt_Curve(void)
{
    if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_PARL_RTD_OV_LOAD)   ///< Discharge power limitation over load DC voltage
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = stComTbl.stPrmPfcRtd1.ftRatAcOvLoad;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_RTD_PL_DCHA)    ///< Discharge power limitation rated DC voltage
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = stPowLimLoc.ftCoeffDchaBattVoltPL_K * stD2dAdc.ftVoltBattLpf100HzEquiv + stPowLimLoc.ftCoeffDchaBattVoltPL_B;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_DWN_PL_DCHA)    ///< Discharge power limitation down DC voltage
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = COEFF_K_VOLT_BATT_PL_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_VOLT_BATT_PL_DCHA;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv > VOLT_BATT_LO_PL_DCHA)
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = COEFF_K_VOLT_BATT_LO_PL_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_VOLT_BATT_LO_PL_DCHA;
    }
    else
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = COEFF_LO_VOLT_BATT_PL_DCHA;
    }
    /* Under AC over load situation, normalize ftCoeffBattVolt to 1.0f */
    if(1U == stComIf.uiEnaAcOvLoad)
    {
        stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt = stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt * stPowLimLoc.ftRecprRatAcOvLoad;
    }
}
/*********************************************End**********************************************/

#if 1U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Battery low voltage power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Dcha_Batt_LV_1ms(void)
{
    float32 l_ftVoltAcCalc   = 0.0f;
    float32 l_ftVoltBattCalc = 0.0f;

    if((stD2dAdc.ftVoltBattLpf100HzEquiv < VOLT_BATT_MAX_BATT_LV_PL_DCHA) && (stPfcDataCalc.stMeasParm.ftVgMinRms > VOLT_AC_MIN_BATT_LV_PL_DCHA))
    {
        l_ftVoltAcCalc = stPfcDataCalc.stMeasParm.ftVgMinRms;
        l_ftVoltBattCalc = stD2dAdc.ftVoltBattLpf100HzEquiv;

        if(l_ftVoltAcCalc >= VOLT_AC_MAX_BATT_LV_PL_DCHA)       ///< Max AC voltage when Battery low voltage power limitation
        {
            l_ftVoltAcCalc = VOLT_AC_MAX_BATT_LV_PL_DCHA;
        }
        if(l_ftVoltBattCalc <= VOLT_BATT_MIN_BATT_LV_PL_DCHA)   ///< Min battery voltage when Battery low voltage power limitation
        {
            l_ftVoltBattCalc = VOLT_BATT_MIN_BATT_LV_PL_DCHA;
        }

        stPowLimLoc.ftCoeffBattLVLim = COEFF1_BATT_LV_PL_DCHA + COEFF2_BATT_LV_PL_DCHA * l_ftVoltAcCalc + \
                COEFF3_BATT_LV_PL_DCHA * l_ftVoltBattCalc + COEFF4_BATT_LV_PL_DCHA * l_ftVoltAcCalc * l_ftVoltBattCalc;

        /* Up and down limitation */
        UP_DOWN_LIMIT(stPowLimLoc.ftCoeffBattLVLim, 1.0f, COEFF_MIN_BATT_LV_PL_DCHA);
    }
    else
    {
        stPowLimLoc.ftCoeffBattLVLim = 1.0f;
    }
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Disharge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Dcha_PowCalc_1ms(void)
{
    /* Comparison of power limiting coefficients */
    stPowLimLoc.stPrmDchaLim.ftCoeffLim = ftFcn_MinOfThree(stPowLimLoc.stPrmDchaLim.ftCoeffAcVolt, stPowLimLoc.stPrmDchaLim.ftCoeffBattVolt, stPowLimLoc.stPrmDchaLim.ftCoeffLT);
    stPowLimLoc.stPrmDchaLim.ftPowLim   = stPowLimLoc.stPrmDchaLim.ftCoeffLim * stPowLimLoc.ftCoeffBattLVLim * stComIf.ftPAcMax;
#if 1U == GRID_PHASE_NUMBER
    /* Can not discharge 7.4kW when battery voltage 300V */
    if((stD2dAdc.ftVoltBattLpf100HzEquiv < VOLT_BATT_SPCL_RTD_PL_DCHA) && (stPowLimLoc.stPrmDchaLim.ftPowLim > POW_ACT_RTD_PL_DCHA))
    {
        stPowLimLoc.stPrmDchaLim.ftPowLim = POW_ACT_RTD_PL_DCHA;
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Disharge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_BidirChk_1ms(void)
{
    /* Battery max current to BMS */
    stPowLimLoc.ftPowAcChrgMax  = stPowLimLoc.stPrmChrgLim.ftPowLim * stPowLimLoc.stPrmChrgLim.ftCoeffHT;
    stPowLimLoc.ftPowAcDchaMax  = stPowLimLoc.stPrmDchaLim.ftPowLim * stPowLimLoc.stPrmDchaLim.ftCoeffHT;

    stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms = stPowLimLoc.ftPowAcChrgMax * stPowLimLoc.ftVoltBattRecpr * EFF_PL_CHRG;
    UP_LIMIT(stPowLimLoc.stPrmExt.ftCurrBattChrgMaxToBms, stCom.ftCurrBattMaxBidir);

    stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms = -stPowLimLoc.ftPowAcDchaMax * stPowLimLoc.ftVoltBattRecpr * EFF_RECPR_PL_DCHA;
    DOWN_LIMIT(stPowLimLoc.stPrmExt.ftCurrBattDchaMaxToBms, -stCom.ftCurrBattMaxBidir);

    /* AC power limitation */
    stPowLimLoc.stPrmExt.ftPowAcChrgLim = stPowLimLoc.ftPowAcChrgMax;
    stPowLimLoc.stPrmExt.ftPowAcDchaLim = stPowLimLoc.ftPowAcDchaMax;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Disharge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_AcPow_1ms(void)
{
    /* Reactive power */
    stPowLimLoc.stPrmExt.ftQaAcLim = stComIf.ftQaReq;
    stPowLimLoc.stPrmExt.ftQbAcLim = stComIf.ftQbReq;
    stPowLimLoc.stPrmExt.ftQcAcLim = stComIf.ftQcReq;

    /* Active power */
    stPowLimLoc.ftPaAcReq = stComIf.ftPaReq;
    vFcn_FtUpDwnLim(&stPowLimLoc.ftPaAcReq, stPowLimLoc.stPrmChrgLim.ftPowAcVolt1P, -stPowLimLoc.stPrmDchaLim.ftPowAcVolt1P);
    stPowLimLoc.ftPbAcReq = stComIf.ftPbReq;
    vFcn_FtUpDwnLim(&stPowLimLoc.ftPbAcReq, stPowLimLoc.stPrmChrgLim.ftPowAcVolt1P, -stPowLimLoc.stPrmDchaLim.ftPowAcVolt1P);
    stPowLimLoc.ftPcAcReq = stComIf.ftPcReq;
    vFcn_FtUpDwnLim(&stPowLimLoc.ftPcAcReq, stPowLimLoc.stPrmChrgLim.ftPowAcVolt1P, -stPowLimLoc.stPrmDchaLim.ftPowAcVolt1P);

    stPowLimLoc.ftPAcReq = stPowLimLoc.ftPaAcReq + stPowLimLoc.ftPbAcReq + stPowLimLoc.ftPcAcReq;    ///< Sum active power request
    if(stPowLimLoc.ftPAcReq > stPowLimLoc.stPrmExt.ftPowAcChrgLim)
    {
        stPowLimLoc.ftCoeffPAcReq = stPowLimLoc.stPrmExt.ftPowAcChrgLim / stPowLimLoc.ftPAcReq;
        stPowLimLoc.ftPaAcReq = stPowLimLoc.ftPaAcReq * stPowLimLoc.ftCoeffPAcReq;
        stPowLimLoc.ftPbAcReq = stPowLimLoc.ftPbAcReq * stPowLimLoc.ftCoeffPAcReq;
        stPowLimLoc.ftPcAcReq = stPowLimLoc.ftPcAcReq * stPowLimLoc.ftCoeffPAcReq;
    }
    else if(stPowLimLoc.ftPAcReq < -stPowLimLoc.stPrmExt.ftPowAcDchaLim)
    {
        stPowLimLoc.ftCoeffPAcReq = -stPowLimLoc.stPrmExt.ftPowAcDchaLim / stPowLimLoc.ftPAcReq;
        stPowLimLoc.ftPaAcReq = stPowLimLoc.ftPaAcReq * stPowLimLoc.ftCoeffPAcReq;
        stPowLimLoc.ftPbAcReq = stPowLimLoc.ftPbAcReq * stPowLimLoc.ftCoeffPAcReq;
        stPowLimLoc.ftPcAcReq = stPowLimLoc.ftPcAcReq * stPowLimLoc.ftCoeffPAcReq;
    }
    else
    {
        ///< Do nothing
    }

    /* Calculation of active and reactive power */
    v_PowLim_Curr_Pow_OnePha_1ms(stPowLimLoc.stPrmExt.ftQaAcLim, stPowLimLoc.ftPaAcReq, &stPowLimLoc.stPrmExt.ftPaAcLim);
    v_PowLim_Curr_Pow_OnePha_1ms(stPowLimLoc.stPrmExt.ftQbAcLim, stPowLimLoc.ftPbAcReq, &stPowLimLoc.stPrmExt.ftPbAcLim);
    v_PowLim_Curr_Pow_OnePha_1ms(stPowLimLoc.stPrmExt.ftQcAcLim, stPowLimLoc.ftPcAcReq, &stPowLimLoc.stPrmExt.ftPcAcLim);
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Disharge power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Temp_1ms(void)
{
    /* Temperature coefficient */
    if(stPowLimLoc.ftPAcReq > 0.0f)    ///< Charge power
    {
        stPowLimLoc.stPrmExt.ftCoeffTemp = ftFcn_MinOfTwo(stPowLimLoc.stPrmChrgLim.ftCoeffHT, stPowLimLoc.stPrmChrgLim.ftCoeffLT);
    }
    else    ///< Discharge mode
    {
        stPowLimLoc.stPrmExt.ftCoeffTemp = ftFcn_MinOfTwo(stPowLimLoc.stPrmDchaLim.ftCoeffHT, stPowLimLoc.stPrmDchaLim.ftCoeffLT);
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Power limitation according to battery current
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_BattReq_1ms(void)
{
#ifdef ENA_POWLIM_BAT
//#ifndef _SIMULATION_NO_DSP_
#if 3U == GRID_PHASE_NUMBER
    float32 l_ftCurrBattDchaLim = 0.0f;
#endif

    if(PFC_EN_D2D_EN == stCom.uiStgRunEnReq)
    {
        if(stD2dStMac.uiStD2dRun >= D2D_ST_MAC_PWMEN)       ///< D2D State Machine PWM_EN State
        {
            stPowLimLoc.stPrmChrgLim.ftCurrBattReq = stComIf.ftCurrBattChrgReq;   ///< Max Battery Charge Current limitation
#if 3U == GRID_PHASE_NUMBER
            l_ftCurrBattDchaLim = ftFcn_MaxOfTwo(stComIf.ftCurrBattDchaReq, stPowLimLoc.ftCurrBattDchaMax);               ///< Max Battery Discharge Current limitation
            stPowLimLoc.stPrmDchaLim.ftCurrBattReq = l_ftCurrBattDchaLim;         ///< Batter Discharge Current Request Give
#else
            stPowLimLoc.stPrmDchaLim.ftCurrBattReq = stComIf.ftCurrBattDchaReq;   ///< Batter Discharge Current Request Give
#endif
        }
        else
        {
            stPowLimLoc.stPrmChrgLim.ftCurrBattReq = 0.0f;      ///< Initialize to 0.0f
            stPowLimLoc.stPrmDchaLim.ftCurrBattReq = 0.0f;      ///< Initialize to 0.0f
        }

        /* Charge power limitation according to battery current request */
        stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim = stPowLimLoc.ftVoltBattCalc * stPowLimLoc.stPrmChrgLim.ftCurrBattReq * EFF_RECPR_PL_CHRG \
                - stPowLimLoc.stPowComp.stBattCurrChrgPI.ftOutp;
        vFcn_FtUpDwnLim(&stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim, stComIf.ftPAcMax, 0.0f);
        /* Discharge power limitation according to battery current request; Negative*/
        stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim = stPowLimLoc.ftVoltBattCalc * stPowLimLoc.stPrmDchaLim.ftCurrBattReq * EFF_PL_DCHA \
                + stPowLimLoc.stPowComp.stBattCurrDchaPI.ftOutp;
        vFcn_FtUpDwnLim(&stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim, 0.0f, -stComIf.ftPAcMax);
    }
    else
    {
        stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim  = stComIf.ftPAcMax;
        stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim  = -stComIf.ftPAcMax;
    }
#else
    stPowLimLoc.stPrmExt.ftPowBattCurrChrgLim  = stComIf.ftPAcMax;
    stPowLimLoc.stPrmExt.ftPowBattCurrDchaLim  = -stComIf.ftPAcMax;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        One phase active power limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Curr_Pow_OnePha_1ms(float32 ftQLim, float32 ftPReq, float32 *ftPlim)
{
    float32 l_ftSSq  = 0.0f;    ///< Square of Apparent power
    float32 l_ftPLim = 0.0f;    ///< Active power limitation
    float32 l_ftTmp  = 0.0f;    ///< Temporary variable

    l_ftSSq = SQUARE(ftPReq) + SQUARE(ftQLim);
    if(l_ftSSq > SQUARE(stComIf.ftPOnePhaMax))
    {
        l_ftTmp = SQUARE(stComIf.ftPOnePhaMax) - SQUARE(ftQLim);
        if(l_ftTmp > 0.0f)
        {
            l_ftPLim = sqrtf(l_ftTmp);
        }
        else
        {
            l_ftPLim = 0.0f;
        }
    }
    else
    {
        l_ftPLim = stComIf.ftPOnePhaMax;
    }
    vFcn_FtUpDwnLim(&ftPReq, l_ftPLim, -l_ftPLim);    ///< Limitation process
    *ftPlim = ftPReq;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Current limitation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_BusVolt_1ms(void)
{
    /* Bus voltage calculation according to AC voltage */
#if(1U == GRID_PHASE_NUMBER)
    stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2 + 30.0f;           ///< Vac Peak add 30.0V
#elif(2U == GRID_PHASE_NUMBER)
    stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2 * 2.0f + 30.0f;    ///< Vac Peak add 30.0V
#else
    if(OFFGRID_MODE == stComIf.uiModRun)
    {
        stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt = stCom.ftVoltAcV2LReq * CON_SQRT_2 * 2.0f + stComTbl.stPrmPowLim.ftVoltBusAdd;
    }
    else
    {
        if((PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss) || ((BIDIR_ONGRID_MODE == stComIf.uiModPfcRun) && (PFC_PWR_ARM_CTRL_MODE == stCom.unModPfcPow.bit.uiModPowCtrl)))
        {
            stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2 * 2.0f + stComTbl.stPrmPowLim.ftVoltBusAdd;
        }
        else
        {
            stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2 + stComTbl.stPrmPowLim.ftVoltBusAdd;
        }
    }
#endif

    /* Bus voltage calculation according to battery voltage */
	stPowLimLoc.stPrmBusVoltLim.ftPrmBattVolt = COEFF_BUS_BATT_VOLT * stD2dAdc.ftVoltBattLpf10HzEquiv;
#if(1U == GRID_PHASE_NUMBER)
	UP_LIMIT(stPowLimLoc.stPrmBusVoltLim.ftPrmBattVolt, VOLT_BUS_TGT_BATT_MAX);
#endif

	if(PFC_EN_D2D_DIS == stCom.uiStgRunEnReq)         ///< PFC enable & D2D disable
	{
		stPowLimLoc.stPrmExt.ftVoltBusLim = stComTbl.stPrmPowLim.ftVoltBusPfcReq;
	}
	else if(PFC_DIS_D2D_EN == stCom.uiStgRunEnReq)    ///< PFC disable & D2D enable
    {
    	stPowLimLoc.stPrmExt.ftVoltBusLim = stComTbl.stPrmPowLim.ftVoltBusD2dReq;
    }
	else
	{
		stPowLimLoc.stPrmExt.ftVoltBusLim = ftFcn_MaxOfTwo(stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt, stPowLimLoc.stPrmBusVoltLim.ftPrmBattVolt);
		vFcn_FtUpDwnLim(&stPowLimLoc.stPrmExt.ftVoltBusLim, stComTbl.stPrmPowLim.ftVoltBusMax, stComTbl.stPrmPowLim.ftVoltBusMin);
	}
	stPowLimLoc.stPrmExt.ftVoltBusAcLim   = stPowLimLoc.stPrmBusVoltLim.ftPrmAcVolt;
	stPowLimLoc.stPrmExt.ftVoltBusBattLim = stPowLimLoc.stPrmBusVoltLim.ftPrmBattVolt;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Power compensation 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_PowComp_100ms(void)
{
    if(CHG_ONGRID_MODE == stComIf.uiModRun)
    {
        if(D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun)    ///< Charge mode
        {
            /* Power compensation according to AC current RMS limitation */
            stPowLimLoc.stPowComp.stAcCurrChrgPI.ftInp = (float32)stPfcDataCalc.stMeasParm.uiIgMaxRms100Times * 0.01f - stComIf.ftCurrAcRmsMax;
            vFcn_PosnPICtrl(&stPowLimLoc.stPowComp.stAcCurrChrgPI);    ///< PI control
            /* Power compensation according to OCPP power limitation */
            stPowLimLoc.stPowComp.stOcppChrgPI.ftInp = -(float32)stPfcDataCalc.stMeasParm.slActvPowerLPF - stComIf.ftPwrChrgReq;    ///< slActvPowerLPF is negative in charge mode
            vFcn_PosnPICtrl(&stPowLimLoc.stPowComp.stOcppChrgPI);      ///< PI control
        }
        else
        {
            /* Initialize AC current RMS PI parameter */
            vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stAcCurrChrgPI);
            /* Initialize OCPP power PI parameter */
            vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stOcppChrgPI);
        }
    }
    else if(BIDIR_ONGRID_MODE == stComIf.uiModRun)         ///< Bi-direction mode
    {
        if(PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt)
        {
            /* Power compensation according to Max battery charge current */
            stPowLimLoc.stPowComp.stBattCurrChrgPI.ftInp = stD2dAdc.ftCurrBattLpf10Hz - stPowLimLoc.stPrmChrgLim.ftCurrBattReq;
            vFcn_PosnPICtrl(&stPowLimLoc.stPowComp.stBattCurrChrgPI);    ///< PI control
            /* Power compensation according to Max battery discharge current */
            stPowLimLoc.stPowComp.stBattCurrDchaPI.ftInp = stPowLimLoc.stPrmDchaLim.ftCurrBattReq - stD2dAdc.ftCurrBattLpf10Hz;
            vFcn_PosnPICtrl(&stPowLimLoc.stPowComp.stBattCurrDchaPI);    ///< PI control
        }
        else
        {
            /* Initialize battery charge current PI parameter */
            vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stBattCurrChrgPI);
            /* Initialize battery discharge current PI parameter */
            vFcn_InitPIPrm(&stPowLimLoc.stPowComp.stBattCurrDchaPI);
        }
    }
    else
    {
        stPowLimLoc.stPowComp.stAcCurrChrgPI.ftOutp   = 0.0f;
        stPowLimLoc.stPowComp.stOcppChrgPI.ftOutp     = 0.0f;
        stPowLimLoc.stPowComp.stBattCurrChrgPI.ftOutp = 0.0f; ///< sst no use
        stPowLimLoc.stPowComp.stBattCurrDchaPI.ftOutp = 0.0f; ///< sst no use
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        High temperature limitation status
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Temp_100ms(void)
{
	/* Temperature limitation */
    switch(stComIf.uiModRun)
    {
        case CHG_ONGRID_MODE:
            /* Charge power limitation according to high temperature */
            v_PowLim_Temp_ChrgHigh_100ms();
            /* Charge power limitation according to low temperature */
            v_PowLim_Temp_ChrgLow_100ms();

            stPowLimLoc.stTempDchaPrm.ftCoeffHT = 1.0f;
            stPowLimLoc.stTempDchaPrm.ftCoeffLT = 1.0f;
            /* Temperature for fault diagnosis */
            stPowLimLoc.stPrmExt.ftTempMax      = stPowLimLoc.stTempChrgPrm.ftTempMax;
            stPowLimLoc.stPrmExt.ftTempMin      = stPowLimLoc.stTempChrgPrm.ftTempMin;
            /* Temperature for fan control */
            stPowLimLoc.ftTempMaxFanCtrl        = stPowLimLoc.stTempChrgPrm.ftTempMax;
            break;

        case BIDIR_ONGRID_MODE:
            /* Charge power limitation according to high temperature */
            v_PowLim_Temp_ChrgHigh_100ms();
            /* Charge power limitation according to low temperature */
            v_PowLim_Temp_ChrgLow_100ms();

            /* Discharge power limitation according to high temperature */
            v_PowLim_Temp_DchaHigh_100ms();
            /* Discharge power limitation according to low temperature */
            v_PowLim_Temp_DchaLow_100ms();

            /* Temperature for fault diagnosis */
            stPowLimLoc.stPrmExt.ftTempMax = ftFcn_MinOfTwo(stPowLimLoc.stTempDchaPrm.ftTempMax, stPowLimLoc.stTempChrgPrm.ftTempMax);    ///< Avoid Over_temperature fault due to power direction changed
            stPowLimLoc.stPrmExt.ftTempMin = stPowLimLoc.stTempChrgPrm.ftTempMin;

            /* Temperature for fan control */
            if(stPowLimLoc.ftPAcReq > 0.0f)    ///< Charge power
            {
                stPowLimLoc.ftTempMaxFanCtrl = stPowLimLoc.stTempChrgPrm.ftTempMax;
            }
            else    ///< Discharge mode
            {
                stPowLimLoc.ftTempMaxFanCtrl = stPowLimLoc.stTempDchaPrm.ftTempMax;
            }
            break;

        case OFFGRID_MODE:
            /* Charge power limitation according to high temperature */
            v_PowLim_Temp_ChrgHigh_100ms();
            /* Charge power limitation according to high temperature */
            v_PowLim_Temp_DchaHigh_100ms();

            stPowLimLoc.stTempChrgPrm.ftCoeffLT = 1.0f;
            stPowLimLoc.stTempDchaPrm.ftCoeffLT = 1.0f;

            /* Temperature for fault diagnosis */
            stPowLimLoc.stPrmExt.ftTempMax = ftFcn_MinOfTwo(stPowLimLoc.stTempDchaPrm.ftTempMax, stPowLimLoc.stTempChrgPrm.ftTempMax);    ///< Avoid Over_temperature fault due to power direction changed
            stPowLimLoc.stPrmExt.ftTempMin = stPowLimLoc.stTempChrgPrm.ftTempMin;
            /* Temperature for fan control */
            if(stPfcDataCalc.stMeasParm.slActvPowerLPF > 0L)    ///< Discharge power
            {
                stPowLimLoc.ftTempMaxFanCtrl = stPowLimLoc.stTempDchaPrm.ftTempMax;
            }
            else    ///< Charge mode
            {
                stPowLimLoc.ftTempMaxFanCtrl = stPowLimLoc.stTempChrgPrm.ftTempMax;
            }
            break;

        default:
            ///< Do nothing
            break;
    }
#ifdef ENA_POWLIM_BAT
//#ifndef _SIMULATION_NO_DSP_
    stPowLimLoc.stPrmChrgLim.ftCoeffHT = stPowLimLoc.stTempChrgPrm.ftCoeffHT;
    stPowLimLoc.stPrmDchaLim.ftCoeffHT = stPowLimLoc.stTempDchaPrm.ftCoeffHT;
    stPowLimLoc.stPrmChrgLim.ftCoeffLT = stPowLimLoc.stTempChrgPrm.ftCoeffLT;
    stPowLimLoc.stPrmDchaLim.ftCoeffLT = stPowLimLoc.stTempDchaPrm.ftCoeffLT;
#else
    stPowLimLoc.stPrmChrgLim.ftCoeffHT = 1.0f;
    stPowLimLoc.stPrmDchaLim.ftCoeffHT = 1.0f;
    stPowLimLoc.stPrmChrgLim.ftCoeffLT = 1.0f;
    stPowLimLoc.stPrmDchaLim.ftCoeffLT = 1.0f;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge Power limitation according to high temperature
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Temp_ChrgHigh_100ms(void)
{
    float32 l_ftTempMax = 0.0f;
    float32 l_ftTempMin = 0.0f;

    /* Power Limit High Temperature compensation */
    if(stD2dAdc.ftVoltBattLpf100HzEquiv <= LV_BATT_HT_PL_CHRG)     ///< Battery voltage is less than power limit high temperature low voltage
    {
        stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd        = TEMP_CMP_ARM_BD_LV_CHRG;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd        = TEMP_CMP_DSP_BD_LV_CHRG;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0     = TEMP_CMP_NTC0_LV_CHRG;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1     = TEMP_CMP_NTC1_LV_CHRG;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2     = TEMP_CMP_NTC2_LV_CHRG;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3     = TEMP_CMP_NTC3_LV_CHRG;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4     = TEMP_CMP_NTC4_LV_CHRG;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5     = TEMP_CMP_NTC5_LV_CHRG;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6     = TEMP_CMP_NTC6_LV_CHRG;             ///< D2D inductor NTC temperature Compensation
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV_BATT_HT_PL_CHRG)       ///< Power Limit High Temperature Middle battery Voltage
    {
        stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd        = COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd        = COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0     = COEFF_K_TEMP_CMP_NTC0_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1     = COEFF_K_TEMP_CMP_NTC1_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2     = COEFF_K_TEMP_CMP_NTC2_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3     = COEFF_K_TEMP_CMP_NTC3_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4     = COEFF_K_TEMP_CMP_NTC4_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5     = COEFF_K_TEMP_CMP_NTC5_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_LV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6     = COEFF_K_TEMP_CMP_NTC6_LV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_LV_CHRG;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= HV_BATT_HT_PL_CHRG)        ///< Power Limit High Temperature High battery Voltage
    {
        stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd        = COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd        = COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0     = COEFF_K_TEMP_CMP_NTC0_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1     = COEFF_K_TEMP_CMP_NTC1_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2     = COEFF_K_TEMP_CMP_NTC2_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3     = COEFF_K_TEMP_CMP_NTC3_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4     = COEFF_K_TEMP_CMP_NTC4_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5     = COEFF_K_TEMP_CMP_NTC5_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6     = COEFF_K_TEMP_CMP_NTC6_HV_CHRG * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_HV_CHRG;
    }
    else
    {
        stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd        = TEMP_CMP_ARM_BD_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd        = TEMP_CMP_DSP_BD_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0     = TEMP_CMP_NTC0_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1     = TEMP_CMP_NTC1_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2     = TEMP_CMP_NTC2_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3     = TEMP_CMP_NTC3_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4     = TEMP_CMP_NTC4_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5     = TEMP_CMP_NTC5_HV_CHRG;
        stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6     = TEMP_CMP_NTC6_HV_CHRG;
    }

#if(1U == GRID_PHASE_NUMBER)
    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFive((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc0 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0), \
                           (stComIf.ftTempNtc1 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempChrgPrm.ftTempMax = ftFcn_MaxOfFive(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5), \
                                             (stComIf.ftTempNtc6 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc6));

    l_ftTempMin = ftFcn_MinOfFive(stCmnAdc.ftTempDspBd, stComIf.ftTempArmBd, stComIf.ftTempNtc0, stComIf.ftTempNtc1, stComIf.ftTempNtc2);
    stPowLimLoc.stTempChrgPrm.ftTempMin = ftFcn_MinOfFive(l_ftTempMin, stComIf.ftTempNtc3, stComIf.ftTempNtc4, stComIf.ftTempNtc5, stComIf.ftTempNtc6);
#elif(2U == GRID_PHASE_NUMBER)
    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFour((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc1 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc1), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempChrgPrm.ftTempMax = ftFcn_MaxOfFour(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5));
											
    l_ftTempMin = ftFcn_MinOfFour(stCmnAdc.ftTempDspBd, stComIf.ftTempArmBd, stComIf.ftTempNtc1, stComIf.ftTempNtc2);
    stPowLimLoc.stTempChrgPrm.ftTempMin = ftFcn_MinOfFour(l_ftTempMin, stComIf.ftTempNtc3, stComIf.ftTempNtc4, stComIf.ftTempNtc5);
#else
    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFour((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempChrgPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc0 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc0), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempChrgPrm.ftTempMax = ftFcn_MaxOfFour(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempChrgPrm.stTempComp.ftTempNtc5));
    l_ftTempMin = ftFcn_MinOfFour(stCmnAdc.ftTempDspBd, stComIf.ftTempArmBd, stComIf.ftTempNtc0, stComIf.ftTempNtc2);
    stPowLimLoc.stTempChrgPrm.ftTempMin = ftFcn_MinOfFour(l_ftTempMin, stComIf.ftTempNtc3, stComIf.ftTempNtc4, stComIf.ftTempNtc5);
#endif

    if(FCN_ENABLE == stComTbl.stPrmPowLim.unCmd.bit.uiEnaHTPowLim)
    {
        /* Power Limit High Temperature Coefficient Calculation */
        if(FAN_RUN_MODE_IS_NORMAL)
        {
            if(stPowLimLoc.stTempChrgPrm.ftTempMax <= TEMP_DWN_POW_LIM_HT)          ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_DWN_HT_PL;
            }
            else if(stPowLimLoc.stTempChrgPrm.ftTempMax >= TEMP_UP_POW_LIM_HT)       ///< Power Limit High Temperature Up
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_UP_HT_PL;
            }
            else
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_K_HT_PL * stPowLimLoc.stTempChrgPrm.ftTempMax + COEFF_B_HT_PL;
            }
        }
        else
        {
            if(stPowLimLoc.stTempChrgPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT1)          ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_DWN_SILENCE_HT_PL;
            }
            else if(stPowLimLoc.stTempChrgPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT2)     ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_K_SILENCE_HT_PL_UP * stPowLimLoc.stTempChrgPrm.ftTempMax + COEFF_B_SILENCE_HT_PL_UP;
            }
            else if(stPowLimLoc.stTempChrgPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT3)     ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_MID_SILENCE_HT_PL;
            }
            else if(stPowLimLoc.stTempChrgPrm.ftTempMax <= TEMP_UP_SILENCE_POW_LIM_HT)       ///< Power Limit High Temperature Up
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_K_SILENCE_HT_PL_DWN * stPowLimLoc.stTempChrgPrm.ftTempMax + COEFF_B_SILENCE_HT_PL_DWN;
            }
            else
            {
                stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt = COEFF_UP_SILENCE_HT_PL;
            }
        }

        /* Power Limit High Temperature Coefficient Step */
        if(stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt  - stPowLimLoc.stTempChrgPrm.ftCoeffHT > COEFF_STEP_HT_PL)
        {
            stPowLimLoc.stTempChrgPrm.ftCoeffHT += COEFF_STEP_HT_PL;
        }
        else if(stPowLimLoc.stTempChrgPrm.ftCoeffHT - stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt  > COEFF_STEP_HT_PL)
        {
            stPowLimLoc.stTempChrgPrm.ftCoeffHT -= COEFF_STEP_HT_PL;
        }
        else
        {
            stPowLimLoc.stTempChrgPrm.ftCoeffHT = stPowLimLoc.stTempChrgPrm.ftCoeffHTTgt;
        }

        vFcn_FtUpDwnLim(&stPowLimLoc.stTempChrgPrm.ftCoeffHT, 1.0f, 0.0f);
    }
    else
    {
        stPowLimLoc.stTempChrgPrm.ftCoeffHT = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Charge Power limitation according to low temperature
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Temp_ChrgLow_100ms(void)
{
    float32 l_ftTimTmp = 0.0f;    ///< Temporary time

    if(FCN_ENABLE == stComTbl.stPrmPowLim.unCmd.bit.uiEnaLTPowLim)
    {
        /* Power Limit Low Temperature Coefficient Calculation */
        switch(stPowLimLoc.stTempChrgPrm.enLowTempSts)
        {
            /* Power Limit Low Temperature Initial Status*/
            case LOW_POW_INIT_STS:
                /* Power Limit Low Temperature Time */
                if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_SOFTSTRT)    ///< D2D State Machine Softstart State
                {
                    if(stPowLimLoc.stTempChrgPrm.ftTempMin < TEMP_DWN_LT_PL)        ///< Power Limit High Temperature Down
                    {
                        stPowLimLoc.stTempChrgPrm.ftCoeffLT    = COEFF_DWN_LT_PL;
                        stPowLimLoc.stTempChrgPrm.uiLowTempTim = TIM_DWN_LT_PL;
                    }
                    else if(stPowLimLoc.stTempChrgPrm.ftTempMin < TEMP_UP_LT_PL)    ///< Power Limit High Temperature Up
                    {
                        stPowLimLoc.stTempChrgPrm.ftCoeffLT    = COEFF_K_LT_PL * stPowLimLoc.stTempChrgPrm.ftTempMin + COEFF_B_LT_PL;
                        l_ftTimTmp = COEFF_K_TIM_LT_PL * stPowLimLoc.stTempChrgPrm.ftTempMin + COEFF_B_TIM_LT_PL;
                        stPowLimLoc.stTempChrgPrm.uiLowTempTim = (Uint16)l_ftTimTmp;
                    }
                    else
                    {
                        stPowLimLoc.stTempChrgPrm.ftCoeffLT    = COEFF_UP_LT_PL;
                        stPowLimLoc.stTempChrgPrm.uiLowTempTim = TIM_UP_LT_PL;
                    }
                }
                else
                {
                    stPowLimLoc.stTempChrgPrm.uiLowTempCnt = 0U;
                    stPowLimLoc.stTempChrgPrm.enLowTempSts = LOW_POW_RUN_STS;
                }
                break;

            /* Power Limit Low Temperature Run Status*/
            case LOW_POW_RUN_STS:
                if(fabsf(stD2dAdc.ftCurrBattLpf10Hz) > 0.3f)
                {
                    stPowLimLoc.stTempChrgPrm.uiLowTempCnt++;
                    if(stPowLimLoc.stTempChrgPrm.uiLowTempCnt >= stPowLimLoc.stTempChrgPrm.uiLowTempTim)
                    {
                        stPowLimLoc.stTempChrgPrm.uiLowTempCnt = 0U;
                        stPowLimLoc.stTempChrgPrm.enLowTempSts = ADD_POW_RUN_STS;
                    }
                }
                else if(stPowLimLoc.stTempChrgPrm.uiLowTempCnt > 0U)
                {
                    stPowLimLoc.stTempChrgPrm.uiLowTempCnt--;
                }
                else
                {
                    ///< Do nothing
                }

                if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_SOFTSTRT)     ///< Reset When D2D Run Mode At Standby Or Fault State
                {
                    stPowLimLoc.stTempChrgPrm.enLowTempSts = LOW_POW_INIT_STS;
                }
                break;

            /* Add Power*/
            case ADD_POW_RUN_STS:
                stPowLimLoc.stTempChrgPrm.ftCoeffLT += COEFF_STEP_LT_PL;
                if(stPowLimLoc.stTempChrgPrm.ftCoeffLT >= 1.0f)
                {
                    stPowLimLoc.stTempChrgPrm.ftCoeffLT = 1.0f;
                    stPowLimLoc.stTempChrgPrm.enLowTempSts = ADD_POW_OK_STS;
                }
                vFcn_FtUpDwnLim(&stPowLimLoc.stTempChrgPrm.ftCoeffLT, 1.0f, 0.0f);

                if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB)          ///< Reset When D2D Run Mode At Standby Or Fault State
                {
                    stPowLimLoc.stTempChrgPrm.enLowTempSts = LOW_POW_INIT_STS;
                }
                break;

            /*  Add Power OK Status*/
            case ADD_POW_OK_STS:
                if(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_SOFTSTRT)     ///< Reset When D2D Run Mode At Standby Or Fault State
                {
                    stPowLimLoc.stTempChrgPrm.enLowTempSts = LOW_POW_INIT_STS;
                }
                break;

            default:
                ///< Do nothing
                break;
        }
    }
    else
    {
        stPowLimLoc.stTempChrgPrm.ftCoeffLT = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge Power limitation according to high temperature
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Temp_DchaHigh_100ms(void)
{
    float32 l_ftTempMax = 0.0f;

#if(1U == GRID_PHASE_NUMBER)
    /* Power Limit High Temperature compensation */
    if(stD2dAdc.ftVoltBattLpf100HzEquiv <= LV_BATT_HT_PL_DCHA)     ///< Power Limit High Temperature Low Series Voltage
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_LV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_LV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_LV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_LV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_LV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_LV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_LV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_LV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_LV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV1_BATT_HT_PL_DCHA)      ///< Power Limit High Temperature Middle Series Voltage1
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_LV_DCHA;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV2_BATT_HT_PL_DCHA)
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_MV_DCHA;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= HV_BATT_HT_PL_DCHA)
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_HV_DCHA;
    }
    else
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_HV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_HV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_HV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_HV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_HV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_HV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_HV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_HV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_HV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }

    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFive((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc0 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0), \
                           (stComIf.ftTempNtc1 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempDchaPrm.ftTempMax = ftFcn_MaxOfFive(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5), \
                                             (stComIf.ftTempNtc6 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6));
#elif(2U == GRID_PHASE_NUMBER)
    /* Power Limit High Temperature compensation */
    if(stD2dAdc.ftVoltBattLpf100HzEquiv <= LV_BATT_HT_PL_DCHA)     ///< Power Limit High Temperature Low Series Voltage
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_LV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_LV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_LV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_LV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_LV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_LV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_LV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_LV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_LV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV1_BATT_HT_PL_DCHA)      ///< Power Limit High Temperature Middle Series Voltage1
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_LV_DCHA;
    }
    #if 0
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV2_BATT_HT_PL_DCHA)
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_MV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_MV_DCHA;
    }
    #endif
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= HV_BATT_HT_PL_DCHA)
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_HV_DCHA;
    }
    else
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_HV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_HV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_HV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_HV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_HV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_HV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_HV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_HV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_HV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }
	
    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFour((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc1 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempDchaPrm.ftTempMax = ftFcn_MaxOfFour(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5));
#else
    /* Power Limit High Temperature compensation */
    if(stD2dAdc.ftVoltBattLpf100HzEquiv <= LV_BATT_HT_PL_DCHA)     ///< Power Limit High Temperature Low Series Voltage
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_LV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_LV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_LV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_LV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_LV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_LV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_LV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_LV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_LV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= MV1_BATT_HT_PL_DCHA)      ///< Power Limit High Temperature Middle Series Voltage1
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_LV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_LV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_LV_DCHA;
    }
    else if(stD2dAdc.ftVoltBattLpf100HzEquiv <= HV_BATT_HT_PL_DCHA)
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = COEFF_K_TEMP_CMP_NTC0_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC0_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = COEFF_K_TEMP_CMP_NTC1_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC1_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = COEFF_K_TEMP_CMP_NTC2_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC2_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = COEFF_K_TEMP_CMP_NTC3_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC3_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = COEFF_K_TEMP_CMP_NTC4_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC4_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = COEFF_K_TEMP_CMP_NTC5_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC5_HV_DCHA;
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = COEFF_K_TEMP_CMP_NTC6_HV_DCHA * stD2dAdc.ftVoltBattLpf100HzEquiv + COEFF_B_TEMP_CMP_NTC6_HV_DCHA;
    }
    else
    {
        stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd       = TEMP_CMP_ARM_BD_HV_DCHA;           ///< ARM Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd       = TEMP_CMP_DSP_BD_HV_DCHA;           ///< DSP Board temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0    = TEMP_CMP_NTC0_HV_DCHA;             ///< D2D Port NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc1    = TEMP_CMP_NTC1_HV_DCHA;             ///< PFC slow MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2    = TEMP_CMP_NTC2_HV_DCHA;             ///< PFC quick MOS NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3    = TEMP_CMP_NTC3_HV_DCHA;             ///< D2D up NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4    = TEMP_CMP_NTC4_HV_DCHA;             ///< D2D down NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5    = TEMP_CMP_NTC5_HV_DCHA;             ///< D2D transformer NTC temperature Compensation
        stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc6    = TEMP_CMP_NTC6_HV_DCHA;             ///< D2D inductor NTC temperature Compensation
    }
    /* Compare Max And Min Value*/
    l_ftTempMax = ftFcn_MaxOfFour((stCmnAdc.ftTempDspBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftDspBd), \
                           (stComIf.ftTempArmBd - stPowLimLoc.stTempDchaPrm.stTempComp.ftArmBd), \
                           (stComIf.ftTempNtc0 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc0), \
                           (stComIf.ftTempNtc2 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc2));
    stPowLimLoc.stTempDchaPrm.ftTempMax = ftFcn_MaxOfFour(l_ftTempMax, \
                                             (stComIf.ftTempNtc3 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc3), \
                                             (stComIf.ftTempNtc4 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc4), \
                                             (stComIf.ftTempNtc5 - stPowLimLoc.stTempDchaPrm.stTempComp.ftTempNtc5));

    /* Calculate The Maximum Difference Between The NTC And The Discharging Derating Point */
    stPowLimLoc.ftNtcTempDiffMax = stPowLimLoc.stTempDchaPrm.ftTempMax - TEMP_DWN_POW_LIM_HT;

    /* Power Limit Max Discharge Current According To Max Ntc Temperature */
    if(stPowLimLoc.ftNtcTempDiffMax < TEMP_DIFF_DWN_DCHA)
    {
        stPowLimLoc.ftCurrBattDchaMax = CURR_BATT_MAX_TEMP_DWN_DCHA;
    }
    else if(stPowLimLoc.ftNtcTempDiffMax < TEMP_DIFF_UP_DCHA)
    {
        stPowLimLoc.ftCurrBattDchaMax = COEFF_K_CURR_BATT_MAX_DCHA * stPowLimLoc.ftNtcTempDiffMax + COEEF_B_CURR_BATT_MAX_DCHA;
    }
    else
    {
        stPowLimLoc.ftCurrBattDchaMax = CURR_BATT_MAX_TEMP_UP_DCHA;
    }
#endif

    if(FCN_ENABLE == stComTbl.stPrmPowLim.unCmd.bit.uiEnaHTPowLim)
    {
        /* Power Limit High Temperature Down Coefficient Calculation */
        if(FAN_RUN_MODE_IS_NORMAL)
        {
            if(stPowLimLoc.stTempDchaPrm.ftTempMax  <= TEMP_DWN_POW_LIM_HT)       ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_DWN_HT_PL;
            }
            else if(stPowLimLoc.stTempDchaPrm.ftTempMax >= TEMP_UP_POW_LIM_HT)   ///< Power Limit High Temperature Up
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_UP_HT_PL;
            }
            else
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_K_HT_PL * stPowLimLoc.stTempDchaPrm.ftTempMax + COEFF_B_HT_PL;
            }
        }
        else
        {
            if(stPowLimLoc.stTempDchaPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT1)          ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_DWN_SILENCE_HT_PL;            
            }
            else if(stPowLimLoc.stTempDchaPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT2)     ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_K_SILENCE_HT_PL_UP * stPowLimLoc.stTempDchaPrm.ftTempMax + COEFF_B_SILENCE_HT_PL_UP; 
            }
            else if(stPowLimLoc.stTempDchaPrm.ftTempMax <= TEMP_DWN_SILENCE_POW_LIM_HT3)     ///< Power Limit High Temperature Down
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_MID_SILENCE_HT_PL;   
            }
            else if(stPowLimLoc.stTempDchaPrm.ftTempMax <= TEMP_UP_SILENCE_POW_LIM_HT)       ///< Power Limit High Temperature Up
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_K_SILENCE_HT_PL_DWN * stPowLimLoc.stTempDchaPrm.ftTempMax + COEFF_B_SILENCE_HT_PL_DWN;
            }
            else
            {
                stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt = COEFF_UP_SILENCE_HT_PL;
            }
        }

        /* Power Limit High Temperature Down Coefficient Step */
        if(stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt - stPowLimLoc.stTempDchaPrm.ftCoeffHT > COEFF_STEP_HT_PL)
        {
         stPowLimLoc.stTempDchaPrm.ftCoeffHT += COEFF_STEP_HT_PL;
        }
        else if(stPowLimLoc.stTempDchaPrm.ftCoeffHT - stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt > COEFF_STEP_HT_PL)
        {
         stPowLimLoc.stTempDchaPrm.ftCoeffHT -= COEFF_STEP_HT_PL;
        }
        else
        {
         stPowLimLoc.stTempDchaPrm.ftCoeffHT = stPowLimLoc.stTempDchaPrm.ftCoeffHTTgt;
        }

        vFcn_FtUpDwnLim(&stPowLimLoc.stTempDchaPrm.ftCoeffHT, 1.0f, 0.0f);
    }
    else
    {
        stPowLimLoc.stTempDchaPrm.ftCoeffHT = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Discharge Power limitation according to low temperature
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_Temp_DchaLow_100ms(void)
{
    stPowLimLoc.stTempDchaPrm.ftCoeffLT = stPowLimLoc.stTempChrgPrm.ftCoeffLT;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        High temperature limitation status
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_HTSt_100ms(void)
{
    if(((stD2dAdc.ftCurrBattLpf10Hz > 0.0f) && FLOAT_PRM_IS_NOT_EQUAL(stPowLimLoc.stPrmChrgLim.ftCoeffHT, 1.0f)) \
       || ((stD2dAdc.ftCurrBattLpf10Hz < 0.0f) && FLOAT_PRM_IS_NOT_EQUAL(stPowLimLoc.stPrmDchaLim.ftCoeffHT, 1.0f)))
    {
        stPowLimLoc.stPrmExt.uiFlgHTLim = 1U;       ///< Set high Temperature limit flag
    }
    else
    {
        stPowLimLoc.stPrmExt.uiFlgHTLim = 0U;       ///< Clear high Temperature limit flag
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fan Duty limitation according to Max temperature
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PowLim_FanDutyCal_100ms(void)
{
    static Uint16 sl_uiFlgD2dRun   = 0U;    ///< D2D run flag
    static Uint16 sl_uiCntrD2dStop = 0U;    ///< D2D stop counter

    /* Fan Duty Limit High Temperature  */
    if((D2D_ST_MAC_NORMRUN == stD2dStMac.uiStD2dRun) && (INS_DET_ST_IS_OFF))    ///< Fan works when DCDC NORMRUN and no insulation detection
    {
        sl_uiFlgD2dRun   = 1U;    ///< Set D2D run flag
        sl_uiCntrD2dStop = 0U;    ///< Clear D2D stop counter

        if(stPowLimLoc.ftTempMaxFanCtrl <= TEMP_DWN_HYS_FAN_DUTY)        ///< Fan Duty Limit High Temperature Down Hysteresis Value
        {
            stPowLimLoc.ftFanDutyTgt = DUTY_FAN_START;
        }
        else if(stPowLimLoc.ftTempMaxFanCtrl <= TEMP_DWN_FAN_DUTY)       ///< Fan Duty Limit High Temperature Down
        {
            if(stPowLimLoc.ftFanDutyTgt < DUTY_HYS_DWN_FAN)              ///< Fan Duty Limit High Temperature Down Coefficient Hysteresis Flag
            {
                stPowLimLoc.ftFanDutyTgt = DUTY_FAN_START;
            }
            else
            {
                stPowLimLoc.ftFanDutyTgt = DUTY_DWN_FAN;
            }
        }
        else if(stPowLimLoc.ftTempMaxFanCtrl <= TEMP_MID_FAN_DUTY)       ///< Fan Duty Limit High Temperature Middle
        {
            stPowLimLoc.ftFanDutyTgt = COEFF_K_FAN_DUTY_DWN * stPowLimLoc.ftTempMaxFanCtrl + COEFF_B_FAN_DUTY_DWN;
        }
        else if(stPowLimLoc.ftTempMaxFanCtrl <= TEMP_UP_FAN_DUTY)        ///< Fan Duty Limit High Temperature Up
        {
            stPowLimLoc.ftFanDutyTgt = COEFF_K_FAN_DUTY_UP * stPowLimLoc.ftTempMaxFanCtrl + COEFF_B_FAN_DUTY_UP;
        }
        else
        {
            stPowLimLoc.ftFanDutyTgt = DUTY_UP_FAN;
        }

        if(FAN_RUN_MODE_IS_SILENT)
        {
            UP_LIMIT(stPowLimLoc.ftFanDutyTgt, DUTY_MID_FAN);    ///< Limit fan max duty in silent mode
        }
    }
    else if(1U == sl_uiFlgD2dRun)    ///< Fan stop after delay time
    {
        sl_uiCntrD2dStop++;
        if(sl_uiCntrD2dStop >= TIME_FAN_DELAY_STOP)
        {
            sl_uiFlgD2dRun   = 0U;    ///< Clear D2D run flag
            sl_uiCntrD2dStop = 0U;    ///< Clear D2D stop counter
        }
    }
    else
    {
        stPowLimLoc.ftFanDutyTgt = DUTY_FAN_START;
    }

    /* Fan Duty Coefficient Step */
    if(stPowLimLoc.ftFanDutyTgt  - stPowLimLoc.stPrmExt.ftFanDuty > STEP_FAN_DUTY)
    {
        stPowLimLoc.stPrmExt.ftFanDuty += STEP_FAN_DUTY;              ///< Add fan duty step
    }
    else if(stPowLimLoc.stPrmExt.ftFanDuty - stPowLimLoc.ftFanDutyTgt  > STEP_FAN_DUTY)
    {
        stPowLimLoc.stPrmExt.ftFanDuty -= STEP_FAN_DUTY;              ///< Reduce fan duty step
    }
    else
    {
        stPowLimLoc.stPrmExt.ftFanDuty = stPowLimLoc.ftFanDutyTgt;
    }

    vFcn_FtUpDwnLim(&stPowLimLoc.stPrmExt.ftFanDuty, 1.0f, DUTY_FAN_START);
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

