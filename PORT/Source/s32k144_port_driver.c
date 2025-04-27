/**
 * @file s32k144_port_driver.h
 * @author Nguyen Dinh Le Quang (ndlequang1242@gmail.com)
 * @brief GPIO driver for S32K144
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "../src/Driver/PORT/Include/s32k144_port_driver.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

static func_ptr PORT_callback_func_arr[5] = {NULL};

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Initialize the specified port with the given configuration.
 *
 * This function configures the peripheral type, pull settings, and interrupt mode
 * for a specific pin on the given port. It clears and sets the necessary fields according
 * to the configuration provided. If the pin is not available, or the port or configuration
 * is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] config Pointer to the port configuration structure.
 * @return Std_PORT_Status Returns PORT_E_OK if successful, otherwise returns PORT_E_NOT_OK.
 */
Std_PORT_Status PORT_Init(PORT_Type *PORTx, PORT_Config_t *config)
{
    Std_PORT_Status result = PORT_E_OK;

    if (NULL != PORTx && NULL != config)
    {
        if (PIN_IS_AVAILABLE(config->pin))
        {
            /* Peripheral type configuration */
            /* Clear MUX field */
            HAL_Port_ClearMux(PORTx, config->pin);
            /* Set MUX field */
            HAL_Port_SetMux(PORTx, config->pin, config->mux);
            /* Toggle pull configuration */
            if (PORT_PIN_PULL_ENABLE == config->pull_enable)
            {
                /* Enable pull configuration by set PE field to 1 */
                HAL_Port_EnablePull(PORTx, config->pin);
                /* Configure pull configuration mode */
                if (PORT_PIN_PULLUP == config->pull_select)
                {
                    /* Set pull-up mode by set PS field to 1 */
                    HAL_Port_SetPullUp(PORTx, config->pin);
                }
                else if (PORT_PIN_PULLDOWN == config->pull_select)
                {
                    /* Set pull-down mode by set PS field to 0 */
                    HAL_Port_SetPullDown(PORTx, config->pin);
                }
                else
                {
                    /* do nothing */
                }
            }
            else if (PORT_PIN_PULL_DISABLE == config->pull_enable)
            {
                /* Disable pull configuration by set PE field to 0 */
                HAL_Port_DisablePull(PORTx, config->pin);
            }
            else
            {
                /* do nothing */
            }

            /* Interrupt mode configuration */
            /* Clear IRQC field */
            HAL_Port_ClearIrq(PORTx, config->pin);
            /* Set MUX field */
            HAL_Port_SetIrqMode(PORTx, config->pin, config->irq_mode);
        }
        else
        {
            result = PORT_E_NOT_OK;
        }
    }
    else
    {
        result = PORT_E_NOT_OK;
    }

    return result;
}

/**
 * @brief Enable interrupt for a specific pin on the given port.
 *
 * This function clears the interrupt status flag for the specified pin
 * and configures the interrupt mode for the pin on the specified port.
 * If the pin is not available or the port is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @param[in] irq_mode The interrupt mode to set.
 * @return Std_PORT_Status Returns PORT_E_OK if successful, otherwise returns PORT_E_NOT_OK.
 */
Std_PORT_Status PORT_EnableInterrupt(PORT_Type *PORTx, PORT_Pin_type pin, PORT_IRQ_MODE_type irq_mode)
{
    Std_PORT_Status result = PORT_E_OK;


    if (NULL != PORTx)
    {
        if (PIN_IS_AVAILABLE(pin))
        {
            /* clear interrupt flat*/
            PORTx->PCR[pin] |= PORT_PCR_ISF(1);
            HAL_Port_SetIrqMode(PORTx, pin, irq_mode);
        }
        else
        {
            result = PORT_E_NOT_OK;
        }
    }
    else
    {
        result = PORT_E_NOT_OK;
    }

    return result;
}

/**
 * @brief Disable interrupt for a specific pin on the given port.
 *
 * This function clears the interrupt configuration for the specified pin
 * on the given port. If the pin is not available, or the port is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to disable the interrupt for.
 * @return Std_PORT_Status Returns PORT_E_OK if successful, otherwise returns PORT_E_NOT_OK.
 */
Std_PORT_Status PORT_DisableInterrupt(PORT_Type *PORTx, PORT_Pin_type pin)
{
    Std_PORT_Status result = PORT_E_OK;

    if (NULL != PORTx)
    {
        if (PIN_IS_AVAILABLE(pin))
        {
            HAL_Port_ClearIrq(PORTx, pin);
        }
        else
        {
            result = PORT_E_NOT_OK;
        }
    }
    else
    {
        result = PORT_E_NOT_OK;
    }

    return result;
}

/**
 * @brief Register an interrupt handler function for a specific port.
 *
 * This function registers a callback function for the specified port.
 * If the port or callback function is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] App_Function Pointer to the application-specific interrupt handler function.
 * @return Std_PORT_Status Returns PORT_E_OK if successful, otherwise returns PORT_E_NOT_OK.
 */
Std_PORT_Status Register_InterruptHandler(PORT_Type *PORTx, func_ptr App_Function)
{
    Std_PORT_Status result = PORT_E_OK;
    if(NULL != PORTx)
    {
        if(NULL != App_Function)
        {
            if (PORTx == PORTA)
            {
                PORT_callback_func_arr[0] = App_Function;
            }
            else if (PORTx == PORTB)
            {
                PORT_callback_func_arr[1] = App_Function;
            }
            else if (PORTx == PORTC)
            {
                PORT_callback_func_arr[2] = App_Function;
            }
            else if (PORTx == PORTD)
            {
                PORT_callback_func_arr[3] = App_Function;
            }
            else if (PORTx == PORTE)
            {
                PORT_callback_func_arr[4] = App_Function;
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            result = PORT_E_NOT_OK;
        }
    }
    else
    {
        result = PORT_E_NOT_OK;
    }

    return result;
}

void PORTA_IRQHandler(void)
{
    if (NULL != PORT_callback_func_arr[0])
    {
        PORT_callback_func_arr[0]();
    }
    else
    {
        /* do nothing */
    }
}

void PORTB_IRQHandler(void)
{
    if (NULL != PORT_callback_func_arr[1])
    {
        PORT_callback_func_arr[1]();
    }
    else
    {
        /* do nothing */
    }
}

void PORTC_IRQHandler(void)
{
    if (NULL != PORT_callback_func_arr[2])
    {
        PORT_callback_func_arr[2]();
    }
    else
    {
        /* do nothing */
    }
}

void PORTD_IRQHandler(void)
{
    if (NULL != PORT_callback_func_arr[3])
    {
        PORT_callback_func_arr[3]();
    }
    else
    {
        /* do nothing */
    }
}

void PORTE_IRQHandler(void)
{
    if (NULL != PORT_callback_func_arr[4])
    {
        PORT_callback_func_arr[4]();
    }
    else
    {
        /* do nothing */
    }
}
