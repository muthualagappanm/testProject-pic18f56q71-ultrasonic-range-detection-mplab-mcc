/**
 *  @brief Header file for the Moving Average module
 *
 *  @copyright (c) 2023 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany
 *  Microchip software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 *  NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 *  RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 *  DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 **/


#ifndef MOVE_AVG_H
#define	MOVE_AVG_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  Includes                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "ring_buffer.h"

#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        Typedefs, enums and structs                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Moving average structure type.
 */
typedef struct MOVING_AVERAGE
{
    ring_buffer_t * const ringBuffer; /** Pointer to the ring buffer structure. */
    uint8_t const size;               /** Size of the moving average. */
    uint32_t sum;                     /** Current sum of the moving average. */
} moving_average_t;

/**
 * @brief Moving average status return type.
 */
typedef enum MOVING_AVERAGE_STATUS
{
    MOVING_AVERAGE_OK       = 0x00, /** Operation successful. */
    MOVING_AVERAGE_ERROR    = 0x01, /** Operation failed. */
    MOVING_AVERAGE_NULL_PTR = 0x02, /** Operation failed, null pointer passed. */
} moving_average_status_t;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 Public API                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Adds a new data point to the moving average.
 * @param[in,out] movingAverage Pointer to the moving average structure.
 * @param[in] data New data point to be added to the moving average.
 * @return moving_average_status_t
 * @retval MOVING_AVERAGE_OK Operation successful.
 * @retval MOVING_AVERAGE_ERROR Operation failed.
 */
moving_average_status_t MovingAverage_Add(moving_average_t * const movingAverage, uint16_t const data);

/**
 * @brief Checks if the moving average buffer is full.
 * @param[in] movingAverage Pointer to the moving average structure.
 * @return bool
 * @retval true Moving average buffer is full.
 * @retval false Moving average buffer is not full or null pointer passed.
 */
bool MovingAverage_IsFull(moving_average_t const * const movingAverage);

/**
 * @brief Gets the current moving average value.
 * @param[in] movingAverage Pointer to the moving average structure.
 * @param[out] average Pointer to the variable where the average will be stored.
 * @return moving_average_status_t
 * @retval MOVING_AVERAGE_OK Operation successful.
 * @retval MOVING_AVERAGE_NULL_PTR Operation failed, null pointer passed.
 */
moving_average_status_t MovingAverage_Get(moving_average_t const * const movingAverage, float * const average);


#endif	/* MOVE_AVG_H */

