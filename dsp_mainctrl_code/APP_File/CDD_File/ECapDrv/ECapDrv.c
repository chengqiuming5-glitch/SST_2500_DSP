//==============================================================================================
//    File description
//==============================================================================================
/**@file         ECapDrv.c
 * @brief
 * Source file of ECap drive.
 *
 * Module      :                       \n
 * ECapDrv
 *
 * Module Task :                       \n
 * v_EcapDrv_Init()                    \n
 * v_EcapDrv_1ms()                     \n
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
#include "ECapDrv.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_ECAP_DRV stECapDrv;
#if (1U == EACP_DRV_DBG)
ST_ECAP_DRV stECapDrvDbg;
#endif
#if(1U == FLG_SWUT_EN)
struct ECAP_REGS ECap1RegsUnitTest;
struct ECAP_REGS ECap2RegsUnitTest;
struct ECAP_REGS ECap3RegsUnitTest;
#endif
static ST_ECAP_DRV_LOC stECapDrvLoc;    ///< ADC drive local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        ECap drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ECapDrv_Init(void)
{
    stECapDrvLoc.stPrmExt.ulCntrEcapRegA = 0UL;        ///< Initialize to 0UL
    stECapDrvLoc.stPrmExt.ulCntrEcapRegB = 0UL;        ///< Initialize to 0UL
    stECapDrvLoc.stPrmExt.ulCntrEcapRegC = 0UL;        ///< Initialize to 0UL

    /* Global Signal*/
#if (1U == EACP_DRV_DBG)
    stECapDrvDbg.ulCntrEcapRegA = stECapDrvLoc.stPrmExt.ulCntrEcapRegA;
    stECapDrvDbg.ulCntrEcapRegB = stECapDrvLoc.stPrmExt.ulCntrEcapRegB;
    stECapDrvDbg.ulCntrEcapRegC = stECapDrvLoc.stPrmExt.ulCntrEcapRegC;

    stECapDrv.ulCntrEcapRegA    = stECapDrvDbg.ulCntrEcapRegA;
    stECapDrv.ulCntrEcapRegB    = stECapDrvDbg.ulCntrEcapRegB;
    stECapDrv.ulCntrEcapRegC    = stECapDrvDbg.ulCntrEcapRegC;
#else
    stECapDrv.ulCntrEcapRegA    = stECapDrvLoc.stPrmExt.ulCntrEcapRegA;
    stECapDrv.ulCntrEcapRegB    = stECapDrvLoc.stPrmExt.ulCntrEcapRegB;
    stECapDrv.ulCntrEcapRegC    = stECapDrvLoc.stPrmExt.ulCntrEcapRegC;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_ECapDrv_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        ECap drive 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ECapDrv_1ms(void)
{
    if(1U == PFC_PHASE_A_FRQ_ECAP_REG.ECFLG.bit.CEVT1)    ///< Falling edge of PhaseA flag
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegA = PFC_PHASE_A_FRQ_ECAP_REG.CAP1;
        /* Clear flag */
        PFC_PHASE_A_FRQ_ECAP_REG.ECCLR.bit.CEVT1 = 1U;
    }
    else
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegA = 0UL;
    }

#if(GRID_PHASE_NUMBER > 1U)
    if(1U == PFC_PHASE_B_FRQ_ECAP_REG.ECFLG.bit.CEVT1)    ///< Falling edge of PhaseA flag
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegB = PFC_PHASE_B_FRQ_ECAP_REG.CAP1;
        /* Clear flag */
        PFC_PHASE_B_FRQ_ECAP_REG.ECCLR.bit.CEVT1 = 1U;
    }
    else
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegB = 0UL;
    }

#if(GRID_PHASE_NUMBER > 2U)
    if(1U == PFC_PHASE_C_FRQ_ECAP_REG.ECFLG.bit.CEVT1)    ///< Falling edge of PhaseA flag
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegC = PFC_PHASE_C_FRQ_ECAP_REG.CAP1;
        /* Clear flag */
        PFC_PHASE_C_FRQ_ECAP_REG.ECCLR.bit.CEVT1 = 1U;
    }
    else
    {
        stECapDrvLoc.stPrmExt.ulCntrEcapRegC = 0UL;
    }
    #endif
#endif

    /* Global Signal*/
#if (1U == EACP_DRV_DBG)
    stECapDrv.ulCntrEcapRegA    = stECapDrvDbg.ulCntrEcapRegA;
    stECapDrv.ulCntrEcapRegB    = stECapDrvDbg.ulCntrEcapRegB;
    stECapDrv.ulCntrEcapRegC    = stECapDrvDbg.ulCntrEcapRegC;
#else
    stECapDrv.ulCntrEcapRegA    = stECapDrvLoc.stPrmExt.ulCntrEcapRegA;
    stECapDrv.ulCntrEcapRegB    = stECapDrvLoc.stPrmExt.ulCntrEcapRegB;
    stECapDrv.ulCntrEcapRegC    = stECapDrvLoc.stPrmExt.ulCntrEcapRegC;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_ECapDrv_1ms() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
