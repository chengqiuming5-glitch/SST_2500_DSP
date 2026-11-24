/**
*******************************************************
* @copyright 2010-2040, WANBANG Digital Energy Co. LTD
* @file      FaultData.c
* @author    xcc
* @date      2026/7/02 11:17:47
* @version   V0.1
**********************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project
#define FAULT_DATA_C
//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FaultDataInc.h"
#include "FaultData.h"
//==============================================================================================
//    Variable Definition
//==============================================================================================
Uint16 wBaseFaultOccurTime[FAULTNUM] = {0U};
Uint16 wSafetyFaultOccurTime[SAFETY_FAULT_NUM] = {0U};
static Uint16 UnusedConstWord = 0U;

const FaultDataType BaseFaultDataTable[FAULTNUM]=
{
/** Line_000*/   {22544U, 0U, 40U, 10000U, 2500U, (void *)&stPfcDataCalc.stMeasParm.uiVoltDcMax1000Times, (void *)&stPfcDiag.uiVgDcProt1000Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 35498U, 35498U, 35370U, 35498U}, 0U}, /**< 逆变电压直流分量超限 */ 
/** Line_001*/   {6145U, 2048U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.uiFltIdcOv, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电流直流分量超限 */ 
/** Line_002*/   {6162U, 10336U, 40U, 0U, 2500U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 35328U, 35328U, 35328U, 35370U}, 0U}, /**< 电网瞬时过流 */ 
/** Line_003*/   {22547U, 0U, 40U, 500U, 2500U, (void *)&stPfcDataCalc.stMeasParm.uiIgMaxRms100Times, (void *)&stPfcDiag.uiAcRmsOCProt100Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 0U, 0U}, 0U}, /**< 网侧模块有效值过流 */ 
/** Line_004*/   {6164U, 10240U, 0U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 0U, 0U}, 0U}, /**< 网侧模块硬件过流 */ 
/** Line_005*/   {6166U, 22608U, 0U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 35328U, 35328U, 35330U, 35370U}, 0U}, /**< 电网电流CBC保护 */ 
/** Line_006*/   {22551U, 0U, 40U, 1000U, 2500U, (void *)&stPfcDataCalc.stMeasParm.uiIgDiffRms100Times, (void *)&stPfcDiag.uiCurrAcImBal100Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< AC电流不平衡 */ 
/** Line_007*/   {6168U, 22560U, 0U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 0U, 0U}, 0U}, /**< 直流母线硬件过压 */ 
/** Line_008*/   {22555U, 0U, 20U, 1U, 2500U, (void *)&stPfcDataCalc.stMeasParm.siVbus10Times, (void *)&stPfcDiag.uiBusOVProt10Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 0U, 0U}, 0U}, /**< 直流母线过压 */ 
/** Line_009*/   {22556U, 256U, 20U, 15U, 2500U, (void *)&stPfcDataCalc.stMeasParm.siVbus10Times, (void *)&stPfcDiag.uiBusUVProt10Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 42U, 42U, 42U, 35498U}, 0U}, /**< 直流母线欠压 */ 
/** Line_010*/   {22557U, 20480U, 20U, 1U, 2500U, (void *)&stPfcDataCalc.stMeasParm.siVbusPos10Times, (void *)&stPfcDiag.uiHalfBusOVProt10Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 8U, 10U, 10U, 35370U}, 0U}, /**< 正半母线过压 */ 
/** Line_011*/   {22559U, 20480U, 40U, 200U, 2500U, (void *)&stPfcDataCalc.stMeasParm.uiVbusMid10Times, (void *)&stPfcDiag.uiMidBusOVProt10Times, &stComTbl.unWordPfcFlt1.all, &stComTbl.unWordPfcFltMask1.all, &stComTbl.unWordPfcFltSts1.all, { 0U, 0U, 42U, 35338U}, 0U}, /**< 母线中点偏移超限 */ 
/** Line_012*/   {22528U, 0U, 40U, 2500U, 2500U, (void *)&stPfcDataCalc.stMeasParm.uiVgDiffRms10Times, (void *)&stPfcDiag.uiVoltAcImBal10Times, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 682U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压不平衡 */ 
/** Line_013*/   {6145U, 2096U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 0U, 35370U, 35498U}, 0U}, /**< 电网暂态过压 */ 
/** Line_014*/   {6162U, 2240U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 0U, 0U, 35498U}, 0U}, /**< AC过载 */ 
/** Line_015*/   {6163U, 22592U, 0U, 0U, 100U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 0U, 170U, 35498U}, 0U}, /**< PFC状态机自检超时 */ 
/** Line_016*/   {6169U, 2176U, 0U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcDiag.unFlt.all, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 34816U, 35498U, 35370U}, 0U}, /**< 交流接线故障 */ 
/** Line_017*/   {6160U, 2048U, 40U, 1000U, 250U, (void *)&UnusedConstWord, (void *)&stCmnDiag.uiFltSys, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 0U, 0U, 35498U}, 0U}, /**< 高温故障 */ 
/** Line_018*/   {6161U, 2064U, 40U, 1000U, 250U, (void *)&UnusedConstWord, (void *)&stCmnDiag.uiFltSys, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 0U, 0U, 35498U}, 0U}, /**< 低温故障 */ 
/** Line_019*/   {6162U, 2048U, 0U, 5U, 10U, (void *)&UnusedConstWord, (void *)&stEep.stEepErr.all, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 0U, 0U, 0U}, 0U}, /**< Eeprom参数初始化失败 */ 
/** Line_020*/   {6163U, 2096U, 0U, 5U, 10U, (void *)&UnusedConstWord, (void *)&stCmnDiag.uiFltSys, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 0U, 0U, 0U}, 0U}, /**< CAN通讯故障 */ 
/** Line_021*/   {22549U, 0U, 40U, 100U, 25U, (void *)&stCmnAdc.stAux12V.uiErr1000Times, (void *)&stCmnDiag.uiAux12VProt1000Times, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 34816U, 0U, 0U}, 0U}, /**< 12V供电异常 */ 
/** Line_022*/   {22550U, 0U, 40U, 100U, 25U, (void *)&stCmnAdc.stAux1V5.uiErr1000Times, (void *)&stCmnDiag.uiAux1V5Prot1000Times, &stComTbl.unWordSysFlt.all, &stComTbl.unWordSysFltMask.all, &stComTbl.unWordSysFltSts.all, { 0U, 0U, 0U, 0U}, 0U}/**< 1.5V采样基准异常 */ 
}; 

