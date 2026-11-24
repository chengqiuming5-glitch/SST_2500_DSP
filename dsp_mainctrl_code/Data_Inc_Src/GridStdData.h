/**
*******************************************************
* @Copyright: 2010-2040, WANBANG Digital Energy Co.,LTD
* @File:      GridStdData.h
* @Author:    xcc
* @date:      2026/7/02 11:17:48
* @Version:   V3.08
**********************************************************
*/
#ifndef GS_DATA_H_
#define GS_DATA_H_
#if defined(GS_DATA_C) 
#define GS_DATA_EXT
#else
#define GS_DATA_EXT  extern
#endif
//==============================================================================================
//    Include Header Files
//==============================================================================================


//==============================================================================================
//    Macro Definition
//==============================================================================================
#define GRID_STD_VER    308U
#define GRID_STD_SUM_NUM    27U
#define VDE4105    0U 
#define EN50549    1U 
#define G99    2U 
#define G98    3U 
#define IEC_50Hz    4U 
#define CEI0_21    5U 
#define IEEE1547    6U 
#define AS4777_A    7U 
#define AS4777_B    8U 
#define AS4777_C    9U 
#define AS4777_NZ    10U 
#define NTS_A    11U 
#define NRS_097    12U 
#define TOR_R25    13U 
#define C10_11    14U 
#define BR_INMETRO_140    15U 
#define CZ_PPDS    16U 
#define DK_TR    17U 
#define GR_1165    18U 
#define RENBLAD_342    19U 
#define SE_EIFS    20U 
#define PL_EN50549    21U 
#define RO_EN50549    22U 
#define CH_VDE4105    23U 
#define NBT32004    24U 
#define VJV_EN50549    25U 
#define TOR_R37    26U 
/*************************Tbl_Grid_Rated_Parameter************************************************/
#define GS_FUNC_1_COLNUM    8U
#define GS_FUNC_1_COLNUM_UI    2U
#define GS_FUNC_1_ROWNUM    27U
/*************************Tbl_Power_Control************************************************/
#define GS_FUNC_2_COLNUM    20U
#define GS_FUNC_2_COLNUM_UI    8U
#define GS_FUNC_2_ROWNUM    27U
/*************************Tbl_Grid_Protection************************************************/
#define GS_FUNC_3_COLNUM    38U
#define GS_FUNC_3_COLNUM_UI    11U
#define GS_FUNC_3_ROWNUM    27U
/*************************Tbl_Frq_Power_Response************************************************/
#define GS_FUNC_4_COLNUM    27U
#define GS_FUNC_4_COLNUM_UI    10U
#define GS_FUNC_4_ROWNUM    27U
/*************************Tbl_Reactive_Qu_Mode************************************************/
#define GS_FUNC_5_COLNUM    23U
#define GS_FUNC_5_COLNUM_UI    5U
#define GS_FUNC_5_ROWNUM    27U
/*************************Tbl_Reactive_Qp_Mode************************************************/
#define GS_FUNC_6_COLNUM    24U
#define GS_FUNC_6_COLNUM_UI    4U
#define GS_FUNC_6_ROWNUM    27U
/*************************Tbl_HVRT************************************************/
#define GS_FUNC_7_COLNUM    11U
#define GS_FUNC_7_COLNUM_UI    6U
#define GS_FUNC_7_ROWNUM    27U
/*************************Tbl_LVRT************************************************/
#define GS_FUNC_8_COLNUM    11U
#define GS_FUNC_8_COLNUM_UI    6U
#define GS_FUNC_8_ROWNUM    27U
/*************************Tbl_Volt_Power_Response************************************************/
#define GS_FUNC_9_COLNUM    11U
#define GS_FUNC_9_COLNUM_UI    4U
#define GS_FUNC_9_ROWNUM    27U

