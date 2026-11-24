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


/**
*******************************************************************************
**************************
*											Pre-defines
*******************************************************************************
**************************
*/
#define CTRL_ISR_FOR_GLOBAL

/**
*******************************************************************************
**************************
*                                           Include files
*******************************************************************************
**************************
*/
#include  <math.h>
#include  "User_Ctrl_ISR.h"


/*
*******************************************************************************
**************************/


/*
*******************************************************************************
**************************
*                           Local macro Defines (#define)
*******************************************************************************
**************************
*/
CTRL_ISR_EXT  const PI_INIT_TYPE stPIConstSet[2][PI_PARA_NUM]=
{
    {
        {0.000009 , 0.000000015 ,100 ,DELTA_THETA_STEP*2 ,-DELTA_THETA_STEP*2 ,&PI_VgPhaseLockLoop },
        {0.3212  , 0.000558    ,500  ,100    ,-100  ,&PI_VdcBusLoop },
        {15.5668  , 0.29203    ,50   ,(1.84*100)   ,-(1.94*100)  ,&PI_IgD_Loop },
        {15.5668  , 0.29203    ,50   ,(1.84*100)   ,-(1.94*100)  ,&PI_IgQ_Loop },
        {16.668  , 0.0000    ,100  ,(0.84*1000)   ,-(0.84*1000) ,&PI_AcCurr },
        {0.0003  , 0.0000    ,300   ,0.048 ,-0.048 ,&PI_CellAvgVolt },
        {0.0014  , 0.0000    ,300   ,0.048 ,-0.048 ,&PI_BusCapVolt },
        {1.56    , 0.00785   ,500   ,800  ,-800   ,&PI_VoltQ_Loop },        
    },
    {
        {0.000068 , 0.000000145 ,100 ,DELTA_THETA_STEP*2 ,-DELTA_THETA_STEP*2 ,&PI_VgPhaseLockLoop },
        {0.011    , 0.00006   ,500  ,140    ,-140  ,&PI_VdcBusLoop },
        {1.268   , 0.0035    ,60    ,550   ,-550  ,&PI_IgD_Loop },
        {1.268   , 0.0035    ,60    ,550   ,-550  ,&PI_IgQ_Loop },
        {0.0193  , 0.000135  ,300   ,75    ,-5    ,&PI_PowerLoop },
        {0.0193  , 0.000135  ,300   ,75    ,-75   ,&PI_RepowerLoop },
        {1.56   , 0.00785   ,500   ,850   ,-400   ,&PI_VoltD_Loop },
        {1.56   , 0.00785   ,500   ,800   ,-800   ,&PI_VoltQ_Loop },        
    }
};



/**
****************************************************************************************************/



/******************************************************环路计算部分********************************************************/
/**
* @brief   DSP reads the AD conversion result and normalization processing which used the interrupt method in the procession of data processing  
* @param[in]  
* @param[out] 
* @return 
*/

CTRL_ISR_EXT inline void Read_AD_and_Normalization()
{
//    Uint16 PhaseIndex = 0;
//    Uint16 CellIndex = 0;

//     stVg_0.A = Ua;  //输入电压
//     stVg_0.B = Ub;
//     stVg_0.C = Uc;
//
//     stIg_0.A = GridCurrA;  //输入电流
//     stIg_0.B = GridCurrB;
//     stIg_0.C = GridCurrC;

//    for(PhaseIndex = 0; PhaseIndex < 3; PhaseIndex++)
//    {
//        for(CellIndex = 0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
//        {
//            stPI_SOC_unbalance.Feedback[CellIndex] = ;//SOC反馈
//            stPI_Udc_unbalance.f32Unit_Up_Bus_Avg_U[PhaseIndex][CellIndex] = ; //半母线均压反馈
//            stPI_Udc_unbalance.f32Unit_Dn_Bus_Avg_U[PhaseIndex][CellIndex] = ;
//        }
//    }
}

CTRL_ISR_EXT void DSOGI_TYPE_Calc(DSOGI_TYPE * p)
{
    //alpha 广义XX分
    p->alpha_osg_u[0]  = (p->osg_b0 * (p->alpha_u[0]-p->alpha_u[2]))
                       + (p->osg_a1 * p->alpha_osg_u[1])
                       + (p->osg_a2 * p->alpha_osg_u[2]);

    p->alpha_osg_u[2]  =  p->alpha_osg_u[1];
    p->alpha_osg_u[1]  =  p->alpha_osg_u[0];

    p->alpha_osg_qu[0] = (p->osg_qb0 * p->alpha_u[0])
                       + (p->osg_qb1 * p->alpha_u[1])
                       + (p->osg_qb2 * p->alpha_u[2])
                       + (p->osg_a1*p->alpha_osg_qu[1])
                       + (p->osg_a2*p->alpha_osg_qu[2]);

    p->alpha_osg_qu[2] =  p->alpha_osg_qu[1];
    p->alpha_osg_qu[1] =  p->alpha_osg_qu[0];
    p->alpha_u[2]      =  p->alpha_u[1];
    p->alpha_u[1]      =  p->alpha_u[0];
    //beta 广义XX分
    p->beta_osg_u[0]   = (p->osg_b0 * (p->beta_u[0]-p->beta_u[2]))
                       + (p->osg_a1 * p->beta_osg_u[1])
                       + (p->osg_a2 * p->beta_osg_u[2]);

    p->beta_osg_u[2]   =   p->beta_osg_u[1];
    p->beta_osg_u[1]   =   p->beta_osg_u[0];

    p->beta_osg_qu[0]  = (p->osg_qb0 * p->beta_u[0])
                       + (p->osg_qb1 * p->beta_u[1])
                       + (p->osg_qb2 * p->beta_u[2])
                       + (p->osg_a1 * p->beta_osg_qu[1])
                       + (p->osg_a2*p->beta_osg_qu[2]);

    p->beta_osg_qu[2]  =  p->beta_osg_qu[1];
    p->beta_osg_qu[1]  =  p->beta_osg_qu[0];
    p->beta_u[2]       =  p->beta_u[1];
    p->beta_u[1]       =   p->beta_u[0];
    //对称分量
    p->Ualphap   =   0.5 * (p->alpha_osg_u[0] - p->beta_osg_qu[0]);
    p->Ubetap    =   0.5 * (p->beta_osg_u[0]  + p->alpha_osg_qu[0]);
    p->Ualphan   =   0.5 * (p->alpha_osg_u[0] + p->beta_osg_qu[0]);
    p->Ubetan    =   0.5 * (p->beta_osg_u[0]  - p->alpha_osg_qu[0]);
}

CTRL_ISR_EXT void Notch_Filter_Cal(NOTCH *v)
{
    v->Output   =  v->a *(v->Input + v->Input_2) + v->b * (v->Input_1 - v->Output_1) - v->c * v->Output_2;
    v->Input_2  =  v->Input_1;
    v->Input_1  =  v->Input;
    v->Output_2 = v->Output_1;
    v->Output_1 = v->Output;
}

