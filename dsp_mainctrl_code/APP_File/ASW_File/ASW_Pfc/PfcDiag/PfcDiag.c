//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDiag.c
 * @brief
 * The source file of PFC fault diagnosis module.
 *
 * Module      :                           \n
 * PfcDiag
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_PfcDiag_Init()                        \n
 * v_PfcDiag_1ms()                         \n
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
 * 2024/03/20
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
 * <tr><td>2024/03/20  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcDiag.h"
#include "PrmDispExt.h"
#include "F2837xD_Examples.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_DIAG stPfcDiag;    ///< PFC fault diagnosis global struct

#if (1U == PFC_DIAG_DBG)
ST_PFC_DIAG stPfcDiagDbg;    ///< PFC fault diagnosis debug global struct
#endif

static ST_PFC_DIAG_LOC stPfcDiagLoc;    ///< PFC fault diagnosis local struct

static const Uint16 uiMaxLvlAry[256] =
{
    0U, 0U, 1U, 1U, 2U, 2U, 2U, 2U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U,
    4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,
    5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
    5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
    6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
    6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
    6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
    6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U
};

static ST_FLT_MOD_SEL stFltChkMod[2][10]=
{
    ///< 0-digital fault
    {
        {ui_InvldChkMod},        ///< 0-ANALOG_UP
        {ui_InvldChkMod},        ///< 1-ANALOG_DN
        {ui_InvldChkMod},        ///< 2-ANALOG_ABS_UP
        {ui_InvldChkMod},        ///< 3-ANALOG_ABS_DN
        {ui_InvldChkMod},        ///< 4-CMD_EQUAL_STS  ui_CmdEquStMod
        {ui_InvldChkMod},        ///< 5-CMD_DIFF_STS   ui_CmdUnEquStMod
        {ui_InvldChkMod},        ///< 6-CMD_EQUAL_ONE  ui_CmdEquOneMod
        {ui_InvldChkMod},        ///< 7-CMD_DIFF_ONE   ui_CmdEquZeroMod
        {ui_StEquOneMod},        ///< 8-STS_EQUAL_ONE
        {ui_InvldChkMod},        ///< 9-STS_DIFF_ONE   ui_StEquZeroMod
    },
    ///< 1-analog fault
    {
        {ui_HighrThanLmtMod},    ///< 0-ANALOG_UP
        {ui_LowrThanLmtMod},     ///< 1-ANALOG_DN
        {ui_InvldChkMod},        ///< 2-ANALOG_ABS_UP  ui_AbsHighrThanLmtMod
        {ui_InvldChkMod},        ///< 3-ANALOG_ABS_DN  ui_AbsLowrThanLmtMod
        {ui_InvldChkMod},        ///< 4-CMD_EQUAL_STS
        {ui_InvldChkMod},        ///< 5-CMD_DIFF_STS
        {ui_InvldChkMod},        ///< 6-CMD_EQUAL_ONE
        {ui_InvldChkMod},        ///< 7-CMD_DIFF_ONE
        {ui_InvldChkMod},        ///< 8-STS_EQUAL_ONE
        {ui_InvldChkMod},        ///< 9-STS_DIFF_ONE
    },
};

