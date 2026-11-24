//==============================================================================================
//    File description
//==============================================================================================
/**@file         Adc_Cfg.c
* TITLE         : Adc configuration Source File
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
#include "AdcCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   ADC initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_AdcCfg_Init(void)
{
    v_AdcCfg_Cmn_Init();        ///< Configure ADCCLK divider and pulse positions
    v_AdcCfg_Pfc_Init();        ///< PFC ADC initial
    v_AdcCfg_D2d_Init();        ///< D2D ADC initial
#if 0U == FLG_SWUT_EN
	DELAY_US(5000.0L);
#endif
}

/**
* @brief   ADC initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_AdcCfg_Cmn_Init(void)
{
    EALLOW;
    /* ADCA Configuration*/
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6U;       ///< set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    ///< Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1U;       ///< power up the ADC

    /* ADCB Configuration*/
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6U;       ///< set ADCCLK divider to /4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    ///< Set pulse positions to late
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1U;       ///< power up the ADC

    /* ADCC Configuration*/
    AdccRegs.ADCCTL2.bit.PRESCALE = 6U;       ///< set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    ///< Set pulse positions to late
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1U;       ///< power up the ADC

    /* ADCD Configuration*/
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6U;       ///< set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    ///< Set pulse positions to late
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1U;       ///< power up the ADC
#if 0U == FLG_SWUT_EN
    DELAY_US(1000.0L);                          ///<  delay for 1ms to allow ADC time to power up
#endif
    EDIS;
}

/**
* @brief   PFC initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_AdcCfg_Pfc_Init(void)
{
    EALLOW;
#if 0
    //ADCA_SOC0
    AdcaRegs.ADCSOC0CTL.bit.CHSEL    = 2;        //ADCINA2;Iac_A
    AdcaRegs.ADCSOC0CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC1
    AdcaRegs.ADCSOC1CTL.bit.CHSEL    = 3;        //ADCINA3;Vac_B
    AdcaRegs.ADCSOC1CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC2
    AdcaRegs.ADCSOC2CTL.bit.CHSEL    = 4;        //ADCINA4;Vac_C
    AdcaRegs.ADCSOC2CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC3
    AdcaRegs.ADCSOC3CTL.bit.CHSEL    = 1;        //ADCINA1;Vbus
    AdcaRegs.ADCSOC3CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC4
    AdcaRegs.ADCSOC4CTL.bit.CHSEL    = 0;        //ADCINA0;Vbus_P
    AdcaRegs.ADCSOC4CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC5
    AdcaRegs.ADCSOC5CTL.bit.CHSEL    = 5;        //ADCINA0;DC_A
    AdcaRegs.ADCSOC5CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCA_SOC6
    AdcaRegs.ADCSOC6CTL.bit.CHSEL    = 13;        //DSP core temperature sensor
    AdcaRegs.ADCSOC6CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCB_SOC0
    AdcbRegs.ADCSOC0CTL.bit.CHSEL    = 0;        //ADCINB0;Iac_C
    AdcbRegs.ADCSOC0CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCB_SOC1
    AdcbRegs.ADCSOC1CTL.bit.CHSEL    = 2;        //ADCINB1;Iac_D
    AdcbRegs.ADCSOC1CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 0x05;      //ePWM1 SOCA
    //ADCB_SOC3
    AdcbRegs.ADCSOC3CTL.bit.CHSEL    = 3;        //ADCINB3;DC_B
    AdcbRegs.ADCSOC3CTL.bit.ACQPS   = AD_ACQPS;     //ACQPS
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCD_SOC0
    AdcdRegs.ADCSOC0CTL.bit.CHSEL   = 1;         //ADCIND1;Iac_B
    AdcdRegs.ADCSOC0CTL.bit.ACQPS  = AD_ACQPS;      //ACQPS
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCD_SOC1
    AdcdRegs.ADCSOC1CTL.bit.CHSEL   = 14;        //ADCIN14;Vac_A
    AdcdRegs.ADCSOC1CTL.bit.ACQPS  = AD_ACQPS;      //ACQPS
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCD_SOC2
    AdcdRegs.ADCSOC2CTL.bit.CHSEL   = 3;         //ADCIND3;DC_C
    AdcdRegs.ADCSOC2CTL.bit.ACQPS  = AD_ACQPS;      //ACQPS
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = 3;      //end of SOC3 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;      //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1  = 1;      //make sure INT1 flag is cleared
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;

    //ADCD_SOC1
    AdcdRegs.ADCSOC1CTL.bit.CHSEL   = 14;        //ADCIN14;Vac_A
    AdcdRegs.ADCSOC1CTL.bit.ACQPS  = AD_ACQPS;      //ACQPS
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
    //ADCD_SOC2
    AdcdRegs.ADCSOC2CTL.bit.CHSEL   = 3;         //ADCIND3;DC_C
    AdcdRegs.ADCSOC2CTL.bit.ACQPS  = AD_ACQPS;      //ACQPS
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 0x07;      //ePWM2 SOCA
#endif
    /* ADCA SOC0 sample channel_A5 Phase_A voltage */
    AdcaRegs.ADCSOC0CTL.bit.CHSEL    = CH_PFC_VAC_CA;   //ADCINA5;Uac_A
    AdcaRegs.ADCSOC0CTL.bit.ACQPS    = AD_ACQPS;        //ACQPS
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;  //ePWM2 SOCA
    /* ADCA SOC1 sample channel_A4 Phase_B voltage */
    AdcaRegs.ADCSOC1CTL.bit.CHSEL    = CH_PFC_VAC_AB;   //ADCINA4;Uac_B
    AdcaRegs.ADCSOC1CTL.bit.ACQPS    = AD_ACQPS;        //ACQPS
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;  //ePWM2 SOCA
    /* ADCA SOC2 sample channel_A3 Phase_C voltage */
    AdcaRegs.ADCSOC2CTL.bit.CHSEL    = CH_PFC_VAC_BC;   //ADCINA3;Uac_C
    AdcaRegs.ADCSOC2CTL.bit.ACQPS    = AD_ACQPS;        //ACQPS
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;  //ePWM2 SOCA
    /* ADCA SOC3 sample channel_A2 Phase_C DC component */
    AdcaRegs.ADCSOC3CTL.bit.CHSEL    = CH_PFC_VAC_DC_C;  //ADCINA2;Idc_C
    AdcaRegs.ADCSOC3CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA

    /* ADCB SOC0 sample channel_B3 Phase A current */
    AdcbRegs.ADCSOC0CTL.bit.CHSEL    = CH_PFC_IAC_A;     //ADCINB3;Iac_A
    AdcbRegs.ADCSOC0CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA
    /* ADCB SOC1 sample channel_B2 Phase B voltage */
    AdcbRegs.ADCSOC1CTL.bit.CHSEL    = CH_PFC_IAC_B;     //ADCINB2;Iac_B
    AdcbRegs.ADCSOC1CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA
    /* ADCB SOC2 sample channel_B0 Phase C voltage */
    AdcbRegs.ADCSOC2CTL.bit.CHSEL    = CH_PFC_IAC_C;     //ADCINB1;Iac_C
    AdcbRegs.ADCSOC2CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA

    AdcbRegs.ADCSOC3CTL.bit.CHSEL    = CH_PFC_VDC;     //ADCINB0;Vout
    AdcbRegs.ADCSOC3CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA

    /* ADCC SOC0 sample channel_C0 Phase C voltage */
    AdccRegs.ADCSOC0CTL.bit.CHSEL    = CH_P1V5;          //ADCINC2;P1V5
    AdccRegs.ADCSOC0CTL.bit.ACQPS    = AD_ACQPS;         //ACQPS
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;   //ePWM2 SOCA

    /* ADCD SOC0 sample channel_D14 Phase_B DC component */
    AdcdRegs.ADCSOC0CTL.bit.CHSEL    = CH_PFC_VAC_DC_B;   //ADCIND14;Idc_B
    AdcdRegs.ADCSOC0CTL.bit.ACQPS    = AD_ACQPS;          //ACQPS
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;    //ePWM2 SOCA
    /* ADCD SOC1 sample channel_D15 Phase_A DC component */
    AdcdRegs.ADCSOC1CTL.bit.CHSEL    = CH_PFC_VAC_DC_A;   //ADCIND15;Idc_A
    AdcdRegs.ADCSOC1CTL.bit.ACQPS    = AD_ACQPS;          //ACQPS
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;    //ePWM2 SOCA
    /* ADCD SOC2 sample channel_D0 PT1 temperature */
    AdcdRegs.ADCSOC2CTL.bit.CHSEL    = CH_PFC_TMP_PT1;    //ADCIND1;Temp_PT1
    AdcdRegs.ADCSOC2CTL.bit.ACQPS    = AD_ACQPS;          //ACQPS
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;    //ePWM2 SOCA
    /* ADCD SOC3 sample channel_D1 PT2 temperature */
    AdcdRegs.ADCSOC3CTL.bit.CHSEL    = CH_PFC_TMP_PT2;    //ADCIND0;Temp_PT2
    AdcdRegs.ADCSOC3CTL.bit.ACQPS    = AD_ACQPS;          //ACQPS
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL  = PFC_AD_TRI_SRC;    //ePWM2 SOCA

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = 2;      //end of SOC2 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;      //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1  = 1;      //make sure INT1 flag is cleared
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;
    EDIS;
