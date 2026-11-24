//========================================================================
// FILE          : ComExt.h
// TITLE         : CAN Communication Header File
//========================================================================
/* Copyright (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Created by    : Ricky
* Created date  : 2023.07.06
* Version       : v1.0
* Descriptions  : Include Header Files & Macro Definition &
*                 Variable Declaration & Function Declaration
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
**************************************************************************
*/

/*
**************************************************************************
* @file         CAN_Comm.h
* @brief        CAN Communication Header File
* @details
* @author       Ricky
* @date         2023.07.06
* @version      v1.0
* @copyright    (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* @attention
* MCU:          TMS320F2837xD \n
* Environment:  CCS v10.4.0
* @par Log Information:
* <table>
* <tr><th>Date         <th>Version       <th>Author       <th>Description
* <tr><td>2023.07.06   <td>1.0           <td>Ricky        <td>Initial Version
* </table>
*
**************************************************************************
*/

#ifndef COMEXT_H_
#define COMEXT_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "ASW_Cmn.h"

//=====================================================
//    Macro Definition
//=====================================================
#define COM_DBG    0U    ///< Debug for SWUT,SWIT,Function debug,etc

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
/* ST_COM_TBL Typedef*/
typedef struct
{
    float32 ftVoltGrid;             ///< Rated grid phase rms voltage
    float32 ftFrqGrid;              ///< Rated grid frequency
    float32 ftPowRtd;               ///< Rated power
    float32 ftPFMin;                ///< Min power factor
    float32 ftPowBattChrgRtd;       ///< Rated battery power
    float32 ftRatAcOvLoad;          ///< Ac over load ratio
    float32 ftRsvd0;                ///< float Reserved 0
    float32 ftRsvd1;                ///< float Reserved 1
    float32 ftRsvd2;                ///< float Reserved 2
    float32 ftRsvd3;                ///< float Reserved 3
    Uint16  uiRsvd0;                ///< Uint Reserved 0
    Uint16  uiRsvd1;                ///< Uint Reserved 1
    Uint16  uiRsvd2;                ///< Uint Reserved 2
    Uint16  uiRsvd3;                ///< Uint Reserved 3
    Uint16  uiRsvd4;                ///< Uint Reserved 4
    Uint16  uiRsvd5;                ///< Uint Reserved 5
}ST_COMTBL_PFC_RATED_PARM1;

typedef struct
{
    float32 ftCurrIabcCBC;          ///< Iac CBC limit
    float32 ftCurrInCBC;            ///< In(Balance bridge current) CBC limit
}ST_COMTBL_PFC_RATED_PARM2;

typedef struct
{
    Uint16  uiSwtFrqIabc;           ///<PFC phase A/B/C switch frequency/Hz
    Uint16  uiDeadTiIabc;           ///<PFC phase A/B/C deadtime/ns

    Uint16  uiDeadTiIn;             ///<PFC phase N deadtime/ns
    Uint32  ulSwtFrqIn;             ///<PFC phase N switch frequency/Hz
}ST_COMTBL_PFC_HARDWARE_PARM;

typedef union
{
    Uint16 all;

    struct
    {
        Uint16 uiEnCurrPR1st:       1;    ///< bit0 - Current 1st PR enable bit
        Uint16 uiEnCurrPR2nd:       1;    ///< bit1 - Current 2nd PR enable bit
        Uint16 uiEnCurrPR3rd:       1;    ///< bit2 - Current 3rd PR enable bit
        Uint16 uiEnCurrPR5th:       1;    ///< bit3 - Current 5th PR enable bit
        Uint16 uiEnCurrPR7th:       1;    ///< bit4 - Current 7th PR enable bit
        Uint16 uiEnVoltPR1st:       1;    ///< bit5 - Voltage 1st PR enable bit
        Uint16 uiEnVoltPR3rd:       1;    ///< bit6 - Voltage 3rd PR enable bit
        Uint16 uiEnVoltPR5th:       1;    ///< bit7 - Voltage 5th PR enable bit
        Uint16 uiEnVoltPR7th:       1;    ///< bit8 - Voltage 7th PR enable bit
        Uint16 uiEnZeroCurrPR1st:   1;    ///< bit9 - Zero Sequence Current 1st PR enable bit
        Uint16 uiEnZeroCurrPR3rd:   1;    ///< bit10- Zero Sequence Current 3rd PR enable bit
        Uint16 uiEnZeroCurrPR5th:   1;    ///< bit11- Zero Sequence Current 5th PR enable bit
        Uint16 uiEnZeroVoltPR1st:   1;    ///< bit12 -Zero Sequence Voltage 1st PR enable bit
        Uint16 uiEnZeroVoltPR3rd:   1;    ///< bit13 -Zero Sequence Voltage 3rd PR enable bit
        Uint16 uiEnCurrPR9th:       1;    ///< bit14 - Current 9th PR enable bit
        Uint16 uiEnCurrPR15th:      1;    ///< bit15 - Current 11th PR enable bit
    }bit;
}UN_CMD_PFC_POW_CTRL1;

typedef union
{
    Uint16 all;

    struct
    {
        Uint16 uiPwmModeBal:        2;    ///< bit0-1 - Balance mode pwm mode,0: SVPWM; 1: SPWM; 2: DPWM*/
        Uint16 uiPwmModeImBal:      2;    ///< bit2-3 - Imbalance mode pwm mode, 0: SVPWM; 1: SPWM; 2: DPWM*/
        Uint16 uiEnV2LRep:          1;    ///< bit4   - V2L repeat control enable bit
        Uint16 uiEnV2LNegVolt:      1;    ///< bit5   - V2L negative sequence voltage control enable bit
        Uint16 uiEnCurrNeg3P:       1;    ///< bit6   - 3-phase negative sequence current control enable bit
        Uint16 uiEnCurrThd3P:       1;    ///< bit7   - 3-phase current THD control enable bit
        Uint16 uiEnBalBrdg:         1;    ///< bit8   - Balance bridge enable bit
        Uint16 uiModVgFF:           1;    ///< bit9   - Grid voltage feed forward mode: 0U-Instantaneous value; 1U-PLL voltage
        Uint16 uiEnBusMid:          1;    ///< bit10  - Bus mid-point voltage control enable bit
        Uint16 uiEnV2LThdCtrl:      1;    ///< bit11  - V2L Vac THD control enable
        Uint16 uiModV2LThdCtrl:     1;    ///< bit12  - V2L Vac THD control mode: 0-PR control, 1-Repeat control
        Uint16 uiRsvd:              3;    ///< bit13-15 -Reserved
    }bit;
}UN_CMD_PFC_POW_CTRL2;

typedef union
{
    Uint16 all;
    struct
    {
    Uint16 uiVdcOver:          1;   ///< bit0  - Voltage DC component over
    Uint16 uiIdcFltOv1:        1;   ///< bit1  - Idc over1 fault
    Uint16 uiIacInsOver:       1;   ///< bit2  - AC current instant value over
    Uint16 uiIacRmsOver:       1;   ///< bit3  - AC current rms value over
    Uint16 uiIacHwPosOver:     1;   ///< bit4  - AC current hardware positive value over
    Uint16 uiIacHwNegOver:     1;   ///< bit5  - AC current hardware negative value over
    Uint16 uiIacCBCOvTi:       1;   ///< bit6  - AC current CBC over time
    Uint16 uiIacImbal:         1;   ///< bit7  - AC current imbalance
    Uint16 uiVbusHwOver:       1;   ///< bit8  - Vbus hardware over
    Uint16 uiVbusPosHwOver:    1;   ///< bit9  - VbusPos hardware over
    Uint16 uiVbusNegHwOver:    1;   ///< bit10 - VbusNeg hardware over
    Uint16 uiVbusOver:         1;   ///< bit11 - Vbus over
    Uint16 uiVbusUnder:        1;   ///< bit12 - Vbus under
    Uint16 uiVbusPosOver:      1;   ///< bit13 - VbusPos over
    Uint16 uiVbusNegOver:      1;   ///< bit14 - VbusNeg over
    Uint16 uiVbusMidOver:      1;   ///< bit15 - VbusMid over
    }bit;
}UN_PFC_FLT_WORD1;

