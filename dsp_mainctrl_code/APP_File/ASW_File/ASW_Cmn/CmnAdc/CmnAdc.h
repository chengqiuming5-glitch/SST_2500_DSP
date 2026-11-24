//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnAdc.h
 * @brief
 * The header file of common Adc is designed to realize common signals sample.
 *
 * Module      :                       \n
 * CmnAdc
 *
 * Module Task :                       \n
 * v_CmnAdc_Init()                     \n
 * v_CmnAdc_1ms()                      \n
 * v_CmnAdc_100ms()                    \n
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

#ifndef CMNADC_H_
#define CMNADC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CmnAdcExt.h"

#include "AdcDrvExt.h"
#include "ComExt.h"
#include "PerdTskExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#if(3U == GRID_PHASE_NUMBER)
#define COEFF_AUX_12V_AD              0.00805665f                                   ///< Aux 12V AD coefficient
#else
#define COEFF_AUX_12V_AD              ((70.4f*3.0)/(10.0f*4095.0f))                 ///< Aux 12V AD coefficient
#endif
#define COEFF_AUX_1V5_AD              (3.0/4095.0f)                                 ///< Aux 1V5 AD coefficient
#define AUX_12V_1000TIMES             12000                                         ///< 12V 1000 times
#define AUX_1V5_1000TIMES             1500                                          ///< 1.5V 1000 times

/* Temperature Macro Definition */
#define AIR_Temp_TBL_CNT              166U                                          ///< Air Temperature Table Counter
#define AIR_Temp_TBL_BIAS             -40                                           ///< Air Temperature Table Bias

#if(3U != GRID_PHASE_NUMBER)
#define A0_SW_ON
#define A0_SW_OFF
#define A1_SW_ON
#define A1_SW_OFF
#else
#define A0_SW_ON                      GpioDataRegs.GPBSET.bit.GPIO44 = 1
#define A0_SW_OFF                     GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1
#define A1_SW_ON                      GpioDataRegs.GPBSET.bit.GPIO55 = 1
#define A1_SW_OFF                     GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1
#endif

#define AD_SW_P1V5                    {A0_SW_OFF;A1_SW_OFF;}
#define AD_SW_TEMP                    {A0_SW_OFF;A1_SW_ON;}
#define AD_SW_P12V                    {A0_SW_ON;A1_SW_ON;}
#define AD_SW_RESVD                   {A0_SW_ON;A1_SW_OFF;}

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_CMN_ADC stPrmExt;               ///< Parameter to extern

    float32 ftADDspBdTemp;             ///< DSP board temperature AD result
    Uint16  uiFlgAdcChSel;             ///< ADC channel select flag
}ST_CMN_ADC_LOC;

//==============================================================================================
//    Variable Declaration
//==============================================================================================
static int16 siAirTempAdTbl[AIR_Temp_TBL_CNT];

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_CmnAdc_TempADLpf_1ms(void);
static void v_CmnAdc_Aux12V_1ms(void);
static void v_CmnAdc_Aux1V5_1ms(void);
static float32 ft_CmnAdc_TempTblLU(int16 siTempAD, int16 *sipTable, Uint16 uiTblCnt, int16 siTempBias);

//==============================================================================================
//    Global Function Declaration
//==============================================================================================
extern int16 GetTemperatureC(int16 sensorSample);

#endif /* CMNADC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================

