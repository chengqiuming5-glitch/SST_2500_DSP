//==============================================================================================
//    File description
//==============================================================================================
/**@file         PrmDispExt.h
 * @brief
 * The external header file of module parameter display is designed to realize relevant parameter display.
 *
 * Module      :                       \n
 * PrmDisp
 *
 * Module Task :                       \n
 * v_PrmDisp_Init()                    \n
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

#ifndef PRMDISPEXT_H_
#define PRMDISPEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    int16   siPrm1;
    int16   siPrm2;
    int16   siPrm3;
    int16   siPrm4;
    int16   siPrm5;

    Uint16  uiPrm1;
    Uint16  uiPrm2;
    Uint16  uiPrm3;
    Uint16  uiPrm4;
    Uint16  uiPrm5;

    float32 ftPrm1;
    float32 ftPrm2;
    float32 ftPrm3;
    float32 ftPrm4;
    float32 ftPrm5;
}ST_PRM_DISP;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PRM_DISP stPrmDisp;

#endif /* PRMDISPEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
