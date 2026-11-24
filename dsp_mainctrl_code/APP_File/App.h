//==============================================================================================
//    File description
//==============================================================================================
/**@file         App.h
* TITLE         : APP Include Header File
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.10
* Version       : V1.0
* Descriptions  : Include Header Files & Macro Definition &
*                 Variable Declaration & Function Declaration
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
************************************************************************************************
*/

/*
************************************************************************************************
* Module        :
* 1st Unit      :
* 2nd Unit      :
* 3rd Unit      :
*
* Module Task   :

*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
************************************************************************************************
*/
#ifndef APP_H_
#define APP_H_

//=====================================================
//    Include Header Files
//=====================================================
//#include "F28x_Project.h"
#include "F2837xD_Cla_typedefs.h"    ///< F2837xD CLA Type definitions
#include "F2837xD_device.h"          ///< F2837xD Headerfile Include File

#include "Data_type_definition.h"
#include <math.h>

//=====================================================
//    Macro Definition
//=====================================================
/**************************  ASPICE and Debug Macro Definition *****************************/
/* ASPICE Macro Definition */
#define FLG_SWIT_EN              0U                     ///< SWIT Enabled
#define FLG_SWUT_EN              0U                     ///< SWUT Enabled
#define FLG_RUN_TIME_TEST_EN     0U                     ///< Run time test enabled

/* Test Definition */
#define CLA_GPIO_TEST            0U                     ///< 1U-CLA GPIO Test
#define ENA_SURGE_TEST           1U                     ///< Surge test enable

/********************** SW version and Product model Macro Definition **********************/
/* DSP software version Macro Definition */
#define  DSP_SOFT_VERSON         100U

#define  SST_1250kW

/* Product Macro Definition */
#define GRID_PHASE_NUMBER        3U      ///< Grid phase number (1-7.4kW, 2-19.2kW,3-11kW)
#if GRID_PHASE_NUMBER > 1U
#define ONE_PHASE_COEFF          (1.0f / (float32)GRID_PHASE_NUMBER)    ///< One phase coefficient
#else
#define ONE_PHASE_COEFF          1.0f
#endif

#define IEC_GRID_STD             0x00U                  ///< Grid standard ID - IEC
#define GB_GRID_STD              0x01U                  ///< Grid standard ID - GB
#define UL_GRID_STD              0x02U                  ///< Grid standard ID - UL
#define GRID_STD_ID              IEC_GRID_STD

#define STD_CUSTUMER             0x01U                  ///< Customer ID - standard product
#define BMW_CUSTUMER             0x02U                  ///< Customer ID - BMW product
#define CUSTUMER_ID              BMW_CUSTUMER

#define DUAL_CORE_CPU1           0U                     ///< CPU1
#define DUAL_CORE_CPU2           1U                     ///< CPU2
#define CPU_NUMBER               DUAL_CORE_CPU1
/* Product model definition: bit0~bit3 - Customer ID; bit4~bit7 - Grid standard ID; bit8~bit15 - Power level ID;
 *      IEC_7K4_STD_PROD_MDL     0x0101U                IEC-7.4 standard product model
 *      IEC_7K4_BMW_PROD_MDL     0x0102U                IEC-7.4 BMW product model
 *      GB_7K4_STD_PROD_MDL      0x0111U                GB-7.4 product product model
 *      GB_7K4_BMW_PROD_MDL      0x0112U                GB-7.4 BMW product model
 *      UL_19K2_STD_PROD_MDL     0x0221U                UL-19.2 standard product model
 *      UL_19K2_BMW_PROD_MDL     0x0222U                UL-19.2 BMW product model
 *      IEC_11K_STD_PROD_MDL     0x0301U                IEC-11 standard product model
 *      IEC_11K_BMW_PROD_MDL     0x0302U                IEC-11 BMW product model
 *      GB_11K_STD_PROD_MDL      0x0311U                GB-11 standard product model
 *      GB_11K_BMW_PROD_MDL      0x0312U                GB-11 BMW product model
 */
#define PROD_MDL                 ((((CPU_NUMBER << 3U) | GRID_PHASE_NUMBER) << 8U) | (GRID_STD_ID << 4U) | CUSTUMER_ID)   ///< Product model

/* Function enable Macro Definition */
#define FLG_CPU2_UPD_EN          0U                     ///< CPU2 update enabled
#define FLG_FLT_RSTRT_EN         1U                     ///< Fault restart enabled
#define FLG_SPI_RDID_EN          0U                     ///< SPI read ID debug disabled
#if BMW_CUSTUMER == CUSTUMER_ID
#define FLG_FLT_DATA_REC_EN      1U                     ///< Fault data record disabled
#define FLG_ON_OFF_GRID_SWT_EN   0U                     ///< On&off grid switch disabled
#else
#define FLG_FLT_DATA_REC_EN      1U                     ///< Fault data record enabled
#define FLG_ON_OFF_GRID_SWT_EN   1U                     ///< On&off grid switch enabled
#endif
#define FLG_PFC_POWCTRL_EN          1U                     ///< Pfc power control enabled
#define FLG_PFC_GRIDCTRL_EN         0U                     ///< pfc grid control enable
#define FLG_D2D_POWCTRL_EN          0U                     ///< D2d power control enabled
/* Communication mode Macro Definition */
#define COM_MODE                CAN
#define SCI                     0U
#define CAN                     1U
/***************************** Command data Macro Definition *****************************/
/* Const Macro Definition */
#define PI_CONST                 3.1415926f             ///< pi
#define RECPR_PI_CONST           (1.0f/PI_CONST)        ///< Reciprocal of pi
#define PI_2_CONST               (2.0f*PI_CONST)        ///< 2*pi
#define RECPR_PI_2_CONST         (1.0f/PI_2_CONST)      ///< Reciprocal of 2*pi
#define RECPR_CON_2              (1.0f/2.0f)            ///< Reciprocal of 2.0
#define RECPR_CON_3              (1.0f/3.0f)            ///< Reciprocal of 3.0
#define CON_SQRT_2               1.414214f              ///< sqrt(2)
#define CON_SQRT_3               1.732051f              ///< sqrt(3)
#define RECPR_CON_SQRT_2         (1.0f/CON_SQRT_2)      ///< Reciprocal of sqrt(2)
#define RECPR_CON_SQRT_3         (1.0f/CON_SQRT_3)      ///< Reciprocal of sqrt(3)
#define CON_SQRT_6               2.449490f              ///< sqrt(6)
#define CON_ZERO_DELTA           0.0001f                ///< float zero deviation
#define FCN_ENABLE               1U                     ///< Enable
#define FCN_DISABLE              0U                     ///< Disable
/* Data Type Macro Definition */
#define TYPE_INT16               0x1U                   ///< int16
#define TYPE_UINT16              0x2U                   ///< Uint16
#define TYPE_INT32               0x3U                   ///< int32
#define TYPE_UINT32              0x4U                   ///< Uint32
#define TYPE_FLOAT32             0x5U                   ///< float32
#define TYPE_STRING              0x6U                   ///< string
#define C1_DIV_SQRT3             0.577350269189f
#define SQRT3_DIV_C2             0.866025403784f
#define C2_DIV_C3                0.6666666666667f

#define C1_DIV_SQRT18            0.23570226f
#define C2_DIV_SQRT18            0.47140452f
#define C1_DIV_SQRT6             0.40824829f

#define PI2_DIV_C3               2.094395102393f
/* Data Coefficient Macro Definition */
#define COEFF_VOLT_ARM           10.0f                  ///< Voltage coefficient
#define RECPR_COEFF_VOLT_ARM     (1.0f/COEFF_VOLT_ARM)  ///< Reciprocal of voltage coefficient
#define COEFF_CURR_ARM           100.0f                 ///< Current coefficient
#define RECPR_COEFF_CURR_ARM     (1.0f/COEFF_CURR_ARM)  ///< Reciprocal of current coefficient
#define COEFF_FRQ_ARM            100.0f                 ///< Frequency coefficient
#define RECPR_COEFF_FRQ_ARM      (1.0f/COEFF_FRQ_ARM)   ///< Reciprocal of frequency coefficient
#define COEFF_DC_ARM             1000.0f                ///< DC component coefficient
#define RECPR_COEFF_DC_ARM       (1.0f/COEFF_DC_ARM)    ///< Reciprocal of DC voltage/current coefficient
#define COEFF_TEMP_ARM           10.0f                  ///< Temperature coefficient
#define RECPR_COEFF_TEMP_ARM     (1.0f/COEFF_TEMP_ARM)  ///< Reciprocal of DC voltage/current coefficient
#define COEFF_AUX_ARM            1000.0f                ///< Aux-power voltage coefficient
#define COEFF_PF_ARM             10000.0f               ///< PF coefficient
#define COEFF_FAN_DUTY_ARM       100.0f                 ///< Fan duty coefficient
/* LPF Coefficient Macro Definition */
#define COEFF_LPF_1HZ_1MS        (1.0f/(1.0f+PI_2_CONST*1.0f*0.001f))      ///< 1Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_6HZ_1MS        (1.0f/(1.0f+PI_2_CONST*6.0f*0.001f))      ///< 6Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_10HZ_1MS       (1.0f/(1.0f+PI_2_CONST*10.0f*0.001f))     ///< 10Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_20HZ_1MS       (1.0f/(1.0f+PI_2_CONST*20.0f*0.001f))     ///< 20Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_50HZ_1MS       (1.0f/(1.0f+PI_2_CONST*50.0f*0.001f))     ///< 50Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_1HZ_3MS        (1.0f/(1.0f+PI_2_CONST*1.0f*0.003f))      ///< 1Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_10HZ_100MS     (1.0f/(1.0f+PI_2_CONST*10.0f*0.1f))       ///< 10Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_100HZ_1MS      (1.0f/(1.0f+PI_2_CONST*100.0f*0.001f))    ///< 100Hz LPF Cof1:1/(1+wT)
#define COEFF_LPF_100HZ_3MS      (1.0f/(1.0f+PI_2_CONST*100.0f*0.003f))    ///< 100Hz LPF Cof1:1/(1+wT)
/* DSP PIEACK Macro Definition */
#define PIEACK_GROUP1_DSP        0x0001U
#define PIEACK_GROUP2_DSP        0x0002U
#define PIEACK_GROUP3_DSP        0x0004U
#define PIEACK_GROUP4_DSP        0x0008U
#define PIEACK_GROUP5_DSP        0x0010U
#define PIEACK_GROUP6_DSP        0x0020U
#define PIEACK_GROUP7_DSP        0x0040U
#define PIEACK_GROUP8_DSP        0x0080U
#define PIEACK_GROUP9_DSP        0x0100U
#define PIEACK_GROUP10_DSP       0x0200U
#define PIEACK_GROUP11_DSP       0x0400U
#define PIEACK_GROUP12_DSP       0x0800U

/*************************** System parameter Macro Definition ***************************/
/* DSP system parameter Macro Definition */
#define SYS_CLK_FRQ              200000000UL                               ///< DSP System Clock Frequency
/* AC Rated parameter Macro Definition */
#if 1U == GRID_PHASE_NUMBER
#define RATED_POW                7400.0f                                   ///< Rated power
#elif 2U == GRID_PHASE_NUMBER
#define RATED_POW                19200.0f                                  ///< Rated power
#elif 3U == GRID_PHASE_NUMBER
#define RATED_POW                (70000.0f*3.0f)                           ///< Rated power
#endif
#define POW_AC_RTD               RATED_POW                                 ///< Rated AC Power
#if 2U != GRID_PHASE_NUMBER
#define RATED_AC_VOLT_RMS        962.0f                                    ///< Rated AC voltage RMS
#define RATED_AC_FRQ             50.0f                                     ///< Rated AC frequency RMS
#else
#define RATED_AC_VOLT_RMS        120.0f                                    ///< Rated AC voltage RMS
#define RATED_AC_FRQ             60.0f                                     ///< Rated AC frequency RMS
#endif
#define RATED_AC_VOLT_AMP        (CON_SQRT_2 * RATED_AC_VOLT_RMS)          ///< Rated AC voltage amplitude

#define AC_PF_MIN                0.8f                                      ///< Min AC Power factor: 0.8
#define RATED_AC_REACTV_COEFF    sqrtf(1.0f - AC_PF_MIN * AC_PF_MIN)       ///< Rated AC reactive coefficient
#define RATED_REACTV_POW         (RATED_AC_REACTV_COEFF * POW_AC_RTD)      ///< Rated reactive power

#if(GB_GRID_STD == GRID_STD_ID)
#define RAT_AC_CURR_LIM          1.2f                                      ///< Overload coefficient
#else
#define RAT_AC_CURR_LIM          1.0f
#endif

#ifndef _SIMULATION_NO_DSP_
#define COEFF_AC_CURR_CALC       1.1f                                      ///< AC current calculation coefficient
#else
#define COEFF_AC_CURR_CALC       1.0f                                      ///< AC current calculation coefficient
#endif

#define RATED_AC_CURR_RMS        (COEFF_AC_CURR_CALC * (POW_AC_RTD * ONE_PHASE_COEFF / RATED_AC_VOLT_RMS))        ///< Rated AC active current RMS
#define MAX_AC_CURR_RMS          (RAT_AC_CURR_LIM * RATED_AC_CURR_RMS)          ///< Maximum AC active current RMS

#define POW_AC_1P_RTD            (ONE_PHASE_COEFF * POW_AC_RTD)                 ///< One phase rated power
#define POW_ACTV_1P_RTD          POW_AC_1P_RTD                                  ///< Rated 1-Phase active power
#define RATED_REACTV_POW_1P      (RATED_AC_REACTV_COEFF * POW_ACTV_1P_RTD)      ///< Rated 1-Phase reactive power
#define RATED_ACTV_CURR_RMS      RATED_AC_CURR_RMS                              ///< Rated active current rms
#define RATED_REACTV_CURR_RMS    (RATED_AC_REACTV_COEFF * RATED_AC_CURR_RMS)    ///< Rated reactive current rms

/* DC Rated parameter Macro Definition */
#define RATED_BATT_POW             RATED_POW                                    ///< Rated battery output power
#define POW_BATT_MAX               (RATED_BATT_POW + 100.0f)                    ///< Max battery output power
#define VOLT_BATT_PARL_RTD         300.0f                                       ///< Parallel rated battery voltage
#define VOLT_BATT_PARL_RTD_OV_LOAD (VOLT_BATT_PARL_RTD * 1.2f)                  ///< Parallel rated battery voltage under over load status
#define VOLT_BATT_MIN              200.0f                                       ///< Output Voltage Min
#define VOLT_BATT_MAX              920.0f                                       ///< Output Voltage Target Max
#define VOLT_BATT_SERIES_MIN       400.0f                                       ///< Series Minimum Voltage
#define VOLT_BATT_PARL_MAX         510.0f                                       ///< Parallel Maximum Voltage
#define CURR_BATT_PARL_MAX         (POW_BATT_MAX / VOLT_BATT_PARL_RTD)          ///< Parallel Max battery current
#define CURR_BATT_SERIES_MAX       (CURR_BATT_PARL_MAX * 0.5f)                  ///< Series Max battery current

/************************** EPWM configuration Macro Definition **************************/
#define FRQ_PWMCLK               100000000UL               ///< EPWM Clock Frequency
/* PFC EPWM Macro Definition */
#ifndef _SIMULATION_NO_DSP_
#define FRQ_PFC_SWITCH           24000U                    ///< PFC switch frequency
#if 2U != GRID_PHASE_NUMBER
#define FRQ_BAL_SWITCH           20000U                    ///< Balance bridge switch frequency
#else
#define FRQ_BAL_SWITCH           60000U                    ///< Balance bridge switch frequency
#endif
#else
#define FRQ_PFC_SWITCH           24000U                    ///< PFC switch frequency
#define FRQ_BAL_SWITCH           24000U                    ///< Balance bridge switch frequenc
#endif

#if 1U == GRID_PHASE_NUMBER
#define PERIOD_PFC_PWM           (Uint16)((FRQ_PWMCLK / FRQ_PFC_SWITCH)>>1U)    ///< PFC PWM period register
#define PERIOD_BAL_PWM           (Uint16)((FRQ_PWMCLK / FRQ_BAL_SWITCH)>>1U)    ///< PFC balance bridge PWM period register
#elif 2U == GRID_PHASE_NUMBER
#define PERIOD_PFC_PWM           (Uint16)((FRQ_PWMCLK / FRQ_PFC_SWITCH)>>1U)    ///< PFC PWM period register
#define PERIOD_BAL_PWM           (Uint16)((float32)COEFF_ECAP / (float32)FRQ_BAL_SWITCH)
#elif 3U == GRID_PHASE_NUMBER
#define PERIOD_PFC_PWM           (Uint16)((float32)FRQ_PWMCLK / (float32)PFC_CTRL_INTL / (float32)FRQ_PFC_SWITCH)
#define PERIOD_BAL_PWM           (Uint16)((float32)FRQ_PWMCLK / (float32)PFC_CTRL_INTL / (float32)FRQ_BAL_SWITCH)
#endif

#if 1U == GRID_PHASE_NUMBER
#define PFC_CTRL_INTL            1U                        ///< PFC interrupt entry interval
#define PFC_RMS_POINT_SHIFT_NUM  3U                        ///< PFC RMS calculation point left shift number
#define PFC_FAST_PWM             EPwm8Regs                 ///< PFC fast MOS EPWM register
#define PFC_SLOW_PWM             EPwm9Regs                 ///< PFC slow MOS EPWM register
#define PFC_RELAY_PWM            EPwm10Regs                ///< PFC relay control EPWM register
#define PFC_ISR_PWM_REG          EPwm11Regs                ///< PFC ISR EPWM register
#if 0U == FLG_SWUT_EN
#define PFC_TZ_HW_SUM_PWM_REG    EPwm12Regs                ///< PFC HW fault TZ EPWM register
#else
#define PFC_TZ_HW_SUM_PWM_REG    EPwm12RegsUnitTest        ///< PFC HW fault TZ EPWM register
#endif
#define PFC_PWM_DEADTIME         220U                      ///< PFC dead time
#define BAL_PWM_DEADTIME         2500U
#define PFC_EPWM_DB              (PFC_PWM_DEADTIME/10U)    ///< PFC EPWM DB value
#elif 2U == GRID_PHASE_NUMBER
#define PFC_CTRL_INTL            2U                        ///< PFC interrupt entry interval
#define PFC_RMS_POINT_SHIFT_NUM  2U                        ///< PFC RMS calculation point left shift number
#define PWM_L1A1_REG  			 EPwm4Regs
#define PWM_L1A2_REG  			 EPwm5Regs
#define PWM_L1B1_REG  			 EPwm9Regs
#define PWM_L1B2_REG  			 EPwm10Regs

#define PWM_L2A1_REG  			 EPwm7Regs
#define PWM_L2A2_REG  			 EPwm8Regs
#define PWM_L2B1_REG  			 EPwm11Regs
#define PWM_L2B2_REG  			 EPwm12Regs

#define PWM_BAL_COMP_REG         ECap3Regs.CAP4
#define PWM_BAL_PRD_REG(prd)     ECap3Regs.CAP1 = (prd);\
                                 ECap3Regs.CAP3 = (prd)
#define PFC_PWM_DEADTIME         200U
#define PFC_EPWM_DB              2000U
#define BAL_PWM_DEADTIME         2000U
#elif 3U == GRID_PHASE_NUMBER
#define PFC_CTRL_INTL            2U                        ///< PFC interrupt entry interval
#define PFC_RMS_POINT_SHIFT_NUM  2U                        ///< PFC RMS calculation point left shift number

#if 0U == FLG_SWUT_EN
#define PFC_TZ_HW_SUM_PWM_REG    EPwm5Regs                 ///< PFC HW fault TZ EPWM register
#else
#define PFC_TZ_HW_SUM_PWM_REG    EPwm5RegsUnitTest         ///< PFC HW fault TZ EPWM register
#endif
#define PWM_A_REG                EPwm2Regs                 ///< PFC phase A EPWM register
#define PWM_B_REG                EPwm3Regs                 ///< PFC phase B EPWM register
#define PWM_C_REG                EPwm4Regs                 ///< PFC phase C EPWM register
#define PWM_N_REG                EPwm1Regs                 ///< PFC phase N EPWM register
#define PFC_PWM_DEADTIME         300U                      ///< PFC dead time; 300ns
#define BAL_PWM_DEADTIME         2500U                     ///< 2500ns=2.5us
#endif

