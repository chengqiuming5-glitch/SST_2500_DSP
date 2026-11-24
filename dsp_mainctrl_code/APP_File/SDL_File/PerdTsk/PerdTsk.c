//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerdTsk.c
 * @brief
 * The source file of PerdTsk is designed to judge module execution sequence.
 *
 * Module      :        		 \n
 * PerdTsk
 *
 * Unit        :        		 \n
 * null
 *
 * Unit Task   :                 \n
 * v_PerdTsk_Init()              \n
 * v_PerdTsk_1ms()               \n
 * v_PerdTsk_10ms()              \n
 * v_PerdTsk_100ms()             \n
 * v_PerdTsk_1s()                \n
 *
 * Unit Task   :        		 \n
 * null
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

//=====================================================
//    Include Header Files
//=====================================================
#include "PerdTsk.h"

//=====================================================
//    Variable Definition
//=====================================================
ST_PERD_TSK stPerdTsk;                  ///< PerdTsk global struct

static ST_PERD_TSK_LOC stPerdTskLoc;    ///< PerdTsk local struct

#if(1U == FLG_SWUT_EN)
struct CPUTIMER_REGS  CpuTimer0RegsUnitTest;
#endif

//=====================================================
//    Function definition
//=====================================================
/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period task initialization function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerdTsk_Init(void)
{
    /* Local Signal */
    stPerdTskLoc.uiCntr1ms           = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiCntr10ms          = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiCntr100ms         = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiCntr1s            = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiFlgSWIT1msDone    = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiFlgSWIT10msDone   = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiFlgSWIT100msDone  = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiFlgSWIT1sDone     = 0U;    ///< Initialize to 0U
    stPerdTskLoc.uiFlgSWITIsrDone                                 = 0U;      ///< Initialize to 0U
    stPerdTskLoc.stRunTimeTestLoc.uiCntrIsr                       = 0U;      ///< Initialize to 0U
    stPerdTskLoc.stRunTimeTestLoc.uiCntrMainloop                  = 0U;      ///< Initialize to 0U
    stPerdTskLoc.stRunTimeTestLoc.uiCntrIsrIn1ms                  = 0U;      ///< Initialize to 0U
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrStart                   = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrEnd                     = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValMainloopStart              = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValMainloopEnd                = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrDelta                   = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValMainloopDelta              = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrSum                     = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulCnrtIsrIn1msSum               = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.ulValMainloopSum                = 0UL;     ///< Initialize to 0UL
    stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrMax           = 0.0f;    ///< Initialize to 0.0f
    stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrAvg           = 0.0f;    ///< Initialize to 0.0f
    stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopMax      = 0.0f;    ///< Initialize to 0.0f
    stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopAvg      = 0.0f;    ///< Initialize to 0.0f
    stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopNoIsrAvg = 0.0f;    ///< Initialize to 0.0f

    /* Global Signal */
    stPerdTsk.uiFlgSWIT1msEn         = FCN_DISABLE;
    stPerdTsk.uiFlgSWIT10msEn        = FCN_DISABLE;
    stPerdTsk.uiFlgSWIT100msEn       = FCN_DISABLE;
    stPerdTsk.uiFlgSWIT1sEn          = FCN_DISABLE;
    stPerdTsk.uiFlgSWITIsrEn         = FCN_DISABLE;
    stPerdTsk.uiFlgSWITDyn1ms        = FCN_DISABLE;
    stPerdTsk.uiFlgSWITDyn10ms       = FCN_DISABLE;
    stPerdTsk.uiFlgSWITDyn100ms      = FCN_DISABLE;
    stPerdTsk.uiFlgSWITDyn1s         = FCN_DISABLE;
    stPerdTsk.uiFlgSWITDynIsr        = FCN_DISABLE;
    stPerdTsk.stRunTimeTest.ftTimeIsrMax           = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrMax;
    stPerdTsk.stRunTimeTest.ftTimeIsrAvg           = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrAvg;
    stPerdTsk.stRunTimeTest.ftTimeMainloopMax      = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopMax;
    stPerdTsk.stRunTimeTest.ftTimeMainloopAvg      = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopAvg;
    stPerdTsk.stRunTimeTest.ftTimeMainloopNoIsrAvg = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopNoIsrAvg;

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_PerdTsk_Init() is running****\r\n");
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period task ADCB1 ISR function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if(0U == FLG_SWUT_EN)
#ifndef _SIMULATION_NO_DSP_
#pragma CODE_SECTION(v_PerdTsk_Adc_ISR, ".TI.ramfunc");
#endif
interrupt void v_PerdTsk_Adc_ISR(void)
#else
void v_PerdTsk_Adc_ISR(void)
#endif
{

#if(1U == FLG_SWIT_EN)
    if((FCN_ENABLE == stPerdTsk.uiFlgSWITIsrEn) && (0U == stPerdTskLoc.uiFlgSWITIsrDone))
    {
        stPerdTsk.uiFlgSWITDynIsr = FCN_ENABLE;
    }
    else
    {
        stPerdTsk.uiFlgSWITDynIsr = FCN_DISABLE;
    }
#endif

#ifndef _SIMULATION_NO_DSP_
    if(0U == stCom.uiFlgUpgProg) ///< BootLoader flag
    {
        ServiceDog();    ///< Service WatchDog
    }
#endif

#if 1U == FLG_RUN_TIME_TEST_EN
    /* CPU timer value when ISR start */
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrStart = CNTR_CPUTIMER1_REG;
#endif

    /* ADC drive */
    v_AdcDrv_Isr();    //0.64us
    /* PFC ADC */
    v_PfcAdc_Isr();   //3.74us
    /* PFC fault diagnosis  ov oc */
    v_PfcDiag_Isr();  //2.1us
    /*read fast data from fpga*/
    v_Emif_Rd_Isr();  //7.06us

#if 1U == FLG_PFC_POWCTRL_EN
    /* PFC power control ISR task */

    v_PfcPowCtrl_Isr(); //27.4us

#endif
#if 1U == FLG_D2D_POWCTRL_EN
    /* D2D power control ISR task */
    v_D2dPowCtrl_Isr();
#endif
    /* EPWM drive */
    //v_EPwmDrv_Isr();
    /* PFC data calculation task in ISR */  
    v_PfcDataCalc_Isr(); //8.9us

#if 1U == FLG_FLT_DATA_REC_EN
    /* Fault data record task in ISR */
    v_FltDataRec_ISR();
#endif
#if 2U == GRID_PHASE_NUMBER
    /* PFC relay pwm control task in ISR */
    v_PerphDrv_Isr();
#endif
#if 1U == FLG_ON_OFF_GRID_SWT_EN
    /* On&off grid switch task in ISR */
    v_OnOffGridSwt_Isr();
#endif

#if 1U == FLG_RUN_TIME_TEST_EN
    /* CPU timer value when ISR end */
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrEnd = CNTR_CPUTIMER1_REG;
    /* Calculate CPU run timer */
    v_PerdTsk_Isr_Runtime_Cal();
#endif

#ifndef _SIMULATION_NO_DSP_
    ADC_INT_REG.ADCINTFLGCLR.bit.ADCINT1 = 1U;      ///< Clear ADCINT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1_DSP;     ///< Acknowledge this INT to receive more INT from group 1
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITIsrEn)
    {
        stPerdTskLoc.uiFlgSWITIsrDone = 1U;
    }
    else
    {
        stPerdTskLoc.uiFlgSWITIsrDone = 0U;
    }
#endif

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period task in main-loop
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_PerdTsk_MainLoop(void)
{
#ifndef _SIMULATION_NO_DSP_
    if(1U == CPUTIMER0_REG.TCR.bit.TIF)
#endif
    {
        CPUTIMER0_REG.TCR.bit.TIF = 1U;                ///< Clear the CpuTimer0 flag

        v_PerdTsk_1ms();                               ///< CPU timer 1ms task
        stPerdTskLoc.uiCntr1ms++;
        if(stPerdTskLoc.uiCntr1ms >= 10U)
        {
            stPerdTskLoc.uiCntr1ms = 0U;               ///< Clear 1ms counter
            v_PerdTsk_10ms();                          ///< CPU timer 10ms task

            stPerdTskLoc.uiCntr10ms++;
            if(stPerdTskLoc.uiCntr10ms >= 10U)
            {
                stPerdTskLoc.uiCntr10ms = 0U;          ///< Clear 10ms counter
                v_PerdTsk_100ms();                     ///< CPU timer 100ms task

                stPerdTskLoc.uiCntr100ms++;
                if(stPerdTskLoc.uiCntr100ms >= 10U)
                {
                    stPerdTskLoc.uiCntr100ms = 0U;     ///< Clear 100ms counter
                    v_PerdTsk_1s();                    ///< CPU timer 1s task

                    stPerdTskLoc.uiCntr1s++;
                }
            }
        }
		
#if 1U == FLG_RUN_TIME_TEST_EN
        stPerdTskLoc.stRunTimeTestLoc.ulValMainloopEnd = CNTR_CPUTIMER1_REG;    ///< CPU timer value when main loop start
        v_PerdTsk_Mainloop_Runtime_Cal_1ms();                                   ///< Calculate main loop run time
#endif
    }

#if 1U == FLG_RUN_TIME_TEST_EN
        stPerdTskLoc.stRunTimeTestLoc.ulValMainloopStart = CNTR_CPUTIMER1_REG;    ///< CPU timer value when main loop start
        stPerdTskLoc.stRunTimeTestLoc.uiCntrIsrIn1ms     = 0U;                    ///< Clear ISR occur counter in 1ms task
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerdTsk_1ms(void)
{


#if(1U == FLG_SWIT_EN)
    if((FCN_ENABLE == stPerdTsk.uiFlgSWIT1msEn) && (0U == stPerdTskLoc.uiFlgSWIT1msDone))
    {
        stPerdTsk.uiFlgSWITDyn1ms = FCN_ENABLE;
    }
    else
    {
        stPerdTsk.uiFlgSWITDyn1ms = FCN_DISABLE;
    }
#endif

    v_AdcDrv_1ms();                 ///< 1st  1ms Task: ADC drive 1ms task
    v_ECapDrv_1ms();                ///< 2nd  1ms Task: ECap drive 1ms task
#ifndef SST_1250kW
    v_EPwmDrv_1ms();                ///< 3rd  1ms Task: EPwm drive 1ms task
#endif
    v_ComIf_1ms();                  ///< 4th  1ms Task: Module ComIf
    v_CmnAdc_1ms();                 ///< 5th  1ms Task: Module CmnAdc
    v_D2dAdc_1ms();                 ///< 6th  1ms Task: Module D2dAdc
    v_PfcAdc_1ms();                 ///< 7th  1ms Task: Cell Bus voltage  9.1us
    v_PfcDataCalc_1ms();          	///< 8th  1ms Task: Module PfcDataCalc
    v_CmnDiag_1ms();              	///< 9th  1ms Task: Module CmnDiag
    v_PfcDiag_1ms();              	///< 10th  1ms Task: Module PfcDiag
    v_D2dDiag_1ms();              	///< 11th 1ms Task: Module D2dDiag
    v_PfcStMac_1ms();             	///< 12th 1ms Task: Module PfcStMac
    v_D2dStMac_1ms();             	///< 13th 1ms Task: Module D2dStMac
#ifndef SST_1250kW
    v_PerphCtrl_1ms();            	///< 14th 1ms Task: Module PerphCtrl
    v_PerphDrv_1ms();             	///< 15th 1ms Task: Module PerphDrv
#endif
    v_PowLim_1ms();               	///< 16th 1ms Task: Module PowLim
#if 1U == FLG_PFC_GRIDCTRL_EN
    v_PfcGridCtrl_1ms();          	///< 17th 1ms Task: Module PfcGridCtrl
#endif
    v_PfcPowPreCtrl_1ms();        	///< 18th 1ms Task: Module PfcPowPreCtrl reference ramp
    v_PfcPowCtrl_1ms();         	///< 19th 1ms Task: PFC power control 1ms task
    v_D2dPowPreCtrl_1ms();        	///< 20th 1ms Task: Module D2dPowPreCtrl
    v_D2dPowCtrl_1ms();           	///< 21th 1ms Task: Module D2dPowCtrl
#ifndef _SIMULATION_NO_DSP_
    v_Eep_1ms();                 	///< 22th 1ms Task: Module Eep
#endif
#if 1U == FLG_FLT_DATA_REC_EN
    v_FltDataRec_1ms();           	///< 22th 1ms Task: Module FltDataRec
    v_Spi_1ms();                  	///< 23th 1ms Task: Module Spi
#endif 
#if 1U == FLG_ON_OFF_GRID_SWT_EN
    v_OnOffGridSwt_1ms();           ///< 24th 1ms Task: Module OnOffGridSwt
#endif

#if(0U == COM_MODE)
    v_SciDrv_1ms();                 ///< 22th 1ms Task: Module SciDrv
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWIT1msEn)
    {
        stPerdTskLoc.uiFlgSWIT1msDone = 1U;
    }
    else
    {
        stPerdTskLoc.uiFlgSWIT1msDone = 0U;
    }
#endif

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period 10ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerdTsk_10ms(void)
{
#if(1U == FLG_SWIT_EN)
    if((FCN_ENABLE == stPerdTsk.uiFlgSWIT10msEn) && (0U == stPerdTskLoc.uiFlgSWIT10msDone))
    {
        stPerdTsk.uiFlgSWITDyn10ms = FCN_ENABLE;
    }
    else
    {
        stPerdTsk.uiFlgSWITDyn10ms = FCN_DISABLE;
    }
#endif

    v_ComIf_10ms();                   ///< 1st  10ms Task: Module ComIf
    v_PfcDataCalc_10ms();             ///< 2nd  10ms Task: Module PfcDataCalc
    v_PfcDiag_10ms();                 ///< 3rd  10ms Task: Module PfcDiag
	v_D2dDiag_10ms();                 ///< 4th  10ms Task: Module D2dDiag
    v_PerphCtrl_10ms();               ///< 5th  10ms Task: Module PerphCtrl
    v_PerphDrv_10ms();                ///< 6th  10ms Task: Module PerphDrv
#if 1U == FLG_PFC_GRIDCTRL_EN
    v_PfcGridCtrl_10ms();             ///< 7th  10ms Task: Module PfcGridCtrl
#endif
    v_PfcPowPreCtrl_10ms();           ///< 8th  10ms Task: Module PfcPowPreCtrl
#if 1U == FLG_FLT_RSTRT_EN
    v_FltRstrt_10ms();                ///< 9th  10ms Task: Module FltRstrt
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWIT10msEn)
    {
        stPerdTskLoc.uiFlgSWIT10msDone = 1U;
    }
    else
    {
        stPerdTskLoc.uiFlgSWIT10msDone = 0U;
    }
#endif

}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period 100ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerdTsk_100ms(void)
{
#if(1U == FLG_SWIT_EN)
    if((FCN_ENABLE == stPerdTsk.uiFlgSWIT100msEn) && (0U == stPerdTskLoc.uiFlgSWIT100msDone))
    {
        stPerdTsk.uiFlgSWITDyn100ms = FCN_ENABLE;
    }
    else
    {
        stPerdTsk.uiFlgSWITDyn100ms = FCN_DISABLE;
    }
#endif

    static Uint16 i =0;
  if(i == 0)
  {
      WATCHDAG_ON;
      i = 1;
  }
  else
  {
      i = 0;
      WATCHDAG_OFF;
  }

    v_Com_100ms();                      ///< 1st  100ms task: Module Com
    v_ComIf_100ms();                    ///< 2nd  100ms Task: Module ComIf
    v_CmnAdc_100ms();                   ///< 3rd  100ms Task: Module CmnAdc(sst no use)
    v_CmnDiag_100ms();                  ///< 4th  100ms Task: Module CmnDiag
    v_PfcDiag_100ms();                  ///< 5th  100ms Task: Module PfcDiag
    v_PerphCtrl_100ms();                ///< 6th  100ms Task: Module PerphCtrl Run Led Control
    v_PerphDrv_100ms();                 ///< 7th  100ms Task: Module PerphDrv Run Led Control
    v_PowLim_100ms();                   ///< 8th  100ms Task: Module PowLim
    v_Eep_100ms();						///< 9th  100ms Task: Module Eep

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWIT100msEn)
    {
        stPerdTskLoc.uiFlgSWIT100msDone = 1U;
    }
    else
    {
        stPerdTskLoc.uiFlgSWIT100msDone = 0U;
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Period 1s task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerdTsk_1s(void)
{
#if(1U == FLG_SWIT_EN)
    if((FCN_ENABLE == stPerdTsk.uiFlgSWIT1sEn) && (0U == stPerdTskLoc.uiFlgSWIT1sDone))
    {
        stPerdTsk.uiFlgSWITDyn1s = FCN_ENABLE;
    }
    else
    {
        stPerdTsk.uiFlgSWITDyn1s = FCN_DISABLE;
    }
#endif

    v_Com_1s();                       ///< 1st 1s Task: Module Com
#if 1U == FLG_FLT_RSTRT_EN
    v_FltRstrt_1s();                  ///< 2nd 1s Task: Module FltRstrt
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWIT1sEn)
    {
        stPerdTskLoc.uiFlgSWIT1sDone = 1U;
    }
    else
    {
        stPerdTskLoc.uiFlgSWIT1sDone = 0U;
    }
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Calculate Isr run time
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
#if 1U == FLG_RUN_TIME_TEST_EN
static void v_PerdTsk_Isr_Runtime_Cal(void)
{
    float32 l_ftRunTimeIsr = 0.0f;    ///< ISR run time

    /* Calculate delta CPU timer value of ISR */
    if(stPerdTskLoc.stRunTimeTestLoc.ulValIsrStart > stPerdTskLoc.stRunTimeTestLoc.ulValIsrEnd)
    {
        stPerdTskLoc.stRunTimeTestLoc.ulValIsrDelta = stPerdTskLoc.stRunTimeTestLoc.ulValIsrStart - stPerdTskLoc.stRunTimeTestLoc.ulValIsrEnd;
    }
    else
    {
        stPerdTskLoc.stRunTimeTestLoc.ulValIsrDelta = stPerdTskLoc.stRunTimeTestLoc.ulValIsrStart + (PERD_CPUTIMER1_REG - stPerdTskLoc.stRunTimeTestLoc.ulValIsrEnd);
    }

    /* Calculate Max ISR time */
    l_ftRunTimeIsr = (float32)stPerdTskLoc.stRunTimeTestLoc.ulValIsrDelta * COEFF_ISR_RUN_TIME_MAX;
    if(l_ftRunTimeIsr > stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrMax)
    {
        stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrMax = l_ftRunTimeIsr;
    }

    /* Calculate Average ISR time */
    stPerdTskLoc.stRunTimeTestLoc.uiCntrIsr++;
    stPerdTskLoc.stRunTimeTestLoc.ulValIsrSum += stPerdTskLoc.stRunTimeTestLoc.ulValIsrDelta;
    if(stPerdTskLoc.stRunTimeTestLoc.uiCntrIsr >= NUM_ISR_RUN_TIME_TEST)
    {
        stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrAvg = (float32)(stPerdTskLoc.stRunTimeTestLoc.ulValIsrSum) * COEFF_ISR_RUN_TIME_AVG;
        stPerdTskLoc.stRunTimeTestLoc.uiCntrIsr   = 0U;        ///< Clear counter
        stPerdTskLoc.stRunTimeTestLoc.ulValIsrSum = 0UL;       ///< Clear sum value
    }

    stPerdTskLoc.stRunTimeTestLoc.uiCntrIsrIn1ms++;

    /* Global Signal */
    stPerdTsk.stRunTimeTest.ftTimeIsrMax = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrMax;
    stPerdTsk.stRunTimeTest.ftTimeIsrAvg = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrAvg;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: Calculate main loop run time
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_PerdTsk_Mainloop_Runtime_Cal_1ms(void)
{
    float32 l_ftRunTimeMainLoop = 0.0f;    ///< Main loop run time

    /* Calculate delta CPU timer value of main loop */
    if(stPerdTskLoc.stRunTimeTestLoc.ulValMainloopStart > stPerdTskLoc.stRunTimeTestLoc.ulValMainloopEnd)
    {
        stPerdTskLoc.stRunTimeTestLoc.ulValMainloopDelta = stPerdTskLoc.stRunTimeTestLoc.ulValMainloopStart - stPerdTskLoc.stRunTimeTestLoc.ulValMainloopEnd;
    }
    else
    {
        stPerdTskLoc.stRunTimeTestLoc.ulValMainloopDelta = stPerdTskLoc.stRunTimeTestLoc.ulValMainloopStart + (PERD_CPUTIMER1_REG - stPerdTskLoc.stRunTimeTestLoc.ulValMainloopEnd);
    }

    /* Calculate Max main loop run time */
    l_ftRunTimeMainLoop = (float32)stPerdTskLoc.stRunTimeTestLoc.ulValMainloopDelta * COEFF_MAIN_LOOP_RUN_MAX;
    if(l_ftRunTimeMainLoop > stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopMax)
    {
        stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopMax = l_ftRunTimeMainLoop;
    }

    /* Calculate average main loop run time */
    stPerdTskLoc.stRunTimeTestLoc.uiCntrMainloop++;
    stPerdTskLoc.stRunTimeTestLoc.ulValMainloopSum += stPerdTskLoc.stRunTimeTestLoc.ulValMainloopDelta;
    stPerdTskLoc.stRunTimeTestLoc.ulCnrtIsrIn1msSum += stPerdTskLoc.stRunTimeTestLoc.uiCntrIsrIn1ms;       ///< Sum Isr counter while 1ms task occur in main loop
    if(stPerdTskLoc.stRunTimeTestLoc.uiCntrMainloop >= NUM_MAIN_LOOP_RUN_TIME_TEST)
    {
        /* Calculate Average PerdTsk run time */
        stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopAvg = (float32)stPerdTskLoc.stRunTimeTestLoc.ulValMainloopSum * COEFF_MAIN_LOOP_RUN_AVG;
        /* Calculate Average PerdTsk run time without interrupt */
        stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopNoIsrAvg = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopAvg \
                - ((float32)stPerdTskLoc.stRunTimeTestLoc.ulCnrtIsrIn1msSum * RECPR_MAIN_LOOP_RUN_TIME_TEST) * stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeIsrAvg;

        stPerdTskLoc.stRunTimeTestLoc.uiCntrMainloop    = 0U;     ///< Clear main loop counter
        stPerdTskLoc.stRunTimeTestLoc.ulCnrtIsrIn1msSum = 0UL;    ///< Clear sum of ISR counter in 1ms
        stPerdTskLoc.stRunTimeTestLoc.ulValMainloopSum  = 0UL;    ///< Clear sum of main loop delta value
    }

    /* Global Signal */
    stPerdTsk.stRunTimeTest.ftTimeMainloopAvg      = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopAvg;
    stPerdTsk.stRunTimeTest.ftTimeMainloopMax      = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopMax;
    stPerdTsk.stRunTimeTest.ftTimeMainloopNoIsrAvg = stPerdTskLoc.stRunTimeTestLoc.stPrmExt.ftTimeMainloopNoIsrAvg;
}
#endif
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
