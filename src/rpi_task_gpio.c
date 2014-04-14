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
	// notify switch to userspace
	//rt_task_set_mode(T_WARNSW, 0, NULL); 
	#ifdef DEBUG
		rt_printf ("Task Start\n");
	#endif
	for(;;) {
		// poll input pin for trigger
		if(digitalRead(INPUT_PIN) != 0){
			//start task marker
			digitalWrite(0, 1);
			#ifdef DEBUG
				rt_printf ("Trigger\n");
			#endif
			// when triggered, do security task
			rt_task_sleep(1000);

			digitalWrite(0, 0);
			//digitalWrite(0, 1);
			while(digitalRead(INPUT_PIN!=0)) {
				// wait for response
			}
		}
		else{
			rt_printf ("0\n");
			delay(1);
			//rt_task_sleep(1);
		}
	}
}
int main (int argc, char *argv[])
{
	// Enable the on-goard GPIO
	wiringPiSetup ();
	// rt print
	rt_print_auto_init(1);
	// turn off paging
	mlockall(MCL_CURRENT|MCL_FUTURE);

	#ifdef DEBUG
	rt_printf ("SecureRT - Test\n");
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
