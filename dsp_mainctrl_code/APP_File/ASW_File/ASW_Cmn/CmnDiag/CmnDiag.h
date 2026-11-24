//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnDiag.h
 * @brief
 * The header file of common diagnosis is designed to realize common diagnosis function.
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

#ifndef CMNDIAG_H_
#define CMNDIAG_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CmnDiagExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcDataCalcExt.h"
#include "PowLimExt.h"
#include "PerdTskExt.h"
#include "SpiExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define VOLT_AUX_12V_ERR_PROT         1.2f      ///< AUX 12V protection
#define VOLT_AUX_1V5_ERR_PROT         0.15f     ///< AUX 1.5V protection

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_CMN_DIAG stPrmExt;    ///< Parameter to extern
}ST_CMN_DIAG_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_CmnDiag_FltRst_1ms(void);
static void v_CmnDiag_Temp_100ms(void);
static void v_CmnDiag_Com_100ms(void);
static void v_CmnDiag_SPI_100ms(void);

#endif /* CMNDIAG_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
