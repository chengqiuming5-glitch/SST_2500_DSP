//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDataCalc.c
 * @brief
 * The source file of PFC measurement and control parameter calculation.
 *
 * Module      :                           \n
 * PfcDataCalc
 *
 * Unit        :                           \n
 * PfcDataCalc_PhaSeqChk                   \n
 * PfcDataCalc_SysPrmChg                   \n
 * PfcDataCalc_FrqChk                      \n
 * PfcDataCalc_PrmUpd                      \n
 * PfcDataCalc_PrmChgUpd                   \n
 * PfcDataCalc_PrmClr                      \n
 * PfcDataCalc_PwrCalc                     \n
 * PfcDataCalc_VCRmsCalc                   \n
 * PfcDataCalc_DcCptCalc                   \n
 * PfcDataCalc_FrqCalc                     \n
 * PfcDataCalc_Acm                         \n
 * PfcDataCalc_FrqCalc                     \n
 *
 *
 * Module Task :                           \n
 * v_PfcDataCalc_Init()                    \n
 * v_PfcDataCalc_Isr()                     \n
 * v_PfcDataCalc_1ms()                     \n
 * v_PfcDataCalc_10ms()                    \n
 *
 * Unit Task   :                           \n
 * v_PfcDataCalc_PhaSeqChk_Init()          \n
 * v_PfcDataCalc_PhaSeqChk_1ms()           \n
 * v_PfcDataCalc_FrqChk_Init()             \n
 * v_PfcDataCalc_FrqChk_10ms()             \n
 * v_PfcDataCalc_PrmChgUpd_Init()          \n
 * v_PfcDataCalc_PrmChgUpd_10ms()          \n
 * v_PfcDataCalc_PrmUpd_Isr()              \n
 * v_PfcDataCalc_PrmClr_1ms()              \n
 * v_PfcDataCalc_PwrCalc_Init()            \n
 * v_PfcDataCalc_PwrCalc_1ms()             \n
 * v_PfcDataCalc_RmsCalc_Init()            \n
 * v_PfcDataCalc_RmsCalc_1ms()             \n
 * v_PfcDataCalc_DcCptCalc_Init()          \n
 * v_PfcDataCalc_DcCptCalc_1ms()           \n
 * v_PfcDataCalc_FrqCalc_Init()            \n
 * v_PfcDataCalc_FrqCalc_1ms()             \n
 * v_PfcDataCalc_Acm_Init()                \n
 * v_PfcDataCalc_Acm_Isr()                 \n
 * v_PfcDataCalc_SysPrmChg_Init()          \n
 * v_PfcDataCalc_PrmUpd_Eep()              \n
 *
 * Sub Unit Task   :                       \n
 * v_PfcDataCalc_PhaSeqChk_3P_1ms()        \n
 * v_PfcDataCalc_FrqChk_OnGrid()           \n
 * v_PfcDataCalc_FrqChk_OffGrid()          \n
 * v_PfcDataCalc_PwrCalc_AVG_1ms()         \n
 * v_PfcDataCalc_PwrCalc_LPF_1ms()         \n
 * v_PfcDataCalc_RmsCalc_Volt_1ms()        \n
 * v_PfcDataCalc_RmsCalc_VoltLPF()         \n
 * v_PfcDataCalc_RmsCalc_Curr_1ms()        \n
 * v_PfcDataCalc_RmsCalc_CurrLPF()         \n
 * v_PfcDataCalc_RmsCalc_MaxMin()          \n
 * v_PfcDataCalc_DcCptCalc_Volt()          \n
 * v_PfcDataCalc_DcCptCalc_Curr()          \n
 * v_PfcDataCalc_FrqCalc_Avg_1ms()         \n
 * v_PfcDataCalc_Acm_Pwr_Isr()             \n
 * v_PfcDataCalc_Acm_VFPoint_Isr()         \n
 * v_PfcDataCalc_Acm_Rms3P_Isr()           \n
 * v_PfcDataCalc_Acm_Rms_Isr()             \n
 * v_PfcDataCalc_Acm_Avg3P_Isr()           \n
 * v_PfcDataCalc_PrmUpd_Rtd1_Eep()         \n
 * v_PfcDataCalc_PrmUpd_Frq_Eep()          \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/01/24
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD           \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2024/01/24  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcDataCalc.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_DATACALC_OUTP stPfcDataCalc;                         ///< PFC data calculation global struct

#if (1U == PFC_DATACALC_DBG)
ST_PFC_DATACALC_OUTP stPfcDataCalcDbg;                      ///< PFC data calculation debug global struct
#endif

static ST_PFC_DATACALC_LOC stPfcDataCalcLoc;                ///< PFC data calculation local struct