CTRL_ISR_EXT void PLL_LOOP(SPLL_SINGLE *stPLL)
{
     stPLL->IOut = stPLL->IOut + stPLL->KiSet * stPLL->u_Q;  //

     if ( stPLL->IOut > stPLL->IOutUpLimt1)             //I输出限幅,±10hz,±62.8
     {
         stPLL->IOut = stPLL->IOutUpLimt1;
     }
     else if ( stPLL->IOut < stPLL->IOutDnLimt1)    //
     {
         stPLL->IOut = stPLL->IOutDnLimt1;  //
     }
     stPLL->PIOut = stPLL->KpSet*stPLL->u_Q + stPLL->IOut;  //即为W的变化，20200724
     if ( stPLL->PIOut > stPLL->IOutUpLimt1)             //I输出限幅,±10hz,±62.8
     {
         stPLL->PIOut = stPLL->IOutUpLimt1;
     }
     else if ( stPLL->PIOut < stPLL->IOutDnLimt1)    //
     {
         stPLL->PIOut = stPLL->IOutDnLimt1;  //
     }
     stPLL->Wo = stPLL->wn+stPLL->PIOut ;//wo=滤波器输出+wn,0723

     if ( stPLL->Wo > stPLL->WOUpLimt)             //对应频率限幅值40hz-69hz
     {
         stPLL->Wo = stPLL->WOUpLimt;
     }
     else if ( stPLL->Wo < stPLL->WODnLimt)    //
     {
         stPLL->Wo = stPLL->WODnLimt;
     }

     stPLL->theta=stPLL->theta + (stPLL->Wo * stPLL->delta_T);//计算角度值，0723


     if(stPLL->theta>=(float32)(PI2))//角度限幅值
     {
         stPLL->theta-=(float32)(PI2);//可以直接减去-6.28
     }
    //采集到的电网电压的相位进行相位补偿，理论计算=TS+5rc=100+50=150us，对应0.0471弧度，对应2.7°，实际调试0.02效果还可以，0.0471效果差，20210302

     stPLL->sinA  = (float32)sin(stPLL->theta );//sin
     stPLL->cosA  = (float32)cos(stPLL->theta );//cos
     stPLL->sinB  = (float32)sin(stPLL->theta - PI2_DIV_3 );  // sin
     stPLL->cosB  = (float32)cos(stPLL->theta - PI2_DIV_3);   // cos
     stPLL->sinC  = (float32)sin(stPLL->theta + PI2_DIV_3 );  // sin
     stPLL->cosC  = (float32)cos(stPLL->theta + PI2_DIV_3);   // cos

     stPLL->fo = stPLL->Wo * ONE_DIV_PI2;//使用平均角频率计算频率，20210612

}

CTRL_ISR_EXT void LPF_Calc_Isr(LPF *v)
{
    v->Output   = v->a * v->Output0 + v->b * (v->Input + v->Input0);
    v->Input0   = v->Input;
    v->Output0  = v->Output;
}

/**
* @brief   数据变换
* @param[in]
* @param[out]
* @return 返回值说明
*/
CTRL_ISR_EXT  void GridData_Transform()
{

    stIg_0.Alfa  = stIg_0.A * K_2Div3Cnst - (stIg_0.B + stIg_0.C ) * K_1Div3Cnst;
    stIg_0.Beta  = (stIg_0.B - stIg_0.C ) * K_1DivSqrt3;

    stVg_0.D  = stVg_0.Alfa * stVg_0.CosTheta + stVg_0.Beta * stVg_0.SinTheta; //输入电压D轴
    stVg_0.Q  = stVg_0.Beta * stVg_0.CosTheta - stVg_0.Alfa * stVg_0.SinTheta;

    stIg_0.D  = stIg_0.Alfa * stVg_0.CosTheta + stIg_0.Beta * stVg_0.SinTheta;  //输入电流D轴
    stIg_0.Q  = stIg_0.Beta * stVg_0.CosTheta - stIg_0.Alfa * stVg_0.SinTheta;

    Vg_D_LPF.Input = stVg_0.D;
    LPF_Calc_Isr(&Vg_D_LPF);  //低通滤波
    Vg_Q_LPF.Input = stVg_0.Q;
    LPF_Calc_Isr(&Vg_Q_LPF);

}

CTRL_ISR_EXT void PI_Regulator(PI_DATA_TYPE *pstPiCtr,Uint16 uiDesaturationCtrEn)
{

    pstPiCtr->Err = pstPiCtr->Reference - pstPiCtr->Feedback;
    UpDownLimit16_ISR(pstPiCtr->Err,pstPiCtr->ErrUpLimt,pstPiCtr->ErrDnLimt);

    pstPiCtr->PIOut = pstPiCtr->IOut + pstPiCtr->Err * pstPiCtr->Kp;

    UpDownLimit16_ISR(pstPiCtr->PIOut,pstPiCtr->PIOutUpLimt,pstPiCtr->PIOutDnLimt);

    pstPiCtr->IOut = pstPiCtr->IOut + pstPiCtr->Err * pstPiCtr->Ki;// + pstPiCtr->Kol * (pstPiCtr->PIOut - Output0);
    UpDownLimit16_ISR(pstPiCtr->IOut,pstPiCtr->IOutUpLimt,pstPiCtr->IOutDnLimt);

 }

CTRL_ISR_EXT void PR_Calc(PR_TYPE *p)
{
    p->output[0] = (p->a0 * p->input[0] + p->a1 * p->input[1] + p->a2 * p->input[2] - p->b1 * p->output[1] - p->b2 * p->output[2]) * p->b0;

    if (p->output[0] > p->max)
    {
        p->output[0] =  p->max;
    }
    if (p->output[0] < p->min)
    {
        p->output[0] =  p->min;
    }
    p->output[2] = p->output[1];
    p->output[1] = p->output[0];

    p->input[2]  = p->input[1];
    p->input[1]  = p->input[0];
}