#if 3U != GRID_PHASE_NUMBER
#define FRQ_PFC_SWITCH_MAX       65000U                    ///< PFC MAX switch frequency
#define FRQ_PFC_SWITCH_MIN       10000U                    ///< PFC MIN switch frequency
#define FRQ_BAL_SWITCH_MAX       65000U                    ///< PFC balance bridge MAX switch frequency
#define FRQ_BAL_SWITCH_MIN       5000U                     ///< PFC balance bridge MIN switch frequency
#define PFC_PWM_BAL_DEADTIME_MAX 1000U                     ///< PFC balance bridge MAX dead time
#define PFC_PWM_BAL_DEADTIME_MIN 200U                      ///< PFC balance bridge MIN dead time
#else
#define FRQ_PFC_SWITCH_MAX       60000U                    ///< PFC MAX switch frequency
#define FRQ_PFC_SWITCH_MIN       10000U                    ///< PFC MIN switch frequency
#define FRQ_BAL_SWITCH_MAX       100000UL                  ///< PFC balance bridge MAX switch frequency
#define FRQ_BAL_SWITCH_MIN       10000UL                   ///< PFC balance bridge MIN switch frequency
#define PFC_PWM_BAL_DEADTIME_MAX 3000U                     ///< PFC balance bridge MAX dead time
#define PFC_PWM_BAL_DEADTIME_MIN 200U                      ///< PFC balance bridge MIN dead time
#endif
#define PFC_PWM_DEADTIME_MAX     500U                      ///< PFC MAX dead time
#define PFC_PWM_DEADTIME_MIN     200U                      ///< PFC MIN dead time
#define FRQ_PFC_CTRL             (FRQ_PFC_SWITCH / PFC_CTRL_INTL)          ///< PFC Control Frequency
#define PERD_PFC_CTRL            (1.0f/(float32)FRQ_PFC_CTRL)              ///< PFC Control period
/* D2D EPWM Macro Definition */
#if 1U == GRID_PHASE_NUMBER
#define D2D_CLA_FRQ              FRQ_PFC_CTRL                              ///< CLA Frequency
#define D2D_CLA_PRD              (1.0f / (float32)D2D_CLA_FRQ)             ///< CLA period
#define D2D_FRQ_MIN              48000.0f                                  ///< D2D Min Frequency; 48000.0f
#define D2D_FRQ_MAX              200000.0f                                 ///< D2D Max Frequency
#define EPWM_BURST_CBC_FRQ       50000UL                                   ///< CBC Frequency; 50K
#define EPWM_BURST_CBC_PRD       (FRQ_PWMCLK/EPWM_BURST_CBC_FRQ - 1U)      ///< CBC Epwm period
#elif 2U == GRID_PHASE_NUMBER
#define D2D_CLA_FRQ              FRQ_PFC_SWITCH                            ///< CLA Frequency 48kHz
#define D2D_CLA_PRD              (1.0f/ (float32)D2D_CLA_FRQ)              ///< CLA period
#define D2D_FRQ_MIN              41000.0f                                  ///< D2D Min Frequency; 41000.0f
#define D2D_FRQ_MAX              200000.0f                                 ///< D2D Max Frequency
#define BUSN_PWM_FREQ_SET        56000
#define BUS_N_PWM_PERIOD         (Uint16)(200000000.0 / (float32)BUSN_PWM_FREQ_SET -1.0)
#elif 3U == GRID_PHASE_NUMBER
#define D2D_CLA_FRQ               24000.0f                                  ///< CLA Frequency
#define D2D_CLA_PRD               (1.0f/D2D_CLA_FRQ)                        ///< CLA period
#define D2D_FRQ_MIN               48000L                                    ///< Min Frequency
#define D2D_FRQ_MAX               200000L                                   ///< Max Frequency
#define OUTP_DAB_OL_MIN           0.0f                                      ///< Min DS1 in DAB
#define OUTP_DAB_OL_MAX           0.5f                                      ///< Max DS1 in DAB
#define FRQ_EPWM_CLK              100000000.0f                              ///< EPWM Clock Frequency
#define FRQ_D2D_DAB_DFT           70000.0f                                  ///< DAB switching frequency default
#define FRQ_D2D_CLA               24000.0f                                  ///< CLA Frequency
#define PERD_EPWM_DFT             (Uint16)(FRQ_EPWM_CLK/FRQ_D2D_DAB_DFT)    ///< Default Epwm PRD 100000000U/85000.0f
#define PERD_EPWM_D2D_INT         (Uint16)(FRQ_EPWM_CLK/FRQ_D2D_CLA)        ///< Default Epwm PRD 100000000U/24000.0f
#endif
#if 3U != GRID_PHASE_NUMBER
#define PWM_DCEVT_EN             1U                        ///< 1U - PWM DCEVT Enabled
#define PWM_SET_POINT            1U                        ///< 0U- CTR=0 set; 1U- CTR=PRD set
#endif
#define PWM_UP_DN_MODE           0U                        ///< 0U-Up Mode; 1U-Up Down Mode

#define EPWM_INT_PRD             (Uint16)(FRQ_PWMCLK / D2D_CLA_FRQ)                 ///< EPWM INT PRD
#if 0U == PWM_UP_DN_MODE
#define EPWM_PRD_MAX             (Uint16)(FRQ_PWMCLK / (Uint32)D2D_FRQ_MIN)         ///< Max Epwm PRD;2000
#define EPWM_PRD_MIN             (Uint16)(FRQ_PWMCLK / (Uint32)D2D_FRQ_MAX)         ///< Min Epwm PRD;500
#else
#define EPWM_PRD_MAX             (Uint16)((FRQ_PWMCLK / (Uint32)D2D_FRQ_MIN)>>1)    ///< Max Epwm PRD;2000
#define EPWM_PRD_MIN             (Uint16)((FRQ_PWMCLK / (Uint32)D2D_FRQ_MAX)>>1)    ///< Min Epwm PRD;500
#endif
#define EPWM_CMP_MIN             (EPWM_PRD_MIN>>1)                                  ///< Min Epwm CMP

#if 1U == GRID_PHASE_NUMBER
#define EPWM_PRI_UP_BDG          EPwm6Regs                                 ///< Primary Up Bridge EPWM
#define EPWM_PRI_DN_BDG          EPwm7Regs                                 ///< Primary Dn Bridge EPWM
#define EPWM_SEC_UP_BDGL         EPwm1Regs                                 ///< Secondary Up Bridge Left EPWM
#define EPWM_SEC_UP_BDGR         EPwm2Regs                                 ///< Secondary Up Bridge Right EPWM
#define EPWM_SEC_DN_BDGL         EPwm3Regs                                 ///< Secondary Down Bridge Left EPWM
#define EPWM_SEC_DN_BDGR         EPwm4Regs                                 ///< Secondary Down Bridge Right EPWM
#define EPWM_BURST_CBC_REG       EPwm5Regs                                 ///< Burst CBC EPWM Register
#define EPWM_UP_LINK_NUM         5U                                        ///< Link to PRI_UP Epwm6
#define EPWM_DN_LINK_NUM         6U                                        ///< Link to PRI_UP Epwm7
#define EPWM_FAST_LINK_NUM       7U                                        ///< Link to PFC_FAST_PWM Epwm8
#define EPWM_DB_HALFCYCLE        (33U<<1)                                  ///< EPWM DB
#elif 2U == GRID_PHASE_NUMBER
#define EPWM_PRI_UP_BDG         EPwm3Regs       ///< Primary Up Bridge EPWM EPwm3Regs
#define EPWM_PRI_DN_BDG         EPwm6Regs       ///< Primary Dn Bridge EPWM EPwm6Regs
#define EPWM_SEC_UP_BDG         EPwm1Regs       ///< Secondary Up Bridge EPWM
#define EPWM_SEC_DN_BDG         EPwm2Regs       ///< Secondary Down Bridge EPWM
#define EPWM_UP_LINK_NUM        2U              ///< Link to PRI_UP Epwm3
#define EPWM_DN_LINK_NUM        5U              ///< Link to PRI_UP Epwm6
#define EPWM_DB_HALFCYCLE       (33U<<1)        ///< DB
#define EPWM_BURST_CBC_FRQ      50000UL         ///< CBC Frequency; 50K
#define ECAP_BURST_CBC_PRD      ((SYS_CLK_FRQ/EPWM_BURST_CBC_FRQ) - 1U)
#elif 3U == GRID_PHASE_NUMBER
#define EPWM_PRI_BDGL                 EPwm8Regs        ///< Primary Bridge Left EPWM
#define EPWM_PRI_BDGR                 EPwm7Regs        ///< Primary Bridge Right EPWM
#define EPWM_SEC_UP_BDGL              EPwm12Regs       ///< Secondary Up Bridge Left EPWM
#define EPWM_SEC_UP_BDGR              EPwm11Regs       ///< Secondary Up Bridge Right EPWM
#define EPWM_SEC_DN_BDGL              EPwm10Regs       ///< Secondary Down Bridge Left EPWM
#define EPWM_SEC_DN_BDGR              EPwm9Regs        ///< Secondary Down Bridge Right EPWM
#define EPWM_PRD_LINK_NUM             7U               ///< PRD Link to Epwm8
#define EPWM_SEC_BDGL_CMP_LINK_NUM    11U              ///< Link to Epwm12
#define EPWM_SEC_BDGR_CMP_LINK_NUM    10U              ///< Link to Epwm11
#define EPWM_DB_HALFCYCLE             (23U<<1)         ///< DB
#define EPWM_PRI_EN_SEC_EN            3U                ///< Enable Primary EPWM & Enable Secondary EPWM
#endif
#define EPWM_EN                  1U                                        ///< PWM Enable
#define EPWM_DIS                 0U                                        ///< PWM Disable
#define EPWM_PRI_DIS_SEC_DIS     0U                                        ///< Disable Primary EPWM & Disable Secondary EPWM
#define EPWM_PRI_EN_SEC_DIS      1U                                        ///< Enable Primary EPWM & Disable Secondary EPWM
#define EPWM_PRI_DIS_SEC_EN      2U                                        ///< Disable Primary EPWM & Enable Secondary EPWM
#define DISABLE_EPWM(EPWMX)      ((EPWMX).TZFRC.bit.OST = 1U)              ///< Disable EPWMX
#define ENABLE_EPWM(EPWMX)       ((EPWMX).TZCLR.bit.OST = 1U)              ///< Enable EPWMX

/************************** Module PfcPowPreCtrl Macro Definition **************************/
#if(1U == GRID_PHASE_NUMBER)
#define PFC_INPUT_X_CAP                (13.85e-6)                        ///< AC input X-capacitor;10.5
#elif(2U == GRID_PHASE_NUMBER)
#define PFC_INPUT_X_CAP                (12.5e-6)                         ///< AC input X-capacitor 37.3
#elif(3U == GRID_PHASE_NUMBER)
//#define PFC_INPUT_X_CAP                (23.5e-6)                         ///< AC input X-capacitor
#define PFC_INPUT_X_CAP                (0.0f)                         ///< AC input X-capacitor
#endif

/************************** Module PfcDataCalc Macro Definition **************************/
#define GRID_POS_SEQ             0U        ///< Grid positive sequence
#define GRID_NEG_SEQ             1U        ///< Grid negative sequence

/************************** Module PfcPowCtrl Macro Definition **************************/
/** PFC power control Macro Definition */
#define ISR_INTL_RMS_CALC        (Uint16)(1U << PFC_RMS_POINT_SHIFT_NUM)   ///< RMS interrupt calculation interval
#define NUM_20MS_PFC_ISR         (FRQ_PFC_CTRL / 50U / ISR_INTL_RMS_CALC)
#define RECPR_NUM_20MS_PFC_ISR   (1.0f / (float32)NUM_20MS_PFC_ISR)
#define GRID_FRQ_MAX             67U                                       ///< Max grid frequency
#define GRID_FRQ_MIN             44U                                       ///< Min grid frequency
#define MAX_REPEAT_NUM           (FRQ_PFC_CTRL / GRID_FRQ_MIN)
#define MIN_REPEAT_NUM           (FRQ_PFC_CTRL / GRID_FRQ_MAX)
#define MAX_RMS_NUM              (MAX_REPEAT_NUM >> PFC_RMS_POINT_SHIFT_NUM)
#define MIN_RMS_NUM              (MIN_REPEAT_NUM >> PFC_RMS_POINT_SHIFT_NUM)

#define NUM_REPEAT_PERD_CLA      4U                                        ///< Repeat control period number in CLA
#define REPEAT_CTRL_NUM_CLA      (FRQ_PFC_SWITCH / ((int16)RATED_AC_FRQ) / NUM_REPEAT_PERD_CLA)
#define MAX_REPEAT_NUM_CLA       (FRQ_PFC_SWITCH / GRID_FRQ_MIN / NUM_REPEAT_PERD_CLA)
#define MIN_REPEAT_NUM_CLA       (FRQ_PFC_SWITCH / GRID_FRQ_MAX / NUM_REPEAT_PERD_CLA)

#define AC_VOLT_PR_CTRL_MODE     0U                                        ///< AC voltage PR control mode
#define AC_VOLT_REP_CTRL_MODE    1U                                        ///< AC voltage repeat control mode

#define DELTA_THETA_STEP         (RATED_AC_FRQ * PI_2_CONST / (float32)FRQ_PFC_CTRL)
#define COEFF_NOTCH_BW           0.1f                                      ///< Notch bandwidth coefficient
#if 1U == GRID_PHASE_NUMBER
#define COMP_PLL_THETA           0.0125f                                   ///< PLL theta compensation
#define KP_PLL_INIT              0.72f                                     ///< Initial PLL Kp;0.015f
#define KI_PLL_INIT              0.000345f                                 ///< Initial PLL Ki;0.0000072f
#define KP_PLL                   (KP_PLL_INIT * 0.15f)                     ///< PLL Kp
#define KI_PLL                   (KI_PLL_INIT * 0.1f)                      ///< PLL Ki
#define MAX_PLL_LOOP             (18.0f * PI_2_CONST)                      ///< Max PLL loop output: 18Hz
#define MIN_PLL_LOOP             (-MAX_PLL_LOOP)                           ///< Min PLL loop output: -18Hz

#define KP_PFC_BUS_VOLT_LOOP     0.53f                                     ///< PFC Bus voltage loop Kp
#define KI_PFC_BUS_VOLT_LOOP     0.0013f                                   ///< PFC Bus voltage loop Ki
#define MAX_PFC_BUS_VOLT_LOOP    58.0f                                     ///< Max PFC bus voltage loop
#define MIN_PFC_BUS_VOLT_LOOP    (-MAX_PFC_BUS_VOLT_LOOP)                  ///< Min PFC bus voltage loop

#define KP_CURR_LOOP             4.0f                                      ///< Current loop Kp;4.0f
#define KI_CURR_LOOP             0.005f                                    ///< Current loop Ki
#define MAX_CURR_LOOP            100.0f                                    ///< Max current loop;100.0f
#elif 2U == GRID_PHASE_NUMBER
#define COMP_PLL_THETA           0.0125f                                   ///< PLL theta compensation
#define KP_PLL_INIT              0.015f                                    ///< Initial PLL Kp
#define KI_PLL_INIT              0.0001f                                   ///< Initial PLL Ki
#define KP_PLL                   (KP_PLL_INIT * 0.55f)                     ///< PLL Kp
#define KI_PLL                   (KI_PLL_INIT * 0.4f)                      ///< PLL Ki
#define MAX_PLL_LOOP             (DELTA_THETA_STEP*2000.0f)                ///< Max PLL loop output
#define MIN_PLL_LOOP             (-MAX_PLL_LOOP)                           ///< Min PLL loop output

#define KP_PFC_BUS_VOLT_LOOP     0.78f                                     ///< PFC Bus voltage loop Kp
#define KI_PFC_BUS_VOLT_LOOP     0.003f                                    ///< PFC Bus voltage loop Ki
#define MAX_PFC_BUS_VOLT_LOOP    135.0f                                    ///< Max PFC bus voltage loop
#define MIN_PFC_BUS_VOLT_LOOP    (-MAX_PFC_BUS_VOLT_LOOP)                  ///< Min PFC bus voltage loop

#define KP_CURR_LOOP             0.39f                                     ///< Current loop Kp
#define KI_CURR_LOOP             0.0f                                      ///< Current loop Ki
#define MAX_CURR_LOOP            350.0f                                    ///< Max current loop
#elif 3U == GRID_PHASE_NUMBER
#define COMP_PLL_THETA           0.0125f                                   ///< PLL theta compensation
#define KP_PLL_INIT              0.000078f                                 ///< Initial PLL Kp
#define KI_PLL_INIT              0.00000017f                               ///< Initial PLL Ki
#define KP_PLL                   (KP_PLL_INIT * 0.18f)                     ///< PLL Kp
#define KI_PLL                   (KI_PLL_INIT * 0.1f)                      ///< PLL Ki
#define MAX_PLL_LOOP             (DELTA_THETA_STEP*2.0f)                   ///< Max PLL loop output
#define MIN_PLL_LOOP             (-MAX_PLL_LOOP)                           ///< Min PLL loop output

#define KP_PFC_BUS_VOLT_LOOP     0.86f                                     ///< PFC Bus voltage loop Kp
#define KI_PFC_BUS_VOLT_LOOP     0.002f                                    ///< PFC Bus voltage loop Ki
#define MAX_PFC_BUS_VOLT_LOOP    38.0f                                     ///< Max PFC bus voltage loop
#define MIN_PFC_BUS_VOLT_LOOP    (-MAX_PFC_BUS_VOLT_LOOP)                  ///< Min PFC bus voltage loop

#define KP_CURR_LOOP             3.0f                                      ///< Current loop Kp
#define KI_CURR_LOOP             0.003f                                    ///< Current loop Ki
#define MAX_CURR_LOOP            100.0f                                    ///< Max current loop
#endif
#define MIN_CURR_LOOP            (-MAX_CURR_LOOP)                          ///< Min current loop

#define KR_CURR_LOOP_1ST_PR      25.0f                                     ///< Current loop 1st PR Kr
#define WC_CURR_LOOP_1ST_PR      (PI_2_CONST * 0.25f)                      ///< Current loop 1st PR Wc
#define MAX_CURR_LOOP_1ST_PR     150.0f                                    ///< Current loop 1st PR Max output
#define MIN_CURR_LOOP_1ST_PR     (-MAX_CURR_LOOP_1ST_PR)                   ///< Current loop 1st PR Min output

#define KR_CURR_LOOP_3RD_PR      40.0f                                     ///< Current loop 3rd PR Kr
#define WC_CURR_LOOP_3RD_PR      (WC_CURR_LOOP_1ST_PR * 3.0f)              ///< Current loop 3rd PR Wc
#define MAX_CURR_LOOP_3RD_PR     50.0f                                     ///< Current loop 3rd PR Max output
#define MIN_CURR_LOOP_3RD_PR     (-MAX_CURR_LOOP_3RD_PR)                   ///< Current loop 3rd PR Min output

#define KR_CURR_LOOP_5TH_PR      35.0f                                     ///< Current loop 5th PR Kr
#define WC_CURR_LOOP_5TH_PR      (WC_CURR_LOOP_1ST_PR * 5.0f)              ///< Current loop 5th PR Wc
#define MAX_CURR_LOOP_5TH_PR     30.0f                                     ///< Current loop 5th PR Max output
#define MIN_CURR_LOOP_5TH_PR     (-MAX_CURR_LOOP_5TH_PR)                   ///< Current loop 5th PR Min output

#define KR_CURR_LOOP_7TH_PR      30.0f                                     ///< Current loop 7th PR Kr
#define WC_CURR_LOOP_7TH_PR      (WC_CURR_LOOP_1ST_PR * 7.0f)              ///< Current loop 7th PR Wc
#define MAX_CURR_LOOP_7TH_PR     20.0f                                     ///< Current loop 7th PR Max output
#define MIN_CURR_LOOP_7TH_PR     (-MAX_CURR_LOOP_7TH_PR)                   ///< Current loop 7th PR Min output

#define ORDER_9TH_PR             9.0f                                      ///< Harmonic order of 2nd PR
#define KR_CURR_LOOP_9TH_PR      20.0f                                     ///< Current loop 2nd PR Kr
#define WC_CURR_LOOP_9TH_PR      (WC_CURR_LOOP_1ST_PR * ORDER_9TH_PR)      ///< Current loop 2nd PR Wc: for 9th harmonic
#define MAX_CURR_LOOP_9TH_PR     15.0f                                     ///< Current loop 2nd PR Max output
#define MIN_CURR_LOOP_9TH_PR     (-MAX_CURR_LOOP_9TH_PR)                   ///< Current loop 2nd PR Min output

#define ORDER_15TH_PR            15.0f                                     ///< Harmonic order of 11th PR
#define KR_CURR_LOOP_15TH_PR     15.0f                                     ///< Current loop 15th PR Kr
#define WC_CURR_LOOP_15TH_PR     (WC_CURR_LOOP_1ST_PR * ORDER_15TH_PR)     ///< Current loop 15th PR Wc: for 15th harmonic
#define MAX_CURR_LOOP_15TH_PR    15.0f                                     ///< Current loop 15th PR Max output
#define MIN_CURR_LOOP_15TH_PR    (-MAX_CURR_LOOP_15TH_PR)                  ///< Current loop 15th PR Min output

#if 1U == GRID_PHASE_NUMBER
#define KP_AC_VOLT_LOOP          0.2f                                      ///< AC voltage loop Kp
#define KI_AC_VOLT_LOOP          0.015f                                    ///< AC voltage loop Ki;0.003f
#define MAX_AC_VOLT_LOOP         (1.8f * CON_SQRT_2 * RATED_AC_CURR_RMS)   ///< Max AC voltage loop
#define MIN_AC_VOLT_LOOP         (-MAX_AC_VOLT_LOOP)                       ///< Min AC voltage loop

#define QZ_AC_VOLT_LOOP_REP         0.97f
#define KR_COMP_AC_VOLT_LOOP_REP    0.1f
#define NR_COMP_AC_VOLT_LOOP_REP    20U
#define MAX_AC_VOLT_LOOP_REP        (MAX_AC_VOLT_LOOP)

#define KR_AC_VOLT_LOOP_1ST_PR      20.0f                                  ///< Voltage loop 1st PR Kr;40.0f
#define WC_AC_VOLT_LOOP_1ST_PR      (PI_2_CONST * 0.1f)                    ///< Voltage loop 1st PR Wc;0.25f
#define MAX_AC_VOLT_LOOP_1ST_PR     (1.0f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 1st PR Max output
#define MIN_AC_VOLT_LOOP_1ST_PR     (-MAX_AC_VOLT_LOOP_1ST_PR)             ///< Voltage loop 1st PR Min output

#define KR_AC_VOLT_LOOP_3RD_PR      20.0f                                  ///< Voltage loop 3rd PR Kr;40.0f
#define WC_AC_VOLT_LOOP_3RD_PR      (WC_AC_VOLT_LOOP_1ST_PR * 3.0f)        ///< Voltage loop 3rd PR Wc
#define MAX_AC_VOLT_LOOP_3RD_PR     (0.5f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 3rd PR Max output
#define MIN_AC_VOLT_LOOP_3RD_PR     (-MAX_AC_VOLT_LOOP_3RD_PR)             ///< Voltage loop 3rd PR Min output

#define KR_AC_VOLT_LOOP_5TH_PR      27.5f                                  ///< Voltage loop 5th PR Kr;55.0f
#define WC_AC_VOLT_LOOP_5TH_PR      (WC_AC_VOLT_LOOP_1ST_PR * 5.0f)        ///< Voltage loop 5th PR Wc
#define MAX_AC_VOLT_LOOP_5TH_PR     (0.4f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 5th PR Max output
#define MIN_AC_VOLT_LOOP_5TH_PR     (-MAX_AC_VOLT_LOOP_5TH_PR)             ///< Voltage loop 5th PR Min output

#define KR_AC_VOLT_LOOP_7TH_PR      22.5f                                  ///< Voltage loop 7th PR Kr;45.0
#define WC_AC_VOLT_LOOP_7TH_PR      (WC_AC_VOLT_LOOP_1ST_PR * 7.0f)        ///< Voltage loop 7th PR Wc
#define MAX_AC_VOLT_LOOP_7TH_PR     (0.3f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 7th PR Max output
#define MIN_AC_VOLT_LOOP_7TH_PR     (-MAX_AC_VOLT_LOOP_7TH_PR)             ///< Voltage loop 7th PR Min output
#elif 2U == GRID_PHASE_NUMBER
#define KP_AC_VOLT_LOOP             0.5f                                   ///< AC voltage loop Kp
#define KI_AC_VOLT_LOOP             0.01f                                  ///< AC voltage loop Ki
#define MAX_AC_VOLT_LOOP            (2.0f * CON_SQRT_2 * RATED_AC_CURR_RMS)///< Max AC voltage loop
#define MIN_AC_VOLT_LOOP            (-MAX_AC_VOLT_LOOP)                    ///< Min AC voltage loop

#define QZ_AC_VOLT_LOOP_REP         0.91f
#define KR_COMP_AC_VOLT_LOOP_REP    0.139f
#define NR_COMP_AC_VOLT_LOOP_REP    11U
#define MAX_AC_VOLT_LOOP_REP        (MAX_AC_VOLT_LOOP)

