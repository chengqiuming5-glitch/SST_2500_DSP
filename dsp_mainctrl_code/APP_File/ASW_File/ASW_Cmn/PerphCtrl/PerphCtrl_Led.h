//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_Led.h
 * @brief
 * The header file of led control is designed to realize D2d Led function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Led_Init()              \n
 * v_PerphCtrl_Led_100ms()             \n
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


#ifndef PERPHCTRL_LED_H_
#define PERPHCTRL_LED_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrl.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* LED Macro Definition */
#define LED_TOG_DSP_BOOT    1U                      ///< Led Toggle in Boot state    - 200ms
#define LED_TOG_DSP_APP     10U                     ///< Led Toggle in APP state     - 1s
#define LED_TOG_FLT         5U                      ///< Led Toggle in Fault state   - 500ms
#define LED_TOG_STB         10U                     ///< Led Toggle in Standby state - 1s
#define LED_TOG_RUN         20U                     ///< Led Toggle in run state     - 2s

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_LED stPrmExt;          ///< Parameter to extern

    Uint16 uiNrDspRun;        ///< DSP run number
    Uint16 uiNrPfcRunSt;      ///< PFC run state number
    Uint16 uiCntrPfcRunSt;    ///< PFC run state counter
	Uint16 uiNrD2dRunSt;      ///< D2D run state number
	Uint16 uiCntrD2dRunSt;    ///< D2D run state counter
}ST_LED_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PerphCtrl_Led_DspRun_100ms(void);
static void v_PerphCtrl_Led_PfcRunSt_100ms(void);
static void v_PerphCtrl_Led_D2dRunSt_100ms(void);

#endif /* PERPHCTRL_LED_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
