#include <sys/mman.h>
#include <native/task.h>
#include <wiringPi.h>
// task parameters
#define TASK_PRIO 99 /* Highest RT priority */
#define TASK_MODE 0 /* No flags */
#define TASK_STKSZ 0 /* Stack size (use default one) */
// input and output pins
#define INPUT_PIN 0
#define OUTPUT_PIN 1
RT_TASK task_desc;
void task_body (void *cookie)
{
for (;;) {
// poll input pin for trigger

// when triggered, do security task
// ...else continue

// send response on output pin

continue;
}
}
int main (int argc, char *argv[])
{
int err;
// turn off paging
mlockall(MCL_CURRENT|MCL_FUTURE);
/* ... */
err = rt_task_create(&task_desc,
"SRT_task",
TASK_STKSZ,
TASK_PRIO,
TASK_MODE);
if (!err)
rt_task_start(&task_desc,&task_body,NULL);
/* ... */
}
void cleanup (void)
{
rt_task_delete(&task_desc);
}
