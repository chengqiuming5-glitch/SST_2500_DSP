//==============================================================================================
//    File description
//==============================================================================================
/**@file         OnOffGridSwt.c
 * @brief
 * The source file of On&Off grid switch module.
 *
 * Module      :                           \n
 * OnOffGridSwt
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_OnOffGridSwt_Init()                   \n
 * v_OnOffGridSwt_1ms()                    \n
 * v_OnOffGridSwt_Isr()
 *
 * Unit Task   :                           \n
 *                                         \n
 *
 * Sub Unit Task   :                       \n
 *
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2025/05/15
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
 * <tr><td>2025/05/15  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "OnOffGridSwt.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_ON_OFF_GRID_SWT stOnOffGridSwt;                 ///< On&Off grid switch global struct

#if (1U == ON_OFF_GRID_SWT_FLG_DBG)
ST_ON_OFF_GRID_SWT stOnOffGridSwtDbg;              ///< On&Off grid switch debug global struct
#endif

static ST_ON_OFF_GRID_SWT_LOC stOnOffGridSwtLoc;   ///< On&Off grid switch local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: On&Off grid switch module initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_OnOffGridSwt_Init(void)
{
    stOnOffGridSwtLoc.uiOrdJdg          = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVaOv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVbOv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVcOv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVabOv       = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVbcOv       = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVcaOv       = 0U;   ///< Initialize to 0U

    stOnOffGridSwtLoc.uiCntrVaHv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVbHv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVcHv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVaLv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVbLv        = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiCntrVcLv        = 0U;   ///< Initialize to 0U

    stOnOffGridSwtLoc.uiVaHv1stJdg      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiVbHv1stJdg      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiVcHv1stJdg      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiVaLv1stJdg      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiVbLv1stJdg      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiVcLv1stJdg      = 0U;   ///< Initialize to 0U

    stOnOffGridSwtLoc.uiFlgVaOvIns      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVbOvIns      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVcOvIns      = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVabOvIns     = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVbcOvIns     = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVcaOvIns     = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVaHv         = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVbHv         = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVcHv         = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVaLv         = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVbLv         = 0U;   ///< Initialize to 0U
    stOnOffGridSwtLoc.uiFlgVcLv         = 0U;   ///< Initialize to 0U

    stOnOffGridSwtLoc.uiHvCntrLmtUp     = HV_CNTR_UP_LIM;
    stOnOffGridSwtLoc.uiHvCntrLmtDn     = HV_CNTR_DN_LIM;
    stOnOffGridSwtLoc.uiLvCntrLmtUp     = LV_CNTR_UP_LIM;
    stOnOffGridSwtLoc.uiLvCntrLmtDn     = LV_CNTR_DN_LIM;

    stOnOffGridSwtLoc.ftVoltHvJdgLim    = VOLT_JDG_HV_LMT;
    stOnOffGridSwtLoc.ftVoltLvJdgLim    = VOLT_JDG_LV_LMT;
    stOnOffGridSwtLoc.ftVoltLineInsPrt  = stPfcDiag.ftAcOVProt * CON_SQRT_3;
    stOnOffGridSwtLoc.stPrmExt.uiFlgSwt = 0U;

#if (1U == ON_OFF_GRID_SWT_FLG_DBG)
    stOnOffGridSwtDbg.uiFlgSwt          = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtDbg.uiFlgSwt;
#else
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: On&Off grid switch module 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_OnOffGridSwt_1ms(void)
{
    /* Switch success or fail, clear switch flag */
    if(((1U == stOnOffGridSwtLoc.stPrmExt.uiFlgSwt) && (OFFGRID_MODE == stComIf.uiModPfcRun)
       && (PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt)) || (STOP_CMD == stComIf.uiCmdRun))
    {
        stOnOffGridSwtLoc.stPrmExt.uiFlgSwt = 0U;   ///< Switch to V2L mode, clear switch flag
    }

    /* Output parameter */
#if (1U == ON_OFF_GRID_SWT_FLG_DBG)
    stOnOffGridSwtDbg.uiFlgSwt          = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtDbg.uiFlgSwt;
