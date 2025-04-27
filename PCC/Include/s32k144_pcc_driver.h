/**
 * @file Driver_PCC_Module.h
 * @author Vo Doan Quynh Nhi
 * @brief
 * @version 0.1
 * @date 2025-01-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef DRIVER_PCCMODULE_H_
#define DRIVER_PCCMODULE_H_

/*******************************************************************************
* Include
*******************************************************************************/
#include "../src/Driver/PCC/Include/s32k144_PCC_hal.h"

/*******************************************************************************/
/* Type Definitions                                                            */
/*******************************************************************************/

typedef enum
{
   SCG_E_OK     = 0U,
   SCG_E_NOT_OK = 1U,
}Std_SCG_Status;

typedef enum
{
   PCC_E_OK = 0U,                           /* successful */
   PCC_E_NOT_OK = 1U,                       /* fail */
}Std_PCC_Status;

/*******************************************************************************
* Prototypes
******************************************************************************/
/**
 * @brief Check the peripheral reset status.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Check_PR( uint32_t peripheralIndex);

/**
 * @brief Initialize the specified peripheral.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Init( uint32_t peripheralIndex);

/**
 * @brief Select the clock source for a peripheral.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @param source              [Input] Clock source to be selected.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Clock_Source_Select( uint32_t peripheralIndex, PeripheralClockSource source);

/**
 * @brief Set the clock divider and fraction for a peripheral.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @param divider             [Input] Clock divider value.
 * @param fraction            [Input] Clock fraction value.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Clock_Divider_Select( uint32_t peripheralIndex, PeripheralClockDividerSelect divider, PeripheralClockFractionSelect fraction);

/**
 * @brief De-initialize the specified peripheral.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_De_Init( uint32_t peripheralIndex);

#endif /* DRIVER_PCCMODULE_H_ */
