/**
* @file  User_ISR.c
* @brief			 interrupt service
* @details	   interrupt service function (PWM_zero_isr), interrupt service function (PWM_tripZone_isr)
* @author	   xcc
* @date 			 2022-03-25
* @version	   V1.0
* @copyright	 (c) Copyright 2010-2040, WANBANG Digital Energy Co. LTD
*				            All Rights Reserved
*******************************************************************************
***
* @attention
* 硬件平台:DSP28377D \n
* Environment:  CCS v10.4
* Compiler : TI21.6
* @par 修改日志:
* <table>
* <tr><th>Date         <th>Version        <th>Author        <th>Description
* <tr><td>2022/11/21   <td>1.0            <td>xcc          <td>创建初始版本
* </table>
*
*******************************************************************************
***
*/




	
#ifndef _PWM_ISR_H_
#define _PWM_ISR_H_

/*
*******************************************************************************
**************************
*                              Pre-defines
*******************************************************************************
**************************
*/


#if defined(CTRL_ISR_FOR_GLOBAL)
#define  CTRL_ISR_EXT
#else
#define  CTRL_ISR_EXT  extern 
#endif




/*
*******************************************************************************
**************************
*                               Include files
*******************************************************************************
**************************
*/

#ifndef _SIMULATION_NO_DSP_
#include "F28x_Project.h"
//#include "Fpga.h"
//#include "GlobalDefs.h"
#endif
/*
*******************************************************************************
**************************
*                         Global macro Defines (#define)
*******************************************************************************
**************************
*/
typedef void (*CALCFUN)();
typedef void (*INITFUN)();
/** Control frequency of system operation */
#define CONTROL_FREQUENCY_SET         20000//stSysNormalValue.stHardPara.ControlFreq//12500//25000
/** Number of controls in 1 millisecond */
#define MICROSECOND_COUNT             (Uint16)((CONTROL_FREQUENCY_SET+500)/1000)
#define ISR_100MS                     (Uint16)(MICROSECOND_COUNT*100)
#define ISR_50MS                      (Uint16)(MICROSECOND_COUNT*50)
/** The sampling interval of the instantaneous value when calculating the RMS*/
#define SAMP_RATE_FOR_CALCRMS         2u
#define SAMP_SHIFT_NUM                (SAMP_RATE_FOR_CALCRMS>>1)
/** 80us System sampling time */

/** Default grid frequency*/
#define GRID_FREQ_SET                 50u

#define GRID_FREQ_MAX                 66u
#define GRID_FREQ_MIN                 39u
/** The number of storage points used to calculate the RMS  with  sliding window method */
#define RMS_NUM                     ((Uint16)(CONTROL_FREQUENCY_SET / GRID_FREQ_SET / SAMP_RATE_FOR_CALCRMS))
#define WHOLE_RMS_NUM                RMS_NUM

#define MAX_RMS_NUM                 ((Uint16)(CONTROL_FREQUENCY_SET / GRID_FREQ_MIN / SAMP_RATE_FOR_CALCRMS))
#define MIN_RMS_NUM                 ((Uint16)(CONTROL_FREQUENCY_SET / GRID_FREQ_MAX / SAMP_RATE_FOR_CALCRMS))

#define RMS_NUM_INV                 (Uint16)(4096 * 4 / RMS_NUM)
#define DECOMPOSITION_TIME_NUM_INV  (Uint16)(4097 * 4 / WHOLE_RMS_NUM)

#define PLL_GAIN_CONST           200

/** state machine of Calibrate AD zero drift  */
#define AD_ADJUST_OVER              0
#define MANUAL_AUTO_ADJUST_CMD      1
#define VG_ADJUST_CMD               2
#define DCBUS_ADJUST_CMD            3


#define SAMPLE_CYCLE_TS             ((float32)1/CONTROL_FREQUENCY_SET)//0.00008
#define CONTROL_CYCLE               SAMPLE_CYCLE_TS//  (float32)1/CONTROL_FREQUENCY_SET

/** 2 * pi*/
#define Z_WL   (float32)0.058119       /**< 0.0424115  //2*3.14*50*0.000135  impedance value for decoupling*/
       