#define KR_AC_VOLT_LOOP_1ST_PR      20.0f                                  ///< Voltage loop 1st PR Kr
#define WC_AC_VOLT_LOOP_1ST_PR      3.0f                                   ///< Voltage loop 1st PR Wc
#define MAX_AC_VOLT_LOOP_1ST_PR     (1.0f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 1st PR Max output
#define MIN_AC_VOLT_LOOP_1ST_PR     (-MAX_AC_VOLT_LOOP_1ST_PR)             ///< Voltage loop 1st PR Min output

#define KR_AC_VOLT_LOOP_3RD_PR      20.0f                                  ///< Voltage loop 3rd PR Kr
#define WC_AC_VOLT_LOOP_3RD_PR      9.0f                                   ///< Voltage loop 3rd PR Wc
#define MAX_AC_VOLT_LOOP_3RD_PR     (0.5f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 3rd PR Max output
#define MIN_AC_VOLT_LOOP_3RD_PR     (-MAX_AC_VOLT_LOOP_3RD_PR)             ///< Voltage loop 3rd PR Min output

#define KR_AC_VOLT_LOOP_5TH_PR      20.0f                                  ///< Voltage loop 5th PR Kr
#define WC_AC_VOLT_LOOP_5TH_PR      11.0f                                  ///< Voltage loop 5th PR Wc
#define MAX_AC_VOLT_LOOP_5TH_PR     (0.4f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 5th PR Max output
#define MIN_AC_VOLT_LOOP_5TH_PR     (-MAX_AC_VOLT_LOOP_5TH_PR)             ///< Voltage loop 5th PR Min output

#define KR_AC_VOLT_LOOP_7TH_PR      15.0f                                  ///< Voltage loop 7th PR Kr
#define WC_AC_VOLT_LOOP_7TH_PR      15.0f                                  ///< Voltage loop 7th PR Wc
#define MAX_AC_VOLT_LOOP_7TH_PR     (0.3f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 7th PR Max output
#define MIN_AC_VOLT_LOOP_7TH_PR     (-MAX_AC_VOLT_LOOP_7TH_PR)             ///< Voltage loop 7th PR Min output
#elif 3U == GRID_PHASE_NUMBER
#define KP_AC_VOLT_LOOP             0.5f                                   ///< AC voltage loop Kp
#define KI_AC_VOLT_LOOP             0.01f                                  ///< AC voltage loop Ki
#define MAX_AC_VOLT_LOOP            (2.0f * CON_SQRT_2 * RATED_AC_CURR_RMS)///< Max AC voltage loop
#define MIN_AC_VOLT_LOOP            (-MAX_AC_VOLT_LOOP)                    ///< Min AC voltage loop

#define QZ_AC_VOLT_LOOP_REP         0.86f
#define KR_COMP_AC_VOLT_LOOP_REP    0.239f
#define NR_COMP_AC_VOLT_LOOP_REP    10U
#define MAX_AC_VOLT_LOOP_REP        (MAX_AC_VOLT_LOOP)

#define KR_AC_VOLT_LOOP_1ST_PR      20.0f                                  ///< Voltage loop 1st PR Kr
#define WC_AC_VOLT_LOOP_1ST_PR      3.0f                                   ///< Voltage loop 1st PR Wc
#define MAX_AC_VOLT_LOOP_1ST_PR     (1.0f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 1st PR Max output
#define MIN_AC_VOLT_LOOP_1ST_PR     (-MAX_AC_VOLT_LOOP_1ST_PR)             ///< Voltage loop 1st PR Min output

#define KR_AC_VOLT_LOOP_3RD_PR      20.0f                                  ///< Voltage loop 3rd PR Kr
#define WC_AC_VOLT_LOOP_3RD_PR      9.0f                                   ///< Voltage loop 3rd PR Wc
#define MAX_AC_VOLT_LOOP_3RD_PR     (0.5f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 3rd PR Max output
#define MIN_AC_VOLT_LOOP_3RD_PR     (-MAX_AC_VOLT_LOOP_3RD_PR)             ///< Voltage loop 3rd PR Min output

#define KR_AC_VOLT_LOOP_5TH_PR      20.0f                                  ///< Voltage loop 5th PR Kr
#define WC_AC_VOLT_LOOP_5TH_PR      11.0f                                  ///< Voltage loop 5th PR Wc
#define MAX_AC_VOLT_LOOP_5TH_PR     (0.4f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 5th PR Max output
#define MIN_AC_VOLT_LOOP_5TH_PR     (-MAX_AC_VOLT_LOOP_5TH_PR)             ///< Voltage loop 5th PR Min output

#define KR_AC_VOLT_LOOP_7TH_PR      15.0f                                  ///< Voltage loop 7th PR Kr
#define WC_AC_VOLT_LOOP_7TH_PR      15.0f                                  ///< Voltage loop 7th PR Wc
#define MAX_AC_VOLT_LOOP_7TH_PR     (0.3f * MAX_AC_VOLT_LOOP)              ///< Voltage loop 7th PR Max output
#define MIN_AC_VOLT_LOOP_7TH_PR     (-MAX_AC_VOLT_LOOP_7TH_PR)             ///< Voltage loop 7th PR Min output
#endif

#if(2U == GRID_PHASE_NUMBER)
#define KP_VOLT_LOOP             0.5f                                      ///< Voltage loop Kp
#define KI_VOLT_LOOP             0.01f                                     ///< Voltage loop Ki
#define MAX_VOLT_LOOP            MAX_AC_VOLT_LOOP                          ///< Max Voltage loop
#define MIN_VOLT_LOOP            MIN_AC_VOLT_LOOP                          ///< Min Voltage loop

#define KP_CURR_D_P_LOOP         1.8f                                      ///< Current loop Kp
#define KI_CURR_D_P_LOOP         0.003f                                    ///< Current loop Ki
#define MAX_CURR_D_P_LOOP        550.0f                                    ///< Max current loop
#define MIN_CURR_D_P_LOOP        (-MAX_CURR_D_P_LOOP)                      ///< Min current loop

#define KP_CURR_Q_P_LOOP         1.8f                                      ///< Current loop Kp
#define KI_CURR_Q_P_LOOP         0.003f                                    ///< Current loop Ki
#define MAX_CURR_Q_P_LOOP        550.0f                                    ///< Max current loop
#define MIN_CURR_Q_P_LOOP        (-MAX_CURR_Q_P_LOOP)                      ///< Min current loop

#define KP_CURR_D_N_LOOP         1.0f                                      ///< Current loop Kp
#define KI_CURR_D_N_LOOP         0.003f                                    ///< Current loop Ki
#define MAX_CURR_D_N_LOOP        200.0f                                    ///< Max current loop
#define MIN_CURR_D_N_LOOP        (-MAX_CURR_D_N_LOOP)                      ///< Min current loop

#define KP_CURR_Q_N_LOOP         1.0f                                      ///< Current loop Kp
#define KI_CURR_Q_N_LOOP         0.003f                                    ///< Current loop Ki
#define MAX_CURR_Q_N_LOOP        200.0f                                    ///< Max current loop
#define MIN_CURR_Q_N_LOOP        (-MAX_CURR_Q_N_LOOP)                      ///< Min current loop

#define KP_VOLT_D_P_LOOP         0.156f                                    ///< Voltage loop Kp
#define KI_VOLT_D_P_LOOP         0.0003925f                                ///< Voltage loop Ki
#define MAX_VOLT_D_P_LOOP        80.0f                                     ///< Max Voltage loop
#define MIN_VOLT_D_P_LOOP        (-MAX_VOLT_D_P_LOOP)                      ///< Min Voltage loop

#define KP_VOLT_Q_P_LOOP         0.156f                                    ///< Voltage loop Kp
#define KI_VOLT_Q_P_LOOP         0.0003925f                                ///< Voltage loop Ki
#define MAX_VOLT_Q_P_LOOP        80.0f                                     ///< Max Voltage loop
#define MIN_VOLT_Q_P_LOOP        (-MAX_VOLT_Q_P_LOOP)                      ///< Min Voltage loop

#define KP_VOLT_D_N_LOOP         0.146f                                    ///< Voltage loop Kp
#define KI_VOLT_D_N_LOOP         0.0003225f                                ///< Voltage loop Ki
#define MAX_VOLT_D_N_LOOP        80.0f                                     ///< Max Voltage loop
#define MIN_VOLT_D_N_LOOP        (-MAX_VOLT_D_N_LOOP)                      ///< Min Voltage loop

#define KP_VOLT_Q_N_LOOP         0.146f                                    ///< Voltage loop Kp
#define KI_VOLT_Q_N_LOOP         0.0003225f                                ///< Voltage loop Ki
#define MAX_VOLT_Q_N_LOOP        80.0f                                     ///< Max Voltage loop
#define MIN_VOLT_Q_N_LOOP        (-MAX_VOLT_Q_N_LOOP)                      ///< Min Voltage loop
#elif (3U == GRID_PHASE_NUMBER)
#define KP_VOLT_LOOP             0.09f                                     ///< Voltage loop Kp
#define KI_VOLT_LOOP             0.00002f                                  ///< Voltage loop Ki
#define MAX_VOLT_LOOP            600.0f                                    ///< Max Voltage loop
#define MIN_VOLT_LOOP            (-MAX_VOLT_LOOP)                          ///< Min Voltage loop

#define KP_CURR_D_P_LOOP         2.0*1.0f                                     ///< Current loop Kp
#define KI_CURR_D_P_LOOP         0.008f                                    ///< Current loop Ki
#define MAX_CURR_D_P_LOOP        5.0f*3.0f                                    ///< Max current loop
#define MIN_CURR_D_P_LOOP        (-MAX_CURR_D_P_LOOP)                      ///< Min current loop

#define KP_CURR_Q_P_LOOP         2.0*1.0f                                     ///< Current loop Kp
#define KI_CURR_Q_P_LOOP         0.008f                                    ///< Current loop Ki
#define MAX_CURR_Q_P_LOOP        5.0f                                    ///< Max current loop
#define MIN_CURR_Q_P_LOOP        (-MAX_CURR_Q_P_LOOP)                      ///< Min current loop

#define KP_CURR_D_N_LOOP         2.0f                                      ///< Current loop Kp
#define KI_CURR_D_N_LOOP         0.008f                                    ///< Current loop Ki
#define MAX_CURR_D_N_LOOP        5.0f                                    ///< Max current loop
#define MIN_CURR_D_N_LOOP        (-MAX_CURR_D_N_LOOP)                      ///< Min current loop

#define KP_CURR_Q_N_LOOP         2.0f                                      ///< Current loop Kp
#define KI_CURR_Q_N_LOOP         0.008f                                    ///< Current loop Ki
#define MAX_CURR_Q_N_LOOP        5.0f                                     ///< Max current loop
#define MIN_CURR_Q_N_LOOP        (-MAX_CURR_Q_N_LOOP)                      ///< Min current loop

#define KP_VOLT_D_P_LOOP         0.5f                                      ///< Voltage loop Kp
#define KI_VOLT_D_P_LOOP         0.001f                                    ///< Voltage loop Ki
#define MAX_VOLT_D_P_LOOP        MAX_AC_VOLT_LOOP                          ///< Max Voltage loop
#define MIN_VOLT_D_P_LOOP        MIN_AC_VOLT_LOOP                          ///< Min Voltage loop

#define KP_VOLT_Q_P_LOOP         0.5f                                      ///< Voltage loop Kp
#define KI_VOLT_Q_P_LOOP         0.001f                                    ///< Voltage loop Ki
#define MAX_VOLT_Q_P_LOOP        MAX_AC_VOLT_LOOP                          ///< Max Voltage loop
#define MIN_VOLT_Q_P_LOOP        MIN_AC_VOLT_LOOP                          ///< Min Voltage loop

#define KP_VOLT_D_N_LOOP         0.15f                                     ///< Voltage loop Kp
#define KI_VOLT_D_N_LOOP         0.001f                                    ///< Voltage loop Ki
#define MAX_VOLT_D_N_LOOP        MAX_AC_VOLT_LOOP                          ///< Max Voltage loop
#define MIN_VOLT_D_N_LOOP        MIN_AC_VOLT_LOOP                          ///< Min Voltage loop

#define KP_VOLT_Q_N_LOOP         0.15f                                     ///< Voltage loop Kp
#define KI_VOLT_Q_N_LOOP         0.001f                                    ///< Voltage loop Ki
#define MAX_VOLT_Q_N_LOOP        MAX_AC_VOLT_LOOP                          ///< Max Voltage loop
#define MIN_VOLT_Q_N_LOOP        MIN_AC_VOLT_LOOP                          ///< Min Voltage loop

#define KP_VOLT_BALANCE_LOOP     0.0005f                                  ///< Voltage loop Kp
#define KI_VOLT_BALANCE_LOOP     0.00002f                                 ///< Voltage loop Ki
#define MAX_VOLT_BALANCE_LOOP    8.0f                                    ///< Max Voltage loop
#define MIN_VOLT_BALANCE_LOOP    (-MAX_VOLT_BALANCE_LOOP)                 ///< Min Voltage loop

#define KP_SOC_BALANCE_LOOP      10.0f                                  ///< Voltage loop Kp
#define KI_SOC_BALANCE_LOOP      0.0f                                 ///< Voltage loop Ki
#define MAX_SOC_BALANCE_LOOP     200.0f                                    ///< Max Voltage loop
#define MIN_SOC_BALANCE_LOOP     (-MAX_SOC_BALANCE_LOOP)                 ///< Min Voltage loop

#endif

#if 1U == GRID_PHASE_NUMBER
#define KP_AC_CURR_DC_LOOP       0.001f*0.05f                              ///< AC current DC component control loop KP
#define KI_AC_CURR_DC_LOOP       0.0005f*0.05f                             ///< AC current DC component control loop KI
#define LMT_AC_CURR_DC_LOOP      5.0f                                      ///< AC current DC component control loop output limit
#define KP_AC_VOLT_DC_LOOP       0.0001f*0.3f                              ///< AC voltage DC component control loop KP
#define KI_AC_VOLT_DC_LOOP       0.00005f*0.3f                             ///< AC voltage DC component control loop KI
#define LMT_AC_VOLT_DC_LOOP      10.0f                                     ///< AC voltage DC component control loop output limit
#elif 2U == GRID_PHASE_NUMBER
#define KP_AC_CURR_DC_LOOP       0.00005f                                  ///< AC current DC component control loop KP
#define KI_AC_CURR_DC_LOOP       0.0000425f                                ///< AC current DC component control loop KI
#define LMT_AC_CURR_DC_LOOP      6.0f                                      ///< AC current DC component control loop output limit
#define KP_AC_VOLT_DC_LOOP       0.9f                                      ///< AC voltage DC component control loop KP
#define KI_AC_VOLT_DC_LOOP       0.05f                                     ///< AC voltage DC component control loop KI
#define LMT_AC_VOLT_DC_LOOP      5000.0f                                   ///< AC voltage DC component control loop output limit
#else
#define KP_AC_CURR_DC_LOOP       (0.001f * 0.04f)                          ///< AC current DC component control loop KP
#define KI_AC_CURR_DC_LOOP       (0.0005f * 0.04f)                         ///< AC current DC component control loop KI
#define LMT_AC_CURR_DC_LOOP      3.0f                                      ///< AC current DC component control loop output limit, 3A
#define KP_AC_VOLT_DC_LOOP       0.9f                                      ///< AC voltage DC component control loop KP
#define KI_AC_VOLT_DC_LOOP       0.05f                                     ///< AC voltage DC component control loop KI
#define LMT_AC_VOLT_DC_LOOP      10000.0f                                  ///< AC voltage DC component control loop output limit, 10V
#endif

#define SVPWM                    0U                                        ///< SVPWM modulation
#define SPWM                     1U                                        ///< SPWM modulation
#define DPWM                     2U                                        ///< DPWM modulation

/************************** Module D2dPowCtrl Macro Definition **************************/
#define COEFF_D2D_FRQ_MAX             (D2D_FRQ_MIN / D2D_FRQ_MAX)                            ///< Max Frequency corresponding coefficient;0.25
#define D2D_MIN_LOOP_OUT_BW           (0.05f * COEFF_D2D_FRQ_MAX)                            ///< D2D Min Loop Output Bandwidth
#define COEFF_INV_D2D_FRQ_MAX         (1.0f / COEFF_D2D_FRQ_MAX)                             ///< Inverse coefficient
#define FRQ_D2D_OPEN_LOOP_BURST_MAX   (D2D_FRQ_MAX + 100000.0f)                              ///< Open-loop Max Burst Freq
#define COEFF_D2D_OPEN_LOOP_BURST     (1.0f / (FRQ_D2D_OPEN_LOOP_BURST_MAX - D2D_FRQ_MAX))   ///< Open-loop Max Burst Freq
#define VOLT_BATT_REQ_MIN             (VOLT_BATT_MIN - 2.0f)                                 ///< Min request output Voltage
#define VOLT_BATT_REQ_MAX             (VOLT_BATT_MAX + 15.0f)                                ///< Max request output Voltage
#define CURR_BATT_TGT_MIN              0.0f                                                  ///< Output Current Target Min;0.3f
#if 1U == GRID_PHASE_NUMBER
#define CURR_BATT_TGT_MAX             (CURR_BATT_PARL_MAX + 2.0f)                            ///< Output Current Target Max
#define VOLT_BATT_BURST_PARL_MAX      (VOLT_BATT_PARL_MAX + 10.0f)                           ///< Parallel maximum burst voltage
#define VOLT_BATT_BURST_SERIES_MAX    (VOLT_BATT_REQ_MAX + 10.0f)                            ///< Series maximum burst voltage
#define CURR_BATT_BURST_PARL_MAX      (CURR_BATT_PARL_MAX + 10.0f)                            ///< Parallel maximum burst current;8.0f->10.f
#define CURR_BATT_BURST_SERIES_MAX    (CURR_BATT_SERIES_MAX + 10.0f)                          ///< Series maximum burst current;8.0f->10.f
#define VOLT_BUS_BURST_MAX            445.0f                                                 ///< Maximum burst bus voltage;445.0f
#elif 2U == GRID_PHASE_NUMBER
#define CURR_BATT_TGT_MAX             (CURR_BATT_PARL_MAX + 3.5f)                            ///< Output Current Target Max
#define VOLT_BATT_BURST_PARL_MAX      (VOLT_BATT_PARL_MAX + 10.0f)                           ///< Parallel maximum burst voltage
#define VOLT_BATT_BURST_SERIES_MAX    (VOLT_BATT_REQ_MAX + 10.0f)                            ///< Series maximum burst voltage
#define CURR_BATT_BURST_PARL_MAX      (CURR_BATT_PARL_MAX + 8.0f)                            ///< Parallel maximum burst current
#define CURR_BATT_BURST_SERIES_MAX    (CURR_BATT_SERIES_MAX + 8.0f)                          ///< Series maximum burst current
#define VOLT_BUS_BURST_MAX            465.0f                                                 ///< Maximum burst bus voltage;445.0f
#elif 3U == GRID_PHASE_NUMBER
#define CURR_BATT_TGT_MAX             (CURR_BATT_PARL_MAX + 2.0f)                            ///< Output Current Target Max
#define VOLT_BATT_BURST_PARL_MAX      (VOLT_BATT_PARL_MAX + 10.0f)                           ///< Battery max burst voltage in parallel mode
#define VOLT_BATT_BURST_SERIES_MAX    (VOLT_BATT_MAX + 10.0f)                                ///< Battery max burst voltage in series mode
#define CURR_BATT_BURST_PARL_MAX      (CURR_BATT_PARL_MAX + 3.5f)                            ///< Battery max burst current in parallel mode
#define CURR_BATT_BURST_SERIES_MAX    (CURR_BATT_SERIES_MAX + 3.5f)                          ///< Battery max burst current in series mode
#define VOLT_BUS_BURST_MAX            850.0f                                                 ///< Bus max burst voltage
#endif
#if(3U == GRID_PHASE_NUMBER)
#define BURST_BUS_VOLT_DELTA          100.0f                                                 ///< Maximum burst delta bus voltage
#else
#define BURST_BUS_VOLT_DELTA          30.0f                                                  ///< Maximum burst delta bus voltage
#define BURST_BUS_VOLT_DELTA_RT       30.0f                                                  ///< Maximum burst delta bus voltage at Room Temperature
#define BURST_BUS_VOLT_DELTA_LT       45.0f                                                  ///< Maximum burst delta bus voltage at Low Temperature
#endif
/* D2D Loop Control Parameter*/
#define CURR_INV_DIR                  0U                                                     ///< Invalid Direction
#define CURR_CHG_DIR                  1U                                                     ///< Charge Direction
#define CURR_DISCH_DIR                2U                                                     ///< Discharge Direction
#define VOLT_LOOP_MODE                0U                                                     ///< Voltage Loop Mode
#define CURR_LOOP_MODE                1U                                                     ///< Current Loop Mode
#define MAX_D2D_LOOP_OUTP             1.0f                                                   ///< D2D loop output MAX
#define MIN_D2D_LOOP_OUTP             -1.0f                                                  ///< D2D loop output MIN
#define D2D_LOOP_SW_DVAL              0.02f                                                  ///< D2D loop switch difference value
#define D2D_LOOP_STEP_LMT             0.01f                                                  ///< D2D loop output step limit

#if 1U == GRID_PHASE_NUMBER
#define KP_BATT_VOLT_LOOP             0.0025f                                                ///< Battery Voltage Loop Kp;0.005f
#define KI_BATT_VOLT_LOOP             0.00002f                                               ///< Battery Voltage Loop Ki;0.00001f
#define MAX_BATT_VOLT_LOOP            1.0f                                                   ///< Battery Voltage Loop Max
#define MIN_BATT_VOLT_LOOP            (-MAX_BATT_VOLT_LOOP)                                  ///< Battery Voltage Loop Min

#define KR_BATT_VOLT_PR_1ST_LOOP      0.05f                                                  ///< Battery Voltage 1st PR Kr;0.015f
#define MAX_BATT_VOLT_PR_1ST_LOOP     0.15f                                                  ///< Battery Voltage 1st PR Max output;0.15f
#define MIN_BATT_VOLT_PR_1ST_LOOP     (-MAX_BATT_VOLT_PR_1ST_LOOP)                           ///< Battery Voltage 1st PR Min output;-0.15f

#define KR_BATT_VOLT_PR_2ND_LOOP      0.015f                                                 ///< Battery Voltage 2nd PR Kr
#define MAX_BAT_VOLT_PR_2ND_LOOP      0.1f                                                   ///< Battery Voltage 2nd PR Max output;0.1f
#define MIN_BAT_VOLT_PR_2ND_LOOP      (-MAX_BAT_VOLT_PR_2ND_LOOP)                            ///< Battery Voltage 2nd PR Max output;-0.1f