typedef union
{
    Uint16 all;
    struct
    {
    Uint16 uiOV1st:            1;   ///< bit0  - Grid over voltage-1st
    Uint16 uiOV2nd:            1;   ///< bit1  - Grid over voltage-2nd
    Uint16 uiOV3rd:            1;   ///< bit2  - Grid over voltage-3rd
    Uint16 uiUV1st:            1;   ///< bit3  - Grid under voltage-1st
    Uint16 uiUV2nd:            1;   ///< bit4  - Grid under voltage-2nd
    Uint16 uiUV3rd:            1;   ///< bit5  - Grid under voltage-3rd
    Uint16 uiOV10min:          1;   ///< bit6  - Grid over voltage-10min
    Uint16 uiOF1st:            1;   ///< bit7  - Grid over frequency-1st
    Uint16 uiOF2nd:            1;   ///< bit8  - Grid over frequency-2nd
    Uint16 uiOF3rd:            1;   ///< bit9  - Grid over frequency-3rd
    Uint16 uiUF1st:            1;   ///< bit10 - Grid under frequency-1st
    Uint16 uiUF2nd:            1;   ///< bit11 - Grid under frequency-2nd
    Uint16 uiUF3rd:            1;   ///< bit12 - Grid under frequency-3rd
    Uint16 uiHvrtOvTi:         1;   ///< bit13 - Hvrt over time
    Uint16 uiLvrtOvTi:         1;   ///< bit14 - Lvrt over time
    Uint16 uiGridAbnorm:       1;   ///< bit15 - On-grid condition not satisfy
    }bit;
}UN_PFC_FLT_WORD2;

typedef union
{
    Uint16 all;
    struct
    {
    Uint16 uiVacImbal:         1;   ///< bit0  - AC voltage imbalance
    Uint16 uiVacInsOver:       1;   ///< bit1  - AC voltage instant value over
    Uint16 uiPacOver:          1;   ///< bit2  - AC over power
    Uint16 uiStChkOvTi:        1;   ///< bit3  - PFC state machine check status over time
    Uint16 uiAntiIsland:       1;   ///< bit4  - Anti-Island fault
    Uint16 uiPasIsland:        1;   ///< bit5  - Passive-Island fault
    Uint16 uiHwSum:            1;   ///< bit6  - PFC hardware fault summary
    Uint16 uiRstrtOvNum:       1;   ///< bit7  - PFC restart number over
    Uint16 uiSelfTestFail:     1;   ///< bit8  - Italy self-test fail
    Uint16 uiACWiring:         1;   ///< bit9  - AC wiring fault
    Uint16 uiIdcFltOv2:        1;   ///< bit10 - Idc over2 fault
    Uint16 uiDspDataRec:       1;   ///< bit11 - DSP Data record
    Uint16 uiRsvd:             4;   ///< bit12-15 -Reserved
    }bit;
}UN_PFC_FLT_WORD3;

typedef union
{
    Uint16 all;
    struct
    {
    Uint16 uiOverTemp:         1;   ///< bit0  - Over temperature
    Uint16 uiUnderTemp:        1;   ///< bit1  - Under temperature
    Uint16 uiErrEeprom:        1;   ///< bit2  - Eeprom error
    Uint16 uiErrCan:           1;   ///< bit3  - CAN communication error
    Uint16 uiErrSpi:           1;   ///< bit4  - SPI communication error
    Uint16 uiFlt12V:           1;   ///< bit5  - 12V fault
    Uint16 uiFlt1V5:           1;   ///< bit6  - 1.5V fault
    Uint16 uiHwVers:           1;   ///< bit7  - Hardware version fault
    Uint16 uiRsvd:             8;   ///< bit8-15 -Reserved
    }bit;
}UN_SYS_FLT_WORD;

typedef struct
{
    float32 ftVoltAcDbgSet;         ///< Debug mode ac voltage set,x10
    float32 ftFrqAcDbgSet;          ///< Debug mode ac frequency set
    float32 ftKpVdPos;              ///< V2L mode d-axis positive voltage PI loop kp set
    float32 ftKiVdPos;              ///< V2L mode d-axis positive voltage PI loop ki set
    float32 ftIoutUpLimVdPos;       ///< V2L mode d-axis positive voltage PI loop integration up limit set
    float32 ftIoutDnLimVdPos;       ///< V2L mode d-axis positive voltage PI loop integration down limit set
    float32 ftKpVqPos;              ///< V2L mode q-axis positive voltage PI loop kp set
    float32 ftKiVqPos;              ///< V2L mode q-axis positive voltage PI loop ki set
    float32 ftIoutUpLimVqPos;       ///< V2L mode q-axis positive voltage PI loop integration up limit set
    float32 ftIoutDnLimVqPos;       ///< V2L mode q-axis positive voltage PI loop integration down limit set
    float32 ftKpVdNeg;              ///< V2L mode d-axis negitive voltage PI loop kp set
    float32 ftKiVdNeg;              ///< V2L mode d-axis negitive voltage PI loop ki set
    float32 ftIoutUpLimVdNeg;       ///< V2L mode d-axis negitive voltage PI loop integration up limit set
    float32 ftIoutDnLimVdNeg;       ///< V2L mode d-axis negitive voltage PI loop integration down limit set
    float32 ftKpVqNeg;              ///< V2L mode q-axis negitive voltage PI loop kp set
    float32 ftKiVqNeg;              ///< V2L mode q-axis negitive voltage PI loop ki set
    float32 ftIoutUpLimVqNeg;       ///< V2L mode q-axis negitive voltage PI loop integration up limit set
    float32 ftIoutDnLimVqNeg;       ///< V2L mode q-axis negitive voltage PI loop integration down limit set
    float32 ftKrZeroVoltPR1;        ///< Zero sequence voltage PR1 controller Kr set
    float32 ftWcZeroVoltPR1;        ///< Zero sequence voltage PR1 controller Wc set
    float32 ftKrZeroVoltPR3;        ///< Zero sequence voltage PR3 controller Kr set
    float32 ftWcZeroVoltPR3;        ///< Zero sequence voltage PR3 controller Wc set
    float32 ftKrZeroVoltPR5;        ///< Zero sequence voltage PR5 controller Kr set
    float32 ftWcZeroVoltPR5;        ///< Zero sequence voltage PR5 controller Wc set
    float32 ftKrZeroVoltPR7;        ///< Zero sequence voltage PR7 controller Kr set
    float32 ftWcZeroVoltPR7;        ///< Zero sequence voltage PR7 controller Wc set
    float32 ftQzVoltRepn;           ///< AC voltage repetitive controller-Qz
    float32 ftKrVoltRepn;           ///< AC voltage repetitive controller-Kr
    Uint16  uiKcmpVoltRepn;         ///< AC voltage repetitive controller-Kcompensation
}ST_COMTBL_OFFGRID_CMD;

