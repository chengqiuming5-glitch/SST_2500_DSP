//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmnDiag.c
 * @brief
 * The source file of common diagnosis is designed to realize common diagnosis function.
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CmnDiag.h"
//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_CMN_DIAG stCmnDiag;                  ///< D2D diagnose global struct

#if (1U == CMN_DIAG_DBG)
ST_CMN_DIAG stCmnDiagDbg;               ///< Diagnose debug global struct
#endif

static ST_CMN_DIAG_LOC stCmnDiagLoc;    ///< Diagnose local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnDiag_Init(void)
{
    /* Local Signal*/
	stCmnDiagLoc.stPrmExt.uiFltSys              = 0U;                ///< Initialize to 0
	stCmnDiagLoc.stPrmExt.uiAux12VProt1000Times = (Uint16)(VOLT_AUX_12V_ERR_PROT * COEFF_AUX_ARM);
    stCmnDiagLoc.stPrmExt.uiAux1V5Prot1000Times = (Uint16)(VOLT_AUX_1V5_ERR_PROT * COEFF_AUX_ARM);

    /* Global Signal*/
#if (1U == CMN_DIAG_DBG)
	stCmnDiagDbg.uiFltSys              = stCmnDiagLoc.stPrmExt.uiFltSys;     ///< Initialize to 0
	stCmnDiagDbg.uiAux12VProt1000Times = stCmnDiagLoc.stPrmExt.uiAux12VProt1000Times;
	stCmnDiagDbg.uiAux1V5Prot1000Times = stCmnDiagLoc.stPrmExt.uiAux1V5Prot1000Times;

	stCmnDiag.uiFltSys              = stCmnDiagDbg.uiFltSys;                 ///< Initialize to 0
    stCmnDiag.uiAux12VProt1000Times = stCmnDiagDbg.uiAux12VProt1000Times;
    stCmnDiag.uiAux1V5Prot1000Times = stCmnDiagDbg.uiAux1V5Prot1000Times;
#else
	stCmnDiag.uiFltSys              = stCmnDiagLoc.stPrmExt.uiFltSys;        ///< Initialize to 0
	stCmnDiag.uiAux12VProt1000Times = stCmnDiagLoc.stPrmExt.uiAux12VProt1000Times;
	stCmnDiag.uiAux1V5Prot1000Times = stCmnDiagLoc.stPrmExt.uiAux1V5Prot1000Times;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_CmnDiag_Init() is running****\r\n");
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnDiag_1ms(void)
{
    v_CmnDiag_FltRst_1ms();         ///< Reset Fault

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_CmnDiag_1ms() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmnDiag_100ms(void)
{
    v_CmnDiag_Temp_100ms();         ///< Temperature Fault
    v_CmnDiag_Com_100ms();          ///< Communication Fault
    v_CmnDiag_SPI_100ms();          ///< SPI verify data Fault

    /* Output Signal*/
#if (1U == CMN_DIAG_DBG)
    stCmnDiag.uiFltSys    = stCmnDiagDbg.uiFltSys;
#else
    stCmnDiag.uiFltSys    = stCmnDiagLoc.stPrmExt.uiFltSys;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_CmnDiag_100ms() is running****\r\n");
    }
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault reset 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnDiag_FltRst_1ms(void)
{
    /* D2D fault reset */
    if((FCN_ENABLE == stComIf.uiFlgFltRst) && (0U != stCmnDiagLoc.stPrmExt.uiFltSys))
    {
        stCmnDiagLoc.stPrmExt.uiFltSys = 0U;
    }

    /* Output Signal*/
#if (1U == CMN_DIAG_DBG)
    stCmnDiag.uiFltSys    = stCmnDiagDbg.uiFltSys;
#else
    stCmnDiag.uiFltSys    = stCmnDiagLoc.stPrmExt.uiFltSys;
#endif
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose Temperature 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnDiag_Temp_100ms(void)
{
    /* Temperature Protection */
    if((1U == stComIf.uiFlgPowOn) \
            && (PFC_EN_D2D_EN == stCom.uiStgRunEnReq) \
            && (OPENLOOP_MODE != stComIf.uiModRun) && (PFC_CHG_D2D_OL_MODE != stComIf.uiModRun) && (PFC_OL_D2D_DISCH_MODE != stComIf.uiModRun))    // Control power on && PFC and D2D Run && No open-loop mode
    {
        /* Over Temperature Protection */
        if((stPowLim.ftTempMax > stComTbl.stPrmCmnDiag.ftOverTemp) && (0U == (stComTbl.unWordSysFltMask.all & FLT_SYS_OT)))
        {
            stCmnDiagLoc.stPrmExt.uiFltSys |= FLT_SYS_OT;
        }

        /* Under Temperature Protection */
        if((stPowLim.ftTempMin < stComTbl.stPrmCmnDiag.ftUnderTemp) && (0U == (stComTbl.unWordSysFltMask.all & FLT_SYS_UT)))
        {
            stCmnDiagLoc.stPrmExt.uiFltSys |= FLT_SYS_UT;
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose Communication 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnDiag_Com_100ms(void)
{
    /* Can communication Protection */
    if((1U == stComIf.uiFlgPowOn) && (START_CMD == stComIf.uiCmdRun))    ///< Control power on && After Run command
    {
        if((stCom.uiComFailCntr > 8U) && (0U == (stComTbl.unWordSysFltMask.all & FLT_SYS_CAN_COM)))    ///< 8s
        {
            stCmnDiagLoc.stPrmExt.uiFltSys |= FLT_SYS_CAN_COM;
        }
    }
}
/********************************************End***********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Diagnose Communication 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_CmnDiag_SPI_100ms(void)
{
    /* SPI Data verify Protection */
    if((0U != stSpi.stErrSpi.all) && (0U == (stComTbl.unWordSysFltMask.all & FLT_SYS_SPI_COM)))
    {
        stCmnDiagLoc.stPrmExt.uiFltSys |= FLT_SYS_SPI_COM;
    }
}
/********************************************End***********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
