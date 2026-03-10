#include "MKL46Z4.h"
#include "Queue.h"
#include "UART0_Init.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static queue_struct_t g_queue;
/*******************************************************************************
 * Code
 ******************************************************************************/
void queue_init()/*init queue*/
{
    uint8_t data_index;
    uint8_t element_index;
    for(element_index = 0; element_index < MAX_QUEUE_SIZE; element_index++)/*set all elements to 0*/
    {
        for(data_index = 0; data_index < MAX_DATA_SREC_SIZE; data_index++)
        {
            g_queue.element[element_index].data[data_index] = 0;
        }
    }
    g_queue.putIndex = 0;
    g_queue.getIndex = 0;
    g_queue.size = 0;
}

bool queue_isEmpty()/*check if queue empty*/
{
    bool ret;
    if(0 == g_queue.size)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool queue_isFull()/*check if queue full*/
{
    bool ret;
    if(MAX_QUEUE_SIZE == g_queue.size)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

void queue_put()/*enqueue*/
{
    if(!queue_isFull())/*not full*/
    {
        g_queue.putIndex = (g_queue.putIndex+1) % MAX_QUEUE_SIZE;
        g_queue.size++;
    }
}

void queue_get()/*dequeue*/
{
    if(!queue_isEmpty())/*not empty*/
    {
        g_queue.getIndex = (g_queue.getIndex+1) % MAX_QUEUE_SIZE;
        g_queue.size--;
    }
}

void Q_getLine(uint8_t ** line)/*get line from queue*/
{
    if(!queue_isFull())
    {
        *line = g_queue.element[g_queue.putIndex].data;
    }
    else
    {
        return;
    }
}

bool queue_getData(uint8_t **line)/*get data from queue*/
{
    bool ret;
    if(!queue_isEmpty())
    {
        ret = true;
        *line = (uint8_t*)g_queue.element[g_queue.getIndex].data;
    }
    else
    {
        ret = false;
    }
    return ret;
}