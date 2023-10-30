/**
 *  @brief Source file for the Ring Buffer module
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

#include "ring_buffer.h"

#include <stddef.h>


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Public definitions                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

ring_buffer_status_t RingBuffer_Push(ring_buffer_t * const ring, ring_buffer_data_t const data)
{
    if (ring == NULL)
    {
        return RING_BUFFER_NULL_PTR;
    }

    uint8_t next = (uint8_t) (ring->head + 1) % ring->size;

    if (next == ring->tail)
    {
        return RING_BUFFER_FULL;
    }

    ring->buffer[ring->head] = data;
    ring->head = next;
    
    return RING_BUFFER_OK;
}

ring_buffer_status_t RingBuffer_Pop(ring_buffer_t * const ring, ring_buffer_data_t * const data)
{
    if (ring == NULL || data == NULL)
    {
        return RING_BUFFER_NULL_PTR;
    }

    if (ring->head == ring->tail)
    {
        return RING_BUFFER_EMPTY;
    }

    *data = ring->buffer[ring->tail];
    ring->tail = (uint8_t) (ring->tail + 1) % ring->size;

    return RING_BUFFER_OK;
}

bool RingBuffer_IsFull(ring_buffer_t const * const ring)
{
    if (ring == NULL)
    {
        return false;
    }

    return ((uint8_t) (ring->head + 1) % ring->size) == ring->tail;
}