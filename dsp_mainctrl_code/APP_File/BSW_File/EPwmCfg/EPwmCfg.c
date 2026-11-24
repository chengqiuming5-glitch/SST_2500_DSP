//==============================================================================================
//    File description
//==============================================================================================
/**@file         EpwmCfg.c
* TITLE         : Epwm configuration source file
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
#include "EPwmCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_EPwmCfg_Init(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    v_EPwmCfg_Pfc_Init();    ///< PFC EPWM Initial
#ifndef SST_1250kW
    v_EPwmCfg_D2d_Init();    ///< D2D EPWM Initial
#endif
}

/**
* @brief   PFC EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_Pfc_Init(void)
{
    v_EPwmCfg_Pfc_PhaA_Init();                ///< PFC Phase A trigger ADC sample
}

/**
* @brief   PFC EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_Pfc_PhaD_Init(void)
{
     //-------------------
     //initialize ePWM1
     //-------------------
     //-------------------
     //TB module
     EALLOW;
     EPwm1Regs.TBPRD  = PERIOD_BAL_PWM;
     EPwm1Regs.TBCTR  = 0x0000;                      // Time base counter cleared to zero(TBCTR)
     EPwm1Regs.TBPHS.bit.TBPHS = 0;
     EPwm1Regs.TBCTL.bit.CTRMODE  = TB_COUNT_UPDOWN;
     EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;         // Mapping mode
     EPwm1Regs.TBCTL2.bit.PRDLDSYNC = 0x0;          // TBPRD is loaded from the shadow register when CTR=0
     EPwm1Regs.TBCTL.bit.PHSEN  = TB_DISABLE;       // Load TBPHS to TBCTR when synchronization is enabled
     EPwm1Regs.TBCTL.bit.PHSDIR = TB_DOWN;          // Count down during synchronization
     EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
     EPwm1Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
     EPwm1Regs.TBCTL.bit.CLKDIV   = TB_DIV1;
     //CMP module
     EPwm1Regs.CMPA.bit.CMPA = (0);
     EPwm1Regs.CMPB.bit.CMPB = (0);
     EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
     EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;    // CMPA is loaded when TBCTR=PRD
     EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
     EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    // CMPB is loaded when TBCTR=PRD
     //AQ module
     EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
     EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
     //DB module
     EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both rising and falling edges are enabled
     EPwm1Regs.DBCTL.bit.IN_MODE  = DBA_ALL;         // Both rising and falling edge input sources are EPWMA
     EPwm1Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;     // High level Complementation (AHC),EPWMxB inverting
     EPwm1Regs.DBRED.bit.DBRED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);
     EPwm1Regs.DBFED.bit.DBFED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);

     //DC module
     EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 0x6;          // DCAH = TRIPIN7
     EPwm1Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;          // DCAEVT1.force=DCAEVT2(unfiltered)
     EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; // DCAEVT2 Asynchronous signal source
     EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 0x6;          // DCBH = TRIPIN7
     EPwm1Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;          // DCBEVT1.force=DCBEVT2(unfiltered)
     EPwm1Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; // DCBEVT2 Asynchronous signal source

     //TZ module
     EPwm1Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;          // DCAEVT1 = DCAH high
     EPwm1Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;          // DCBEVT1 = DCBH high
     EPwm1Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;             // Enable DCAEVT2.force to serve as the TZ_CBC source
     EPwm1Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;             // Enable DCBEVT2.force to serve as the TZ_CBC source
     EPwm1Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;           // EPWMxA is forced to be in the low state
     EPwm1Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;           // EPWMxB is forced to be in the low state
     EPwm1Regs.TZEINT.bit.DCAEVT2 = 0;                    // Disable DCAEVT2 as TZ interrupt
     EPwm1Regs.TZEINT.bit.DCBEVT2 = 0;                    // Disable DCBEVT2 as TZ interrupt

     EPwm1Regs.TZSEL.bit.OSHT1 = 1;                         // Description OSHT1 was enabled as the TZ_OST source
     EPwm1Regs.TZSEL.bit.OSHT2 = 1;                         // Description OSHT2 was enabled as the TZ_OST source
     EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;                 //The pin is forced to be low when a TZ event occurs
     EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
     EPwm1Regs.TZFRC.bit.OST = 1;                           // The OST is forcibly generated

     EPwm1Regs.ETSEL.bit.SOCAEN  = 1;                     // enable SOC on A group
     EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;            // Select SOC on 0
     EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;                 // Generate pulse on 1st event

     EDIS;

}

/**
* @brief   Turn off All PFC Drive function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_Pfc_PhaA_Init(void)
{
    //-------------------
     //initialize ePWM2
     //-------------------
     //-------------------
     //TB module
     EALLOW;
     EPwm2Regs.TBPRD = PERIOD_PFC_PWM;
     EPwm2Regs.TBCTR  = 0x0000;                     // Time base counter cleared to zero(TBCTR)
     EPwm2Regs.TBPHS.bit.TBPHS = 0;
     EPwm2Regs.TBCTL.bit.CTRMODE  = TB_COUNT_UPDOWN;
     EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;         // Mapping mode
     EPwm2Regs.TBCTL2.bit.PRDLDSYNC = 0x0;          // TBPRD is loaded from the shadow register when CTR=0
     EPwm2Regs.TBCTL.bit.PHSEN  = TB_DISABLE;       // Load TBPHS to TBCTR when synchronization is enabled
     EPwm2Regs.TBCTL.bit.PHSDIR = TB_DOWN;          // Count down during synchronization
     EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
     EPwm2Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
     EPwm2Regs.TBCTL.bit.CLKDIV   = TB_DIV1;
     //CMP module
     EPwm2Regs.CMPA.bit.CMPA = (0);
     EPwm2Regs.CMPB.bit.CMPB = (0);
     EPwm2Regs.CMPC = 500;
     EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
     EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;    // CMPA is loaded when TBCTR=PRD
     EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
     EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    // CMPB is loaded when TBCTR=PRD
     //AQ module
     EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
     EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
     //DB module
     EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both rising and falling edges are enabled
     EPwm2Regs.DBCTL.bit.IN_MODE  = DBA_ALL;         // Both rising and falling edge input sources are EPWMA
     EPwm2Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;     // High level Complementation (AHC),EPWMxB inverting
     EPwm2Regs.DBRED.bit.DBRED  = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);
     EPwm2Regs.DBFED.bit.DBFED  = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);

     //DC module
     EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 0x3;          // DCAH = TRIPIN4
     EPwm2Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;          // DCAEVT1.force=DCAEVT1(unfiltered)
     EPwm2Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; // DCAEVT1 Asynchronous signal source
     EPwm2Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 0x3;          // DCBH = TRIPIN4
     EPwm2Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;          // DCBEVT1.force=DCBEVT1(unfiltered)
     EPwm2Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; // DCBEVT1 Asynchronous signal source
     //TZ module
     EPwm2Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;          // DCAEVT1 = DCAH high
     EPwm2Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;          // DCBEVT1 = DCBH high
     EPwm2Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;             // Enable DCAEVT2.force to serve as the TZ_CBC source
     EPwm2Regs.TZSEL.bit.DCBEVT2 = TZ_DISABLE;             // Enable DCBEVT2.force to serve as the TZ_CBC source
     EPwm2Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;           // EPWMxA is forced to be in the low state
     EPwm2Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;           // EPWMxB is forced to be in the low state
     EPwm2Regs.TZEINT.bit.DCAEVT2 = 0;                    // Disable DCAEVT2 as TZ interrupt
     EPwm2Regs.TZEINT.bit.DCBEVT2 = 0;                    // Disable DCBEVT2 as TZ interrupt

     EPwm2Regs.TZSEL.bit.OSHT1 = 1;                       // Description OSHT1 was enabled as the TZ_OST source
     EPwm2Regs.TZSEL.bit.OSHT2 = 1;                       // Description OSHT2 was enabled as the TZ_OST source
     EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;               // The pin is forced to be low when a TZ event occurs
     EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

     EPwm2Regs.TZFRC.bit.OST = 1;                         // The OST is forcibly generated
     EPwm2Regs.TZCLR.bit.CBCPULSE = 1;                    // CTR=0/PRD clear CBC

     EPwm2Regs.ETSEL.bit.SOCAEN  = 1;                     // enable SOC on A group
     EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;            // Select SOC on 0
     EPwm2Regs.ETPS.bit.SOCAPRD = ET_2ND;                 // Generate pulse on 1st event

     EDIS;
}

/**
* @brief   Turn off All PFC Drive function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_Pfc_PhaB_Init(void)
{
    //-------------------
     //initialize ePWM3
     //-------------------
     //-------------------
     //TB module
     EALLOW;
     EPwm3Regs.TBPRD  = PERIOD_PFC_PWM;
     EPwm3Regs.TBCTR  = 0x0000;                // Time base counter cleared to zero(TBCTR)
     EPwm3Regs.TBPHS.bit.TBPHS = 0;
     EPwm3Regs.TBCTL.bit.CTRMODE  = TB_COUNT_UPDOWN;
     EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;         // Mapping mode
     EPwm3Regs.TBCTL2.bit.PRDLDSYNC = 0x0;          // TBPRD is loaded from the shadow register when CTR=0
     EPwm3Regs.TBCTL.bit.PHSEN  = TB_DISABLE;       // Load TBPHS to TBCTR when synchronization is enabled
     EPwm3Regs.TBCTL.bit.PHSDIR = TB_DOWN;          // Count down during synchronization
     EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
     EPwm3Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
     EPwm3Regs.TBCTL.bit.CLKDIV   = TB_DIV1;
     //CMP module
     EPwm3Regs.CMPA.bit.CMPA = (0);
     EPwm3Regs.CMPB.bit.CMPB = (0);
     EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
     EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;    // CMPA is loaded when TBCTR=PRD
     EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
     EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    // CMPB is loaded when TBCTR=PRD
     //AQ module
     EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
     EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
     //DB module
     EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both rising and falling edges are enabled
     EPwm3Regs.DBCTL.bit.IN_MODE  = DBA_ALL;         // Both rising and falling edge input sources are EPWMA
     EPwm3Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;     // High level Complementation (AHC),EPWMxB inverting
     EPwm3Regs.DBRED.bit.DBRED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);
     EPwm3Regs.DBFED.bit.DBFED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);

     //DC module
     EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 0x3;          //DCAH = TRIPIN4
     EPwm3Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;          //DCAEVT1.force=DCAEVT1(unfiltered)
     EPwm3Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; //DCAEVT1 Asynchronous signal source
     EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 0x3;          //DCBH = TRIPIN4
     EPwm3Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;          //DCBEVT1.force=DCBEVT1(unfiltered)
     EPwm3Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; //DCBEVT1 Asynchronous signal source
     //TZ module
     EPwm3Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;          // DCAEVT1 = DCAH high
     EPwm3Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;          // DCBEVT1 = DCBH high
     EPwm3Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;             // Enable DCAEVT2.force to serve as the TZ_CBC source
     EPwm3Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;             // Enable DCBEVT2.force to serve as the TZ_CBC source
     EPwm3Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;           // EPWMxA is forced to be in the low state
     EPwm3Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;           // EPWMxB is forced to be in the low state
     EPwm3Regs.TZEINT.bit.DCAEVT2 = 0;                    // Disable DCAEVT2 as TZ interrupt
     EPwm3Regs.TZEINT.bit.DCBEVT2 = 0;                    // Disable DCBEVT2 as TZ interrupt

     EPwm3Regs.TZSEL.bit.OSHT1 = 1;                       // Description OSHT1 was enabled as the TZ_OST source
     EPwm3Regs.TZSEL.bit.OSHT2 = 1;                       // Description OSHT2 was enabled as the TZ_OST source
     EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;               // The pin is forced to be low when a TZ event occurs
     EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
     EPwm3Regs.TZFRC.bit.OST = 1;                         // The OST is forcibly generated
     EPwm3Regs.TZCLR.bit.CBCPULSE = 1;                    // CTR=0/PRD clear CBC

     EDIS;

}

/**
* @brief   Turn off All PFC Drive function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_Pfc_PhaC_Init(void)
{
    //-------------------
     //initialize ePWM4
     //-------------------
     //-------------------
     //TB module
     EALLOW;
     EPwm4Regs.TBPRD = PERIOD_PFC_PWM;
     EPwm4Regs.TBCTR  = 0x0000;                     // Time base counter cleared to zero(TBCTR)
     EPwm4Regs.TBPHS.bit.TBPHS = 0;
     EPwm4Regs.TBCTL.bit.CTRMODE  = TB_COUNT_UPDOWN;
     EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;         // Mapping mode
     EPwm4Regs.TBCTL2.bit.PRDLDSYNC = 0x0;          // TBPRD is loaded from the shadow register when CTR=0
     EPwm4Regs.TBCTL.bit.PHSEN  = TB_DISABLE;       // Load TBPHS to TBCTR when synchronization is enabled
     EPwm4Regs.TBCTL.bit.PHSDIR = TB_DOWN;          // Count down during synchronization
     EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
     EPwm4Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
     EPwm4Regs.TBCTL.bit.CLKDIV   = TB_DIV1;
     //CMP module
     EPwm4Regs.CMPA.bit.CMPA = (0);
     EPwm4Regs.CMPB.bit.CMPB = (0);
     EPwm4Regs.CMPC = 500;
     EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
     EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;    // CMPA is loaded when TBCTR=PRD
     EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
     EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;    // CMPB is loaded when TBCTR=PRD
    //AQ module
     EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
     EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
     //DB module
     EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both rising and falling edges are enabled
     EPwm4Regs.DBCTL.bit.IN_MODE  = DBA_ALL;         // Both rising and falling edge input sources are EPWMA
     EPwm4Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;     // High level Complementation (AHC),EPWMxB inverting
     EPwm4Regs.DBRED.bit.DBRED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);
     EPwm4Regs.DBFED.bit.DBFED    = (Uint16)((float32)PFC_PWM_DEADTIME * 0.1f);

     //DC module
     EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 0x3;           // DCAH = TRIPIN4
     EPwm4Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;           // DCAEVT1.force=DCAEVT1(unfiltered)
     EPwm4Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;  // DCAEVT1 Asynchronous signal source
     EPwm4Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 0x3;           // DCBH = TRIPIN4
     EPwm4Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;           // DCBEVT1.force=DCBEVT1(unfiltered)
     EPwm4Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;  // DCBEVT1 Asynchronous signal source
     //TZ module
     EPwm4Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;          // DCAEVT1 = DCAH high
     EPwm4Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCBH_HI;          // DCBEVT1 = DCBH high
     EPwm4Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;             // Enable DCAEVT2.force to serve as the TZ_CBC source
     EPwm4Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;             // Enable DCBEVT2.force to serve as the TZ_CBC source
     EPwm4Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;           // EPWMxA is forced to be in the low state
     EPwm4Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;           // EPWMxB is forced to be in the low state
     EPwm4Regs.TZEINT.bit.DCAEVT2 = 0;                    // Disable DCAEVT2 as TZ interrupt
     EPwm4Regs.TZEINT.bit.DCBEVT2 = 0;                    // Disable DCBEVT2 as TZ interrupt

     EPwm4Regs.TZSEL.bit.OSHT1 = 1;                       // Description OSHT1 was enabled as the TZ_OST source
     EPwm4Regs.TZSEL.bit.OSHT2 = 1;                       // Description OSHT2 was enabled as the TZ_OST source
     EPwm4Regs.TZCTL.bit.TZA = TZ_FORCE_LO;               // The pin is forced to be low when a TZ event occurs
     EPwm4Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
     EPwm4Regs.TZFRC.bit.OST = 1;                         // The OST is forcibly generated
     EPwm4Regs.TZCLR.bit.CBCPULSE = 1;                    // CTR=0/PRD clear CBC

     EDIS;
}
#if(1U == GRID_PHASE_NUMBER)
/***********************************************************************************************
* @Type         : Sub-Unit function
* @brief        : D2D EPWM CBC configuration function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_EPwmCfg_Pfc_Slow_CBC_Cfg(void)
{
    if(OFFGRID_MODE == stCom.uiModRunReq)
    {
        EALLOW;
        PFC_SLOW_PWM.TZSEL.bit.DCAEVT2 = TZ_DISABLE;      ///< Disable DCAETV2.force as TZ_CBC source;
        PFC_SLOW_PWM.TZSEL.bit.DCBEVT2 = TZ_DISABLE;      ///< Disable DCBEVT2.force as TZ_CBC source;
        EDIS;
    }
    else
    {
        EALLOW;
        PFC_SLOW_PWM.TZSEL.bit.DCAEVT2 = TZ_ENABLE;       ///< Enable DCAETV2.force as TZ_CBC source;
        PFC_SLOW_PWM.TZSEL.bit.DCBEVT2 = TZ_ENABLE;       ///< Enable DCBEVT2.force as TZ_CBC source;
        EDIS;
    }
}
#endif
/**
* @brief   Turn off All PFC Drive function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_EPwmCfg_Pfc_TzTrig_Init(void)
{
   EALLOW;
   EPwm5Regs.TZSEL.bit.OSHT1 = 1;            ///< TZ OSHT1 register init
   EPwm5Regs.TZSEL.bit.OSHT2 = 1;            ///< TZ OSHT2 register init
   EPwm5Regs.TZCTL.bit.TZA = TZ_NO_CHANGE;   ///< TZ control register init
   EPwm5Regs.TZCTL.bit.TZB = TZ_NO_CHANGE;
   EPwm5Regs.TZEINT.bit.OST   = 1;
   EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_Init(void)
{
#if 0
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0U;    // Turn off EPWM Time-Base clock
    EDIS;

    v_EPwmCfg_D2d_PriBrdgL_Init();     ///< D2D PriBrdgL_Init
    v_EPwmCfg_D2d_PriBrdgR_Init();     ///< D2d_PriBrdgR_Init
    v_EPwmCfg_D2d_SecUpBrdgL_Init();   ///< D2d_SecUpBrdgL_Init
    v_EPwmCfg_D2d_SecUpBrdgR_Init();   ///< D2d_SecUpBrdgR_Init
    v_EPwmCfg_D2d_SecDwnBrdgL_Init();  ///< D2d_SecDwnBrdgL_Init
    v_EPwmCfg_D2d_SecDwnBrdgR_Init();  ///< D2d_SecDwnBrdgR_Init
    v_EPwmCfg_D2d_ClaPerd_Init();
    v_EPwmDrv_D2d_TurnOff();
#endif
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_PriBrdgL_Init(void)
{
    EALLOW;
    /* Primary Left Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_PRI_BDGL);
    EPWM_PRI_BDGL.TBCTL.bit.PHSEN = TB_ENABLE;    // Load TBCTR from TBPHS
    EPWM_PRI_BDGL.TBPHS.bit.TBPHS = 2U;    // Phase Offset
    EPWM_PRI_BDGL.TBCTL.bit.SYNCOSEL = 0U;    // Set EPWMxSYNCOUT signal when EPWMxSYNCI / SWFSYNC
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_PriBrdgR_Init(void)
{
    EALLOW;
    /* Primary Right Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_PRI_BDGR);
    EPWM_PRI_BDGR.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable Load TBCTR from TBPHS
    EPWM_PRI_BDGR.TBCTL.bit.SYNCOSEL = 1U;    // Set EPWMxSYNCOUT signal when TBCTR = 0
    EPWM_PRI_BDGR.TZEINT.bit.DCAEVT1 = 1U;    // Enable DCAEVT1 Interrupt
    EPWM_PRI_BDGR.TZCLR.bit.DCAEVT1 = 1U;    // Clear DCAEVT1 flag
    EPWM_PRI_BDGR.TZCLR.bit.INT = 1U;    // Clear INT flag
    EPWM_PRI_BDGR.CMPC = PERD_EPWM_DFT>>2;    // Set CMPC to Generate SOCA;PERD_EPWM_DFT>>3
    EPWM_PRI_BDGR.ETSEL.bit.SOCAEN = 1U;               // Enable EPWM7SOCA
    EPWM_PRI_BDGR.ETSEL.bit.SOCASEL = ET_CTRU_CMPA;    // Enable EPWM7SOCA at TBCTR = CMPA or CMPC when the timer is incrementing
    EPWM_PRI_BDGR.ETSEL.bit.SOCASELCMP = 1U;           // Enable EPWMxSOCA at TBCTR = CMPC
    EPWM_PRI_BDGR.ETPS.bit.SOCAPRD = ET_1ST;           // Generate EPWMxSOCA pulse on first event
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_SecUpBrdgL_Init(void)
{
    EALLOW;
    /* Secondary Up Left Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_SEC_UP_BDGL);
    EPWM_SEC_UP_BDGL.TBCTL.bit.PHSEN = TB_ENABLE;    // Load TBCTR from TBPHS
    EPWM_SEC_UP_BDGL.TBPHS.bit.TBPHS = 2U;    // Phase Offset
    EPWM_SEC_UP_BDGL.TBCTL.bit.SYNCOSEL = 0U;    // Set EPWMxSYNCOUT signal when EPWMxSYNCI / SWFSYNC
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_SecUpBrdgR_Init(void)
{
    EALLOW;
    /* Secondary Up Right Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_SEC_UP_BDGR);
    EPWM_SEC_UP_BDGR.TBCTL.bit.PHSEN = TB_ENABLE;    // Load TBCTR from TBPHS
    EPWM_SEC_UP_BDGR.TBPHS.bit.TBPHS = 2U;    // Phase Offset
    EPWM_SEC_UP_BDGR.TBCTL.bit.SYNCOSEL = 0U;    // Set EPWMxSYNCOUT signal when EPWMxSYNCI / SWFSYNC
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_SecDwnBrdgL_Init(void)
{
    EALLOW;
    /* Secondary Down Left Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_SEC_DN_BDGL);
    EPWM_SEC_DN_BDGL.EPWMXLINK.bit.CMPALINK = EPWM_SEC_BDGL_CMP_LINK_NUM;
    EPWM_SEC_DN_BDGL.EPWMXLINK.bit.CMPBLINK = EPWM_SEC_BDGL_CMP_LINK_NUM;
    SyncSocRegs.SYNCSELECT.bit.EPWM10SYNCIN = 2U;    // EPPW7SYNCOUT selected for Sync Input Source of EPWM10
    EPWM_SEC_DN_BDGL.TBCTL.bit.PHSEN = TB_ENABLE;    // Load TBCTR from TBPHS
    EPWM_SEC_DN_BDGL.TBPHS.bit.TBPHS = 2U;    // Phase Offset
    EPWM_SEC_DN_BDGL.TBCTL.bit.SYNCOSEL = 0U;    // Set EPWMxSYNCOUT signal when EPWMxSYNCI / SWFSYNC
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_SecDwnBrdgR_Init(void)
{
    EALLOW;
    /* Secondary Down Right Bridge EPWM Initial Configuration */