static ST_GRID_VOLT_CURR     stVgIg;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC measurement and control parameter calculation initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDataCalc_Init(void)
{
    v_PfcDataCalc_PhaSeqChk_Init();     ///< Grid sequence check function initialization task
    v_PfcDataCalc_FrqChk_Init();        ///< Grid frequency check function initialization task
    v_PfcDataCalc_PrmChgUpd_Init();     ///< Control parameter update function initialization task
    v_PfcDataCalc_SysPrmChg_Init();     ///< System parameter change function initialization task
    v_PfcDataCalc_PwrCalc_Init();       ///< Power correlation calculation Init task
    v_PfcDataCalc_RmsCalc_Init();       ///< Voltage&Current RMS calculation Init task
    v_PfcDataCalc_DcCptCalc_Init();     ///< DC component calculation Init task
    v_PfcDataCalc_FrqCalc_Init();       ///< Frequency calculation Init task
    v_PfcDataCalc_ADBiasCalc_Init();    ///< AD bias calculation Init task
    v_PfcDataCalc_Acm_Init();           ///< Sample value accumulation calculation ISR init task

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcDataCalc_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC measurement and control parameter calculation 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDataCalc_1ms(void)
{
    v_PfcDataCalc_PhaSeqChk_1ms();     ///< Grid sequence check function 1ms task
    v_PfcDataCalc_PwrCalc_1ms();       ///< Power calculation 1ms task
    v_PfcDataCalc_RmsCalc_1ms();       ///< Voltage&Current RMS calculation 1ms task
    v_PfcDataCalc_DcCptCalc_1ms();     ///< DC component calculation 1ms task
    v_PfcDataCalc_FrqCalc_1ms();       ///< Frequency calculation 1ms task
    v_PfcDataCalc_ADBiasCalc_1ms();    ///< AD bias calculation 1ms task
	
#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PfcDataCalc_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC measurement and control parameter calculation 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDataCalc_10ms(void)
{
    v_PfcDataCalc_FrqChk_10ms();       ///< Grid frequency check function 10ms task
    v_PfcDataCalc_PrmChgUpd_10ms();    ///<  Control parameter update after grid&control frequency change 10ms task

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_PfcDataCalc_10ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC measurement and control parameter calculation 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Isr, ".TI.ramfunc");
#endif
void v_PfcDataCalc_Isr(void)
{
    v_PfcDataCalc_Acm_Isr();    //6.86us   ///< Sample value accumulation calculation ISR task

    v_PfcDataCalc_PrmUpd_Isr();  //2us  ///< Control parameter update after grid&control frequency change Isr task

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr) 
    {
        printf("****SWIT DynamicTest: function v_PfcDataCalc_Isr() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid sequence check function initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PhaSeqChk_Init(void)
{
    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq      = GRID_POS_SEQ;    ///< Initialize to positive sequence
    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 0U;
    stPfcDataCalcLoc.uiCntrPosSeq               = 0U;
    stPfcDataCalcLoc.uiCntrNegSeq               = 0U;
    stPfcDataCalcLoc.uiCntrSeqChkTiOut          = 0U;

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeqChkOk = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk;
    stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeq      = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq;

    stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk    = stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeqChkOk;
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeq         = stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeq;
#else
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk;
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeq      = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid sequence check function 1ms task
 * @param [in]   stPfcStMac.unPFCSts.bit.uiMacSt
 * @param [in]   stCom.uiTypeGrid
 * @param [in]   stPfcDataCalcLoc.stMeasExt.siVgMinRmsLPF
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PhaSeqChk_1ms(void)
{
#if 3U == GRID_PHASE_NUMBER
    if(stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_CHK)    ///< PFC run state
    {
        if((0U != stComTbl.unWordPfcFlt3.bit.uiPasIsland) || \
           (0U != stComTbl.unWordPfcFlt2.bit.uiUV3rd) || \
           (0U != stComTbl.unWordPfcFlt2.bit.uiLvrtOvTi))
        {
            stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 0U;    ///< After island & under voltage & lvrt over time, check grid sequence again
        }

        if(stPfcDataCalcLoc.stMeasExt.ftVgMinRms > SEQCHK_VOLT_LIM)
        {
            if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)    ///< Phase full run mode
            {
                v_PfcDataCalc_PhaSeqChk_3P_1ms();
            }
            else
            {
                stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 1U;
            }
        }
        else
        {
            stPfcDataCalcLoc.uiCntrPosSeq = 0U;
            stPfcDataCalcLoc.uiCntrNegSeq = 0U;
            stPfcDataCalcLoc.uiCntrSeqChkTiOut = 0U;
        }
    }
    else
    {
        stPfcDataCalcLoc.uiCntrPosSeq = 0U;
        stPfcDataCalcLoc.uiCntrNegSeq = 0U;
        stPfcDataCalcLoc.uiCntrSeqChkTiOut = 0U;
    }
#else
    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 1U;
    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq      = GRID_POS_SEQ;    ///< Positive sequence
#endif

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk = stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeqChkOk;
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeq      = stPfcDataCalcDbg.stCtrlParm.uiFlgPhaSeq;
#else
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk;
    stPfcDataCalc.stCtrlParm.uiFlgPhaSeq      = stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq;
#endif
}
/*********************************************End**********************************************/

#if 3U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Grid sequence check function-Three phase system check 1ms task
 * @param [in]   stPfcDataCalcLoc.stMeasExt.siVgMinRmsLPF
 * @param [in]   stPfcDataCalcInp.ftSqPosVolt
 * @param [in]   stPfcDataCalcInp.ftSqNegVolt
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PhaSeqChk_3P_1ms(void)
{
    if(0U == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk)    ///< Grid sequence check no ok
    {
#if 1U == FLG_PFC_POWCTRL_EN
        if(stPfcPowCtrl.ftPosVoltSq > stPfcPowCtrl.ftNegVoltSq)        ///< Vdp is greater than Vdn
#else
        if(1U)    ///< To be modiefied
#endif
        {
            stPfcDataCalcLoc.uiCntrPosSeq++;
            stPfcDataCalcLoc.uiCntrNegSeq = 0U;
            if(stPfcDataCalcLoc.uiCntrPosSeq >= SEQCHK_OK_TIME)    ///< Last 1s
            {
                stPfcDataCalcLoc.uiCntrPosSeq = 0U;
                stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 1U;
            }
        }
        else        ///< Vdp is less than Vdn
        {
            stPfcDataCalcLoc.uiCntrNegSeq++;
            stPfcDataCalcLoc.uiCntrPosSeq = 0U;

            if(stPfcDataCalcLoc.uiCntrNegSeq >= SEQCHK_OK_TIME)    ///< Last 1s
            {
                stPfcDataCalcLoc.uiCntrNegSeq = 0U;
                stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 1U;

                if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
                {
                    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq = GRID_NEG_SEQ;
                }
                else
                {
                    stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq = GRID_POS_SEQ;
                }
            }
        }

        if(stPfcDataCalcLoc.uiCntrSeqChkTiOut++ >= SEQCHK_TIMEOUT_TIME)
        {
            stPfcDataCalcLoc.uiCntrPosSeq = 0U;
            stPfcDataCalcLoc.uiCntrNegSeq = 0U;
            stPfcDataCalcLoc.uiCntrSeqChkTiOut = 0U;
            if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
            {
                stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq = GRID_NEG_SEQ;
            }
            else
            {
                stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq = GRID_POS_SEQ;
            }
        }
    }
#if 1U == FLG_PFC_POWCTRL_EN
    else if(stPfcPowCtrl.ftPosVoltSq < stPfcPowCtrl.ftNegVoltSq)
#else
    else if(1U)    ///< To be modified
#endif
    {
        stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeqChkOk = 0U;
        stPfcDataCalcLoc.uiCntrPosSeq = 0U;
        stPfcDataCalcLoc.uiCntrNegSeq = 0U;
        stPfcDataCalcLoc.uiCntrSeqChkTiOut = 0U;
    }
    else
    {
        ///< Do nothing
    }
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid frequency check function initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqChk_Init(void)
{
    stPfcDataCalcLoc.ftErrEcapFrq = 0.0f;        ///< Initialize to 0.0f
    stPfcDataCalcLoc.ftErrFrq     = 0.0f;        ///< Initialize to 0.0f

    stPfcDataCalcLoc.uiFlgGridFrqChg = 0U;       ///< Initialize to 0U
    stPfcDataCalcLoc.uiFlgCtrlFrqChg = 0U;       ///< Initialize to 0U
    stPfcDataCalcLoc.uiCntrPllChk    = 0U;       ///< Initialize to 0U

    stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk      = 0U;       ///< Initialize to 0U
    stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr = 0U;       ///< Initialize to 0U

    /* Output parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stCtrlParm.uiFlgPllOk      = stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk;
    stPfcDataCalcDbg.stCtrlParm.uiFlgParmUpdIsr = stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr;

    stPfcDataCalc.stCtrlParm.uiFlgPllOk      = stPfcDataCalcDbg.stCtrlParm.uiFlgPllOk;
    stPfcDataCalc.stCtrlParm.uiFlgParmUpdIsr = stPfcDataCalcDbg.stCtrlParm.uiFlgParmUpdIsr;
#else
    stPfcDataCalc.stCtrlParm.uiFlgPllOk      = stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk;
    stPfcDataCalc.stCtrlParm.uiFlgParmUpdIsr = stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: Parameter update: grid frequency related such as PR; 10ms task
 * @param [in]   null
 * @param [in]   null
 * @param [in]   null
 * @param [in]   null
 * @param [in]   null
 * @param [out]  null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PrmChgUpd_GridFrq(void)
{
    v_PfcPowCtrl_Frq_PrmUpd(stPfcDataCalcLoc.stSysExt.ftSampTime, stPfcDataCalcLoc.ftWoUpd);                             ///< Grid frequency parameter update task
    //v_D2dPowCtrl_PRPrmUpd((stPfcDataCalcLoc.stSysExt.ftSampTime * RAT_D2D_SAMPTI_BASE_PFC), stPfcDataCalcLoc.ftWoUpd);   ///< D2D PR parameter update function
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid frequency check function 10ms task
 * @param [in]   stComIf.uiModPfcRun
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqChk_10ms(void)
{
    switch(stComIf.uiModPfcRun)
    {
       case CHG_ONGRID_MODE:
       case BIDIR_ONGRID_MODE:
           v_PfcDataCalc_FrqChk_OnGrid();     ///< On-Grid frequency check function
       break;

       case OFFGRID_MODE:
       case OPENLOOP_MODE:
           v_PfcDataCalc_FrqChk_OffGrid();    ///< Off-Grid frequency check function
       break;

       default:
           ///> No code
       break;
    }

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stCtrlParm.uiFlgPllOk = stPfcDataCalcDbg.stCtrlParm.uiFlgPllOk;
#else
    stPfcDataCalc.stCtrlParm.uiFlgPllOk = stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: On-Grid frequency check function 10ms task
 * @param [in]   stPfcDataCalcLoc.stMeasExt.siFrqCapAvgLpf
 * @param [in]   stPfcDataCalcLoc.stMeasExt.uiFrqPllLPF
 * @param [in]   stPfcGridCtrl.stVrt.uiFlgHvrt
 * @param [in]   stPfcGridCtrl.stVrt.uiFlgLvrt
 * @param [in]   stPfcDataCalcLoc.uiFlgCtrlFrqChg
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgCtrlParmUpd
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqChk_OnGrid(void)
{
    stPfcDataCalcLoc.ftErrEcapFrq = fabsf(stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF - stPfcDataCalcLoc.ftFrqEcapOld);
    if(stPfcDataCalcLoc.ftErrEcapFrq > CAP_FRQ_UPD_ERR)    ///< CAP frequency error is greater than CAP_FRQ_UPD_ERR
    {
        stPfcDataCalcLoc.uiFlgGridFrqChg = 1U;
    }

    v_PfcDataCalc_FrqChk_OnGrid_Pll();    ///< PLL frequency check function
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub-Unit function: PLL frequency check function 10ms task
 * @param [in]   stPfcDataCalcLoc.uiErrFrq
 * @param [in]   stPfcDataCalcLoc.stMeasExt.siVgMinRmsLPF
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqChk_OnGrid_Pll(void)
{
    float32 l_ftVrmsMax = 0.0f;
    float32 l_ftVrmsMin = 0.0f;

    stPfcDataCalcLoc.ftErrFrq = fabsf(stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF - stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF);    ///< PLL frequency error absolute value

    if(0U == stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk)
    {
        l_ftVrmsMax = PLL_OK_VOLT_ERR_COEFF_MAX * stPfcDataCalcLoc.stMeasExt.ftVgAvgRms;    ///< Max voltage RMS
        l_ftVrmsMin = PLL_OK_VOLT_ERR_COEFF_MIN * stPfcDataCalcLoc.stMeasExt.ftVgAvgRms;    ///< Min voltage RMS

        if((stPfcDataCalcLoc.stMeasExt.ftVgMinRms > FRQCALC_VOLT_LIM) && \
           (stPfcDataCalcLoc.ftErrFrq < PLL_OK_FRQ_ERR) && \
           (stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF > l_ftVrmsMin) && (stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF < l_ftVrmsMax))
        {
            stPfcDataCalcLoc.uiCntrPllChk++;
            if(stPfcDataCalcLoc.uiCntrPllChk > FRQ_CHK_OK_TIME)    ///< Last 500ms
            {
                stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk = 1U;
                stPfcDataCalcLoc.uiCntrPllChk         = 0U;
            }
        }
        else
        {
            stPfcDataCalcLoc.uiCntrPllChk = 0U;
        }
    }
    else
    {
        if(stPfcDataCalcLoc.ftErrFrq > PLL_FLT_FRQ_ERR)    ///< PLL frequency error absolute value is more than 0.3f
        {
            stPfcDataCalcLoc.uiCntrPllChk++;
            if(stPfcDataCalcLoc.uiCntrPllChk > FRQ_CHK_NO_TIME)    ///< Last 500ms
            {
                stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk = 0U;
                stPfcDataCalcLoc.uiCntrPllChk         = 0U;
            }
        }
        else
        {
            stPfcDataCalcLoc.uiCntrPllChk = 0U;
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: On-Grid frequency check function; 10ms task
 * @param [in]   stPfcDataCalcLoc.stMeasExt.uiFrqPllLPF
 * @param [in]   stPfcDataCalcLoc.uiFlgCtrlFrqChg
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgCtrlParmUpd
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqChk_OffGrid(void)
{
    stPfcDataCalcLoc.stCtrlExt.uiFlgPllOk = 1U;    ///< PLL frequency Ok flag

    stPfcDataCalcLoc.ftErrEcapFrq = fabsf(stCom.ftFrqAcV2LReq - stPfcDataCalcLoc.ftFrqEcapOld);
    if(stPfcDataCalcLoc.ftErrEcapFrq > 0.01f)
    {
        stPfcDataCalcLoc.uiFlgGridFrqChg = 1U;
    }
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Control parameter update function initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PrmChgUpd_Init(void)
{
    float32 l_ftDataTmp = 0.0f;

    stPfcDataCalcLoc.ftFrqUpdRef  = RATED_AC_FRQ;                        ///< Initialize to rated frequency
    stPfcDataCalcLoc.ftFrqEcapOld = stPfcDataCalcLoc.ftFrqUpdRef;
    stPfcDataCalcLoc.uiFrqCtrl    = FRQ_PFC_CTRL;
    stPfcDataCalcLoc.ftWoUpd      = PI_2_CONST * RATED_AC_FRQ;

    l_ftDataTmp = ((float32)stPfcDataCalcLoc.uiFrqCtrl / stPfcDataCalcLoc.ftFrqUpdRef) + 0.5f;
    stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew = (Uint16)l_ftDataTmp;       ///< Repetitive control sample points
    vFcn_UiUpDwnLim(&stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew, MAX_REPEAT_NUM, MIN_REPEAT_NUM);
    stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew = stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew >> PFC_RMS_POINT_SHIFT_NUM;       ///< RMS control sample points
    vFcn_UiUpDwnLim(&stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew, MAX_RMS_NUM, MIN_RMS_NUM);

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stCtrlParm.uiRepet_PiontsNew = stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew;
    stPfcDataCalcDbg.stCtrlParm.uiRms_PiontsNew   = stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew;

    stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew = stPfcDataCalcDbg.stCtrlParm.uiRepet_PiontsNew;
    stPfcDataCalc.stCtrlParm.uiRms_PiontsNew   = stPfcDataCalcDbg.stCtrlParm.uiRms_PiontsNew;
#else
    stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew = stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew;
    stPfcDataCalc.stCtrlParm.uiRms_PiontsNew   = stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Control parameter update after grid&control frequency change 10ms task
 * @param [in]   stComTbl.unWordPfcCtrlCmd1.bit.uiFrqUpd
 * @param [in]   stComIf.uiModPfcRun
 * @param [in]   stComTbl.stPrmPfcRtd1.ftFrqGrid
 * @param [in]   stPfcDataCalcLoc.stCtrlExt.uiFlgCtrlParmUpd
 * @param [in]   null
 * @param [out]  stPfcDataCalcLoc.ftWo
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew
 * @param [out]  stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PrmChgUpd_10ms(void)
{
    float32 l_ftDataTmp = 0.0f;

    if(((1U == stPfcDataCalcLoc.uiFlgGridFrqChg) || (1U == stPfcDataCalcLoc.uiFlgCtrlFrqChg)) \
       && (0U == stPfcGridCtrl.stVrt.uiFlgHvrt) && (0U == stPfcGridCtrl.stVrt.uiFlgLvrt) \
       && (0U == stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr))
    {
        if((CHG_ONGRID_MODE == stComIf.uiModPfcRun) || (BIDIR_ONGRID_MODE == stComIf.uiModPfcRun))
        {
            stPfcDataCalcLoc.ftFrqUpdRef = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;    ///< CAP frequency
        }
        else if(OFFGRID_MODE == stComIf.uiModPfcRun)
        {
            stPfcDataCalcLoc.ftFrqUpdRef = stCom.ftFrqAcV2LReq;    ///< V2L frequency request
        }
        else
        {
            stPfcDataCalcLoc.ftFrqUpdRef = stComTbl.stPrmPfcRtd1.ftFrqGrid;    ///< Rated frequency
        }

        l_ftDataTmp = ((float32)stPfcDataCalcLoc.uiFrqCtrl / stPfcDataCalcLoc.ftFrqUpdRef) + 0.5f;
        stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew = (Uint16)l_ftDataTmp;       ///< Repetitive control sample points
        vFcn_UiUpDwnLim(&stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew, MAX_REPEAT_NUM, MIN_REPEAT_NUM);
        stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew = stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew >> PFC_RMS_POINT_SHIFT_NUM;       ///< RMS control sample points
        vFcn_UiUpDwnLim(&stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew, MAX_RMS_NUM, MIN_RMS_NUM);
        stPfcDataCalcLoc.ftWoUpd = PI_2_CONST * stPfcDataCalcLoc.ftFrqUpdRef;

        /* Parameter update */
        v_PfcDataCalc_PrmChgUpd_GridFrq();

        stPfcDataCalcLoc.ftFrqEcapOld              = stPfcDataCalcLoc.ftFrqUpdRef;
        stPfcDataCalcLoc.uiFlgCtrlFrqChg           = 0U;
        stPfcDataCalcLoc.uiFlgGridFrqChg           = 0U;
        stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr = 1U;

        /* Global parameter */
#if 1U == PFC_DATACALC_DBG
        stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew = stPfcDataCalcDbg.stCtrlParm.uiRepet_PiontsNew;
        stPfcDataCalc.stCtrlParm.uiRms_PiontsNew   = stPfcDataCalcDbg.stCtrlParm.uiRms_PiontsNew;
        stPfcDataCalc.stCtrlParm.uiFlgParmUpdIsr   = stPfcDataCalcDbg.stCtrlParm.uiFlgParmUpdIsr;
#else
        stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew = stPfcDataCalcLoc.stCtrlExt.uiRepet_PiontsNew;
        stPfcDataCalc.stCtrlParm.uiRms_PiontsNew   = stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew;
        stPfcDataCalc.stCtrlParm.uiFlgParmUpdIsr   = stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr;
#endif		
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: System parameter change function initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_SysPrmChg_Init(void)
{
    ///< First power on update parameter
    stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr = 1.0f / RATED_AC_VOLT_RMS;               ///< Reciprocal of rated grid voltage
    stPfcDataCalcLoc.stSysExt.ftPwrRtdRecpr  = 1.0f / POW_AC_RTD;                      ///< Reciprocal of rated active power
    stPfcDataCalcLoc.stSysExt.uiPerdPwmABC   = PERIOD_PFC_PWM;                         ///< Phase A/B/C PWM timer period
    stPfcDataCalcLoc.stSysExt.uiPerdPwmN     = PERIOD_BAL_PWM;                         ///< Phase N PWM timer period
    stPfcDataCalcLoc.stSysExt.ftSampTime     = PERD_PFC_CTRL;                          ///< Control/Sample period
    stPfcDataCalcLoc.stSysExt.ftRadFrqRtd    = PI_2_CONST * RATED_AC_FRQ;              ///< Rated radian frequncy
    stPfcDataCalcLoc.stSysExt.ftFrqCoeff = (float32)FRQ_PFC_CTRL / PI_2_CONST;
    stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta = PI_2_CONST * RATED_AC_FRQ * stPfcDataCalcLoc.stSysExt.ftSampTime;

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stSysParm.ftVoltRtdRecpr   = stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
    stPfcDataCalcDbg.stSysParm.ftPwrRtdRecpr    = stPfcDataCalcLoc.stSysExt.ftPwrRtdRecpr;
    stPfcDataCalcDbg.stSysParm.uiPerdPwmABC     = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    stPfcDataCalcDbg.stSysParm.uiPerdPwmN       = stPfcDataCalcLoc.stSysExt.uiPerdPwmN;
    stPfcDataCalcDbg.stSysParm.ftSampTime       = stPfcDataCalcLoc.stSysExt.ftSampTime;
    stPfcDataCalcDbg.stSysParm.ftRadFrqRtd      = stPfcDataCalcLoc.stSysExt.ftRadFrqRtd;
    stPfcDataCalcDbg.stSysParm.ftFrqCoeff       = stPfcDataCalcLoc.stSysExt.ftFrqCoeff;
    stPfcDataCalcDbg.stSysParm.ftPLL_DeltaTheta = stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta;

    stPfcDataCalc.stSysParm.ftVoltRtdRecpr   = stPfcDataCalcDbg.stSysParm.ftVoltRtdRecpr;
    stPfcDataCalc.stSysParm.ftPwrRtdRecpr    = stPfcDataCalcDbg.stSysParm.ftPwrRtdRecpr;
    stPfcDataCalc.stSysParm.uiPerdPwmABC     = stPfcDataCalcDbg.stSysParm.uiPerdPwmABC;
    stPfcDataCalc.stSysParm.uiPerdPwmN       = stPfcDataCalcDbg.stSysParm.uiPerdPwmN;
    stPfcDataCalc.stSysParm.ftSampTime       = stPfcDataCalcDbg.stSysParm.ftSampTime;
    stPfcDataCalc.stSysParm.ftRadFrqRtd      = stPfcDataCalcDbg.stSysParm.ftRadFrqRtd;
    stPfcDataCalc.stSysParm.ftFrqCoeff       = stPfcDataCalcDbg.stSysParm.ftFrqCoeff;
    stPfcDataCalc.stSysParm.ftPLL_DeltaTheta = stPfcDataCalcDbg.stSysParm.ftPLL_DeltaTheta;
#else
    stPfcDataCalc.stSysParm.ftVoltRtdRecpr   = stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
    stPfcDataCalc.stSysParm.ftPwrRtdRecpr    = stPfcDataCalcLoc.stSysExt.ftPwrRtdRecpr;
    stPfcDataCalc.stSysParm.uiPerdPwmABC     = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    stPfcDataCalc.stSysParm.uiPerdPwmN       = stPfcDataCalcLoc.stSysExt.uiPerdPwmN;
    stPfcDataCalc.stSysParm.ftSampTime       = stPfcDataCalcLoc.stSysExt.ftSampTime;
    stPfcDataCalc.stSysParm.ftRadFrqRtd      = stPfcDataCalcLoc.stSysExt.ftRadFrqRtd;
    stPfcDataCalc.stSysParm.ftFrqCoeff       = stPfcDataCalcLoc.stSysExt.ftFrqCoeff;
    stPfcDataCalc.stSysParm.ftPLL_DeltaTheta = stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Parameter update Eeprom task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDataCalc_PrmUpd_Eep(void)
{
    v_PfcDataCalc_PrmUpd_Rtd1_Eep();        ///< System parameter change-Rated parameter1 update Eeprom task
    if((STOP_CMD == stComIf.uiCmdRun) && (stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_STB))    ///< PFC no running
    {
        v_PfcDataCalc_PrmUpd_Frq_Eep();     ///< System parameter change-Control frequency parameter update Eeprom task
    }

    /* RoCoF phase flag update */
#if 1U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stRoCoF.uiFlgPha = ROCOF_FLAG_PHASE_A;    ///< Set to phase A flag
#else
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)         ///< Phase full run mode
    {
        stPfcDataCalcLoc.stRoCoF.uiFlgPha = ROCOF_FLAG_PHASE_A;    ///< Set to phase A flag
    }
    else
    {
        if(TYPE_GRID_BN == stCom.uiTypeGrid)
        {
            stPfcDataCalcLoc.stRoCoF.uiFlgPha = ROCOF_FLAG_PHASE_B;    ///< Set to phase B flag
        }
    #if 3U == GRID_PHASE_NUMBER
        else if(TYPE_GRID_CN == stCom.uiTypeGrid)
        {
            stPfcDataCalcLoc.stRoCoF.uiFlgPha = ROCOF_FLAG_PHASE_C;    ///< Set to phase C flag
        }
    #endif /* 3U == GRID_PHASE_NUMBER */
        else
        {
            stPfcDataCalcLoc.stRoCoF.uiFlgPha = ROCOF_FLAG_PHASE_A;    ///< Set to phase C flag
        }

    }
#endif /* GRID_PHASE_NUMBER */
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: System parameter change-Rated parameter1 update Eeprom task
 * @param [in]   stComTbl.stPrmPfcRtd1
 * @param [out]  stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PrmUpd_Rtd1_Eep(void)
{
    if(stComTbl.stPrmPfcRtd1.ftVoltGrid > 1.0f)
    {
        stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr = 1.0f / stComTbl.stPrmPfcRtd1.ftVoltGrid;    ///< Reciprocal of rated grid voltage
    }
    if(stComTbl.stPrmPfcRtd1.ftPowRtd > 1.0f)
    {
        stPfcDataCalcLoc.stSysExt.ftPwrRtdRecpr = 1.0f / stComTbl.stPrmPfcRtd1.ftPowRtd;       ///< Reciprocal of rated active power
    }

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stSysParm.ftVoltRtdRecpr = stPfcDataCalcDbg.stSysParm.ftVoltRtdRecpr;
    stPfcDataCalc.stSysParm.ftPwrRtdRecpr = stPfcDataCalcDbg.stSysParm.ftPwrRtdRecpr;
#else
    stPfcDataCalc.stSysParm.ftVoltRtdRecpr = stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr; ///<no use
    stPfcDataCalc.stSysParm.ftPwrRtdRecpr = stPfcDataCalcLoc.stSysExt.ftPwrRtdRecpr;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: System parameter change-Control frequency parameter update Eeprom task
 * @param [in]   stComTbl.stPrmPfcHw
 * @param [in]   null
 * @param [out]  stPfcDataCalcLoc.stSysExt.uiPerdPwmABC
 * @param [out]  stPfcDataCalcLoc.stSysExt.uiPerdPwmN
 * @param [out]  stPfcDataCalcLoc.stSysExt.ftSampTime
 * @param [out]  stPfcDataCalcLoc.stSysExt.ftRadFrqRtd
 * @param [out]  stPfcDataCalcLoc.stSysExt.ftFrqCoeff
 * @param [out]  stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PrmUpd_Frq_Eep(void)
{
    Uint32 l_uLDataTmp   = 0UL;
    Uint16 l_uiDeadTiTmp = 0U;

    /* PFC ABC phase MOS frequency */
    vFcn_UiUpDwnLim(&stComTbl.stPrmPfcHw.uiSwtFrqIabc, FRQ_PFC_SWITCH_MAX, FRQ_PFC_SWITCH_MIN);
    l_uLDataTmp = (Uint32)stComTbl.stPrmPfcHw.uiSwtFrqIabc;
    stPfcDataCalcLoc.stSysExt.uiPerdPwmABC = (Uint16)((FRQ_PWMCLK / l_uLDataTmp) >> 1);
    /* PFC N bridge MOS frequency */
    UP_DOWN_LIMIT(stComTbl.stPrmPfcHw.ulSwtFrqIn, FRQ_BAL_SWITCH_MAX, FRQ_BAL_SWITCH_MIN);
#if 2U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stSysExt.uiPerdPwmN = (Uint16)(COEFF_ECAP / stComTbl.stPrmPfcHw.ulSwtFrqIn);
#else
    stPfcDataCalcLoc.stSysExt.uiPerdPwmN = (Uint16)((FRQ_PWMCLK / stComTbl.stPrmPfcHw.ulSwtFrqIn) >> 1);
#endif
    /* Dead zone time */
    vFcn_UiUpDwnLim(&stComTbl.stPrmPfcHw.uiDeadTiIabc, PFC_PWM_DEADTIME_MAX, PFC_PWM_DEADTIME_MIN);
    l_uiDeadTiTmp = stComTbl.stPrmPfcHw.uiDeadTiIabc / 10U;
#ifndef _SIMULATION_NO_DSP_
    #if 1U == GRID_PHASE_NUMBER
    /* Fast bridge ePWM module update */
    PFC_FAST_PWM.TBCTR = 0U;
    PFC_FAST_PWM.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PFC_FAST_PWM.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PFC_FAST_PWM.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Slow bridge ePWM module update */
    PFC_SLOW_PWM.TBCTR = 0U;
    PFC_SLOW_PWM.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PFC_SLOW_PWM.DBRED.bit.DBRED = l_uiDeadTiTmp<<1U;
    PFC_SLOW_PWM.DBFED.bit.DBFED = l_uiDeadTiTmp<<1U;
    /* ISR trigger ePWM module update */
    PFC_ISR_PWM_REG.TBCTR = 0U;
    PFC_ISR_PWM_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;

    #elif 2U == GRID_PHASE_NUMBER
    /* Phase1 A1 ePWM module update */
    PWM_L1A1_REG.TBCTR = 0U;
    PWM_L1A1_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L1A1_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L1A1_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase1 A2 ePWM module update */
    PWM_L1A2_REG.TBCTR = 0U;
    PWM_L1A2_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L1A2_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L1A2_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase1 B1 ePWM module update */
    PWM_L1B1_REG.TBCTR = 0U;
    PWM_L1B1_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L1B1_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L1B1_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase1 B2 ePWM module update */
    PWM_L1B2_REG.TBCTR = 0U;
    PWM_L1B2_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L1B2_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L1B2_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase2 A1 ePWM module update */
    PWM_L2A1_REG.TBCTR = 0U;
    PWM_L2A1_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L2A1_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L2A1_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase2 A2 ePWM module update */
    PWM_L2A2_REG.TBCTR = 0U;
    PWM_L2A2_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L2A2_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L2A2_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase2 B1 ePWM module update */
    PWM_L2B1_REG.TBCTR = 0U;
    PWM_L2B1_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L2B1_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L2B1_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase2 B2 ePWM module update */
    PWM_L2B2_REG.TBCTR = 0U;
    PWM_L2B2_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_L2B2_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_L2B2_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Balance bridge period register update */
    PWM_BAL_PRD_REG(stPfcDataCalcLoc.stSysExt.uiPerdPwmN);

    #elif 3U == GRID_PHASE_NUMBER
    /* Phase A ePWM module update */
    PWM_A_REG.TBCTR = 0U;
    PWM_A_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_A_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_A_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase B ePWM module update */
    PWM_B_REG.TBCTR = 0U;
    PWM_B_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_B_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_B_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    /* Phase C ePWM module update */
    PWM_C_REG.TBCTR = 0U;
    PWM_C_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    PWM_C_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_C_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;

    vFcn_UiUpDwnLim(&stComTbl.stPrmPfcHw.uiDeadTiIn, PFC_PWM_BAL_DEADTIME_MAX, PFC_PWM_BAL_DEADTIME_MIN);
    l_uiDeadTiTmp = stComTbl.stPrmPfcHw.uiDeadTiIn / 10U;
    /* Balance bridge ePWM module update */
    PWM_N_REG.TBCTR = 0U;
    PWM_N_REG.TBPRD = stPfcDataCalcLoc.stSysExt.uiPerdPwmN;
    PWM_N_REG.DBRED.bit.DBRED = l_uiDeadTiTmp;
    PWM_N_REG.DBFED.bit.DBFED = l_uiDeadTiTmp;
    #endif
#endif

    /* Control sample period */
    stPfcDataCalcLoc.uiFrqCtrl = stComTbl.stPrmPfcHw.uiSwtFrqIabc / PFC_CTRL_INTL;
    stPfcDataCalcLoc.stSysExt.ftSampTime  = 1.0f / (float32)stPfcDataCalcLoc.uiFrqCtrl;
    /* Rated radian frequency */
    stPfcDataCalcLoc.stSysExt.ftRadFrqRtd = PI_2_CONST * stComTbl.stPrmPfcRtd1.ftFrqGrid;
    stPfcDataCalcLoc.stSysExt.ftFrqCoeff = (float32)stPfcDataCalcLoc.uiFrqCtrl / PI_2_CONST;
    stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta = PI_2_CONST * stComTbl.stPrmPfcRtd1.ftFrqGrid * stPfcDataCalcLoc.stSysExt.ftSampTime;

    stPfcDataCalcLoc.uiFlgCtrlFrqChg = 1U;   ///< Control frequency update flag set

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stSysParm.uiPerdPwmABC = stPfcDataCalcDbg.stSysParm.uiPerdPwmABC;
    stPfcDataCalc.stSysParm.uiPerdPwmN = stPfcDataCalcDbg.stSysParm.uiPerdPwmN;
    stPfcDataCalc.stSysParm.ftSampTime = stPfcDataCalcDbg.stSysParm.ftSampTime;
    stPfcDataCalc.stSysParm.ftRadFrqRtd = stPfcDataCalcDbg.stSysParm.ftRadFrqRtd;
    stPfcDataCalc.stSysParm.ftFrqCoeff = stPfcDataCalcDbg.stSysParm.ftFrqCoeff;
    stPfcDataCalc.stSysParm.ftPLL_DeltaTheta = stPfcDataCalcDbg.stSysParm.ftPLL_DeltaTheta;
#else
    stPfcDataCalc.stSysParm.uiPerdPwmABC = stPfcDataCalcLoc.stSysExt.uiPerdPwmABC;
    stPfcDataCalc.stSysParm.uiPerdPwmN   = stPfcDataCalcLoc.stSysExt.uiPerdPwmN;
    stPfcDataCalc.stSysParm.ftSampTime   = stPfcDataCalcLoc.stSysExt.ftSampTime;
    stPfcDataCalc.stSysParm.ftRadFrqRtd  = stPfcDataCalcLoc.stSysExt.ftRadFrqRtd;
    stPfcDataCalc.stSysParm.ftFrqCoeff   = stPfcDataCalcLoc.stSysExt.ftFrqCoeff;
    stPfcDataCalc.stSysParm.ftPLL_DeltaTheta = stPfcDataCalcLoc.stSysExt.ftPLL_DeltaTheta;
#endif
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Control parameter update after grid&control frequency change Isr task
 * @param [in]   stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr
 * @param [in]   stPfcDataCalc.stCtrlParm.uiRms_PiontsNew
 * @param [in]   stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_PrmUpd_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_PrmUpd_Isr(void)
{
    if(1U == stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr)
    {
#if 1U == FLG_PFC_POWCTRL_EN
		/* Grid frequency parameter copy */
        v_PfcPowCtrl_Frq_PrmCopy_Isr();
#endif
        stPfcDataCalcLoc.stCtrlExt.uiFlgParmUpdIsr = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Power correlation calculation Init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PwrCalc_Init(void)
{
    stPfcDataCalcLoc.stMeasExt.ftVbusPosLPF       = 0.0f;       	///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVbusLPF          = 0.0f;       	///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.siVbus10Times      = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siVbusPos10Times   = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.uiVbusMid10Times   = 0U;         	///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.ftIdRefLPF         = 0.0f;       	///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.siPaAvg            = 0;         	 	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siPbAvg            = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siPcAvg            = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQaAvg            = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQbAvg            = 0;          	///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQcAvg            = 0;          	///< Initialize to 0

    stPfcDataCalcLoc.stMeasExt.slActvPower 		  = 0L;             ///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.slRePower   		  = 0L;             ///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.slAprtPower 		  = 0L;             ///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.ftPf        		  = 1.0f;           ///< PF initialize to 1.0f

    stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF 		  = RATED_AC_FRQ;   ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.siPaAvgLPF  		  = 0;              ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siPbAvgLPF  		  = 0;              ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siPcAvgLPF  		  = 0;              ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQaAvgLPF  		  = 0;              ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQbAvgLPF  		  = 0;              ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siQcAvgLPF  		  = 0;              ///< Initialize to 0

    stPfcDataCalcLoc.stMeasExt.slActvPowerLPF     = 0L;        		///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.slRePowerLPF       = 0L;        		///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF     = 0L;        		///< Initialize to 0L
    stPfcDataCalcLoc.stMeasExt.ftPfLPF            = 1.0f;      		///< PF LPF initialize to 1.0f
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF    = 0.0f;      		///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF    = 0.0f;      		///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF    = 0.0f;      		///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftAprtPwr1PLPFMax  = 0.0f;      		///< Initialize to 0.0f

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stMeasParm.ftVbusPosLPF      = stPfcDataCalcLoc.stMeasExt.ftVbusPosLPF;
    stPfcDataCalcDbg.stMeasParm.ftVbusLPF         = stPfcDataCalcLoc.stMeasExt.ftVbusLPF;
    stPfcDataCalcDbg.stMeasParm.siVbus10Times     = stPfcDataCalcLoc.stMeasExt.siVbus10Times;
    stPfcDataCalcDbg.stMeasParm.siVbusPos10Times  = stPfcDataCalcLoc.stMeasExt.siVbusPos10Times;
    stPfcDataCalcDbg.stMeasParm.uiVbusMid10Times  = stPfcDataCalcLoc.stMeasExt.uiVbusMid10Times;
    stPfcDataCalcDbg.stMeasParm.ftIdRefLPF        = stPfcDataCalcLoc.stMeasExt.ftIdRefLPF;
    stPfcDataCalcDbg.stMeasParm.siPaAvg           = stPfcDataCalcLoc.stMeasExt.siPaAvg;
    stPfcDataCalcDbg.stMeasParm.siPbAvg           = stPfcDataCalcLoc.stMeasExt.siPbAvg;
    stPfcDataCalcDbg.stMeasParm.siPcAvg           = stPfcDataCalcLoc.stMeasExt.siPcAvg;
    stPfcDataCalcDbg.stMeasParm.siQaAvg           = stPfcDataCalcLoc.stMeasExt.siQaAvg;
    stPfcDataCalcDbg.stMeasParm.siQbAvg           = stPfcDataCalcLoc.stMeasExt.siQbAvg;
    stPfcDataCalcDbg.stMeasParm.siQcAvg           = stPfcDataCalcLoc.stMeasExt.siQcAvg;
    stPfcDataCalcDbg.stMeasParm.slActvPower 	  = stPfcDataCalcLoc.stMeasExt.slActvPower;
    stPfcDataCalcDbg.stMeasParm.slRePower   	  = stPfcDataCalcLoc.stMeasExt.slRePower;
    stPfcDataCalcDbg.stMeasParm.slAprtPower 	  = stPfcDataCalcLoc.stMeasExt.slAprtPower;
    stPfcDataCalcDbg.stMeasParm.ftPf        	  = stPfcDataCalcLoc.stMeasExt.ftPf;
    stPfcDataCalcDbg.stMeasParm.ftFrqPllLPF 	  = stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF;
    stPfcDataCalcDbg.stMeasParm.siPaAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siPaAvgLPF;
    stPfcDataCalcDbg.stMeasParm.siPbAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siPbAvgLPF;
    stPfcDataCalcDbg.stMeasParm.siPcAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siPcAvgLPF;
    stPfcDataCalcDbg.stMeasParm.siQaAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siQaAvgLPF;
    stPfcDataCalcDbg.stMeasParm.siQbAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siQbAvgLPF;
    stPfcDataCalcDbg.stMeasParm.siQcAvgLPF  	  = stPfcDataCalcLoc.stMeasExt.siQcAvgLPF;
    stPfcDataCalcDbg.stMeasParm.slActvPowerLPF 	  = stPfcDataCalcLoc.stMeasExt.slActvPowerLPF;
    stPfcDataCalcDbg.stMeasParm.slRePowerLPF   	  = stPfcDataCalcLoc.stMeasExt.slRePowerLPF;
    stPfcDataCalcDbg.stMeasParm.slAprtPowerLPF 	  = stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF;
    stPfcDataCalcDbg.stMeasParm.ftPfLPF        	  = stPfcDataCalcLoc.stMeasExt.ftPfLPF;
    stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhALPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF;
    stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhBLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF;
    stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhCLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF;
    stPfcDataCalcDbg.stMeasParm.ftAprtPwr1PLPFMax = stPfcDataCalcLoc.stMeasExt.ftAprtPwr1PLPFMax;

    stPfcDataCalc.stMeasParm.ftVbusPosLPF      = stPfcDataCalcDbg.stMeasParm.ftVbusPosLPF;
    stPfcDataCalc.stMeasParm.ftVbusLPF         = stPfcDataCalcDbg.stMeasParm.ftVbusLPF;
    stPfcDataCalc.stMeasParm.siVbus10Times     = stPfcDataCalcDbg.stMeasParm.siVbus10Times;
    stPfcDataCalc.stMeasParm.siVbusPos10Times  = stPfcDataCalcDbg.stMeasParm.siVbusPos10Times;
    stPfcDataCalc.stMeasParm.uiVbusMid10Times  = stPfcDataCalcDbg.stMeasParm.uiVbusMid10Times;
    stPfcDataCalc.stMeasParm.ftIdRefLPF        = stPfcDataCalcDbg.stMeasParm.ftIdRefLPF;
    stPfcDataCalc.stMeasParm.siPaAvg           = stPfcDataCalcDbg.stMeasParm.siPaAvg;
    stPfcDataCalc.stMeasParm.siPbAvg           = stPfcDataCalcDbg.stMeasParm.siPbAvg;
    stPfcDataCalc.stMeasParm.siPcAvg           = stPfcDataCalcDbg.stMeasParm.siPcAvg;
    stPfcDataCalc.stMeasParm.siQaAvg           = stPfcDataCalcDbg.stMeasParm.siQaAvg;
    stPfcDataCalc.stMeasParm.siQbAvg           = stPfcDataCalcDbg.stMeasParm.siQbAvg;
    stPfcDataCalc.stMeasParm.siQcAvg           = stPfcDataCalcDbg.stMeasParm.siQcAvg;
    stPfcDataCalc.stMeasParm.slActvPower 	   = stPfcDataCalcDbg.stMeasParm.slActvPower;
    stPfcDataCalc.stMeasParm.slRePower   	   = stPfcDataCalcDbg.stMeasParm.slRePower;
    stPfcDataCalc.stMeasParm.slAprtPower 	   = stPfcDataCalcDbg.stMeasParm.slAprtPower;
    stPfcDataCalc.stMeasParm.ftPf        	   = stPfcDataCalcDbg.stMeasParm.ftPf;
    stPfcDataCalc.stMeasParm.ftFrqPllLPF 	   = stPfcDataCalcDbg.stMeasParm.ftFrqPllLPF;
    stPfcDataCalc.stMeasParm.siPaAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siPaAvgLPF;
    stPfcDataCalc.stMeasParm.siPbAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siPbAvgLPF;
    stPfcDataCalc.stMeasParm.siPcAvgLPF    	   = stPfcDataCalcDbg.stMeasParm.siPcAvgLPF;
    stPfcDataCalc.stMeasParm.siQaAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQaAvgLPF;
    stPfcDataCalc.stMeasParm.siQbAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQbAvgLPF;
    stPfcDataCalc.stMeasParm.siQcAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQcAvgLPF;
    stPfcDataCalc.stMeasParm.slActvPowerLPF    = stPfcDataCalcDbg.stMeasParm.slActvPowerLPF;
    stPfcDataCalc.stMeasParm.slRePowerLPF      = stPfcDataCalcDbg.stMeasParm.slRePowerLPF;
    stPfcDataCalc.stMeasParm.slAprtPowerLPF    = stPfcDataCalcDbg.stMeasParm.slAprtPowerLPF;
    stPfcDataCalc.stMeasParm.ftPfLPF           = stPfcDataCalcDbg.stMeasParm.ftPfLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhALPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhALPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhBLPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhBLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhCLPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhCLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax = stPfcDataCalcDbg.stMeasParm.ftAprtPwr1PLPFMax;
#else
    stPfcDataCalc.stMeasParm.ftVbusPosLPF      = stPfcDataCalcLoc.stMeasExt.ftVbusPosLPF;
    stPfcDataCalc.stMeasParm.ftVbusLPF         = stPfcDataCalcLoc.stMeasExt.ftVbusLPF;
    stPfcDataCalc.stMeasParm.siVbus10Times     = stPfcDataCalcLoc.stMeasExt.siVbus10Times;
    stPfcDataCalc.stMeasParm.siVbusPos10Times  = stPfcDataCalcLoc.stMeasExt.siVbusPos10Times;
    stPfcDataCalc.stMeasParm.uiVbusMid10Times  = stPfcDataCalcLoc.stMeasExt.uiVbusMid10Times;
    stPfcDataCalc.stMeasParm.ftIdRefLPF        = stPfcDataCalcLoc.stMeasExt.ftIdRefLPF;
    stPfcDataCalc.stMeasParm.siPaAvg           = stPfcDataCalcLoc.stMeasExt.siPaAvg;
    stPfcDataCalc.stMeasParm.siPbAvg           = stPfcDataCalcLoc.stMeasExt.siPbAvg;
    stPfcDataCalc.stMeasParm.siPcAvg           = stPfcDataCalcLoc.stMeasExt.siPcAvg;
    stPfcDataCalc.stMeasParm.siQaAvg           = stPfcDataCalcLoc.stMeasExt.siQaAvg;
    stPfcDataCalc.stMeasParm.siQbAvg           = stPfcDataCalcLoc.stMeasExt.siQbAvg;
    stPfcDataCalc.stMeasParm.siQcAvg           = stPfcDataCalcLoc.stMeasExt.siQcAvg;

    stPfcDataCalc.stMeasParm.slActvPower       = stPfcDataCalcLoc.stMeasExt.slActvPower;
    stPfcDataCalc.stMeasParm.slRePower         = stPfcDataCalcLoc.stMeasExt.slRePower;
    stPfcDataCalc.stMeasParm.slAprtPower       = stPfcDataCalcLoc.stMeasExt.slAprtPower;
    stPfcDataCalc.stMeasParm.ftPf              = stPfcDataCalcLoc.stMeasExt.ftPf;

    stPfcDataCalc.stMeasParm.ftFrqPllLPF       = stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF;
    stPfcDataCalc.stMeasParm.siPaAvgLPF        = stPfcDataCalcLoc.stMeasExt.siPaAvgLPF;
    stPfcDataCalc.stMeasParm.siPbAvgLPF        = stPfcDataCalcLoc.stMeasExt.siPbAvgLPF;
    stPfcDataCalc.stMeasParm.siPcAvgLPF        = stPfcDataCalcLoc.stMeasExt.siPcAvgLPF;
    stPfcDataCalc.stMeasParm.siQaAvgLPF        = stPfcDataCalcLoc.stMeasExt.siQaAvgLPF;
    stPfcDataCalc.stMeasParm.siQbAvgLPF        = stPfcDataCalcLoc.stMeasExt.siQbAvgLPF;
    stPfcDataCalc.stMeasParm.siQcAvgLPF        = stPfcDataCalcLoc.stMeasExt.siQcAvgLPF;

    stPfcDataCalc.stMeasParm.slActvPowerLPF    = stPfcDataCalcLoc.stMeasExt.slActvPowerLPF;
    stPfcDataCalc.stMeasParm.slRePowerLPF      = stPfcDataCalcLoc.stMeasExt.slRePowerLPF;
    stPfcDataCalc.stMeasParm.slAprtPowerLPF    = stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF;
    stPfcDataCalc.stMeasParm.ftPfLPF           = stPfcDataCalcLoc.stMeasExt.ftPfLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhALPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhBLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhCLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax = stPfcDataCalcLoc.stMeasExt.ftAprtPwr1PLPFMax;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Power correlation calculation 1ms task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PwrCalc_1ms(void)
{
    v_PfcDataCalc_PwrCalc_AVG_1ms();    ///< Power average calculation 1ms task
    v_PfcDataCalc_PwrCalc_LPF_1ms();    ///< Power LPF calculation 1ms task

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.ftVbusPosLPF      = stPfcDataCalcDbg.stMeasParm.ftVbusPosLPF;
    stPfcDataCalc.stMeasParm.ftVbusLPF         = stPfcDataCalcDbg.stMeasParm.ftVbusLPF;
    stPfcDataCalc.stMeasParm.siVbus10Times     = stPfcDataCalcDbg.stMeasParm.siVbus10Times;
    stPfcDataCalc.stMeasParm.siVbusPos10Times  = stPfcDataCalcDbg.stMeasParm.siVbusPos10Times;
    stPfcDataCalc.stMeasParm.uiVbusMid10Times  = stPfcDataCalcDbg.stMeasParm.uiVbusMid10Times;
    stPfcDataCalc.stMeasParm.ftIdRefLPF        = stPfcDataCalcDbg.stMeasParm.ftIdRefLPF;
    stPfcDataCalc.stMeasParm.siPaAvg           = stPfcDataCalcDbg.stMeasParm.siPaAvg;
    stPfcDataCalc.stMeasParm.siPbAvg           = stPfcDataCalcDbg.stMeasParm.siPbAvg;
    stPfcDataCalc.stMeasParm.siPcAvg           = stPfcDataCalcDbg.stMeasParm.siPcAvg;
    stPfcDataCalc.stMeasParm.siQaAvg           = stPfcDataCalcDbg.stMeasParm.siQaAvg;
    stPfcDataCalc.stMeasParm.siQbAvg           = stPfcDataCalcDbg.stMeasParm.siQbAvg;
    stPfcDataCalc.stMeasParm.siQcAvg           = stPfcDataCalcDbg.stMeasParm.siQcAvg;
    stPfcDataCalc.stMeasParm.slActvPower 	   = stPfcDataCalcDbg.stMeasParm.slActvPower;
    stPfcDataCalc.stMeasParm.slRePower   	   = stPfcDataCalcDbg.stMeasParm.slRePower;
    stPfcDataCalc.stMeasParm.slAprtPower 	   = stPfcDataCalcDbg.stMeasParm.slAprtPower;
    stPfcDataCalc.stMeasParm.ftPf        	   = stPfcDataCalcDbg.stMeasParm.ftPf;
    stPfcDataCalc.stMeasParm.ftFrqPllLPF 	   = stPfcDataCalcDbg.stMeasParm.ftFrqPllLPF;
    stPfcDataCalc.stMeasParm.siPaAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siPaAvgLPF;
    stPfcDataCalc.stMeasParm.siPbAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siPbAvgLPF;
    stPfcDataCalc.stMeasParm.siPcAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siPcAvgLPF;
    stPfcDataCalc.stMeasParm.siQaAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQaAvgLPF;
    stPfcDataCalc.stMeasParm.siQbAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQbAvgLPF;
    stPfcDataCalc.stMeasParm.siQcAvgLPF  	   = stPfcDataCalcDbg.stMeasParm.siQcAvgLPF;
    stPfcDataCalc.stMeasParm.slActvPowerLPF    = stPfcDataCalcDbg.stMeasParm.slActvPowerLPF;
    stPfcDataCalc.stMeasParm.slRePowerLPF      = stPfcDataCalcDbg.stMeasParm.slRePowerLPF;
    stPfcDataCalc.stMeasParm.slAprtPowerLPF    = stPfcDataCalcDbg.stMeasParm.slAprtPowerLPF;
    stPfcDataCalc.stMeasParm.ftPfLPF           = stPfcDataCalcDbg.stMeasParm.ftPfLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhALPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhALPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhBLPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhBLPF;
    stPfcDataCalc.stMeasParm.ftAprtPwrPhCLPF   = stPfcDataCalcDbg.stMeasParm.ftAprtPwrPhCLPF;
	stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax = stPfcDataCalcDbg.stMeasParm.ftAprtPwr1PLPFMax;
#else
    stPfcDataCalc.stMeasParm.ftVbusPosLPF      = stPfcDataCalcLoc.stMeasExt.ftVbusPosLPF;        ///< LPF value of upper bus voltage
    stPfcDataCalc.stMeasParm.ftVbusLPF         = stPfcDataCalcLoc.stMeasExt.ftVbusLPF;           ///< LPF value of bus voltage
    stPfcDataCalc.stMeasParm.siVbus10Times     = stPfcDataCalcLoc.stMeasExt.siVbus10Times;       ///< Bus voltage 10 times for fault detect
    stPfcDataCalc.stMeasParm.siVbusPos10Times  = stPfcDataCalcLoc.stMeasExt.siVbusPos10Times;    ///< Positive half bus voltage 10 times for fault detect
    stPfcDataCalc.stMeasParm.uiVbusMid10Times  = stPfcDataCalcLoc.stMeasExt.uiVbusMid10Times;    ///< Mid-point bus voltage 10 times for fault detect
    stPfcDataCalc.stMeasParm.ftIdRefLPF        = stPfcDataCalcLoc.stMeasExt.ftIdRefLPF;          ///< LPF value of IdRef
    stPfcDataCalc.stMeasParm.siPaAvg           = stPfcDataCalcLoc.stMeasExt.siPaAvg;             ///< 20ms Average active power of phase A
    stPfcDataCalc.stMeasParm.siPbAvg           = stPfcDataCalcLoc.stMeasExt.siPbAvg;             ///< 20ms Average active power of phase B
    stPfcDataCalc.stMeasParm.siPcAvg           = stPfcDataCalcLoc.stMeasExt.siPcAvg;             ///< 20ms Average active power of phase C
    stPfcDataCalc.stMeasParm.siQaAvg           = stPfcDataCalcLoc.stMeasExt.siQaAvg;             ///< 20ms Average reactive  power of phase A
    stPfcDataCalc.stMeasParm.siQbAvg           = stPfcDataCalcLoc.stMeasExt.siQbAvg;             ///< 20ms Average reactive  power of phase B
    stPfcDataCalc.stMeasParm.siQcAvg           = stPfcDataCalcLoc.stMeasExt.siQcAvg;             ///< 20ms Average reactive  power of phase C

    stPfcDataCalc.stMeasParm.slActvPower       = stPfcDataCalcLoc.stMeasExt.slActvPower;         ///< total active power
    stPfcDataCalc.stMeasParm.slRePower         = stPfcDataCalcLoc.stMeasExt.slRePower;           ///< total reactive power
    stPfcDataCalc.stMeasParm.slAprtPower       = stPfcDataCalcLoc.stMeasExt.slAprtPower;         ///< total apparent power
    stPfcDataCalc.stMeasParm.ftPf              = stPfcDataCalcLoc.stMeasExt.ftPf;                ///< total power factor

    stPfcDataCalc.stMeasParm.ftFrqPllLPF 	   = stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF;         ///< Grid PLL frequency 10Hz LPF value
    stPfcDataCalc.stMeasParm.siPaAvgLPF 	   = stPfcDataCalcLoc.stMeasExt.siPaAvgLPF;          ///< LPF active power of phase A
    stPfcDataCalc.stMeasParm.siPbAvgLPF 	   = stPfcDataCalcLoc.stMeasExt.siPbAvgLPF;          ///< LPF active power of phase B
    stPfcDataCalc.stMeasParm.siPcAvgLPF 	   = stPfcDataCalcLoc.stMeasExt.siPcAvgLPF;          ///< LPF active power of phase C
    stPfcDataCalc.stMeasParm.siQaAvgLPF 	   = stPfcDataCalcLoc.stMeasExt.siQaAvgLPF;          ///< LPF reactive  power of phase A
    stPfcDataCalc.stMeasParm.siQbAvgLPF        = stPfcDataCalcLoc.stMeasExt.siQbAvgLPF;          ///< LPF reactive  power of phase B
    stPfcDataCalc.stMeasParm.siQcAvgLPF 	   = stPfcDataCalcLoc.stMeasExt.siQcAvgLPF;          ///< LPF reactive  power of phase C

    stPfcDataCalc.stMeasParm.slActvPowerLPF    = stPfcDataCalcLoc.stMeasExt.slActvPowerLPF;      ///< total active power LPF
    stPfcDataCalc.stMeasParm.slRePowerLPF      = stPfcDataCalcLoc.stMeasExt.slRePowerLPF;        ///< total reactive  power LPF
    stPfcDataCalc.stMeasParm.slAprtPowerLPF    = stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF;      ///< total apparent power LPF
    stPfcDataCalc.stMeasParm.ftPfLPF           = stPfcDataCalcLoc.stMeasExt.ftPfLPF;             ///< total power factor LPF
    stPfcDataCalc.stMeasParm.ftAprtPwrPhALPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF;     ///< Phase A apparent power LPF
    stPfcDataCalc.stMeasParm.ftAprtPwrPhBLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF;     ///< Phase B apparent power LPF
    stPfcDataCalc.stMeasParm.ftAprtPwrPhCLPF   = stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF;     ///< Phase C apparent power LPF
    stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax = stPfcDataCalcLoc.stMeasExt.ftAprtPwr1PLPFMax;   ///< Phase C apparent power LPF
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Power correlation calculation 1ms task--Average part
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PwrCalc_AVG_1ms(void)
{
    float32 l_ftDataTmp       = 0.0f;
//    float32 l_ftReactvPowComp = 0.0f;
    int32   l_slTemp          = 0L;

#if 1U == GRID_PHASE_NUMBER
    /* 20ms Average active power */
    l_ftDataTmp       = stPfcDataCalcLoc.stPwr.ftPASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    l_ftReactvPowComp = COEFF_REACTV_POW_CALC_COMP * l_ftDataTmp;
    stPfcDataCalcLoc.stMeasExt.siPaAvg = (int16)(l_ftDataTmp);
    stPfcDataCalcLoc.stMeasExt.siPbAvg = 0;
    stPfcDataCalcLoc.stMeasExt.siPcAvg = 0;
    /* 20ms Average reactive power */
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp + l_ftReactvPowComp;    ///< Add Reactive power compensation
    stPfcDataCalcLoc.stMeasExt.siQaAvg = (int16)(l_ftDataTmp);
    stPfcDataCalcLoc.stMeasExt.siQbAvg = 0;
    stPfcDataCalcLoc.stMeasExt.siQcAvg = 0;
#elif 2U == GRID_PHASE_NUMBER
    /* 20ms Average active power */
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftPASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    stPfcDataCalcLoc.stMeasExt.siPaAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftPBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    stPfcDataCalcLoc.stMeasExt.siPbAvg = (int16)(l_ftDataTmp);
    stPfcDataCalcLoc.stMeasExt.siPcAvg = 0;
    /* 20ms Average reactive power */
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp;
    stPfcDataCalcLoc.stMeasExt.siQaAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp;
    stPfcDataCalcLoc.stMeasExt.siQbAvg = (int16)(l_ftDataTmp);
    stPfcDataCalcLoc.stMeasExt.siQcAvg = 0;
#elif 3U == GRID_PHASE_NUMBER
    /* 20ms Average active power */
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftPASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    stPfcDataCalcLoc.stMeasExt.siPaAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftPBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    stPfcDataCalcLoc.stMeasExt.siPbAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftPCSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints;
    stPfcDataCalcLoc.stMeasExt.siPcAvg = (int16)(l_ftDataTmp);
    /* 20ms Average reactive power */
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp;
    stPfcDataCalcLoc.stMeasExt.siQaAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp;
    stPfcDataCalcLoc.stMeasExt.siQbAvg = (int16)(l_ftDataTmp);
    l_ftDataTmp = stPfcDataCalcLoc.stPwr.ftQCSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints + stPfcPowPreCtrl.ftReactvPowComp;
    stPfcDataCalcLoc.stMeasExt.siQcAvg = (int16)(l_ftDataTmp);
#endif
    /* Total active power */
    stPfcDataCalcLoc.stMeasExt.slActvPower = (int32)stPfcDataCalcLoc.stMeasExt.siPaAvg + \
            (int32)stPfcDataCalcLoc.stMeasExt.siPbAvg + (int32)stPfcDataCalcLoc.stMeasExt.siPcAvg;
    /* Total reactive power */
    stPfcDataCalcLoc.stMeasExt.slRePower = (int32)stPfcDataCalcLoc.stMeasExt.siQaAvg + \
            (int32)stPfcDataCalcLoc.stMeasExt.siQbAvg + (int32)stPfcDataCalcLoc.stMeasExt.siQcAvg;
    /* Total apparent power */
    l_slTemp = stPfcDataCalcLoc.stMeasExt.slActvPower * stPfcDataCalcLoc.stMeasExt.slActvPower + \
            stPfcDataCalcLoc.stMeasExt.slRePower * stPfcDataCalcLoc.stMeasExt.slRePower;
    l_ftDataTmp = sqrtf((float32)(l_slTemp));
    stPfcDataCalcLoc.stMeasExt.slAprtPower = (int32)(l_ftDataTmp);
    /* Total power factor */
    if(stPfcDataCalcLoc.stMeasExt.slAprtPower > 100L)
    {
        if(stPfcDataCalcLoc.stMeasExt.slRePower < 0L)
        {
            stPfcDataCalcLoc.stMeasExt.ftPf = -fabsf((float32)stPfcDataCalcLoc.stMeasExt.slActvPower) / (float32)stPfcDataCalcLoc.stMeasExt.slAprtPower;
        }
        else
        {
            stPfcDataCalcLoc.stMeasExt.ftPf = fabsf((float32)stPfcDataCalcLoc.stMeasExt.slActvPower) / (float32)stPfcDataCalcLoc.stMeasExt.slAprtPower;
        }
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.ftPf = 1.0f;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Power correlation calculation 1ms task--LPF part, used for display
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_PwrCalc_LPF_1ms(void)
{
    int16   l_siDataTmp      = 0;
    int32   l_slTemp         = 0L;
    float32 l_ftDataTmp      = 0.0f;
    float32 ftLpfIn          = 0.0f;
    static float32 ftLpfOut1 = 0.0f;
    static float32 ftLpfOut2 = 0.0f;
    static float32 ftLpfOut3 = 0.0f;
    static float32 ftLpfOut4 = 0.0f;
    static float32 ftLpfOut5 = 0.0f;
    static float32 ftLpfOut6 = 0.0f;
    static float32 ftLpfOut7 = 0.0f;
    static float32 ftLpfOut8 = 0.0f;
    static float32 ftLpfOut9 = 0.0f;

    /* Grid PLL frequency 10Hz LPF value calculation */
#if 1U == FLG_PFC_POWCTRL_EN
    if(stPfcDataCalc.stMeasParm.ftVgMinRms > FRQCALC_VOLT_LIM)
    {
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF, stPfcPowCtrl.ftFrqPll, COEFF_LPF_10HZ_1MS);
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.ftFrqPllLPF  = stComTbl.stPrmPfcRtd1.ftFrqGrid;
    }
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIdRefLPF, stPfcPowCtrl.ftIdRef, COEFF_LPF_20HZ_1MS);
#endif
    /* LPF value of bus voltage calculation */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVbusLPF, stPfcAdc.stVbus.ftValLpf10kHz_A, COEFF_LPF_10HZ_1MS);
    l_ftDataTmp = stPfcAdc.stVbus.ftValLpf10kHz_A * COEFF_VOLT_ARM;
    stPfcDataCalcLoc.stMeasExt.siVbus10Times = (int16)(l_ftDataTmp);

#if GRID_PHASE_NUMBER > 1U
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVbusPosLPF, stPfcAdc.stVbusPos.ftValLpf10kHz_A, COEFF_LPF_10HZ_1MS);
    l_ftDataTmp = stPfcAdc.stVbusPos.ftValLpf10kHz_A * COEFF_VOLT_ARM;
    stPfcDataCalcLoc.stMeasExt.siVbusPos10Times = (int16)(l_ftDataTmp);
    l_siDataTmp = stPfcDataCalcLoc.stMeasExt.siVbus10Times - stPfcDataCalcLoc.stMeasExt.siVbusPos10Times * 2;
    stPfcDataCalcLoc.stMeasExt.uiVbusMid10Times = ABS_INT(l_siDataTmp);
#endif

    /* LPF value of Phase A active power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siPaAvg;
    vFcn_1stOrdLPF(&ftLpfOut1, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siPaAvgLPF = (int16)ftLpfOut1;
    /* LPF value of Phase B active power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siPbAvg;
    vFcn_1stOrdLPF(&ftLpfOut2, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siPbAvgLPF = (int16)ftLpfOut2;
    /* LPF value of Phase C active power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siPcAvg;
    vFcn_1stOrdLPF(&ftLpfOut3, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siPcAvgLPF = (int16)ftLpfOut3;

    /* LPF value of Phase A reactive power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siQaAvg;
    vFcn_1stOrdLPF(&ftLpfOut4, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siQaAvgLPF = (int16)ftLpfOut4;
    /* LPF value of Phase B reactive power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siQbAvg;
    vFcn_1stOrdLPF(&ftLpfOut5, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siQbAvgLPF = (int16)ftLpfOut5;
    /* LPF value of Phase C reactive power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.siQcAvg;
    vFcn_1stOrdLPF(&ftLpfOut6, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siQcAvgLPF = (int16)ftLpfOut6;

    /* LPF value of total active power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.slActvPower;
    vFcn_1stOrdLPF(&ftLpfOut7, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.slActvPowerLPF = (int32)ftLpfOut7;

    /* LPF value of total reactive power calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.slRePower;
    vFcn_1stOrdLPF(&ftLpfOut8, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.slRePowerLPF = (int32)ftLpfOut8;

    /* LPF value of apparent power LPF calculation */
    ftLpfIn = (float32)stPfcDataCalcLoc.stMeasExt.slAprtPower;
    vFcn_1stOrdLPF(&ftLpfOut9, ftLpfIn, COEFF_LPF_50HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF = (int32)ftLpfOut9;

    /* LPF value of total power factor calculation */
    if(stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF > 100L)
    {
        if(stPfcDataCalcLoc.stMeasExt.slRePowerLPF < 0L)
        {
            stPfcDataCalcLoc.stMeasExt.ftPfLPF = -fabsf((float32)stPfcDataCalcLoc.stMeasExt.slActvPowerLPF) / (float32)stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF;
        }
        else
        {
            stPfcDataCalcLoc.stMeasExt.ftPfLPF = fabsf((float32)stPfcDataCalcLoc.stMeasExt.slActvPowerLPF) / (float32)stPfcDataCalcLoc.stMeasExt.slAprtPowerLPF;
        }
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.ftPfLPF = 1.0f;
    }

    /* Phase A apparent power */
    l_slTemp = (int32)stPfcDataCalcLoc.stMeasExt.siPaAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siPaAvgLPF \
               + (int32)stPfcDataCalcLoc.stMeasExt.siQaAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siQaAvgLPF;
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF = sqrtf((float32)(l_slTemp));
#if GRID_PHASE_NUMBER > 1U
    /* Phase B apparent power */
    l_slTemp = (int32)stPfcDataCalcLoc.stMeasExt.siPbAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siPbAvgLPF \
               + (int32)stPfcDataCalcLoc.stMeasExt.siQbAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siQbAvgLPF;
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF = sqrtf((float32)(l_slTemp));
#if GRID_PHASE_NUMBER > 2U
    /* Phase C apparent power */
    l_slTemp = (int32)stPfcDataCalcLoc.stMeasExt.siPcAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siPcAvgLPF \
               + (int32)stPfcDataCalcLoc.stMeasExt.siQcAvgLPF * (int32)stPfcDataCalcLoc.stMeasExt.siQcAvgLPF;
    stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF = sqrtf((float32)(l_slTemp));
#endif
#endif
    /* Single phase maximum apparent power */
    stPfcDataCalcLoc.stMeasExt.ftAprtPwr1PLPFMax = ftFcn_MaxOfThree(stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhALPF, stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhBLPF, stPfcDataCalcLoc.stMeasExt.ftAprtPwrPhCLPF);
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Voltage&Current RMS calculation Init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_Init(void)
{
    stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVaRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVbRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVcRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVabRms      = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVbcRms      = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVacRms      = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVaInvRms    = 0.0f;
    stPfcDataCalcLoc.stMeasExt.ftVbInvRms    = 0.0f;
    stPfcDataCalcLoc.stMeasExt.ftIaRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftIbRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftIcRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftInRms       = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVaRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVbRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVcRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVaInvRmsLPF = 0.0f;
    stPfcDataCalcLoc.stMeasExt.ftVbInvRmsLPF = 0.0f;
    stPfcDataCalcLoc.stMeasExt.ftIaRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftIbRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftIcRmsLPF    = 0.0f;          ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftInRmsLPF    = 0.0f;          ///< Initialize to 0.0f

    stPfcDataCalcLoc.stMeasExt.ftVgMaxRms          = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVgMinRms          = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVLineMaxRms       = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVLineMinRms       = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVgAvgRms          = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftVgAvgRmsLPF       = 0.0f;    ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax     = 1.0f;    ///< Initialize to 1.0f
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin     = 1.0f;    ///< Initialize to 1.0f
    stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times  = 0U;      ///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times  = 0U;      ///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times = 0U;      ///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.uiVgDiffRms10Times  = 0U;      ///< Initialize to 0U

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stMeasParm.ftVdRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVaRms             = stPfcDataCalcLoc.stMeasExt.ftVaRms;
    stPfcDataCalcDbg.stMeasParm.ftVbRms             = stPfcDataCalcLoc.stMeasExt.ftVbRms;
    stPfcDataCalcDbg.stMeasParm.ftVcRms             = stPfcDataCalcLoc.stMeasExt.ftVcRms;
    stPfcDataCalcDbg.stMeasParm.ftVaInvRms          = stPfcDataCalcLoc.stMeasExt.ftVaInvRms;
    stPfcDataCalcDbg.stMeasParm.ftVbInvRms          = stPfcDataCalcLoc.stMeasExt.ftVbInvRms;
    stPfcDataCalcDbg.stMeasParm.ftIaRms             = stPfcDataCalcLoc.stMeasExt.ftIaRms;
    stPfcDataCalcDbg.stMeasParm.ftIbRms             = stPfcDataCalcLoc.stMeasExt.ftIbRms;
    stPfcDataCalcDbg.stMeasParm.ftIcRms             = stPfcDataCalcLoc.stMeasExt.ftIcRms;
    stPfcDataCalcDbg.stMeasParm.ftInRms             = stPfcDataCalcLoc.stMeasExt.ftInRms;
    stPfcDataCalcDbg.stMeasParm.ftVaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVaRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVbRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVcRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVaInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVaInvRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVbInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVbInvRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftIaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIaRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftIbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIbRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftIcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIcRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftInRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftInRmsLPF;
    stPfcDataCalcDbg.stMeasParm.ftVgMaxRms          = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms;
    stPfcDataCalcDbg.stMeasParm.ftVgMinRms          = stPfcDataCalcLoc.stMeasExt.ftVgMinRms;
    stPfcDataCalcDbg.stMeasParm.ftVgAvgRms          = stPfcDataCalcLoc.stMeasExt.ftVgAvgRms;
    stPfcDataCalcDbg.stMeasParm.ftVgAvgRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVgAvgRmsLPF;
    stPfcDataCalcDbg.stMeasParm.uiIgMaxRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times;
    stPfcDataCalcDbg.stMeasParm.uiIgMinRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times;
    stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMax     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax;
    stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMin     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin;
    stPfcDataCalcDbg.stMeasParm.uiIgDiffRms100Times = stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times;
    stPfcDataCalcDbg.stMeasParm.uiVgDiffRms10Times  = stPfcDataCalcLoc.stMeasExt.uiVgDiffRms10Times;

    stPfcDataCalc.stMeasParm.ftVdRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVdRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaRms             = stPfcDataCalcDbg.stMeasParm.ftVaRms;
    stPfcDataCalc.stMeasParm.ftVbRms             = stPfcDataCalcDbg.stMeasParm.ftVbRms;
    stPfcDataCalc.stMeasParm.ftVcRms             = stPfcDataCalcDbg.stMeasParm.ftVcRms;
    stPfcDataCalc.stMeasParm.ftVaInvRms          = stPfcDataCalcDbg.stMeasParm.ftVaInvRms;
    stPfcDataCalc.stMeasParm.ftVbInvRms          = stPfcDataCalcDbg.stMeasParm.ftVbInvRms;
    stPfcDataCalc.stMeasParm.ftIaRms             = stPfcDataCalcDbg.stMeasParm.ftIaRms;
    stPfcDataCalc.stMeasParm.ftIbRms             = stPfcDataCalcDbg.stMeasParm.ftIbRms;
    stPfcDataCalc.stMeasParm.ftIcRms             = stPfcDataCalcDbg.stMeasParm.ftIcRms;
    stPfcDataCalc.stMeasParm.ftInRms             = stPfcDataCalcDbg.stMeasParm.ftInRms;
    stPfcDataCalc.stMeasParm.ftVaRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVaRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVbRmsLPF;
    stPfcDataCalc.stMeasParm.ftVcRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVcRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaInvRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVaInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbInvRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVbInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftIaRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIaRmsLPF;
    stPfcDataCalc.stMeasParm.ftIbRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIbRmsLPF;
    stPfcDataCalc.stMeasParm.ftIcRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIcRmsLPF;
    stPfcDataCalc.stMeasParm.ftInRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftInRmsLPF;
    stPfcDataCalc.stMeasParm.ftVgMaxRms          = stPfcDataCalcDbg.stMeasParm.ftVgMaxRms;
    stPfcDataCalc.stMeasParm.ftVgMinRms          = stPfcDataCalcDbg.stMeasParm.ftVgMinRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRms          = stPfcDataCalcDbg.stMeasParm.ftVgAvgRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVgAvgRmsLPF;
    stPfcDataCalc.stMeasParm.uiIgMaxRms100Times  = stPfcDataCalcDbg.stMeasParm.uiIgMaxRms100Times;
    stPfcDataCalc.stMeasParm.uiIgMinRms100Times  = stPfcDataCalcDbg.stMeasParm.uiIgMinRms100Times;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMax     = stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMax;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMin     = stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMin;
    stPfcDataCalc.stMeasParm.uiIgDiffRms100Times = stPfcDataCalcDbg.stMeasParm.uiIgDiffRms100Times;
    stPfcDataCalc.stMeasParm.uiVgDiffRms10Times  = stPfcDataCalcDbg.stMeasParm.uiVgDiffRms10Times;
#else
    stPfcDataCalc.stMeasParm.ftVdRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaRms             = stPfcDataCalcLoc.stMeasExt.ftVaRms;
    stPfcDataCalc.stMeasParm.ftVbRms             = stPfcDataCalcLoc.stMeasExt.ftVbRms;
    stPfcDataCalc.stMeasParm.ftVcRms             = stPfcDataCalcLoc.stMeasExt.ftVcRms;
    stPfcDataCalc.stMeasParm.ftVabRms            = stPfcDataCalcLoc.stMeasExt.ftVabRms;
    stPfcDataCalc.stMeasParm.ftVbcRms            = stPfcDataCalcLoc.stMeasExt.ftVbcRms;
    stPfcDataCalc.stMeasParm.ftVacRms            = stPfcDataCalcLoc.stMeasExt.ftVacRms;
    stPfcDataCalc.stMeasParm.ftVaInvRms          = stPfcDataCalcLoc.stMeasExt.ftVaInvRms;
    stPfcDataCalc.stMeasParm.ftVbInvRms          = stPfcDataCalcLoc.stMeasExt.ftVbInvRms;
    stPfcDataCalc.stMeasParm.ftIaRms             = stPfcDataCalcLoc.stMeasExt.ftIaRms;
    stPfcDataCalc.stMeasParm.ftIbRms             = stPfcDataCalcLoc.stMeasExt.ftIbRms;
    stPfcDataCalc.stMeasParm.ftIcRms             = stPfcDataCalcLoc.stMeasExt.ftIcRms;
    stPfcDataCalc.stMeasParm.ftInRms             = stPfcDataCalcLoc.stMeasExt.ftInRms;
    stPfcDataCalc.stMeasParm.ftVaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVaRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVbRmsLPF;
    stPfcDataCalc.stMeasParm.ftVcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVcRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVaInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVbInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftIaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIaRmsLPF;
    stPfcDataCalc.stMeasParm.ftIbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIbRmsLPF;
    stPfcDataCalc.stMeasParm.ftIcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIcRmsLPF;
    stPfcDataCalc.stMeasParm.ftInRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftInRmsLPF;
    stPfcDataCalc.stMeasParm.ftVgMaxRms          = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms;
    stPfcDataCalc.stMeasParm.ftVgMinRms          = stPfcDataCalcLoc.stMeasExt.ftVgMinRms;
    stPfcDataCalc.stMeasParm.ftVLineMaxRms       = stPfcDataCalcLoc.stMeasExt.ftVLineMaxRms;
    stPfcDataCalc.stMeasParm.ftVLineMinRms       = stPfcDataCalcLoc.stMeasExt.ftVLineMinRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRms          = stPfcDataCalcLoc.stMeasExt.ftVgAvgRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVgAvgRmsLPF;
    stPfcDataCalc.stMeasParm.uiIgMaxRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times;
    stPfcDataCalc.stMeasParm.uiIgMinRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMax     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMin     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin;
    stPfcDataCalc.stMeasParm.uiIgDiffRms100Times = stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times;
    stPfcDataCalc.stMeasParm.uiVgDiffRms10Times  = stPfcDataCalcLoc.stMeasExt.uiVgDiffRms10Times;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Voltage&Current RMS calculation 1ms task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_1ms(void)
{
    /* Reciprocal of RMS calculation points */
    vFcn_UiUpDwnLim(&stPfcDataCalcLoc.stVFcalc.uiCurrPoints, MAX_RMS_NUM, MIN_RMS_NUM);
    stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints = 1.0f / (float32)stPfcDataCalcLoc.stVFcalc.uiCurrPoints;

    /* Voltage&Current RMS calculation */
    v_PfcDataCalc_RmsCalc_Volt_1ms();    ///< Voltage RMS calculation
    v_PfcDataCalc_RmsCalc_Curr_1ms();    ///< Current RMS calculation

    /* LPF of Voltage&Current RMS calculation */
    v_PfcDataCalc_RmsCalc_VoltLPF();    ///< LPF of Voltage RMS calculation
    v_PfcDataCalc_RmsCalc_CurrLPF();    ///< LPF of Current RMS calculation

    /* Max and Min of Voltage&Current RMS calculation */
    v_PfcDataCalc_RmsCalc_MaxMin();

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.ftVdRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVdRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaRms             = stPfcDataCalcDbg.stMeasParm.ftVaRms;
    stPfcDataCalc.stMeasParm.ftVbRms             = stPfcDataCalcDbg.stMeasParm.ftVbRms;
    stPfcDataCalc.stMeasParm.ftVcRms             = stPfcDataCalcDbg.stMeasParm.ftVcRms;
    stPfcDataCalc.stMeasParm.ftVaInvRms          = stPfcDataCalcDbg.stMeasParm.ftVaInvRms;
    stPfcDataCalc.stMeasParm.ftVbInvRms          = stPfcDataCalcDbg.stMeasParm.ftVbInvRms;
    stPfcDataCalc.stMeasParm.ftIaRms             = stPfcDataCalcDbg.stMeasParm.ftIaRms;
    stPfcDataCalc.stMeasParm.ftIbRms             = stPfcDataCalcDbg.stMeasParm.ftIbRms;
    stPfcDataCalc.stMeasParm.ftIcRms             = stPfcDataCalcDbg.stMeasParm.ftIcRms;
    stPfcDataCalc.stMeasParm.ftInRms             = stPfcDataCalcDbg.stMeasParm.ftInRms;
    stPfcDataCalc.stMeasParm.ftVaRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVaRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVbRmsLPF;
    stPfcDataCalc.stMeasParm.ftVcRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftVcRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaInvRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVaInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbInvRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVbInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftIaRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIaRmsLPF;
    stPfcDataCalc.stMeasParm.ftIbRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIbRmsLPF;
    stPfcDataCalc.stMeasParm.ftIcRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftIcRmsLPF;
    stPfcDataCalc.stMeasParm.ftInRmsLPF          = stPfcDataCalcDbg.stMeasParm.ftInRmsLPF;
    stPfcDataCalc.stMeasParm.ftVgMaxRms          = stPfcDataCalcDbg.stMeasParm.ftVgMaxRms;
    stPfcDataCalc.stMeasParm.ftVgMinRms          = stPfcDataCalcDbg.stMeasParm.ftVgMinRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRms          = stPfcDataCalcDbg.stMeasParm.ftVgAvgRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRmsLPF       = stPfcDataCalcDbg.stMeasParm.ftVgAvgRmsLPF;
    stPfcDataCalc.stMeasParm.uiIgMaxRms100Times  = stPfcDataCalcDbg.stMeasParm.uiIgMaxRms100Times;
    stPfcDataCalc.stMeasParm.uiIgMinRms100Times  = stPfcDataCalcDbg.stMeasParm.uiIgMinRms100Times;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMax     = stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMax;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMin     = stPfcDataCalcDbg.stMeasParm.ftRatVoltVrtMin;
    stPfcDataCalc.stMeasParm.uiIgDiffRms100Times = stPfcDataCalcDbg.stMeasParm.uiIgDiffRms100Times;
    stPfcDataCalc.stMeasParm.uiVgDiffRms10Times  = stPfcDataCalcDbg.stMeasParm.uiVgDiffRms10Times;
#else
    stPfcDataCalc.stMeasParm.ftVdRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaRms             = stPfcDataCalcLoc.stMeasExt.ftVaRms;
    stPfcDataCalc.stMeasParm.ftVbRms             = stPfcDataCalcLoc.stMeasExt.ftVbRms;
    stPfcDataCalc.stMeasParm.ftVcRms             = stPfcDataCalcLoc.stMeasExt.ftVcRms;
    stPfcDataCalc.stMeasParm.ftVabRms            = stPfcDataCalcLoc.stMeasExt.ftVabRms;
    stPfcDataCalc.stMeasParm.ftVbcRms            = stPfcDataCalcLoc.stMeasExt.ftVbcRms;
    stPfcDataCalc.stMeasParm.ftVacRms            = stPfcDataCalcLoc.stMeasExt.ftVacRms;
    stPfcDataCalc.stMeasParm.ftVaInvRms          = stPfcDataCalcLoc.stMeasExt.ftVaInvRms;
    stPfcDataCalc.stMeasParm.ftVbInvRms          = stPfcDataCalcLoc.stMeasExt.ftVbInvRms;
    stPfcDataCalc.stMeasParm.ftIaRms             = stPfcDataCalcLoc.stMeasExt.ftIaRms;
    stPfcDataCalc.stMeasParm.ftIbRms             = stPfcDataCalcLoc.stMeasExt.ftIbRms;
    stPfcDataCalc.stMeasParm.ftIcRms             = stPfcDataCalcLoc.stMeasExt.ftIcRms;
    stPfcDataCalc.stMeasParm.ftInRms             = stPfcDataCalcLoc.stMeasExt.ftInRms;  ///< sst no use
    stPfcDataCalc.stMeasParm.ftVaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVaRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVbRmsLPF;
    stPfcDataCalc.stMeasParm.ftVcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftVcRmsLPF;
    stPfcDataCalc.stMeasParm.ftVaInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVaInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftVbInvRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVbInvRmsLPF;
    stPfcDataCalc.stMeasParm.ftIaRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIaRmsLPF;
    stPfcDataCalc.stMeasParm.ftIbRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIbRmsLPF;
    stPfcDataCalc.stMeasParm.ftIcRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftIcRmsLPF;
    stPfcDataCalc.stMeasParm.ftInRmsLPF          = stPfcDataCalcLoc.stMeasExt.ftInRmsLPF;
    stPfcDataCalc.stMeasParm.ftVgMaxRms          = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms;
    stPfcDataCalc.stMeasParm.ftVgMinRms          = stPfcDataCalcLoc.stMeasExt.ftVgMinRms;
    stPfcDataCalc.stMeasParm.ftVLineMaxRms       = stPfcDataCalcLoc.stMeasExt.ftVLineMaxRms;
    stPfcDataCalc.stMeasParm.ftVLineMinRms       = stPfcDataCalcLoc.stMeasExt.ftVLineMinRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRms          = stPfcDataCalcLoc.stMeasExt.ftVgAvgRms;
    stPfcDataCalc.stMeasParm.ftVgAvgRmsLPF       = stPfcDataCalcLoc.stMeasExt.ftVgAvgRmsLPF;
    stPfcDataCalc.stMeasParm.uiIgMaxRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times;
    stPfcDataCalc.stMeasParm.uiIgMinRms100Times  = stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times;
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMax     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax; ///< sst no use
    stPfcDataCalc.stMeasParm.ftRatVoltVrtMin     = stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin; ///< sst no use
    stPfcDataCalc.stMeasParm.uiIgDiffRms100Times = stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times;
    stPfcDataCalc.stMeasParm.uiVgDiffRms10Times  = stPfcDataCalcLoc.stMeasExt.uiVgDiffRms10Times;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Voltage&Current RMS calculation 1ms task-Voltage RMS
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_Volt_1ms(void)
{
    /* Phase A voltage rms value calculation */
    stPfcDataCalcLoc.stMeasExt.ftVaRms = sqrtf(stPfcDataCalcLoc.stVolt.ftARmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);

#if 2U == GRID_PHASE_NUMBER
    /* Phase B voltage rms value calculation */
    stPfcDataCalcLoc.stMeasExt.ftVbRms = sqrtf(stPfcDataCalcLoc.stVolt.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    /* Phase A invert voltage rms value calculation */
    stPfcDataCalcLoc.stMeasExt.ftVaInvRms = sqrtf(stPfcDataCalcLoc.stVoltInv.ftARmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    /* Phase B invert voltage rms value calculation */
    stPfcDataCalcLoc.stMeasExt.ftVbInvRms = sqrtf(stPfcDataCalcLoc.stVoltInv.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
#elif  3U == GRID_PHASE_NUMBER
    /* Phase B voltage rms value calculation */
    if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
    {
        stPfcDataCalcLoc.stMeasExt.ftVbRms = sqrtf(stPfcDataCalcLoc.stVolt.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.ftVbRms = sqrtf(stPfcDataCalcLoc.stVolt.ftCRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }

    /* Phase C voltage rms value calculation */
    if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
    {
        stPfcDataCalcLoc.stMeasExt.ftVcRms = sqrtf(stPfcDataCalcLoc.stVolt.ftCRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.ftVcRms = sqrtf(stPfcDataCalcLoc.stVolt.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }

    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)
    {
        /* Line AB voltage rms value calculation */
        stPfcDataCalcLoc.stMeasExt.ftVabRms = sqrtf(stPfcDataCalcLoc.stVoltLine.ftARmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
        /* Line BC voltage rms value calculation */
        stPfcDataCalcLoc.stMeasExt.ftVbcRms = sqrtf(stPfcDataCalcLoc.stVoltLine.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
        /* Line AC voltage rms value calculation */
        stPfcDataCalcLoc.stMeasExt.ftVacRms = sqrtf(stPfcDataCalcLoc.stVoltLine.ftCRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Voltage&Current RMS calculation 1ms task-Voltage RMS-LPF
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_VoltLPF(void)
{
#if 1U == FLG_PFC_POWCTRL_EN
    /* LPF value of D-axis voltage rms value */
    stPfcDataCalcLoc.stMeasExt.ftVdRmsLPF = stPfcPowCtrl.ftVgDPllLpf * RECPR_CON_SQRT_2;
#endif
    /* LPF value of phase A voltage rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVaRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVaRms, COEFF_LPF_20HZ_1MS);
#if GRID_PHASE_NUMBER > 1U
    /* LPF value of phase B voltage rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVbRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVbRms, COEFF_LPF_20HZ_1MS);
    /* LPF value of phase A invert voltage rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVaInvRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVaInvRms, COEFF_LPF_20HZ_1MS);
    /* LPF value of phase B invert voltage rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVbInvRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVbInvRms, COEFF_LPF_20HZ_1MS);
    #if GRID_PHASE_NUMBER > 2U
    /* LPF value of phase C voltage rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVcRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVcRms, COEFF_LPF_20HZ_1MS);
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Voltage&Current RMS calculation 1ms task-Current RMS
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_Curr_1ms(void)
{
    float32 ftLpfIn = 0.0f;
    /* Phase A current rms value */
    ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftARmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIaRms, ftLpfIn, COEFF_LPF_50HZ_1MS);

#if GRID_PHASE_NUMBER > 1U
    /* Balance bridge current rms value */
    ftLpfIn = sqrtf(stPfcDataCalcLoc.stIn.ftRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftInRms, ftLpfIn, COEFF_LPF_50HZ_1MS);

    #if 2U == GRID_PHASE_NUMBER
    /* Phase B current rms value */
    ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIbRms, ftLpfIn, COEFF_LPF_50HZ_1MS);
    #elif  3U == GRID_PHASE_NUMBER
    /* Phase B current rms value */
    if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
    {
        ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    else
    {
        ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftCRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIbRms, ftLpfIn, COEFF_LPF_50HZ_1MS);
    /* Phase C current rms value */
    if(GRID_POS_SEQ == stPfcDataCalcLoc.stCtrlExt.uiFlgPhaSeq)
    {
        ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftCRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    else
    {
        ftLpfIn = sqrtf(stPfcDataCalcLoc.stCurr.ftBRmsSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints);
    }
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIcRms, ftLpfIn, COEFF_LPF_50HZ_1MS);
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Voltage&Current RMS calculation 1ms task-Current RMS-LPF
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_CurrLPF(void)
{
    /* LPF value of phase A current rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIaRmsLPF, stPfcDataCalcLoc.stMeasExt.ftIaRms, COEFF_LPF_20HZ_1MS);
#if GRID_PHASE_NUMBER > 1U
    /* LPF value of balance bridge current rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftInRmsLPF, stPfcDataCalcLoc.stMeasExt.ftInRms, COEFF_LPF_20HZ_1MS);
    /* LPF value of phase B current rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIbRmsLPF, stPfcDataCalcLoc.stMeasExt.ftIbRms, COEFF_LPF_20HZ_1MS);
    #if GRID_PHASE_NUMBER > 2U
    /* LPF value of phase C current rms value */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftIcRmsLPF, stPfcDataCalcLoc.stMeasExt.ftIcRms, COEFF_LPF_20HZ_1MS);
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Voltage&Current RMS calculation 1ms task-Maximum&Minimum value
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_MaxMin(void)
{
    float32 l_ftDataTmp = 0.0f;

    /* Max and Min value of RMS calculation  */
#if 1U == GRID_PHASE_NUMBER
    v_PfcDataCalc_RmsCalc_MaxMin_1P();
#elif 2U == GRID_PHASE_NUMBER
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)    ///< Phase full run mode
    {
        v_PfcDataCalc_RmsCalc_MaxMin_2P();
    }
    else                                                  ///< One phase run mode
    {
        v_PfcDataCalc_RmsCalc_MaxMin_1P();
    }
#elif 3U == GRID_PHASE_NUMBER
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)    ///< Phase full run mode
    {
        v_PfcDataCalc_RmsCalc_MaxMin_3P();
    }
    else                                                  ///< One phase run mode
    {
        v_PfcDataCalc_RmsCalc_MaxMin_1P();
    }
#endif

    /* LPF value of Average grid voltage RMS calculation  */
    vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftVgAvgRmsLPF, stPfcDataCalcLoc.stMeasExt.ftVgAvgRms, COEFF_LPF_6HZ_1MS);

    /* Deviation value of grid current 100 times for fault detect */
    if((BIDIR_ONGRID_MODE == stComIf.uiModPfcRun) \
       && ((PFC_IMBAL_RUN_MODE == stCom.unModPfcPow.bit.uiModActvImbal) || (PFC_IMBAL_RUN_MODE == stCom.unModPfcPow.bit.uiModReactvImbal)))
    {
        stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times = 0U;
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.uiIgDiffRms100Times = stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times - stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times;
    }

    /* Deviation value of grid voltage 10 times for fault detect */
    l_ftDataTmp = (stPfcDataCalcLoc.stMeasExt.ftVgMaxRms - stPfcDataCalcLoc.stMeasExt.ftVgMinRms) * COEFF_VOLT_ARM;
    stPfcDataCalcLoc.stMeasExt.uiVgDiffRms10Times = (Uint16)(l_ftDataTmp);
}
/*********************************************End**********************************************/

#if 3U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: Voltage&Current RMS calculation 1ms task-Maximum&Minimum value-Three phase system
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_MaxMin_3P(void)
{
    float32 l_ftDataTmp = 0.0f;

    /* Max value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgMaxRms = ftFcn_MaxOfThree(stPfcDataCalcLoc.stMeasExt.ftVaRms, \
                                            stPfcDataCalcLoc.stMeasExt.ftVbRms,stPfcDataCalcLoc.stMeasExt.ftVcRms);
    /* Min value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgMinRms = ftFcn_MinOfThree(stPfcDataCalcLoc.stMeasExt.ftVaRms, \
                                            stPfcDataCalcLoc.stMeasExt.ftVbRms,stPfcDataCalcLoc.stMeasExt.ftVcRms);
    /* Average value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgAvgRms = (stPfcDataCalcLoc.stMeasExt.ftVaRms + stPfcDataCalcLoc.stMeasExt.ftVbRms \
                                             + stPfcDataCalcLoc.stMeasExt.ftVcRms) * RECPR_CON_3;

    /* Max value of grid current RMS calculation */
    l_ftDataTmp = ftFcn_MaxOfThree(stPfcDataCalcLoc.stMeasExt.ftIaRms, stPfcDataCalcLoc.stMeasExt.ftIbRms, \
                       stPfcDataCalcLoc.stMeasExt.ftIcRms) * COEFF_CURR_ARM;
    stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times = (Uint16)(l_ftDataTmp);
    /* Min value of grid current RMS calculation */
    l_ftDataTmp = ftFcn_MinOfThree(stPfcDataCalcLoc.stMeasExt.ftIaRms, stPfcDataCalcLoc.stMeasExt.ftIbRms, \
                       stPfcDataCalcLoc.stMeasExt.ftIcRms) * COEFF_CURR_ARM;
    stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times = (Uint16)(l_ftDataTmp);

    /* Ratio of Max grid voltage for VRT calculation */
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
    /* Ratio of Min grid voltage for VRT calculation */
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin = stPfcDataCalcLoc.stMeasExt.ftVgMinRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;

    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)
    {
        /* Max value of grid line voltage RMS calculation */
        stPfcDataCalcLoc.stMeasExt.ftVLineMaxRms = ftFcn_MaxOfThree(stPfcDataCalcLoc.stMeasExt.ftVabRms, \
                                                             stPfcDataCalcLoc.stMeasExt.ftVbcRms, stPfcDataCalcLoc.stMeasExt.ftVacRms);
        /* Min value of grid line voltage RMS calculation */
        stPfcDataCalcLoc.stMeasExt.ftVLineMinRms = ftFcn_MinOfThree(stPfcDataCalcLoc.stMeasExt.ftVabRms, \
                                                             stPfcDataCalcLoc.stMeasExt.ftVbcRms, stPfcDataCalcLoc.stMeasExt.ftVacRms);
    }
}
/*********************************************End**********************************************/
#endif

#if 2U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: Voltage&Current RMS calculation 1ms task-Maximum&Minimum value-Two phase system
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_MaxMin_2P(void)
{
    float32 l_ftDataTmp = 0.0f;

    /* Max value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgMaxRms = ftFcn_MaxOfTwo(stPfcDataCalcLoc.stMeasExt.ftVaRms, stPfcDataCalcLoc.stMeasExt.ftVbRms);
    /* Min value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgMinRms = ftFcn_MinOfTwo(stPfcDataCalcLoc.stMeasExt.ftVaRms, stPfcDataCalcLoc.stMeasExt.ftVbRms);
    /* Average value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgAvgRms = (stPfcDataCalcLoc.stMeasExt.ftVaRms + stPfcDataCalcLoc.stMeasExt.ftVbRms) * RECPR_CON_2;

    /* Max value of grid current RMS calculation */
    l_ftDataTmp = ftFcn_MaxOfTwo(stPfcDataCalcLoc.stMeasExt.ftIaRms, stPfcDataCalcLoc.stMeasExt.ftIbRms) * COEFF_CURR_ARM;
    stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times = (Uint16)(l_ftDataTmp);
    /* Min value of grid current RMS calculation */
    l_ftDataTmp = ftFcn_MinOfTwo(stPfcDataCalcLoc.stMeasExt.ftIaRms, stPfcDataCalcLoc.stMeasExt.ftIbRms) * COEFF_CURR_ARM;
    stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times = (Uint16)(l_ftDataTmp);

    /* Ratio of Max grid voltage for VRT calculation */
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
    /* Ratio of Min grid voltage for VRT calculation */
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin = stPfcDataCalcLoc.stMeasExt.ftVgMinRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: -&Minimum value-Single phase system
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_RmsCalc_MaxMin_1P(void)
{
    float32 l_ftDataTmp1 = 0.0f;
    float32 l_ftDataTmp2 = 0.0f;

    if(TYPE_GRID_AN == stCom.uiTypeGrid)
    {
        l_ftDataTmp1 = stPfcDataCalcLoc.stMeasExt.ftVaRms;
        l_ftDataTmp2 = stPfcDataCalcLoc.stMeasExt.ftIaRms * COEFF_CURR_ARM;
    }
    else if(TYPE_GRID_BN == stCom.uiTypeGrid)
    {
        l_ftDataTmp1 = stPfcDataCalcLoc.stMeasExt.ftVbRms;
        l_ftDataTmp2 = stPfcDataCalcLoc.stMeasExt.ftIbRms * COEFF_CURR_ARM;
    }
    else
    {
        l_ftDataTmp1 = stPfcDataCalcLoc.stMeasExt.ftVcRms;
        l_ftDataTmp2 = stPfcDataCalcLoc.stMeasExt.ftIcRms * COEFF_CURR_ARM;
    }

    /* Max,Min and average value of grid voltage RMS calculation */
    stPfcDataCalcLoc.stMeasExt.ftVgMaxRms = l_ftDataTmp1;
    stPfcDataCalcLoc.stMeasExt.ftVgMinRms = l_ftDataTmp1;
    stPfcDataCalcLoc.stMeasExt.ftVgAvgRms = l_ftDataTmp1;
    /* Max,Min value of grid current RMS calculation */
    stPfcDataCalcLoc.stMeasExt.uiIgMaxRms100Times = (Uint16)(l_ftDataTmp2);
    stPfcDataCalcLoc.stMeasExt.uiIgMinRms100Times = (Uint16)(l_ftDataTmp2);
    /* Ratio of grid voltage for VRT calculation */
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMax = stPfcDataCalcLoc.stMeasExt.ftVgMaxRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
    stPfcDataCalcLoc.stMeasExt.ftRatVoltVrtMin = stPfcDataCalcLoc.stMeasExt.ftVgMinRms * stPfcDataCalcLoc.stSysExt.ftVoltRtdRecpr;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: DC component calculation Init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_DcCptCalc_Init(void)
{
    stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times = 0U;        ///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times   = 0;         ///< Initialize to 0
    stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times = 0U;        ///< Initialize to 0U

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stMeasParm.siIaDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.siIbDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.siIcDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.uiCurrDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times;
    stPfcDataCalcDbg.stMeasParm.siVaDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.siVbDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.siVcDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times;
    stPfcDataCalcDbg.stMeasParm.uiVoltDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times;

    stPfcDataCalc.stMeasParm.siIaDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siIaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIbDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siIbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIcDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siIcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiCurrDcMax1000Times = stPfcDataCalcDbg.stMeasParm.uiCurrDcMax1000Times;
    stPfcDataCalc.stMeasParm.siVaDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siVaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVbDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siVbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVcDcAvg1000Times   = stPfcDataCalcDbg.stMeasParm.siVcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiVoltDcMax1000Times = stPfcDataCalcDbg.stMeasParm.uiVoltDcMax1000Times;
#else
    stPfcDataCalc.stMeasParm.siIaDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIbDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIcDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiCurrDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times;
    stPfcDataCalc.stMeasParm.siVaDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVbDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVcDcAvg1000Times   = stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiVoltDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: DC component calculation 1ms task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_DcCptCalc_1ms(void)
{
    if(OFFGRID_MODE == stComIf.uiModPfcRun)
    {
        v_PfcDataCalc_DcCptCalc_Volt();    ///< Voltage DC component calculation 1ms task in off-grid mode
    }
    else
    {
        v_PfcDataCalc_DcCptCalc_Curr();    ///< Current DC component calculation 1ms task in on-grid mode
    }

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.siIaDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siIaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIbDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siIbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIcDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siIcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiCurrDcMax1000Times = stPfcDataCalcDbg.stMeasParm.uiCurrDcMax1000Times;
    stPfcDataCalc.stMeasParm.siVaDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siVaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVbDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siVbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVcDcAvg1000Times = stPfcDataCalcDbg.stMeasParm.siVcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiVoltDcMax1000Times = stPfcDataCalcDbg.stMeasParm.uiVoltDcMax1000Times;
#else
    stPfcDataCalc.stMeasParm.siIaDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIbDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siIcDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiCurrDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times;
    stPfcDataCalc.stMeasParm.siVaDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVbDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times;
    stPfcDataCalc.stMeasParm.siVcDcAvg1000Times = stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times;
    stPfcDataCalc.stMeasParm.uiVoltDcMax1000Times = stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: DC component calculation 1ms task - Voltage component
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_DcCptCalc_Volt(void)
{
    float32 ftLpfIn = 0.0f;
    static float32 ftLpfOut1 = 0.0f;
    Uint16 l_uiAbsVaDc = 0U;
#if  GRID_PHASE_NUMBER > 1U
    static float32 ftLpfOut2 = 0.0f;
    Uint16 l_uiAbsVbDc = 0U;
#if  3U == GRID_PHASE_NUMBER
    static float32 ftLpfOut3 = 0.0f;
    Uint16 l_uiAbsVcDc = 0U;
#endif
#endif

    /* Average value of phase A grid voltage DC components */
    ftLpfIn = stPfcDataCalcLoc.stVdc.ftASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    vFcn_1stOrdLPF(&ftLpfOut1, ftLpfIn, COEFF_LPF_10HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times = (int16)ftLpfOut1;
    l_uiAbsVaDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times);
#if 1U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times = l_uiAbsVaDc;
#else
    /* Average value of phase B grid voltage DC components */
    ftLpfIn = stPfcDataCalcLoc.stVdc.ftBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    vFcn_1stOrdLPF(&ftLpfOut2, ftLpfIn, COEFF_LPF_10HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times = (int16)ftLpfOut2;
    l_uiAbsVbDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times);
    #if 2U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times = ftFcn_MaxOfTwo(l_uiAbsVaDc, l_uiAbsVbDc);
    #else
    /* Average value of phase C grid voltage DC components */
    ftLpfIn = stPfcDataCalcLoc.stVdc.ftCSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    vFcn_1stOrdLPF(&ftLpfOut3, ftLpfIn, COEFF_LPF_10HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times = (int16)ftLpfOut3;
    l_uiAbsVcDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times);
    stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times = ftFcn_MaxOfThree(l_uiAbsVaDc, l_uiAbsVbDc, l_uiAbsVcDc);
    #endif
#endif

    /* Average value of grid current DC components are clear to 0 */
    stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times = 0U;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: DC component calculation 1ms task - Current component
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_DcCptCalc_Curr(void)
{
    float32 ftLpfIn = 0.0f;
    Uint16 l_uiAbsIaDc = 0U;
#if  GRID_PHASE_NUMBER > 1U
    Uint16 l_uiAbsIbDc = 0U;
#if  3U == GRID_PHASE_NUMBER
    Uint16 l_uiAbsIcDc = 0U;
#endif
#endif

    /* Average value of phase A grid current DC components */
    ftLpfIn = stPfcDataCalcLoc.stIdc.ftASum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times = (int16)ftLpfIn;
    l_uiAbsIaDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siIaDcAvg1000Times);
#if 1U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times = l_uiAbsIaDc;
#else
    /* Average value of phase B grid current DC components */
    ftLpfIn = stPfcDataCalcLoc.stIdc.ftBSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times = (int16)ftLpfIn;
    l_uiAbsIbDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siIbDcAvg1000Times);
    #if 2U == GRID_PHASE_NUMBER
    stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times = ftFcn_MaxOfTwo(l_uiAbsIaDc, l_uiAbsIbDc);
    #else
    /* Average value of phase C grid current DC components */
    ftLpfIn = stPfcDataCalcLoc.stIdc.ftCSum * stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints * COEFF_DC_ARM;
    stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times = (int16)ftLpfIn;
    l_uiAbsIcDc = ABS_INT(stPfcDataCalcLoc.stMeasExt.siIcDcAvg1000Times);
    stPfcDataCalcLoc.stMeasExt.uiCurrDcMax1000Times = ftFcn_MaxOfThree(l_uiAbsIaDc, l_uiAbsIbDc, l_uiAbsIcDc);
    #endif
#endif

    /* Average value of grid voltage DC components are clear to 0 */
    stPfcDataCalcLoc.stMeasExt.siVaDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.siVbDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.siVcDcAvg1000Times   = 0;
    stPfcDataCalcLoc.stMeasExt.uiVoltDcMax1000Times = 0U;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Frequency calculation Init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_Init(void)
{
    Uint16 i = 0U;

    stPfcDataCalcLoc.stFrqA.uiIndex  = 0U;                 ///< Initialize to 0U
    stPfcDataCalcLoc.stFrqA.ulPHTSum = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqA.ulPHTAvg = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqA.ulPHT    = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqA.ftFrqVal = RATED_AC_FRQ;       ///< Initialize to RATED_AC_FRQ

    stPfcDataCalcLoc.stFrqB.uiIndex  = 0U;                 ///< Initialize to 0U
    stPfcDataCalcLoc.stFrqB.ulPHTSum = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqB.ulPHTAvg = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqB.ulPHT    = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqB.ftFrqVal = RATED_AC_FRQ;       ///< Initialize to RATED_AC_FRQ

    stPfcDataCalcLoc.stFrqC.uiIndex  = 0U;                 ///< Initialize to 0U
    stPfcDataCalcLoc.stFrqC.ulPHTSum = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqC.ulPHTAvg = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqC.ulPHT    = 0UL;                ///< Initialize to 0UL
    stPfcDataCalcLoc.stFrqC.ftFrqVal = RATED_AC_FRQ;       ///< Initialize to RATED_AC_FRQ

    for(i = 0U; i < FRQ_ARRAY_LEN; i++)
    {
        stPfcDataCalcLoc.stFrqA.ulPHTArray[i] = 0UL;        ///< Initialize to 0UL
        stPfcDataCalcLoc.stFrqB.ulPHTArray[i] = 0UL;        ///< Initialize to 0UL
        stPfcDataCalcLoc.stFrqC.ulPHTArray[i] = 0UL;        ///< Initialize to 0UL
    }

    stPfcDataCalcLoc.stRoCoF.uiFlgPha       = ROCOF_FLAG_PHASE_A;    ///< Initialize to phase A flag
    stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross = FCN_DISABLE;           ///< Initialize to disable
    stPfcDataCalcLoc.stRoCoF.uiIdxArry      = 0U;                    ///< Initialize to 0U
    for(i = 0U; i < ROCOF_ARRAY_LEN; i++)
    {
        stPfcDataCalcLoc.stRoCoF.ftFrqArry[i] = RATED_AC_FRQ;        ///< Initialize to RATED_AC_FRQ
    }

    stPfcDataCalcLoc.stMeasExt.ftFrqVaCap = RATED_AC_FRQ;        ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftFrqVbCap = RATED_AC_FRQ;        ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftFrqVcCap = RATED_AC_FRQ;        ///< Initialize to rated frequency

    stPfcDataCalcLoc.stMeasExt.ftFrqCapMax    = RATED_AC_FRQ;    ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftFrqCapMin    = RATED_AC_FRQ;    ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF = RATED_AC_FRQ;    ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF = RATED_AC_FRQ;    ///< Initialize to rated frequency
    stPfcDataCalcLoc.stMeasExt.ftRoCoF        = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof   = (float32)ROCOF_ARRAY_LEN/RATED_AC_FRQ;

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stMeasParm.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
    stPfcDataCalcDbg.stMeasParm.ftFrqVbCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
    stPfcDataCalcDbg.stMeasParm.ftFrqVcCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVcCap;
    stPfcDataCalcDbg.stMeasParm.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMax;
    stPfcDataCalcDbg.stMeasParm.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMin;
    stPfcDataCalcDbg.stMeasParm.ftFrqCapAvgLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
    stPfcDataCalcDbg.stMeasParm.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF;
    stPfcDataCalcDbg.stMeasParm.ftRoCoF        = stPfcDataCalcLoc.stMeasExt.ftRoCoF;
    stPfcDataCalcDbg.stMeasParm.ftTiSumRoCof   = stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof;

    stPfcDataCalc.stMeasParm.ftFrqVaCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVaCap;
    stPfcDataCalc.stMeasParm.ftFrqVbCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVbCap;
    stPfcDataCalc.stMeasParm.ftFrqVcCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVcCap;
    stPfcDataCalc.stMeasParm.ftFrqCapMax    = stPfcDataCalcDbg.stMeasParm.ftFrqCapMax;
    stPfcDataCalc.stMeasParm.ftFrqCapMin    = stPfcDataCalcDbg.stMeasParm.ftFrqCapMin;
    stPfcDataCalc.stMeasParm.ftFrqCapAvgLPF = stPfcDataCalcDbg.stMeasParm.ftFrqCapAvgLPF;
    stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF = stPfcDataCalcDbg.stMeasParm.ftFrqCap6HzLPF;
    stPfcDataCalc.stMeasParm.ftRoCoF        = stPfcDataCalcDbg.stMeasParm.ftRoCoF;
    stPfcDataCalc.stMeasParm.ftTiSumRoCof   = stPfcDataCalcDbg.stMeasParm.ftTiSumRoCof;
#else
    stPfcDataCalc.stMeasParm.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
    stPfcDataCalc.stMeasParm.ftFrqVbCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
    stPfcDataCalc.stMeasParm.ftFrqVcCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVcCap;
    stPfcDataCalc.stMeasParm.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMax;
    stPfcDataCalc.stMeasParm.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMin;
    stPfcDataCalc.stMeasParm.ftFrqCapAvgLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
    stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF;
    stPfcDataCalc.stMeasParm.ftRoCoF        = stPfcDataCalcLoc.stMeasExt.ftRoCoF;
    stPfcDataCalc.stMeasParm.ftTiSumRoCof   = stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Frequency calculation 1ms task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_1ms(void)
{
    float32 l_ftFrqAvgLpfInp = 0.0f;

    /* CAP Frequency calculation 1ms task */
    v_PfcDataCalc_FrqCalc_Samp_1ms();

#if 1U == GRID_PHASE_NUMBER
    if(stPfcDataCalcLoc.stMeasExt.ftVgMinRms > FRQCALC_VOLT_LIM)    ///> Grid voltage is more than FRQCALC_VOLT_LIM
    {
        /* Average CAP frequency calculation */
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqA);
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap = stPfcDataCalcLoc.stFrqA.ftFrqVal;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap = 0.0f;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap = 0.0f;
        /* Max,Min CAP frequency calculation */
        l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMax = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMin = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
        /* LPF of CAP frequency calculation */
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, l_ftFrqAvgLpfInp, COEFF_LPF_50HZ_1MS);
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF, stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, COEFF_LPF_6HZ_1MS);
    }
    else    ///> Grid voltage is less than FRQCALC_VOLT_LIM
    {
        stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF = stComTbl.stPrmPfcRtd1.ftFrqGrid;
        stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap     = 0.0f;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap     = 0.0f;
    }
#elif 2U == GRID_PHASE_NUMBER
    if(stPfcDataCalcLoc.stMeasExt.ftVgMinRms > FRQCALC_VOLT_LIM)    ///> Grid voltage is more than FRQCALC_VOLT_LIM
    {
        /* Average CAP frequency calculation */
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqA);
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqB);
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap = stPfcDataCalcLoc.stFrqA.ftFrqVal;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap = stPfcDataCalcLoc.stFrqB.ftFrqVal;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap = 0.0f;
        /* Max,Min CAP frequency calculation */
        if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)    ///< Phase full run mode
        {
            l_ftFrqAvgLpfInp = (stPfcDataCalcLoc.stMeasExt.ftFrqVaCap + stPfcDataCalcLoc.stMeasExt.ftFrqVbCap) * RECPR_CON_2;
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMax = ftFcn_MaxOfTwo(stPfcDataCalcLoc.stMeasExt.ftFrqVaCap,stPfcDataCalcLoc.stMeasExt.ftFrqVbCap);
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMin = ftFcn_MinOfTwo(stPfcDataCalcLoc.stMeasExt.ftFrqVaCap,stPfcDataCalcLoc.stMeasExt.ftFrqVbCap);
        }
        else
        {
            if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
            }
            else
            {
                l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
            }
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMax = l_ftFrqAvgLpfInp;
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMin = l_ftFrqAvgLpfInp;
        }
        /* LPF of CAP frequency calculation */
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, l_ftFrqAvgLpfInp, COEFF_LPF_50HZ_1MS);
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF, stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, COEFF_LPF_6HZ_1MS);
    }
    else    ///> Grid voltage is less than FRQCALC_VOLT_LIM
    {
        stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF = stComTbl.stPrmPfcRtd1.ftFrqGrid;
        stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap     = 0.0f;
    }
#elif 3U == GRID_PHASE_NUMBER
    if(stPfcDataCalcLoc.stMeasExt.ftVgMinRms > FRQCALC_VOLT_LIM)    ///> Grid voltage is more than FRQCALC_VOLT_LIM
    {
        /* Average CAP frequency calculation */
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqA);
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqB);
        v_PfcDataCalc_FrqCalc_Avg_1ms(&stPfcDataCalcLoc.stFrqC);
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap = stPfcDataCalcLoc.stFrqA.ftFrqVal;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap = stPfcDataCalcLoc.stFrqB.ftFrqVal;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap = stPfcDataCalcLoc.stFrqC.ftFrqVal;
        /* Max,Min CAP frequency calculation */
        if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)    ///< Phase full run mode
        {
            l_ftFrqAvgLpfInp = (stPfcDataCalcLoc.stMeasExt.ftFrqVaCap + stPfcDataCalcLoc.stMeasExt.ftFrqVbCap + stPfcDataCalcLoc.stMeasExt.ftFrqVcCap) * RECPR_CON_3;
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMax = ftFcn_MaxOfThree(stPfcDataCalcLoc.stMeasExt.ftFrqVaCap,stPfcDataCalcLoc.stMeasExt.ftFrqVbCap,stPfcDataCalcLoc.stMeasExt.ftFrqVcCap);
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMin = ftFcn_MinOfThree(stPfcDataCalcLoc.stMeasExt.ftFrqVaCap,stPfcDataCalcLoc.stMeasExt.ftFrqVbCap,stPfcDataCalcLoc.stMeasExt.ftFrqVcCap);
        }
        else
        {
            if(TYPE_GRID_AN == stCom.uiTypeGrid)
            {
                l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
            }
            else if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
            }
            else
            {
                l_ftFrqAvgLpfInp = stPfcDataCalcLoc.stMeasExt.ftFrqVcCap;
            }
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMax = l_ftFrqAvgLpfInp;
            stPfcDataCalcLoc.stMeasExt.ftFrqCapMin = l_ftFrqAvgLpfInp;
        }
        /* LPF of CAP frequency calculation */
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, l_ftFrqAvgLpfInp, COEFF_LPF_50HZ_1MS);
        vFcn_1stOrdLPF(&stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF, stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF, COEFF_LPF_6HZ_1MS);
    }
    else    ///> Grid voltage is less than FRQCALC_VOLT_LIM
    {
        stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF = stComTbl.stPrmPfcRtd1.ftFrqGrid;
        stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVbCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
        stPfcDataCalcLoc.stMeasExt.ftFrqVcCap     = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
    }
#endif

    /* RoCoF value calculation */
    v_PfcDataCalc_FrqCalc_RoCoF_1ms();///< sst no use

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.ftFrqVaCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVaCap;
    stPfcDataCalc.stMeasParm.ftFrqVbCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVbCap;
    stPfcDataCalc.stMeasParm.ftFrqVcCap     = stPfcDataCalcDbg.stMeasParm.ftFrqVcCap;
    stPfcDataCalc.stMeasParm.ftFrqCapMax    = stPfcDataCalcDbg.stMeasParm.ftFrqCapMax;
    stPfcDataCalc.stMeasParm.ftFrqCapMin    = stPfcDataCalcDbg.stMeasParm.ftFrqCapMin;
    stPfcDataCalc.stMeasParm.ftFrqCapAvgLPF = stPfcDataCalcDbg.stMeasParm.ftFrqCapAvgLPF;
    stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF = stPfcDataCalcDbg.stMeasParm.ftFrqCap6HzLPF;
#else
    stPfcDataCalc.stMeasParm.ftFrqVaCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
    stPfcDataCalc.stMeasParm.ftFrqVbCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
    stPfcDataCalc.stMeasParm.ftFrqVcCap     = stPfcDataCalcLoc.stMeasExt.ftFrqVcCap;
    stPfcDataCalc.stMeasParm.ftFrqCapMax    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMax;
    stPfcDataCalc.stMeasParm.ftFrqCapMin    = stPfcDataCalcLoc.stMeasExt.ftFrqCapMin;
    stPfcDataCalc.stMeasParm.ftFrqCapAvgLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCapAvgLPF;
    stPfcDataCalc.stMeasParm.ftFrqCap6HzLPF = stPfcDataCalcLoc.stMeasExt.ftFrqCap6HzLPF;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Frequency calculation 1ms task-Average value calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_Avg_1ms(ST_FRQ_CALC *pData)
{
    /* Average value calculation */
    pData->ulPHTAvg = (pData->ulPHTSum >> DIVNUM_FRQ_AVG);

    if (pData->ulPHTAvg > 0U)
    {
        pData->ftFrqVal = (float32)COEFF_ECAP / (float32)pData->ulPHTAvg;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: Frequency calculation 1ms task-RoCoF value calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_RoCoF_1ms(void)
{
    float32 l_ftFrqInp = 0.0;    ///< Frequency input

    if(FCN_ENABLE == stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross)    ///< If zero crossing flag is set
    {
        stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross = FCN_DISABLE;    ///< Clear zero crossing flag

        if(ROCOF_FLAG_PHASE_A == stPfcDataCalcLoc.stRoCoF.uiFlgPha)
        {
            l_ftFrqInp = stPfcDataCalcLoc.stMeasExt.ftFrqVaCap;
        }
        else if(ROCOF_FLAG_PHASE_B == stPfcDataCalcLoc.stRoCoF.uiFlgPha)
        {
            l_ftFrqInp = stPfcDataCalcLoc.stMeasExt.ftFrqVbCap;
        }
        else
        {
            l_ftFrqInp = stPfcDataCalcLoc.stMeasExt.ftFrqVcCap;
        }

        /* Calculate slip window time sum and RoCoF */
        if((l_ftFrqInp > CON_ZERO_DELTA) && (stPfcDataCalcLoc.stRoCoF.ftFrqArry[stPfcDataCalcLoc.stRoCoF.uiIdxArry] > CON_ZERO_DELTA))
        {
            stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof += (1.0f/l_ftFrqInp - 1.0f/stPfcDataCalcLoc.stRoCoF.ftFrqArry[stPfcDataCalcLoc.stRoCoF.uiIdxArry]);
            if(stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof > CON_ZERO_DELTA)
            {
                stPfcDataCalcLoc.stMeasExt.ftRoCoF = fabsf(l_ftFrqInp - stPfcDataCalcLoc.stRoCoF.ftFrqArry[stPfcDataCalcLoc.stRoCoF.uiIdxArry]) / stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof;
            }
        }

        /* Update array value and index */
        stPfcDataCalcLoc.stRoCoF.ftFrqArry[stPfcDataCalcLoc.stRoCoF.uiIdxArry] = l_ftFrqInp;
        stPfcDataCalcLoc.stRoCoF.uiIdxArry++;
        if(stPfcDataCalcLoc.stRoCoF.uiIdxArry >= ROCOF_ARRAY_LEN)
        {
            stPfcDataCalcLoc.stRoCoF.uiIdxArry = 0U;
        }

        /* Global parameter */
#if 1U == PFC_DATACALC_DBG
        stPfcDataCalc.stMeasParm.ftRoCoF      = stPfcDataCalcDbg.stMeasParm.ftRoCoF;
        stPfcDataCalc.stMeasParm.ftTiSumRoCof = stPfcDataCalcDbg.stMeasParm.ftTiSumRoCof;
#else
        stPfcDataCalc.stMeasParm.ftRoCoF      = stPfcDataCalcLoc.stMeasExt.ftRoCoF; ///< sst no use
        stPfcDataCalc.stMeasParm.ftTiSumRoCof = stPfcDataCalcLoc.stMeasExt.ftTiSumRoCof;
#endif /* PFC_DATACALC_DBG */
    }
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        Sub unit function: Frequency calculation 1ms task- frequency sample
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_Samp_1ms(void)
{
#ifndef _SIMULATION_NO_DSP_
    /* Average of Phase A CAP register result */
    if((stECapDrv.ulCntrEcapRegA < MAX_PERIOD_ECAP) && (stECapDrv.ulCntrEcapRegA > MIN_PERIOD_ECAP))
    {
        stPfcDataCalcLoc.stFrqA.ulPHT = stECapDrv.ulCntrEcapRegA;
        v_PfcDataCalc_FrqCalc_Samp_Avg(&stPfcDataCalcLoc.stFrqA);

        if(ROCOF_FLAG_PHASE_A == stPfcDataCalcLoc.stRoCoF.uiFlgPha)
        {
            stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross = FCN_ENABLE;    ///< Set ROCOF zero crossing flag
        }
    }

    #if GRID_PHASE_NUMBER > 1U
     /* Average of Phase B CAP register result */
    if((stECapDrv.ulCntrEcapRegB < MAX_PERIOD_ECAP) && (stECapDrv.ulCntrEcapRegB > MIN_PERIOD_ECAP))
    {
         stPfcDataCalcLoc.stFrqB.ulPHT = stECapDrv.ulCntrEcapRegB;
         v_PfcDataCalc_FrqCalc_Samp_Avg(&stPfcDataCalcLoc.stFrqB);

         if(ROCOF_FLAG_PHASE_B == stPfcDataCalcLoc.stRoCoF.uiFlgPha)
         {
             stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross = FCN_ENABLE;    ///< Set ROCOF zero crossing flag
         }
    }
    #if GRID_PHASE_NUMBER > 2U
    /* Average of Phase C CAP register result */
    if((stECapDrv.ulCntrEcapRegC < MAX_PERIOD_ECAP) && (stECapDrv.ulCntrEcapRegC > MIN_PERIOD_ECAP))
    {
        stPfcDataCalcLoc.stFrqC.ulPHT = stECapDrv.ulCntrEcapRegC;
        v_PfcDataCalc_FrqCalc_Samp_Avg(&stPfcDataCalcLoc.stFrqC);

        if(ROCOF_FLAG_PHASE_C == stPfcDataCalcLoc.stRoCoF.uiFlgPha)
        {
            stPfcDataCalcLoc.stRoCoF.uiFlgZeroCross = FCN_ENABLE;    ///< Set ROCOF zero crossing flag
        }
    }
    #endif /* GRID_PHASE_NUMBER > 2U */
    #endif /* GRID_PHASE_NUMBER > 1U */
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: Frequency calculation 1ms task-Frequency sample average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_FrqCalc_Samp_Avg(ST_FRQ_CALC *pData)
{
    /* Sum of frequency CAP register result */
    pData->ulPHTSum = pData->ulPHTSum + pData->ulPHT - pData->ulPHTArray[pData->uiIndex];

    pData->ulPHTArray[pData->uiIndex] = pData->ulPHT;
    pData->uiIndex++;
    if(pData->uiIndex >= FRQ_ARRAY_LEN)
    {
       pData->uiIndex = 0U;
    }
}
/*********************************************End**********************************************/


/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_Acm_Init(void)
{
    Uint16 i;

    stPfcDataCalcLoc.uiCntrSampIntl   = 0U;              ///< Initialize to 0U

    stPfcDataCalcLoc.stVFcalc.uiCntrBuf         = 0U;    ///< Initialize to 0U
    stPfcDataCalcLoc.stVFcalc.uiCurrPoints      = stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew;
    stPfcDataCalcLoc.stVFcalc.uiPosnLastLastVal = 0U;    ///< Initialize to 0U
    stPfcDataCalcLoc.stVFcalc.uiPosnLastVal     = 0U;    ///< Initialize to 0U
    stPfcDataCalcLoc.stVFcalc.uiSts             = 0U;    ///< Initialize to 0U
    stPfcDataCalcLoc.stVFcalc.ftRecprRMSPoints  = 1.0f / (float32)stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew;

    stPfcDataCalcLoc.stVolt.ftARmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVolt.ftBRmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVolt.ftCRmsSum = 0.0f;            ///< Initialize to 0.0f

    stPfcDataCalcLoc.stVoltLine.ftARmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVoltLine.ftBRmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVoltLine.ftCRmsSum = 0.0f;            ///< Initialize to 0.0f

    stPfcDataCalcLoc.stVoltInv.ftARmsSum = 0.0f;
    stPfcDataCalcLoc.stVoltInv.ftBRmsSum = 0.0f;
    stPfcDataCalcLoc.stVoltInv.ftCRmsSum = 0.0f;

    stPfcDataCalcLoc.stCurr.ftARmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stCurr.ftBRmsSum = 0.0f;            ///< Initialize to 0.0f
    stPfcDataCalcLoc.stCurr.ftCRmsSum = 0.0f;            ///< Initialize to 0.0f

    stPfcDataCalcLoc.stIn.ftRmsSum = 0.0f;               ///< Initialize to 0.0f

    stPfcDataCalcLoc.stVdc.ftASum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVdc.ftBSum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stVdc.ftCSum = 0.0f;                ///< Initialize to 0.0f

    stPfcDataCalcLoc.stIdc.ftASum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stIdc.ftBSum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stIdc.ftCSum = 0.0f;                ///< Initialize to 0.0f

    stPfcDataCalcLoc.stPwr.ftPASum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stPwr.ftPBSum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stPwr.ftPCSum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stPwr.ftQASum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stPwr.ftQBSum = 0.0f;                ///< Initialize to 0.0f
    stPfcDataCalcLoc.stPwr.ftQCSum = 0.0f;                ///< Initialize to 0.0f

    for(i = 0U; i < MAX_RMS_NUM; i++)
    {
        stPfcDataCalcLoc.stVolt.ftARmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVolt.ftBRmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVolt.ftCRmsStore[i] = 0.0f;    ///< Initialize to 0.0f

        stPfcDataCalcLoc.stVoltLine.ftARmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVoltLine.ftBRmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVoltLine.ftCRmsStore[i] = 0.0f;    ///< Initialize to 0.0f

        stPfcDataCalcLoc.stVoltInv.ftARmsStore[i] = 0.0f;
        stPfcDataCalcLoc.stVoltInv.ftBRmsStore[i] = 0.0f;
        stPfcDataCalcLoc.stVoltInv.ftCRmsStore[i] = 0.0f;

        stPfcDataCalcLoc.stCurr.ftARmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stCurr.ftBRmsStore[i] = 0.0f;    ///< Initialize to 0.0f
        stPfcDataCalcLoc.stCurr.ftCRmsStore[i] = 0.0f;    ///< Initialize to 0.0f

        stPfcDataCalcLoc.stIn.ftRmsStore[i] = 0.0f;       ///< Initialize to 0.0f

        stPfcDataCalcLoc.stVdc.ftAStore[i] = 0.0f;        ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVdc.ftBStore[i] = 0.0f;        ///< Initialize to 0.0f
        stPfcDataCalcLoc.stVdc.ftCStore[i] = 0.0f;        ///< Initialize to 0.0f

        stPfcDataCalcLoc.stIdc.ftAStore[i] = 0.0f;        ///< Initialize to 0.0f
        stPfcDataCalcLoc.stIdc.ftBStore[i] = 0.0f;        ///< Initialize to 0.0f
        stPfcDataCalcLoc.stIdc.ftCStore[i] = 0.0f;        ///< Initialize to 0.0f

        stPfcDataCalcLoc.stPwr.ftPAStore[i] = 0.0f;       ///< Initialize to 0.0f
        stPfcDataCalcLoc.stPwr.ftPBStore[i] = 0.0f;       ///< Initialize to 0.0f
        stPfcDataCalcLoc.stPwr.ftPCStore[i] = 0.0f;       ///< Initialize to 0.0f
        stPfcDataCalcLoc.stPwr.ftQAStore[i] = 0.0f;       ///< Initialize to 0.0f
        stPfcDataCalcLoc.stPwr.ftQBStore[i] = 0.0f;       ///< Initialize to 0.0f
        stPfcDataCalcLoc.stPwr.ftQCStore[i] = 0.0f;       ///< Initialize to 0.0f
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Isr(void)
{
    if(++stPfcDataCalcLoc.uiCntrSampIntl >= ISR_INTL_RMS_CALC)    ///< 8 interrupt periods
    {
        stPfcDataCalcLoc.uiCntrSampIntl = 0U;
        /* VF Point calculation */
        v_PfcDataCalc_Acm_VFPoint_Isr();

#if 1U == GRID_PHASE_NUMBER
        /* Grid RMS accumulation calculation */
        v_PfcDataCalc_Acm_Rms1P_Isr(&stPfcAdc.stVg, &stPfcDataCalcLoc.stVolt, &stPfcDataCalcLoc.stVFcalc);
        v_PfcDataCalc_Acm_Rms1P_Isr(&stPfcAdc.stIg, &stPfcDataCalcLoc.stCurr, &stPfcDataCalcLoc.stVFcalc);

        if(OFFGRID_MODE == stComIf.uiModPfcRun)
        {
            /* Grid voltage DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg1P_Isr(&stPfcAdc.stVgDc, &stPfcDataCalcLoc.stVdc, &stPfcDataCalcLoc.stVFcalc);
        }
        else
        {
            /* Grid current DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg1P_Isr(&stPfcAdc.stIgDc, &stPfcDataCalcLoc.stIdc, &stPfcDataCalcLoc.stVFcalc);
        }

        /* Power accumulation calculation */
        stVgIg.ftVaMpf = stPfcPowCtrl.ftVaSogiBpf;
        stVgIg.ftVaLpf = stPfcPowCtrl.ftVaSogiLpf;
        v_PfcDataCalc_Acm_Pwr1P_Isr(&stPfcDataCalcLoc.stPwr, &stPfcDataCalcLoc.stVFcalc);
#elif 2U == GRID_PHASE_NUMBER
        /* Grid RMS accumulation calculation */
        v_PfcDataCalc_Acm_Rms2P_Isr(&stPfcAdc.stVg, &stPfcDataCalcLoc.stVolt, &stPfcDataCalcLoc.stVFcalc);
		v_PfcDataCalc_Acm_Rms2P_Isr(&stPfcAdc.stVgInv, &stPfcDataCalcLoc.stVoltInv, &stPfcDataCalcLoc.stVFcalc);
        v_PfcDataCalc_Acm_Rms2P_Isr(&stPfcAdc.stIg, &stPfcDataCalcLoc.stCurr, &stPfcDataCalcLoc.stVFcalc);
        v_PfcDataCalc_Acm_Rms_Isr(stPfcAdc.stIg.ftValLpf10kHz_N, &stPfcDataCalcLoc.stIn, &stPfcDataCalcLoc.stVFcalc);

        if(OFFGRID_MODE == stComIf.uiModPfcRun)
        {
            /* Grid voltage DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg2P_Isr(&stPfcAdc.stVgDc, &stPfcDataCalcLoc.stVdc, &stPfcDataCalcLoc.stVFcalc);
        }
        else
        {
            /* Grid current DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg2P_Isr(&stPfcAdc.stIgDc, &stPfcDataCalcLoc.stIdc, &stPfcDataCalcLoc.stVFcalc);
        }
        /* Power accumulation accumulation calculation */
        stVgIg.ftVaMpf = stPfcAdc.stVg.ftValLpf10kHz_A;
        stVgIg.ftVbMpf = stPfcAdc.stVg.ftValLpf10kHz_B;
        stVgIg.ftVaLpf = stPfcPowCtrl.ftVa_MPF;
        stVgIg.ftVbLpf = stPfcPowCtrl.ftVb_MPF;
        v_PfcDataCalc_Acm_Pwr2P_Isr(&stPfcDataCalcLoc.stPwr, &stPfcDataCalcLoc.stVFcalc);
#elif 3U == GRID_PHASE_NUMBER
        /* Grid RMS accumulation calculation */
        v_PfcDataCalc_Acm_Rms3P_Isr(&stPfcAdc.stVg, &stPfcDataCalcLoc.stVolt, &stPfcDataCalcLoc.stVFcalc);
        if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)
        {
            v_PfcDataCalc_Acm_Rms3P_Isr(&stPfcAdc.stVgLine, &stPfcDataCalcLoc.stVoltLine, &stPfcDataCalcLoc.stVFcalc);
        }
        v_PfcDataCalc_Acm_Rms3P_Isr(&stPfcAdc.stIg, &stPfcDataCalcLoc.stCurr, &stPfcDataCalcLoc.stVFcalc);
        v_PfcDataCalc_Acm_Rms_Isr(stPfcAdc.stIg.ftValLpf10kHz_N, &stPfcDataCalcLoc.stIn, &stPfcDataCalcLoc.stVFcalc);

        if(OFFGRID_MODE == stComIf.uiModPfcRun)
        {
            /* Grid voltage DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg3P_Isr(&stPfcAdc.stVgDc, &stPfcDataCalcLoc.stVdc, &stPfcDataCalcLoc.stVFcalc);
        }
        else
        {
            /* Grid current DC accumulation calculation */
            v_PfcDataCalc_Acm_Avg3P_Isr(&stPfcAdc.stIgDc, &stPfcDataCalcLoc.stIdc, &stPfcDataCalcLoc.stVFcalc);
        }
        /* Power accumulation calculation */
        stVgIg.ftVaMpf = stPfcAdc.stVg.ftValLpf10kHz_A;
        stVgIg.ftVbMpf = stPfcAdc.stVg.ftValLpf10kHz_B;
        stVgIg.ftVcMpf = stPfcAdc.stVg.ftValLpf10kHz_C;
#if 1U == FLG_PFC_POWCTRL_EN
        stVgIg.ftVaLpf = stPfcPowCtrl.ftVa_MPF;
        stVgIg.ftVbLpf = stPfcPowCtrl.ftVb_MPF;
        stVgIg.ftVcLpf = stPfcPowCtrl.ftVc_MPF;
#endif

        v_PfcDataCalc_Acm_Pwr3P_Isr(&stPfcDataCalcLoc.stPwr, &stPfcDataCalcLoc.stVFcalc);
#endif

        stPfcDataCalcLoc.stVFcalc.uiCntrBuf++;
        if(stPfcDataCalcLoc.stVFcalc.uiCntrBuf >= MAX_RMS_NUM)
        {
            stPfcDataCalcLoc.stVFcalc.uiCntrBuf = 0U;
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-VF Point calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_VFPoint_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_VFPoint_Isr(void)
{
    stPfcDataCalcLoc.stVFcalc.uiPosnLastVal = (stPfcDataCalcLoc.stVFcalc.uiCntrBuf + MAX_RMS_NUM - stPfcDataCalcLoc.stVFcalc.uiCurrPoints) % MAX_RMS_NUM;
    stPfcDataCalcLoc.stVFcalc.uiPosnLastLastVal = (stPfcDataCalcLoc.stVFcalc.uiPosnLastVal + 1U) % MAX_RMS_NUM;

    /* Update VF Point */
    if(stPfcDataCalcLoc.stVFcalc.uiCurrPoints < stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew)         ///> Current points are less than calculation points
    {
        stPfcDataCalcLoc.stVFcalc.uiCurrPoints++;
        stPfcDataCalcLoc.stVFcalc.uiSts = 2U;
    }
    else if(stPfcDataCalcLoc.stVFcalc.uiCurrPoints > stPfcDataCalcLoc.stCtrlExt.uiRms_PiontsNew)    ///> Current points are greater than calculation points
    {
        stPfcDataCalcLoc.stVFcalc.uiCurrPoints--;
        stPfcDataCalcLoc.stVFcalc.uiSts = 1U;
    }
    else                                                                                        ///> Current points are equal to calculation points
    {
        stPfcDataCalcLoc.stVFcalc.uiSts = 0U;
    }
}
/*********************************************End**********************************************/

#if 3U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-3-phase VF Rms calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Rms3P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Rms3P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1,ftTempOldB1,ftTempOldC1;
    float32 ftTempOldA2,ftTempOldB2,ftTempOldC2;
    float32 ftNewVal_A,ftNewVal_B,ftNewVal_C;

    ftNewVal_A = pstThreePhaseData->ftValLpf10kHz_A;
    ftNewVal_B = pstThreePhaseData->ftValLpf10kHz_B;
    ftNewVal_C = pstThreePhaseData->ftValLpf10kHz_C;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeRms->ftARmsSum += (ftNewVal_A * ftNewVal_A);    ///< Phase A sum
        pstThreeRms->ftBRmsSum += (ftNewVal_B * ftNewVal_B);    ///< Phase B sum
        pstThreeRms->ftCRmsSum += (ftNewVal_C * ftNewVal_C);    ///< Phase C sum
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastVal];
        ftTempOldC1 = pstThreeRms->ftCRmsStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastLastVal];
        ftTempOldB2 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastLastVal];
        ftTempOldC2 = pstThreeRms->ftCRmsStore[pstCalc->uiPosnLastLastVal];

        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);    ///< Phase A sum
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);
        pstThreeRms->ftARmsSum -= (ftTempOldA2 * ftTempOldA2);

        pstThreeRms->ftBRmsSum += (ftNewVal_B  * ftNewVal_B);    ///< Phase B sum
        pstThreeRms->ftBRmsSum -= (ftTempOldB1 * ftTempOldB1);
        pstThreeRms->ftBRmsSum -= (ftTempOldB2 * ftTempOldB2);

        pstThreeRms->ftCRmsSum += (ftNewVal_C  * ftNewVal_C);    ///< Phase C sum
        pstThreeRms->ftCRmsSum -= (ftTempOldC1 * ftTempOldC1);
        pstThreeRms->ftCRmsSum -= (ftTempOldC2 * ftTempOldC2);

    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove first value from the previous period */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastVal];
        ftTempOldC1 = pstThreeRms->ftCRmsStore[pstCalc->uiPosnLastVal];

        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);    ///< Phase A sum
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);

        pstThreeRms->ftBRmsSum += (ftNewVal_B  * ftNewVal_B);    ///< Phase B sum
        pstThreeRms->ftBRmsSum -= (ftTempOldB1 * ftTempOldB1);

        pstThreeRms->ftCRmsSum += (ftNewVal_C  * ftNewVal_C);    ///< Phase C sum
        pstThreeRms->ftCRmsSum -= (ftTempOldC1 * ftTempOldC1);

    }
    /* Storage new value */
    pstThreeRms->ftARmsStore[pstCalc->uiCntrBuf] = ftNewVal_A;
    pstThreeRms->ftBRmsStore[pstCalc->uiCntrBuf] = ftNewVal_B;
    pstThreeRms->ftCRmsStore[pstCalc->uiCntrBuf] = ftNewVal_C;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-3-phase VF average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Avg3P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Avg3P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1,ftTempOldB1,ftTempOldC1;
    float32 ftTempOldA2,ftTempOldB2,ftTempOldC2;
    float32 ftNewVal_A,ftNewVal_B,ftNewVal_C;

    ftNewVal_A = pstThreePhaseData->ftVal_A;
    ftNewVal_B = pstThreePhaseData->ftVal_B;
    ftNewVal_C = pstThreePhaseData->ftVal_C;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeAvg->ftASum += ftNewVal_A;    ///< Phase A sum
        pstThreeAvg->ftBSum += ftNewVal_B;    ///< Phase B sum
        pstThreeAvg->ftCSum += ftNewVal_C;    ///< Phase C sum
    }
    else if(pstCalc->uiSts == 1U)
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastVal];
        ftTempOldC1 = pstThreeAvg->ftCStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastLastVal];
        ftTempOldB2 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastLastVal];
        ftTempOldC2 = pstThreeAvg->ftCStore[pstCalc->uiPosnLastLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;    ///< Phase A sum
        pstThreeAvg->ftASum -= ftTempOldA1;
        pstThreeAvg->ftASum -= ftTempOldA2;

        pstThreeAvg->ftBSum += ftNewVal_B;    ///< Phase B sum
        pstThreeAvg->ftBSum -= ftTempOldB1;
        pstThreeAvg->ftBSum -= ftTempOldB2;

        pstThreeAvg->ftCSum += ftNewVal_C;    ///< Phase C sum
        pstThreeAvg->ftCSum -= ftTempOldC1;
        pstThreeAvg->ftCSum -= ftTempOldC2;

    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastVal];
        ftTempOldC1 = pstThreeAvg->ftCStore[pstCalc->uiPosnLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;    ///< Phase A sum
        pstThreeAvg->ftASum -= ftTempOldA1;

        pstThreeAvg->ftBSum += ftNewVal_B;    ///< Phase B sum
        pstThreeAvg->ftBSum -= ftTempOldB1;

        pstThreeAvg->ftCSum += ftNewVal_C;    ///< Phase C sum
        pstThreeAvg->ftCSum -= ftTempOldC1;
    }
    /* Storage new value */
    pstThreeAvg->ftAStore[pstCalc->uiCntrBuf] = ftNewVal_A;
    pstThreeAvg->ftBStore[pstCalc->uiCntrBuf] = ftNewVal_B;
    pstThreeAvg->ftCStore[pstCalc->uiCntrBuf] = ftNewVal_C;
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-3-phase VF average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Pwr3P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Pwr3P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftPTmpOldA1 = 0.0f, ftQTmpOldA1 = 0.0f;
    float32 ftPTmpOldA2 = 0.0f, ftQTmpOldA2 = 0.0f;
    float32 ftPNewVal_A = 0.0f, ftQNewVal_A = 0.0f;
    float32 ftPTmpOldB1 = 0.0f, ftQTmpOldB1 = 0.0f;
    float32 ftPTmpOldB2 = 0.0f, ftQTmpOldB2 = 0.0f;
    float32 ftPNewVal_B = 0.0f, ftQNewVal_B = 0.0f;
    float32 ftPTmpOldC1 = 0.0f, ftQTmpOldC1 = 0.0f;
    float32 ftPTmpOldC2 = 0.0f, ftQTmpOldC2 = 0.0f;
    float32 ftPNewVal_C = 0.0f, ftQNewVal_C = 0.0f;

    ftPNewVal_A = stVgIg.ftVaMpf * stPfcAdc.stIg.ftValLpf10kHz_A;
    ftQNewVal_A = stVgIg.ftVaLpf * stPfcAdc.stIg.ftValLpf10kHz_A;
    ftPNewVal_B = stVgIg.ftVbMpf * stPfcAdc.stIg.ftValLpf10kHz_B;
    ftQNewVal_B = stVgIg.ftVbLpf * stPfcAdc.stIg.ftValLpf10kHz_B;
    ftPNewVal_C = stVgIg.ftVcMpf * stPfcAdc.stIg.ftValLpf10kHz_C;
    ftQNewVal_C = stVgIg.ftVcLpf * stPfcAdc.stIg.ftValLpf10kHz_C;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreePwr->ftPASum += ftPNewVal_A;    ///< Phase A active power sum
        pstThreePwr->ftQASum += ftQNewVal_A;    ///< Phase A reactive power sum

        pstThreePwr->ftPBSum += ftPNewVal_B;    ///< Phase B active power sum
        pstThreePwr->ftQBSum += ftQNewVal_B;    ///< Phase B reactive power sum

        pstThreePwr->ftPCSum += ftPNewVal_C;    ///< Phase C active power sum
        pstThreePwr->ftQCSum += ftQNewVal_C;    ///< Phase C reactive power sum
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];
        ftPTmpOldA2 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftPASum += ftPNewVal_A;    ///< Phase A active power sum
        pstThreePwr->ftPASum -= ftPTmpOldA1;
        pstThreePwr->ftPASum -= ftPTmpOldA2;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];
        ftQTmpOldA2 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftQASum += ftQNewVal_A;    ///< Phase A reactive power sum
        pstThreePwr->ftQASum -= ftQTmpOldA1;
        pstThreePwr->ftQASum -= ftQTmpOldA2;

        ftPTmpOldB1 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastVal];
        ftPTmpOldB2 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftPBSum += ftPNewVal_B;    ///< Phase B active power sum
        pstThreePwr->ftPBSum -= ftPTmpOldB1;
        pstThreePwr->ftPBSum -= ftPTmpOldB2;

        ftQTmpOldB1 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastVal];
        ftQTmpOldB2 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftQBSum += ftQNewVal_B;    ///< Phase B reactive power sum
        pstThreePwr->ftQBSum -= ftQTmpOldB1;
        pstThreePwr->ftQBSum -= ftQTmpOldB2;

        ftPTmpOldC1 = pstThreePwr->ftPCStore[pstCalc->uiPosnLastVal];
        ftPTmpOldC2 = pstThreePwr->ftPCStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftPCSum += ftPNewVal_C;    ///< Phase C active power sum
        pstThreePwr->ftPCSum -= ftPTmpOldC1;
        pstThreePwr->ftPCSum -= ftPTmpOldC2;

        ftQTmpOldC1 = pstThreePwr->ftQCStore[pstCalc->uiPosnLastVal];
        ftQTmpOldC2 = pstThreePwr->ftQCStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftQCSum += ftQNewVal_C;    ///< Phase C reactive power sum
        pstThreePwr->ftQCSum -= ftQTmpOldC1;
        pstThreePwr->ftQCSum -= ftQTmpOldC2;
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftPASum += ftPNewVal_A;    ///< Phase A active power sum
        pstThreePwr->ftPASum -= ftPTmpOldA1;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftQASum += ftQNewVal_A;    ///< Phase A reactive power sum
        pstThreePwr->ftQASum -= ftQTmpOldA1;

        ftPTmpOldB1 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftPBSum += ftPNewVal_B;    ///< Phase B active power sum
        pstThreePwr->ftPBSum -= ftPTmpOldB1;

        ftQTmpOldB1 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftQBSum += ftQNewVal_B;    ///< Phase B reactive power sum
        pstThreePwr->ftQBSum -= ftQTmpOldB1;

        ftPTmpOldC1 = pstThreePwr->ftPCStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftPCSum += ftPNewVal_C;    ///< Phase C active power sum
        pstThreePwr->ftPCSum -= ftPTmpOldC1;

        ftQTmpOldC1 = pstThreePwr->ftQCStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftQCSum += ftQNewVal_C;    ///< Phase C reactive power sum
        pstThreePwr->ftQCSum -= ftQTmpOldC1;
    }
    /* Storage new value */
    pstThreePwr->ftPAStore[pstCalc->uiCntrBuf] = ftPNewVal_A;
    pstThreePwr->ftQAStore[pstCalc->uiCntrBuf] = ftQNewVal_A;
    pstThreePwr->ftPBStore[pstCalc->uiCntrBuf] = ftPNewVal_B;
    pstThreePwr->ftQBStore[pstCalc->uiCntrBuf] = ftQNewVal_B;
    pstThreePwr->ftPCStore[pstCalc->uiCntrBuf] = ftPNewVal_C;
    pstThreePwr->ftQCStore[pstCalc->uiCntrBuf] = ftQNewVal_C;
}

#elif 2U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-2-phase VF Rms calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Rms2P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Rms2P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1,ftTempOldB1;
    float32 ftTempOldA2,ftTempOldB2;
    float32 ftNewVal_A,ftNewVal_B;

    ftNewVal_A = pstThreePhaseData->ftValLpf10kHz_A;
    ftNewVal_B = pstThreePhaseData->ftValLpf10kHz_B;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeRms->ftARmsSum += (ftNewVal_A * ftNewVal_A);
        pstThreeRms->ftBRmsSum += (ftNewVal_B * ftNewVal_B);
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastLastVal];
        ftTempOldB2 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastLastVal];

        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);
        pstThreeRms->ftARmsSum -= (ftTempOldA2 * ftTempOldA2);

        pstThreeRms->ftBRmsSum += (ftNewVal_B  * ftNewVal_B);
        pstThreeRms->ftBRmsSum -= (ftTempOldB1 * ftTempOldB1);
        pstThreeRms->ftBRmsSum -= (ftTempOldB2 * ftTempOldB2);
    }
    else
    {
        /* Add the latest value and remove the value before one cycle */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeRms->ftBRmsStore[pstCalc->uiPosnLastVal];

        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);

        pstThreeRms->ftBRmsSum += (ftNewVal_B  * ftNewVal_B);
        pstThreeRms->ftBRmsSum -= (ftTempOldB1 * ftTempOldB1);
    }
    /* Storage new value */
    pstThreeRms->ftARmsStore[pstCalc->uiCntrBuf] = ftNewVal_A;
    pstThreeRms->ftBRmsStore[pstCalc->uiCntrBuf] = ftNewVal_B;
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-2-phase VF average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Avg2P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Avg2P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1,ftTempOldB1;
    float32 ftTempOldA2,ftTempOldB2;
    float32 ftNewVal_A,ftNewVal_B;

    ftNewVal_A = pstThreePhaseData->ftVal_A;
    ftNewVal_B = pstThreePhaseData->ftVal_B;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeAvg->ftASum += ftNewVal_A;
        pstThreeAvg->ftBSum += ftNewVal_B;
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastLastVal];
        ftTempOldB2 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;
        pstThreeAvg->ftASum -= ftTempOldA1;
        pstThreeAvg->ftASum -= ftTempOldA2;

        pstThreeAvg->ftBSum += ftNewVal_B;
        pstThreeAvg->ftBSum -= ftTempOldB1;
        pstThreeAvg->ftBSum -= ftTempOldB2;
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];
        ftTempOldB1 = pstThreeAvg->ftBStore[pstCalc->uiPosnLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;
        pstThreeAvg->ftASum -= ftTempOldA1;

        pstThreeAvg->ftBSum += ftNewVal_B;
        pstThreeAvg->ftBSum -= ftTempOldB1;
    }
    /* Storage new value */
    pstThreeAvg->ftAStore[pstCalc->uiCntrBuf] = ftNewVal_A;
    pstThreeAvg->ftBStore[pstCalc->uiCntrBuf] = ftNewVal_B;
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-2-phase VF average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Pwr2P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Pwr2P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftPTmpOldA1 = 0.0f, ftQTmpOldA1 = 0.0f;    ///< Initialize to 0.0f;
    float32 ftPTmpOldA2 = 0.0f, ftQTmpOldA2 = 0.0f;    ///< Initialize to 0.0f;
    float32 ftPNewVal_A = 0.0f, ftQNewVal_A = 0.0f;    ///< Initialize to 0.0f;
    float32 ftPTmpOldB1 = 0.0f, ftQTmpOldB1 = 0.0f;    ///< Initialize to 0.0f;
    float32 ftPTmpOldB2 = 0.0f, ftQTmpOldB2 = 0.0f;    ///< Initialize to 0.0f;
    float32 ftPNewVal_B = 0.0f, ftQNewVal_B = 0.0f;    ///< Initialize to 0.0f;

    ftPNewVal_A = stVgIg.ftVaMpf * stPfcAdc.stIg.ftValLpf10kHz_A;
    ftQNewVal_A = stVgIg.ftVaLpf * stPfcAdc.stIg.ftValLpf10kHz_A;
    ftPNewVal_B = stVgIg.ftVbMpf * stPfcAdc.stIg.ftValLpf10kHz_B;
    ftQNewVal_B = stVgIg.ftVbLpf * stPfcAdc.stIg.ftValLpf10kHz_B;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftQASum += ftQNewVal_A;

        pstThreePwr->ftPBSum += ftPNewVal_B;
        pstThreePwr->ftQBSum += ftQNewVal_B;
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];
        ftPTmpOldA2 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftPASum -= ftPTmpOldA1;
        pstThreePwr->ftPASum -= ftPTmpOldA2;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];
        ftQTmpOldA2 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftQASum += ftQNewVal_A;
        pstThreePwr->ftQASum -= ftQTmpOldA1;
        pstThreePwr->ftQASum -= ftQTmpOldA2;

        ftPTmpOldB1 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastVal];
        ftPTmpOldB2 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftPBSum += ftPNewVal_B;
        pstThreePwr->ftPBSum -= ftPTmpOldB1;
        pstThreePwr->ftPBSum -= ftPTmpOldB2;

        ftQTmpOldB1 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastVal];
        ftQTmpOldB2 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastLastVal];
        pstThreePwr->ftQBSum += ftQNewVal_B;
        pstThreePwr->ftQBSum -= ftQTmpOldB1;
        pstThreePwr->ftQBSum -= ftQTmpOldB2;
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftPASum -= ftPTmpOldA1;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftQASum += ftQNewVal_A;
        pstThreePwr->ftQASum -= ftQTmpOldA1;

        ftPTmpOldB1 = pstThreePwr->ftPBStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftPBSum += ftPNewVal_B;
        pstThreePwr->ftPBSum -= ftPTmpOldB1;

        ftQTmpOldB1 = pstThreePwr->ftQBStore[pstCalc->uiPosnLastVal];
        pstThreePwr->ftQBSum += ftQNewVal_B;
        pstThreePwr->ftQBSum -= ftQTmpOldB1;
    }
    /* Storage new value */
    pstThreePwr->ftPAStore[pstCalc->uiCntrBuf] = ftPNewVal_A;
    pstThreePwr->ftQAStore[pstCalc->uiCntrBuf] = ftQNewVal_A;
    pstThreePwr->ftPBStore[pstCalc->uiCntrBuf] = ftPNewVal_B;
    pstThreePwr->ftQBStore[pstCalc->uiCntrBuf] = ftQNewVal_B;
}