/**
* @brief      网侧电流环控制
* @details   The actual switching frequency is 50K and the control frequency is 25K. The control output is updated once every two switching cycles.
* @param[in]  void
* @param[out] void
* @return 
*/
CTRL_ISR_EXT  void Current_DQ_Loop()
{
//    float32 IgErrAbs = 0.0;
  /**XX序D轴电流控制********************************************************************/
    Pref = 60000;
    PI_IgD_Loop.Reference = Pref / (1.5 * stVg_0.D);
    PI_IgD_Loop.Feedback = stIg_0.D ;

//    IgErrAbs = fabsf(PI_IgD_Loop.Err);
//
//    UpDownLimit16_ISR(IgErrAbs, 25, 0);
        
//    if (IgErrAbs > 6.0 )
//    {
//
//        PI_IgD_Loop.Kp = PI_IgD_Loop.KpSet;
//        PI_IgD_Loop.Ki = PI_IgD_Loop.KiSet;
//    }
//    else
//    {
//        PI_IgD_Loop.Kp = PI_IgD_Loop.KpSet;
//        PI_IgD_Loop.Ki = PI_IgD_Loop.KiSet;
//    }
    
    PI_Regulator(&PI_IgD_Loop, 1);
    


   /**XX序Q轴电流控制*********************************************************************/
    Qref = 0;
    PI_IgQ_Loop.Reference = Qref / (-1.5 * stVg_0.D);
    PI_IgQ_Loop.Feedback = stIg_0.Q;
    
    PI_Regulator(&PI_IgQ_Loop, 1);

   /**谐波电流控制************************************************************************/
    
   Ig_Q_PR2.input[0]   = (PI_IgQ_Loop.Reference - stIg_0.Q) * stPWMdrive.DelayTime;
   PR_Calc(&Ig_Q_PR2);
   Ig_Q_PR4.input[0]   = Ig_Q_PR2.input[0];
   PR_Calc(&Ig_Q_PR4);
   Ig_Q_PR6.input[0]   = Ig_Q_PR2.input[0];
   PR_Calc(&Ig_Q_PR6);
   Ig_Q_PR10.input[0]  = Ig_Q_PR2.input[0];
   PR_Calc(&Ig_Q_PR10);
   
   stPWMdrive.PR_Out_Q = Ig_Q_PR2.output[0]
                       + Ig_Q_PR4.output[0]
                       + Ig_Q_PR6.output[0]
                       + Ig_Q_PR10.output[0];
   
    Ig_D_PR2.input[0]   = (PI_IgD_Loop.Reference - stIg_0.D) * stPWMdrive.DelayTime;
    PR_Calc(&Ig_D_PR2);
    Ig_D_PR4.input[0]   = Ig_D_PR2.input[0];
    PR_Calc(&Ig_D_PR4);
    Ig_D_PR6.input[0]   = Ig_D_PR2.input[0];
    PR_Calc(&Ig_D_PR6);
    Ig_D_PR10.input[0]  = Ig_D_PR2.input[0];
    PR_Calc(&Ig_D_PR10);
    
    stPWMdrive.PR_Out_D = Ig_D_PR2.output[0]
                        + Ig_D_PR4.output[0]
                        + Ig_D_PR6.output[0]
                        + Ig_D_PR10.output[0];

   /**负序电流控制**********************************************************************/

   /** generate the space vector，此处对直流侧标幺化*/    
    
    stPWMdrive.Dr  = (Vg_D_LPF.Output  - PI_IgD_Loop.PIOut - stPWMdrive.PR_Out_D ) * stPWMdrive.Vdc_Normalize;
    stPWMdrive.Qr  = (Vg_Q_LPF.Output  - PI_IgQ_Loop.PIOut - stPWMdrive.PR_Out_Q ) * stPWMdrive.Vdc_Normalize;

    stPWMdrive.Vinv = sqrt(stPWMdrive.Dr * stPWMdrive.Dr + stPWMdrive.Qr * stPWMdrive.Qr);
    
    if (stPWMdrive.Vinv > 1.0)
    {
        stPWMdrive.Dr = stPWMdrive.Dr  / stPWMdrive.Vinv;
        stPWMdrive.Qr = stPWMdrive.Qr  / stPWMdrive.Vinv;
    }

    
    stPWMdrive.Alfa  = stPWMdrive.Dr * stPLL_DSOGI.cosA - stPWMdrive.Qr * stPLL_DSOGI.sinA;
    stPWMdrive.Beta  = stPWMdrive.Qr * stPLL_DSOGI.cosA + stPWMdrive.Dr * stPLL_DSOGI.sinA;
    
    stPWMdrive.As = stPWMdrive.Alfa;
    stPWMdrive.Bs = stPWMdrive.Beta*K_Sqrt3Div2Cnst - stPWMdrive.Alfa*K_1Div2Cnst;
    stPWMdrive.Cs = -stPWMdrive.As - stPWMdrive.Bs;
    

    stSST_Control_Para.f32Base_Modulate_signal[0] = stPWMdrive.As;
    stSST_Control_Para.f32Base_Modulate_signal[1] = stPWMdrive.Bs;
    stSST_Control_Para.f32Base_Modulate_signal[2] = stPWMdrive.Cs;

}

CTRL_ISR_EXT void SOC_PI_Regulator(STPI_SOCLP1 *pstPI_SOC_unbalance, Uint16 CellIndex)
{

    pstPI_SOC_unbalance->Err[CellIndex] = pstPI_SOC_unbalance->Reference - pstPI_SOC_unbalance->Feedback[CellIndex];
    UpDownLimit16_ISR(pstPI_SOC_unbalance->Err[CellIndex],pstPI_SOC_unbalance->ErrUpLimt,pstPI_SOC_unbalance->ErrDnLimt);

    pstPI_SOC_unbalance->PIOut[CellIndex] = pstPI_SOC_unbalance->IOut[CellIndex] + pstPI_SOC_unbalance->Err[CellIndex] * pstPI_SOC_unbalance->Kp;

    UpDownLimit16_ISR(pstPI_SOC_unbalance->PIOut[CellIndex],pstPI_SOC_unbalance->PIOutUpLimt,pstPI_SOC_unbalance->PIOutDnLimt);

    pstPI_SOC_unbalance->IOut[CellIndex] = pstPI_SOC_unbalance->IOut[CellIndex] + pstPI_SOC_unbalance->Err[CellIndex] * pstPI_SOC_unbalance->Ki;
    UpDownLimit16_ISR(pstPI_SOC_unbalance->IOut[CellIndex],pstPI_SOC_unbalance->IOutUpLimt,pstPI_SOC_unbalance->IOutDnLimt);

 }

