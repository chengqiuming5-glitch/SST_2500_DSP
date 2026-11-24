//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_Led.c
 * @brief
 * The source file of led control is designed to realize D2d Led function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Led_Init()              \n
 * v_PerphCtrl_Led_100ms()             \n
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
#include "PerphCtrl_Led.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_LED_LOC stLedLoc;

//==============================================================================================
//    Function definition
//==============================================================================================

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: led control in initial task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_Led_Init(void)
{
    /* Local Signal*/
    stLedLoc.stPrmExt.uiCmdDspRun   = 0U;
    stLedLoc.stPrmExt.uiCmdPfcRunSt = 0U;
	stLedLoc.stPrmExt.uiCmdD2dRunSt = 0U;
    stLedLoc.uiNrDspRun             = 0U;
    stLedLoc.uiNrPfcRunSt           = 0U;
    stLedLoc.uiCntrPfcRunSt         = 0U;
	stLedLoc.uiNrD2dRunSt           = 0U;
	stLedLoc.uiCntrD2dRunSt         = 0U;

    /* Global Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrlDbg.stLed.uiCmdDspRun   = stLedLoc.stPrmExt.uiCmdDspRun;
    stPerphCtrlDbg.stLed.uiCmdPfcRunSt = stLedLoc.stPrmExt.uiCmdPfcRunSt;
	stPerphCtrlDbg.stLed.uiCmdD2dRunSt = stLedLoc.stPrmExt.uiCmdD2dRunSt;

    stPerphCtrl.stLed.uiCmdDspRun      = stPerphCtrlDbg.stLed.uiCmdDspRun;
    stPerphCtrl.stLed.uiCmdPfcRunSt    = stPerphCtrlDbg.stLed.uiCmdPfcRunSt;
	stPerphCtrl.stLed.uiCmdD2dRunSt    = stPerphCtrlDbg.stLed.uiCmdD2dRunSt;
#else
    stPerphCtrl.stLed.uiCmdDspRun      = stLedLoc.stPrmExt.uiCmdDspRun;
    stPerphCtrl.stLed.uiCmdPfcRunSt    = stLedLoc.stPrmExt.uiCmdPfcRunSt;
	stPerphCtrl.stLed.uiCmdD2dRunSt    = stLedLoc.stPrmExt.uiCmdD2dRunSt;
#endif
}

/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: led control in 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerphCtrl_Led_100ms(void)
{
    v_PerphCtrl_Led_DspRun_100ms();
    v_PerphCtrl_Led_PfcRunSt_100ms(); ///< sst no use
    v_PerphCtrl_Led_D2dRunSt_100ms(); ///< sst no use
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC run state led control in 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Led_DspRun_100ms(void)
{
    stLedLoc.uiNrDspRun++;
    if(stLedLoc.uiNrDspRun > LED_TOG_DSP_APP)
    {
        if(0U == stLedLoc.stPrmExt.uiCmdDspRun)
        {
            stLedLoc.stPrmExt.uiCmdDspRun = 1U;
        }
        else
        {
            stLedLoc.stPrmExt.uiCmdDspRun = 0U;
        }
        stLedLoc.uiNrDspRun = 0U;
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrl.stLed.uiCmdDspRun = stPerphCtrlDbg.stLed.uiCmdDspRun;
#else
    stPerphCtrl.stLed.uiCmdDspRun = stLedLoc.stPrmExt.uiCmdDspRun;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: PFC run state led control in 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Led_PfcRunSt_100ms(void)
{
    if(PFC_ST_MAC_FLT == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        stLedLoc.uiNrPfcRunSt = LED_TOG_FLT;       ///< Led toggle for PFC Fault state
    }
    else if(PFC_ST_MAC_STB == stPfcStMac.unPFCSts.bit.uiMacSt)
    {
        stLedLoc.uiNrPfcRunSt = LED_TOG_STB;       ///< Led toggle for PFC standby state
    }
    else
    {
        stLedLoc.uiNrPfcRunSt = LED_TOG_RUN;       ///< Led toggle for PFC other state
    }

    /* Led Toggle logic*/
    stLedLoc.uiCntrPfcRunSt++;
    if(stLedLoc.uiCntrPfcRunSt >= stLedLoc.uiNrPfcRunSt)
    {
        if(0U == stLedLoc.stPrmExt.uiCmdPfcRunSt)
        {
            stLedLoc.stPrmExt.uiCmdPfcRunSt = 1U;
        }
        else
        {
            stLedLoc.stPrmExt.uiCmdPfcRunSt = 0U;
        }
        stLedLoc.uiCntrPfcRunSt = 0U;
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrl.stLed.uiCmdPfcRunSt = stPerphCtrlDbg.stLed.uiCmdPfcRunSt;
#else
    stPerphCtrl.stLed.uiCmdPfcRunSt = stLedLoc.stPrmExt.uiCmdPfcRunSt;
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Unit function: D2D run state led control in 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerphCtrl_Led_D2dRunSt_100ms(void)
{
    if(D2D_ST_MAC_FLT == stD2dStMac.uiStD2dRun)
    {
        stLedLoc.uiNrD2dRunSt = LED_TOG_FLT;       ///< Led toggle for D2d Fault state
    }
    else if(D2D_ST_MAC_STB == stD2dStMac.uiStD2dRun)
    {
        stLedLoc.uiNrD2dRunSt = LED_TOG_STB;       ///< Led toggle for D2d standby state
    }
    else
    {
        stLedLoc.uiNrD2dRunSt = LED_TOG_RUN;       ///< Led toggle for D2d other state
    }

    /* Led Toggle logic*/
    stLedLoc.uiCntrD2dRunSt++;
    if(stLedLoc.uiCntrD2dRunSt >= stLedLoc.uiNrD2dRunSt)
    {
        if(0U == stLedLoc.stPrmExt.uiCmdD2dRunSt)
        {
            stLedLoc.stPrmExt.uiCmdD2dRunSt = 1U;
        }
        else
        {
            stLedLoc.stPrmExt.uiCmdD2dRunSt = 0U;
        }
        stLedLoc.uiCntrD2dRunSt = 0U;
    }

    /* Output Signal*/
#if (1U == PERPH_CTRL_DBG)
    stPerphCtrl.stLed.uiCmdD2dRunSt = stPerphCtrlDbg.stLed.uiCmdD2dRunSt;
#else
    stPerphCtrl.stLed.uiCmdD2dRunSt = stLedLoc.stPrmExt.uiCmdD2dRunSt;
#endif
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