#define PI2_TS                     (float32)(PI2 * SAMPLE_CYCLE_TS)

#define CUTOFF_LPF_AD_ZERO          5

#define CUTOFF_LPF_CONTROL          11

#define CUTOFF_LPF_RMSSHOW          50

#define MAIN_LOOP_TIME 1000
#define MAIN_CYCLE_TS  0.001


#define  DC_SERI_MODE      1u
#define  DC_PARALLEL_MODE  0u //parallel


#ifndef _SIMULATION_NO_DSP_ 
/**<  pi 与标准库中函XX参XX重名*/

#define PI_F32           (float32)3.1415926536
#endif


/**  PLL parameters */
//#define FREQUENCY_SET      50
#define THETA_TO_FFEQ       ((float32)CONTROL_FREQUENCY_SET / PI2)
#define DELTA_THETA_STEP    ((float32)GRID_FREQ_SET * PI2 / CONTROL_FREQUENCY_SET)

#define INVERSE_FREQ_QUENUM  2u

#define FREQ_QUE_NUM       (1u<<INVERSE_FREQ_QUENUM)//4u//10 

#define PWM_WAIT_RESTART  0

#define PWM_RESTARTING    1

#define PI_PARA_NUM  8

#define CURR_PR_1_K  (float32)89.0
#define CURR_PR_2_K  (float32)1.0
#define CURR_PR_3_K  (float32)8.0
#define CURR_PR_5_K  (float32)6.0
#define CURR_PR_7_K  (float32)3.0


#define DQ_PR_2_K  (float32)30.0
#define DQ_PR_4_K  (float32)17.0
#define DQ_PR_6_K  (float32)12.0
#define DQ_PR_10_K (float32)8.0

#define PI2                 6.2831853071796f
#define K_1Div2Cnst         0.5
#define K_1Div3Cnst         0.33333333333334
#define K_2Div3Cnst         0.6666666666667
#define K_1DivSqrt3         0.577350269189// 2365/*Q12*/
#define K_Sqrt3Div2Cnst     0.866025403784
#define ONE_DIV_PI2  (float32)0.15915494309189f
#define PI2_DIV_3    (float32)2.0943951023932f

#define  UpDownLimit16(iValue,UpValue,DownValue)         {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}
#define  UpDownLimit16_ISR(iValue,UpValue,DownValue)     {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}

//------------------------------------------------环路标幺参数----------------------------------------------
#define SYS_RATED_POWER               1250000.0f // 额定功率 1.25MW (与Pref对应)
#define SYS_GRID_VOLTAGE_LINE_RMS     10000.0f     // 电网线电压额定值 10kV
#define SYS_GRID_VOLTAGE_PHASE_RMS    (SYS_GRID_VOLTAGE_LINE_RMS * K_1DivSqrt3)    // 电网相电压额定值

#define BASE_Power                    (SYS_RATED_POWER)                     //功率基准值
#define BASE_Voltage_PhasePeak        (SYS_GRID_VOLTAGE_PHASE_RMS * 1.414)  //相电压峰值基准值
#define BASE_Current_Peak             (BASE_Power / (1.5f * BASE_Voltage_PhasePeak)) //电流基准值
#define BASE_Impedance                (BASE_Voltage_PhasePeak / BASE_Current_Peak) //基准阻抗
#define BASE_AngularFreq              (PI2 * 50)  //基准角频率，电网频率50

#define  MODUL_NUM_PHASE              6
/*

*******************************************************************************
**************************
*                               Global data define
*******************************************************************************
**************************
*/

typedef union
{
    int32 dword;
    struct
    {
        Uint16    lword;
        int16     hword;
    }half;
}UNLONG;