#elif 1U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-Phase A VF Rms calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Rms1P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Rms1P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1 = 0.0f;
    float32 ftTempOldA2 = 0.0f;
    float32 ftNewVal_A  = 0.0f;

    ftNewVal_A = pstThreePhaseData->ftValLpf10kHz_A;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeRms->ftARmsSum += (ftNewVal_A * ftNewVal_A);
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastLastVal];
        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);
        pstThreeRms->ftARmsSum -= (ftTempOldA2 * ftTempOldA2);
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftTempOldA1 = pstThreeRms->ftARmsStore[pstCalc->uiPosnLastVal];
        pstThreeRms->ftARmsSum += (ftNewVal_A  * ftNewVal_A);
        pstThreeRms->ftARmsSum -= (ftTempOldA1 * ftTempOldA1);
    }

    /* Storage new value */
    pstThreeRms->ftARmsStore[pstCalc->uiCntrBuf] = ftNewVal_A;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-1-phase VF average calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Avg1P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Avg1P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1 = 0.0f;
    float32 ftTempOldA2 = 0.0f;
    float32 ftNewVal_A  = 0.0f;

    ftNewVal_A = pstThreePhaseData->ftVal_A;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreeAvg->ftASum += ftNewVal_A;
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];
        ftTempOldA2 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;
        pstThreeAvg->ftASum -= ftTempOldA1;
        pstThreeAvg->ftASum -= ftTempOldA2;
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftTempOldA1 = pstThreeAvg->ftAStore[pstCalc->uiPosnLastVal];

        pstThreeAvg->ftASum += ftNewVal_A;
        pstThreeAvg->ftASum -= ftTempOldA1;
    }

    /* Storage new value */
    pstThreeAvg->ftAStore[pstCalc->uiCntrBuf] = ftNewVal_A;
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-1-phase power calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Pwr1P_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Pwr1P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftPTmpOldA1 = 0.0f, ftQTmpOldA1 = 0.0f;
    float32 ftPTmpOldA2 = 0.0f, ftQTmpOldA2 = 0.0f;
    float32 ftPNewVal_A = 0.0f, ftQNewVal_A = 0.0f;

    ftPNewVal_A = stVgIg.ftVaMpf * stPfcAdc.stIg.ftValLpf10kHz_A;
    ftQNewVal_A = stVgIg.ftVaLpf * stPfcAdc.stIg.ftValLpf10kHz_A;

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftQASum += ftQNewVal_A;
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];
        ftPTmpOldA2 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastLastVal];

        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftPASum -= ftPTmpOldA1;
        pstThreePwr->ftPASum -= ftPTmpOldA2;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];
        ftQTmpOldA2 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastLastVal];

        pstThreePwr->ftQASum += ftQNewVal_A;
        pstThreePwr->ftQASum -= ftQTmpOldA1;
        pstThreePwr->ftQASum -= ftQTmpOldA2;
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        ftPTmpOldA1 = pstThreePwr->ftPAStore[pstCalc->uiPosnLastVal];

        pstThreePwr->ftPASum += ftPNewVal_A;
        pstThreePwr->ftPASum -= ftPTmpOldA1;

        ftQTmpOldA1 = pstThreePwr->ftQAStore[pstCalc->uiPosnLastVal];

        pstThreePwr->ftQASum += ftQNewVal_A;
        pstThreePwr->ftQASum -= ftQTmpOldA1;
    }

    /* Storage new value */
    pstThreePwr->ftPAStore[pstCalc->uiCntrBuf] = ftPNewVal_A;
    pstThreePwr->ftQAStore[pstCalc->uiCntrBuf] = ftQNewVal_A;
}
#endif

