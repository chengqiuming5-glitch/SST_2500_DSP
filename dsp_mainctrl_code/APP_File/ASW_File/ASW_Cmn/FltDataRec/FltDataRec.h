//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltDataRec.h
 * @brief
 * The header file of fault data record is designed to record the fault data.
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

#ifndef FLTDATAREC_H_
#define FLTDATAREC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FltDataRecExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "CmnAdcExt.h"
#include "PfcAdcExt.h"
#include "CmnDiagExt.h"
#include "PfcDiagExt.h"
#include "D2dDiagExt.h"
//#include "D2dPowCtrlExt.h"
#include "SpiExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* Time constants */
#define MILLISECONDS_PER_SECOND    1000U
#define SECONDS_PER_MINUTE         60U
#define MINUTES_PER_HOUR           60U
#define HOURS_PER_DAY              24U
#define MONTHS_PER_YEAR            12U

/* Time validation constants */
#define MIN_VALID_YEAR             2024U
#define MIN_VALID_MONTH            1U
#define MAX_VALID_MONTH            12U
#define MIN_VALID_DATE             1U
#define MAX_VALID_HOUR             23U
#define MAX_VALID_MINUTE           59U
#define MAX_VALID_SECOND           59U

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    UN_SYS_TIME unTiLoc;     ///< Local time

    Uint16 uiCntrPostFlt;    ///< Post fault counter
}ST_FLT_DATA_REC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_FltDataRec_TiPrm_Init(void);
static void v_FltDataRec_DataPrm_Init(void);
static void v_FltDataRec_Volt_Curr(void);
static void v_FltDataRec_Time(void);
static void v_FltDataRec_Flt(void);
static void v_FltDataRec_Temp(void);
static void v_FltDataRec_ClrChk_1ms(void);
static void v_FltDataRec_TiSycn(void);
static void v_FltDataRec_TiSycn_Hndl(UN_SYS_TIME* pstExtTime);
static void v_FltDataRec_TiSycn_Inct(void);
static bool b_FltDataRec_TiSycn_IsLeapYear(Uint32 ulYear);
static Uint16 ui_FltDataRec_TiSycn_GetDate(Uint32 ulYear, Uint32 ulMonth);
#endif /* FLTDATAREC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
