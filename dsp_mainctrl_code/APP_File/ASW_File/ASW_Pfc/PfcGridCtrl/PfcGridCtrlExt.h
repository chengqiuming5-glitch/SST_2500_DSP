//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcGridCtrlExt.h
* TITLE         : Header file of PFC on&off-grid control external parameter and function
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

#ifndef PFCGRIDCTRLEXT_H_
#define PFCGRIDCTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_GRIDCTRL_DBG    0U

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16  uiFlgStrt;                      ///< On-grid start power ramp flag
    Uint16  uiFlgHF;                        ///< High frequency power response ramp flag
    Uint16  uiFlgLF;                        ///< Low frequency power response ramp flag
    Uint16  uiFlgPU;                        ///< Grid voltage power response ramp flag

    Uint16  uiFlgGridChkOk;                 ///< Grid check ok flag
    Uint16  uiFlgGridChkNo;                 ///< Grid check not ok flag

    int16   siPwrLimHF;                     ///< High frequency power limit
    int16   siPwrLimLF;                     ///< Low frequency power limit
    int16   siPwrLimPU;                     ///< Grid voltage power limit

    int16   siPwrSet;                       ///< Active power control module output power value
    float32 ftRatePwrUp;                    ///< Active power control module output power up rate value
    float32 ftRatePwrDwn;                   ///< Active power control module output power down rate value
}ST_PFC_GRIDCTRL_ACTVPOWER_OUTP;

typedef struct
{
    float32  ftTi1stOrdLpfResp;             ///< Reactive power first order LPF response time
    float32  ftPwrSet;                      ///< Reactive module output value-reactive power
}ST_PFC_GRIDCTRL_REACTVPOWER_OUTP;

typedef struct
{
    Uint16   uiFlgFrqChk;                   ///< Frequency check flag
    Uint16   uiFlgHvrt;                     ///< HVRT flag
    Uint16   uiFlgLvrt;                     ///< LVRT flag
    Uint16   uiFlgHvrtOvTi;                 ///< HVRT over time flag
    Uint16   uiFlgLvrtOvTi;                 ///< LVRT over time flag
    Uint16   uiFlgIdRcvVrt;                 ///< VRT Id recovery flag
    float32  ftIdPosRef;                    ///< VRT output Id-positive reference
    float32  ftIqPosRef;                    ///< VRT output Iq-positive reference
}ST_PFC_GRIDCTRL_VRT_OUTP;

typedef struct
{
    Uint16  uiFltAi;                       ///< Anti-Island fault
    float32 ftIqAiDstbc;                   ///< Anti-Island module output Iq disturbance
    float32 ftVaDcInhb;                    ///< Voltage dc component inhibition module output phase A disturbance
    float32 ftVbDcInhb;                    ///< Voltage dc component inhibition module output phase B disturbance
    float32 ftVcDcInhb;                    ///< Voltage dc component inhibition module output phase C disturbance
    float32 ftIaDcInhb;                    ///< Current dc component inhibition module output phase A disturbance
    float32 ftIbDcInhb;                    ///< Current dc component inhibition module output phase B disturbance
    float32 ftIcDcInhb;                    ///< Current dc component inhibition module output phase C disturbance
}ST_PFC_GRIDCTRL_DSTBC_OUTP;

typedef union
{
    Uint16 all;

    /* The parameter of struct can not be modified, Otherwise, you need to modify the code  */
    struct
    {
        /*00*/    Uint16 uiFlgOV1st      :1;    ///< Over voltage 1 level protection flag
        /*01*/    Uint16 uiFlgOV2nd      :1;    ///< Over voltage 2 level protection flag
        /*02*/    Uint16 uiFlgOV3rd      :1;    ///< Over voltage 3 level protection flag
        /*03*/    Uint16 uiFlgOV4st      :1;    ///< Over voltage 4 level protection flag
        /*04*/    Uint16 uiFlgOV5st      :1;    ///< Over voltage 5 level protection flag
        /*05*/    Uint16 uiFlgUV1st      :1;    ///< Under voltage 1 level protection flag
        /*06*/    Uint16 uiFlgUV2nd      :1;    ///< Under voltage 2 level protection flag
        /*07*/    Uint16 uiFlgUV3rd      :1;    ///< Under voltage 3 level protection flag
        /*08*/    Uint16 uiFlgUV4st      :1;    ///< Under voltage 4 level protection flag
        /*09*/    Uint16 uiFlgUV5st      :1;    ///< Under voltage 5 level protection flag
        /*10*/    Uint16 uiFlgOV10min    :1;    ///< Over voltage 10min protection flag
        /*11*/    Uint16 uiRsvd1         :1;
        /*12~15*/ Uint16 uiRsvd2         :4;
    }bit;
}UN_VOLTPROT_OUT;

