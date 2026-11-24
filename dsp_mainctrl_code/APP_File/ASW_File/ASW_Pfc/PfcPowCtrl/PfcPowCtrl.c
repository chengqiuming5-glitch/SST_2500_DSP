//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcPowCtrl.c
 * @brief
 * The source file of PFC power control module.
 *
 * Module      :                           \n
 * PfcPowCtrl
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_PfcPowCtrl_Init()                     \n
 * v_PfcPowCtrl_Isr()                      \n
 *
 * Unit Task   :                           \n
 *                                         \n
 *
 * Sub Unit Task   :                       \n
**************************************************************************
*/

/*
**************************************************************************
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD           \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2024/03/14  <td>1.0             <td>             <td>First edition
 * </table>
 *
 *************************************************************************
 */

#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcPowCtrl.h"
#include "PrmDispExt.h"
#ifndef _SIMULATION_NO_DSP_
#if 0U == FLG_SWUT_EN
#pragma CODE_SECTION(v_PfcPowCtrl_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_PwmEn_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Calc_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Calc_Filter_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Calc_PARK_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_PLL_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Clr_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_BusOVBurp_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Bus_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_3PDQ_Isr, ".TI.ramfunc");
#ifndef SST_1250kW
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_3PABC_Isr, ".TI.ramfunc");
#endif
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_1PCurr_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_ACVolt_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Dbg_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_BalBrdg_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Inner_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Inner_1P_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_Inner_3P_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_PWM_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_PWM_1P_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_PWM_3P_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_CellSOCBal_1ms, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Loop_CellBusVoltBal_1ms, ".TI.ramfunc");
#pragma CODE_SECTION(MPF_CALC, ".TI.ramfunc");
#pragma CODE_SECTION(DSOGI_CALC, ".TI.ramfunc");
#pragma CODE_SECTION(PR_CALC, ".TI.ramfunc");
//#pragma CODE_SECTION(NOTCH_CALC, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Frq_PrmCopy_Isr, ".TI.ramfunc");

#pragma CODE_SECTION(v_PfcPowCtrl_Emif_Prm_Calc_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_PfcPowCtrl_Emif_Fpga_Wr_Isr, ".TI.ramfunc");
#pragma CODE_SECTION(v_Emif_Rd_Isr, ".TI.ramfunc");
#endif
#endif
//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_POW_CTRL stPfcPowCtrl;    // PFC power control global struct
DSOGI_TYPE    stVg_Decompose;
DSOGI_TYPE    stIg_Decompose;

MPF_TYPE      stVaMpf;
MPF_TYPE      stVbMpf;
MPF_TYPE      stVcMpf;

NOTCH        BusVolt_Notch;
//NOTCH        PosBusVolt_Notch_A[6];
//NOTCH        PosBusVolt_Notch_B[6];
//NOTCH        PosBusVolt_Notch_C[6];
//NOTCH        NegBusVolt_Notch_A[6];
//NOTCH        NegBusVolt_Notch_B[6];
//NOTCH        NegBusVolt_Notch_C[6];


PR PR2_d;
PR PR2_q;
PR PR6_d;
PR PR6_q;
PR PR12_d;
PR PR12_q;

PR PR1_Ian;
PR PR2_Ian;
PR PR3_Ian;
PR PR5_Ian;
PR PR7_Ian;

PR ZeroVolt_PR1;
PR ZeroVolt_PR3;

//PR ZeroCurr_PR1;
//PR ZeroCurr_PR3;

PR MidBusVolt_PR;
PR MidBusCurr_PR;

ST_PI_PRM  stMidBusLoop;
ST_PI_PRM  stMidCurrLoop;

#if (1U == PFC_POW_CTRL_FLG_DBG)
ST_PFC_POW_CTRL stPfcPowCtrlDbg;    // PFC power control debug global struct
#endif

static ST_PFC_POW_CTRL_LOC stPfcPowCtrlLoc;    // PFC power control local struct
Uint16 flag_PFC = 0U;
//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC power control module initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcPowCtrl_Init(void)
{
    v_PfcPowCtrl_PwmEn_Init();
    v_PfcPowCtrl_Calc_Init();
    v_PfcPowCtrl_PLL_Init();
    v_PfcPowCtrl_Loop_Init();

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcPowCtrl_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC power control module ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcPowCtrl_Isr(void)
{
    v_PfcPowCtrl_PwmEn_Isr();

    v_PfcPowCtrl_Calc_Isr(); //8.3us

    v_PfcPowCtrl_PLL_Isr(); //1.26us

    v_PfcPowCtrl_Loop_Isr(); //8.92us

    v_PfcPowCtrl_Emif_Fpga_Wr_Isr(); //8.82us

    START_DMA1_READ();

}
/*********************************************End**********************************************/

/***********************************************************************************************
* @Type         : Module function
* @brief        : PFC power control 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowCtrl_1ms(void)
{
    v_PfcPowCtrl_DataCalc_1ms(); ///< Control parameter calculation (sst no use)
    v_PfcPowCtrl_V2LCBC_1ms();   ///< V2L current CBC (sst no use)
    v_PfcPowCtrl_CtrlMod_1ms();  ///< Control mode update 1ms task
    v_PfcPowCtrl_PrmClr_1ms();   ///< Control parameter clear after PFC stop-running 1ms task
    v_PfcPowCtrl_Loop_CellBusVoltBal_1ms();  ///< 17.5us balance half busvoltage loop
    v_PfcPowCtrl_Loop_CellSOCBal_1ms();
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC PWM enable/disable function initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_PwmEn_Init(void)
{
    stPfcPowCtrlLoc.uiCntrCbcTz             = 0U;             ///< Initialize to 0U
    stPfcPowCtrlLoc.uiFlgCbcTz              = 0U;             ///< Initialize to 0U
    stPfcPowCtrlLoc.stPowCtrlExt.uiFlgPwmEn = 0U;             ///< Initialize to 0U

    stPfcPowCtrl.uiFlgPwmEn = stPfcPowCtrlLoc.stPowCtrlExt.uiFlgPwmEn;
}
/*********************************************End**********************************************/

static void v_PfcPowCtrl_Emif_Prm_Calc_Isr(void)  //0.5us
{

    stPfcPowCtrlLoc.stEmifWrPre.unRunCmd1.uiD2dPwmValDutyPowCell = (Uint16)stD2dPowCtrl.ftD2dPwmValDutyPowCell;   ///< DC-DC PWM Duty

    if((1U == stComTbl.stPrmToFpga.uiClearRedFlt)&&(0U == stComIf.uiFlgFltRst)&&(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB))
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode = FPGA_D2D_MOD_CMD_CLEAR_REDUNDANT_FAULT;
    }
    else if((1U == stComTbl.stPrmToFpga.uiOTAModulFpga)&&(0U == stComIf.uiFlgFltRst)&&(stD2dStMac.uiStD2dRun <= D2D_ST_MAC_STB))
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode = FPGA_D2D_MOD_CELL_FPGA_UPDATE;
    }
    else
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode = stD2dPowCtrl.uiRunModPowCell;
    }


    if ((stPfcPowCtrl.uiFlgPwmEn == FCN_ENABLE)&&(0U == stComTbl.stPrmToFpga.uiClearRedFlt)&&(0U == stComIf.uiFlgFltRst))
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.PfcRunMode = FPGA_PFC_MOD_POWER_ON;
    }
    else
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.PfcRunMode = FPGA_PFC_MOD_POWER_OFF;
    }
    if((stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode == FPGA_D2D_MOD_CMD_CLEAR_SYS_FAULT)||(stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode == FPGA_D2D_MOD_CMD_CLEAR_REDUNDANT_FAULT) \
            ||(stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode == FPGA_D2D_MOD_CELL_FPGA_UPDATE))
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.PfcRunMode = stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode;
    }
    if(1U == stComTbl.stPrmToFpga.uiHandControl)
    {
        if((1U == stComTbl.stPrmToFpga.uiCloseRely)||(1U == stPfcStMac.unGPIOCmd.bit.uiRlyA))
        {
            stPfcPowCtrlLoc.stEmifWrPre.unRunCmd3.PreRelay_Ctrl = 1;
        }
        else
        {
            stPfcPowCtrlLoc.stEmifWrPre.unRunCmd3.PreRelay_Ctrl = 0;
        }
    }
    else
    {
        stPfcPowCtrlLoc.stEmifWrPre.unRunCmd3.PreRelay_Ctrl = stPfcStMac.unGPIOCmd.bit.uiRlyA;
    }
    if(1U == stComTbl.stPrmToFpga.uiHandControl)
    {
        stPfcPowCtrlLoc.stEmifWrPre.unARedCmd.DIS2EN = stComTbl.stPrmToFpga.uiRedunAEnable;
        stPfcPowCtrlLoc.stEmifWrPre.unARedCmd.DIS2N = stComTbl.stPrmToFpga.uiRedundantA;

        stPfcPowCtrlLoc.stEmifWrPre.unBRedCmd.DIS2EN = stComTbl.stPrmToFpga.uiRedunBEnable;
        stPfcPowCtrlLoc.stEmifWrPre.unBRedCmd.DIS2N = stComTbl.stPrmToFpga.uiRedundantB;

        stPfcPowCtrlLoc.stEmifWrPre.unCRedCmd.DIS2EN = stComTbl.stPrmToFpga.uiRedunCEnable;
        stPfcPowCtrlLoc.stEmifWrPre.unCRedCmd.DIS2N = stComTbl.stPrmToFpga.uiRedundantC;
    }
    else
    {

    }

}

