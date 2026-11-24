//========================================================================
// FILE          : Comm.h
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
* @file         Com.h
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

#ifndef COM_H_
#define COM_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "ComExt.h"

#include "ComIfExt.h"
#include "CmnAdcExt.h"
#include "D2dAdcExt.h"
#include "PfcDataCalcExt.h"
#include "CmnDiagExt.h"
#include "D2dDiagExt.h"
#include "OnOffGridSwtExt.h"
#include "PfcStMacExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "PfcGridCtrlExt.h"
#include "EepExt.h"
#include "ComDrvExt.h"
#include "DSPParaData.h"
#include "GridStdData.h"
#include "BSW_Cfg.h"
#include "SpiExt.h"
#include "F2837xD_Ipc_drivers.h"

//=====================================================
//    Macro Definition
//=====================================================
/* Command */
#define CAN_OUT_VOLT_ADJ_CMD              0x01U    ///< Output Voltage Adjusting
#define CAN_OUT_CURR_ADJ_CMD              0x02U    ///< Output Current Adjusting
#define CAN_OUT_VOLT_DN_ADJ_CMD           0x03U    ///< Down Output Voltage Adjusting
#define CAN_OUT_CURR_DN_ADJ_CMD           0x04U    ///< Down Output Current Adjusting
#define CAN_AC_VOLT_ADJ_CMD               0x05U    ///< AC Voltage Adjusting
#define CAN_AC_CURR_ADJ_CMD               0x06U    ///< AC Current Adjusting
#define CAN_PFC_ZERO_ADJ_CMD              0x07U    ///< PFC ADZero Adjusting
#define CAN_PFC_STD_CMD                   0x08U    ///< PFC Standard Parameter
#define CAN_VAC_READ_CMD                  0x09U    ///< INV AC Volt Read
#define CAN_PARAM_SET_CMD                 0x10U    ///< Parameter Setting
#define CAN_PARAM_READ_CMD                0x11U    ///< Parameter Read
#define CAN_GRID_TYPE_CMD                 0x12U    ///< Grid Type command
#define CAN_RUN_ORD_CMD                   0x20U    ///< Run Command
#define CAN_VOLT_CURR_CMD                 0x21U    ///< Voltage and Current command
#define CAN_GRID_CTRL_CMD                 0x22U    ///< Grid Control Setting
#define CAN_OP_DATA_READ_CMD              0x23U    ///< Operation Data Read
#define CAN_THREE_PHASE_ACTV_POW_CMD      0x24U    ///< Three phase power command
#define CAN_TEMP1_CMD                     0x25U    ///< Temperature1 command
#define CAN_TEMP2_CMD                     0x26U    ///< Temperature2 command
#define CAN_THREE_PHASE_REACTV_POW_CMD    0x27U    ///< Three phase power command
#define CAN_TEST_DATA_READ_CMD            0x28U    ///< Self Test Data Read
#define CAN_DATA_RECORD_CMD               0x60U    ///< Data Record
#define CAN_TIME_SYCN_CMD                 0x61U    ///< Time Synchronization
#define CAN_FCT_CMD                       0x71U    ///< FCT Command
#define CAN_TABLE_VER_CMD                 0xAAU    ///< Table Version
#define CAN_MAIN_DSP_UPG_CMD              0xF1U    ///< Main DSP Upgrade
#define CAN_CPLDUPD_RDY_CMD               0xE0U    ///< CPLD Upgrade Ready command
#define CAN_CPLDUPD_NOTICE_CMD            0xE1U    ///< CPLD Upgrade Notice command
#define CAN_CPLDUPD_ERASE_CMD             0xE2U    ///< CPLD Upgrade Erase command
#define CAN_CPLDUPD_RX_CMD                0xE3U    ///< CPLD Upgrade receive command
#define CAN_CPLDUPD_CHK_CMD               0xE4U    ///< CPLD Upgrade Check command
#define CAN_CPLDUPD_STOP_CMD              0xE5U    ///< CPLD Upgrade Stop command