typedef struct                        
{
    int16    A_ad;       /**< A 相AD采样值*/
    int16    B_ad;       /**< B 相AD采样值*/
    int16    C_ad;       /**< C 相AD采样值*/
    
    UNLONG   unAzero;    /**< A 相AD零漂值*/
    UNLONG   unBzero;    /**< B 相AD零漂值*/
    UNLONG   unCzero;    /**< C 相AD零漂值*/
    
    union
    {
        struct
        {
            float32  A;          /**< A 相算法用瞬时值*/
            float32  B;          /**< B 相算法用瞬时值*/
            float32  C;          /**< C 相算法用瞬时值*/
        };
        float32 Iin[3];          /**< 三相电流数组*/
    };

    float32  KadA;       /**< A相AD采样斜率*/
    float32  KadB;       /**< */
    float32  KadC;       /**< */
    float32  Kscal;      /**< 标幺系XX*/
    float32  KscalShow;  /**< 显示系XX*/

    int16    AShow;      /**< A相瞬时显示值*/
    int16    BShow;      /**< */
    int16    CShow;      /**< */

    float32  D;          /**< D轴瞬时值*/
    float32  Q;          /**< */
 
    float32  Alfa;       /**< 静止两相坐标系下，alfa*/
    float32  Beta;       /**< */

    float32  D_P;          /**< D轴XX序瞬时值*/
    float32  Q_P;          /**< */
 
    //float32  Alfa_P;       /**< 静止两相坐标系下，XX序alfa*/
    //float32  Beta_P;       /**< */

    float32  D_N;          /**< D轴负序瞬时值*/
    float32  Q_N;          /**< */
 
    //float32  Alfa_N;       /**< 静止两相坐标系下，负序alfa*/
    //float32  Beta_N;       /**< */

    float32  SinTheta;   /**< 锁相环XX序输出sin*/
    float32  CosTheta;   /**< */

    int16    DeltaZeroA; /**< A相直流分量调整值*/
    int16    DeltaZeroB; /**< */
    int16    DeltaZeroC; /**< */
    //UNLONG   ModeFlt;
    
}THREE_PHASE_DATA_TYPE;



typedef struct
{
    float32  a;
    float32  b;
    float32  Input;       ///< 本次XX据输入
    float32  Input0;      ///< 上一次XX据输入
    float32  Output;      ///< 本次XX据输出
    float32  Output0;     ///< 上一次XX据输出
    float32  Omiga_Ts;    ///< 截止频率*开关周期        //
    CALCFUN  calc;
    INITFUN  init;
} LPF;

typedef LPF *LPF_handle;


typedef struct                        
{
    
    float32  Vinv;
    float32  Dr;
    float32  Qr;
    float32  Zr;
    float32  VectorAmp;
    float32  Alfa;
    float32  Beta;
    float32  Gama;
    float32  As;
    float32  Bs;
    float32  Cs;
    float32  Ns;
    float32  Vdc_Normalize;
    float32  PR_Out_D;
    float32  PR_Out_Q;
    float32  DelayTime;
    Uint16   Pwm_Prd;
    Uint16   ClearFlag;
     
}PWM_DRIVE_DATA;

typedef struct
{
    float32 f32Base_Modulate_signal[3];         //由电流环得到的三相基本调制波
    float32 f32Final_Modulate_signal[3][6][2];
    float32 f32Final_Phase_signal_ToFpga[3];
}STSSTCONTROL;

typedef struct
{
    float32 f32udc1_udc2_delta[3][6];
    float32 f32is[3];//有功电流方向
    float32 f32ur[3][6];
    float32 f32PIOut[3][6];
    float32 f32POut[3][6];
    float32 f32IOut[3][6];
    float32 f32Unit_Up_Bus_Avg_U[3][6];
    float32 f32Unit_Dn_Bus_Avg_U[3][6];
    float32 f32KpSet;
    float32 f32KiSet;
    float32 f32ErrUpLimt;
    float32 f32ErrDnLimt;
    float32 f32UpLimt;
    float32 f32DnLimt;
    float32 f32Unit_Bus_U[3][6];
    float32 f32Phase_Bus_Avg_U[3];
    float32 f32All_Bus_Avg_U;
    float32 f32All_Bus_Sum_U;
}STPI_UdcBusLP1;