static void v_PfcPowCtrl_Emif_Fpga_Wr_Isr(void) //9us
{
    static Uint16 sl_uiPollAddr = 0U;
    static Uint16 ParaData[11][2] = {{0, 0}, {1, 4095}, {2, 24999}, {3, 900}, {4, 0}, {5, 0}, {6, 19}, {7, 0},
                                         {0x1001, 4095}, {0x1002, 4095}, {0x1003, 4095}};


    v_PfcPowCtrl_Emif_Prm_Calc_Isr();

    stPfcPowCtrlLoc.stEmifWr.uiFrameHead = 0xAAAA;

    stPfcPowCtrlLoc.stEmifWr.unRunCmd1.uiD2dPwmValDutyPowCell = stPfcPowCtrlLoc.stEmifWrPre.unRunCmd1.uiD2dPwmValDutyPowCell;       ///< DC-DC PWM Duty

    stPfcPowCtrlLoc.stEmifWr.unRunCmd2.BURSTNUM = 0U;                                     ///< Module burst number: 0
    stPfcPowCtrlLoc.stEmifWr.unRunCmd2.DabRunMode = stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.DabRunMode;         ///< Power cell D2D Run Mode
    stPfcPowCtrlLoc.stEmifWr.unRunCmd2.PfcRunMode = stPfcPowCtrlLoc.stEmifWrPre.unRunCmd2.PfcRunMode;    ///< Power cell CHB Run Mode


    stPfcPowCtrlLoc.stEmifWr.unRunCmd3.PreRelay_Ctrl  = stPfcPowCtrlLoc.stEmifWrPre.unRunCmd3.PreRelay_Ctrl;  ///< Pre-charge relay on/off signal
    stPfcPowCtrlLoc.stEmifWr.unRunCmd3.OVER_CURR      = 0U;                               ///< AC cbc control disable
    stPfcPowCtrlLoc.stEmifWr.unRunCmd3.CTRL_MODE      = BIDIR_ONGRID_MODE;                ///< Bi-directional on grid mode

    stPfcPowCtrlLoc.stEmifWr.uiModulEnablA = stComTbl.stPrmToFpga.uiRunAEnable;
    stPfcPowCtrlLoc.stEmifWr.uiModulEnablB = stComTbl.stPrmToFpga.uiRunBEnable;
    stPfcPowCtrlLoc.stEmifWr.uiModulEnablC = stComTbl.stPrmToFpga.uiRunCEnable;


    stPfcPowCtrlLoc.stEmifWr.uiCmpA = (int16)(stPfcPowCtrl.ftVaCmn * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.uiCmpB = (int16)(stPfcPowCtrl.ftVbCmn * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.uiCmpC = (int16)(stPfcPowCtrl.ftVcCmn * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siId = (int16)(stPfcPowCtrlLoc.stIg.ftD_axis * 100.0);
    stPfcPowCtrlLoc.stEmifWr.siIq = (int16)(stPfcPowCtrlLoc.stIg.ftQ_axis * 100.0);

    stPfcPowCtrlLoc.stEmifWr.siSinTheta = (int16)(stPfcPowCtrlLoc.ftSinTheta * 1024.0);
    stPfcPowCtrlLoc.stEmifWr.siCosTheta = (int16)(stPfcPowCtrlLoc.ftCosTheta * 1024.0);

    stPfcPowCtrlLoc.stEmifWr.unARedCmd.all = stPfcPowCtrlLoc.stEmifWrPre.unARedCmd.all;
    stPfcPowCtrlLoc.stEmifWr.unBRedCmd.all = stPfcPowCtrlLoc.stEmifWrPre.unBRedCmd.all;
    stPfcPowCtrlLoc.stEmifWr.unCRedCmd.all = stPfcPowCtrlLoc.stEmifWrPre.unCRedCmd.all;

    sl_uiPollAddr++;
    if(sl_uiPollAddr >= 11)
    {
        sl_uiPollAddr = 0;
    }

    stPfcPowCtrlLoc.stEmifWr.siPollAddr = ParaData[sl_uiPollAddr][0];
 //   stPfcPowCtrlLoc.stEmifWr.siPollData = ParaData[sl_uiPollAddr][1];

    switch(stPfcPowCtrlLoc.stEmifWr.siPollAddr)
    {
        case ADDR_POLL_RES:
            stPfcPowCtrlLoc.stEmifWr.siPollData = stComTbl.stPrmToFpga.uiFltDataRec;
            break;
//        case ADDR_POLL_CHB_VOLT_BAL_TH: //ÏàÊý
//            stPfcPowCtrlLoc.stEmifWr.siPollData = (int16)(stPowLim.ftVoltBusLim * COEFF_AD_VBUS_RECPR); ///<Vbus ref
//            break;
        case ADDR_POLL_CHB_VOLT_BAL_TH_A:
            stPfcPowCtrlLoc.stEmifWr.siPollData = (int16)(stComTbl.stPrmToFpga.uiDischargeVolCHBA * COEFF_AD_VBUS_RECPR);
            break;
        case ADDR_POLL_CHB_VOLT_BAL_TH_B:
            stPfcPowCtrlLoc.stEmifWr.siPollData = (int16)(stComTbl.stPrmToFpga.uiDischargeVolCHBB * COEFF_AD_VBUS_RECPR);
            break;
        case ADDR_POLL_CHB_VOLT_BAL_TH_C:
            stPfcPowCtrlLoc.stEmifWr.siPollData = (int16)(stComTbl.stPrmToFpga.uiDischargeVolCHBC * COEFF_AD_VBUS_RECPR);
            break;
        case ADDR_POLL_CHB_FRQ:
            stPfcPowCtrlLoc.stEmifWr.siPollData = stComTbl.stPrmToFpga.uiPeriodCHB;
            break;
        case ADDR_POLL_DAB_FRQ:
            stPfcPowCtrlLoc.stEmifWr.siPollData = (Uint16)stD2dPowCtrl.ftD2dPwmPeriodPowCell;
            break;
        case ADDR_POLL_DAB_DEAD_TIME:
            stPfcPowCtrlLoc.stEmifWr.siPollData = (Uint16)stD2dPowCtrl.ftD2dPwmDeadTimePowCell;
            break;

        default:
            stPfcPowCtrlLoc.stEmifWr.siPollData = ParaData[sl_uiPollAddr][1];
            break;

    }


    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA1 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA2 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA3 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA4 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA5 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlA6 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[0][5] * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB1 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB2 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB3 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB4 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB5 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlB6 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[1][5] * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC1 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC2 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC3 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC4 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC5 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siSOCCtrlC6 = (int16)(stPfcPowCtrl.ftOutpCellSOCBal[2][5] * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA1 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA2 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA3 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA4 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA5 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlA6 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalA[5] * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB1 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB2 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB3 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB4 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB5 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlB6 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalB[5] * COEFF_AD_VBUS_RECPR);

    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC1 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[0] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC2 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[1] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC3 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[2] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC4 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[3] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC5 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[4] * COEFF_AD_VBUS_RECPR);
    stPfcPowCtrlLoc.stEmifWr.siHalfVbusCtrlC6 = (int16)(stPfcPowCtrl.ftOutpCellBusVoltBalC[5] * COEFF_AD_VBUS_RECPR);


    v_Emif_Fpga_Wr((int16 *)&stPfcPowCtrlLoc.stEmifWr, FPGA_WR_BASE_ADDR);//7us

    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[0] = 0x6666;
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[1] = (int16)stPfcAdc.stVg.ftVal_A;
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[2] = (int16)stPfcAdc.stVg.ftVal_B;
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[3] = (int16)stPfcAdc.stVg.ftVal_C;
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[4] = (int16)(stPfcAdc.stIg.ftVal_A * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[5] = (int16)(stPfcAdc.stIg.ftVal_B * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[6] = (int16)(stPfcAdc.stIg.ftVal_C * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[7] = (int16)(stPfcPowCtrlLoc.ftIdRef * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[8] = (int16)(stPfcPowCtrlLoc.ftIqRef * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[9] = (int16)(stPfcPowCtrlLoc.stPICurrD_P.ftOutp * 100.0);
    stPfcPowCtrlLoc.stEmifDebugWr.uiDebugData[10] = (int16)(stPfcPowCtrlLoc.stPICurrQ_P.ftOutp * 100.0);

    v_Emif_Fpga_Wr_Debug((int16 *)&stPfcPowCtrlLoc.stEmifDebugWr, FPGA_WR_DEBUG_ADDR);
}


/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC PWM enable/disable function ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_PwmEn_Isr(void)
{

    if((1U == stPfcStMac.unCtrlCmd.bit.uiCmdRun) && (0U == stPfcDiag.unFlt.all)\
      && (FCN_DISABLE == stOnOffGridSwt.uiFlgSwt))
    {
        stPfcPowCtrlLoc.stPowCtrlExt.uiFlgPwmEn = FCN_ENABLE;
    }
    else
    {
        stPfcPowCtrlLoc.stPowCtrlExt.uiFlgPwmEn = FCN_DISABLE;
    }

    stPfcPowCtrl.uiFlgPwmEn = stPfcPowCtrlLoc.stPowCtrlExt.uiFlgPwmEn;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control related calculation Initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Calc_Init(void)
{
    float32  l_ftTs;

    l_ftTs = stPfcDataCalc.stSysParm.ftSampTime;
    ///< AC voltage filter initial
    stVaMpf.stLcdSet.ftK = 1.414f;
    stVaMpf.stLcdSet.ftW = PI_2_CONST * RATED_AC_FRQ;
    MPF_INIT(&stVaMpf,l_ftTs);
    stVbMpf = stVaMpf;
    stVcMpf = stVaMpf;
    ///< Bus voltage filter initial
    BusVolt_Notch.stLcdSet.ftQ = 0.3f;
    BusVolt_Notch.stLcdSet.ftWo = 2.0f * RATED_AC_FRQ * PI_2_CONST;
    NOTCH_INIT(&BusVolt_Notch,l_ftTs);

    ///< Vd/Vq/Id/Iq filter initial
    stPfcPowCtrlLoc.stId_Lpf2.ftTs = stPfcDataCalc.stSysParm.ftSampTime;
    stPfcPowCtrlLoc.stId_Lpf2.ftWc = PI_2_CONST * 10000.0f;
    v_PfcPowCtrl_InitPfcRepLpfPrm(&stPfcPowCtrlLoc.stId_Lpf2);
    stPfcPowCtrlLoc.stIq_Lpf2 = stPfcPowCtrlLoc.stId_Lpf2;

    stVg_Decompose.stLcdSet.ftOsg_k = 0.4f;
    stVg_Decompose.stLcdSet.ftWn = PI_2_CONST * RATED_AC_FRQ;
    DSOGI_INIT(&stVg_Decompose,l_ftTs);

    stIg_Decompose.stLcdSet.ftOsg_k = 0.5f;
    stIg_Decompose.stLcdSet.ftWn = PI_2_CONST * RATED_AC_FRQ;
    DSOGI_INIT(&stIg_Decompose,l_ftTs);

    stPfcPowCtrlLoc.ftId_Lpf2                   = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftIq_Lpf2                   = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVdLpf                     = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVqLpf                     = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVbusLpf                   = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVbusRecpr                 = 0.003f;          ///< Initialize to 0.003f
    stPfcPowCtrlLoc.stPowCtrlExt.ftVa_MPF       = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftVb_MPF       = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftVc_MPF       = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftVbusNotch    = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf    = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftPosVoltSq    = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftNegVoltSq    = 0.0f;            ///< Initialize to 0.0f

    stPfcPowCtrl.ftVa_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVa_MPF;
    stPfcPowCtrl.ftVb_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVb_MPF;
    stPfcPowCtrl.ftVc_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVc_MPF;
    stPfcPowCtrl.ftVbusNotch    = stPfcPowCtrlLoc.stPowCtrlExt.ftVbusNotch;
    stPfcPowCtrl.ftVgDPllLpf    = stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf;
    stPfcPowCtrl.ftPosVoltSq    = stPfcPowCtrlLoc.stPowCtrlExt.ftPosVoltSq;
    stPfcPowCtrl.ftNegVoltSq    = stPfcPowCtrlLoc.stPowCtrlExt.ftNegVoltSq;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control related calculation ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Calc_Isr(void)
{
    v_PfcPowCtrl_Calc_Filter_Isr();  ///< Filter calculation
    v_PfcPowCtrl_Calc_PARK_Isr();    ///< Park calculation

    /* Output parameter */
    stPfcPowCtrl.ftVa_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVa_MPF;
    stPfcPowCtrl.ftVb_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVb_MPF;
    stPfcPowCtrl.ftVc_MPF       = stPfcPowCtrlLoc.stPowCtrlExt.ftVc_MPF;
    // stPfcPowCtrl.ftVbusNotch    = stPfcPowCtrlLoc.stPowCtrlExt.ftVbusNotch;
    stPfcPowCtrl.ftVgDPllLpf    = stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf; ///< for judg PLL OK
    stPfcPowCtrl.ftPosVoltSq    = stPfcPowCtrlLoc.stPowCtrlExt.ftPosVoltSq;
    stPfcPowCtrl.ftNegVoltSq    = stPfcPowCtrlLoc.stPowCtrlExt.ftNegVoltSq;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control related calculation ISR task-Filter calculation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Calc_Filter_Isr(void)
{

    stVaMpf.ftMpf_In = stPfcAdc.stVg.ftVal_A;  ///< ADC sample ac voltage input
    stVbMpf.ftMpf_In = stPfcAdc.stVg.ftVal_B;
    stVcMpf.ftMpf_In = stPfcAdc.stVg.ftVal_C;

    MPF_CALC(&stVaMpf);
    MPF_CALC(&stVbMpf);
    MPF_CALC(&stVcMpf);

#if 0
    BusVolt_Notch.ftInp = stPfcAdc.stVbus.ftVal_A;  ///< ADC sample bus voltage input
#else
 //   BusVolt_Notch.ftInp = stPfcAdc.stVbus.ftValLpf10kHz_A;  ///< ADC sample bus voltage input
#endif
   // NOTCH_CALC(&BusVolt_Notch); //100Hz SST no use
    ///< Bus voltage LPF calculation
    // FIRST_ORD_LPF(stPfcPowCtrlLoc.ftVbusLpf, stPfcAdc.stVbus.ftVal_A, LPF_100HZ_ISR_COEFF); //sst no use

    /* Output parameter */
    stPfcPowCtrlLoc.stPowCtrlExt.ftVa_MPF = stVaMpf.ftLpf_Out;
    stPfcPowCtrlLoc.stPowCtrlExt.ftVb_MPF = stVbMpf.ftLpf_Out;
    stPfcPowCtrlLoc.stPowCtrlExt.ftVc_MPF = stVcMpf.ftLpf_Out;
  //  stPfcPowCtrlLoc.stPowCtrlExt.ftVbusNotch = BusVolt_Notch.ftOutp;

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control related calculation ISR task-PARK transformation
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Calc_PARK_Isr(void)
{
    float32 l_ftIa = 0.0f;  ///< Initialize to 0.0f
    float32 l_ftIb = 0.0f;  ///< Initialize to 0.0f
    float32 l_ftIc = 0.0f;  ///< Initialize to 0.0f

    l_ftIa = stPfcAdc.stIg.ftVal_A;
    if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)
    {
        l_ftIb = stPfcAdc.stIg.ftVal_B;
        l_ftIc = stPfcAdc.stIg.ftVal_C;
    }
    else
    {
        l_ftIb = stPfcAdc.stIg.ftVal_B;
        l_ftIc = stPfcAdc.stIg.ftVal_C;
    }

    ///< Three phase voltage abc to alfa/beta
    stPfcPowCtrlLoc.stVg.ftAlfa  = stPfcAdc.stVg.ftVal_A * C2_DIV_C3 - (stPfcAdc.stVg.ftVal_B + stPfcAdc.stVg.ftVal_C) * RECPR_CON_3;
    stPfcPowCtrlLoc.stVg.ftBeta  = (stPfcAdc.stVg.ftVal_B - stPfcAdc.stVg.ftVal_C) * C1_DIV_SQRT3;
    ///< Three phase current abc to alfa/beta
    stPfcPowCtrlLoc.stIg.ftAlfa  = l_ftIa * C2_DIV_C3 - (l_ftIb + l_ftIc) * RECPR_CON_3;
    stPfcPowCtrlLoc.stIg.ftBeta  = (l_ftIb - l_ftIc) * C1_DIV_SQRT3;
    ///< Three phase voltage alfa/beta to D/Q
    stPfcPowCtrlLoc.stVg.ftD_axis = stPfcPowCtrlLoc.stVg.ftAlfa * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stVg.ftBeta * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stVg.ftQ_axis = stPfcPowCtrlLoc.stVg.ftBeta * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stVg.ftAlfa * stPfcPowCtrlLoc.ftSinTheta;
    ///< Three phase current alfa/beta to D/Q
    stPfcPowCtrlLoc.stIg.ftD_axis = stPfcPowCtrlLoc.stIg.ftAlfa * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stIg.ftBeta * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stIg.ftQ_axis = stPfcPowCtrlLoc.stIg.ftBeta * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stIg.ftAlfa * stPfcPowCtrlLoc.ftSinTheta;

    stPfcPowCtrlLoc.stIg.ftD_axis_N = stPfcPowCtrlLoc.stIg.ftAlfa * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stIg.ftBeta * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stIg.ftQ_axis_N = stPfcPowCtrlLoc.stIg.ftBeta * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stIg.ftAlfa * stPfcPowCtrlLoc.ftSinTheta;

    stVg_Decompose.ftAlpha_u[0] = stPfcPowCtrlLoc.stVg.ftAlfa;
    stVg_Decompose.ftBeta_u[0]  = stPfcPowCtrlLoc.stVg.ftBeta;
    DSOGI_CALC(&stVg_Decompose);

    stPfcPowCtrlLoc.stVg.ftD_axis_P = stVg_Decompose.ftUalphap * stPfcPowCtrlLoc.ftCosTheta + stVg_Decompose.ftUbetap * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stVg.ftQ_axis_P = stVg_Decompose.ftUbetap * stPfcPowCtrlLoc.ftCosTheta - stVg_Decompose.ftUalphap * stPfcPowCtrlLoc.ftSinTheta;

    stPfcPowCtrlLoc.stVg.ftD_axis_N = stVg_Decompose.ftUalphan * stPfcPowCtrlLoc.ftCosTheta - stVg_Decompose.ftUbetan * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stVg.ftQ_axis_N = stVg_Decompose.ftUbetan * stPfcPowCtrlLoc.ftCosTheta + stVg_Decompose.ftUalphan * stPfcPowCtrlLoc.ftSinTheta;
    ///< Positive&negative voltage calculation
    if(stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_CHK)
    {
        stPfcPowCtrlLoc.stPowCtrlExt.ftNegVoltSq = stPfcPowCtrlLoc.stVg.ftD_axis_N*stPfcPowCtrlLoc.stVg.ftD_axis_N + stPfcPowCtrlLoc.stVg.ftQ_axis_N * stPfcPowCtrlLoc.stVg.ftQ_axis_N;

        stPfcPowCtrlLoc.stPowCtrlExt.ftPosVoltSq = stPfcPowCtrlLoc.stVg.ftD_axis_P*stPfcPowCtrlLoc.stVg.ftD_axis_P + stPfcPowCtrlLoc.stVg.ftQ_axis_P * stPfcPowCtrlLoc.stVg.ftQ_axis_P;
    }

    ///< D-axis voltage filter cut-off frequency 40Hz Tau=4ms
    FIRST_ORD_LPF(stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf, stPfcPowCtrlLoc.stVg.ftD_axis_P, LPF_40HZ_ISR_COEFF);

    FIRST_ORD_LPF(stPfcPowCtrlLoc.ftVdLpf, stPfcPowCtrlLoc.stVg.ftD_axis, LPF_40HZ_ISR_COEFF);
    FIRST_ORD_LPF(stPfcPowCtrlLoc.ftVqLpf, stPfcPowCtrlLoc.stVg.ftQ_axis, LPF_40HZ_ISR_COEFF);
    ///< Id current LPF calculation
    SECOND_ORD_LPF(stPfcPowCtrlLoc.ftId_Lpf2, stPfcPowCtrlLoc.stIg.ftD_axis, stPfcPowCtrlLoc.stId_Lpf2);
    ///< Iq current LPF calculation
    SECOND_ORD_LPF(stPfcPowCtrlLoc.ftIq_Lpf2, stPfcPowCtrlLoc.stIg.ftQ_axis, stPfcPowCtrlLoc.stIq_Lpf2);

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control phase-lock-loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_PLL_Init(void)
{
    ///< PLL PI initial
    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPI_PLL);
    stPfcPowCtrlLoc.stPI_PLL.ftKp      = KP_PLL_INIT;
    stPfcPowCtrlLoc.stPI_PLL.ftKi      = KI_PLL_INIT;
    stPfcPowCtrlLoc.stPI_PLL.ftOutpMax = MAX_PLL_LOOP;
    stPfcPowCtrlLoc.stPI_PLL.ftOutpMin = MIN_PLL_LOOP;

    stPfcPowCtrlLoc.ftStepTheta = DELTA_THETA_STEP;
    stPfcPowCtrlLoc.ftPLLTheta  = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftSinTheta  = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftCosTheta  = 1.0f;        ///< Initialize to 1.0f
    stPfcPowCtrlLoc.ftSinThetaB = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftCosThetaB = 1.0f;        ///< Initialize to 1.0f
    stPfcPowCtrlLoc.ftSinThetaC = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftCosThetaC = 1.0f;        ///< Initialize to 1.0f

    stPfcPowCtrlLoc.stPowCtrlExt.ftFrqPll = RATED_AC_FRQ;
    stPfcPowCtrl.ftFrqPll = stPfcPowCtrlLoc.stPowCtrlExt.ftFrqPll;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control phase-lock-loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_PLL_Isr(void)
{
    static Uint16  sl_uiFlgVgZero = 0U;        ///< Initialize to 0U

    switch(stComIf.uiModPfcRun)
    {
        case CHG_ONGRID_MODE:
        case BIDIR_ONGRID_MODE:

            if(fabsf(stPfcPowCtrlLoc.stVg.ftQ_axis_P) < VQ_LIMN_PLL_OK)   ///< PLL is ok
            {
                stPfcPowCtrlLoc.stPI_PLL.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpPll;
                stPfcPowCtrlLoc.stPI_PLL.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiPll;
            }
            else
            {
                stPfcPowCtrlLoc.stPI_PLL.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpPllInit;
                stPfcPowCtrlLoc.stPI_PLL.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiPllInit;
            }

            stPfcPowCtrlLoc.stPI_PLL.ftInp = -stPfcPowCtrlLoc.stVg.ftQ_axis_P;
            INC_PI_CTRL(stPfcPowCtrlLoc.stPI_PLL);
            stPfcPowCtrlLoc.ftStepTheta = (stPfcDataCalc.stSysParm.ftPLL_DeltaTheta - stPfcPowCtrlLoc.stPI_PLL.ftOutp);

            break;
        case OFFGRID_MODE:
            stPfcPowCtrlLoc.ftStepTheta = stCom.ftFrqAcV2LReq * PI_2_CONST * stPfcDataCalc.stSysParm.ftSampTime;

        break;

        case OPENLOOP_MODE:
            stPfcPowCtrlLoc.ftStepTheta = stComTbl.stPrmOffGridCtrl.ftFrqAcDbgSet * PI_2_CONST * stPfcDataCalc.stSysParm.ftSampTime;
        break;
        default:
            ///< No code
            break;
    }
#if 0
    stPfcPowCtrlLoc.ftStepTheta = stComTbl.stPrmOffGridCtrl.ftFrqAcDbgSet * PI_2_CONST * stPfcDataCalc.stSysParm.ftSampTime;
#endif
    stPfcPowCtrlLoc.ftPLLTheta += stPfcPowCtrlLoc.ftStepTheta;

    stPfcPowCtrlLoc.stPowCtrlExt.ftFrqPll = stPfcPowCtrlLoc.ftStepTheta * stPfcDataCalc.stSysParm.ftFrqCoeff;

    ///< PLL theta limit
    if (stPfcPowCtrlLoc.ftPLLTheta >= PI_2_CONST)
    {
        stPfcPowCtrlLoc.ftPLLTheta -= PI_2_CONST;
    }
    else if(stPfcPowCtrlLoc.ftPLLTheta < 0.0f)
    {
        stPfcPowCtrlLoc.ftPLLTheta += PI_2_CONST;
    }
    else
    {
        // No code
    }

#if 1U == AI_DSTBC_VG_ZERO_MODE
    /* The injected reactive current is modified when the voltage crosses zero */
    if((stPfcPowCtrlLoc.ftPLLTheta > IREACTV_ZERO_THETA_MIN) && (stPfcPowCtrlLoc.ftPLLTheta < IREACTV_ZERO_THETA_MAX))
    {
        if(0U == sl_uiFlgVgZero)
        {
            stPfcPowCtrlLoc.ftIqDstbcAi = stPfcGridCtrl.stDstbc.ftIqAiDstbc;
            sl_uiFlgVgZero = 1U;
        }
    }
    else
    {
        sl_uiFlgVgZero = 0U;
    }
#endif
    ///< Three phase angle calculation
    #ifdef _SIMULATION_NO_DSP_
    stPfcPowCtrlLoc.ftSinTheta  = sin(stPfcPowCtrlLoc.ftPLLTheta);
    stPfcPowCtrlLoc.ftCosTheta  = cos(stPfcPowCtrlLoc.ftPLLTheta);
    stPfcPowCtrlLoc.ftSinThetaB = sin(stPfcPowCtrlLoc.ftPLLTheta - PI2_DIV_C3);
    stPfcPowCtrlLoc.ftCosThetaB = cos(stPfcPowCtrlLoc.ftPLLTheta - PI2_DIV_C3);
    stPfcPowCtrlLoc.ftSinThetaC = sin(stPfcPowCtrlLoc.ftPLLTheta + PI2_DIV_C3);
    stPfcPowCtrlLoc.ftCosThetaC = cos(stPfcPowCtrlLoc.ftPLLTheta + PI2_DIV_C3);
    #else
    stPfcPowCtrlLoc.ftSinTheta  = sinf(stPfcPowCtrlLoc.ftPLLTheta);
    stPfcPowCtrlLoc.ftCosTheta  = cosf(stPfcPowCtrlLoc.ftPLLTheta);
    if(PFC_3PCURRABC_CTRL == stPfcPowCtrlLoc.uiModLoop)
    {
        stPfcPowCtrlLoc.ftSinThetaB = sinf(stPfcPowCtrlLoc.ftPLLTheta - PI2_DIV_C3);
        stPfcPowCtrlLoc.ftCosThetaB = cosf(stPfcPowCtrlLoc.ftPLLTheta - PI2_DIV_C3);
        stPfcPowCtrlLoc.ftSinThetaC = sinf(stPfcPowCtrlLoc.ftPLLTheta + PI2_DIV_C3);
        stPfcPowCtrlLoc.ftCosThetaC = cosf(stPfcPowCtrlLoc.ftPLLTheta + PI2_DIV_C3);
    }
    #endif

    /* Output parameter */
    stPfcPowCtrl.ftFrqPll = stPfcPowCtrlLoc.stPowCtrlExt.ftFrqPll;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control loop control initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Init(void)
{
    stPfcPowCtrlLoc.uiModLoop   = PFC_DCBUS_CTRL;  ///< Initialize to PFC_DCBUS_CTRL
    stPfcPowCtrlLoc.uiModPwm    = SVPWM;           ///< Initialize to SVPWM
    stPfcPowCtrlLoc.ftIqDstbcAi = 0.0f;            ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVgFF      = 0.0f;            ///< Initialize to 0.0f
    v_PfcPowCtrl_Loop_PWM_Init();
    v_PfcPowCtrl_Loop_Curr_Init();
    v_PfcPowCtrl_Loop_ACVolt_Init();
    v_PfcPowCtrl_Loop_BalBrdg_Init();
    v_PfcPowCtrl_Loop_Inner_Init();
    v_PfcPowCtrl_Loop_CellBusVoltBal_Init();
    v_PfcPowCtrl_Loop_CellSOCBal_Init();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-PWM drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_PWM_Init(void)
{
    stPfcPowCtrlLoc.stPWMdrive.ftHarm      = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp = 0.5f;        ///< Initialize to 0.5f
    stPfcPowCtrlLoc.stPWMdrive.ftD_axis    = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftQ_axis    = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftZero      = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftAlfa      = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftBeta      = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftA         = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftB         = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftC         = 0.0f;        ///< Initialize to 0.0f
//    stPfcPowCtrlLoc.stPWMdrive.ftN         = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftMax       = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPWMdrive.ftMin       = 0.0f;        ///< Initialize to 0.0f

    stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q    = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D    = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D     = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q     = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stHarmCtrl.ftRepet_D   = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stHarmCtrl.ftRepet_Q   = 0.0f;        ///< Initialize to 0.0f

    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA = 0.0f;  ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB = 0.0f;  ///< Initialize to 0.0f
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC = 0.0f;  ///< Initialize to 0.0f
#ifndef SST_1250kW
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN = 0.0f;  ///< Initialize to 0.0f
#endif
    stPfcPowCtrl.ftOutpPwmModlnA = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA;
    stPfcPowCtrl.ftOutpPwmModlnB = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB;
    stPfcPowCtrl.ftOutpPwmModlnC = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC;
#ifndef SST_1250kW
    stPfcPowCtrl.ftOutpPwmModlnN = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC power control loop control ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Isr(void)
{

#ifndef _SIMULATION_NO_DSP_

    if(FCN_DISABLE == stPfcPowCtrl.uiFlgPwmEn)
#else
    if(stPfcStMac.unCtrlCmd.bit.uiCmdRun == 0)
#endif
    {
        v_PfcPowCtrl_Loop_Clr_Isr();
        stComTbl.stPrmToFpga.uiFltDataRec = 0;
    }
    else
    {
        stComTbl.stPrmToFpga.uiFltDataRec = 1;
        stPfcPowCtrlLoc.uiFlgLoopClr = 1U;

        switch (stPfcPowCtrlLoc.uiModLoop)
        {
            case PFC_DCBUS_CTRL:

                v_PfcPowCtrl_Loop_Bus_Isr();    ///< Only charge mode

            break;

            case PFC_3PCURRDQ_CTRL:

                v_PfcPowCtrl_Loop_3PDQ_Isr();   ///< On-grid bidirectional balance mode

            break;
#ifndef SST_1250kW
            case PFC_3PCURRABC_CTRL:

                v_PfcPowCtrl_Loop_3PABC_Isr();  ///< On-grid bidirectional imbalance mode

            break;
#endif
            case PFC_1PCURR_CTRL:

                v_PfcPowCtrl_Loop_1PCurr_Isr();  ///< On-grid bidirectional single phase mode

            break;

            case PFC_V2L_CTRL:

                v_PfcPowCtrl_Loop_ACVolt_Isr();  ///< Off-grid mode

            break;

            case PFC_DBG_CTRL:

                v_PfcPowCtrl_Loop_Dbg_Isr();     ///< Debug mode

            break;

            default:
                stPfcPowCtrlLoc.ftIdRef = 0.0f;
                stPfcPowCtrlLoc.ftIqRef = 0.0f;
                break;
        }

        //v_PfcPowCtrl_Loop_BalBrdg_Isr();

        v_PfcPowCtrl_Loop_Inner_Isr();

//        v_PfcPowCtrl_Loop_CellBusVoltBal_1ms();
        //v_PfcPowCtrl_Loop_PWM_Isr();
    }
        //v_PfcPowCtrl_Loop_BusOVBurp_Isr();

#if 0
    float32 l_ftVAlpha = 0;
    float32 l_ftVBeta = 0;
    stPfcPowCtrlLoc.stPWMdrive.ftD_axis = 1000.0f;
    stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = 0.0f;
    l_ftVAlpha = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
    l_ftVBeta  = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn = l_ftVAlpha + stPfcPowCtrlLoc.ftVaDcInhb;
    stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn = SQRT3_DIV_C2 * l_ftVBeta - RECPR_CON_2 * l_ftVAlpha + stPfcPowCtrlLoc.ftVbDcInhb;
    stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn = -stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn - stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn + stPfcPowCtrlLoc.ftVcDcInhb;
#endif
    /* Output parameter */
    stPfcPowCtrl.uiEnaBalBrdgPwm = stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm;
    stPfcPowCtrl.ftIdRef         = stPfcPowCtrlLoc.ftIdRef;
    stPfcPowCtrl.ftVaCmn         = stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn;
    stPfcPowCtrl.ftVbCmn         = stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn;
    stPfcPowCtrl.ftVcCmn         = stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Loop clear ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Clr_Isr(void)
{
    Uint16 i = 0U;
    if(1U == stPfcPowCtrlLoc.uiFlgLoopClr)
    {
        stPfcPowCtrlLoc.ftIdRef = 0.0f;
        stPfcPowCtrlLoc.ftIqRef = 0.0f;

        stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm = 0U;

        stPfcPowCtrlLoc.stPWMdrive.ftD_axis = stPfcPowCtrlLoc.ftVdLpf * stPfcPowCtrlLoc.ftVbusRecpr;
        stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = stPfcPowCtrlLoc.ftVqLpf * stPfcPowCtrlLoc.ftVbusRecpr;

        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q    = 0.0f;        ///< Initialize to 0.0f
        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D    = 0.0f;        ///< Initialize to 0.0f
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D     = 0.0f;        ///< Initialize to 0.0f
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q     = 0.0f;        ///< Initialize to 0.0f
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_D   = 0.0f;        ///< Initialize to 0.0f
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_Q   = 0.0f;        ///< Initialize to 0.0f

        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVbus);    ///< Initialize Bus voltage PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrC);   ///< Initialize current PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrD_P); ///< Initialize current PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrQ_P); ///< Initialize current PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrD_N); ///< Initialize current PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrQ_N); ///< Initialize current PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltD_P); ///< Initialize voltage PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltQ_P); ///< Initialize voltage PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltD_N); ///< Initialize voltage PI parameter
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltQ_N); ///< Initialize voltage PI parameter
        for(i = 0; i < NUM_PHA_POW_CELL;i++)
        {
            vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlA[i]);
            vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlB[i]);
            vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlC[i]);

            vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPISOCCtrl[i]);
        }

        stPfcPowCtrlLoc.uiFlgLoopClr = 0U;
    }

    stPfcPowCtrlLoc.stPIVoltD_P.ftIntgl = -stPfcPowCtrlLoc.stVg.ftD_axis_P;
    stPfcPowCtrlLoc.stPIVoltQ_P.ftIntgl = -stPfcPowCtrlLoc.stVg.ftQ_axis_P;
    stPfcPowCtrlLoc.stPIVoltD_N.ftIntgl = -stPfcPowCtrlLoc.stVg.ftD_axis_N;
    stPfcPowCtrlLoc.stPIVoltQ_N.ftIntgl = -stPfcPowCtrlLoc.stVg.ftQ_axis_N;
}
/*********************************************End**********************************************/

/**
* @brief   Bus over voltage burp function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_PfcPowCtrl_Loop_BusOVBurp_Isr(void)
{
    if((CHG_ONGRID_MODE == stComIf.uiModPfcRun) || (BIDIR_ONGRID_MODE == stComIf.uiModPfcRun))
    {
        if((stPfcAdc.stVbus.ftValLpf10kHz_A > VOLT_LIM_BUS_OV) && (0U == stPfcPowCtrlLoc.uiFlgBusOV))
        {
            stPfcPowCtrlLoc.uiFlgBusOV  = 1U;  ///< Bus over voltage flag set
            stPfcPowCtrlLoc.uiCntrBusOV = 0U;
        }
        else if(1U == stPfcPowCtrlLoc.uiFlgBusOV)
        {
            if(stPfcPowCtrlLoc.uiCntrBusOV < CNTR_LIM_BUS_OV)
            {
                stPfcPowCtrlLoc.uiCntrBusOV++;
            }

            if((stPfcPowCtrlLoc.uiCntrBusOV >= CNTR_LIM_BUS_OV) || ((stPowLim.ftVoltBusLim - stPfcPowCtrlLoc.stPowCtrlExt.ftVbusNotch) > -5.0f))
            {
                stPfcPowCtrlLoc.uiCntrBusOV = 0U;  ///< Bus over voltage flag clear
                stPfcPowCtrlLoc.uiFlgBusOV  = 0U;
            }
        }
        else
        {
            ///< Do nothing
        }
    }
    else
    {
        stPfcPowCtrlLoc.uiCntrBusOV = 0U;
        stPfcPowCtrlLoc.uiFlgBusOV  = 0U;
    }

    /* Output parameter */
    stPfcPowCtrl.uiFlgBusOV = stPfcPowCtrlLoc.uiFlgBusOV;
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Open loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Dbg_Isr(void)
{
    stPfcPowCtrlLoc.stPWMdrive.ftD_axis = stPfcPowPreCtrl.ftDutyAmpRef * CON_SQRT_2;// * stPfcPowCtrlLoc.ftVbusRecpr;
    stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = 0.0f;
//    stPfcPowCtrlLoc.stPWMdrive.ftN = 0.0f;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Bus voltage outer loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Bus_Isr(void)
{
#if 0
    ///< Bus voltage loop input
    stPfcPowCtrlLoc.stPIVbus.ftInp = stPfcPowPreCtrl.ftVoltBusRef - BusVolt_Notch.ftOutp;
#else
    stPfcPowCtrlLoc.stPIVbus.ftInp = stPfcPowPreCtrl.ftVoltBusRef - stPfcAdc.ftVbusCellAvg;
#endif
    ///< Bus voltage PI control
    POS_PI_CTRL(stPfcPowCtrlLoc.stPIVbus);
    ///< Bus voltage loop output
    stPfcPowCtrlLoc.ftIdRef = -stPfcPowCtrlLoc.stPIVbus.ftOutp;
    stPfcPowCtrlLoc.ftIqRef = 0;//stPfcPowPreCtrl.ftIaReactvAmpRef;
    stPrmDisp.ftPrm1 = stPfcAdc.ftVbusCellAvg;
    stPrmDisp.ftPrm2 = stPfcPowCtrlLoc.stPIVbus.ftOutp;
    stPrmDisp.ftPrm3 = stPfcPowPreCtrl.ftVoltBusRef;
//    stPrmDisp.ftPrm4 = stD2dAdc.ftVoltCellBusSum[2];
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Outer loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Curr_Init(void)
{
#ifndef SST_1250kW
    float32  l_ftTs;

    l_ftTs = stPfcDataCalc.stSysParm.ftSampTime;
    ///< Zero sequence current PR1 initial

    ZeroCurr_PR1.stLcdSet.ftKr = 30.0f;
    ZeroCurr_PR1.stLcdSet.ftWc = 8.0f;
    ZeroCurr_PR1.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ;
    ZeroCurr_PR1.stLcdSet.ftMax = 150.0f;
    ZeroCurr_PR1.stLcdSet.ftMin = -150.0f;
    PR_INIT(&ZeroCurr_PR1,l_ftTs);
    ///< Zero sequence current PR3 initial
    ZeroCurr_PR3.stLcdSet.ftKr = 20.0f;
    ZeroCurr_PR3.stLcdSet.ftWc = 12.0f;
    ZeroCurr_PR3.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 3.0f;
    ZeroCurr_PR3.stLcdSet.ftMax = 20.0f;
    ZeroCurr_PR3.stLcdSet.ftMin = -20.0f;
    PR_INIT(&ZeroCurr_PR3,l_ftTs);
#endif
//    stPfcPowCtrlLoc.ftIalfaRef = 0.0f;        ///< Initialize to 0.0f
//    stPfcPowCtrlLoc.ftIbetaRef = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftZeroOut = 0.0f;         ///< Initialize to 0.0f

    stPfcPowCtrlLoc.uiFlgLoopClr = 1U;        ///< Initialize to 1U
    stPfcPowCtrlLoc.ftStartDelay = 0.0f;      ///< Initialize to 0.0f

    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrC);   ///< Initialize current PI parameter
    stPfcPowCtrlLoc.stPICurrC.ftKp     = KP_CURR_LOOP;
    stPfcPowCtrlLoc.stPICurrC.ftKi     = KI_CURR_LOOP;
    stPfcPowCtrlLoc.stPICurrC.ftOutpMax = MAX_CURR_LOOP;
    stPfcPowCtrlLoc.stPICurrC.ftOutpMin = MIN_CURR_LOOP;
    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrD_P); ///< Initialize current PI parameter
    stPfcPowCtrlLoc.stPICurrD_P.ftKp     = KP_CURR_D_P_LOOP;
    stPfcPowCtrlLoc.stPICurrD_P.ftKi     = KI_CURR_D_P_LOOP;
    stPfcPowCtrlLoc.stPICurrD_P.ftOutpMax = MAX_CURR_D_P_LOOP;
    stPfcPowCtrlLoc.stPICurrD_P.ftOutpMin = MIN_CURR_D_P_LOOP;
    stPfcPowCtrlLoc.stPICurrQ_P = stPfcPowCtrlLoc.stPICurrD_P;
    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICurrD_N); ///< Initialize current PI parameter
    stPfcPowCtrlLoc.stPICurrD_N.ftKp     = KP_CURR_D_N_LOOP;
    stPfcPowCtrlLoc.stPICurrD_N.ftKi     = KI_CURR_D_N_LOOP;
    stPfcPowCtrlLoc.stPICurrD_N.ftOutpMax = MAX_CURR_D_N_LOOP;
    stPfcPowCtrlLoc.stPICurrD_N.ftOutpMin = MIN_CURR_D_N_LOOP;
    stPfcPowCtrlLoc.stPICurrQ_N = stPfcPowCtrlLoc.stPICurrD_N;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-3-phase current DQ-axis balance loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_3PDQ_Isr(void)
{
    stPfcPowCtrlLoc.ftIdRef = -stPfcPowPreCtrl.ftIaActvAmpRef;
    stPfcPowCtrlLoc.ftIqRef = stPfcPowPreCtrl.ftIaReactvAmpRef + 0*stPfcPowCtrlLoc.ftIqDstbcAi;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-3-phase current ABC-axis imbalance loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_3PABC_Isr(void)
{
#ifndef SST_1250kW
    float32 l_ftIZeroRef = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftIZeroFb  = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftIZeroInp = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftIaRef    = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftIbRef    = 0.0f;   ///< Initialize to 0.0f
    float32 l_ftIcRef    = 0.0f;   ///< Initialize to 0.0f
    ///< A/B/C phase current reference
    l_ftIaRef = -stPfcPowPreCtrl.ftIaActvAmpRef * stPfcPowCtrlLoc.ftCosTheta  - stPfcPowPreCtrl.ftIaReactvAmpRef * stPfcPowCtrlLoc.ftSinTheta;
    l_ftIbRef = -stPfcPowPreCtrl.ftIbActvAmpRef * stPfcPowCtrlLoc.ftCosThetaB - stPfcPowPreCtrl.ftIbReactvAmpRef * stPfcPowCtrlLoc.ftSinThetaB;
    l_ftIcRef = -stPfcPowPreCtrl.ftIcActvAmpRef * stPfcPowCtrlLoc.ftCosThetaC - stPfcPowPreCtrl.ftIcReactvAmpRef * stPfcPowCtrlLoc.ftSinThetaC;
    ///< A/B/C phase current reference to alfa/beta
    stPfcPowCtrlLoc.ftIalfaRef  = l_ftIaRef * C2_DIV_C3 - (l_ftIbRef + l_ftIcRef) * RECPR_CON_3;
    stPfcPowCtrlLoc.ftIbetaRef  = (l_ftIbRef - l_ftIcRef) * C1_DIV_SQRT3;
    ///< alfa/beta current reference to D/Q
    stPfcPowCtrlLoc.ftIdRef = stPfcPowCtrlLoc.ftIalfaRef * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.ftIbetaRef * stPfcPowCtrlLoc.ftSinTheta;
    stPfcPowCtrlLoc.ftIqRef = stPfcPowCtrlLoc.ftIbetaRef * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.ftIalfaRef * stPfcPowCtrlLoc.ftSinTheta\
                            + stPfcPowCtrlLoc.ftIqDstbcAi;
    ///< Zero sequence current control
    l_ftIZeroRef = (l_ftIaRef + l_ftIbRef + l_ftIcRef) * RECPR_CON_3;
    l_ftIZeroFb  = (stPfcAdc.stIg.ftValLpf10kHz_A + stPfcAdc.stIg.ftValLpf10kHz_B + stPfcAdc.stIg.ftValLpf10kHz_C) * RECPR_CON_3;
    l_ftIZeroInp = l_ftIZeroRef - l_ftIZeroFb;

    ZeroCurr_PR1.ftInp[0] = l_ftIZeroInp;
    PR_CALC(&ZeroCurr_PR1);
    ZeroCurr_PR3.ftInp[0] = l_ftIZeroInp;
    PR_CALC(&ZeroCurr_PR3);
    ///< Zero sequence current control output
    stPfcPowCtrlLoc.ftZeroOut = ZeroCurr_PR1.ftOutp[0] + ZeroCurr_PR3.ftOutp[0];
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-1-phase current loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_1PCurr_Isr(void)
{
    if(TYPE_GRID_AN == stCom.uiTypeGrid)
    {
        stPfcPowCtrlLoc.ftIdRef = -stPfcPowPreCtrl.ftIaActvAmpRef * 1.1f;  ///< Reference compensation
        stPfcPowCtrlLoc.ftIqRef = stPfcPowPreCtrl.ftIaReactvAmpRef + stPfcPowCtrlLoc.ftIqDstbcAi;
    }
    else if(TYPE_GRID_BN == stCom.uiTypeGrid)
    {
        stPfcPowCtrlLoc.ftIdRef = -stPfcPowPreCtrl.ftIbActvAmpRef * 1.1f; ///< Reference compensation
        stPfcPowCtrlLoc.ftIqRef = stPfcPowPreCtrl.ftIbReactvAmpRef + stPfcPowCtrlLoc.ftIqDstbcAi;
    }
    else
    {
        stPfcPowCtrlLoc.ftIdRef = -stPfcPowPreCtrl.ftIcActvAmpRef * 1.1f; ///< Reference compensation
        stPfcPowCtrlLoc.ftIqRef = stPfcPowPreCtrl.ftIcReactvAmpRef + stPfcPowCtrlLoc.ftIqDstbcAi;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-AC voltage loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_ACVolt_Init(void)
{
    float32  l_ftTs;

    l_ftTs = stPfcDataCalc.stSysParm.ftSampTime;  ///< Control period

    stPfcPowCtrlLoc.uiCntrBusOV  = 0U;        ///< Initialize to 0U
    stPfcPowCtrlLoc.uiFlgBusOV   = 0U;        ///< Initialize to 0U

    stPfcPowCtrlLoc.stVdRep.uiNrPerd         = MAX_REPEAT_NUM;
    stPfcPowCtrlLoc.stVdRep.ftQz             = QZ_AC_VOLT_LOOP_REP;
    stPfcPowCtrlLoc.stVdRep.ftKrComp         = KR_COMP_AC_VOLT_LOOP_REP;
    stPfcPowCtrlLoc.stVdRep.uiNrPhaComp      = NR_COMP_AC_VOLT_LOOP_REP;
    stPfcPowCtrlLoc.stVdRep.ftOutpMax        = MAX_AC_VOLT_LOOP_REP;
    stPfcPowCtrlLoc.stVdRep.ftOutp           = 0.0f;
    stPfcPowCtrlLoc.stVdRep.ftOutpLpf        = 0.0f;
    stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd.ftTs = PERD_PFC_CTRL;
    stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd.ftWc = PI_2_CONST * FRQ_LPF_REPEAT;
    v_PfcPowCtrl_InitPfcRepPrm(&stPfcPowCtrlLoc.stVdRep);
    v_PfcPowCtrl_InitPfcRepLpfPrm(&stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd);

    stPfcPowCtrlLoc.stVqRep = stPfcPowCtrlLoc.stVdRep;

    ZeroVolt_PR1.stLcdSet.ftKr = 6.0f;        ///< Initialize zero voltage sequence PR1 controller
    ZeroVolt_PR1.stLcdSet.ftWc = 4.0f;
    ZeroVolt_PR1.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ;
    ZeroVolt_PR1.stLcdSet.ftMax  = 40.0f;
    ZeroVolt_PR1.stLcdSet.ftMin  = -40.0f;
    PR_INIT(&ZeroVolt_PR1, l_ftTs);

    ZeroVolt_PR3.stLcdSet.ftKr = 5.0f;        ///< Initialize zero voltage sequence PR3 controller
    ZeroVolt_PR3.stLcdSet.ftWc = 5.0f;
    ZeroVolt_PR3.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 3.0f;
    ZeroVolt_PR3.stLcdSet.ftMax = 20.0f;
    ZeroVolt_PR3.stLcdSet.ftMin = -20.0f;
    PR_INIT(&ZeroVolt_PR3, l_ftTs);

    stPfcPowCtrlLoc.ftVaDcInhb = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVbDcInhb = 0.0f;        ///< Initialize to 0.0f
    stPfcPowCtrlLoc.ftVcDcInhb = 0.0f;        ///< Initialize to 0.0f

    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVbus);    ///< Initialize Bus voltage PI parameter
    stPfcPowCtrlLoc.stPIVbus.ftKp      = KP_PFC_BUS_VOLT_LOOP;
    stPfcPowCtrlLoc.stPIVbus.ftKi      = KI_PFC_BUS_VOLT_LOOP;
    stPfcPowCtrlLoc.stPIVbus.ftOutpMax = MAX_PFC_BUS_VOLT_LOOP;
    stPfcPowCtrlLoc.stPIVbus.ftOutpMin = MIN_PFC_BUS_VOLT_LOOP;
    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltD_P); ///< Initialize voltage PI parameter
    stPfcPowCtrlLoc.stPIVoltD_P.ftKp     = KP_VOLT_D_P_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_P.ftKi     = KI_VOLT_D_P_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_P.ftOutpMax = MAX_VOLT_D_P_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_P.ftOutpMin = MIN_VOLT_D_P_LOOP;
    stPfcPowCtrlLoc.stPIVoltQ_P = stPfcPowCtrlLoc.stPIVoltD_P;
    vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPIVoltD_N); ///< Initialize voltage PI parameter
    stPfcPowCtrlLoc.stPIVoltD_N.ftKp     = KP_VOLT_D_N_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_N.ftKi     = KI_VOLT_D_N_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_N.ftOutpMax = MAX_VOLT_D_N_LOOP;
    stPfcPowCtrlLoc.stPIVoltD_N.ftOutpMin = MIN_VOLT_D_N_LOOP;
    stPfcPowCtrlLoc.stPIVoltQ_N = stPfcPowCtrlLoc.stPIVoltD_N;

    stPfcPowCtrl.uiFlgBusOV = stPfcPowCtrlLoc.uiFlgBusOV;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-AC voltage loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_ACVolt_Isr(void)
{
    float32 l_ftVdErr   = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftVqErr   = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftSin2wt  = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftCos2wt  = 0.0f;        ///< Initialize to 0.0f

    l_ftVdErr = stPfcPowPreCtrl.ftVoltAcAmpRef - stPfcPowCtrlLoc.stVg.ftD_axis;
    l_ftVqErr = -stPfcPowCtrlLoc.stVg.ftQ_axis;
    ///< Positive sequence Vd control
    stPfcPowCtrlLoc.stPIVoltD_P.ftInp = l_ftVdErr;
    POS_PI_CTRL(stPfcPowCtrlLoc.stPIVoltD_P);
    ///< Positive sequence Vq control
    stPfcPowCtrlLoc.stPIVoltQ_P.ftInp = l_ftVqErr;
    POS_PI_CTRL(stPfcPowCtrlLoc.stPIVoltQ_P);

    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LNegVolt)
    {
        ///< Negative sequence Vd control
        stPfcPowCtrlLoc.stPIVoltD_N.ftInp = -stPfcPowCtrlLoc.stVg.ftD_axis_N;
        POS_PI_CTRL(stPfcPowCtrlLoc.stPIVoltD_N);
        ///< Negative sequence Vq control
        stPfcPowCtrlLoc.stPIVoltQ_N.ftInp = -stPfcPowCtrlLoc.stVg.ftQ_axis_N;
        POS_PI_CTRL(stPfcPowCtrlLoc.stPIVoltQ_N);
#if 0U
        ///< Negative sequence Id control
        stPfcPowCtrlLoc.stPICurrD_N.ftOutp = stPfcPowCtrlLoc.stPICurrD_N.ftKp * (stPfcPowCtrlLoc.stPIVoltD_N.ftOutp - stPfcPowCtrlLoc.stIg.ftD_axis_N);
        ///< Negative sequence Iq control
        stPfcPowCtrlLoc.stPICurrQ_N.ftOutp = stPfcPowCtrlLoc.stPICurrQ_N.ftKp * (stPfcPowCtrlLoc.stPIVoltQ_N.ftOutp - stPfcPowCtrlLoc.stIg.ftQ_axis_N);
        UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrD_N.ftOutp, stPfcPowCtrlLoc.stPICurrD_N.ftOutpMax, stPfcPowCtrlLoc.stPICurrD_N.ftOutpMin);
        UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrQ_N.ftOutp, stPfcPowCtrlLoc.stPICurrQ_N.ftOutpMax, stPfcPowCtrlLoc.stPICurrQ_N.ftOutpMin);
#endif
        l_ftSin2wt = stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftCosTheta;
        l_ftCos2wt = stPfcPowCtrlLoc.ftCosTheta * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftSinTheta;
        ///< Negative control output
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = stPfcPowCtrlLoc.stPIVoltD_N.ftOutp * l_ftCos2wt + stPfcPowCtrlLoc.stPIVoltQ_N.ftOutp * l_ftSin2wt;
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = stPfcPowCtrlLoc.stPIVoltQ_N.ftOutp * l_ftCos2wt - stPfcPowCtrlLoc.stPIVoltD_N.ftOutp * l_ftSin2wt;
    }
    else
    {
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = 0.0f;
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = 0.0f;
    }

    /* Harmonic nonlinear control */
    if((0U == stPfcPowCtrlLoc.uiFlgCbcTz) && (1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnV2LRep))  ///< CBC TZ flag is cleared
    {
        /* Vd repeat control */
        stPfcPowCtrlLoc.stVdRep.ftInp = l_ftVdErr;
        stPfcPowCtrlLoc.stVdRep.uiNrPerd = stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew;    ///< Update period number
        REPEAT_CTRL(stPfcPowCtrlLoc.stVdRep);
        /* LPF */
        SECOND_ORD_LPF(stPfcPowCtrlLoc.stVdRep.ftOutpLpf, stPfcPowCtrlLoc.stVdRep.ftOutp, stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd);
        /* Control loop output */
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_D = stPfcPowCtrlLoc.stVdRep.ftOutpLpf;
        /* Vq repeat control */
        stPfcPowCtrlLoc.stVqRep.ftInp = l_ftVqErr;
        stPfcPowCtrlLoc.stVqRep.uiNrPerd = stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew;    ///< Update period number
        REPEAT_CTRL(stPfcPowCtrlLoc.stVqRep);
        /* LPF */
        SECOND_ORD_LPF(stPfcPowCtrlLoc.stVqRep.ftOutpLpf, stPfcPowCtrlLoc.stVqRep.ftOutp, stPfcPowCtrlLoc.stVqRep.stLpf2ndOrd);
        /* Control loop output */
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_Q = stPfcPowCtrlLoc.stVqRep.ftOutpLpf;
    }
    else
    {
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_D = 0.0f;
        stPfcPowCtrlLoc.stHarmCtrl.ftRepet_Q = 0.0f;
    }

    ///< Positive sequence Id control
    stPfcPowCtrlLoc.stPICurrD_P.ftInp = stPfcPowCtrlLoc.stPIVoltD_P.ftOutp + stPfcPowCtrlLoc.stHarmCtrl.ftRepet_D;
    ///< Positive sequence Iq control
    stPfcPowCtrlLoc.stPICurrQ_P.ftInp = stPfcPowCtrlLoc.stPIVoltQ_P.ftOutp + stPfcPowCtrlLoc.stHarmCtrl.ftRepet_Q;
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrD_P.ftInp, MAX_AC_VOLT_LOOP, MIN_AC_VOLT_LOOP);
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrQ_P.ftInp, MAX_AC_VOLT_LOOP, MIN_AC_VOLT_LOOP);
    stPfcPowCtrlLoc.stPICurrD_P.ftOutp = stPfcPowCtrlLoc.stPICurrD_P.ftKp * (stPfcPowCtrlLoc.stPICurrD_P.ftInp - stPfcPowCtrlLoc.stIg.ftD_axis);
    stPfcPowCtrlLoc.stPICurrQ_P.ftOutp = stPfcPowCtrlLoc.stPICurrQ_P.ftKp * (stPfcPowCtrlLoc.stPICurrQ_P.ftInp - stPfcPowCtrlLoc.stIg.ftQ_axis);
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrD_P.ftOutp, stPfcPowCtrlLoc.stPICurrD_P.ftOutpMax, stPfcPowCtrlLoc.stPICurrD_P.ftOutpMin);
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPICurrQ_P.ftOutp, stPfcPowCtrlLoc.stPICurrQ_P.ftOutpMax, stPfcPowCtrlLoc.stPICurrQ_P.ftOutpMin);

    ZeroVolt_PR1.ftInp[0] = -(stPfcAdc.stVg.ftVal_A + stPfcAdc.stVg.ftVal_B + stPfcAdc.stVg.ftVal_C) * RECPR_CON_3;
    ///< Zero sequence voltage PR1 controller
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroVoltPR1st)
    {
        PR_CALC(&ZeroVolt_PR1);
    }
    else
    {
        PR_CLC(&ZeroVolt_PR1);
    }
    ///< Zero sequence voltage PR3 controller
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroVoltPR3rd)
    {
        ZeroVolt_PR3.ftInp[0] = ZeroVolt_PR1.ftInp[0];
        PR_CALC(&ZeroVolt_PR3);
    }
    else
    {
        PR_CLC(&ZeroVolt_PR3);
    }
    ///< Zero sequence voltage PR5 controller
//    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnZeroVoltPR5th)
//    {
//        ZeroVolt_PR5.ftInp[0] = ZeroVolt_PR1.ftInp[0];
//        PR_CALC(&ZeroVolt_PR5);
//    }
//    else
//    {
//        PR_CLC(&ZeroVolt_PR5);
//    }

    stPfcPowCtrlLoc.ftZeroOut = ZeroVolt_PR1.ftOutp[0] + ZeroVolt_PR3.ftOutp[0];
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Balance bridge loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_BalBrdg_Init(void)
{
    float32 l_ftTs;  ///< control/sample period

    l_ftTs = stPfcDataCalc.stSysParm.ftSampTime;
    ///< Balance bridge voltage loop PR controller initial
    MidBusVolt_PR.stLcdSet.ftKr  = 2.2f;
    MidBusVolt_PR.stLcdSet.ftWc  = 1.0f;
    MidBusVolt_PR.stLcdSet.ftWo  = PI_2_CONST * RATED_AC_FRQ;
    MidBusVolt_PR.stLcdSet.ftMax = 30.0f;
    MidBusVolt_PR.stLcdSet.ftMin = -30.0f;
    PR_INIT(&MidBusVolt_PR, l_ftTs);
    ///< Balance bridge current loop PR controller initial
    MidBusCurr_PR.stLcdSet.ftKr  = 6.0f;
    MidBusCurr_PR.stLcdSet.ftWc  = 4.0f;
    MidBusCurr_PR.stLcdSet.ftWo  = PI_2_CONST * RATED_AC_FRQ;
    MidBusCurr_PR.stLcdSet.ftMax = 20.0f;
    MidBusCurr_PR.stLcdSet.ftMin = -20.0f;
    PR_INIT(&MidBusCurr_PR, l_ftTs);
    ///< Balance bridge voltage/current loop PI controller initial
    stMidBusLoop.ftKp  = 0.001f;
    stMidBusLoop.ftOutpMax = 40.0f;
    stMidBusLoop.ftOutpMin = -40.0f;
    stMidCurrLoop.ftKp = 0.05f;

    stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm = 0U;       ///< Initialize to 0U

    stPfcPowCtrl.uiEnaBalBrdgPwm = stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Balance bridge control loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_BalBrdg_Isr(void)
{
    float32 l_ftErrTemp = 0.0f;        ///< Initialize to 0.0f
    ///< Input error
    stMidBusLoop.ftInp = stPfcAdc.stVbus.ftVal_A - 2.0f * stPfcAdc.stVbusPos.ftVal_A;
    l_ftErrTemp = fabsf(stMidBusLoop.ftInp);

    if((0U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnBalBrdg)\
    || ((PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss) && ((CHG_ONGRID_MODE == stComIf.uiModPfcRun) || (BIDIR_ONGRID_MODE == stComIf.uiModPfcRun))))
    {
        stMidBusLoop.ftOutp  = 0.0f;    ///< Clear PI control
        stMidCurrLoop.ftOutp = 0.0f;
        PR_CLC(&MidBusVolt_PR);     ///< Clear PR control
        PR_CLC(&MidBusCurr_PR);
        stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm = 0U;   ///< Clear PWM enable flag
    }
    else if((FCN_ENABLE == stPfcStMac.unPFCSts.bit.uiFlgRunOk)\
        && ((1U == stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm) || (l_ftErrTemp > stComTbl.stPrmBalBrdg.ftVoltBalEna)))
    {
        UP_DOWN_LIMIT(stMidBusLoop.ftInp,55.0f,-55.0f);   ///< Input limit
        stMidBusLoop.ftOutp = stMidBusLoop.ftInp * stMidBusLoop.ftKp;
        MidBusVolt_PR.ftInp[0] = stMidBusLoop.ftInp;
        PR_CALC(&MidBusVolt_PR);   ///< Voltage loop PR control

        stMidBusLoop.ftOutp = stMidBusLoop.ftOutp + MidBusVolt_PR.ftOutp[0];
        UP_DOWN_LIMIT(stMidBusLoop.ftOutp, stMidBusLoop.ftOutpMax, stMidBusLoop.ftOutpMin);
        stMidCurrLoop.ftInp = stMidBusLoop.ftOutp - stPfcAdc.stIg.ftVal_N;
        stMidCurrLoop.ftOutp = stMidCurrLoop.ftInp * stMidCurrLoop.ftKp; //V2L kp=0.8, V2H kp=3
        MidBusCurr_PR.ftInp[0] = stMidCurrLoop.ftInp;
        PR_CALC(&MidBusCurr_PR);   ///< Current loop PR control

        stPfcPowCtrlLoc.stPowCtrlExt.uiEnaBalBrdgPwm = 1U;
    }
    else
    {
        ///< No code
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Current inner loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Inner_Init(void)
{
    float32  l_ftTs = 0.0f;         ///< Initialize to 0.0f

    l_ftTs = stPfcDataCalc.stSysParm.ftSampTime;  ///< Control period
    ///< 3P current PR2 controller initial
    PR2_d.stLcdSet.ftKr = 20.0f;
    PR2_d.stLcdSet.ftWc = 4.0f;
    PR2_d.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 2.0f;
    PR2_d.stLcdSet.ftMax = 50.0f;
    PR2_d.stLcdSet.ftMin = -50.0f;
    PR_INIT(&PR2_d, l_ftTs);
    ///< 3P current PR2 controller initial
    PR2_q = PR2_d;
    ///< 3P current PR6 controller initial
    PR6_d.stLcdSet.ftKr = 20.0f;
    PR6_d.stLcdSet.ftWc = 20.0f;
    PR6_d.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 6.0f;
    PR6_d.stLcdSet.ftMax = 10.0f;
    PR6_d.stLcdSet.ftMin = -10.0f;
    PR_INIT(&PR6_d, l_ftTs);
    ///< 3P current PR6 controller initial
    PR6_q = PR6_d;
    ///< 3P current PR12 controller initial
    PR12_d.stLcdSet.ftKr = 3.0f;
    PR12_d.stLcdSet.ftWc = 36.0f;
    PR12_d.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 12.0f;
    PR12_d.stLcdSet.ftMax = 10.0f;
    PR12_d.stLcdSet.ftMin = -10.0f;
    PR_INIT(&PR12_d, l_ftTs);
    ///< 3P current PR12 controller initial
    PR12_q = PR12_d;
    ///< 1P current PR1 controller initial
    PR1_Ian.stLcdSet.ftKr = 10.0f;
    PR1_Ian.stLcdSet.ftWc = 3.0f;
    PR1_Ian.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ;
    PR1_Ian.stLcdSet.ftMax = 60.0f;
    PR1_Ian.stLcdSet.ftMin = -60.0f;
    PR_INIT(&PR1_Ian, l_ftTs);
    ///< 1P current PR2 controller initial
    PR2_Ian.stLcdSet.ftKr = 10.0f;
    PR2_Ian.stLcdSet.ftWc = 6.0f;
    PR2_Ian.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 2.0f;
    PR2_Ian.stLcdSet.ftMax = 30.0f;
    PR2_Ian.stLcdSet.ftMin = -30.0f;
    PR_INIT(&PR2_Ian, l_ftTs);
    ///< 1P current PR3 controller initial
    PR3_Ian.stLcdSet.ftKr = 10.0f;
    PR3_Ian.stLcdSet.ftWc = 9.0f;
    PR3_Ian.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 3.0f;
    PR3_Ian.stLcdSet.ftMax = 20.0f;
    PR3_Ian.stLcdSet.ftMin = -20.0f;
    PR_INIT(&PR3_Ian, l_ftTs);
    ///< 1P current PR5 controller initial
    PR5_Ian.stLcdSet.ftKr = 15.0f;
    PR5_Ian.stLcdSet.ftWc = 15.0f;
    PR5_Ian.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 5.0f;
    PR5_Ian.stLcdSet.ftMax = 20.0f;
    PR5_Ian.stLcdSet.ftMin = -20.0f;
    PR_INIT(&PR5_Ian, l_ftTs);
    ///< 1P current PR7 controller initial
    PR7_Ian.stLcdSet.ftKr = 15.0f;
    PR7_Ian.stLcdSet.ftWc = 21.0f;
    PR7_Ian.stLcdSet.ftWo = PI_2_CONST * RATED_AC_FRQ * 7.0f;
    PR7_Ian.stLcdSet.ftMax = 20.0f;
    PR7_Ian.stLcdSet.ftMin = -20.0f;
    PR_INIT(&PR7_Ian, l_ftTs);
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Cell Bus Voltage balanced loop initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_CellBusVoltBal_Init(void)
{
    Uint16 i = 0U;
    for(i = 0; i < NUM_PHA_POW_CELL;i++)
    {
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlA[i]);
        stPfcPowCtrlLoc.stPICellCtrlA[i].ftKp = KP_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlA[i].ftKi = KI_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlA[i].ftOutpMax = MAX_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlA[i].ftOutpMin = MIN_VOLT_BALANCE_LOOP;
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlB[i]);
        stPfcPowCtrlLoc.stPICellCtrlB[i].ftKp = KP_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlB[i].ftKi = KI_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutpMax = MAX_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutpMin = MIN_VOLT_BALANCE_LOOP;
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPICellCtrlC[i]);
        stPfcPowCtrlLoc.stPICellCtrlC[i].ftKp = KP_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlC[i].ftKi = KI_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutpMax = MAX_VOLT_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutpMin = MIN_VOLT_BALANCE_LOOP;
    }
    for(i = 0; i < 6;i++)
    {
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalA[i] = 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i] = 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i] = 0.0f;
        stPfcPowCtrl.ftOutpCellBusVoltBalA[i] = 0.0f;
        stPfcPowCtrl.ftOutpCellBusVoltBalB[i] = 0.0f;
        stPfcPowCtrl.ftOutpCellBusVoltBalC[i] = 0.0f;
    }
}
/*********************************************End**********************************************/

static void v_PfcPowCtrl_Loop_CellSOCBal_Init(void)
{
    Uint16 i = 0U;
    for(i = 0; i < NUM_PHA_POW_CELL;i++)
    {
        vFcn_InitPIPrm(&stPfcPowCtrlLoc.stPISOCCtrl[i]);
        stPfcPowCtrlLoc.stPISOCCtrl[i].ftKp = KP_SOC_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPISOCCtrl[i].ftKi = KI_SOC_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPISOCCtrl[i].ftOutpMax = MAX_SOC_BALANCE_LOOP;
        stPfcPowCtrlLoc.stPISOCCtrl[i].ftOutpMin = MIN_SOC_BALANCE_LOOP;
    }
    for(i = 0; i < 6;i++)
    {
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[0][i] = 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[1][i] = 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[2][i] = 0.0f;
        stPfcPowCtrl.ftOutpCellSOCBal[0][i] = 0.0f;
        stPfcPowCtrl.ftOutpCellSOCBal[1][i] = 0.0f;
        stPfcPowCtrl.ftOutpCellSOCBal[2][i] = 0.0f;
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-Current inner loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Inner_Isr(void)
{
    float32 l_ftVAlpha = 0;
    float32 l_ftVBeta = 0;
    switch (stPfcPowCtrlLoc.uiModLoop)
    {
        case PFC_DCBUS_CTRL:
        case PFC_3PCURRDQ_CTRL:
        case PFC_3PCURRABC_CTRL:
        case PFC_1PCURR_CTRL:
            /**Current open loop control control**********************************/
            if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)
            {
                v_PfcPowCtrl_Loop_Inner_1P_Isr();  ///< Single phase current loop
            }
            else
            {
                flag_PFC = 1U;
                v_PfcPowCtrl_Loop_Inner_3P_Isr();  ///< Three phase current loop
                stPrmDisp.ftPrm4 = stPfcPowCtrlLoc.stPICurrD_P.ftOutp;
                stPrmDisp.ftPrm5 = stPfcAdc.stVg.ftVal_A;
            }

        break;

        case PFC_V2L_CTRL:

            stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (stPfcPowCtrlLoc.stPICurrD_P.ftOutp + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D \
                                                   + stPfcPowCtrlLoc.stVg.ftD_axis) * stPfcPowCtrlLoc.ftVbusRecpr;
            stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (stPfcPowCtrlLoc.stPICurrQ_P.ftOutp + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q \
                                                   + stPfcPowCtrlLoc.stVg.ftQ_axis) * stPfcPowCtrlLoc.ftVbusRecpr;
            stPfcPowCtrlLoc.stPWMdrive.ftZero   = stPfcPowCtrlLoc.ftZeroOut * stPfcPowCtrlLoc.ftVbusRecpr * 10.0f;

        break;

        case PFC_DBG_CTRL:

            l_ftVAlpha = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
            l_ftVBeta  = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;
            stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn = l_ftVAlpha + stPfcPowCtrlLoc.ftVaDcInhb;
            stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn = SQRT3_DIV_C2 * l_ftVBeta - RECPR_CON_2 * l_ftVAlpha + stPfcPowCtrlLoc.ftVbDcInhb;
            stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn = -stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn - stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn + stPfcPowCtrlLoc.ftVcDcInhb;///< No code
        break;

        default:
            ///< No code
            break;
    }
#ifndef SST_1250kW
    stPfcPowCtrlLoc.stPWMdrive.ftN = (stMidCurrLoop.ftOutp + MidBusCurr_PR.ftOutp[0]) * stPfcPowCtrlLoc.ftVbusRecpr;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-sub Unit function: PFC power control loop control-3P-Current inner loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Inner_3P_Isr(void)
{
    float32 l_ftSin2wt    = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftCos2wt    = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftVAlpha   = 0.0f;
    float32 l_ftVBeta   = 0.0f;

    /**Positive sequence D-axis current control********************************************************/
    stPfcPowCtrlLoc.stPICurrD_P.ftInp = stPfcPowCtrlLoc.ftIdRef - stPfcPowCtrlLoc.ftId_Lpf2;
//    stPfcPowCtrlLoc.stPICurrD_P.ftInp = stPrmDisp.ftPrm1 - stPfcPowCtrlLoc.ftId_Lpf2;
//    stPfcPowCtrlLoc.stPICurrD_P.ftInp = stPfcPowCtrlLoc.ftIdRef - stPfcPowCtrlLoc.stIg.ftD_axis;
    POS_PI_CTRL(stPfcPowCtrlLoc.stPICurrD_P);

    /**Positive sequence Q-axis current control********************************************************/
    stPfcPowCtrlLoc.stPICurrQ_P.ftInp = stPfcPowCtrlLoc.ftIqRef - stPfcPowCtrlLoc.ftIq_Lpf2;
//    stPfcPowCtrlLoc.stPICurrQ_P.ftInp = stPrmDisp.ftPrm2 - stPfcPowCtrlLoc.ftIq_Lpf2;
//    stPfcPowCtrlLoc.stPICurrQ_P.ftInp = stPfcPowCtrlLoc.ftIqRef - stPfcPowCtrlLoc.stIg.ftQ_axis;
    POS_PI_CTRL(stPfcPowCtrlLoc.stPICurrQ_P);

    /**Harmonic current control************************************************************************/
#if 1
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnCurrThd3P)
    {
        PR12_d.ftInp[0] = -stPfcPowCtrlLoc.stIg.ftD_axis;
        PR_CALC(&PR12_d);  ///< D-axis current PR12 control
        PR12_q.ftInp[0] = -stPfcPowCtrlLoc.stIg.ftQ_axis;
        PR_CALC(&PR12_q);  ///< Q-axis current PR12 control
        PR6_d.ftInp[0]  = -stPfcPowCtrlLoc.stIg.ftD_axis;
        PR_CALC(&PR6_d);   ///< D-axis current PR6 control
        PR6_q.ftInp[0]  = -stPfcPowCtrlLoc.stIg.ftQ_axis;
        PR_CALC(&PR6_q);   ///< Q-axis current PR6 control
        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D = PR12_d.ftOutp[0] + PR6_d.ftOutp[0];
        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q = PR12_q.ftOutp[0] + PR6_q.ftOutp[0];
    }
    else
    {
        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D = 0.0f;
        stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q = 0.0f;
    }

    /**Negative sequence current control**********************************************************/
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiEnCurrNeg3P)
    {
        if(PFC_3PCURRDQ_CTRL == stPfcPowCtrlLoc.uiModLoop)
        {
            stPfcPowCtrlLoc.stPICurrD_N.ftInp = -stPfcPowCtrlLoc.stIg.ftD_axis_N;
            POS_PI_CTRL(stPfcPowCtrlLoc.stPICurrD_N);  ///< D-axis negative current PI control

            stPfcPowCtrlLoc.stPICurrQ_N.ftInp = -stPfcPowCtrlLoc.stIg.ftQ_axis_N;
            POS_PI_CTRL(stPfcPowCtrlLoc.stPICurrQ_N);  ///< Q-axis negative current PI control

            l_ftSin2wt = stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftCosTheta;
            l_ftCos2wt = stPfcPowCtrlLoc.ftCosTheta * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.ftSinTheta * stPfcPowCtrlLoc.ftSinTheta;
            ///< Negative control output
            stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = stPfcPowCtrlLoc.stPICurrD_N.ftOutp * l_ftCos2wt + stPfcPowCtrlLoc.stPICurrQ_N.ftOutp * l_ftSin2wt;
            stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = stPfcPowCtrlLoc.stPICurrQ_N.ftOutp * l_ftCos2wt - stPfcPowCtrlLoc.stPICurrD_N.ftOutp * l_ftSin2wt;
        }
        else
        {
            PR2_d.ftInp[0] = stPfcPowCtrlLoc.ftIdRef - stPfcPowCtrlLoc.stIg.ftD_axis;
            PR_CALC(&PR2_d);  ///< D-axis current PR2 control
            PR2_q.ftInp[0] = stPfcPowCtrlLoc.ftIqRef - stPfcPowCtrlLoc.stIg.ftQ_axis;
            PR_CALC(&PR2_q);  ///< Q-axis current PR2 control
            ///< Negative control output
            stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = PR2_d.ftOutp[0];
            stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = PR2_q.ftOutp[0];
        }
    }
    else
    {
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = 0.0f;
        stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = 0.0f;
    }

    if(0U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
    {
        stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (stPfcPowCtrlLoc.stPICurrD_P.ftOutp + stPfcPowCtrlLoc.stVg.ftD_axis + stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D*0) * 1.0f;
        stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (stPfcPowCtrlLoc.stPICurrQ_P.ftOutp + stPfcPowCtrlLoc.stVg.ftQ_axis + stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q*0) * 1.0f;
    }
    else
    {
        stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (stPfcPowCtrlLoc.stPICurrD_P.ftOutp + COEFF_KP_VOLT_FF * stPfcPowCtrlLoc.ftVdLpf + stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D) * 1.0f;
        stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (stPfcPowCtrlLoc.stPICurrQ_P.ftOutp + COEFF_KP_VOLT_FF * stPfcPowCtrlLoc.ftVqLpf + stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q + stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q) * 1.0f;
    }

    if(0U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
    {
        /* DQ to Alpha-Beta */
        l_ftVAlpha = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
        l_ftVBeta  = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;
    }
    else
    {
        /* DQ to Alpha-Beta */
        l_ftVAlpha = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta \
                                            + (1.0f - COEFF_KP_VOLT_FF) * stPfcPowCtrlLoc.stVg.ftAlfa;
        l_ftVBeta = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta \
                                            + (1.0f - COEFF_KP_VOLT_FF) * stPfcPowCtrlLoc.stVg.ftBeta;
    }
#else
    stPfcPowCtrlLoc.stHarmCtrl.ftHarm_D = 0.0f;
    stPfcPowCtrlLoc.stHarmCtrl.ftHarm_Q = 0.0f;
    stPfcPowCtrlLoc.stHarmCtrl.ftNeg_D = 0.0f;
    stPfcPowCtrlLoc.stHarmCtrl.ftNeg_Q = 0.0f;

    stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (stPfcPowCtrlLoc.stPICurrD_P.ftOutp + stPfcPowCtrlLoc.stVg.ftD_axis);
    stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (stPfcPowCtrlLoc.stPICurrQ_P.ftOutp + stPfcPowCtrlLoc.stVg.ftQ_axis);
    /* DQ to Alpha-Beta */
    l_ftVAlpha = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
    l_ftVBeta  = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;

#endif
    /* Alpha-Beta to ABC */
    if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)
    {

        stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn = l_ftVAlpha;
        stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn = SQRT3_DIV_C2 * l_ftVBeta - RECPR_CON_2 * l_ftVAlpha;
        stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn = -stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn - stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn;
    }
    else
    {
        stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn = l_ftVAlpha;
        stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn = SQRT3_DIV_C2 * l_ftVBeta - RECPR_CON_2 * l_ftVAlpha;
        stPfcPowCtrlLoc.stPowCtrlExt.ftVbCmn = -stPfcPowCtrlLoc.stPowCtrlExt.ftVaCmn - stPfcPowCtrlLoc.stPowCtrlExt.ftVcCmn;
    }

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-sub Unit function: PFC power control loop control-1P-Current inner loop ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_Inner_1P_Isr(void)
{
    float32 l_ftCurrFb = 0.0f;        ///< Initialize to 0.0f
    float32 l_ftIdcInp = 0.0f;        ///< Initialize to 0.0f
    ///< Current feedback select
    if(TYPE_GRID_AN == stCom.uiTypeGrid)
    {
        l_ftIdcInp = stPfcGridCtrl.stDstbc.ftIaDcInhb;
        l_ftCurrFb = stPfcAdc.stIg.ftValLpf10kHz_A;
    }
    else if(TYPE_GRID_BN == stCom.uiTypeGrid)
    {
        l_ftIdcInp = stPfcGridCtrl.stDstbc.ftIbDcInhb;
        l_ftCurrFb = stPfcAdc.stIg.ftValLpf10kHz_B;
    }
    else
    {
        l_ftIdcInp = stPfcGridCtrl.stDstbc.ftIcDcInhb;
        l_ftCurrFb = stPfcAdc.stIg.ftValLpf10kHz_C;
    }
    /* Current PR control input without Idc disturbance */
    PR1_Ian.ftInp[0] = stPfcPowCtrlLoc.ftIdRef * stPfcPowCtrlLoc.ftCosTheta \
    - stPfcPowCtrlLoc.ftIqRef * stPfcPowCtrlLoc.ftSinTheta - l_ftCurrFb;
    /* Current PI control input with Idc disturbance */
     stPfcPowCtrlLoc.stPICurrC.ftInp = PR1_Ian.ftInp[0] - l_ftIdcInp;
    ///< Single phase current loop PI control
    POS_PI_CTRL(stPfcPowCtrlLoc.stPICurrC);
    ///< Single phase current loop PR1 control
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR1st)
    {
        PR_CALC(&PR1_Ian);
    }
    else
    {
        PR_CLC(&PR1_Ian);
    }
    ///< Single phase current loop PR2 control
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR2nd)
    {
        PR2_Ian.ftInp[0] = PR1_Ian.ftInp[0];
        PR_CALC(&PR2_Ian);
    }
    else
    {
        PR_CLC(&PR2_Ian);
    }
    ///< Single phase current loop PR3 control
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR3rd)
    {
        PR3_Ian.ftInp[0] = PR1_Ian.ftInp[0];
        PR_CALC(&PR3_Ian);
    }
    else
    {
        PR_CLC(&PR3_Ian);
    }
    ///< Single phase current loop PR5 control
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR5th)
    {
        PR5_Ian.ftInp[0] = PR1_Ian.ftInp[0];
        PR_CALC(&PR5_Ian);
    }
    else
    {
        PR_CLC(&PR5_Ian);
    }
    ///< Single phase current loop PR7 control
    if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.bit.uiEnCurrPR7th)
    {
        PR7_Ian.ftInp[0] = PR1_Ian.ftInp[0];
        PR_CALC(&PR7_Ian);
    }
    else
    {
        PR_CLC(&PR7_Ian);
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC power control loop control-PWM drive ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_PWM_Isr(void)
{
    if((PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss) && (PFC_V2L_CTRL != stPfcPowCtrlLoc.uiModLoop))
    {
        v_PfcPowCtrl_Loop_PWM_1P_Isr();   ///< Single phase modulation
    }
    else
    {
        if(stPfcPowCtrlLoc.uiModLoop != PFC_V2L_CTRL)
        {
            stPfcPowCtrlLoc.ftVaDcInhb = 0.0f;
            stPfcPowCtrlLoc.ftVbDcInhb = 0.0f;
            stPfcPowCtrlLoc.ftVcDcInhb = 0.0f;
            if(stPfcPowCtrlLoc.uiModLoop != PFC_3PCURRABC_CTRL)
            {
                stPfcPowCtrlLoc.stPWMdrive.ftZero = 0.0f;
            }
        }

        v_PfcPowCtrl_Loop_PWM_3P_Isr();   ///< Three phase modulation
    }

    /* Output parameter */
    stPfcPowCtrl.ftOutpPwmModlnA = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA;
    stPfcPowCtrl.ftOutpPwmModlnB = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB;
    stPfcPowCtrl.ftOutpPwmModlnC = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC;
#ifndef SST_1250kW
    stPfcPowCtrl.ftOutpPwmModlnN = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: PFC power control loop control- Single phase PWM drive ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_PWM_1P_Isr(void)
{
    if(TYPE_GRID_AN == stCom.uiTypeGrid)
    {
        /* Grid voltage forward feedback method select */
        if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf * stPfcPowCtrlLoc.ftCosTheta * COEFF_KP_VOLT_FF + stPfcAdc.stVg.ftValLpf10kHz_A * (1.0f - COEFF_KP_VOLT_FF);
        }
        else
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcAdc.stVg.ftValLpf10kHz_A;
        }
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA = (stPfcPowCtrlLoc.stPICurrC.ftOutp + PR1_Ian.ftOutp[0] + PR2_Ian.ftOutp[0] + PR3_Ian.ftOutp[0] + PR5_Ian.ftOutp[0] \
                                                        + PR7_Ian.ftOutp[0] + stPfcPowCtrlLoc.ftVgFF) * stPfcPowCtrlLoc.ftVbusRecpr;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB = 0.0f;                       ///< Limit to 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC = 0.0f;                       ///< Limit to 0.0f;
        UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA, 0.5f, -0.5f);  ///< Phase A modulation limit
    }
    else if(TYPE_GRID_BN == stCom.uiTypeGrid)
    {
        /* Grid voltage forward feedback method select */
        if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf * stPfcPowCtrlLoc.ftCosTheta * COEFF_KP_VOLT_FF + stPfcAdc.stVg.ftValLpf10kHz_B * (1.0f - COEFF_KP_VOLT_FF);
        }
        else
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcAdc.stVg.ftValLpf10kHz_B;
        }
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA = 0.0f;                       ///< Limit to 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB = (stPfcPowCtrlLoc.stPICurrC.ftOutp + PR1_Ian.ftOutp[0] + PR2_Ian.ftOutp[0] + PR3_Ian.ftOutp[0] + PR5_Ian.ftOutp[0] \
                                                        + PR7_Ian.ftOutp[0] + stPfcPowCtrlLoc.ftVgFF) * stPfcPowCtrlLoc.ftVbusRecpr;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC = 0.0f;                       ///< Limit to 0.0f;
        UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB, 0.5f, -0.5f);  ///< Phase B modulation limit
    }
    else
    {
        /* Grid voltage forward feedback method select */
        if(1U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcPowCtrlLoc.stPowCtrlExt.ftVgDPllLpf * stPfcPowCtrlLoc.ftCosTheta * COEFF_KP_VOLT_FF + stPfcAdc.stVg.ftValLpf10kHz_C * (1.0f - COEFF_KP_VOLT_FF);
        }
        else
        {
            stPfcPowCtrlLoc.ftVgFF = stPfcAdc.stVg.ftValLpf10kHz_C;
        }
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA = 0.0f;                       ///< Limit to 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB = 0.0f;                       ///< Limit to 0.0f;
        stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC = (stPfcPowCtrlLoc.stPICurrC.ftOutp + PR1_Ian.ftOutp[0] + PR2_Ian.ftOutp[0] + PR3_Ian.ftOutp[0] + PR5_Ian.ftOutp[0] \
                                                        + PR7_Ian.ftOutp[0] + stPfcPowCtrlLoc.ftVgFF) * stPfcPowCtrlLoc.ftVbusRecpr;
        UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC, 0.5f, -0.5f);  ///< Phase C modulation limit
    }