#define CAN_CPU2_UPG1_CMD                 0xF6U    ///< CPU2 Upgrade1
#define CAN_CPU2_UPG2_CMD                 0xF7U    ///< CPU2 Upgrade2
#define CAN_CPU2_UPG3_CMD                 0xF8U    ///< CPU2 Upgrade3
#define CAN_CPU2_UPG4_CMD                 0xF9U    ///< CPU2 Upgrade4
#define CAN_CPU2_UPG5_CMD                 0xFAU    ///< CPU2 Upgrade5

/* CPLD Upgrade Macro Definition */
#define FLASH_CPLD_START_ADDRESS          0x0000U
#define UPGRADE_SUCCESS                   0x5555U  ///< Upgrade Successful
#define UPGRADE_FAIL                      0xAAAAU  ///< Upgrade fail
#define STOP_SUCCESS                      0x5555U  ///< Stop successful
#define STOP_FAIL                         0xAAAAU  ///< Stop fail
#define STOP_UPGRADE_CMD                  0x1111U  ///< Stop Upgrade command
#define NUM_SUB_FRM_WR_EN                 22U      ///< Frame Sub Num Write enable
#define SIZE_WR_FRM_CPLDUPD               128U     ///< Per Write size CPLD Upd
#define BLOCK1_FRIST_ADDR                 0x00000U ///< Block 1 first address
#define BLOCK2_FRIST_ADDR                 0x10000U ///< Block 2 first address
#define BLOCK3_FRIST_ADDR                 0x20000U ///< Block 3 first address
#define BLOCK4_FRIST_ADDR                 0x30000U ///< Block 4 first address
/* Adjusting Range Macro Definition */
#define ADJ_COFK_MIN                      0.8f     ///< Adjusting Coefficient K Min
#define ADJ_COFK_MAX                      1.2f     ///< Adjusting Coefficient K Max
#define VOLT_ADJ_COFB_MIN                 -30.0f   ///< Voltage Adjusting Coefficient B Min
#define VOLT_ADJ_COFB_MAX                 30.0f    ///< Voltage Adjusting Coefficient B Max
#define CURR_ADJ_COFB_MIN                 -1.0f    ///< Current Adjusting Coefficient B Min
#define CURR_ADJ_COFB_MAX                 5.0f     ///< Current Adjusting Coefficient B Max
#define ADJ_INTL_NUM                      5U       ///< Adjusting interval number

#define CAN_V2G_MODE_PRM                  0x5555U  ///< V2G mode
#define CAN_V2L_MODE_PRM                  0xFFFFU  ///< V2L mode

#define CAN_SRC_ARM                       0xFEU    ///< Source is ARM
#define CAN_SRC_PC                        0xFFU    ///< Source is PC
#define CAN_DST_DSP                       0x00U    ///< Destination is DSP
#define CAN_DST_GROUP                     0xFFU    ///< Destination is Group

#define SELF_TEST_OVER_TIME              (15U*60U)    ///< Self test 15min over time

#define CURR_LMT_X_CAP_COMP              (1.3f*RATED_AC_VOLT_RMS*PI_2_CONST*((float32)GRID_FRQ_MAX)*PFC_INPUT_X_CAP)         ///< AC input X-capacitor reactive current compensation limit

#define COEFF_BUS_PRE_CHRG_3P             1.414f//2.37f     ///< Three-phase bus pre-charge coefficient
#if 2U == GRID_PHASE_NUMBER
#define COEFF_BUS_PRE_CHRG_1P             2.58f     ///< Single-phase bus pre-charge coefficient
#define VOLT_GRID_OV_CHRG                 132.0f    ///< Charge mode grid over voltage value
#define VOLT_GRID_UV_CHRG                 49.5f     ///< Charge mode grid under voltage value
#else
#define COEFF_BUS_PRE_CHRG_1P             2.65f     ///< Single-phase bus pre-charge coefficient
#define VOLT_GRID_OV_CHRG                 264.0f    ///< Charge mode grid over voltage value
#define VOLT_GRID_UV_CHRG                 114.0f    ///< Charge mode grid under voltage value
#endif

