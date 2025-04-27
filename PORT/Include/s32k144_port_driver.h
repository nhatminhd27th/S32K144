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

#ifndef PORT_DRIVER_H
#define PORT_DRIVER_H

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "s32k144_port_hal.h"

/*******************************************************************************
 * Typedef
 ******************************************************************************/

typedef void (*func_ptr)(void);

typedef uint32_t PORT_Pin_type;

/*******************************************************************************
 * Enum
 ******************************************************************************/
typedef enum
{
    PORT_E_OK,    /* Indicates that the operation was successful */
    PORT_E_NOT_OK /* Indicates that the operation failed or encountered an error */
} Std_PORT_Status;

typedef enum
{
    PORT_MUX_DISABLED     = 0,  /* Pin disabled (Alternative 0) (analog) */
    PORT_MUX_GPIO         = 1,  /* Alternative 1 (GPIO) */
    PORT_MUX_ALTERNATIVE2 = 2,  /* Alternative 2 (chip-specific) */
    PORT_MUX_ALTERNATIVE3 = 3,  /* Alternative 3 (chip-specific) */
    PORT_MUX_ALTERNATIVE4 = 4,  /* Alternative 4 (chip-specific) */
    PORT_MUX_ALTERNATIVE5 = 5,  /* Alternative 5 (chip-specific) */
    PORT_MUX_ALTERNATIVE6 = 6,  /* Alternative 6 (chip-specific) */
    PORT_MUX_ALTERNATIVE7 = 7   /* Alternative 7 (chip-specific) */
} PORT_MUX_MODE_type;

typedef enum
{
    PORT_IRQ_MODE_DISABLED         = 0x0U,  /* Interrupt Status Flag (ISF) is disabled */
    PORT_IRQ_MODE_RISING_EDGE      = 0x1U,  /* ISF flag and DMA request on rising edge */
    PORT_IRQ_MODE_FALLING_EDGE     = 0x2U,  /* ISF flag and DMA request on falling edge */
    PORT_IRQ_MODE_EITHER_EDGE      = 0x3U,  /* ISF flag and DMA request on either edge */
    PORT_IRQ_MODE_LOGIC_0          = 0x8U,  /* ISF flag and Interrupt when logic 0 */
    PORT_IRQ_MODE_RISING_EDGE_INT  = 0x9U,  /* ISF flag and Interrupt on rising-edge */
    PORT_IRQ_MODE_FALLING_EDGE_INT = 0xAU,  /* ISF flag and Interrupt on falling-edge */
    PORT_IRQ_MODE_EITHER_EDGE_INT  = 0xBU,  /* ISF flag and Interrupt on either edge */
    PORT_IRQ_MODE_LOGIC_1          = 0xCU   /* ISF flag and Interrupt when logic 1 */
} PORT_IRQ_MODE_type;

typedef enum
{
    PORT_PIN_PULL_DISABLE = 0, /* Disable pull configuration */
    PORT_PIN_PULL_ENABLE  = 1  /* Enable pull configuration */
} PORT_PULL_ENABLE_type;

typedef enum
{
    PORT_PIN_PULLDOWN = 0, /* Configures the pin with a pull-down resistor */
    PORT_PIN_PULLUP   = 1  /* Configures the pin with a pull-up resistor */
} PORT_PIN_PULL_MODE_type;

/*******************************************************************************
 * Struct
 ******************************************************************************/

typedef struct
{
    PORT_Pin_type pin;                   /* Specifies the pin number to be configured */
    PORT_MUX_MODE_type mux;              /* Selects the multiplexer mode for the pin */
    PORT_PULL_ENABLE_type pull_enable;   /* Enables or disables the pull resistor on the pin */
    PORT_PIN_PULL_MODE_type pull_select; /* Specifies the type of pull resistor */
    PORT_IRQ_MODE_type irq_mode;         /* Configures the interrupt mode for the pin */
} PORT_Config_t;

/*******************************************************************************
 * API
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
 * @return uint32_t Returns PORT_DRIVER_OK if successful, otherwise returns PORT_DRIVER_NOT_OK.
 */
Std_PORT_Status PORT_Init(PORT_Type *PORTx, PORT_Config_t *config);

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
 * @return Std_PORT_Status Returns PORT_DRIVER_OK if successful, otherwise returns PORT_DRIVER_NOT_OK.
 */
Std_PORT_Status PORT_EnableInterrupt(PORT_Type *PORTx, PORT_Pin_type pin, PORT_IRQ_MODE_type irq_mode);

/**
 * @brief Disable interrupt for a specific pin on the given port.
 *
 * This function clears the interrupt configuration for the specified pin
 * on the given port. If the pin is not available, or the port is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] pin The pin number to disable the interrupt for.
 * @return Std_PORT_Status Returns PORT_DRIVER_OK if successful, otherwise returns PORT_DRIVER_NOT_OK.
 */
Std_PORT_Status PORT_DisableInterrupt(PORT_Type *PORTx, PORT_Pin_type pin);

/**
 * @brief Register an interrupt handler function for a specific port.
 *
 * This function registers a callback function for the specified port.
 * If the port or callback function is NULL, it returns an error code.
 *
 * @param[in] PORTx Pointer to the port register structure.
 * @param[in] App_Function Pointer to the application-specific interrupt handler function.
 * @return Std_PORT_Status Returns PORT_DRIVER_OK if successful, otherwise returns PORT_DRIVER_NOT_OK.
 */
Std_PORT_Status Register_InterruptHandler(PORT_Type *PORTx, func_ptr App_Function);

#endif /* PORT_DRIVER_H */