CTRL_ISR_EXT  void SOC_Balance_Loop()
{
    Uint16 PhaseIndex = 0;
    Uint16 CellIndex = 0;
    stPI_SOC_unbalance.SOCSum = 0;
    for(CellIndex=0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
    {
        stPI_SOC_unbalance.SOCSum += stPI_SOC_unbalance.Feedback[CellIndex];
    }
    stPI_SOC_unbalance.Reference = stPI_SOC_unbalance.SOCSum / MODUL_NUM_PHASE;
    for(CellIndex=0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
    {
        SOC_PI_Regulator(&stPI_SOC_unbalance,CellIndex);
    }
    stPI_SOC_unbalance.IinSqrtDQ = sqrt(stIg_0.D * stIg_0.D + stIg_0.Q * stIg_0.Q);
    if(stPI_SOC_unbalance.IinSqrtDQ > 1)
    {
        stPI_SOC_unbalance.IinD = stIg_0.D / stPI_SOC_unbalance.IinSqrtDQ;
        stPI_SOC_unbalance.IinQ = stIg_0.Q / stPI_SOC_unbalance.IinSqrtDQ;
    }
    stPI_SOC_unbalance.IinAlfa = stPI_SOC_unbalance.IinD * stPLL_DSOGI.cosA - stPI_SOC_unbalance.IinQ * stPLL_DSOGI.sinA;
    stPI_SOC_unbalance.IinBeta = stPI_SOC_unbalance.IinQ * stPLL_DSOGI.cosA + stPI_SOC_unbalance.IinD * stPLL_DSOGI.sinA;

    stPI_SOC_unbalance.IinCosTheta[0] = stPI_SOC_unbalance.IinAlfa;
    stPI_SOC_unbalance.IinCosTheta[1] = stPI_SOC_unbalance.IinBeta*K_Sqrt3Div2Cnst - stPI_SOC_unbalance.IinAlfa*K_1Div2Cnst;
    stPI_SOC_unbalance.IinCosTheta[2] = -stPI_SOC_unbalance.IinCosTheta[0] - stPI_SOC_unbalance.IinCosTheta[1];

    for(PhaseIndex = 0; PhaseIndex < 3; PhaseIndex++)
    {
        for(CellIndex = 0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
        {
            stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex] = stPI_SOC_unbalance.PIOut[CellIndex] * stPI_SOC_unbalance.IinCosTheta[PhaseIndex];
        }
    }
}

CTRL_ISR_EXT void vUdc_unbalance_calc(STPI_UdcBusLP1 *pstPI_Udc_unbalance, Uint16 PhaseIndex, Uint16 CellIndex)
{
    /*根据基准调制波*is进行判断 ，对单元上下直流母线均压*/
    pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] + pstPI_Udc_unbalance->f32KiSet * pstPI_Udc_unbalance->f32udc1_udc2_delta[PhaseIndex][CellIndex];  //
    if ( pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] > pstPI_Udc_unbalance->f32UpLimt)             //
    {
        pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32UpLimt;
    }
    else if ( pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] < pstPI_Udc_unbalance->f32DnLimt)    //
    {
        pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32DnLimt;
    }
    pstPI_Udc_unbalance->f32POut[PhaseIndex][CellIndex]= pstPI_Udc_unbalance->f32KpSet * pstPI_Udc_unbalance->f32udc1_udc2_delta[PhaseIndex][CellIndex];  //
    pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32POut[PhaseIndex][CellIndex] + pstPI_Udc_unbalance->f32IOut[PhaseIndex][CellIndex];
    if( (pstPI_Udc_unbalance->f32ur[PhaseIndex][CellIndex] * pstPI_Udc_unbalance->f32is[PhaseIndex]) >= 0)
    {
        pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex]  = pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex];
    }
    else
    {
        pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex]  = -pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex];
    }

    if ( pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex] > pstPI_Udc_unbalance->f32UpLimt)             //PI输出限幅
    {
        pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32UpLimt;
    }
    else if ( pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex] < pstPI_Udc_unbalance->f32DnLimt)    //
    {
        pstPI_Udc_unbalance->f32PIOut[PhaseIndex][CellIndex] = pstPI_Udc_unbalance->f32DnLimt;
    }
}

CTRL_ISR_EXT  void HalfVoltage_Balance_Loop()
{
    Uint16 PhaseIndex = 0;
    Uint16 CellIndex = 0;
    for(PhaseIndex = 0; PhaseIndex < 3; PhaseIndex++)
    {
        stPI_Udc_unbalance.f32is[PhaseIndex] = stIg_0.Iin[PhaseIndex];//用于单元内均压控制，判别有功方向
       for(CellIndex = 0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
       {
           stPI_Udc_unbalance.f32udc1_udc2_delta[PhaseIndex][CellIndex] = stPI_Udc_unbalance.f32Unit_Up_Bus_Avg_U[PhaseIndex][CellIndex]
                                                         - stPI_Udc_unbalance.f32Unit_Dn_Bus_Avg_U[PhaseIndex][CellIndex];//X相Y单元内均压上下母线电压环给定
           stPI_Udc_unbalance.f32ur[PhaseIndex][CellIndex] = stSST_Control_Para.f32Base_Modulate_signal[PhaseIndex] + stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex];
           vUdc_unbalance_calc(&stPI_Udc_unbalance, PhaseIndex, CellIndex);//X相Y单元内上下均压
       }
    }
}

CTRL_ISR_EXT  void Finally_Modul_Signal_Control()
{
    Uint16 PhaseIndex = 0;
    Uint16 CellIndex = 0;
    for(PhaseIndex = 0; PhaseIndex < 3; PhaseIndex++)
    {
        for(CellIndex = 0; CellIndex < MODUL_NUM_PHASE; CellIndex++)
        {
//            stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] = stSST_Control_Para.f32Base_Modulate_signal[PhaseIndex] + stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex] - stPI_Udc_unbalance.f32PIOut[PhaseIndex][CellIndex];
//            stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] = - (stSST_Control_Para.f32Base_Modulate_signal[PhaseIndex] + stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex]) - stPI_Udc_unbalance.f32PIOut[PhaseIndex][CellIndex];
            stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] = PI_Ig_Loop.Base_Modulate_signal[PhaseIndex] + stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex] - stPI_Udc_unbalance.f32PIOut[PhaseIndex][CellIndex];
            stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] = - (PI_Ig_Loop.Base_Modulate_signal[PhaseIndex] + stPI_SOC_unbalance.SOCOut[PhaseIndex][CellIndex]) - stPI_Udc_unbalance.f32PIOut[PhaseIndex][CellIndex];
            if(stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] >= 0.99)
            {
                stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] = 0.99;
            }
            else if(stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] <= -0.99)
            {
                stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][0] = -0.99;
            }
            if(stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] >= 0.99)
            {
                stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] = 0.99;
            }
            else if(stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] <= -0.99)
            {
                stSST_Control_Para.f32Final_Modulate_signal[PhaseIndex][CellIndex][1] = -0.99;
            }
        }
        stSST_Control_Para.f32Final_Phase_signal_ToFpga[PhaseIndex] =PI_Ig_Loop.Base_Modulate_signal_fpga[PhaseIndex];
    }
}

