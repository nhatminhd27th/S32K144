/**
 * @file s32k144_lpuart_driver.c
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This is the definition file of the driver for LPUAR module of S32K144 MCU.
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */
/****************************************************************************************************************
 *                                                 INCLUSIONS                                                   *
 ****************************************************************************************************************/
#include "s32k144_lpuart_driver.h"

/****************************************************************************************************************
 *                                                   MACROS                                                     *
 ****************************************************************************************************************/
#define MAX_BAUDRATE    (clock / 4) /* Maximum baudrate */

#define INSTANCE_IS_AVAILABLE(Instance) ((Instance == LPUART0) || (Instance == LPUART1) || (Instance == LPUART2))   /* Check if the instance is available */

/****************************************************************************************************************
 *                                              GLOBAL VARIABLES                                                *
 ****************************************************************************************************************/
LPUART_CallbackPtr LPUART_Callback[3] = {0};    /* Array of callback functions */

/****************************************************************************************************************
 *                                         STATIC FUNCTIONS DECLARATIONS                                        *
 ****************************************************************************************************************/
/**
 * @name LPUART_CheckHandleValidation
 *
 * @brief This function is used to check the validation of the handle
 *
 * @param pLPUARTHandle[in]: pointer to the LPUART handle
 *
 * @return Std_LPUART_Status: status of the operation
 */
static Std_LPUART_Status LPUART_CheckHandleValidation(LPUART_Handle_Type *pLPUARTHandle);

/****************************************************************************************************************
 *                                         STATIC FUNCTIONS DEFINITIONS                                         *
 ****************************************************************************************************************/
/**
 * @brief This function is used to check the validation of the handle
 *
 * @param pLPUARTHandle[in]: pointer to the LPUART handle
 *
 * @return Std_LPUART_Status: status of the operation
 */
static Std_LPUART_Status LPUART_CheckHandleValidation(LPUART_Handle_Type *pLPUARTHandle)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if( INSTANCE_IS_AVAILABLE(pLPUARTHandle->pLPUARTx) &&
        (LPUART_FRAME_7BITS <= pLPUARTHandle->LPUART_Config.frameLenth) &&
        (LPUART_FRAME_10BITS >= pLPUARTHandle->LPUART_Config.frameLenth) &&
        (LPUART_PARITY_DISABLE >= pLPUARTHandle->LPUART_Config.parityMode) &&
        ((LPUART_STOP_BITS_1 == pLPUARTHandle->LPUART_Config.nOfStopBits) ||
        (LPUART_STOP_BITS_2 == pLPUARTHandle->LPUART_Config.nOfStopBits)) &&
        ((LPUART_MSB_FIRST == pLPUARTHandle->LPUART_Config.msbFirst) ||
        (LPUART_LSB_FIRST == pLPUARTHandle->LPUART_Config.msbFirst)) &&
        ((LPUART_TX_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.txInterrupt) ||
        (LPUART_TX_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.txInterrupt)) &&
        ((LPUART_RX_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.rxInterrupt) ||
        (LPUART_RX_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.rxInterrupt)) &&
        ((LPUART_TX_COMPLETE_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.txCompleteInterrupt) ||
        (LPUART_TX_COMPLETE_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.txCompleteInterrupt)) &&
        ((LPUART_OVERRUN_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.overRunInterrupt) ||
        (LPUART_OVERRUN_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.overRunInterrupt)) &&
        ((LPUART_NOISE_ERROR_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.noiseErrorInterrupt) ||
        (LPUART_NOISE_ERROR_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.noiseErrorInterrupt)) &&
        ((LPUART_FRAME_ERROR_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.frameErrorInterrupt) ||
        (LPUART_FRAME_ERROR_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.frameErrorInterrupt)) &&
        ((LPUART_PARITY_ERROR_INTERRUPT_DISABLE == pLPUARTHandle->LPUART_Config.parityErrorInterrupt) ||
        (LPUART_PARITY_ERROR_INTERRUPT_ENABLE == pLPUARTHandle->LPUART_Config.parityErrorInterrupt)) &&
        ((LPUART_TX_DATA_INVERSION_DISABLE == pLPUARTHandle->LPUART_Config.txPolarity) ||
        (LPUART_TX_DATA_INVERSION_ENABLE == pLPUARTHandle->LPUART_Config.txPolarity)) &&
        ((LPUART_RX_DATA_INVERSION_DISABLE == pLPUARTHandle->LPUART_Config.rxPolarity) ||
        (LPUART_RX_DATA_INVERSION_ENABLE == pLPUARTHandle->LPUART_Config.rxPolarity)) &&
        (0 < pLPUARTHandle->LPUART_Config.baudRate) &&
        (MAX_BAUDRATE >= pLPUARTHandle->LPUART_Config.baudRate) )
    {
        status = LPUART_E_OK;
    }

    return status;
}