#define KP_BATT_CURR_LOOP             0.002f                                                 ///< Battery Current Loop Kp;0.005f
#define KI_BATT_CURR_LOOP             0.00002f                                               ///< Battery Current Loop Ki;0.00002f
#define MAX_BATT_CURR_LOOP            1.0f                                                   ///< Battery Current Loop Max
#define MIN_BATT_CURR_LOOP            (-MAX_BATT_CURR_LOOP)                                  ///< Battery Current Loop Min

#define KR_BATT_CURR_PR_1ST_LOOP      0.05f                                                  ///< Battery Current 1st PR Kr
#define MAX_BATT_CURR_PR_1ST_LOOP     0.15f                                                  ///< Battery Current 1st PR Max outputx
#define MIN_BATT_CURR_PR_1ST_LOOP     (-MAX_BATT_CURR_PR_1ST_LOOP)                           ///< Battery Current 1st PR Min output

#define KR_BATT_CURR_PR_2ND_LOOP      0.05f                                                  ///< Battery Current 2nd PR Kr
#define MAX_BATT_CURR_PR_2ND_LOOP     0.1f                                                   ///< Battery Current 2nd PR Max output
#define MIN_BATT_CURR_PR_2ND_LOOP     (-MAX_BATT_CURR_PR_2ND_LOOP)                           ///< Battery Current 2nd PR Max output

#define KP_BATT_IMBAL_LOOP            0.0015f                                                ///< Battery Imbalance Loop Kp;0.005f
#define KI_BATT_IMBAL_LOOP            0.00001f                                               ///< Battery Imbalance Loop Ki;0.0001f
#define MAX_BATT_IMBAL_LOOP           0.1f                                                   ///< Battery Imbalance Loop Max
#define MIN_BATT_IMBAL_LOOP           (-MAX_BATT_IMBAL_LOOP)                                 ///< Battery Imbalance Loop Min

#define KP_D2D_BUS_VOLT_LOOP          1.0f                                                   ///< D2D Bus Voltage Loop Kp;1.5f
#define KI_D2D_BUS_VOLT_LOOP          0.0001f                                                ///< D2D Bus Voltage Loop Ki;0.001f
#define MAX_D2D_BUS_VOLT_LOOP_PARL    (CURR_BATT_PARL_MAX + 2.0f)                            ///< D2D Bus Voltage Loop Max in parallel mode
#define MIN_D2D_BUS_VOLT_LOOP_PARL    (-CURR_BATT_PARL_MAX/0.95f - 2.0f)                     ///< D2D Bus Voltage Loop Min in parallel mode
#define MAX_D2D_BUS_VOLT_LOOP_SERIES  (CURR_BATT_SERIES_MAX + 2.0f)                          ///< D2D Bus Voltage Loop Max in series mode
#define MIN_D2D_BUS_VOLT_LOOP_SERIES  (-CURR_BATT_SERIES_MAX/0.95f - 2.0f)                   ///< D2D Bus Voltage Loop Min in series mode
#elif 2U == GRID_PHASE_NUMBER
#define KP_BATT_VOLT_LOOP             0.002f                                                 ///< Battery Voltage Loop Kp;0.005f
#define KI_BATT_VOLT_LOOP             0.00005f                                               ///< Battery Voltage Loop Ki;0.00001f
#define MAX_BATT_VOLT_LOOP            1.0f                                                   ///< Battery Voltage Loop Max
#define MIN_BATT_VOLT_LOOP            (-MAX_BATT_VOLT_LOOP)                                  ///< Battery Voltage Loop Min

#define KR_BATT_VOLT_PR_1ST_LOOP      0.015f                                                 ///< Battery Voltage 1st PR Kr
#define MAX_BATT_VOLT_PR_1ST_LOOP     0.15f                                                  ///< Battery Voltage 1st PR Max output;0.15f
#define MIN_BATT_VOLT_PR_1ST_LOOP     (-MAX_BATT_VOLT_PR_1ST_LOOP)                           ///< Battery Voltage 1st PR Min output;-0.15f

#define KR_BATT_VOLT_PR_2ND_LOOP      0.015f                                                 ///< Battery Voltage 2nd PR Kr
#define MAX_BAT_VOLT_PR_2ND_LOOP      0.1f                                                   ///< Battery Voltage 2nd PR Max output;0.1f
#define MIN_BAT_VOLT_PR_2ND_LOOP      (-MAX_BAT_VOLT_PR_2ND_LOOP)                            ///< Battery Voltage 2nd PR Max output;-0.1f

#define KP_BATT_CURR_LOOP             0.002f                                                ///< Battery Current Loop Kp;0.01f
#define KI_BATT_CURR_LOOP             0.00005f                                                ///< Battery Current Loop Ki;0.00002f
#define MAX_BATT_CURR_LOOP            1.0f                                                   ///< Battery Current Loop Max
#define MIN_BATT_CURR_LOOP            (-MAX_BATT_CURR_LOOP)                                  ///< Battery Current Loop Min

#define KR_BATT_CURR_PR_1ST_LOOP      0.05f                                                  ///< Battery Current 1st PR Kr
#define MAX_BATT_CURR_PR_1ST_LOOP     0.15f                                                  ///< Battery Current 1st PR Max outputx
#define MIN_BATT_CURR_PR_1ST_LOOP     (-MAX_BATT_CURR_PR_1ST_LOOP)                           ///< Battery Current 1st PR Min output

#define KR_BATT_CURR_PR_2ND_LOOP      0.05f                                                  ///< Battery Current 2nd PR Kr
#define MAX_BATT_CURR_PR_2ND_LOOP     0.1f                                                   ///< Battery Current 2nd PR Max output
#define MIN_BATT_CURR_PR_2ND_LOOP     (-MAX_BATT_CURR_PR_2ND_LOOP)                           ///< Battery Current 2nd PR Max output

#define KP_BATT_IMBAL_LOOP            0.0005f                                                ///< Battery Imbalance Loop Kp;0.005f
#define KI_BATT_IMBAL_LOOP            0.000005f                                              ///< Battery Imbalance Loop Ki;0.0001f
#define MAX_BATT_IMBAL_LOOP           0.05f                                                  ///< Battery Imbalance Loop Max
#define MIN_BATT_IMBAL_LOOP           (-MAX_BATT_IMBAL_LOOP)                                 ///< Battery Imbalance Loop Min

#define KP_D2D_BUS_VOLT_LOOP          1.0f                                                   ///< D2D Bus Voltage Loop Kp;1.5f
#define KI_D2D_BUS_VOLT_LOOP          0.0001f                                                ///< D2D Bus Voltage Loop Ki;0.001f
#define MAX_D2D_BUS_VOLT_LOOP_PARL    (CURR_BATT_PARL_MAX + 4.0f)                            ///< D2D Bus Voltage Loop Max in parallel mode
#define MIN_D2D_BUS_VOLT_LOOP_PARL    (-CURR_BATT_PARL_MAX/0.95f - 4.0f)                     ///< D2D Bus Voltage Loop Min in parallel mode
#define MAX_D2D_BUS_VOLT_LOOP_SERIES  (CURR_BATT_SERIES_MAX + 4.0f)                          ///< D2D Bus Voltage Loop Max in series mode
#define MIN_D2D_BUS_VOLT_LOOP_SERIES  (-CURR_BATT_SERIES_MAX/0.95f - 4.0f)                   ///< D2D Bus Voltage Loop Min in series mode

#define KR_COMP_BATT_CURR_LOOP_REP    0.0003f                                                ///< D2D Battery Current Repeat Kr
#define QZ_BATT_CURR_LOOP_REP         0.91f                                                  ///< D2D Battery Current Repeat Qz
#define NR_COMP_BATT_CURR_LOOP_REP    11U                                                    ///< D2D Battery Current Repeat Nr
#define FRQ_LPF_BATT_CURR_LOOP_REP    300.0f                                                 ///< D2D Battery Current Repeat LPF Frq
#elif 3U == GRID_PHASE_NUMBER
#define KP_BATT_VOLT_LOOP             0.005f                                                 ///< Battery Voltage Loop Kp;0.005f
#define KI_BATT_VOLT_LOOP             0.0002f                                                ///< Battery Voltage Loop Ki;0.00001f
#define MAX_BATT_VOLT_LOOP            1.0f                                                   ///< Battery Voltage Loop Max
#define MIN_BATT_VOLT_LOOP            (-MAX_BATT_VOLT_LOOP)                                  ///< Battery Voltage Loop Min

#define KR_BATT_VOLT_PR_1ST_LOOP      0.015f                                                 ///< Battery Voltage 1st PR Kr
#define MAX_BATT_VOLT_PR_1ST_LOOP     0.15f                                                  ///< Battery Voltage 1st PR Max output;0.15f
#define MIN_BATT_VOLT_PR_1ST_LOOP     (-MAX_BATT_VOLT_PR_1ST_LOOP)                           ///< Battery Voltage 1st PR Min output;-0.15f

#define KR_BATT_VOLT_PR_2ND_LOOP      0.015f                                                 ///< Battery Voltage 2nd PR Kr
#define MAX_BAT_VOLT_PR_2ND_LOOP      0.1f                                                   ///< Battery Voltage 2nd PR Max output;0.1f
#define MIN_BAT_VOLT_PR_2ND_LOOP      (-MAX_BAT_VOLT_PR_2ND_LOOP)                            ///< Battery Voltage 2nd PR Max output;-0.1f

#define KP_BATT_CURR_LOOP             0.0075f                                                 ///< Battery Current Loop Kp;0.01f
#define KI_BATT_CURR_LOOP             0.00002f                                               ///< Battery Current Loop Ki;0.00002f
#define MAX_BATT_CURR_LOOP            1.0f                                                   ///< Battery Current Loop Max
#define MIN_BATT_CURR_LOOP            (-MAX_BATT_CURR_LOOP)                                  ///< Battery Current Loop Min

#define KR_BATT_CURR_PR_1ST_LOOP      0.05f                                                  ///< Battery Current 1st PR Kr
#define MAX_BATT_CURR_PR_1ST_LOOP     0.15f                                                  ///< Battery Current 1st PR Max outputx
#define MIN_BATT_CURR_PR_1ST_LOOP     (-MAX_BATT_CURR_PR_1ST_LOOP)                           ///< Battery Current 1st PR Min output

#define KR_BATT_CURR_PR_2ND_LOOP      0.05f                                                  ///< Battery Current 2nd PR Kr
#define MAX_BATT_CURR_PR_2ND_LOOP     0.1f                                                   ///< Battery Current 2nd PR Max output
#define MIN_BATT_CURR_PR_2ND_LOOP     (-MAX_BATT_CURR_PR_2ND_LOOP)                           ///< Battery Current 2nd PR Max output

#define KP_BATT_IMBAL_LOOP            0.0005f                                                ///< Battery Imbalance Loop Kp;0.005f
#define KI_BATT_IMBAL_LOOP            0.000005f                                              ///< Battery Imbalance Loop Ki;0.0001f
#define MAX_BATT_IMBAL_LOOP           0.05f                                                  ///< Battery Imbalance Loop Max
#define MIN_BATT_IMBAL_LOOP           (-MAX_BATT_IMBAL_LOOP)                                 ///< Battery Imbalance Loop Min

#define KP_D2D_BUS_VOLT_LOOP          1.0f                                                   ///< D2D Bus Voltage Loop Kp;1.5f
#define KI_D2D_BUS_VOLT_LOOP          0.0001f                                                ///< D2D Bus Voltage Loop Ki;0.001f
#define MAX_D2D_BUS_VOLT_LOOP_PARL    (CURR_BATT_PARL_MAX + 2.0f)                            ///< D2D Bus Voltage Loop Max in parallel mode
#define MIN_D2D_BUS_VOLT_LOOP_PARL    (-CURR_BATT_PARL_MAX/0.95f - 2.0f)                     ///< D2D Bus Voltage Loop Min in parallel mode
#define MAX_D2D_BUS_VOLT_LOOP_SERIES  (CURR_BATT_SERIES_MAX + 2.0f)                          ///< D2D Bus Voltage Loop Max in series mode
#define MIN_D2D_BUS_VOLT_LOOP_SERIES  (-CURR_BATT_SERIES_MAX/0.95f - 2.0f)                   ///< D2D Bus Voltage Loop Min in series mode
#endif

#if 2U == GRID_PHASE_NUMBER
/* SR Macro Definition*/
#define D2D_FRQ_RSN                   80.0f   ///< Enable over-resonance Loop Output kHZ
#define D2D_CURR_SR_ENA               6.0f    ///< Enable SR Curr 3.3A
#define D2D_CURR_SR_ENA2              6.0f    ///< Enable SR Curr 3.3A
#endif

#if 3U == GRID_PHASE_NUMBER
/* DAB Open Loop Macro Definition */
#define OUTP_DAB_OL_MIN               0.0f                  ///< Min DS1 in DAB
#define OUTP_DAB_OL_MAX               0.5f                  ///< Max DS1 in DAB
#define CURR_BATT_LIM_MIN             0.5f                  ///< Output Current Limit Min;0.3f
#endif

/****************************** Module Com Macro Definition ******************************/
/* Run Mode Macro Definition */
#define CHG_ONGRID_MODE          1U                     ///< Charging mode
#define BIDIR_ONGRID_MODE        2U                     ///< On-grid bidirection mode
#define OFFGRID_MODE             3U                     ///< Off-grid mode
#define OPENLOOP_MODE            4U                     ///< Open loop debug mode
#define PFC_CHG_D2D_OL_MODE      5U                     ///< PFC charge and D2D Openloop mode
#define PFC_OL_D2D_DISCH_MODE    6U                     ///< PFC Openloop and D2D Discharge mode
/* Run Command Macro */
#define STOP_CMD                 0U                     ///< Stop command
#define START_CMD                1U                     ///< Start command
/* Run Stage Macro */
#define PFC_EN_D2D_EN            0U                     ///< PFC enable & D2D enable
#define PFC_DIS_D2D_EN           1U                     ///< PFC disable & D2D enable
#define PFC_EN_D2D_DIS           2U                     ///< PFC enable & D2D disable
/* ARM Status Macro Definition */
#define ARM_DC_RLY_STA           0x0001U
#define ARM_AC_RLY_STA           0x0002U
#define ARM_SYS_FLT_RESET        0x0004U
#define INS_DET_ST               0x0008U                ///< Insulation Detection State
#define V2L_AUXPOW_EN            0x0010U                ///< V2L 12V to 1000V Auxpower enbale
#define FRQ_PRT_REM_CMD          0x0020U                ///< Italy frequency protection remote command
#define MODE_FAN_RUN             0x0040U                ///< Fan run mode;0-Normal mode,1-Silent mode
#define MODE_ON_OFF_GRID         0x0080U                ///< On&off grid switch mode;0-Normal mode,1-Rapid mode
#define BACK_TO_BACK_AGING_ST    0x0100U                ///< Back-to-back aging state; 0-Off,1-On

#define OUT_RLY_IS_OFF                  (0U == (stCom.uiStArm & ARM_DC_RLY_STA))
#define OUT_RLY_IS_ON                   (0U != (stCom.uiStArm & ARM_DC_RLY_STA))
#define AC_RLY_IS_OFF                   (0U == (stCom.uiStArm & ARM_AC_RLY_STA))
#define AC_RLY_IS_ON                    (0U != (stCom.uiStArm & ARM_AC_RLY_STA))
#define SYS_FLT_RESET_IS_OFF            (0U == (stCom.uiStArm & ARM_SYS_FLT_RESET))
#define SYS_FLT_RESET_IS_ON             (0U != (stCom.uiStArm & ARM_SYS_FLT_RESET))
#define INS_DET_ST_IS_OFF               (0U == (stCom.uiStArm & INS_DET_ST))
#define INS_DET_ST_IS_ON                (0U != (stCom.uiStArm & INS_DET_ST))
#define V2L_AUXPOW_EN_IS_OFF            (0U == (stCom.uiStArm & V2L_AUXPOW_EN))
#define V2L_AUXPOW_EN_IS_ON             (0U != (stCom.uiStArm & V2L_AUXPOW_EN))
#define FRQ_PRT_REM_CMD_IS_BROAD        (0U == (stCom.uiStArm & FRQ_PRT_REM_CMD))    ///< Broad frequency protection
#define FRQ_PRT_REM_CMD_IS_NARROW       (0U != (stCom.uiStArm & FRQ_PRT_REM_CMD))    ///< Narrow frequency protection
#define FAN_RUN_MODE_IS_NORMAL          (0U == (stCom.uiStArm & MODE_FAN_RUN))
#define FAN_RUN_MODE_IS_SILENT          (0U != (stCom.uiStArm & MODE_FAN_RUN))
#define ON_OFF_GRID_IS_NORMAL           (0U == (stCom.uiStArm & MODE_ON_OFF_GRID))
#define ON_OFF_GRID_IS_RAPID            (0U != (stCom.uiStArm & MODE_ON_OFF_GRID))
#define BACK_TO_BACK_AGING_ST_IS_OFF    (0U == (stCom.uiStArm & BACK_TO_BACK_AGING_ST))
#define BACK_TO_BACK_AGING_ST_IS_ON     (0U != (stCom.uiStArm & BACK_TO_BACK_AGING_ST))

/***************************** Module ComIf Macro Definition *****************************/
/* On-grid mode macro definition */
#define PFC_PWR_GRID_STD_MODE    0x0U                   ///< PFC power grid standard mode
#define PFC_PWR_ARM_CTRL_MODE    0x1U                   ///< PFC power OCPP control mode

#define PFC_BAL_RUN_MODE         0x0U                   ///< PFC balance run mode
#define PFC_IMBAL_RUN_MODE       0x1U                   ///< PFC Imbalance run mode

#define PFC_ARM_CTRL_ACTV_POW_MODE        0x0U          ///< PFC active power ARM control mode
#define PFC_ARM_CTRL_ACTV_POW_FRQ_MODE    0x1U          ///< PFC active P/F ARM control mode

#define PFC_ARM_CTRL_REACTV_POW_MODE      0x0U          ///< PFC reactive power ARM control mode
#define PFC_ARM_CTRL_REACTV_QU_MODE       0x1U          ///< PFC reactive Q/U ARM control mode

#define PHASE_FULL_RUN_MODE      0x0U                   ///< Phase full run mode
#define PHASE_LOSS_RUN_MODE      0x1U                   ///< Phase loss run mode

#define PHASE_N_EXIST_MODE       0x0U                   ///< Exist Phase N mode
#define PHASE_N_NONE_MODE        0x1U                   ///< None Phase N mode

#define SINGLE_PHASE_BAL_MODE          0U               ///< Single phase balance mode
#define SINGLE_PHASE_IMBAL_MODE        1U               ///< Single phase imbalance mode
#define TWO_PHASE_BAL_MODE             2U               ///< Two phase balance mode
#define TWO_PHASE_IMBAL_MODE           3U               ///< Two phase imbalance mode
#define TWO_PHASE_SINGLE_RUN_MODE      4U               ///< Two phase single phase run  mode
#define THREE_PHASE_BAL_MODE           5U               ///< Three phase balance mode
#define THREE_PHASE_IMBAL_MODE         6U               ///< Three phase imbalance mode
#define THREE_PHASE_SINGLE_RUN_MODE    7U               ///< Three phase single phase run  mode
/* Grid connection method Macro Definition */
#define SINGLE_PHASE_AN          0x19U                  ///< 0001 1001
#define TWO_PHASE_AB             0x2CU                  ///< 0010 1100
#define TWO_PHASE_ABN            0x2CU                  ///< 0010 1100
#define TWO_PHASE_AN             0x29U                  ///< 0010 1001
#define TWO_PHASE_BN             0x25U                  ///< 0010 0101
#define THREE_PHASE_ABC          0x3EU                  ///< 0010 1110
#define THREE_PHASE_ABCN         0x3FU                  ///< 0010 1111
#define THREE_PHASE_AN           0x39U                  ///< 0010 1001
#define THREE_PHASE_BN           0x35U                  ///< 0010 0101
#define THREE_PHASE_CN           0x33U                  ///< 0010 0011

/************************** Module PowLim Macro Definition **************************/
/* Power Limit */
#if 1U == GRID_PHASE_NUMBER
#define VOLT_BUS_TGT_MIN             380.0f
#define VOLT_BUS_TGT_BATT_MAX        420.0f
#define VOLT_BUS_TGT_MAX             425.0f
#elif 2U == GRID_PHASE_NUMBER
#define VOLT_BUS_TGT_MIN             360.0f
#define VOLT_BUS_TGT_MAX             430.0f
#elif 3U == GRID_PHASE_NUMBER
#define VOLT_BUS_TGT_MIN             700.0f
#define VOLT_BUS_TGT_MAX             800.0f
#endif
#define COEFF_PFC_POW_RAT_1MS_STEP   (0.01f/60000.0f)   ///< PFC power ratio 1ms step coefficient
/* Power Limit High Temperature */
#define TEMP_DWN_POW_LIM_HT             60.0f           ///< Power Limit High Temperature Down
#if 1U == GRID_PHASE_NUMBER
#define TEMP_UP_POW_LIM_HT              64.0f           ///< Power Limit High Temperature Up
#define TEMP_DWN_COMP_SILENCE_POW_LIM1  -27.0f          ///< Power Limit Down Temperature compensation at silence mode
#if(BMW_CUSTUMER == CUSTUMER_ID)
#define TEMP_DWN_COMP_SILENCE_POW_LIM2  -23.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM3  -8.0f           ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_UP_COMP_SILENCE_POW_LIM    -2.0f           ///< Power Limit UP Temperature compensation at silence mode
#else
#define TEMP_DWN_COMP_SILENCE_POW_LIM2  -20.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM3  -4.0f           ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_UP_COMP_SILENCE_POW_LIM    -4.0f           ///< Power Limit UP Temperature compensation at silence mode
#endif
#elif 2U == GRID_PHASE_NUMBER
#define TEMP_UP_POW_LIM_HT              65.0f           ///< Power Limit High Temperature Up
#define TEMP_DWN_COMP_SILENCE_POW_LIM1  -27.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM2  -19.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM3  -2.0f           ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_UP_COMP_SILENCE_POW_LIM    -2.0f           ///< Power Limit UP Temperature compensation at silence mode
#elif 3U == GRID_PHASE_NUMBER
#define TEMP_UP_POW_LIM_HT              65.0f           ///< Power Limit High Temperature Up
#define TEMP_DWN_COMP_SILENCE_POW_LIM1  -32.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM2  -17.0f          ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_DWN_COMP_SILENCE_POW_LIM3  0.0f            ///< Power Limit Down Temperature compensation at silence mode
#define TEMP_UP_COMP_SILENCE_POW_LIM    0.0f            ///< Power Limit UP Temperature compensation at silence mode
#endif
#define TEMP_DWN_SILENCE_POW_LIM_HT1    (TEMP_DWN_POW_LIM_HT + TEMP_DWN_COMP_SILENCE_POW_LIM1)  ///< Power Limit Down Temperature Down in Silent Mode
#define TEMP_DWN_SILENCE_POW_LIM_HT2    (TEMP_DWN_POW_LIM_HT + TEMP_DWN_COMP_SILENCE_POW_LIM2)  ///< Power Limit Down Temperature Down in Silent Mode
#define TEMP_DWN_SILENCE_POW_LIM_HT3    (TEMP_DWN_POW_LIM_HT + TEMP_DWN_COMP_SILENCE_POW_LIM3)  ///< Power Limit Down Temperature Down in Silent Mode
#define TEMP_UP_SILENCE_POW_LIM_HT      (TEMP_UP_POW_LIM_HT + TEMP_UP_COMP_SILENCE_POW_LIM)     ///< Power Limit UP Temperature Down in Silent Mode