typedef struct
{
    float32  Kp;          /**< 比XX系XX */
    float32  KpSet;       /**< 比XX系XX设置 */
    float32  Ki;          /**< XX分系XX  */
    float32  KiSet;       /**< XX分系XX设置  */
    float32  Kol;         /**< 抗饱和系XX  */
    float32  Reference;   /**< 参考值  */
    float32  Feedback;    /**< 反馈值  */

    float32  Err;         /**< 误差  */
    float32  ErrUpLimt;   /**< 误差上限  */
    float32  ErrDnLimt;   /**< 误差下限  */

    float32  IOut;        /**< XX分输出  */
    float32  IOutUpLimt;  /**< XX分输出上限  */
    float32  IOutDnLimt;  /**< XX分输出下限  */

    float32  PIOut;       /**< 控制器输出  */
    float32  PIOutUpLimt; /**< 控制器输出上限  */
    float32  PIOutDnLimt; /**< 控制器输出下限  */

}    PI_DATA_TYPE;

typedef struct
{
    float32  Kp;          /**< 比XX系XX */
    float32  KpSet;       /**< 比XX系XX设置 */
    float32  Ki;          /**< XX分系XX  */
    float32  KiSet;       /**< XX分系XX设置  */
    float32  SOCSum;
    float32  Reference;   /**< 参考值  */
    float32  Feedback[MODUL_NUM_PHASE];    /**< 反馈值  */

    float32  Err[MODUL_NUM_PHASE];         /**< 误差  */
    float32  ErrUpLimt;   /**< 误差上限  */
    float32  ErrDnLimt;   /**< 误差下限  */

    float32  IOut[MODUL_NUM_PHASE];        /**< XX分输出  */
    float32  IOutUpLimt;  /**< XX分输出上限  */
    float32  IOutDnLimt;  /**< XX分输出下限  */

    float32  PIOut[MODUL_NUM_PHASE];       /**< 控制器输出  */
    float32  PIOutUpLimt; /**< 控制器输出上限  */
    float32  PIOutDnLimt; /**< 控制器输出下限  */

    float32  SOCOut[3][MODUL_NUM_PHASE];
    float32  IinD;
    float32  IinQ;
    float32  IinAlfa;
    float32  IinBeta;
    float32  IinSqrtDQ;
    float32  IinCosTheta[3];

} STPI_SOCLP1;

typedef struct
{
    float32 u[3];  // Ac Input
//    float32 osg_u[3];
//    float32 osg_qu[3];
    float32 u_Q; //锁相环输入
    float32 u_D; //正序D轴电压

    float32 fo; //锁相环频率输出
    float32 fn; //
    float32 wn; //锁相环角频率初始值

    float32 Wo; //锁相环角频率输出
    float32 theta; //锁相环相位输出

    float32 delta_T; //锁相环参数
//    SOGI_1PH_COEFF osg_coeff;
    float32 PIOut; //锁相环环路输出
    float32 IOut; //锁相环积分输出
    float32 KpSet; //锁相环比例参数
    float32 KiSet; //锁相环积分参数
    float32 IOutUpLimt1; //锁相环积分限幅
    float32 IOutDnLimt1; //锁相环积分限幅
    float32 WOUpLimt; //锁相环角频率限幅
    float32 WODnLimt; //锁相环角频率限幅
    float32 sinA; //锁相环输出
    float32 sinB; //锁相环输出
    float32 sinC; //锁相环输出
    float32 cosA; //锁相环输出
    float32 cosB; //锁相环输出
    float32 cosC; //锁相环输出
    float32 costheta[3]; //三相电压相位

    Uint16  Flag_T0_period_reg_update;
}SPLL_SINGLE;

typedef struct
{
    float32  input[3];      /**< */
    float32  output[3];     /**< 建立缓冲区，用于存储历史XX据*/
    float32  max;           /**< 输出上限*/
    float32  min;           /**< 输出下限*/

    float32  a0;            /**< */
    float32  a1;            /**< */

    float32  a2;            /**< */
    float32  b0;            /**< */
    float32  b1;            /**< */
    float32  b2;            /**< */
    float32  Kp;            /**< 比XX系XX*/
    float32  Kr;            /**< 谐振系XX*/
    float32  wc;            /**< 带宽频率*/
    float32  wo;            /**< 谐振频率*/
    float32  Ts_pr;         /**< 控制周期*/
    CALCFUN  calc;          /**< Pointer to calculation function */
    INITFUN  init;          /**< Pointer to Initialization function */
} PR_TYPE;
typedef PR_TYPE *PR_handle;


