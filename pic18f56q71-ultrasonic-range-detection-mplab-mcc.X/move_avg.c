/**
 *  @brief Source file for the Moving Average module
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


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  Includes                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "move_avg.h"

#include <stddef.h>


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Public definitions                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

moving_average_status_t MovingAverage_Add(moving_average_t * const movingAverage, uint16_t const data)
{
    if (movingAverage == NULL)
    {
        return MOVING_AVERAGE_NULL_PTR;
    }

    uint16_t oldData = 0;

    if (MovingAverage_IsFull(movingAverage))
    {
        ring_buffer_status_t const status = RingBuffer_Pop(movingAverage->ringBuffer, &oldData);
        
        if (status != RING_BUFFER_OK)
        {
            return MOVING_AVERAGE_ERROR;
        }
    }

    ring_buffer_status_t const status = RingBuffer_Push(movingAverage->ringBuffer, data);
    
    if (status != RING_BUFFER_OK)
    {
        return MOVING_AVERAGE_ERROR;
    }

    movingAverage->sum = movingAverage->sum - oldData + data;
    
    return MOVING_AVERAGE_OK;
}

bool MovingAverage_IsFull(moving_average_t const * const movingAverage)
{
    if (movingAverage == NULL)
    {
        return false;
    }

    return RingBuffer_IsFull(movingAverage->ringBuffer);
}

moving_average_status_t MovingAverage_Get(moving_average_t const * const movingAverage, float * const average)
{
    if (movingAverage == NULL || average == NULL)
    {
        return MOVING_AVERAGE_NULL_PTR;
    }

    *average = (float) movingAverage->sum / movingAverage->size;

    return MOVING_AVERAGE_OK;
}