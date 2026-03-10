#ifndef _Queue_H_
#define _Queue_H_
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
* Definitions
*******************************************************************************/
#define MAX_DATA_SREC_SIZE   78
#define MAX_QUEUE_SIZE       4

typedef struct
{
    uint8_t data[MAX_DATA_SREC_SIZE];
} queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
} queue_struct_t;
/*******************************************************************************
* Function
*******************************************************************************/

/*
 * @brief get line from queue
 * @param line is pointer to line in queue
*/
void Q_getLine(uint8_t **line);

/*
 * @brief init queue
*/
void queue_init();

/*
 * @brief check queue if empty
*/
bool queue_isEmpty ();

/*
 * @brief check queue if full
*/
bool queue_isFull();

/*
 * @brief enqueue
*/
void queue_put(void);

/*
 * @brief dequeue
*/
void queue_get(void);

/*
 * @brief get data from queue
 * @param line is pointer to line in queue
*/
bool queue_getData(uint8_t **line);

#endif /* _Queue_H_ */