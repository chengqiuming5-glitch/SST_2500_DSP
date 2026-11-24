//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnDiagExt.h
 * @brief
 * The external header file of common diagnosis is designed to realize common diagnosis function.
 *
 * Module      :                       \n
 * CmnDiag                             \n
 *
 *
 * Module Task :                       \n
 * v_CmnDiag_Init()                    \n
 * v_CmnDiag_1ms()                     \n
 * v_CmnDiag_10ms()                    \n
 * v_CmnDiag_100ms()                   \n
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

#ifndef CMNDIAGEXT_H_
#define CMNDIAGEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define CMN_DIAG_DBG    0U    ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	Uint16 uiFltSys;                 ///< System fault
    Uint16 uiAux12VProt1000Times;    ///< AUX 12V protection 1000 times
    Uint16 uiAux1V5Prot1000Times;    ///< AUX 1.5V protection 1000 times
}ST_CMN_DIAG;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_CMN_DIAG stCmnDiag;

#if (1U == CMN_DIAG_DBG)
extern ST_CMN_DIAG stCmnDiagDbg;
#endif

#endif /* CMNDIAGEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