/****************************************************************************************************************
 *                                              API DEFINITIONS                                                 *
 ****************************************************************************************************************/
/**
 * @brief This function is used to initialize the LPUART
 *
 * @param pLPUARTHandle[in/out]: pointer to the LPUART handle
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_Init(LPUART_Handle_Type *pLPUARTHandle)
{

    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(LPUART_E_OK == LPUART_CheckHandleValidation(pLPUARTHandle))
    {
        HAL_LPUART_ClearTE(pLPUARTHandle->pLPUARTx);
        HAL_LPUART_ClearRE(pLPUARTHandle->pLPUARTx);

        HAL_LPUART_FrameLengthConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.frameLenth);

        HAL_LPUART_ParityConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.parityMode);

        HAL_LPUART_TxDataInversionConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.txPolarity);

        HAL_LPUART_RxDataInversionConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.rxPolarity);

        HAL_LPUART_SetNumOfStopBit(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.nOfStopBits);

        HAL_LPUART_MSBFConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.msbFirst);

        LPUART_BaudRateConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.baudRate);

        HAL_LPUART_TxInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.txInterrupt);

        HAL_LPUART_TxCompleteInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.txCompleteInterrupt);

        HAL_LPUART_RxInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.rxInterrupt);

        HAL_LPUART_OverRunInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.overRunInterrupt);

        HAL_LPUART_NoiseErrorInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.noiseErrorInterrupt);

        HAL_LPUART_FrameErrorInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.frameErrorInterrupt);

        HAL_LPUART_ParityErrorInterruptConfig(pLPUARTHandle->pLPUARTx, pLPUARTHandle->LPUART_Config.parityErrorInterrupt);

        HAL_LPUART_SetTE(pLPUARTHandle->pLPUARTx);
        HAL_LPUART_SetRE(pLPUARTHandle->pLPUARTx);

        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to start and stop Transmitter of LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetTxState(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_TxInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to start and stop Receiver of LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetRxState(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_RxInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to calculate and config the baudrate
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param baudRate[in]: baudrate to set, must be less than or equal to MAX_BAUDRATE
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_BaudRateConfig(LPUART_Type *pLPUARTx, uint32_t baudRate)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != baudRate) && (MAX_BAUDRATE >= baudRate))
    {
        float minError = 100;
        volatile uint8_t osrVal = 0;
        volatile uint16_t sbrVal = 0;

        for(uint8_t i = 31; (i >= 3) && (minError != 0); i--)
        {
            uint16_t tmpSBRval = (uint32_t)clock / ((i + 1) * baudRate);
            uint32_t tmpBaudRate = clock / ((i + 1) * tmpSBRval);
            float error = ((float)(tmpBaudRate - baudRate) / baudRate) * 100;

            if(error < minError)
            {
                minError = error;
                osrVal = i;
                sbrVal = tmpSBRval;
            }
        }

        HAL_LPUART_SetBaudrate(pLPUARTx, osrVal, sbrVal);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to send a frame of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxFrame7_8(LPUART_Type *pLPUARTx, uint8_t data)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx))
    {
        HAL_LPUART_TxFrame7_8(pLPUARTx, data);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to send multiple frames of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pTxBuffer[in]: pointer to the data buffer
 * @param len[in]: length of the data buffer
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxMultiFrame7_8(LPUART_Type *pLPUARTx, uint8_t *pTxBuffer, uint32_t len)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != len) && (0 != pTxBuffer))
    {
        for(uint32_t i = 0; i < len; i++)
        {
            HAL_LPUART_TxFrame7_8(pLPUARTx, pTxBuffer[i]);
        }
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to send a frame of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxFrame9_10(LPUART_Type *pLPUARTx, uint16_t data) /* Chuyen qua HAL */
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx))
    {
        HAL_LPUART_TxFrame9_10(pLPUARTx, data);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to send multiple frames of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pTxBuffer[in]: pointer to the data buffer
 * @param len[in]: length of the data buffer
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxMultiFrame9_10(LPUART_Type *pLPUARTx, uint16_t *pTxBuffer, uint32_t len)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != len) && (0 != pTxBuffer))
    {
        for(uint32_t i = 0; i < len; i++)
        {
            HAL_LPUART_TxFrame9_10(pLPUARTx, pTxBuffer[i]);
        }
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to receive a frame
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param RxBuffer[in]: pointer to the buffer to store the received data
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_RxFrame(LPUART_Type *pLPUARTx, uint8_t* RxBuffer)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != RxBuffer))
    {
        *RxBuffer = HAL_LPUART_RxFrame(pLPUARTx);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to receive multiple frames
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pRxBuffer[in]: pointer to the buffer to store the received data
 * @param len[in]: length of the buffer
 *
 * @return uint32_t: number of data received
 */
uint32_t LPUART_RxMultiFrame(LPUART_Type *pLPUARTx, uint16_t *pRxBuffer, uint32_t len)
{
    uint32_t nOfDataRx = 0;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != *pRxBuffer) && (0 != len))
    {
        for(uint32_t nOfDataRx = 0; nOfDataRx < len; nOfDataRx++)
        {
            pRxBuffer[nOfDataRx] = HAL_LPUART_RxFrame(pLPUARTx);
        }
    }

    return nOfDataRx;
}

