/**
 * @file s32k144_lpuart_driver.c
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This is the header file of the driver for LPUAR module of S32K144 MCU.
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef S32K144_LPUART_DRIVER_H
#define S32K144_LPUART_DRIVER_H

/****************************************************************************************************************
 *                                                 INCLUSIONS                                                   *
 ****************************************************************************************************************/
#include "s32k144_lpuart_hal.h"

#define LPUART_FRAME_10BITS (0xA)   /* Frame length is 10 bits */
#define LPUART_FRAME_9BITS  (0x9)   /* Frame length is 9 bits */
#define LPUART_FRAME_8BITS  (0x8)   /* Frame length is 8 bits */
#define LPUART_FRAME_7BITS  (0x7)   /* Frame length is 7 bits */

#define LPUART_PARITY_EVEN      (0x0)   /* Parity type is even */
#define LPUART_PARITY_ODD       (0x1)   /* Parity type is odd */
#define LPUART_PARITY_DISABLE   (0x2)   /* Disable parity */

#define LPUART_STOP_BITS_1 (0x0)    /* Number of stop bit is 1 */
#define LPUART_STOP_BITS_2 (0x1)    /* Number of stop bit is 2 */

#define LPUART_MSB_FIRST (0x0)      /* LSB (bit0) is transmitted first following the start bit, the first bit received after the start bit is identified as bit0. */
#define LPUART_LSB_FIRST (0x1)      /* MSB (bit9, bit8, bit7 or bit6) is the first bit that is transmitted following the start bit */

#define LPUART_TX_INTERRUPT_ENABLE (0x1)    /* Enable Tx interrupt */
#define LPUART_TX_INTERRUPT_DISABLE (0x0)   /* Disable Tx interrupt */

#define LPUART_RX_INTERRUPT_ENABLE (0x1)    /* Enable Rx interrupt */
#define LPUART_RX_INTERRUPT_DISABLE (0x0)   /* Disable Rx interrupt */

#define LPUART_TX_COMPLETE_INTERRUPT_ENABLE (0x1)   /* Enable interrupt when Tx complete */
#define LPUART_TX_COMPLETE_INTERRUPT_DISABLE (0x0)  /* Disable interrupt when Rx complete */

#define LPUART_OVERRUN_INTERRUPT_ENABLE (0x1)   /* Enable overrun interrupt */
#define LPUART_OVERRUN_INTERRUPT_DISABLE (0x0)  /* Disable overrun interrupt */

#define LPUART_NOISE_ERROR_INTERRUPT_ENABLE (0x1)   /* Enable interrupt when noise error happen */
#define LPUART_NOISE_ERROR_INTERRUPT_DISABLE (0x0)  /* Disable interrupt when noise error happen */

#define LPUART_FRAME_ERROR_INTERRUPT_ENABLE (0x1)   /* Enable interrupt when frame error happen */
#define LPUART_FRAME_ERROR_INTERRUPT_DISABLE (0x0)  /* Disable interrupt when frame error happen */

#define LPUART_PARITY_ERROR_INTERRUPT_ENABLE (0x1)  /* Enable interrupt when parity error happen */
#define LPUART_PARITY_ERROR_INTERRUPT_DISABLE (0x0) /* Disable interrupt when parity error happen */

#define LPUART_TX_DATA_INVERSION_ENABLE (0x1)   /* Enable Tx data inversion */
#define LPUART_TX_DATA_INVERSION_DISABLE (0x0)  /* Disable Tx data inversion */

#define LPUART_RX_DATA_INVERSION_ENABLE (0x1)   /* Enable Rx data inversion */
#define LPUART_RX_DATA_INVERSION_DISABLE (0x0)  /* Disable Rx data inversion */

/****************************************************************************************************************
 *                                              GLOBAL VARIABLES                                                *
 ****************************************************************************************************************/
extern uint32_t clock; /* Clock frequency */

/****************************************************************************************************************
 *                                              TYPE DEFINITIONS                                                *
 ****************************************************************************************************************/
typedef enum
{
    LPUART_E_OK,       /* Operation completed without error */
    LPUART_E_NOT_OK,   /* Operation not completed */
} Std_LPUART_Status;   /* Standard status type */

typedef struct
{
    uint8_t frameLenth;             /* Frame length, value is from 7 to 10                                  */
    uint8_t parityMode;             /* Parity mode, value is 0 for even, 1 for odd, 2 for disable           */
    uint8_t nOfStopBits;            /* Number of stop bits, value is 0 for 1 stop bit, 1 for 2 stop bits    */
    uint8_t msbFirst;               /* MSB first, value is 0 for MSB first, 1 for LSB first                 */
    uint8_t txInterrupt;            /* Transmit interrupt, value is 0 for disable, 1 for enable             */
    uint8_t rxInterrupt;            /* Receive interrupt, value is 0 for disable, 1 for enable              */
    uint8_t txCompleteInterrupt;    /* Transmit complete interrupt, value is 0 for disable, 1 for enable    */
    uint8_t overRunInterrupt;       /* Overrun interrupt, value is 0 for disable, 1 for enable              */
    uint8_t noiseErrorInterrupt;    /* Noise error interrupt, value is 0 for disable, 1 for enable          */
    uint8_t frameErrorInterrupt;    /* Frame error interrupt, value is 0 for disable, 1 for enable          */
    uint8_t parityErrorInterrupt;   /* Parity error interrupt, value is 0 for disable, 1 for enable         */
    uint8_t rxPolarity;             /* Rx data inversion, value is 0 for disable, 1 for enable              */
    uint8_t txPolarity;             /* Tx data inversion, value is 0 for disable, 1 for enable              */
    uint32_t baudRate;              /* Baudrate, value is less than MAX_BAUDRATE                            */
} LPUART_Config_Type;

