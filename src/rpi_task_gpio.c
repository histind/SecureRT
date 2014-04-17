#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <native/task.h>
#include <wiringPi.h> 
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
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

void handle_errors(){
	ERR_print_errors_fp(stderr);
	abort();


}

int encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * key, unsigned char * iv, unsigned char * ciphertext) {
	EVP_CIPHER_CTX *ctx;
	int len;
	int ciphertext_len;

	// init context
	if(!(ctx = EVP_CIPHER_CTX_new())){
       		 handle_errors();
	}
	// init encryption operation
	if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)){
		handle_errors();
	}
	// obtain encrypted output
	if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)){
		handle_errors();
		//ciphertext_len = len; 
	}
	ciphertext_len=len;
	// finalize 
	if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)){
		handle_errors();
		//ciphertext_len += len;
	}
	ciphertext_len += len;
	EVP_CIPHER_CTX_free(ctx);
	return ciphertext_len;

}
void task_body (void *cookie)
{
        int ciphertext_len; 
        unsigned char key[] = "01234567890123456789012345678901";
	unsigned char iv[] = "01234567890123456";
        unsigned char plaintext[] = "the quick brown fox jumps over the lazy dog";
        unsigned char ciphertext[128];
	// init library
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);  
	// notify switch to userspace
	//rt_task_set_mode(T_WARNSW, 0, NULL); 
	#ifdef DEBUG
		rt_printf ("Task Start\n");
		delay(1000);
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
			//rt_printf("%s\n", plaintext);
			//rt_task_sleep(100000);
			//delay(100);
			ciphertext_len = encrypt(plaintext, strlen(plaintext), key, iv, ciphertext);
			//rt_printf("Ciphertext is %d:\n", ciphertext_len);
			//BIO_dump_fp(stdout, ciphertext, ciphertext_len);
			//EVP_cleanup();
			//ERR_free_strings();
			digitalWrite(0, 0);
			while(digitalRead(INPUT_PIN!=0)) {
				// wait for response
			}
		}
		else{
			//rt_printf ("0\n");
			//delay(1);
			//rt_task_sleep(1);
		}
	}
	//EVP_cleanup();
	//ERR_free_strings();
}
int main (int argc, char *argv[])
{
	// Enable the on-board GPIO
	wiringPiSetup ();
	// rt print
	rt_print_auto_init(1);
	// turn off paging
	mlockall(MCL_CURRENT|MCL_FUTURE);

	#ifdef DEBUG
	rt_printf ("SecureRT - Test\n");
	delay(1000);
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
	return(0);
}
void cleanup (void)
{
	rt_printf("\nending...\n");
	rt_task_delete(&task_desc);
}