typedef struct
{
    float32   alpha_u[3];   /**<   Ualpha Input*/
    float32   beta_u[3];    /**<   beta Input  */

    float32   alpha_osg_u[3];
    float32   alpha_osg_qu[3];

    float32   beta_osg_u[3];
    float32   beta_osg_qu[3];

    float32   osg_k;
    float32   osg_x;
    float32   osg_y;
    float32   osg_b0;
    float32   osg_b2;
    float32   osg_a1;
    float32   osg_a2;
    float32   osg_qb0;
    float32   osg_qb1;
    float32   osg_qb2;
    float32   Ualphap;    /**<  output XX序alpha */
    float32   Ubetap;     /**<  XX序beta  */
    float32   Ualphan;    /**<  负序alpha */
    float32   Ubetan;     /**<  负序beta */
    float32   wn;         /**<  nominal angle frequency 中心频率，可以给定也可以根据实时值更改*/
    float32   delta_T;    /**<  采样时间T，s*/

}DSOGI_TYPE;

typedef DSOGI_TYPE * DSOGI_TYPE_handle;

typedef struct
{
    float32  Input;        // Output: stationary d-axis stator variable
    float32  Input_1;      // Output: Error(k-1)
    float32  Input_2;      // Output: Error(k-2)
    float32  Output;    // output: Output(k)
    float32  Output_1;  // output: Output(k-1)
    float32  Output_2;  // output: Output(k-2)
    float32  Q;         // Input: rotating q-axis stator variable
    float32  wo_Ts;  // Input:
    float32  wo;  // Input:
    float32  m;  // Input: (4+4*Q*wc*Ts+wo^2*Ts^2)
    float32  a;  // Input: (4+wo^2*Ts^2)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    float32  b;  // Input: (2*wo^2*Ts^2-8)/(4+4*Q*wo*Ts+wo^2*Ts^2)
    float32  c;  // Input: ((4-4*Q*wo*Ts+wo^2*Ts^2))/(4+4*Q*wo*Ts+wo^2*Ts^2)
    void  (*calc)();// Pointer to calculation function
    void  (*init)();
} NOTCH;

typedef NOTCH *Notch_handle;


typedef struct
{
    float32  Kp;
    float32  Ki;
    float32  ErrLimt;
    float32  PiOutUpLimt;
    float32  PiOutDnLimt;
    PI_DATA_TYPE *pstPidata;
}PI_INIT_TYPE;

typedef struct
{
    int16 iPower;  /**< x1*/
    int16 iVnorm;  /**< x10*/
    int16 iFnorm;  /**< x100*/
    int16 iIgnorm; /**< x100*/
    Uint16 uiPhaseNum; /**< 三相或单相 */
    Uint16 uiCellNum;  /**< A相模块个数 */
}PROJECT_NORM_PARA;

typedef struct
{
    Uint16 uiSwitchFrequency; /**< x1*/
    Uint16 uiIntNumSet;       /**< x1*/
    Uint16 uiCPUClkMhz;       /**< x1*/
    Uint16 uiInterval;
    Uint16 uiControlFreq;     /**< x1*/
    Uint16 uiDeadTime;        /**< ns*/
    Uint16 uiCBC_OcpSet;      /**< CBC门限值*/
}HARD_PARA;

typedef struct
{

    PROJECT_NORM_PARA stPowerNomValue;
    PROJECT_NORM_PARA stPowerNomValueOld;
    HARD_PARA stHardPara;
    HARD_PARA stHardParaOld;
    //Uint16   uiTrigdelay;
    Uint16   uiCalcRMSPoints;
    Uint16   uiHardChangeFlag;
    Uint16   uiControlParaChange;
    int16    iCLockDiv;
    Uint16   uiParaChange;
    Uint16   uiPwmTimerPeriod;
    float32  fThetaStepBase;
    float32  SampTime; //运算周期
    float32  Theta_TO_FFEQ;

}SYSTEM_NORMAL_VALUE;