typedef struct
{
    LPUART_Type *pLPUARTx;                      /* This holds the base address of the GPIO port to which the pin belongs */
    LPUART_Config_Type LPUART_Config;           /* This holds GPIO pin configuration settings */
} LPUART_Handle_Type;                           /* GPIO handle type */

typedef void (*LPUART_CallbackPtr) (void);      /*LPUART Callback type for the pointer to callback fuction*/

/****************************************************************************************************************
 *                                              API DECLARATIONS                                                *
 ****************************************************************************************************************/
/**
 * @name LPUART_Init
 *
 * @brief This function is used to initialize the LPUART
 *
 * @param pLPUARTHandle[in/out]: pointer to the LPUART handle
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_Init(LPUART_Handle_Type *pLPUARTHandle);

/**
 * @name LPUART_SetTxState
 *
 * @brief This function is used to start and stop Transmitter of LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetTxState(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetRxState
 *
 * @brief This function is used to start and stop Receiver of LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetRxState(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_BaudRateConfig
 *
 * @brief This function is used to calculate and config the baudrate
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param baudRate[in]: baudrate to set, must be less than or equal to MAX_BAUDRATE
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_BaudRateConfig(LPUART_Type *pLPUARTx, uint32_t baudRate);

/**
 * @name LPUART_TxFrame7_8
 *
 * @brief This function is used to send a frame of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxFrame7_8(LPUART_Type *pLPUARTx, uint8_t data);

/**
 * @name LPUART_TxMultiFrame7_8
 *
 * @brief This function is used to send multiple frames of 7 or 8 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pTxBuffer[in]: pointer to the data buffer
 * @param len[in]: length of the data buffer
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxMultiFrame7_8(LPUART_Type *pLPUARTx, uint8_t *pTxBuffer, uint32_t len);

/**
 * @name LPUART_TxFrame9_10
 *
 * @brief This function is used to send a frame of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param data[in]: data to send
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxFrame9_10(LPUART_Type *pLPUARTx, uint16_t data);

/**
 * @name LPUART_TxMultiFrame9_10
 *
 * @brief This function is used to send multiple frames of 9 or 10 bits
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pTxBuffer[in]: pointer to the data buffer
 * @param len[in]: length of the data buffer
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_TxMultiFrame9_10(LPUART_Type *pLPUARTx, uint16_t *pTxBuffer, uint32_t len);

/**
 * @name LPUART_RxFrame
 *
 * @brief This function is used to receive a frame
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param RxBuffer[in]: pointer to the buffer to store the received data
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_RxFrame(LPUART_Type *pLPUARTx, uint8_t* RxBuffer);

/**
 * @name LPUART_RxMultiFrame
 *
 * @brief This function is used to receive multiple frames
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param pRxBuffer[in]: pointer to the buffer to store the received data
 * @param len[in]: length of the buffer
 *
 * @return uint32_t: number of data received
 */
uint32_t LPUART_RxMultiFrame(LPUART_Type *pLPUARTx, uint16_t *pRxBuffer, uint32_t len);

/**
 * @name LPUART_SetTxInterrupt
 *
 * @brief This function is used to configure the LPUART Tx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetTxInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetTxCompleteInterrupt
 *
 * @brief This function is used to configure the LPUART Tx complete interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetTxCompleteInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetRxInterrupt
 *
 * @brief This function is used to configure the LPUART Rx interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetRxInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetOverRunInterrupt
 *
 * @brief This function is used to configure the LPUART OverRun interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetOverRunInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetNoiseErrorInterrupt
 *
 * @brief This function is used to configure the LPUART Noise error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetNoiseErrorInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetFrameErrorInterrupt
 *
 * @brief This function is used to configure the LPUART Frame error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetFrameErrorInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_SetParityErrorInterrupt
 *
 * @brief This function is used to configure the LPUART Parity error interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param enable[in]: state to set
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_SetParityErrorInterrupt(LPUART_Type *pLPUARTx, uint8_t enable);

/**
 * @name LPUART_CallbackRegister
 *
 * @brief This function is used to register the callback function for the LPUART interrupt
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 * @param IRQHandler[in]: pointer to the callback function
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_CallbackRegister(LPUART_Type *pLPUARTx, LPUART_CallbackPtr IRQHandler);

/**
 * @name LPUART_DeInit
 *
 * @brief This function is used to de-initialize the LPUART
 *
 * @param pLPUARTx[in/out]: pointer to the LPUART instance
 *
 * @return Std_LPUART_Status: status of the operation
 */
Std_LPUART_Status LPUART_DeInit(LPUART_Type *pLPUARTx);

#endif /* S32K144_LPUART_DRIVER_H */