const FaultDataType CQC_Table[19]=
{
/** Line_000*/   {5152U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35370U, 35498U}, 0U}, /**< 电网电压过压1 */ 
/** Line_001*/   {5153U, 34832U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压过压2 */ 
/** Line_002*/   {5154U, 34848U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压过压3 */ 
/** Line_003*/   {5155U, 34896U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠压1 */ 
/** Line_004*/   {5156U, 34912U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠压2 */ 
/** Line_005*/   {5157U, 34928U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠压3 */ 
/** Line_006*/   {5158U, 34976U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unVoltProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 35498U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压10分钟均值过压 */ 
/** Line_007*/   {5159U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压过频1 */ 
/** Line_008*/   {5160U, 34832U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压过频2 */ 
/** Line_009*/   {5161U, 34848U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压过频3 */ 
/** Line_010*/   {5162U, 34896U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠频1 */ 
/** Line_011*/   {5163U, 34912U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠频2 */ 
/** Line_012*/   {5164U, 34928U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.unFrqProt.all, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 电网电压欠频3 */ 
/** Line_013*/   {5165U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stVrt.uiFlgHvrtOvTi, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 35498U, 0U, 35498U, 35498U}, 0U}, /**< 高穿超时 */ 
/** Line_014*/   {5166U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stVrt.uiFlgLvrtOvTi, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 35498U, 0U, 35498U, 35498U}, 0U}, /**< 低穿超时 */ 
/** Line_015*/   {5167U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgGridChkNo, &stComTbl.unWordPfcFlt2.all, &stComTbl.unWordPfcFltMask2.all, &stComTbl.unWordPfcFltSts2.all, { 35498U, 0U, 35498U, 35498U}, 0U}, /**< 不满足并网条件 */ 
/** Line_016*/   {5156U, 34816U, 0U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stDstbc.uiFltAi, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 0U, 35498U, 35498U}, 0U}, /**< 主动孤岛检测故障 */ 
/** Line_017*/   {5176U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stCom.uiFltSelfTest, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 35456U, 35456U, 35498U, 35498U}, 0U}, /**< 意大利自检失败 */ 
/** Line_018*/   {5162U, 34816U, 40U, 0U, 0U, (void *)&UnusedConstWord, (void *)&stPfcGridCtrl.stGridDet.uiFltRoCoF, &stComTbl.unWordPfcFlt3.all, &stComTbl.unWordPfcFltMask3.all, &stComTbl.unWordPfcFltSts3.all, { 0U, 0U, 35498U, 35498U}, 0U}/**< RoCoF保护 */ 
}; 

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

