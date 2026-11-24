//==============================================================================================
//    File description
//==============================================================================================
/**@file         XbarCfg.c
* TITLE         : Xbar configuration Source File
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
#include "XBarCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================

/**
* @brief   X-BAR initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_XBarCfg_Init(void)
{
//    v_XBarCfg_Pfc_Init();   ///< PFC Xbar initial
//    v_XBarCfg_D2d_Init();   ///< D2D Xbar initial
    v_XBarCfg_OCP_Init();
}

/**
* @brief   PFC X-BAR initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_XBarCfg_Pfc_Init(void)
{
    EALLOW;

    EPwmXbarRegs.TRIP7MUXENABLE.bit.MUX4 = 1;          //Enable channel 4 of TRIP7
    EPwmXbarRegs.TRIP7MUX0TO15CFG.bit.MUX4 = 0;        //TRIP7 Channel 4 Select CMPSS3.CTRIPOUTH
    EPwmXbarRegs.TRIP7MUXENABLE.bit.MUX5 = 1;          //Enable channel 5 of TRIP7
    EPwmXbarRegs.TRIP7MUX0TO15CFG.bit.MUX5 = 0;        //TRIP8 Channel 5 Select CMPSS3.CTRIPOUTL

    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX12 = 1;         //Enable channel 12 of TRIP4
    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX12 = 0;       //TRIP4 Channel 12 Select CMPSS7.CTRIPOUTH
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX14 = 1;         //Enable channel 14 of TRIP4
    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX14 = 0;       //TRIP4 Channel 14 Select CMPSS8.CTRIPOUTH

    InputXbarRegs.INPUT1SELECT = 62;//PFC-OCP
    InputXbarRegs.INPUT2SELECT = 73;//BUS-OVP

    EDIS;
}

/**
* @brief   D2D X-BAR initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_XBarCfg_D2d_Init(void)
{
    EALLOW;

    /* EPWM_XBAR Configuration */
    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX9 = 0x1U;     // TRIP5: Input Xbar 5
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX9 = 1U;         // Respective output of MUX9 is enabled to drive the TRIP5
    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX10 = 0x0U;    // TRIP5: CMPSS6.CTRIPH
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX10 = 1U;        // Respective output of MUX14 is enabled to drive the TRIP5
    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX11 = 0x0U;    // TRIP5: CMPSS6.CTRIPL
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX11 = 1U;        // Respective output of MUX15 is enabled to drive the TRIP5

    /* Clear X-BAR Flag */
    XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPH = 1U;         // Clear CMPSS6_CTRIPH Flag in X-BAR
    XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPL = 1U;         // Clear CMPSS6_CTRIPL Flag in X-BAR

    /* INPUT_XBAR Configuration */
    InputXbarRegs.INPUT5SELECT = 94U;                 // Set GPIO94 as Input5
    InputXbarRegs.INPUT13SELECT = 27U;                // Set GPIO27 as XINT4
    InputXbarRegs.INPUT14SELECT = 30U;                // Set GPIO30 as XINT5

    EDIS;
}

static void v_XBarCfg_OCP_Init(void)
{
    EALLOW;

    InputXbarRegs.INPUT3SELECT = 32;            //OCP_A
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX5 = 1;
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX5 = 1; //GPIO5

    InputXbarRegs.INPUT4SELECT = 29;            //OCP_B
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX7 = 1;
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX7 = 1; //GPIO5

    InputXbarRegs.INPUT5SELECT = 28;            //OCP_C
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX9 = 1;
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX9 = 1; //GPIO5

    OutputXbarRegs.OUTPUTINV.bit.OUTPUT3 = 1;

//    InputXbarRegs.INPUT4SELECT = 29;            //OCP_B
//    OutputXbarRegs.OUTPUT4MUX0TO15CFG.bit.MUX7 = 1;
//    OutputXbarRegs.OUTPUT4MUXENABLE.bit.MUX7 = 1; //GPIO6
//
//    InputXbarRegs.INPUT5SELECT = 28;            //OCP_C
//    OutputXbarRegs.OUTPUT5MUX0TO15CFG.bit.MUX9 = 1;
//    OutputXbarRegs.OUTPUT5MUXENABLE.bit.MUX9 = 1; //GPIO7

    EDIS;
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