/* Power Limit Under Temperature */
#define TEMP_UNDER_PROTN               -40.0f                   ///< Under temperature protection
/*  Efficiency Macro Definition */
#define EFF_PL_CHRG                     0.95f                   ///< Charge power limit efficiency
#define EFF_RECPR_PL_CHRG               (1.0f / EFF_PL_CHRG)    ///< Charge power limit efficiency Reciprocal
#define EFF_PL_DCHA                     0.95f                   ///< Discharge power limit efficiency
#define EFF_RECPR_PL_DCHA               (1.0f / EFF_PL_DCHA)    ///< Discharge power limit efficiency Reciprocal


/************************** Module PerphCtrl Macro Definition **************************/
/* AC relay Macro Definition */
#define PFC_TEST_OFF             0U
#define PFC_TEST_RLY             1U
#define PFC_TEST_BUS             2U
#define PFC_TEST_FAN             3U

#define LEVEL_MOD_AC_RLY         0U                     ///< AC precharge relay level mode
#define PWM_MOD_AC_RLY           1U                     ///< AC precharge relay PWM mode
#define DUTY_AC_RLY_PWM          0.73f                  ///< AC precharge relay PWM duty
#define FRQ_AC_RLY_PWM           24000U                 ///< AC precharge relay PWM frequency
#define PRD_AC_RLY_PWM           ((Uint16)(FRQ_PWMCLK / 2U / FRQ_AC_RLY_PWM))
/* Series Parallel Relay Macro Definition */
#define SP_RLY_PARL_ST           0U                     ///< D2D relay Parallel State
#define SP_RLY_SERIES_ST         1U                     ///< D2D relay Series State
#define SP_RLY_NC_ST             2U                     ///< SP relay NC State
/* I2C Macro Definition */
#if 0U == FLG_SWUT_EN
#define I2CX_REG       I2caRegs
#else
#define I2CX_REG       I2caRegsUnitTest
#endif
/* D2D bleeder Macro Definition */
#define BLD_ST_MAC_STB           1U                                        ///< Bleeder resister state machine Standby state
#define BLD_ST_MAC_EN            2U                                        ///< Bleeder resister state machine Enable state
#define BLD_ST_MAC_V2L           3U                                        ///< Bleeder resister state machine V2L state

/* GPIO Macro Definition */
#if 1U == GRID_PHASE_NUMBER
#ifndef _SIMULATION_NO_DSP_
#define SP_RLY_SER_ON            GpioDataRegs.GPBSET.bit.GPIO61   = 1U     ///< Turn on Output Series Relay
#define SP_RLY_SER_OFF           GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1U     ///< Turn off Output Series Relay
#define SP_RLY_PARA_ON           GpioDataRegs.GPBSET.bit.GPIO60   = 1U     ///< Turn on Output Parallel Relay
#define SP_RLY_PARA_OFF          GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1U     ///< Turn off Output Parallel Relay
#else
#define SP_RLY_SER_ON                                                      ///< Turn on Output Series Relay
#define SP_RLY_SER_OFF                                                     ///< Turn off Output Series Relay
#define SP_RLY_PARA_ON                                                     ///< Turn on Output Parallel Relay
#define SP_RLY_PARA_OFF                                                    ///< Turn off Output Parallel Relay
#endif

#define D2D_BLEED_RES_EN         1U                                        ///< 1U-Out Bleed Resistor Enabled
#if 1U == D2D_BLEED_RES_EN
#define D2D_BLEED_RES_ON         GpioDataRegs.GPBSET.bit.GPIO59   = 1U     ///< Turn on Output Bleed Resistor
#define D2D_BLEED_RES_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1U     ///< Turn off Output Bleed Resistor
#else
#define D2D_BLEED_RES_ON                                                   ///< Turn on Output Bleed Resistor
#define D2D_BLEED_RES_OFF                                                  ///< Turn off Output Bleed Resistor
#endif
/* LED Macro Definition */
#define DSP_RUN_LED_ON           GpioDataRegs.GPBSET.bit.GPIO49    = 1U    ///< Turn on DSP Run Mode LED
#define DSP_RUN_LED_OFF          GpioDataRegs.GPBCLEAR.bit.GPIO49  = 1U    ///< Turn off DSP Run Mode LED
#define DSP_RUN_LED_TOGGLE       GpioDataRegs.GPBTOGGLE.bit.GPIO49 = 1U    ///< Toggle DSP Run Mode LED
#define PFC_RUN_MODE_LED_ON      GpioDataRegs.GPBSET.bit.GPIO50    = 1U    ///< Turn on PFC Run Mode LED
#define PFC_RUN_MODE_LED_OFF     GpioDataRegs.GPBCLEAR.bit.GPIO50  = 1U    ///< Turn off PFC Run Mode LED
#define PFC_RUN_MODE_LED_TOGGLE  GpioDataRegs.GPBTOGGLE.bit.GPIO50 = 1U    ///< Toggle PFC Run Mode LED
#define PFC_RUN_STS_LED_ON       GpioDataRegs.GPBSET.bit.GPIO51    = 1U    ///< Turn on PFC Run Status LED
#define PFC_RUN_STS_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO51  = 1U    ///< Turn off PFC Run Status LED
#define PFC_RUN_STS_LED_TOGGLE   GpioDataRegs.GPBTOGGLE.bit.GPIO51 = 1U    ///< Toggle PFC Run Status LED
#define D2D_RUN_MODE_LED_ON      GpioDataRegs.GPBSET.bit.GPIO52    = 1U    ///< Turn on D2D Run Mode LED
#define D2D_RUN_MODE_LED_OFF     GpioDataRegs.GPBCLEAR.bit.GPIO52  = 1U    ///< Turn off D2D Run Mode LED
#define D2D_RUN_MODE_LED_TOGGLE  GpioDataRegs.GPBTOGGLE.bit.GPIO52 = 1U    ///< Toggle D2D Run Mode LED
#define D2D_RUN_STS_LED_ON       GpioDataRegs.GPBSET.bit.GPIO53    = 1U    ///< Turn on D2D Run Status LED
#define D2D_RUN_STS_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO53  = 1U    ///< Turn off D2D Run Status LED
#define D2D_RUN_STS_LED_TOGGLE   GpioDataRegs.GPBTOGGLE.bit.GPIO53 = 1U    ///< Toggle D2D Run Status LED
/* I2C GPIO Macro Definition */
#define IIC_WRITE_ENABLE         GpioDataRegs.GPCCLEAR.bit.GPIO81  = 1U
#define IIC_READ_ONLY            GpioDataRegs.GPCSET.bit.GPIO81    = 1U
/* V2L Macro Definition */
#define V2L_AUX_POW_ON           GpioDataRegs.GPASET.bit.GPIO19    = 1U    ///< Turn on V2L AUX power
#define V2L_AUX_POW_OFF          GpioDataRegs.GPACLEAR.bit.GPIO19  = 1U    ///< Turn off V2L AUX power
#elif 2U == GRID_PHASE_NUMBER
#ifndef _SIMULATION_NO_DSP_
#define SP_RLY_SER_ON            GpioDataRegs.GPCSET.bit.GPIO64 = 1U       ///< Turn on Output Series Relay
#define SP_RLY_SER_OFF           GpioDataRegs.GPCCLEAR.bit.GPIO64 = 1U     ///< Turn off Output Series Relay
#define SP_RLY_PARA_ON           GpioDataRegs.GPBSET.bit.GPIO63 = 1U       ///< Turn on Output Parallel Relay
#define SP_RLY_PARA_OFF          GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1U     ///< Turn off Output Parallel Relay
#else
#define SP_RLY_SER_ON            stD2dCpuParam.stSPRelay.uiSimSerOn = 1U   ///< Turn on Output Series Relay
#define SP_RLY_SER_OFF           stD2dCpuParam.stSPRelay.uiSimSerOn = 0U   ///< Turn off Output Series Relay
#define SP_RLY_PARA_ON           stD2dCpuParam.stSPRelay.uiSimParaOn = 1U  ///< Turn on Output Parallel Relay
#define SP_RLY_PARA_OFF          stD2dCpuParam.stSPRelay.uiSimParaOn = 0U  ///< Turn off Output Parallel Relay
#endif
#define D2D_BLEED_RES_EN         1U                                        ///< 1U-Out Bleed Resistor Enabled
#if 1U == D2D_BLEED_RES_EN
#define D2D_BLEED_RES_ON         GpioDataRegs.GPCSET.bit.GPIO65 = 1U       ///< Turn on Output Bleed Resistor
#define D2D_BLEED_RES_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO65 = 1U     ///< Turn off Output Bleed Resistor
#else
#define D2D_BLEED_RES_ON                                                   ///< Turn on Output Bleed Resistor
#define D2D_BLEED_RES_OFF                                                  ///< Turn off Output Bleed Resistor
#endif
/* LED Macro Definition */
#define D2D_UPGRADE_LED_ON       GpioDataRegs.GPBSET.bit.GPIO33 = 1U       ///< Turn on  Program Upgrade LED
#define D2D_UPGRADE_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1U     ///< Turn off Program Upgrade LED
#define D2D_RUN_STS_LED_ON       GpioDataRegs.GPBSET.bit.GPIO48 = 1U       ///< Turn on D2D Run Status LED
#define D2D_RUN_STS_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1U     ///< Turn off D2D Run Status LED
#define D2D_RUN_STS_LED_TOGGLE   GpioDataRegs.GPBTOGGLE.bit.GPIO48 = 1U    ///< Toggle D2D Run Status LED
#define DSP_RUN_LED_ON           GpioDataRegs.GPBSET.bit.GPIO40 = 1U       ///< Turn on D2D Run Status LED
#define DSP_RUN_LED_OFF          GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1U     ///< Turn off D2D Run Status LED
#define PFC_RUN_STS_LED_ON       GpioDataRegs.GPBSET.bit.GPIO41    = 1U    ///< Turn on PFC Run Status LED
#define PFC_RUN_STS_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO41  = 1U    ///< Turn off PFC Run Status LED
#define PFC_RUN_STS_LED_TOG      GpioDataRegs.GPBTOGGLE.bit.GPIO41 = 1U    ///< Toggle PFC Run Status LED
#define PFC_RUN_MODE_LED_OFF
#define D2D_RUN_MODE_LED_OFF
/* V2L Macro Definition */
#define AUXPOWER12V_ON_B       GpioDataRegs.GPBSET.bit.GPIO50   = 1U       ///< Turn on 400 to 12V AUX power
#define AUXPOWER12V_OFF_B      GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1U
#define AUXPOWER12V_DAT_B      GpioDataRegs.GPBDAT.bit.GPIO50
#define AUXPOWER12V_ON         GpioDataRegs.GPCSET.bit.GPIO89   = 1U       ///< Turn on 400 to 12V AUX power
#define AUXPOWER12V_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO89 = 1U
#define AUXPOWER12V_DAT        GpioDataRegs.GPCDAT.bit.GPIO89
#define V2L_AUX_POW_ON         GpioDataRegs.GPBSET.bit.GPIO51   = 1U       ///< Turn on V2L AUX power
#define V2L_AUX_POW_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1U       ///< Turn off V2L AUX power
/* PFC Relay Macro Definition */
#define PFC_RELAY_A_ON         GpioDataRegs.GPBSET.bit.GPIO49   = 1U
#define PFC_RELAY_A_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1U
#define PFC_RELAY_B_ON         GpioDataRegs.GPBSET.bit.GPIO49   = 1U
#define PFC_RELAY_B_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1U
#define PFC_RELAY_C_ON         GpioDataRegs.GPBSET.bit.GPIO49   = 1U
#define PFC_RELAY_C_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1U
#define PFC_RELAY_N_ON         (0U)
#define PFC_RELAY_N_OFF        (0U)
#define PFC_RELAY_A_PWM        GpioDataRegs.GPBTOGGLE.bit.GPIO49 = 1U
/* I2C Macro Definition */
#define IIC_WRITE_ENABLE       GpioDataRegs.GPBCLEAR.bit.GPIO47    = 1U   
#define IIC_READ_ONLY          GpioDataRegs.GPBSET.bit.GPIO47      = 1U   
#elif 3U == GRID_PHASE_NUMBER
/* I2C Macro Definition */
#define IIC_WRITE_ENABLE       GpioDataRegs.GPACLEAR.bit.GPIO2    = 1U
#define IIC_READ_ONLY          GpioDataRegs.GPASET.bit.GPIO2    = 1U
//#define SP_RLY_SER_ON          GpioDataRegs.GPCSET.bit.GPIO81 = 1U        ///< Turn on Output Series Relay
//#define SP_RLY_SER_OFF         GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1U      ///< Turn off Output Series Relay
//#define SP_RLY_PARA_ON         GpioDataRegs.GPCSET.bit.GPIO80 = 1U        ///< Turn on Output Parallel Relay
//#define SP_RLY_PARA_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1U      ///< Turn off Output Parallel Relay
//#define D2D_BLEED_RES_ON       GpioDataRegs.GPCSET.bit.GPIO82 = 1U        ///< Turn on Output Bleed Resistor
//#define D2D_BLEED_RES_OFF      GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1U      ///< Turn off Output Bleed Resistor

#define DSP_RUN_LED_ON         GpioDataRegs.GPBSET.bit.GPIO63 = 1U        ///< Turn on DSP Run Status LED
#define DSP_RUN_LED_OFF        GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1U      ///< Turn off DSP Run Status LED
#define DSP_FAULT_LED_ON       GpioDataRegs.GPBSET.bit.GPIO62 = 1U        ///< Turn on DSP Fault Status LED
#define DSP_FAULT_LED_OFF      GpioDataRegs.GPBCLEAR.bit.GPIO62 = 1U      ///< Turn on DSP Fault Status LED
//#define PFC_RUN_STS_LED_ON     GpioDataRegs.GPCSET.bit.GPIO68 = 1U        ///< Turn on PFC Run Status LED
//#define PFC_RUN_STS_LED_OFF    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1U      ///< Turn off PFC Run Status LED
//#define PFC_RUN_STS_LED_TOG    GpioDataRegs.GPCTOGGLE.bit.GPIO68 = 1U     ///< Toggle PFC Run Status LED
//#define D2D_RUN_STS_LED_ON     GpioDataRegs.GPCSET.bit.GPIO69 = 1U        ///< Turn on D2D Run Status LED
//#define D2D_RUN_STS_LED_OFF    GpioDataRegs.GPCCLEAR.bit.GPIO69 = 1U      ///< Turn off D2D Run Status LED
//#define D2D_RUN_STS_LED_TOG    GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1U     ///< Toggle D2D Run Status LED

//#define V2L_AUX_POW_ON         GpioDataRegs.GPASET.bit.GPIO9 = 1U         ///< Turn on V2L AUX power
//#define V2L_AUX_POW_OFF        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1U       ///< Turn off V2L AUX power
//#define AUXPOWER12V_ON         GpioDataRegs.GPCSET.bit.GPIO86   = 1U
//#define AUXPOWER12V_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO86 = 1U

#define WATCHDAG_ON            GpioDataRegs.GPCSET.bit.GPIO91 = 1U
#define WATCHDAG_OFF           GpioDataRegs.GPCCLEAR.bit.GPIO91 = 1U

/* PFC Relay Macro Definition */
//#define PFC_RELAY_A_ON         GpioDataRegs.GPCSET.bit.GPIO77   = 1U
//#define PFC_RELAY_A_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1U
//#define PFC_RELAY_B_ON         GpioDataRegs.GPCSET.bit.GPIO76   = 1U
//#define PFC_RELAY_B_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1U
//#define PFC_RELAY_C_ON         GpioDataRegs.GPCSET.bit.GPIO74   = 1U
//#define PFC_RELAY_C_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1U
//#define PFC_RELAY_N_ON         GpioDataRegs.GPCSET.bit.GPIO75   = 1U
//#define PFC_RELAY_N_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1U
#define PFC_HW_FLT_RESET_EN    (GpioDataRegs.GPBSET.bit.GPIO41 = 1U)     ///< Hardware fault reset gpio signal enable
#define PFC_HW_FLT_RESET_DS    (GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1U)   ///< Hardware fault reset gpio signal disable
#endif
/*DSP to CPLD*/
#if(2U == GRID_PHASE_NUMBER)
#ifndef _SIMULATION_NO_DSP_
#define Charge_EN              GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1U     ///< charge
#define DisCharge_EN           GpioDataRegs.GPCSET.bit.GPIO82 = 1U       ///< discharge
#define SR_EN_OFF              GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1U     ///< SR_OFF
#define SR_EN_ON               GpioDataRegs.GPCSET.bit.GPIO81 = 1U       ///< SR_ON
#define SR2_EN_OFF             GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1U     ///< SR2_OFF
#define SR2_EN_ON              GpioDataRegs.GPCSET.bit.GPIO75 = 1U       ///< SR2_ON
#define Over_Resonance_OFF     GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1U     ///< over-resonance_OFF
#define Over_Resonance_ON      GpioDataRegs.GPCSET.bit.GPIO79 = 1U       ///< over-resonance_ON
#define CPLD_REBOOT_ON         GpioDataRegs.GPCSET.bit.GPIO77 = 1U       ///< Reboot after upgrade 
#define CPLD_REBOOT_OFF        GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1U     ///< Clear Reboot
#define CPLD_FCT_ON            GpioDataRegs.GPCSET.bit.GPIO76 = 1U       ///< CPLD enable FCT Mode
#define CPLD_FCT_OFF           GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1U     ///< CPLD disable FCT Mode
#else
#define Charge_EN              stDataClaToCpu.uiSimCharOn = 0U           ///< charge
#define DisCharge_EN           stDataClaToCpu.uiSimCharOn = 1U           ///< discharge
#define SR_EN_OFF              stDataClaToCpu.uiSimSROn = 0U             ///< SR_OFF
#define SR_EN_ON               stDataClaToCpu.uiSimSROn = 1U             ///< SR_ON
#define Over_Resonance_OFF     stDataClaToCpu.uiSimHFOn = 0U             ///< HF_Mode_OFF
#define Over_Resonance_ON      stDataClaToCpu.uiSimHFOn = 1U             ///< HF_Mode_ON
#endif
#endif
/********************************** SPI Macro Definition *********************************/
#if(2U != GRID_PHASE_NUMBER)
#define SPIX_REG                 SpiaRegs
#else
#define SPIX_REG                 SpiaRegs
#define SPIC_REG                 SpicRegs
#endif

/********************************** SCI Macro Definition *********************************/
#if 0
#define SCI_REG                 SciaRegs
#else
#define SCI_REG                 ScibRegs
#endif
/*************************** Module SPI drive Macro Definition ***************************/
#if(2U != GRID_PHASE_NUMBER)
/* Set the selection line low and select  */
#define SF_CS_LOW()              GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1U;
/* The selection line is set high and not selected */
#define SF_CS_HIGH()             GpioDataRegs.GPBSET.bit.GPIO57 = 1U;
#else
/* Set the selection line low and select  */
#define SF_CS_LOW()              GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1U;
/* The selection line is set high and not selected */
#define SF_CS_HIGH()             GpioDataRegs.GPBSET.bit.GPIO57 = 1U;
/* Set the selection line low and select  */
#define SF_CS_CPLD_LOW()         GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1U;
/* The selection line is set high and not selected */
#define SF_CS_CPLD_HIGH()        GpioDataRegs.GPCSET.bit.GPIO72 = 1U;
#endif

#define SIZE_TI_SYS_FLT_REC              8U                              ///< System time size
#define SIZE_POW_PRM_TYP_FLT_REC         14U                             ///< Power parameter size
#define SIZE_POW_PRM_NUM_FLT_REC         40U                             ///< Power parameter size
#define SIZE_TEMP_DATA_FLT_REC           9U                              ///< Temperature data size
#define SIZE_FAULT_WORD_FLT_REC          6U                              ///< Fault word size

/****************** Module CmnDiag & PfcDiag & D2dDiag Macro Definition ******************/
/* System Fault bit Macro */
#define FLT_SYS_OT               (0x0001U<<0)           ///< System over temperature fault
#define FLT_SYS_UT               (0x0001U<<1)           ///< System under temperature fault
#define FLT_SYS_EEPROM_INIT      (0x0001U<<2)           ///< System EEPROM initialize fault
#define FLT_SYS_CAN_COM          (0x0001U<<3)           ///< System CAN communication fault
#define FLT_SYS_SPI_COM          (0x0001U<<4)           ///< System SPI communication fault
#define FLT_SYS_AUX_12V          (0x0001U<<5)           ///< AUX 12V fault
#define FLT_SYS_AUX_1V5          (0x0001U<<6)           ///< AUX 1.5V fault
#define FLT_SYS_HW_VER           (0x0001U<<7)           ///< Hardware version fault
/* Fault state */
#define READYOK_PFC_FLT_LVL      0U                     ///< PFC ready OK fault level
#define ALARM_PFC_FLT_LVL        1U                     ///< PFC alarm fault level
#define PAUSE_PFC_FLT_LVL        2U                     ///< PFC pause fault level
#define MPUOFF_PFC_FLT_LVL       3U                     ///< PFC MPU off fault level
#define GPUOFF_PFC_FLT_LVL       4U                     ///< PFC GPU off fault level
#define STOP_PFC_FLT_LVL         5U                     ///< PFC stop fault level
#define EMERGSTOP_PFC_FLT_LVL    6U                     ///< PFC emergency stop fault level
#define FORBIDRUN_PFC_FLT_LVL    7U                     ///< PFC forbid run level

