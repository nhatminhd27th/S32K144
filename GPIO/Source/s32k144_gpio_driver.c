/**
 * @file    s32k1xx_gpio_driver.c
 * @author  Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief   GPIO driver for S32K1xx
 * @version 0.1
 * @date    2025-01-20
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * INCLUSION
 */
#include "../src/Driver/GPIO/Include/s32k144_gpio_driver.h"

#include "../src/Driver/GPIO/Include/s32k144_gpio_hal.h"

/**
 * MACROS
 */
/**
 * @brief   Check if the pin is available
 *
 * @param pin   [in]    GPIO pin
 * @param port  [in]    GPIO port
 * @return Std_GPIO_Status    1 if available, 0 if not available
 */
#define PIN_IS_AVAILABLE(pin, port)     ((pin) < ((port == PTE) ? 17U : 18U))

/**
 * FUNCTION DEFINITIONS
 */
/**
 * @brief   Initialize the GPIO
 *
 * @param pGPIOHandle   [in]GPIO handle
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
Std_GPIO_Status GPIO_Init(GPIO_Handle_Type *pGPIOHandle)
{
    Std_GPIO_Status result = GPIO_E_OK;

    /* Check if the pin is available and set direction for it */
    if (PIN_IS_AVAILABLE(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->pGPIOx)) {
        HAL_GPIO_SetDirection(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinDirection);
    }
    else
    {
        result = GPIO_E_NOT_OK;
    }

    return result;
}

/**
 * @brief   Set the direction input or output of the pin
 *
 * @param   pGPIOx      [in]    GPIO port
 * @param   pin         [in]    GPIO pin
 * @param   direction   [in]    Direction of the pin
 * @return  Std_GPIO_Status    GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_SetDirection(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin, ARM_GPIO_DIRECTION direction)
{
    Std_GPIO_Status result = GPIO_E_OK;

    /* Check if the inputs are available and set direction for the pin */
    if(PIN_IS_AVAILABLE(pin, pGPIOx) && (direction == ARM_GPIO_INPUT || direction == ARM_GPIO_OUTPUT))
    {
        HAL_GPIO_SetDirection(pGPIOx, pin, direction);
    }
    else
    {
        result = GPIO_E_NOT_OK;
    }

    return result;
}

/**
 * @brief   Read the value of the pin
 *
 * @param   pGPIOx  [in]    GPIO port
 * @param   pin     [in]    GPIO pin
 * @return Std_GPIO_Status   Value of the pin
 */
uint32_t GPIO_ReadPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin)
{
    Std_GPIO_Status val = 0U;

    /* Check if the pin is available and read the value of the pin */
    if (PIN_IS_AVAILABLE(pin, pGPIOx))
    {
        val = HAL_GPIO_ReadPin(pGPIOx, pin);
    }

    return val;
}

/**
 * @brief   Read values of the port
 *
 * @param pGPIOx    [in]    GPIO port
 * @return Std_GPIO_Status  Values of the port
 */
uint32_t GPIO_ReadPort(GPIO_Type *pGPIOx)
{
    return HAL_GPIO_ReadPort(pGPIOx);
}

/**
 * @brief   Set the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @param value     [in]    Value to set
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_SetPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin)
{
    Std_GPIO_Status result = GPIO_E_OK;

    /* Check if the pin is available and set the value for the pin */
    if (PIN_IS_AVAILABLE(pin, pGPIOx)) {
        HAL_GPIO_SetPin(pGPIOx, pin);
    }
    else
    {
        result = GPIO_E_NOT_OK;
    }

    return result;
}

/**
 * @brief   Clear the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @param value     [in]    Value to clear
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_ClearPin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin)
{
    Std_GPIO_Status result = GPIO_E_OK;

    /* Check if the pin is available and clear the value for the pin */
    if (PIN_IS_AVAILABLE(pin, pGPIOx)) {
        HAL_GPIO_ClearPin(pGPIOx, pin);
    }
    else
    {
        result = GPIO_E_NOT_OK;
    }

    return result;
}

/**
 * @brief   Toggle the logic level on pin
 *
 * @param pGPIOx    [in]    GPIO port
 * @param pin       [in]    GPIO pin
 * @return Std_GPIO_Status GPIO_E_OK if success, GPIO_E_NOT_OK if error
 */
uint32_t GPIO_TogglePin(GPIO_Type *pGPIOx, ARM_GPIO_Pin_Type pin)
{
    Std_GPIO_Status result = GPIO_E_OK;

    /* Check if the pin is available and toggle the value for the pin */
    if (PIN_IS_AVAILABLE(pin, pGPIOx)) {
        HAL_GPIO_TogglePin(pGPIOx, pin);
    }
    else
    {
        result = GPIO_E_NOT_OK;
    }

    return result;
}