#if 0U == FLG_SWUT_EN
    InitTempSensor(AD_REF_VOLT);
#endif
}

/**
* @brief   D2D ADC initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_AdcCfg_D2d_Init(void)
{
#if 0
    EALLOW;
#if 0U
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6U;    //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1U;    //power up the ADC

    AdccRegs.ADCCTL2.bit.PRESCALE = 6U;    //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    //Set pulse positions to late
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1U;    //power up the ADC

    AdcdRegs.ADCCTL2.bit.PRESCALE = 6U;    //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1U;    //Set pulse positions to late
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1U;    //power up the ADC
#endif
    /* SOC0 Configuration */
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 0x4U;            // C4: Total Output Current
    AdccRegs.ADCSOC0CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    /* SOC1 Configuration */
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 0x3U;            // C3: Total Output Voltage
    AdccRegs.ADCSOC1CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    /* SOC2 Configuration */
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 0x4U;            // C4: Total Output Current
    AdccRegs.ADCSOC2CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source
#if 0U
    /* SOC3 Configuration */
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 0x1U;            // A1: Bus voltage
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source
#endif
    AdccRegs.ADCSOC3CTL.bit.CHSEL = 0x3U;            // C3: Total Output Voltage
    AdccRegs.ADCSOC3CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 0xFU;            // D15:  Down Output Current
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    /* SOC4 Configuration */
    AdcdRegs.ADCSOC4CTL.bit.CHSEL = 0x4U;            // D4: Analog multiplexer; S1-1.5V; S3-Board temperature; S4-P12V
    AdcdRegs.ADCSOC4CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    /* SOC5 Configuration */
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 0x1U;            // A5: Down Output Voltage
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = AD_ACQPS;        // SH: 20 SYSCLK
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = AD_TRI_SRC;    // Trigger Source

    EDIS;
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
