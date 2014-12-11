//#include "producer.h"
//#include "rb.h"

void writeBuffer(char );

void* producer(int pid, pthread_cond_t *restart, int *waitFlag, char rangeA, char rangeB, int waitTime)
	{
	printf("Producer started; %d: \n", pid);
	
	int cur=rangeA;
	
	while(1)
		{
		cur++;
		if (cur>rangeB) cur=rangeA;
		
		// Mutex verriegeln
		pthread_testcancel();
		pthread_mutex_lock(&rb_mutex);
		
		while(*waitFlag || (p_rb -> p_in == p_rb -> p_out && p_rb -> count == MAX)) 
			{
			if (*waitFlag) 
				{
				printf("Full,Wait\n");
				pthread_cond_wait(restart, &rb_mutex);
				printf("Aufgewacht: count %d, Thread_Nr. %d\n",p_rb -> count,  pid);
				}
			else 
				{
printf("hi\n");
				pthread_cond_wait(&not_full_condvar, &rb_mutex);
				
				}
			}
		// check if buffer voll oder prod sttopped
		writeBuffer(cur);
		
		pthread_mutex_unlock(&rb_mutex);
		
		sleep(waitTime);
		}
	return NULL;
	}
	
void writeBuffer(char c)
	{
	//printf("IN:->%c\n", c);
	*(p_rb -> p_in) = c;
	// input zeiger vorschieben
	(p_rb -> p_in)++;
	// zirkulien des Zeigers garantieren
	if((p_rb -> p_in) > p_end)		p_rb -> p_in = p_start;

	// belegung des Puffers erhöhen
	(p_rb -> count)++;

	// Signal an den Consumer, dass der Puffer gefüllt ist
	if(p_rb -> count != 0)		pthread_cond_signal(&not_empty_condvar);
	}