typedef struct
{
    float32 ftKpPll;                ///< Voltage phase locked loop Kp set
    float32 ftKiPll;                ///< Voltage phase locked loop Ki set
    float32 ftErrUpLimPll;          ///< PLL input error up limit
    float32 ftErrDnLimPll;          ///< PLL input error down limit
    float32 ftIoutUpLimPll;         ///< PLL output integration up limit
    float32 ftIoutDnLimPll;         ///< PLL output integration down limit
    float32 ftKpVBus;               ///< PFC bus voltage PI loop kp
    float32 ftKiVBus;               ///< PFC bus voltage PI loop ki
    float32 ftErrUpLimVBus;         ///< PFC bus voltage PI loop input error up limit
    float32 ftErrDnLimVBus;         ///< PFC bus voltage PI loop input error down limit
    float32 ftIoutUpLimVBus;        ///< PFC bus voltage PI loop output integration up limit
    float32 ftIoutDnLimVBus;        ///< PFC bus voltage PI loop output integration down limit
    float32 ftKpId;                 ///< D-axis positive current PI loop Kp set
    float32 ftKiId;                 ///< D-axis positive current PI loop Ki set
    float32 ftErrUpLimId;           ///< D-axis positive current PI loop input error up limit
    float32 ftErrDnLimId;           ///< D-axis positive current PI loop input error down limit
    float32 ftIoutUpLimId;          ///< D-axis positive current PI loop output integration up limit
    float32 ftIoutDnLimId;          ///< D-axis positive current PI loop output integration down limit
    float32 ftKpIq;                 ///< Q-axis positive current PI loop Kp set
    float32 ftKiIq;                 ///< Q-axis positive current PI loop Ki set
    float32 ftErrUpLimIq;           ///< Q-axis positive current PI loop input error up limit
    float32 ftErrDnLimIq;           ///< Q-axis positive current PI loop input error down limit
    float32 ftIoutUpLimIq;          ///< Q-axis positive current PI loop output integration up limit
    float32 ftIoutDnLimIq;          ///< Q-axis positive current PI loop output integration down limit
    float32 ftKrIdPR2;              ///< D-axis current PR2 loop Kr set
    float32 ftWcIdPR2;              ///< D-axis current PR2 loop Wc set
    float32 ftKrIqPR2;              ///< Q-axis current PR2 loop Kr set
    float32 ftWcIqPR2;              ///< Q-axis current PR2 loop Wc set
    float32 ftKrIdPR6;              ///< D-axis current PR6 loop Kr set
    float32 ftWcIdPR6;              ///< D-axis current PR6 loop Wc set
    float32 ftKrIqPR6;              ///< Q-axis current PR6 loop Kr set
    float32 ftWcIqPR6;              ///< Q-axis current PR6 loop Wc set
    float32 ftKrIdPR12;             ///< D-axis current PR12 loop Kr set
    float32 ftWcIdPR12;             ///< D-axis current PR12 loop Wc set
    float32 ftKrIqPR12;             ///< Q-axis current PR12 loop Kr set
    float32 ftWcIqPR12;             ///< Q-axis current PR12 loop Wc set
    float32 ftKrZeroCurrPR1;        ///< Zero sequence current PR1 loop Kr set
    float32 ftWcZeroCurrPR1;        ///< Zero sequence current PR1 loop Wc set
    float32 ftKrZeroCurrPR3;        ///< Zero sequence current PR3 loop Kr set
    float32 ftWcZeroCurrPR3;        ///< Zero sequence current PR3 loop Wc set
    float32 ftKrZeroCurrPR5;        ///< Zero sequence current PR5 loop Kr set
    float32 ftWcZeroCurrPR5;        ///< Zero sequence current PR5 loop Wc set
    float32 ftKrZeroCurrPR7;        ///< Zero sequence current PR7 loop Kr set
    float32 ftWcZeroCurrPR7;        ///< Zero sequence current PR7 loop Wc set
    float32 ftKp1PCurr;             ///< Single phase current PI loop Kp set
    float32 ftKi1PCurr;             ///< Single phase current PI loop Ki set
    float32 ftErrUpLim1PCurr;       ///< Single phase current PI loop input error up limit set
    float32 ftErrDnLim1PCurr;       ///< Single phase current PI loop input error down limit set
    float32 ftIoutUpLim1PCurr;      ///< Single phase current PI loop output integration up limit set
    float32 ftIoutDnLim1PCurr;      ///< Single phase current PI loop output integration down limit set
    float32 ftKr1PCurrPR1;          ///< Single phase current PR1 loop Kr set
    float32 ftWc1PCurrPR1;          ///< Single phase current PR1 loop Wc set
    float32 ftKr1PCurrPR2;          ///< Single phase current PR2 loop Kr set
    float32 ftWc1PCurrPR2;          ///< Single phase current PR2 loop Wc set
    float32 ftKr1PCurrPR3;          ///< Single phase current PR3 loop Kr set
    float32 ftWc1PCurrPR3;          ///< Single phase current PR3 loop Wc set
    float32 ftKr1PCurrPR5;          ///< Single phase current PR5 loop Kr set
    float32 ftWc1PCurrPR5;          ///< Single phase current PR5 loop Wc set
    float32 ftKr1PCurrPR7;          ///< Single phase current PR7 loop Kr set
    float32 ftWc1PCurrPR7;          ///< Single phase current PR7 loop Wc set
}ST_COMTBL_ONGRID_CMD;

typedef struct
{
    float32 ftVoltBalEna;           ///< Balance bridge enable voltage limit
    float32 ftKpVolt;               ///< Balance bridge voltage PI loop Kp set
    float32 ftKiVolt;               ///< Balance bridge voltage PI loop Ki set
    float32 ftErrUpLimVolt;         ///< Balance bridge voltage PI loop input error up limit set
    float32 ftErrDnLimVolt;         ///< Balance bridge voltage PI loop input error down limit set
    float32 ftKrVoltPR;             ///< Balance bridge voltage PR loop Kr set
    float32 ftWcVoltPR;             ///< Balance bridge voltage PR loop Wc set
    float32 ftLimRefCurr;           ///< Balance bridge current loop reference limit
    float32 ftKpCurr;               ///< Balance bridge current PI loop Kp set
    float32 ftKiCurr;               ///< Balance bridge current PI loop Ki set
    float32 ftKrCurrPR;             ///< Balance bridge current PR loop Kr set
    float32 ftWcCurrPR;             ///< Balance bridge current PR loop Wc set
}ST_COMTBL_BALBRDG_CMD;

typedef struct
{
    int16   siVbusMax;
    int16   siVbusMin;
    int16   siVbusUpRat;
    int16   siVbusDnRat;

    int16   siVacMax;
    int16   siVacMin;
    int16   siVacUpRat;
    int16   siVacDnRat;
}ST_COMTBL_VOLTRAMP_CMD;

typedef struct
{
    Uint16  uiEnaAntiIsland;        ///< Anti-island enable switch
    Uint16  uiEnaCurrDcCtrl;        ///< AC current DC component control enable switch
    Uint16  uiEnaVoltDcCtrl;        ///< AC voltage DC component control enable switch
    Uint16  uiEnaFltRcvPwrLim;      ///< Fault recovery power limit enable switch
    Uint16  uiEnaEntrSrv;           ///< IEEE 1547 enter service enable switch
    Uint16  uiRsvd0;                ///< Uint Reserved0
    Uint16  uiRsvd1;                ///< Uint Reserved1
    Uint16  uiRsvd2;                ///< Uint Reserved2
    Uint16  uiRsvd3;                ///< Uint Reserved3
    Uint16  uiRsvd4;                ///< Uint Reserved4
    Uint16  uiRsvd5;                ///< Uint Reserved5

    float32 ftRatePwrUpNorm;        ///< On grid normal running power up rate
    float32 ftRatePwrDwnNorm;       ///< On grid normal running power down rate
    float32 ftRatePwrReload;        ///< On grid reconnect power rate
    float32 ftTiWaitRecnct;         ///< On grid reconnect wait time
    float32 ftRatePwrLoad;          ///< On grid connect power rate
    float32 ftTiWaitCnct;           ///< On grid connect wait time
    float32 ftVoltGridReCnctMax;    ///< On grid reconnect max voltage
    float32 ftVoltGridReCnctMin;    ///< On grid reconnect min voltage
    float32 ftFrqGridReCnctMax;     ///< On grid reconnect max frequency
    float32 ftFrqGridReCnctMin;     ///< On grid reconnect min frequency
    float32 ftVoltGridCnctMax;      ///< On grid connect max voltage
    float32 ftVoltGridCnctMin;      ///< On grid connect min voltage
    float32 ftFrqGridCnctMax;       ///< On grid connect max frequency
    float32 ftFrqGridCnctMin;       ///< On grid connect min frequency

    float32 ftTiReactvRespPf;       ///< Reactive power Pf mode first order response time
    float32 ftTiReactvRespQu;       ///< Reactive power Qu mode first order response time
    float32 ftTiReactvRespQp;       ///< Reactive power Qp mode first order response time
    float32 ftTiReactvRespQt;       ///< Reactive power Qt mode first order response time
    float32 ftRsvd0;                ///< float Reserved0
    float32 ftRsvd1;                ///< float Reserved1
    float32 ftRsvd2;                ///< float Reserved2
    float32 ftRsvd3;                ///< float Reserved3
    float32 ftRsvd4;                ///< float Reserved4
    float32 ftRsvd5;                ///< float Reserved5
}ST_COMTBL_POWERCTRL;