#ifndef SST_1250kW
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN = stPfcPowCtrlLoc.stPWMdrive.ftN;
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN, 0.1f, -0.1f);      ///< Phase N modulation limit
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: PFC power control loop control- Three phase PWM drive ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcPowCtrl_Loop_PWM_3P_Isr(void)
{
    stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp = sqrtf(stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.stPWMdrive.ftD_axis + stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.stPWMdrive.ftQ_axis);
    if(SPWM == stPfcPowCtrlLoc.uiModPwm)  ///< SPWM
    {
        if (stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp > 0.5f)
        {
            stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (0.5f * stPfcPowCtrlLoc.stPWMdrive.ftD_axis ) / stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp;
            stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (0.5f * stPfcPowCtrlLoc.stPWMdrive.ftQ_axis ) / stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp;
            stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp = 0.5f;
        }
    }
    else  ///< SVPWM
    {
        if (stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp > 0.565f)
        {
            stPfcPowCtrlLoc.stPWMdrive.ftD_axis = (0.565f * stPfcPowCtrlLoc.stPWMdrive.ftD_axis) / stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp;
            stPfcPowCtrlLoc.stPWMdrive.ftQ_axis = (0.565f * stPfcPowCtrlLoc.stPWMdrive.ftQ_axis) / stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp;
            stPfcPowCtrlLoc.stPWMdrive.ftVectorAmp = 0.565f;
        }
    }
    ///< D/Q modulation to alfa/beta modulation
    if((OFFGRID_MODE == stComIf.uiModPfcRun) || (OPENLOOP_MODE == stComIf.uiModPfcRun))
    {
        stPfcPowCtrlLoc.stPWMdrive.ftAlfa = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
        stPfcPowCtrlLoc.stPWMdrive.ftBeta = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;
    }
    else
    {
        if(0U == stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiModVgFF)
        {
            stPfcPowCtrlLoc.stPWMdrive.ftAlfa = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta;
            stPfcPowCtrlLoc.stPWMdrive.ftBeta = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta;
        }
        else
        {
            stPfcPowCtrlLoc.stPWMdrive.ftAlfa = stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftCosTheta - stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftSinTheta \
                                                + (1.0f - COEFF_KP_VOLT_FF) * stPfcPowCtrlLoc.stVg.ftAlfa * stPfcPowCtrlLoc.ftVbusRecpr;
            stPfcPowCtrlLoc.stPWMdrive.ftBeta = stPfcPowCtrlLoc.stPWMdrive.ftQ_axis * stPfcPowCtrlLoc.ftCosTheta + stPfcPowCtrlLoc.stPWMdrive.ftD_axis * stPfcPowCtrlLoc.ftSinTheta \
                                                + (1.0f - COEFF_KP_VOLT_FF) * stPfcPowCtrlLoc.stVg.ftBeta * stPfcPowCtrlLoc.ftVbusRecpr;
        }
    }
    ///< alfa/beta modulation to abc modulation and add voltage dc component control
    stPfcPowCtrlLoc.stPWMdrive.ftA = stPfcPowCtrlLoc.stPWMdrive.ftAlfa + stPfcPowCtrlLoc.ftVaDcInhb;
    stPfcPowCtrlLoc.stPWMdrive.ftB = SQRT3_DIV_C2 * stPfcPowCtrlLoc.stPWMdrive.ftBeta - RECPR_CON_2 * stPfcPowCtrlLoc.stPWMdrive.ftAlfa + stPfcPowCtrlLoc.ftVbDcInhb;
    stPfcPowCtrlLoc.stPWMdrive.ftC = -stPfcPowCtrlLoc.stPWMdrive.ftA - stPfcPowCtrlLoc.stPWMdrive.ftB + stPfcPowCtrlLoc.ftVcDcInhb;

    if(SVPWM == stPfcPowCtrlLoc.uiModPwm)  ///< SVPWM
    {
        COMPARE(stPfcPowCtrlLoc.stPWMdrive.ftA, stPfcPowCtrlLoc.stPWMdrive.ftB, stPfcPowCtrlLoc.stPWMdrive.ftC, stPfcPowCtrlLoc.stPWMdrive.ftMax, stPfcPowCtrlLoc.stPWMdrive.ftMin);
        stPfcPowCtrlLoc.stPWMdrive.ftHarm = (stPfcPowCtrlLoc.stPWMdrive.ftMax + stPfcPowCtrlLoc.stPWMdrive.ftMin) * 0.5f;
    }
    else  ///< SPWM
    {
        stPfcPowCtrlLoc.stPWMdrive.ftHarm = 0.0f;
    }
    ///< Add zero sequence control and harmonic control
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA = (stPfcPowCtrlLoc.stPWMdrive.ftA + stPfcPowCtrlLoc.stPWMdrive.ftZero - stPfcPowCtrlLoc.stPWMdrive.ftHarm);
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB = (stPfcPowCtrlLoc.stPWMdrive.ftB + stPfcPowCtrlLoc.stPWMdrive.ftZero - stPfcPowCtrlLoc.stPWMdrive.ftHarm);
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC = (stPfcPowCtrlLoc.stPWMdrive.ftC + stPfcPowCtrlLoc.stPWMdrive.ftZero - stPfcPowCtrlLoc.stPWMdrive.ftHarm);
#ifndef SST_1250kW
    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN =  stPfcPowCtrlLoc.stPWMdrive.ftN;
#endif
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnA, 0.5f, -0.5f);   ///< Phase A modulation limit
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnB, 0.5f, -0.5f);   ///< Phase B modulation limit
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnC, 0.5f, -0.5f);   ///< Phase C modulation limit
#ifndef SST_1250kW
    UP_DOWN_LIMIT(stPfcPowCtrlLoc.stPowCtrlExt.ftOutpPwmModlnN, 0.1f, -0.1f);   ///< Phase N modulation limit
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: EEPROM parameter update
 * @param [in]   null
 * @param [out]
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcPowCtrl_PrmUpd_Eep(void)
{
    stPfcPowCtrlLoc.stPIVbus.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpVbusLoop;    ///< Bus voltage loop Kp update
    stPfcPowCtrlLoc.stPIVbus.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiVbusLoop;    ///< Bus voltage loop Ki update
    stPfcPowCtrlLoc.stPIVbus.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxVbusLoop;    ///< Bus voltage loop Max output update
    stPfcPowCtrlLoc.stPIVbus.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinVbusLoop;    ///< Bus voltage loop Max output update

    stPfcPowCtrlLoc.stPICurrD_P.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpIdPosLoop;    ///< Current loop Kp update
    stPfcPowCtrlLoc.stPICurrD_P.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxIdPosLoop;    ///< Current loop Max output update
    stPfcPowCtrlLoc.stPICurrD_P.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinIdPosLoop;    ///< Current loop Max output update

    stPfcPowCtrlLoc.stPICurrQ_P.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpIdPosLoop;    ///< Current loop Kp update
    stPfcPowCtrlLoc.stPICurrQ_P.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxIdPosLoop;    ///< Current loop Max output update
    stPfcPowCtrlLoc.stPICurrQ_P.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinIdPosLoop;    ///< Current loop Max output update

    stPfcPowCtrlLoc.stPICurrD_N.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpIdNegLoop;    ///< Current loop Kp update
    stPfcPowCtrlLoc.stPICurrD_N.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxIdNegLoop;    ///< Current loop Max output update
    stPfcPowCtrlLoc.stPICurrD_N.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinIdNegLoop;    ///< Current loop Max output update

    stPfcPowCtrlLoc.stPICurrQ_N.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpIdNegLoop;    ///< Current loop Kp update
    stPfcPowCtrlLoc.stPICurrQ_N.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxIdNegLoop;    ///< Current loop Max output update
    stPfcPowCtrlLoc.stPICurrQ_N.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinIdNegLoop;    ///< Current loop Max output update

    stPfcPowCtrlLoc.stPIVoltD_P.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpVdPosLoop;    ///< Voltage loop Kp update
    stPfcPowCtrlLoc.stPIVoltD_P.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiVdPosLoop;    ///< Voltage loop Ki update
    stPfcPowCtrlLoc.stPIVoltD_P.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxVdPosLoop;    ///< Voltage loop Max output update
    stPfcPowCtrlLoc.stPIVoltD_P.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinVdPosLoop;    ///< Voltage loop Max output update

    stPfcPowCtrlLoc.stPIVoltQ_P.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpVdPosLoop;    ///< Voltage loop Kp update
    stPfcPowCtrlLoc.stPIVoltQ_P.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiVdPosLoop;    ///< Voltage loop Ki update
    stPfcPowCtrlLoc.stPIVoltQ_P.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxVdPosLoop;    ///< Voltage loop Max output update
    stPfcPowCtrlLoc.stPIVoltQ_P.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinVdPosLoop;    ///< Voltage loop Max output update

    stPfcPowCtrlLoc.stPIVoltD_N.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpVdNegLoop;    ///< Voltage loop Kp update
    stPfcPowCtrlLoc.stPIVoltD_N.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiVdNegLoop;    ///< Voltage loop Ki update
    stPfcPowCtrlLoc.stPIVoltD_N.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxVdNegLoop;    ///< Voltage loop Max output update
    stPfcPowCtrlLoc.stPIVoltD_N.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinVdNegLoop;    ///< Voltage loop Max output update

    stPfcPowCtrlLoc.stPIVoltQ_N.ftKp = stComTbl.stPrmPfcPowCtrl.ftKpVdNegLoop;    ///< Voltage loop Kp update
    stPfcPowCtrlLoc.stPIVoltQ_N.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiVdNegLoop;    ///< Voltage loop Ki update
    stPfcPowCtrlLoc.stPIVoltQ_N.ftOutpMax = stComTbl.stPrmPfcPowCtrl.ftMaxVdNegLoop;    ///< Voltage loop Max output update
    stPfcPowCtrlLoc.stPIVoltQ_N.ftOutpMin = stComTbl.stPrmPfcPowCtrl.ftMinVdNegLoop;    ///< Voltage loop Max output update

    stPfcPowCtrlLoc.stVdRep.ftQz          = stComTbl.stPrmPfcPowCtrl.ftQzVacLoopRep;        ///< Vd repeat control loop Qz
    stPfcPowCtrlLoc.stVdRep.ftKrComp      = stComTbl.stPrmPfcPowCtrl.ftKrCompVacLoopRep;    ///< Vd repeat control loop compensation Kr
    stPfcPowCtrlLoc.stVdRep.uiNrPhaComp   = stComTbl.stPrmPfcPowCtrl.uiNrPhaCompVacLoopRep; ///< Vd repeat control loop phase compensation number
    stPfcPowCtrlLoc.stVdRep.ftOutpMax     = stComTbl.stPrmPfcPowCtrl.ftOutpMaxVacLoopRep;   ///< Vd repeat control loop MAX output

    stPfcPowCtrlLoc.stVqRep.ftQz          = stComTbl.stPrmPfcPowCtrl.ftQzVacLoopRep;        ///< Vq repeat control loop Qz
    stPfcPowCtrlLoc.stVqRep.ftKrComp      = stComTbl.stPrmPfcPowCtrl.ftKrCompVacLoopRep;    ///< Vq repeat control loop compensation Kr
    stPfcPowCtrlLoc.stVqRep.uiNrPhaComp   = stComTbl.stPrmPfcPowCtrl.uiNrPhaCompVacLoopRep; ///< Vq repeat control loop phase compensation number
    stPfcPowCtrlLoc.stVqRep.ftOutpMax     = stComTbl.stPrmPfcPowCtrl.ftOutpMaxVacLoopRep;   ///< Vq repeat control loop MAX output
}
/*********************************************End**********************************************/

