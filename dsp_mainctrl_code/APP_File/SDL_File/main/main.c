//==============================================================================================
//    File description
//==============================================================================================
/**@file         main.c
 * @brief
 * The source file of main is designed to call main function C Source File.
 *
 * Module      :                 \n
 * AppInit
 *
 * Unit        :                 \n
 * null
 *
 * Unit Task   :                 \n
 * v_AppInit()                   \n
 * ServiceDog()                  \n
 * v_ComDrv_Rx()                 \n
 * v_Com_Rx()                    \n
 * v_ComDrv_TxOkFlg()            \n
 * v_Com_Tx()                    \n
 * v_ComDrv_Tx()                 \n
 * v_PerdTsk_MainLoop()          \n
 *
 * Unit Task   :                 \n
 * null
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

//=====================================================
//    Include Header Files
//=====================================================
#include "main.h"

//=====================================================
//    Variable Definition
//=====================================================
#pragma DATA_SECTION(stAppProperty,"AppProperty_sect");
extern const ST_APP_PROPERTY stAppProperty = {0xAAAAU, 0x0101U};

#pragma DATA_SECTION(g_uiMdlProd,"ProdMdl_sect");
extern const Uint16 g_uiMdlProd = PROD_MDL;

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   main function
* @param [in]  null
* @param [out] null
* @return null
*/
void main(void)
{
    /* APP initialization */
    v_AppInit();

    /* Main Loop */
#if(0U == FLG_SWUT_EN)
    for(;;)
#endif
    {
        /* Service WatchDog */
        if(0U == stCom.uiFlgUpgProg)
        {
            ServiceDog();    ///< Service WatchDog
        }

#if(0U == COM_MODE)
        /* SCI communication */
        v_SciDrv_ErrRst();
        v_SciDrv_Rx();
        v_Com_Rx();
        v_Com_Tx();
        v_SciDrv_Tx();
        v_SciDrv_TxOkFlg();
#else
        /* CAN Communication */
        v_ComDrv_Rx();
        v_Com_Rx();
        v_ComDrv_TxOkFlg();
        v_Com_Tx();
        v_ComDrv_Tx();
#endif

        /* Period task in main loop */
        v_PerdTsk_MainLoop();

#if FLG_SPI_RDID_EN
        if(1U == stComTbl.stPrmToFpga.uiHandControl)
        {
            Uint16 l_uiIDData = 0;
            l_uiIDData = ui_SpiDrv_Cmn_ReadId(&SPIX_REG);
            stComTbl.stPrmToFpga.uiHandControl = 0;
        }
#endif
    }
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