typedef struct
{
    Uint16  uiEnaOV10minProt;       ///< Grid voltage 10min over voltage protection enable switch
    Uint16  uiClassProt;            ///< Protect class
    Uint16  uiModePrtTi;            ///< Protect time mode: <0:+100ms, 1:-100ms>
    Uint16  uiModePrtSel;           ///< Protection mode select, for voltage protect:0-phase voltage;1-line voltage
    Uint16  uiEnaRoCoF;             ///< Rate of change of frequency protection enable switch
    Uint16  uiRsvd0;                ///< Uint16 Reserved0

    float32 ftValOver1;             ///< On grid over voltage/frequency protect value1
    float32 ftTiOver1;              ///< On grid over voltage/frequency protect time1
    float32 ftValOver2;             ///< On grid over voltage/frequency protect value2
    float32 ftTiOver2;              ///< On grid over voltage/frequency protect time2
    float32 ftValOver3;             ///< On grid over voltage/frequency protect value3
    float32 ftTiOver3;              ///< On grid over voltage/frequency protect time3
    float32 ftValOverRcv;           ///< On grid over voltage/frequency recovery value
    float32 ftValUnder1;            ///< On grid under voltage/frequency protect value1
    float32 ftTiUnder1;             ///< On grid under voltage/frequency protect time1
    float32 ftValUnder2;            ///< On grid under voltage/frequency protect value2
    float32 ftTiUnder2;             ///< On grid under voltage/frequency protect time2
    float32 ftValUnder3;            ///< On grid under voltage/frequency protect value3
    float32 ftTiUnder3;             ///< On grid under voltage/frequency protect time3
    float32 ftValUnderRcv;          ///< On grid under voltage/frequency recovery value
    float32 ftValOver10min;         ///< On grid 10min over voltage protect value
    float32 ftValOver10minRcv;      ///< On grid 10min over voltage recovery value
    float32 ftValRoCoF;             ///< Rate of change of frequency protect value
    float32 ftRsvd0;                ///< Float Reserved0
    float32 ftRsvd1;                ///< Float Reserved1
}ST_COMTBL_VOLT_FRQ_PROT;

typedef struct
{
    Uint16  uiEna;                  ///< Idc protect enable switch: 0-Off,1-On
    float32 ftIdcOv1Perc;           ///< Idc over protect value1-%In
    float32 ftIdcOv2Real;           ///< Idc over protect value2-A, reserved
    float32 ftTiIdcOv1;             ///< Idc over protect time1
    float32 ftTiIdcOv2;             ///< Idc over protect time2, reserved
}ST_COMTBL_IDC_PROT;

typedef struct
{
    Uint16  uiEna;                  ///< High/Low frequency power response enable switch
    Uint16  uiCurve;                ///< High/Low frequency power response curve select
    Uint16  uiBaseSlop;             ///< High/Low frequency power response curve slope baseline, 0-Max power,1-Current power
    Uint16  uiRsvd0;                ///< Uint16 Reserved0
    Uint16  uiRsvd1;                ///< Uint16 Reserved1

    float32 ftFrqIn;                ///< High/Low frequency power response enter frequency
    float32 ftFrqOut;               ///< High/Low frequency power response exit frequency
    float32 ftFrqMid;               ///< High/Low frequency power response mid-frequency(For AS/NZS 4777.2:2020)
    float32 ftFrqEnd;               ///< High/Low frequency power response end frequency
    float32 ftTiInWait;             ///< High/Low frequency power response enter wait time
    float32 ftTiOutWait;            ///< High/Low frequency power response exit wait time
    float32 ftRatePwrResp;          ///< High/Low frequency power response rate
    float32 ftRatePwrRcv;           ///< High/Low frequency power response exit power recovery rate
    float32 ftSlopCurve1;           ///< High/Low frequency power response curve slope1
    float32 ftSlopCurve2;           ///< High/Low frequency power response curve slope2
    float32 ftTiResp1stLpf;         ///< High/Low frequency power 1st order LPF response time(For IEEE1547)
    float32 ftRsvd0;                ///< Reserved
    float32 ftRsvd1;                ///< Reserved
    float32 ftRsvd2;                ///< Reserved
}ST_COMTBL_FRQ_CTL;

typedef struct
{
    Uint16  uiCurve;                ///< Qu curve select
    Uint16  uiModeResp;             ///< Qu response mode select
    Uint16  uiRsvd0;                ///< Uint16 Reserved0
    Uint16  uiRsvd1;                ///< Uint16 Reserved1
    Uint16  uiRsvd2;                ///< Uint16 Reserved2

    float32 ftPFLim;                ///< Qu PF limit mode PF limit value
    float32 ftRatioU1_A;            ///< Qu-Curve A-U1
    float32 ftRatioQ1_A;            ///< Qu-Curve A-Q1
    float32 ftRatioU2_A;            ///< Qu-Curve A-U2
    float32 ftRatioQ2_A;            ///< Qu-Curve A-Q2
    float32 ftRatioU3_A;            ///< Qu-Curve A-U3
    float32 ftRatioQ3_A;            ///< Qu-Curve A-Q3
    float32 ftRatioU4_A;            ///< Qu-Curve A-U4
    float32 ftRatioQ4_A;            ///< Qu-Curve A-Q4
    float32 ftRatioU1_B;            ///< Qu-Curve B-U1
    float32 ftRatioQ1_B;            ///< Qu-Curve B-Q1
    float32 ftRatioU2_B;            ///< Qu-Curve B-U2
    float32 ftRatioQ2_B;            ///< Qu-Curve B-Q2
    float32 ftRatioU3_B;            ///< Qu-Curve B-U3
    float32 ftRatioQ3_B;            ///< Qu-Curve B-Q3
    float32 ftRatioU4_B;            ///< Qu-Curve B-U4
    float32 ftRatioQ4_B;            ///< Qu-Curve B-Q4
    float32 ftHysVolt;              ///< Qu voltage Hysteresis
    float32 ftRatioPwrIn;           ///< Qu response in power ratio
    float32 ftRatioPwrOut;          ///< Qu response out power ratio
	float32 ftCoeffVref;            ///< Qu-CurveB-Vref coefficient
    float32 ftTiVref;               ///< Vref time constant
    float32 ftRsvd0;                ///< Float Reserved0
}ST_COMTBL_QU_CTL;

