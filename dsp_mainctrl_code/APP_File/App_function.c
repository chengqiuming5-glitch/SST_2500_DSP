//==============================================================================================
//    File description
//==============================================================================================
/**@file         App_fuction.c
 * @brief
 * The source file of App_fuction is to design global function for app.
 *
 * Module      :                 \n
 * AppInit
 *
 * Unit        :                 \n
 * null
 *
 * Unit Task   :                 \n
 * v_AppInit()                   \n
 * ServiceDog()                  \n
 * v_ComDrv_Rx()                 \n
 * v_Com_Rx()                    \n
 * v_ComDrv_TxOkFlg()            \n
 * v_Com_Tx()                    \n
 * v_ComDrv_Tx()                 \n
 * v_PerdTsk_MainLoop()          \n
 *
 * Unit Task   :                 \n
 * null
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2025/08/21
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
 * <tr><td>2025/08/21  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#if (!defined _D2D_LIB_PRJ_)

//=====================================================
//    Include Header Files
//=====================================================
#include "App.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/**
* @brief   first order LPF function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_1stOrdLPF(float32 *pftValOut, float32 ftValIn, float32 ftCoeffLpf)
{
    *pftValOut = ftCoeffLpf * (*pftValOut) + (1.0f - ftCoeffLpf) * ftValIn;
}

/**
* @brief   float up down limitation function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_FtUpDwnLim(float32 *pftValOut, float32 ftValUp, float32 ftValDwn)
{
#if 1
    *pftValOut = ((*pftValOut) < ftValUp) ? (*pftValOut) : ftValUp;
    *pftValOut = ((*pftValOut) > ftValDwn) ? (*pftValOut) : ftValDwn;
#else
    if(*pftValOut > ftValUp)
    {
        *pftValOut = ftValUp;
    }
    else if(*pftValOut < ftValDwn)
    {
        *pftValOut = ftValDwn;
    }
    else
    {
        ///< No code
    }
#endif
}

#if (!defined _PFC_LIB_PRJ_)
/**
* @brief   Unit16 up down limitation function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_UiUpDwnLim(Uint16 *puiValOut, Uint16 uiValUp, Uint16 uiValDwn)
{
#if 1
    *puiValOut = ((*puiValOut) < uiValUp) ? (*puiValOut) : uiValUp;
    *puiValOut = ((*puiValOut) > uiValDwn) ? (*puiValOut) : uiValDwn;
#else
    if(*puiValOut > uiValUp)
    {
        *puiValOut = uiValUp;
    }
    else if(*puiValOut < uiValDwn)
    {
        *puiValOut = uiValDwn;
    }
    else
    {
        ///< No code
    }
#endif
}
#endif

/**
* @brief   Same slope ramp function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_RampSameSlope(float *pftValRef, float ftValTgt, float ftValStep)
{
    if((*pftValRef) - ftValTgt > ftValStep)         ///< The reference value is greater than the target value
    {
        (*pftValRef) -= ftValStep;
    }
    else if(ftValTgt - (*pftValRef) > ftValStep)    ///< The target value is greater than the reference value
    {
        (*pftValRef) += ftValStep;
    }
    else                                            ///< The reference value is equal to the target value
    {
        (*pftValRef) = ftValTgt;
    }
}

/**
* @brief   Un-birdirection different slope ramp function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_UnbidirRampDiffSlope(float *pftValRef, float ftValTgt, float ftValUpStep, float ftValDwnStep)
{
    if((*pftValRef) - ftValTgt > ftValDwnStep)          ///< The reference value is greater than the target value
    {
        (*pftValRef) -= ftValDwnStep;
    }
    else if(ftValTgt - (*pftValRef) > ftValUpStep)      ///< The target value is greater than the reference value
    {
        (*pftValRef) += ftValUpStep;
    }
    else                                                ///< The reference value is equal to the target value
    {
        (*pftValRef) = ftValTgt;
    }
}

#if (!defined _PFC_LIB_PRJ_)
/**
* @brief   Birdirection different slope ramp function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_BidirRampDiffSlope(float *pftValRef, float ftValTgt, float ftValUpStep, float ftValDwnStep)
{
    if((*pftValRef) > 0.0f)    ///< Positive reference
    {
        vFcn_UnbidirRampDiffSlope(&(*pftValRef), ftValTgt, ftValUpStep, ftValDwnStep);
    }
    else    ///< Negative reference
    {
        vFcn_UnbidirRampDiffSlope(&(*pftValRef), ftValTgt, ftValDwnStep, ftValUpStep);
    }
}
#endif

/**
* @brief   Initialize PI parameter function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_InitPIPrm(ST_PI_PRM *pstPIPrm)
{
    (*pstPIPrm).ftInp    = 0.0f;        ///< Initialize to 0.0f
    (*pstPIPrm).ftIntgl  = 0.0f;        ///< Initialize to 0.0f
    (*pstPIPrm).ftOutp   = 0.0f;        ///< Initialize to 0.0f
    (*pstPIPrm).ftInpPre = 0.0f;        ///< Initialize to 0.0f
}

#if (!defined _PFC_LIB_PRJ_)
/**
* @brief   Position PI control function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_PosnPICtrl(ST_PI_PRM *pstPIPrm)
{
    (*pstPIPrm).ftIntgl += (*pstPIPrm).ftInp * (*pstPIPrm).ftKi;
    /* Integral limitation */
    if((*pstPIPrm).ftIntgl > (*pstPIPrm).ftOutpMax)
    {
        (*pstPIPrm).ftIntgl = (*pstPIPrm).ftOutpMax;
    }
    else if((*pstPIPrm).ftIntgl < (*pstPIPrm).ftOutpMin)
    {
        (*pstPIPrm).ftIntgl = (*pstPIPrm).ftOutpMin;
    }
    else
    {
        ///< No code
    }

    (*pstPIPrm).ftOutp = (*pstPIPrm).ftInp * (*pstPIPrm).ftKp + (*pstPIPrm).ftIntgl;
    /* Output limitation */
    if((*pstPIPrm).ftOutp > (*pstPIPrm).ftOutpMax)
    {
        (*pstPIPrm).ftOutp = (*pstPIPrm).ftOutpMax;
    }
    else if((*pstPIPrm).ftOutp < (*pstPIPrm).ftOutpMin)
    {
        (*pstPIPrm).ftOutp = (*pstPIPrm).ftOutpMin;
    }
    else
    {
        ///< No code
    }
}
#endif

