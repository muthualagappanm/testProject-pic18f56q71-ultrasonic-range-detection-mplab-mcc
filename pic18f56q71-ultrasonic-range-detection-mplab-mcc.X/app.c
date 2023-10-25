/**
 *  @file app.c
 *  @author Cristian Cristea - M70957
 *  @date August 16, 2023
 *
 *  @brief Source file for the Application module
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

#include "app.h"

#include "move_avg.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Macros and defines                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define MOVING_AVERAGE_SIZE        ( 16 )

#define MIN_DISTANCE               ( 350 )
#define MAX_DISTANCE               ( 9000 )

#define HALF_COUNT_TIME_US         ( 0.164063f )
#define SPEED_OF_SOUND_CM_PER_US   ( 0.034321f )
#define CENTIMETERS_PER_COUNT      ( HALF_COUNT_TIME_US * SPEED_OF_SOUND_CM_PER_US )

/**
 * @brief Offset used to compensate for timing errors.
 * @note This should be calibrated for the available hardware.
 */
#define DISTANCE_OFFSET            ( 2.2f )

#define STATIC_INLINE              __attribute__((always_inline)) static inline


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                            Private (static) API                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Callback function that triggers when the comparator detects a falling
 *        edge on its output. When this callback is triggered, the Universal 
 *        Timer's counter is captured and the value is stored in the counter
 *        variable. Furthermore, the comparator's interrupt is disabled to avoid
 *        detecting a false received echo signal and the print flag is enabled.
 * @return None.
 */
static void CaptureCounterCallback(void);

/**
 * @brief Callback function that triggers when the Control PWM signal's period
 *        is reached. When this callback is triggered, the comparator's 
 *        interrupt flag is cleared and the comparator's interrupt is re-enabled.
 * @return None.
 */
static void ResetComparatorInterruptCallback(void);

/**
 * @brief Checks if the counter variable is valid by comparing it with the
 *        minimum and maximum physically possible counter values.
 * @note The check is performed on the counter value rather than the distance
 *       because the distance value is a floating point number, consequently the
 *       comparison is computationally expensive.
 * @return bool
 * @retval true The counter is within the valid range.
 * @retval false The counter is outside the valid range.
 */
STATIC_INLINE bool IsCounterValid(void);

/**
 * @brief Calculates the distance in centimeters based on the counter value, 
 *        the speed of sound and the frequency of the Universal Timer. It also
 *        applies an offset to the distance value to compensate for timing 
 *        errors.
 * @param[in] counterValue A counter value.
 * @return float The distance in centimeters.
 */
STATIC_INLINE float GetDistance(float const counterValue);

/**
 * @brief Registers the callback functions and enables the global interrupts.
 * @return None.
 */
STATIC_INLINE void InitializeCallbacks(void);

/**
 * @brief Averages the distance values and prints the result.
 * @return None.
 */
STATIC_INLINE void AverageAndPrint(void);


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        Private (static) definitions                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Stores the value of the Universal Timer's counter.
 */
volatile static uint16_t counter = 0;

/**
 * @brief Flag that indicates if the distance should be printed.
 */
volatile static bool newDataAvailable = false;

/**
 * @brief Static allocation of the ring buffer used by the moving average.
 */
static uint16_t storage[MOVING_AVERAGE_SIZE + 1] = { 0 }; 

/**
 * @brief Ring buffer used by the moving average.
 */
static ring_buffer_t ringBuffer = {                      
    .buffer = storage,                        
    .size = MOVING_AVERAGE_SIZE + 1,                         
    .head = 0,                                     
    .tail = 0  
};

/**
 * @brief Moving average structure used for filtering the distance values.
 */
static moving_average_t movingAverage = {                
    .ringBuffer = &ringBuffer,
    .size = MOVING_AVERAGE_SIZE,
    .sum = 0
};

static void CaptureCounterCallback(void)
{
    counter = COUNTER_OnCommandCapture();

    // Disable CMP1's interrupt to avoid detecting a false echo
    PIE1bits.C1IE = 0;

    newDataAvailable = true;
}

static void ResetComparatorInterruptCallback(void)
{
    // Clear CMP1's interrupt flag
    PIR1bits.C1IF = 0;
    
    // Re-enable CMP1's interrupt
    PIE1bits.C1IE = 1;
}

static inline bool IsCounterValid(void)
{
    return ( (MIN_DISTANCE <= counter) && (counter <= MAX_DISTANCE) );
}

static inline float GetDistance(float const counterValue)
{
    return ( counterValue * CENTIMETERS_PER_COUNT + DISTANCE_OFFSET );
}

static inline void InitializeCallbacks(void)
{
    CMP_InterruptCallbackRegister(CaptureCounterCallback);
    PWM_CONTROL_Period_SetInterruptHandler(ResetComparatorInterruptCallback);
    
    INTERRUPT_GlobalInterruptHighEnable(); 
    
    return;
}

static inline void AverageAndPrint(void)
{
    static float meanCounter = 0.0f;
    static uint16_t counterValue = 0;
    
    static moving_average_status_t status = MOVING_AVERAGE_OK;
    
    if (IsCounterValid())
    {
        status = MOVING_AVERAGE_OK;
        
        /**
         * @brief Atomic block to prevent corruption of the current counter value.
         */
        INTERRUPT_GlobalInterruptHighDisable();
        counterValue = counter;
        INTERRUPT_GlobalInterruptHighEnable();

        status = MovingAverage_Add(&movingAverage, counterValue);
        
        if (status != MOVING_AVERAGE_OK)
        {
            /**
             * @brief Error handling.
             * @note This scenario is theoretically impossible.
             */
        }
        
        status = MovingAverage_Get(&movingAverage, &meanCounter);

        if (status != MOVING_AVERAGE_OK)
        {
            /**
             * @brief Error handling.
             * @note This scenario is theoretically impossible.
             */
        }

        printf("Distance: %.02f cm\r\n", GetDistance(meanCounter));
    }

    newDataAvailable = false;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Public definitions                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

inline void Application_Run(void)
{
    SYSTEM_Initialize();
    
    InitializeCallbacks();

    while (true)
    {
        if (!newDataAvailable)
        {
            continue;
        }
      
        AverageAndPrint();
    }
}