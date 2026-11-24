//==============================================================================================
//    File description
//==============================================================================================
/**@file         SysCfg.c
* TITLE         : System configuration Source File
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
#include "SysCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : System initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SysCfg_Init(void)
{
    InitSysCtrl();    ///< Initialize System Clock
    DisableDog();     ///< Disable Watchdog
    DINT;             ///< Disable CPU interrupts

    v_SysCfg_CpuSel_Init();    ///< Configure the peripheral permissions of CPU1 and CPU2
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : WatchDog Configuration and Enable initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SysCfg_EnableDog(void)
{
    EALLOW;
    WdRegs.WDCR.all = 0x0028U;   ///< Enable WatchDog; Period = 256/(10MHz/512/1) = 13.11ms
    EDIS;
}

/***********************************************************************************************
* @Type         : Unit function
* @brief        : CPU Selection Initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SysCfg_CpuSel_Init(void)
{
    EALLOW;
    DevCfgRegs.CPUSEL0.bit.EPWM1   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM2   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM3   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM4   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM5   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM6   = PWR_CPU;       ///< CPU1
    DevCfgRegs.CPUSEL0.bit.EPWM7   = PWR_CPU;
    DevCfgRegs.CPUSEL0.bit.EPWM8   = PWR_CPU;
    DevCfgRegs.CPUSEL0.bit.EPWM9   = PWR_CPU;
    DevCfgRegs.CPUSEL0.bit.EPWM10  = PWR_CPU;
    DevCfgRegs.CPUSEL0.bit.EPWM11  = PWR_CPU;
    DevCfgRegs.CPUSEL0.bit.EPWM12  = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP1   = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP2   = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP3   = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP4   = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP5   = PWR_CPU;
    DevCfgRegs.CPUSEL1.bit.ECAP6   = PWR_CPU;
    DevCfgRegs.CPUSEL5.bit.SCI_A   = PWR_CPU;
    DevCfgRegs.CPUSEL5.bit.SCI_B   = PWR_CPU;
    DevCfgRegs.CPUSEL5.bit.SCI_C   = PWR_CPU;
    DevCfgRegs.CPUSEL5.bit.SCI_D   = SAF_CPU;       ///< CPU2
    DevCfgRegs.CPUSEL8.bit.CAN_B   = PWR_CPU;
    DevCfgRegs.CPUSEL11.bit.ADC_A  = PWR_CPU;
    DevCfgRegs.CPUSEL11.bit.ADC_B  = PWR_CPU;
    DevCfgRegs.CPUSEL11.bit.ADC_C  = PWR_CPU;
    DevCfgRegs.CPUSEL11.bit.ADC_D  = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS1 = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS2 = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS5 = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS6 = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS7 = PWR_CPU;
    DevCfgRegs.CPUSEL12.bit.CMPSS8 = PWR_CPU;
    /* CPU global RAM configuration */
    MemCfgRegs.GSxMSEL.bit.MSEL_GS0  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS1  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS2  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS3  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS4  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS5  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS6  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS7  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS8  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS9  = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS10 = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS11 = PWR_CPU;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = PWR_CPU;

    MemCfgRegs.GSxMSEL.bit.MSEL_GS13 = SAF_CPU;     ///< CPU2
    MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = SAF_CPU;     ///< CPU2
    MemCfgRegs.GSxMSEL.bit.MSEL_GS15 = SAF_CPU;     ///< CPU2
    EDIS;
#if(1U == GRID_PHASE_NUMBER)
    /* Give CPU2 control of GPIO53 and set it as safety led */
    GPIO_SetupPinMux(53,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(53, GPIO_OUTPUT,0);
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