#else
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: On&Off grid switch module EEPROM parameter update task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_OnOffGridSwt_PrmUpd_Eep(void)
{
    float32 l_ftSinTmp  = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftAsinTmp = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftLmtTmp  = 0.0f;   ///< Initialize to 0.0f

    /* High voltage judgment counter up limit calculation */
    l_ftSinTmp = VOLT_RAT_JDG_HV_LMT / stComTbl.stPrmGridVoltProt.ftValOver3;
    vFcn_FtUpDwnLim(&l_ftSinTmp, 1.0f, 0.0f);
    ASINF(l_ftAsinTmp, l_ftSinTmp, ASIN_DN_LIM);   ///< Asinf calculation
    l_ftLmtTmp = (PI_CONST - 2.0f * l_ftAsinTmp) * RECPR_PI_CONST * NUM_HALF_GRID_ISR;
    stOnOffGridSwtLoc.uiHvCntrLmtUp = (Uint16)l_ftLmtTmp;
    /* High voltage judgment counter down limit calculation */
    l_ftSinTmp = VOLT_RAT_JDG_HV_LMT / stComTbl.stPrmGridVoltProt.ftValUnder3;
    vFcn_FtUpDwnLim(&l_ftSinTmp, 1.0f, 0.0f);
    ASINF(l_ftAsinTmp, l_ftSinTmp, ASIN_UP_LIM);   ///< Asinf calculation
    l_ftLmtTmp = (PI_CONST - 2.0f * l_ftAsinTmp) * RECPR_PI_CONST * NUM_HALF_GRID_ISR;
    stOnOffGridSwtLoc.uiHvCntrLmtDn = (Uint16)l_ftLmtTmp;
    /* Low voltage judgment counter up limit calculation */
    l_ftSinTmp = VOLT_RAT_JDG_LV_LMT / stComTbl.stPrmGridVoltProt.ftValOver3;
    vFcn_FtUpDwnLim(&l_ftSinTmp, 1.0f, 0.0f);
    ASINF(l_ftAsinTmp, l_ftSinTmp, ASIN_DN_LIM);   ///< Asinf calculation
    l_ftLmtTmp = 2.0f * l_ftAsinTmp * RECPR_PI_CONST * NUM_HALF_GRID_ISR;
    stOnOffGridSwtLoc.uiLvCntrLmtDn = (Uint16)l_ftLmtTmp;
    /* Low voltage judgment counter down limit calculation */
    l_ftSinTmp = VOLT_RAT_JDG_LV_LMT / stComTbl.stPrmGridVoltProt.ftValUnder3;
    vFcn_FtUpDwnLim(&l_ftSinTmp, 1.0f, 0.0f);
    ASINF(l_ftAsinTmp, l_ftSinTmp, ASIN_UP_LIM);   ///< Asinf calculation
    l_ftLmtTmp = 2.0f * l_ftAsinTmp * RECPR_PI_CONST * NUM_HALF_GRID_ISR;
    stOnOffGridSwtLoc.uiLvCntrLmtUp = (Uint16)l_ftLmtTmp;
    /* Line voltage over voltage value calculation */
    stOnOffGridSwtLoc.ftVoltLineInsPrt = stPfcDiag.ftAcOVProt * CON_SQRT_3;
    /* HV&LV judgement limit voltage update */
    stOnOffGridSwtLoc.ftVoltHvJdgLim = VOLT_RAT_JDG_HV_LMT * CON_SQRT_2 * stComTbl.stPrmPfcRtd1.ftVoltGrid;
    stOnOffGridSwtLoc.ftVoltLvJdgLim = VOLT_RAT_JDG_LV_LMT * CON_SQRT_2 * stComTbl.stPrmPfcRtd1.ftVoltGrid;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: On&Off grid switch module ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_OnOffGridSwt_Isr(void)
{
    if(ON_OFF_GRID_IS_RAPID)         ///< Rapid on&off grid switch enable
    {
        v_OnOffGridSwt_Inp_Isr();    ///< On&off grid switch function input parameter
        v_OnOffGridSwt_Jdg_Isr();    ///< On&off grid switch function judgment process
        v_OnOffGridSwt_Outp_Isr();   ///< On&off grid switch function output parameter
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: On&Off grid switch module- input parameter process function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#ifndef SST_1250kW
static void v_OnOffGridSwt_Inp_Isr(void)
{
    /* Voltage absolute value calculation */
#if 1U == GRID_PHASE_NUMBER
    stOnOffGridSwtLoc.ftVaAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);   ///< Phase A voltage
#elif 2U == GRID_PHASE_NUMBER
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)   ///< Phase full run mode
    {
        if(0U == stOnOffGridSwtLoc.uiOrdJdg)
        {
            stOnOffGridSwtLoc.ftVaAbs  = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);       ///< Phase A voltage
            stOnOffGridSwtLoc.ftVabAbs = fabsf(stPfcAdc.stVgLine.ftValLpf10kHz_A);   ///< Line AB voltage
        }
        else
        {
            stOnOffGridSwtLoc.ftVbAbs  = fabsf(stPfcAdc.stVg.ftValLpf10kHz_B);       ///< Phase B voltage
        }
    }
    else
    {
        if(TYPE_GRID_AN == stCom.uiTypeGrid)   ///< AN wiring
        {
            stOnOffGridSwtLoc.ftVaAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);   ///< Phase A voltage
        }
        else
        {
            stOnOffGridSwtLoc.ftVbAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_B);   ///< Phase B voltage
        }
    }
