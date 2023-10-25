/**
 *  @file ring_buffer.h
 *  @author Cristian Cristea - M70957
 *  @date August 18, 2023
 *
 *  @brief Header file for the Ring Buffer module
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


#ifndef RING_BUFFER_H
#define	RING_BUFFER_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  Includes                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        Typedefs, enums and structs                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Ring buffer data type.
 */
typedef uint16_t ring_buffer_data_t;

/**
 * @brief Ring buffer structure type.
 */
typedef struct RING_BUFFER
{
    ring_buffer_data_t * const buffer; /** Pointer to the storage buffer. */
    uint8_t const size;      /** Size of the storage buffer. */
    uint8_t head;            /** Index of the head of the ring buffer. */
    uint8_t tail;            /** Index of the tail of the ring buffer. */
} ring_buffer_t;

/**
 * @brief Ring buffer status return type.
 */
typedef enum RING_BUFFER_STATUS
{
    RING_BUFFER_OK       = 0x00, /** Operation successful. */
    RING_BUFFER_FULL     = 0x01, /** Operation failed, ring buffer is full. */
    RING_BUFFER_EMPTY    = 0x02, /** Operation failed, ring buffer is empty. */
    RING_BUFFER_NULL_PTR = 0x03, /** Operation failed, null pointer passed. */
} ring_buffer_status_t;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 Public API                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pushes data into the ring buffer. If the ring buffer is not full, the
 *        element is pushed and the head is incremented. If the ring buffer is
 *        full, the element is not pushed and an error is returned.
 * @param[in,out] ring Pointer to the ring buffer structure.
 * @param[in] data Data to be pushed into the ring buffer.
 * @return ring_buffer_status_t 
 * @retval RING_BUFFER_OK Operation successful.
 * @retval RING_BUFFER_FULL Operation failed, ring buffer is full.
 * @retval RING_BUFFER_NULL_PTR Operation failed, null pointer passed.
 */
ring_buffer_status_t RingBuffer_Push(ring_buffer_t * const ring, ring_buffer_data_t const data);

/**
 * @brief Pops data from the ring buffer. If the ring buffer is not empty, the
 *        element is popped and the tail is incremented. If the ring buffer is 
 *        empty, an error is returned.
 * @param[in,out] ring Pointer to the ring buffer structure.
 * @param[out] data Data popped from the ring buffer.
 * @return ring_buffer_status_t 
 * @retval RING_BUFFER_OK Operation successful.
 * @retval RING_BUFFER_EMPTY Operation failed, ring buffer is empty.
 * @retval RING_BUFFER_NULL_PTR Operation failed, null pointer passed.
 */
ring_buffer_status_t RingBuffer_Pop(ring_buffer_t * const ring, ring_buffer_data_t * const data);

/**
 * @brief Checks if the ring buffer is full.
 * @param[in] ring Pointer to the ring buffer structure.
 * @return bool 
 * @retval true Ring buffer is full.
 * @retval false Ring buffer is not full or null pointer passed.
 */
bool RingBuffer_IsFull(ring_buffer_t const * const ring);


#endif	/* RING_BUFFER_H */

