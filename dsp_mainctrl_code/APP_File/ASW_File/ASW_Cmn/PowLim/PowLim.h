//==============================================================================================
//    File description
//==============================================================================================
/**@file         PowLim.h
 * @brief
 * The header file of power limitation is designed to realize peripheral function.
 *
 * Module      :                       \n
 * PowLim
 *
 * Unit        :                       \n
 *                                     \n
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

#ifndef POWLIM_H_
#define POWLIM_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PowLimExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "CmnAdcExt.h"
#include "D2dAdcExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PfcGridCtrl.h"
#include "PerdTskExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/*High Temperature Power Limit Macro Definition */
#define COEFF_DWN_HT_PL                 1.0f        ///< Power Limit High Temperature Down power Coefficient
#define COEFF_UP_HT_PL                  0.0f        ///< Power Limit High Temperature Up power Coefficient
#define COEFF_K_HT_PL                   ((COEFF_DWN_HT_PL - COEFF_UP_HT_PL) / (TEMP_DWN_POW_LIM_HT - TEMP_UP_POW_LIM_HT))
#define COEFF_B_HT_PL                   (COEFF_DWN_HT_PL - COEFF_K_HT_PL * TEMP_DWN_POW_LIM_HT)
#define COEFF_DWN_SILENCE_HT_PL         1.0f        ///< Power Limit High Temperature Down power Coefficient
#if 1U == GRID_PHASE_NUMBER
#define COEFF_MID_SILENCE_HT_PL         0.68f       ///< Power Limit High Temperature middle power Coefficient
#elif 2U == GRID_PHASE_NUMBER
#define COEFF_MID_SILENCE_HT_PL         0.68f       ///< Power Limit High Temperature middle power Coefficient
#elif 3U == GRID_PHASE_NUMBER
#define COEFF_MID_SILENCE_HT_PL         0.66f       ///< Power Limit High Temperature middle power Coefficient
#endif
#define COEFF_UP_SILENCE_HT_PL          0.0f        ///< Power Limit High Temperature Up power Coefficient
#define COEFF_K_SILENCE_HT_PL_UP        ((COEFF_DWN_SILENCE_HT_PL - COEFF_MID_SILENCE_HT_PL) / (TEMP_DWN_SILENCE_POW_LIM_HT1 - TEMP_DWN_SILENCE_POW_LIM_HT2))
#define COEFF_B_SILENCE_HT_PL_UP        (COEFF_DWN_SILENCE_HT_PL - COEFF_K_SILENCE_HT_PL_UP * TEMP_DWN_SILENCE_POW_LIM_HT1)
#define COEFF_K_SILENCE_HT_PL_DWN       ((COEFF_MID_SILENCE_HT_PL - COEFF_UP_SILENCE_HT_PL) / (TEMP_DWN_SILENCE_POW_LIM_HT3 - TEMP_UP_SILENCE_POW_LIM_HT))
#define COEFF_B_SILENCE_HT_PL_DWN       (COEFF_MID_SILENCE_HT_PL - COEFF_K_SILENCE_HT_PL_DWN * TEMP_DWN_SILENCE_POW_LIM_HT3)

#ifndef _SIMULATION_NO_DSP_
#define COEFF_STEP_HT_PL                0.01f       ///< Power Limit High Temperature power Coefficient Step: 1%/100ms
#else
#define COEFF_STEP_HT_PL                0.1f        ///< Power Limit High Temperature power Coefficient Step: 10%/100ms
#endif

/*Low temperature power limitation Macro Definition*/
#define TEMP_DWN_LT_PL                  -35.0f      ///< Power Limit High Temperature Down
#define TEMP_UP_LT_PL                   -22.0f      ///< Power Limit High Temperature Up
#define COEFF_DWN_LT_PL                 0.1f        ///< Power Limit Low Temperature Down power Power
#define COEFF_UP_LT_PL                  1.0f        ///< Power Limit Low Temperature Up power Power
#define COEFF_K_LT_PL                   ((COEFF_UP_LT_PL - COEFF_DWN_LT_PL) / (TEMP_UP_LT_PL - TEMP_DWN_LT_PL))
#define COEFF_B_LT_PL                   (COEFF_UP_LT_PL - COEFF_K_LT_PL * TEMP_UP_LT_PL)

#ifndef _SIMULATION_NO_DSP_
#define TIM_DWN_LT_PL                   6000U       ///< Power Limit Low Temperature Down Timer: 6000*100ms = 600s
#define TIM_UP_LT_PL                    0U          ///< Power Limit Low Temperature Up Power Timer
#define COEFF_STEP_LT_PL                0.001f      ///< 0.1%/100ms
#else
#define TIM_DWN_LT_PL                   5U          ///< Power Limit Low Temperature Down Timer: 5*100ms = 0.5s
#define TIM_UP_LT_PL                    1U          ///< Power Limit Low Temperature Up Power Timer: 1*100ms = 0.1s
#define COEFF_STEP_LT_PL                0.1f        ///< 10%/100ms
#endif
#define COEFF_K_TIM_LT_PL               (((float32)TIM_UP_LT_PL - (float32)TIM_DWN_LT_PL) / (TEMP_UP_LT_PL - TEMP_DWN_LT_PL))
#define COEFF_B_TIM_LT_PL               ((float32)TIM_UP_LT_PL - COEFF_K_TIM_LT_PL * TEMP_UP_LT_PL)

/* AC voltage charge power limitation Macro Definition */
#if(2U == GRID_PHASE_NUMBER)
#define VOLT_AC_DWN_PL_CHRG             (100.0f * 0.5f)		///< Charge power limitation down AC voltage
#define VOLT_AC_RTD_PL_CHRG	            (240.0f * 0.5f)		///< Charge power limitation rated AC voltage
#else
#define VOLT_AC_DWN_PL_CHRG             100.0f	    ///< Charge power limitation down AC voltage
#define VOLT_AC_RTD_PL_CHRG	            230.0f	    ///< Charge power limitation rated AC voltage
#endif
#define COEFF_DWN_VOLT_AC_PL_CHRG       (VOLT_AC_DWN_PL_CHRG / VOLT_AC_RTD_PL_CHRG)    ///< Down AC voltage power coefficient
#define COEFF_RTD_VOLT_AC_PL_CHRG       1.0f        ///< Rated AC voltage power coefficient
#define COEFF_K_VOLT_AC_PL_CHRG         ((COEFF_RTD_VOLT_AC_PL_CHRG - COEFF_DWN_VOLT_AC_PL_CHRG) / (VOLT_AC_RTD_PL_CHRG - VOLT_AC_DWN_PL_CHRG))    ///< AC voltage Charge power limitation CofK
#define COEFF_B_VOLT_AC_PL_CHRG         (COEFF_RTD_VOLT_AC_PL_CHRG - COEFF_K_VOLT_AC_PL_CHRG * VOLT_AC_RTD_PL_CHRG)    ///< AC voltage Charge power limitation CofB
/* AC voltage discharge power limitation Macro Definition */
#if(2U == GRID_PHASE_NUMBER)
#define VOLT_AC_DWN_PL_DCHA             (100.0f * 0.5f)	///< Discharge power limitation down AC voltage
#define VOLT_AC_RTD_PL_DCHA	            (240.0f * 0.5f)	///< Discharge power limitation rated AC voltage
#else
#define VOLT_AC_DWN_PL_DCHA             100.0f	    ///< Discharge power limitation down AC voltage
#define VOLT_AC_RTD_PL_DCHA	            230.0f	    ///< Discharge power limitation rated AC voltage
#endif
#define COEFF_DWN_VOLT_AC_PL_DCHA       (VOLT_AC_DWN_PL_DCHA / VOLT_AC_RTD_PL_DCHA)    ///< Down AC voltage power coefficient
#define COEFF_RTD_VOLT_AC_PL_DCHA       1.0f        ///< Rated AC voltage power coefficient
#define COEFF_K_VOLT_AC_PL_DCHA         ((COEFF_RTD_VOLT_AC_PL_DCHA - COEFF_DWN_VOLT_AC_PL_DCHA) / (VOLT_AC_RTD_PL_DCHA - VOLT_AC_DWN_PL_DCHA))    ///< AC voltage Discharge power limitation CofK
#define COEFF_B_VOLT_AC_PL_DCHA         (COEFF_RTD_VOLT_AC_PL_DCHA - COEFF_K_VOLT_AC_PL_DCHA * VOLT_AC_RTD_PL_DCHA)    ///< AC voltage Discharge power limitation CofB

/* DC voltage charge power limitation Macro Definition */
#define VOLT_BATT_DWN_PL_CHRG           VOLT_BATT_MIN	       ///< Charge power limitation down DC voltage
#define VOLT_BATT_RTD_PL_CHRG	        VOLT_BATT_PARL_RTD	   ///< Charge power limitation rated DC voltage
#define COEFF_DWN_VOLT_BATT_PL_CHRG     (VOLT_BATT_DWN_PL_CHRG / VOLT_BATT_RTD_PL_CHRG)    ///< Down DC voltage power coefficient
#define COEFF_RTD_VOLT_BATT_PL_CHRG     1.0f        ///< Rated DC voltage power coefficient
#define COEFF_K_VOLT_BATT_PL_CHRG       ((COEFF_RTD_VOLT_BATT_PL_CHRG - COEFF_DWN_VOLT_BATT_PL_CHRG)/(VOLT_BATT_RTD_PL_CHRG - VOLT_BATT_DWN_PL_CHRG))    ///< DC voltage charge power limitation CofK
#define COEFF_B_VOLT_BATT_PL_CHRG       (COEFF_RTD_VOLT_BATT_PL_CHRG - COEFF_K_VOLT_BATT_PL_CHRG * VOLT_BATT_RTD_PL_CHRG)    ///< DC voltage charge power limitation CofB