#define SYS_FLT_IS_SET           (0U != stComTbl.unWordSysFlt.all)                                                 ///<  System fault is set state
#define SYS_FLT_IS_CLR           (0U == stComTbl.unWordSysFlt.all)                                                 ///<  System fault is clear state
#define PFC_FLT_IS_SET           ((stPfcDiag.uiMaxFltLevel >= STOP_PFC_FLT_LVL) || (0U != stPfcDiag.unFlt.all))    ///< PFC fault is set state; stPfcDiag.uiMaxFltLevel
#define PFC_FLT_IS_CLR           ((stPfcDiag.uiMaxFltLevel < STOP_PFC_FLT_LVL) && (0U == stPfcDiag.unFlt.all))     ///< PFC fault is clear state; stPfcDiag.uiMaxFltLevel
#define D2D_FLT_IS_SET           ((0U != stD2dDiag.uiFltCpu) || (0U != stD2dDiag.uiFltCla))                        ///< D2D fault is set state
#define D2D_FLT_IS_CLR           ((0U == stD2dDiag.uiFltCpu) && (0U == stD2dDiag.uiFltCla))                        ///< D2D fault is clear state
/* D2D Protection Macro Definition */
#define PROTN_D2D_PARL_BATT_OV       (VOLT_BATT_PARL_MAX + 30.0f)    ///< D2D Parallel OV Protection
#define PROTN_D2D_SERIES_BATT_OV     (VOLT_BATT_MAX + 40.0f)         ///< D2D Series OV Protection
#define PROTN_D2D_PARL_BATT_UV       (VOLT_BATT_MIN - 10.0f)         ///< D2D Parallel UV Protection
#if 1U == GRID_PHASE_NUMBER
#define PROTN_D2D_PARL_BATT_OC       (CURR_BATT_PARL_MAX * 1.2f)     ///< D2D Parallel OC Protection, 30A
#define PROTN_D2D_SERIES_BATT_OC     (CURR_BATT_SERIES_MAX * 2.0f)  ///< D2D series OC Protection; 22.0f->25.0f
#define PROTN_D2D_BUS_OV             460.0f                          ///< D2D Bus OV Protection
#elif 2U == GRID_PHASE_NUMBER
#define PROTN_D2D_PARL_BATT_OC       (CURR_BATT_PARL_MAX * 1.21f)    ///< D2D Parallel OC Protection, 78A
#define PROTN_D2D_SERIES_BATT_OC     (CURR_BATT_SERIES_MAX * 1.24f)  ///< D2D series OC Protection, 40A
#define PROTN_D2D_BUS_OV             475.0f                          ///< D2D Bus OV Protection
#elif 3U == GRID_PHASE_NUMBER
#define PROTN_D2D_PARL_BATT_OC       (CURR_BATT_PARL_MAX * 1.35f)    ///< D2D Parallel OC Protection, no use
#define PROTN_D2D_SERIES_BATT_OC     (CURR_BATT_SERIES_MAX * 1.35f)  ///< D2D series OC Protection, 25A
#define PROTN_D2D_BUS_OV             890.0f                          ///< D2D Bus OV Protection
#endif
#define PROTN_D2D_BUS_UV             310.0f                          ///< D2D Bus UV Protection
#define PROTN_D2D_BATT_IMBAL_VOLT    30.0f                           ///< D2D Imbalance Voltage Protection
#define PROTN_D2D_BATT_IMBAL_CURR    5.0f                            ///< D2D Imbalance Current Protection
/* D2D CPU Fault bit Macro Definition */
#define FLT_CMPSS_D2D_BATT_OC        0x0001U                         ///< D2D Output OC CMPSS Fault
#define FLT_HW_D2D_SUM               0x0002U                         ///< D2D Sum Hardware Fault
#define FLT_HW_D2D_BATT_OV           0x0004U                         ///< D2D Output OV Hardware Fault
#define FLT_HW_D2D_BATT_DN_OV        0x0008U                         ///< D2D Output Down OV Hardware Fault
#define FLT_HW_D2D_BATT_OC_POS       0x0010U                         ///< D2D Positive Output OC Hardware Fault
#define FLT_HW_D2D_BATT_OC_NEG       0x0020U                         ///< D2D Negative Output OC Hardware Fault
#define FLT_HW_D2D_PRI_UP_OC         0x0040U                         ///< D2D Primary Up OC Hardware Fault
#define FLT_HW_D2D_PRI_DN_OC         0x0080U                         ///< D2D Primary Down OC Hardware Fault
#define FLT_HW_D2D_BUS_OV            0x0100U                         ///< D2D Bus OV Hardware Fault
#define FLT_D2D_BATT_UV              0x0200U                         ///< D2D Output UV Fault
#define FLT_D2D_BATT_SC              0x0400U                         ///< D2D Output Short Circuit Fault
#define FLT_D2D_BLD_RES              0x0800U                         ///< Bleed Resistor Fault
#define FLT_D2D_SP_RLY               0x1000U                         ///< D2D SP Relay Fault
#define FLT_D2D_BATT_IMBAL_CURR      0x2000U                         ///< D2D Output Imbalance Current Fault
#define FLT_D2D_BATT_IMBAL_VOLT      0x4000U                         ///< D2D Output Imbalance Voltage Fault
#define FLT_D2D_BUS_SLOW_UV          0x8000U                         ///< D2D Bus slow UV Fault
/* D2D CLA Fault bit Macro Definition */
#define FLT_D2D_BATT_UP_OC           0x0001U                         ///< D2D battery up OC fault
#define FLT_D2D_BATT_DN_OC           0x0002U                         ///< D2D battery down OC fault
#define FLT_D2D_BATT_UP_OV           0x0004U                         ///< D2D battery up OV fault
#define FLT_D2D_BATT_DN_OV           0x0008U                         ///< D2D battery down OV fault
#define FLT_D2D_BUS_OV               0x0010U                         ///< D2D Bus OV fault
#define FLT_D2D_BUS_UV               0x0020U                         ///< D2D Bus UV fault
#define FLT_D2D_BATT_OV              0x0040U                         ///< D2D battery OV fault

/*************************** Module PfcStMac Macro Definition ***************************/
#define PRE_CHRG_AMP_COEFF       (0.9f * 1.414214f)     ///< Pre-charge coefficient
/* PFC state machine Macro Definition */
#define PFC_ST_MAC_FLT           0U                     ///< PFC State Machine Fault State
#define PFC_ST_MAC_STB           1U                     ///< PFC State Machine Standby State
#define PFC_ST_MAC_CHK           2U                     ///< PFC State Machine Check State
#define PFC_ST_MAC_PWMEN         3U                     ///< PFC State Machine PWM_EN State
#define PFC_ST_MAC_NORMRUN       4U                     ///< PFC State Machine NormalRun State

/*************************** Module D2dStMac Macro Definition ***************************/
/* D2D state machine Macro Definition */
#define D2D_ST_MAC_FLT           0U                     ///< D2D State Machine Fault State
#define D2D_ST_MAC_STB           1U                     ///< D2D State Machine Standby State
#define D2D_ST_MAC_PWMENPRE      2U                     ///< D2D State Machine PWM_EN_PRE State
#define D2D_ST_MAC_PWMEN         3U                     ///< D2D State Machine PWM_EN State
#define D2D_ST_MAC_SOFTSTRT      4U                     ///< D2D State Machine Softstart State
#define D2D_ST_MAC_NORMRUN       5U                     ///< D2D State Machine NormalRun State

/************************* Module PfcGridCtrl Macro Definition *************************/
/* Active power control mode */
#define  ACTV_POW_RAT_SET_MODE   0U                     ///< Active power ratio set mode
#define  ACTV_POW_VAL_SET_MODE   1U                     ///< Active power value set mode
/* Reactive power control mode */
#define  REACTV_POW_DISABLE_MODE 0U                     ///< Reactive power disable mode
#define  REACTV_POW_PF_MODE      1U                     ///< Reactive power PF mode
#define  REACTV_POW_QU_MODE      2U                     ///< Reactive power QU mode
#define  REACTV_POW_QP_MODE      3U                     ///< Reactive power QP mode
#define  REACTV_POW_QT_MODE      4U                     ///< Reactive power QT mode
/* Anti-island Macro Definition */
#define AI_DSTBC_VG_ZERO_MODE    1U                     ///< 1U - Vg zero mode
/* Italy self test */
#define SELF_TEST_STS_INIT       0U                     ///< Self-test function state machine-Initial-status
#define SELF_TEST_STS_VOLT       1U                     ///< Self-test function state machine-Voltage test-status
#define SELF_TEST_STS_FRQ        2U                     ///< Self-test function state machine-Frequency test-status
#define SELF_TEST_STS_10MIN      3U                     ///< Self-test function state machine-10min voltage test-status
#define SELF_TEST_STS_END        4U                     ///< Self-test function state machine-end status
/* Grid Type Macro Definition */
#define TYPE_GRID_ABCN           0U
#define TYPE_GRID_ABC            1U
#define TYPE_GRID_AN             2U
#define TYPE_GRID_BN             3U
#define TYPE_GRID_CN             4U
#define TYPE_GRID_AB             5U
#define TYPE_GRID_ABN            6U

#if(3U == GRID_PHASE_NUMBER)
#ifndef _SIMULATION_NO_DSP_
#define AC_CURR_DC_EN            GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1U
#define AC_VOLT_DC_EN            GpioDataRegs.GPBSET.bit.GPIO36   = 1U
#else
#define AC_CURR_DC_EN
#define AC_VOLT_DC_EN
#endif
#else
#define AC_CURR_DC_EN        
#define AC_VOLT_DC_EN        
#endif

/************************* Module D2dPowPreCtrl Macro Definition *************************/
#if(3U == GRID_PHASE_NUMBER)
#define PERD_D2D_CLA             (1.0f/FRQ_D2D_CLA)
#define L_DAB_PRI_LEAK           0.000037f          ///< DAB Primary Inductor 35uH;0.000037f
#define DP3_D2D_DAB_MAX          0.998f             ///< Primary Mos3 PhaseShift Duty Up Limit
#endif

#ifndef _SIMULATION_NO_DSP_
#define CURR_BATT_STEP              0.1f                            ///< Output Current Reference Step;0.2f
#else
#define CURR_BATT_STEP              1.0f                            ///< Output Current Reference Step;0.2f
#endif
#define CURR_BATT_DWN_STEP          1.0f                            ///< Output Current Reference Step;1.0f

/**************************** Module ECapCfg Macro Definition ****************************/
/* CAP register */
#if(0U == FLG_SWUT_EN)
#define PFC_PHASE_A_FRQ_ECAP_REG     ECap1Regs          ///< PFC_PHASE_A_FRQ_ECAP_REG
#else
#define PFC_PHASE_A_FRQ_ECAP_REG     ECap1RegsUnitTest  ///< PFC_PHASE_A_FRQ_ECAP_REG
#endif

#if 1U == GRID_PHASE_NUMBER
#if(0U == FLG_SWUT_EN)
#define PFC_HW_NEG_OC_ECAP_REG       ECap2Regs          ///< PFC_HW_NEG_OC_ECAP_REG
#else
#define PFC_HW_NEG_OC_ECAP_REG       ECap2RegsUnitTest  ///< PFC_HW_NEG_OC_ECAP_REG
#endif
#elif 2U == GRID_PHASE_NUMBER
#if 0U == FLG_SWUT_EN
#define PFC_PHASE_B_FRQ_ECAP_REG    ECap2Regs           ///< PFC_PHASE_B_FRQ_ECAP_REG
#define PFC_BAL_PWM_ECAP_REG        ECap3Regs           ///< Balance PWM
#define D2D_UP_BURST_ECAP_REG       ECap4Regs           ///< Burst CBC ECAP Register
#define D2D_DN_BURST_ECAP_REG       ECap5Regs           ///< Burst CBC ECAP Register
#define PFC_HW_NEG_OV_ECAP_REG      ECap6Regs           ///< BUS hardware negative OV
#else
#define PFC_PHASE_B_FRQ_ECAP_REG    ECap2RegsUnitTest   ///< PFC_PHASE_B_FRQ_ECAP_REG
#define PFC_BAL_PWM_ECAP_REG        ECap3Regs           ///< Balance PWM
#define D2D_UP_BURST_ECAP_REG       ECap4Regs           ///< Burst CBC ECAP Register
#define D2D_DN_BURST_ECAP_REG       ECap5Regs           ///< Burst CBC ECAP Register
#define PFC_HW_NEG_OV_ECAP_REG      ECap6RegsUnitTest   ///< BUS hardware negative OV
#endif
#elif 3U == GRID_PHASE_NUMBER
#if 0U == FLG_SWUT_EN
#define PFC_PHASE_B_FRQ_ECAP_REG    ECap2Regs
#define PFC_PHASE_C_FRQ_ECAP_REG    ECap3Regs
#else
#define PFC_PHASE_B_FRQ_ECAP_REG    ECap2RegsUnitTest   ///< PFC_PHASE_B_FRQ_ECAP_REG
#define PFC_PHASE_C_FRQ_ECAP_REG    ECap3RegsUnitTest   ///< PFC_PHASE_C_FRQ_ECAP_REG
#endif
#endif
/**************************** Module GpioCfg Macro Definition ****************************/
/* GPIO register */
#if 1U == GRID_PHASE_NUMBER
#define PFC_GRID_HW_OC_POS       GpioDataRegs.GPADAT.bit.GPIO25
#define PFC_GRID_HW_OC_NEG       GpioDataRegs.GPADAT.bit.GPIO26
#define PFC_BUS_HW_OV            GpioDataRegs.GPADAT.bit.GPIO27
#elif 2U == GRID_PHASE_NUMBER
#define PFC_GRID_HW_OC           GpioDataRegs.GPCDAT.bit.GPIO94
#define PFC_BUS_HW_OV_POS        GpioDataRegs.GPCDAT.bit.GPIO93
#define PFC_BUS_HW_OV_NEG        GpioDataRegs.GPCDAT.bit.GPIO92
#elif 3U == GRID_PHASE_NUMBER
///<TBD
#endif

/**************************** Module AdcCfg Macro Definition ****************************/
/* ADC register */
#define ADCA_REG                 AdcaRegs
#define ADCB_REG                 AdcbRegs
#define ADCC_REG                 AdccRegs
#define ADCD_REG                 AdcdRegs

#if 1U == GRID_PHASE_NUMBER
#define DSP_CORE_TEMP_AD_RESULT  AdcaResultRegs.ADCRESULT2
#define BOARD_TEMP_AD_RESULT     AdcaResultRegs.ADCRESULT3
#define AUX_1V5_AD_RESULT        AdccResultRegs.ADCRESULT3
#define AUX_12V_AD_RESULT        AdccResultRegs.ADCRESULT2
///> PFC ADC result register
#define VG_AD_RESULT1            AdcbResultRegs.ADCRESULT2
#define VG_AD_RESULT2            AdcbResultRegs.ADCRESULT3
#define VG_AD_A_RESULT           ((VG_AD_RESULT1 + VG_AD_RESULT2)>>1U)

#define IG_AD_RESULT1            AdcbResultRegs.ADCRESULT0
#define IG_AD_RESULT2            AdcbResultRegs.ADCRESULT1
#define IG_AD_A_RESULT           ((IG_AD_RESULT1 + IG_AD_RESULT2)>>1U)

#define VBUS_AD_RESULT1          AdcaResultRegs.ADCRESULT0
#define VBUS_AD_RESULT2          AdcaResultRegs.ADCRESULT1
#define VBUS_AD_RESULT           ((VBUS_AD_RESULT1 + VBUS_AD_RESULT2)>>1U)

#define VG_DC_AD_A_RESULT        AdcbResultRegs.ADCRESULT4
#define IG_DC_AD_A_RESULT        AdcbResultRegs.ADCRESULT5
///> D2D ADC result register
#define BATT_CURR_AD_RESULT1       AdccResultRegs.ADCRESULT0
#define BATT_CURR_AD_RESULT2       AdccResultRegs.ADCRESULT1
#define BATT_CURR_AD_RESULT        ((BATT_CURR_AD_RESULT1 + BATT_CURR_AD_RESULT2)>>1U)
#define BATT_DWN_CURR_AD_RESULT    AdcdResultRegs.ADCRESULT2
#define BATT_VOLT_AD_RESULT1       AdcdResultRegs.ADCRESULT0
#define BATT_VOLT_AD_RESULT2       AdcdResultRegs.ADCRESULT1
#define BATT_VOLT_AD_RESULT        ((BATT_VOLT_AD_RESULT1 + BATT_VOLT_AD_RESULT2)>>1U)
#define BATT_DWN_VOLT_AD_RESULT    AdcdResultRegs.ADCRESULT3
#define BUS_VOLT_AD_RESULT         AdcaResultRegs.ADCRESULT0

#elif (2U == GRID_PHASE_NUMBER)
#define IG_AD_A_RESULT           AdcaResultRegs.ADCRESULT2      ///< A2
#define IG_AD_B_RESULT           AdcaResultRegs.ADCRESULT3      ///< A4
#define IG_AD_D_RESULT           AdccResultRegs.ADCRESULT2      ///< C3

#define IG_DC_AD_A_RESULT        AdcaResultRegs.ADCRESULT4      ///< A3
#define IG_DC_AD_B_RESULT        AdcaResultRegs.ADCRESULT5      ///< A5

#define VG_AD_A_RESULT           AdcbResultRegs.ADCRESULT0      ///< 14
#define VG_AD_B_RESULT           AdcbResultRegs.ADCRESULT1      ///< B1

#define VG_INV_AD_A_RESULT       AdcaResultRegs.ADCRESULT0      ///< A0
#define VG_INV_AD_B_RESULT       AdcaResultRegs.ADCRESULT1      ///< A1

#define VG_DC_AD_A_RESULT        AdccResultRegs.ADCRESULT3      ///< 15
#define VG_DC_AD_B_RESULT        AdcbResultRegs.ADCRESULT5      ///< B0

#define VBUSPOS_AD_RESULT        AdccResultRegs.ADCRESULT0      ///< C2
#define VBUSNEG_AD_RESULT        AdccResultRegs.ADCRESULT1      ///< C4
#define DSP_CORE_TEMP_AD_RESULT  AdcaResultRegs.ADCRESULT6      ///< 13
#define BOARD_TEMP_AD_RESULT     AdcdResultRegs.ADCRESULT3      ///< D2

#define AUX_1V5_AD_RESULT        AdcdResultRegs.ADCRESULT4      ///< D3
#define AUX_12V_AD_RESULT        AdcdResultRegs.ADCRESULT5      ///< D2
///> D2D ADC result register
#define BATT_CURR_AD_RESULT1       AdcbResultRegs.ADCRESULT2
#define BATT_CURR_AD_RESULT2       AdcbResultRegs.ADCRESULT3
#define BATT_CURR_AD_RESULT        ((BATT_CURR_AD_RESULT1 + BATT_CURR_AD_RESULT2)>>1U)
#define BATT_DWN_CURR_AD_RESULT    AdcbResultRegs.ADCRESULT4
#define BATT_VOLT_AD_RESULT1       AdcdResultRegs.ADCRESULT0
#define BATT_VOLT_AD_RESULT2       AdcdResultRegs.ADCRESULT1
#define BATT_VOLT_AD_RESULT        ((BATT_VOLT_AD_RESULT1 + BATT_VOLT_AD_RESULT2)>>1U)
#define BATT_DWN_VOLT_AD_RESULT    AdcdResultRegs.ADCRESULT2

#define BUS_POS_VOLT_AD_RESULT         AdccResultRegs.ADCRESULT0
#define BUS_NEG_VOLT_AD_RESULT         AdccResultRegs.ADCRESULT1
#else
/* PFC power control Macro Definition */
#define IG_AD_A_RESULT           AdcbResultRegs.ADCRESULT0      ///< B2
#define IG_AD_B_RESULT           AdcbResultRegs.ADCRESULT1      ///< B1
#define IG_AD_C_RESULT           AdcbResultRegs.ADCRESULT2      ///< B0
#define IG_AD_D_RESULT           0                              ///< Nothing

#define VG_AD_AB_RESULT          AdcaResultRegs.ADCRESULT1      ///< A4 1
#define VG_AD_BC_RESULT          AdcaResultRegs.ADCRESULT2      ///< A3 2
#define VG_AD_CA_RESULT          AdcaResultRegs.ADCRESULT0      ///< A5 0

#define VBUS_AD_RESULT           0                              ///< Nothing
#define VBUSPOS_AD_RESULT        0                              ///< Nothing

#define IG_DC_AD_A_RESULT        AdcdResultRegs.ADCRESULT0      ///< D15
#define VG_DC_AD_A_RESULT        AdcdResultRegs.ADCRESULT0      ///< D15

#define IG_DC_AD_B_RESULT        AdcdResultRegs.ADCRESULT1      ///< D14
#define VG_DC_AD_B_RESULT        AdcdResultRegs.ADCRESULT1      ///< D14

#define IG_DC_AD_C_RESULT        AdcaResultRegs.ADCRESULT3      ///< A2
#define VG_DC_AD_C_RESULT        AdcaResultRegs.ADCRESULT3      ///< A2

#define TEMP_PT1_AD_RESULT       AdcdResultRegs.ADCRESULT2      ///< D0
#define TEMP_PT2_AD_RESULT       AdcdResultRegs.ADCRESULT3      ///< D1

#define AD_MUX_SAMPLE                 AdcdResultRegs.ADCRESULT4 ///< D4
#define BOARD_TEMP_AD_RESULT          AD_MUX_SAMPLE
#define AUX_1V5_AD_RESULT             AdccResultRegs.ADCRESULT0 ///< C2
#define AUX_12V_AD_RESULT             AD_MUX_SAMPLE
#define DSP_CORE_TEMP_AD_RESULT       AdcaResultRegs.ADCRESULT6 ///< A6

#define  COEFF_AD_VBUS     0.370798204f
#define  COEFF_AD_VBUSPOS  0.370798204f
#define  COEFF_AD_VBUSNEG  0.370798204f
#define  COEFF_AD_VBUS_RECPR  (1/COEFF_AD_VBUS)
//#define INNER_TEMP_AD AdcaResultRegs.ADCRESULT6//13
#endif

