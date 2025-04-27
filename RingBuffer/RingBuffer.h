#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
/****************************************************************************************************************
 *                                                 INCLUSIONS                                                   *
 ****************************************************************************************************************/
#include <stdio.h>

/****************************************************************************************************************
 *                                              TYPE DEFINITIONS                                                *
 ****************************************************************************************************************/
typedef unsigned char uint8_t;
typedef struct {
    uint8_t front;      /* Index of the front element */
    uint8_t tail;       /* Index of the rear element */
    uint8_t size;       /* Size of the queue */
    uint8_t capacity;   /* Capacity of the queue */
    uint8_t *queueArr;  /* Pointer to the array */
} Std_Queue_Types;      /* Structure of the queue */

/****************************************************************************************************************
 *                                              API DECLARATIONS                                                *
 ****************************************************************************************************************/
/**
 * @name queueInit
 *
 * @brief This function is used to initialize the queue
 *
 * @param queue[in/out]: pointer to the queue
 * @param arr[in]: pointer to the array
 * @param capacity[in]: capacity of the queue
 *
 * @return void
 */
void queueInit(Std_Queue_Types* queue, uint8_t* Arr, uint8_t capacity);

/**
 * @name queuePush
 *
 * @brief This function is used to push data to the queue
 *
 * @param queue[in/out]: pointer to the queue
 * @param data[in]: data to push
 *
 * @return void
 */
void queuePush(Std_Queue_Types* queue, uint8_t data);

/**
 * @name queuePop
 *
 * @brief This function is used to pop data from the queue
 *
 * @param queue[in/out]: pointer to the queue
 *
 * @return uint8_t: data popped
 */
uint8_t queuePop(Std_Queue_Types* queue);

#endif /* RINGBUFFER_H_ */
