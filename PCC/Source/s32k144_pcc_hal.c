/**
 * @file HAL_PCC_Module.c
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
#include "../src/Driver/PCC/Include/s32k144_PCC_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t clock = 48000000;
uint32_t HAL_SystemClock_Config (SCG_ClockSource_t source)
{
    switch (source)
    {
        case SCG_CLOCK_SOSC:
            SCG->SOSCCSR = 0; /* Reset SOSCCSR */
            SCG->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;  /* Unlock SOSCCSR for configuration */
            SCG->SOSCCSR &= ~SCG_SOSCCSR_SOSCEN_MASK; /* Disable SOSC for configuration */

            /* External crystal oscillator */
            SCG->SOSCCFG = SCG_SOSCCFG_RANGE(2) | SCG_SOSCCFG_EREFS_MASK;
            SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK; /* Enable SOSC */

            /* Wait for SOSC to be valid */
            while (!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK))
            {

            }
            break;

        case SCG_CLOCK_SIRC:
            SCG->SIRCCSR = 0; /* Reset SIRCCSR */
            SCG->SIRCCSR &= ~SCG_SIRCCSR_LK_MASK;    /* Unlock SIRCCSR for configuration */
            SCG->SIRCCSR &= ~SCG_SIRCCSR_SIRCEN_MASK; /* Disable SIRC for configuration */

            /* Enable SIRC */
            SCG->SIRCCSR = SCG_SIRCCSR_SIRCEN_MASK;

            /* Wait for SIRC to be valid */
            while (!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK))
            {

            }
            break;

        case SCG_CLOCK_FIRC:
            SCG->FIRCCSR = 0; /* Reset FIRCCSR */
            SCG->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;    /* Unlock FIRCCSR for configuration */
            SCG->FIRCCSR &= ~SCG_FIRCCSR_FIRCEN_MASK; /* Disable FIRC for configuration */

            /* Enable FIRC */
            SCG->FIRCCSR = SCG_FIRCCSR_FIRCEN_MASK;

            /* Wait for FIRC to be valid */
            while (!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK))
            {

            }
            break;

        case SCG_CLOCK_SPLL:
            SCG->SPLLCSR = 0; /* Reset SPLLCSR */
            SCG->SPLLCSR &= ~SCG_SPLLCSR_LK_MASK;    /* Unlock SPLLCSR for configuration */
            SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK; /* Disable SPLL for configuration */

            /* Enable SPLL */
            SCG->SPLLCSR = SCG_SPLLCSR_SPLLEN_MASK;

            /* Wait for SPLL to be valid */
            while (!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
            {

            }
            break;

        default:
            // Không cần trả về mã lỗi, chỉ thực hiện các thao tác cấu hình
            break;
    }
}


/**
 * @brief This bit shows whether the peripheral is present on this device.
 *

 * @param peripheralIndex            [Input] Index of the peripheral to check.
 * @return uint32_t                  Returns 0 if the check is successful
 */
uint32_t HAL_Check_PR( uint32_t peripheralIndex)
{
    uint32_t PR_bit = (PCC->PCCn[peripheralIndex] & PCC_PCCn_PR_MASK) >> PCC_PCCn_PR_SHIFT;
    return (PR_bit == 1) ? PR_BIT_SET : PR_BIT_CLEAR;
}

/**
 * @brief Enable the clock for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Enable_Peripheral_Clock(uint32_t peripheralIndex)
{
    /* Set the CGC bit to enable the clock. */
    PCC->PCCn[peripheralIndex] |= PCC_PCCn_CGC(1);
    return 0;
}

/**
 * @brief select the clock source for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @param source                    [Input] Clock source to be set for the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Source_Select( uint32_t peripheralIndex, PeripheralClockSource source)
{
    /* Clear the CGC bit before setting the source. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    /* Set the PCS bits to select the clock source. */
    PCC->PCCn[peripheralIndex] |= (uint32_t)(source << PCC_PCCn_PCS_SHIFT);
    return 0;
}

/**
 * @brief Set the clock divider and fraction for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral.
 * @param divider                   [Input] Clock divider value to set.
 * @param fraction                  [Input] Clock fraction value to set.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Divider_Select(uint32_t peripheralIndex, PeripheralClockDividerSelect divider, PeripheralClockFractionSelect fraction)
{
    /* Clear the CGC bit before setting the divider and fraction. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    /* Set the divider bits. */
    PCC->PCCn[peripheralIndex] |= (uint32_t)(divider << PCC_PCCn_CGC_SHIFT);
    /* Set the fraction bits. */
    PCC->PCCn[peripheralIndex] |= (uint32_t)(fraction << PCC_PCCn_FRAC_SHIFT);
    return 0;
}

/**
 * @brief Disable the clock
 *
 * @param peripheralIndex           [Input] Index of the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Disable_Peripheral_Clock(uint32_t peripheralIndex)
{
    /* Clear the CGC bit to disable the clock. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    return 0;
}
