/**
*******************************************************
* @Copyright: 2010-2040, WANBANG Digital Energy Co.,LTD
* @File:      DSPParaData.h
* @Author:    xcc
* @date:      2026/7/02 11:17:50
* @Version:   V3.08
**********************************************************
*/
#ifndef DSPPARA_DATA_H_
#define DSPPARA_DATA_H_
#if defined(DSPPARA_DATA_C) 
#define DSP_DATA_EXT
#else
#define DSP_DATA_EXT  extern
#endif

//==============================================================================================
//    Include Header Files
//==============================================================================================

//==============================================================================================
//    Macro Definition
//==============================================================================================
#define PROJECT_TYPE    "11kW_PLAT"
#define PARAM_VER    308U

/** Parameter number */ 
#define FUNC_CODE_NUM    687U

/** Parameter group number */ 
#define GROUP_NUM    25U

/** Start EEPROM address of erasable parameter */ 
#define NORMAL_DATA_START_ADDR_EEPROM    100U

/** Start EEPROM address of non-erasable parameter */ 
#define NONERASE_DATA_START_ADDR_EEPROM    10000U

/** Download parameter number */ 
#define SAVE_EEPROM_NUM    350U
#define MASTER_SAVE_NUM    312U
#define MASTER_NONERASE_SAVE_NUM    38U

/** Parameter version */ 
#define PARAM_VERSON    308U

/** Special identifier number */ 
#define MASTER_TAG_NUM    38U

/** Special identification macro definition */ 
#define GRID_STD_NUM    146U
#define VOUT_ADJ_COFK_NUM    151U
#define VOUT_ADJ_COFB_NUM    152U
#define IOUT_ADJ_COFK_NUM    153U
#define IOUT_ADJ_COFB_NUM    154U
#define VOUT_DN_ADJ_COFK_NUM    155U
#define VOUT_DN_ADJ_COFB_NUM    156U
#define IOUT_DN_ADJ_COFK_NUM    157U
#define IOUT_DN_ADJ_COFB_NUM    158U
#define VA_ADJ_ZERO_NUM    160U
#define VB_ADJ_ZERO_NUM    161U
#define VC_ADJ_ZERO_NUM    162U
#define VA_DC_ADJ_ZERO_NUM    163U
#define VB_DC_ADJ_ZERO_NUM    164U
#define VC_DC_ADJ_ZERO_NUM    165U
#define IA_ADJ_ZERO_NUM    166U
#define IB_ADJ_ZERO_NUM    167U
#define IC_ADJ_ZERO_NUM    168U
#define IN_ADJ_ZERO_NUM    169U
#define IA_DC_ADJ_ZERO_NUM    170U
#define IB_DC_ADJ_ZERO_NUM    171U
#define IC_DC_ADJ_ZERO_NUM    172U
#define VBUS_ADJ_ZERO_NUM    173U
#define VBUSPOS_ADJ_ZERO_NUM    174U
#define VA_ADJ_COFK_NUM    175U
#define VB_ADJ_COFK_NUM    176U
#define VC_ADJ_COFK_NUM    177U
#define IA_ADJ_COFK_NUM    178U
#define IB_ADJ_COFK_NUM    179U
#define IC_ADJ_COFK_NUM    180U
#define IN_ADJ_COFK_NUM    181U
#define VBUS_ADJ_COFK_NUM    182U
#define VBUSPOS_ADJ_COFK_NUM    183U
#define AC_CURR_RMS_LIM_NUM    184U
#define GRID_TYPE_NUM    185U
#define IA_DC_ADJ_ZERO_N_NUM    186U
#define IB_DC_ADJ_ZERO_N_NUM    187U
#define IC_DC_ADJ_ZERO_N_NUM    188U

//==============================================================================================
//    Variable Declaration
//==============================================================================================
typedef struct
{
    Uint16  uiModifyAndDataType; 
    Uint16  *ParaAddr; 
    Uint16  Project; 
    Uint16  IndexEEprom; 
    Uint16  Factor; 
    Uint16  MasterSaveAddr; 
    Uint16  SlaveSaveAddr; 
}DSP_PARAM_TYPE;
typedef struct
{
    Uint16  *puiGroupName; 
    Uint16  uiLength; 
}DSP_GROUP_TYPE;

/** Parameter table declaration */ 
DSP_DATA_EXT  DSP_PARAM_TYPE  sFuncCode[FUNC_CODE_NUM + 1U] ;