typedef struct
{
    Uint16  uiCurve;                ///< Qp curve select
    Uint16  uiModeResp;             ///< Qp response mode select
    Uint16  uiRsvd0;                ///< Uint16 Reserved0
    Uint16  uiRsvd1;                ///< Uint16 Reserved1
    Uint16  uiRsvd2;                ///< Uint16 Reserved2

    float32 ftRatioP1_PF;           ///< Qp-P1_PF
    float32 ftRatioP2_PF;           ///< Qp-P2_PF
    float32 ftRatioP3_PF;           ///< Qp-P3_PF
    float32 ftRatioP4_PF;           ///< Qp-P4_PF
    float32 ftRatioPF1;             ///< Qp-PF1
    float32 ftRatioPF2;             ///< Qp-PF2
    float32 ftRatioPF3;             ///< Qp-PF3
    float32 ftRatioPF4;             ///< Qp-PF4
    float32 ftRatioP1_Q;            ///< Qp-P1_Q
    float32 ftRatioP2_Q;            ///< Qp-P2_Q
    float32 ftRatioP3_Q;            ///< Qp-P3_Q
    float32 ftRatioP4_Q;            ///< Qp-P4_Q
    float32 ftRatioP5_Q;            ///< Qp-P5_Q
    float32 ftRatioP6_Q;            ///< Qp-P6_Q
    float32 ftRatioQ1;              ///< Qp-Q1
    float32 ftRatioQ2;              ///< Qp-Q2
    float32 ftRatioQ3;              ///< Qp-Q3
    float32 ftRatioQ4;              ///< Qp-Q4
    float32 ftRatioQ5;              ///< Qp-Q5
    float32 ftRatioQ6;              ///< Qp-Q6

    float32 ftRatioVoltIn;          ///< Qp response in voltage ratio
    float32 ftRatioVoltOut;         ///< Qp response out voltage ratio
    float32 ftRsvd0;                ///< Float Reserved0
    float32 ftRsvd1;                ///< Float Reserved1
    float32 ftRsvd2;                ///< Float Reserved2

    float32 ftRatioP1;              ///< Qp-P1
    float32 ftRatioP2;              ///< Qp-P2
    float32 ftRatioP3;              ///< Qp-P3
    float32 ftRatioP4;              ///< Qp-P4
}ST_COMTBL_QP_CTL;

typedef struct
{
    Uint16  uiEna;                  ///< GVRT enable switch
    Uint16  uiModePwr;              ///< GVRT power mode
    Uint16  uiEnaZeroPwr;           ///< GVRT zero power enable switch
    Uint16  uiEnaIqLim;             ///< GVRT reactive current limit enable switch
    Uint16  uiRsvd0;                ///< Uint16 Reserved0
    Uint16  uiRsvd1;                ///< Uint16 Reserved1
    Uint16  uiRsvd2;                ///< Uint16 Reserved2

    float32 ftVolt1;                ///< Hvrt/Lvrt curve U1
    float32 ftVolt2;                ///< Hvrt/Lvrt curve U2
    float32 ftVolt3;                ///< Hvrt/Lvrt curve U3
    float32 ftTi1;                  ///< Hvrt/Lvrt curve T1
    float32 ftTi2;                  ///< Hvrt/Lvrt curve T2
    float32 ftTi3;                  ///< Hvrt/Lvrt curve T3
    float32 ftRatioZeroPwrVolt;     ///< Hvrt/Lvrt zero power trigger voltage
    float32 ftValIqLim;             ///< Hvrt/Lvrt reactive current limit value
    float32 ftCoeffIq;              ///< Hvrt/Lvrt reactive current calculation coefficient
    float32 ftRsvd0;                ///< Reserved
    float32 ftRsvd1;                ///< Reserved
    float32 ftRsvd2;                ///< Reserved
}ST_COMTBL_GVRT;

typedef struct
{
    Uint16  uiEna;                  ///< PU enable switch
    Uint16  uiCurve;                ///< PU curve select
    Uint16  uiRsvd0;                ///< Uint16 Reserved0
    Uint16  uiRsvd1;                ///< Uint16 Reserved1

    float32 ftVolt1;                ///< PU curve-U1
    float32 ftVolt2;                ///< PU curve-U2
    float32 ftVolt3;                ///< PU curve-U3
    float32 ftVolt4;                ///< PU curve-U4
    float32 ftPwr1;                 ///< PU curve-P1
    float32 ftPwr2;                 ///< PU curve-P2
    float32 ftPwr3;                 ///< PU curve-P3
    float32 ftPwr4;                 ///< PU curve-P4
    float32 ftTiResp;               ///< PU response time
    float32 ftRsvd0;                ///< Reserved
    float32 ftRsvd1;                ///< Reserved
    float32 ftRsvd2;                ///< Reserved
}ST_COMTBL_PU_CTL;

typedef struct
{
    float32 ftKpIdcCtrl;            ///< Vac dc component control loop kp set
    float32 ftKiIdcCtrl;            ///< Vac dc component control loop ki set
    float32 ftOutpLimIdcCtrl;       ///< Iac dc component control output limit
    float32 ftKpVdcCtrl;            ///< Vac dc component control loop kp set
    float32 ftKiVdcCtrl;            ///< Vac dc component control loop ki set
    float32 ftOutpLimtVdcCtrl;      ///< Vac dc component control output limit
}ST_COMTBL_GRID_DC_CTL;

typedef struct
{
    float32 ftCurrBattParlMax;     ///< Max parallel output current
    float32 ftCurrAcRmsRtd;        ///< Rated AC current RMS
}ST_COMTBL_RTD_PRM;

typedef struct
{
    float32 ftDs1OLReq;      ///< DS1 request in open-loop mode(11kW)
    float32 ftFrqOLReq;      ///< Frequency request in open-loop mode(7.4kW, 19.2kW)
}ST_COMTBL_COMIF;

typedef struct
{
    Uint16 uiDacCh;          ///< DAC channel
    int16  siAux12VZero;
    int16  siAux1V5Zero;
}ST_COMTBL_CMNADC;

typedef struct
{
    Uint16 uiFltSys;       	 ///< System fault
    float32 ftOverTemp;      ///< Over temperature protection
    float32 ftUnderTemp;     ///< Under temperature protection
}ST_COMTBL_CMNDIAG;

typedef struct
{
    Uint16   uiFltCpuNC;                              ///< D2D CPU fault
    float32  ftVoltBattUV;                            ///< Battery UV protection
    float32  ftCurrBattImbal;                         ///< Battery Imbalance current protection
    float32  ftVoltBattImbal;                         ///< Battery Imbalance current protection
}ST_COMTBL_D2DDIAG;

typedef union
{
    Uint16 all;

    struct
    {
        Uint16 uiEnaHTPowLim:        1;    ///< bit0 - High temperature power limitation enable
        Uint16 uiEnaLTPowLim:        1;    ///< bit1 - Low temperature power limitation enable
        Uint16 uiRsvd:              14;    ///< bit2-15 -Reserved
    }bit;
}UN_COMTBL_CMD_POWLIM;

typedef struct
{
    float32  ftTempNtc1PowLim;                        ///< limit temperature of Ntc1
    float32  ftTempNtc2PowLim;                        ///< limit temperature of Ntc2
    float32  ftTempNtc3PowLim;                        ///< limit temperature of Ntc3
    float32  ftTempNtc4PowLim;                        ///< limit temperature of Ntc4
    float32  ftTempNtc5PowLim;                        ///< limit temperature of Ntc5
    float32  ftTempArmBdPowlim;                       ///< limit temperature of ARM board
}ST_TEMPLIM_PARAM;

typedef struct
{
    UN_COMTBL_CMD_POWLIM   unCmd;                     ///< Command
    ST_TEMPLIM_PARAM       stChrgPrm;                 ///< Charge temperature limit parameters
    ST_TEMPLIM_PARAM       stDchaPrm;                 ///< Disharge temperature limit parameters
    float32  ftVoltBusPfcReq;                         ///< Desired value of bus voltage when PFC is only activated
    float32  ftVoltBusD2dReq;                         ///< Desired value of bus voltage when DCDC is only activated
    float32  ftVoltBusMax;                            ///< Max limited value of bus voltage
    float32  ftVoltBusMin;                            ///< Min limited value of bus voltage
    float32  ftVoltBusAdd;                            ///< Bus voltage reference added value
    float32  ftCoeffBusPreChg3P;                      ///< Bus pre-charge coefficient 3-phase
    float32  ftCoeffBusPreChg1P;                      ///< Bus pre-charge coefficient 1-phase
}ST_COMTBL_POWLIM;

typedef struct
{
    Uint16 uiModAcRly;              ///< AC precharge relay mode: 0U-level; 1U-PWM
    float32 ftDutyAcRlyPwm;         ///< AC precharge relay PWM duty
}ST_COMTBL_PERPHCTRL;