#elif 3U == GRID_PHASE_NUMBER
    if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)   ///< Phase full run mode
    {
        if(0U == stOnOffGridSwtLoc.uiOrdJdg)
        {
            stOnOffGridSwtLoc.ftVaAbs  = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);       ///< Phase A voltage
            stOnOffGridSwtLoc.ftVabAbs = fabsf(stPfcAdc.stVgLine.ftValLpf10kHz_A);   ///< Line AB voltage
        }
        else if(1U == stOnOffGridSwtLoc.uiOrdJdg)
        {
            stOnOffGridSwtLoc.ftVbAbs  = fabsf(stPfcAdc.stVg.ftValLpf10kHz_B);       ///< Phase B voltage
            stOnOffGridSwtLoc.ftVbcAbs = fabsf(stPfcAdc.stVgLine.ftValLpf10kHz_B);   ///< Line BC voltage
        }
        else if(2U == stOnOffGridSwtLoc.uiOrdJdg)
        {
            stOnOffGridSwtLoc.ftVcAbs  = fabsf(stPfcAdc.stVg.ftValLpf10kHz_C);       ///< Phase C voltage
            stOnOffGridSwtLoc.ftVcaAbs = fabsf(stPfcAdc.stVgLine.ftValLpf10kHz_C);   ///< Line CA voltage
        }
        else
        {
            ///< Do nothing
        }
    }
    else
    {
        if(TYPE_GRID_AN == stCom.uiTypeGrid)   ///< AN wiring
        {
            stOnOffGridSwtLoc.ftVaAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);
        }
        else if(TYPE_GRID_BN == stCom.uiTypeGrid)   ///< BN wiring
        {
            stOnOffGridSwtLoc.ftVbAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_B);
        }
        else
        {
            stOnOffGridSwtLoc.ftVcAbs = fabsf(stPfcAdc.stVg.ftValLpf10kHz_C);
        }
    }
#endif
}
#endif
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: On&Off grid switch module- voltage judgment process function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_OnOffGridSwt_Jdg_Isr(void)
{
    if((0U == stOnOffGridSwtLoc.stPrmExt.uiFlgSwt) && (BIDIR_ONGRID_MODE == stComIf.uiModPfcRun))
    {
#if 1U == GRID_PHASE_NUMBER
        /* Phase A voltage over voltage detect */
        stOnOffGridSwtLoc.uiFlgVaOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVaAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVaOv);
        /* Phase A voltage over Hv detect */
        stOnOffGridSwtLoc.uiFlgVaHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaHv, &stOnOffGridSwtLoc.uiVaHv1stJdg);
        /* Phase A voltage below Lv detect */
        stOnOffGridSwtLoc.uiFlgVaLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaLv, &stOnOffGridSwtLoc.uiVaLv1stJdg);
