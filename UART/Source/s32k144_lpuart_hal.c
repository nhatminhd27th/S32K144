/**
 * @file s32k144_lpuart_hal.h
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This is the definition file of the Hardware Abstraction Layer for LPUAR module of S32K144 MCU.
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */
/****************************************************************************************************************
 *                                                 INCLUSIONS                                                   *
 ****************************************************************************************************************/
#include "s32k144_lpuart_hal.h"

/****************************************************************************************************************
 *                                              API DEFINITIONS                                                 *
 ****************************************************************************************************************/
/**
 * @brief This function is used to configure the frame length of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param frameLength[in]: frame length to set
 *
 * @return void
 */
void HAL_LPUART_FrameLengthConfig(LPUART_Type *pLPUARTx, LPUART_FrameLength_Type frameLength)
{
    switch (frameLength)
    {
        case FRAME_7BITS:
            pLPUARTx->CTRL |= LPUART_CTRL_M7_MASK;
            pLPUARTx->CTRL &= ~LPUART_CTRL_M_MASK;
            pLPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            break;
        case FRAME_8BITS:
            pLPUARTx->CTRL &= ~LPUART_CTRL_M7_MASK;
            pLPUARTx->CTRL &= ~LPUART_CTRL_M_MASK;
            pLPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            break;
        case FRAME_9BITS:
            pLPUARTx->CTRL &= ~LPUART_CTRL_M7_MASK;
            pLPUARTx->CTRL |= LPUART_CTRL_M_MASK;
            pLPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            break;
        case FRAME_10BITS:
            pLPUARTx->CTRL &= ~LPUART_CTRL_M7_MASK;
            pLPUARTx->CTRL &= ~LPUART_CTRL_M_MASK;
            pLPUARTx->BAUD |= LPUART_BAUD_M10_MASK;
            break;
    }
}

/**
 * @brief This function is used to configure the parity mode of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param mode[in]: parity mode to set
 *
 * @return void
 */
void HAL_LPUART_ParityConfig(LPUART_Type *pLPUARTx, LPUART_ParityMode_Type mode)
{
    if(NONE == mode)
    {
        pLPUARTx->CTRL &= ~LPUART_CTRL_PE_MASK;
    }
    else
    {
        pLPUARTx->CTRL |= LPUART_CTRL_PE_MASK;

        if(EVEN == mode)
        {
            pLPUARTx->CTRL &= ~LPUART_CTRL_PT_MASK;
        }
        else
        {
            pLPUARTx->CTRL |= LPUART_CTRL_PT_MASK;
        }
    }
}

/**
 * @brief This function is used to configure the Tx data inversion of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxDataInversionConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_TXINV_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_TXINV(enable);
}

/**
 * @brief This function is used to configure the Rx data inversion of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_RxDataInversionConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_STAT_RXINV_MASK;
    pLPUARTx->CTRL |= LPUART_STAT_RXINV(enable);
}


/**
 * @brief This function is used to configure the number of stop bits of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param nOfStopBits[in]: number of stop bits to set
 *
 * @return void
 */
void HAL_LPUART_SetNumOfStopBit(LPUART_Type *pLPUARTx, uint8_t nOfStopBits)
{
    pLPUARTx->BAUD &= ~LPUART_BAUD_SBNS_MASK;
    pLPUARTx->BAUD |= LPUART_BAUD_SBNS(nOfStopBits);
}

/**
 * @brief This function is used to configure the most significant bit first of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param lsbMsbFirst[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_MSBFConfig(LPUART_Type *pLPUARTx, uint8_t lsbMsbFirst)
{
    pLPUARTx->CTRL &= ~LPUART_STAT_MSBF_MASK;
    pLPUARTx->CTRL |= LPUART_STAT_MSBF(lsbMsbFirst);
}

/**
 * @brief This function is used to enable the transmitter of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_SetTE(LPUART_Type *pLPUARTx)
{
    pLPUARTx->CTRL |= LPUART_CTRL_TE_MASK;
}

/**
 * @brief This function is used to disable the transmitter of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_ClearTE(LPUART_Type *pLPUARTx)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_TE_MASK;
}

/**
 * @brief This function is used to enable the receiver of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_SetRE(LPUART_Type *pLPUARTx)
{
    pLPUARTx->CTRL |= LPUART_CTRL_RE_MASK;
}

/**
 * @brief This function is used to disable the receiver of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_ClearRE(LPUART_Type *pLPUARTx)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_RE_MASK;
}

/**
 * @brief This function is used to configure the baudrate of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param OSRVal[in]: oversampling ratio value
 * @param SBRVal[in]: baudrate value
 *
 * @return void
 */
void HAL_LPUART_SetBaudrate(LPUART_Type *pLPUARTx, uint8_t OSRVal, uint16_t SBRVal)
{
    pLPUARTx->BAUD = (pLPUARTx->BAUD & ~(LPUART_BAUD_OSR_MASK | LPUART_BAUD_SBR_MASK)) | LPUART_BAUD_OSR(OSRVal) | LPUART_BAUD_SBR(SBRVal);
}

/**
 * @brief This function is used to send a frame of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return void
 */
void HAL_LPUART_TxFrame7_8(LPUART_Type *pLPUARTx, uint8_t data)
{
    while(!(pLPUARTx->STAT & LPUART_STAT_TDRE_MASK))
    {
        /* Do nothing */
    }

    pLPUARTx->DATA |= data;

    while(!(pLPUARTx->STAT & LPUART_STAT_TC_MASK))
    {
        /* Do nothing */
    }
}

/**
 * @brief This function is used to send a frame of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return void
 */
void HAL_LPUART_TxFrame9_10(LPUART_Type *pLPUARTx, uint16_t data)
{
    while(!(pLPUARTx->STAT & LPUART_STAT_TDRE_MASK))
    {
        /* Do nothing */
    }

    pLPUARTx->DATA |= data;

    while(!(pLPUARTx->STAT & LPUART_STAT_TC_MASK))
    {
        /* Do nothing */
    }
}

/**
 * @brief This function is used to receive a frame
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return uint16_t: received data
 */
uint16_t HAL_LPUART_RxFrame(LPUART_Type *pLPUARTx)
{
    while(!(pLPUARTx->STAT & LPUART_STAT_RDRF_MASK))
    {
        /* Do nothing */
    }

    return pLPUARTx->DATA;
}

/**
 * @brief This function is used to configure the LPUART Tx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_TIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_TIE(enable);
}

/**
 * @brief This function is used to configure the LPUART Tx complete interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxCompleteInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_TCIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_TCIE(enable);
}

/**
 * @brief This function is used to configure the LPUART Rx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_RxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_RIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_RIE(enable);
}

/**
 * @brief This function is used to configure the LPUART OverRun interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_OverRunInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_ORIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_ORIE(enable);
}

/**
 * @brief This function is used to configure the LPUART Noise error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_NoiseErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_NEIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_NEIE(enable);
}

/**
 * @brief This function is used to configure the LPUART Frame error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_FrameErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_FEIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_FEIE(enable);
}

/**
 * @brief This function is used to configure the LPUART Parity error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_ParityErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    pLPUARTx->CTRL &= ~LPUART_CTRL_PEIE_MASK;
    pLPUARTx->CTRL |= LPUART_CTRL_PEIE(enable);
}

/**
 * @brief This function is used to de-initialize the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_DeInit(LPUART_Type *pLPUARTx)
{
    pLPUARTx->GLOBAL |= LPUART_GLOBAL_RST_MASK;
    pLPUARTx->GLOBAL &= ~LPUART_GLOBAL_RST_MASK;
}