/** Group 0, null by default */ 
#define GROUP_0_NUM   0U
DSP_DATA_EXT const Uint16 Group0Index[GROUP_0_NUM  + 1U];
#define GROUP_1_NUM   24U
DSP_DATA_EXT const Uint16 Group1Index[GROUP_1_NUM  + 1U];
#define GROUP_2_NUM   40U
DSP_DATA_EXT const Uint16 Group2Index[GROUP_2_NUM  + 1U];
#define GROUP_3_NUM   47U
DSP_DATA_EXT const Uint16 Group3Index[GROUP_3_NUM  + 1U];
#define GROUP_4_NUM   34U
DSP_DATA_EXT const Uint16 Group4Index[GROUP_4_NUM  + 1U];
#define GROUP_5_NUM   43U
DSP_DATA_EXT const Uint16 Group5Index[GROUP_5_NUM  + 1U];
#define GROUP_6_NUM   24U
DSP_DATA_EXT const Uint16 Group6Index[GROUP_6_NUM  + 1U];
#define GROUP_7_NUM   37U
DSP_DATA_EXT const Uint16 Group7Index[GROUP_7_NUM  + 1U];
#define GROUP_8_NUM   5U
DSP_DATA_EXT const Uint16 Group8Index[GROUP_8_NUM  + 1U];
#define GROUP_9_NUM   18U
DSP_DATA_EXT const Uint16 Group9Index[GROUP_9_NUM  + 1U];
#define GROUP_10_NUM   65U
DSP_DATA_EXT const Uint16 Group10Index[GROUP_10_NUM  + 1U];
#define GROUP_11_NUM   37U
DSP_DATA_EXT const Uint16 Group11Index[GROUP_11_NUM  + 1U];
#define GROUP_12_NUM   16U
DSP_DATA_EXT const Uint16 Group12Index[GROUP_12_NUM  + 1U];
#define GROUP_13_NUM   22U
DSP_DATA_EXT const Uint16 Group13Index[GROUP_13_NUM  + 1U];
#define GROUP_14_NUM   21U
DSP_DATA_EXT const Uint16 Group14Index[GROUP_14_NUM  + 1U];
#define GROUP_15_NUM   12U
DSP_DATA_EXT const Uint16 Group15Index[GROUP_15_NUM  + 1U];
#define GROUP_16_NUM   13U
DSP_DATA_EXT const Uint16 Group16Index[GROUP_16_NUM  + 1U];
#define GROUP_17_NUM   10U
DSP_DATA_EXT const Uint16 Group17Index[GROUP_17_NUM  + 1U];
#define GROUP_18_NUM   28U
DSP_DATA_EXT const Uint16 Group18Index[GROUP_18_NUM  + 1U];
#define GROUP_19_NUM   49U
DSP_DATA_EXT const Uint16 Group19Index[GROUP_19_NUM  + 1U];
#define GROUP_20_NUM   37U
DSP_DATA_EXT const Uint16 Group20Index[GROUP_20_NUM  + 1U];
#define GROUP_21_NUM   28U
DSP_DATA_EXT const Uint16 Group21Index[GROUP_21_NUM  + 1U];
#define GROUP_22_NUM   28U
DSP_DATA_EXT const Uint16 Group22Index[GROUP_22_NUM  + 1U];
#define GROUP_23_NUM   17U
DSP_DATA_EXT const Uint16 Group23Index[GROUP_23_NUM  + 1U];
#define GROUP_24_NUM   17U
DSP_DATA_EXT const Uint16 Group24Index[GROUP_24_NUM  + 1U];
#define GROUP_25_NUM   15U
DSP_DATA_EXT const Uint16 Group25Index[GROUP_25_NUM  + 1U];

DSP_DATA_EXT const DSP_GROUP_TYPE  sGroup [GROUP_NUM + 1U];
DSP_DATA_EXT const Uint16  SaveEEPromIndex[SAVE_EEPROM_NUM];
DSP_DATA_EXT const Uint16  MasterSaveEEPromIndex[MASTER_SAVE_NUM];
DSP_DATA_EXT const Uint16  MasterNonEraseEEPromIndex[MASTER_NONERASE_SAVE_NUM];

#endif    /* DSPPARA_DATA_H_ */
//==============================================================================================
// End of file.
//==============================================================================================