#if 3U == GRID_PHASE_NUMBER
    v_EPwmCfg_D2d_Cmn_Init(&EPWM_SEC_DN_BDGR);
    EPWM_SEC_DN_BDGR.EPWMXLINK.bit.CMPALINK = EPWM_SEC_BDGR_CMP_LINK_NUM;
    EPWM_SEC_DN_BDGR.EPWMXLINK.bit.CMPBLINK = EPWM_SEC_BDGR_CMP_LINK_NUM;
    EPWM_SEC_DN_BDGR.TBCTL.bit.PHSEN = TB_ENABLE;    // Load TBCTR from TBPHS
    EPWM_SEC_DN_BDGR.TBPHS.bit.TBPHS = 2U;    // Phase Offset
    EPWM_SEC_DN_BDGR.TBCTL.bit.SYNCOSEL = 0U;    // Set EPWMxSYNCOUT signal when EPWMxSYNCI / SWFSYNC
#endif
    EDIS;
}

/**
* @brief   User EPWM initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_ClaPerd_Init(void)
{
    EALLOW;
    v_EPwmCfg_D2d_Cmn_Init(&EPwm6Regs);
    EPwm6Regs.TBPRD = PERD_EPWM_D2D_INT - 1U;    // 24kHz
    EPwm6Regs.EPWMXLINK.bit.TBPRDLINK = 5U;    // TBPRD Link to EPWM6
    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    //INT on Zero event
    EPwm6Regs.ETSEL.bit.INTEN = 1U;    //Disable INT
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;    //Generate INT on 1st event
    EPwm6Regs.TZCLR.bit.INT = 1U;
    EPwm6Regs.ETCLR.bit.INT = 1U;
    EDIS;
}
/**
* @brief   User EPWMX Unified initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_EPwmCfg_D2d_Cmn_Init(volatile struct EPWM_REGS *stEpwmX)
{
    /* TB Configuration */
    stEpwmX->TBPRD = PERD_EPWM_DFT - 1U;              // Frequency
    stEpwmX->TBCTL.bit.CTRMODE = TB_COUNT_UP;           // Up-Count Mode
    stEpwmX->TBCTR = 0U;                                // Clear Time Base Counter
    stEpwmX->TBPHS.bit.TBPHS = 2U;                      // Phase Offset
    stEpwmX->TBCTL.bit.PRDLD = TB_SHADOW;               // TBPRD Load from Shadow register
    stEpwmX->TBCTL2.bit.PRDLDSYNC = 0x0U;               // Shadow to Active Load of TBPRD occurs only when TBCTR = 0
    stEpwmX->TBCTL.bit.PHSEN = TB_DISABLE;              // Do not load TBCTR from TBPHS
    stEpwmX->TBCTL.bit.PHSDIR = TB_UP;                  // Count up after the synchronization event
    stEpwmX->TBCTL.bit.HSPCLKDIV = TB_DIV1;             // HSPCLKDIV = 1
    stEpwmX->TBCTL.bit.CLKDIV = TB_DIV1;                // CLKDIV = 1; TBCLK = EPWMCLK / (HSPCLKDIV * CLKDIV)

    /* CMP Configuration */
    stEpwmX->CMPCTL.bit.SHDWAMODE = CC_SHADOW;          // CMPA Shadow mode
    stEpwmX->CMPCTL.bit.SHDWBMODE = CC_SHADOW;          // CMPB Shadow mode
    stEpwmX->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;    // CMPA Load on either CTR = 0 or CTR = PRD
    stEpwmX->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;    // CMPB Load on either CTR = 0 or CTR = PRD
    stEpwmX->CMPA.bit.CMPA = 0U;                        // Set CMPA
    stEpwmX->CMPB.bit.CMPB = PERD_EPWM_DFT>>1;           // Set CMPB
    /* AQ Configuration */
    stEpwmX->AQCTLA.bit.CAU = AQ_SET;                   // Set EPWMxA when TBCTR = CMPA on Up Count
    stEpwmX->AQCTLA.bit.CBU = AQ_CLEAR;                 // Clear EPWMxA when TBCTR = CMPB on Up Count
    stEpwmX->AQCSFRC.all = 0x0U;                        // Software forcing is disabled and has no effect
    /* DC Configuration */