/* DAC register */
#if(0U == FLG_SWUT_EN)
#define DACA_REG                 DacaRegs
#else
#define DACA_REG                 DacaRegsUnitTest
#endif
#define DACB_REG                 DacbRegs
/* PFC AD Macro Definition */
#define AD_BIAS_BUS_VOLT         0                      ///< Vbus 0V Bias
#define AD_BIAS_GRID_VOLT        2048                   ///< Vg 0V Bias
#define AD_BIAS_GRID_CURR        2048                   ///< Ig 0A Bias
#define AD_BIAS_DC_VOLT          2048                   ///< Vg_DC 0V Bias
#define AD_BIAS_DC_CURR          2048                   ///< Ig_DC 0A Bias
#define AD_BIAS_AUX_12V          0                      ///< AUX 12V Bias
#define AD_BIAS_AUX_1V5          0                      ///< AUX 1.5V Bias
/** PFC AD bias adjusting Macro Definition */
#define AD_BIAS_ADJUST_OVER      0U                     ///< Adjust over
#define VG_BIAS_ADJUST_BIT       (1U<<0)                ///< Grid voltage bias adjust bit
#define IG_BIAS_ADJUST_BIT       (1U<<1)                ///< Grid current bias adjust bit
#define VG_BIAS_DC_ADJUST_BIT    (1U<<2)                ///< Grid dc voltage bias adjust bit
#define IG_BIAS_DC_ADJUST_BIT    (1U<<3)                ///< Grid dc current bias adjust bit
/* D2D ADC Macro Definition */
#define AD_BIAS_BATT_CURR        2048.0f                ///< Battery current 1.5V Bias
#if 1U == GRID_PHASE_NUMBER
#define COEFF_K_AD_BATT_VOLT     0.27344f               ///< Battery Voltage Sample coefficient K
#define COEFF_K_AD_BATT_CURR     0.02604f               ///< Battery Current Sample coefficient K
#define COEFF_B_AD_BATT_CURR     AD_BIAS_BATT_CURR      ///< Battery Current Sample coefficient B
#define COEFF_K_AD_BATT_VOLT_DWN 0.13672f               ///< Battery Voltage Down Sample coefficient K
#define COEFF_K_AD_BATT_CURR_DWN 0.01302f               ///< Battery Current Down Sample coefficient K
#define COEFF_B_AD_BATT_CURR_DWN AD_BIAS_BATT_CURR      ///< Battery Current Down Sample coefficient B
#define COEFF_K_AD_BUS_VOLT      0.1208f                ///< Battery Voltage Down Sample coefficient K
#define R_COMP_BATT_SIDE         0.02f                  ///< Battery side compensate resistance
#elif 2U == GRID_PHASE_NUMBER
#define COEFF_K_AD_BATT_VOLT     0.27396f               ///< Battery Voltage Sample coefficient K
#define COEFF_K_AD_BATT_CURR     0.039072f              ///< Battery Current Sample coefficient K
#define COEFF_B_AD_BATT_CURR     AD_BIAS_BATT_CURR      ///< Battery Current Sample coefficient B
#define COEFF_K_AD_BATT_VOLT_DWN 0.13698f               ///< Battery Voltage Down Sample coefficient K
#define COEFF_K_AD_BATT_CURR_DWN 0.019536f              ///< Battery Current Down Sample coefficient K
#define COEFF_B_AD_BATT_CURR_DWN AD_BIAS_BATT_CURR      ///< Battery Current Down Sample coefficient B
#define COEFF_K_AD_BUS_VOLT_POS  0.08894f               ///< Posetive Bus Voltage Sample coefficient K
#define COEFF_K_AD_BUS_VOLT_NEG  0.08901f               ///< Negative Bus Voltage Sample coefficient K
#define R_COMP_BATT_SIDE         0.02f                  ///< Battery side compensate resistance
#elif 3U == GRID_PHASE_NUMBER
///< Reserved
#endif

/*************************** Module CmpssCfg Macro Definition ***************************/
/* PFC CMPSS register */
#if 1U == GRID_PHASE_NUMBER
    #define CBC_CMPSS1_REG       Cmpss1Regs             ///< ADC and CMPSS use difference interface
    #define CBC_CMPSS4_REG       Cmpss4Regs             ///< ADC and CMPSS use same interface
    #define VBUS_CMPSS_REG       Cmpss2Regs             ///< PFC VBUS CMPSS Register

    #define IAC_CBC_CURR         70.0f                  ///< PFC CBC current
    #define IN_CBC_CURR          12.0f                  ///< In(balance bridge) CBC value
    #define IAC_CBC_COEFF_K      22.447f                ///< PFC current CBC coefficient
    #define IAC_CBC_COEFF_B      1862.0f
#elif 2U == GRID_PHASE_NUMBER
    #define CBC_CMPSS_REG        Cmpss1Regs
    #define IBCBC_CMPSS_REG      Cmpss2Regs
    #define IN_CMPSS_REG         Cmpss5Regs

    #define IAC_CBC_CURR         155.0f
    #define IN_CBC_CURR          15.0f
    #define IAC_CBC_COEFF_K      10.67111f              ///< PFC current CBC coefficient
    #define IAC_CBC_COEFF_B      1861.818f
    #define IN_CBC_COEFF_K       40.01667f              ///< Balance bridge current CBC coefficient
    #define IN_CBC_COEFF_B       1861.818f
    #define IN_CMPSS_POS         (Uint16)(IN_CBC_CURR*IN_CBC_COEFF_K+IN_CBC_COEFF_B)
    #define IN_CMPSS_NEG         (Uint16)(-IN_CBC_CURR*IN_CBC_COEFF_K+IN_CBC_COEFF_B)
#elif 3U == GRID_PHASE_NUMBER
    #define CBC_CMPSS_REG        ///< TBD
    #define VBUS_CMPSS_REG       ///< TBD

    #define IAC_CBC_COEFF_K      46.54f                 ///< PFC current CBC coefficient
    #define IAC_CBC_COEFF_B      823.0f
    #define IN_CBC_COEFF_K       29.0f                  ///< Balance bridge current CBC coefficient
    #define IN_CBC_COEFF_B       2048.0f
    #define IAC_CBC_CURR         46.0f                  ///< Iac CBC value
    #define IN_CBC_CURR          12.0f                  ///< In(balance bridge) CBC value
#endif
    #define IAC_CMPSS_POS        (Uint16)(IAC_CBC_CURR*IAC_CBC_COEFF_K+IAC_CBC_COEFF_B)
    #define IAC_CMPSS_NEG        (Uint16)(-IAC_CBC_CURR*IAC_CBC_COEFF_K+IAC_CBC_COEFF_B)

#define CMPSS_MAX_LIMIT          4046.0f
#define CMPSS_MIN_LIMIT          50.0f

/* D2D CMPSS Macro Definition */
#define IOUT_BIAS_CMPSS          1861.8f                                      ///< IOUT 1.5V Bias
#if 1U == GRID_PHASE_NUMBER
#define OUT_CURR_CMPSS_REG       Cmpss8Regs 
#define CMPSS_OUTPARA_CURR_POS   ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_PARL_MAX*1.72f*34.909f))       ///< Total Output Parallel Current Positive Protection;40A->43A
#define CMPSS_OUTPARA_CURR_NEG   ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_PARL_MAX*1.72f*34.909f))       ///< Total Output Parallel Current Negative Protection;-40A->-43A
#define CMPSS_OUTSER_CURR_POS    ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_SERIES_MAX*2.08f*34.909f))     ///< Total Output Series Current Positive Protection;24A->26A
#define CMPSS_OUTSER_CURR_NEG    ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_SERIES_MAX*2.08f*34.909f))     ///< Total Output Series Current Negative Protection;-24A->26A
#elif 2U == GRID_PHASE_NUMBER
#define OUT_CURR_CMPSS_REG       Cmpss3Regs
#define CMPSS_OUTPARA_CURR_POS   ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_PARL_MAX*1.197f*23.267f))      ///< Total Output Parallel Current Positive Protection;75A;
#define CMPSS_OUTPARA_CURR_NEG   ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_PARL_MAX*1.197f*23.267f))      ///< Total Output Parallel Current Negative Protection;-75A;
#define CMPSS_OUTSER_CURR_POS    ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_SERIES_MAX*1.306f*23.267f))    ///< Total Output Series Current Positive Protection;38A
#define CMPSS_OUTSER_CURR_NEG    ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_SERIES_MAX*1.306f*23.267f))    ///< Total Output Series Current Negative Protection;-38A
#elif 3U == GRID_PHASE_NUMBER
#define OUT_CURR_CMPSS_REG       Cmpss6Regs
#define CMPSS_OUTPARA_CURR_POS   ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_PARL_MAX*1.459f*27.927f))      ///< Total Output Parallel Current Positive Protection;54A;
#define CMPSS_OUTPARA_CURR_NEG   ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_PARL_MAX*1.459f*27.927f))      ///< Total Output Parallel Current Negative Protection;-54A;
#define CMPSS_OUTSER_CURR_POS    ((int16)(IOUT_BIAS_CMPSS+CURR_BATT_SERIES_MAX*2.0f*27.927f))    ///< Total Output Series Current Positive Protection;29A
#define CMPSS_OUTSER_CURR_NEG    ((int16)(IOUT_BIAS_CMPSS-CURR_BATT_SERIES_MAX*2.0f*27.927f))    ///< Total Output Series Current Negative Protection;-29A
#endif
/**************************** Module CanCfg Macro Definition ****************************/
/* CAN register Macro Definition */
#if(0U == FLG_SWUT_EN)
#define CANX_REGS                CanbRegs               ///< Use CanA Module
#else
#define CANX_REGS                CanRegsUnitTest        ///< Use CanA Module
#endif
/* CAN Macro Definition */
#define CAN_RX_BOX               15U                    ///< RX Mailbox
#define CAN_TX_BOX               1U                     ///< TX Mailbox
#define CAN_RX_ID                0x175A00FFUL           ///< Receiver ID
#define CAN_TX_ID                0x1770FF00UL           ///< Transmitter ID
#define MSG_DATA_LENGTH          8U                     ///< Data Length
#define CAN_MSG_OBJ_NO_FLAGS     (0x00000000UL)         ///< This indicates that a message object has no flags set

/**************************** Module I2cCfg Macro Definition ****************************/
#define MAX_DATABUFF_SIZE        32U                    ///< The max buff size for write or read Eeprom data
#define DATA_NUM_BUFF_SIZE       50U                    ///< The Data Group and Line Number Buffer Size;20
#define I2C_BUFF_SIZE            20U                    ///< I2C read and write buffer size
#define MASTER_DSP_DATA          1U                     ///< Data to Master DSP
#define SLAVE_DSP_DATA           2U                     ///< Data to Slave DSP
#define SAVE_TO_EEPROM           1U                     ///< Data need to be saved to EEPROM

#define I2C_NONE_PARAM          0x0U                    ///< None parameter
#define I2C_ALL_PARAM           0x1U                    ///< All Parameter
#define I2C_EXC_ADJ_PARAM       0x2U                    ///< Except Adjusting Parameter
#define I2C_ADJ_PARAM           0x3U                    ///< Adjusting Parameter
/* I2C Data read return flag */
#define I2C_RETURN_READ_FAIL        2U
#define I2C_RETURN_READ_SUCESS      1U
#define I2C_RETURN_READING          0U
/* I2C Data write return flag */
#define I2C_RETURN_WRITE_FAIL       2U
#define I2C_RETURN_WRITE_SUCESS     1U
#define I2C_RETURN_WRITTING         0U
/* EEPROM read return flag */
#define PARA_EEPROM_READ_FAIL       2U
#define PARA_EEPROM_READ_SUCESS     1U
#define PARA_EEPROM_READING         0U
/* EEPROM write return flag */
#define PARA_EEPROM_WRITE_FAIL      2U
#define PARA_EEPROM_WRITE_SUCESS    1U
#define PARA_EEPROM_WRITTING        0U

#define NUM_EEPROM_DATA_QUE_OPER    2U                  ///< EEPROM data queue operation number
/**************************** Module EMIF && DMA Macro Definition ****************************/
#define NUM_PHA_GRID                GRID_PHASE_NUMBER
#define NUM_PHA_POW_CELL            3U
#define NUM_EMIF_POW_CELL           (NUM_PHA_POW_CELL > 6 ? NUM_PHA_POW_CELL : 6)
#define NUM_SUM_POW_CELL            (NUM_PHA_GRID * NUM_PHA_POW_CELL)
#define NUM_EMIF_SUM_POW_CELL       (NUM_PHA_GRID * NUM_EMIF_POW_CELL)
#define FPGA_WR_WORD_NUM            (23 + NUM_EMIF_POW_CELL*6 + 1)                          ///< FPGA write word number
#define FPGA_RD_WORD_NUM            (NUM_EMIF_SUM_POW_CELL + 2U)      ///< FPGA read word number

#define DMA_FPGA_BURST_SIZE         32U                          ///< 32 16-bit words
#define DMA_FPGA_SRC_BURST_STEP     1                            ///< Add 1 to address
#define DMA_FPGA_DST_BURST_STEP     1                            ///< Add 1 to address

#if 0U
#define DMA_FPGA_TRANSFER_SIZE      1U                           ///< Transfer burst number
#define DMA_FPGA_SRC_TRANSFER_STEP  0
#define DMA_FPGA_DST_TRANSFER_STEP  0
#define ENA_DMA2_FPGA               1U
#else
#define DMA_FPGA_TRANSFER_SIZE      2U                           ///< Transfer burst number
#define DMA_FPGA_SRC_TRANSFER_STEP  DMA_FPGA_SRC_BURST_STEP
#define DMA_FPGA_DST_TRANSFER_STEP  1
#define ENA_DMA2_FPGA               0U
#endif

#define DMA_FPGA_WORD_NUM           (DMA_FPGA_TRANSFER_SIZE * DMA_FPGA_BURST_SIZE)    ///< FPGA EMIF bytes number

#define EMIF_FPGA_BASE_ADDR         0x300000UL                                  ///< FPGA CS3 base address
#define FPGA_WR_BASE_ADDR           (EMIF_FPGA_BASE_ADDR)                       ///< FPGA write base address
#define FPGA_DMA_RD_BASE_ADDR       (EMIF_FPGA_BASE_ADDR + DMA_FPGA_TRANSFER_SIZE * 0x0020)            ///< FPGA DMA read base address
//#define FPGA_DMA2_RD_BASE_ADDR      (FPGA_DMA_RD_BASE_ADDR + 0x0040UL)          ///< FPGA DMA read base address

#define FPGA_CELL_ADDR_DELTA        (FPGA_RD_WORD_NUM * DMA_FPGA_SRC_BURST_STEP)///< Cell delta address
#define FPGA_RD_CHB_FLT_BASE_ADDR   (FPGA_DMA_RD_BASE_ADDR + DMA_FPGA_WORD_NUM)
#define FPGA_RD_CHB_VOLT_BASE_ADDR  (FPGA_RD_CHB_FLT_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_DAB_CURR_BASE_ADDR  (FPGA_RD_CHB_VOLT_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_FPGA_VER_BASE_ADDR  (FPGA_RD_DAB_CURR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_DAB_FLT_BASE_ADDR   (FPGA_RD_FPGA_VER_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_RES_CURR_BASE_ADDR   (FPGA_RD_DAB_FLT_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_DAB_VOLT_BASE_ADDR   (FPGA_RD_RES_CURR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_TEMP1_BASE_ADDR   (FPGA_RD_DAB_VOLT_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_TEMP2_BASE_ADDR   (FPGA_RD_HV_TEMP1_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_LV_TEMP1_BASE_ADDR   (FPGA_RD_HV_TEMP2_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_LV_TEMP2_BASE_ADDR   (FPGA_RD_LV_TEMP1_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_FIBER_ERR_BASE_ADDR   (FPGA_RD_LV_TEMP2_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_UP_FERR_BASE_ADDR   (FPGA_RD_FIBER_ERR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_DOWN_FERR_BASE_ADDR   (FPGA_RD_HV_UP_FERR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_LV_FIBER_ERR_BASE_ADDR   (FPGA_RD_HV_DOWN_FERR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_FAN_STATE_BASE_ADDR   (FPGA_RD_LV_FIBER_ERR_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_TEMP3_BASE_ADDR   (FPGA_RD_FAN_STATE_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_TEMP4_BASE_ADDR   (FPGA_RD_HV_TEMP3_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_HV_TEMP5_BASE_ADDR   (FPGA_RD_HV_TEMP4_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_LV_TEMP3_BASE_ADDR   (FPGA_RD_HV_TEMP5_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_LV_TEMP4_BASE_ADDR   (FPGA_RD_LV_TEMP3_BASE_ADDR + FPGA_CELL_ADDR_DELTA)
#define FPGA_RD_MO_RF_VAL_BASE_ADDR   (FPGA_RD_LV_TEMP4_BASE_ADDR + FPGA_CELL_ADDR_DELTA)

#define FPGA_WR_DEBUG_ADDR          0x300400UL
#define FPGA_WR_HEAD                0xAAAAU                      ///< FPGA write head
#define FPGA_RD_HEAD                0x5555U                      ///< FPGA read head

#define DMA_FPGA_DST_ADDR           ((volatile Uint16 *)&stEmifDma1Raw)
#define DMA_FPGA_SRC_ADDR           ((volatile Uint16 *)FPGA_DMA_RD_BASE_ADDR)      ////< FPGA read base address

#define ADDR_POLL_RES                 0U
#define ADDR_POLL_CHB_VOLT_BAL_TH     1U
#define ADDR_POLL_CHB_FRQ             2U
#define ADDR_POLL_DAB_FRQ             3U
#define ADDR_POLL_DAB_SOFTSTART_RATE  4U
#define ADDR_POLL_DAB_SYNC_DUTY       5U
#define ADDR_POLL_DAB_DEAD_TIME       6U
#define ADDR_POLL_DAB_BURST_OFF_TIM   7U
#define ADDR_POLL_CHB_VOLT_BAL_TH_A   0x1001
#define ADDR_POLL_CHB_VOLT_BAL_TH_B   0x1002
#define ADDR_POLL_CHB_VOLT_BAL_TH_C   0x1003

#define START_DMA1_READ()           EALLOW; \
                                    DmaRegs.CH1.CONTROL.bit.PERINTFRC = 1U; \
                                    EDIS;
#define ENA_EMIF_DSP_WR             1U
#define ENA_EMIF_DSP_RD_CELL        1U
#define ENA_EMIF_DSP_DMA_RD         1U

#define DMA2_FPGA_DST_ADDR          ((volatile Uint16 *)&stEmifDma2)
#define DMA2_FPGA_SRC_ADDR          ((volatile Uint16 *)FPGA_DMA_RD_BASE_ADDR)      ////< FPGA read base address

#define START_DMA2_READ()           EALLOW; \
                                    DmaRegs.CH2.CONTROL.bit.PERINTFRC = 1U; \
                                    EDIS;

#define FPGA_D2D_MOD_POWER_OFF                         0x0U
#define FPGA_D2D_MOD_CMD_CLEAR_REDUNDANT_FAULT         0x1U
#define FPGA_D2D_MOD_DCHA_BURST                        0x2U
#define FPGA_D2D_MOD_QUASI_CHRG                        0x3U
#define FPGA_D2D_MOD_SYNC                              0x4U
#define FPGA_D2D_MOD_CMD_CLEAR_SYS_FAULT               0x5U
#define FPGA_D2D_MOD_CHRG                              0x6U
#define FPGA_D2D_MOD_CHRG_BURST                        0x7U
#define FPGA_D2D_MOD_QUASI_DCHA                        0x8U
#define FPGA_D2D_MOD_DCHA                              0x9U
#define FPGA_D2D_MOD_CELL_FPGA_UPDATE                  0xfU

#define FPGA_PFC_MOD_POWER_OFF                         0x0U
#define FPGA_PFC_MOD_CMD_CLEAR_REDUNDANT_FAULT         0x1U
#define FPGA_PFC_MOD_CHECK_SELF                        0x2U
#define FPGA_PFC_MOD_POWER_ON                          0x4U
#define FPGA_PFC_MOD_CMD_CLEAR_SYS_FAULT               0x5U
#define FPGA_PFC_MOD_CELL_FPGA_UPDATE                  0xfU

/**************************** Module PerdTsk Macro Definition ****************************/
/* CPU system register */
#if(0U == FLG_SWUT_EN)
#define CPUTIMER0_REG           CpuTimer0Regs
#else
#define CPUTIMER0_REG           CpuTimer0RegsUnitTest
#endif

#define PERD_CPUTIMER1          1000000UL               ///< 1s
#define PERD_CPUTIMER1_REG      (200UL*PERD_CPUTIMER1)
#define CNTR_CPUTIMER1_REG      CpuTimer1Regs.TIM.all

/*********************** User Function Macro Definition ***********************/
/* LPF */
#define FIRST_ORD_LPF(OUT_VAL, IN_VAL, LPF_COEFF)    (OUT_VAL) = (LPF_COEFF) * (OUT_VAL) + (1.0f - (LPF_COEFF)) * (IN_VAL);
#define SECOND_ORD_LPF(OUT_VAL, IN_VAL, ST_LPF_2ND) \
{ \
    (OUT_VAL) = (ST_LPF_2ND).ftOutpPre[0] * (ST_LPF_2ND).ftCoeff[0] + (ST_LPF_2ND).ftOutpPre[1] * (ST_LPF_2ND).ftCoeff[1] + (IN_VAL) * (ST_LPF_2ND).ftCoeff[2] + (ST_LPF_2ND).ftInpPre[0] * (ST_LPF_2ND).ftCoeff[3] + (ST_LPF_2ND).ftInpPre[1] * (ST_LPF_2ND).ftCoeff[4]; \
    (ST_LPF_2ND).ftOutpPre[1] = (ST_LPF_2ND).ftOutpPre[0]; \
    (ST_LPF_2ND).ftOutpPre[0] = (OUT_VAL); \
    (ST_LPF_2ND).ftInpPre[1] = (ST_LPF_2ND).ftInpPre[0]; \
    (ST_LPF_2ND).ftInpPre[0] = (IN_VAL); \
}

/* PI */
#define INC_PI_CTRL(stPI)    { \
    (stPI).ftOutp = (stPI).ftOutp + (stPI).ftInp * (stPI).ftKp + (stPI).ftInp * (stPI).ftKi \
            - (stPI).ftInpPre * (stPI).ftKp; \
    if((stPI).ftOutp > (stPI).ftOutpMax) \
    { \
        (stPI).ftOutp = (stPI).ftOutpMax; \
    } \
    else if((stPI).ftOutp < (stPI).ftOutpMin) \
    { \
        (stPI).ftOutp = (stPI).ftOutpMin; \
    } \
    else \
    { \
    } \
    (stPI).ftInpPre = (stPI).ftInp; \
}

#define POS_PI_CTRL(stPI)    { \
    (stPI).ftIntgl += (stPI).ftInp * (stPI).ftKi; \
    if((stPI).ftIntgl > (stPI).ftOutpMax) \
    { \
        (stPI).ftIntgl = (stPI).ftOutpMax; \
    } \
    else if((stPI).ftIntgl < (stPI).ftOutpMin) \
    { \
        (stPI).ftIntgl = (stPI).ftOutpMin; \
    } \
    else \
    { \
    } \
    (stPI).ftOutp = (stPI).ftInp * (stPI).ftKp + (stPI).ftIntgl; \
    if((stPI).ftOutp > (stPI).ftOutpMax) \
    { \
        (stPI).ftOutp = (stPI).ftOutpMax; \
    } \
    else if((stPI).ftOutp < (stPI).ftOutpMin) \
    { \
        (stPI).ftOutp = (stPI).ftOutpMin; \
    } \
    else \
    { \
    } \
}

