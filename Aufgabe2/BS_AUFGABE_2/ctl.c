#include "ctl.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void* control(int pid) {
	int run=1;
	printf("CTL gestartet\n");
	while(run) 
		{
printf("ctl running\n");
		switch(getchar()) 
			{
			case '1': //toggle Producer1
//printf("Eingabe1\n");
				if (prod_1_stopped) 
					{
printf("Neustart: Producer 1\n");
					pthread_cond_signal(&prod_1_restart);
					prod_1_stopped = 0;
					} 
				else 
					{
printf("Stopp: Producer 1\n");
					prod_1_stopped = 1;
					}
				break;
			case '2': // toggle Producer2
//printf("Eingabe2\n");
				if (prod_2_stopped) 
					{
printf("Neustart: Producer 2\n");
					pthread_cond_signal(&prod_2_restart);
					prod_2_stopped = 0;
					}	 
				else 
					{
printf("Stopp: Producer 2\n");
					prod_2_stopped = 1;
					}
				break;
			case 'c': 
			case 'C': // toggle Consumer
//printf("Eingabec\n");
				if (cons_stopped) 
					{
					printf("Neustart: Consumer\n");
					pthread_cond_signal(&cons_restart);
					cons_stopped = 0;
					} 
				else 
					{
printf("Stopp: Consumer\n");
					cons_stopped = 1;
					}
				break;
			case 'q':
			case 'Q': // End
				run=0;
				break;
			case 'h':
			case 'H': // Help
				break;
			default:
printf("%");
				break;
			}
		}
printf("terminating\n");
	pthread_mutex_unlock(&rb_mutex);
	pthread_cancel(threads[1]); // prod 1
	pthread_cancel(threads[2]); // prod 2
	pthread_cancel(threads[3]); // consumer
printf("Alle terminiert, beende\n");
	return NULL;
}
