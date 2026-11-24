//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmpssCfg.c
* TITLE         : Cmpss configuration Source File
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.10
* Version       : V1.0
* Descriptions  :
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
************************************************************************************************
*/

/*
************************************************************************************************
* Module        :
* 1st Unit      :
* 2nd Unit      :
* 3rd Unit      :
*
* Module Task   :

*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
************************************************************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//=====================================================
//    Include Header Files
//=====================================================
#include "CmpssCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   CMPSS initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_CmpssCfg_Init(void)
{
    EALLOW;
    v_CmpssCfg_Pfc_Init();  ///< PFC CMPSS initial
    v_CmpssCfg_D2d_Init();  ///< D2D CMPSS initial
    EDIS;
}

/**
* @brief   PFC CMPSS initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_CmpssCfg_Pfc_Init(void)
{
    EALLOW;
    Cmpss3Regs.COMPCTL.bit.COMPDACE     = 1;
    Cmpss3Regs.COMPDACCTL.bit.DACSOURCE = 0;
    Cmpss3Regs.COMPDACCTL.bit.SELREF    = REFERENCE_VDDA;
    Cmpss3Regs.COMPDACCTL.bit.SWLOADSEL = 0;
    Cmpss3Regs.COMPHYSCTL.bit.COMPHYS   = 4;
    /***H-cmpss**/
    Cmpss3Regs.COMPCTL.bit.COMPHSOURCE  = NEGIN_DAC;
    Cmpss3Regs.COMPCTL.bit.COMPHINV = 0;
    Cmpss3Regs.COMPCTL.bit.ASYNCHEN = ORGATE_ASYNCH_DIS;
    Cmpss3Regs.DACHVALS.bit.DACVAL      = 2628;

    Cmpss3Regs.CTRIPHFILCTL.bit.SAMPWIN = 16;
    Cmpss3Regs.CTRIPHFILCTL.bit.THRESH  = 12;
    Cmpss3Regs.CTRIPHFILCTL.bit.FILINIT = 1;

    Cmpss3Regs.COMPCTL.bit.CTRIPOUTHSEL = CTRIP_FILTER;
    Cmpss3Regs.COMPCTL.bit.CTRIPHSEL    = CTRIP_FILTER;

    /***L-cmpss**/
    Cmpss3Regs.COMPCTL.bit.COMPLSOURCE  = NEGIN_DAC;
    Cmpss3Regs.COMPCTL.bit.COMPLINV     = 1;
    Cmpss3Regs.COMPCTL.bit.ASYNCLEN     = ORGATE_ASYNCH_DIS;
    Cmpss3Regs.DACLVALS.bit.DACVAL      = 1468;

    Cmpss3Regs.CTRIPLFILCTL.bit.SAMPWIN = 16;
    Cmpss3Regs.CTRIPLFILCTL.bit.THRESH  = 12;
    Cmpss3Regs.CTRIPLFILCTL.bit.FILINIT = 1;

    Cmpss3Regs.COMPCTL.bit.CTRIPOUTLSEL = CTRIP_FILTER;
    Cmpss3Regs.COMPCTL.bit.CTRIPLSEL    = CTRIP_FILTER;

    Cmpss7Regs.COMPCTL.bit.COMPDACE = 1;                //comparator DAC1 enable
    Cmpss7Regs.COMPCTL.bit.COMPHSOURCE = NEGIN_DAC;     //Inverting input of comparator driven by internal DAC
    Cmpss7Regs.COMPCTL.bit.COMPHINV = 0;                //Output of comparator is not inverted
    Cmpss7Regs.COMPCTL.bit.ASYNCHEN = ORGATE_ASYNCH_DIS;
    Cmpss7Regs.COMPDACCTL.bit.DACSOURCE = 0;            //DACHVALA is updated from DACHVALS
    Cmpss7Regs.COMPDACCTL.bit.SELREF = REFERENCE_VDDA;  //VDDA is the voltage reference for the DAC
    Cmpss7Regs.COMPDACCTL.bit.SWLOADSEL = 0;            //DACxVALA is updated from DACxVALS on SYSCLK
    Cmpss7Regs.DACHVALS.bit.DACVAL = 1318;              //Protection value = 35A

    Cmpss7Regs.CTRIPHFILCTL.bit.SAMPWIN = 8;            //High filter sample window size:SAMPWIN+1
    Cmpss7Regs.CTRIPHFILCTL.bit.THRESH  = 5;            //High filter majority voting threshold:THRESH+1
    Cmpss7Regs.CTRIPHFILCTL.bit.FILINIT = 1;            //Initialize all samples to filter input value
    Cmpss7Regs.COMPCTL.bit.CTRIPOUTHSEL = 2;            //Output of digital filter drives CTRIPOUTH
    Cmpss7Regs.COMPCTL.bit.CTRIPHSEL  = 2;              //Output of digital filter drives CTRIPH
    Cmpss7Regs.COMPHYSCTL.bit.COMPHYS = 4;              //Set the typical hysteresis width

    Cmpss8Regs.COMPCTL.bit.COMPDACE = 1;                //comparator DAC1 enable
    Cmpss8Regs.COMPCTL.bit.COMPHSOURCE = NEGIN_DAC;     //Inverting input of comparator driven by internal DAC
    Cmpss8Regs.COMPCTL.bit.COMPHINV = 0;                //Output of comparator is not inverted
    Cmpss8Regs.COMPCTL.bit.ASYNCHEN = ORGATE_ASYNCH_DIS;
    Cmpss8Regs.COMPDACCTL.bit.DACSOURCE = 0;            //DACHVALA is updated from DACHVALS
    Cmpss8Regs.COMPDACCTL.bit.SELREF = REFERENCE_VDDA;  //VDDA is the voltage reference for the DAC
    Cmpss8Regs.COMPDACCTL.bit.SWLOADSEL = 0;            //DACxVALA is updated from DACxVALS on SYSCLK
    Cmpss8Regs.DACHVALS.bit.DACVAL =  1318;             //Protection value = 35A

    Cmpss8Regs.CTRIPHFILCTL.bit.SAMPWIN = 8;            //High filter sample window size:SAMPWIN+1
    Cmpss8Regs.CTRIPHFILCTL.bit.THRESH  = 5;            //High filter majority voting threshold:THRESH+1
    Cmpss8Regs.CTRIPHFILCTL.bit.FILINIT = 1;            //Initialize all samples to filter input value
    Cmpss8Regs.COMPCTL.bit.CTRIPOUTHSEL = 2;            //Output of digital filter drives CTRIPOUTH
    Cmpss8Regs.COMPCTL.bit.CTRIPHSEL = 2;               //Output of digital filter drives CTRIPH
    Cmpss8Regs.COMPHYSCTL.bit.COMPHYS = 4;              //Set the typical hysteresis width

    XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPH = 1;            //Clear flag bit
    XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPL = 1;            //Clear flag bit
    XbarRegs.XBARCLR1.bit.CMPSS7_CTRIPH = 1;            //Clear flag bit
    XbarRegs.XBARCLR1.bit.CMPSS8_CTRIPH = 1;            //Clear flag bit

    EDIS;

}