#elif 2U == GRID_PHASE_NUMBER
        if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)         ///< Phase full run mode
        {
            if(0U == stOnOffGridSwtLoc.uiOrdJdg)
            {
                /* Phase A voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVaOvIns  = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVaAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVaOv);
                /* Line AB voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVabOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVabAbs, stOnOffGridSwtLoc.ftVoltLineInsPrt, &stOnOffGridSwtLoc.uiCntrVabOv);
                /* Phase A voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVaHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaHv, &stOnOffGridSwtLoc.uiVaHv1stJdg);
                /* Phase A voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVaLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaLv, &stOnOffGridSwtLoc.uiVaLv1stJdg);
                stOnOffGridSwtLoc.uiOrdJdg   = 1U;
            }
            else
            {
                /* Phase B voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVbOvIns  = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVbAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVbOv);
                /* Phase B voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVbHv   = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbHv, &stOnOffGridSwtLoc.uiVbHv1stJdg);
                /* Phase B voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVbLv   = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbLv, &stOnOffGridSwtLoc.uiVbLv1stJdg);
                stOnOffGridSwtLoc.uiOrdJdg    = 0U;
            }
        }
        else
        {
            if(TYPE_GRID_AN == stCom.uiTypeGrid)
            {
                /* Phase A voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVaOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVaAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVaOv);
                /* Phase A voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVaHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaHv, &stOnOffGridSwtLoc.uiVaHv1stJdg);
                /* Phase A voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVaLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaLv, &stOnOffGridSwtLoc.uiVaLv1stJdg);
            }
            else
            {
                /* Phase B voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVbOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVbAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVbOv);
                /* Phase B voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVbHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbHv, &stOnOffGridSwtLoc.uiVbHv1stJdg);
                /* Phase B voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVbLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbLv, &stOnOffGridSwtLoc.uiVbLv1stJdg);
            }
        }
#elif 3U == GRID_PHASE_NUMBER
        if(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)         ///< Phase full run mode
        {
            if(0U == stOnOffGridSwtLoc.uiOrdJdg)
            {
                /* Phase A voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVaOvIns  = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVaAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVaOv);
                /* Line AB voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVabOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVabAbs, stOnOffGridSwtLoc.ftVoltLineInsPrt, &stOnOffGridSwtLoc.uiCntrVabOv);
                /* Phase A voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVaHv   = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaHv, &stOnOffGridSwtLoc.uiVaHv1stJdg);
                /* Phase A voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVaLv   = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaLv, &stOnOffGridSwtLoc.uiVaLv1stJdg);
                stOnOffGridSwtLoc.uiOrdJdg    = 1U;
            }
            else if(1U == stOnOffGridSwtLoc.uiOrdJdg)
            {
                /* Phase B voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVbOvIns  = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVbAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVbOv);
                /* Line BC voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVbcOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVbcAbs, stOnOffGridSwtLoc.ftVoltLineInsPrt, &stOnOffGridSwtLoc.uiCntrVbcOv);
                /* Phase B voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVbHv   = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbHv, &stOnOffGridSwtLoc.uiVbHv1stJdg);
                /* Phase B voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVbLv   = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbLv, &stOnOffGridSwtLoc.uiVbLv1stJdg);
                stOnOffGridSwtLoc.uiOrdJdg    = 2U;
            }
            else if(2U == stOnOffGridSwtLoc.uiOrdJdg)
            {
                /* Phase C voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVcOvIns  = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVcAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVcOv);
                /* Line CA voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVcaOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVcaAbs, stOnOffGridSwtLoc.ftVoltLineInsPrt, &stOnOffGridSwtLoc.uiCntrVcaOv);
                /* Phase C voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVcHv   = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVcAbs, &stOnOffGridSwtLoc.uiCntrVcHv, &stOnOffGridSwtLoc.uiVcHv1stJdg);
                /* Phase C voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVcLv   = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVcAbs, &stOnOffGridSwtLoc.uiCntrVcLv, &stOnOffGridSwtLoc.uiVcLv1stJdg);
                stOnOffGridSwtLoc.uiOrdJdg    = 0U;
            }
            else
            {
                ///< Do nothing
            }
        }
        else
        {
            if(TYPE_GRID_AN == stCom.uiTypeGrid)
            {
                /* Phase A voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVaOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVaAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVaOv);
                /* Phase A voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVaHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaHv, &stOnOffGridSwtLoc.uiVaHv1stJdg);
                /* Phase A voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVaLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVaAbs, &stOnOffGridSwtLoc.uiCntrVaLv, &stOnOffGridSwtLoc.uiVaLv1stJdg);
            }
            else if(TYPE_GRID_BN == stCom.uiTypeGrid)
            {
                /* Phase B voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVbOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVbAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVbOv);
                /* Phase B voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVbHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbHv, &stOnOffGridSwtLoc.uiVbHv1stJdg);
                /* Phase B voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVbLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVbAbs, &stOnOffGridSwtLoc.uiCntrVbLv, &stOnOffGridSwtLoc.uiVbLv1stJdg);
            }
            else
            {
                /* Phase C voltage over voltage detect */
                stOnOffGridSwtLoc.uiFlgVcOvIns = ui_OnOffGridSwt_VgInsDet_Isr(stOnOffGridSwtLoc.ftVcAbs, stPfcDiag.ftAcOVProt, &stOnOffGridSwtLoc.uiCntrVcOv);
                /* Phase C voltage over Hv detect */
                stOnOffGridSwtLoc.uiFlgVcHv  = ui_OnOffGridSwt_HvCntr_Isr(stOnOffGridSwtLoc.ftVcAbs, &stOnOffGridSwtLoc.uiCntrVcHv, &stOnOffGridSwtLoc.uiVcHv1stJdg);
                /* Phase C voltage below Lv detect */
                stOnOffGridSwtLoc.uiFlgVcLv  = ui_OnOffGridSwt_LvCntr_Isr(stOnOffGridSwtLoc.ftVcAbs, &stOnOffGridSwtLoc.uiCntrVcLv, &stOnOffGridSwtLoc.uiVcLv1stJdg);
            }
        }