#if GRID_PHASE_NUMBER > 1U
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Sample value accumulation calculation ISR task-1-phase VF Rms calculation
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDataCalc_Acm_Rms_Isr, ".TI.ramfunc");
#endif
static void v_PfcDataCalc_Acm_Rms_Isr(float32 ftData, ST_1P_RMS_CALC *pstOneRms, ST_RMS_SAMP_ISR *pstCalc)
{
    float32 ftTempOldA1;
    float32 ftTempOldA2;
    float32 ftNewVal_A;

    ftNewVal_A = ftData;

    ftTempOldA1 = pstOneRms->ftRmsStore[pstCalc->uiPosnLastVal];
    ftTempOldA2 = pstOneRms->ftRmsStore[pstCalc->uiPosnLastLastVal];

    if(pstCalc->uiSts == 2U)         ///> Current points are less than calculation points
    {
        /* The sum does not need to be removed from the previous period */
        pstOneRms->ftRmsSum += (ftNewVal_A  * ftNewVal_A);
    }
    else if(pstCalc->uiSts == 1U)    ///> Current points are greater than calculation points
    {
        /* The sum does not need to be removed first two value from the previous period */
        pstOneRms->ftRmsSum += (ftNewVal_A  * ftNewVal_A);
        pstOneRms->ftRmsSum -= (ftTempOldA1 * ftTempOldA1);
        pstOneRms->ftRmsSum -= (ftTempOldA2 * ftTempOldA2);
    }
    else                            ///> Current points are equal to calculation points
    {
        /* Add the latest value and remove the value before one cycle */
        pstOneRms->ftRmsSum += (ftNewVal_A  * ftNewVal_A);
        pstOneRms->ftRmsSum -= (ftTempOldA1 * ftTempOldA1);

    }
    /* Storage new value */
    pstOneRms->ftRmsStore[pstCalc->uiCntrBuf] = ftData;
}
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: AD bias calculation Init task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBiasCalc_Init(void)
{
    stPfcDataCalcLoc.uiStADBias                   = AD_BIAS_ST_WAIT;
    stPfcDataCalcLoc.uiCntrADBiasLpf              = 0U;                   ///< Initialize to 0U
    stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF      = AD_BIAS_GRID_VOLT;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF      = AD_BIAS_GRID_VOLT;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF      = AD_BIAS_GRID_VOLT;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF   = AD_BIAS_GRID_VOLT;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF   = AD_BIAS_GRID_VOLT;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF      = AD_BIAS_GRID_CURR;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF      = AD_BIAS_GRID_CURR;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF      = AD_BIAS_GRID_CURR;    ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF    = AD_BIAS_DC_VOLT;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF    = AD_BIAS_DC_VOLT;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF    = AD_BIAS_DC_VOLT;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF    = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF    = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF    = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N  = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N  = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N  = AD_BIAS_DC_CURR;      ///< Initialize to 2048
    stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK      = 0U;                   ///< Initialize to 0U
    stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.all = 0U;

    /* Output parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalcDbg.stMeasParm.siVaADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVbADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVcADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVaInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVbInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIaADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIbADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIcADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVaDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVbDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siVcDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF;
    stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N;
    stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N;
    stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N;
    stPfcDataCalcDbg.stMeasParm.uiFlgADBiasOK      = stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK;
    stPfcDataCalcDbg.stCtrlParm.unCmdADBiasRly.all = stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.all;

    stPfcDataCalc.stMeasParm.siVaADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVaADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVbADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVaInvADBiasLPF   = stPfcDataCalcDbg.stMeasParm.siVaInvADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbInvADBiasLPF   = stPfcDataCalcDbg.stMeasParm.siVbInvADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIaADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIbADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVaDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.uiFlgADBiasOK      = stPfcDataCalcDbg.stMeasParm.uiFlgADBiasOK;
    stPfcDataCalc.stCtrlParm.unCmdADBiasRly.all = stPfcDataCalcDbg.stCtrlParm.unCmdADBiasRly.all;
#else
    stPfcDataCalc.stMeasParm.siVaADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVaInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcADBiasLPF      = stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVaDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF    = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF_N  = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.uiFlgADBiasOK      = stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK;
    stPfcDataCalc.stCtrlParm.unCmdADBiasRly.all = stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.all;
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: AD bias calculation 1ms task
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBiasCalc_1ms(void)
{
    switch(stPfcDataCalcLoc.uiStADBias)
    {
        case AD_BIAS_ST_WAIT:
            v_PfcDataCalc_ADBias_StWait();       ///< Wait status
            break;

        case AD_BIAS_ST_BUS_CHK:
            v_PfcDataCalc_ADBias_StBusChk();     ///< Bus check status
            break;

        case AD_BIAS_ST_RLYN_OFF:
            v_PfcDataCalc_ADBias_StOffRlyN();    ///< Relay N Off status
            break;

        case AD_BIAS_ST_RLYN_ON:
            v_PfcDataCalc_ADBias_StOnRlyN();     ///< Relay N On status
            break;

        case AD_BIAS_ST_END:
            v_PfcDataCalc_ADBias_StEnd();        ///< End status
            break;

        default:
            ///< Do nothing
            break;
    }
    if(AD_BIAS_ST_WAIT != stPfcDataCalcLoc.uiStADBias)
    {
        v_PfcDataCalc_ADBias_Outp();
    }

    /* Global parameter */
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.uiFlgADBiasOK = stPfcDataCalcDbg.stMeasParm.uiFlgADBiasOK;
#else
    stPfcDataCalc.stMeasParm.uiFlgADBiasOK = stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK;
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task: Wait-Status
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_StWait(void)
{
    if((AD_BIAS_ADJUST_OVER != stCom.uiCmdPfcADZeroAdj) && (1U == stComIf.uiFlgPowOn) && (STOP_CMD == stComIf.uiCmdRun))
    {
        /* Switch to BUS_CHECK state */
        stPfcDataCalcLoc.uiStADBias = AD_BIAS_ST_BUS_CHK;
    }
    else
    {
        stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK = 0U;       ///< Clear OK flag
#if(3U == GRID_PHASE_NUMBER)
        /* AD switch action */
        if(OFFGRID_MODE == stComIf.uiModPfcRun)
        {
            AC_VOLT_DC_EN;
        }
        else
        {
            AC_CURR_DC_EN;
        }
#endif
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task: Bus voltage check-Status
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_StBusChk(void)
{
    float32 l_ftVoltPreChrgLmt = 0.0f;


#if(1U == GRID_PHASE_NUMBER)
    l_ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * PRE_CHRG_AMP_COEFF;
#elif(2U == GRID_PHASE_NUMBER)
    l_ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComTbl.stPrmPowLim.ftCoeffBusPreChg1P;
#elif(3U == GRID_PHASE_NUMBER)
    l_ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComIf.ftCoeffBusPreChrg;
#endif
    //if((stD2dAdc.ftVoltCellBusSum[0] > l_ftVoltPreChrgLmt) && (stD2dAdc.ftVoltCellBusSum[1] > l_ftVoltPreChrgLmt) && (stD2dAdc.ftVoltCellBusSum[2] > l_ftVoltPreChrgLmt))
    if(stPfcDataCalc.stMeasParm.ftVgMaxRms < FRQCALC_VOLT_LIM)
    {
        stPfcDataCalcLoc.uiCntrADBiasLpf++;
        if(stPfcDataCalcLoc.uiCntrADBiasLpf > 50U)    ///< Bus voltage maintain 50ms
        {
            stPfcDataCalcLoc.uiCntrADBiasLpf = 0U;

            /* Switch to RLYN_OFF state */
            stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyA = 1U;
            stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyB = 1U;
            stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyC = 1U;
            stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyN = 0U;
            AC_CURR_DC_EN;
            stPfcDataCalcLoc.uiStADBias = AD_BIAS_ST_RLYN_OFF;
        }
    }
    else
    {
        stPfcDataCalcLoc.uiCntrADBiasLpf = 0U;
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task: Relay N Off-Status
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_StOffRlyN(void)
{
    stPfcDataCalcLoc.uiCntrADBiasLpf++;
    if(stPfcDataCalcLoc.uiCntrADBiasLpf <= 2000U)    ///< 0~2s
    {
        /* Grid Voltage AD LPF */
        v_PfcDataCalc_ADBias_Volt();
        /* Grid Current AD LPF */
        v_PfcDataCalc_ADBias_Curr();
        /* Grid DC current bias AD LPF */
        v_PfcDataCalc_ADBias_CurrDC();
#if(3U != GRID_PHASE_NUMBER)
        /* Grid DC Voltage AD LPF */
        v_PfcDataCalc_ADBias_VoltDC();
#endif
    }
    else
    {
        stPfcDataCalcLoc.uiCntrADBiasLpf = 0U;
#if(3U != GRID_PHASE_NUMBER)
        /* Switch to END state */
        stPfcDataCalcLoc.uiStADBias      = AD_BIAS_ST_END;
#else
        /* Switch to RLY_N_ON state */
        stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyN = 1U;
        stPfcDataCalcLoc.uiStADBias                          = AD_BIAS_ST_RLYN_ON;
#endif
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task: Relay N On-Status
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_StOnRlyN(void)
{
    stPfcDataCalcLoc.uiCntrADBiasLpf++;
    if(stPfcDataCalcLoc.uiCntrADBiasLpf <= 2000U)    ///< 0~2s
    {
        /* Grid dc current bias adjust */
        v_PfcDataCalc_ADBias_CurrDC();
    }
    else if(stPfcDataCalcLoc.uiCntrADBiasLpf <= 4000U)    ///< 2~4s
    {
        /* Switch to DC Voltage AD sample */
#ifndef SST_1250kW
        AC_VOLT_DC_EN;
#endif
        /* Grid DC Voltage AD LPF */
        v_PfcDataCalc_ADBias_VoltDC();
    }
    else
    {
        stPfcDataCalcLoc.uiCntrADBiasLpf = 0U;
        /* Switch to END state */
        stPfcDataCalcLoc.uiStADBias      = AD_BIAS_ST_END;
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task: End-Status
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_StEnd(void)
{
    stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyA = 0U;    ///< Clear relay command
    stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyB = 0U;
    stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyC = 0U;
    stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.bit.uiRlyN = 0U;
    stPfcDataCalcLoc.stMeasExt.uiFlgADBiasOK = 1U;                ///< Set AD bais calcultation flag
    /* Switch to WAIT state */
    stPfcDataCalcLoc.uiStADBias = AD_BIAS_ST_WAIT;
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task - Voltage AD bias calculation
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_Volt(void)
{
    float32 l_ftInpLpf              = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpVaLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 1U
    static float32 sl_ftOutpVbLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 2U
    static float32 sl_ftOutpVcLpf   = 0.0f;  ///< Initialize to 0.0f
#endif
#endif
#if 2U == GRID_PHASE_NUMBER
    static float32 sl_ftOutpVaInvLpf= 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpVbInvLpf= 0.0f;  ///< Initialize to 0.0f
#endif

    /* Phase A voltage AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgA;
    vFcn_1stOrdLPF(&sl_ftOutpVaLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF = (int16)sl_ftOutpVaLpf;
#if GRID_PHASE_NUMBER > 1U
    /* Phase B voltage AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgB;
    vFcn_1stOrdLPF(&sl_ftOutpVbLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF = (int16)sl_ftOutpVbLpf;
#if GRID_PHASE_NUMBER > 2U
    /* Phase C voltage AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgC;
    vFcn_1stOrdLPF(&sl_ftOutpVcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF = (int16)sl_ftOutpVcLpf;
#endif
#endif

#if 2U == GRID_PHASE_NUMBER
    l_ftInpLpf = (float32)stAdcDrv.uiADVgInvA;
    vFcn_1stOrdLPF(&sl_ftOutpVaInvLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF = (int16)sl_ftOutpVaInvLpf;
    l_ftInpLpf = (float32)stAdcDrv.uiADVgInvB;
    vFcn_1stOrdLPF(&sl_ftOutpVbInvLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF = (int16)sl_ftOutpVbInvLpf;
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task - Current AD bias calculation
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_Curr(void)
{
    float32 l_ftInpLpf              = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpIaLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 1U
    static float32 sl_ftOutpIbLpf   = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpInLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 2U
    static float32 sl_ftOutpIcLpf   = 0.0f;  ///< Initialize to 0.0f
#endif
#endif

    /* Phase A current AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADIgA;
    vFcn_1stOrdLPF(&sl_ftOutpIaLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF = (int16)sl_ftOutpIaLpf;
#if GRID_PHASE_NUMBER > 1U
    /* Phase B current AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADIgB;
    vFcn_1stOrdLPF(&sl_ftOutpIbLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF = (int16)sl_ftOutpIbLpf;
    /* Phase N current AD bias LPF */
#ifndef SST_1250kW
    l_ftInpLpf = (float32)stAdcDrv.uiADIgN;
    vFcn_1stOrdLPF(&sl_ftOutpInLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siInADBiasLPF = (int16)sl_ftOutpInLpf;
#endif
#if GRID_PHASE_NUMBER > 2U
    /* Phase C current AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADIgC;
    vFcn_1stOrdLPF(&sl_ftOutpIcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF = (int16)sl_ftOutpIcLpf;
#endif
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task - Voltage DC component AD bias calculation
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_VoltDC(void)
{
    float32 l_ftInpLpf              = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpVaDcLpf = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 1U
    static float32 sl_ftOutpVbDcLpf = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 2U
    static float32 sl_ftOutpVcDcLpf = 0.0f;  ///< Initialize to 0.0f
#endif
#endif
    /* Phase A voltage DC component AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgDcA;
    vFcn_1stOrdLPF(&sl_ftOutpVaDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF = (int16)sl_ftOutpVaDcLpf;
#if GRID_PHASE_NUMBER > 1U
    /* Phase B voltage DC component AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgDcB;
    vFcn_1stOrdLPF(&sl_ftOutpVbDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF = (int16)sl_ftOutpVbDcLpf;
#if GRID_PHASE_NUMBER > 2U
    /* Phase C voltage DC component AD bias LPF */
    l_ftInpLpf = (float32)stAdcDrv.uiADVgDcC;
    vFcn_1stOrdLPF(&sl_ftOutpVcDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
    stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF = (int16)sl_ftOutpVcDcLpf;
#endif
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task - Current DC component AD bias calculation
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_CurrDC(void)
{
    float32 l_ftInpLpf                = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpIaDcLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 1U
    static float32 sl_ftOutpIbDcLpf   = 0.0f;  ///< Initialize to 0.0f
#if GRID_PHASE_NUMBER > 2U
    static float32 sl_ftOutpIcDcLpf   = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpIaDcLpf_N = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpIbDcLpf_N = 0.0f;  ///< Initialize to 0.0f
    static float32 sl_ftOutpIcDcLpf_N = 0.0f;  ///< Initialize to 0.0f
#endif
#endif

    if(AD_BIAS_ST_RLYN_OFF == stPfcDataCalcLoc.uiStADBias)
    {
        /* Phase A current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcA;
        vFcn_1stOrdLPF(&sl_ftOutpIaDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF = (int16)sl_ftOutpIaDcLpf;
#if GRID_PHASE_NUMBER > 1U
        /* Phase B current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcB;
        vFcn_1stOrdLPF(&sl_ftOutpIbDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF = (int16)sl_ftOutpIbDcLpf;
#if GRID_PHASE_NUMBER > 2U
        /* Phase C current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcC;
        vFcn_1stOrdLPF(&sl_ftOutpIcDcLpf, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF = (int16)sl_ftOutpIcDcLpf;
#endif
#endif
    }
#if 3U == GRID_PHASE_NUMBER
    else
    {
        /* Phase A current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcA;
        vFcn_1stOrdLPF(&sl_ftOutpIaDcLpf_N, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N = (int16)sl_ftOutpIaDcLpf_N;
        /* Phase B current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcB;
        vFcn_1stOrdLPF(&sl_ftOutpIbDcLpf_N, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N = (int16)sl_ftOutpIbDcLpf_N;
        /* Phase C current DC component AD bias LPF */
        l_ftInpLpf = (float32)stAdcDrv.uiADIgDcC;
        vFcn_1stOrdLPF(&sl_ftOutpIcDcLpf_N, l_ftInpLpf, COEFF_LPF_1HZ_1MS);
        stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N = (int16)sl_ftOutpIcDcLpf_N;
    }
#endif
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: AD bias calculation 1ms task - Output process
 * @param [in]
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDataCalc_ADBias_Outp(void)
{
#if 1U == PFC_DATACALC_DBG
    stPfcDataCalc.stMeasParm.siVaADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVaADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVbADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siVcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIaADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIbADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcADBiasLPF      = stPfcDataCalcDbg.stMeasParm.siIcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVaDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVbDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siVcDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siVcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF    = stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF;
    stPfcDataCalc.stMeasParm.siIaDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIaDcADBiasLPF_N;
    stPfcDataCalc.stMeasParm.siIbDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIbDcADBiasLPF_N
    stPfcDataCalc.stMeasParm.siIcDcADBiasLPF_N  = stPfcDataCalcDbg.stMeasParm.siIcDcADBiasLPF_N;
    stPfcDataCalc.stCtrlParm.unCmdADBiasRly.all = stPfcDataCalcDbg.stCtrlParm.unCmdADBiasRly.all;
#else
    /* Phase A voltage AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF > AD_BIAS_GRID_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF < AD_BIAS_GRID_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVaADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVaADBiasLPF;
    }
    /* Phase B voltage AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF > AD_BIAS_GRID_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF < AD_BIAS_GRID_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVbADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVbADBiasLPF;
    }
    /* Phase C voltage AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF > AD_BIAS_GRID_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF < AD_BIAS_GRID_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVcADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVcADBiasLPF;
    }
    /* Phase A invert voltage AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF > AD_BIAS_GRID_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF < AD_BIAS_GRID_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVaInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVaInvADBiasLPF;
    }
    /* Phase B invert voltage AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF > AD_BIAS_GRID_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF < AD_BIAS_GRID_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVbInvADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siVbInvADBiasLPF;
    }
    /* Phase A current AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF > AD_BIAS_GRID_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF < AD_BIAS_GRID_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIaADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siIaADBiasLPF;
    }
    /* Phase B current AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF > AD_BIAS_GRID_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF < AD_BIAS_GRID_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIbADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siIbADBiasLPF;
    }
    /* Phase C current AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF > AD_BIAS_GRID_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF < AD_BIAS_GRID_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIcADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siIcADBiasLPF;
    }
    /* Phase N current AD bias LPF value limit */
#ifndef SST_1250kW
    if((stPfcDataCalcLoc.stMeasExt.siInADBiasLPF > AD_BIAS_GRID_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siInADBiasLPF < AD_BIAS_GRID_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siInADBiasLPF   = stPfcDataCalcLoc.stMeasExt.siInADBiasLPF;
    }
#endif
    /* Phase A voltage DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF > AD_BIAS_DC_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF < AD_BIAS_DC_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVaDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siVaDcADBiasLPF;
    }
    /* Phase B voltage DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF > AD_BIAS_DC_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF < AD_BIAS_DC_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVbDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siVbDcADBiasLPF;
    }
    /* Phase C voltage DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF > AD_BIAS_DC_VOLT_MIN) && (stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF < AD_BIAS_DC_VOLT_MAX))
    {
        stPfcDataCalc.stMeasParm.siVcDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siVcDcADBiasLPF;
    }
    /* Phase A current DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIaDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF;
    }
    /* Phase B current DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIbDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF;
    }
    /* Phase C current DC component AD bias LPF value limit */
    if((stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIcDcADBiasLPF = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF;
    }
    /* Phase A current DC component AD bias LPF value limit(Relay N close) */
    if((stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIaDcADBiasLPF_N = stPfcDataCalcLoc.stMeasExt.siIaDcADBiasLPF_N;
    }
    /* Phase B current DC component AD bias LPF value limit(Relay N close) */
    if((stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIbDcADBiasLPF_N = stPfcDataCalcLoc.stMeasExt.siIbDcADBiasLPF_N;
    }
    /* Phase C current DC component AD bias LPF value limit(Relay N close) */
    if((stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N > AD_BIAS_DC_CURR_MIN) && (stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N < AD_BIAS_DC_CURR_MAX))
    {
        stPfcDataCalc.stMeasParm.siIcDcADBiasLPF_N = stPfcDataCalcLoc.stMeasExt.siIcDcADBiasLPF_N;
    }
    /* AD bias calculation Relay command */
    stPfcDataCalc.stCtrlParm.unCmdADBiasRly.all = stPfcDataCalcLoc.stCtrlExt.unCmdADBiasRly.all;
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
