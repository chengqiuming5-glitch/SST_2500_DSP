//==============================================================================================
//    File description
//==============================================================================================
/**@file         GpioCfg.c
* TITLE         : Gpio configuration function
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
#include "GpioCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   main function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_GpioCfg_Init(void)
{
    InitGpio();             ///< Resets CPU GPIO
    v_GpioCfg_Pfc_Init();   ///< PFC GPIO Initial
    v_GpioCfg_D2d_Init();   ///< D2D GPIO Initial
    v_GpioCfg_Cmn_Init();   ///< Common GPIO Initial
}

/**
* @brief
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_Pfc_Init(void)
{
    v_GpioCfg_Pfc_ZCD_Init();       ///< ECAP init
    v_GpioCfg_Pfc_HwFlt_Init();     ///< Hardware fault init
    v_GpioCfg_Pfc_ECap_Init();     ///< ECap GPIO Initial
}

/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : ZCD GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Pfc_ZCD_Init(void)
{
    /* GPIO16 is set as Phase A ZCD signal */
    GPIO_SetupPinMux(PFC_ECAP1, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(PFC_ECAP1, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL6);
    /* GPIO17 is set as Phase B ZCD signal */
    GPIO_SetupPinMux(PFC_ECAP2, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(PFC_ECAP2, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL6);
    /* GPIO18 is set as Phase C ZCD signal */
    GPIO_SetupPinMux(PFC_ECAP3, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(PFC_ECAP3, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL6);
}
/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : PFC Hardware fault GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Pfc_HwFlt_Init(void)
{
#if 0
    //Iac_OCP
    GPIO_SetupPinMux(62U, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(62U, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL3);
    //BUS_OVP
    GPIO_SetupPinMux(73U, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(73U, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL6);

    EALLOW;
    GpioCtrlRegs.GPCCTRL.bit.QUALPRD1 = 160U;
    EDIS;

    //DSP_FAULT_OUTPUT
    GPIO_SetupPinMux(8U, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(8U, GPIO_OUTPUT, GPIO_PUSHPULL);
    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1U;        // Turn off DSP to ARM Emergence signal
    //ARM_FAULT_INTPUT
    GPIO_SetupPinMux(99U, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(99U, GPIO_INPUT, GPIO_PULLUP);
#endif
    /* GPIO32 is set as Phase A OCP input signal */
    GPIO_SetupPinMux(PFC_OCPA_HW, GPIO_MUX_CPU1, 0U);                  // GPIO32-GPIO
    GPIO_SetupPinOptions(PFC_OCPA_HW, GPIO_INPUT, GPIO_PULLUP|GPIO_INVERT|GPIO_QUAL6);        // GPIO32-Input
    /* GPIO29 is set as Phase B OCP input signal */
    GPIO_SetupPinMux(PFC_OCPB_HW, GPIO_MUX_CPU1, 0U);                  // GPIO29-GPIO
    GPIO_SetupPinOptions(PFC_OCPB_HW, GPIO_INPUT, GPIO_PULLUP|GPIO_INVERT|GPIO_QUAL6);        // GPIO29-Input
    /* GPIO28 is set as Phase C OCP input signal */
    GPIO_SetupPinMux(PFC_OCPC_HW, GPIO_MUX_CPU1, 0U);                  // GPIO28-GPIO
    GPIO_SetupPinOptions(PFC_OCPC_HW, GPIO_INPUT, GPIO_PULLUP|GPIO_INVERT|GPIO_QUAL6);        // GPIO28-Input

}

/**
* @brief   CAN GPIO initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_Pfc_ECap_Init(void)
{
    InitECapGpio();
}


/**
* @brief   D2D GPIO initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_D2d_Init(void)
{
#if 0
#if GRID_PHASE_NUMBER > 1U
    v_GpioCfg_D2d_V2L_Init();    ///< V2L IO init
#endif
    v_GpioCfg_D2d_EPwm_Init();   ///< D2d Epwm init
    v_GpioCfg_D2d_Bleed_Init();  ///< Bleed IO init
    v_GpioCfg_D2d_Rly_Init();    ///< D2d relay IO int
    v_GpioCfg_D2d_Led_Init();    ///< LED IO init
    v_GpioCfg_D2d_HwFlt_Init();
#endif
}

/**
* @brief   main function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_Cmn_Init(void)
{
    v_GpioCfg_Cmn_Spi_Init();      ///< Spi GPIO Initial
    v_GpioCfg_Cmn_Sci_Init();      ///< Sci GPIO Initial
    v_GpioCfg_Cmn_Can_Init();      ///< Can GPIO Initial
    v_GpioCfg_Cmn_I2c_Init();      ///< I2c GPIO Initial
    v_GpioCfg_Cmn_Led_Init();      ///< Led GPIO Initial
    v_GpioCfg_Cmn_HwFlt_Init();    ///< Hardware fault signal GPIO Initial
    v_GpioCfg_Cmn_Emif_Init();     ///< Emif GPIO Initial
    v_GpioCfg_Cmn_WDog_Init();
}

/**
* @brief   SPI GPIO initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_Cmn_Spi_Init(void)
{
    GPIO_SetupPinMux(CMN_SPI_SIMO, GPIO_MUX_CPU1, MUX_OPTION_SPI_SIMO);         ///< GPIO63-SPISIMOA
    GPIO_SetupPinOptions(CMN_SPI_SIMO, GPIO_OUTPUT, GPIO_PULLUP|GPIO_ASYNC);    ///< Enable pull-up && Asynch output
    GPIO_SetupPinMux(CMN_SPI_SOMI, GPIO_MUX_CPU1, MUX_OPTION_SPI_SOMI);         ///< GPIO64-SPISOMIA
    GPIO_SetupPinOptions(CMN_SPI_SOMI, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);     ///< Enable pull-up && Asynch input
    GPIO_SetupPinMux(CMN_SPI_CLK, GPIO_MUX_CPU1, MUX_OPTION_SPI_CLK);           ///< GPIO65-SPICLKA
    GPIO_SetupPinOptions(CMN_SPI_CLK, GPIO_OUTPUT, GPIO_PULLUP|GPIO_ASYNC);     ///< Enable pull-up && Asynch output
#if 0U
    GPIO_SetupPinMux(CMN_SPI_STE, GPIO_MUX_CPU1, 15U);                          ///< GPIO66-SPISTEB
    GPIO_SetupPinOptions(CMN_SPI_STE, GPIO_OUTPUT, GPIO_PULLUP|GPIO_ASYNC);     ///< Enable pull-up && Asynch output
#else
    GPIO_SetupPinMux(CMN_SPI_STE, GPIO_MUX_CPU1, MUX_OPTION_SPI_STE);           ///< GPIO66-SPISTEA
    GPIO_SetupPinOptions(CMN_SPI_STE, GPIO_OUTPUT, GPIO_PULLUP|GPIO_ASYNC);                ///< Enable pull-up && Asynch output
#endif
}

/**
* @brief   CAN GPIO initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_GpioCfg_Cmn_Can_Init(void)
{
#if 1
    /* GPIO12 & GPIO13 is set as CAN Pin */
    GPIO_SetupPinMux(13U, GPIO_MUX_CPU1, 2U);                  // GPIO13-CANB_RX
    GPIO_SetupPinOptions(13U, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);     // Enable pull-up && Asynch input
    GPIO_SetupPinMux(12U, GPIO_MUX_CPU1, 2U);                  // GPIO12-CANB_TX
#else
    /* GPIO62 & GPIO63 is set as CAN Pin */
    GPIO_SetupPinMux(62U, GPIO_MUX_CPU1, 6U);                  // GPIO62-CANA_RX
    GPIO_SetupPinOptions(62U, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);     // Enable pull-up && Asynch input
    GPIO_SetupPinMux(63U, GPIO_MUX_CPU1, 6U);                  // GPIO63-CANA_TX
#endif
}

/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : I2C GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Cmn_I2c_Init(void)
{
#if 0
    I2cAGpioConfig(I2C_A_GPIO0_GPIO1);    // I2C GPIO initialization
#endif
    /* GPIO0 is set as I2CA SDA */
    GPIO_SetupPinMux(CMN_I2C_SDA, GPIO_MUX_CPU1, MUX_OPTION_I2C_SDA);
    GPIO_SetupPinOptions(CMN_I2C_SDA, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);      ///< Enable pull-up && Asynch input
    /* GPIO1 is set as I2C SCL */
    GPIO_SetupPinMux(CMN_I2C_SCL, GPIO_MUX_CPU1, MUX_OPTION_I2C_SCL);
    GPIO_SetupPinOptions(CMN_I2C_SCL, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);      ///< Enable pull-up && Asynch input
    /* GPIO2 is set as I2C WP*/
    GPIO_SetupPinMux(CMN_I2C_WP, GPIO_MUX_CPU1, MUX_OPTION_I2C_WP);
    GPIO_SetupPinOptions(CMN_I2C_WP, GPIO_OUTPUT, GPIO_PUSHPULL);   ///< GPIO-2 Output
    IIC_WRITE_ENABLE;
}

/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : LED GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Cmn_Led_Init(void)
{
    /* GPIO62 is set as LED Drive on the Control Panel to display system fault */
    GPIO_SetupPinMux(DSP_FAULT_LED, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(DSP_FAULT_LED, GPIO_OUTPUT, GPIO_PUSHPULL);
    /* GPIO63 is set as LED Drive on the Control Panel to display system run */
    GPIO_SetupPinMux(DSP_RUN_LED, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(DSP_RUN_LED, GPIO_OUTPUT, GPIO_PUSHPULL);
}

/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : Hardware fault GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Cmn_HwFlt_Init(void)
{
    /* GPIO14 is set as Hardware Fault input signal */
    GPIO_SetupPinMux(CMN_FAULT_HW, GPIO_MUX_CPU1, 0U);                                     // GPIO24-GPIO
    GPIO_SetupPinOptions(CMN_FAULT_HW, GPIO_INPUT, GPIO_PULLUP|GPIO_QUAL_3SAMPLES);        // GPIO24-Input

    /* GPIO15 is set as output signal to reset Hardware Fault */
    GPIO_SetupPinMux(CMN_FAULT_RST, GPIO_MUX_CPU1, 0U);
    GPIO_SetupPinOptions(CMN_FAULT_RST, GPIO_OUTPUT, GPIO_PUSHPULL);
}

/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : Sci GPIO initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_GpioCfg_Cmn_Sci_Init(void)
{
    /* GPIO22 & GPIO23 is set as SCIB Pin */
    GPIO_SetupPinMux(CMN_SCI_TX, GPIO_MUX_CPU1, MUX_OPTION_SCI_TX);                  // GPIO22-SCIB_TX
    GPIO_SetupPinOptions(CMN_SCI_TX, GPIO_OUTPUT, GPIO_PULLUP|GPIO_ASYNC);     // Enable pull-up && Asynch Output
    GPIO_SetupPinMux(CMN_SCI_RX, GPIO_MUX_CPU1, MUX_OPTION_SCI_RX);                  // GPIO23-SCIB_RX
    GPIO_SetupPinOptions(CMN_SCI_RX, GPIO_INPUT, GPIO_PULLUP|GPIO_ASYNC);     // Enable pull-up && Asynch Input
}

static void v_GpioCfg_Cmn_Emif_Init(void)
{
    extern void setup_emif1_pinmux_async_16bit(Uint16 cpu_sel);
    setup_emif1_pinmux_async_16bit(0);      /*EMIF*/
}

static void v_GpioCfg_Cmn_WDog_Init(void)
{
    GPIO_SetupPinMux(CMN_FEED_DOG, GPIO_MUX_CPU1, 0U);                  // GPIO91
    GPIO_SetupPinOptions(CMN_FEED_DOG, GPIO_OUTPUT, GPIO_OPENDRAIN);     // Enable OPENDRAIN Output

    GPIO_SetupPinMux(CMN_OCP_A, GPIO_MUX_CPU1, 3U);                     // GPIO5 OUTPUTXBAR3 MUX5|7|9
    GPIO_SetupPinOptions(CMN_OCP_A, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(CMN_OCP_B, GPIO_MUX_CPU1, 0U);                     // GPIO6 OUTPUTXBAR4
    GPIO_SetupPinOptions(CMN_OCP_B, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(CMN_OCP_C, GPIO_MUX_CPU1, 0U);                     // GPIO7 OUTPUTXBAR5
    GPIO_SetupPinOptions(CMN_OCP_C, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(CMN_TEST4, GPIO_MUX_CPU1, 0U);                     // GPIO8
    GPIO_SetupPinOptions(CMN_TEST4, GPIO_OUTPUT, GPIO_PUSHPULL);     // Enable PUSHPULL Output
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