#endif
    }
    else
    {
        /* Parameter clear */
        stOnOffGridSwtLoc.uiCntrVaOv   = 0U;
        stOnOffGridSwtLoc.uiCntrVbOv   = 0U;
        stOnOffGridSwtLoc.uiCntrVcOv   = 0U;
        stOnOffGridSwtLoc.uiCntrVabOv  = 0U;
        stOnOffGridSwtLoc.uiCntrVbcOv  = 0U;
        stOnOffGridSwtLoc.uiCntrVcaOv  = 0U;

        stOnOffGridSwtLoc.uiCntrVaHv   = 0U;
        stOnOffGridSwtLoc.uiCntrVbHv   = 0U;
        stOnOffGridSwtLoc.uiCntrVcHv   = 0U;
        stOnOffGridSwtLoc.uiCntrVaLv   = 0U;
        stOnOffGridSwtLoc.uiCntrVbLv   = 0U;
        stOnOffGridSwtLoc.uiCntrVcLv   = 0U;

        stOnOffGridSwtLoc.uiVaHv1stJdg = 0U;
        stOnOffGridSwtLoc.uiVbHv1stJdg = 0U;
        stOnOffGridSwtLoc.uiVcHv1stJdg = 0U;
        stOnOffGridSwtLoc.uiVaLv1stJdg = 0U;
        stOnOffGridSwtLoc.uiVbLv1stJdg = 0U;
        stOnOffGridSwtLoc.uiVcLv1stJdg = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: On&Off grid switch module- output parameter process function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_OnOffGridSwt_Outp_Isr(void)
{
    if((PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt) \
       && ((1U == stOnOffGridSwtLoc.uiFlgVaOvIns) || (1U == stOnOffGridSwtLoc.uiFlgVbOvIns) || (1U == stOnOffGridSwtLoc.uiFlgVcOvIns) \
           || (1U == stOnOffGridSwtLoc.uiFlgVabOvIns) || (1U == stOnOffGridSwtLoc.uiFlgVbcOvIns) || (1U == stOnOffGridSwtLoc.uiFlgVcaOvIns) \
           || (1U == stOnOffGridSwtLoc.uiFlgVaHv) || (1U == stOnOffGridSwtLoc.uiFlgVbHv) || (1U == stOnOffGridSwtLoc.uiFlgVcHv) \
           || (1U == stOnOffGridSwtLoc.uiFlgVaLv) || (1U == stOnOffGridSwtLoc.uiFlgVbLv) || (1U == stOnOffGridSwtLoc.uiFlgVcLv)))
    {
        stOnOffGridSwtLoc.stPrmExt.uiFlgSwt = 1U;
        /* Parameter clear */
        stOnOffGridSwtLoc.uiCntrVaOv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVbOv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVcOv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVabOv   = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVbcOv   = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVcaOv   = 0U;   ///< Clear to 0U

        stOnOffGridSwtLoc.uiCntrVaHv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVbHv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVcHv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVaLv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVbLv    = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiCntrVcLv    = 0U;   ///< Clear to 0U

        stOnOffGridSwtLoc.uiVaHv1stJdg  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiVbHv1stJdg  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiVcHv1stJdg  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiVaLv1stJdg  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiVbLv1stJdg  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiVcLv1stJdg  = 0U;   ///< Clear to 0U

        stOnOffGridSwtLoc.uiFlgVaOvIns  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVbOvIns  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVcOvIns  = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVabOvIns = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVaHv     = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVbHv     = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVcHv     = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVaLv     = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVbLv     = 0U;   ///< Clear to 0U
        stOnOffGridSwtLoc.uiFlgVcLv     = 0U;   ///< Clear to 0U
    }

    /* Output parameter */
#if (1U == ON_OFF_GRID_SWT_FLG_DBG)
    stOnOffGridSwtDbg.uiFlgSwt          = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtDbg.uiFlgSwt;
#else
    stOnOffGridSwt.uiFlgSwt             = stOnOffGridSwtLoc.stPrmExt.uiFlgSwt;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid transient over voltage judgment ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_OnOffGridSwt_VgInsDet_Isr(float32 ftVolt, float32 ftPrtVal, Uint16 *puiCntr)
{
    static Uint16 sl_uiRetTmp = 0U;    ///< Initialize to 0U

    if(ftVolt > ftPrtVal)
    {
        if(++(*puiCntr) >= TI_VOLT_INS_PRT)
        {
            sl_uiRetTmp = 1U;   ///< Voltage ins-protect set
        }
    }
    else
    {
        *puiCntr    = 0U;
        sl_uiRetTmp = 0U;
    }

    return sl_uiRetTmp;   ///< Return result
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid high voltage counter judgment ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_OnOffGridSwt_HvCntr_Isr(float32 ftVolt, Uint16 *puiCntr, Uint16 *pui1stJdg)
{
    static Uint16 sl_uiRetTmp = 0U;    ///< Initialize to 0U

    if(ftVolt > stOnOffGridSwtLoc.ftVoltHvJdgLim)   ///< AC voltage over Hv counter
    {
        (*puiCntr)++;
        *pui1stJdg = 0U;
        if(*puiCntr > stOnOffGridSwtLoc.uiHvCntrLmtUp)   ///< AC voltage over Hv last too long
        {
            sl_uiRetTmp = 1U;
        }
    }
    else if((0U == *pui1stJdg) && (ftVolt < stOnOffGridSwtLoc.ftVoltLvJdgLim))
    {
        if(*puiCntr < stOnOffGridSwtLoc.uiHvCntrLmtDn)   ///< AC voltage over Hv last too short
        {
            sl_uiRetTmp = 1U;
        }
        else
        {
            sl_uiRetTmp = 0U;
        }

        *pui1stJdg = 1U;
        *puiCntr   = 0U;
    }
    else
    {
        ///< Do nothing
    }

    return sl_uiRetTmp;   ///< Return result
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: Grid low voltage counter judgment ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static Uint16 ui_OnOffGridSwt_LvCntr_Isr(float32 ftVolt, Uint16 *puiCntr, Uint16 *pui1stJdg)
{
    static Uint16 sl_uiRetTmp = 0U;    ///< Initialize to 0U

    if(ftVolt < stOnOffGridSwtLoc.ftVoltLvJdgLim)   ///< AC voltage below Lv counter
    {
        (*puiCntr)++;
        *pui1stJdg = 0U;
        if(*puiCntr > stOnOffGridSwtLoc.uiLvCntrLmtUp)   ///< AC voltage below Lv last too long
        {
            sl_uiRetTmp = 1U;
        }
    }
    else if((0U == *pui1stJdg) && (ftVolt > stOnOffGridSwtLoc.ftVoltHvJdgLim))
    {
        if(*puiCntr < stOnOffGridSwtLoc.uiLvCntrLmtDn)   ///< AC voltage below Lv last too short
        {
            sl_uiRetTmp = 1U;
        }
        else
        {
            sl_uiRetTmp = 0U;
        }

        *pui1stJdg = 1U;
        *puiCntr   = 0U;
    }
    else
    {
        ///< Do nothing
    }

    return sl_uiRetTmp;   ///< Return result
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

