/**
 * @file Driver_PCC_Module.c
 * @author Vo Doan Quynh Nhi
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

/*******************************************************************************
* Include
*******************************************************************************/
#include "../src/Driver/PCC/Include/s32k144_PCC_driver.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
Std_SCG_Status SCG_SystemClock_Config(SCG_ClockSource_t source)
{
    Std_SCG_Status status = SCG_E_OK;
    status = HAL_SystemClock_Config(source);

    if(SCG_E_OK != status)
    {
        status = SCG_E_NOT_OK;
    }

    return status;
}
/**
 * @brief Initialize the specified peripheral.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Init( uint32_t peripheralIndex)
{
    Std_PCC_Status status = PCC_E_OK;
    /* enable the peripheral clock using the HAL function */
    status = HAL_Enable_Peripheral_Clock( peripheralIndex);

    /* Check if the operation was not successful */
    if(PCC_E_OK != status)
    {
        status = PCC_E_NOT_OK;
    }

    return status;
}

/**
 * @brief This bit shows whether the peripheral is present on this device.
 *
 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Check_PR( uint32_t peripheralIndex)
{
    Std_PCC_Status status = PCC_E_OK;
    /* Check if the Clock Gating Control (CGC) bit is set in the PCCn register */
    if(PCC->PCCn[peripheralIndex] & PCC_PCCn_CGC_MASK)
    {
        status = PCC_E_NOT_OK;
    }

    HAL_Check_PR( peripheralIndex);
    return status;
}

/**
 * @brief Select the clock source for a peripheral.
 *

 * @param peripheralIndex     [Input] Index of the peripheral.
 * @param source              [Input] Clock source to be selected.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Clock_Source_Select( uint32_t peripheralIndex, PeripheralClockSource source)
{
    Std_PCC_Status status = PCC_E_OK;
    /* Prevent changing the clock source if the clock is currently enabled */
    if(PCC->PCCn[peripheralIndex] & PCC_PCCn_CGC_MASK)
    {
        status = PCC_E_NOT_OK;
    }

    /* Set the clock source using the HAL function */
    HAL_Clock_Source_Select( peripheralIndex, source);
    return status;
}

/**
 * @brief Set the clock divider and fraction for a peripheral.
 *

 * @param peripheralIndex     [Input] Index of the peripheral.
 * @param divider             [Input] Clock divider value.
 * @param fraction            [Input] Clock fraction value.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_Clock_Divider_Select( uint32_t peripheralIndex, PeripheralClockDividerSelect divider, PeripheralClockFractionSelect fraction)
{
    Std_PCC_Status status = PCC_E_OK;
    /* Check for invalid divider values or if the clock is already enabled */
    if((divider > PCD_DIVIDE_BY_8) || (PCC->PCCn[peripheralIndex] & PCC_PCCn_CGC_MASK))
    {
        status = PCC_E_NOT_OK;
    }
    /* Additional check for invalid fractional value when divider is set to 1 */
    else if (divider == PCD_DIVIDE_BY_1 && fraction != PCD_FRACTIONAL_VALUE_0)
    {
        status = PCC_E_NOT_OK;
    }

    /* Apply the clock divider and fraction settings using HAL function */
    HAL_Clock_Divider_Select( peripheralIndex, divider, fraction);
    return status;
}

/**
 * @brief De-initialize the specified peripheral.
 *

 * @param peripheralIndex     [Input] Index of the peripheral.
 * @return uint32_t           Returns E_OK if the check is successful, otherwise E_NOT_OK.
 */
Std_PCC_Status PCC_De_Init( uint32_t peripheralIndex)
{
    Std_PCC_Status status = PCC_E_OK;
    /* DDisable the peripheral clock using the HAL function */
    status = HAL_Disable_Peripheral_Clock( peripheralIndex);

    /* Check if the operation was not successful */
    if(PCC_E_OK != status)
    {
        status = PCC_E_NOT_OK;
    }

    return status;
}