#if 1U == PWM_DCEVT_EN
    stEpwmX->DCTRIPSEL.bit.DCAHCOMPSEL = DC_TRIPIN5;    // DCAH Select TRIPIN5
    stEpwmX->DCACTL.bit.EVT1SRCSEL = DC_EVT1;           // Source is DCAEVT1(no filter)
    stEpwmX->DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Source is passed through asynchronously
    stEpwmX->DCTRIPSEL.bit.DCBHCOMPSEL = DC_TRIPIN5;    // DCBH Select TRIPIN5
    stEpwmX->DCBCTL.bit.EVT1SRCSEL = DC_EVT1;           // Source is DCAEVT1(no filter)
    stEpwmX->DCBCTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Source is passed through asynchronously

    /* TZ Configuration */
    stEpwmX->TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI;          // DCAEVT1 = DCAH high, DCAL don't care
    stEpwmX->TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI;          // DCBEVT1 = DCBH high, DCBL don't care
    stEpwmX->TZSEL.bit.DCAEVT1 = TZ_ENABLE;             // Enable DCAEVT1 as one-shot-trip source
    stEpwmX->TZSEL.bit.DCBEVT1 = TZ_ENABLE;             // Enable DCBEVT1 as one-shot-trip source
#endif
    stEpwmX->TZCTL.bit.TZA = TZ_FORCE_LO;               // Force EPWMxA to a low state when a trip event occurs
    stEpwmX->TZCTL.bit.TZB = TZ_FORCE_LO;               // Force EPWMxB to a low state when a trip event occurs
    stEpwmX->TZCTL.bit.DCAEVT1 = TZ_FORCE_LO;           // Force EPWMxA to a low state when DCAEVT1
    stEpwmX->TZCTL.bit.DCBEVT1 = TZ_FORCE_LO;           // Force EPWMxB to a low state when DCBEVT1
    stEpwmX->TZFRC.bit.OST = 1U;                        // Force a One-Short Trip via Software

    /* DB Configuration */
    stEpwmX->DBCTL.bit.IN_MODE = DBA_ALL;               // EPWMxA In is the source for both falling-edge and rising-edge delay
    stEpwmX->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;       // DBM is fully enabled (both RED and FED active)
    stEpwmX->DBCTL.bit.POLSEL = DB_ACTV_HIC;            // Active high complementary (AHC). EPWMxB is inverted.
    stEpwmX->DBCTL.bit.HALFCYCLE = 1U;                  // The dead-band counters are clocked at TBCLK*2.
    stEpwmX->DBFED.bit.DBFED = EPWM_DB_HALFCYCLE;       // Falling Edge Delay Count
    stEpwmX->DBRED.bit.DBRED = EPWM_DB_HALFCYCLE;       // Rising Edge Delay Count
    stEpwmX->DBCTL.bit.OUTSWAP = 0x3U;    // Swap EPWMxA and EPWMxB