typedef struct
{
    Uint16 uiFlgFrqJitEn;         ///< Frequency jitter enable
    Uint16 uiPerdFrqJit;          ///< Frequency jitter period
    float32 ftGainFrqJitRng;      ///< Frequency jitter range
}ST_COMTBL_D2DPOWPRECTRL;

typedef struct
{
    float32 ftCurrInduLeakSwt;
    float32 ftFacBattVoltChrgKp;
    float32 ftFacBattVoltChrgKi;
    float32 ftFacBattCurrChrgKp;
    float32 ftFacBattCurrChrgKi;
    float32 ftFacBusVoltBidirKp;
    float32 ftFacBusVoltBidirKi;
    float32 ftFacBattCurrBidirKp;
    float32 ftFacBattCurrBidirKi;
    float32 ftFacBattVoltPRKr;
    float32 ftFacBattCurrPRKr;
    float32 ftOutpChrgDirDzCmp;
    float32 ftCurrBattBidirRefStep;           ///< Battery current reference step limit in bi-directional mode

    float32 ftCurrBattOCPThd;
    float32 ftVoltBattOVPThd;
    float32 ftVoltBusOVPThd;

    Uint16  ftD2dPwmValDutyPowCell;

    Uint16  uiFlgChrgPREn;
    Uint16  uiFlgDzCmpEn;
    Uint16  uiFltClaNC;
    Uint16  uiFlgBidirDynKiEn;               ///< Flag of dynamic ki enable
}ST_PRM_D2D_POW_CTRL;

typedef struct
{
    UN_CMD_PFC_POW_CTRL1 unCmdCtrl1;    ///< Control command 1
    UN_CMD_PFC_POW_CTRL2 unCmdCtrl2;    ///< Control command 1

    Uint16  uiEnaFrqJit;         ///< Frequency jitter enable
    Uint16  uiFrqJitRng;         ///< Frequency jitter range

    float32 ftThetaCompPll;      ///< PLL theta compensation
    float32 ftKpPllInit;         ///< Initial PLL Kp
    float32 ftKiPllInit;         ///< Initial PLL Ki
    float32 ftKpPll;             ///< PLL Kp
    float32 ftKiPll;             ///< PLL Ki
    float32 ftCoeffVbusNotchBw;  ///< Bus voltage Notch bandwitch coefficient

    float32 ftKpVbusLoop;        ///< Bus voltage loop Kp
    float32 ftKiVbusLoop;        ///< Bus voltage loop Ki
    float32 ftMaxVbusLoop;       ///< Bus voltage loop Max output
    float32 ftMinVbusLoop;       ///< Bus voltage loop Min output

    float32 ftKpCurrLoop;        ///< Current loop Kp
    float32 ftKiCurrLoop;        ///< Current loop Ki
    float32 ftMaxCurrLoop;       ///< Current loop Max output
    float32 ftMinCurrLoop;       ///< Current loop Min output

    float32 ftKpVoltLoop;        ///< Voltage loop Kp
    float32 ftKiVoltLoop;        ///< Voltage loop Ki
    float32 ftMaxVoltLoop;       ///< Voltage loop Max output
    float32 ftMinVoltLoop;       ///< Voltage loop Min output

    float32 ftKpIdPosLoop;       ///< Current loop Kp
    float32 ftKiIdPosLoop;       ///< Current loop Ki
    float32 ftMaxIdPosLoop;      ///< Current loop Max output
    float32 ftMinIdPosLoop;      ///< Current loop Min output

    float32 ftKpIdNegLoop;       ///< Current loop Kp
    float32 ftKiIdNegLoop;       ///< Current loop Ki
    float32 ftMaxIdNegLoop;      ///< Current loop Max output
    float32 ftMinIdNegLoop;      ///< Current loop Min output

    float32 ftKpVdPosLoop;       ///< Voltage loop Kp
    float32 ftKiVdPosLoop;       ///< Voltage loop Ki
    float32 ftMaxVdPosLoop;      ///< Voltage loop Max output
    float32 ftMinVdPosLoop;      ///< Voltage loop Min output

    float32 ftKpVdNegLoop;       ///< Voltage loop Kp
    float32 ftKiVdNegLoop;       ///< Voltage loop Ki
    float32 ftMaxVdNegLoop;      ///< Voltage loop Max output
    float32 ftMinVdNegLoop;      ///< Voltage loop Min output

    float32 ftKrCurrLoopPR1st;   ///< Current loop 1st PR Kr
    float32 ftWcCurrLoopPR1st;   ///< Current loop 1st PR Wc
    float32 ftMaxCurrLoopPR1st;  ///< Current loop 1st PR Max output
    float32 ftMinCurrLoopPR1st;  ///< Current loop 1st PR Min output
    float32 ftKrCurrLoopPR3rd;   ///< Current loop 3rd PR Kr
    float32 ftWcCurrLoopPR3rd;   ///< Current loop 3rd PR Wc
    float32 ftMaxCurrLoopPR3rd;  ///< Current loop 3rd PR Max output
    float32 ftMinCurrLoopPR3rd;  ///< Current loop 3rd PR Min output
    float32 ftKrCurrLoopPR5th;   ///< Current loop 5th PR Kr
    float32 ftWcCurrLoopPR5th;   ///< Current loop 5th PR Wc
    float32 ftMaxCurrLoopPR5th;  ///< Current loop 5th PR Max output
    float32 ftMinCurrLoopPR5th;  ///< Current loop 5th PR Min output
    float32 ftKrCurrLoopPR7th;   ///< Current loop 7th PR Kr
    float32 ftWcCurrLoopPR7th;   ///< Current loop 7th PR Wc
    float32 ftMaxCurrLoopPR7th;  ///< Current loop 7th PR Max output
    float32 ftMinCurrLoopPR7th;  ///< Current loop 7th PR Min output
    float32 ftKrCurrLoopPR9th;   ///< Current loop 9th PR Kr
    float32 ftWcCurrLoopPR9th;   ///< Current loop 9th PR Wc
    float32 ftMaxCurrLoopPR9th;  ///< Current loop 9th PR Max output
    float32 ftMinCurrLoopPR9th;  ///< Current loop 9th PR Min output
    float32 ftKrCurrLoopPR15th;  ///< Current loop 15th PR Kr
    float32 ftWcCurrLoopPR15th;  ///< Current loop 15th PR Wc
    float32 ftMaxCurrLoopPR15th; ///< Current loop 15th PR Max output
    float32 ftMinCurrLoopPR15th; ///< Current loop 15th PR Min output

    float32 ftKpVacLoop;         ///< AC voltage loop Kp
    float32 ftKiVacLoop;         ///< AC voltage loop Ki
    float32 ftMaxVacLoop;        ///< AC voltage loop Max output
    float32 ftMinVacLoop;        ///< AC voltage loop Min output

    float32 ftQzVacLoopRep;      ///< AC voltage repeat control loop Qz
    float32 ftKrCompVacLoopRep;  ///< AC voltage repeat control loop compensation Kr
    Uint16  uiNrPhaCompVacLoopRep; ///< AC voltage repeat control loop phase compensation number
    float32 ftOutpMaxVacLoopRep; ///< AC voltage repeat control loop MAX output

    float32 ftKrVacLoopPR1st;    ///< AC voltage loop 1st PR Kr
    float32 ftWcVacLoopPR1st;    ///< AC voltage loop 1st PR Wc
    float32 ftMaxVacLoopPR1st;   ///< AC voltage loop 1st PR Max output
    float32 ftMinVacLoopPR1st;   ///< AC voltage loop 1st PR Min output
    float32 ftKrVacLoopPR3rd;    ///< AC voltage loop 3rd PR Kr
    float32 ftWcVacLoopPR3rd;    ///< AC voltage loop 3rd PR Wc
    float32 ftMaxVacLoopPR3rd;   ///< AC voltage loop 3rd PR Max output
    float32 ftMinVacLoopPR3rd;   ///< AC voltage loop 3rd PR Min output
    float32 ftKrVacLoopPR5th;    ///< AC voltage loop 5th PR Kr
    float32 ftWcVacLoopPR5th;    ///< AC voltage loop 5th PR Wc
    float32 ftMaxVacLoopPR5th;   ///< AC voltage loop 5th PR Max output
    float32 ftMinVacLoopPR5th;   ///< AC voltage loop 5th PR Min output
    float32 ftKrVacLoopPR7th;    ///< AC voltage loop 7th PR Kr
    float32 ftWcVacLoopPR7th;    ///< AC voltage loop 7th PR Wc
    float32 ftMaxVacLoopPR7th;   ///< AC voltage loop 7th PR Max output
    float32 ftMinVacLoopPR7th;   ///< AC voltage loop 7th PR Min output
}ST_COMTBL_PFCPOWCTRL;

