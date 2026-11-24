//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerdTskExt.h
 * @brief
 * The external header file of PerdTsk is designed to judge module execution sequence.
 *
 * Module      :                 \n
 * PerdTsk
 *
 * Unit        :                 \n
 * null
 *
 * Unit Task   :                 \n
 * v_PerdTsk_Init()              \n
 * v_PerdTsk_1ms()               \n
 * v_PerdTsk_10ms()              \n
 * v_PerdTsk_100ms()             \n
 * v_PerdTsk_1s()                \n
 *
 * Unit Task   :                 \n
 * null
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

#ifndef PERDTSKEXT_H_
#define PERDTSKEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "SDL.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================


//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32 ftTimeIsrMax;               ///< Max interrupt run time
    float32 ftTimeIsrAvg;               ///< Average interrupt run time
    float32 ftTimeMainloopMax;          ///< Max mainloop run time
    float32 ftTimeMainloopAvg;          ///< Average main loop run time
    float32 ftTimeMainloopNoIsrAvg;     ///< Average main loop run time without ISR
}ST_RUN_TIME_TEST;

typedef struct
{
    Uint16 uiFlgSWIT1msEn;
    Uint16 uiFlgSWIT10msEn;
    Uint16 uiFlgSWIT100msEn;
    Uint16 uiFlgSWIT1sEn;
    Uint16 uiFlgSWITIsrEn;

    Uint16 uiFlgSWITDyn1ms;
    Uint16 uiFlgSWITDyn10ms;
    Uint16 uiFlgSWITDyn100ms;
    Uint16 uiFlgSWITDyn1s;
    Uint16 uiFlgSWITDynIsr;

    ST_RUN_TIME_TEST stRunTimeTest;
}ST_PERD_TSK;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PERD_TSK stPerdTsk;

#endif /* PERDTSKEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
