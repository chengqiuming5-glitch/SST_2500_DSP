//==============================================================================================
//    File description
//==============================================================================================
/**@file         ASW_Cmn.h
 * @brief
 * The header file of ASW_Cmn is designed to realize header file of ASW common.
 *
 * Module      :      \n
 *
 *
 * :                  \n
 *                    \n
 *                    \n
 *                    \n
 *
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

#ifndef ASW_CMN_H_
#define ASW_CMN_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "App.h"
#include "DSPParaData.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================
#ifndef  VB_ADJ_ZERO_NUM
/* Calibration coefficient address Macro Definition */
#define  VB_ADJ_ZERO_NUM         0U
#define  VC_ADJ_ZERO_NUM         0U
#define  VB_DC_ADJ_ZERO_NUM      0U
#define  VC_DC_ADJ_ZERO_NUM      0U

#define  IB_ADJ_ZERO_NUM         0U
#define  IC_ADJ_ZERO_NUM         0U
#define  IN_ADJ_ZERO_NUM         0U

#define  IB_DC_ADJ_ZERO_NUM      0U
#define  IC_DC_ADJ_ZERO_NUM      0U
#define  IA_DC_ADJ_ZERO_N_NUM    0U
#define  IB_DC_ADJ_ZERO_N_NUM    0U
#define  IC_DC_ADJ_ZERO_N_NUM    0U
#define  VBUSPOS_ADJ_ZERO_NUM    0U

#define  IN_ADJ_COFK_NUM         0U
#define  VBUSPOS_ADJ_COFK_NUM    0U
#endif    /* #ifndef VB_ADJ_ZERO_NUM */

#ifndef  VAINV_ADJ_ZERO_NUM
/* Calibration coefficient address Macro Definition */
#define  VAINV_ADJ_ZERO_NUM      0U
#define  VBINV_ADJ_ZERO_NUM      0U

#define  VBUSNEG_ADJ_ZERO_NUM    0U

#define  VAINV_ADJ_COFK_NUM      0U
#define  VBINV_ADJ_COFK_NUM      0U

#define  VBUSNEG_ADJ_COFK_NUM    0U
#endif    /* #ifndef VAINV_ADJ_ZERO_NUM */

//==============================================================================================
//   Global Struct & Enum & Union Typedef
//==============================================================================================


//==============================================================================================
//    Global Function Declaration
//==============================================================================================
/* Com */
extern void v_Com_Rx(void);
extern void v_Com_Tx(void);
extern void v_Com_Init(void);
extern void v_Com_100ms(void);
extern void v_Com_1s(void);
extern void v_Com_NonEraPrm_Init(void);
extern void v_Com_Rx_Tsk_EepPrmUpd(void);
extern void v_Com_ParlPrmUpd(void);
extern void v_Com_SeriesPrmUpd(void);
/* ComIf */
extern void v_ComIf_Init(void);
extern void v_ComIf_1ms(void);
extern void v_ComIf_10ms(void);
extern void v_ComIf_100ms(void);
/* CmnAdc */
extern void v_CmnAdc_Init(void);
extern void v_CmnAdc_1ms(void);
extern void v_CmnAdc_100ms(void);
/* CmnDiag */
extern void v_CmnDiag_Init(void);
extern void v_CmnDiag_1ms(void);
extern void v_CmnDiag_100ms(void);
/* PerphCtrl */
extern void v_PerphCtrl_Init(void);
extern void v_PerphCtrl_AcRly_Init(void);
extern void v_PerphCtrl_SPRly_Init(void);
extern void v_PerphCtrl_Bld_Init(void);
extern void v_PerphCtrl_Led_Init(void);
extern void v_PerphCtrl_V2LAuxPow_Init(void);
extern void v_PerphCtrl_1ms(void);
extern void v_PerphCtrl_10ms(void);
extern void v_PerphCtrl_100ms(void);
extern void v_PerphCtrl_AcRly_10ms(void);
extern void v_PerphCtrl_SPRly_10ms(void);
extern void v_PerphCtrl_Bld_1ms(void);
extern void v_PerphCtrl_V2LAuxPow_1ms(void);
extern void v_PerphCtrl_Led_100ms(void);
/* PowLim */
extern void v_PowLim_Init(void);
extern void v_PowLim_1ms(void);
extern void v_PowLim_100ms(void);
extern void v_PowLim_PrmUpd_Eep(void);
/* PrmDisp */
extern void v_PrmDisp_Init(void);
/* Eep */
extern void v_Eep_RcvPrm(void);
extern void v_Eep_Init(void);
extern void v_Eep_1ms(void);
extern void v_Eep_100ms(void);
extern Uint16 ui_Eep_DataEnQue(ST_EEP_DATA_QUE *Que, Uint16 *puiDataAddr, Uint16 uiDatalength);
/* SwVers */
extern void v_SwVers_Init(void);
/* FltRstrt */
extern void v_FltRstrt_Init(void);
extern void v_FltRstrt_10ms(void);
extern void v_FltRstrt_1s(void);
/* Spi */
extern void v_Spi_Init(void);
extern void v_Spi_1ms(void); 
/* Emif */
extern void v_Emif_Init(void);
extern void v_Emif_Rd_Isr(void);
extern void v_Emif_Fpga_Wr(int16 *siBufWr, Uint32 ulAddrBase);
extern void v_Emif_Fpga_Wr_Debug(int16 *siBufWr, Uint32 ulAddrBase);
extern Uint16 ui_Emif_Fpga_Fast_Chk(int16 *siBufDma);
#endif /* ASW_CMN_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
