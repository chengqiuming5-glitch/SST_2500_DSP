//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcStMac.c
 * @brief
 * The source file of PFC state machine module.
 *
 * Module      :                           \n
 * PfcStMac
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_PfcStMac_Init()                       \n
 * v_PfcStMac_1ms()                        \n
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
 * 2024/03/19
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
 * <tr><td>2024/03/19  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcStMac.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_PFC_ST_MAC stPfcStMac;    // PFC state machine global struct

#if (1U == PFC_ST_MAC_FLG_DBG)
ST_PFC_ST_MAC stPfcStMacDbg;    // PFC state machine debug global struct
#endif

static ST_PFC_ST_MAC_LOC stPfcStMacLoc;    // PFC state machine local struct

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC state machine module initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcStMac_Init(void)
{
    stPfcStMacLoc.uiCntrBusChk           = 0U;
    stPfcStMacLoc.uiCntrPfcRly           = 0U;
    stPfcStMacLoc.uiCntrBusRdy           = 0U;
    stPfcStMacLoc.uiFlgModChg            = FCN_DISABLE;    ///< Initialize to disable status
    stPfcStMacLoc.uiCntrModChg           = 0U;
    stPfcStMacLoc.uiCmdRly               = PFC_RLY_OFF;    ///< Initial PFC control relay command
    stPfcStMacLoc.ftBusVoltRdyToRun      = 1000.0f;

    stPfcStMacLoc.stExt.unPFCSts.all         = 0U;                ///< Initial PFC status
    stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_STB;    ///< Initial PFC state machine to standby
    stPfcStMacLoc.stExt.unGPIOCmd.all        = 0U;                ///< Initial PFC control GPIO command
    stPfcStMacLoc.stExt.unCtrlCmd.all        = 0U;                ///< Initial PFC control command
    stPfcStMacLoc.stExt.unStsToArm.all       = 0U;                ///< Initial PFC status to ARM
    stPfcStMacLoc.stExt.ftVoltPreChrgLmt     = 0.0f;              ///< Initial Bus pre-charge voltage limit

    /* Output parameter */
#if (1U == PFC_ST_MAC_FLG_DBG)
    stPfcStMacDbg.unPFCSts.all           = stPfcStMacLoc.stExt.unPFCSts.all;
    stPfcStMacDbg.unCtrlCmd.all          = stPfcStMacLoc.stExt.unCtrlCmd.all;
    stPfcStMacDbg.unGPIOCmd.all          = stPfcStMacLoc.stExt.unGPIOCmd.all;
    stPfcStMacDbg.unStsToArm.all         = stPfcStMacLoc.stExt.unStsToArm.all;
    stPfcStMacDbg.ftVoltPreChrgLmt       = stPfcStMacLoc.stExt.ftVoltPreChrgLmt;

    stPfcStMac.unPFCSts.all              = stPfcStMacDbg.unPFCSts.all;
    stPfcStMac.unCtrlCmd.all             = stPfcStMacDbg.unCtrlCmd.all;
    stPfcStMac.unGPIOCmd.all             = stPfcStMacDbg.unGPIOCmd.all;
    stPfcStMac.unStsToArm.all            = stPfcStMacDbg.unStsToArm.all;
    stPfcStMac.ftVoltPreChrgLmt          = stPfcStMacDbg.ftVoltPreChrgLmt;
#else
    stPfcStMac.unPFCSts.all              = stPfcStMacLoc.stExt.unPFCSts.all;
    stPfcStMac.unCtrlCmd.all             = stPfcStMacLoc.stExt.unCtrlCmd.all;
    stPfcStMac.unGPIOCmd.all             = stPfcStMacLoc.stExt.unGPIOCmd.all;
    stPfcStMac.unStsToArm.all            = stPfcStMacLoc.stExt.unStsToArm.all;
    stPfcStMac.ftVoltPreChrgLmt          = stPfcStMacLoc.stExt.ftVoltPreChrgLmt;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PfcStMac_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: PFC state machine module 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PfcStMac_1ms(void)
{
    v_PfcStMac_ST_1ms();
    v_PfcStMac_Outp_1ms();
//stPrmDisp.siPrm4 = stComIf.uiCmdPfcRun;
//stPrmDisp.siPrm1 = stPfcStMac.unPFCSts.bit.uiMacSt;
//stPrmDisp.siPrm2 = stPfcStMac.unPFCSts.bit.uiFlgPreChrgOk;
//stPrmDisp.siPrm3 = stPfcStMac.unPFCSts.bit.uiFlgBusVoltOk;

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_PfcStMac_1ms() is running****\r\n");
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC state machine 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_1ms(void)
{
    switch(stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt)
    {
        case PFC_ST_MAC_FLT:
            v_PfcStMac_ST_Flt_1ms();    ///< PFC Fault status
            break;

        case PFC_ST_MAC_STB:
            v_PfcStMac_ST_Stb_1ms();    ///< PFC Statndby status
            break;

        case PFC_ST_MAC_CHK:
            v_PfcStMac_ST_Chk_1ms();    ///< PFC Check status
            break;

        case PFC_ST_MAC_PWMEN:
            v_PfcStMac_ST_PwmEn_1ms();    ///< PFC PWM Enable status
            break;

        case PFC_ST_MAC_NORMRUN:
            v_PfcStMac_ST_NormRun_1ms();    ///< PFC normal run status
            break;

        default:
            ///< No code
            break;
    }
    /* Output parameter */
#if (1U == PFC_ST_MAC_FLG_DBG)
    stPfcStMac.unPFCSts.all              = stPfcStMacDbg.unPFCSts.all;
    stPfcStMac.unCtrlCmd.all             = stPfcStMacDbg.unCtrlCmd.all;
#else
    stPfcStMac.unPFCSts.all              = stPfcStMacLoc.stExt.unPFCSts.all;
    stPfcStMac.unCtrlCmd.all             = stPfcStMacLoc.stExt.unCtrlCmd.all;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state fault state 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_Flt_1ms(void)
{
    /* Condition (transition from state "PFC_ST_MAC_FLT" to state "PFC_ST_MAC_STB" with priority 1st)  */
    if(PFC_FLT_IS_CLR)    ///< No fault
    {
        /* Switch to state "PFC_ST_MAC_STB"  */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFault = 0U;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_STB;
    }
    /* Static (state "PFC_ST_MAC_FLT")  */
    else
    {
        stPfcStMacLoc.uiCmdRly = PFC_RLY_OFF;       ///< AC pre-charger relay command off
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFault    = 1U;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk = FCN_DISABLE;
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun  = FCN_DISABLE;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiAuxRly  = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state standby state 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_Stb_1ms(void)
{
    /* Condition (transition from state "PFC_ST_MAC_STB" to state "PFC_ST_MAC_FLT" with priority 1st)  */
    if(PFC_FLT_IS_SET)
    {
        /* Switch to state "PFC_ST_MAC_FLT" */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_FLT;    ///< Switch to state "PFC_ST_MAC_FLT"
    }
    /* Condition (transition from state "PFC_ST_MAC_STB" to state "PFC_ST_MAC_CHK"  with priority 2nd) */
    else if(START_CMD == stComIf.uiCmdPfcRun)
    {
        /* Switch to state "PFC_ST_MAC_CHK" */
        stPfcStMacLoc.uiCntrBusChk = 0U;
        stPfcStMacLoc.uiCntrPfcRly = 0U;
        stPfcStMacLoc.uiCntrModChg = 0U;
        stPfcStMacLoc.uiFlgModChg  = FCN_DISABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 0U;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgBusVoltOk = 0U;
        if(PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss)
        {
            stPfcStMacLoc.uiCmdRly = PFC_RLY_N_LINE_ON;
        }

        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_CHK;
    }
    /* Static (state "PFC_ST_MAC_STB") */
    else
    {
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk = FCN_DISABLE;
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun  = FCN_DISABLE;
        if(FCN_DISABLE == stPfcStMacLoc.uiFlgModChg)    ///< Run mode no change
        {
            stPfcStMacLoc.uiCmdRly = PFC_RLY_OFF;       ///< Initial AC pre-charger relay command
            stPfcStMacLoc.stExt.unGPIOCmd.bit.uiAuxRly = 0U;
        }
        else    ///< Run mode change
        {
            stPfcStMacLoc.uiCntrModChg++;
            if(stPfcStMacLoc.uiCntrModChg > 10000U)    ///< More than 10s
            {
                stPfcStMacLoc.uiFlgModChg = FCN_DISABLE;
            }
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state check state 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_Chk_1ms(void)
{
    /* Condition (transition from state "PFC_ST_MAC_CHK" to state "PFC_ST_MAC_FLT" with priority 1st)  */
    if(PFC_FLT_IS_SET)
    {
        /* Switch to state "PFC_ST_MAC_FLT" */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_FLT;    ///< Switch to state "PFC_ST_MAC_FLT"
    }
    /* Condition (transition from state "PFC_ST_MAC_CHK" to state "PFC_ST_MAC_STB" with priority 2nd) */
    else if(STOP_CMD == stComIf.uiCmdPfcRun)
    {
        /* Switch to state "PFC_ST_MAC_STB"  */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_STB;    ///< Switch to state "PFC_ST_MAC_STB"
    }
    /* Condition (If stComIf.uiModRun is not equal to stCom.uiModRunReq with priority 3rd) */
    else if(stComIf.uiModRun != stCom.uiModRunReq)
    {
        stPfcStMacLoc.uiCntrPfcRly = 0U;
        stPfcStMacLoc.uiFlgModChg  = FCN_ENABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 0U;
    }
    /* Condition (transition from state "PFC_ST_MAC_CHK" to state "PFC_ST_MAC_PWMEN"  with priority 4th) */
    else if(1U == stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk)
    {
        /* Switch to state "PFC_ST_MAC_PWMEN" */
        stPfcStMacLoc.uiCntrBusRdy = 0U;

        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_PWMEN;
    }
    /* Static (state "PFC_ST_MAC_CHK") */
    else
    {
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk = FCN_DISABLE;
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun  = FCN_DISABLE;
        if(1U == v_PfcStMac_ST_Chk_GridCdn_1ms())
        {
            if(1U == stOnOffGridSwt.uiFlgSwt)
            {
                stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 1U;
            }
            else
            {
                v_PfcStMac_ST_Chk_BusChk_1ms();
            }
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state check state grid condition judgment 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       l_uiRetTmp
 * @see          SWDD-xxxx
 */
static Uint16 v_PfcStMac_ST_Chk_GridCdn_1ms(void)
{
   Uint16 l_uiRetTmp = 0U;    ///< Initialize to 0U

   switch(stComIf.uiModPfcRun)
   {
       case CHG_ONGRID_MODE:
       case BIDIR_ONGRID_MODE:
           if((1U == stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk) && \
              (1U == stPfcDataCalc.stCtrlParm.uiFlgPllOk))
           {
               l_uiRetTmp = 1U;
           }
           break;

       case OFFGRID_MODE:
       case OPENLOOP_MODE:
           if((0U == stCom.unCmdFct.bit.uiEnFctPwm) && (ON_OFF_GRID_IS_NORMAL))
           {
               if(stPfcDataCalc.stMeasParm.ftVgMaxRms < 20.0f)    ///< No grid detect
               {
                   l_uiRetTmp = 1U;
               }
           }
           else
           {
               l_uiRetTmp = 1U;
           }
           if(stComTbl.stPrmToFpga.uiHandControl == 1U)
           {
               l_uiRetTmp = 1U;
           }
           break;

       default:
           ///< No code
           break;
   }

   return l_uiRetTmp;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Sub Unit function: PFC state machine-Chk-State - Bus voltage check 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_Chk_BusChk_1ms(void)
{
    switch(stComIf.uiModPfcRun)
    {
        case CHG_ONGRID_MODE:
#if(1U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * PRE_CHRG_AMP_COEFF;    ///< Charge mode: Take into account rectification coefficient
#elif(2U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComTbl.stPrmPowLim.ftCoeffBusPreChg1P;
#elif(3U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComIf.ftCoeffBusPreChrg;
#endif
            break;

        case BIDIR_ONGRID_MODE:
        case OFFGRID_MODE:
#if(1U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2;    ///< Bi-direction or off-grid mode: must more than grid voltage amplitude
#elif(2U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * stComTbl.stPrmPowLim.ftCoeffBusPreChg1P;
#elif(3U == GRID_PHASE_NUMBER)
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = stPfcDataCalc.stMeasParm.ftVgMaxRms * CON_SQRT_2;
#endif
            break;

        case OPENLOOP_MODE:
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = -10.0f;
            break;

        default:
            stPfcStMacLoc.stExt.ftVoltPreChrgLmt = 0.0f;
            break;
    }

    if(0U == stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgBusVoltOk)
    {
//        if(stPfcDataCalc.stMeasParm.ftVbusLPF > stPfcStMacLoc.stExt.ftVoltPreChrgLmt)
        if((stD2dAdc.ftVoltCellBusSum[0] > stPfcStMacLoc.stExt.ftVoltPreChrgLmt)&&(stD2dAdc.ftVoltCellBusSum[1] > stPfcStMacLoc.stExt.ftVoltPreChrgLmt)&&(stD2dAdc.ftVoltCellBusSum[2] > stPfcStMacLoc.stExt.ftVoltPreChrgLmt))
        {
            stPfcStMacLoc.uiCntrBusChk++;
            if(stPfcStMacLoc.uiCntrBusChk > 50U)    ///< Bus voltage maintain 50ms
            {
                stPfcStMacLoc.uiCntrBusChk = 0U;
                stPfcStMacLoc.uiCmdRly     = PFC_RLY_ON;
                stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgBusVoltOk = 1U;
            }
        }
        else
        {
            stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgBusVoltOk = 0U;
            stPfcStMacLoc.uiCntrBusChk = 0U;
        }
    }
    else
    {
        stPfcStMacLoc.uiCntrPfcRly++;
        if(stPfcStMacLoc.uiCntrPfcRly > 50U)    ///< Maintain 40ms make sure AC relay finish action
        {
            stPfcStMacLoc.uiCntrPfcRly = 0U;
            stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 1U;
            stPfcStMacLoc.stExt.unGPIOCmd.bit.uiAuxRly      = 1U;
        }
    }

    /* Output parameter */
#if (1U == PFC_ST_MAC_FLG_DBG)
    stPfcStMac.ftVoltPreChrgLmt = stPfcStMacDbg.ftVoltPreChrgLmt;
#else
    stPfcStMac.ftVoltPreChrgLmt = stPfcStMacLoc.stExt.ftVoltPreChrgLmt;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state PWM Enable state 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_PwmEn_1ms(void)
{
    /* Condition (transition from state "PFC_ST_MAC_PWMEN" to state "PFC_ST_MAC_FLT" with priority 1st)  */
    if(PFC_FLT_IS_SET)
    {
        /* Switch to state "PFC_ST_MAC_FLT" */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_FLT;    ///< Switch to state "PFC_ST_MAC_FLT"
    }
    /* Condition (transition from state "PFC_ST_MAC_PWMEN" to state "PFC_ST_MAC_STB" with priority 2nd) */
    else if(STOP_CMD == stComIf.uiCmdPfcRun)
    {
        /* Switch to state "PFC_ST_MAC_STB"  */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_STB;    ///< Switch to state "PFC_ST_MAC_STB"
    }
    /* Condition (transition from state "PFC_ST_MAC_PWMEN" to state "PFC_ST_MAC_CHK" with priority 3rd) */
    else if(stComIf.uiModRun != stCom.uiModRunReq)
    {
        stPfcStMacLoc.uiCntrPfcRly = 0U;
        stPfcStMacLoc.uiFlgModChg  = FCN_ENABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 0U;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk     = FCN_DISABLE;
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun      = FCN_DISABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt        = PFC_ST_MAC_CHK;
    }
    /* Condition (transition from state "PFC_ST_MAC_PWMEN" to state "PFC_ST_MAC_NORMRUN"  with priority 4th) */
    else if(FCN_ENABLE == stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk)
    {
        /* Switch to state "PFC_ST_MAC_NORMRUN" */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_NORMRUN;
    }
    /* Static (state "PFC_ST_MAC_PWMEN") */
    else
    {
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun  = FCN_ENABLE;
        v_PfcStMac_ST_PwmEn_RunOk_1ms();
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state PWM Enable state RunOK judgment 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_PwmEn_RunOk_1ms(void)
{
    if(CHG_ONGRID_MODE == stComIf.uiModPfcRun)
    {
        if((fabsf(stPowLim.ftVoltBusLim - stPfcAdc.ftVbusCell[0][0]) < 10.0f) \
           &&(fabsf(stPowLim.ftVoltBusLim - stPfcAdc.ftVbusCell[1][0]) < 10.0f) \
           &&(fabsf(stPowLim.ftVoltBusLim - stPfcAdc.ftVbusCell[2][0]) < 10.0f)) ///< Bus voltage control OK
        {
            stPfcStMacLoc.uiCntrBusRdy++;
            if(stPfcStMacLoc.uiCntrBusRdy > 100U)
            {
                stPfcStMacLoc.uiCntrBusRdy = 0U;
                stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk = FCN_ENABLE;
            }
        }
        else if(stPfcStMacLoc.uiCntrBusRdy > 0U)
        {
            stPfcStMacLoc.uiCntrBusRdy--;
        }
        else
        {
            ///< No code
        }
    }
    else
    {
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk = FCN_ENABLE;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC machine state normal run state 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_ST_NormRun_1ms(void)
{
    /* Condition (transition from state "PFC_ST_MAC_NORMRUN" to state "PFC_ST_MAC_FLT" with priority 1st)  */
    if(PFC_FLT_IS_SET)
    {
        /* Switch to state "PFC_ST_MAC_FLT" */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_FLT;    ///< Switch to state "PFC_ST_MAC_FLT"
    }
    /* Condition (transition from state "PFC_ST_MAC_NORMRUN" to state "PFC_ST_MAC_STB" with priority 2nd) */
    else if(STOP_CMD == stComIf.uiCmdPfcRun)
    {
        /* Switch to state "PFC_ST_MAC_STB"  */
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt = PFC_ST_MAC_STB;    ///< Switch to state "PFC_ST_MAC_STB"
    }
    /* Condition (transition from state "PFC_ST_MAC_PWMEN" to state "PFC_ST_MAC_CHK" with priority 3rd) */
    else if(stComIf.uiModRun != stCom.uiModRunReq)
    {
        stPfcStMacLoc.uiCntrPfcRly = 0U;
        stPfcStMacLoc.uiFlgModChg  = FCN_ENABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgPreChrgOk = 0U;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk     = FCN_DISABLE;
        stPfcStMacLoc.stExt.unCtrlCmd.bit.uiCmdRun      = FCN_DISABLE;
        stPfcStMacLoc.stExt.unPFCSts.bit.uiMacSt        = PFC_ST_MAC_CHK;
    }
    /* Static (state "PFC_ST_MAC_NORMRUN") */
    else
    {
        ///< No code
    }
}

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC state machine output signal 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_Outp_1ms(void)
{
    v_PfcStMac_Outp_Rly_1ms();
    v_PfcStMac_Outp_ARM_1ms();

    /* Output parameter */
#if (1U == PFC_ST_MAC_FLG_DBG)
    stPfcStMac.unStsToArm.all = stPfcStMacDbg.unStsToArm.all;
    stPfcStMac.unGPIOCmd.all  = stPfcStMacDbg.unGPIOCmd.all;
#else
    stPfcStMac.unStsToArm.all = stPfcStMacLoc.stExt.unStsToArm.all;
    stPfcStMac.unGPIOCmd.all  = stPfcStMacLoc.stExt.unGPIOCmd.all;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub Unit function: PFC state machine output signal - DSP to ARM 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_Outp_ARM_1ms(void)
{
    stPfcStMacLoc.stExt.unStsToArm.bit.uiRunOk      = stPfcStMacLoc.stExt.unPFCSts.bit.uiFlgRunOk;    ///< PFC running OK flag

    stPfcStMacLoc.stExt.unStsToArm.bit.uiRelayA_Sts = stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyA;      ///< Bus pre-charge relay status
    stPfcStMacLoc.stExt.unStsToArm.bit.uiRelayB_Sts = stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyB;
    stPfcStMacLoc.stExt.unStsToArm.bit.uiRelayC_Sts = stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyC;
    stPfcStMacLoc.stExt.unStsToArm.bit.uiRelayN_Sts = stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN;

    stPfcStMacLoc.stExt.unStsToArm.bit.uiFlt        = stPfcStMacLoc.stExt.unPFCSts.bit.uiFault;      ///< PFC fault status
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: PFC state machine output signal - Relay control 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PfcStMac_Outp_Rly_1ms(void)
{
    if((1U == stCom.unCmdFct.bit.uiEnaAcRly) && (0U == stComIf.uiCmdPfcRun))    ///< AC relay simulation && PFC stop command
    {
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyA = stCom.unCmdFct.bit.uiEnaAcRlyA;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyB = stCom.unCmdFct.bit.uiEnaAcRlyB;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyC = stCom.unCmdFct.bit.uiEnaAcRlyC;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = stCom.unCmdFct.bit.uiEnaAcRlyN;
    }
    else if((AD_BIAS_ADJUST_OVER != stCom.uiCmdPfcADZeroAdj) && (0U == stComIf.uiCmdPfcRun))    ///< AC relay control by AD bias calculation
    {
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyA = stPfcDataCalc.stCtrlParm.unCmdADBiasRly.bit.uiRlyA;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyB = stPfcDataCalc.stCtrlParm.unCmdADBiasRly.bit.uiRlyB;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyC = stPfcDataCalc.stCtrlParm.unCmdADBiasRly.bit.uiRlyC;
        stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = stPfcDataCalc.stCtrlParm.unCmdADBiasRly.bit.uiRlyN;
    }
    else
    {
        switch(stPfcStMacLoc.uiCmdRly)
        {
            /* Turn off all relay */
            case PFC_RLY_OFF:
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyA = 0U;
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyB = 0U;
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyC = 0U;
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = 0U;
                break;
            /* Turn on related relay */
            case PFC_RLY_ON:
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyA = 1U;
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyB = 1U;
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyC = 1U;
                /* N line relay */
                if((PHASE_LOSS_RUN_MODE == stComIf.uiModPfcPhaLoss) || \
                   (OFFGRID_MODE == stComIf.uiModPfcRun) || \
                   ((BIDIR_ONGRID_MODE == stComIf.uiModPfcRun) && (PFC_PWR_ARM_CTRL_MODE == stCom.unModPfcPow.bit.uiModPowCtrl)))
                {
                    stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = 1U;
                }
                else
                {
                    stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = 0U;
                }
                break;
            /* Turn on N line relay */
            case PFC_RLY_N_LINE_ON:
                stPfcStMacLoc.stExt.unGPIOCmd.bit.uiRlyN = 1U;
                break;

            default:
                ///< Do nothing
                break;
        }
    }
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