/********************************************Begin*********************************************/
/**
 * @brief        Sub-Unit function: System parameter change-Rated parameter2 update Eeprom task
 * @param [in]   stComTbl.stPrmPfcRtd2
 * @param [out]  null
 * @param [out]  null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_CmpssCfg_PrmUpd_Eep(void)
{
    if((STOP_CMD == stComIf.uiCmdRun) && (stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_STB))    ///< PFC no running
    {
        float32 l_ftCBCTemp = 0.0f;

#if 1U == GRID_PHASE_NUMBER
    /* Iac CBC */
    l_ftCBCTemp = stComTbl.stPrmPfcRtd2.ftCurrIabcCBC * IAC_CBC_COEFF_K + IAC_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    CBC_CMPSS_REG.DACHVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
    l_ftCBCTemp = -stComTbl.stPrmPfcRtd2.ftCurrIabcCBC * IAC_CBC_COEFF_K + IAC_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    CBC_CMPSS_REG.DACLVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
#elif 2U == GRID_PHASE_NUMBER
    l_ftCBCTemp = stComTbl.stPrmPfcRtd2.ftCurrIabcCBC * IAC_CBC_COEFF_K + IAC_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss1Regs.DACHVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
    Cmpss2Regs.DACHVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
    l_ftCBCTemp = -stComTbl.stPrmPfcRtd2.ftCurrIabcCBC * IAC_CBC_COEFF_K + IAC_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss1Regs.DACLVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
    Cmpss2Regs.DACLVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;

    l_ftCBCTemp = stComTbl.stPrmPfcRtd2.ftCurrInCBC * IN_CBC_COEFF_K + IN_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss5Regs.DACHVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
    l_ftCBCTemp = -stComTbl.stPrmPfcRtd2.ftCurrInCBC * IN_CBC_COEFF_K + IN_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss5Regs.DACLVALS.bit.DACVAL = (Uint16)l_ftCBCTemp;