#define INIT_PI_PRM(stPI)    { \
    (stPI).ftInp = 0.0f; \
    (stPI).ftIntgl = 0.0f; \
    (stPI).ftOutp = 0.0f; \
    (stPI).ftInpPre = 0.0f; \
}

#define POS_PI_MODE    0U    ///< Position PI
#define INC_PI_MODE    1U    ///< Increment PI
#define PI_MODE        POS_PI_MODE
#if POS_PI_MODE == PI_MODE
    #define PI_CTRL(stPI)    POS_PI_CTRL(stPI)
#else
    #define PI_CTRL(stPI)    INC_PI_CTRL(stPI)
#endif

/* PR */
#define PR_CTRL(stPR)    { \
    (stPR).ftOutp = (stPR).ftCoeff1 * (stPR).ftOutpPre[0] + (stPR).ftCoeff2 * (stPR).ftOutpPre[1] + \
                        (stPR).ftCoeff3 *(stPR).ftInp - (stPR).ftCoeff3 * (stPR).ftInpPre[1]; \
    if((stPR).ftOutp > (stPR).ftOutpMax) \
    { \
        (stPR).ftOutp = (stPR).ftOutpMax; \
    } \
    else if((stPR).ftOutp < (stPR).ftOutpMin) \
    { \
        (stPR).ftOutp = (stPR).ftOutpMin; \
    } \
    else \
    { \
    } \
    (stPR).ftOutpPre[1] = (stPR).ftOutpPre[0]; \
    (stPR).ftOutpPre[0] = (stPR).ftOutp; \
    (stPR).ftInpPre[1] = (stPR).ftInpPre[0]; \
    (stPR).ftInpPre[0] = (stPR).ftInp; \
}

#define INIT_PR_PRM(stPR)    { \
    (stPR).ftInp = 0.0f; \
    (stPR).ftInpPre[0] = 0.0f; \
    (stPR).ftInpPre[1] = 0.0f; \
    (stPR).ftOutp = 0.0f; \
    (stPR).ftOutpPre[0] = 0.0f; \
    (stPR).ftOutpPre[1] = 0.0f; \
}

/* Repeat control */
#define REPEAT_CTRL(stRepeat)    { \
    (stRepeat).uiPtrComp = ((stRepeat).uiPtr + (stRepeat).uiNrPhaComp) % (stRepeat).uiNrPerd; \
    (stRepeat).ftOutp = (stRepeat).ftQz * (stRepeat).ftOutpArr[(stRepeat).uiPtr] + (stRepeat).ftKrComp * (stRepeat).ftErrArr[(stRepeat).uiPtrComp]; \
    UP_DOWN_LIMIT((stRepeat).ftOutp, (stRepeat).ftOutpMax, (-(stRepeat).ftOutpMax)); \
    (stRepeat).ftErrArr[(stRepeat).uiPtr] = (stRepeat).ftInp; \
    (stRepeat).ftOutpArr[(stRepeat).uiPtr] = (stRepeat).ftOutp; \
    (stRepeat).uiPtr++; \
    if((stRepeat).uiPtr >= (stRepeat).uiNrPerd) \
    { \
        (stRepeat).uiPtr = 0U; \
    } \
}

/* Delay us */
#define CPU_CLK_RATE     5.00L   ///< for a 200MHz CPU clock speed (SYSCLKOUT)
#if 0U == FLG_SWUT_EN
#define DELAY_US_APP(A)  F28x_usDelay((long)(((((long double)(A)* 1000.0L) / CPU_CLK_RATE) - 9.0L) / 5.0L))
#else
#define DELAY_US_APP(A)
#endif

/* MAX and MIN */
#define MAX_TWO(A, B)          (((A)>(B))?(A):(B))
#define MIN_TWO(A, B)          (((A)<(B))?(A):(B))
#define MAX_THREE(A,B,C)       ((MAX_TWO((A),(B))>(C))?MAX_TWO((A),(B)):(C))
#define MIN_THREE(A,B,C)       ((MIN_TWO((A),(B))<(C))?MIN_TWO((A),(B)):(C))
#define MAX_FOUR(A,B,C,D)      ((MAX_THREE((A),(B),(C))>(D))?MAX_THREE((A),(B),(C)):(D))
#define MIN_FOUR(A,B,C,D)      ((MIN_THREE((A),(B),(C))<(D))?MIN_THREE((A),(B),(C)):(D))
#define MAX_FIVE(A,B,C,D,E)    ((MAX_FOUR((A),(B),(C),(D))>(E))?MAX_FOUR((A),(B),(C),(D)):(E))
#define MIN_FIVE(A,B,C,D,E)    ((MIN_FOUR((A),(B),(C),(D))<(E))?MIN_FOUR((A),(B),(C),(D)):(E))
/* Abs INT */
#define ABS_INT(A)    (((A)<0)?((Uint16)(-(A))):((Uint16)(A)))    ///< signed int Abs
/* Square */
#define SQUARE(A)       ((A)*(A))
/* Float parameter is Equal */
#define FLOAT_PRM_IS_EQUAL(A, B)        (fabsf((A)-(B)) < CON_ZERO_DELTA)
#define FLOAT_PRM_IS_NOT_EQUAL(A, B)    (fabsf((A)-(B)) >= CON_ZERO_DELTA)

/* Up and Dowm Limit */
#define UP_LIMIT(OUT_VAL, UP_VAL)      ((OUT_VAL) = MIN_TWO((OUT_VAL), (UP_VAL)))
#define DOWN_LIMIT(OUT_VAL, DN_VAL)    ((OUT_VAL) = MAX_TWO((OUT_VAL), (DN_VAL)))
#define UP_DOWN_LIMIT(OUT_VAL, UP_VAL, DN_VAL)    { \
    UP_LIMIT((OUT_VAL), (UP_VAL)); \
    DOWN_LIMIT((OUT_VAL), (DN_VAL)); \
}

/* Target ramp process */
#define RAMP_SAME_SLOPE(REF_VAL, TGT_VAL, STEP_VAL)  { \
    if((REF_VAL) - (TGT_VAL) > (STEP_VAL)) \
    { \
        (REF_VAL) -= (STEP_VAL); \
    } \
    else if((TGT_VAL) - (REF_VAL) > (STEP_VAL)) \
    { \
        (REF_VAL) += (STEP_VAL); \
    } \
    else \
    { \
        (REF_VAL) = (TGT_VAL); \
    } \
}

#define RAMP_DIFFERENT_SLOPE_UNBIDIR(REF_VAL, TGT_VAL, UP_STEP_VAL, DWN_STEP_VAL)  { \
    if((REF_VAL) - (TGT_VAL) > (DWN_STEP_VAL)) \
    { \
        (REF_VAL) -= (DWN_STEP_VAL); \
    } \
    else if((TGT_VAL) - (REF_VAL) > (UP_STEP_VAL)) \
    { \
        (REF_VAL) += (UP_STEP_VAL); \
    } \
    else \
    { \
        (REF_VAL) = (TGT_VAL); \
    } \
}

#define RAMP_DIFFERENT_SLOPE_BIDIR(REF_VAL, TGT_VAL, UP_STEP_VAL, DWN_STEP_VAL)  { \
    if((REF_VAL) > 0.0f) \
    { \
        RAMP_DIFFERENT_SLOPE_UNBIDIR((REF_VAL), (TGT_VAL), (UP_STEP_VAL), (DWN_STEP_VAL)) \
    } \
    else \
    { \
        RAMP_DIFFERENT_SLOPE_UNBIDIR((REF_VAL), (TGT_VAL), (DWN_STEP_VAL), (UP_STEP_VAL)) \
    } \
}

//=====================================================
//    Global Struct & Enum & Union Typedef
//=====================================================
/* CAN struct typedef */
typedef union
{
    Uint32 all;
    struct
    {
        Uint16 SRCADDR     :8;    ///< 7:0 Source Address
        Uint16 DSTADDR     :8;    ///< 15:8 Destination Address
        Uint16 DATACMD     :8;    ///< 23:16 Command Data
        Uint16 DATAID      :5;    ///< 28:24 Identifier
        Uint16 RSV         :3;    ///< 31:29 Reserve
    }bit;
}UN_CAN_MAIL_BOX_ID;

typedef struct
{
    UN_CAN_MAIL_BOX_ID unIDMaskRx;    ///< Receive ID mask

    Uint16 uiFlgRxOk;                 ///< Receive flag
    Uint16 uiFlgTxOk;                 ///< Send OK flag
    Uint16 uiByteRx[8];               ///< Can RX Byte
}ST_COM_DRV;

/* PI struct typedef */
typedef struct
{
    float32 ftKp;
    float32 ftKi;
    float32 ftInp;
    float32 ftInpPre;
    float32 ftIntgl;        ///< Integral
    float32 ftOutp;         ///< Output
    float32 ftOutpMax;      ///< Max output
    float32 ftOutpMin;      ///< Min output
}ST_PI_PRM;

/* 2-order LPF */
typedef struct
{
    float32 ftWc;
    float32 ftTs;
    float32 ftCoeff[5];       ///< Caluculating coefficient
    float32 ftInpPre[2];      ///< Previous input
    float32 ftOutpPre[2];     ///< Previous output
}ST_2ND_ORD_LPF_PRM;

/* Repeat struct typedef */
typedef struct
{
    Uint16  uiNrPerd;       ///< Period number
    Uint16  uiNrPhaComp;    ///< Phase compensation number
    Uint16  uiPtr;          ///< Pointer
    Uint16  uiPtrComp;      ///< Compensation pointer

    float32 ftInp;          ///< Input
    float32 ftOutp;         ///< Output
    float32 ftOutpLpf;      ///< LPF output
    float32 ftQz;           ///< Qz coefficient
    float32 ftKrComp;       ///< Compensation coefficient
    float32 ftOutpMax;      ///< MAX output
    float32 ftErrArr[MAX_REPEAT_NUM];
    float32 ftOutpArr[MAX_REPEAT_NUM];

    ST_2ND_ORD_LPF_PRM stLpf2ndOrd;     ///< 2nd order LPF
}ST_PFC_REPEAT_PRM;

/* SOGI struct typedef */
typedef struct
{
    float32 ftTs;           ///< Control period
    float32 ftWn;           ///< Characteristic radian frequency
    float32 ftK;            ///< Damping coefficient
    float32 ftCoeff1Bpf;    ///< BPF coefficient 1
    float32 ftCoeff2Bpf;    ///< BPF coefficient 2
    float32 ftCoeff3Bpf;    ///< BPF coefficient 3
    float32 ftCoeff1Lpf;    ///< LPF coefficient 1
    float32 ftInp;          ///< Input
    float32 ftBpf;          ///< BPF output
    float32 ftLpf;          ///< LPF output
    float32 ftInpPre[2];    ///< Previous input
    float32 ftBpfPre[2];    ///< BPF previous output
    float32 ftLpfPre[2];    ///< LPF previous output
}ST_SOGI_PRM;

/* PR struct typedef */
typedef struct
{
    float32 ftTs;           ///< Control period
    float32 ftWn;           ///< Center adian frequency
    float32 ftWc;           ///< Band-width radian frequency
    float32 ftKr;           ///< Resonance coefficient
    float32 ftCoeff1;       ///< PR coefficient 1
    float32 ftCoeff2;       ///< PR coefficient 2
    float32 ftCoeff3;       ///< PR coefficient 3
    float32 ftInp;          ///< Input
    float32 ftOutp;         ///< Output
    float32 ftInpPre[2];    ///< Previous input
    float32 ftOutpPre[2];   ///< Previous output
    float32 ftOutpMax;      ///< Max output
    float32 ftOutpMin;      ///< Min output
}ST_PR_PRM;

/* EEPROM data struct typedef */
typedef struct
{
    Uint16  uiRear;
    Uint16  uiFront;
    Uint16  uiDataLength;    ///< Length of data
    Uint16  *puiQueBuf;      ///< Address of data
    Uint16  QueMax;
}ST_EEP_DATA_QUE;

/* I2C parameter struct typedef */
typedef struct
{
    Uint16 uiStoredOK;
    Uint16 uiNonErasedOK;
    Uint16 uiStsWr;                             ///< I2C data command code; What do I do next with the I2C command
    Uint16 uiWrOK;
    Uint16 uiErrCnt;
    Uint16 uiAddrSecBas;
    Uint16 uiAddrThrdBas;
    Uint16 uiStsMsgBus;                         ///< I2C status bit: Indicates the current status of the I2C
    Uint16 uiAddrSlave;                         ///< I2C Slave address Settings
    Uint16 uiNumOfWords;                        ///< I2C word length of data to be written
    Uint16 uiNumWrByt;                          ///< I2C Indicates the byte length of the written data
    Uint16 uiNumMarkReadByt;                    ///< I2C Indicates the byte length of the read data
    Uint16 uiLimtWrNum;                         ///< I2C Number of write err counts
    Uint16 uiLimtReadNum;                       ///< I2C Number of read err counts
    Uint16 uiAddrMem;                           ///< I2C Start address of writing data to the data store
    Uint16 uiBufMsgRead[MAX_DATABUFF_SIZE];     ///< Write data buff
    Uint16 uiBufMsgWr[MAX_DATABUFF_SIZE];       ///< Read data buff
}ST_I2C_PRM;
typedef  ST_I2C_PRM* ST_I2C_handle;

typedef union
{
    Uint16 all;

    struct
    {
        /*00*/    Uint16 uiRlyA     :1;   ///< Pre-charge relay A command
        /*01*/    Uint16 uiRlyB     :1;   ///< Pre-charge relay B command
        /*02*/    Uint16 uiRlyC     :1;   ///< Pre-charge relay C command
        /*03*/    Uint16 uiRlyN     :1;   ///< Pre-charge relay N command
        /*04*/    Uint16 uiAuxRly   :1;   ///< Auxiliary power control command
        /*05~15*/ Uint16 uiResvd    :11;  ///< reserved
     }bit;
}UN_PFC_GPIO_CMD;

typedef struct
{
    float32  ftMax;           ///< Output upper limit
    float32  ftMin;           ///< Output lower limit
    float32  ftKr;            ///< Resonance coefficient
    float32  ftWc;            ///< Bandwidth frequency
    float32  ftWo;            ///< Resonant frequency
}PR_LCDSET;

typedef struct
{
    float32  ftA0;
    float32  ftA1;
    float32  ftA2;
    float32  ftB0;
    float32  ftB1;
    float32  ftB2;
}PR_COEFF;

typedef struct
{
    PR_LCDSET stLcdSet;
    PR_COEFF  stCoeff;
    PR_COEFF  stCoeffTmp;

    float32  ftInp[3];       ///<
    float32  ftOutp[3];      ///< Creates a buffer to store historical XX data
}PR;

typedef struct
{
    float32  ftQ;             ///< rotating q-axis stator variable
    float32  ftWo;            ///< 2*pi*frequency
}NOTCH_LCDSET;

typedef struct
{
    float32  ftWo_Ts;         ///< wo*Ts
    float32  ftM;             ///< (4+4*Q*wc*Ts+wo^2*Ts^2)
    float32  ftA;             ///< (4+wo^2*Ts^2)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    float32  ftB;             ///< (2*wo^2*Ts^2-8)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    float32  ftC;             ///< ((4-4*Q*wo*Ts+wo^2*Ts^2))/(4+4*Q*wo*Ts+wo^2*Ts^2)
}NOTCH_COEFF;

typedef struct
{
    NOTCH_LCDSET stLcdSet;
    NOTCH_COEFF  stCoeff;
    NOTCH_COEFF  stCoeffTmp;

    float32  ftInp;         ///< Output: stationary d-axis stator variable
    float32  ftInp_1;       ///< Output: Error(k-1)
    float32  ftInp_2;       ///< Output: Error(k-2)
    float32  ftOutp;        ///< output: Output(k)
    float32  ftOutp_1;      ///< output: Output(k-1)
    float32  ftOutp_2;      ///< output: Output(k-2)
}NOTCH;

typedef struct
{
    float32 ftK;
    float32 ftW;
}MPF_LCDSET;

typedef struct
{
    float32 ftMPFCof1;
    float32 ftMPFCof2;
    float32 ftMPFCof3;
    float32 ftLPFCof1;
}MPF_COEFF;

typedef struct
{
    MPF_LCDSET stLcdSet;
    MPF_COEFF  stCoeff;
    MPF_COEFF  stCoeffTmp;

    float32 ftInData[2];
    float32 ftMpfTemp[2];
    float32 ftLpfTemp[2];

    float32 ftMpf_In;
    float32 ftMpf_Out;
    float32 ftLpf_Out;
    float32 ftMode;
}MPF_TYPE;

typedef struct
{
    float32   ftOsg_k;
    float32   ftWn;            ///<  nominal angle frequency
}DSOGI_LCDSET;

typedef struct
{
    float32   ftOsg_x;
    float32   ftOsg_y;
    float32   ftOsg_b0;
    float32   ftOsg_b2;
    float32   ftOsg_a1;
    float32   ftOsg_a2;
    float32   ftOsg_qb0;
    float32   ftOsg_qb1;
    float32   ftOsg_qb2;
}DSOGI_COEFF;

typedef struct
{
    DSOGI_LCDSET stLcdSet;
    DSOGI_COEFF  stCoeff;
    DSOGI_COEFF  stCoeffTmp;

    float32   ftAlpha_u[3];   ///<  Ualpha Input
    float32   ftBeta_u[3];    ///<  beta Input

    float32   ftAlpha_osg_u[3];
    float32   ftAlpha_osg_qu[3];

    float32   ftBeta_osg_u[3];
    float32   ftBeta_osg_qu[3];

    float32   ftUalphap;    ///<  output Positive sequence alpha
    float32   ftUbetap;     ///<  Positive sequence beta
    float32   ftUalphan;    ///<  Negative sequence alpha
    float32   ftUbetan;     ///<  Negative sequence beta
}DSOGI_TYPE;

typedef struct
{
    float32   ftOsg_k;
    float32   ftWn;         ///<  nominal angle frequency
}SOGI_LCDSET;

typedef struct
{
    float32   ftOsg_x;
    float32   ftOsg_y;
    float32   ftOsg_b0;
    float32   ftOsg_b2;
    float32   ftOsg_a1;
    float32   ftOsg_a2;
    float32   ftOsg_qb0;
    float32   ftOsg_qb1;
    float32   ftOsg_qb2;
}SOGI_COEFF;

typedef struct
{
    SOGI_LCDSET stLcdSet;
    SOGI_COEFF  stCoeff;
    SOGI_COEFF  stCoeffTmp;

    float32   ftAlpha_u[3];   /**<   Ualpha Input*/
    float32   ftAlpha_osg_u[3];
    float32   ftAlpha_osg_qu[3];
}SOGI_TYPE;

typedef union
{
    Uint64 all;

    struct
    {
        Uint32 ulMillSec   : 10;    //< bit0~9: Millisecond
        Uint32 ulSec       : 6;     //< bit10~15: Second
        Uint32 ulMin       : 6;     //< bit16~21: Minute
        Uint32 ulHour      : 5;     //< bit22~26: Hour
        Uint32 ulRsvd0     : 5;     //< bit27~31: Reserved0
        Uint32 ulDate      : 6;     //< bit32~37: Date
        Uint32 ulMonth     : 4;     //< bit38~41: Month
        Uint32 ulYear      : 16;    //< bit42~57: Year
        Uint32 ulRsvd1     : 6;     //< bit58~63: Reserved1
    }bit;
}UN_SYS_TIME;

typedef struct 
{
    UN_SYS_TIME ullTime;                                                    ///< Time
    Uint16 uiPrmPow[SIZE_POW_PRM_TYP_FLT_REC][SIZE_POW_PRM_NUM_FLT_REC];    ///< Power parameter
    int16  siTemp[SIZE_TEMP_DATA_FLT_REC];                                  ///< Temperature
    Uint16 uiWordFlt[SIZE_FAULT_WORD_FLT_REC];                              ///< Fault word
}ST_FLT_DATA;

typedef struct
{
    Uint16 uiCpu2UpdByte[8];
}ST_C1_TO_C2_PRM;

typedef struct
{
    Uint16 uiCpu2UpdBack[8];
}ST_C2_TO_C1_PRM;

//=====================================================
//    Variable Declaration
//=====================================================
#if (1U == FLG_SWUT_EN)
/* ASPICE Test */
extern  struct EPWM_REGS EPwm12RegsUnitTest;
extern  struct EPWM_REGS EPwm5RegsUnitTest;
extern  struct CAN_REGS  CanRegsUnitTest;
extern  struct ECAP_REGS ECap1RegsUnitTest;
extern  struct ECAP_REGS ECap2RegsUnitTest;
extern  struct ECAP_REGS ECap3RegsUnitTest;
extern  struct ECAP_REGS ECap4RegsUnitTest;
extern  struct ECAP_REGS ECap5RegsUnitTest;
extern  struct ECAP_REGS ECap6RegsUnitTest;
extern  struct DAC_REGS  DacaRegsUnitTest;
extern  struct CPUTIMER_REGS  CpuTimer0RegsUnitTest;
extern  struct I2C_REGS I2caRegsUnitTest;
#endif

//=====================================================
//    Function Declaration
//=====================================================
extern void F28x_usDelay(long LoopCount);
extern void vFcn_1stOrdLPF(float32 *pftValOut, float32 ftValIn, float32 ftCoeffLpf);
extern void vFcn_FtUpDwnLim(float32 *pftValOut, float32 ftValUp, float32 ftValDwn);
extern void vFcn_UiUpDwnLim(Uint16 *puiValOut, Uint16 uiValUp, Uint16 uiValDwn);
extern void vFcn_RampSameSlope(float *pftValRef, float ftValTgt, float ftValStep);
extern void vFcn_UnbidirRampDiffSlope(float *pftValRef, float ftValTgt, float ftValUpStep, float ftValDwnStep);
extern void vFcn_BidirRampDiffSlope(float *pftValRef, float ftValTgt, float ftValUpStep, float ftValDwnStep);
extern void vFcn_InitPIPrm(ST_PI_PRM *pstPIPrm);
extern void vFcn_PosnPICtrl(ST_PI_PRM *pstPIPrm);
extern void vFcn_IncPICtrl(ST_PI_PRM *pstPIPrm);
extern float32 ftFcn_MaxOfTwo(float32 ftValA, float32 ftValB);
extern float32 ftFcn_MinOfTwo(float32 ftValA, float32 ftValB);
extern float32 ftFcn_MaxOfThree(float32 ftValA, float32 ftValB, float32 ftValC);
extern float32 ftFcn_MinOfThree(float32 ftValA, float32 ftValB, float32 ftValC);
extern float32 ftFcn_MaxOfFour(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD);
extern float32 ftFcn_MinOfFour(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD);
extern float32 ftFcn_MaxOfFive(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD, float32 ftValE);
extern float32 ftFcn_MinOfFive(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD, float32 ftValE);

#endif    /* APP_H_ */
//===========================================================================
// End of file.
//===========================================================================