typedef union
{
    Uint16 all;
    struct
    {
        /*00*/    Uint16 uiFlgOF1st      :1;///< Over frequency 1 level protection flag
        /*01*/    Uint16 uiFlgOF2nd      :1;///< Over frequency 2 level protection flag
        /*02*/    Uint16 uiFlgOF3rd      :1;///< Over frequency 3 level protection flag
        /*03*/    Uint16 uiFlgOF4st      :1;///< Over frequency 4 level protection flag
        /*04*/    Uint16 uiFlgOF5st      :1;///< Over frequency 5 level protection flag
        /*05*/    Uint16 uiFlgUF1st      :1;///< Under frequency 1 level protection flag
        /*06*/    Uint16 uiFlgUF2nd      :1;///< Under frequency 2 level protection flag
        /*07*/    Uint16 uiFlgUF3rd      :1;///< Under frequency 3 level protection flag
        /*08*/    Uint16 uiFlgUF4st      :1;///< Under frequency 4 level protection flag
        /*09*/    Uint16 uiFlgUF5st      :1;///< Under frequency 5 level protection flag
        /*10*/    Uint16 uiRsvd1         :1;
        /*11~15*/ Uint16 uiRsvd2         :5;
    }bit;
}UN_FRQPROT_OUT;

typedef struct
{
    Uint16   uiResult;                      ///< Test result: 0-testing; 1-pass
    Uint16   uiValSet;                      ///< Trip value set: voltage or frequency-0.1V/0.01Hz
    Uint16   uiTiSet;                       ///< Trip time set: 0.01s
    Uint16   uiValTrip;                     ///< Trip value: voltage or frequency-0.1V/0.01Hz
    Uint16   uiTiTrip;                      ///< Trip time: 0.01s
    Uint16   uiVoltTrip;                    ///< Grid voltage at the trigger moment/0.1V
    Uint16   uiFrqTrip;                     ///< Grid frequency at the trigger moment/0.01Hz
}ST_SELF_TEST_OUTP;

typedef struct
{
    UN_VOLTPROT_OUT unVoltProt;
    UN_FRQPROT_OUT  unFrqProt;

    ST_SELF_TEST_OUTP st59S1;               ///< Grid over voltage protection-S1
    ST_SELF_TEST_OUTP st59S2;               ///< Grid over voltage protection-S2
    ST_SELF_TEST_OUTP st27S1;               ///< Grid under voltage protection-S1
    ST_SELF_TEST_OUTP st27S2;               ///< Grid under voltage protection-S2
    ST_SELF_TEST_OUTP st81OvS1;             ///< Grid over frequency protection-S1
    ST_SELF_TEST_OUTP st81OvS2;             ///< Grid over frequency protection-S2
    ST_SELF_TEST_OUTP st81UnS1;             ///< Grid under frequency protection-S1
    ST_SELF_TEST_OUTP st81UnS2;             ///< Grid under frequency protection-S2

    Uint16  uiStsSelfTest;                  ///< Self-test status
    Uint16  uiFltIdcOv;                     ///< Idc over fault
    Uint16  uiFltRoCoF;                     ///< RoCoF fault protection
}ST_PFC_GRIDCTRL_DET_OUTP;

typedef struct
{
    ST_PFC_GRIDCTRL_ACTVPOWER_OUTP   stActvCtrl;
    ST_PFC_GRIDCTRL_REACTVPOWER_OUTP stReactv;
    ST_PFC_GRIDCTRL_VRT_OUTP         stVrt;
    ST_PFC_GRIDCTRL_DSTBC_OUTP       stDstbc;
    ST_PFC_GRIDCTRL_DET_OUTP         stGridDet;
}ST_PFC_GRIDCTRL_OUTP;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_GRIDCTRL_OUTP stPfcGridCtrl;
//==============================================================================================
//    Global Function Declaration
//==============================================================================================

#endif /* PFCGRIDCTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
