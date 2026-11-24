//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dAdc.h
 * @brief
 * The header file of D2d ADC is designed to realize various related sampling.
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

#ifndef D2DADC_H_
#define D2DADC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "D2dAdcExt.h"

#include "CmnAdcExt.h"
//#include "D2dPowCtrlExt.h"
#include "PerdTskExt.h"
#include "PfcAdcExt.h"
#include "EmifExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* Battery current compensation Macro Definition */
#define TEMP_LOW_CURR_BATT_COMP       10.0f        ///< Low temperature point
#define TEMP_HIGH_CURR_BATT_COMP      20.0f        ///< High temperature point

#define COEFF_K_CURR_BATT_COMP_LOW    -0.0087f      ///< Coefficient K in low temperature
#define COEFF_B_CURR_BATT_COMP_LOW    0.1228f       ///< Coefficient B in low temperature

#define COEFF_K_CURR_BATT_COMP_HIGH   -0.0038f     ///< Coefficient K in high temperature
#define COEFF_B_CURR_BATT_COMP_HIGH   0.0424f      ///< Coefficient B in high temperature

#define COEFF_AD_VBATT                0.431746f
#define COEFF_AD_IBATT                0.04882f
//==============================================================================================
//    Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_D2D_ADC stPrmExt;                  ///< Parameter to extern
    Uint16 uiCntrComp;                    ///< CurrBattComp counter
}ST_D2D_ADC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
#if 1U == GRID_PHASE_NUMBER
static void v_D2dAdc_CurrBattComp(void);
#endif /* 1U == GRID_PHASE_NUMBER */

#endif /* D2DADC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
