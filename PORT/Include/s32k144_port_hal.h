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
 
#ifndef HAL_PORT_DRIVER_H
#define HAL_PORT_DRIVER_H

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "../include/S32K144.h"
#include <stddef.h>

/*******************************************************************************
 * Macro
 ******************************************************************************/

#define PORT_MAX_PINS 32U
#define PIN_IS_AVAILABLE(n) ((n) < PORT_MAX_PINS)

/*******************************************************************************
 * Typedef
 ******************************************************************************/

typedef uint32_t HAL_Pin_type;

/*******************************************************************************
 * Enum
 ******************************************************************************/

typedef enum
{
    HAL_E_OK,
    HAL_E_NOT_OK
} Std_HAL_Status;

typedef enum
{
    HAL_MUX_DISABLED     = 0,   /* Pin disabled (Alternative 0) (analog) */
    HAL_MUX_GPIO         = 1,   /* Alternative 1 (GPIO) */
    HAL_MUX_ALTERNATIVE2 = 2,   /* Alternative 2 (chip-specific) */
    HAL_MUX_ALTERNATIVE3 = 3,   /* Alternative 3 (chip-specific) */
    HAL_MUX_ALTERNATIVE4 = 4,   /* Alternative 4 (chip-specific) */
    HAL_MUX_ALTERNATIVE5 = 5,   /* Alternative 5 (chip-specific) */
    HAL_MUX_ALTERNATIVE6 = 6,   /* Alternative 6 (chip-specific) */
    HAL_MUX_ALTERNATIVE7 = 7    /* Alternative 7 (chip-specific) */
} HAL_MUX_MODE_type;

typedef enum
{
    HAL_IRQ_MODE_DISABLED         = 0x0U,   /* Interrupt Status Flag (ISF) is disabled */
    HAL_IRQ_MODE_RISING_EDGE      = 0x1U,   /* ISF flag and DMA request on rising edge */
    HAL_IRQ_MODE_FALLING_EDGE     = 0x2U,   /* ISF flag and DMA request on falling edge */
    HAL_IRQ_MODE_EITHER_EDGE      = 0x3U,   /* ISF flag and DMA request on either edge */
    HAL_IRQ_MODE_LOGIC_0          = 0x8U,   /* ISF flag and Interrupt when logic 0 */
    HAL_IRQ_MODE_RISING_EDGE_INT  = 0x9U,   /* ISF flag and Interrupt on rising-edge */
    HAL_IRQ_MODE_FALLING_EDGE_INT = 0xAU,   /* ISF flag and Interrupt on falling-edge */
    HAL_IRQ_MODE_EITHER_EDGE_INT  = 0xBU,   /* ISF flag and Interrupt on either edge */
    HAL_IRQ_MODE_LOGIC_1          = 0xCU    /* ISF flag and Interrupt when logic 1 */
} HAL_IRQ_MODE_type;

/*******************************************************************************
 * API
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
Std_HAL_Status HAL_Port_ClearMux(PORT_Type *PORTx, HAL_Pin_type pin);

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
Std_HAL_Status HAL_Port_SetMux(PORT_Type *PORTx, HAL_Pin_type pin, HAL_MUX_MODE_type mux);

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
Std_HAL_Status HAL_Port_EnablePull(PORT_Type *PORTx, HAL_Pin_type pin);

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
Std_HAL_Status HAL_Port_DisablePull(PORT_Type *PORTx, HAL_Pin_type pin);

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

Std_HAL_Status HAL_Port_SetPullUp(PORT_Type *PORTx, HAL_Pin_type pin);

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
Std_HAL_Status HAL_Port_SetPullDown(PORT_Type *PORTx, HAL_Pin_type pin);

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
Std_HAL_Status HAL_Port_ClearIrq(PORT_Type *PORTx, HAL_Pin_type pin);

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
Std_HAL_Status HAL_Port_SetIrqMode(PORT_Type *PORTx, HAL_Pin_type pin, HAL_IRQ_MODE_type irq_mode);

#endif /* HAL_PORT_DRIVER_H */