static void NOTCH_INIT(NOTCH *v,float32 Ts)
{
    v->stCoeffTmp.ftWo_Ts = v->stLcdSet.ftWo * Ts;
    v->stCoeffTmp.ftM = (4.0f + 4.0f * v->stLcdSet.ftQ * v->stCoeffTmp.ftWo_Ts + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts);
    v->stCoeffTmp.ftA = (4.0f + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts) / v->stCoeffTmp.ftM;
    v->stCoeffTmp.ftB = (2.0f * v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts - 8.0f) / v->stCoeffTmp.ftM;
    v->stCoeffTmp.ftC = (4.0f - 4.0f * v->stLcdSet.ftQ * v->stCoeffTmp.ftWo_Ts + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts) / v->stCoeffTmp.ftM;

    v->stCoeff = v->stCoeffTmp;

    v->ftInp    = 0.0f;        ///< Initialize to 0.0f
    v->ftInp_1  = 0.0f;        ///< Initialize to 0.0f
    v->ftInp_2  = 0.0f;        ///< Initialize to 0.0f

    v->ftOutp   = 0.0f;        ///< Initialize to 0.0f
    v->ftOutp_1 = 0.0f;        ///< Initialize to 0.0f
    v->ftOutp_2 = 0.0f;        ///< Initialize to 0.0f
}