#define FRQ_GRID_OF_CHRG                  60.24f    ///< Charge mode grid over frequency value
#define FRQ_GRID_UF_CHRG                  49.8f     ///< Charge mode grid under frequency value

/* Fault Data Read macro definition */
#define SIZE_TI_DATA                      4U
#define SIZE_PER_FRAME                    3U
#define WORDS_FLT_DATA_READ_TOTAL         (SIZE_TI_DATA + SIZE_POW_PRM_TYP_FLT_REC*SIZE_POW_PRM_NUM_FLT_REC + SIZE_TEMP_DATA_FLT_REC + SIZE_FAULT_WORD_FLT_REC)
#define NUM_REM_FLT_DATA_READ             (WORDS_FLT_DATA_READ_TOTAL % SIZE_PER_FRAME)    ///< Remainder number of fault data
#if 0U == NUM_REM_FLT_DATA_READ
#define FRAME_FLT_DATA_READ_TOTAL         (WORDS_FLT_DATA_READ_TOTAL / SIZE_PER_FRAME)
#else
#define FRAME_FLT_DATA_READ_TOTAL         ((WORDS_FLT_DATA_READ_TOTAL / SIZE_PER_FRAME) + 1U)
#endif

#define IPC_COM_OVER_TI                   6000000UL   ///< nearby 600ms
//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
/* CAN Typedef */
typedef enum
{
    TYPE_2K2W,          ///< 2.2kW
    TYPE_22KW,          ///< 22kW
    TYPE_11KW,          ///< 11kW
    TYPE_SST,
    TYPE_6K6W_3I1,
    TYPE_3KW,
    TYPE_6K6W_BIDIR,
    TYPE_20KW,
    TYPE_IEC7K4W,       ///< IEC7.4kW
    TYPE_IEC11KW,       ///< IEC11kW
    TYPE_UL19K2W,       ///< UL19.2kW
    TYPE_GB22KW
}EN_CAN_MECH_TYPE;

typedef struct
{
    UN_CAN_MAIL_BOX_ID IDMask;          ///< Function Code
    Uint16             Data1;           ///< Data1
    Uint16             Data2;           ///< Data2
    Uint16             Data3;           ///< Data3
    Uint16             Data4;           ///< Data 4
}ST_CAN_DATA;


typedef union
{
    Uint16 all;
    struct
    {
        Uint16 RdWrStat    :2;    ///< 1:0 Read or Write Status: 00b-Read, 11b-Write
        Uint16 CmdType     :3;    ///< 4:2 001bRead data record, 010b-Read data configuration, 011b-Read Packet
        Uint16 TrigCmd     :1;    ///< 5 1b-Trigger Command,0b-invalid
        Uint16 ON_Cmd      :1;    ///< 6 1b-Turn on Data Record
        Uint16 OFF_Cmd     :1;    ///< 7 1b-Turn off Data Record
        Uint16 WordsNum    :7;    ///< 14:8 Data Word Number
        Uint16 FrameEnd    :1;    ///< 15 1b-End Frame; 0b-Not End Frame
    }bit;
}UN_CAN_RecordCmd;

typedef struct
{
    UN_CAN_RecordCmd FrameCmd;    ///< Frame Command
    Uint16           FrameNum;    ///< Frame Number
    Uint16           HiWord;      ///< High Word
    Uint16           LoWord;      ///< Low Word
}ST_CAN_RECORD_RETURN;

typedef struct
{
    Uint16 FrameCmd;    ///< Frame Command
    Uint16 Data1;       ///< Data1
    Uint16 Data2;       ///< Data2
    Uint16 Data3;       ///< Data3
    Uint16 Data4;       ///< Data4
}ST_CAN_UPDATA_RETURN;

/* CAN Parameter Typedef */
typedef struct
{
    Uint16 uiCmdCode;        ///< Can Command code
    Uint16 uiSrcAddr;        ///< Can Source Address
    Uint16 uiRxTabData[40];  ///< Can RX Table Data
    Uint16 uiTxWord[8];      ///< Send word
    Uint16 uiTxEndFlg;       ///< Transmission completion flag
    Uint16 uiGroupNum;       ///< Group Number
    Uint16 uiBitNum;         ///< Bit Number
    Uint16 uiDataType;       ///< Data Type
    Uint16 uiFrameNum;       ///< Current Frame Number
    Uint16 uiFrameOverFlg;   ///< Frame Over Flag
}ST_CAN_PARAM;

