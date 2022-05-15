/**
 * @file main.c
 * @author İsmail Enes Bilgin (bilginenesismail@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "RingBuffer.h"

void RingBuffer_TestOneData(void);
void RingBuffer_TestFull(void);

/**
 * @brief Function Entry Point
 * 
 * @return int 
 */
int main(void){
    // Call test one data for ring buffer
    RingBuffer_TestOneData();

    // Call full test 
    RingBuffer_TestFull();

    return 0;
}

/**
 * @brief The test function for the initialization ring buffer,
 * insert a data, and remove.
 * 
 */
void RingBuffer_TestOneData(void){
    RingBuffer_Handler_t myRingBuffer;

    printf("Initialization the Ring Buffer\n\r");
    RingBuffer_Init(&myRingBuffer);
    printf("Ring Buffer Empty Query : %d\n\r", RingBuffer_isEmpty(&myRingBuffer));

    printf("Insert the data(10) to ring buffer. Ring Buffer Counter Value : %d\n\r", RingBuffer_getCount(&myRingBuffer));
    RingBuffer_insert(&myRingBuffer, 10);
    printf("After insertaion Ring Buffer Counter Value : %d\n\r", RingBuffer_getCount(&myRingBuffer));

    printf("Remove the data(10) to ring buffer. Ring Buffer Counter Value : %d\n\r", RingBuffer_getCount(&myRingBuffer));
    printf("Removed Value : %d \n\r", RingBuffer_remove(&myRingBuffer));
    printf("After Removing Ring Buffer Counter Value : %d\n\r", RingBuffer_getCount(&myRingBuffer));
}

/**
 * @brief The test function for the initialization ring buffer,
 * and fill buffer to full, and remove the buffer.
 * 
 */
void RingBuffer_TestFull(void){
    RingBuffer_Handler_t myRingBuffer;

    printf("Initialization the Ring Buffer\n\r");
    RingBuffer_Init(&myRingBuffer);
    printf("Ring Buffer Empty Query : %d, Ring Buffer counter value : %d\n\r",
            RingBuffer_isEmpty(&myRingBuffer),
            RingBuffer_getCount(&myRingBuffer));
    
    printf("Fill to buffer as full. (0 - 255)\n\r");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++){
        RingBuffer_insert(&myRingBuffer, i);
        printf("Ring Buffer Counter Value : %d, Inserted Data : %d\n\r", RingBuffer_getCount(&myRingBuffer), i);
    }

    printf("Remove to buffer.\n\r");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++){
        printf("Ring Buffer Counter Value : %d, Removed Data : %d\n\r", RingBuffer_getCount(&myRingBuffer), RingBuffer_remove(&myRingBuffer));
    }

        printf("Fill to buffer as full. (0 - 255)\n\r");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++){
        RingBuffer_insert(&myRingBuffer, i);
        printf("Ring Buffer Counter Value : %d, Inserted Data : %d\n\r", RingBuffer_getCount(&myRingBuffer), i);
    }

        printf("Remove to buffer.\n\r");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++){
        printf("Ring Buffer Counter Value : %d, Removed Data : %d\n\r", RingBuffer_getCount(&myRingBuffer), RingBuffer_remove(&myRingBuffer));
    }
}