typedef struct
{
    Uint16 uiEnaFltRstrt;
    Uint16 uiEnaD2dFltCpuRstrt;
    Uint16 uiEnaD2dFltClaRstrt;

    UN_PFC_FLT_WORD1 unEnaPfcFltRstrt1;
    UN_PFC_FLT_WORD2 unEnaPfcFltRstrt2;
    UN_PFC_FLT_WORD3 unEnaPfcFltRstrt3;
    UN_SYS_FLT_WORD  unEnaSysFltRstrt;
}ST_COMTBL_FLT_RSTRT;

typedef struct
{
    Uint16 uiHandControl; ///< 1:hand made 0:auto
    Uint16 uiModulEnabl[3]; ///< module enable
    Uint16 uiClearRedFlt;   ///< Clear Redundant Fault
    Uint16 uiOTAModulFpga;      ///< OTA Modul Fpga
    Uint16 uiCloseRely;
    Uint16  uiPeriodCHB;         ///< CHB PWM Period counter value
    Uint16  uiDischargeVolCHBA;         ///< CHB PWM Period counter value
    Uint16  uiDischargeVolCHBB;
    Uint16  uiDischargeVolCHBC;
    Uint16  uiHalfBusBlanceEn;         ///< CHB PWM Period counter value
    Uint16  uiFltDataRec;           ///< FPGA Data record

    Uint16  uiRedundantA;
    Uint16  uiRedundantB;
    Uint16  uiRedundantC;
    Uint16  uiRedunAEnable;
    Uint16  uiRedunBEnable;
    Uint16  uiRedunCEnable;
    Uint16  uiRunAEnable;
    Uint16  uiRunBEnable;
    Uint16  uiRunCEnable;
	Uint16  uiSOCBlanceEn;             ///< SOC Blance enable
    float32  ftSUMOCPValue;
    float32  ftD2dPwmPeriodPowCell;  ///< DAB PWM Period counter value
    float32  ftD2dPwmDeadTimePowCell; ///< DAB PWM dead time

    float32  ftPwmDutyTarget;     ///< DAB PWM DUTY

}ST_COMTBL_FPGACMD;

typedef struct
{
    ST_COMTBL_PFC_RATED_PARM1     stPrmPfcRtd1;
    ST_COMTBL_PFC_RATED_PARM2     stPrmPfcRtd2;
    ST_COMTBL_PFC_HARDWARE_PARM   stPrmPfcHw;
    UN_PFC_FLT_WORD1              unWordPfcFlt1;
    UN_PFC_FLT_WORD1              unWordPfcFltSts1;
    UN_PFC_FLT_WORD1              unWordPfcFltMask1;
    UN_PFC_FLT_WORD2              unWordPfcFlt2;
    UN_PFC_FLT_WORD2              unWordPfcFltSts2;
    UN_PFC_FLT_WORD2              unWordPfcFltMask2;
    UN_PFC_FLT_WORD3              unWordPfcFlt3;
    UN_PFC_FLT_WORD3              unWordPfcFltSts3;
    UN_PFC_FLT_WORD3              unWordPfcFltMask3;
    UN_SYS_FLT_WORD               unWordSysFlt;
    UN_SYS_FLT_WORD               unWordSysFltSts;
    UN_SYS_FLT_WORD               unWordSysFltMask;
    ST_COMTBL_OFFGRID_CMD         stPrmOffGridCtrl;
    ST_COMTBL_ONGRID_CMD          stPrmOnGridCtrl;
    ST_COMTBL_BALBRDG_CMD         stPrmBalBrdg;
    ST_COMTBL_VOLTRAMP_CMD        stPrmPfcVoltRamp;
    ST_COMTBL_POWERCTRL           stPrmPwrCtrl;
    ST_COMTBL_VOLT_FRQ_PROT       stPrmGridVoltProt;
    ST_COMTBL_VOLT_FRQ_PROT       stPrmGridFrqProt;
    ST_COMTBL_FRQ_CTL             stPrmPwrRespHF;
    ST_COMTBL_FRQ_CTL             stPrmPwrRespLF;
    ST_COMTBL_QU_CTL              stPrmReactvQu;
    ST_COMTBL_QP_CTL              stPrmReactvQp;
    ST_COMTBL_GVRT                stPrmHvrt;
    ST_COMTBL_GVRT                stPrmLvrt;
    ST_COMTBL_PU_CTL              stPrmPu;
    ST_COMTBL_RTD_PRM             stRtdPrm;    ///< Rated parameter
    ST_COMTBL_COMIF            	  stPrmComIf;
    ST_COMTBL_CMNADC           	  stPrmCmnAdc;
    ST_COMTBL_CMNDIAG          	  stPrmCmnDiag;
    ST_COMTBL_D2DDIAG          	  stPrmD2dDiag;
    ST_COMTBL_POWLIM           	  stPrmPowLim;
    ST_COMTBL_GRID_DC_CTL         stPrmDcCpt;
    ST_COMTBL_PERPHCTRL        	  stPrmPerphCtrl;
    ST_COMTBL_PFCPOWCTRL          stPrmPfcPowCtrl;
    ST_COMTBL_D2DPOWPRECTRL    	  stPrmD2dPowPreCtrl;
    ST_PRM_D2D_POW_CTRL           stPrmD2dPowCtrl;
    ST_COMTBL_FLT_RSTRT           stPrmFltRstrt;
    ST_COMTBL_IDC_PROT            stIdcPrt;
    ST_COMTBL_FPGACMD             stPrmToFpga;
}ST_COM_TBL;

