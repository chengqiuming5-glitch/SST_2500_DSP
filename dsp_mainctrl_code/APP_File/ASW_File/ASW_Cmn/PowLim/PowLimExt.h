//==============================================================================================
//    File description
//==============================================================================================
/**@file         PowLimExt.h
 * @brief
 * The Header file of power limitation is designed to realize peripheral function.
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

#ifndef POWLIMEXT_H_
#define POWLIMEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define POW_LIM_DBG                              0U             ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16  uiFlgHTLim;                 ///< High temperature power limitation flag

	float32 ftVoltBattChrgLim;          ///< Charge battery voltage limitation
	float32 ftCurrBattChrgLim;          ///< Charge battery current limitation
	float32 ftVoltBusLim;               ///< Bus voltage limitation
    float32 ftVoltBusAcLim;             ///< Bus voltage AC voltage limitation
    float32 ftVoltBusBattLim;           ///< Bus voltage battery voltage limitation
    float32 ftPowAcChrgLim;             ///< Charge AC power limitation
    float32 ftPowAcDchaLim;             ///< Discharge AC power limitation
    float32 ftPowBattCurrChrgLim;       ///< Battery current charge power limitation
    float32 ftPowBattCurrDchaLim;       ///< Battery current discharge power limitation
	float32 ftCurrBattChrgMaxToBms;     ///< Max charge battery current to BMS
	float32 ftCurrBattDchaMaxToBms;     ///< Max charge battery current to BMS

	float32 ftPaAcLim;    				///< Phase A active power limitation
	float32 ftPbAcLim;    				///< Phase B active power limitation
	float32 ftPcAcLim;    				///< Phase C active power limitation
	float32 ftQaAcLim;    				///< Phase A reactive power limitation
	float32 ftQbAcLim;    				///< Phase B reactive power limitation
	float32 ftQcAcLim;    				///< Phase C reactive power limitation

	float32 ftVoltAcAmpLim;    			///< Phase voltage amplitude limitation
    float32 ftTempMax;         			///< Max temperature
    float32 ftTempMin;         			///< Min temperature
    float32 ftFanDuty;         			///< Fan duty
    float32 ftCoeffTemp;       			///< Temperature limitation coefficient in bi-direction mode
}ST_POW_LIM;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_POW_LIM stPowLim;

#if (1U == POW_LIM_DBG)
extern ST_POW_LIM stPowLimDbg;
#endif



#endif /* POWLIMEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
