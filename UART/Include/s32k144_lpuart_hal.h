/**
 * @file s32k144_lpuart_hal.h
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This is the header file of the Hardware Abstraction Layer for LPUAR module of S32K144 MCU.
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef S32K144_LPUART_HAL_H
#define S32K144_LPUART_HAL_H

/****************************************************************************************************************
 *                                                 INCLUSIONS                                                   *
 ****************************************************************************************************************/
#include "S32K144.h"

/****************************************************************************************************************
 *                                              TYPE DEFINITIONS                                                *
 ****************************************************************************************************************/
typedef enum
{
    EVEN,   /* Parity bit is set such that the number of 1s in the data is even */
    ODD,    /* Parity bit is set such that the number of 1s in the data is odd */
    NONE,   /* No parity bit is used */
} LPUART_ParityMode_Type;   /* Parity mode */

typedef enum
{
    FRAME_7BITS,    /* 7-bit data frame */
    FRAME_8BITS,    /* 8-bit data frame */
    FRAME_9BITS,    /* 9-bit data frame */
    FRAME_10BITS,   /* 10-bit data frame */
} LPUART_FrameLength_Type;  /* Data frame length */

/****************************************************************************************************************
 *                                              API DECLARATIONS                                                *
 ****************************************************************************************************************/
/**
 * @name HAL_LPUART_FrameLengthConfig
 *
 * @brief This function is used to configure the frame length of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param frameLength[in]: frame length to set
 *
 * @return void
 */
void HAL_LPUART_FrameLengthConfig(LPUART_Type *pLPUARTx, LPUART_FrameLength_Type frameLength);

/**
 * @name HAL_LPUART_ParityConfig
 *
 * @brief This function is used to configure the parity mode of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param mode[in]: parity mode to set
 *
 * @return void
 */
void HAL_LPUART_ParityConfig(LPUART_Type *pLPUARTx, LPUART_ParityMode_Type mode);

/**
 * @name HAL_LPUART_TxDataInversionConfig
 *
 * @brief This function is used to configure the Tx data inversion of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxDataInversionConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_RxDataInversion
 *
 * @brief This function is used to configure the Rx data inversion of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_RxDataInversionConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_SetNumOfStopBit
 *
 * @brief This function is used to configure the number of stop bits of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param nOfStopBits[in]: number of stop bits to set
 *
 * @return void
 */
void HAL_LPUART_SetNumOfStopBit(LPUART_Type *pLPUARTx, uint8_t nOfStopBits);

/**
 * @name HAL_LPUART_MSBFConfig
 *
 * @brief This function is used to configure the most significant bit first of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param lsbMsbFirst[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_MSBFConfig(LPUART_Type *pLPUARTx, uint8_t lsbMsbFirst);

/**
 * @name HAL_LPUART_SetTE
 *
 * @brief This function is used to enable the transmitter of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_SetTE(LPUART_Type *pLPUARTx);

/**
 * @name HAL_LPUART_ClearTE
 *
 * @brief This function is used to disable the transmitter of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_ClearTE(LPUART_Type *pLPUARTx);

/**
 * @name HAL_LPUART_SetRE
 *
 * @brief This function is used to enable the receiver of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_SetRE(LPUART_Type *pLPUARTx);

/**
 * @name HAL_LPUART_ClearRE
 *
 * @brief This function is used to disable the receiver of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_ClearRE(LPUART_Type *pLPUARTx);

/**
 * @name HAL_LPUART_SetBaudrate
 *
 * @brief This function is used to set the baudrate of the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param OSRVal[in]: oversampling ratio value
 * @param SBRVal[in]: baudrate value
 *
 * @return void
 */
void HAL_LPUART_SetBaudrate(LPUART_Type *pLPUARTx, uint8_t OSRVal, uint16_t SBRVal);

/**
 * @name HAL_LPUART_TxFrame7_8
 *
 * @brief This function is used to send a frame of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return void
 */
void HAL_LPUART_TxFrame7_8(LPUART_Type *pLPUARTx, uint8_t data);

/**
 * @name HAL_LPUART_TxFrame9_10
 *
 * @brief This function is used to send a frame of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return void
 */
void HAL_LPUART_TxFrame9_10(LPUART_Type *pLPUARTx, uint16_t data);

/**
 * @name HAL_LPUART_RxFrame
 *
 * @brief This function is used to receive a frame
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return uint16_t: received data
 */
uint16_t HAL_LPUART_RxFrame(LPUART_Type *pLPUARTx);

/**
 * @name HAL_LPUART_TxInterruptConfig
 *
 * @brief This function is used to configure the LPUART Tx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_TxCompleteInterruptConfig
 *
 * @brief This function is used to configure the LPUART Tx complete interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_TxCompleteInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_RxInterruptConfig
 *
 * @brief This function is used to configure the LPUART Rx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_RxInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_OverRunInterruptConfig
 *
 * @brief This function is used to configure the LPUART OverRun interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_OverRunInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_NoiseErrorInterruptConfig
 *
 * @brief This function is used to configure the LPUART Noise error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_NoiseErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_FrameErrorInterruptConfig
 *
 * @brief This function is used to configure the LPUART Frame error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_FrameErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_ParityErrorInterruptConfig
 *
 * @brief This function is used to configure the LPUART Parity error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return void
 */
void HAL_LPUART_ParityErrorInterruptConfig(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name HAL_LPUART_DeInit
 *
 * @brief This function is used to de-initialize the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return void
 */
void HAL_LPUART_DeInit(LPUART_Type *pLPUARTx);

#endif /* S32K144_LPUART_HAL_H */
