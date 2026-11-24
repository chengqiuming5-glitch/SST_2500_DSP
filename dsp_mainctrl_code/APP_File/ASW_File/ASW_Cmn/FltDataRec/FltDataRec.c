//==============================================================================================
//    File description
//==============================================================================================
/**@file         FltDataRec.c
 * @brief
 * The header file of fault data record is designed to record the fault data.
 *
 * Module      :                       \n
 * FltDataRec                          \n
 *
 * Unit        :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 * Module Task :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 * Unit Task   :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/10/14
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
 * <tr><td>2024/10/14  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FltDataRec.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_FLT_DATA_REC stFltDataRec;                         ///< Fault data record global struct
UN_SYS_TIME unTimeSys;                                ///< System time

#if (1U == FLT_DATA_REC_DBG)
extern ST_FLT_DATA_REC stFltDataRecDbg;               ///< Fault data record debug global struct
#endif

static ST_FLT_DATA_REC_LOC stFltDataRecLoc;           ///< Fault data record local struct

/* Monthly days table (index 0 not used) */
static const Uint16 uiDatePerMonth[13] = {0U,31U,28U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U};

//==============================================================================================
//    Function definition
//==============================================================================================
/********************************************Begin*********************************************/
/**
 * @brief        Fault data record initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltDataRec_Init(void)
{
    v_FltDataRec_TiPrm_Init();       ///< Initialize time parameters
    v_FltDataRec_DataPrm_Init();     ///< Initialize data parameters
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault data record initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_TiPrm_Init(void)
{
    /* Local Signal*/
    stFltDataRecLoc.unTiLoc.all                     = 0ULL;                       ///< Time local time
    stFltDataRecLoc.unTiLoc.bit.ulYear              = YEAR_SYS_TIME_DFT;          ///< Default year of system time
    stFltDataRecLoc.unTiLoc.bit.ulMonth             = MONTH_SYS_TIME_DFT;         ///< Default month of system time
    stFltDataRecLoc.unTiLoc.bit.ulDate              = DATE_SYS_TIME_DFT;          ///< Default date of system time
    stFltDataRecLoc.unTiLoc.bit.ulHour              = HOUR_SYS_TIME_DFT;          ///< Default hour of system time
    stFltDataRecLoc.unTiLoc.bit.ulMin               = MIN_SYS_TIME_DFT;           ///< Default minute of system time
    stFltDataRecLoc.unTiLoc.bit.ulSec               = SEC_SYS_TIME_DFT;           ///< Default second of system time
    stFltDataRecLoc.unTiLoc.bit.ulMillSec           = MILLI_SEC_SYS_TIME_DFT;     ///< Default milli-second of system time

    /* Global Signal*/
    stFltDataRec.stFltData.ullTime.all               = 0ULL;                       ///< System time
    stFltDataRec.stFltData.ullTime.bit.ulYear        = YEAR_SYS_TIME_DFT;          ///< Default year of system time
    stFltDataRec.stFltData.ullTime.bit.ulMonth       = MONTH_SYS_TIME_DFT;         ///< Default month of system time
    stFltDataRec.stFltData.ullTime.bit.ulDate        = DATE_SYS_TIME_DFT;          ///< Default date of system time
    stFltDataRec.stFltData.ullTime.bit.ulHour        = HOUR_SYS_TIME_DFT;          ///< Default hour of system time
    stFltDataRec.stFltData.ullTime.bit.ulMin         = MIN_SYS_TIME_DFT;           ///< Default minute of system time
    stFltDataRec.stFltData.ullTime.bit.ulSec         = SEC_SYS_TIME_DFT;           ///< Default second of system time
    stFltDataRec.stFltData.ullTime.bit.ulMillSec     = MILLI_SEC_SYS_TIME_DFT;     ///< Default milli-second of system time
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault data record initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_DataPrm_Init(void)
{
    Uint16 i = 0U;
    Uint16 j = 0U;

    /* Local Signal*/
    stFltDataRecLoc.uiCntrPostFlt     = 0U;                       ///< Post fault counter

    /* Global Signal*/
    for(i = 0U; i <= NUM_ARRAY_IBATT_DWN; i++)
    {
        for(j = 0U; j < SIZE_REC_ARRAY; j++)
        {
            stFltDataRec.stFltData.uiPrmPow[i][j] = 0U;           ///< Default value of power parameter
        }
    }

        /* Initialize temperature data */
    for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
    {
        stFltDataRec.stFltData.siTemp[i] = 0;                     ///< Default value of temperature
    }

    /* Initialize fault words */
    for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
    {   
        stFltDataRec.stFltData.uiWordFlt[i] = 0U;                 ///< Default value of fault word
    }

    stFltDataRec.uiFlgFltDataRec      = 0U;                       ///< Fault data record flag
    stFltDataRec.uiPtrArrRec          = 0U;
    stFltDataRec.unFlgRec.all         = 0U;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault data record 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltDataRec_1ms(void)
{
    v_FltDataRec_TiSycn();      ///< Time synchronization processings
    v_FltDataRec_ClrChk_1ms();  ///< Clear check
    
    if(0U == stFltDataRec.unFlgRec.bit.uiStrt)           ///< There is no fault
    {
        v_FltDataRec_Volt_Curr();
    }
    else if(0U == stFltDataRec.unFlgRec.bit.uiEnd)
    {
        stFltDataRecLoc.uiCntrPostFlt++;
        if(stFltDataRecLoc.uiCntrPostFlt <= 20U)
        {
            v_FltDataRec_Volt_Curr();
            v_FltDataRec_Flt();

            if(20U == stFltDataRecLoc.uiCntrPostFlt)
            {
                stFltDataRec.unFlgRec.bit.uiEnd = 1U;    ///< Set record end flag
                stFltDataRec.uiFlgFltDataRec    = 1U;    ///< Set fault data record flag
                stFltDataRecLoc.uiCntrPostFlt   = 0U;    ///< Clear post fault counter
            }
        }
    }
    else
    {
        ///< Do nothing
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault data parameter clear 1ms task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_ClrChk_1ms(void)
{
    Uint16 l_uiStFltPrsnt           = 0U;      ///< Current fault status
    static Uint16 sl_uiStFltLast    = 0U;      ///< Last fault status

    /* Determine the current comprehensive fault status */
    l_uiStFltPrsnt = stComTbl.unWordPfcFlt1.all | stComTbl.unWordPfcFlt2.all | stComTbl.unWordPfcFlt3.all | \
                            stComTbl.unWordSysFlt.all | stD2dDiag.uiFltCpu | stD2dDiag.uiFltCla;

    /* Trigger clearing when the fault state changes from non-zero to zero */
    if(SPI_STATE_WRITE != stSpi.uiStSpi)
    {
        if((0U == l_uiStFltPrsnt) && (0U != sl_uiStFltLast))
        {
            sl_uiStFltLast = 0U;  ///< Update status record
            v_FltDataRec_DataPrm_Init();    ///< Clear data parameter
        }
        else
        {
            sl_uiStFltLast = l_uiStFltPrsnt;  ///< Update status record
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Voltage & Current data record task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_Volt_Curr(void)
{
    /* Va record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VA][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stVg.ftValLpf10kHz_A;
    /* Vb record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VB][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stVg.ftValLpf10kHz_B;
    /* Vc record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VC][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stVg.ftValLpf10kHz_C;
    /* Ia record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IA][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stIg.ftValLpf10kHz_A;
    /* Ib record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IB][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stIg.ftValLpf10kHz_B;
    /* Ic record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IC][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stIg.ftValLpf10kHz_C;
    /* In record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IN][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stPfcAdc.stIg.ftValLpf10kHz_N;
    /* Vbus record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VBUS][stFltDataRec.uiPtrArrRec]      = (Uint16)(int16)stPfcAdc.stVbus.ftValLpf10kHz_A;
    /* Positive Vbus record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VBUS_POS][stFltDataRec.uiPtrArrRec]  = (Uint16)(int16)stPfcAdc.stVbusPos.ftValLpf10kHz_A;
    /* Negative Vbus record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VBUS_NEG][stFltDataRec.uiPtrArrRec]  = (Uint16)(int16)stPfcAdc.stVbusNeg.ftValLpf10kHz_A;
#if 1U == FLG_D2D_POWCTRL_EN
    /* Up Vbatt record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VBATT_UP][stFltDataRec.uiPtrArrRec]  = (Uint16)(int16)stD2dPowCtrlClaToCpu.stAdc.ftVoltBattUpLpf5kHz;
    /* Down Vbatt record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_VBATT_DWN][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stD2dPowCtrlClaToCpu.stAdc.ftVoltBattDwnLpf5kHz;
    /* Up Ibatt record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IBATT_UP][stFltDataRec.uiPtrArrRec]  = (Uint16)(int16)stD2dPowCtrlClaToCpu.stAdc.ftCurrBattUpLpf5kHz;
    /* Down Ibatt record */
    stFltDataRec.stFltData.uiPrmPow[NUM_ARRAY_IBATT_DWN][stFltDataRec.uiPtrArrRec] = (Uint16)(int16)stD2dPowCtrlClaToCpu.stAdc.ftCurrBattDwnLpf5kHz;
#endif
    stFltDataRec.uiPtrArrRec++;
    if(stFltDataRec.uiPtrArrRec >= SIZE_REC_ARRAY)
    {
        stFltDataRec.uiPtrArrRec = 0U;
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault data record ISR task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_FltDataRec_ISR(void)
{
    if(0U == stFltDataRec.unFlgRec.bit.uiStrt)
    {
        if((0U != stComTbl.unWordSysFlt.all) ||  \
           (0U != stComTbl.unWordPfcFlt1.all) || (0U != stComTbl.unWordPfcFlt2.all) || (0U != stComTbl.unWordPfcFlt3.all) || \
           (0U != stD2dDiag.uiFltCpu) || (0U != stD2dDiag.uiFltCla))
        {
            v_FltDataRec_Volt_Curr();    ///< Voltage & Current data record
            v_FltDataRec_Time();         ///< Time data record
            v_FltDataRec_Temp();         ///< Temperature data record
            v_FltDataRec_Flt();          ///< Fault data record

            stFltDataRec.unFlgRec.bit.uiStrt = 1U;    ///< Set record start flag
        }
    }
    else
    {
        ///< Clear record start flag
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Time data record task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_Time(void)
{
    /* Time record */
   stFltDataRec.stFltData.ullTime.bit.ulYear      = stFltDataRecLoc.unTiLoc.bit.ulYear;      ///< Year
   stFltDataRec.stFltData.ullTime.bit.ulMonth     = stFltDataRecLoc.unTiLoc.bit.ulMonth;     ///< Month
   stFltDataRec.stFltData.ullTime.bit.ulDate      = stFltDataRecLoc.unTiLoc.bit.ulDate;      ///< Date
   stFltDataRec.stFltData.ullTime.bit.ulHour      = stFltDataRecLoc.unTiLoc.bit.ulHour;      ///< Hour
   stFltDataRec.stFltData.ullTime.bit.ulMin       = stFltDataRecLoc.unTiLoc.bit.ulMin;       ///< Minute
   stFltDataRec.stFltData.ullTime.bit.ulSec       = stFltDataRecLoc.unTiLoc.bit.ulSec;       ///< Second
   stFltDataRec.stFltData.ullTime.bit.ulMillSec   = stFltDataRecLoc.unTiLoc.bit.ulMillSec;   ///< Millisecond 
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Time synchronization processing
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_TiSycn(void)
{
    /* Receive time from Com */
    v_FltDataRec_TiSycn_Hndl(&stCom.unTiSys);

    /* Time counting processing*/
    v_FltDataRec_TiSycn_Inct();
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Time synchronization processing
 * @param [in]   pstExtTime: Pointer to external time structure
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_TiSycn_Hndl(UN_SYS_TIME *pstExtTime)
{
    Uint16 l_uiDateMax          = 0U;
    static Uint64 ull_TiLastExt = 0ULL;

    if(ull_TiLastExt != pstExtTime->all)
    {
        /* Update received time from Com */
        ull_TiLastExt = pstExtTime->all;

        /* Basic validity check */
        l_uiDateMax = ui_FltDataRec_TiSycn_GetDate(pstExtTime->bit.ulYear, pstExtTime->bit.ulMonth);    ///< Get the maximum date of the month
        if((pstExtTime->bit.ulYear >= MIN_VALID_YEAR) && \
           (pstExtTime->bit.ulMonth >= MIN_VALID_MONTH) && (pstExtTime->bit.ulMonth <= MAX_VALID_MONTH) && \
           (pstExtTime->bit.ulDate >= MIN_VALID_DATE) && (pstExtTime->bit.ulDate <= l_uiDateMax) && \
           (pstExtTime->bit.ulHour <= MAX_VALID_HOUR) && \
           (pstExtTime->bit.ulMin <= MAX_VALID_MINUTE) && \
           (pstExtTime->bit.ulSec <= MAX_VALID_SECOND))
        {
            stFltDataRecLoc.unTiLoc.bit.ulYear     = pstExtTime->bit.ulYear;     ///< Year
            stFltDataRecLoc.unTiLoc.bit.ulMonth    = pstExtTime->bit.ulMonth;    ///< Month
            stFltDataRecLoc.unTiLoc.bit.ulDate     = pstExtTime->bit.ulDate;     ///< Date
            stFltDataRecLoc.unTiLoc.bit.ulHour     = pstExtTime->bit.ulHour;     ///< Hour
            stFltDataRecLoc.unTiLoc.bit.ulMin      = pstExtTime->bit.ulMin;      ///< Minute
            stFltDataRecLoc.unTiLoc.bit.ulSec      = pstExtTime->bit.ulSec;      ///< Second
            stFltDataRecLoc.unTiLoc.bit.ulMillSec  = pstExtTime->bit.ulMillSec;  ///< Millisecond
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Time synchronization Time increment processing
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_TiSycn_Inct(void)
{
    Uint16 l_uiDateMax = 0U;

    /* Millisecond increment */
    if(++stFltDataRecLoc.unTiLoc.bit.ulMillSec >= MILLISECONDS_PER_SECOND)
    {
        stFltDataRecLoc.unTiLoc.bit.ulMillSec = 0UL;
        
        /* Second increment */
        if(++stFltDataRecLoc.unTiLoc.bit.ulSec >= SECONDS_PER_MINUTE) 
        {
            stFltDataRecLoc.unTiLoc.bit.ulSec = 0UL;
            
            /* Minute increment */
            if(++stFltDataRecLoc.unTiLoc.bit.ulMin >= MINUTES_PER_HOUR) 
            {
                stFltDataRecLoc.unTiLoc.bit.ulMin = 0UL;
                
                /* Hour increment */
                if(++stFltDataRecLoc.unTiLoc.bit.ulHour >= HOURS_PER_DAY) 
                {
                    stFltDataRecLoc.unTiLoc.bit.ulHour = 0UL;
                    
                    /* Date increment */
                    l_uiDateMax = ui_FltDataRec_TiSycn_GetDate(stFltDataRecLoc.unTiLoc.bit.ulYear, stFltDataRecLoc.unTiLoc.bit.ulMonth);
                    if(++stFltDataRecLoc.unTiLoc.bit.ulDate > l_uiDateMax)
                    {
                        stFltDataRecLoc.unTiLoc.bit.ulDate = 1UL;
                        
                        /* Month increment */
                        if(++stFltDataRecLoc.unTiLoc.bit.ulMonth > MONTHS_PER_YEAR) 
                        {
                            stFltDataRecLoc.unTiLoc.bit.ulMonth = 1UL;
                            stFltDataRecLoc.unTiLoc.bit.ulYear++;
                        }
                    }
                }
            }
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Get the maximum date of the month
 * @param [in]   ulYear: Year
 * @param [in]   ulMonth: Month
 * @param [out]  null
 * @return       Maximum date
 * @see          SWDD-xxxx
 */
static Uint16 ui_FltDataRec_TiSycn_GetDate(Uint32 ulYear, Uint32 ulMonth)
{
    Uint16 l_uiRetVal = 0U;

    if((ulMonth == 2UL) && (b_FltDataRec_TiSycn_IsLeapYear(ulYear)))
    {
        l_uiRetVal = 29U;
    }
    else
    {
        l_uiRetVal = uiDatePerMonth[ulMonth];   ///< Get date
    }

    return l_uiRetVal;
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Check if the year is a leap year
 * @param [in]   ulYear: Year
 * @param [out]  null
 * @return       1: leap year, 0: not leap year
 * @see          SWDD-xxxx
 */
static bool b_FltDataRec_TiSycn_IsLeapYear(Uint32 ulYear)
{
    return ((((ulYear % 4UL) == 0UL) && ((ulYear % 100UL) != 0UL)) || ((ulYear % 400UL) == 0UL));
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Fault type data record task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_Flt(void)
{
    if(0U == stFltDataRec.unFlgRec.bit.uiFltRcd)
    {
        if((0U != stComTbl.unWordSysFlt.all) ||  \
           (0U != stComTbl.unWordPfcFlt1.all) || (0U != stComTbl.unWordPfcFlt2.all) || (0U != stComTbl.unWordPfcFlt3.all) || \
           (0U != stD2dDiag.uiFltCpu) || (0U != stD2dDiag.uiFltCla))
        {
            /* System fault record */
            stFltDataRec.stFltData.uiWordFlt[0] = stComTbl.unWordSysFlt.all;
            /* PFC fault 1 record */
            stFltDataRec.stFltData.uiWordFlt[1] = stComTbl.unWordPfcFlt1.all;
            /* PFC fault 2 record */
            stFltDataRec.stFltData.uiWordFlt[2] = stComTbl.unWordPfcFlt2.all;
            /* PFC fault 3 record */
            stFltDataRec.stFltData.uiWordFlt[3] = stComTbl.unWordPfcFlt3.all;
            /* D2D CPU fault record */
            stFltDataRec.stFltData.uiWordFlt[4] = stD2dDiag.uiFltCpu;
            /* D2D CLA fault record */
            stFltDataRec.stFltData.uiWordFlt[5] = stD2dDiag.uiFltCla;

            stFltDataRec.unFlgRec.bit.uiFltRcd = 1U;    ///< Set fault record flag
        }
    }
}
/*********************************************End**********************************************/

/********************************************Begin*********************************************/
/**
 * @brief        Temperature data record task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
static void v_FltDataRec_Temp(void)
{
    float32 l_ftDataTmp = 0.0f;    ///< Temporary data

    /* DSP board temperature record */
    l_ftDataTmp = stCmnAdc.ftTempDspBd * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[0] = (int16)l_ftDataTmp;
    /* ARM board temperature record */
    l_ftDataTmp = stComIf.ftTempArmBd * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[1] = (int16)l_ftDataTmp;
    /* NTC0 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc0 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[2] = (int16)l_ftDataTmp;
    /* NTC1 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc1 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[3] = (int16)l_ftDataTmp;
    /* NTC2 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc2 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[4] = (int16)l_ftDataTmp;
    /* NTC3 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc3 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[5] = (int16)l_ftDataTmp;
    /* NTC4 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc4 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[6] = (int16)l_ftDataTmp;
    /* NTC5 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc5 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[7] = (int16)l_ftDataTmp;
    /* NTC6 temperature record */
    l_ftDataTmp = stComIf.ftTempNtc6 * COEFF_TEMP_ARM;
    stFltDataRec.stFltData.siTemp[8] = (int16)l_ftDataTmp;
}
/*********************************************End**********************************************/

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
