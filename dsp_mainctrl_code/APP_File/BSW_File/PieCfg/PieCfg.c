//==============================================================================================
//    File description
//==============================================================================================
/**@file         PieCfg.c
* TITLE         : Pie Configuration Source File
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
#include "PieCfg.h"

//=====================================================
//    Variable Definition
//=====================================================


//=====================================================
//    Function definition
//=====================================================
/**
* @brief   PIE initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_PieCfg_Init(void)
{
    InitPieCtrl();    // Initialize the PIE control registers

    IER = 0x0000U;    // Disable CPU interrupts
    IFR = 0x0000U;    // Clear all CPU interrupt flags

    InitPieVectTable();    // Initialize the PIE vector table

    v_PieCfg_Pfc_Init();
//    v_PieCfg_D2d_Init();
    v_PieCfg_Cmn_Init();
}

/***********************************************************************************************
* @Type         : Sub Unit function
* @brief        : PIE initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PieCfg_Pfc_Init(void)
{
#if 0U == FLG_SWUT_EN
    EALLOW;
    /* PFC ISR */
    /** control algorithm interrupt */
    PieVectTable.ADCA1_INT = &v_PerdTsk_Adc_ISR; //44.6us
    /** hardware protection interrupt */
#if(2U != GRID_PHASE_NUMBER)
    //PieVectTable.EPWM5_TZ_INT = &v_PfcDiag_ePwm_TZ_ISR;
#endif
    EDIS;
#endif
}

/***********************************************************************************************
* @Type         : Sub Unit function
* @brief        : PIE initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PieCfg_D2d_Init(void)
{
#if 0U == FLG_SWUT_EN
    EALLOW;
    /* D2D ISR */
//    PieVectTable.EPWM6_INT = &vEpwm6Isr;
    //PieVectTable.EPWM7_TZ_INT = &v_D2dDiag_EpwmTz_Hw_Isr;
    //PieVectTable.XINT4_INT = &v_D2dDiag_XInt_PriUpOC_Isr;
//    PieVectTable.XINT5_INT = &v_D2dDiag_XInt5Isr;
    EDIS;
#endif
}

/***********************************************************************************************
* @Type         : Sub Unit function
* @brief        : PIE initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_PieCfg_Cmn_Init(void)
{
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;     // ADCA1
    IER |= M_INT1;
    //PieCtrlRegs.PIEIER2.bit.INTx5 = 1;     // EPWM5 TZ int
//    PieCtrlRegs.PIEIER3.bit.INTx6 = 1U;    // EPWM6_INT(3.6)
//    IER |= M_INT3;                         // GROUP3
    //PieCtrlRegs.PIEIER2.bit.INTx7 = 1U;    // EPWM7_TZ_INT(2.7)
    //IER |= M_INT2;                         // GROUP2
    //XintRegs.XINT4CR.bit.POLARITY = 0U;    // XINT4: negative edge triggered
    //XintRegs.XINT4CR.bit.ENABLE = 1U;    // XINT4: Enable
    //PieCtrlRegs.PIEIER12.bit.INTx2 = 1U;    // XINT4_INT(12.2)
//    XintRegs.XINT5CR.bit.POLARITY = 0U;    // XINT5: negative edge triggered
//    XintRegs.XINT5CR.bit.ENABLE = 1U;    // XINT5: Enable
//    PieCtrlRegs.PIEIER12.bit.INTx3 = 1U;    // XINT5_INT(12.3)
    //IER |= M_INT12;                         // GROUP2
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : FCT PWM test PIE configuration function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_PieCfg_Cmn_FctPwm(void)
{
    PieCtrlRegs.PIEIER2.bit.INTx5  = 0U;    ///< Disable EPWM5 TZ
    PieCtrlRegs.PIEIER2.bit.INTx7  = 0U;    ///< Disable EPWM7_TZ_INT(2.7)
    PieCtrlRegs.PIEIER12.bit.INTx2 = 0U;    ///< Disable XINT4_INT(12.2)
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