/**
* @brief   Incremental PI control function
* @param [in]  null
* @param [out] null
* @return null
*/
void vFcn_IncPICtrl(ST_PI_PRM *pstPIPrm)
{
    (*pstPIPrm).ftOutp = (*pstPIPrm).ftOutp + (*pstPIPrm).ftInp * (*pstPIPrm).ftKp +  (*pstPIPrm).ftInp * (*pstPIPrm).ftKi \
                            - (*pstPIPrm).ftInpPre * (*pstPIPrm).ftKp;

    /* Output limitation */
    if((*pstPIPrm).ftOutp > (*pstPIPrm).ftOutpMax)
    {
        (*pstPIPrm).ftOutp  = (*pstPIPrm).ftOutpMax;
    }
    else if((*pstPIPrm).ftOutp < (*pstPIPrm).ftOutpMin)
    {
        (*pstPIPrm).ftOutp = (*pstPIPrm).ftOutpMin;
    }
    else
    {
        ///< No code
    }

    /* Record input */
    (*pstPIPrm).ftInpPre = (*pstPIPrm).ftInp;
}

#if (!defined _PFC_LIB_PRJ_)
/**
* @brief   Max of two function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MaxOfTwo(float32 ftValA, float32 ftValB)
{
#if 1
    return ((ftValA > ftValB) ? ftValA : ftValB);
#else
    float32 l_ftTmp = 0.0f;

    if(ftValA > ftValB)
    {
        l_ftTmp = ftValA;
    }
    else
    {
        l_ftTmp = ftValB;
    }

    return l_ftTmp;
#endif
}

/**
* @brief   Min of two function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MinOfTwo(float32 ftValA, float32 ftValB)
{
#if 1
    return ((ftValA < ftValB) ? ftValA : ftValB);
#else
    float32 l_ftTmp = 0.0f;

    if(ftValA < ftValB)
    {
        l_ftTmp = ftValA;
    }
    else
    {
        l_ftTmp = ftValB;
    }

    return l_ftTmp;
#endif
}

/**
* @brief   Max of three function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MaxOfThree(float32 ftValA, float32 ftValB, float32 ftValC)
{
    return (((ftFcn_MaxOfTwo(ftValA, ftValB)) > (ftValC)) ? (ftFcn_MaxOfTwo(ftValA, ftValB)) : ftValC);
}

/**
* @brief   Min of three function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MinOfThree(float32 ftValA, float32 ftValB, float32 ftValC)
{
    return (((ftFcn_MinOfTwo(ftValA, ftValB)) < (ftValC)) ? (ftFcn_MinOfTwo(ftValA, ftValB)) : ftValC);
}

/**
* @brief   Max of four function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MaxOfFour(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD)
{
    return (((ftFcn_MaxOfThree(ftValA, ftValB, ftValC)) > (ftValD)) ? (ftFcn_MaxOfThree(ftValA, ftValB, ftValC)) : ftValD);
}

/**
* @brief   Min of four function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MinOfFour(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD)
{
    return (((ftFcn_MinOfThree(ftValA, ftValB, ftValC)) < (ftValD)) ? (ftFcn_MinOfThree(ftValA, ftValB, ftValC)) : ftValD);
}

/**
* @brief   Max of five function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MaxOfFive(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD, float32 ftValE)
{
    return (((ftFcn_MaxOfFour(ftValA, ftValB, ftValC, ftValD)) > (ftValE)) ? (ftFcn_MaxOfFour(ftValA, ftValB, ftValC, ftValD)) : ftValE);
}

/**
* @brief   Min of five function
* @param [in]  null
* @param [out] null
* @return null
*/
float32 ftFcn_MinOfFive(float32 ftValA, float32 ftValB, float32 ftValC, float32 ftValD, float32 ftValE)
{
    return (((ftFcn_MinOfFour(ftValA, ftValB, ftValC, ftValD)) < (ftValE)) ? (ftFcn_MinOfFour(ftValA, ftValB, ftValC, ftValD)) : ftValE);
}
#endif
#endif    // (!defined _PFC_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
