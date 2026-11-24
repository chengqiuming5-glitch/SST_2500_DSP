//==============================================================================================
//    File description
//==============================================================================================
/**@file         EmifExt.h
 * @brief
 * The header file of EmifExt is designed to realize Emif communication.
 *
 * Module      :                       \n
 *
 *
 * Module Task :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
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
 * <tr><td>2025/11/27  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#ifndef EMIFExt_H_
#define EMIFExt_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define EMIF_DBG                 0U              ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef union
{
    Uint16 all;
    struct
    {
        Uint16 uiPu1ChbPwm:1;   /*CHB PWM使能标志,1为使能*/
        Uint16 uiPu1DabFPwm:1;  /*DAB前级PWM输出状态,1为使能*/
        Uint16 uiPu1DabBPwm:1;  /*DAB后级PWM输出状态,1为使能*/
        Uint16 uiPu1Fault:1;    /*功率单元故障标志,1为出现故障*/

        Uint16 uiPu2ChbPwm:1;
        Uint16 uiPu2DabFPwm:1;
        Uint16 uiPu2DabBPwm:1;
        Uint16 uiPu2Fault:1;

        Uint16 uiPu3ChbPwm:1;
        Uint16 uiPu3DabFPwm:1;
        Uint16 uiPu3DabBPwm:1;
        Uint16 uiPu3Fault:1;

        Uint16 uiPu4ChbPwm:1;
        Uint16 uiPu4DabFPwm:1;
        Uint16 uiPu4DabBPwm:1;
        Uint16 uiPu4Fault:1;
    };
}PU_STA1;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 uiPu5ChbPwm:1;
        Uint16 uiPu5DabFPwm:1;
        Uint16 uiPu5DabBPwm:1;
        Uint16 uiPu5Fault:1;

        Uint16 uiPu6ChbPwm:1;
        Uint16 uiPu6DabFPwm:1;
        Uint16 uiPu6DabBPwm:1;
        Uint16 uiPu6Fault:1;

        Uint16 uiPu7ChbPwm:1;
        Uint16 uiPu7DabFPwm:1;
        Uint16 uiPu7DabBPwm:1;
        Uint16 uiPu7Fault:1;

        Uint16 uiPu8ChbPwm:1;
        Uint16 uiPu8DabFPwm:1;
        Uint16 uiPu8DabBPwm:1;
        Uint16 uiPu8Fault:1;
    };
}PU_STA2;

typedef  struct
{
    Uint16  uiFrameHead; ///<FrameHead 0x5555
    PU_STA1 unRunStateA1_4; ///<Phase A Run State1
    PU_STA2 unRunStateA5_6; ///<Phase A Run State2
    PU_STA1 unRunStateB1_4;
    PU_STA2 unRunStateB5_6;
    PU_STA1 unRunStateC1_4;
    PU_STA2 unRunStateC5_6;
    Uint16  uiRedunStateA1;///<Phase A Redundant State1
    Uint16  uiRedunStateB1;
    Uint16  uiRedunStateC1;
    Uint16  uiPollAddr;  ///<Polling address
    int16   siPollData;   ///<Polling data
    int16   siVbusUpA[6]; ///<Phase A up half Vbus
    int16   siVbusUpB[6];
    int16   siVbusUpC[6];
    int16   siVbusDnA[6];///<Phase A down half Vbus
    int16   siVbusDnB[6];
    int16   siVbusDnC[6];
    int16   siFltSaveA; ///<Fpga save Phase A fault
    int16   siFltSaveB; ///<Fpga save Phase B fault
    int16   siFltSaveC; ///<Fpga save Phase C fault
    int16   siResv[12];
    Uint16  uiCheckSum;
}ST_EMIF_DMA;


typedef struct
{
    int16 siFltChbCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压功率单元故障
    int16 siVoltChbCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< CHB电压
    int16 siCurrDabCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< dab电流
    int16 siVerFpgaCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL]; //NUM_PHA_POW_CELL   ///< Cell FPGA version
    int16 siFltDabCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压功率单元故障
    int16 siResCurCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 谐振电流
    int16 siVoltDabCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< dab电压
    int16 siTemp1HvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压温度1
    int16 siTemp2HvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压温度2
    int16 siTemp1LvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压温度1
    int16 siTemp2LvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压温度2
    int16 siErrFiberCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 辅控光纤误码率
    int16 siErrHvUpFiberCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压上行光纤误码率
    int16 siErrHvDownFiberCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压下行光纤误码率
    int16 siErrLvFiberCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压光纤误码率
    int16 siStateFanCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 风扇状态
    int16 siTemp3HvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压温度3
    int16 siTemp4HvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压温度4
    int16 siTemp5HvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 高压温度5
    int16 siTemp3LvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压温度3
    int16 siTemp4LvCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 低压温度4
    int16 siRfValCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< 谐振频率统计值
}ST_EMIF;

typedef struct
{
    int16 siFpgaVersion1;
    int16 siFpgaVersion2;
    int16 siFpgaVersion3;

}ST_EMIF_DMA_DATA;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
extern ST_EMIF_DMA stEmifDma1;
extern ST_EMIF_DMA stEmifDma1Raw;
extern ST_EMIF_DMA_DATA stEmifDmaPollData;
//extern ST_EMIF_DMA stEmifDma2;
extern ST_EMIF     stEmif;
#endif /* EMIFExt_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