/* ST_COM Typedef*/
typedef struct
{
    int16  siVgZero_A;             ///< 3-phase grid voltage zero-shift value
    int16  siVgZero_B;
    int16  siVgZero_C;

    int16  siVgInvZero_A;          ///< 2-phase inverter voltage zero-shift value
    int16  siVgInvZero_B;

    int16  siIgZero_A;             ///< 3-phase grid current zero-shift value
    int16  siIgZero_B;
    int16  siIgZero_C;
    int16  siIgZero_N;             ///< Balance bridge current zero-shift value

    int16  siVgDcZero_A;           ///< 3-phase grid voltage DC component zero-drift value
    int16  siVgDcZero_B;
    int16  siVgDcZero_C;

    int16  siIgDcZero_A;           ///< 3-phase grid current DC component zero-drift value
    int16  siIgDcZero_B;
    int16  siIgDcZero_C;

    int16  siIgDcZero_A_N;         ///< 3-phase grid current DC component zero-drift value(Relay N ON)
    int16  siIgDcZero_B_N;
    int16  siIgDcZero_C_N;

    int16  siBusVoltZero;          ///< Bus voltage zero-shift value
    int16  siPosBusVoltZero;       ///< Positive half bus voltage zero-shift value
    int16  siNegBusVoltZero;       ///< Negative half bus voltage zero-shift value

    float32 ftVaK;                 ///< Va calibration coefficient
    float32 ftVbK;                 ///< Vb calibration coefficient
    float32 ftVcK;                 ///< Vc calibration coefficient
    float32 ftVaInvK;              ///< VaInv calibration coefficient
    float32 ftVbInvK;              ///< VbInv calibration coefficient
    float32 ftIaK;                 ///< Ia calibration coefficient
    float32 ftIbK;                 ///< Ib calibration coefficient
    float32 ftIcK;                 ///< Ic calibration coefficient
    float32 ftInK;                 ///< In calibration coefficient
    float32 ftVBusK;               ///< Bus voltage calibration coefficient
    float32 ftVPosBusK;            ///< Positive bus voltage calibration coefficient
    float32 ftVNegBusK;            ///< Negative bus voltage calibration coefficient
}ST_COM_NONERASEPRM;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 uiModPowCtrl      :   1;    ///< bit0    - Power control mode: 0U-Grid standard mode; 1U-ARM control mode
        Uint16 uiModActvImbal    :   1;    ///< bit1    - Active power imbalance run bit
        Uint16 uiModActvArmCtrl  :   2;    ///< bit2~3  - ARM active power control mode bit: 0U- active power mode; 1U- P/F mode
        Uint16 uiModReactvImbal  :   1;    ///< bit4    - Reactive power imbalance run bit
        Uint16 uiModReactvArmCtrl:   2;    ///< bit5~6  - ARM reactive power control mode bit: 0U- reactive power mode; 1U- Q/U mode
        Uint16 uiRsvd            :   9;    ///< bit7~15 - Reserved
    }bit;
}UN_COM_PFC_POW_MODE;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 uiEnaBld     :    1;        ///< bit0 - Bleeder command enable bit
        Uint16 uiEnaV2L     :    1;        ///< bit1 - V2L enable bit
        Uint16 uiEnaAuxPwr  :    1;        ///< bit2 - Auxiliary power enable bit
        Uint16 uiEnaAcRly   :    1;        ///< bit3 - AC relay enable bit
        Uint16 uiEnaAcRlyA  :    1;        ///< bit4 - AC relay A enable bit
        Uint16 uiEnaAcRlyB  :    1;        ///< bit5 - AC relay B enable bit
        Uint16 uiEnaAcRlyC  :    1;        ///< bit6 - AC relay C enable bit
        Uint16 uiEnaAcRlyN  :    1;        ///< bit7 - AC relay N enable bit
        Uint16 uiEnaBusUV   :    1;        ///< bit8 - Bus under voltage test enable bit
        Uint16 uiEnFctPwm   :    1;        ///< bit9 - 11kW FCT PWM test enable bit
        Uint16 uiRsvd       :    6;        ///< bit10~15 - Reserved
    }bit;
}UN_FCT_CMD;

typedef struct
{
    float32 ftPwrChrgReq;         ///< Charge power request
    float32 ftPwrActvReq;         ///< Active power request
    float32 ftPwrReactvReq;       ///< Reactive power ratio request
    float32 ftPFReq;              ///< PF request
    float32 ftVoltAcV2LReq;       ///< V2L voltage request
    float32 ftFrqAcV2LReq;        ///< V2L frequency request
    float32 ftPaAcReq;            ///< AC PhaseA active request
    float32 ftPbAcReq;            ///< AC PhaseB active request
    float32 ftPcAcReq;            ///< AC PhaseC active request
    float32 ftQaAcReq;            ///< AC PhaseA reactive request
    float32 ftQbAcReq;            ///< AC PhaseB reactive request
    float32 ftQcAcReq;            ///< AC PhaseC reactive request

    float32 ftCoeffKBattVoltCal;      ///< Battery voltage calibration coefficient K
    float32 ftCoeffBBattVoltCal;      ///< Battery voltage calibration coefficient B
    float32 ftCoeffKBattCurrCal;      ///< Battery current calibration coefficient K
    float32 ftCoeffBBattCurrCal;      ///< Battery current calibration coefficient B
    float32 ftCoeffKBattDwnVoltCal;   ///< Battery down voltage calibration coefficient K
    float32 ftCoeffBBattDwnVoltCal;   ///< Battery down voltage calibration coefficient B
    float32 ftCoeffKBattDwnCurrCal;   ///< Battery down current calibration coefficient K
    float32 ftCoeffBBattDwnCurrCal;   ///< Battery down current calibration coefficient B
    float32 ftCurrAcRmsLim;           ///< AC current RMS limit

    Uint16 uiModeReactv;           ///< Reactive power mode in grid standard mode
    Uint16 uiCmdPfcADZeroAdj;
    Uint16 uiModRunReq;       ///< Run mode request
    Uint16 uiCmdRunReq;       ///< Run command request
    Uint16 uiStgRunEnReq;     ///< Run stage enable request
    Uint16 uiStArm;           ///< ARM state
    Uint16 uiStdGridSet;      ///< Grid standard
    Uint16 uiTypeGrid;        ///< Grid type
    Uint16 uiFlgUpgProg;      ///< Program upgrade flag
    Uint16 uiComFailCntr;     ///< Communication fail counter
    Uint16 uiEnaSelfTest;     ///< Italy Self test enable
    Uint16 uiFltSelfTest;     ///< Self test fault
    Uint16 uiFlgTxMsg;        ///< Transmit message flag
    Uint16 uiCmdCode;         ///< Command code
    Uint16 uiByteTx[8];       ///< Send Byte
    Uint16 uiFlgReadReq;      ///< Read request flag


    float32 ftVoltBattChrgReq;    ///< Charge battery voltage request
    float32 ftCurrBattChrgReq;    ///< Charge battery current request
    float32 ftVoltBattDchaReq;    ///< Discharge battery voltage request
    float32 ftCurrBattDchaReq;    ///< Discharge battery current request
    float32 ftVoltBattBms;        ///< Battery voltage from BMS
    float32 ftVoltBattBmsMax;     ///< Max battery voltage from BMS

    float32 ftTempArmBd;          ///< ARM board temperature
    float32 ftTempNtc0;           ///< NTC0 temperature: AC Terminal temperature
    float32 ftTempNtc1;           ///< NTC1 temperature: 7.4-PFC slow MOS NTC temperature, 11-reserved
    float32 ftTempNtc2;           ///< NTC2 temperature: 7.4-PFC quick MOS NTC temperature, 11-PFC-MOS
    float32 ftTempNtc3;           ///< NTC3 temperature: 7.4-D2D up NTC temperature, 11-D2D primary side MOS
    float32 ftTempNtc4;           ///< NTC4 temperature: 7.4-D2D down NTC temperature, 11-D2D secondary side MOS
    float32 ftTempNtc5;           ///< NTC5 temperature: 7.4-D2D transformer NTC temperature, 11-D2D magnetic medium
    float32 ftTempNtc6;           ///< NTC6 temperature: 7.4-D2D inductor NTC temperature, 11-reserved

    float32 ftPowBattMax;         ///< Max battery power
    float32 ftQAcMax;             ///< Max AC reactive power
    float32 ftQOnePhaMax;         ///< One phase Max reactive power
    float32 ftIdAcRtd;            ///< Rated AC active current amplitude
    float32 ftIqAcRtd;            ///< Rated AC reactive current amplitude
    float32 ftCurrBattMaxChrg;    ///< Max battery current in charge mode
    float32 ftCurrBattMaxBidir;   ///< Max battery current in bi-direction mode

    UN_FCT_CMD            unCmdFct;             ///< FCT Command
    UN_SYS_TIME           unTiSys;              ///< System time
    UN_SYS_TIME           unTiReq;              ///< Fault time request
    UN_COM_PFC_POW_MODE   unModPfcPow;          ///< PFC power mode
    UN_CAN_MAIL_BOX_ID    unIDMaskTx;           ///< Transmit ID mask
    ST_COM_NONERASEPRM    stPrmPfcAdjCoeff;
}ST_COM;

//=====================================================
//    Variable Declaration
//=====================================================
extern ST_COM stCom;
extern ST_COM_TBL stComTbl;

extern ST_C1_TO_C2_PRM stPrmC1ToC2;
extern ST_C2_TO_C1_PRM stPrmC2ToC1;

#if (1U == COM_DBG)
extern ST_COM stComDbg;
#endif

#endif /* COMEXT_H_ */
//===========================================================================
// End of file.
//===========================================================================