static ST_FLT_TI_CALC stFltStTiChk[2]=
{
    {v_DigFltTiCntr},      ///< 0-digital fault
    {v_AnFltTiCntr},       ///< 1-analog  fault
};

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis module initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDiag_Init(void)
{
    Uint16 i = 0U;

    /* Fault list-1 counter reset */
    stPfcDiagLoc.stSingleFlt.puiCntr = wBaseFaultOccurTime;
    for(i = 0U; i < FAULTNUM; i++)
    {
        *(stPfcDiagLoc.stSingleFlt.puiCntr + i) = 0U;
    }
    /* Fault list-2 counter reset */
    stPfcDiagLoc.stSingleFlt.puiCntr = wSafetyFaultOccurTime;
    for(i = 0; i < SAFETY_FAULT_NUM; i++)
    {
        *(stPfcDiagLoc.stSingleFlt.puiCntr + i) = 0U;
    }

    stPfcDiagLoc.stSingleFlt.siActualVal        = 0;         ///< Initialize to 0
    stPfcDiagLoc.stSingleFlt.uiTiClr            = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiFlgDisDet        = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.siHysLmtVal        = 0;         ///< Initialize to 0
    stPfcDiagLoc.stSingleFlt.uiDisDetByPfcSt    = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiTiCfm            = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.unFaultMode.all    = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.unProperty.all     = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiExtFltTypeBit    = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiFltLvlBit        = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiADFltType        = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiFltDetType       = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiDigFltCmdBit     = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiDigFltStsBit     = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiPfcStsWord       = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiFltLvlCmbnTemp   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stSingleFlt.uiFltLvlCmbn       = 0U;        ///< Initialize to 0U

    stPfcDiagLoc.uiCntrChkStOT                  = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrGridOV                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrGridOC                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrCBCSet                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrCBCClr                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiFlgCBCSet                    = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiFlgV2LCBCRec                 = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrV2LCBCSum                = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiTiV2LCBCDet                  = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrAprtOL                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrActvOL                   = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrWiringDet                = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.uiCntrCurrSum                  = 0U;
    stPfcDiagLoc.ftVgMax                        = 0.0f;      ///< Initialize to 0.0f
    stPfcDiagLoc.ftIgMax                        = 0.0f;      ///< Initialize to 0.0f

    stPfcDiagLoc.stPrmExt.unFlt.all             = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stPrmExt.uiMaxFltLevel         = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stPrmExt.uiCmdRstHW            = 0U;        ///< Initialize to 0U
    stPfcDiagLoc.stPrmExt.ftAcOVProt            = RATED_AC_VOLT_RMS * PFC_OV_AMP_PROT_COEFF;
    stPfcDiagLoc.stPrmExt.ftAcOCProt            = PFC_OC_AMP_PROT;
    stPfcDiagLoc.stPrmExt.uiTiAcOVProt          = PFC_OV_AMP_PROT_TI;
    stPfcDiagLoc.stPrmExt.uiTiAcOCProt          = PFC_OC_AMP_PROT_TI;
    stPfcDiagLoc.stPrmExt.uiTiCbcProt           = PFC_CBC_TI;
    stPfcDiagLoc.stPrmExt.uiBusUVProt10Times    = (Uint16)(PFC_BUS_UV_PROT * COEFF_VOLT_ARM);
    stPfcDiagLoc.stPrmExt.uiBusOVProt10Times    = (Uint16)(PFC_BUS_OV_PROT * COEFF_VOLT_ARM);
    stPfcDiagLoc.stPrmExt.uiHalfBusOVProt10Times= (Uint16)(PFC_HALF_BUS_OV_PROT * COEFF_VOLT_ARM);
    stPfcDiagLoc.stPrmExt.uiMidBusOVProt10Times = (Uint16)(PFC_MID_BUS_OV_PROT * COEFF_VOLT_ARM);
    stPfcDiagLoc.stPrmExt.uiAcRmsOCProt100Times = (Uint16)(RATED_AC_CURR_RMS * PFC_OC_RMS_PROT_COEFF * RAT_AC_CURR_LIM * COEFF_CURR_ARM);
    stPfcDiagLoc.stPrmExt.uiVoltAcImBal10Times  = (Uint16)(PFC_OV_RMS_IMBAL_PROT * COEFF_VOLT_ARM);
    stPfcDiagLoc.stPrmExt.uiCurrAcImBal100Times = (Uint16)(PFC_OC_RMS_IMBAL_PROT * COEFF_CURR_ARM);
    stPfcDiagLoc.stPrmExt.uiVgDcProt1000Times   = (Uint16)(PFC_VOLT_DC_PROT * COEFF_DC_ARM);
    stPfcDiagLoc.stPrmExt.uiIgDcProt1000Times   = (Uint16)(PFC_CURR_DC_PROT * COEFF_DC_ARM);
    stPfcDiagLoc.stPrmExt.ftRatPwrOvLoadLim     = PFC_PWR_PROT_COEFF;

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiagDbg.uiMaxFltLevel          = stPfcDiagLoc.stPrmExt.uiMaxFltLevel;
    stPfcDiagDbg.uiCmdRstHW             = stPfcDiagLoc.stPrmExt.uiCmdRstHW;
    stPfcDiagDbg.unFlt.all              = stPfcDiagLoc.stPrmExt.unFlt.all;
    stPfcDiagDbg.ftAcOVProt             = stPfcDiagLoc.stPrmExt.ftAcOVProt;
    stPfcDiagDbg.ftAcOCProt             = stPfcDiagLoc.stPrmExt.ftAcOCProt;
    stPfcDiagDbg.uiTiAcOVProt           = stPfcDiagLoc.stPrmExt.uiTiAcOVProt;
    stPfcDiagDbg.uiTiAcOCProt           = stPfcDiagLoc.stPrmExt.uiTiAcOCProt;
    stPfcDiagDbg.uiBusUVProt10Times     = stPfcDiagLoc.stPrmExt.uiBusUVProt10Times;
    stPfcDiagDbg.uiBusOVProt10Times     = stPfcDiagLoc.stPrmExt.uiBusOVProt10Times;
    stPfcDiagDbg.uiHalfBusOVProt10Times = stPfcDiagLoc.stPrmExt.uiHalfBusOVProt10Times;
    stPfcDiagDbg.uiMidBusOVProt10Times  = stPfcDiagLoc.stPrmExt.uiMidBusOVProt10Times;
    stPfcDiagDbg.uiAcRmsOCProt100Times  = stPfcDiagLoc.stPrmExt.uiAcRmsOCProt100Times;
    stPfcDiagDbg.uiVoltAcImBal10Times   = stPfcDiagLoc.stPrmExt.uiVoltAcImBal10Times;
    stPfcDiagDbg.uiCurrAcImBal100Times  = stPfcDiagLoc.stPrmExt.uiCurrAcImBal100Times;
    stPfcDiagDbg.uiVgDcProt1000Times    = stPfcDiagLoc.stPrmExt.uiVgDcProt1000Times;
    stPfcDiagDbg.uiIgDcProt1000Times    = stPfcDiagLoc.stPrmExt.uiIgDcProt1000Times;
    stPfcDiagDbg.ftRatPwrOvLoadLim      = stPfcDiagLoc.stPrmExt.ftRatPwrOvLoadLim;
    stPfcDiagDbg.uiTiCbcProt            = stPfcDiagLoc.stPrmExt.uiTiCbcProt;

    stPfcDiag.uiMaxFltLevel             = stPfcDiagDbg.uiMaxFltLevel;
    stPfcDiag.uiCmdRstHW                = stPfcDiagDbg.uiCmdRstHW;
    stPfcDiag.unFlt.all                 = stPfcDiagDbg.unFlt.all;
    stPfcDiag.ftAcOVProt                = stPfcDiagDbg.ftAcOVProt;
    stPfcDiag.ftAcOCProt                = stPfcDiagDbg.ftAcOCProt;
    stPfcDiag.uiTiAcOVProt              = stPfcDiagDbg.uiTiAcOVProt;
    stPfcDiag.uiTiAcOCProt              = stPfcDiagDbg.uiTiAcOCProt;
    stPfcDiag.uiBusUVProt10Times        = stPfcDiagDbg.uiBusUVProt10Times;
    stPfcDiag.uiBusOVProt10Times        = stPfcDiagDbg.uiBusOVProt10Times;
    stPfcDiag.uiHalfBusOVProt10Times    = stPfcDiagDbg.uiHalfBusOVProt10Times;
    stPfcDiag.uiMidBusOVProt10Times     = stPfcDiagDbg.uiMidBusOVProt10Times;
    stPfcDiag.uiAcRmsOCProt100Times     = stPfcDiagDbg.uiAcRmsOCProt100Times;
    stPfcDiag.uiVoltAcImBal10Times      = stPfcDiagDbg.uiVoltAcImBal10Times;
    stPfcDiag.uiCurrAcImBal100Times     = stPfcDiagDbg.uiCurrAcImBal100Times;
    stPfcDiag.uiVgDcProt1000Times       = stPfcDiagDbg.uiVgDcProt1000Times;
    stPfcDiag.uiIgDcProt1000Times       = stPfcDiagDbg.uiIgDcProt1000Times;
    stPfcDiag.ftRatPwrOvLoadLim         = stPfcDiagDbg.ftRatPwrOvLoadLim;
    stPfcDiag.uiTiCbcProt               = stPfcDiagDbg.uiTiCbcProt;
#else
    stPfcDiag.uiMaxFltLevel             = stPfcDiagLoc.stPrmExt.uiMaxFltLevel;
    stPfcDiag.uiCmdRstHW                = stPfcDiagLoc.stPrmExt.uiCmdRstHW;
    stPfcDiag.unFlt.all                 = stPfcDiagLoc.stPrmExt.unFlt.all;
    stPfcDiag.ftAcOVProt                = stPfcDiagLoc.stPrmExt.ftAcOVProt;
    stPfcDiag.ftAcOCProt                = stPfcDiagLoc.stPrmExt.ftAcOCProt;
    stPfcDiag.uiTiAcOVProt              = stPfcDiagLoc.stPrmExt.uiTiAcOVProt;
    stPfcDiag.uiTiAcOCProt              = stPfcDiagLoc.stPrmExt.uiTiAcOCProt;
    stPfcDiag.uiBusUVProt10Times        = stPfcDiagLoc.stPrmExt.uiBusUVProt10Times;
    stPfcDiag.uiBusOVProt10Times        = stPfcDiagLoc.stPrmExt.uiBusOVProt10Times;
    stPfcDiag.uiHalfBusOVProt10Times    = stPfcDiagLoc.stPrmExt.uiHalfBusOVProt10Times;
    stPfcDiag.uiMidBusOVProt10Times     = stPfcDiagLoc.stPrmExt.uiMidBusOVProt10Times;
    stPfcDiag.uiAcRmsOCProt100Times     = stPfcDiagLoc.stPrmExt.uiAcRmsOCProt100Times;
    stPfcDiag.uiVoltAcImBal10Times      = stPfcDiagLoc.stPrmExt.uiVoltAcImBal10Times;
    stPfcDiag.uiCurrAcImBal100Times     = stPfcDiagLoc.stPrmExt.uiCurrAcImBal100Times;
    stPfcDiag.uiVgDcProt1000Times       = stPfcDiagLoc.stPrmExt.uiVgDcProt1000Times;
    stPfcDiag.uiIgDcProt1000Times       = stPfcDiagLoc.stPrmExt.uiIgDcProt1000Times;
    stPfcDiag.ftRatPwrOvLoadLim         = stPfcDiagLoc.stPrmExt.ftRatPwrOvLoadLim;
    stPfcDiag.uiTiCbcProt               = stPfcDiagLoc.stPrmExt.uiTiCbcProt;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcDiag_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis module in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_Isr, ".TI.ramfunc");