typedef struct
{
    float32 ftRatRxPrm;      ///< Ratio of RX parameter
    float32 ftCoeffK;
    float32 ftCoeffKMin;
    float32 ftCoeffKMax;
    float32 ftCoeffB;
    float32 ftCoeffBMin;
    float32 ftCoeffBMax;

    Uint16 uiAddrCoeffK;
    Uint16 uiAddrCoeffB;
    Uint16 uiCntrIntl;       ///< Interval counter
}ST_COM_CAL;

typedef struct
{
    Uint32 ulCodLen;                              ///< code length
    Uint32 ulSumNumFrm;                           ///< code Frame Num Sum
    Uint32 ulCurrNumFrm;                          ///< Frame Current Num
    Uint32 ulCpldFlashAddr;                       ///< Cpld Flash address
    Uint16 uiSubNumFrm;                           ///< Frame Sub Num
    Uint16 uiFlgChk;                              ///< Check flag
    Uint16 uiFlgEraseOK;                          ///< Erase OK flag
    Uint16 uiFlgWrFlt;                            ///< Write fail flag
    Uint16 uiFrmWordWrBuf[SIZE_WR_FRM_CPLDUPD];   ///< Frame Word Write Buffer
    Uint16 uiFrmWordRdBuf[SIZE_WR_FRM_CPLDUPD];   ///< Frame Word Read Buffer
}ST_CPLD_BOOT;

/* Communicate Local Typedef */
typedef struct
{
    ST_COM stPrmExt;          ///< External parameter

    ST_COM_CAL BattVolt;      ///< Output Voltage Calibration
    ST_COM_CAL BattCurr;      ///< Output Current  Calibration
    ST_COM_CAL BattDnVolt;    ///< Output Voltage Down  Calibration
    ST_COM_CAL BattDnCurr;    ///< Output Current Down  Calibration

    ST_CAN_DATA stCanaRx;     ///< Can Receive
    ST_CAN_DATA stCanaTx;     ///< Can Transmit
    ST_CAN_PARAM stCanParam;  ///< Can Parameter
    ST_CPLD_BOOT stCpldBoot;  ///< CPLD UPgrade Parameter
    Uint16 uiFrmNrOpData;	  ///< Operation data frame number
    Uint16 uiFrmNrSelfTest;	  ///< Self test frame number
    Uint16 uiSelfTestCnt;     ///< Self test counter
    Uint16 uiModGrid;         ///< Grid mode
    Uint16 uiNumSelfTest;     ///< Self test ARM confirm number
    Uint16 uiIdxAry[NUM_EEPROM_DATA_QUE_OPER];  ///< Dequeue index array
    Uint16 uiBufFltData[WORDS_FLT_DATA_READ_TOTAL]; ///< Fault data buffer
    Uint16 uiFrameFltDataRead;  ///< Fault data read frame number
    float32 ftCoeffReactv;    ///< Reactive power coefficient
}ST_COM_LOC;

//=====================================================
//    Variable Declaration
//=====================================================
extern ST_COM_LOC stComLoc;

//=====================================================
//    Function Declaration
//=====================================================
//Initial
static void v_Com_PrmInit(void);