CTRL_ISR_EXT  void  Per_Unit_Calc(BASE_VALUES *pPI_Ig_Loop)
{
    Pref = 60000;
    pPI_Ig_Loop->PI_IgD_Loop_pu.Reference = Pref / (1.5 * stVg_0.D) / PI_Ig_Loop.Ibase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.Feedback = stIg_0.D / PI_Ig_Loop.Ibase;

    Qref = 0;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.Reference = Qref / (-1.5 * stVg_0.D) / PI_Ig_Loop.Ibase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.Feedback = stIg_0.Q / PI_Ig_Loop.Ibase;

    PI_Regulator(&PI_Ig_Loop.PI_IgD_Loop_pu, 1);
    PI_Regulator(&PI_Ig_Loop.PI_IgQ_Loop_pu, 1);

#ifdef _SIMULATION_NO_DSP_
    pPI_Ig_Loop->Vg_D_pu = Vg_D_LPF.Output / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->Vg_Q_pu = Vg_Q_LPF.Output / pPI_Ig_Loop->Vbase;

    pPI_Ig_Loop->Vdc_Normalize_pu = stPWMdrive.Vdc_Normalize * pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->D_pu = (pPI_Ig_Loop->Vg_D_pu - pPI_Ig_Loop->PI_IgD_Loop_pu.PIOut) *  pPI_Ig_Loop->Vdc_Normalize_pu;
    pPI_Ig_Loop->Q_pu = (pPI_Ig_Loop->Vg_Q_pu - pPI_Ig_Loop->PI_IgQ_Loop_pu.PIOut) *  pPI_Ig_Loop->Vdc_Normalize_pu;

    pPI_Ig_Loop->Vinv_pu = sqrt(pPI_Ig_Loop->D_pu * pPI_Ig_Loop->D_pu + pPI_Ig_Loop->Q_pu * pPI_Ig_Loop->Q_pu);
    if(pPI_Ig_Loop->Vinv_pu > 1.0)
    {
        pPI_Ig_Loop->D_pu = pPI_Ig_Loop->D_pu / pPI_Ig_Loop->Vinv_pu;
        pPI_Ig_Loop->Q_pu = pPI_Ig_Loop->Q_pu / pPI_Ig_Loop->Vinv_pu;
    }

    pPI_Ig_Loop->Alfa_pu  = pPI_Ig_Loop->D_pu * stPLL_DSOGI.cosA - pPI_Ig_Loop->Q_pu * stPLL_DSOGI.sinA;
    pPI_Ig_Loop->Beta_pu  = pPI_Ig_Loop->Q_pu * stPLL_DSOGI.cosA + pPI_Ig_Loop->D_pu * stPLL_DSOGI.sinA;

    pPI_Ig_Loop->Base_Modulate_signal[0] = pPI_Ig_Loop->Alfa_pu;
    pPI_Ig_Loop->Base_Modulate_signal[1] = pPI_Ig_Loop->Beta_pu*K_Sqrt3Div2Cnst - pPI_Ig_Loop->Alfa_pu*K_1Div2Cnst;
    pPI_Ig_Loop->Base_Modulate_signal[2] = -pPI_Ig_Loop->Base_Modulate_signal[0] - pPI_Ig_Loop->Base_Modulate_signal[1];
#else
    pPI_Ig_Loop->D_pu_fpga = (Vg_D_LPF.Output - pPI_Ig_Loop->PI_IgD_Loop_pu.PIOut * pPI_Ig_Loop->Vbase);// * COFF_REF_VOLT;
    pPI_Ig_Loop->Q_pu_fpga = (Vg_Q_LPF.Output - pPI_Ig_Loop->PI_IgQ_Loop_pu.PIOut * pPI_Ig_Loop->Vbase);// * COFF_REF_VOLT;

    pPI_Ig_Loop->Alfa_pu_fpga  = pPI_Ig_Loop->D_pu_fpga * stPLL_DSOGI.cosA - pPI_Ig_Loop->Q_pu_fpga * stPLL_DSOGI.sinA;
    pPI_Ig_Loop->Beta_pu_fpga  = pPI_Ig_Loop->Q_pu_fpga * stPLL_DSOGI.cosA + pPI_Ig_Loop->D_pu_fpga * stPLL_DSOGI.sinA;

    pPI_Ig_Loop->Base_Modulate_signal_fpga[0] = pPI_Ig_Loop->Alfa_pu_fpga;
    pPI_Ig_Loop->Base_Modulate_signal_fpga[1] = pPI_Ig_Loop->Beta_pu_fpga*K_Sqrt3Div2Cnst - pPI_Ig_Loop->Alfa_pu_fpga*K_1Div2Cnst;
    pPI_Ig_Loop->Base_Modulate_signal_fpga[2] = -pPI_Ig_Loop->Base_Modulate_signal_fpga[0] - pPI_Ig_Loop->Base_Modulate_signal_fpga[1];
#endif
}

CTRL_ISR_EXT void Vbus_Ig_DQ_Control(void)
{ 

    Read_AD_and_Normalization();    //AD数据

    stPWMdrive.Vdc_Normalize = 1.0 / (stPI_Udc_unbalance.f32All_Bus_Avg_U * (float32)MODUL_NUM_PHASE); //母线电压标幺化
    
    stVg_0.Alfa  = stVg_0.A * K_2Div3Cnst - (stVg_0.B + stVg_0.C ) * K_1Div3Cnst;
    stVg_0.Beta  = (stVg_0.B - stVg_0.C ) * K_1DivSqrt3; 
    stVg_DSOGI.alpha_u[0]  = stVg_0.Alfa;
    stVg_DSOGI.beta_u[0]   = stVg_0.Beta;
    
    DSOGI_TYPE_Calc(&stVg_DSOGI);
    
    stVg_0.D_P  = stVg_DSOGI.Ualphap * stVg_0.CosTheta + stVg_DSOGI.Ubetap * stVg_0.SinTheta;     //输入电压正序分量
    stVg_0.Q_P  = stVg_DSOGI.Ubetap  * stVg_0.CosTheta - stVg_DSOGI.Ualphap * stVg_0.SinTheta;
    
    stVg_0.D_N  = stVg_DSOGI.Ualphan * stVg_0.CosTheta - stVg_DSOGI.Ubetan * stVg_0.SinTheta;      //输入电压负序分量
    stVg_0.Q_N  = stVg_DSOGI.Ubetan  * stVg_0.CosTheta + stVg_DSOGI.Ualphan * stVg_0.SinTheta;
    
    stPLL_DSOGI.u_D = stVg_0.D_P ;
    stVgQ_2th.Input = stVg_0.Q_P ;
    Notch_Filter_Cal(&stVgQ_2th);          //正序Q轴电压陷波器100Hz
    stPLL_DSOGI.u_Q = stVgQ_2th.Output;
    PLL_LOOP(&stPLL_DSOGI);                //正序电压锁相
    
    stVg_0.CosTheta = stPLL_DSOGI.cosA;    //A相相位
    stVg_0.SinTheta = stPLL_DSOGI.sinA;

    stPLL_DSOGI.costheta[0] = stPLL_DSOGI.cosA;   //三相cos相位
    stPLL_DSOGI.costheta[1] = stPLL_DSOGI.cosB;
    stPLL_DSOGI.costheta[2] = stPLL_DSOGI.cosC;


    GridData_Transform();        //DQ变换
//    Current_DQ_Loop();           //电流环DQ控制
//    SOC_Balance_Loop();          //SOC均衡控制
//    HalfVoltage_Balance_Loop();  //上下母线均压控制
//    Finally_Modul_Signal_Control();
    //------------------------------------------环路标幺化---------------------------------
   // Per_Unit_Calc(&PI_Ig_Loop);
}


/****************************************************DQ环路初始化部分*****************************************************/
/**
* @brief   LoadPiDefaultPara
* @param[in] uiMachineCode
* @param[out]
* @return 返回值说明
*/

CTRL_ISR_EXT void LoadPiDefaultPara(Uint16 uiMachineCode)
{
    Uint16 i,j;
    i= uiMachineCode;

    for (j = 0; j <PI_PARA_NUM; j++)
    {
        (stPIConstSet[i][j].pstPidata)->PIOut   = 0;
        (stPIConstSet[i][j].pstPidata)->PIOut   = 0;
        (stPIConstSet[i][j].pstPidata)->IOut    = 0;

        (stPIConstSet[i][j].pstPidata)->KpSet   = stPIConstSet[i][j].Kp;
        (stPIConstSet[i][j].pstPidata)->KiSet   = stPIConstSet[i][j].Ki;
        (stPIConstSet[i][j].pstPidata)->Kp      = stPIConstSet[i][j].Kp;
        (stPIConstSet[i][j].pstPidata)->Ki      = stPIConstSet[i][j].Ki;
        (stPIConstSet[i][j].pstPidata)->Reference    = 0;
        (stPIConstSet[i][j].pstPidata)->Feedback     = 0;
        (stPIConstSet[i][j].pstPidata)->ErrUpLimt    =  stPIConstSet[i][j].ErrLimt;
        (stPIConstSet[i][j].pstPidata)->ErrDnLimt    = -stPIConstSet[i][j].ErrLimt;
        (stPIConstSet[i][j].pstPidata)->IOutUpLimt   = stPIConstSet[i][j].PiOutUpLimt;
        (stPIConstSet[i][j].pstPidata)->IOutDnLimt   = stPIConstSet[i][j].PiOutDnLimt;
        (stPIConstSet[i][j].pstPidata)->PIOutUpLimt  = stPIConstSet[i][j].PiOutUpLimt;
        (stPIConstSet[i][j].pstPidata)->PIOutDnLimt  = stPIConstSet[i][j].PiOutDnLimt;
        (stPIConstSet[i][j].pstPidata)->Kol          = stPIConstSet[i][j].Ki/stPIConstSet[i][j].Kp;
    }

}