#endif
void v_PfcDiag_Isr(void)
{
    if(0U == stCom.unCmdFct.bit.uiEnFctPwm)
    {
        v_PfcDiag_GridOV_Isr();        ///< Grid over-voltage fault
        v_PfcDiag_GridOC_Isr();        ///< Grid over-current fault
   //     v_PfcDiag_CBCOT_Isr();         ///< Grid current CBC over-time fault
    }

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all = stPfcDiagDbg.unFlt.all;
#else
    stPfcDiag.unFlt.all = stPfcDiagLoc.stPrmExt.unFlt.all;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDynIsr) 
    {
        printf("****SWIT DynamicTest: function v_PfcDiag_Isr() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis module 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDiag_1ms(void)
{
    /* Fault diagnosis mode check */
    v_PfcDiag_FltMod_1ms();
    /* Fault detect */
    v_PfcDiag_FltDet_1ms();

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PfcDiag_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis module 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDiag_10ms(void)
{
    float32 l_ftVoltAcAmpLim = 0.0f;

    /* PFC fault reset */
    if(FCN_ENABLE == stComIf.uiFlgFltRst)
    {
        stPfcDiagLoc.stPrmExt.unFlt.all = 0U;             ///< Reset PFC fault
        stPfcDiagLoc.stPrmExt.uiCmdRstHW = FCN_ENABLE;    ///< Reset PFC Hardware fault
    }
    else
    {
        stPfcDiagLoc.stPrmExt.uiCmdRstHW = FCN_DISABLE;
    }

    /* PFC Bus UV */
#if(3U == GRID_PHASE_NUMBER)
    if(OFFGRID_MODE == stComIf.uiModPfcRun)
    {
        l_ftVoltAcAmpLim = stPowLim.ftVoltAcAmpLim * RECPR_CON_SQRT_2 * stComIf.ftCoeffBusPreChrg * COEFF_VOLT_ARM;
        stPfcDiagLoc.stPrmExt.uiBusUVProt10Times = (Uint16)l_ftVoltAcAmpLim;
    }
    else
    {
        l_ftVoltAcAmpLim = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComIf.ftCoeffBusPreChrg * COEFF_VOLT_ARM;
        stPfcDiagLoc.stPrmExt.uiBusUVProt10Times = (Uint16)l_ftVoltAcAmpLim;
    }
    DOWN_LIMIT(stPfcDiagLoc.stPrmExt.uiBusUVProt10Times , 2000U);
#else
    if(OFFGRID_MODE == stComIf.uiModPfcRun)
    {
        l_ftVoltAcAmpLim = stPowLim.ftVoltAcAmpLim * (float32)GRID_PHASE_NUMBER * COEFF_VOLT_ARM;
    }
    else
    {
        l_ftVoltAcAmpLim = stPfcDataCalc.stMeasParm.ftVgMaxRms * (float32)GRID_PHASE_NUMBER * CON_SQRT_2 * COEFF_VOLT_ARM;
    }

    if(FCN_ENABLE == stComIf.uiFlgPfcTzToDC)
    {
        l_ftVoltAcAmpLim *= 0.9f;    ///< In standby 0A mode, bus voltage is uncontrolled rectification voltage
    }
    stPfcDiagLoc.stPrmExt.uiBusUVProt10Times = (Uint16)l_ftVoltAcAmpLim;
#endif

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all          = stPfcDiagDbg.unFlt.all;
    stPfcDiag.uiCmdRstHW         = stPfcDiagDbg.uiCmdRstHW;
    stPfcDiag.uiBusUVProt10Times = stPfcDiagDbg.uiBusUVProt10Times;
#else
    stPfcDiag.unFlt.all          = stPfcDiagLoc.stPrmExt.unFlt.all;
    stPfcDiag.uiCmdRstHW         = stPfcDiagLoc.stPrmExt.uiCmdRstHW;
    if(0U == stCom.unCmdFct.bit.uiEnaBusUV)
    {
        stPfcDiag.uiBusUVProt10Times = stPfcDiagLoc.stPrmExt.uiBusUVProt10Times;
    }
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn10ms)
    {
        printf("****SWIT DynamicTest: function v_PfcDiag_10ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis module 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcDiag_100ms(void)
{
    float32 l_ftRatVoltTmp = 0.0f;   ///< AC instant over voltage ratio

    if(0U == stCom.unCmdFct.bit.uiEnFctPwm)
    {
	    /* PFC state machine check over-time fault */
	    v_PfcDiag_StMac_Chk_100ms();

	    /* PFC wiring fault */
	    v_PfcDiag_WiringFlt_100ms(); ///< sst no use

	    /* PFC over load fault */
	    v_PfcDiag_OL_Flt_100ms();
    }
    /* AS-NZS 4777.2 over voltage test */
    if((stCom.uiStdGridSet >= AS4777_A) && (stCom.uiStdGridSet <= AS4777_NZ))
    {
        l_ftRatVoltTmp = stComTbl.stPrmGridVoltProt.ftValOver3 + 0.02f;
    }
    else
    {
        l_ftRatVoltTmp = stComTbl.stPrmGridVoltProt.ftValOver3 + 0.05f;
    }
    stPfcDiagLoc.stPrmExt.ftAcOVProt = l_ftRatVoltTmp * CON_SQRT_2 * stComTbl.stPrmPfcRtd1.ftVoltGrid;

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all  = stPfcDiagDbg.unFlt.all;
    stPfcDiag.ftAcOVProt = stPfcDiagDbg.ftAcOVProt;
#else
    stPfcDiag.unFlt.all  = stPfcDiagLoc.stPrmExt.unFlt.all;
    stPfcDiag.ftAcOVProt = stPfcDiagLoc.stPrmExt.ftAcOVProt;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_PfcDiag_100ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC grid over-voltage fault diagnosis module in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_GridOV_Isr, ".TI.ramfunc");
#endif
static void v_PfcDiag_GridOV_Isr(void)
{
    if(ON_OFF_GRID_IS_NORMAL)
    {
    #if 1U == GRID_PHASE_NUMBER
        ///< Maximum voltage calculation
        stPfcDiagLoc.ftVgMax = fabsf(stPfcAdc.stVg.ftValLpf10kHz_A);
    #elif 2U == GRID_PHASE_NUMBER
        ///< Maximum voltage calculation
        stPfcDiagLoc.ftVgMax = ftFcn_MaxOfTwo(fabsf(stPfcAdc.stVg.ftValLpf10kHz_A), fabsf(stPfcAdc.stVg.ftValLpf10kHz_B));
    #elif 3U == GRID_PHASE_NUMBER
        ///< Maximum voltage calculation
        stPfcDiagLoc.ftVgMax = ftFcn_MaxOfThree(fabsf(stPfcAdc.stVg.ftValLpf10kHz_A), fabsf(stPfcAdc.stVg.ftValLpf10kHz_B), fabsf(stPfcAdc.stVg.ftValLpf10kHz_C));
    #endif

        if(stPfcDiagLoc.ftVgMax > stPfcDiag.ftAcOVProt)
        {
            stPfcDiagLoc.uiCntrGridOV++;
            if(stPfcDiagLoc.uiCntrGridOV >= stPfcDiag.uiTiAcOVProt)
            {
                stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridOV = 1U;    ///< Set grid OV fault
            }
        }
        else if(stPfcDiagLoc.uiCntrGridOV > 0U)
        {
            stPfcDiagLoc.uiCntrGridOV--;
        }
        else
        {
            ///< Do nothing
        }
    }
    else
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridOV = 0U;   ///< Fault clear
        stPfcDiagLoc.uiCntrGridOV                = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC grid over-current fault diagnosis module in ISR
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_GridOC_Isr, ".TI.ramfunc");
#endif
static void v_PfcDiag_GridOC_Isr(void)
{
    float32 l_ftCurrSumAbs = 0.0f;
#if 1U == GRID_PHASE_NUMBER
    ///< Maximum current calculation
    stPfcDiagLoc.ftIgMax = fabsf(stPfcAdc.stIg.ftValLpf10kHz_A);
#elif 2U == GRID_PHASE_NUMBER
    ///< Maximum current calculation
    stPfcDiagLoc.ftIgMax = ftFcn_MaxOfThree(fabsf(stPfcAdc.stIg.ftValLpf10kHz_A), fabsf(stPfcAdc.stIg.ftValLpf10kHz_B), fabsf(stPfcAdc.stIg.ftValLpf10kHz_N));
#else
    ///< Maximum current calculation
#ifndef SST_1250kW
    stPfcDiagLoc.ftIgMax = ftFcn_MaxOfFour(fabsf(stPfcAdc.stIg.ftValLpf10kHz_A), fabsf(stPfcAdc.stIg.ftValLpf10kHz_B), fabsf(stPfcAdc.stIg.ftValLpf10kHz_C), \
                                    fabsf(stPfcAdc.stIg.ftValLpf10kHz_N));
#else
    stPfcDiagLoc.ftIgMax = ftFcn_MaxOfThree(fabsf(stPfcAdc.stIg.ftValLpf10kHz_A), fabsf(stPfcAdc.stIg.ftValLpf10kHz_B), fabsf(stPfcAdc.stIg.ftValLpf10kHz_C));
#endif
#endif
//    if(1U == stComTbl.stPrmToFpga.uiHandControl)
//    {
//        stPfcDiag.ftAcOCProt = 200;
//    }
    /* PFC Hardware OC detect */
    if((PFC_OCP_A_HW_FLT_IS_ON)||(PFC_OCP_B_HW_FLT_IS_ON)||(PFC_OCP_C_HW_FLT_IS_ON))
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwPosOC = 1U;    ///< Grid hardware positive OC
    }
#if 0
    if(PFC_OCP_A_HW_FLT_IS_ON)
    {
        stPrmDisp.siPrm1 = 1;
    }
    if(PFC_OCP_B_HW_FLT_IS_ON)
    {
        stPrmDisp.siPrm2 = 1;
    }
    if(PFC_OCP_C_HW_FLT_IS_ON)
    {
        stPrmDisp.siPrm3 = 1;
    }
#endif
    l_ftCurrSumAbs = stPfcAdc.stIg.ftValLpf10kHz_A + stPfcAdc.stIg.ftValLpf10kHz_B + stPfcAdc.stIg.ftValLpf10kHz_C;
    if((l_ftCurrSumAbs > stComTbl.stPrmToFpga.ftSUMOCPValue)||(l_ftCurrSumAbs < -stComTbl.stPrmToFpga.ftSUMOCPValue))
    {
        stPfcDiagLoc.uiCntrCurrSum++;
        if(stPfcDiagLoc.uiCntrCurrSum >= 3U)
        {
            stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwNegOC = 1U;    ///< Current unblanced or current Sample fault
        }
    }
    else if(stPfcDiagLoc.uiCntrCurrSum > 0U)
    {
        stPfcDiagLoc.uiCntrCurrSum --;
    }
    else
    {
        ///< Do nothing
    }


    if(stPfcDiagLoc.ftIgMax > stPfcDiag.ftAcOCProt)
    {
        stPfcDiagLoc.uiCntrGridOC++;
        if(stPfcDiagLoc.uiCntrGridOC >= stPfcDiag.uiTiAcOCProt)
        {
            stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridOC = 1U;    ///< Set grid OC fault 
//            GpioDataRegs.GPASET.bit.GPIO5 = 1U;
        }
    }
    else if(stPfcDiagLoc.uiCntrGridOC > 0U)
    {
        stPfcDiagLoc.uiCntrGridOC--;
    }
    else
    {
        ///< Do nothing
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
* @brief      PFC Diag CBC Over time function
* @details    The control frequency is 48K
* @param[in]  void
* @param[out] void
* @return
*/
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_CBCOT_Isr, ".TI.ramfunc");
#endif
static void v_PfcDiag_CBCOT_Isr(void)
{
#if 0U == FLG_SWUT_EN
    #if(1U == GRID_PHASE_NUMBER)
    Uint16 l_uiFlgTz = 0U;               ///< TZ flag
    #elif(2U == GRID_PHASE_NUMBER)
    static Uint16 sl_uiCntrIntl = 0U;    ///< Initialize to 0U;
    Uint16 l_uiFlgTz = 0U;               ///< TZ flag
    #else
    static Uint16 sl_uiCntrIntl = 0U;
    Uint16 l_uiFlgTz1 = 0U;              ///< TZ1 flag
    Uint16 l_uiFlgTz2 = 0U;              ///< TZ2 flag
    Uint16 l_uiFlgTz3 = 0U;              ///< TZ3 flag
    Uint16 l_uiFlgTz4 = 0U;              ///< TZ4 flag
    Uint16 l_uiFlgTz5 = 0U;              ///< TZ5 flag
    #endif

    #if(1U == GRID_PHASE_NUMBER)
    if(0U == stPfcDiagLoc.stPrmExt.unFlt.bit.uiCBCOT)
    {
        l_uiFlgTz = PFC_FAST_PWM.TZFLG.bit.DCAEVT2;
        if((1U == PFC_FAST_PWM.TZFLG.bit.DCBEVT2) || (1U == l_uiFlgTz))    ///< The right operand of the || operator must not contain side effects
        {
            /* Clear DCEVT TZ flag */
            EALLOW;
            PFC_FAST_PWM.TZCLR.bit.DCAEVT2 = 1U;
            PFC_FAST_PWM.TZCLR.bit.DCBEVT2 = 1U;
            EDIS;

            /* Set CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 1U;
            /* Record V2L CBC flag */
            stPfcDiagLoc.uiFlgV2LCBCRec = 1U;
        }
        else
        {
            /* Clear CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 0U;
        }

        /* CBC over time fault judge */
        v_PfcDiag_CBCOT_Jdg_Isr();
    }
    #elif(2U == GRID_PHASE_NUMBER)
    if((++sl_uiCntrIntl >= PFC_CBC_PERD) && (0U == stPfcDiagLoc.stPrmExt.unFlt.bit.uiCBCOT))
    {
        sl_uiCntrIntl = 0U;

        l_uiFlgTz = PWM_L1A1_REG.TZFLG.bit.DCBEVT2;
        if((1U == PWM_L1A1_REG.TZFLG.bit.DCAEVT2) || (1U == l_uiFlgTz))    ///< The right operand of the || operator must not contain side effects

        {
            /* Clear DCEVT TZ flag */
            EALLOW;
            PWM_L1A1_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L1A1_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L1A2_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L1A2_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L1B1_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L1B1_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L1B2_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L1B2_REG.TZCLR.bit.DCBEVT2 = 1U;

            PWM_L2A1_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L2A1_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L2A2_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L2A2_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L2B1_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L2B1_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_L2B2_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_L2B2_REG.TZCLR.bit.DCBEVT2 = 1U;
            EDIS;

            /* Set CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 1U;
            /* Record V2L CBC flag */
            stPfcDiagLoc.uiFlgV2LCBCRec = 1U;
        }
        else
        {
            /* Clear CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 0U;
        }

        /* CBC over time fault judge */
        v_PfcDiag_CBCOT_Jdg_Isr();
    }
    #else
    if((++sl_uiCntrIntl >= PFC_CBC_PERD) && (0U == stPfcDiagLoc.stPrmExt.unFlt.bit.uiCBCOT))
    {
        sl_uiCntrIntl = 0U;

        /* Three phase bridge CBC */
        l_uiFlgTz1 = PWM_A_REG.TZFLG.bit.DCBEVT2;
        l_uiFlgTz2 = PWM_B_REG.TZFLG.bit.DCAEVT2;
        l_uiFlgTz3 = PWM_B_REG.TZFLG.bit.DCBEVT2;
        l_uiFlgTz4 = PWM_C_REG.TZFLG.bit.DCAEVT2;
        l_uiFlgTz5 = PWM_C_REG.TZFLG.bit.DCBEVT2;

        if((1U == PWM_A_REG.TZFLG.bit.DCAEVT2) || (1U == l_uiFlgTz1) || (1U == l_uiFlgTz2) \
           ||(1U == l_uiFlgTz3) || (1U == l_uiFlgTz4) || (1U == l_uiFlgTz5))    ///< The right operand of the || operator must not contain side effects
        {
            /* Clear DCEVT TZ flag */
            EALLOW;
            PWM_A_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_A_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_B_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_B_REG.TZCLR.bit.DCBEVT2 = 1U;
            PWM_C_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_C_REG.TZCLR.bit.DCBEVT2 = 1U;
            EDIS;

            /* Set CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 1U;
            /* Record V2L CBC flag */
            stPfcDiagLoc.uiFlgV2LCBCRec = 1U;
        }
        else
        {
            /* Clear CBC flag */
            stPfcDiagLoc.uiFlgCBCSet = 0U;
        }
        stPfcDiagLoc.uiFlgCBCSet = 0U;
        /* CBC over time fault judge */
        v_PfcDiag_CBCOT_Jdg_Isr();

        /* N bridge CBC*/
        l_uiFlgTz1 = PWM_N_REG.TZFLG.bit.DCBEVT2;
        if((1U == PWM_N_REG.TZFLG.bit.DCAEVT2) || (1U == l_uiFlgTz1))    ///< The right operand of the || operator must not contain side effects
        {
            EALLOW;
            PWM_N_REG.TZCLR.bit.DCAEVT2 = 1U;
            PWM_N_REG.TZCLR.bit.DCBEVT2 = 1U;
            EDIS;
        }
    }
    #endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
* @brief      PFC Diag CBC Over time fault judge function
* @details    
* @param[in]  void
* @param[out] void
* @return
*/
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_CBCOT_Isr, ".TI.ramfunc");
#endif
static void v_PfcDiag_CBCOT_Jdg_Isr(void)
{
    if(OFFGRID_MODE != stComIf.uiModPfcRun)     ///< Not OffGrid Mode
    {
        if(1U == stPfcDiagLoc.uiFlgCBCSet)
        {
            stPfcDiagLoc.uiCntrCBCSet++;    ///< Set CBC counter
            if(stPfcDiagLoc.uiCntrCBCSet > stPfcDiag.uiTiCbcProt)
            {
                stPfcDiagLoc.stPrmExt.unFlt.bit.uiCBCOT = 1U;
                stPfcDiagLoc.uiCntrCBCSet = 0U;
            }

            stPfcDiagLoc.uiCntrCBCClr = 0U;
        }
        else if(stPfcDiagLoc.uiCntrCBCSet > 0U)
        {
            stPfcDiagLoc.uiCntrCBCClr++;
            if(stPfcDiagLoc.uiCntrCBCClr > stPfcDiag.uiTiCbcProt)
            {
                stPfcDiagLoc.uiCntrCBCSet--;
            }
        }
        else
        {
            ///< Do nothing
        }
    }
    else    ///< OffGrid Mode
    {
        if(++stPfcDiagLoc.uiTiV2LCBCDet > NUM_CBC_PERD)             ///< Detect 20ms
        {
            stPfcDiagLoc.uiTiV2LCBCDet = 0U;
            if(1U == stPfcDiagLoc.uiFlgV2LCBCRec)
            {
                stPfcDiagLoc.uiFlgV2LCBCRec = 0U;                    ///< Clear Record CBC flag
                if(++stPfcDiagLoc.uiCntrV2LCBCSum >= NUM_CBC_TRIG)   ///< Lasts 10s
                {
                    stPfcDiagLoc.stPrmExt.unFlt.bit.uiCBCOT = 1U;    ///< Set CBC fault
                    stPfcDiagLoc.uiCntrV2LCBCSum  = 0U;
                }
            }
            else if(stPfcDiagLoc.uiCntrV2LCBCSum > 0U)
            {
                stPfcDiagLoc.uiCntrV2LCBCSum--;
            }
            else
            {
                ///< Do nothing
            }
        }
    }
}
/*********************************************End**********************************************/

#if 0U == FLG_SWUT_EN
#if(3U != GRID_PHASE_NUMBER)
/********************************************Begin*********************************************/
/**
* @brief        Module function: PFC fault diagnosis eCAP ISR; 7.4kW-PFC negative hardware OC
* @param[in]
* @param[out]
* @return
*/
interrupt void v_PfcDiag_eCap_ISR(void)
{
    v_EPwmDrv_Pfc_TurnOff();    ///< PFC EPwm drive turn off

#if(1U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwNegOC = 1U;    ///< Grid hardware negative OC
#elif(2U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiNegBusHwOV = 1U;     ///< Negative half bus hardware OV
#endif

    PieCtrlRegs.PIEACK.all = (Uint16)PIEACK_GROUP4_DSP;    ///< Acknowledge this INT to receive more INT from group 4

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all = stPfcDiagDbg.unFlt.all;
#else
    stPfcDiag.unFlt.all = stPfcDiagLoc.stPrmExt.unFlt.all;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
* @brief        Module function: PFC fault diagnosis XINT1 ISR; 7.4kW-PFC positive hardware OC
* @param[in]
* @param[out]
* @return
*/
interrupt void v_PfcDiag_XInt1_ISR(void)
{
    v_EPwmDrv_Pfc_TurnOff();    ///< PFC EPwm drive turn off

#if(1U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwPosOC = 1U;        ///< Grid hardware positive OC
#elif(2U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiTzHwSum = 1U;            ///< PFC hardware summary
    if(1U == PFC_GRID_HW_OC)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwPosOC = 1U;    ///< Grid hardware positive OC
    }

    if(1U == PFC_BUS_HW_OV_POS)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiPosBusHwOV = 1U;     ///< Grid hardware negative OC
    }

    if(1U == PFC_BUS_HW_OV_NEG)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiNegBusHwOV = 1U;     ///< Bus hardware OV
    }
#endif

    PieCtrlRegs.PIEACK.all = (Uint16)PIEACK_GROUP1_DSP;        ///< Acknowledge this INT to receive more INT from group 1

#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all = stPfcDiagDbg.unFlt.all;
#else
    stPfcDiag.unFlt.all = stPfcDiagLoc.stPrmExt.unFlt.all;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
* @brief        Module function: PFC fault diagnosis XINT3 ISR; 7.4kW-Bus hardware OV
* @param[in]
* @param[out]
* @return
*/
interrupt void v_PfcDiag_XInt3_ISR(void)
{
    v_EPwmDrv_Pfc_TurnOff();    ///< PFC EPwm drive turn off

#if(1U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiBusHwOV = 1U;         ///< Bus hardware OV
#elif(2U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiPosBusHwOV = 1U;      ///< Positive half bus hardware OV
#endif

    PieCtrlRegs.PIEACK.all = (Uint16)PIEACK_GROUP12_DSP;    ///< Acknowledge this INT to receive more INT from group 12

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all = stPfcDiagDbg.unFlt.all;
#else
    stPfcDiag.unFlt.all = stPfcDiagLoc.stPrmExt.unFlt.all;
#endif
}
/*********************************************End**********************************************/
#endif

#if(2U != GRID_PHASE_NUMBER)
/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC fault diagnosis EPWM TZ ISR(PFC hardware fault summary)
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
interrupt void v_PfcDiag_ePwm_TZ_ISR(void)
{
    v_EPwmDrv_Pfc_TurnOff();    ///< PFC EPwm drive turn off

#if(1U == GRID_PHASE_NUMBER)
    stPfcDiagLoc.stPrmExt.unFlt.bit.uiTzHwSum = 1U;            ///< Hardware fault summary

    if(1U == PFC_GRID_HW_OC_POS)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwPosOC = 1U;    ///< Grid hardware positive OC
    }

    if(1U == PFC_GRID_HW_OC_NEG)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwNegOC = 1U;    ///< Grid hardware negative OC
    }

    if(1U == PFC_BUS_HW_OV)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiBusHwOV = 1U;        ///< Bus hardware OV
    }
#elif(3U == GRID_PHASE_NUMBER)
#ifndef SST_1250kW
    if(1U == EPwm5Regs.TZOSTFLG.bit.OST1)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiGridHwPosOC = 1U;    ///< Grid hardware positive OC
    }

    if(1U == EPwm5Regs.TZOSTFLG.bit.OST2)
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiBusHwOV = 1U;        ///< Bus hardware OV
    }
#endif
#endif
    PieCtrlRegs.PIEACK.all = (Uint16)PIEACK_GROUP2_DSP;        ///< Acknowledge this INT to receive more INT from group 2

    /* Output parameter */
#if (1U == PFC_DIAG_DBG)
    stPfcDiag.unFlt.all = stPfcDiagDbg.unFlt.all;
#else
    stPfcDiag.unFlt.all = stPfcDiagLoc.stPrmExt.unFlt.all;
#endif
}
/*********************************************End**********************************************/
#endif
#endif
/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC fault diagnosis module 1ms task- Fault diagnosis mode check
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_FltMod_1ms(void)
{
    ST_FLT_SYS_STS_WORD stFaultSysStsWord;

    stFaultSysStsWord.all = 0U;

    switch(stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        case PFC_ST_MAC_FLT:
        case PFC_ST_MAC_STB:
            stFaultSysStsWord.bit.uiPfcStOff = 1U;    ///< Off state
            break;
        case PFC_ST_MAC_CHK:
            stFaultSysStsWord.bit.uiPfcStChk = 1U;    ///< Check state
            break;
        case PFC_ST_MAC_PWMEN:
            stFaultSysStsWord.bit.uiPfcStRdy = 1U;    ///< Ready state
            break;
        case PFC_ST_MAC_NORMRUN:
            stFaultSysStsWord.bit.uiPfcStRun = 1U;    ///< Run state
            break;

        default:
            ///< Do nothing
            break;
    }

    stPfcDiagLoc.stSingleFlt.uiPfcStsWord = stFaultSysStsWord.all;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC fault diagnosis module 1ms task- Fault Detect
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcDiag_FltDet_1ms, ".TI.ramfunc");
#endif
static void v_PfcDiag_FltDet_1ms(void)
{
    Uint16 i = 0U;
    static Uint16 j = 0U;

     j = ~j;

     if(0U == j)
     {
         /* Detect the first half fault list */
         stPfcDiagLoc.stSingleFlt.uiFltLvlCmbnTemp = 0U;    ///< Clear fault level
         for(i = 0U; i < FAULTNUM; i++)
         {
             v_SingleFaultDet(i, BaseFaultDataTable, wBaseFaultOccurTime);
         }
     }
     else
     {
         /* Detect the latter half fault list */
         for(i = 0U; i < SAFETY_FAULT_NUM; i++)
         {
             v_SingleFaultDet(i, CQC_Table, wSafetyFaultOccurTime);
         }

         /* Find the maximum fault level */
         stPfcDiagLoc.stSingleFlt.uiFltLvlCmbn = stPfcDiagLoc.stSingleFlt.uiFltLvlCmbnTemp;
         vFcn_UiUpDwnLim(&stPfcDiagLoc.stSingleFlt.uiFltLvlCmbn, 255U, 0U);
         stPfcDiagLoc.stPrmExt.uiMaxFltLevel = uiMaxLvlAry[stPfcDiagLoc.stSingleFlt.uiFltLvlCmbn];
     }

     /* Global parameter */
 #if (1U == PFC_DIAG_DBG)
     stPfcDiag.uiMaxFltLevel = stPfcDiagDbg.uiMaxFltLevel;
 #else
     stPfcDiag.uiMaxFltLevel = stPfcDiagLoc.stPrmExt.uiMaxFltLevel;
 #endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC fault detect unit- Single fault detect
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_SingleFaultDet, ".TI.ramfunc");
#endif
static void v_SingleFaultDet(Uint16 uiFltIndex,const FaultDataType *pstFltDataTab,Uint16 *uiFaultConter)
{
    Uint16 uiFaultFlagTemp    = 0U;
    Uint16 uiFaultStsFlagTemp = 0U;

    stPfcDiagLoc.stSingleFlt.unProperty.all  = (pstFltDataTab[uiFltIndex].FaultType);         ///< Fault property
    stPfcDiagLoc.stSingleFlt.unFaultMode.all = (pstFltDataTab[uiFltIndex].DetectType);        ///< Fault mode
    stPfcDiagLoc.stSingleFlt.uiDisDetByPfcSt = (pstFltDataTab[uiFltIndex].Mode_Dis[stComIf.uiModPfcRun-1U]);    ///< Disable fault detect flag
    stPfcDiagLoc.stSingleFlt.uiMaskWord      = *(pstFltDataTab[uiFltIndex].FaultMaskWordAddr);    ///< Fault mask word

    stPfcDiagLoc.stSingleFlt.puiFaultWord    = (pstFltDataTab[uiFltIndex].FaultWordAddr);         ///< Fault word pointer
    stPfcDiagLoc.stSingleFlt.puiFaultStWord  = (pstFltDataTab[uiFltIndex].FaultStsWordAddr);      ///< Fault status word pointer
    stPfcDiagLoc.stSingleFlt.puiCntr         = uiFaultConter + uiFltIndex;                        ///< Fault counter pointer

#if 0U == FLG_SWUT_EN
    if(GET_FLT_BIT() < 16U)    ///< Static scan: Check the right operand
    {
        stPfcDiagLoc.stSingleFlt.uiFltWordBit    = (1U<<GET_FLT_BIT());
    }
    if(GET_EXT_FLT_TYPE() < 16U)    ///< Static scan: Check the right operand
    {
        stPfcDiagLoc.stSingleFlt.uiExtFltTypeBit = (1U<<GET_EXT_FLT_TYPE());
    }
    if(GET_FLT_LVL() < 16U)    ///< Static scan: Check the right operand
    {
        stPfcDiagLoc.stSingleFlt.uiFltLvlBit     = (1U<<GET_FLT_LVL());
    }
#else
    stPfcDiagLoc.stSingleFlt.uiFltWordBit    = (1U<<GET_FLT_BIT());
    stPfcDiagLoc.stSingleFlt.uiExtFltTypeBit = (1U<<GET_EXT_FLT_TYPE());
    stPfcDiagLoc.stSingleFlt.uiFltLvlBit     = (1U<<GET_FLT_LVL());
#endif

    stPfcDiagLoc.stSingleFlt.uiFlgDisDet = (Uint16)((INNER_DIS_CHK() > 0U) || (EXT_MASK_DIS_CHK() > 0U));

    if(stPfcDiagLoc.stSingleFlt.uiFlgDisDet > 0U)
    {
        CLR_FLT_STS_WORD();
        FLT_CNTR() = 0U;
        uiFaultFlagTemp    = GET_FLT_WORD();
        uiFaultStsFlagTemp = GET_FLT_STS_WORD();
    }
    else
    {

        stPfcDiagLoc.stSingleFlt.siActualVal  = *(pstFltDataTab[uiFltIndex].Actual_valueAddr);    ///< Actual value of detected object
        stPfcDiagLoc.stSingleFlt.siLmtVal     = *(pstFltDataTab[uiFltIndex].ThresholdsAddr);      ///< Limit value of detected object
        stPfcDiagLoc.stSingleFlt.uiTiClr      = pstFltDataTab[uiFltIndex].DisappearTime;          ///< Fault clear time
        stPfcDiagLoc.stSingleFlt.uiTiCfm      = pstFltDataTab[uiFltIndex].ConfirmTime;            ///< Fault confirm time
        stPfcDiagLoc.stSingleFlt.uiHysVal     = pstFltDataTab[uiFltIndex].LimtHysteresis;         ///< Hysteresis value

        stPfcDiagLoc.stSingleFlt.uiADFltType  = GET_AD_FLT_TYPE();
        stPfcDiagLoc.stSingleFlt.uiFltDetType = GET_DET_MOD();
#if 0U == FLG_SWUT_EN
        if(GET_DIG_FLT_CMD_BIT() < 16U)    ///< Static scan: Check the right operand
        {
            stPfcDiagLoc.stSingleFlt.uiDigFltCmdBit = (1U<<GET_DIG_FLT_CMD_BIT());
        }
        if(GET_DIG_FLT_STS_BIT() < 16U)    ///< Static scan: Check the right operand
        {
            stPfcDiagLoc.stSingleFlt.uiDigFltStsBit = (1U<<GET_DIG_FLT_STS_BIT());
        }
#else
        stPfcDiagLoc.stSingleFlt.uiDigFltCmdBit = (1U<<GET_DIG_FLT_CMD_BIT());
        stPfcDiagLoc.stSingleFlt.uiDigFltStsBit = (1U<<GET_DIG_FLT_STS_BIT());
#endif
        vFcn_UiUpDwnLim(&stPfcDiagLoc.stSingleFlt.uiADFltType, 1U, 0U);
        vFcn_UiUpDwnLim(&stPfcDiagLoc.stSingleFlt.uiFltDetType, 9U, 0U);

        stPfcDiagLoc.stSingleFlt.uiFlgFltOccur = stFltChkMod[stPfcDiagLoc.stSingleFlt.uiADFltType][stPfcDiagLoc.stSingleFlt.uiFltDetType].pui_fun();
        stFltStTiChk[stPfcDiagLoc.stSingleFlt.uiADFltType].pv_fun();
        uiFaultFlagTemp    = GET_FLT_WORD();
        uiFaultStsFlagTemp = GET_FLT_STS_WORD();
    }

    if(GET_LATCH_FLG() == 0U)  ///< No latch fault
    {
        if(uiFaultFlagTemp > 0U)  ///< Fault flag = 1
        {
             if(uiFaultStsFlagTemp == 0U)  ///< Fault status = 0, means fault disappear
             {
                 CLR_FLT_WORD();
             }
             else
             {
                 SET_FLT_LVL();
             }
        }
        else
        {
            if(uiFaultStsFlagTemp > 0U)  ///< Fault status = 1
            {
                SET_FLT_WORD();
            }
        }
    }
    else  ///< Latch fault
    {
        if(uiFaultFlagTemp > 0U)  ///< Fault flag = 1
        {
            if((FCN_ENABLE == stComIf.uiFlgFltRst) && (uiFaultStsFlagTemp == 0U))  ///< ||(IN_RESET_CMD==1)
            {
                CLR_FLT_WORD();
            }
            else
            {
                SET_FLT_LVL();
            }
        }
        else
        {
            if((uiFaultStsFlagTemp > 0U))  ///< Fault status = 1
            {
                SET_FLT_WORD();
            }
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault confirm and disappear time check
* @param[in]
* @param[out]
* @return
*/
static void v_DigFltTiCntr(void)
{
    if(GET_FLT_STS_WORD() > 0U)
    {
        if(stPfcDiagLoc.stSingleFlt.uiFlgFltOccur == 0U)
        {
            FLT_CNTR()++;
        }
        else
        {
            if(FLT_CNTR() > 0U)
            {
                FLT_CNTR()--;
            }
        }

        if(FLT_CNTR() > (FLT_CLR_TI()))    ///< Duration time
        {
            FLT_CLR_SET();    ///< Clear fault flag and counter
        }
        else
        {
            SET_FLT_LVL();
//            SET_EXT_FLT_FLAG();
        }
    }
    else
    {
        if(stPfcDiagLoc.stSingleFlt.uiFlgFltOccur == 1U)
        {
            FLT_CNTR()++;
        }
        else
        {

            if(FLT_CNTR() > 0U)
            {
                FLT_CNTR()--;
            }
        }
        if(FLT_CNTR() > (FLT_CFM_TI()))    ///< Duration time
        {
            SET_FLT_STS_WORD();
            SET_FLT_LVL();
            FLT_CNTR() = 0U;        ///< Clear fault counter
//            SET_EXT_FLT_FLAG();
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Analog fault confirm and disappear time check
* @param[in]
* @param[out]
* @return
*/
static void v_AnFltTiCntr(void)
{
    if(GET_FLT_STS_WORD() > 0U)
    {
        if(stPfcDiagLoc.stSingleFlt.uiFlgFltOccur == 0U)
        {
            if(FLT_CNTR() < (FLT_CLR_TI() + 2U))
            {
                FLT_CNTR()++;
            }
         }
         else
         {
            if(FLT_CNTR() > 0U)
            {
                FLT_CNTR()--;
            }
         }

         if(FLT_CNTR() > FLT_CLR_TI())    ///< Duration time
         {
            FLT_CLR_SET();    ///< Clear fault flag and counter
         }
         else
         {
            SET_FLT_LVL();
//          SET_EXT_FLT_FLAG();
         }
    }
    else
    {
        if(stPfcDiagLoc.stSingleFlt.uiFlgFltOccur == 1U)
        {
            if(FLT_CNTR() < (FLT_CFM_TI() + 2U))
            {
                FLT_CNTR()++;
            }
        }
        else
        {

            if(FLT_CNTR() > 0U)
            {
                FLT_CNTR()--;
            }
        }
        if(FLT_CNTR() > FLT_CFM_TI())    ///< Duration time
        {
            SET_FLT_STS_WORD();
            SET_FLT_LVL();
            FLT_CNTR() = 0U;        ///< Clear fault counter
//          SET_EXT_FLT_FLAG();
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Invalid fault check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_InvldChkMod(void)
{
    return 0U;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Analog fault analog value higher than limit value check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_HighrThanLmtMod(void)
{
    Uint16 uiFaultCondition = 0U;
    stPfcDiagLoc.stSingleFlt.siHysLmtVal = (int16)(((int32)stPfcDiagLoc.stSingleFlt.siLmtVal * (4096L - (int32)FLT_HYS_VAL())) / 4096L);

    if(GET_FLT_STS_WORD() > 0U)
    {
        if(GET_ACT_VAL() < stPfcDiagLoc.stSingleFlt.siHysLmtVal)        ///< Actual value is greater than limitation hysteresis value
        {
             uiFaultCondition = 0U;
        }
         else
        {
             if(GET_ACT_VAL() > GET_LMT_VAL())       ///< Actual value is greater than limitation
             {
                 uiFaultCondition = 1U;
             }
        }
    }
    else
    {
        if(GET_ACT_VAL() > GET_LMT_VAL())            ///< Actual value is greater than limitation
        {
            uiFaultCondition = 1U;
        }
        else
        {
            uiFaultCondition = 0U;
        }
    }
    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Analog fault analog value lower than limit value check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_LowrThanLmtMod(void)
{
    Uint16 uiFaultCondition = 0U;
    stPfcDiagLoc.stSingleFlt.siHysLmtVal = (int16)(((int32)stPfcDiagLoc.stSingleFlt.siLmtVal * (4096L + (int32)FLT_HYS_VAL())) / 4096L);

    if(GET_FLT_STS_WORD() > 0U)
    {
        if(GET_ACT_VAL() > stPfcDiagLoc.stSingleFlt.siHysLmtVal)        ///< Actual value is greater than limitation hysteresis value
        {
            uiFaultCondition = 0U;
        }
        else
        {
            if(GET_ACT_VAL() < GET_LMT_VAL())       ///< Actual value is less than limitation
            {
                uiFaultCondition = 1U;
            }
        }
    }
    else
    {
        if(GET_ACT_VAL() < GET_LMT_VAL())           ///< Actual value is greater than limitation
        {
            uiFaultCondition = 1U;
        }
        else
        {
            uiFaultCondition = 0U;
        }
    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault status equal 1 check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_StEquOneMod(void)
{
    Uint16 uiFaultCondition = 0U;
    if(GET_DIG_STS_VAL() > 0U)
    {
        uiFaultCondition = 1U;
    }

    else
    {
        uiFaultCondition = 0U;
    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

#if 0U
/********************************************Begin*********************************************/
/*
* @brief  Digital fault command equal status check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_CmdEquStMod(void)
{
     Uint16 uiFaultCondition = 0U;
     Uint16 uiCmdValueTemp   = 0U;
     Uint16 uiStsValueTemp   = 0U;
      if(GET_DIG_CMD_VAL() > 0U)
     {
         uiCmdValueTemp = 1U;
     }

     if(GET_DIG_STS_VAL() > 0U)
     {
         uiStsValueTemp = 1U;
     }

     if(uiCmdValueTemp == uiStsValueTemp)
     {
         uiFaultCondition = 1U;
     }
     else
     {
         uiFaultCondition = 0U;
     }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault command unequal status check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_CmdUnEquStMod(void)
{
    Uint16 uiFaultCondition = 0U;
    Uint16 uiCmdValueTemp   = 0U;
    Uint16 uiStsValueTemp   = 0U;
    if(GET_DIG_CMD_VAL() > 0U)
    {
        uiCmdValueTemp = 1U;
    }

    if(GET_DIG_STS_VAL() > 0U)
    {
        uiStsValueTemp = 1U;
    }

    if(uiCmdValueTemp != uiStsValueTemp)
    {
        uiFaultCondition = 1U;
    }
    else
    {
        uiFaultCondition = 0U;
    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault status equal 0 check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_StEquZeroMod(void)
{
     Uint16 uiFaultCondition = 0U;

     if(GET_DIG_STS_VAL() > 0U)
     {
         uiFaultCondition = 0U;
     }
     else
     {
         uiFaultCondition = 1U;
     }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault command equal 1 check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_CmdEquOneMod(void)
{
    Uint16 uiFaultCondition = 0U;

    if(GET_DIG_CMD_VAL() > 0U)
    {
        uiFaultCondition = 1U;
    }
    else
    {
        uiFaultCondition = 0U;
    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Digital fault command equal 0 check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_CmdEquZeroMod(void)
{
    Uint16 uiFaultCondition = 0U;

    if(GET_DIG_CMD_VAL() > 0U)
    {
        uiFaultCondition = 0U;
    }
    else
    {
        uiFaultCondition = 1U;
    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Analog fault analog absolute value higher than limit value check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_AbsHighrThanLmtMod(void)
{
    Uint16 uiFaultCondition = 0U;
    stPfcDiagLoc.stSingleFlt.siHysLmtVal = (int16)(((int32)GET_LMT_VAL_ABS() * (4096L - (int32)FLT_HYS_VAL())) >> 12L);

    if(GET_FLT_STS_WORD() > 0U)
    {
        if(GET_ACT_VAL_ABS() < stPfcDiagLoc.stSingleFlt.siHysLmtVal)
        {
            uiFaultCondition = 0U;
        }
        else
        {
            if(GET_ACT_VAL_ABS() > GET_LMT_VAL_ABS())
            {
                uiFaultCondition = 1U;
            }
        }
    }
    else
    {
        if(GET_ACT_VAL_ABS() > GET_LMT_VAL_ABS())
        {
            uiFaultCondition = 1U;
        }
        else
        {
            uiFaultCondition = 0U;
        }

    }

    return uiFaultCondition;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/*
* @brief  Analog fault analog absolute value lower than limit value check mode
* @param[in]
* @param[out]
* @return fault status
*/
static Uint16 ui_AbsLowrThanLmtMod(void)
{
    Uint16 uiFaultCondition = 0U;
    stPfcDiagLoc.stSingleFlt.siHysLmtVal = (int16)(((int32)GET_LMT_VAL_ABS() * (4096L + (int32)FLT_HYS_VAL())) >> 12L);

    if(GET_FLT_STS_WORD() > 0U)
    {
        if(GET_ACT_VAL_ABS() > stPfcDiagLoc.stSingleFlt.siHysLmtVal)
        {
            uiFaultCondition = 0U;
        }
        else
        {
            if(GET_ACT_VAL_ABS() < GET_LMT_VAL_ABS())
            {
                uiFaultCondition = 1U;
            }
        }
    }
    else
    {
        if(GET_ACT_VAL_ABS() < GET_LMT_VAL_ABS())
        {
            uiFaultCondition = 1U;
        }
        else
        {
            uiFaultCondition = 0U;
        }
    }

    return uiFaultCondition;
}
#endif
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC check state machine over-time fault diagnosis 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_StMac_Chk_100ms(void)
{
    if(PFC_ST_MAC_CHK == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        stPfcDiagLoc.uiCntrChkStOT++;
        if(stPfcDiagLoc.uiCntrChkStOT > PFC_ST_OV_TI)    ///< PFC state machine check state last longer than 5s/20s
        {
            stPfcDiagLoc.stPrmExt.unFlt.bit.uiChkStOT = 1U;
        }
    }
    else
    {
        stPfcDiagLoc.uiCntrChkStOT = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC wiring fault diagnosis 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_WiringFlt_100ms(void)
{
    if(STOP_CMD == stCom.uiCmdRunReq)
    {
    #if 1U == GRID_PHASE_NUMBER
        v_PfcDiag_WiringFlt_1Pha_100ms();    ///< 1-phase wiring fault diagnosis
    #elif 2U == GRID_PHASE_NUMBER
        v_PfcDiag_WiringFlt_2Pha_100ms();    ///< 2-phase wiring fault diagnosis
    #elif 3U == GRID_PHASE_NUMBER
        v_PfcDiag_WiringFlt_3Pha_100ms();    ///< 3-phase wiring fault diagnosis
    #endif
    }
}
/*********************************************End**********************************************/

#if 1U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC 1-phase wiring fault diagnosis 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_WiringFlt_1Pha_100ms(void)
{
    if(TYPE_GRID_AN != stCom.uiTypeGrid)    ///< Error wiring mode
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 1U;    ///< Set wiring error
    }
    else
    {
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 0U;    ///< Clear wiring error
    }
}

#elif 2U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC 2-phase wiring fault diagnosis 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_WiringFlt_2Pha_100ms(void)
{
    float32 l_ftVoltTmp = 0.0f;    ///< Temporary voltage

    if((TYPE_GRID_AN == stCom.uiTypeGrid) || (TYPE_GRID_BN == stCom.uiTypeGrid))    ///< Single phase mode
    {
        /* Voltage selection */
        if(TYPE_GRID_AN == stCom.uiTypeGrid)
        {
            l_ftVoltTmp = stPfcDataCalc.stMeasParm.ftVbRmsLPF;    ///< Select phase B voltage in AN mode
        }
        else
        {
            l_ftVoltTmp = stPfcDataCalc.stMeasParm.ftVaRmsLPF;    ///< select phase A voltage in BN mode
        }

        if(1U == stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring)
        {
            /* Fault clearance judgment */
            if(l_ftVoltTmp < PFC_ZV_RMS_LIM)
            {
                if(stPfcDiagLoc.uiCntrWiringDet++ > 10U)
                {
                    stPfcDiagLoc.uiCntrWiringDet = 0U;
                    stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 0U;    ///< Clear wiring error
                }
            }
            else
            {
                stPfcDiagLoc.uiCntrWiringDet = 0U;
            }
        }
        else
        {
            /* Fault judgment */
            if(l_ftVoltTmp > PFC_ZV_RMS_LIM)
            {
                if(stPfcDiagLoc.uiCntrWiringDet++ > 10U)
                {
                    stPfcDiagLoc.uiCntrWiringDet = 0U;
                    stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 1U;    ///< Set wiring error
                }
            }
            else if(stPfcDiagLoc.uiCntrWiringDet > 0U)
            {
                stPfcDiagLoc.uiCntrWiringDet--;
            }
            else
            {
                ///< Do nothing
            }
        }
    }
    else if((TYPE_GRID_ABN == stCom.uiTypeGrid) || (TYPE_GRID_AB == stCom.uiTypeGrid))
    {
        stPfcDiagLoc.uiCntrWiringDet = 0U;
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 0U;    ///< Clear wiring error
    }
    else    ///< Error wiring mode
    {
        stPfcDiagLoc.uiCntrWiringDet = 0U;
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 1U;    ///< Set wiring error
    }
}

#elif 3U == GRID_PHASE_NUMBER
/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC 3-phase wiring fault diagnosis 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_WiringFlt_3Pha_100ms(void)
{
    float32 l_ftVoltTmp1 = 0.0f;    ///< Temporary voltage
    float32 l_ftVoltTmp2 = 0.0f;    ///< Temporary voltage

    if((TYPE_GRID_AN == stCom.uiTypeGrid) || (TYPE_GRID_BN == stCom.uiTypeGrid) || (TYPE_GRID_CN == stCom.uiTypeGrid))    ///< Single phase mode
    {
        /* Voltage selection */
        if(TYPE_GRID_AN == stCom.uiTypeGrid)
        {
            l_ftVoltTmp1 = stPfcDataCalc.stMeasParm.ftVbRmsLPF;    ///< Select phase B/C voltage in AN mode
            l_ftVoltTmp2 = stPfcDataCalc.stMeasParm.ftVcRmsLPF;
        }
        else if(TYPE_GRID_BN == stCom.uiTypeGrid)
        {
            l_ftVoltTmp1 = stPfcDataCalc.stMeasParm.ftVaRmsLPF;    ///< select phase A/C voltage in BN mode
            l_ftVoltTmp2 = stPfcDataCalc.stMeasParm.ftVcRmsLPF;
        }
        else
        {
            l_ftVoltTmp1 = stPfcDataCalc.stMeasParm.ftVaRmsLPF;    ///< select phase A/B voltage in BN mode
            l_ftVoltTmp2 = stPfcDataCalc.stMeasParm.ftVbRmsLPF;
        }

        if(1U == stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring)
        {
            /* Fault clearance judgment */
            if((l_ftVoltTmp1 < PFC_ZV_RMS_LIM) && (l_ftVoltTmp2 < PFC_ZV_RMS_LIM))
            {
                if(stPfcDiagLoc.uiCntrWiringDet++ > 10U)
                {
                    stPfcDiagLoc.uiCntrWiringDet = 0U;
                    stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 0U;    ///< Clear wiring error
                }
            }
            else
            {
                stPfcDiagLoc.uiCntrWiringDet = 0U;
            }
        }
        else
        {
            /* Fault judgment */
            if((l_ftVoltTmp1 > PFC_ZV_RMS_LIM) || (l_ftVoltTmp2 > PFC_ZV_RMS_LIM))
            {
                if(stPfcDiagLoc.uiCntrWiringDet++ > 10U)
                {
                    stPfcDiagLoc.uiCntrWiringDet = 0U;
                    stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 1U;    ///< Set wiring error
                }
            }
            else if(stPfcDiagLoc.uiCntrWiringDet > 0U)
            {
                stPfcDiagLoc.uiCntrWiringDet--;
            }
            else
            {
                ///< Do nothing
            }
        }
    }
    else if((TYPE_GRID_ABCN == stCom.uiTypeGrid) || (TYPE_GRID_ABC == stCom.uiTypeGrid))
    {
        stPfcDiagLoc.uiCntrWiringDet = 0U;
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 0U;    ///< Clear wiring error
    }
    else    ///< Error wiring mode
    {
        stPfcDiagLoc.uiCntrWiringDet = 0U;
        stPfcDiagLoc.stPrmExt.unFlt.bit.uiWiring = 1U;    ///< Set wiring error
    }
}
/*********************************************End**********************************************/
#endif

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: AC over load fault diagnosis 100ms task
 *               Maximum single-phase apparent power protection in all mode. Total active power protection in off-grid mode.
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcDiag_OL_Flt_100ms(void)
{
    float32 l_ftAprtPowLim     = 0.0f;    ///< Apparent power Square limit
    float32 l_ftActvPow        = 0.0f;    ///< Active power
    float32 l_ftActvPowChrgLim = 0.0f;    ///< Charge active power limit
    float32 l_ftActvPowDchaLim = 0.0f;    ///< Discharge active power limit

    l_ftAprtPowLim = stComIf.ftPOnePhaMax * stPfcDiag.ftRatPwrOvLoadLim;
    /* Fault judgment */
    if(((CHG_ONGRID_MODE == stComIf.uiModPfcRun) && (stPfcDataCalc.stMeasParm.ftAprtPwr1PLPFMax > l_ftAprtPowLim)) \
       || (((BIDIR_ONGRID_MODE == stComIf.uiModPfcRun) || (OFFGRID_MODE == stComIf.uiModPfcRun)) && (stComIf.ftRatSumTiOvLoad > 1.0f)))
    {
        stPfcDiagLoc.uiCntrAprtOL++;
        if(stPfcDiagLoc.uiCntrAprtOL > 100U)   ///< Last for 10s
        {
            stPfcDiagLoc.stPrmExt.unFlt.bit.uiAcOL = 1U;    ///< Set AC over-load fault
        }
    }
    else if(stPfcDiagLoc.uiCntrAprtOL > 0U)
    {
        stPfcDiagLoc.uiCntrAprtOL--;
    }
    else
    {
        ///< Do nothing
    }

    /* Total active power protection in off-grid mode */
    l_ftActvPow = (float32)stPfcDataCalc.stMeasParm.slActvPowerLPF;        ///< l_ftActvPow is negative in charge mode
    l_ftActvPowChrgLim = stPowLim.ftPowAcChrgLim * stPfcDiag.ftRatPwrOvLoadLim;
    l_ftActvPowDchaLim = stPowLim.ftPowAcDchaLim * stPfcDiag.ftRatPwrOvLoadLim;
    /* Fault judgment */
    if((OFFGRID_MODE == stComIf.uiModPfcRun) && (PFC_ST_MAC_NORMRUN == stPfcStMac.unPFCSts.bit.uiMacSt) && (fabsf(l_ftActvPow) > 500.0f) \
       && (((-l_ftActvPow) > l_ftActvPowChrgLim) || (l_ftActvPow > l_ftActvPowDchaLim)))
    {
        stPfcDiagLoc.uiCntrActvOL++;
        if(stPfcDiagLoc.uiCntrActvOL > 100U)   ///< Last for 10s
        {
            stPfcDiagLoc.stPrmExt.unFlt.bit.uiAcOL = 1U;   ///< Set AC over-load fault
        }
    }
    else if(stPfcDiagLoc.uiCntrActvOL > 0U)
    {
        stPfcDiagLoc.uiCntrActvOL--;
    }
    else
    {
        ///< Do nothing
    }
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