#if 3U == GRID_PHASE_NUMBER
    stEpwmX->EPWMXLINK.bit.TBPRDLINK = EPWM_PRD_LINK_NUM;    // TBPRD Link to EPWM8
#endif
    stEpwmX->TZEINT.bit.DCAEVT1 = 0U;    // Disable DCAEVT1 Interrupt
    stEpwmX->TZCLR.bit.DCAEVT1 = 1U;    // Clear DCAEVT1 flag
    stEpwmX->TZCLR.bit.INT = 1U;    // Clear INT flag
}

/**
* @brief   D2d FCT test EPWM function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_EPwmCfg_D2d_FctPwm(void)
{
    EALLOW;
    /* Disable PRI_BDGL EPWM TZ event */
    EPWM_PRI_BDGL.TZDCSEL.bit.DCAEVT1 	 = TZ_EVT_DISABLE;
    EPWM_PRI_BDGL.TZDCSEL.bit.DCBEVT1 	 = TZ_EVT_DISABLE;
    EPWM_PRI_BDGL.TZSEL.bit.DCAEVT1   	 = TZ_DISABLE;
    EPWM_PRI_BDGL.TZSEL.bit.DCBEVT1    	 = TZ_DISABLE;
    /* Disable PRI_BDGR EPWM TZ event */
    EPWM_PRI_BDGR.TZDCSEL.bit.DCAEVT1 	 = TZ_EVT_DISABLE;
    EPWM_PRI_BDGR.TZDCSEL.bit.DCBEVT1 	 = TZ_EVT_DISABLE;
    EPWM_PRI_BDGR.TZSEL.bit.DCAEVT1   	 = TZ_DISABLE;
    EPWM_PRI_BDGR.TZSEL.bit.DCBEVT1      = TZ_DISABLE;
    /* Disable SEC_DN_BDGL EPWM TZ event */
    EPWM_SEC_DN_BDGL.TZDCSEL.bit.DCAEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_DN_BDGL.TZDCSEL.bit.DCBEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_DN_BDGL.TZSEL.bit.DCAEVT1   = TZ_DISABLE;
    EPWM_SEC_DN_BDGL.TZSEL.bit.DCBEVT1   = TZ_DISABLE;
    /* Disable SEC_DN_BDGR EPWM TZ event */
    EPWM_SEC_DN_BDGR.TZDCSEL.bit.DCAEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_DN_BDGR.TZDCSEL.bit.DCBEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_DN_BDGR.TZSEL.bit.DCAEVT1   = TZ_DISABLE;
    EPWM_SEC_DN_BDGR.TZSEL.bit.DCBEVT1   = TZ_DISABLE;
    /* Disable SEC_UP_BDGL EPWM TZ event */
    EPWM_SEC_UP_BDGL.TZDCSEL.bit.DCAEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_UP_BDGL.TZDCSEL.bit.DCBEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_UP_BDGL.TZSEL.bit.DCAEVT1   = TZ_DISABLE;
    EPWM_SEC_UP_BDGL.TZSEL.bit.DCBEVT1   = TZ_DISABLE;
    /* Disable SEC_UP_BDGR EPWM TZ event */
    EPWM_SEC_UP_BDGR.TZDCSEL.bit.DCAEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_UP_BDGR.TZDCSEL.bit.DCBEVT1 = TZ_EVT_DISABLE;
    EPWM_SEC_UP_BDGR.TZSEL.bit.DCAEVT1   = TZ_DISABLE;
    EPWM_SEC_UP_BDGR.TZSEL.bit.DCBEVT1   = TZ_DISABLE;
    EDIS;
}
/**
* @brief   D2d FCT test EPWM function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_EPwmCfg_Pfc_FctPwm(void)
{
    EALLOW;
    /* Disable PhaseA EPWM TZ*/
    EPwm1Regs.TZSEL.bit.OSHT1   = TZ_DISABLE;
    EPwm1Regs.TZSEL.bit.OSHT2   = TZ_DISABLE;
    EPwm1Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
    EPwm1Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
	/* Disable PhaseB EPWM TZ*/
    EPwm2Regs.TZSEL.bit.OSHT1   = TZ_DISABLE;
    EPwm2Regs.TZSEL.bit.OSHT2   = TZ_DISABLE;
    EPwm2Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
    EPwm2Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
	/* Disable PhaseC EPWM TZ*/
    EPwm3Regs.TZSEL.bit.OSHT1   = TZ_DISABLE;
    EPwm3Regs.TZSEL.bit.OSHT2   = TZ_DISABLE;
    EPwm3Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
    EPwm3Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
	/* Disable Balance Bridge EPWM TZ*/
	EPwm4Regs.TZSEL.bit.OSHT1   = TZ_DISABLE;
    EPwm4Regs.TZSEL.bit.OSHT2   = TZ_DISABLE;
    EPwm4Regs.TZSEL.bit.DCAEVT2 = TZ_DISABLE;
    EPwm4Regs.TZSEL.bit.DCBEVT2 = TZ_DISABLE;
    EDIS;
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
