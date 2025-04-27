/**
 * @file s32k1xx_gpio_driver.h
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief GPIO driver for S32K1xx
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef INC_S32K1XX_GPIO_DRIVER_H_
#define INC_S32K1XX_GPIO_DRIVER_H_

/**
 * INCLUSION
 */
#include "../include/S32K144.h"
/**
 * TYPE DEFINITIONS
 */
typedef uint32_t ARM_GPIO_Pin_Type; /* GPIO pin type */

typedef enum
{
    ARM_GPIO_INPUT,     /* GPIO pin is input */
    ARM_GPIO_OUTPUT     /* GPIO pin is output */
} ARM_GPIO_DIRECTION;   /* GPIO direction type */

typedef enum
{
    GPIO_E_OK,       /* Operation completed without error */
    GPIO_E_NOT_OK,   /* Operation not completed */
} Std_GPIO_Status;   /* Standard status type */

typedef struct
{
    uint8_t GPIO_PinNumber;                 /* This holds the GPIO pin number */
    ARM_GPIO_DIRECTION GPIO_PinDirection;   /* This holds the GPIO pin direction */
}GPIO_PinConfig_Type;                       /* GPIO pin configuration type */

typedef struct
{
    GPIO_Type *pGPIOx;                      /* This holds the base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_Type GPIO_PinConfig;     /* This holds GPIO pin configuration settings */
}GPIO_Handle_Type;                          /* GPIO handle type */

/**
 * FUNCTION PROTOTYPES
 */
/**
 * @name    GPIO_Init
 *
 * @brief   Initialize the GPIO
 *
 * @param pGPIOHandle   [in]    GPIO handle
 * @return Std_GPIO_Status     GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
Std_GPIO_Status GPIO_Init(GPIO_Handle_Type *pGPIOHandle);

/**
 * @name    GPIO_SetDirection
 * @brief   Set the direction input or output of the pin
 *
 * @param   pGPIOx      [in]    GPIO port
 * @param   pin         [in]    GPIO pin
 * @param   direction   [in]    Direction of the pin
 * @return  Std_GPIO_Status    GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_SetDirection(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin, ARM_GPIO_DIRECTION direction);

/**
 * @name    GPIO_ReadPin
 *
 * @brief   Read the value of the pin
 *
 * @param   pGPIOx  [in]    GPIO port
 * @param   pin     [in]    GPIO pin
 * @return Std_GPIO_Status   Value of the pin
 */
uint32_t GPIO_ReadPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin);

/**
 * @name    GPIO_ReadPort
 *
 * @brief   Read values of the port
 *
 * @param pGPIOx    [in]    GPIO port
 * @return Std_GPIO_Status  Values of the port
 */
uint32_t GPIO_ReadPort(GPIO_Type *pGPIOx);

/**
 * @name    GPIO_SetPin
 *
 * @brief   Set the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @param value     [in]    Value to set
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_SetPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin);

/**
 * @name    GPIO_ClearPin
 *
 * @brief   Clear the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @param value     [in]    Value to clear
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_ClearPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin);

/**
 * @name    GPIO_TogglePin
 *
 * @brief   Toggle the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_TogglePin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin);

#endif /* INC_S32K1XX_GPIO_DRIVER_H_ */