static void NOTCH_UPD(NOTCH *v,float32 Ts)
{
    ///< wo*Ts
    v->stCoeffTmp.ftWo_Ts = v->stLcdSet.ftWo * Ts;
    ///< (4+4*Q*wc*Ts+wo^2*Ts^2)
    v->stCoeffTmp.ftM = (4.0f + 4.0f * v->stLcdSet.ftQ * v->stCoeffTmp.ftWo_Ts + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts);
    ///< (4+wo^2*Ts^2)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    v->stCoeffTmp.ftA = (4.0f + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts) / v->stCoeffTmp.ftM;
    ///< (2*wo^2*Ts^2-8)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    v->stCoeffTmp.ftB = (2.0f * v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts - 8.0f) / v->stCoeffTmp.ftM;
    ///< ((4-4*Q*wo*Ts+wo^2*Ts^2))/(4+4*Q*wo*Ts+wo^2*Ts^2)
    v->stCoeffTmp.ftC = (4.0f - 4.0f * v->stLcdSet.ftQ * v->stCoeffTmp.ftWo_Ts + v->stCoeffTmp.ftWo_Ts * v->stCoeffTmp.ftWo_Ts) / v->stCoeffTmp.ftM;
}

static void NOTCH_CALC(NOTCH *v)
{
    ///< Output calculation
    v->ftOutp   = v->stCoeff.ftA *(v->ftInp + v->ftInp_2) + v->stCoeff.ftB * (v->ftInp_1 - v->ftOutp_1) - v->stCoeff.ftC * v->ftOutp_2;
    ///< Input record
    v->ftInp_2  = v->ftInp_1;
    v->ftInp_1  = v->ftInp;
    ///< Output record
    v->ftOutp_2 = v->ftOutp_1;
    v->ftOutp_1 = v->ftOutp;
}