typedef struct {
    float32 Vbase;      // 基准相电压 (V)
    float32 Ibase;      // 基准交流电流 (A)
    float32 Sbase;      // 基准功率 (W)
    float32 Zbase;      // 基准阻抗 (Ω)
    float32 wbase;      // 基准角频率 (rad/s)
    float32 Ts;          //控制周期
    float32 Tsbase;          //基准控制周期
    float32 Ts_pu;      // 标幺化采样时间
    PI_DATA_TYPE PI_IgD_Loop_pu;  //D轴电流环标幺
    PI_DATA_TYPE PI_IgQ_Loop_pu;  //Q轴电流环标幺
    float32 Vg_D_pu;    //D轴电压标幺值
    float32 Vg_Q_pu;    //Q轴电压标幺值
    float32 Vdc_Normalize_pu; //母线电压标幺
    float32 D_pu;       //D轴调制波
    float32 Q_pu;       //Q轴调制波
    float32 Vinv_pu;
    float32 Alfa_pu;
    float32 Beta_pu;
    float32 Base_Modulate_signal[3];

    float32 D_pu_fpga;
    float32 Q_pu_fpga;
    float32 Alfa_pu_fpga;
    float32 Beta_pu_fpga;
    float32 Base_Modulate_signal_fpga[3];
} BASE_VALUES;

/** 算法用电网 电压定义*/
CTRL_ISR_EXT THREE_PHASE_DATA_TYPE    stVg_0;
/**  算法用电网电流变量*/
CTRL_ISR_EXT THREE_PHASE_DATA_TYPE    stIg_0;

/** 电网电压XX负序分解变量*/
CTRL_ISR_EXT DSOGI_TYPE    stVg_DSOGI;
CTRL_ISR_EXT NOTCH stVgQ_2th; //陷波器


/** 算法用电网 电压  电流 母线 定义*/

CTRL_ISR_EXT SPLL_SINGLE   stPLL_DSOGI; //锁相环

CTRL_ISR_EXT  LPF    Vg_D_LPF; //D轴电压低通滤波
CTRL_ISR_EXT  LPF    Vg_Q_LPF; //Q轴电压低通滤波


CTRL_ISR_EXT PI_DATA_TYPE  PI_VgPhaseLockLoop; //resv

CTRL_ISR_EXT PI_DATA_TYPE  PI_VdcBusLoop;      //resv
CTRL_ISR_EXT PI_DATA_TYPE  PI_IgD_Loop;        //D轴电流环
CTRL_ISR_EXT PI_DATA_TYPE  PI_IgQ_Loop;        //Q轴电流环
CTRL_ISR_EXT PI_DATA_TYPE  PI_PowerLoop;       //resv
CTRL_ISR_EXT PI_DATA_TYPE  PI_RepowerLoop;     //resv

CTRL_ISR_EXT BASE_VALUES  PI_Ig_Loop;        //电流环标幺化

CTRL_ISR_EXT PI_DATA_TYPE  PI_AcCurr;          //resv
CTRL_ISR_EXT PI_DATA_TYPE  PI_CellAvgVolt;     //resv
CTRL_ISR_EXT PI_DATA_TYPE  PI_BusCapVolt;      //resv

CTRL_ISR_EXT PI_DATA_TYPE  PI_VoltD_Loop;      //resv
CTRL_ISR_EXT PI_DATA_TYPE  PI_VoltQ_Loop;      //resv
CTRL_ISR_EXT PWM_DRIVE_DATA  stPWMdrive;       //调制波DQ反变换
CTRL_ISR_EXT STSSTCONTROL stSST_Control_Para;  //调制波
CTRL_ISR_EXT STPI_UdcBusLP1 stPI_Udc_unbalance; //半母线均压
CTRL_ISR_EXT STPI_SOCLP1 stPI_SOC_unbalance; //半母线均压


CTRL_ISR_EXT PR_TYPE Ig_D_PR2; //D轴电流环PR
CTRL_ISR_EXT PR_TYPE Ig_D_PR4;
CTRL_ISR_EXT PR_TYPE Ig_D_PR6;
CTRL_ISR_EXT PR_TYPE Ig_D_PR10;

