#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "activeObject.h"
#include <stdint.h>

void *run(void *arg)
{
    ActiveObject *this = (ActiveObject *)arg;
    while (!this->stop)
    {
        if (this->isFirst == 1)
        {
            void *data = dequeue(this->queue);
            this->task(data);
        }
        else
        {
            int data = (int)(uintptr_t)dequeue(this->queue);
            if (data == -3)
            {
                this->stop = 1;
            }
            else
            {
                this->task(&data);
            }
            if (this->next != NULL)
            {
                enqueue(this->next->queue, (void *)(uintptr_t)data);
            }
        }
    }
    return NULL;
}

ActiveObject *createActiveObject(TaskFunction task, ActiveObject *nextActiveObject)
{
    ActiveObject *this = malloc(sizeof(ActiveObject));
    if (this == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    this->queue = createQueue();
    if (this->queue == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    this->stop = 0;
    this->isFirst = 0;
    this->next = nextActiveObject;
    this->task = task;
    this->thread = (pthread_t)calloc(1,sizeof(pthread_t));
    if (&(this->thread) == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    if (pthread_create(&(this->thread), NULL, run, this) != 0)
    {
        fprintf(stderr, "failed pthread creation\n");
        exit(1);
    }
    return this;
}
Queue *getQueue(ActiveObject *activeObj)
{
    return activeObj->queue;
}

void stopActiveObject(ActiveObject *activeObj)
{
    activeObj->stop = 1; // stop the loop in the run nicely
    pthread_cancel((pthread_t)(activeObj->thread)); // force stop the loop by cancel thread
    pthread_join((pthread_t)(activeObj->thread), NULL);
    freeQueue(activeObj->queue);
    free(activeObj);
}