static void DSOGI_INIT(DSOGI_TYPE *p, float32 Ts)
{
    float32 l_ftTemp = 0.0f;      ///< Initialize to 0.0f

    p->stCoeffTmp.ftOsg_x = 2.0f * p->stLcdSet.ftOsg_k * p->stLcdSet.ftWn * Ts;//x=2k*ftWn*Ts
    p->stCoeffTmp.ftOsg_y = p->stLcdSet.ftWn * Ts * p->stLcdSet.ftWn * Ts;//y=ftWn*Ts*ftWn*Ts
    l_ftTemp = 1.0f / (p->stCoeffTmp.ftOsg_x + p->stCoeffTmp.ftOsg_y + 4.0f);//
    p->stCoeffTmp.ftOsg_b0 = p->stCoeffTmp.ftOsg_x * l_ftTemp;
    p->stCoeffTmp.ftOsg_b2 = (-1.0f) * p->stCoeffTmp.ftOsg_b0;
    p->stCoeffTmp.ftOsg_a1 = 2.0f * (4.0f - p->stCoeffTmp.ftOsg_y) * l_ftTemp;
    p->stCoeffTmp.ftOsg_a2 = (p->stCoeffTmp.ftOsg_x - p->stCoeffTmp.ftOsg_y - 4.0f) * l_ftTemp;
    p->stCoeffTmp.ftOsg_qb0= p->stLcdSet.ftOsg_k * p->stCoeffTmp.ftOsg_y * l_ftTemp;
    p->stCoeffTmp.ftOsg_qb1= p->stCoeffTmp.ftOsg_qb0 * 2.0f;
    p->stCoeffTmp.ftOsg_qb2= p->stCoeffTmp.ftOsg_qb0;

    p->stCoeff = p->stCoeffTmp;

    p->ftAlpha_u[0]      = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_u[1]      = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_u[2]      = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_u[0]  = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_u[1]  = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_u[2]  = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_qu[0] = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_qu[1] = 0.0f;        ///< Initialize to 0.0f
    p->ftAlpha_osg_qu[2] = 0.0f;        ///< Initialize to 0.0f

    p->ftBeta_u[0]       = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_u[1]       = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_u[2]       = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_u[0]   = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_u[1]   = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_u[2]   = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_qu[0]  = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_qu[1]  = 0.0f;        ///< Initialize to 0.0f
    p->ftBeta_osg_qu[2]  = 0.0f;        ///< Initialize to 0.0f

    p->ftUalphap         = 0.0f;        ///< Initialize to 0.0f
    p->ftUalphan         = 0.0f;        ///< Initialize to 0.0f
    p->ftUbetap          = 0.0f;        ///< Initialize to 0.0f
    p->ftUbetan          = 0.0f;        ///< Initialize to 0.0f
}

static void DSOGI_UPD(DSOGI_TYPE *p, float32 Ts)
{
    float32 l_ftTemp = 0.0f;      ///< Initialize to 0.0f

    p->stCoeffTmp.ftOsg_x = 2.0f * p->stLcdSet.ftOsg_k * p->stLcdSet.ftWn * Ts;//x=2k*ftWn*Ts
    p->stCoeffTmp.ftOsg_y = p->stLcdSet.ftWn * Ts * p->stLcdSet.ftWn * Ts;//y=ftWn*Ts*ftWn*Ts
    l_ftTemp = 1.0f / (p->stCoeffTmp.ftOsg_x + p->stCoeffTmp.ftOsg_y + 4.0f);//
    p->stCoeffTmp.ftOsg_b0 = p->stCoeffTmp.ftOsg_x * l_ftTemp;
    p->stCoeffTmp.ftOsg_b2 = (-1.0f) * p->stCoeffTmp.ftOsg_b0;
    p->stCoeffTmp.ftOsg_a1 = 2.0f * (4.0f - p->stCoeffTmp.ftOsg_y) * l_ftTemp;
    p->stCoeffTmp.ftOsg_a2 = (p->stCoeffTmp.ftOsg_x - p->stCoeffTmp.ftOsg_y - 4.0f) * l_ftTemp;
    p->stCoeffTmp.ftOsg_qb0= p->stLcdSet.ftOsg_k * p->stCoeffTmp.ftOsg_y * l_ftTemp;
    p->stCoeffTmp.ftOsg_qb1= p->stCoeffTmp.ftOsg_qb0 * 2.0f;
    p->stCoeffTmp.ftOsg_qb2= p->stCoeffTmp.ftOsg_qb0;
}