CTRL_ISR_EXT PR_TYPE Ig_Q_PR2; //Q轴电流环PR
CTRL_ISR_EXT PR_TYPE Ig_Q_PR4;
CTRL_ISR_EXT PR_TYPE Ig_Q_PR6;
CTRL_ISR_EXT PR_TYPE Ig_Q_PR10;

CTRL_ISR_EXT SYSTEM_NORMAL_VALUE  stSysNormalValue;

CTRL_ISR_EXT  const PI_INIT_TYPE stPIConstSet[][PI_PARA_NUM];

CTRL_ISR_EXT float32 Pref;
CTRL_ISR_EXT float32 Qref;

/*
*******************************************************************************
*                 Function Declaration 
*******************************************************************************
*/



CTRL_ISR_EXT void Vbus_Ig_DQ_Control(void);

//CTRL_ISR_EXT __interrupt void ePWM7_TZ1_ISR(void);   //不清TZ中断标志
//CTRL_ISR_EXT __interrupt void ePWM4_TZ2_ISR(void);   //不清TZ中断标志
//CTRL_ISR_EXT __interrupt void ePWM5_TZ3_ISR(void);   //不清TZ中断标志
CTRL_ISR_EXT  void PI_Regulator(PI_DATA_TYPE *pstPiCtr,Uint16 uiDesaturationCtrEn);
CTRL_ISR_EXT  void LPF_Calc_Isr(LPF_handle);
CTRL_ISR_EXT  void PR_Calc(PR_handle);
CTRL_ISR_EXT  void PR_Init(PR_handle);
CTRL_ISR_EXT  void PI_Init(PI_DATA_TYPE *pstPiCtr,float32 Kp,float32 Ki,float32 Errlimt,float32 Outlimt);


CTRL_ISR_EXT void PLL_LOOP(SPLL_SINGLE *stPLL);
CTRL_ISR_EXT  void PI_Clear(PI_DATA_TYPE *pstPiCtr);

CTRL_ISR_EXT void Spll_1ph_init(float32 Grid_freq, float32 DELTA_T, SPLL_SINGLE *stPLL);
CTRL_ISR_EXT void DSOGI_TYPE_Init(DSOGI_TYPE *p);
CTRL_ISR_EXT  void Notch_Filter_init(NOTCH *v);
CTRL_ISR_EXT  void LPF_Init(LPF_handle);
CTRL_ISR_EXT  void DSOGI_TYPE_Calc(DSOGI_TYPE *p);
CTRL_ISR_EXT  void Notch_Filter_Cal(NOTCH *v);
CTRL_ISR_EXT  void PR_Clear(PR_TYPE *p);
CTRL_ISR_EXT  void Current_DQ_Loop(void);
CTRL_ISR_EXT  void GridData_Transform(void);
CTRL_ISR_EXT  void Control_Loop_Init(void);
CTRL_ISR_EXT  void Ctrl_ISR_Init(void);
CTRL_ISR_EXT  void SOC_Balance_Loop(void);
CTRL_ISR_EXT  void HalfVoltage_Balance_Loop(void);
CTRL_ISR_EXT  void Finally_Modul_Signal_Control(void);
CTRL_ISR_EXT  void vUdc_unbalance_calc(STPI_UdcBusLP1 *pstPI_Udc_unbalancee, Uint16 PhaseIndex, Uint16 CellIndex);
CTRL_ISR_EXT  void vUdc_unbalance_loop_para_initial(STPI_UdcBusLP1 *pstPI_Udc_unbalance);
CTRL_ISR_EXT  void SOC_PI_Regulator(STPI_SOCLP1 *pstPI_SOC_unbalance, Uint16 CellIndex);
CTRL_ISR_EXT  void SOC_Balance_loop_para_initial(STPI_SOCLP1 *pstPI_SOC_unbalance);
CTRL_ISR_EXT  void Base_Values_initial(BASE_VALUES *pPI_Ig_Loop);
CTRL_ISR_EXT  void Per_Unit_Calc(BASE_VALUES *pPI_Ig_Loop);
#endif


