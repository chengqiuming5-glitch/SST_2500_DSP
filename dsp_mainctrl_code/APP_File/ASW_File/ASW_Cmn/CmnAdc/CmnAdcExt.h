//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnAdc.h
 * @brief
 * The external header file of common Adc is designed to realize common signals sample.
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

#ifndef CMNADCEXT_H_
#define CMNADCEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define CMN_ADC_DBG                   0U             ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    int16  siVal1000Times;     ///< Value 1000 times
    Uint16 uiErr1000Times;     ///< Error 1000 times
}ST_AUX_PARM;

typedef struct
{
    ST_AUX_PARM stAux12V;      ///< AUX 12V parameter
    ST_AUX_PARM stAux1V5;      ///< AUX 1.5V parameter

    float32 ftTempDspCore;     ///< DSP core temperature
    float32 ftTempDspBd;       ///< DSP board temperature
}ST_CMN_ADC;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_CMN_ADC stCmnAdc;

#if (1U == CMN_ADC_DBG)
extern ST_CMN_ADC stCmnAdcDbg;
#endif

#endif /* CMNADCEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