static void DSOGI_CALC(DSOGI_TYPE *p)
{
    ///< alpha double sogi
    p->ftAlpha_osg_u[0] = (p->stCoeff.ftOsg_b0 * (p->ftAlpha_u[0]-p->ftAlpha_u[2])) + (p->stCoeff.ftOsg_a1 * p->ftAlpha_osg_u[1]) + (p->stCoeff.ftOsg_a2 * p->ftAlpha_osg_u[2]);
    p->ftAlpha_osg_u[2] = p->ftAlpha_osg_u[1];
    p->ftAlpha_osg_u[1] = p->ftAlpha_osg_u[0];
    p->ftAlpha_osg_qu[0] = (p->stCoeff.ftOsg_qb0 * p->ftAlpha_u[0]) + (p->stCoeff.ftOsg_qb1 * p->ftAlpha_u[1]) + (p->stCoeff.ftOsg_qb2 * p->ftAlpha_u[2])\
                       + (p->stCoeff.ftOsg_a1*p->ftAlpha_osg_qu[1]) + (p->stCoeff.ftOsg_a2*p->ftAlpha_osg_qu[2]);
    p->ftAlpha_osg_qu[2] = p->ftAlpha_osg_qu[1];
    p->ftAlpha_osg_qu[1] = p->ftAlpha_osg_qu[0];
    ///< input record
    p->ftAlpha_u[2] = p->ftAlpha_u[1];
    p->ftAlpha_u[1] = p->ftAlpha_u[0];
    ///< beta double sogi
    p->ftBeta_osg_u[0] = (p->stCoeff.ftOsg_b0 * (p->ftBeta_u[0]-p->ftBeta_u[2])) + (p->stCoeff.ftOsg_a1 * p->ftBeta_osg_u[1]) + (p->stCoeff.ftOsg_a2 * p->ftBeta_osg_u[2]);
    p->ftBeta_osg_u[2] = p->ftBeta_osg_u[1];
    p->ftBeta_osg_u[1] = p->ftBeta_osg_u[0];
    p->ftBeta_osg_qu[0] = (p->stCoeff.ftOsg_qb0 * p->ftBeta_u[0]) + (p->stCoeff.ftOsg_qb1 * p->ftBeta_u[1]) + (p->stCoeff.ftOsg_qb2 * p->ftBeta_u[2])\
                      + (p->stCoeff.ftOsg_a1 * p->ftBeta_osg_qu[1]) + (p->stCoeff.ftOsg_a2*p->ftBeta_osg_qu[2]);
    p->ftBeta_osg_qu[2] = p->ftBeta_osg_qu[1];
    p->ftBeta_osg_qu[1] = p->ftBeta_osg_qu[0];
    ///< input record
    p->ftBeta_u[2] = p->ftBeta_u[1];
    p->ftBeta_u[1] = p->ftBeta_u[0];
    ///< Symmetrical component
    p->ftUalphap = 0.5f * (p->ftAlpha_osg_u[0] - p->ftBeta_osg_qu[0]);
    p->ftUbetap  = 0.5f * (p->ftBeta_osg_u[0] + p->ftAlpha_osg_qu[0]);
    p->ftUalphan = 0.5f * (p->ftAlpha_osg_u[0] + p->ftBeta_osg_qu[0]);
    p->ftUbetan  = 0.5f * (p->ftBeta_osg_u[0] - p->ftAlpha_osg_qu[0]);

}

static void PR_INIT(PR *p,float32 Ts)
{
    p->stCoeffTmp.ftA0 = 4.0f * p->stLcdSet.ftKr * p->stLcdSet.ftWc * Ts;
    p->stCoeffTmp.ftA1 = 0.0f;
    p->stCoeffTmp.ftA2 = -p->stCoeffTmp.ftA0;
    p->stCoeffTmp.ftB0 = 1.0f / (4.0f + 4.0f * p->stLcdSet.ftWc * Ts + p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts);
    p->stCoeffTmp.ftB1 =  2.0f * p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts - 8.0f;
    p->stCoeffTmp.ftB2 = 4.0f - 4.0f * p->stLcdSet.ftWc * Ts + p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts;

    p->stCoeff = p->stCoeffTmp;

    p->ftInp[0]  = 0.0f;        ///< Initialize to 0.0f
    p->ftInp[1]  = 0.0f;        ///< Initialize to 0.0f
    p->ftInp[2]  = 0.0f;        ///< Initialize to 0.0f

    p->ftOutp[0] = 0.0f;        ///< Initialize to 0.0f
    p->ftOutp[1] = 0.0f;        ///< Initialize to 0.0f
    p->ftOutp[2] = 0.0f;        ///< Initialize to 0.0f

}

static void PR_CLC(PR *p)
{
    p->ftInp[0]  = 0.0f;        ///< Initialize to 0.0f
    p->ftInp[1]  = 0.0f;        ///< Initialize to 0.0f
    p->ftInp[2]  = 0.0f;        ///< Initialize to 0.0f

    p->ftOutp[0] = 0.0f;        ///< Initialize to 0.0f
    p->ftOutp[1] = 0.0f;        ///< Initialize to 0.0f
    p->ftOutp[2] = 0.0f;        ///< Initialize to 0.0f
}

static void PR_UPD(PR *p,float32 Ts)
{
    p->stCoeffTmp.ftA0 = 4.0f * p->stLcdSet.ftKr * p->stLcdSet.ftWc * Ts;  ///< PR parameter a0 update
    p->stCoeffTmp.ftA1 = 0.0f;
    p->stCoeffTmp.ftA2 = -p->stCoeffTmp.ftA0;                            ///< PR parameter a2 update
    p->stCoeffTmp.ftB0 = 1.0f / (4.0f + 4.0f * p->stLcdSet.ftWc * Ts + p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts);  ///< PR parameter b0 update
    p->stCoeffTmp.ftB1 =  2.0f * p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts - 8.0f;                                ///< PR parameter b1 update
    p->stCoeffTmp.ftB2 = 4.0f - 4.0f * p->stLcdSet.ftWc * Ts + p->stLcdSet.ftWo * p->stLcdSet.ftWo * Ts * Ts;           ///< PR parameter b2 update
}

static void PR_CALC(PR *p)
{
    ///< PR control output
    p->ftOutp[0] = (p->stCoeff.ftA0 * p->ftInp[0] + p->stCoeff.ftA1 * p->ftInp[1] + p->stCoeff.ftA2 * p->ftInp[2]\
                    - p->stCoeff.ftB1 * p->ftOutp[1] - p->stCoeff.ftB2 * p->ftOutp[2]) * p->stCoeff.ftB0;
    ///< Output limit
    if (p->ftOutp[0] > p->stLcdSet.ftMax)
    {
        p->ftOutp[0] =  p->stLcdSet.ftMax;
    }
    if (p->ftOutp[0] < p->stLcdSet.ftMin)
    {
        p->ftOutp[0] =  p->stLcdSet.ftMin;
    }
    ///< Output record
    p->ftOutp[2] = p->ftOutp[1];
    p->ftOutp[1] = p->ftOutp[0];
    ///< Input record
    p->ftInp[2]  = p->ftInp[1];
    p->ftInp[1]  = p->ftInp[0];
}

static void MPF_INIT(MPF_TYPE *p,float32 Ts)
{
    float32 l_ftCoeff1 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff2 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff3 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff4 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff5 = 0.0f;      ///< Initialize to 0.0f

    l_ftCoeff1 = p->stLcdSet.ftW * Ts;
    l_ftCoeff2 = l_ftCoeff1 * l_ftCoeff1;
    l_ftCoeff3 = 4.0f + (2.0f * p->stLcdSet.ftK * l_ftCoeff1) + l_ftCoeff2;
    l_ftCoeff4 = -4.0f + (2.0f * p->stLcdSet.ftK * l_ftCoeff1)- l_ftCoeff2;
    l_ftCoeff5 = 1.0f / l_ftCoeff3;

    p->stCoeffTmp.ftMPFCof1 = (8.0f - (2.0f * l_ftCoeff2)) * l_ftCoeff5;
    p->stCoeffTmp.ftMPFCof2 = l_ftCoeff4 * l_ftCoeff5;
    p->stCoeffTmp.ftMPFCof3 = 2.0f * p->stLcdSet.ftK * l_ftCoeff1 * l_ftCoeff5;
    p->stCoeffTmp.ftLPFCof1 = p->stLcdSet.ftK * l_ftCoeff2 * l_ftCoeff5;

    p->stCoeff = p->stCoeffTmp;

    p->ftInData[0]  = 0.0f;        ///< Initialize to 0.0f
    p->ftMpfTemp[0] = 0.0f;        ///< Initialize to 0.0f
    p->ftLpfTemp[0] = 0.0f;        ///< Initialize to 0.0f
    p->ftInData[1]  = 0.0f;        ///< Initialize to 0.0f
    p->ftMpfTemp[1] = 0.0f;        ///< Initialize to 0.0f
    p->ftLpfTemp[1] = 0.0f;        ///< Initialize to 0.0f

    p->ftMpf_In  = 0.0f;        ///< Initialize to 0.0f
    p->ftMpf_Out = 0.0f;        ///< Initialize to 0.0f
    p->ftLpf_Out = 0.0f;        ///< Initialize to 0.0f
}

static void MPF_UPD(MPF_TYPE *p,float32 Ts)
{
    float32 l_ftCoeff1 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff2 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff3 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff4 = 0.0f;      ///< Initialize to 0.0f
    float32 l_ftCoeff5 = 0.0f;      ///< Initialize to 0.0f

    l_ftCoeff1 = p->stLcdSet.ftW * Ts;
    l_ftCoeff2 = l_ftCoeff1 * l_ftCoeff1;
    l_ftCoeff3 = 4.0f + (2.0f * p->stLcdSet.ftK * l_ftCoeff1) + l_ftCoeff2;
    l_ftCoeff4 = -4.0f + (2.0f * p->stLcdSet.ftK * l_ftCoeff1)- l_ftCoeff2;
    l_ftCoeff5 = 1.0f / l_ftCoeff3;

    p->stCoeffTmp.ftMPFCof1 = (8.0f - (2.0f * l_ftCoeff2)) * l_ftCoeff5;
    p->stCoeffTmp.ftMPFCof2 = l_ftCoeff4 * l_ftCoeff5;
    p->stCoeffTmp.ftMPFCof3 = 2.0f * p->stLcdSet.ftK * l_ftCoeff1 * l_ftCoeff5;
    p->stCoeffTmp.ftLPFCof1 = p->stLcdSet.ftK * l_ftCoeff2 * l_ftCoeff5;
}

static void MPF_CALC(MPF_TYPE *p)
{
    ///< MPF output
    p->ftMpf_Out = (p->stCoeff.ftMPFCof1 * p->ftMpfTemp[0]) + (p->stCoeff.ftMPFCof2 * p->ftMpfTemp[1]) + (p->stCoeff.ftMPFCof3 * (p->ftMpf_In - p->ftInData[1]));
    ///< LPF output
    p->ftLpf_Out = (p->stCoeff.ftMPFCof1 * p->ftLpfTemp[0]) + (p->stCoeff.ftMPFCof2 * p->ftLpfTemp[1]) + (p->stCoeff.ftLPFCof1 * (p->ftMpf_In+(2.0f * p->ftInData[0]) + p->ftInData[1]));
    p->ftMpfTemp[1] = p->ftMpfTemp[0];
    p->ftMpfTemp[0] = p->ftMpf_Out;
    p->ftLpfTemp[1] = p->ftLpfTemp[0];
    p->ftLpfTemp[0] = p->ftLpf_Out;
    p->ftInData[1]  = p->ftInData[0];
    p->ftInData[0]  = p->ftMpf_In;
}

/**
* @brief      v_PfcPowCtrl_InitPfcRepPrm
* @details    PFC repeat control parameter initialization
* @param[in]  void
* @param[out] void
* @return
*/
static void v_PfcPowCtrl_InitPfcRepPrm(ST_PFC_REPEAT_PRM *stRepPfc)
{
    Uint16 i = 0U;
    static Uint16 sl_uiFlgInit = 0U;    ///< Initialize flag

//    if((FCN_DISABLE == stPfcPowCtrlLoc.stPrmExt.uiFlgPwmEn) || (1U == stPfcPowCtrlLoc.uiFlgCbcTz))    ///< PWM disabled or CBC TZ flag is set
    if(FCN_DISABLE == stPfcPowCtrl.uiFlgPwmEn)    ///< PWM disabled
    {
        if(0U == sl_uiFlgInit)
        {
            /* Initialize repeat parameter*/
            stRepPfc->uiPtr     = 0U;
            stRepPfc->uiPtrComp = 0U;
            stRepPfc->ftOutp    = 0.0f;
            stRepPfc->ftOutpLpf = 0.0f;

            for(i = 0U; i < MAX_REPEAT_NUM; i++)
            {
                stRepPfc->ftErrArr[i]  = 0.0f;
                stRepPfc->ftOutpArr[i] = 0.0f;
            }

            sl_uiFlgInit = 1U;    ///< Set initialize flag
        }
    }
    else    ///< PWM enabled or CBC TZ flag is cleared
    {
        sl_uiFlgInit = 0U;        ///< Clear initialize flag
    }
}

