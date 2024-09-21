
#include "worker.h"

#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "static_mem.h"



#define WORKER_QUEUE_LENGTH 5

struct worker_work {
  void (*function)(void*);
  void* arg;
};

static xQueueHandle workerQueue;

STATIC_MEM_QUEUE_ALLOC(workerQueue, WORKER_QUEUE_LENGTH, sizeof(struct worker_work));

void workerInit()
{
  if (workerQueue)
    return;

  workerQueue = STATIC_MEM_QUEUE_CREATE(workerQueue);

}

bool workerTest()
{
  return (workerQueue != NULL);
}

void workerLoop()
{
  struct worker_work work;

  if (!workerQueue)
    return;

  while (1)
  {
    xQueueReceive(workerQueue, &work, portMAX_DELAY);

    if (work.function)
      work.function(work.arg);
  }
}

int workerSchedule(void (*function)(void*), void *arg)
{
  struct worker_work work;

  if (!function)
    return ENOEXEC;

  work.function = function;
  work.arg = arg;
  if (xQueueSend(workerQueue, &work, 0) == pdFALSE)
    return ENOMEM;

  return 0;
}