/**************************************************************************************/
/**
* @brief   PICtrlLoopPara_Init
* @param[in] uiMachineCode
* @param[out]
* @return 返回值说明
*/

CTRL_ISR_EXT void PI_LoopPara_Init()
{

    stPLL_DSOGI.KiSet = 0.000001;
    stPLL_DSOGI.KpSet = 0.045;
    stPLL_DSOGI.PIOut =(float32)(0.0);
    stPLL_DSOGI.IOut  =(float32)(0.0);
    stPLL_DSOGI.IOutUpLimt1 =(float32)(10.0*PI2);
    stPLL_DSOGI.IOutDnLimt1 =(float32)(-10.0*PI2);
    stPLL_DSOGI.WOUpLimt = 69.0*PI2;//对应±20hz
    stPLL_DSOGI.WODnLimt = 40.0*PI2;//限幅必须为正值，0728

}

CTRL_ISR_EXT void PR_Init(PR_TYPE *p)
{
    p->a0 = 4 * p->Kr * p->wc * p->Ts_pr;
    p->a1 = 0;
    p->a2 = -p->a0;
    p->b0 = (float)1 / (4 + 4 * p->wc * p->Ts_pr + p->wo * p->wo * p->Ts_pr * p->Ts_pr);
    p->b1 =  (float)2 * p->wo * p->wo * p->Ts_pr * p->Ts_pr - 8 ;
    p->b2 = 4 - 4 * p->wc * p->Ts_pr + p->wo * p->wo * p->Ts_pr * p->Ts_pr;


    p->input[0]  = 0;
    p->input[1]  = 0;
    p->input[2]  = 0;

    p->output[0] = 0;
    p->output[1] = 0;
    p->output[2] = 0;

}


CTRL_ISR_EXT void Current_PR_Para_Init()
{

    Ig_D_PR2.Kr     = DQ_PR_2_K;             ///< PR1_alpha.Kr;70
    Ig_D_PR2.wc     = 6;              ///< 谐振点处带宽
    Ig_D_PR2.wo     = PI2 * (float32)GRID_FREQ_SET * 2.0 ;//314.159265*4;   ///< 谐振频率
    Ig_D_PR2.Ts_pr  = stSysNormalValue.SampTime;
    Ig_D_PR2.max    = 500;
    Ig_D_PR2.min    = -500;
    Ig_D_PR2.init   = PR_Init;
    Ig_D_PR2.calc   = PR_Calc;
    PR_Init(&Ig_D_PR2);

    Ig_D_PR4.Kr     = DQ_PR_4_K;             ///< PR1_alpha.Kr;70
    Ig_D_PR4.wc     = 12;              ///< 谐振点处带宽
    Ig_D_PR4.wo     = PI2 * (float32)GRID_FREQ_SET * 4.0 ;//314.159265*4;   ///< 谐振频率
    Ig_D_PR4.Ts_pr  = stSysNormalValue.SampTime;
    Ig_D_PR4.max    = 300;
    Ig_D_PR4.min    = -300;
    Ig_D_PR4.init   = PR_Init;
    Ig_D_PR4.calc   = PR_Calc;
    PR_Init(&Ig_D_PR4);

    Ig_D_PR6.Kr     = DQ_PR_6_K;             ///< PR1_alpha.Kr;70
    Ig_D_PR6.wc     = 18;              ///< 谐振点处带宽
    Ig_D_PR6.wo     = PI2 * (float32)GRID_FREQ_SET * 6.0 ;//314.159265*4;   ///< 谐振频率
    Ig_D_PR6.Ts_pr  = stSysNormalValue.SampTime;
    Ig_D_PR6.max    = 200;
    Ig_D_PR6.min    = -200;
    Ig_D_PR6.init   = PR_Init;
    Ig_D_PR6.calc   = PR_Calc;
    PR_Init(&Ig_D_PR6);

    Ig_D_PR10.Kr     = DQ_PR_10_K;             ///< PR1_alpha.Kr;70
    Ig_D_PR10.wc     = 30;              ///< 谐振点处带宽
    Ig_D_PR10.wo     = PI2 * (float32)GRID_FREQ_SET * 10.0 ;//314.159265*4;   ///< 谐振频率
    Ig_D_PR10.Ts_pr  = stSysNormalValue.SampTime;
    Ig_D_PR10.max    = 100;
    Ig_D_PR10.min    = -100;
    Ig_D_PR10.init   = PR_Init;
    Ig_D_PR10.calc   = PR_Calc;
    PR_Init(&Ig_D_PR10);

    Ig_Q_PR2.Kr     = DQ_PR_2_K;             ///< PR1_alpha.Kr;70
    Ig_Q_PR2.wc     = 6;              ///< 谐振点处带宽
    Ig_Q_PR2.wo     = PI2 * (float32)GRID_FREQ_SET * 2.0 ;//314.159265*4;   ///< 谐振频率
    Ig_Q_PR2.Ts_pr  = stSysNormalValue.SampTime;
    Ig_Q_PR2.max    = 500;
    Ig_Q_PR2.min    = -500;
    Ig_Q_PR2.init   = PR_Init;
    Ig_Q_PR2.calc   = PR_Calc;
    PR_Init(&Ig_Q_PR2);

    Ig_Q_PR4.Kr     = DQ_PR_4_K;             ///< PR1_alpha.Kr;70
    Ig_Q_PR4.wc     = 12;              ///< 谐振点处带宽
    Ig_Q_PR4.wo     = PI2 * (float32)GRID_FREQ_SET * 4.0 ;//314.159265*4;   ///< 谐振频率
    Ig_Q_PR4.Ts_pr  = stSysNormalValue.SampTime;
    Ig_Q_PR4.max    = 300;
    Ig_Q_PR4.min    = -300;
    Ig_Q_PR4.init   = PR_Init;
    Ig_Q_PR4.calc   = PR_Calc;
    PR_Init(&Ig_Q_PR4);

    Ig_Q_PR6.Kr     = DQ_PR_6_K;             ///< PR1_alpha.Kr;70
    Ig_Q_PR6.wc     = 18;              ///< 谐振点处带宽
    Ig_Q_PR6.wo     = PI2 * (float32)GRID_FREQ_SET * 6.0 ;//314.159265*4;   ///< 谐振频率
    Ig_Q_PR6.Ts_pr  = stSysNormalValue.SampTime;
    Ig_Q_PR6.max    = 200;
    Ig_Q_PR6.min    = -200;
    Ig_Q_PR6.init   = PR_Init;
    Ig_Q_PR6.calc   = PR_Calc;
    PR_Init(&Ig_Q_PR6);

    Ig_Q_PR10.Kr     = DQ_PR_10_K;             ///< PR1_alpha.Kr;70
    Ig_Q_PR10.wc     = 30;              ///< 谐振点处带宽
    Ig_Q_PR10.wo     = PI2 * (float32)GRID_FREQ_SET * 10.0 ;//314.159265*4;   ///< 谐振频率
    Ig_Q_PR10.Ts_pr  = stSysNormalValue.SampTime;
    Ig_Q_PR10.max    = 100;
    Ig_Q_PR10.min    = -100;
    Ig_Q_PR10.init   = PR_Init;
    Ig_Q_PR10.calc   = PR_Calc;
    PR_Init(&Ig_Q_PR10);
}


