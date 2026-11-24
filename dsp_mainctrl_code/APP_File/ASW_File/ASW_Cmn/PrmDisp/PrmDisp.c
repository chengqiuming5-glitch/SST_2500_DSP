//==============================================================================================
//    File description
//==============================================================================================
/**@file         PrmDisp.c
 * @brief
 * The source file of module parameter display is designed to realize relevant parameter display.
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PrmDisp.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PRM_DISP stPrmDisp;

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        null
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PrmDisp_Init(void)
{
    stPrmDisp.siPrm1   = 0;         ///< Initialize to 0
    stPrmDisp.siPrm2   = 0;         ///< Initialize to 0
    stPrmDisp.siPrm3   = 0;         ///< Initialize to 0
    stPrmDisp.siPrm4   = 0;         ///< Initialize to 0
    stPrmDisp.siPrm5   = 0;         ///< Initialize to 0

    stPrmDisp.uiPrm1   = 0U;        ///< Initialize to 0
    stPrmDisp.uiPrm2   = 0U;        ///< Initialize to 0
    stPrmDisp.uiPrm3   = 0U;        ///< Initialize to 0
    stPrmDisp.uiPrm4   = 0U;        ///< Initialize to 0
    stPrmDisp.uiPrm5   = 0U;        ///< Initialize to 0

    stPrmDisp.ftPrm1   = 0.0f;      ///< Initialize to 0
    stPrmDisp.ftPrm2   = 0.0f;      ///< Initialize to 0
    stPrmDisp.ftPrm3   = 0.0f;      ///< Initialize to 0
    stPrmDisp.ftPrm4   = 0.0f;      ///< Initialize to 0
    stPrmDisp.ftPrm5   = 0.0f;      ///< Initialize to 0

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PrmDisp_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
