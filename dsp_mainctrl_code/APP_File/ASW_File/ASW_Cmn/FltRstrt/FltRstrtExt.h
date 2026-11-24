//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltDataRecExt.h
 * @brief
 * The external header file of fault restart.
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

#ifndef FLTRSTRTEXT_H_
#define FLTRSTRTEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define FLT_RSTRT_DBG              0U              ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiFlgOverLim;         ///< Fault restart over limit flag
    Uint16 uiCmdFltRstrt;        ///< Fault restart command
    Uint16 uiCntrFltRstrt;       ///< Fault restart counter
}ST_FLT_RSTRT;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_FLT_RSTRT stFltRstrt;

#if (1U == FLT_RSTRT_DBG)
extern ST_FLT_RSTRT stFltRstrtDbg;
#endif

#endif /* FLTRSTRTEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