CTRL_ISR_EXT void Spll_1ph_init(float32 Grid_freq, float32 DELTA_T, SPLL_SINGLE *stPLL)
{
   stPLL->u[0]      = (float32)(0.0);
   stPLL->u[1]      = (float32)(0.0);
   stPLL->u[2]      = (float32)(0.0);

   stPLL->u_Q    = (float32)(0.0);

   stPLL->u_D    = (float32)(0.0);

   stPLL->fo        = (float32)(Grid_freq);
   stPLL->fn        = (float32)(Grid_freq);
   stPLL->wn        = (float32)(PI2*Grid_freq);
   stPLL->Wo        = (float32)(PI2*Grid_freq);
   stPLL->theta     = (float32)(0.0);

   stPLL->sinA       = (float32)(0.0);
   stPLL->cosA       = (float32)(0.0);
   stPLL->sinB       = (float32)(0.0);
   stPLL->cosB       = (float32)(0.0);
   stPLL->sinC       = (float32)(0.0);
   stPLL->cosC       = (float32)(0.0);

   stPLL->delta_T    =  DELTA_T;
   stPLL->Flag_T0_period_reg_update = 0;
}

CTRL_ISR_EXT void DSOGI_TYPE_Init(DSOGI_TYPE * p)
{
    float32 osgx,osgy,temp;
    osgx      = (float32)(2.0 * p->osg_k * p->wn * p->delta_T);//x=2k*Wn*Ts
    p->osg_x  = (float32)(osgx);//
    osgy      = (float32)(p->wn * p->delta_T * p->wn * p->delta_T);//y=Wn*Ts*Wn*Ts
    p->osg_y  = (float32)(osgy);
    temp      = (float32)1.0 / (osgx + osgy + 4.0);//
    p->osg_b0 = ((float32)osgx * temp);
    p->osg_b2 = ((float32)(-1.0) * p->osg_b0);
    p->osg_a1 = ((float32)(2.0 * (4.0-osgy)) * temp);
    p->osg_a2 = ((float32)(osgx-osgy-4) * temp);
    p->osg_qb0= ((float32)(p->osg_k * osgy) * temp);
    p->osg_qb1= (p->osg_qb0 * (float32)(2.0));
    p->osg_qb2=  p->osg_qb0;

    p->alpha_u[0] = 0;
    p->alpha_u[1] = 0;
    p->alpha_u[2] = 0;
    p->alpha_osg_u[0]   = 0;
    p->alpha_osg_u[1]   = 0;
    p->alpha_osg_u[2]   = 0;
    p->alpha_osg_qu[0]  = 0;
    p->alpha_osg_qu[1]  = 0;
    p->alpha_osg_qu[2]  = 0;

    p->beta_u[0] = 0;
    p->beta_u[1] = 0;
    p->beta_u[2] = 0;
    p->beta_osg_u[0]  = 0;
    p->beta_osg_u[1]  = 0;
    p->beta_osg_u[2]  = 0;
    p->beta_osg_qu[0] = 0;
    p->beta_osg_qu[1] = 0;
    p->beta_osg_qu[2] = 0;

    p->Ualphap  = 0;
    p->Ualphan  = 0;
    p->Ubetap   = 0;
    p->Ubetan   = 0;
}


CTRL_ISR_EXT void Notch_Filter_init(NOTCH *v)
{
    v->m = (4 + 4 * v->Q * v->wo_Ts + v->wo_Ts * v->wo_Ts);
    v->a = (4 + v->wo_Ts * v->wo_Ts) / v->m;
    v->b = (2 * v->wo_Ts * v->wo_Ts - 8) / v->m;
    v->c = ((4 - 4 * v->Q * v->wo_Ts + v->wo_Ts * v->wo_Ts)) / v->m;
    v->Input    = 0;
    v->Input_1  = 0;
    v->Input_2  = 0;

    v->Output   = 0;
    v->Output_1 = 0;
    v->Output_2 = 0;
}


CTRL_ISR_EXT void LPF_Init(LPF *v)
{
    v->a = (2 - v->Omiga_Ts) / (2 + v->Omiga_Ts);
    v->b = v->Omiga_Ts / (2 + v->Omiga_Ts);
    v->Output  = 0;
    v->Input0  = 0;
    v->Input   = 0;
    v->Output0 = v->Output;
}

void vUdc_unbalance_loop_para_initial(STPI_UdcBusLP1 *pstPI_Udc_unbalance)
{
   //中性点控制环
    Uint16 i=0,j=0;
    for(i=0;i<3;i++)
    {
        for( j=0; j<MODUL_NUM_PHASE; j++ )
        {
            pstPI_Udc_unbalance->f32udc1_udc2_delta[i][j] =0;
            pstPI_Udc_unbalance->f32PIOut[i][j] =0;
            pstPI_Udc_unbalance->f32POut[i][j] =0;
            pstPI_Udc_unbalance->f32IOut[i][j] =0;
            pstPI_Udc_unbalance->f32Unit_Up_Bus_Avg_U[i][j] = 0;
            pstPI_Udc_unbalance->f32Unit_Dn_Bus_Avg_U[i][j] = 0;
        }
    }
    pstPI_Udc_unbalance->f32KpSet=0.001; //
    pstPI_Udc_unbalance->f32KiSet=0.000001;
    pstPI_Udc_unbalance->f32ErrUpLimt=100;//积分起作用判断条件，20200623，wdj
    pstPI_Udc_unbalance->f32ErrDnLimt=-100;
    pstPI_Udc_unbalance->f32UpLimt=0.02;
    pstPI_Udc_unbalance->f32DnLimt=-0.02;
}