/**
* @brief      v_PfcPowCtrl_InitPfcRepLpfPrm
* @details    PFC repeat control lpf parameter initialization
* @param[in]  void
* @param[out] void
* @return
*/
static void v_PfcPowCtrl_InitPfcRepLpfPrm(ST_2ND_ORD_LPF_PRM *p)
{
    float32 l_ftCoeff1Tmp = 0.0f;
    float32 l_ftCoeff2Tmp = 0.0f;
    float32 l_ftCoeff3Tmp = 0.0f;
    float32 l_ftCoeff4Tmp = 0.0f;

    l_ftCoeff1Tmp = p->ftWc * p->ftTs;                                ///< ftWn*t
    l_ftCoeff2Tmp = 4.0f * 0.707f * p->ftWc * p->ftTs;                ///< 4*wc*ftWn*t
    l_ftCoeff3Tmp = l_ftCoeff1Tmp * l_ftCoeff1Tmp;                    ///< (ftWn*t)^2
    l_ftCoeff4Tmp = 1.0f / (4.0f + l_ftCoeff2Tmp + l_ftCoeff3Tmp);    ///< 1/(4+4*wc*ftWn*t+(ftWn*t)^2)

    p->ftCoeff[0] = (-2.0f * l_ftCoeff3Tmp + 8.0f) * l_ftCoeff4Tmp;
    p->ftCoeff[1] = (-4.0f + l_ftCoeff2Tmp - l_ftCoeff3Tmp) * l_ftCoeff4Tmp;
    p->ftCoeff[2] = l_ftCoeff3Tmp * l_ftCoeff4Tmp;
    p->ftCoeff[3] = 2.0f * (p->ftCoeff[2]);
    p->ftCoeff[4] = p->ftCoeff[2];

    p->ftInpPre[0]  = 0.0f;
    p->ftInpPre[1]  = 0.0f;
    p->ftOutpPre[0] = 0.0f;
    p->ftOutpPre[1] = 0.0f;
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Grid frequency parameter update task
* @Signal [in]  : ftTs
* @Signal [in]  : ftWn
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowCtrl_Frq_PrmUpd(float32 l_ftTs, float32 l_ftWn)
{
    ///< Voltag filter update
    BusVolt_Notch.stLcdSet.ftWo = l_ftWn * 2.0f;
    NOTCH_UPD(&BusVolt_Notch,l_ftTs);
    ///< 3P current loop PR2 control update
    PR2_d.stLcdSet.ftWo = l_ftWn * 2.0f;
    PR_UPD(&PR2_d,l_ftTs);
    ///< 3P current loop PR6 control update
    PR6_d.stLcdSet.ftWo = l_ftWn * 6.0f;
    PR_UPD(&PR6_d,l_ftTs);
    ///< 3P current loop PR12 control update
    PR12_d.stLcdSet.ftWo = l_ftWn * 12.0f;
    PR_UPD(&PR12_d,l_ftTs);

    ZeroVolt_PR1.stLcdSet.ftWo = l_ftWn;
    ZeroVolt_PR3.stLcdSet.ftWo = l_ftWn * 3.0f;
    PR_UPD(&ZeroVolt_PR1,l_ftTs);   ///< Zero voltage loop PR1 control update
    PR_UPD(&ZeroVolt_PR3,l_ftTs);   ///< Zero voltage loop PR3 control update

#ifndef SST_1250kW
    ZeroCurr_PR1.stLcdSet.ftWo = l_ftWn;
    ZeroCurr_PR3.stLcdSet.ftWo = l_ftWn * 3.0f;
    PR_UPD(&ZeroCurr_PR1,l_ftTs);   ///< Zero current loop PR1 control update
    PR_UPD(&ZeroCurr_PR3,l_ftTs);   ///< Zero current loop PR3 control update
#endif

    PR1_Ian.stLcdSet.ftWo = l_ftWn;
    PR2_Ian.stLcdSet.ftWo = l_ftWn * 2.0f;
    PR3_Ian.stLcdSet.ftWo = l_ftWn * 3.0f;
    PR5_Ian.stLcdSet.ftWo = l_ftWn * 5.0f;
    PR7_Ian.stLcdSet.ftWo = l_ftWn * 7.0f;
    PR_UPD(&PR1_Ian,l_ftTs);    ///< 1P current loop PR1 control update
    PR_UPD(&PR2_Ian,l_ftTs);    ///< 1P current loop PR2 control update
    PR_UPD(&PR3_Ian,l_ftTs);    ///< 1P current loop PR3 control update
    PR_UPD(&PR5_Ian,l_ftTs);    ///< 1P current loop PR5 control update
    PR_UPD(&PR7_Ian,l_ftTs);    ///< 1P current loop PR7 control update

    MidBusVolt_PR.stLcdSet.ftWo = l_ftWn;
    MidBusCurr_PR.stLcdSet.ftWo = l_ftWn;
    PR_UPD(&MidBusVolt_PR,l_ftTs);
    PR_UPD(&MidBusCurr_PR,l_ftTs);

    stVg_Decompose.stLcdSet.ftWn = l_ftWn;
    DSOGI_UPD(&stVg_Decompose,l_ftTs);

    stIg_Decompose.stLcdSet.ftWn = l_ftWn;
    DSOGI_UPD(&stIg_Decompose,l_ftTs);

    stVaMpf.stLcdSet.ftW = l_ftWn;
    MPF_UPD(&stVaMpf,l_ftTs);
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Grid frequency parameter copy task in ISR
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PfcPowCtrl_Frq_PrmCopy_Isr(void)
{
    stVg_Decompose.stCoeff = stVg_Decompose.stCoeffTmp;  ///< Voltage calculation parameter update
    stVaMpf.stCoeff = stVaMpf.stCoeffTmp;
    stVbMpf.stCoeff = stVaMpf.stCoeffTmp;
    stVcMpf.stCoeff = stVaMpf.stCoeffTmp;
    BusVolt_Notch.stCoeff = BusVolt_Notch.stCoeffTmp;

    if((CHG_ONGRID_MODE == stComIf.uiModPfcRun) || (BIDIR_ONGRID_MODE == stComIf.uiModPfcRun))
    {
        if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)
        {
            PR1_Ian.stCoeff = PR1_Ian.stCoeffTmp;     ///< Single phase current loop PR1 parameter update
            PR2_Ian.stCoeff = PR2_Ian.stCoeffTmp;     ///< Single phase current loop PR2 parameter update
            PR3_Ian.stCoeff = PR3_Ian.stCoeffTmp;     ///< Single phase current loop PR3 parameter update
            PR5_Ian.stCoeff = PR5_Ian.stCoeffTmp;     ///< Single phase current loop PR5 parameter update
            PR7_Ian.stCoeff = PR7_Ian.stCoeffTmp;     ///< Single phase current loop PR7 parameter update
            MidBusVolt_PR.stCoeff = MidBusVolt_PR.stCoeffTmp;
            MidBusCurr_PR.stCoeff = MidBusCurr_PR.stCoeffTmp;
        }
        else
        {
            PR2_d.stCoeff = PR2_d.stCoeffTmp;         ///< Three phase D/Q current loop PR2 parameter update
            PR2_q.stCoeff = PR2_d.stCoeffTmp;
            PR6_d.stCoeff = PR6_d.stCoeffTmp;         ///< Three phase D/Q current loop PR6 parameter update
            PR6_q.stCoeff = PR6_d.stCoeffTmp;
            PR12_d.stCoeff = PR12_d.stCoeffTmp;       ///< Three phase D/Q current loop PR12 parameter update
            PR12_q.stCoeff = PR12_d.stCoeffTmp;

#ifndef   SST_1250kW
            ZeroCurr_PR1.stCoeff = ZeroCurr_PR1.stCoeffTmp;  ///< Zero sequence current PR1 loop parameter update
            ZeroCurr_PR3.stCoeff = ZeroCurr_PR3.stCoeffTmp;  ///< Zero sequence current PR3 loop parameter update
#endif
            stIg_Decompose.stCoeff = stIg_Decompose.stCoeffTmp;  ///< Current calculation parameter update
        }
    }
    else
    {
        ZeroVolt_PR1.stCoeff = ZeroVolt_PR1.stCoeffTmp;      ///< Zero sequence voltage PR1 loop parameter update
        ZeroVolt_PR3.stCoeff = ZeroVolt_PR3.stCoeffTmp;      ///< Zero sequence voltage PR3 loop parameter update

        MidBusVolt_PR.stCoeff = MidBusVolt_PR.stCoeffTmp;
        MidBusCurr_PR.stCoeff = MidBusCurr_PR.stCoeffTmp;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power control 1ms task- control mode update
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowCtrl_CtrlMod_1ms(void)
{
    if(PFC_ST_MAC_CHK == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        switch (stComIf.uiModPfcRun)
        {
           case CHG_ONGRID_MODE:

               stPfcPowCtrlLoc.uiModLoop = PFC_DCBUS_CTRL;  ///< PFC bus voltage control mode
               stPfcPowCtrlLoc.uiModPwm  = stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeBal;

               ///< Charge mode current ki = 0.003f;
               stPfcPowCtrlLoc.stPICurrD_P.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiIdPosLoop * 0.375f;   ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrQ_P.ftKi = stPfcPowCtrlLoc.stPICurrD_P.ftKi;                  ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrD_N.ftKi = stPfcPowCtrlLoc.stPICurrD_P.ftKi;                  ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrQ_N.ftKi = stPfcPowCtrlLoc.stPICurrD_P.ftKi;                  ///< Current loop Ki update

           break;

           case BIDIR_ONGRID_MODE:
               ///< Bidirectional mode current ki = 0.008f;
               stPfcPowCtrlLoc.stPICurrD_P.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiIdPosLoop;    ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrQ_P.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiIdPosLoop;    ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrD_N.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiIdNegLoop;    ///< Current loop Ki update
               stPfcPowCtrlLoc.stPICurrQ_N.ftKi = stComTbl.stPrmPfcPowCtrl.ftKiIdNegLoop;    ///< Current loop Ki update

               if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)  ///< Select current loop mode
               {
                   stPfcPowCtrlLoc.uiModLoop = PFC_1PCURR_CTRL;  ///< Single phase current loop
                   stPfcPowCtrlLoc.uiModPwm = stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeImBal;
               }
               else
               {
                   if(PFC_PWR_ARM_CTRL_MODE == stCom.unModPfcPow.bit.uiModPowCtrl)
                   {
                       stPfcPowCtrlLoc.uiModLoop = PFC_3PCURRABC_CTRL;  ///< Three phase current imbalance control
                       stPfcPowCtrlLoc.uiModPwm = stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeImBal;
                   }
                   else
                   {
                       stPfcPowCtrlLoc.uiModLoop = PFC_3PCURRDQ_CTRL;  ///< Three phase current balance control
                       stPfcPowCtrlLoc.uiModPwm = stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeBal;
                   }
               }

           break;

           case OFFGRID_MODE:

               stPfcPowCtrlLoc.uiModLoop = PFC_V2L_CTRL;
               stPfcPowCtrlLoc.uiModPwm = stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.bit.uiPwmModeImBal;

           break;

           case OPENLOOP_MODE:

               stPfcPowCtrlLoc.uiModLoop = PFC_DBG_CTRL;

           break;

           default:
               ///< Do nothing
           break;
        }
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power control 1ms task- Control parameter clear after PFC stop-running 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowCtrl_PrmClr_1ms(void)
{
    static Uint16 l_uiFlgFirstIn = 0U;        ///< Initialize to 0U

    if(FCN_DISABLE == stPfcPowCtrl.uiFlgPwmEn)
    {
        if(0U == l_uiFlgFirstIn)
        {
            v_PfcPowCtrl_InitPfcRepLpfPrm(&stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd);
            stPfcPowCtrlLoc.stVqRep.stLpf2ndOrd = stPfcPowCtrlLoc.stVdRep.stLpf2ndOrd;
            vFcn_InitPIPrm(&stMidBusLoop);
            vFcn_InitPIPrm(&stMidCurrLoop);

            PR_CLC(&PR12_d);          ///< clear D/Q current loop PR12 controller
            PR_CLC(&PR12_q);
            PR_CLC(&PR6_d);           ///< clear D/Q current loop PR6 controller
            PR_CLC(&PR6_q);
            PR_CLC(&PR2_d);           ///< clear D/Q current loop PR2 controller
            PR_CLC(&PR2_q);

            PR_CLC(&ZeroVolt_PR1);    ///< clear zero sequence voltage loop PR1 controller
            PR_CLC(&ZeroVolt_PR3);    ///< clear zero sequence voltage loop PR3 controller
#ifndef SST_1250kW
            PR_CLC(&ZeroCurr_PR1);    ///< clear zero sequence current loop PR1 controller
            PR_CLC(&ZeroCurr_PR3);    ///< clear zero sequence current loop PR3 controller
#endif

            PR_CLC(&MidBusVolt_PR);
            PR_CLC(&MidBusCurr_PR);
            PR_CLC(&PR1_Ian);         ///< clear single phase current loop PR1 controller
            PR_CLC(&PR2_Ian);         ///< clear single phase current loop PR2 controller
            PR_CLC(&PR3_Ian);         ///< clear single phase current loop PR3 controller
            PR_CLC(&PR5_Ian);         ///< clear single phase current loop PR5 controller
            PR_CLC(&PR7_Ian);         ///< clear single phase current loop PR7 controller

            l_uiFlgFirstIn = 1U;
        }
    }
    else
    {
        l_uiFlgFirstIn = 0U;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power control 1ms task- Data calculation 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowCtrl_DataCalc_1ms(void)
{
    ///< Bus voltage reciprocal
    if(stPfcPowCtrlLoc.ftVbusLpf > 25.0f)
    {
        stPfcPowCtrlLoc.ftVbusRecpr = 1.0f / stPfcPowCtrlLoc.ftVbusLpf;
    }
    else
    {
        stPfcPowCtrlLoc.ftVbusRecpr = 0.003f;          ///< Initialize to 0.003f
    }
    ///< Voltage DC component calculation
    if(1U == stComTbl.stPrmPwrCtrl.uiEnaVoltDcCtrl)
    {
        stPfcPowCtrlLoc.ftVaDcInhb = stPfcGridCtrl.stDstbc.ftVaDcInhb     * (-0.001f) * stPfcPowCtrlLoc.ftVbusRecpr;
        if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)  ///< Positive sequence
        {
            stPfcPowCtrlLoc.ftVbDcInhb = stPfcGridCtrl.stDstbc.ftVbDcInhb * (-0.001f) * stPfcPowCtrlLoc.ftVbusRecpr;
            stPfcPowCtrlLoc.ftVcDcInhb = stPfcGridCtrl.stDstbc.ftVcDcInhb * (-0.001f) * stPfcPowCtrlLoc.ftVbusRecpr;
        }
        else  ///< Negative sequence
        {
            stPfcPowCtrlLoc.ftVbDcInhb = stPfcGridCtrl.stDstbc.ftVcDcInhb * (-0.001f) * stPfcPowCtrlLoc.ftVbusRecpr;
            stPfcPowCtrlLoc.ftVcDcInhb = stPfcGridCtrl.stDstbc.ftVbDcInhb * (-0.001f) * stPfcPowCtrlLoc.ftVbusRecpr;
        }
    }
    else
    {
        stPfcPowCtrlLoc.ftVaDcInhb = 0.0f;
        stPfcPowCtrlLoc.ftVbDcInhb = 0.0f;
        stPfcPowCtrlLoc.ftVcDcInhb = 0.0f;
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power control 1ms task- V2L CBC 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowCtrl_V2LCBC_1ms(void)
{
    Uint16 l_uiFlgTz1 = 0U;    ///< TZ1 flag
    Uint16 l_uiFlgTz2 = 0U;    ///< TZ2 flag
    Uint16 l_uiFlgTz3 = 0U;    ///< TZ3 flag
    Uint16 l_uiFlgTz4 = 0U;    ///< TZ4 flag
    Uint16 l_uiFlgTz5 = 0U;    ///< TZ5 flag

    if(OFFGRID_MODE == stComIf.uiModPfcRun)
    {
        /* EPWM CBC judgment */
        if(FCN_ENABLE == stPfcPowCtrl.uiFlgPwmEn)    ///< PWM enabled
        {
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

                stPfcPowCtrlLoc.uiCntrCbcTz = 0U;        ///< Clear CBC TZ counter
                stPfcPowCtrlLoc.uiFlgCbcTz  = 1U;        ///< Set CBC TZ flag
            }
            else if(1U == stPfcPowCtrlLoc.uiFlgCbcTz)
            {
                stPfcPowCtrlLoc.uiCntrCbcTz++;
                if(stPfcPowCtrlLoc.uiCntrCbcTz > 50U)
                {
                    stPfcPowCtrlLoc.uiFlgCbcTz = 0U;    ///< Clear CBC TZ flag
                }
            }
            else
            {
                ///< No code
            }
        }
        else
        {
            stPfcPowCtrlLoc.uiFlgCbcTz = 0U;    ///< Clear CBC TZ flag
        }

        /* PFC Vd repeat control parameter initialization */
        v_PfcPowCtrl_InitPfcRepPrm(&stPfcPowCtrlLoc.stVdRep);
        /* PFC Vq repeat control parameter initialization */
        v_PfcPowCtrl_InitPfcRepPrm(&stPfcPowCtrlLoc.stVqRep);
    }
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : PFC power control Isr task- Cell Bus voltage balanced control Isr task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PfcPowCtrl_Loop_CellBusVoltBal_1ms(void)
{
    float32 l_ftPowA = 0.0f;
    float32 l_ftPowB = 0.0f;
    float32 l_ftPowC = 0.0f;
    Uint16  i = 0;
    if(((PFC_3PCURRDQ_CTRL == stPfcPowCtrlLoc.uiModLoop)||(PFC_DBG_CTRL == stPfcPowCtrlLoc.uiModLoop))&&(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)&&(FCN_ENABLE == stPfcPowCtrl.uiFlgPwmEn)&&(1U == stComTbl.stPrmToFpga.uiHalfBusBlanceEn))
    {
        l_ftPowA = stPfcAdc.stIg.ftValLpf10kHz_A * stPfcAdc.stVg.ftValLpf10kHz_A;
        l_ftPowB = stPfcAdc.stIg.ftValLpf10kHz_B * stPfcAdc.stVg.ftValLpf10kHz_B;
        l_ftPowC = stPfcAdc.stIg.ftValLpf10kHz_C * stPfcAdc.stVg.ftValLpf10kHz_C;
//        l_ftPowA = stPfcAdc.stIg.ftValLpf10kHz_A * stPfcPowCtrl.ftVaCmn;
//        l_ftPowB = stPfcAdc.stIg.ftValLpf10kHz_B * stPfcPowCtrl.ftVbCmn;
//        l_ftPowC = stPfcAdc.stIg.ftValLpf10kHz_C * stPfcPowCtrl.ftVcCmn;

        for(i = 0;i < NUM_PHA_POW_CELL;i++)
        {
            /* Phase A cell Bus voltage PI calculation */
            stPfcPowCtrlLoc.stPICellCtrlA[i].ftInp = stPfcAdc.ftVbusPosCell[0][i] - stPfcAdc.ftVbusNegCell[0][i];
            POS_PI_CTRL(stPfcPowCtrlLoc.stPICellCtrlA[i]);
            /* Phase B cell Bus voltage PI calculation */
            stPfcPowCtrlLoc.stPICellCtrlB[i].ftInp = stPfcAdc.ftVbusPosCell[1][i] - stPfcAdc.ftVbusNegCell[1][i];
            POS_PI_CTRL(stPfcPowCtrlLoc.stPICellCtrlB[i]);
            /* Phase C cell Bus voltage PI calculation */
            stPfcPowCtrlLoc.stPICellCtrlC[i].ftInp = stPfcAdc.ftVbusPosCell[2][i] - stPfcAdc.ftVbusNegCell[2][i];
            POS_PI_CTRL(stPfcPowCtrlLoc.stPICellCtrlC[i]);

            /* Phase A cell voltage balanced output */
            if(l_ftPowA > 0.0f)
            {
                stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalA[i] = stPfcPowCtrlLoc.stPICellCtrlA[i].ftOutp;
            }
            else
            {
                stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalA[i] = -stPfcPowCtrlLoc.stPICellCtrlA[i].ftOutp;
            }
            if(GRID_POS_SEQ == stPfcDataCalc.stCtrlParm.uiFlgPhaSeq)
            {
                /* Phase B cell voltage balanced output */
                if(l_ftPowB > 0.0f)
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i] = stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutp;
                }
                else
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i] = -stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutp;
                }

                /* Phase C cell voltage balanced output */
                if(l_ftPowC > 0.0f)
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i] = stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutp;
                }
                else
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i] = -stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutp;
                }
            }
            else
            {
                /* Phase B cell voltage balanced output */
                if(l_ftPowC > 0.0f)
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i] = stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutp;
                }
                else
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i] = -stPfcPowCtrlLoc.stPICellCtrlB[i].ftOutp;
                }

                /* Phase C cell voltage balanced output */
                if(l_ftPowB > 0.0f)
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i] = stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutp;
                }
                else
                {
                    stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i] = -stPfcPowCtrlLoc.stPICellCtrlC[i].ftOutp;
                }
            }
        }
        for(i = 0;i < NUM_PHA_POW_CELL;i++)
        {
            stPfcPowCtrl.ftOutpCellBusVoltBalA[i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalA[i];
            stPfcPowCtrl.ftOutpCellBusVoltBalB[i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalB[i];
            stPfcPowCtrl.ftOutpCellBusVoltBalC[i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellBusVoltBalC[i];
        }
    }
    else
    {

    }


}

static void  v_PfcPowCtrl_Loop_CellSOCBal_1ms(void)
{
    float32 l_ftIinD = 0.0f;
    float32 l_ftIinQ = 0.0f;
    float32 l_ftIinSqrtDQ = 0.0f;
    float32 l_ftIinAlfa = 0.0f;
    float32 l_ftIinBeta = 0.0f;
    float32 l_ftIinCosTheta[3] = {0.0,0.0,0.0};

    Uint16 i = 0;

    if((PFC_3PCURRDQ_CTRL == stPfcPowCtrlLoc.uiModLoop)&&(PHASE_FULL_RUN_MODE == stComIf.uiModPfcPhaLoss)&&(FCN_ENABLE == stPfcPowCtrl.uiFlgPwmEn)&&(1U == stComTbl.stPrmToFpga.uiSOCBlanceEn))
    {
        l_ftIinSqrtDQ = sqrt(stPfcPowCtrlLoc.ftId_Lpf2 * stPfcPowCtrlLoc.ftId_Lpf2 + stPfcPowCtrlLoc.ftIq_Lpf2 * stPfcPowCtrlLoc.ftIq_Lpf2);
        if(l_ftIinSqrtDQ > 1)
        {
            l_ftIinD = stPfcPowCtrlLoc.ftId_Lpf2 / l_ftIinSqrtDQ;
            l_ftIinQ = stPfcPowCtrlLoc.ftIq_Lpf2 / l_ftIinSqrtDQ;
        }
        else if(l_ftIinSqrtDQ < 0.9)
        {
            l_ftIinD = stPfcPowCtrlLoc.ftId_Lpf2;
            l_ftIinQ = stPfcPowCtrlLoc.ftIq_Lpf2;
        }

        l_ftIinAlfa = l_ftIinD * stPfcPowCtrlLoc.ftCosTheta - l_ftIinQ * stPfcPowCtrlLoc.ftSinTheta;
        l_ftIinBeta = l_ftIinQ * stPfcPowCtrlLoc.ftCosTheta + l_ftIinD * stPfcPowCtrlLoc.ftSinTheta;

        l_ftIinCosTheta[0] = l_ftIinAlfa;
        l_ftIinCosTheta[1] = l_ftIinBeta * SQRT3_DIV_C2 - l_ftIinAlfa * RECPR_CON_2;
        l_ftIinCosTheta[2] = - l_ftIinCosTheta[0] - l_ftIinCosTheta[1];

        for(i = 0;i < NUM_PHA_POW_CELL;i++)
        {
            /* SOC PI calculation */
            stPfcPowCtrlLoc.stPISOCCtrl[i].ftInp = 0;//average - cellSOC;
            POS_PI_CTRL(stPfcPowCtrlLoc.stPISOCCtrl[i]);

            stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[0][i] = stPfcPowCtrlLoc.stPISOCCtrl[i].ftOutp * l_ftIinCosTheta[0];
            stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[1][i] = stPfcPowCtrlLoc.stPISOCCtrl[i].ftOutp * l_ftIinCosTheta[1];
            stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[2][i] = stPfcPowCtrlLoc.stPISOCCtrl[i].ftOutp * l_ftIinCosTheta[2];

            stPfcPowCtrl.ftOutpCellSOCBal[0][i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[0][i];
            stPfcPowCtrl.ftOutpCellSOCBal[1][i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[1][i];
            stPfcPowCtrl.ftOutpCellSOCBal[2][i] = stPfcPowCtrlLoc.stPowCtrlExt.ftOutpCellSOCBal[2][i];
        }
    }

}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
