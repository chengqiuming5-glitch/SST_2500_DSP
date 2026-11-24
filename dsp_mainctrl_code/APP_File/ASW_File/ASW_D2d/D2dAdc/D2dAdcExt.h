//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dAdcExt.h
 * @brief
 * The external header file of D2d ADC is designed to realize various related sampling.
 *
 * Module      :                       \n
 * D2dAdc                              \n
 *
 * Unit        :                       \n
 * PrmUpd                              \n
 * Ramp                                \n
 * FrqJit                              \n
 *
 * Module Task :                       \n
 * v_D2dAdc_Init()                     \n
 * v_D2dAdc_1ms()                      \n
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

#ifndef D2DADCEXT_H_
#define D2DADCEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_D2d.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define D2D_ADC_DBG                0U                  ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	float32 ftVoltBattLpf5kHz;          ///< Battery voltage 5kHz LPF
	float32 ftVoltBattLpf100Hz;         ///< Battery voltage 100Hz LPF
	float32 ftVoltBattLpf100HzEquiv;    ///< Battery voltage equivalent 100Hz LPF
	float32 ftVoltBattLpf10Hz;          ///< Battery voltage 10Hz LPF
	float32 ftVoltBattLpf10HzEquiv;     ///< Battery voltage equivalent 10Hz LPF
	float32 ftVoltBattUpLpf10Hz;        ///< Battery voltage up 10Hz LPF
	float32 ftVoltBattDwnLpf10Hz;       ///< Battery voltage down 10Hz LPF
    float32 ftVoltCellBatt[NUM_PHA_GRID][NUM_EMIF_POW_CELL];    ///< Power cell Battery voltage
    float32 ftVoltCellBusSum[NUM_PHA_GRID];///< Summery cell bus voltage
	float32 ftCurrBattLpf5kHz;          ///< Battery current 5kHz LPF
	float32 ftCurrBattLpf10Hz;          ///< Battery current 10Hz LPF
	float32 ftCurrBattUpLpf10Hz;        ///< Battery current up 10Hz LPF
	float32 ftCurrBattDwnLpf10Hz;       ///< Battery current down 10Hz LPF
	float32 ftCurrBattComp;             ///< Battery Current compensation by DSP board temperature
    float32 ftCurrCellBatt[NUM_PHA_GRID][NUM_EMIF_POW_CELL];    ///< Power cell Battery current

}ST_D2D_ADC;
//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_D2D_ADC stD2dAdc;

#if (1U == D2D_ADC_DBG)
extern ST_D2D_ADC stD2dAdcDbg;
#endif

#endif /* D2DADCEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================