/**
 * @brief This function is used to configure the LPUART Tx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_TxInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART Tx complete interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxCompleteInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_TxCompleteInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART Rx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_RxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_RxInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART OverRun interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_OverRunInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_OverRunInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART Noise error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_NoiseErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_OverRunInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART Frame error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_FrameErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_FrameErrorInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to configure the LPUART Parity error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_ParityErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && ((0 == enable) || (1 == enable)))
    {
        HAL_LPUART_ParityErrorInterruptConfig(pLPUARTx, enable);
        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to register the callback function for the LPUART interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param IRQHandler[in]: pointer to the callback function
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_CallbackRegister(LPUART_Type *pLPUARTx, LPUART_CallbackPtr IRQHandler)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx) && (0 != IRQHandler))
    {
        if(LPUART0 == pLPUARTx)
        {
            LPUART_Callback[0] = IRQHandler;
        }
        else if(LPUART1 == pLPUARTx)
        {
            LPUART_Callback[1] = IRQHandler;
        }
        else if(LPUART2 == pLPUARTx)
        {
            LPUART_Callback[2] = IRQHandler;
        }
        else
        {
            /* Do nothing */
        }

        status = LPUART_E_OK;
    }

    return status;
}

/**
 * @brief This function is used to de-initialize the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_DeInit(LPUART_Type *pLPUARTx)
{
    Std_LPUART_Status status = LPUART_E_NOT_OK;

    if(INSTANCE_IS_AVAILABLE(pLPUARTx))
    {
        HAL_LPUART_DeInit(pLPUARTx);
        status = LPUART_E_OK;
    }

    return status;
}

/****************************************************************************************************************
 *                                                  IRQ HANDLER                                                 *
 ****************************************************************************************************************/
/**
 * @brief IRQ Handler for LPUART0
 */
void LPUART0_RxTx_IRQHandler(void)
{
    if(0 != LPUART_Callback[0])
    {
        LPUART_Callback[0]();
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief IRQ Handler for LPUART0
 */
void LPUART1_RxTx_IRQHandler(void)
{
    if(0 != LPUART_Callback[1])
    {
        LPUART_Callback[1]();
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief IRQ Handler for LPUART0
 */
void LPUART2_RxTx_IRQHandler(void)
{
    if(0 != LPUART_Callback[2])
    {
        LPUART_Callback[2]();
    }
    else
    {
        /* Do nothing */
    }
}
