//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl.c
 * @brief
 * The source file of peripheral control is designed to realize peripheral function.
 *
 * Module      :                       \n
 * PerphCtrl
 *
 * Unit        :                       \n
 * SPRly                               \n
 * Bld                                 \n
 * Led                                 \n
 * V2LAuxPow
 *
 * Module Task :                       \n
 * v_PerphCtrl_Init()                  \n
 * v_PerphCtrl_1ms()                   \n
 * v_PerphCtrl_10ms()                  \n
 * v_PerphCtrl_100ms()                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_SPRly_Init()            \n
 * v_PerphCtrl_SPRly_10ms()            \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Bld_Init()              \n
 * v_PerphCtrl_Bld_1ms()               \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Led_Init()              \n
 * v_PerphCtrl_Led_100ms()             \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_V2LAuxPow_Init()        \n
 * v_PerphCtrl_V2LAuxPow_1ms()         \n
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
#include "PerphCtrl.h"


//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PERPH_CTRL stPerphCtrl;       ///< Peripheral control global struct

#if (1U == PERPH_CTRL_DBG)
ST_PERPH_CTRL stPerphCtrlDbg;    ///< Peripheral control debug global struct
#endif

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: peripheral control in Init task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_Init(void)
{
    v_PerphCtrl_AcRly_Init();           ///< Ac relay initialization
    v_PerphCtrl_SPRly_Init();           ///< SP relay initialization
    v_PerphCtrl_Bld_Init();             ///< Bleed initialization
    v_PerphCtrl_Led_Init();             ///< Led initialization
    v_PerphCtrl_V2LAuxPow_Init();       ///< V2L Aux power initialization

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PerphCtrl_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: peripheral control in 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_1ms(void)
{
	v_PerphCtrl_Bld_1ms();	///< sst no use
	v_PerphCtrl_V2LAuxPow_1ms();    ///< sst no use

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PerphCtrl_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: peripheral control in 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_10ms(void)
{
    v_PerphCtrl_AcRly_10ms(); ///< sst no use
	v_PerphCtrl_SPRly_10ms(); ///< sst no use

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_PerphCtrl_10ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: peripheral control in 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_100ms(void)
{
	v_PerphCtrl_Led_100ms();

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_PerphCtrl_100ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
