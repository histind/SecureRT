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
		rt_printf ("Task Start\n");
	#endif
	for (;;) {
		// poll input pin for trigger
		if(digitalRead(INPUT_PIN) != 0){
		#ifdef DEBUG
			rt_printf ("Trigger\n");
			rt_printf ("%d\n", digitalRead(INPUT_PIN));
			return;
		#endif
		// when triggered, do security task
		// send response on output pin
		// digitalWrite(1);
		}
		else{
			rt_printf ("%d\n", digitalRead(INPUT_PIN));
			delay(100);
			continue;
		}
	}
}
int main (int argc, char *argv[])
{
	// Enable the on-goard GPIO
	wiringPiSetup ();
	// rt print
	rt_print_auto_init(1);
	// turn off pagin
	mlockall(MCL_CURRENT|MCL_FUTURE);

	#ifdef DEBUG
	rt_printf ("Raspberry Pi - Test\n");
	#endif /*DEBUG*/

	// setup pins
	pinMode (OUTPUT_PIN, OUTPUT);
	pinMode (INPUT_PIN, INPUT);
	int err;
	// create task
	err = rt_task_create(&task_desc,
		"SRT_task",
		TASK_STKSZ,
		TASK_PRIO,
		TASK_MODE);
	if (!err)
		rt_task_start(&task_desc,&task_body,NULL);
	while(1){
		//wait for rt_task
	}
}
void cleanup (void)
{
	rt_printf("\nending...\n");
	rt_task_delete(&task_desc);
}
