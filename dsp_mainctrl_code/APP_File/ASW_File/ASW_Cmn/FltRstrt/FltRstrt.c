//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltRstrt.c
 * @brief
 * The header file of fault restart is designed to restart after fault.
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
 * <tr><td>2024/10/14  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FltRstrt.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_FLT_RSTRT stFltRstrt;                         ///< Fault restart global struct

#if (1U == FLT_RSTRT_DBG)
extern ST_FLT_RSTRT stFltRstrtDbg;               ///< Fault restart debug global struct
#endif

static ST_FLT_RSTRT_LOC stFltRstrtLoc;           ///< Fault data record local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        Fault restart initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltRstrt_Init(void)
{
    /* Local Signal */
    v_FltRstrt_InitPrm();

    /* Global Signal */
#if (1U == FLT_RSTRT_DBG)
    stFltRstrtDbg.uiFlgOverLim   = stFltRstrtLoc.stPrmExt.uiFlgOverLim;
    stFltRstrtDbg.uiCmdFltRstrt  = stFltRstrtLoc.stPrmExt.uiCmdFltRstrt;
    stFltRstrtDbg.uiCntrFltRstrt = stFltRstrtLoc.stPrmExt.uiCntrFltRstrt;

    stFltRstrt.uiFlgOverLim   = stFltRstrtDbg.uiFlgOverLim;
    stFltRstrt.uiCmdFltRstrt  = stFltRstrtDbg.uiCmdFltRstrt;
    stFltRstrt.uiCntrFltRstrt = stFltRstrtDbg.uiCntrFltRstrt;
#else
    stFltRstrt.uiFlgOverLim   = stFltRstrtLoc.stPrmExt.uiFlgOverLim;
    stFltRstrt.uiCmdFltRstrt  = stFltRstrtLoc.stPrmExt.uiCmdFltRstrt;
    stFltRstrt.uiCntrFltRstrt = stFltRstrtLoc.stPrmExt.uiCntrFltRstrt;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_FltRstrt_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault restart parameter initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltRstrt_InitPrm(void)
{
    Uint16 i;

    stFltRstrtLoc.stPrmExt.uiFlgOverLim   = FCN_DISABLE;        ///< Initialize to disable flag
    stFltRstrtLoc.stPrmExt.uiCmdFltRstrt  = FCN_DISABLE;        ///< Initialize to disable command
    stFltRstrtLoc.stPrmExt.uiCntrFltRstrt = 0U;                 ///< Initialize to 0U
    stFltRstrtLoc.uiFlgSetCmd             = FCN_DISABLE;        ///< Initialize to disable flag
    stFltRstrtLoc.uiCntrSetCmd            = 0U;                 ///< Initialize to 0U
    stFltRstrtLoc.uiCntrClrCmd            = 0U;                 ///< Initialize to 0U
    stFltRstrtLoc.stQue.uiFront           = 0U;                 ///< Initialize to 0U
    stFltRstrtLoc.stQue.uiRear            = 0U;                 ///< Initialize to 0U
    for(i = 0U; i < MAX_NUM_FLT_RSTRT; i++)
    {
        stFltRstrtLoc.stQue.uiCntrAry[i] = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault restart 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltRstrt_10ms(void)
{
    /* Initialize parameter under fault reset command */
    if(SYS_FLT_RESET_IS_ON)
    {
        v_FltRstrt_InitPrm();

        /* Global Signal */
#if (1U == FLT_RSTRT_DBG)
        stFltRstrt.uiFlgOverLim   = stFltRstrtDbg.uiFlgOverLim;
        stFltRstrt.uiCmdFltRstrt  = stFltRstrtDbg.uiCmdFltRstrt;
        stFltRstrt.uiCntrFltRstrt = stFltRstrtDbg.uiCntrFltRstrt;
#else
        stFltRstrt.uiFlgOverLim   = stFltRstrtLoc.stPrmExt.uiFlgOverLim;
        stFltRstrt.uiCmdFltRstrt  = stFltRstrtLoc.stPrmExt.uiCmdFltRstrt;
        stFltRstrt.uiCntrFltRstrt = stFltRstrtLoc.stPrmExt.uiCntrFltRstrt;
#endif
    }

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_FltRstrt_10ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault restart 1s task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltRstrt_1s(void)
{
    if(START_CMD == stCom.uiCmdRunReq)
    {
        if(FCN_DISABLE == stFltRstrtLoc.stPrmExt.uiCmdFltRstrt)    ///< Fault restart command is disabled
        {
            if(FCN_DISABLE == stFltRstrtLoc.uiFlgSetCmd)    ///< Set command flag is disabled
            {
                if((FCN_DISABLE == stFltRstrtLoc.stPrmExt.uiFlgOverLim) && (FCN_ENABLE == stComTbl.stPrmFltRstrt.uiEnaFltRstrt))    ///< No over limit flag && Fault restart enable
                {
                    v_FltRstrt_Jdg_1s();    ///< Fault restart judgement task
                }
            }
            else                                            ///< Set command flag is enabled
            {
                /* After delay 10s, set fault restart command */
                stFltRstrtLoc.uiCntrSetCmd++;
                if(stFltRstrtLoc.uiCntrSetCmd >= TIME_DELAY_FLT_RSTRT_SET)
                {
                    stFltRstrtLoc.stPrmExt.uiCmdFltRstrt = FCN_ENABLE;    ///< Set fault restart command
                    stFltRstrtLoc.uiFlgSetCmd  = FCN_DISABLE;             ///< Clear set command flag
                    stFltRstrtLoc.uiCntrSetCmd = 0U;                      ///< Clear set command counter
                }
            }
        }
        else    ///< Fault restart command is enabled
        {
            /* After delay 2s, clear fault restart command */
            stFltRstrtLoc.uiCntrClrCmd++;
            if(stFltRstrtLoc.uiCntrClrCmd >= TIME_DELAY_FLT_RSTRT_CLR)
            {
                stFltRstrtLoc.stPrmExt.uiCmdFltRstrt = FCN_DISABLE;
                stFltRstrtLoc.uiCntrClrCmd = 0U;
            }
        }

        /* Fault restart queue task */
        v_FltRstrt_Que_1s();
    }
    else
    {
        /* Initialize parameter under stop command */
        v_FltRstrt_InitPrm();
    }

    /* Global Signal*/
#if (1U == FLT_RSTRT_DBG)
    stFltRstrt.uiFlgOverLim   = stFltRstrtDbg.uiFlgOverLim;
    stFltRstrt.uiCmdFltRstrt  = stFltRstrtDbg.uiCmdFltRstrt;
    stFltRstrt.uiCntrFltRstrt = stFltRstrtDbg.uiCntrFltRstrt;
#else
    stFltRstrt.uiFlgOverLim   = stFltRstrtLoc.stPrmExt.uiFlgOverLim;
    stFltRstrt.uiCmdFltRstrt  = stFltRstrtLoc.stPrmExt.uiCmdFltRstrt;
    stFltRstrt.uiCntrFltRstrt = stFltRstrtLoc.stPrmExt.uiCntrFltRstrt;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1s)
    {
        printf("****SWIT DynamicTest: function v_FltRstrt_1s() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault restart judgement task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltRstrt_Jdg_1s(void)
{
    Uint16 l_uiEnaPfcGridFltRstrt = 0U;    ///< PFC grid fault restart enable

    /* In On-grid bi-direction mode, grid fault need to be ignored */
    if(BIDIR_ONGRID_MODE == stComIf.uiModRun)
    {
        l_uiEnaPfcGridFltRstrt = 0U;
    }
    else
    {
        l_uiEnaPfcGridFltRstrt = stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt2.all;
    }

    /* Fault restart judgement */
    if((0U != (stComTbl.unWordPfcFlt1.all & stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt1.all)) \
       || (0U != (stComTbl.unWordPfcFlt2.all & l_uiEnaPfcGridFltRstrt)) \
       || (0U != (stComTbl.unWordPfcFlt3.all & stComTbl.stPrmFltRstrt.unEnaPfcFltRstrt3.all)) \
       || (0U != (stComTbl.unWordSysFlt.all & stComTbl.stPrmFltRstrt.unEnaSysFltRstrt.all)) \
       || (0U != (stD2dDiag.uiFltCpu & stComTbl.stPrmFltRstrt.uiEnaD2dFltCpuRstrt)) \
       || (0U != (stD2dDiag.uiFltCla & stComTbl.stPrmFltRstrt.uiEnaD2dFltClaRstrt)))
    {
        stFltRstrtLoc.stPrmExt.uiCntrFltRstrt++;
        if(stFltRstrtLoc.stPrmExt.uiCntrFltRstrt <= MAX_NUM_FLT_RSTRT)
        {
            /* Update queue rear */
            stFltRstrtLoc.stQue.uiRear++;
            if(stFltRstrtLoc.stQue.uiRear >= MAX_NUM_FLT_RSTRT)
            {
                stFltRstrtLoc.stQue.uiRear = 0U;
            }

            stFltRstrtLoc.uiFlgSetCmd = FCN_ENABLE;
        }
        else
        {
            stFltRstrtLoc.stPrmExt.uiFlgOverLim = FCN_ENABLE;    ///< Set over limit flag
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault restart queue task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltRstrt_Que_1s(void)
{
    Uint16 l_uiCntrTmp      = 0U;    ///< Counter temporary
    Uint16 l_uiCntrFltRstrt = 0U;
    Uint16 i;

    if(stFltRstrtLoc.stPrmExt.uiCntrFltRstrt > 0U)    ///< Fault restart counter is not 0U
    {
        l_uiCntrFltRstrt = stFltRstrtLoc.stPrmExt.uiCntrFltRstrt;
        for(i = 0U; i < l_uiCntrFltRstrt; i++)
        {
            /* Calculate array pointer */
            l_uiCntrTmp = stFltRstrtLoc.stQue.uiFront + i;
            if(l_uiCntrTmp >= MAX_NUM_FLT_RSTRT)
            {
                l_uiCntrTmp = 0U;
            }

            /* Calculate fault time */
            stFltRstrtLoc.stQue.uiCntrAry[l_uiCntrTmp]++;
            if(stFltRstrtLoc.stQue.uiCntrAry[l_uiCntrTmp] >= TIME_FLT_RSTRT)
            {
                /* Update queue fault counter */
                stFltRstrtLoc.stPrmExt.uiCntrFltRstrt--;

                /* Update queue front */
                stFltRstrtLoc.stQue.uiFront++;
                if(stFltRstrtLoc.stQue.uiFront >= MAX_NUM_FLT_RSTRT)
                {
                    stFltRstrtLoc.stQue.uiFront = 0U;
                }

                stFltRstrtLoc.stQue.uiCntrAry[l_uiCntrTmp] = 0U;
            }
        }
    }
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
