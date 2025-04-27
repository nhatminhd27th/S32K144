/**
 * @file RingBuffer.c
 * @author Minh Nguyen Nhat (nhatminhd27th@gmail.com)
 * @brief This file is used to define the functions to handle the ring buffer
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */
/****************************************************************************************************************
 *                                                 INCLUSION                                                    *
 ****************************************************************************************************************/
#include "RingBuffer.h"

/****************************************************************************************************************
 *                                                   MACROS                                                     *
 ****************************************************************************************************************/
#define QUEUE_IS_FULL(queue) ((queue->size) == (queue->capacity))   /* Check if the queue is full */
#define QUEUE_IS_EMPTY(queue) ((queue->size) == 0)                  /* Check if the queue is empty */

/****************************************************************************************************************
 *                                              API DEFINITIONS                                                 *
 ****************************************************************************************************************/
/**
 * @brief This function is used to initialize the queue
 *
 * @param queue[in/out]: pointer to the queue
 * @param arr[in]: pointer to the array
 * @param capacity[in]: capacity of the queue
 *
 * @return void
 */
void queueInit(Std_Queue_Types* queue, uint8_t* arr, uint8_t capacity)
{
    queue->capacity = capacity;
    queue->queueArr = arr;
}

/**
 * @brief This function is used to push data to the queue
 *
 * @param queue[in/out]: pointer to the queue
 * @param data[in]: data to push
 *
 * @return void
 */
void queuePush(Std_Queue_Types* queue, uint8_t data)
{
    if(!QUEUE_IS_FULL(queue))
    {
        queue->queueArr[queue->tail] = data;
        queue->tail = (queue->tail + 1) % queue->capacity;
        queue->size += 1;
    }
    else
    {
        // Queue is full
    }
}

/**
 * @brief This function is used to pop data from the queue
 *
 * @param queue[in/out]: pointer to the queue
 *
 * @return uint8_t: data popped
 */
uint8_t queuePop(Std_Queue_Types* queue)
{
	uint8_t data = 0;

    if(!QUEUE_IS_EMPTY(queue))
    {
        data = queue->queueArr[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size -= 1;
    }
    else
    {
        // Queue is empty
    }

    return data;
}
