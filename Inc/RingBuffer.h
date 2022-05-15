/**
 * @file RingBuffer.h
 * @author İsmail Enes Bilgin (bilginenesismail@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * @note See the http://www.fourwalledcubicle.com/files/LightweightRingBuff.h for the license information.
 */

#ifndef __RING_BUFFER_H_
#define __RING_BUFFER_H_

/**********************************************************************
 * Includes
 *********************************************************************/
#include <stdint.h>
#include <stdbool.h>

/**********************************************************************
 * Macros
 *********************************************************************/
#define BUFFER_SIZE         255         /* Size of each ring buffer, in data elements-must be between 1 and 255. */

#define RingBuffer_Data_t   uint8_t     /* Type of data to store into the buffer. */

/* Datatype which may be used to store the count of data stored in a buffer, retrived via a call \ref RingBuffer_getCount(). */
#if (BUFFER_SIZE <= 0xFF)
    #define RingBuffer_Count_t  uint8_t
#else
    #define RingBuffer_Count_t  uint16_t
#endif


/**********************************************************************
 * Type Definitions
 *********************************************************************/

/**
 * @brief The define for a new ring buffer object. Buffers should be initialized via a call to 
 * \ref RingBuffer_InitBuffer() before use.
 * 
 */
typedef struct{
    RingBuffer_Data_t       sBuffer[BUFFER_SIZE];   /**< Internal ring buffer data, referenced by the buffer pointers. */
    RingBuffer_Data_t *     psIn;                   /**< Current storage location in the circular buffer. */
    RingBuffer_Data_t *     psOut;                  /**< Current retrieval location in the circular buffer. */ 
    RingBuffer_Count_t      sCount;                 /**< */
}RingBuffer_Handler_t;

/**********************************************************************
 * Inline Functions
 *********************************************************************/

/**
 * @brief Initializes a ring byuffer ready for use. Buffers must be initialized via this function before
 * any operations are called upon them. Already initialized buffers may be reset by re-initializing them
 * using this function.
 * 
 * @param Buffer IN/OUT
 *               Pointer to a ring buffer structure to initialize
 */
static inline void RingBuffer_Init(RingBuffer_Handler_t * const Buffer){
    // Set next element to the start of the ring buffer.
    Buffer->psIn = Buffer->sBuffer;

    // Set last element to the start of the ring buffer.
    Buffer->psOut = Buffer->sBuffer;

    // Set the count value to zero.
    Buffer->sCount = 0;
}

/**
 * @brief Retrives the minimum number of bytes stored in a particular buffer. This value is computed by entering
 * an atomic lock on the buffer while the IN and OUT locations are fetched, so that when reading cannot be modified
 * while the computation takes place. This value should be cached when reading out the contents of the buffer, so that 
 * as small a time possible is spent in a atomic lock.
 * 
 * @note The value returned by this function is guaranteed to only by the minimum number of bytes stored in the given buffer;
 * this value may change as other threads write new data and so the returned number should be used only to determin how many
 * successive reads may safely be performed on the buffer.
 * 
 * @param Buffer IN
 *               Pointer to a ring buffer structure whose count is to be computed
 * 
 * @return RingBuffer_Count_t OUT
 *                            Value to ring buffer 
 */
static inline RingBuffer_Count_t RingBuffer_getCount(RingBuffer_Handler_t * const Buffer){
    // Get the count value.
    return Buffer->sCount;
}

/**
 * @brief Atomically determines if the specified ring buffer contains any data. This should be tested before removing data from
 * data from the buffer, to ensure that the buffer does not underflow.
 * 
 * If the data is to be removed in a loop, store the total number of bytes stored iint the buffer 
 * (via a call to the \ref RingBuffer_getCount() function) in a temporary variable to redıce the time spent in atomicity locks.
 * 
 * @param Buffer IN/OUT
 *               Pointer to a ring buffer structure to insert into,
 * 
 * @return true If the buffer countains no free space, false otherwise
 */
static inline bool RingBuffer_isEmpty(RingBuffer_Handler_t* const Buffer){
    // Check the count value is equal to zero.
    return (RingBuffer_getCount(Buffer) == 0);
}

/**
 * @brief Inserts an element into the ring buffer.
 * 
 * @note Only one execution thread (main program thread or an ISR) may insert into a single buffer
 *       otherwise data corruption may occur. Insertion and removal may occur from different execution
 *       threads.
 * 
 * @param Buffer IN/OUT
 *               Pointer to a ring buffer structure to insert into
 * @param Data   IN
 *               Data element to insert the buffer
 */
static inline void RingBuffer_insert(RingBuffer_Handler_t* const Buffer, const RingBuffer_Data_t Data){
    // Put the data to the next element of the ring buffer.
    *Buffer->psIn = Data;

    // Check the next element equals the start of the ring buffer.
    if(++Buffer->psIn == &Buffer->sBuffer[BUFFER_SIZE]){
        Buffer->psIn = Buffer->sBuffer;
    }

    // Increase the count value.
    Buffer->sCount++;
}

/**
 * @brief Removes an element from the ring buffer.
 * 
 * @note Only one execution thread (main program thread or an ISR) may remove from a sinle buffer
 *       otherwise data corruption may occur. Insertion and removal may occur from different execution
 *       threads.
 * 
 * @param Buffer IN/OUT
 *               Pointer to a ring buffer structure to retrieve from 
 * 
 * @return RingBuffer_Data_t Next data element stored in the buffer.
 */
static inline RingBuffer_Data_t RingBuffer_remove(RingBuffer_Handler_t * const Buffer){
    // Get data from the last element of the ring buffer.
    RingBuffer_Data_t Data = *Buffer->psOut;

    // Check the last element equals the last element of the ring buffer.
    if(++Buffer->psOut == &Buffer->sBuffer[BUFFER_SIZE]){
        Buffer->psOut = Buffer->sBuffer;
    }
    
    // Decrease the count value.
    Buffer->sCount--;

    return Data;
}


#endif /* __RING_BUFFER_H_ */

/* EOF */