#define VOLT_BATT_LO_PL_CHRG            150.0f      ///< Charge power limit low battery voltage
#define COEFF_LO_VOLT_BATT_PL_CHRG      0.05f       ///< Low DC voltage power coefficient
#define COEFF_K_VOLT_BATT_LO_PL_CHRG    ((COEFF_DWN_VOLT_BATT_PL_CHRG - COEFF_LO_VOLT_BATT_PL_CHRG) / (VOLT_BATT_DWN_PL_CHRG - VOLT_BATT_LO_PL_CHRG))
#define COEFF_B_VOLT_BATT_LO_PL_CHRG    (COEFF_DWN_VOLT_BATT_PL_CHRG - COEFF_K_VOLT_BATT_LO_PL_CHRG * VOLT_BATT_DWN_PL_CHRG)

/* DC voltage discharge power limitation Macro Definition */
#define VOLT_BATT_DWN_PL_DCHA           VOLT_BATT_MIN	      ///< Discharge power limitation down DC voltage
#define VOLT_BATT_RTD_PL_DCHA	        VOLT_BATT_PARL_RTD	  ///< Discharge power limitation rated DC voltage

#if 1U == GRID_PHASE_NUMBER
#define COEFF_DWN_VOLT_BATT_PL_DCHA     0.2f        ///< Down DC voltage coefficient; 0.05f;(VOLT_BATT_DWN_PL_DCHA/VOLT_BATT_RTD_PL_DCHA)
#elif 2U == GRID_PHASE_NUMBER
#define COEFF_DWN_VOLT_BATT_PL_DCHA     0.4f        ///< Down DC voltage coefficient; 0.05f;(VOLT_BATT_DWN_PL_DCHA/VOLT_BATT_RTD_PL_DCHA)
#else
#define COEFF_DWN_VOLT_BATT_PL_DCHA     0.67f       ///< Down DC voltage coefficient; 0.05f;(VOLT_BATT_DWN_PL_DCHA/VOLT_BATT_RTD_PL_DCHA)
#endif
#define COEFF_RTD_VOLT_BATT_PL_DCHA     1.0f        ///< Rated DC voltage coefficient
#define COEFF_K_VOLT_BATT_PL_DCHA       ((COEFF_RTD_VOLT_BATT_PL_DCHA - COEFF_DWN_VOLT_BATT_PL_DCHA) / (VOLT_BATT_RTD_PL_DCHA - VOLT_BATT_DWN_PL_DCHA))    ///< DC voltage Discharge power limitation CofK
#define COEFF_B_VOLT_BATT_PL_DCHA       (COEFF_RTD_VOLT_BATT_PL_DCHA - COEFF_K_VOLT_BATT_PL_DCHA * VOLT_BATT_RTD_PL_DCHA)    ///< DC voltage Discharge power limitation CofB

#define VOLT_BATT_LO_PL_DCHA            180.0f      ///< Discharge power limit low battery voltage
#define COEFF_LO_VOLT_BATT_PL_DCHA      0.0f        ///< Low DC voltage power coefficient
#define COEFF_K_VOLT_BATT_LO_PL_DCHA    ((COEFF_DWN_VOLT_BATT_PL_DCHA - COEFF_LO_VOLT_BATT_PL_DCHA) / (VOLT_BATT_DWN_PL_DCHA - VOLT_BATT_LO_PL_DCHA))
#define COEFF_B_VOLT_BATT_LO_PL_DCHA    (COEFF_DWN_VOLT_BATT_PL_DCHA - COEFF_K_VOLT_BATT_LO_PL_DCHA * VOLT_BATT_DWN_PL_DCHA)

#if 1U == GRID_PHASE_NUMBER
#define VOLT_BATT_SPCL_RTD_PL_DCHA      (VOLT_BATT_RTD_PL_DCHA + 10.0f)    ///< Special battery voltage:can not discharge 7.4kW when battery voltage 300V
#define POW_ACT_RTD_PL_DCHA             (0.99f * POW_AC_RTD)               ///< Special discharge power
#endif

/* Power compensation Macro Definition */
#define KP_POW_COMP_CURR                10.0f                     ///< Kp of Power compensation accrding to current
#define KI_POW_COMP_CURR                10.0f                     ///< Ki of Power compensation accrding to current
#define KP_POW_COMP_POW                 0.2f                      ///< Kp of Power compensation accrding to power; 100ms PI
#define KI_POW_COMP_POW                 0.1f                      ///< Ki of Power compensation accrding to power; 100ms PI
#define MAX_POW_COMP_CHRG               (0.03f * RATED_POW)       ///< Max charge power limitation of PI output; 3%
#define MIN_POW_COMP_CHRG               (-0.01f * RATED_POW)      ///< Min charge power limitation of PI output; 1%
#define MAX_POW_COMP_DCHA               (0.03f * RATED_POW)       ///< Max discharge power limitation of PI output; 3%
#define MIN_POW_COMP_DCHA               0.0f                      ///< Min discharge power limitation of PI output; 0% - 7.4kW Discharge power is insufficient when battery voltage is 300V

/* Bus voltage limitation Macro Definition */
#if(1U == GRID_PHASE_NUMBER)
#define GAIN_CLLC_RSN                   0.87f                     ///< CLLC resonance gain
#define RAT_TR                          (12.0f/11.0f)             ///< Transformer Ratio
#define COEFF_BUS_BATT_VOLT             (RAT_TR/GAIN_CLLC_RSN)    ///< Bus voltage and out voltage coefficient
#elif(2U == GRID_PHASE_NUMBER)
#define GAIN_CLLC_RSN                   0.887f    				  ///< CLLC resonance gain
#define RAT_TR                          (16.0f/18.0f)    		  ///< Transformer Ratio
#define COEFF_BUS_BATT_VOLT             (RAT_TR/GAIN_CLLC_RSN)    ///< Bus voltage and out voltage coefficient
#elif(3U == GRID_PHASE_NUMBER)
#define RAT_TR                          (30.0f/17.0f)             ///< Transformer Ratio;30:17
#define COEFF_BUS_BATT_VOLT             RAT_TR                    ///< Bus voltage and out voltage coefficient
#endif

/* Temperature Power Limit Macro Definition */
/* DSP Core Temperature Compensation */
#if(1U == GRID_PHASE_NUMBER)
#define TEMP_CMP_DSP_CORE_CHRG          (100.0f - TEMP_DWN_POW_LIM_HT)    ///< High temperature power limit DSP CORE temperature compensation
#define TEMP_CMP_DSP_CORE_DCHA          TEMP_CMP_DSP_CORE_CHRG
#elif(2U == GRID_PHASE_NUMBER)
#define TEMP_CMP_DSP_CORE_CHRG          (100.0f - TEMP_DWN_POW_LIM_HT)    ///< High temperature power limit DSP CORE temperature compensation
#define TEMP_CMP_DSP_CORE_DCHA          TEMP_CMP_DSP_CORE_CHRG
#elif(3U == GRID_PHASE_NUMBER)
#define TEMP_CMP_DSP_CORE_CHRG          (112.0f - TEMP_DWN_POW_LIM_HT)    ///< High temperature power limit DSP CORE temperature compensation
#define TEMP_CMP_DSP_CORE_DCHA      	TEMP_CMP_DSP_CORE_CHRG
#endif

#if(1U == GRID_PHASE_NUMBER)
/********************** High Temperature Compensation in charge mode **********************/
#define LV_BATT_HT_PL_CHRG              200.0f      ///< High temperature power limit low battery Voltage in charge mode
#define MV_BATT_HT_PL_CHRG              400.0f      ///< High temperature power limit middle battery Voltage in charge mode
#define HV_BATT_HT_PL_CHRG              500.0f      ///< High temperature power limit high battery Voltage in charge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_CHRG         (90.0f - TEMP_DWN_POW_LIM_HT)    ///< LV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_MV_CHRG         (83.0f - TEMP_DWN_POW_LIM_HT)    ///< MV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_HV_CHRG         (86.0f - TEMP_DWN_POW_LIM_HT)    ///< HV DSP board temperature compensation in charge mode
/* ARM BOARD Temperature Compensation */
#if(IEC_GRID_STD == GRID_STD_ID)
#define TEMP_CMP_ARM_BD_LV_CHRG         (100.0f - TEMP_DWN_POW_LIM_HT)    ///< LV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_MV_CHRG         (98.0f - TEMP_DWN_POW_LIM_HT)     ///< MV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_HV_CHRG         (100.0f - TEMP_DWN_POW_LIM_HT)    ///< HV ARM board temperature compensation in charge mode
#else
#define TEMP_CMP_ARM_BD_LV_CHRG         (90.0f - TEMP_DWN_POW_LIM_HT)     ///< LV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_MV_CHRG         (88.0f - TEMP_DWN_POW_LIM_HT)     ///< MV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_HV_CHRG         (90.0f - TEMP_DWN_POW_LIM_HT)     ///< HV ARM board temperature compensation in charge mode
#endif
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)    ///< Terminal temperature; LV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_MV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)    ///< Terminal temperature; MV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_HV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)    ///< Terminal temperature; HV NTC0 temperature compensation in charge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_CHRG           (75.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC Slow MOS NTC; LV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_MV_CHRG           (68.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC Slow MOS NTC; MV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_HV_CHRG           (71.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC Slow MOS NTC; HV NTC1 temperature compensation in charge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_CHRG           (75.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC quick MOS NTC; LV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_MV_CHRG           (68.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC quick MOS NTC; MV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_HV_CHRG           (71.0f - TEMP_DWN_POW_LIM_HT)     ///< PFC quick MOS NTC; HV NTC2 temperature compensation in charge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_CHRG           (76.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D up NTC; LV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_MV_CHRG           (68.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D up NTC; MV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_HV_CHRG           (70.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D up NTC; HV NTC3 temperature compensation in charge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_CHRG           (76.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D down NTC; LV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_MV_CHRG           (68.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D down NTC; MV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_HV_CHRG           (70.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D down NTC; HV NTC4 temperature compensation in charge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_CHRG           (79.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D transformer NTC; LV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_MV_CHRG           (76.5f - TEMP_DWN_POW_LIM_HT)     ///< D2D transformer NTC; MV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_HV_CHRG           (80.0f - TEMP_DWN_POW_LIM_HT)     ///< D2D transformer NTC; HV NTC5 temperature compensation in charge mode
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_CHRG           (75.5f - TEMP_DWN_POW_LIM_HT)     ///< D2D inductor NTC; LV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_MV_CHRG           (74.5f - TEMP_DWN_POW_LIM_HT)     ///< D2D inductor NTC; MV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_HV_CHRG           (77.5f - TEMP_DWN_POW_LIM_HT)     ///< D2D inductor NTC; HV NTC6 temperature compensation in charge mode

