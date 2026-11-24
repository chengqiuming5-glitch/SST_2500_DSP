//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerdTsk.h
 * @brief
 * The header file of PerdTsk is designed to judge module execution sequence.
 *
 * Module      :                 \n
 * PerdTsk                       \n
 *
 * Unit Task   :                 \n
 * v_PerdTsk_Init()              \n
 * v_PerdTsk_1ms()               \n
 * v_PerdTsk_10ms()              \n
 * v_PerdTsk_100ms()             \n
 * v_PerdTsk_1s()                \n
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
#ifndef PERD_TSK_H_
#define PERD_TSK_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerdTskExt.h"
#include "ASW_Cmn.h"
#include "ASW_Pfc.h"
#include "ASW_D2d.h"
#include "CDD_Drv.h"
#include "ComExt.h"
#include "FltDataRecExt.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================
#if 1U == GRID_PHASE_NUMBER
#define ADC_INT_REG     AdcbRegs
#else
#define ADC_INT_REG     AdcaRegs
#endif

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* Run time Definition */
#define NUM_MAIN_LOOP_RUN_TIME_TEST         100U            ///< Main loop run time test number
#define NUM_ISR_RUN_TIME_TEST               FRQ_PFC_CTRL    ///< ISR run time test number
#define RECPR_MAIN_LOOP_RUN_TIME_TEST       (1.0f/(float32)(NUM_MAIN_LOOP_RUN_TIME_TEST))    ///< Reciprocal of main loop run time test number
#define RECPR_NUM_ISR_RUN_TIME_TEST         (1.0f/(float32)(NUM_ISR_RUN_TIME_TEST))     ///< Reciprocal of ISR run time test number

#define TIME_CPU_TIMER_CNTR                 5.0f                                                         ///< 5us; Time of CPU timer counter
#define COEFF_ISR_RUN_TIME_MAX              TIME_CPU_TIMER_CNTR                                          ///< Coefficient of Max ISR run time
#define COEFF_ISR_RUN_TIME_AVG              (TIME_CPU_TIMER_CNTR * RECPR_NUM_ISR_RUN_TIME_TEST)          ///< Coefficient of average ISR run time
#define COEFF_MAIN_LOOP_RUN_MAX             TIME_CPU_TIMER_CNTR                                          ///< Coefficient of Max main loop run time
#define COEFF_MAIN_LOOP_RUN_AVG             (TIME_CPU_TIMER_CNTR * RECPR_MAIN_LOOP_RUN_TIME_TEST)    ///< Coefficient of average main loop run time

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_RUN_TIME_TEST stPrmExt;      ///< Parameter to extern

    Uint16 uiCntrIsr;               ///< ISR counter
    Uint16 uiCntrMainloop;          ///< Main loop counter
    Uint16 uiCntrIsrIn1ms;          ///< ISR counter in 1ms
    Uint32 ulCnrtIsrIn1msSum;       ///< Sum of ISR counter in 1ms
    Uint32 ulValIsrStart;           ///< Isr start point CPU timer value
    Uint32 ulValIsrEnd;             ///< Isr end point CPU timer value
    Uint32 ulValMainloopStart;      ///< Main loop start CPU timer value
    Uint32 ulValMainloopEnd;        ///< Main loop end CPU timer value
    Uint32 ulValIsrDelta;           ///< Delta CPU timer value of ISR
    Uint32 ulValMainloopDelta;      ///< Delta CPU timer value of Mainloop
    Uint32 ulValIsrSum;             ///< Sum of ISR delta value
    Uint32 ulValMainloopSum;        ///< Sum of main loop delta value
}ST_RUN_TIME_TEST_LOC;

typedef struct
{
    Uint16 uiCntr1ms;           ///< 1ms counter
    Uint16 uiCntr10ms;          ///< 10ms counter
    Uint16 uiCntr100ms;         ///< 100ms counter
    Uint16 uiCntr1s;            ///< 100ms counter
    Uint16 uiFlgSWIT1msDone;
    Uint16 uiFlgSWIT10msDone;
    Uint16 uiFlgSWIT100msDone;
    Uint16 uiFlgSWIT1sDone;
    Uint16 uiFlgSWITIsrDone;

    ST_RUN_TIME_TEST_LOC  stRunTimeTestLoc;
}ST_PERD_TSK_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PerdTsk_1ms(void);
static void v_PerdTsk_10ms(void);
static void v_PerdTsk_100ms(void);
static void v_PerdTsk_1s(void);
#if 1U == FLG_RUN_TIME_TEST_EN
static void v_PerdTsk_Isr_Runtime_Cal(void);
static void v_PerdTsk_Mainloop_Runtime_Cal_1ms(void);
#endif

//==============================================================================================
//    Global Function Declaration
//==============================================================================================
extern void ServiceDog(void);

#endif /* PERD_TSK_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