#elif 3U == GRID_PHASE_NUMBER
    /* Iac CBC */
    l_ftCBCTemp = stComTbl.stPrmPfcRtd2.ftCurrIabcCBC * IAC_CBC_COEFF_K - IAC_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss7Regs.DACHVALS.bit.DACVAL =(Uint16)l_ftCBCTemp;
    Cmpss8Regs.DACHVALS.bit.DACVAL =(Uint16)l_ftCBCTemp;
    /* In positive CBC CBC */
    l_ftCBCTemp = stComTbl.stPrmPfcRtd2.ftCurrInCBC * IN_CBC_COEFF_K + IN_CBC_COEFF_B;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss3Regs.DACHVALS.bit.DACVAL =(Uint16)l_ftCBCTemp;
    /* In negative CBC CBC */
    l_ftCBCTemp = IN_CBC_COEFF_B - stComTbl.stPrmPfcRtd2.ftCurrInCBC * IN_CBC_COEFF_K;
    vFcn_FtUpDwnLim(&l_ftCBCTemp, CMPSS_MAX_LIMIT, CMPSS_MIN_LIMIT);
    Cmpss3Regs.DACLVALS.bit.DACVAL =(Uint16)l_ftCBCTemp;
#endif
    }
}
/*********************************************End**********************************************/

/**
* @brief   D2D CMPSS initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_CmpssCfg_D2d_Init(void)
{
    EALLOW;

    /* CMPSS8_H Configuration as Total Output Current Positive Protection */
    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPHSOURCE = 0U;                     ///< Inverting input of comparator driven by internal DAC
    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPHINV = 0U;                        ///< Output of comparator is not inverted
    OUT_CURR_CMPSS_REG.COMPCTL.bit.CTRIPHSEL = 2U;                       ///< Output of digital filter drives CTRIPH
    OUT_CURR_CMPSS_REG.COMPCTL.bit.CTRIPOUTHSEL = 2U;                    ///< Output of digital filter drives CTRIPOUTH
    OUT_CURR_CMPSS_REG.COMPDACCTL.bit.DACSOURCE = 0U;                    ///< DACHVALA is updated from DACHVALS
    OUT_CURR_CMPSS_REG.COMPDACCTL.bit.SELREF = 0U;                       ///< VDDA is the voltage reference for the DAC
    OUT_CURR_CMPSS_REG.COMPDACCTL.bit.SWLOADSEL = 0U;                    ///< DACxVALA is updated from DACxVALS on SYSCLK
    OUT_CURR_CMPSS_REG.DACHVALS.bit.DACVAL = (Uint16)CMPSS_OUTPARA_CURR_POS;     ///< Protection value
    OUT_CURR_CMPSS_REG.CTRIPHFILCTL.bit.SAMPWIN = 30U;                    ///< High filter sample window size:SAMPWIN+1
    OUT_CURR_CMPSS_REG.CTRIPHFILCTL.bit.THRESH = 29U;                     ///< High filter majority voting threshold:THRESH+1
    OUT_CURR_CMPSS_REG.CTRIPHFILCTL.bit.FILINIT = 1U;                    ///< Initialize all samples to filter input value
    /* CMPSS8_L Configuration as Total Output Current Negative Protection */
    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPLSOURCE = 0U;                     ///< Inverting input of comparator driven by internal DAC
    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPLINV = 1U;                        ///< Output of comparator is inverted
    OUT_CURR_CMPSS_REG.COMPCTL.bit.CTRIPLSEL = 2U;                       ///< Output of digital filter drives CTRIPL
    OUT_CURR_CMPSS_REG.COMPCTL.bit.CTRIPOUTLSEL = 2U;                    ///< Output of digital filter drives CTRIPOUTL
    OUT_CURR_CMPSS_REG.DACLVALS.bit.DACVAL = (Uint16)CMPSS_OUTPARA_CURR_NEG;     ///< Protection value
    OUT_CURR_CMPSS_REG.CTRIPLFILCTL.bit.SAMPWIN = 30U;                    ///< High filter sample window size:SAMPWIN+1
    OUT_CURR_CMPSS_REG.CTRIPLFILCTL.bit.THRESH = 29U;                     ///< High filter majority voting threshold:THRESH+1
    OUT_CURR_CMPSS_REG.CTRIPLFILCTL.bit.FILINIT = 1U;                    ///< Initialize all samples to filter input value
    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPDACE = 1U;                        ///< Comparator/DAC enabled

    /* Clear CMPSS Output Status*/