//==============================================================================================
//    Variable declaration
//==============================================================================================
/*************************Tbl_Grid_Rated_Parameter************************************************/
GS_DATA_EXT const float32 Tbl_Grid_Rated_Parameter[GS_FUNC_1_ROWNUM][GS_FUNC_1_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Grid_Rated_Parameter_UI[GS_FUNC_1_ROWNUM][GS_FUNC_1_COLNUM_UI];
/*************************Tbl_Power_Control************************************************/
GS_DATA_EXT const float32 Tbl_Power_Control[GS_FUNC_2_ROWNUM][GS_FUNC_2_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Power_Control_UI[GS_FUNC_2_ROWNUM][GS_FUNC_2_COLNUM_UI];
/*************************Tbl_Grid_Protection************************************************/
GS_DATA_EXT const float32 Tbl_Grid_Protection[GS_FUNC_3_ROWNUM][GS_FUNC_3_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Grid_Protection_UI[GS_FUNC_3_ROWNUM][GS_FUNC_3_COLNUM_UI];
/*************************Tbl_Frq_Power_Response************************************************/
GS_DATA_EXT const float32 Tbl_Frq_Power_Response[GS_FUNC_4_ROWNUM][GS_FUNC_4_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Frq_Power_Response_UI[GS_FUNC_4_ROWNUM][GS_FUNC_4_COLNUM_UI];
/*************************Tbl_Reactive_Qu_Mode************************************************/
GS_DATA_EXT const float32 Tbl_Reactive_Qu_Mode[GS_FUNC_5_ROWNUM][GS_FUNC_5_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Reactive_Qu_Mode_UI[GS_FUNC_5_ROWNUM][GS_FUNC_5_COLNUM_UI];
/*************************Tbl_Reactive_Qp_Mode************************************************/
GS_DATA_EXT const float32 Tbl_Reactive_Qp_Mode[GS_FUNC_6_ROWNUM][GS_FUNC_6_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Reactive_Qp_Mode_UI[GS_FUNC_6_ROWNUM][GS_FUNC_6_COLNUM_UI];
/*************************Tbl_HVRT************************************************/
GS_DATA_EXT const float32 Tbl_HVRT[GS_FUNC_7_ROWNUM][GS_FUNC_7_COLNUM];
GS_DATA_EXT const Uint16 Tbl_HVRT_UI[GS_FUNC_7_ROWNUM][GS_FUNC_7_COLNUM_UI];
/*************************Tbl_LVRT************************************************/
GS_DATA_EXT const float32 Tbl_LVRT[GS_FUNC_8_ROWNUM][GS_FUNC_8_COLNUM];
GS_DATA_EXT const Uint16 Tbl_LVRT_UI[GS_FUNC_8_ROWNUM][GS_FUNC_8_COLNUM_UI];
/*************************Tbl_Volt_Power_Response************************************************/
GS_DATA_EXT const float32 Tbl_Volt_Power_Response[GS_FUNC_9_ROWNUM][GS_FUNC_9_COLNUM];
GS_DATA_EXT const Uint16 Tbl_Volt_Power_Response_UI[GS_FUNC_9_ROWNUM][GS_FUNC_9_COLNUM_UI];

//==============================================================================================
//    Function declaration
//==============================================================================================
/*************************Tbl_Grid_Rated_Parameter************************************************/
GS_DATA_EXT void Tbl_Grid_Rated_Parameter_Init(Uint16 uiStdSel);
/*************************Tbl_Power_Control************************************************/
GS_DATA_EXT void Tbl_Power_Control_Init(Uint16 uiStdSel);
/*************************Tbl_Grid_Protection************************************************/
GS_DATA_EXT void Tbl_Grid_Protection_Init(Uint16 uiStdSel);
/*************************Tbl_Frq_Power_Response************************************************/
GS_DATA_EXT void Tbl_Frq_Power_Response_Init(Uint16 uiStdSel);
/*************************Tbl_Reactive_Qu_Mode************************************************/
GS_DATA_EXT void Tbl_Reactive_Qu_Mode_Init(Uint16 uiStdSel);
/*************************Tbl_Reactive_Qp_Mode************************************************/
GS_DATA_EXT void Tbl_Reactive_Qp_Mode_Init(Uint16 uiStdSel);
/*************************Tbl_HVRT************************************************/
GS_DATA_EXT void Tbl_HVRT_Init(Uint16 uiStdSel);
/*************************Tbl_LVRT************************************************/
GS_DATA_EXT void Tbl_LVRT_Init(Uint16 uiStdSel);
/*************************Tbl_Volt_Power_Response************************************************/
GS_DATA_EXT void Tbl_Volt_Power_Response_Init(Uint16 uiStdSel);

#endif
//==============================================================================================
// End of file.
//==============================================================================================

