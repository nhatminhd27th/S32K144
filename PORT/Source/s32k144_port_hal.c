/**
 * @file s32k144_port_hal.h
 * @author Nguyen Dinh Le Quang (ndlequang1242@gmail.com)
 * @brief   This file contains the PORT HAL driver for S32K144
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "../src/Driver/PORT/Include/s32k144_port_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Clear the multiplexer field for a specific pin on the given port.
 *
 * This function clears the MUX field for the specified pin on the given port.
 * If the pin is not available, or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_ClearMux(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] &= ~PORT_PCR_MUX_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Set the multiplexer mode for a specific pin on the given port.
 *
 * This function configures the MUX field for the specified pin on the given port.
 * If the pin is not available, or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @param[in] mux The multiplexer mode to set.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_SetMux(PORT_Type *PORTx, HAL_Pin_type pin, HAL_MUX_MODE_type mux)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] |= PORT_PCR_MUX(mux);
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Enable the pull-up or pull-down resistor for a specific pin on the given port.
 *
 * This function sets the pull enable (PE) field for the specified pin on the given port.
 * If the pin is not available, or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_EnablePull(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] |= PORT_PCR_PE_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Disable the pull-up or pull-down resistor for a specific pin on the given port.
 *
 * This function clears the pull enable (PE) field for the specified pin on the given port.
 * If the pin is not available, or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_DisablePull(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] &= ~PORT_PCR_PE_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Enable the pull-up resistor for a specific pin on the given port.
 *
 * This function sets the pull select (PS) field for the specified pin on the given port
 * to enable the pull-up resistor. If the pin is not available, or the port is NULL, it
 * returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_SetPullUp(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] |= PORT_PCR_PS_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Enable the pull-down resistor for a specific pin on the given port.
 *
 * This function clears the pull select (PS) field for the specified pin on the given port
 * to enable the pull-down resistor. If the pin is not available, or the port is NULL, it
 * returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_SetPullDown(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] &= ~PORT_PCR_PS_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Clear the interrupt configuration for a specific pin on the given port.
 *
 * This function clears the interrupt configuration field (IRQC) for the specified pin
 * on the given port. If the pin is not available, or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_ClearIrq(PORT_Type *PORTx, HAL_Pin_type pin)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}

/**
 * @brief Set the interrupt mode for a specific pin on the given port.
 *
 * This function configures the interrupt configuration field (IRQC) for the specified pin
 * on the given port according to the interrupt mode provided. If the pin is not available,
 * or the port is NULL, it returns an error status.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to configure.
 * @param[in] irq_mode The interrupt mode to set.
 * @return Std_HAL_Status Returns HAL_E_OK if successful, otherwise returns HAL_E_NOT_OK.
 */
Std_HAL_Status HAL_Port_SetIrqMode(PORT_Type *PORTx, HAL_Pin_type pin, HAL_IRQ_MODE_type irq_mode)
{
    Std_HAL_Status status = HAL_E_OK;
    if(NULL != PORTx)
    {
        if(PIN_IS_AVAILABLE(pin))
        {
            PORTx->PCR[pin] |= PORT_PCR_IRQC(irq_mode);
        }
        else
        {
            status = HAL_E_NOT_OK;
        }
    }
    else
    {
        status = HAL_E_NOT_OK;
    }

    return status;
}
