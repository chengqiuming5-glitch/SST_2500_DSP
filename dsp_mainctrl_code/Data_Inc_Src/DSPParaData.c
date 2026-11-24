/**
*******************************************************
* @Copyright: 2010-2040, WANBANG Digital Energy Co.,LTD
* @File:      DSPParaData.c
* @Author:    xcc
* @date:      2026/7/02 11:17:50
* @Version:   V3.08
**********************************************************
*/
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project
#define DSPPARA_DATA_C 
//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "DSPParaDataInc.h"
#include "DSPParaData.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================
#define UNUSED_ADDR    0xFFFFU
//==============================================================================================
//    Variable Definition
//==============================================================================================
static Uint16 MasterParaVersion = PARAM_VER;
/** Parameter table definition */
DSP_PARAM_TYPE sFuncCode[FUNC_CODE_NUM + 1U] = 
{
/*0, 0*/ {0U, (void *)0x0U, 0U, 0U, 0U, 0U, 0U},
/** GROUP_1-01版本信息  */
/**001, 001; Line_001*/  { 0x481U, (void *)&MasterParaVersion, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 参数表版本 */ 
/**001, 002; Line_002*/  { 0x581U, (void *)&uiDspSwVer, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 软件版本号 */ 
/**001, 003; Line_003*/  { 0x581U, (void *)&uiCodeCompileTime, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 软件编译时间 */ 
/**001, 004; Line_004*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A1模块版本号 */ 
/**001, 005; Line_005*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A2模块版本号 */ 
/**001, 006; Line_006*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A3模块版本号 */ 
/**001, 007; Line_007*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A4模块版本号 */ 
/**001, 008; Line_008*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A5模块版本号 */ 
/**001, 009; Line_009*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[0][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A6模块版本号 */ 
/**001, 010; Line_010*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B1模块版本号 */ 
/**001, 011; Line_011*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B2模块版本号 */ 
/**001, 012; Line_012*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B3模块版本号 */ 
/**001, 013; Line_013*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B4模块版本号 */ 
/**001, 014; Line_014*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B5模块版本号 */ 
/**001, 015; Line_015*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[1][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B6模块版本号 */ 
/**001, 016; Line_016*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C1模块版本号 */ 
/**001, 017; Line_017*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C2模块版本号 */ 
/**001, 018; Line_018*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C3模块版本号 */ 
/**001, 019; Line_019*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C4模块版本号 */ 
/**001, 020; Line_020*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C5模块版本号 */ 
/**001, 021; Line_021*/  { 0x481U, (void *)&stEmif.siVerFpgaCell[2][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C6模块版本号 */ 
/**001, 022; Line_022*/  { 0x441U, (void *)&stEmifDmaPollData.siFpgaVersion1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 辅控版本号1 */ 
/**001, 023; Line_023*/  { 0x441U, (void *)&stEmifDmaPollData.siFpgaVersion2, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 辅控版本号2 */ 
/**001, 024; Line_024*/  { 0x441U, (void *)&stEmifDmaPollData.siFpgaVersion3, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 辅控版本号3 */ 
/** GROUP_2-02整机控制  */
/**002, 001; Line_025*/  { 0x480U, (void *)&stCom.uiCmdRunReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整机启动停机设置 */ 
/**002, 002; Line_026*/  { 0x480U, (void *)&stCom.uiStgRunEnReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整机控制模式设置 */ 
/**002, 003; Line_027*/  { 0x480U, (void *)&stCom.uiModRunReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整机运行模式设置 */ 
/**002, 004; Line_028*/  { 0x480U, (void *)&stPerphCtrl.stSPRly.uiSt, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 输出串并联模式设置 */ 
/**002, 005; Line_029*/  { 0x541U, (void *)&stCom.ftPwrActvReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 并网有功功率需求 */ 
/**002, 006; Line_030*/  { 0x541U, (void *)&stCom.ftPwrReactvReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 并网无功功率需求 */ 
/**002, 007; Line_031*/  { 0x541U, (void *)&stCom.ftPFReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 并网功率因数需求 */ 
/**002, 008; Line_032*/  { 0x541U, (void *)&stCom.ftVoltAcV2LReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 离网电压需求 */ 
/**002, 009; Line_033*/  { 0x541U, (void *)&stCom.ftFrqAcV2LReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 离网频率需求 */ 
/**002, 010; Line_034*/  { 0x541U, (void *)&stCom.ftPwrChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 充电模式下功率需求 */ 
/**002, 011; Line_035*/  { 0x541U, (void *)&stCom.ftPaAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相有功功率设置 */ 
/**002, 012; Line_036*/  { 0x541U, (void *)&stCom.ftPbAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相有功功率设置 */ 
/**002, 013; Line_037*/  { 0x541U, (void *)&stCom.ftPcAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相有功功率设置 */ 
/**002, 014; Line_038*/  { 0x541U, (void *)&stCom.ftQaAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相无功功率设置 */ 
/**002, 015; Line_039*/  { 0x541U, (void *)&stCom.ftQbAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相无功功率设置 */ 
/**002, 016; Line_040*/  { 0x541U, (void *)&stCom.ftQcAcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相无功功率设置 */ 
/**002, 017; Line_041*/  { 0x481U, (void *)&stCom.unModPfcPow.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC功率控制模式 */ 
/**002, 018; Line_042*/  { 0x481U, (void *)&stComIf.uiModPfcPhaLoss, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC缺相运行模式 */ 
/**002, 019; Line_043*/  { 0x481U, (void *)&stComIf.uiModPfcNonPhaN, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC-N线模式 */ 
/**002, 020; Line_044*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiHandControl, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 手动运行开关 */ 
/**002, 021; Line_045*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiClearRedFlt, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 清除冗余故障 */ 
/**002, 022; Line_046*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiCloseRely, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 吸合预充继电器 */ 
/**002, 023; Line_047*/  { 0x480U, (void *)&stComIf.uiValRunTimeMs, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 运行时间 */ 
/**002, 024; Line_048*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiDischargeVolCHBA, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相待机母线放电阈值 */ 
/**002, 025; Line_049*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiDischargeVolCHBB, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相待机母线放电阈值 */ 
/**002, 026; Line_050*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiDischargeVolCHBC, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相待机母线放电阈值 */ 
/**002, 027; Line_051*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiHalfBusBlanceEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 半母线均衡使能 */ 
/**002, 028; Line_052*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiSOCBlanceEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< SOC均衡使能 */ 
/**002, 029; Line_053*/  { 0x542U, (void *)&stComTbl.stPrmToFpga.ftSUMOCPValue, 0U, 100U, 1U, 100U,UNUSED_ADDR},   /**< 三相过流保护点 */ 
/**002, 030; Line_054*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedundantA, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相冗余模块设定 */ 
/**002, 031; Line_055*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedundantB, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相冗余模块设定 */ 
/**002, 032; Line_056*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedundantC, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相冗余模块设定 */ 
/**002, 033; Line_057*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRunAEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块运行使能 */ 
/**002, 034; Line_058*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRunBEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块运行使能 */ 
/**002, 035; Line_059*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRunCEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块运行使能 */ 
/**002, 036; Line_060*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedunAEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相冗余使能 */ 
/**002, 037; Line_061*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedunBEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相冗余使能 */ 
/**002, 038; Line_062*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiRedunCEnable, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相冗余使能 */ 
/**002, 039; Line_063*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiOTAModulFpga, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 模块FPGA升级指令 */ 
/**002, 040; Line_064*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiFltDataRec, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA录波指令 */ 
/** GROUP_3-03D2D数据监视  */
/**003, 001; Line_065*/  { 0x481U, (void *)&stCom.uiStArm, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< ARM状态 */ 
/**003, 002; Line_066*/  { 0x541U, (void *)&stCom.ftVoltBattChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 客户请求充电电池电压 */ 
/**003, 003; Line_067*/  { 0x541U, (void *)&stCom.ftCurrBattChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 客户请求充电电池电流 */ 
/**003, 004; Line_068*/  { 0x541U, (void *)&stCom.ftVoltBattDchaReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 客户请求放电电池电压 */ 
/**003, 005; Line_069*/  { 0x541U, (void *)&stCom.ftCurrBattDchaReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 客户请求放电电池电流 */ 
/**003, 006; Line_070*/  { 0x541U, (void *)&stCom.ftVoltBattBms, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< BMS 电池电压 */ 
/**003, 007; Line_071*/  { 0x541U, (void *)&stCom.ftVoltBattBmsMax, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< BMS 最大电池电压 */ 
/**003, 008; Line_072*/  { 0x481U, (void *)&stComIf.uiModRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求模式 */ 
/**003, 009; Line_073*/  { 0x481U, (void *)&stComIf.uiModD2dRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部D2D请求模式 */ 
/**003, 010; Line_074*/  { 0x481U, (void *)&stComIf.uiCmdRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求开关机命令 */ 
/**003, 011; Line_075*/  { 0x481U, (void *)&stComIf.uiCmdD2dRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部D2D请求开关机命令 */ 
/**003, 012; Line_076*/  { 0x481U, (void *)&stComIf.uiFlgBldPtd, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< ARM请求泄放标志 */ 
/**003, 013; Line_077*/  { 0x481U, (void *)&stComIf.uiCmdV2LAuxPow, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< ARM请求V2L辅源标志 */ 
/**003, 014; Line_078*/  { 0x481U, (void *)&stComIf.uiFlgFltRst, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< ARM请求故障清楚 */ 
/**003, 015; Line_079*/  { 0x541U, (void *)&stComIf.ftVoltBattChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求充电电池电压 */ 
/**003, 016; Line_080*/  { 0x541U, (void *)&stComIf.ftCurrBattChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求充电电池电流 */ 
/**003, 017; Line_081*/  { 0x541U, (void *)&stComIf.ftVoltBattDchaReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求放电电池电压 */ 
/**003, 018; Line_082*/  { 0x541U, (void *)&stComIf.ftCurrBattDchaReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求放电电池电流 */ 
/**003, 019; Line_083*/  { 0x541U, (void *)&stComIf.ftOutpOLReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部请求开环输出 */ 
/**003, 020; Line_084*/  { 0x541U, (void *)&stCom.ftTempArmBd, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< ARM芯片温度 */ 
/**003, 021; Line_085*/  { 0x541U, (void *)&stCom.ftTempNtc0, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC端子温度 */ 
/**003, 022; Line_086*/  { 0x541U, (void *)&stCom.ftTempNtc2, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB磁件NTC温度 */ 
/**003, 023; Line_087*/  { 0x541U, (void *)&stCom.ftTempNtc3, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB副边MOS-NTC温度 */ 
/**003, 024; Line_088*/  { 0x541U, (void *)&stCom.ftTempNtc4, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB原边MOS-NTC温度 */ 
/**003, 025; Line_089*/  { 0x541U, (void *)&stCom.ftTempNtc5, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC-MOS-NTC温度 */ 
/**003, 026; Line_090*/  { 0x481U, (void *)&stD2dStMac.uiStD2dRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2d状态机状态 */ 
/**003, 027; Line_091*/  { 0x541U, (void *)&stPowLim.ftVoltBattChrgLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 充电电池电压限制值 */ 
/**003, 028; Line_092*/  { 0x541U, (void *)&stPowLim.ftCurrBattChrgLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 充电电池电流限制值 */ 
/**003, 029; Line_093*/  { 0x541U, (void *)&stPowLim.ftVoltBusLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 母线电压限制值 */ 
/**003, 030; Line_094*/  { 0x541U, (void *)&stPowLim.ftPowAcChrgLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC功率充电限制 */ 
/**003, 031; Line_095*/  { 0x541U, (void *)&stPowLim.ftPowAcDchaLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC功率放电限制 */ 
/**003, 032; Line_096*/  { 0x541U, (void *)&stPowLim.ftPowBattCurrChrgLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 基于电池电流充电功率限制 */ 
/**003, 033; Line_097*/  { 0x541U, (void *)&stPowLim.ftPowBattCurrDchaLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 基于电池电流放电功率限制 */ 
/**003, 034; Line_098*/  { 0x541U, (void *)&stPowLim.ftCurrBattChrgMaxToBms, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 充电模式下电池电流最大值给BMS */ 
/**003, 035; Line_099*/  { 0x541U, (void *)&stPowLim.ftCurrBattDchaMaxToBms, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 放电模式下电池电流最大值给BMS */ 
/**003, 036; Line_100*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftOutpOLRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D开环给定量 */ 
/**003, 037; Line_101*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftVoltBattChrgRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D输出电压环给定量 */ 
/**003, 038; Line_102*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftCurrBattChrgRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D输出电流环给定量 */ 
/**003, 039; Line_103*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftVoltBusRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D母线电压环给定量 */ 
/**003, 040; Line_104*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftVoltBattBurst, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电池电压打嗝值 */ 
/**003, 041; Line_105*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftCurrBattBurst, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电池电流打嗝值 */ 
/**003, 042; Line_106*/  { 0x541U, (void *)&stD2dPowPreCtrl.ftVoltBusBurst, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 母线电压打嗝值 */ 
/**003, 043; Line_107*/  { 0x481U, (void *)&stD2dPowPreCtrl.uiFlgRampDone, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 给定软起完成标志位 */ 
/**003, 044; Line_108*/  { 0x481U, (void *)&stD2dPowPreCtrl.uiFlgDp3OLDone, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB原边内移相角软起完成标志位 */ 
/**003, 045; Line_109*/  { 0x441U, (void *)&stCmnAdc.stAux12V.siVal1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 12V电压值 */ 
/**003, 046; Line_110*/  { 0x441U, (void *)&stCmnAdc.stAux1V5.siVal1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 1.5V电压值 */ 
/**003, 047; Line_111*/  { 0x541U, (void *)&stD2dAdc.ftVoltBattLpf100HzEquiv, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电池侧电压等效值 */ 
/** GROUP_4-04PFC数据监视  */
/**004, 001; Line_112*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftVbusLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC直流母线电压值 */ 
/**004, 002; Line_113*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftVbusPosLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC直流半母线电压值 */ 
/**004, 003; Line_114*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftVaRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压A相有效值 */ 
/**004, 004; Line_115*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftVbRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压B相有效值 */ 
/**004, 005; Line_116*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftVcRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压C相有效值 */ 
/**004, 006; Line_117*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siVaDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网A相直流电压值 */ 
/**004, 007; Line_118*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siVbDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网B相直流电压值 */ 
/**004, 008; Line_119*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siVcDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网C相直流电压值 */ 
/**004, 009; Line_120*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftIaRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网A相电流有效值 */ 
/**004, 010; Line_121*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftIbRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网B相电流有效值 */ 
/**004, 011; Line_122*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftIcRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网C相电流有效值 */ 
/**004, 012; Line_123*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftInRmsLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网N相电流有效值 */ 
/**004, 013; Line_124*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siIaDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧A相直流电流 */ 
/**004, 014; Line_125*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siIbDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧B相直流电流 */ 
/**004, 015; Line_126*/  { 0x441U, (void *)&stPfcDataCalc.stMeasParm.siIcDcAvg1000Times, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧C相直流电流 */ 
/**004, 016; Line_127*/  { 0x4C1U, (void *)&stPfcDataCalc.stMeasParm.slActvPower, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网总进线总有功功率 */ 
/**004, 017; Line_128*/  { 0x4C1U, (void *)&stPfcDataCalc.stMeasParm.slRePower, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网总进线总无功功率 */ 
/**004, 018; Line_129*/  { 0x4C1U, (void *)&stPfcDataCalc.stMeasParm.slAprtPower, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网总进线总视在功率 */ 
/**004, 019; Line_130*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftPf, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网功率因数 */ 
/**004, 020; Line_131*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftFrqVaCap, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< cap电网A相频率 */ 
/**004, 021; Line_132*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftFrqVbCap, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< cap电网B相频率 */ 
/**004, 022; Line_133*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftFrqVcCap, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< cap电网C相频率 */ 
/**004, 023; Line_134*/  { 0x541U, (void *)&stPfcDataCalc.stMeasParm.ftFrqCapAvgLPF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< cap电网频率平均值 */ 
/**004, 024; Line_135*/  { 0x481U, (void *)&stPfcDataCalc.stMeasParm.uiVgDiffRms10Times, 0U, UNUSED_ADDR, 10U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC电压偏差 */ 
/**004, 025; Line_136*/  { 0x481U, (void *)&stPfcDataCalc.stMeasParm.uiIgDiffRms100Times, 0U, UNUSED_ADDR, 100U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC电流偏差 */ 
/**004, 026; Line_137*/  { 0x481U, (void *)&stComIf.uiModPfcRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部PFC请求模式 */ 
/**004, 027; Line_138*/  { 0x481U, (void *)&stComIf.uiCmdPfcRun, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 内部PFC请求开关机命令 */ 
/**004, 028; Line_139*/  { 0x481U, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgGridChkOk, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC启机自检成功标志 */ 
/**004, 029; Line_140*/  { 0x481U, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgStrt, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC缓起标志 */ 
/**004, 030; Line_141*/  { 0x481U, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgHF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 过频功率响应标志 */ 
/**004, 031; Line_142*/  { 0x481U, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgLF, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 欠频功率响应标志 */ 
/**004, 032; Line_143*/  { 0x481U, (void *)&stPfcGridCtrl.stActvCtrl.uiFlgPU, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压功率响应标志 */ 
/**004, 033; Line_144*/  { 0x441U, (void *)&stPfcGridCtrl.stActvCtrl.siPwrSet, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 并网模块输出有功功率 */ 
/**004, 034; Line_145*/  { 0x541U, (void *)&stPfcGridCtrl.stReactv.ftPwrSet, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 并网模块输出无功功率 */ 
/** GROUP_5-05AD校准  */
/**005, 001; Line_146*/  { 0x682U, (void *)&stCom.uiStdGridSet, 0U, 104U, 1U, 10000U,UNUSED_ADDR},   /**< 电网标准选择 */ 
/**005, 002; Line_147*/  { 0x481U, (void *)&stEep.uiStdGridSel, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网标准 */ 
/**005, 003; Line_148*/  { 0x480U, (void *)&stEep.stCmdPrm.uiCmd, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 参数更新命令 */ 
/**005, 004; Line_149*/  { 0x481U, (void *)&stEep.stCmdPrm.uiNumSaved, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 已下载参数个数 */ 
/**005, 005; Line_150*/  { 0x481U, (void *)&stEep.stEepErr.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< Eeprom故障位 */ 
/**005, 006; Line_151*/  { 0x742U, (void *)&stCom.ftCoeffKBattVoltCal, 0U, 106U, 1U, 10002U,UNUSED_ADDR},   /**< 输出电压校准比例 */ 
/**005, 007; Line_152*/  { 0x742U, (void *)&stCom.ftCoeffBBattVoltCal, 0U, 110U, 1U, 10006U,UNUSED_ADDR},   /**< 输出电压校准偏置 */ 
/**005, 008; Line_153*/  { 0x742U, (void *)&stCom.ftCoeffKBattCurrCal, 0U, 114U, 1U, 10010U,UNUSED_ADDR},   /**< 输出电流校准比例 */ 
/**005, 009; Line_154*/  { 0x742U, (void *)&stCom.ftCoeffBBattCurrCal, 0U, 118U, 1U, 10014U,UNUSED_ADDR},   /**< 输出电流校准偏置 */ 
/**005, 010; Line_155*/  { 0x742U, (void *)&stCom.ftCoeffKBattDwnVoltCal, 0U, 122U, 1U, 10018U,UNUSED_ADDR},   /**< 下部电压校准比例 */ 
/**005, 011; Line_156*/  { 0x742U, (void *)&stCom.ftCoeffBBattDwnVoltCal, 0U, 126U, 1U, 10022U,UNUSED_ADDR},   /**< 下部电压校准偏置 */ 
/**005, 012; Line_157*/  { 0x742U, (void *)&stCom.ftCoeffKBattDwnCurrCal, 0U, 130U, 1U, 10026U,UNUSED_ADDR},   /**< 下部电流校准比例 */ 
/**005, 013; Line_158*/  { 0x742U, (void *)&stCom.ftCoeffBBattDwnCurrCal, 0U, 134U, 1U, 10030U,UNUSED_ADDR},   /**< 下部电流校准偏置 */ 
/**005, 014; Line_159*/  { 0x480U, (void *)&stCom.uiCmdPfcADZeroAdj, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 零漂校准命令 */ 
/**005, 015; Line_160*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgZero_A, 0U, 138U, 1U, 10034U,UNUSED_ADDR},   /**< 电网电压A相零漂 */ 
/**005, 016; Line_161*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgZero_B, 0U, 140U, 1U, 10036U,UNUSED_ADDR},   /**< 电网电压B相零漂 */ 
/**005, 017; Line_162*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgZero_C, 0U, 142U, 1U, 10038U,UNUSED_ADDR},   /**< 电网电压C相零漂 */ 
/**005, 018; Line_163*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgDcZero_A, 0U, 144U, 1U, 10040U,UNUSED_ADDR},   /**< 电压A相直流分量零漂 */ 
/**005, 019; Line_164*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgDcZero_B, 0U, 146U, 1U, 10042U,UNUSED_ADDR},   /**< 电压B相直流分量零漂 */ 
/**005, 020; Line_165*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siVgDcZero_C, 0U, 148U, 1U, 10044U,UNUSED_ADDR},   /**< 电压C相直流分量零漂 */ 
/**005, 021; Line_166*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgZero_A, 0U, 150U, 1U, 10046U,UNUSED_ADDR},   /**< 网侧电流A相零漂 */ 
/**005, 022; Line_167*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgZero_B, 0U, 152U, 1U, 10048U,UNUSED_ADDR},   /**< 网侧电流B相零漂 */ 
/**005, 023; Line_168*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgZero_C, 0U, 154U, 1U, 10050U,UNUSED_ADDR},   /**< 网侧电流C相零漂 */ 
/**005, 024; Line_169*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgZero_N, 0U, 156U, 1U, 10052U,UNUSED_ADDR},   /**< 网侧电流N相零漂 */ 
/**005, 025; Line_170*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_A, 0U, 158U, 1U, 10054U,UNUSED_ADDR},   /**< 网侧A相直流分量零漂 */ 
/**005, 026; Line_171*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_B, 0U, 160U, 1U, 10056U,UNUSED_ADDR},   /**< 网侧B相直流分量零漂 */ 
/**005, 027; Line_172*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_C, 0U, 162U, 1U, 10058U,UNUSED_ADDR},   /**< 网侧C相直流分量零漂 */ 
/**005, 028; Line_173*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siBusVoltZero, 0U, 164U, 1U, 10060U,UNUSED_ADDR},   /**< 直流母线电压零漂 */ 
/**005, 029; Line_174*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siPosBusVoltZero, 0U, 166U, 1U, 10062U,UNUSED_ADDR},   /**< 直流正半母线电压零漂 */ 
/**005, 030; Line_175*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftVaK, 0U, 168U, 1U, 10064U,UNUSED_ADDR},   /**< 电网电压A斜率校准 */ 
/**005, 031; Line_176*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftVbK, 0U, 172U, 1U, 10068U,UNUSED_ADDR},   /**< 电网电压B斜率校准 */ 
/**005, 032; Line_177*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftVcK, 0U, 176U, 1U, 10072U,UNUSED_ADDR},   /**< 电网电压C斜率校准 */ 
/**005, 033; Line_178*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftIaK, 0U, 180U, 1U, 10076U,UNUSED_ADDR},   /**< 网侧电流A相斜率校准 */ 
/**005, 034; Line_179*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftIbK, 0U, 184U, 1U, 10080U,UNUSED_ADDR},   /**< 网侧电流B相斜率校准 */ 
/**005, 035; Line_180*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftIcK, 0U, 188U, 1U, 10084U,UNUSED_ADDR},   /**< 网侧电流C相斜率校准 */ 
/**005, 036; Line_181*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftInK, 0U, 192U, 1U, 10088U,UNUSED_ADDR},   /**< 网侧电流N相斜率校准 */ 
/**005, 037; Line_182*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftVBusK, 0U, 196U, 1U, 10092U,UNUSED_ADDR},   /**< 直流母线斜率校准 */ 
/**005, 038; Line_183*/  { 0x742U, (void *)&stCom.stPrmPfcAdjCoeff.ftVPosBusK, 0U, 200U, 1U, 10096U,UNUSED_ADDR},   /**< 直流负母线斜率校准 */ 
/**005, 039; Line_184*/  { 0x742U, (void *)&stCom.ftCurrAcRmsLim, 0U, 204U, 1U, 10100U,UNUSED_ADDR},   /**< AC侧电流有效值限制 */ 
/**005, 040; Line_185*/  { 0x682U, (void *)&stCom.uiTypeGrid, 0U, 208U, 1U, 10104U,UNUSED_ADDR},   /**< 电网接线选择 */ 
/**005, 041; Line_186*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N, 0U, 210U, 1U, 10106U,UNUSED_ADDR},   /**< 网侧A相直流分量零漂(N线继电器闭合) */ 
/**005, 042; Line_187*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N, 0U, 212U, 1U, 10108U,UNUSED_ADDR},   /**< 网侧B相直流分量零漂(N线继电器闭合) */ 
/**005, 043; Line_188*/  { 0x642U, (void *)&stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N, 0U, 214U, 1U, 10110U,UNUSED_ADDR},   /**< 网侧C相直流分量零漂(N线继电器闭合) */ 
/** GROUP_6-06PFC系统参数  */
/**006, 001; Line_189*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd2.ftCurrIabcCBC, 0U, 216U, 1U, 104U,UNUSED_ADDR},   /**< Iabc-CBC保护值 */ 
/**006, 002; Line_190*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd2.ftCurrInCBC, 0U, 220U, 1U, 108U,UNUSED_ADDR},   /**< In-CBC保护值 */ 
/**006, 003; Line_191*/  { 0x482U, (void *)&stComTbl.stPrmPfcHw.uiSwtFrqIabc, 0U, 224U, 1U, 112U,UNUSED_ADDR},   /**< Iabc开关频率 */ 
/**006, 004; Line_192*/  { 0x482U, (void *)&stComTbl.stPrmPfcHw.uiDeadTiIabc, 0U, 226U, 1U, 114U,UNUSED_ADDR},   /**< Iabc死区时间 */ 
/**006, 005; Line_193*/  { 0x502U, (void *)&stComTbl.stPrmPfcHw.ulSwtFrqIn, 0U, 228U, 1U, 116U,UNUSED_ADDR},   /**< In开关频率 */ 
/**006, 006; Line_194*/  { 0x482U, (void *)&stComTbl.stPrmPfcHw.uiDeadTiIn, 0U, 232U, 1U, 120U,UNUSED_ADDR},   /**< In死区时间 */ 
/**006, 007; Line_195*/  { 0x481U, (void *)&stPfcDataCalc.stSysParm.uiPerdPwmABC, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< Iabc-PWM周期值 */ 
/**006, 008; Line_196*/  { 0x481U, (void *)&stPfcDataCalc.stSysParm.uiPerdPwmN, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< In-PWM周期值 */ 
/**006, 009; Line_197*/  { 0x541U, (void *)&stPfcDataCalc.stSysParm.ftPLL_DeltaTheta, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PLL中断步长 */ 
/**006, 010; Line_198*/  { 0x541U, (void *)&stPfcDataCalc.stSysParm.ftSampTime, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC采样时间 */ 
/**006, 011; Line_199*/  { 0x541U, (void *)&stComIf.ftIdAcMax, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D轴电流限幅 */ 
/**006, 012; Line_200*/  { 0x541U, (void *)&stCom.ftIqAcRtd, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< Q轴电流限幅 */ 
/**006, 013; Line_201*/  { 0x541U, (void *)&stComIf.ftPAcMax, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC最大有功功率 */ 
/**006, 014; Line_202*/  { 0x541U, (void *)&stCom.ftQAcMax, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC最大无功功率 */ 
/**006, 015; Line_203*/  { 0x541U, (void *)&stComIf.ftPOnePhaMax, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC单相最大有功功率 */ 
/**006, 016; Line_204*/  { 0x541U, (void *)&stCom.ftQOnePhaMax, 0U, UNUSED_ADDR, 1000U, UNUSED_ADDR,UNUSED_ADDR},   /**< AC单相最大无功功率 */ 
/**006, 017; Line_205*/  { 0x481U, (void *)&stPfcDataCalc.stCtrlParm.uiFlgPhaSeqChkOk, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网相序检测成功标志 */ 
/**006, 018; Line_206*/  { 0x481U, (void *)&stPfcDataCalc.stCtrlParm.uiFlgPhaSeq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网相序 */ 
/**006, 019; Line_207*/  { 0x481U, (void *)&stPfcDataCalc.stCtrlParm.uiFlgPllOk, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 锁相成功标志 */ 
/**006, 020; Line_208*/  { 0x481U, (void *)&stPfcDataCalc.stCtrlParm.uiRepet_PiontsNew, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 重复控制器点数 */ 
/**006, 021; Line_209*/  { 0x481U, (void *)&stPfcDataCalc.stCtrlParm.uiRms_PiontsNew, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 有效值计算点数 */ 
/**006, 022; Line_210*/  { 0x540U, (void *)&stComTbl.stRtdPrm.ftCurrBattParlMax, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D最大输出电流（并联） */ 
/**006, 023; Line_211*/  { 0x541U, (void *)&stCom.ftPowBattMax, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D最大输出功率 */ 
/**006, 024; Line_212*/  { 0x480U, (void *)&stComTbl.stPrmToFpga.uiPeriodCHB, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC驱动周期值 */ 
/** GROUP_7-07故障字  */
/**007, 001; Line_213*/  { 0x481U, (void *)&stComTbl.unWordPfcFlt1.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC故障字1 */ 
/**007, 002; Line_214*/  { 0x481U, (void *)&stComTbl.unWordPfcFlt2.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC故障字2 */ 
/**007, 003; Line_215*/  { 0x480U, (void *)&stComTbl.unWordPfcFlt3.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC故障字3 */ 
/**007, 004; Line_216*/  { 0x481U, (void *)&stD2dDiag.uiFltCpu, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D故障1 */ 
/**007, 005; Line_217*/  { 0x481U, (void *)&stD2dDiag.uiFltCla, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D故障2 */ 
/**007, 006; Line_218*/  { 0x481U, (void *)&stComTbl.unWordSysFlt.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 系统故障字 */ 
/**007, 007; Line_219*/  { 0x481U, (void *)&stPfcDiag.uiMaxFltLevel, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC当前最大故障等级 */ 
/**007, 008; Line_220*/  { 0x481U, (void *)&stEmifDma1.unRunStateA1_4.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相1-4模块运行状态 */ 
/**007, 009; Line_221*/  { 0x481U, (void *)&stEmifDma1.unRunStateA5_6.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相5-8模块运行状态 */ 
/**007, 010; Line_222*/  { 0x481U, (void *)&stEmifDma1.unRunStateB1_4.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相1-4模块运行状态 */ 
/**007, 011; Line_223*/  { 0x481U, (void *)&stEmifDma1.unRunStateB5_6.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相5-8模块运行状态 */ 
/**007, 012; Line_224*/  { 0x481U, (void *)&stEmifDma1.unRunStateC1_4.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相1-4模块运行状态 */ 
/**007, 013; Line_225*/  { 0x481U, (void *)&stEmifDma1.unRunStateC5_6.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相5-8模块运行状态 */ 
/**007, 014; Line_226*/  { 0x481U, (void *)&stEmifDma1.uiRedunStateA1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块冗余状态 */ 
/**007, 015; Line_227*/  { 0x481U, (void *)&stEmifDma1.uiRedunStateB1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块冗余状态 */ 
/**007, 016; Line_228*/  { 0x481U, (void *)&stEmifDma1.uiRedunStateC1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块冗余状态 */ 
/**007, 017; Line_229*/  { 0x441U, (void *)&stEmifDma1.siFltSaveA, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相锁存故障 */ 
/**007, 018; Line_230*/  { 0x441U, (void *)&stEmifDma1.siFltSaveB, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相锁存故障 */ 
/**007, 019; Line_231*/  { 0x441U, (void *)&stEmifDma1.siFltSaveC, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相锁存故障 */ 
/**007, 020; Line_232*/  { 0x441U, (void *)&stEmif.siFltChbCell[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A1高压模块故障 */ 
/**007, 021; Line_233*/  { 0x441U, (void *)&stEmif.siFltChbCell[0][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A2高压模块故障 */ 
/**007, 022; Line_234*/  { 0x441U, (void *)&stEmif.siFltChbCell[0][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A3高压模块故障 */ 
/**007, 023; Line_235*/  { 0x441U, (void *)&stEmif.siFltChbCell[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B1高压模块故障 */ 
/**007, 024; Line_236*/  { 0x441U, (void *)&stEmif.siFltChbCell[1][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B2高压模块故障 */ 
/**007, 025; Line_237*/  { 0x441U, (void *)&stEmif.siFltChbCell[1][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B3高压模块故障 */ 
/**007, 026; Line_238*/  { 0x441U, (void *)&stEmif.siFltChbCell[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C1高压模块故障 */ 
/**007, 027; Line_239*/  { 0x441U, (void *)&stEmif.siFltChbCell[2][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C2高压模块故障 */ 
/**007, 028; Line_240*/  { 0x441U, (void *)&stEmif.siFltChbCell[2][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C3高压模块故障 */ 
/**007, 029; Line_241*/  { 0x441U, (void *)&stEmif.siFltDabCell[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A1低压模块故障 */ 
/**007, 030; Line_242*/  { 0x441U, (void *)&stEmif.siFltDabCell[0][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A2低压模块故障 */ 
/**007, 031; Line_243*/  { 0x441U, (void *)&stEmif.siFltDabCell[0][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A3低压模块故障 */ 
/**007, 032; Line_244*/  { 0x441U, (void *)&stEmif.siFltDabCell[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B1低压模块故障 */ 
/**007, 033; Line_245*/  { 0x441U, (void *)&stEmif.siFltDabCell[1][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B2低压模块故障 */ 
/**007, 034; Line_246*/  { 0x441U, (void *)&stEmif.siFltDabCell[1][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B3低压模块故障 */ 
/**007, 035; Line_247*/  { 0x441U, (void *)&stEmif.siFltDabCell[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C1低压模块故障 */ 
/**007, 036; Line_248*/  { 0x441U, (void *)&stEmif.siFltDabCell[2][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C2低压模块故障 */ 
/**007, 037; Line_249*/  { 0x441U, (void *)&stEmif.siFltDabCell[2][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C3低压模块故障 */ 
/** GROUP_8-08故障屏蔽字  */
/**008, 001; Line_250*/  { 0x482U, (void *)&stComTbl.unWordPfcFltMask1.all, 0U, 234U, 1U, 122U,UNUSED_ADDR},   /**< PFC故障屏蔽字1 */ 
/**008, 002; Line_251*/  { 0x482U, (void *)&stComTbl.unWordPfcFltMask2.all, 0U, 236U, 1U, 124U,UNUSED_ADDR},   /**< PFC故障屏蔽字2 */ 
/**008, 003; Line_252*/  { 0x482U, (void *)&stComTbl.unWordPfcFltMask3.all, 0U, 238U, 1U, 126U,UNUSED_ADDR},   /**< PFC故障屏蔽字3 */ 
/**008, 004; Line_253*/  { 0x482U, (void *)&stComTbl.stPrmD2dDiag.uiFltCpuNC, 0U, 240U, 1U, 128U,UNUSED_ADDR},   /**< D2D故障屏蔽字1 */ 
/**008, 005; Line_254*/  { 0x482U, (void *)&stComTbl.unWordSysFltMask.all, 0U, 242U, 1U, 130U,UNUSED_ADDR},   /**< 系统故障屏蔽字 */ 
/** GROUP_9-09故障门限  */
/**009, 001; Line_255*/  { 0x542U, (void *)&stComTbl.stPrmD2dDiag.ftCurrBattImbal, 0U, 244U, 1U, 132U,UNUSED_ADDR},   /**< D2D输出不均流保护值 */ 
/**009, 002; Line_256*/  { 0x542U, (void *)&stComTbl.stPrmD2dDiag.ftVoltBattImbal, 0U, 248U, 1U, 136U,UNUSED_ADDR},   /**< D2D输出不均压保护值 */ 
/**009, 003; Line_257*/  { 0x542U, (void *)&stComTbl.stPrmD2dDiag.ftVoltBattUV, 0U, 252U, 1U, 140U,UNUSED_ADDR},   /**< D2D输出欠压保护值 */ 
/**009, 004; Line_258*/  { 0x542U, (void *)&stPfcDiag.ftAcOCProt, 0U, 256U, 1U, 144U,UNUSED_ADDR},   /**< 电网（软件）瞬时过流门限 */ 
/**009, 005; Line_259*/  { 0x482U, (void *)&stPfcDiag.uiTiAcOCProt, 0U, 260U, 1U, 148U,UNUSED_ADDR},   /**< 电网（软件）瞬时过流持续时间 */ 
/**009, 006; Line_260*/  { 0x542U, (void *)&stPfcDiag.ftAcOVProt, 0U, 262U, 1U, 150U,UNUSED_ADDR},   /**< 电网瞬时过压门限 */ 
/**009, 007; Line_261*/  { 0x482U, (void *)&stPfcDiag.uiTiAcOVProt, 0U, 266U, 1U, 154U,UNUSED_ADDR},   /**< 电网瞬时过压持续时间 */ 
/**009, 008; Line_262*/  { 0x482U, (void *)&stPfcDiag.uiVoltAcImBal10Times, 0U, 268U, 10U, 156U,UNUSED_ADDR},   /**< 电网电压不平衡门限 */ 
/**009, 009; Line_263*/  { 0x482U, (void *)&stPfcDiag.uiBusOVProt10Times, 0U, 270U, 10U, 158U,UNUSED_ADDR},   /**< PFC母线过压门限 */ 
/**009, 010; Line_264*/  { 0x482U, (void *)&stPfcDiag.uiHalfBusOVProt10Times, 0U, 272U, 10U, 160U,UNUSED_ADDR},   /**< PFC半母线过压门限 */ 
/**009, 011; Line_265*/  { 0x482U, (void *)&stPfcDiag.uiTiCbcProt, 0U, 274U, 1U, 162U,UNUSED_ADDR},   /**< Iabc-CBC保护时间 */ 
/**009, 012; Line_266*/  { 0x482U, (void *)&stPfcDiag.uiMidBusOVProt10Times, 0U, 276U, 10U, 164U,UNUSED_ADDR},   /**< PFC直流母线采样异常门限 */ 
/**009, 013; Line_267*/  { 0x482U, (void *)&stPfcDiag.uiAcRmsOCProt100Times, 0U, 278U, 100U, 166U,UNUSED_ADDR},   /**< 网侧模块过流门限 */ 
/**009, 014; Line_268*/  { 0x482U, (void *)&stPfcDiag.uiCurrAcImBal100Times, 0U, 280U, 100U, 168U,UNUSED_ADDR},   /**< 网侧相电流偏差门限 */ 
/**009, 015; Line_269*/  { 0x480U, (void *)&stPfcDiag.uiBusUVProt10Times, 0U, UNUSED_ADDR, 10U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC母线欠压门限 */ 
/**009, 016; Line_270*/  { 0x542U, (void *)&stComTbl.stPrmCmnDiag.ftOverTemp, 0U, 282U, 1U, 170U,UNUSED_ADDR},   /**< 高温保护值 */ 
/**009, 017; Line_271*/  { 0x542U, (void *)&stComTbl.stPrmCmnDiag.ftUnderTemp, 0U, 286U, 1U, 174U,UNUSED_ADDR},   /**< 低温保护值 */ 
/**009, 018; Line_272*/  { 0x542U, (void *)&stPfcDiag.ftRatPwrOvLoadLim, 0U, 290U, 1U, 178U,UNUSED_ADDR},   /**< 过载保护系数 */ 
/** GROUP_10-10采样过程  */
/**010, 001; Line_273*/  { 0x541U, (void *)&stD2dAdc.ftCurrBattLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D输出电流采样值 */ 
/**010, 002; Line_274*/  { 0x541U, (void *)&stD2dAdc.ftCurrBattDwnLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D下桥臂输出电流采样值 */ 
/**010, 003; Line_275*/  { 0x541U, (void *)&stD2dAdc.ftCurrBattUpLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D上桥臂输出电流采样值 */ 
/**010, 004; Line_276*/  { 0x541U, (void *)&stD2dAdc.ftVoltBattLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D输出电压采样值 */ 
/**010, 005; Line_277*/  { 0x541U, (void *)&stD2dAdc.ftVoltBattDwnLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D下桥臂输出电压采样值 */ 
/**010, 006; Line_278*/  { 0x541U, (void *)&stD2dAdc.ftVoltBattUpLpf10Hz, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D上桥臂输出电压采样值 */ 
/**010, 007; Line_279*/  { 0x541U, (void *)&stPfcAdc.stVg.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压A相瞬时值 */ 
/**010, 008; Line_280*/  { 0x541U, (void *)&stPfcAdc.stVg.ftVal_B, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压B相瞬时值 */ 
/**010, 009; Line_281*/  { 0x541U, (void *)&stPfcAdc.stVg.ftVal_C, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电网电压C相瞬时值 */ 
/**010, 010; Line_282*/  { 0x541U, (void *)&stPfcAdc.stIg.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电感电流A相瞬时值 */ 
/**010, 011; Line_283*/  { 0x541U, (void *)&stPfcAdc.stIg.ftVal_B, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电感电流B相瞬时值 */ 
/**010, 012; Line_284*/  { 0x541U, (void *)&stPfcAdc.stIg.ftVal_C, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电感电流C相瞬时值 */ 
/**010, 013; Line_285*/  { 0x541U, (void *)&stPfcAdc.stIg.ftVal_N, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电感电流N相瞬时值 */ 
/**010, 014; Line_286*/  { 0x541U, (void *)&stPfcAdc.stVgDc.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压A相直流量瞬时值 */ 
/**010, 015; Line_287*/  { 0x541U, (void *)&stPfcAdc.stVgDc.ftVal_B, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压B相直流量瞬时值 */ 
/**010, 016; Line_288*/  { 0x541U, (void *)&stPfcAdc.stVgDc.ftVal_C, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压C相直流量瞬时值 */ 
/**010, 017; Line_289*/  { 0x541U, (void *)&stPfcAdc.stIgDc.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电流A相直流量瞬时值 */ 
/**010, 018; Line_290*/  { 0x541U, (void *)&stPfcAdc.stIgDc.ftVal_B, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电流B相直流量瞬时值 */ 
/**010, 019; Line_291*/  { 0x541U, (void *)&stPfcAdc.stIgDc.ftVal_C, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电流C相直流量瞬时值 */ 
/**010, 020; Line_292*/  { 0x541U, (void *)&stPfcAdc.stVbus.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 母线电压瞬时值 */ 
/**010, 021; Line_293*/  { 0x541U, (void *)&stPfcAdc.stVbusPos.ftVal_A, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 半母线电压瞬时值 */ 
/**010, 022; Line_294*/  { 0x541U, (void *)&stCmnAdc.ftTempDspCore, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DSP芯片温度 */ 
/**010, 023; Line_295*/  { 0x541U, (void *)&stCmnAdc.ftTempDspBd, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DSP板温度 */ 
/**010, 024; Line_296*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块1上母线电压瞬时值 */ 
/**010, 025; Line_297*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块1下母线电压瞬时值 */ 
/**010, 026; Line_298*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块2上母线电压瞬时值 */ 
/**010, 027; Line_299*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块2下母线电压瞬时值 */ 
/**010, 028; Line_300*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块3上母线电压瞬时值 */ 
/**010, 029; Line_301*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块3下母线电压瞬时值 */ 
/**010, 030; Line_302*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块4上母线电压瞬时值 */ 
/**010, 031; Line_303*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块4下母线电压瞬时值 */ 
/**010, 032; Line_304*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块5上母线电压瞬时值 */ 
/**010, 033; Line_305*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块5下母线电压瞬时值 */ 
/**010, 034; Line_306*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[0][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块6上母线电压瞬时值 */ 
/**010, 035; Line_307*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[0][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块6下母线电压瞬时值 */ 
/**010, 036; Line_308*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块1上母线电压瞬时值 */ 
/**010, 037; Line_309*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块1下母线电压瞬时值 */ 
/**010, 038; Line_310*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块2上母线电压瞬时值 */ 
/**010, 039; Line_311*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块2下母线电压瞬时值 */ 
/**010, 040; Line_312*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块3上母线电压瞬时值 */ 
/**010, 041; Line_313*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块3下母线电压瞬时值 */ 
/**010, 042; Line_314*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块4上母线电压瞬时值 */ 
/**010, 043; Line_315*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块4下母线电压瞬时值 */ 
/**010, 044; Line_316*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块5上母线电压瞬时值 */ 
/**010, 045; Line_317*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块5下母线电压瞬时值 */ 
/**010, 046; Line_318*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[1][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块6上母线电压瞬时值 */ 
/**010, 047; Line_319*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[1][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块6下母线电压瞬时值 */ 
/**010, 048; Line_320*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块1上母线电压瞬时值 */ 
/**010, 049; Line_321*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块1下母线电压瞬时值 */ 
/**010, 050; Line_322*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块2上母线电压瞬时值 */ 
/**010, 051; Line_323*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块2下母线电压瞬时值 */ 
/**010, 052; Line_324*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块3上母线电压瞬时值 */ 
/**010, 053; Line_325*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块3下母线电压瞬时值 */ 
/**010, 054; Line_326*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块4上母线电压瞬时值 */ 
/**010, 055; Line_327*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块4下母线电压瞬时值 */ 
/**010, 056; Line_328*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块5上母线电压瞬时值 */ 
/**010, 057; Line_329*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块5下母线电压瞬时值 */ 
/**010, 058; Line_330*/  { 0x541U, (void *)&stPfcAdc.ftVbusPosCell[2][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块6上母线电压瞬时值 */ 
/**010, 059; Line_331*/  { 0x541U, (void *)&stPfcAdc.ftVbusNegCell[2][5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块6下母线电压瞬时值 */ 
/**010, 060; Line_332*/  { 0x541U, (void *)&stD2dAdc.ftVoltCellBatt[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块1DAB电压瞬时值 */ 
/**010, 061; Line_333*/  { 0x541U, (void *)&stD2dAdc.ftVoltCellBatt[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块1DAB电压瞬时值 */ 
/**010, 062; Line_334*/  { 0x541U, (void *)&stD2dAdc.ftVoltCellBatt[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块1DAB电压瞬时值 */ 
/**010, 063; Line_335*/  { 0x541U, (void *)&stD2dAdc.ftCurrCellBatt[0][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相模块1DAB电流瞬时值 */ 
/**010, 064; Line_336*/  { 0x541U, (void *)&stD2dAdc.ftCurrCellBatt[1][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相模块1DAB电流瞬时值 */ 
/**010, 065; Line_337*/  { 0x541U, (void *)&stD2dAdc.ftCurrCellBatt[2][0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相模块1DAB电流瞬时值 */ 
/** GROUP_11-11PFC逻辑参数  */
/**011, 001; Line_338*/  { 0x482U, (void *)&stComTbl.stPrmPfcPowCtrl.unCmdCtrl1.all, 0U, 294U, 1U, 182U,UNUSED_ADDR},   /**< PFC控制命令字1 */ 
/**011, 002; Line_339*/  { 0x482U, (void *)&stComTbl.stPrmPfcPowCtrl.unCmdCtrl2.all, 0U, 296U, 1U, 184U,UNUSED_ADDR},   /**< PFC控制命令字2 */ 
/**011, 003; Line_340*/  { 0x482U, (void *)&stComTbl.stPrmPowLim.unCmd.all, 0U, 298U, 1U, 186U,UNUSED_ADDR},   /**< 限功率控制命令字 */ 
/**011, 004; Line_341*/  { 0x540U, (void *)&stComTbl.stPrmOffGridCtrl.ftVoltAcDbgSet, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 开环发波幅值设定 */ 
/**011, 005; Line_342*/  { 0x540U, (void *)&stComTbl.stPrmOffGridCtrl.ftFrqAcDbgSet, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 开环发波频率设定 */ 
/**011, 006; Line_343*/  { 0x541U, (void *)&stPfcStMac.ftVoltPreChrgLmt, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 软启成功母线电压门限 */ 
/**011, 007; Line_344*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftCoeffBusPreChg3P, 0U, 300U, 1U, 188U,UNUSED_ADDR},   /**< 母线电压预充系数-三相 */ 
/**011, 008; Line_345*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftCoeffBusPreChg1P, 0U, 304U, 1U, 192U,UNUSED_ADDR},   /**< 母线电压预充系数-单相 */ 
/**011, 009; Line_346*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftVoltBusPfcReq, 0U, 308U, 1U, 196U,UNUSED_ADDR},   /**< PFC单级运行母线电压指令 */ 
/**011, 010; Line_347*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftVoltBusMax, 0U, 312U, 1U, 200U,UNUSED_ADDR},   /**< 直流母线电压上限 */ 
/**011, 011; Line_348*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftVoltBusMin, 0U, 316U, 1U, 204U,UNUSED_ADDR},   /**< 直流母线电压下限 */ 
/**011, 012; Line_349*/  { 0x542U, (void *)&stComTbl.stPrmPowLim.ftVoltBusAdd, 0U, 320U, 1U, 208U,UNUSED_ADDR},   /**< 直流母线电压增加值 */ 
/**011, 013; Line_350*/  { 0x481U, (void *)&stPfcStMac.unPFCSts.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC状态机状态字 */ 
/**011, 014; Line_351*/  { 0x481U, (void *)&stPfcStMac.unGPIOCmd.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC状态机GPIO命令字 */ 
/**011, 015; Line_352*/  { 0x481U, (void *)&stPfcStMac.unCtrlCmd.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC状态机控制命令字 */ 
/**011, 016; Line_353*/  { 0x480U, (void *)&stCom.unCmdFct.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FCT控制字 */ 
/**011, 017; Line_354*/  { 0x481U, (void *)&stPfcDiag.unFlt.all, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< PFC故障寄存器 */ 
/**011, 018; Line_355*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftVoltBusRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 直流母线电压直线加减速输出值 */ 
/**011, 019; Line_356*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftVoltAcAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 逆变输出电压直线加减速输出值 */ 
/**011, 020; Line_357*/  { 0x541U, (void *)&stComIf.ftPwrChrgReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< OCPP充电AC侧功率限制 */ 
/**011, 021; Line_358*/  { 0x541U, (void *)&stComIf.ftPaReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相有功功率需求 */ 
/**011, 022; Line_359*/  { 0x541U, (void *)&stPowLim.ftPaAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相有功功率限幅 */ 
/**011, 023; Line_360*/  { 0x541U, (void *)&stPowLim.ftQaAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相无功功率限幅 */ 
/**011, 024; Line_361*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIaActvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相有功电流幅值给定 */ 
/**011, 025; Line_362*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIaReactvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< A相无功电流幅值给定 */ 
/**011, 026; Line_363*/  { 0x541U, (void *)&stComIf.ftPbReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相有功功率需求 */ 
/**011, 027; Line_364*/  { 0x541U, (void *)&stPowLim.ftPbAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相有功功率限幅 */ 
/**011, 028; Line_365*/  { 0x541U, (void *)&stPowLim.ftQbAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相无功功率限幅 */ 
/**011, 029; Line_366*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIbActvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相有功电流幅值给定 */ 
/**011, 030; Line_367*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIbReactvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< B相无功电流幅值给定 */ 
/**011, 031; Line_368*/  { 0x541U, (void *)&stComIf.ftPcReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相有功功率需求 */ 
/**011, 032; Line_369*/  { 0x541U, (void *)&stPowLim.ftPcAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相有功功率限幅 */ 
/**011, 033; Line_370*/  { 0x541U, (void *)&stPowLim.ftQcAcLim, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相无功功率限幅 */ 
/**011, 034; Line_371*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIcActvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相有功电流幅值给定 */ 
/**011, 035; Line_372*/  { 0x541U, (void *)&stPfcPowPreCtrl.ftIcReactvAmpRef, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< C相无功电流幅值给定 */ 
/**011, 036; Line_373*/  { 0x541U, (void *)&stPowLim.ftTempMax, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 最高温度 */ 
/**011, 037; Line_374*/  { 0x541U, (void *)&stPowLim.ftTempMin, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 最低温度 */ 
/** GROUP_12-12D2D控制参数  */
/**012, 001; Line_375*/  { 0x540U, (void *)&stComTbl.stPrmComIf.ftDs1OLReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB开环原副边移相角给定 */ 
/**012, 002; Line_376*/  { 0x482U, (void *)&stComTbl.stPrmD2dPowPreCtrl.uiFlgFrqJitEn, 0U, 324U, 1U, 212U,UNUSED_ADDR},   /**< 抖频使能 */ 
/**012, 003; Line_377*/  { 0x542U, (void *)&stComTbl.stPrmD2dPowPreCtrl.ftGainFrqJitRng, 0U, 326U, 1U, 214U,UNUSED_ADDR},   /**< 抖频范围 */ 
/**012, 004; Line_378*/  { 0x482U, (void *)&stComTbl.stPrmD2dPowPreCtrl.uiPerdFrqJit, 0U, 330U, 1U, 218U,UNUSED_ADDR},   /**< 抖频周期 */ 
/**012, 005; Line_379*/  { 0x482U, (void *)&stComTbl.stPrmD2dPowCtrl.uiFlgDzCmpEn, 0U, 332U, 1U, 220U,UNUSED_ADDR},   /**< 死区补偿使能 */ 
/**012, 006; Line_380*/  { 0x542U, (void *)&stComTbl.stPrmD2dPowCtrl.ftOutpChrgDirDzCmp, 0U, 334U, 1U, 222U,UNUSED_ADDR},   /**< 死区补偿值 */ 
/**012, 007; Line_381*/  { 0x540U, (void *)&stComTbl.stPrmPowLim.ftVoltBusD2dReq, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< D2D母线电压给定 */ 
/**012, 008; Line_382*/  { 0x540U, (void *)&stComTbl.stPrmD2dPowCtrl.ftFacBattVoltPRKr, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压PR系数 */ 
/**012, 009; Line_383*/  { 0x540U, (void *)&stComTbl.stPrmD2dPowCtrl.ftFacBattCurrPRKr, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电流PR系数 */ 
/**012, 010; Line_384*/  { 0x480U, (void *)&stPerdTsk.uiFlgSWIT1msEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< SWIT动态测试1ms任务使能 */ 
/**012, 011; Line_385*/  { 0x480U, (void *)&stPerdTsk.uiFlgSWIT10msEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< SWIT动态测试10ms任务使能 */ 
/**012, 012; Line_386*/  { 0x480U, (void *)&stPerdTsk.uiFlgSWIT100msEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< SWIT动态测试100ms任务使能 */ 
/**012, 013; Line_387*/  { 0x480U, (void *)&stPerdTsk.uiFlgSWIT1sEn, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< SWIT动态测试1s任务使能 */ 
/**012, 014; Line_388*/  { 0x540U, (void *)&stComTbl.stPrmToFpga.ftD2dPwmPeriodPowCell, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB驱动周期值 */ 
/**012, 015; Line_389*/  { 0x540U, (void *)&stComTbl.stPrmToFpga.ftPwmDutyTarget, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB驱动占空比目标值 */ 
/**012, 016; Line_390*/  { 0x540U, (void *)&stComTbl.stPrmToFpga.ftD2dPwmDeadTimePowCell, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< DAB死区时间 */ 
/** GROUP_13-13调试参数  */
/**013, 001; Line_391*/  { 0x440U, (void *)&stPrmDisp.siPrm1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整型调试常数1 */ 
/**013, 002; Line_392*/  { 0x440U, (void *)&stPrmDisp.siPrm2, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整型调试常数2 */ 
/**013, 003; Line_393*/  { 0x440U, (void *)&stPrmDisp.siPrm3, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整型调试常数3 */ 
/**013, 004; Line_394*/  { 0x440U, (void *)&stPrmDisp.siPrm4, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整型调试常数4 */ 
/**013, 005; Line_395*/  { 0x440U, (void *)&stPrmDisp.siPrm5, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 整型调试常数5 */ 
/**013, 006; Line_396*/  { 0x540U, (void *)&stPrmDisp.ftPrm1, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 浮点型调试常数1 */ 
/**013, 007; Line_397*/  { 0x540U, (void *)&stPrmDisp.ftPrm2, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 浮点型调试常数2 */ 
/**013, 008; Line_398*/  { 0x540U, (void *)&stPrmDisp.ftPrm3, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 浮点型调试常数3 */ 
/**013, 009; Line_399*/  { 0x540U, (void *)&stPrmDisp.ftPrm4, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 浮点型调试常数4 */ 
/**013, 010; Line_400*/  { 0x540U, (void *)&stPrmDisp.ftPrm5, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 浮点型调试常数5 */ 
/**013, 011; Line_401*/  { 0x440U, (void *)&stEmifDma1.siResv[0], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数1 */ 
/**013, 012; Line_402*/  { 0x440U, (void *)&stEmifDma1.siResv[1], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数2 */ 
/**013, 013; Line_403*/  { 0x440U, (void *)&stEmifDma1.siResv[2], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数3 */ 
/**013, 014; Line_404*/  { 0x440U, (void *)&stEmifDma1.siResv[3], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数4 */ 
/**013, 015; Line_405*/  { 0x440U, (void *)&stEmifDma1.siResv[4], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数5 */ 
/**013, 016; Line_406*/  { 0x440U, (void *)&stEmifDma1.siResv[5], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数6 */ 
/**013, 017; Line_407*/  { 0x440U, (void *)&stEmifDma1.siResv[6], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数7 */ 
/**013, 018; Line_408*/  { 0x440U, (void *)&stEmifDma1.siResv[7], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数8 */ 
/**013, 019; Line_409*/  { 0x440U, (void *)&stEmifDma1.siResv[8], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数9 */ 
/**013, 020; Line_410*/  { 0x440U, (void *)&stEmifDma1.siResv[9], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数10 */ 
/**013, 021; Line_411*/  { 0x440U, (void *)&stEmifDma1.siResv[10], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数11 */ 
/**013, 022; Line_412*/  { 0x440U, (void *)&stEmifDma1.siResv[11], 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< FPGA整形调试常数12 */ 
/** GROUP_14-14PFC控制参数1  */
/**014, 001; Line_413*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpPllInit, 0U, 338U, 1U, 226U,UNUSED_ADDR},   /**< 锁相环Kp初始值(未完成锁相) */ 
/**014, 002; Line_414*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiPllInit, 0U, 342U, 1U, 230U,UNUSED_ADDR},   /**< 锁相环Ki初始值(未完成锁相) */ 
/**014, 003; Line_415*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpPll, 0U, 346U, 1U, 234U,UNUSED_ADDR},   /**< 锁相环Kp(完成锁相) */ 
/**014, 004; Line_416*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiPll, 0U, 350U, 1U, 238U,UNUSED_ADDR},   /**< 锁相环Ki(完成锁相) */ 
/**014, 005; Line_417*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpVbusLoop, 0U, 354U, 1U, 242U,UNUSED_ADDR},   /**< 直流母线调节器P设置 */ 
/**014, 006; Line_418*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiVbusLoop, 0U, 358U, 1U, 246U,UNUSED_ADDR},   /**< 直流母线调节器I设置 */ 
/**014, 007; Line_419*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxVbusLoop, 0U, 362U, 1U, 250U,UNUSED_ADDR},   /**< 直流母线调节器输出限幅值上限 */ 
/**014, 008; Line_420*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinVbusLoop, 0U, 366U, 1U, 254U,UNUSED_ADDR},   /**< 直流母线调节器输出限幅值下限 */ 
/**014, 009; Line_421*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpIdPosLoop, 0U, 370U, 1U, 258U,UNUSED_ADDR},   /**< 网侧D轴正序电流调节器P设置 */ 
/**014, 010; Line_422*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiIdPosLoop, 0U, 374U, 1U, 262U,UNUSED_ADDR},   /**< 网侧D轴正序电流调节器I设置 */ 
/**014, 011; Line_423*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxIdPosLoop, 0U, 378U, 1U, 266U,UNUSED_ADDR},   /**< 网侧D轴正序电流调节器输出限幅值上限 */ 
/**014, 012; Line_424*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinIdPosLoop, 0U, 382U, 1U, 270U,UNUSED_ADDR},   /**< 网侧D轴正序电流调节器输出限幅值下限 */ 
/**014, 013; Line_425*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpIdNegLoop, 0U, 386U, 1U, 274U,UNUSED_ADDR},   /**< 网侧D轴负序电流调节器P设置 */ 
/**014, 014; Line_426*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiIdNegLoop, 0U, 390U, 1U, 278U,UNUSED_ADDR},   /**< 网侧D轴负序电流调节器I设置 */ 
/**014, 015; Line_427*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxIdNegLoop, 0U, 394U, 1U, 282U,UNUSED_ADDR},   /**< 网侧D轴负序电流调节器输出限幅值上限 */ 
/**014, 016; Line_428*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinIdNegLoop, 0U, 398U, 1U, 286U,UNUSED_ADDR},   /**< 网侧D轴负序电流调节器输出限幅值下限 */ 
/**014, 017; Line_429*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpCurrLoop, 0U, 402U, 1U, 290U,UNUSED_ADDR},   /**< 单相模式电流调节器P设置 */ 
/**014, 018; Line_430*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiCurrLoop, 0U, 406U, 1U, 294U,UNUSED_ADDR},   /**< 单相模式电流调节器I设置 */ 
/**014, 019; Line_431*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxCurrLoop, 0U, 410U, 1U, 298U,UNUSED_ADDR},   /**< 单相模式电流调节器输出限幅值上限 */ 
/**014, 020; Line_432*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinCurrLoop, 0U, 414U, 1U, 302U,UNUSED_ADDR},   /**< 单相模式电流调节器输出限幅值下限 */ 
/**014, 021; Line_433*/  { 0x542U, (void *)&stComTbl.stPrmBalBrdg.ftVoltBalEna, 0U, 418U, 1U, 306U,UNUSED_ADDR},   /**< 中点模块使能门限 */ 
/** GROUP_15-15PFC控制参数2  */
/**015, 001; Line_434*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpVdPosLoop, 0U, 422U, 1U, 310U,UNUSED_ADDR},   /**< 逆变电压D轴正序调节器P设置 */ 
/**015, 002; Line_435*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiVdPosLoop, 0U, 426U, 1U, 314U,UNUSED_ADDR},   /**< 逆变电压D轴正序调节器I设置 */ 
/**015, 003; Line_436*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxVdPosLoop, 0U, 430U, 1U, 318U,UNUSED_ADDR},   /**< 逆变电压D轴正序调节器输出限幅值上限 */ 
/**015, 004; Line_437*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinVdPosLoop, 0U, 434U, 1U, 322U,UNUSED_ADDR},   /**< 逆变电压D轴正序调节器输出限幅值下限 */ 
/**015, 005; Line_438*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKpVdNegLoop, 0U, 438U, 1U, 326U,UNUSED_ADDR},   /**< 逆变电压D轴负序调节器P设置 */ 
/**015, 006; Line_439*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKiVdNegLoop, 0U, 442U, 1U, 330U,UNUSED_ADDR},   /**< 逆变电压D轴负序调节器I设置 */ 
/**015, 007; Line_440*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMaxVdNegLoop, 0U, 446U, 1U, 334U,UNUSED_ADDR},   /**< 逆变电压D轴负序调节器输出限幅值上限 */ 
/**015, 008; Line_441*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftMinVdNegLoop, 0U, 450U, 1U, 338U,UNUSED_ADDR},   /**< 逆变电压D轴负序调节器输出限幅值下限 */ 
/**015, 009; Line_442*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftQzVacLoopRep, 0U, 454U, 1U, 342U,UNUSED_ADDR},   /**< AC电压环重复控制系数Qz */ 
/**015, 010; Line_443*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftKrCompVacLoopRep, 0U, 458U, 1U, 346U,UNUSED_ADDR},   /**< AC电压环重复控制补偿系数Kr */ 
/**015, 011; Line_444*/  { 0x482U, (void *)&stComTbl.stPrmPfcPowCtrl.uiNrPhaCompVacLoopRep, 0U, 462U, 1U, 350U,UNUSED_ADDR},   /**< AC电压环重复控制补偿相位 */ 
/**015, 012; Line_445*/  { 0x542U, (void *)&stComTbl.stPrmPfcPowCtrl.ftOutpMaxVacLoopRep, 0U, 464U, 1U, 352U,UNUSED_ADDR},   /**< AC电压环重复控制输出限幅 */ 
/** GROUP_16-16网侧参数  */
/**016, 001; Line_446*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftKpIdcCtrl, 0U, 468U, 1U, 356U,UNUSED_ADDR},   /**< 电流直流量调节器P设置 */ 
/**016, 002; Line_447*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftKiIdcCtrl, 0U, 472U, 1U, 360U,UNUSED_ADDR},   /**< 电流直流量调节器I设置 */ 
/**016, 003; Line_448*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftOutpLimIdcCtrl, 0U, 476U, 1U, 364U,UNUSED_ADDR},   /**< 电流直流量调节限制 */ 
/**016, 004; Line_449*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftIaDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧A相电流直流分量补偿值 */ 
/**016, 005; Line_450*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftIbDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧B相电流直流分量补偿值 */ 
/**016, 006; Line_451*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftIcDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 网侧C相电流直流分量补偿值 */ 
/**016, 007; Line_452*/  { 0x482U, (void *)&stPfcDiag.uiVgDcProt1000Times, 0U, 480U, 1U, 368U,UNUSED_ADDR},   /**< 电压直流分量超限门限 */ 
/**016, 008; Line_453*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftKpVdcCtrl, 0U, 482U, 1U, 370U,UNUSED_ADDR},   /**< 电压直流量调节器P设置 */ 
/**016, 009; Line_454*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftKiVdcCtrl, 0U, 486U, 1U, 374U,UNUSED_ADDR},   /**< 电压直流量调节器I设置 */ 
/**016, 010; Line_455*/  { 0x542U, (void *)&stComTbl.stPrmDcCpt.ftOutpLimtVdcCtrl, 0U, 490U, 1U, 378U,UNUSED_ADDR},   /**< 电压直流量调节限制 */ 
/**016, 011; Line_456*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftVaDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压直流量调节器A相输出 */ 
/**016, 012; Line_457*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftVbDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压直流量调节器B相输出 */ 
/**016, 013; Line_458*/  { 0x541U, (void *)&stPfcGridCtrl.stDstbc.ftVcDcInhb, 0U, UNUSED_ADDR, 1U, UNUSED_ADDR,UNUSED_ADDR},   /**< 电压直流量调节器C相输出 */ 
/** GROUP_17-17电网额定参数  */
/**017, 001; Line_459*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftVoltGrid, 0U, 494U, 1U, 382U,UNUSED_ADDR},   /**< 额定电网电压 */ 
/**017, 002; Line_460*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftFrqGrid, 0U, 498U, 1U, 386U,UNUSED_ADDR},   /**< 额定电网频率 */ 
/**017, 003; Line_461*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftPowRtd, 0U, 502U, 1U, 390U,UNUSED_ADDR},   /**< 额定功率 */ 
/**017, 004; Line_462*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftPFMin, 0U, 506U, 1U, 394U,UNUSED_ADDR},   /**< 额定功率因数 */ 
/**017, 005; Line_463*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftPowBattChrgRtd, 0U, 510U, 1U, 398U,UNUSED_ADDR},   /**< 电池额定充电功率 */ 
/**017, 006; Line_464*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftRatAcOvLoad, 0U, 514U, 1U, 402U,UNUSED_ADDR},   /**< 交流过载系数 */ 
/**017, 007; Line_465*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftRsvd1, 0U, 518U, 1U, 406U,UNUSED_ADDR},   /**< 电网额定浮点型参数预留1 */ 
/**017, 008; Line_466*/  { 0x542U, (void *)&stComTbl.stPrmPfcRtd1.ftRsvd0, 0U, 522U, 1U, 410U,UNUSED_ADDR},   /**< 电网额定浮点型参数预留0 */ 
/**017, 009; Line_467*/  { 0x482U, (void *)&stComTbl.stPrmPfcRtd1.uiRsvd1, 0U, 526U, 1U, 414U,UNUSED_ADDR},   /**< 电网额定整形参数预留1 */ 
/**017, 010; Line_468*/  { 0x482U, (void *)&stComTbl.stPrmPfcRtd1.uiRsvd0, 0U, 528U, 1U, 416U,UNUSED_ADDR},   /**< 电网额定整形参数预留0 */ 
/** GROUP_18-18V2G功率控制  */
/**018, 001; Line_469*/  { 0x482U, (void *)&stCom.uiModeReactv, 0U, 530U, 1U, 418U,UNUSED_ADDR},   /**< 无功模式 */ 
/**018, 002; Line_470*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiEnaAntiIsland, 0U, 532U, 1U, 420U,UNUSED_ADDR},   /**< 主动孤岛开关 */ 
/**018, 003; Line_471*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiEnaCurrDcCtrl, 0U, 534U, 1U, 422U,UNUSED_ADDR},   /**< 电流直流分量抑制开关 */ 
/**018, 004; Line_472*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiEnaVoltDcCtrl, 0U, 536U, 1U, 424U,UNUSED_ADDR},   /**< 电压直流分量抑制开关 */ 
/**018, 005; Line_473*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiEnaFltRcvPwrLim, 0U, 538U, 1U, 426U,UNUSED_ADDR},   /**< 故障缓起开关 */ 
/**018, 006; Line_474*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiEnaEntrSrv, 0U, 540U, 1U, 428U,UNUSED_ADDR},   /**< Enter Service开关 */ 
/**018, 007; Line_475*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRatePwrUpNorm, 0U, 542U, 1U, 430U,UNUSED_ADDR},   /**< 有功上升速率 */ 
/**018, 008; Line_476*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRatePwrDwnNorm, 0U, 546U, 1U, 434U,UNUSED_ADDR},   /**< 有功下降速率 */ 
/**018, 009; Line_477*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRatePwrReload, 0U, 550U, 1U, 438U,UNUSED_ADDR},   /**< 重连速率 */ 
/**018, 010; Line_478*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiWaitRecnct, 0U, 554U, 100U, 442U,UNUSED_ADDR},   /**< 重连等待时间 */ 
/**018, 011; Line_479*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRatePwrLoad, 0U, 558U, 1U, 446U,UNUSED_ADDR},   /**< 启动速率 */ 
/**018, 012; Line_480*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiWaitCnct, 0U, 562U, 100U, 450U,UNUSED_ADDR},   /**< 启动等待时间 */ 
/**018, 013; Line_481*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftVoltGridReCnctMax, 0U, 566U, 1U, 454U,UNUSED_ADDR},   /**< 重连并网电压上限 */ 
/**018, 014; Line_482*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftVoltGridReCnctMin, 0U, 570U, 1U, 458U,UNUSED_ADDR},   /**< 重连并网电压下限 */ 
/**018, 015; Line_483*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftFrqGridReCnctMax, 0U, 574U, 1U, 462U,UNUSED_ADDR},   /**< 重连并网频率上限 */ 
/**018, 016; Line_484*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftFrqGridReCnctMin, 0U, 578U, 1U, 466U,UNUSED_ADDR},   /**< 重连并网频率下限 */ 
/**018, 017; Line_485*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftVoltGridCnctMax, 0U, 582U, 1U, 470U,UNUSED_ADDR},   /**< 初始并网电压上限 */ 
/**018, 018; Line_486*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftVoltGridCnctMin, 0U, 586U, 1U, 474U,UNUSED_ADDR},   /**< 初始并网电压下限 */ 
/**018, 019; Line_487*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftFrqGridCnctMax, 0U, 590U, 1U, 478U,UNUSED_ADDR},   /**< 初始并网频率上限 */ 
/**018, 020; Line_488*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftFrqGridCnctMin, 0U, 594U, 1U, 482U,UNUSED_ADDR},   /**< 初始并网频率下限 */ 
/**018, 021; Line_489*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiReactvRespPf, 0U, 598U, 1U, 486U,UNUSED_ADDR},   /**< 无功PF响应时间 */ 
/**018, 022; Line_490*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiReactvRespQu, 0U, 602U, 1U, 490U,UNUSED_ADDR},   /**< 无功QU响应时间 */ 
/**018, 023; Line_491*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiReactvRespQp, 0U, 606U, 1U, 494U,UNUSED_ADDR},   /**< 无功QP响应时间 */ 
/**018, 024; Line_492*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftTiReactvRespQt, 0U, 610U, 1U, 498U,UNUSED_ADDR},   /**< 无功QT响应时间 */ 
/**018, 025; Line_493*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiRsvd1, 0U, 614U, 1U, 502U,UNUSED_ADDR},   /**< 功率控制预留整型1 */ 
/**018, 026; Line_494*/  { 0x482U, (void *)&stComTbl.stPrmPwrCtrl.uiRsvd0, 0U, 616U, 1U, 504U,UNUSED_ADDR},   /**< 功率控制预留整型0 */ 
/**018, 027; Line_495*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRsvd1, 0U, 618U, 1U, 506U,UNUSED_ADDR},   /**< 功率控制预留浮点型1 */ 
/**018, 028; Line_496*/  { 0x542U, (void *)&stComTbl.stPrmPwrCtrl.ftRsvd0, 0U, 622U, 1U, 510U,UNUSED_ADDR},   /**< 功率控制预留浮点型0 */ 
/** GROUP_19-19电网保护参数  */
/**019, 001; Line_497*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiEnaOV10minProt, 0U, 626U, 1U, 514U,UNUSED_ADDR},   /**< 十分钟过压保护开关 */ 
/**019, 002; Line_498*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOver10min, 0U, 628U, 1U, 516U,UNUSED_ADDR},   /**< 十分钟过压保护值 */ 
/**019, 003; Line_499*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOver10minRcv, 0U, 632U, 1U, 520U,UNUSED_ADDR},   /**< 十分钟过压恢复值 */ 
/**019, 004; Line_500*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiClassProt, 0U, 636U, 1U, 524U,UNUSED_ADDR},   /**< 电压保护级数 */ 
/**019, 005; Line_501*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiModePrtTi, 0U, 638U, 1U, 526U,UNUSED_ADDR},   /**< 电压保护时间模式 */ 
/**019, 006; Line_502*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOver1, 0U, 640U, 1U, 528U,UNUSED_ADDR},   /**< 过压1级保护值 */ 
/**019, 007; Line_503*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiOver1, 0U, 644U, 100U, 532U,UNUSED_ADDR},   /**< 过压1级保护时间 */ 
/**019, 008; Line_504*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOver2, 0U, 648U, 1U, 536U,UNUSED_ADDR},   /**< 过压2级保护值 */ 
/**019, 009; Line_505*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiOver2, 0U, 652U, 100U, 540U,UNUSED_ADDR},   /**< 过压2级保护时间 */ 
/**019, 010; Line_506*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOver3, 0U, 656U, 1U, 544U,UNUSED_ADDR},   /**< 过压3级保护值 */ 
/**019, 011; Line_507*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiOver3, 0U, 660U, 100U, 548U,UNUSED_ADDR},   /**< 过压3级保护时间 */ 
/**019, 012; Line_508*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValOverRcv, 0U, 664U, 1U, 552U,UNUSED_ADDR},   /**< 过压恢复值 */ 
/**019, 013; Line_509*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValUnder1, 0U, 668U, 1U, 556U,UNUSED_ADDR},   /**< 欠压1级保护值 */ 
/**019, 014; Line_510*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiUnder1, 0U, 672U, 100U, 560U,UNUSED_ADDR},   /**< 欠压1级保护时间 */ 
/**019, 015; Line_511*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValUnder2, 0U, 676U, 1U, 564U,UNUSED_ADDR},   /**< 欠压2级保护值 */ 
/**019, 016; Line_512*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiUnder2, 0U, 680U, 100U, 568U,UNUSED_ADDR},   /**< 欠压2级保护时间 */ 
/**019, 017; Line_513*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValUnder3, 0U, 684U, 1U, 572U,UNUSED_ADDR},   /**< 欠压3级保护值 */ 
/**019, 018; Line_514*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftTiUnder3, 0U, 688U, 100U, 576U,UNUSED_ADDR},   /**< 欠压3级保护时间 */ 
/**019, 019; Line_515*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValUnderRcv, 0U, 692U, 1U, 580U,UNUSED_ADDR},   /**< 欠压恢复值 */ 
/**019, 020; Line_516*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiModePrtSel, 0U, 696U, 1U, 584U,UNUSED_ADDR},   /**< 电压保护模式选择 */ 
/**019, 021; Line_517*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiEnaRoCoF, 0U, 698U, 1U, 586U,UNUSED_ADDR},   /**< 电压保护-整型预留1 */ 
/**019, 022; Line_518*/  { 0x482U, (void *)&stComTbl.stPrmGridVoltProt.uiRsvd0, 0U, 700U, 1U, 588U,UNUSED_ADDR},   /**< 电压保护-整型预留0 */ 
/**019, 023; Line_519*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftValRoCoF, 0U, 702U, 1U, 590U,UNUSED_ADDR},   /**< 电压保护-浮点型预留2 */ 
/**019, 024; Line_520*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftRsvd1, 0U, 706U, 1U, 594U,UNUSED_ADDR},   /**< 电压保护-浮点型预留1 */ 
/**019, 025; Line_521*/  { 0x542U, (void *)&stComTbl.stPrmGridVoltProt.ftRsvd0, 0U, 710U, 1U, 598U,UNUSED_ADDR},   /**< 电压保护-浮点型预留0 */ 
/**019, 026; Line_522*/  { 0x482U, (void *)&stComTbl.stPrmGridFrqProt.uiClassProt, 0U, 714U, 1U, 602U,UNUSED_ADDR},   /**< 频率保护级数 */ 
/**019, 027; Line_523*/  { 0x482U, (void *)&stComTbl.stPrmGridFrqProt.uiModePrtTi, 0U, 716U, 1U, 604U,UNUSED_ADDR},   /**< 频率保护时间模式 */ 
/**019, 028; Line_524*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValOver1, 0U, 718U, 1U, 606U,UNUSED_ADDR},   /**< 过频1级保护值 */ 
/**019, 029; Line_525*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiOver1, 0U, 722U, 100U, 610U,UNUSED_ADDR},   /**< 过频1级保护时间 */ 
/**019, 030; Line_526*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValOver2, 0U, 726U, 1U, 614U,UNUSED_ADDR},   /**< 过频2级保护值 */ 
/**019, 031; Line_527*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiOver2, 0U, 730U, 100U, 618U,UNUSED_ADDR},   /**< 过频2级保护时间 */ 
/**019, 032; Line_528*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValOver3, 0U, 734U, 1U, 622U,UNUSED_ADDR},   /**< 过频3级保护值 */ 
/**019, 033; Line_529*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiOver3, 0U, 738U, 100U, 626U,UNUSED_ADDR},   /**< 过频3级保护时间 */ 
/**019, 034; Line_530*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValOverRcv, 0U, 742U, 1U, 630U,UNUSED_ADDR},   /**< 过频恢复值 */ 
/**019, 035; Line_531*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValUnder1, 0U, 746U, 1U, 634U,UNUSED_ADDR},   /**< 欠频1级保护值 */ 
/**019, 036; Line_532*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiUnder1, 0U, 750U, 100U, 638U,UNUSED_ADDR},   /**< 欠频1级保护时间 */ 
/**019, 037; Line_533*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValUnder2, 0U, 754U, 1U, 642U,UNUSED_ADDR},   /**< 欠频2级保护值 */ 
/**019, 038; Line_534*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiUnder2, 0U, 758U, 100U, 646U,UNUSED_ADDR},   /**< 欠频2级保护时间 */ 
/**019, 039; Line_535*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValUnder3, 0U, 762U, 1U, 650U,UNUSED_ADDR},   /**< 欠频3级保护值 */ 
/**019, 040; Line_536*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftTiUnder3, 0U, 766U, 100U, 654U,UNUSED_ADDR},   /**< 欠频3级保护时间 */ 
/**019, 041; Line_537*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValUnderRcv, 0U, 770U, 1U, 658U,UNUSED_ADDR},   /**< 欠频恢复值 */ 
/**019, 042; Line_538*/  { 0x482U, (void *)&stComTbl.stPrmGridFrqProt.uiModePrtSel, 0U, 774U, 1U, 662U,UNUSED_ADDR},   /**< 意大利宽窄频控制本地命令 */ 
/**019, 043; Line_539*/  { 0x482U, (void *)&stComTbl.stPrmGridFrqProt.uiEnaRoCoF, 0U, 776U, 1U, 664U,UNUSED_ADDR},   /**< RoCoF保护开关 */ 
/**019, 044; Line_540*/  { 0x482U, (void *)&stComTbl.stPrmGridFrqProt.uiRsvd0, 0U, 778U, 1U, 666U,UNUSED_ADDR},   /**< 频率保护-整型预留0 */ 
/**019, 045; Line_541*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftValRoCoF, 0U, 780U, 1U, 668U,UNUSED_ADDR},   /**< RoCoF保护值 */ 
/**019, 046; Line_542*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftRsvd1, 0U, 784U, 1U, 672U,UNUSED_ADDR},   /**< 频率保护-浮点型预留1 */ 
/**019, 047; Line_543*/  { 0x542U, (void *)&stComTbl.stPrmGridFrqProt.ftRsvd0, 0U, 788U, 1U, 676U,UNUSED_ADDR},   /**< 频率保护-浮点型预留0 */ 
/**019, 048; Line_544*/  { 0x542U, (void *)&stComTbl.stIdcPrt.ftIdcOv1Perc, 0U, 792U, 1U, 680U,UNUSED_ADDR},   /**< Idc保护阈值 */ 
/**019, 049; Line_545*/  { 0x542U, (void *)&stComTbl.stIdcPrt.ftTiIdcOv1, 0U, 796U, 100U, 684U,UNUSED_ADDR},   /**< Idc保护时间 */ 
/** GROUP_20-20频率响应参数  */
/**020, 001; Line_546*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespHF.uiEna, 0U, 800U, 1U, 688U,UNUSED_ADDR},   /**< HF-开关 */ 
/**020, 002; Line_547*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespHF.uiCurve, 0U, 802U, 1U, 690U,UNUSED_ADDR},   /**< HF-曲线选择 */ 
/**020, 003; Line_548*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftFrqIn, 0U, 804U, 1U, 692U,UNUSED_ADDR},   /**< HF-Fin */ 
/**020, 004; Line_549*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftFrqOut, 0U, 808U, 1U, 696U,UNUSED_ADDR},   /**< HF-Fout */ 
/**020, 005; Line_550*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftFrqMid, 0U, 812U, 1U, 700U,UNUSED_ADDR},   /**< HF-Fmid */ 
/**020, 006; Line_551*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftFrqEnd, 0U, 816U, 1U, 704U,UNUSED_ADDR},   /**< HF-Fend */ 
/**020, 007; Line_552*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftTiInWait, 0U, 820U, 100U, 708U,UNUSED_ADDR},   /**< HF-延迟响应时间 */ 
/**020, 008; Line_553*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftTiOutWait, 0U, 824U, 100U, 712U,UNUSED_ADDR},   /**< HF-等待恢复时间 */ 
/**020, 009; Line_554*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftTiResp1stLpf, 0U, 828U, 1U, 716U,UNUSED_ADDR},   /**< HF-LPF响应时间 */ 
/**020, 010; Line_555*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftRatePwrResp, 0U, 832U, 1U, 720U,UNUSED_ADDR},   /**< HF-有功响应速率 */ 
/**020, 011; Line_556*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftRatePwrRcv, 0U, 836U, 1U, 724U,UNUSED_ADDR},   /**< HF-有功恢复速率 */ 
/**020, 012; Line_557*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftSlopCurve1, 0U, 840U, 1U, 728U,UNUSED_ADDR},   /**< HF-有功响应斜率1 */ 
/**020, 013; Line_558*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftSlopCurve2, 0U, 844U, 1U, 732U,UNUSED_ADDR},   /**< HF-有功响应斜率2 */ 
/**020, 014; Line_559*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespHF.uiBaseSlop, 0U, 848U, 1U, 736U,UNUSED_ADDR},   /**< HF-曲线斜率基准 */ 
/**020, 015; Line_560*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespHF.uiRsvd1, 0U, 850U, 1U, 738U,UNUSED_ADDR},   /**< HF-整型预留1 */ 
/**020, 016; Line_561*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespHF.uiRsvd0, 0U, 852U, 1U, 740U,UNUSED_ADDR},   /**< HF-整型预留0 */ 
/**020, 017; Line_562*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftRsvd2, 0U, 854U, 1U, 742U,UNUSED_ADDR},   /**< HF-浮点型预留2 */ 
/**020, 018; Line_563*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftRsvd1, 0U, 858U, 1U, 746U,UNUSED_ADDR},   /**< HF-浮点型预留1 */ 
/**020, 019; Line_564*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespHF.ftRsvd0, 0U, 862U, 1U, 750U,UNUSED_ADDR},   /**< HF-浮点型预留0 */ 
/**020, 020; Line_565*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespLF.uiEna, 0U, 866U, 1U, 754U,UNUSED_ADDR},   /**< LF-开关 */ 
/**020, 021; Line_566*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespLF.uiCurve, 0U, 868U, 1U, 756U,UNUSED_ADDR},   /**< LF-曲线选择 */ 
/**020, 022; Line_567*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftFrqIn, 0U, 870U, 1U, 758U,UNUSED_ADDR},   /**< LF-Fin */ 
/**020, 023; Line_568*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftFrqOut, 0U, 874U, 1U, 762U,UNUSED_ADDR},   /**< LF-Fout */ 
/**020, 024; Line_569*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftFrqMid, 0U, 878U, 1U, 766U,UNUSED_ADDR},   /**< LF-Fmid */ 
/**020, 025; Line_570*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftFrqEnd, 0U, 882U, 1U, 770U,UNUSED_ADDR},   /**< LF-Fend */ 
/**020, 026; Line_571*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftTiInWait, 0U, 886U, 100U, 774U,UNUSED_ADDR},   /**< LF-延迟响应时间 */ 
/**020, 027; Line_572*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftTiOutWait, 0U, 890U, 100U, 778U,UNUSED_ADDR},   /**< LF-等待恢复时间 */ 
/**020, 028; Line_573*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftTiResp1stLpf, 0U, 894U, 1U, 782U,UNUSED_ADDR},   /**< LF-LPF响应时间 */ 
/**020, 029; Line_574*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftRatePwrResp, 0U, 898U, 1U, 786U,UNUSED_ADDR},   /**< LF-有功响应速率 */ 
/**020, 030; Line_575*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftRatePwrRcv, 0U, 902U, 1U, 790U,UNUSED_ADDR},   /**< LF-有功恢复速率 */ 
/**020, 031; Line_576*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftSlopCurve1, 0U, 906U, 1U, 794U,UNUSED_ADDR},   /**< LF-有功响应斜率1 */ 
/**020, 032; Line_577*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftSlopCurve2, 0U, 910U, 1U, 798U,UNUSED_ADDR},   /**< LF-有功响应斜率2 */ 
/**020, 033; Line_578*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespLF.uiBaseSlop, 0U, 914U, 1U, 802U,UNUSED_ADDR},   /**< LF-曲线斜率基准 */ 
/**020, 034; Line_579*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespLF.uiRsvd1, 0U, 916U, 1U, 804U,UNUSED_ADDR},   /**< LF-整型预留1 */ 
/**020, 035; Line_580*/  { 0x482U, (void *)&stComTbl.stPrmPwrRespLF.uiRsvd0, 0U, 918U, 1U, 806U,UNUSED_ADDR},   /**< LF-整型预留0 */ 
/**020, 036; Line_581*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftRsvd1, 0U, 920U, 1U, 808U,UNUSED_ADDR},   /**< LF-浮点型预留1 */ 
/**020, 037; Line_582*/  { 0x542U, (void *)&stComTbl.stPrmPwrRespLF.ftRsvd0, 0U, 924U, 1U, 812U,UNUSED_ADDR},   /**< LF-浮点型预留0 */ 
/** GROUP_21-21无功QU参数  */
/**021, 001; Line_583*/  { 0x482U, (void *)&stComTbl.stPrmReactvQu.uiCurve, 0U, 928U, 1U, 816U,UNUSED_ADDR},   /**< Qu曲线选择 */ 
/**021, 002; Line_584*/  { 0x482U, (void *)&stComTbl.stPrmReactvQu.uiModeResp, 0U, 930U, 1U, 818U,UNUSED_ADDR},   /**< Qu模式 */ 
/**021, 003; Line_585*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftPFLim, 0U, 932U, 1U, 820U,UNUSED_ADDR},   /**< Qu-PF限制值 */ 
/**021, 004; Line_586*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU1_A, 0U, 936U, 1U, 824U,UNUSED_ADDR},   /**< Qu-CurveA-U1 */ 
/**021, 005; Line_587*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ1_A, 0U, 940U, 1U, 828U,UNUSED_ADDR},   /**< Qu-CurveA-Q1 */ 
/**021, 006; Line_588*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU2_A, 0U, 944U, 1U, 832U,UNUSED_ADDR},   /**< Qu-CurveA-U2 */ 
/**021, 007; Line_589*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ2_A, 0U, 948U, 1U, 836U,UNUSED_ADDR},   /**< Qu-CurveA-Q2 */ 
/**021, 008; Line_590*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU3_A, 0U, 952U, 1U, 840U,UNUSED_ADDR},   /**< Qu-CurveA-U3 */ 
/**021, 009; Line_591*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ3_A, 0U, 956U, 1U, 844U,UNUSED_ADDR},   /**< Qu-CurveA-Q3 */ 
/**021, 010; Line_592*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU4_A, 0U, 960U, 1U, 848U,UNUSED_ADDR},   /**< Qu-CurveA-U4 */ 
/**021, 011; Line_593*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ4_A, 0U, 964U, 1U, 852U,UNUSED_ADDR},   /**< Qu-CurveA-Q4 */ 
/**021, 012; Line_594*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU1_B, 0U, 968U, 1U, 856U,UNUSED_ADDR},   /**< Qu-CurveB-U1 */ 
/**021, 013; Line_595*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ1_B, 0U, 972U, 1U, 860U,UNUSED_ADDR},   /**< Qu-CurveB-Q1 */ 
/**021, 014; Line_596*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU2_B, 0U, 976U, 1U, 864U,UNUSED_ADDR},   /**< Qu-CurveB-U2 */ 
/**021, 015; Line_597*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ2_B, 0U, 980U, 1U, 868U,UNUSED_ADDR},   /**< Qu-CurveB-Q2 */ 
/**021, 016; Line_598*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU3_B, 0U, 984U, 1U, 872U,UNUSED_ADDR},   /**< Qu-CurveB-U3 */ 
/**021, 017; Line_599*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ3_B, 0U, 988U, 1U, 876U,UNUSED_ADDR},   /**< Qu-CurveB-Q3 */ 
/**021, 018; Line_600*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioU4_B, 0U, 992U, 1U, 880U,UNUSED_ADDR},   /**< Qu-CurveB-U4 */ 
/**021, 019; Line_601*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioQ4_B, 0U, 996U, 1U, 884U,UNUSED_ADDR},   /**< Qu-CurveB-Q4 */ 
/**021, 020; Line_602*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftHysVolt, 0U, 1000U, 1U, 888U,UNUSED_ADDR},   /**< Qu-滞环 */ 
/**021, 021; Line_603*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioPwrIn, 0U, 1004U, 1U, 892U,UNUSED_ADDR},   /**< Qu-Pin */ 
/**021, 022; Line_604*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRatioPwrOut, 0U, 1008U, 1U, 896U,UNUSED_ADDR},   /**< Qu-Pout */ 
/**021, 023; Line_605*/  { 0x482U, (void *)&stComTbl.stPrmReactvQu.uiRsvd2, 0U, 1012U, 1U, 900U,UNUSED_ADDR},   /**< Qu-整型预留2 */ 
/**021, 024; Line_606*/  { 0x482U, (void *)&stComTbl.stPrmReactvQu.uiRsvd1, 0U, 1014U, 1U, 902U,UNUSED_ADDR},   /**< Qu-整型预留1 */ 
/**021, 025; Line_607*/  { 0x482U, (void *)&stComTbl.stPrmReactvQu.uiRsvd0, 0U, 1016U, 1U, 904U,UNUSED_ADDR},   /**< Qu-整型预留0 */ 
/**021, 026; Line_608*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftCoeffVref, 0U, 1018U, 1U, 906U,UNUSED_ADDR},   /**< Qu-Vref系数 */ 
/**021, 027; Line_609*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftTiVref, 0U, 1022U, 1U, 910U,UNUSED_ADDR},   /**< Qu-Vref时间常数 */ 
/**021, 028; Line_610*/  { 0x542U, (void *)&stComTbl.stPrmReactvQu.ftRsvd0, 0U, 1026U, 1U, 914U,UNUSED_ADDR},   /**< Qu-浮点型预留0 */ 
/** GROUP_22-22无功QP参数  */
/**022, 001; Line_611*/  { 0x482U, (void *)&stComTbl.stPrmReactvQp.uiCurve, 0U, 1030U, 1U, 918U,UNUSED_ADDR},   /**< Qp曲线选择 */ 
/**022, 002; Line_612*/  { 0x482U, (void *)&stComTbl.stPrmReactvQp.uiModeResp, 0U, 1032U, 1U, 920U,UNUSED_ADDR},   /**< Qp模式 */ 
/**022, 003; Line_613*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP1_PF, 0U, 1034U, 1U, 922U,UNUSED_ADDR},   /**< Qp-P1_PF */ 
/**022, 004; Line_614*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP2_PF, 0U, 1038U, 1U, 926U,UNUSED_ADDR},   /**< Qp-P2_PF */ 
/**022, 005; Line_615*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP3_PF, 0U, 1042U, 1U, 930U,UNUSED_ADDR},   /**< Qp-P3_PF */ 
/**022, 006; Line_616*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP4_PF, 0U, 1046U, 1U, 934U,UNUSED_ADDR},   /**< Qp-P4_PF */ 
/**022, 007; Line_617*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioPF1, 0U, 1050U, 1U, 938U,UNUSED_ADDR},   /**< Qp-PF1 */ 
/**022, 008; Line_618*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioPF2, 0U, 1054U, 1U, 942U,UNUSED_ADDR},   /**< Qp-PF2 */ 
/**022, 009; Line_619*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioPF3, 0U, 1058U, 1U, 946U,UNUSED_ADDR},   /**< Qp-PF3 */ 
/**022, 010; Line_620*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioPF4, 0U, 1062U, 1U, 950U,UNUSED_ADDR},   /**< Qp-PF4 */ 
/**022, 011; Line_621*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP1_Q, 0U, 1066U, 1U, 954U,UNUSED_ADDR},   /**< Qp-P1_Q */ 
/**022, 012; Line_622*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP2_Q, 0U, 1070U, 1U, 958U,UNUSED_ADDR},   /**< Qp-P2_Q */ 
/**022, 013; Line_623*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP3_Q, 0U, 1074U, 1U, 962U,UNUSED_ADDR},   /**< Qp-P3_Q */ 
/**022, 014; Line_624*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP4_Q, 0U, 1078U, 1U, 966U,UNUSED_ADDR},   /**< Qp-P4_Q */ 
/**022, 015; Line_625*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP5_Q, 0U, 1082U, 1U, 970U,UNUSED_ADDR},   /**< Qp-P5_Q */ 
/**022, 016; Line_626*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioP6_Q, 0U, 1086U, 1U, 974U,UNUSED_ADDR},   /**< Qp-P6_Q */ 
/**022, 017; Line_627*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ1, 0U, 1090U, 1U, 978U,UNUSED_ADDR},   /**< Qp-Q1 */ 
/**022, 018; Line_628*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ2, 0U, 1094U, 1U, 982U,UNUSED_ADDR},   /**< Qp-Q2 */ 
/**022, 019; Line_629*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ3, 0U, 1098U, 1U, 986U,UNUSED_ADDR},   /**< Qp-Q3 */ 
/**022, 020; Line_630*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ4, 0U, 1102U, 1U, 990U,UNUSED_ADDR},   /**< Qp-Q4 */ 
/**022, 021; Line_631*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ5, 0U, 1106U, 1U, 994U,UNUSED_ADDR},   /**< Qp-Q5 */ 
/**022, 022; Line_632*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioQ6, 0U, 1110U, 1U, 998U,UNUSED_ADDR},   /**< Qp-Q6 */ 
/**022, 023; Line_633*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioVoltIn, 0U, 1114U, 1U, 1002U,UNUSED_ADDR},   /**< Qp-Uin */ 
/**022, 024; Line_634*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRatioVoltOut, 0U, 1118U, 1U, 1006U,UNUSED_ADDR},   /**< Qp-Uout */ 
/**022, 025; Line_635*/  { 0x482U, (void *)&stComTbl.stPrmReactvQp.uiRsvd1, 0U, 1122U, 1U, 1010U,UNUSED_ADDR},   /**< Qp-整型预留1 */ 
/**022, 026; Line_636*/  { 0x482U, (void *)&stComTbl.stPrmReactvQp.uiRsvd0, 0U, 1124U, 1U, 1012U,UNUSED_ADDR},   /**< Qp-整型预留0 */ 
/**022, 027; Line_637*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRsvd1, 0U, 1126U, 1U, 1014U,UNUSED_ADDR},   /**< Qp-浮点型预留1 */ 
/**022, 028; Line_638*/  { 0x542U, (void *)&stComTbl.stPrmReactvQp.ftRsvd0, 0U, 1130U, 1U, 1018U,UNUSED_ADDR},   /**< Qp-浮点型预留0 */ 
/** GROUP_23-23高穿参数  */
/**023, 001; Line_639*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiEna, 0U, 1134U, 1U, 1022U,UNUSED_ADDR},   /**< HVRT-开关 */ 
/**023, 002; Line_640*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiModePwr, 0U, 1136U, 1U, 1024U,UNUSED_ADDR},   /**< HVRT-功率模式 */ 
/**023, 003; Line_641*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiEnaZeroPwr, 0U, 1138U, 1U, 1026U,UNUSED_ADDR},   /**< HVRT-零功率模式 */ 
/**023, 004; Line_642*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiEnaIqLim, 0U, 1140U, 1U, 1028U,UNUSED_ADDR},   /**< HVRT-无功电流限制开关 */ 
/**023, 005; Line_643*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftVolt1, 0U, 1142U, 1U, 1030U,UNUSED_ADDR},   /**< HVRT-V1 */ 
/**023, 006; Line_644*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftVolt2, 0U, 1146U, 1U, 1034U,UNUSED_ADDR},   /**< HVRT-V2 */ 
/**023, 007; Line_645*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftVolt3, 0U, 1150U, 1U, 1038U,UNUSED_ADDR},   /**< HVRT-V3 */ 
/**023, 008; Line_646*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftTi1, 0U, 1154U, 1000U, 1042U,UNUSED_ADDR},   /**< HVRT-T1 */ 
/**023, 009; Line_647*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftTi2, 0U, 1158U, 1000U, 1046U,UNUSED_ADDR},   /**< HVRT-T2 */ 
/**023, 010; Line_648*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftTi3, 0U, 1162U, 1000U, 1050U,UNUSED_ADDR},   /**< HVRT-T3 */ 
/**023, 011; Line_649*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftRatioZeroPwrVolt, 0U, 1166U, 1U, 1054U,UNUSED_ADDR},   /**< HVRT-零功率触发电压 */ 
/**023, 012; Line_650*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftValIqLim, 0U, 1170U, 1U, 1058U,UNUSED_ADDR},   /**< HVRT-无功电流限制值 */ 
/**023, 013; Line_651*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftCoeffIq, 0U, 1174U, 1U, 1062U,UNUSED_ADDR},   /**< HVRT-kf因子 */ 
/**023, 014; Line_652*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiRsvd1, 0U, 1178U, 1U, 1066U,UNUSED_ADDR},   /**< HVRT-整型预留1 */ 
/**023, 015; Line_653*/  { 0x482U, (void *)&stComTbl.stPrmHvrt.uiRsvd0, 0U, 1180U, 1U, 1068U,UNUSED_ADDR},   /**< HVRT-整型预留0 */ 
/**023, 016; Line_654*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftRsvd1, 0U, 1182U, 1U, 1070U,UNUSED_ADDR},   /**< HVRT-浮点型预留1 */ 
/**023, 017; Line_655*/  { 0x542U, (void *)&stComTbl.stPrmHvrt.ftRsvd0, 0U, 1186U, 1U, 1074U,UNUSED_ADDR},   /**< HVRT-浮点型预留0 */ 
/** GROUP_24-24低穿参数  */
/**024, 001; Line_656*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiEna, 0U, 1190U, 1U, 1078U,UNUSED_ADDR},   /**< LVRT-开关 */ 
/**024, 002; Line_657*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiModePwr, 0U, 1192U, 1U, 1080U,UNUSED_ADDR},   /**< LVRT-功率模式 */ 
/**024, 003; Line_658*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiEnaZeroPwr, 0U, 1194U, 1U, 1082U,UNUSED_ADDR},   /**< LVRT-零功率模式 */ 
/**024, 004; Line_659*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiEnaIqLim, 0U, 1196U, 1U, 1084U,UNUSED_ADDR},   /**< LVRT-无功电流限制开关 */ 
/**024, 005; Line_660*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftVolt1, 0U, 1198U, 1U, 1086U,UNUSED_ADDR},   /**< LVRT-V1 */ 
/**024, 006; Line_661*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftVolt2, 0U, 1202U, 1U, 1090U,UNUSED_ADDR},   /**< LVRT-V2 */ 
/**024, 007; Line_662*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftVolt3, 0U, 1206U, 1U, 1094U,UNUSED_ADDR},   /**< LVRT-V3 */ 
/**024, 008; Line_663*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftTi1, 0U, 1210U, 1000U, 1098U,UNUSED_ADDR},   /**< LVRT-T1 */ 
/**024, 009; Line_664*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftTi2, 0U, 1214U, 1000U, 1102U,UNUSED_ADDR},   /**< LVRT-T2 */ 
/**024, 010; Line_665*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftTi3, 0U, 1218U, 1000U, 1106U,UNUSED_ADDR},   /**< LVRT-T3 */ 
/**024, 011; Line_666*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftRatioZeroPwrVolt, 0U, 1222U, 1U, 1110U,UNUSED_ADDR},   /**< LVRT-零功率触发电压 */ 
/**024, 012; Line_667*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftValIqLim, 0U, 1226U, 1U, 1114U,UNUSED_ADDR},   /**< LVRT-无功电流限制值 */ 
/**024, 013; Line_668*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftCoeffIq, 0U, 1230U, 1U, 1118U,UNUSED_ADDR},   /**< LVRT-kf因子 */ 
/**024, 014; Line_669*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiRsvd1, 0U, 1234U, 1U, 1122U,UNUSED_ADDR},   /**< LVRT-整型预留1 */ 
/**024, 015; Line_670*/  { 0x482U, (void *)&stComTbl.stPrmLvrt.uiRsvd0, 0U, 1236U, 1U, 1124U,UNUSED_ADDR},   /**< LVRT-整型预留0 */ 
/**024, 016; Line_671*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftRsvd1, 0U, 1238U, 1U, 1126U,UNUSED_ADDR},   /**< LVRT-浮点型预留1 */ 
/**024, 017; Line_672*/  { 0x542U, (void *)&stComTbl.stPrmLvrt.ftRsvd0, 0U, 1242U, 1U, 1130U,UNUSED_ADDR},   /**< LVRT-浮点型预留0 */ 
/** GROUP_25-25电网PU功能参数  */
/**025, 001; Line_673*/  { 0x482U, (void *)&stComTbl.stPrmPu.uiEna, 0U, 1246U, 1U, 1134U,UNUSED_ADDR},   /**< PU开关 */ 
/**025, 002; Line_674*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftVolt1, 0U, 1248U, 1U, 1136U,UNUSED_ADDR},   /**< PU降额电压1 */ 
/**025, 003; Line_675*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftVolt2, 0U, 1252U, 1U, 1140U,UNUSED_ADDR},   /**< PU降额电压2 */ 
/**025, 004; Line_676*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftVolt3, 0U, 1256U, 1U, 1144U,UNUSED_ADDR},   /**< PU降额电压3 */ 
/**025, 005; Line_677*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftVolt4, 0U, 1260U, 1U, 1148U,UNUSED_ADDR},   /**< PU降额电压4 */ 
/**025, 006; Line_678*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftPwr1, 0U, 1264U, 1U, 1152U,UNUSED_ADDR},   /**< PU降额功率1 */ 
/**025, 007; Line_679*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftPwr2, 0U, 1268U, 1U, 1156U,UNUSED_ADDR},   /**< PU降额功率2 */ 
/**025, 008; Line_680*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftPwr3, 0U, 1272U, 1U, 1160U,UNUSED_ADDR},   /**< PU降额功率3 */ 
/**025, 009; Line_681*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftPwr4, 0U, 1276U, 1U, 1164U,UNUSED_ADDR},   /**< PU降额功率4 */ 
/**025, 010; Line_682*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftTiResp, 0U, 1280U, 100U, 1168U,UNUSED_ADDR},   /**< PU降额时间 */ 
/**025, 011; Line_683*/  { 0x482U, (void *)&stComTbl.stPrmPu.uiCurve, 0U, 1284U, 1U, 1172U,UNUSED_ADDR},   /**< PU曲线选择 */ 
/**025, 012; Line_684*/  { 0x482U, (void *)&stComTbl.stPrmPu.uiRsvd1, 0U, 1286U, 1U, 1174U,UNUSED_ADDR},   /**< PU整型预留1 */ 
/**025, 013; Line_685*/  { 0x482U, (void *)&stComTbl.stPrmPu.uiRsvd0, 0U, 1288U, 1U, 1176U,UNUSED_ADDR},   /**< PU整型预留0 */ 
/**025, 014; Line_686*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftRsvd1, 0U, 1290U, 1U, 1178U,UNUSED_ADDR},   /**< PU浮点型预留1 */ 
/**025, 015; Line_687*/  { 0x542U, (void *)&stComTbl.stPrmPu.ftRsvd0, 0U, 1294U, 1U, 1182U,UNUSED_ADDR}  /**< PU浮点型预留0 */ 
}; 
const Uint16 Group0Index[GROUP_0_NUM + 1U] = {0xFFFFU}; 
/**01版本信息*/
const Uint16 Group1Index[GROUP_1_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 
/** Line_002 */ 10U, 11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 
/** Line_003 */ 20U, 21U, 22U, 23U, 24U, 
}; 

/**02整机控制*/
const Uint16 Group2Index[GROUP_2_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 
/** Line_002 */ 34U, 35U, 36U, 37U, 38U, 39U, 40U, 41U, 42U, 43U, 
/** Line_003 */ 44U, 45U, 46U, 47U, 48U, 49U, 50U, 51U, 52U, 53U, 
/** Line_004 */ 54U, 55U, 56U, 57U, 58U, 59U, 60U, 61U, 62U, 63U, 
/** Line_005 */ 64U, 
}; 

/**03D2D数据监视*/
const Uint16 Group3Index[GROUP_3_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 65U, 66U, 67U, 68U, 69U, 70U, 71U, 72U, 73U, 
/** Line_002 */ 74U, 75U, 76U, 77U, 78U, 79U, 80U, 81U, 82U, 83U, 
/** Line_003 */ 84U, 85U, 86U, 87U, 88U, 89U, 90U, 91U, 92U, 93U, 
/** Line_004 */ 94U, 95U, 96U, 97U, 98U, 99U, 100U, 101U, 102U, 103U, 
/** Line_005 */ 104U, 105U, 106U, 107U, 108U, 109U, 110U, 111U, 
}; 

/**04PFC数据监视*/
const Uint16 Group4Index[GROUP_4_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 112U, 113U, 114U, 115U, 116U, 117U, 118U, 119U, 120U, 
/** Line_002 */ 121U, 122U, 123U, 124U, 125U, 126U, 127U, 128U, 129U, 130U, 
/** Line_003 */ 131U, 132U, 133U, 134U, 135U, 136U, 137U, 138U, 139U, 140U, 
/** Line_004 */ 141U, 142U, 143U, 144U, 145U, 
}; 

/**05AD校准*/
const Uint16 Group5Index[GROUP_5_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 146U, 147U, 148U, 149U, 150U, 151U, 152U, 153U, 154U, 
/** Line_002 */ 155U, 156U, 157U, 158U, 159U, 160U, 161U, 162U, 163U, 164U, 
/** Line_003 */ 165U, 166U, 167U, 168U, 169U, 170U, 171U, 172U, 173U, 174U, 
/** Line_004 */ 175U, 176U, 177U, 178U, 179U, 180U, 181U, 182U, 183U, 184U, 
/** Line_005 */ 185U, 186U, 187U, 188U, 
}; 

/**06PFC系统参数*/
const Uint16 Group6Index[GROUP_6_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 189U, 190U, 191U, 192U, 193U, 194U, 195U, 196U, 197U, 
/** Line_002 */ 198U, 199U, 200U, 201U, 202U, 203U, 204U, 205U, 206U, 207U, 
/** Line_003 */ 208U, 209U, 210U, 211U, 212U, 
}; 

/**07故障字*/
const Uint16 Group7Index[GROUP_7_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 213U, 214U, 215U, 216U, 217U, 218U, 219U, 220U, 221U, 
/** Line_002 */ 222U, 223U, 224U, 225U, 226U, 227U, 228U, 229U, 230U, 231U, 
/** Line_003 */ 232U, 233U, 234U, 235U, 236U, 237U, 238U, 239U, 240U, 241U, 
/** Line_004 */ 242U, 243U, 244U, 245U, 246U, 247U, 248U, 249U, 
}; 

/**08故障屏蔽字*/
const Uint16 Group8Index[GROUP_8_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 250U, 251U, 252U, 253U, 254U, 
}; 

/**09故障门限*/
const Uint16 Group9Index[GROUP_9_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 255U, 256U, 257U, 258U, 259U, 260U, 261U, 262U, 263U, 
/** Line_002 */ 264U, 265U, 266U, 267U, 268U, 269U, 270U, 271U, 272U, 
}; 

/**10采样过程*/
const Uint16 Group10Index[GROUP_10_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 273U, 274U, 275U, 276U, 277U, 278U, 279U, 280U, 281U, 
/** Line_002 */ 282U, 283U, 284U, 285U, 286U, 287U, 288U, 289U, 290U, 291U, 
/** Line_003 */ 292U, 293U, 294U, 295U, 296U, 297U, 298U, 299U, 300U, 301U, 
/** Line_004 */ 302U, 303U, 304U, 305U, 306U, 307U, 308U, 309U, 310U, 311U, 
/** Line_005 */ 312U, 313U, 314U, 315U, 316U, 317U, 318U, 319U, 320U, 321U, 
/** Line_006 */ 322U, 323U, 324U, 325U, 326U, 327U, 328U, 329U, 330U, 331U, 
/** Line_007 */ 332U, 333U, 334U, 335U, 336U, 337U, 
}; 

/**11PFC逻辑参数*/
const Uint16 Group11Index[GROUP_11_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 338U, 339U, 340U, 341U, 342U, 343U, 344U, 345U, 346U, 
/** Line_002 */ 347U, 348U, 349U, 350U, 351U, 352U, 353U, 354U, 355U, 356U, 
/** Line_003 */ 357U, 358U, 359U, 360U, 361U, 362U, 363U, 364U, 365U, 366U, 
/** Line_004 */ 367U, 368U, 369U, 370U, 371U, 372U, 373U, 374U, 
}; 

/**12D2D控制参数*/
const Uint16 Group12Index[GROUP_12_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 375U, 376U, 377U, 378U, 379U, 380U, 381U, 382U, 383U, 
/** Line_002 */ 384U, 385U, 386U, 387U, 388U, 389U, 390U, 
}; 

/**13调试参数*/
const Uint16 Group13Index[GROUP_13_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 391U, 392U, 393U, 394U, 395U, 396U, 397U, 398U, 399U, 
/** Line_002 */ 400U, 401U, 402U, 403U, 404U, 405U, 406U, 407U, 408U, 409U, 
/** Line_003 */ 410U, 411U, 412U, 
}; 

/**14PFC控制参数1*/
const Uint16 Group14Index[GROUP_14_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 413U, 414U, 415U, 416U, 417U, 418U, 419U, 420U, 421U, 
/** Line_002 */ 422U, 423U, 424U, 425U, 426U, 427U, 428U, 429U, 430U, 431U, 
/** Line_003 */ 432U, 433U, 
}; 

/**15PFC控制参数2*/
const Uint16 Group15Index[GROUP_15_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 434U, 435U, 436U, 437U, 438U, 439U, 440U, 441U, 442U, 
/** Line_002 */ 443U, 444U, 445U, 
}; 

/**16网侧参数*/
const Uint16 Group16Index[GROUP_16_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 446U, 447U, 448U, 449U, 450U, 451U, 452U, 453U, 454U, 
/** Line_002 */ 455U, 456U, 457U, 458U, 
}; 

/**17电网额定参数*/
const Uint16 Group17Index[GROUP_17_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 459U, 460U, 461U, 462U, 463U, 464U, 465U, 466U, 467U, 
/** Line_002 */ 468U, 
}; 

/**18V2G功率控制*/
const Uint16 Group18Index[GROUP_18_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 469U, 470U, 471U, 472U, 473U, 474U, 475U, 476U, 477U, 
/** Line_002 */ 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U, 
/** Line_003 */ 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 
}; 

/**19电网保护参数*/
const Uint16 Group19Index[GROUP_19_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 497U, 498U, 499U, 500U, 501U, 502U, 503U, 504U, 505U, 
/** Line_002 */ 506U, 507U, 508U, 509U, 510U, 511U, 512U, 513U, 514U, 515U, 
/** Line_003 */ 516U, 517U, 518U, 519U, 520U, 521U, 522U, 523U, 524U, 525U, 
/** Line_004 */ 526U, 527U, 528U, 529U, 530U, 531U, 532U, 533U, 534U, 535U, 
/** Line_005 */ 536U, 537U, 538U, 539U, 540U, 541U, 542U, 543U, 544U, 545U, 
}; 

/**20频率响应参数*/
const Uint16 Group20Index[GROUP_20_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 546U, 547U, 548U, 549U, 550U, 551U, 552U, 553U, 554U, 
/** Line_002 */ 555U, 556U, 557U, 558U, 559U, 560U, 561U, 562U, 563U, 564U, 
/** Line_003 */ 565U, 566U, 567U, 568U, 569U, 570U, 571U, 572U, 573U, 574U, 
/** Line_004 */ 575U, 576U, 577U, 578U, 579U, 580U, 581U, 582U, 
}; 

/**21无功QU参数*/
const Uint16 Group21Index[GROUP_21_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 583U, 584U, 585U, 586U, 587U, 588U, 589U, 590U, 591U, 
/** Line_002 */ 592U, 593U, 594U, 595U, 596U, 597U, 598U, 599U, 600U, 601U, 
/** Line_003 */ 602U, 603U, 604U, 605U, 606U, 607U, 608U, 609U, 610U, 
}; 

/**22无功QP参数*/
const Uint16 Group22Index[GROUP_22_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 611U, 612U, 613U, 614U, 615U, 616U, 617U, 618U, 619U, 
/** Line_002 */ 620U, 621U, 622U, 623U, 624U, 625U, 626U, 627U, 628U, 629U, 
/** Line_003 */ 630U, 631U, 632U, 633U, 634U, 635U, 636U, 637U, 638U, 
}; 

/**23高穿参数*/
const Uint16 Group23Index[GROUP_23_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 639U, 640U, 641U, 642U, 643U, 644U, 645U, 646U, 647U, 
/** Line_002 */ 648U, 649U, 650U, 651U, 652U, 653U, 654U, 655U, 
}; 

/**24低穿参数*/
const Uint16 Group24Index[GROUP_24_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 656U, 657U, 658U, 659U, 660U, 661U, 662U, 663U, 664U, 
/** Line_002 */ 665U, 666U, 667U, 668U, 669U, 670U, 671U, 672U, 
}; 

/**25电网PU功能参数*/
const Uint16 Group25Index[GROUP_25_NUM + 1U] = 
{ 
/** Line_001 */ 0xFFFFU, 673U, 674U, 675U, 676U, 677U, 678U, 679U, 680U, 681U, 
/** Line_002 */ 682U, 683U, 684U, 685U, 686U, 687U, 
}; 

const DSP_GROUP_TYPE sGroup [GROUP_NUM + 1U]=
{ 
    {(void*)Group0Index, 0U}, 
    {(void*)Group1Index, 24U}, 
    {(void*)Group2Index, 40U}, 
    {(void*)Group3Index, 47U}, 
    {(void*)Group4Index, 34U}, 
    {(void*)Group5Index, 43U}, 
    {(void*)Group6Index, 24U}, 
    {(void*)Group7Index, 37U}, 
    {(void*)Group8Index, 5U}, 
    {(void*)Group9Index, 18U}, 
    {(void*)Group10Index, 65U}, 
    {(void*)Group11Index, 37U}, 
    {(void*)Group12Index, 16U}, 
    {(void*)Group13Index, 22U}, 
    {(void*)Group14Index, 21U}, 
    {(void*)Group15Index, 12U}, 
    {(void*)Group16Index, 13U}, 
    {(void*)Group17Index, 10U}, 
    {(void*)Group18Index, 28U}, 
    {(void*)Group19Index, 49U}, 
    {(void*)Group20Index, 37U}, 
    {(void*)Group21Index, 28U}, 
    {(void*)Group22Index, 28U}, 
    {(void*)Group23Index, 17U}, 
    {(void*)Group24Index, 17U}, 
    {(void*)Group25Index, 15U}, 
}; 

const Uint16 SaveEEPromIndex[SAVE_EEPROM_NUM]= 
{ 
/** Line_001 */ 53U, 146U, 151U, 152U, 153U, 154U, 155U, 156U, 157U, 158U, 
/** Line_002 */ 160U, 161U, 162U, 163U, 164U, 165U, 166U, 167U, 168U, 169U, 
/** Line_003 */ 170U, 171U, 172U, 173U, 174U, 175U, 176U, 177U, 178U, 179U, 
/** Line_004 */ 180U, 181U, 182U, 183U, 184U, 185U, 186U, 187U, 188U, 189U, 
/** Line_005 */ 190U, 191U, 192U, 193U, 194U, 250U, 251U, 252U, 253U, 254U, 
/** Line_006 */ 255U, 256U, 257U, 258U, 259U, 260U, 261U, 262U, 263U, 264U, 
/** Line_007 */ 265U, 266U, 267U, 268U, 270U, 271U, 272U, 338U, 339U, 340U, 
/** Line_008 */ 344U, 345U, 346U, 347U, 348U, 349U, 376U, 377U, 378U, 379U, 
/** Line_009 */ 380U, 413U, 414U, 415U, 416U, 417U, 418U, 419U, 420U, 421U, 
/** Line_010 */ 422U, 423U, 424U, 425U, 426U, 427U, 428U, 429U, 430U, 431U, 
/** Line_011 */ 432U, 433U, 434U, 435U, 436U, 437U, 438U, 439U, 440U, 441U, 
/** Line_012 */ 442U, 443U, 444U, 445U, 446U, 447U, 448U, 452U, 453U, 454U, 
/** Line_013 */ 455U, 459U, 460U, 461U, 462U, 463U, 464U, 465U, 466U, 467U, 
/** Line_014 */ 468U, 469U, 470U, 471U, 472U, 473U, 474U, 475U, 476U, 477U, 
/** Line_015 */ 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U, 
/** Line_016 */ 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 
/** Line_017 */ 498U, 499U, 500U, 501U, 502U, 503U, 504U, 505U, 506U, 507U, 
/** Line_018 */ 508U, 509U, 510U, 511U, 512U, 513U, 514U, 515U, 516U, 517U, 
/** Line_019 */ 518U, 519U, 520U, 521U, 522U, 523U, 524U, 525U, 526U, 527U, 
/** Line_020 */ 528U, 529U, 530U, 531U, 532U, 533U, 534U, 535U, 536U, 537U, 
/** Line_021 */ 538U, 539U, 540U, 541U, 542U, 543U, 544U, 545U, 546U, 547U, 
/** Line_022 */ 548U, 549U, 550U, 551U, 552U, 553U, 554U, 555U, 556U, 557U, 
/** Line_023 */ 558U, 559U, 560U, 561U, 562U, 563U, 564U, 565U, 566U, 567U, 
/** Line_024 */ 568U, 569U, 570U, 571U, 572U, 573U, 574U, 575U, 576U, 577U, 
/** Line_025 */ 578U, 579U, 580U, 581U, 582U, 583U, 584U, 585U, 586U, 587U, 
/** Line_026 */ 588U, 589U, 590U, 591U, 592U, 593U, 594U, 595U, 596U, 597U, 
/** Line_027 */ 598U, 599U, 600U, 601U, 602U, 603U, 604U, 605U, 606U, 607U, 
/** Line_028 */ 608U, 609U, 610U, 611U, 612U, 613U, 614U, 615U, 616U, 617U, 
/** Line_029 */ 618U, 619U, 620U, 621U, 622U, 623U, 624U, 625U, 626U, 627U, 
/** Line_030 */ 628U, 629U, 630U, 631U, 632U, 633U, 634U, 635U, 636U, 637U, 
/** Line_031 */ 638U, 639U, 640U, 641U, 642U, 643U, 644U, 645U, 646U, 647U, 
/** Line_032 */ 648U, 649U, 650U, 651U, 652U, 653U, 654U, 655U, 656U, 657U, 
/** Line_033 */ 658U, 659U, 660U, 661U, 662U, 663U, 664U, 665U, 666U, 667U, 
/** Line_034 */ 668U, 669U, 670U, 671U, 672U, 673U, 674U, 675U, 676U, 677U, 
/** Line_035 */ 678U, 679U, 680U, 681U, 682U, 683U, 684U, 685U, 686U, 687U, 
}; 

const Uint16 MasterNonEraseEEPromIndex [MASTER_NONERASE_SAVE_NUM]= 
{ 
/** Line_001 */ 146U, 151U, 152U, 153U, 154U, 155U, 156U, 157U, 158U, 160U, 
/** Line_002 */ 161U, 162U, 163U, 164U, 165U, 166U, 167U, 168U, 169U, 170U, 
/** Line_003 */ 171U, 172U, 173U, 174U, 175U, 176U, 177U, 178U, 179U, 180U, 
/** Line_004 */ 181U, 182U, 183U, 184U, 185U, 186U, 187U, 188U, 
}; 

const Uint16 MasterSaveEEPromIndex[MASTER_SAVE_NUM]= 
{ 
/** Line_001 */ 53U, 189U, 190U, 191U, 192U, 193U, 194U, 250U, 251U, 252U, 
/** Line_002 */ 253U, 254U, 255U, 256U, 257U, 258U, 259U, 260U, 261U, 262U, 
/** Line_003 */ 263U, 264U, 265U, 266U, 267U, 268U, 270U, 271U, 272U, 338U, 
/** Line_004 */ 339U, 340U, 344U, 345U, 346U, 347U, 348U, 349U, 376U, 377U, 
/** Line_005 */ 378U, 379U, 380U, 413U, 414U, 415U, 416U, 417U, 418U, 419U, 
/** Line_006 */ 420U, 421U, 422U, 423U, 424U, 425U, 426U, 427U, 428U, 429U, 
/** Line_007 */ 430U, 431U, 432U, 433U, 434U, 435U, 436U, 437U, 438U, 439U, 
/** Line_008 */ 440U, 441U, 442U, 443U, 444U, 445U, 446U, 447U, 448U, 452U, 
/** Line_009 */ 453U, 454U, 455U, 459U, 460U, 461U, 462U, 463U, 464U, 465U, 
/** Line_010 */ 466U, 467U, 468U, 469U, 470U, 471U, 472U, 473U, 474U, 475U, 
/** Line_011 */ 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 
/** Line_012 */ 486U, 487U, 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 
/** Line_013 */ 496U, 497U, 498U, 499U, 500U, 501U, 502U, 503U, 504U, 505U, 
/** Line_014 */ 506U, 507U, 508U, 509U, 510U, 511U, 512U, 513U, 514U, 515U, 
/** Line_015 */ 516U, 517U, 518U, 519U, 520U, 521U, 522U, 523U, 524U, 525U, 
/** Line_016 */ 526U, 527U, 528U, 529U, 530U, 531U, 532U, 533U, 534U, 535U, 
/** Line_017 */ 536U, 537U, 538U, 539U, 540U, 541U, 542U, 543U, 544U, 545U, 
/** Line_018 */ 546U, 547U, 548U, 549U, 550U, 551U, 552U, 553U, 554U, 555U, 
/** Line_019 */ 556U, 557U, 558U, 559U, 560U, 561U, 562U, 563U, 564U, 565U, 
/** Line_020 */ 566U, 567U, 568U, 569U, 570U, 571U, 572U, 573U, 574U, 575U, 
/** Line_021 */ 576U, 577U, 578U, 579U, 580U, 581U, 582U, 583U, 584U, 585U, 
/** Line_022 */ 586U, 587U, 588U, 589U, 590U, 591U, 592U, 593U, 594U, 595U, 
/** Line_023 */ 596U, 597U, 598U, 599U, 600U, 601U, 602U, 603U, 604U, 605U, 
/** Line_024 */ 606U, 607U, 608U, 609U, 610U, 611U, 612U, 613U, 614U, 615U, 
/** Line_025 */ 616U, 617U, 618U, 619U, 620U, 621U, 622U, 623U, 624U, 625U, 
/** Line_026 */ 626U, 627U, 628U, 629U, 630U, 631U, 632U, 633U, 634U, 635U, 
/** Line_027 */ 636U, 637U, 638U, 639U, 640U, 641U, 642U, 643U, 644U, 645U, 
/** Line_028 */ 646U, 647U, 648U, 649U, 650U, 651U, 652U, 653U, 654U, 655U, 
/** Line_029 */ 656U, 657U, 658U, 659U, 660U, 661U, 662U, 663U, 664U, 665U, 
/** Line_030 */ 666U, 667U, 668U, 669U, 670U, 671U, 672U, 673U, 674U, 675U, 
/** Line_031 */ 676U, 677U, 678U, 679U, 680U, 681U, 682U, 683U, 684U, 685U, 
/** Line_032 */ 686U, 687U, 
}; 

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================

