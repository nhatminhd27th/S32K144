/**
 * @file s32k1xx_gpio_hal.h
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief   This file contains the GPIO HAL driver for S32K1xx
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef INC_S32K1XX_GPIO_HAL_H_
#define INC_S32K1XX_GPIO_HAL_H_

/**
 * INCLUSIONS
 */
#include "../include/S32K144.h"

/**
 * MACROS
 */
#define HAL_GPIO_INPUT      (0U)    /* Input direction */
#define HAL_GPIO_OUTPUT     (1U)    /* Output direction */

/**
 * FUNCTIONS PROTOTYPES
 */
/**
 * @name HAL_GPIO_SetDirection
 *
 * @brief This function set the direction of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 * @param direction [in]    Direction of the pin
 *
 * @return None
 */
void HAL_GPIO_SetDirection(GPIO_Type *pGPIOx, uint8_t pin, uint8_t direction);

/**
 * @name HAL_GPIO_ReadPin
 *
 * @brief This function read the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return uint32_t         Value of the pin
 */
uint32_t HAL_GPIO_ReadPin(GPIO_Type *pGPIOx, uint8_t pin);

/**
 * @name HAL_GPIO_ReadPort
 *
 * @brief This function read the value of a port
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 *
 * @return uint32_t         Value of the port
 */
uint32_t HAL_GPIO_ReadPort(GPIO_Type *pGPIOx);

/**
 * @name HAL_GPIO_SetPin
 *
 * @brief This function set the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_SetPin(GPIO_Type *pGPIOx, uint8_t pin);

/**
 * @name HAL_GPIO_ClearPin
 *
 * @brief This function clear the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_ClearPin(GPIO_Type *pGPIOx, uint8_t pin);

/**
 * @name HAL_GPIO_TogglePin
 *
 * @brief This function toggle the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_TogglePin(GPIO_Type *pGPIOx, uint8_t pin);

#endif /* INC_S32K1XX_GPIO_HAL_H_ */