#if 0U == FLG_SWUT_EN
    DELAY_US(100U);                                                      ///< Delay 100us for steady state
#endif
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.HLATCHCLR = 1U;                    ///< Clear CMPSS8 High Comparator Output Status
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.LLATCHCLR = 1U;                    ///< Clear CMPSS8 Low Comparator Output Status

    EDIS;
}

/**
* @brief   FCT PWM test D2D CMPSS configuration function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_CmpssCfg_D2d_FctPwm(void)
{
    EALLOW;

    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPLINV = 0U;
    OUT_CURR_CMPSS_REG.DACLVALS.bit.DACVAL  = MAX_CMPSS_DACVAL;

    /* Clear CMPSS Output Status*/
#if 0U == FLG_SWUT_EN
    DELAY_US(10U);                                                       ///< Delay 100us for steady state
#endif
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.HLATCHCLR = 1U;                    ///< Clear CMPSS8 High Comparator Output Status
    OUT_CURR_CMPSS_REG.COMPSTSCLR.bit.LLATCHCLR = 1U;                    ///< Clear CMPSS8 Low Comparator Output Status

    OUT_CURR_CMPSS_REG.COMPCTL.bit.COMPDACE = 0U;                        ///< Comparator/DAC disabled

    EDIS;
}

/**
* @brief   FCT PWM test PFC CMPSS configuration function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_CmpssCfg_Pfc_FctPwm(void)
{
    EALLOW;

    Cmpss3Regs.COMPCTL.bit.COMPLINV = 0U;
    Cmpss3Regs.DACLVALS.bit.DACVAL  = MAX_CMPSS_DACVAL;
    Cmpss7Regs.COMPCTL.bit.COMPLINV = 0U;
    Cmpss7Regs.DACLVALS.bit.DACVAL  = MAX_CMPSS_DACVAL;
    Cmpss8Regs.COMPCTL.bit.COMPLINV = 0U;
    Cmpss8Regs.DACLVALS.bit.DACVAL  = MAX_CMPSS_DACVAL;

    /* Clear CMPSS Output Status*/
#if 0U == FLG_SWUT_EN
    DELAY_US(10U);                     ///< Delay 10us for steady state
#endif
    Cmpss3Regs.COMPSTSCLR.bit.HLATCHCLR = 1U;
    Cmpss3Regs.COMPSTSCLR.bit.LLATCHCLR = 1U;
    Cmpss3Regs.COMPCTL.bit.COMPDACE     = 0U;

    Cmpss7Regs.COMPSTSCLR.bit.HLATCHCLR = 1U;
    Cmpss7Regs.COMPSTSCLR.bit.LLATCHCLR = 1U;
    Cmpss7Regs.COMPCTL.bit.COMPDACE     = 0U;

    Cmpss8Regs.COMPSTSCLR.bit.HLATCHCLR = 1U;
    Cmpss8Regs.COMPSTSCLR.bit.LLATCHCLR = 1U;
    Cmpss8Regs.COMPCTL.bit.COMPDACE     = 0U;        ///< Comparator/DAC disabled

    EDIS;
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
