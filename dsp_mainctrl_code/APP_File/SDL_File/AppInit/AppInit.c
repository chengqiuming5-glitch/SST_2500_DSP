//==============================================================================================
//    File description
//==============================================================================================
/**@file         AppInit.c
 * @brief
 * The source file of AppInit is designed to initialize APP Source File.
 *
 * Module      :                 \n
 * AppInit
 *
 * Unit        :                 \n
 * null
 *
 * Unit Task   :                 \n
 * v_AppInit_BSW_Cfg()           \n
 * v_AppInit_CDD_Drv()           \n
 * v_AppInit_ASW_Modl()          \n
 * v_AppInit_SDL_Tsk()           \n
 *
 * Unit Task   :                 \n
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
#include "AppInit.h"
#include "F2837xD_Examples.h"
#include "F2837xD_Ipc_drivers.h"

//=====================================================
//    Variable Definition
//=====================================================


//=====================================================
//    Function definition
//=====================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : APP initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
/********************************************Begin*********************************************/
void v_AppInit(void)
{
    v_AppInit_SDL_Tsk();             ///< Initialize SDL task
    v_AppInit_BSW_Cfg();             ///< Initialize BSW Configure
    v_AppInit_CDD_Drv();             ///< Initialize CDD driver
    DELAY_US_APP(50000.0f);          ///< Delay 50ms

    v_Com_NonEraPrm_Init();          ///< Non erasable parameter Initial
    v_AppInit_ASW_Modl();            ///< Initialize ASW module
    v_Eep_RcvPrm();                  ///< Read parameter from EEPROM
    v_Com_Rx_Tsk_EepPrmUpd();        ///< EEPROM related parameter update

    EALLOW;
    Cla1Regs.MIFRC.bit.INT7 = 1U;    ///< asm(" IACK #0x0080"); one time initialization task
    EDIS;

    StartCpuTimer0();    			 ///< Start CpuTimer0
#if 1U == FLG_RUN_TIME_TEST_EN
    StartCpuTimer1();                ///< Start CpuTimer1
#endif

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1U;    ///< Turn on EPWM Time-Base clock
    EDIS;

//    v_EPwmDrv_Pfc_TurnOff();         ///< Turn off PFC Drive
#if(3U == GRID_PHASE_NUMBER)
//    v_EPwmDrv_Pfc_ClrTzFlg();
#endif
//    v_EPwmDrv_D2d_TurnOff();         ///< Turn off D2D Drive
//    v_EPwmDrv_D2d_ClrTzFlg();        ///< Clear D2D EPWM TZ Flag
    v_SysCfg_EnableDog();    	     ///< Enable WatchDog

    EINT;    ///< Enable Global interrupt INTM
    ERTM;    ///< Enable Global realtime interrupt DBGM
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: BSW Configure initialization function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_AppInit_BSW_Cfg(void)
{
#ifndef _SIMULATION_NO_DSP_
    v_SysCfg_Init();     ///< Initialize System
    v_GpioCfg_Init();    ///< Initialize GPIO
    v_TmrCfg_Init();     ///< Initialize CpuTimers
    v_AdcCfg_Init();     ///< Initialize ADC and DAC
    v_CmpssCfg_Init();   ///< Initialize CMPSS
    v_XBarCfg_Init();    ///< Initialize XBar
    v_EPwmCfg_Init();    ///< Initialize EPWM
    v_ECapCfg_Init();    ///< Initialize ECAP
    v_I2cCfg_Init();     ///< Initialize I2C
    v_ClaCfg_Init();     ///< Initialize CLA
#if(1U == FLG_CPU2_UPD_EN)
    (void)IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#endif
    v_PieCfg_Init();     ///< Initialize PIE
#if(0U == COM_MODE)
    v_SciCfg_Init();     ///< Initialize Sci
#else
    v_CanCfg_Init();     ///< Initialize Can
#endif
    v_EmifCfg_Init();    ///< Initialize Emif
    v_DmaCfg_Init();     ///< Initialize Dma
#if 1U == FLG_FLT_DATA_REC_EN 
    v_SpiCfg_Init();     ///< Initialize SPI
#endif
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: CDD drive initialization function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_AppInit_CDD_Drv(void)
{
    v_AdcDrv_Init();             ///< Initialize AdcDrv
#if(0U == COM_MODE)
    v_SciDrv_Init();             ///< Initialize ComDrv
#else
    v_ComDrv_Init();             ///< Initialize ComDrv
#endif
#ifndef SST_1250kW
    v_EPwmDrv_Init();            ///< Initialize EPwmDrv
#endif
    v_ECapDrv_Init();            ///< Initialize ECapDrv
    v_PerphDrv_Init();           ///< Initialize PerphDrv
    v_EepDrv_Init();             ///< Initialize EepDrv
#if 1U == FLG_FLT_DATA_REC_EN    
    v_SpiDrv_Init();             ///< Initialize SpiDrv
#endif
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: ASW module initialization function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_AppInit_ASW_Modl(void)
{
    v_Com_Init();              ///< 1st Init: Module Com
    v_ComIf_Init();            ///< 2nd Init: Module ComIf
    v_CmnAdc_Init();           ///< 3rd Init: Module CmnAdc
    v_PfcAdc_Init();           ///< 4th Init: Module PfcAdc
    v_D2dAdc_Init();           ///< 5th Init: Module D2dAdc
    v_PfcDataCalc_Init();      ///< 6th Init: Module PfcDataCalc
    v_CmnDiag_Init();          ///< 7th Init: Module CmnDiag
    v_PfcDiag_Init();          ///< 8th Init: Module PfcDiag
    v_D2dDiag_Init();          ///< 9th Init: Module D2dDiag
    v_PfcStMac_Init();         ///< 10th Init: Module PfcStMac
    v_D2dStMac_Init();         ///< 11th Init: Module D2dStMac
    v_PerphCtrl_Init();        ///< 12th Init: Module PerphCtrl
    v_PowLim_Init();           ///< 13th Init: Module PowLim
    v_PfcGridCtrl_Init();      ///< 14th Init: Module PfcGridCtrl
    v_PfcPowPreCtrl_Init();    ///< 15th Init: Module PfcPowPreCtrl
    v_PfcPowCtrl_Init();       ///< 16th Init: Module PfcPowCtrl
    v_D2dPowPreCtrl_Init();    ///< 17th Init: Module D2dPowPreCtrl
    v_D2dPowCtrl_Init();       ///< 18th Init: Module D2dPowCtrl
    v_Eep_Init();              ///< 19th Init: Module Eep
    v_SwVers_Init();           ///< 20th Init: Module SwVers
    v_PrmDisp_Init();          ///< 21th Init: Module PrmDisp
#if 1U == FLG_FLT_DATA_REC_EN  
    v_Spi_Init();              ///< 22th Init: Module Spi
    v_FltDataRec_Init();       ///< 23th Init: Module FltDataRec
#endif
#if 1U == FLG_FLT_RSTRT_EN
    v_FltRstrt_Init();         ///< 24th Init: Module FltRstrt
#endif
#if 1U == FLG_ON_OFF_GRID_SWT_EN
    v_OnOffGridSwt_Init();     ///< 25th Init: Module OnOffGridSwt
#endif
    v_Emif_Init();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Module function: SDL task initialization function
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_AppInit_SDL_Tsk(void)
{
    v_PerdTsk_Init();
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================

