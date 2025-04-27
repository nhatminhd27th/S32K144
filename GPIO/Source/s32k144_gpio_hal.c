/**
 * @file s32k1xx_gpio_hal.c
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This file contains the GPIO HAL driver for S32K1xx
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * INCLUSIONS
 */
#include "../src/Driver/GPIO/Include/s32k144_gpio_hal.h"

/**
 * FUNCTIONS DEFINITIONS
 */
/**
 * @brief This function set the direction of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 * @param direction [in]    Direction of the pin
 *
 * @return None
 */
void HAL_GPIO_SetDirection(GPIO_Type *pGPIOx, uint8_t pin, uint8_t direction)
{
    switch (direction) {
        case HAL_GPIO_INPUT:
            pGPIOx->PDDR &= ~(1 << pin);
            break;
        case HAL_GPIO_OUTPUT:
            pGPIOx->PDDR |= (1 << pin);
            break;
    }
}

/**
 * @brief This function read the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return uint32_t         Value of the pin
 */
uint32_t HAL_GPIO_ReadPin(GPIO_Type *pGPIOx, uint8_t pin)
{
    return ((pGPIOx->PDIR >> pin) & 0x1U);
}

/**
 * @brief This function read the value of a port
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 *
 * @return uint32_t         Value of the port
 */
uint32_t HAL_GPIO_ReadPort(GPIO_Type *pGPIOx)
{
    return (pGPIOx->PDIR);
}

/**
 * @brief This function set the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_SetPin(GPIO_Type *pGPIOx, uint8_t pin)
{
    pGPIOx->PSOR |= (1 << pin);
}

/**
 * @brief This function clear the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_ClearPin(GPIO_Type *pGPIOx, uint8_t pin)
{
    pGPIOx->PCOR |= (1 << pin);
}

/**
 * @brief This function toggle the value of a pin
 *
 * @param pGPIOx    [in]    Pointer to the GPIO base address
 * @param pin       [in]    Pin number
 *
 * @return None
 */
void HAL_GPIO_TogglePin(GPIO_Type *pGPIOx, uint8_t pin)
{
    pGPIOx->PTOR |= (1 << pin);
}