/********************** High Temperature Compensation in discharge mode **********************/
#define LV_BATT_HT_PL_DCHA              200.0f      ///< High temperature power limit low battery Voltage in discharge mode
#define MV1_BATT_HT_PL_DCHA             300.0f      ///< High temperature power limit middle battery Voltage 1 in discharge mode
#define MV2_BATT_HT_PL_DCHA             400.0f      ///< High temperature power limit middle battery Voltage 2 in discharge mode
#define HV_BATT_HT_PL_DCHA              500.0f      ///< High temperature power limit high battery Voltage in discharge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_DCHA         (71.5f - TEMP_DWN_POW_LIM_HT)    ///< LV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_MV_DCHA         (86.5f - TEMP_DWN_POW_LIM_HT)    ///< MV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_HV_DCHA         (90.0f - TEMP_DWN_POW_LIM_HT)    ///< HV DSP board temperature compensation in discharge mode
/* ARM BOARD Temperature Compensation */
#if(IEC_GRID_STD == GRID_STD_ID)
#define TEMP_CMP_ARM_BD_LV_DCHA         (85.0f - TEMP_DWN_POW_LIM_HT)    ///< LV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_MV_DCHA         (98.0f - TEMP_DWN_POW_LIM_HT)    ///< MV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_HV_DCHA         (101.0f - TEMP_DWN_POW_LIM_HT)   ///< HV ARM board temperature compensation in discharge mode
#else
#define TEMP_CMP_ARM_BD_LV_DCHA         (75.0f - TEMP_DWN_POW_LIM_HT)    ///< LV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_MV_DCHA         (88.0f - TEMP_DWN_POW_LIM_HT)    ///< MV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_HV_DCHA         (91.0f - TEMP_DWN_POW_LIM_HT)    ///< HV ARM board temperature compensation in discharge mode
#endif
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< Terminal temperature; LV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_MV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< Terminal temperature; MV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_HV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< Terminal temperature; HV NTC0 temperature compensation in discharge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_DCHA           (57.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC Slow MOS NTC temperature; LV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_MV_DCHA           (68.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC Slow MOS NTC temperature; MV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_HV_DCHA           (70.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC Slow MOS NTC temperature; HV NTC1 temperature compensation in discharge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_DCHA           (57.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC quick MOS NTC temperature; LV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_MV_DCHA           (68.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC quick MOS NTC temperature; MV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_HV_DCHA           (70.0f - TEMP_DWN_POW_LIM_HT)    ///< PFC quick MOS NTC temperature; HV NTC2 temperature compensation in discharge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_DCHA           (57.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D up NTC temperature; LV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_MV_DCHA           (68.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D up NTC temperature; MV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_HV_DCHA           (70.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D up NTC temperature; HV NTC3 temperature compensation in discharge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_DCHA           (57.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D down NTC temperature; LV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_MV_DCHA           (68.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D down NTC temperature; MV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_HV_DCHA           (70.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D down NTC temperature; HV NTC4 temperature compensation in discharge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_DCHA           (61.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D transformer NTC temperature;Power Limit High Temperature Low Series Voltage Temperature Compensation
#define TEMP_CMP_NTC5_MV_DCHA           (77.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D transformer NTC temperature;Power Limit High Temperature Middle Series Voltage Temperature Compensation
#define TEMP_CMP_NTC5_HV_DCHA           (84.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D transformer NTC temperature;Power Limit High Temperature High Series Voltage Temperature Compensation
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_DCHA           (61.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D inductor NTC temperature;Power Limit High Temperature Low Series Voltage Temperature Compensation
#define TEMP_CMP_NTC6_MV_DCHA           (74.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D inductor NTC temperature;Power Limit High Temperature Middle Series Voltage Temperature Compensation
#define TEMP_CMP_NTC6_HV_DCHA           (79.0f - TEMP_DWN_POW_LIM_HT)    ///< D2D inductor NTC temperature;Power Limit High Temperature High Series Voltage Temperature Compensation

#elif(2U == GRID_PHASE_NUMBER)
/********************** High Temperature Compensation in charge mode **********************/
#define LV_BATT_HT_PL_CHRG              250.0f      ///< High temperature power limit low battery Voltage in charge mode
#define MV_BATT_HT_PL_CHRG              300.0f      ///< High temperature power limit middle battery Voltage in charge mode
#define HV_BATT_HT_PL_CHRG              500.0f      ///< High temperature power limit high battery Voltage in charge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_CHRG         (101.8f - TEMP_DWN_POW_LIM_HT)   ///< LV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_MV_CHRG         (103.1f - TEMP_DWN_POW_LIM_HT)   ///< MV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_HV_CHRG         (94.8f - TEMP_DWN_POW_LIM_HT)    ///< HV DSP board temperature compensation in charge mode
/* ARM BOARD Temperature Compensation */
#define TEMP_CMP_ARM_BD_LV_CHRG         (96.0f - TEMP_DWN_POW_LIM_HT)    ///< LV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_MV_CHRG         (99.0f - TEMP_DWN_POW_LIM_HT)    ///< MV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_HV_CHRG         (95.0f - TEMP_DWN_POW_LIM_HT)    ///< HV ARM board temperature compensation in charge mode
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< LV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_MV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< MV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_HV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< HV NTC0 temperature compensation in charge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_CHRG           (70.1f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_MV_CHRG           (73.0f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_HV_CHRG           (70.7f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC1 temperature compensation in charge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_CHRG           (68.6f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_MV_CHRG           (72.8f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_HV_CHRG           (71.1f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC2 temperature compensation in charge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_CHRG           (74.7f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_MV_CHRG           (75.1f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_HV_CHRG           (70.2f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC3 temperature compensation in charge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_CHRG           (75.5f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_MV_CHRG           (73.4f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_HV_CHRG           (63.4f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC4 temperature compensation in charge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_CHRG           (70.2f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_MV_CHRG           (73.3f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_HV_CHRG           (71.1f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC5 temperature compensation in charge mode
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_CHRG           (70.2f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_MV_CHRG           (73.3f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_HV_CHRG           (71.1f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC6 temperature compensation in charge mode

/********************** High Temperature Compensation in discharge mode **********************/
#define LV_BATT_HT_PL_DCHA              250.0f      ///< High temperature power limit low battery Voltage in discharge mode
#define MV1_BATT_HT_PL_DCHA             300.0f      ///< High temperature power limit middle battery Voltage 1 in discharge mode
//#define MV2_BATT_HT_PL_DCHA           500.0f      ///< High temperature power limit middle battery Voltage 2 in discharge mode
#define HV_BATT_HT_PL_DCHA              500.0f      ///< High temperature power limit high battery Voltage in discharge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_DCHA         (87.0f - TEMP_DWN_POW_LIM_HT)    ///< LV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_MV_DCHA         (94.7f - TEMP_DWN_POW_LIM_HT)    ///< MV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_HV_DCHA         (100.3f - TEMP_DWN_POW_LIM_HT)   ///< HV DSP board temperature compensation in discharge mode
/* ARM BOARD Temperature Compensation */
#define TEMP_CMP_ARM_BD_LV_DCHA         (87.0f - TEMP_DWN_POW_LIM_HT)    ///< LV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_MV_DCHA         (93.0f - TEMP_DWN_POW_LIM_HT)    ///< MV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_HV_DCHA         (96.0f - TEMP_DWN_POW_LIM_HT)    ///< HV ARM board temperature compensation in discharge mode
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< 72.0f; LV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_MV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< 62.0f; MV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_HV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< 77.0f; HV NTC0 temperature compensation in discharge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_DCHA           (61.8f - TEMP_DWN_POW_LIM_HT)    ///< 68.0f; LV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_MV_DCHA           (67.1f - TEMP_DWN_POW_LIM_HT)    ///< 51.0f; MV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_HV_DCHA           (70.6f - TEMP_DWN_POW_LIM_HT)    ///< 68.0f; HV NTC1 temperature compensation in discharge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_DCHA           (60.0f - TEMP_DWN_POW_LIM_HT)    ///< 68.0f; LV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_MV_DCHA           (65.4f - TEMP_DWN_POW_LIM_HT)    ///< 51.0f; MV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_HV_DCHA           (68.8f - TEMP_DWN_POW_LIM_HT)    ///< 68.0f; HV NTC2 temperature compensation in discharge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_DCHA           (62.6f - TEMP_DWN_POW_LIM_HT)    ///< 68.0f; LV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_MV_DCHA           (67.4f - TEMP_DWN_POW_LIM_HT)    ///< 55.0f; MV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_HV_DCHA           (71.9f - TEMP_DWN_POW_LIM_HT)    ///< 71.0f; HV NTC3 temperature compensation in discharge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_DCHA           (66.6f - TEMP_DWN_POW_LIM_HT)    ///< 72.0f; LV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_MV_DCHA           (70.2f - TEMP_DWN_POW_LIM_HT)    ///< 62.0f; MV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_HV_DCHA           (74.5f - TEMP_DWN_POW_LIM_HT)    ///< 77.0f; HV NTC4 temperature compensation in discharge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_DCHA           (61.6f - TEMP_DWN_POW_LIM_HT)    ///< 57.0f; LV NTC5 temperature compensation in discharge mode
#define TEMP_CMP_NTC5_MV_DCHA           (67.0f - TEMP_DWN_POW_LIM_HT)    ///< 52.0f; MV NTC5 temperature compensation in discharge mode
#define TEMP_CMP_NTC5_HV_DCHA           (70.5f - TEMP_DWN_POW_LIM_HT)    ///< 55.0f; HV NTC5 temperature compensation in discharge mode
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_DCHA           (61.6f - TEMP_DWN_POW_LIM_HT)    ///< 57.0f; LV NTC6 temperature compensation in discharge mode
#define TEMP_CMP_NTC6_MV_DCHA           (67.0f - TEMP_DWN_POW_LIM_HT)    ///< 52.0f; MV NTC6 temperature compensation in discharge mode
#define TEMP_CMP_NTC6_HV_DCHA           (70.5f - TEMP_DWN_POW_LIM_HT)    ///< 55.0f; HV NTC6 temperature compensation in discharge mode

#else
/********************** High Temperature Compensation in charge mode **********************/
#define LV_BATT_HT_PL_CHRG              300.0f      ///< High Temperature Power Limit Low battery Voltage in charge mode
#define MV_BATT_HT_PL_CHRG              400.0f      ///< High temperature power limit middle battery Voltage in charge mode
#define HV_BATT_HT_PL_CHRG              500.0f      ///< High temperature power limit high battery Voltage in charge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< LV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_MV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< MV DSP board temperature compensation in charge mode
#define TEMP_CMP_DSP_BD_HV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< HV DSP board temperature compensation in charge mode
/* ARM BOARD Temperature Compensation */
#define TEMP_CMP_ARM_BD_LV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< LV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_MV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< MV ARM board temperature compensation in charge mode
#define TEMP_CMP_ARM_BD_HV_CHRG         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< HV ARM board temperature compensation in charge mode
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< LV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_MV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< MV NTC0 temperature compensation in charge mode
#define TEMP_CMP_NTC0_HV_CHRG           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< HV NTC0 temperature compensation in charge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_CHRG           (69.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_MV_CHRG           (65.0f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC1 temperature compensation in charge mode
#define TEMP_CMP_NTC1_HV_CHRG           (69.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC1 temperature compensation in charge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_CHRG           (74.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_MV_CHRG           (72.3f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC2 temperature compensation in charge mode
#define TEMP_CMP_NTC2_HV_CHRG           (80.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC2 temperature compensation in charge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_CHRG           (76.7f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_MV_CHRG           (72.6f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC3 temperature compensation in charge mode
#define TEMP_CMP_NTC3_HV_CHRG           (75.4f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC3 temperature compensation in charge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_CHRG           (77.5f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_MV_CHRG           (73.2f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC4 temperature compensation in charge mode
#define TEMP_CMP_NTC4_HV_CHRG           (77.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC4 temperature compensation in charge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_CHRG           (77.4f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_MV_CHRG           (75.5f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC5 temperature compensation in charge mode
#define TEMP_CMP_NTC5_HV_CHRG           (78.7f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC5 temperature compensation in charge mode
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_CHRG           (65.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_MV_CHRG           (61.0f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC6 temperature compensation in charge mode
#define TEMP_CMP_NTC6_HV_CHRG           (65.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC6 temperature compensation in charge mode

/********************** High Temperature Compensation in discharge mode **********************/
#define LV_BATT_HT_PL_DCHA              300.0f      ///< High temperature power limit low battery Voltage in discharge mode
#define MV1_BATT_HT_PL_DCHA             350.0f      ///< High temperature power limit middle battery Voltage 1 in discharge mode
#define MV2_BATT_HT_PL_DCHA             400.0f      ///< High temperature power limit middle battery Voltage 2 in discharge mode
#define HV_BATT_HT_PL_DCHA              500.0f      ///< High temperature power limit high battery Voltage in discharge mode
/* DSP Board Temperature Compensation */
#define TEMP_CMP_DSP_BD_LV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< LV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_MV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< MV DSP board temperature compensation in discharge mode
#define TEMP_CMP_DSP_BD_HV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< HV DSP board temperature compensation in discharge mode
/* ARM BOARD Temperature Compensation */
#define TEMP_CMP_ARM_BD_LV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< LV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_MV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< MV ARM board temperature compensation in discharge mode
#define TEMP_CMP_ARM_BD_HV_DCHA         (115.0f - TEMP_DWN_POW_LIM_HT)   ///< HV ARM board temperature compensation in discharge mode
/* NTC0 Temperature Compensation */
#define TEMP_CMP_NTC0_LV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< LV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_MV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< MV NTC0 temperature compensation in discharge mode
#define TEMP_CMP_NTC0_HV_DCHA           (200.0f - TEMP_DWN_POW_LIM_HT)   ///< HV NTC0 temperature compensation in discharge mode
/* NTC1 Temperature Compensation */
#define TEMP_CMP_NTC1_LV_DCHA           (51.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_MV_DCHA           (64.0f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC1 temperature compensation in discharge mode
#define TEMP_CMP_NTC1_HV_DCHA           (51.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC1 temperature compensation in discharge mode
/* NTC2 Temperature Compensation */
#define TEMP_CMP_NTC2_LV_DCHA           (75.2f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_MV_DCHA           (73.8f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC2 temperature compensation in discharge mode
#define TEMP_CMP_NTC2_HV_DCHA           (72.2f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC2 temperature compensation in discharge mode
/* NTC3 Temperature Compensation */
#define TEMP_CMP_NTC3_LV_DCHA           (78.6f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_MV_DCHA           (76.2f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC3 temperature compensation in discharge mode
#define TEMP_CMP_NTC3_HV_DCHA           (71.7f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC3 temperature compensation in discharge mode
/* NTC4 Temperature Compensation */
#define TEMP_CMP_NTC4_LV_DCHA           (79.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_MV_DCHA           (75.9f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC4 temperature compensation in discharge mode
#define TEMP_CMP_NTC4_HV_DCHA           (72.9f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC4 temperature compensation in discharge mode
/* NTC5 Temperature Compensation */
#define TEMP_CMP_NTC5_LV_DCHA           (77.5f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC5 temperature compensation in discharge mode
#define TEMP_CMP_NTC5_MV_DCHA           (76.4f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC5 temperature compensation in discharge mode
#define TEMP_CMP_NTC5_HV_DCHA           (75.5f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC5 temperature compensation in discharge mode
/* NTC6 Temperature Compensation */
#define TEMP_CMP_NTC6_LV_DCHA           (63.0f - TEMP_DWN_POW_LIM_HT)    ///< LV NTC6 temperature compensation in discharge mode
#define TEMP_CMP_NTC6_MV_DCHA           (76.0f - TEMP_DWN_POW_LIM_HT)    ///< MV NTC6 temperature compensation in discharge mode
#define TEMP_CMP_NTC6_HV_DCHA           (74.0f - TEMP_DWN_POW_LIM_HT)    ///< HV NTC6 temperature compensation in discharge mode
#endif

#if(1U == GRID_PHASE_NUMBER)
/********************** High Temperature Compensation coefficient in charge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG    ((TEMP_CMP_DSP_BD_MV_CHRG - TEMP_CMP_DSP_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_CHRG    (TEMP_CMP_DSP_BD_MV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG    ((TEMP_CMP_DSP_BD_HV_CHRG - TEMP_CMP_DSP_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_CHRG    (TEMP_CMP_DSP_BD_HV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* ARM BOARD Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG    ((TEMP_CMP_ARM_BD_MV_CHRG - TEMP_CMP_ARM_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_CHRG    (TEMP_CMP_ARM_BD_MV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG    ((TEMP_CMP_ARM_BD_HV_CHRG - TEMP_CMP_ARM_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_CHRG    (TEMP_CMP_ARM_BD_HV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_CHRG      ((TEMP_CMP_NTC0_MV_CHRG - TEMP_CMP_NTC0_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_LV_CHRG      (TEMP_CMP_NTC0_MV_CHRG - COEFF_K_TEMP_CMP_NTC0_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC0_HV_CHRG      ((TEMP_CMP_NTC0_HV_CHRG - TEMP_CMP_NTC0_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_HV_CHRG      (TEMP_CMP_NTC0_HV_CHRG - COEFF_K_TEMP_CMP_NTC0_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_CHRG      ((TEMP_CMP_NTC1_MV_CHRG - TEMP_CMP_NTC1_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_LV_CHRG      (TEMP_CMP_NTC1_MV_CHRG - COEFF_K_TEMP_CMP_NTC1_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC1_HV_CHRG      ((TEMP_CMP_NTC1_HV_CHRG - TEMP_CMP_NTC1_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_HV_CHRG      (TEMP_CMP_NTC1_HV_CHRG - COEFF_K_TEMP_CMP_NTC1_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_CHRG      ((TEMP_CMP_NTC2_MV_CHRG - TEMP_CMP_NTC2_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_LV_CHRG      (TEMP_CMP_NTC2_MV_CHRG - COEFF_K_TEMP_CMP_NTC2_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC2_HV_CHRG      ((TEMP_CMP_NTC2_HV_CHRG - TEMP_CMP_NTC2_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_HV_CHRG      (TEMP_CMP_NTC2_HV_CHRG - COEFF_K_TEMP_CMP_NTC2_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_CHRG      ((TEMP_CMP_NTC3_MV_CHRG - TEMP_CMP_NTC3_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_LV_CHRG      (TEMP_CMP_NTC3_MV_CHRG - COEFF_K_TEMP_CMP_NTC3_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC3_HV_CHRG      ((TEMP_CMP_NTC3_HV_CHRG - TEMP_CMP_NTC3_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_HV_CHRG      (TEMP_CMP_NTC3_HV_CHRG - COEFF_K_TEMP_CMP_NTC3_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_CHRG      ((TEMP_CMP_NTC4_MV_CHRG - TEMP_CMP_NTC4_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_LV_CHRG      (TEMP_CMP_NTC4_MV_CHRG - COEFF_K_TEMP_CMP_NTC4_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC4_HV_CHRG      ((TEMP_CMP_NTC4_HV_CHRG - TEMP_CMP_NTC4_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_HV_CHRG      (TEMP_CMP_NTC4_HV_CHRG - COEFF_K_TEMP_CMP_NTC4_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_CHRG      ((TEMP_CMP_NTC5_MV_CHRG - TEMP_CMP_NTC5_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_LV_CHRG      (TEMP_CMP_NTC5_MV_CHRG - COEFF_K_TEMP_CMP_NTC5_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC5_HV_CHRG      ((TEMP_CMP_NTC5_HV_CHRG - TEMP_CMP_NTC5_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_HV_CHRG      (TEMP_CMP_NTC5_HV_CHRG - COEFF_K_TEMP_CMP_NTC5_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_CHRG      ((TEMP_CMP_NTC6_MV_CHRG - TEMP_CMP_NTC6_LV_CHRG)/(MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_LV_CHRG      (TEMP_CMP_NTC6_MV_CHRG - COEFF_K_TEMP_CMP_NTC6_LV_CHRG*MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC6_HV_CHRG      ((TEMP_CMP_NTC6_HV_CHRG - TEMP_CMP_NTC6_MV_CHRG)/(HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_HV_CHRG      (TEMP_CMP_NTC6_HV_CHRG - COEFF_K_TEMP_CMP_NTC6_HV_CHRG*HV_BATT_HT_PL_CHRG)

/********************** High Temperature Compensation coefficient in discharge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA    ((TEMP_CMP_DSP_BD_MV_DCHA - TEMP_CMP_DSP_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA    (TEMP_CMP_DSP_BD_MV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA    ((TEMP_CMP_DSP_BD_HV_DCHA - TEMP_CMP_DSP_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA    (TEMP_CMP_DSP_BD_HV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* ARM Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA    ((TEMP_CMP_ARM_BD_MV_DCHA - TEMP_CMP_ARM_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA    (TEMP_CMP_ARM_BD_MV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA    ((TEMP_CMP_ARM_BD_HV_DCHA - TEMP_CMP_ARM_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA    (TEMP_CMP_ARM_BD_HV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_DCHA      ((TEMP_CMP_NTC0_MV_DCHA - TEMP_CMP_NTC0_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_LV_DCHA      (TEMP_CMP_NTC0_MV_DCHA - COEFF_K_TEMP_CMP_NTC0_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC0_HV_DCHA      ((TEMP_CMP_NTC0_HV_DCHA - TEMP_CMP_NTC0_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_HV_DCHA      (TEMP_CMP_NTC0_HV_DCHA - COEFF_K_TEMP_CMP_NTC0_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_DCHA      ((TEMP_CMP_NTC1_MV_DCHA - TEMP_CMP_NTC1_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_LV_DCHA      (TEMP_CMP_NTC1_MV_DCHA - COEFF_K_TEMP_CMP_NTC1_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC1_HV_DCHA      ((TEMP_CMP_NTC1_HV_DCHA - TEMP_CMP_NTC1_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_HV_DCHA      (TEMP_CMP_NTC1_HV_DCHA - COEFF_K_TEMP_CMP_NTC1_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_DCHA      ((TEMP_CMP_NTC2_MV_DCHA - TEMP_CMP_NTC2_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_LV_DCHA      (TEMP_CMP_NTC2_MV_DCHA - COEFF_K_TEMP_CMP_NTC2_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC2_HV_DCHA      ((TEMP_CMP_NTC2_HV_DCHA - TEMP_CMP_NTC2_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_HV_DCHA      (TEMP_CMP_NTC2_HV_DCHA - COEFF_K_TEMP_CMP_NTC2_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_DCHA      ((TEMP_CMP_NTC3_MV_DCHA - TEMP_CMP_NTC3_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_LV_DCHA      (TEMP_CMP_NTC3_MV_DCHA - COEFF_K_TEMP_CMP_NTC3_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC3_HV_DCHA      ((TEMP_CMP_NTC3_HV_DCHA - TEMP_CMP_NTC3_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_HV_DCHA      (TEMP_CMP_NTC3_HV_DCHA - COEFF_K_TEMP_CMP_NTC3_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_DCHA      ((TEMP_CMP_NTC4_MV_DCHA - TEMP_CMP_NTC4_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_LV_DCHA      (TEMP_CMP_NTC4_MV_DCHA - COEFF_K_TEMP_CMP_NTC4_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC4_HV_DCHA      ((TEMP_CMP_NTC4_HV_DCHA - TEMP_CMP_NTC4_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_HV_DCHA      (TEMP_CMP_NTC4_HV_DCHA - COEFF_K_TEMP_CMP_NTC4_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_DCHA      ((TEMP_CMP_NTC5_MV_DCHA - TEMP_CMP_NTC5_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_LV_DCHA      (TEMP_CMP_NTC5_MV_DCHA - COEFF_K_TEMP_CMP_NTC5_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC5_HV_DCHA      ((TEMP_CMP_NTC5_HV_DCHA - TEMP_CMP_NTC5_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_HV_DCHA      (TEMP_CMP_NTC5_HV_DCHA - COEFF_K_TEMP_CMP_NTC5_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_DCHA      ((TEMP_CMP_NTC6_MV_DCHA - TEMP_CMP_NTC6_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_LV_DCHA      (TEMP_CMP_NTC6_MV_DCHA - COEFF_K_TEMP_CMP_NTC6_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC6_HV_DCHA      ((TEMP_CMP_NTC6_HV_DCHA - TEMP_CMP_NTC6_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV2_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_HV_DCHA      (TEMP_CMP_NTC6_HV_DCHA - COEFF_K_TEMP_CMP_NTC6_HV_DCHA * HV_BATT_HT_PL_DCHA)
#elif(2U == GRID_PHASE_NUMBER)
/********************** High Temperature Compensation coefficient in charge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG    ((TEMP_CMP_DSP_BD_MV_CHRG - TEMP_CMP_DSP_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_CHRG    (TEMP_CMP_DSP_BD_MV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG    ((TEMP_CMP_DSP_BD_HV_CHRG - TEMP_CMP_DSP_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_CHRG    (TEMP_CMP_DSP_BD_HV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* ARM BOARD Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG    ((TEMP_CMP_ARM_BD_MV_CHRG - TEMP_CMP_ARM_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_CHRG    (TEMP_CMP_ARM_BD_MV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG    ((TEMP_CMP_ARM_BD_HV_CHRG - TEMP_CMP_ARM_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_CHRG    (TEMP_CMP_ARM_BD_HV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_CHRG      ((TEMP_CMP_NTC0_MV_CHRG - TEMP_CMP_NTC0_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_LV_CHRG      (TEMP_CMP_NTC0_MV_CHRG - COEFF_K_TEMP_CMP_NTC0_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC0_HV_CHRG      ((TEMP_CMP_NTC0_HV_CHRG - TEMP_CMP_NTC0_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_HV_CHRG      (TEMP_CMP_NTC0_HV_CHRG - COEFF_K_TEMP_CMP_NTC0_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_CHRG      ((TEMP_CMP_NTC1_MV_CHRG - TEMP_CMP_NTC1_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_LV_CHRG      (TEMP_CMP_NTC1_MV_CHRG - COEFF_K_TEMP_CMP_NTC1_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC1_HV_CHRG      ((TEMP_CMP_NTC1_HV_CHRG - TEMP_CMP_NTC1_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_HV_CHRG      (TEMP_CMP_NTC1_HV_CHRG - COEFF_K_TEMP_CMP_NTC1_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_CHRG      ((TEMP_CMP_NTC2_MV_CHRG - TEMP_CMP_NTC2_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_LV_CHRG      (TEMP_CMP_NTC2_MV_CHRG - COEFF_K_TEMP_CMP_NTC2_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC2_HV_CHRG      ((TEMP_CMP_NTC2_HV_CHRG - TEMP_CMP_NTC2_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_HV_CHRG      (TEMP_CMP_NTC2_HV_CHRG - COEFF_K_TEMP_CMP_NTC2_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_CHRG      ((TEMP_CMP_NTC3_MV_CHRG - TEMP_CMP_NTC3_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_LV_CHRG      (TEMP_CMP_NTC3_MV_CHRG - COEFF_K_TEMP_CMP_NTC3_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC3_HV_CHRG      ((TEMP_CMP_NTC3_HV_CHRG - TEMP_CMP_NTC3_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_HV_CHRG      (TEMP_CMP_NTC3_HV_CHRG - COEFF_K_TEMP_CMP_NTC3_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_CHRG      ((TEMP_CMP_NTC4_MV_CHRG - TEMP_CMP_NTC4_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_LV_CHRG      (TEMP_CMP_NTC4_MV_CHRG - COEFF_K_TEMP_CMP_NTC4_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC4_HV_CHRG      ((TEMP_CMP_NTC4_HV_CHRG - TEMP_CMP_NTC4_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_HV_CHRG      (TEMP_CMP_NTC4_HV_CHRG - COEFF_K_TEMP_CMP_NTC4_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_CHRG      ((TEMP_CMP_NTC5_MV_CHRG - TEMP_CMP_NTC5_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_LV_CHRG      (TEMP_CMP_NTC5_MV_CHRG - COEFF_K_TEMP_CMP_NTC5_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC5_HV_CHRG      ((TEMP_CMP_NTC5_HV_CHRG - TEMP_CMP_NTC5_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_HV_CHRG      (TEMP_CMP_NTC5_HV_CHRG - COEFF_K_TEMP_CMP_NTC5_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_CHRG      ((TEMP_CMP_NTC6_MV_CHRG - TEMP_CMP_NTC6_LV_CHRG)/(MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_LV_CHRG      (TEMP_CMP_NTC6_MV_CHRG - COEFF_K_TEMP_CMP_NTC6_LV_CHRG*MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC6_HV_CHRG      ((TEMP_CMP_NTC6_HV_CHRG - TEMP_CMP_NTC6_MV_CHRG)/(HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_HV_CHRG      (TEMP_CMP_NTC6_HV_CHRG - COEFF_K_TEMP_CMP_NTC6_HV_CHRG*HV_BATT_HT_PL_CHRG)

/********************** High Temperature Compensation coefficient in discharge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA    ((TEMP_CMP_DSP_BD_MV_DCHA - TEMP_CMP_DSP_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA    (TEMP_CMP_DSP_BD_MV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA    ((TEMP_CMP_DSP_BD_HV_DCHA - TEMP_CMP_DSP_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA    (TEMP_CMP_DSP_BD_HV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* ARM Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA    ((TEMP_CMP_ARM_BD_MV_DCHA - TEMP_CMP_ARM_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA    (TEMP_CMP_ARM_BD_MV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA    ((TEMP_CMP_ARM_BD_HV_DCHA - TEMP_CMP_ARM_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA    (TEMP_CMP_ARM_BD_HV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_DCHA      ((TEMP_CMP_NTC0_MV_DCHA - TEMP_CMP_NTC0_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_LV_DCHA      (TEMP_CMP_NTC0_MV_DCHA - COEFF_K_TEMP_CMP_NTC0_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC0_HV_DCHA      ((TEMP_CMP_NTC0_HV_DCHA - TEMP_CMP_NTC0_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_HV_DCHA      (TEMP_CMP_NTC0_HV_DCHA - COEFF_K_TEMP_CMP_NTC0_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_DCHA      ((TEMP_CMP_NTC1_MV_DCHA - TEMP_CMP_NTC1_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_LV_DCHA      (TEMP_CMP_NTC1_MV_DCHA - COEFF_K_TEMP_CMP_NTC1_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC1_HV_DCHA      ((TEMP_CMP_NTC1_HV_DCHA - TEMP_CMP_NTC1_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_HV_DCHA      (TEMP_CMP_NTC1_HV_DCHA - COEFF_K_TEMP_CMP_NTC1_HV_DCHA * HV_BATT_HT_PL_DCHA)

/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_DCHA      ((TEMP_CMP_NTC2_MV_DCHA - TEMP_CMP_NTC2_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_LV_DCHA      (TEMP_CMP_NTC2_MV_DCHA - COEFF_K_TEMP_CMP_NTC2_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC2_HV_DCHA      ((TEMP_CMP_NTC2_HV_DCHA - TEMP_CMP_NTC2_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_HV_DCHA      (TEMP_CMP_NTC2_HV_DCHA - COEFF_K_TEMP_CMP_NTC2_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_DCHA      ((TEMP_CMP_NTC3_MV_DCHA - TEMP_CMP_NTC3_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_LV_DCHA      (TEMP_CMP_NTC3_MV_DCHA - COEFF_K_TEMP_CMP_NTC3_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC3_HV_DCHA      ((TEMP_CMP_NTC3_HV_DCHA - TEMP_CMP_NTC3_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_HV_DCHA      (TEMP_CMP_NTC3_HV_DCHA - COEFF_K_TEMP_CMP_NTC3_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_DCHA      ((TEMP_CMP_NTC4_MV_DCHA - TEMP_CMP_NTC4_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_LV_DCHA      (TEMP_CMP_NTC4_MV_DCHA - COEFF_K_TEMP_CMP_NTC4_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC4_HV_DCHA      ((TEMP_CMP_NTC4_HV_DCHA - TEMP_CMP_NTC4_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_HV_DCHA      (TEMP_CMP_NTC4_HV_DCHA - COEFF_K_TEMP_CMP_NTC4_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_DCHA      ((TEMP_CMP_NTC5_MV_DCHA - TEMP_CMP_NTC5_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_LV_DCHA      (TEMP_CMP_NTC5_MV_DCHA - COEFF_K_TEMP_CMP_NTC5_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC5_HV_DCHA      ((TEMP_CMP_NTC5_HV_DCHA - TEMP_CMP_NTC5_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_HV_DCHA      (TEMP_CMP_NTC5_HV_DCHA - COEFF_K_TEMP_CMP_NTC5_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_DCHA      ((TEMP_CMP_NTC6_MV_DCHA - TEMP_CMP_NTC6_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_LV_DCHA      (TEMP_CMP_NTC6_MV_DCHA - COEFF_K_TEMP_CMP_NTC6_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC6_HV_DCHA      ((TEMP_CMP_NTC6_HV_DCHA - TEMP_CMP_NTC6_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_HV_DCHA      (TEMP_CMP_NTC6_HV_DCHA - COEFF_K_TEMP_CMP_NTC6_HV_DCHA * HV_BATT_HT_PL_DCHA)
#else
/********************** High Temperature Compensation coefficient in charge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG    ((TEMP_CMP_DSP_BD_MV_CHRG - TEMP_CMP_DSP_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_CHRG    (TEMP_CMP_DSP_BD_MV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG    ((TEMP_CMP_DSP_BD_HV_CHRG - TEMP_CMP_DSP_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_CHRG    (TEMP_CMP_DSP_BD_HV_CHRG - COEFF_K_TEMP_CMP_DSP_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* ARM BOARD Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG    ((TEMP_CMP_ARM_BD_MV_CHRG - TEMP_CMP_ARM_BD_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_CHRG    (TEMP_CMP_ARM_BD_MV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG    ((TEMP_CMP_ARM_BD_HV_CHRG - TEMP_CMP_ARM_BD_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_CHRG    (TEMP_CMP_ARM_BD_HV_CHRG - COEFF_K_TEMP_CMP_ARM_BD_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_CHRG      ((TEMP_CMP_NTC0_MV_CHRG - TEMP_CMP_NTC0_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_LV_CHRG      (TEMP_CMP_NTC0_MV_CHRG - COEFF_K_TEMP_CMP_NTC0_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC0_HV_CHRG      ((TEMP_CMP_NTC0_HV_CHRG - TEMP_CMP_NTC0_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC0_HV_CHRG      (TEMP_CMP_NTC0_HV_CHRG - COEFF_K_TEMP_CMP_NTC0_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_CHRG      ((TEMP_CMP_NTC1_MV_CHRG - TEMP_CMP_NTC1_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_LV_CHRG      (TEMP_CMP_NTC1_MV_CHRG - COEFF_K_TEMP_CMP_NTC1_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC1_HV_CHRG      ((TEMP_CMP_NTC1_HV_CHRG - TEMP_CMP_NTC1_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC1_HV_CHRG      (TEMP_CMP_NTC1_HV_CHRG - COEFF_K_TEMP_CMP_NTC1_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_CHRG      ((TEMP_CMP_NTC2_MV_CHRG - TEMP_CMP_NTC2_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_LV_CHRG      (TEMP_CMP_NTC2_MV_CHRG - COEFF_K_TEMP_CMP_NTC2_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC2_HV_CHRG      ((TEMP_CMP_NTC2_HV_CHRG - TEMP_CMP_NTC2_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC2_HV_CHRG      (TEMP_CMP_NTC2_HV_CHRG - COEFF_K_TEMP_CMP_NTC2_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_CHRG      ((TEMP_CMP_NTC3_MV_CHRG - TEMP_CMP_NTC3_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_LV_CHRG      (TEMP_CMP_NTC3_MV_CHRG - COEFF_K_TEMP_CMP_NTC3_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC3_HV_CHRG      ((TEMP_CMP_NTC3_HV_CHRG - TEMP_CMP_NTC3_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC3_HV_CHRG      (TEMP_CMP_NTC3_HV_CHRG - COEFF_K_TEMP_CMP_NTC3_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_CHRG      ((TEMP_CMP_NTC4_MV_CHRG - TEMP_CMP_NTC4_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_LV_CHRG      (TEMP_CMP_NTC4_MV_CHRG - COEFF_K_TEMP_CMP_NTC4_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC4_HV_CHRG      ((TEMP_CMP_NTC4_HV_CHRG - TEMP_CMP_NTC4_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC4_HV_CHRG      (TEMP_CMP_NTC4_HV_CHRG - COEFF_K_TEMP_CMP_NTC4_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_CHRG      ((TEMP_CMP_NTC5_MV_CHRG - TEMP_CMP_NTC5_LV_CHRG) / (MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_LV_CHRG      (TEMP_CMP_NTC5_MV_CHRG - COEFF_K_TEMP_CMP_NTC5_LV_CHRG * MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC5_HV_CHRG      ((TEMP_CMP_NTC5_HV_CHRG - TEMP_CMP_NTC5_MV_CHRG) / (HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC5_HV_CHRG      (TEMP_CMP_NTC5_HV_CHRG - COEFF_K_TEMP_CMP_NTC5_HV_CHRG * HV_BATT_HT_PL_CHRG)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_CHRG      ((TEMP_CMP_NTC6_MV_CHRG - TEMP_CMP_NTC6_LV_CHRG)/(MV_BATT_HT_PL_CHRG - LV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_LV_CHRG      (TEMP_CMP_NTC6_MV_CHRG - COEFF_K_TEMP_CMP_NTC6_LV_CHRG*MV_BATT_HT_PL_CHRG)
#define COEFF_K_TEMP_CMP_NTC6_HV_CHRG      ((TEMP_CMP_NTC6_HV_CHRG - TEMP_CMP_NTC6_MV_CHRG)/(HV_BATT_HT_PL_CHRG - MV_BATT_HT_PL_CHRG))
#define COEFF_B_TEMP_CMP_NTC6_HV_CHRG      (TEMP_CMP_NTC6_HV_CHRG - COEFF_K_TEMP_CMP_NTC6_HV_CHRG*HV_BATT_HT_PL_CHRG)

/********************** High Temperature Compensation coefficient in discharge mode **********************/
/* DSP Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA    ((TEMP_CMP_DSP_BD_MV_DCHA - TEMP_CMP_DSP_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_LV_DCHA    (TEMP_CMP_DSP_BD_MV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA    ((TEMP_CMP_DSP_BD_HV_DCHA - TEMP_CMP_DSP_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_DSP_BD_HV_DCHA    (TEMP_CMP_DSP_BD_HV_DCHA - COEFF_K_TEMP_CMP_DSP_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* ARM Board Temperature Compensation */
#define COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA    ((TEMP_CMP_ARM_BD_MV_DCHA - TEMP_CMP_ARM_BD_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_LV_DCHA    (TEMP_CMP_ARM_BD_MV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA    ((TEMP_CMP_ARM_BD_HV_DCHA - TEMP_CMP_ARM_BD_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_ARM_BD_HV_DCHA    (TEMP_CMP_ARM_BD_HV_DCHA - COEFF_K_TEMP_CMP_ARM_BD_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC0 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC0_LV_DCHA      ((TEMP_CMP_NTC0_MV_DCHA - TEMP_CMP_NTC0_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_LV_DCHA      (TEMP_CMP_NTC0_MV_DCHA - COEFF_K_TEMP_CMP_NTC0_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC0_HV_DCHA      ((TEMP_CMP_NTC0_HV_DCHA - TEMP_CMP_NTC0_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC0_HV_DCHA      (TEMP_CMP_NTC0_HV_DCHA - COEFF_K_TEMP_CMP_NTC0_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC1 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC1_LV_DCHA      ((TEMP_CMP_NTC1_MV_DCHA - TEMP_CMP_NTC1_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_LV_DCHA      (TEMP_CMP_NTC1_MV_DCHA - COEFF_K_TEMP_CMP_NTC1_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC1_HV_DCHA      ((TEMP_CMP_NTC1_HV_DCHA - TEMP_CMP_NTC1_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC1_HV_DCHA      (TEMP_CMP_NTC1_HV_DCHA - COEFF_K_TEMP_CMP_NTC1_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC2 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC2_LV_DCHA      ((TEMP_CMP_NTC2_MV_DCHA - TEMP_CMP_NTC2_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_LV_DCHA      (TEMP_CMP_NTC2_MV_DCHA - COEFF_K_TEMP_CMP_NTC2_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC2_HV_DCHA      ((TEMP_CMP_NTC2_HV_DCHA - TEMP_CMP_NTC2_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC2_HV_DCHA      (TEMP_CMP_NTC2_HV_DCHA - COEFF_K_TEMP_CMP_NTC2_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC3 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC3_LV_DCHA      ((TEMP_CMP_NTC3_MV_DCHA - TEMP_CMP_NTC3_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_LV_DCHA      (TEMP_CMP_NTC3_MV_DCHA - COEFF_K_TEMP_CMP_NTC3_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC3_HV_DCHA      ((TEMP_CMP_NTC3_HV_DCHA - TEMP_CMP_NTC3_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC3_HV_DCHA      (TEMP_CMP_NTC3_HV_DCHA - COEFF_K_TEMP_CMP_NTC3_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC4 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC4_LV_DCHA      ((TEMP_CMP_NTC4_MV_DCHA - TEMP_CMP_NTC4_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_LV_DCHA      (TEMP_CMP_NTC4_MV_DCHA - COEFF_K_TEMP_CMP_NTC4_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC4_HV_DCHA      ((TEMP_CMP_NTC4_HV_DCHA - TEMP_CMP_NTC4_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC4_HV_DCHA      (TEMP_CMP_NTC4_HV_DCHA - COEFF_K_TEMP_CMP_NTC4_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC5 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC5_LV_DCHA      ((TEMP_CMP_NTC5_MV_DCHA - TEMP_CMP_NTC5_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_LV_DCHA      (TEMP_CMP_NTC5_MV_DCHA - COEFF_K_TEMP_CMP_NTC5_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC5_HV_DCHA      ((TEMP_CMP_NTC5_HV_DCHA - TEMP_CMP_NTC5_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC5_HV_DCHA      (TEMP_CMP_NTC5_HV_DCHA - COEFF_K_TEMP_CMP_NTC5_HV_DCHA * HV_BATT_HT_PL_DCHA)
/* NTC6 Temperature Compensation */
#define COEFF_K_TEMP_CMP_NTC6_LV_DCHA      ((TEMP_CMP_NTC6_MV_DCHA - TEMP_CMP_NTC6_LV_DCHA) / (MV1_BATT_HT_PL_DCHA - LV_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_LV_DCHA      (TEMP_CMP_NTC6_MV_DCHA - COEFF_K_TEMP_CMP_NTC6_LV_DCHA * MV1_BATT_HT_PL_DCHA)
#define COEFF_K_TEMP_CMP_NTC6_HV_DCHA      ((TEMP_CMP_NTC6_HV_DCHA - TEMP_CMP_NTC6_MV_DCHA) / (HV_BATT_HT_PL_DCHA - MV1_BATT_HT_PL_DCHA))
#define COEFF_B_TEMP_CMP_NTC6_HV_DCHA      (TEMP_CMP_NTC6_HV_DCHA - COEFF_K_TEMP_CMP_NTC6_HV_DCHA * HV_BATT_HT_PL_DCHA)
#endif

/* High Temperature Macro Definition */
#define COEFF_HT_PWRLIM_CHRG               0.109090909f  ///< 1200W/11000W
#define COEFF_HT_PWRLIM_DCHA               0.2f          ///< 2200W/11000W
#define HT_PWRLIM                          0.01f
#define HT_EXIST_TI                        100U          ///< 10s/0.1s
#define HT_ENTER_TI                        30U           ///< 3s/0.1s

#define TEMP_DIFF_ENTR_HT_PL               0.1f          ///< Enter high temperture limit
#define TEMP_DIFF_EXIT_HT_PL               0.0f          ///< Exit high temperture limit

#define WAIT_ST_MAC_HT_PL                  0U            ///< High temperature power limit state machine: Wait state
#define PROC_ST_MAC_HT_PL                  1U            ///< High temperature power limit state machine: Process state
#define EXIT_ST_MAC_HT_PL                  2U            ///< High temperature power limit state machine: Exit state

/* Fan Duty Macro Definition */
#define DUTY_FAN_START                     0.0f          ///< Fan start duty
#if(1U == GRID_PHASE_NUMBER)
#define TEMP_DWN_FAN_DUTY                  (TEMP_DWN_POW_LIM_HT-34.0f)   ///< Fan Duty Down Temperature;25.0f
#define TEMP_MID_FAN_DUTY                  TEMP_DWN_SILENCE_POW_LIM_HT1  ///< Fan Duty Silence Temperature;32.0f
#if(BMW_CUSTUMER == CUSTUMER_ID)
#define TEMP_UP_FAN_DUTY                   (TEMP_DWN_POW_LIM_HT-19.0f)   ///< Fan Duty Up Temperature;45.0f
#else
#define TEMP_UP_FAN_DUTY                   (TEMP_DWN_POW_LIM_HT-16.0f)   ///< Fan Duty Up Temperature;45.0f
#endif
#elif(2U == GRID_PHASE_NUMBER)
#define TEMP_DWN_FAN_DUTY                  (TEMP_DWN_POW_LIM_HT-30.0f)   ///< Fan Duty Down Temperature;30.0f
#define TEMP_MID_FAN_DUTY                  TEMP_DWN_SILENCE_POW_LIM_HT1  ///< Fan Duty Silence Temperature;38.0f
#define TEMP_UP_FAN_DUTY                   (TEMP_DWN_POW_LIM_HT-15.0f)   ///< Fan Duty Up Temperature;45.0f
#else
#define TEMP_DWN_FAN_DUTY                  (TEMP_DWN_POW_LIM_HT-55.0f)   ///< Fan Duty Down Temperature;5.0f
#define TEMP_MID_FAN_DUTY                  TEMP_DWN_SILENCE_POW_LIM_HT1  ///< Fan Duty Silence Temperature;35.0f
#define TEMP_UP_FAN_DUTY                   (TEMP_DWN_POW_LIM_HT-15.0f)   ///< Fan Duty Up Temperature;45.0f
#endif

#define TEMP_DWN_HYS_FAN_DUTY              (TEMP_DWN_FAN_DUTY - 2.0f)    ///< Fan Duty Temperature Down Hysteresis
#define DUTY_HYS_DWN_FAN                   0.05f         ///< Fan Duty Down Coefficient Hysteresis
#define DUTY_DWN_FAN                       0.1f          ///< Fan Duty Down Coefficient
#if 1U == GRID_PHASE_NUMBER
#if(BMW_CUSTUMER == CUSTUMER_ID)
#define DUTY_MID_FAN                       0.6f          ///< Fan Duty Silence Coefficient
#else
#define DUTY_MID_FAN                       0.44f         ///< Fan Duty Silence Coefficient
#endif
#else
#define DUTY_MID_FAN                       0.6f          ///< Fan Duty Silence Coefficient
#endif
#define DUTY_UP_FAN                        1.0f          ///< Fan Duty Up Coefficient
#define COEFF_K_FAN_DUTY_DWN               ((DUTY_DWN_FAN - DUTY_MID_FAN) / (TEMP_DWN_FAN_DUTY - TEMP_MID_FAN_DUTY))
#define COEFF_B_FAN_DUTY_DWN               (DUTY_DWN_FAN - COEFF_K_FAN_DUTY_DWN * TEMP_DWN_FAN_DUTY)
#define COEFF_K_FAN_DUTY_UP                ((DUTY_MID_FAN - DUTY_UP_FAN) / (TEMP_MID_FAN_DUTY - TEMP_UP_FAN_DUTY))
#define COEFF_B_FAN_DUTY_UP                (DUTY_MID_FAN - COEFF_K_FAN_DUTY_UP * TEMP_MID_FAN_DUTY)
#define STEP_FAN_DUTY                      0.01f         ///< 1%/100ms
#define TIME_FAN_DELAY_STOP                1200U         ///< Fan delay stop time-120s

/* Max discharge current according to high temperature for 11kW */
#define TEMP_DIFF_DWN_DCHA                 -5.0f
#define TEMP_DIFF_UP_DCHA                  0.0f
#define CURR_BATT_MAX_TEMP_DWN_DCHA        -38.5f
#define CURR_BATT_MAX_TEMP_UP_DCHA         -35.5f
#define COEFF_K_CURR_BATT_MAX_DCHA         ((CURR_BATT_MAX_TEMP_DWN_DCHA - CURR_BATT_MAX_TEMP_UP_DCHA )/(TEMP_DIFF_DWN_DCHA - TEMP_DIFF_UP_DCHA))
#define COEEF_B_CURR_BATT_MAX_DCHA         (CURR_BATT_MAX_TEMP_UP_DCHA - COEFF_K_CURR_BATT_MAX_DCHA * TEMP_DIFF_UP_DCHA)

/* Battery low voltage power limitation for 7.4kW */
#define VOLT_BATT_MAX_BATT_LV_PL_DCHA      260.0f           ///< Max battery voltage when Battery low voltage power limitation
#define VOLT_BATT_MIN_BATT_LV_PL_DCHA      VOLT_BATT_MIN    ///< Min battery voltage when Battery low voltage power limitation
#define VOLT_AC_MAX_BATT_LV_PL_DCHA        275.0f           ///< Max AC voltage when Battery low voltage power limitation
#define VOLT_AC_MIN_BATT_LV_PL_DCHA        245.0f           ///< Min AC voltage when Battery low voltage power limitation
#define COEFF_MIN_BATT_LV_PL_DCHA          0.4f

#define COEFF1_BATT_LV_PL_DCHA             22.23f
#define COEFF2_BATT_LV_PL_DCHA             -0.08667f
#define COEFF3_BATT_LV_PL_DCHA             -0.08167f
#define COEFF4_BATT_LV_PL_DCHA             0.0003333f

#define LF_PWR_DWN_LMT_CHRG                (POW_AC_RTD * EFF_PL_CHRG * 0.03f)

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
/* Temperature process typedef */
typedef enum
{
    LOW_POW_INIT_STS, LOW_POW_RUN_STS, ADD_POW_RUN_STS, ADD_POW_OK_STS
}EN_LOW_TEMP_STS;

typedef struct
{
    float32 ftDspCore;      ///< DSP core temperature
    float32 ftDspBd;        ///< DSP Board temperature
    float32 ftArmBd;        ///< ARM Board temperature
    float32 ftTempNtc0;     ///< NTC0 temperature: AC Terminal temperature
    float32 ftTempNtc1;     ///< NTC1 temperature: 7.4-PFC slow MOS NTC temperature, 11-reserved
    float32 ftTempNtc2;     ///< NTC2 temperature: 7.4-PFC quick MOS NTC temperature, 11-D2D magnetic medium
    float32 ftTempNtc3;     ///< NTC3 temperature: 7.4-D2D up NTC temperature, 11-D2D secondary side MOS
    float32 ftTempNtc4;     ///< NTC4 temperature: 7.4-D2D down NTC temperature, 11-D2D primary side MOS
    float32 ftTempNtc5;     ///< NTC5 temperature: 7.4-D2D transformer NTC temperature,11-PFC-MOS
    float32 ftTempNtc6;     ///< NTC6 temperature: 7.4-D2D inductor NTC temperature, 11-reserved
}ST_TEMP_MEM;

typedef struct
{
    Uint16 uiLowTempFlg;    ///< Low Temperature Flag
    Uint16 uiLowTempCnt;    ///< Low Temperature Counter
    Uint16 uiLowTempTim;    ///< Low Temperature Time
    Uint16 uiStHTLim;       ///< High temperature power limit status
    Uint16 uiCntHTEntr;     ///< Enter High temperature counter
    Uint16 uiCntHTExit;     ///< Exist High temperature counter
    float32 ftCoeffHTTgt;   ///< High Temperature Coefficient Target
    float32 ftCoeffHT;      ///< High Temperature Coefficient
    float32 ftCoeffLT;      ///< Low Temperature Coefficient
    float32 ftTempMax;      ///< Max temperature
    float32 ftTempMin;      ///< Min temperature

    EN_LOW_TEMP_STS enLowTempSts;    ///< Low Temperature State
    ST_TEMP_MEM stTempComp;          ///< Member temperature compensation
}ST_TEMP_PARAM;

typedef struct
{
	float32 ftCoeffAcVolt;      ///< Limit coefficient according to AC voltage
	float32 ftPowAcVolt1P;      ///< One phase power limitation according to AC voltage
	float32 ftCoeffBattVolt;    ///< Limit coefficient according to DC voltage
    float32 ftCoeffHT;          ///< Limit coefficient according to High temperature
    float32 ftCoeffLT;          ///< Limit coefficient according to Low temperature
    float32 ftCoeffLim;         ///< Limit coefficient
	float32 ftPowBattCurr;      ///< Limit power related to DC current
    float32 ftPowLim;           ///< Limit power
    float32 ftCurrBattLim;      ///< Limit battery current
    float32 ftCurrBattReq;      ///< Battery current request
    float32 ftPowAcCurrLim;     ///< AC current limit power
    float32 ftPowOcppLim;       ///< OCPP limit power
}ST_LMT_PRM;

typedef struct
{
	float32 ftPrmAcVolt;      ///< Related to AC voltage
	float32 ftPrmBattVolt;    ///< Related to battery voltage
}ST_VOLT_BUS_LIM_PRM;

typedef struct
{
    ST_PI_PRM stOcppChrgPI;            ///< Charge power compensation PI according to OCPP power request
    ST_PI_PRM stAcCurrChrgPI;          ///< Charge power compensation PI according to AC current
    ST_PI_PRM stBattCurrChrgPI;        ///< Charge power compensation PI according to battery current
    ST_PI_PRM stBattCurrDchaPI;        ///< Discharge power compensation PI according to battery current
}ST_POW_COMP;

typedef struct
{
	ST_POW_LIM          stPrmExt;           ///< Parameter to extern

    ST_TEMP_PARAM       stTempChrgPrm;      ///< Charge temperature limitation parameter
    ST_TEMP_PARAM       stTempDchaPrm;      ///< Discharge temperature limitation parameter
	ST_LMT_PRM          stPrmChrgLim;       ///< Charge limitation parameter
	ST_LMT_PRM          stPrmDchaLim;       ///< Discharge limitation parameter
	ST_VOLT_BUS_LIM_PRM stPrmBusVoltLim;    ///< Bus voltage limitation parameter
	ST_POW_COMP         stPowComp;          ///< Power compensation parameter

	float32 ftVoltBattCalc;                 ///< Power limitation calculate battery voltage
	float32 ftVoltBattRecpr;                ///< Reciprocal of battery voltage
	float32 ftPowAcChrgMax;                 ///< Max AC charge power
	float32 ftPowAcDchaMax;                 ///< Max AC discharge power
    float32 ftCoeffBattLVLim;               ///< Power limitation calculate AC and battery voltage
	float32 ftPaAcReq;                      ///< Phase A active power request
    float32 ftPbAcReq;                      ///< Phase B active power request
    float32 ftPcAcReq;                      ///< Phase C active power request
    float32 ftPAcReq;                       ///< Active power request sum
    float32 ftQaAcReq;                      ///< Phase A active power request
    float32 ftQbAcReq;                      ///< Phase A active power request
    float32 ftQcAcReq;                      ///< Phase A active power request
    float32 ftCoeffPAcReq;                  ///< Active power request coefficient
    float32 ftFanDutyTgt;                   ///< Fan duty target
    float32 ftNtcTempDiffMax;               ///< Max NTC temperature
    float32 ftNtcTempMax;                   ///< Max NTC temperature compare with derate point
    float32 ftCurrBattDchaMax;              ///< Max battery discharging current
    float32 ftTempMaxFanCtrl;               ///< Max temperature for fan control
    float32 ftCoeffChrgAcVoltPL_K;          ///< AC voltage Charge power limitation CofK
    float32 ftCoeffChrgAcVoltPL_B;          ///< AC voltage Charge power limitation CofB
    float32 ftCoeffDchaAcVoltPL_K;          ///< AC voltage Discharge power limitation CofK
    float32 ftCoeffDchaAcVoltPL_B;          ///< AC voltage Discharge power limitation CofB

    float32 ftCoeffChrgBattVoltPL_K;        ///< Battery voltage Charge power limitation CofK
    float32 ftCoeffChrgBattVoltPL_B;        ///< Battery voltage Charge power limitation CofB
    float32 ftCoeffDchaBattVoltPL_K;        ///< Battery voltage Discharge power limitation CofK
    float32 ftCoeffDchaBattVoltPL_B;        ///< Battery voltage Discharge power limitation CofB
    float32 ftRecprRatAcOvLoad;             ///< Reciprocal of AC over load ratio
}ST_POW_LIM_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PowLim_BattVolt_1ms(void);
static void v_PowLim_Curr_1ms(void);
static void v_PowLim_Curr_Chrg_1ms(void);
static void v_PowLim_Curr_Chrg_AcVolt_1ms(void);
static void v_PowLim_Curr_Chrg_BattVolt_1ms(void);
static void v_PowLim_Chrg_BattVolt_Curve(void);
static void v_PowLim_Curr_Chrg_PowCalc_1ms(void);
static void v_PowLim_Curr_ChrgChk_1ms(void);
static void v_PowLim_Curr_Dcha_1ms(void);
static void v_PowLim_Curr_Dcha_AcVolt_1ms(void);
static void v_PowLim_Curr_Dcha_BattVolt_1ms(void);
static void v_PowLim_Dcha_BattVolt_Curve(void);
static void v_PowLim_Curr_Dcha_PowCalc_1ms(void);
#if 1U == GRID_PHASE_NUMBER
static void v_PowLim_Curr_Dcha_Batt_LV_1ms(void);
#endif
static void v_PowLim_Curr_BidirChk_1ms(void);
static void v_PowLim_Curr_BattReq_1ms(void);
static void v_PowLim_Curr_AcPow_1ms(void);
static void v_PowLim_Curr_Pow_OnePha_1ms(float32 ftQLim, float32 ftPReq, float32 *ftPlim);
static void v_PowLim_Curr_Temp_1ms(void);
static void v_PowLim_BusVolt_1ms(void);
static void v_PowLim_PowComp_100ms(void);
static void v_PowLim_Temp_100ms(void);
static void v_PowLim_Temp_ChrgHigh_100ms(void);
static void v_PowLim_Temp_ChrgLow_100ms(void);
static void v_PowLim_Temp_DchaHigh_100ms(void);
static void v_PowLim_Temp_DchaLow_100ms(void);
static void v_PowLim_HTSt_100ms(void);
static void v_PowLim_FanDutyCal_100ms(void);

#endif /* POWLIM_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
