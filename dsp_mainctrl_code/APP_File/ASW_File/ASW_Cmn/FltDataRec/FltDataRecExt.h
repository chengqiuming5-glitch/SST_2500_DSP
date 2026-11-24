//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltDataRecExt.h
 * @brief
 * The external header file of fault data record.
 *
 * Module      :                       \n
 * FltDataRec                          \n
 *
 * Unit        :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 * Module Task :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 * Unit Task   :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/10/14
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
 * <tr><td>2024/10/14  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef FLTDATARECEXT_H_
#define FLTDATARECEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define FLT_DATA_REC_DBG              0U              ///< Debug for SWUT,SWIT,Function debug,etc

#define SIZE_REC_ARRAY                SIZE_POW_PRM_NUM_FLT_REC             ///< Record array size
#define NUM_ARRAY_VA                  0U              ///< Va record number
#define NUM_ARRAY_VB                  1U              ///< Vb record number
#define NUM_ARRAY_VC                  2U              ///< Vc record number
#define NUM_ARRAY_IA                  3U              ///< Ia record number
#define NUM_ARRAY_IB                  4U              ///< Ib record number
#define NUM_ARRAY_IC                  5U              ///< Ic record number
#define NUM_ARRAY_IN                  6U              ///< In record number
#define NUM_ARRAY_VBUS                7U              ///< Vbus positive record number
#define NUM_ARRAY_VBUS_POS            8U              ///< Vbus positive record number
#define NUM_ARRAY_VBUS_NEG            9U              ///< Vbus negative record number
#define NUM_ARRAY_VBATT_UP            10U              ///< Up battery voltage record number
#define NUM_ARRAY_VBATT_DWN           11U             ///< Down battery voltage record number
#define NUM_ARRAY_IBATT_UP            12U             ///< Up battery current record number
#define NUM_ARRAY_IBATT_DWN           13U             ///< Down battery current record number

#define YEAR_SYS_TIME_DFT             1990UL          ///< Default year of system time
#define MONTH_SYS_TIME_DFT            1UL             ///< Default month of system time
#define DATE_SYS_TIME_DFT             1UL             ///< Default date of system time
#define HOUR_SYS_TIME_DFT             0UL             ///< Default hour of system time
#define MIN_SYS_TIME_DFT              0UL             ///< Default minute of system time
#define SEC_SYS_TIME_DFT              0UL             ///< Default second of system time
#define MILLI_SEC_SYS_TIME_DFT        0UL             ///< Default milli-second of system time

#define LEFT_SHIFT_BIT_YEAR_REC       35U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_MONTH_REC      31U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_DATE_REC       26U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_HOUR_REC       22U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_MIN_REC        16U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_SEC_REC        10U             ///< Record year left shift bits
#define LEFT_SHIFT_BIT_MILLI_SEC_REC  0U              ///< Record year left shift bits

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiSys;           ///< System fault record
    Uint16 uiPfc1;          ///< PFC fault 1 record
    Uint16 uiPfc2;          ///< PFC fault 2 record
    Uint16 uiPfc3;          ///< PFC fault 3 record
    Uint16 uiD2dCpu;        ///< D2D CPU fault record
    Uint16 uiD2dCla;        ///< D2D CLA fault record
}ST_FLT_REC;

typedef struct
{
    int16  siDspBd;         ///< DSP board temperature record
    int16  siArmBd;         ///< ARM board temperature record
    int16  siNtc0;          ///< NTC 0 temperature record
    int16  siNtc1;          ///< NTC 1 temperature record
    int16  siNtc2;          ///< NTC 2 temperature record
    int16  siNtc3;          ///< NTC 3 temperature record
    int16  siNtc4;          ///< NTC 4 temperature record
    int16  siNtc5;          ///< NTC 5 temperature record
    int16  siNtc6;          ///< NTC 6 temperature record
}ST_TEMP_REC;

typedef union
{
    Uint16 all;

    struct
    {
        Uint16 uiStrt      : 1;     /* bit0: Record start flag */
        Uint16 uiEnd       : 1;     /* bit1: Record end flag */
        Uint16 uiFltRcd    : 1;     /* bit2: Fault record flag */
        Uint16 uiRsvd      : 14;    /* bit3~15: Reserved */
    }bit;
}UN_FLG_DATA_REC;

typedef struct
{
    ST_FLT_DATA stFltData;
    UN_FLG_DATA_REC unFlgRec;
    Uint16 uiPtrArrRec;         ///< Array record pointer.
    Uint16 uiFlgFltDataRec;     ///< Fault data record flag
}ST_FLT_DATA_REC;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_FLT_DATA_REC stFltDataRec;
extern UN_SYS_TIME unTimeSys;

#if (1U == FLT_DATA_REC_DBG)
extern ST_FLT_DATA_REC stFltDataRecDbg;
#endif

/* Fault data record. To be moved to ASW_Cmn.h */
extern void v_FltDataRec_Init(void);
extern void v_FltDataRec_1ms(void);
extern void v_FltDataRec_ISR(void);

#endif /* FLTDATARECEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