void SOC_Balance_loop_para_initial(STPI_SOCLP1 *pstPI_SOC_unbalance)
{
    Uint16 i=0;
    for( i=0; i<MODUL_NUM_PHASE; i++ )
    {
        pstPI_SOC_unbalance->IOut[i] = 0;
        pstPI_SOC_unbalance->PIOut[i] = 0;
    }
    pstPI_SOC_unbalance->KpSet = 10;
    pstPI_SOC_unbalance->Kp = pstPI_SOC_unbalance->KpSet;
    pstPI_SOC_unbalance->KiSet = 0;
    pstPI_SOC_unbalance->Ki = pstPI_SOC_unbalance->KiSet;
    pstPI_SOC_unbalance->ErrUpLimt = 200;
    pstPI_SOC_unbalance->ErrDnLimt = -200;
    pstPI_SOC_unbalance->IOutUpLimt = 0.2;
    pstPI_SOC_unbalance->IOutDnLimt = -0.2;
    pstPI_SOC_unbalance->PIOutUpLimt = 0.2;
    pstPI_SOC_unbalance->PIOutDnLimt = -0.2;
}

void Base_Values_initial(BASE_VALUES *pPI_Ig_Loop)
{
    //--------------------------基准值计算-----------------------------
    pPI_Ig_Loop->Vbase = BASE_Voltage_PhasePeak;
    pPI_Ig_Loop->Sbase = BASE_Power;
    pPI_Ig_Loop->Ibase = BASE_Current_Peak;
    pPI_Ig_Loop->Zbase = BASE_Impedance;
//    pPI_Ig_Loop->wbase = BASE_AngularFreq;
    pPI_Ig_Loop->Ts = stSysNormalValue.SampTime;
    pPI_Ig_Loop->Tsbase = 0.0002;
    pPI_Ig_Loop->Ts_pu = pPI_Ig_Loop->Ts / pPI_Ig_Loop->Tsbase;
    //--------------------------标幺值计算-------------------------------
    pPI_Ig_Loop->PI_IgD_Loop_pu.Kp = PI_IgD_Loop.Kp / pPI_Ig_Loop->Zbase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.Ki = PI_IgD_Loop.Ki / pPI_Ig_Loop->Zbase * pPI_Ig_Loop->Ts_pu;
    pPI_Ig_Loop->PI_IgD_Loop_pu.ErrUpLimt = PI_IgD_Loop.ErrUpLimt / pPI_Ig_Loop->Ibase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.ErrDnLimt = PI_IgD_Loop.ErrDnLimt / pPI_Ig_Loop->Ibase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.IOutUpLimt = PI_IgD_Loop.IOutUpLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.IOutDnLimt = PI_IgD_Loop.IOutDnLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.PIOutUpLimt = PI_IgD_Loop.PIOutUpLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgD_Loop_pu.PIOutDnLimt = PI_IgD_Loop.PIOutDnLimt / pPI_Ig_Loop->Vbase;

    pPI_Ig_Loop->PI_IgQ_Loop_pu.Kp = PI_IgQ_Loop.Kp / pPI_Ig_Loop->Zbase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.Ki = PI_IgQ_Loop.Ki / pPI_Ig_Loop->Zbase * pPI_Ig_Loop->Ts_pu;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.ErrUpLimt = PI_IgQ_Loop.ErrUpLimt / pPI_Ig_Loop->Ibase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.ErrDnLimt = PI_IgQ_Loop.ErrDnLimt / pPI_Ig_Loop->Ibase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.IOutUpLimt = PI_IgQ_Loop.IOutUpLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.IOutDnLimt = PI_IgQ_Loop.IOutDnLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.PIOutUpLimt = PI_IgQ_Loop.PIOutUpLimt / pPI_Ig_Loop->Vbase;
    pPI_Ig_Loop->PI_IgQ_Loop_pu.PIOutDnLimt = PI_IgQ_Loop.PIOutDnLimt / pPI_Ig_Loop->Vbase;
}

CTRL_ISR_EXT void Ctrl_ISR_Init(void)
{

    stSysNormalValue.SampTime = 0.0002;

    LoadPiDefaultPara(0);

    PI_LoopPara_Init();

    Current_PR_Para_Init();

    stPWMdrive.DelayTime = 5.0;
    stPWMdrive.Pwm_Prd   = 31250;
    stPWMdrive.Vdc_Normalize   = 1;
    stPWMdrive.ClearFlag = 1;

    Spll_1ph_init(50.0,stSysNormalValue.SampTime,&stPLL_DSOGI);

    stVg_DSOGI.osg_k    = 0.914;//0.707,0.2，0.35
    stVg_DSOGI.wn       = PI2 * (float32)GRID_FREQ_SET;
    stVg_DSOGI.delta_T  = stSysNormalValue.SampTime;
    DSOGI_TYPE_Init(&stVg_DSOGI);

    stVgQ_2th.Q = 1.414;
    stVgQ_2th.wo = PI2 * (float32)GRID_FREQ_SET * 2.0;
    stVgQ_2th.wo_Ts = stVgQ_2th.wo * stSysNormalValue.SampTime;
    Notch_Filter_init(&stVgQ_2th);

    Vg_D_LPF.Omiga_Ts  = PI2 * 60.0 * stSysNormalValue.SampTime;
    LPF_Init(&Vg_D_LPF);

    Vg_Q_LPF.Omiga_Ts  = PI2 * 60.0 * stSysNormalValue.SampTime;
    LPF_Init(&Vg_Q_LPF);

    vUdc_unbalance_loop_para_initial(&stPI_Udc_unbalance);//半母线均压
    SOC_Balance_loop_para_initial(&stPI_SOC_unbalance);   //SOC均衡控制
    Base_Values_initial(&PI_Ig_Loop); //标幺基准初始化
}

/****************************************************清除DQ环路变量部分*****************************************************/

/**
* @brief      Control_Loop_Init
* @details    停机时环路控制参XX清零及更新
* @param[in]  void
* @param[out] void
* @return
*/
CTRL_ISR_EXT void PI_Clear(PI_DATA_TYPE *pstPiCtr)
{
    pstPiCtr->Err    = 0;
    pstPiCtr->IOut   = 0;
    pstPiCtr->PIOut  = 0;

}

CTRL_ISR_EXT void PR_Clear(PR_TYPE *p)
{

    p->input[0]  = 0;
    p->input[1]  = 0;
    p->input[2]  = 0;

    p->output[0] = 0;
    p->output[1] = 0;
    p->output[2] = 0;
}

CTRL_ISR_EXT  void Control_Loop_Init()
{

    stPWMdrive.DelayTime = 5.0;
    stPWMdrive.Dr = 0;
    stPWMdrive.Qr = 0;
    stPWMdrive.As = 0;//stPWMdrive.Pwm_Prd;
    stPWMdrive.Bs = 0;//stPWMdrive.Pwm_Prd;
    stPWMdrive.Cs = 0;//stPWMdrive.Pwm_Prd;
    stPWMdrive.Ns = 0;

    if (stPWMdrive.ClearFlag ==1)
    {
        stPWMdrive.ClearFlag = 0;
        PI_Clear(&PI_IgD_Loop);
        PI_Clear(&PI_IgQ_Loop);

        PR_Clear(&Ig_D_PR2);
        PR_Clear(&Ig_D_PR4);
        PR_Clear(&Ig_D_PR6);
        PR_Clear(&Ig_D_PR10);

        PR_Clear(&Ig_Q_PR2);
        PR_Clear(&Ig_Q_PR4);
        PR_Clear(&Ig_Q_PR6);
        PR_Clear(&Ig_Q_PR10);

    }

}

/*********************************************************************************************************/
/*********************************************************************************************************/