//Transmit Task
static void v_Com_Tx_Tsk(Uint16 uiFuncCode, Uint16 uiGroupNum, Uint16 uiBitNum);
static void v_Com_Tx_Tsk_PrmRead( Uint16 uiGroupNum, Uint16 uiBitNum);
static void v_Com_Tx_Tsk_PrmRead_DataTpyJdg(Uint16 uiGroupNum, Uint16 uiBitNum, Uint16 l_uiIndex, Uint16 l_uiDataType);
static void v_Com_Tx_Tsk_VoltCurr(void);
static void v_Com_Tx_Tsk_InvVolt(void);
static void v_Com_Tx_Tsk_OpData(void);
static void v_Com_Tx_Tsk_OpData_SndData(Uint16 u16FrameNum);
static void v_Com_Tx_Tsk_SelfTest(void);
static void v_Com_Tx_Tsk_SelfTest_SndData(Uint16 u16FrameNum);
static void v_Com_Tx_Tsk_TblVers(void);
static void v_Com_Tx_Tsk_Dft(void);
#if 1U == FLG_FLT_DATA_REC_EN
static void v_Com_Tx_Tsk_FltDataRec(void);
static void v_Com_Tx_Tsk_FltDataRec_SndData(void);
#endif
#if 2U == GRID_PHASE_NUMBER
static void v_Com_Tx_Tsk_CpldUpd_Notice(void);
static void v_Com_Tx_Tsk_CpldUpd_Erase(void);
static void v_Com_Tx_Tsk_CpldUpd_Rx(void);
static void v_Com_Tx_Tsk_CpldUpd_Chk(void);
static void v_Com_Tx_Tsk_CpldUpd_Stop(void);
static void v_Com_Tx_Tsk_CpldUpd(void);
#endif

//Receive Task
static void v_Com_Rx_Tsk(Uint16 uiDataCmd, Uint16 uiFramesEndFlg);
static void v_Com_Rx_Tsk_RunOrd(void);
static void v_Com_Rx_Tsk_VoltCurr(void);
static void v_Com_Rx_Tsk_GridCtrl(void);
static void v_Com_Rx_Tsk_OpData(void);
static void v_Com_Rx_Tsk_ThreePhaActvPow(void);
static void v_Com_Rx_Tsk_ThreePhaReactvPow(void);
static void v_Com_Rx_Tsk_SelfTest(void);
static void v_Com_Rx_Tsk_Temp1(void);
static void v_Com_Rx_Tsk_Temp2(void);
static void v_Com_Rx_Tsk_PrmSet(Uint16 uiFramesEndFlg);
static void v_Com_Rx_Tsk_PrmSet_PrmSto(Uint16 uiGroupNum, Uint16 uiBitNum, Uint16 uiDataType);
static void v_Com_Rx_Tsk_PrmSet_StoChk(void);
static void v_Com_Rx_Tsk_BattVoltAdj(void);
static void v_Com_Rx_Tsk_BattCurrAdj(void);
static void v_Com_Rx_Tsk_BattDnVoltAdj(void);
static void v_Com_Rx_Tsk_BattDnCurrAdj(void);
static void v_Com_Rx_Tsk_AcVoltAdj(void);
static void v_Com_Rx_Tsk_AcCurrAdj(void);
static void v_Com_Rx_Tsk_AcCoeff(float32 *pftCoeff, float32 ftDisp, float32 ftAct);
static void v_Com_Rx_Tsk_PfcZeroAdj(void);
static void v_Com_Tsk_PfcZeroAdj_100ms(void);
static void v_Com_Tsk_PfcZeroAdj_Vg(void);
static void v_Com_Tsk_PfcZeroAdj_Ig(void);
static void v_Com_Tsk_PfcZeroAdj_VgDc(void);
static void v_Com_Tsk_PfcZeroAdj_IgDc(void);
static void v_Com_Rx_Tsk_PfcStd(void);
static void v_Com_Rx_Tsk_GridType(void);
static void v_Com_Rx_Tsk_MainDspUpg(void);
static void v_Com_Rx_Tsk_Fct(void);
static void v_Com_EepPrmUpd(void);
static void v_Com_Rx_Tsk_TiSync(void);
#if(1U == FLG_CPU2_UPD_EN)
static void v_Com_Rx_Tsk_Cpu2Upg(void);
static void v_Com_Tx_Tsk_Cpu2Upd(void);
#endif
#if 1U == FLG_FLT_DATA_REC_EN
static void v_Com_Rx_Tsk_TiFltData(void);
#endif
#if 2U == GRID_PHASE_NUMBER
static void v_Com_Rx_Tsk_CpldUpd(void);
#endif

#endif /* COM_H_ */
//===========================================================================
// End of file.
//===========================================================================
