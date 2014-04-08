#include <sys/mman.h>
#include <native/task.h>
#include <wiringPi.h>
// task parameters
#define TASK_PRIO 99 /* Highest RT priority */
#define TASK_MODE 0 /* No flags */
#define TASK_STKSZ 0 /* Stack size (use default one) */
// input and output pins
#define OUTPUT_PIN 0
#define INPUT_PIN 1
// debug
#define DEBUG
RT_TASK task_desc;
void task_body (void *cookie)
{ 
	#ifdef DEBUG
		printf ("Task Start");
	#endif
	for (;;) {
		// poll input pin for trigger
		if(digitalRead(INPUT_PIN) != 0){
		#ifdef DEBUG
			printf ("Trigger\n");
			printf ("%d", digitalRead(INPUT_PIN));
		#endif
		// when triggered, do security task
		// send response on output pin
		// digitalWrite(1);
		}
		else{
			printf ("%d", digitalRead(INPUT_PIN));
			continue;
		}
	}
}
int main (int argc, char *argv[])
{
	// Enable the on-goard GPIO
	wiringPiSetup ();

	#ifdef DEBUG
	printf ("Raspberry Pi - Test\n");
	#endif /*DEBUG*/

	// setup pins
	pinMode (OUTPUT_PIN, OUTPUT);
	pinMode (INPUT_PIN, INPUT);
	int err;
	// turn off paging
	mlockall(MCL_CURRENT|MCL_FUTURE);
	// create task
	err = rt_task_create(&task_desc,
		"SRT_task",
		TASK_STKSZ,
		TASK_PRIO,
		TASK_MODE);
	if (!err)
		rt_task_start(&task_desc,&task_body,NULL);
}
void cleanup (void)
{
	rt_task_delete(&task_desc);
}
