//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltDataRec.h
 * @brief
 * The header file of fault data record is designed to restart after fault.
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
 * <tr><td>2024/10/30  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef FLTRSTRT_H_
#define FLTRSTRT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FltRstrtExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "D2dDiagExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define MAX_NUM_FLT_RSTRT           3U       ///< MAX fault restart number
#define TIME_FLT_RSTRT              1800U    ///< 30min
#define TIME_DELAY_FLT_RSTRT_SET    10U      ///< Fault restart set command delay 10s
#define TIME_DELAY_FLT_RSTRT_CLR    2U       ///< Fault restart clear command delay 2s

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiFront;                         ///< Queue front
    Uint16 uiRear;                          ///< Queue rear
    Uint16 uiCntrAry[MAX_NUM_FLT_RSTRT];    ///< Counter array
}ST_FLT_RSTRT_QUE;

typedef struct
{
    ST_FLT_RSTRT     stPrmExt;       ///< External parameter
    ST_FLT_RSTRT_QUE stQue;          ///< Queue parameter
    Uint16 uiFlgSetCmd;              ///< Set command flag
    Uint16 uiCntrSetCmd;             ///< Set command counter
    Uint16 uiCntrClrCmd;             ///< Clear command counter
}ST_FLT_RSTRT_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_FltRstrt_InitPrm(void);
static void v_FltRstrt_Jdg_1s(void);
static void v_FltRstrt_Que_1s(void);

#endif /* FLTRSTRT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
