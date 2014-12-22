#include <pthread.h>
#include <stdio.h>
#include "rb.c"
#include "producer.c"
#include "consumer.c"
#include "ctl.c"
#include <string.h>

// Gobales
int version = 1;
//char* Author = {"JanBartels","PatrickSteinhauer"};
//int thread_id[] = {0,1,2,3};
int thread_count = 4;
//pthread_t threads[thread_count];
//pthread_mutex_t rb_mutex = PTHREAD_MUTEX_INITIALIZER;

//pthread_cond_t not_empty_condvar = PTHREAD_COND_INITIALIZER;
//pthread_cond_t not_full_condvar = PTHREAD_COND_INITIALIZER;
pthread_cond_t prod_1_restart = PTHREAD_COND_INITIALIZER;
pthread_cond_t prod_2_restart = PTHREAD_COND_INITIALIZER;
pthread_cond_t cons_restart = PTHREAD_COND_INITIALIZER;

pthread_t threads[4];

int prod_1_stopped = 0;
int prod_2_stopped = 0;
int cons_stopped = 0;
int consumer_sleep = 2;
int producer1_sleep = 3;
int producer2_sleep = 3;

// Prototypen
void showHelp();
void showInfo();

void* controller();
void* producer_1();
void* producer_2();
void* consumer();

int main( int argc, char* argv[] )
	{
	showInfo();
	
	// Argumente Checken
/*
	for(int i=1; i<(argc);i++)
		{
		switch(0)
			{
			case strcmp(argv[i],"-h"):
			case strcmp(argv[i],"--help"):
				showHelp();
				goto Ende; // Spr�nge sind unsch�n aber in diesem Fall sinnvoll
				break;
			// ToDO Add more options..
			
			}
		}*/
	
	// Ringpuffer leeren
	p_rb -> p_in = p_start;
    p_rb -> p_out = p_start;
    p_rb -> count = 0;
	
	
	// Threads erstellen
	pthread_create(&threads[0], NULL, controller, (void *) &thread_id[0]);
	pthread_create(&threads[1], NULL, producer_1, (void *) &thread_id[1]);
	pthread_create(&threads[2], NULL, producer_2, (void *) &thread_id[2]);
	pthread_create(&threads[3], NULL, consumer, (void *) &thread_id[3]);
	
	// Auf terminierung warten
	for(int i = 0; i < thread_count; i++) 
		{
		pthread_join(threads[i], NULL);
		}
		
	Ende:
	return 0;
	}

	
void showInfo() 
	{/*
	printf("BS Aufgabe 2\n");
	printf("############\n\n");
	printf("Bearbeiter:\n%s",Author);
	printf("Version: %d",version);*/
	}

void showHelp()
	{
	// ToDO add Help..
	}
	
void *controller( int pid)
	{
	// read input, do something!
	return control(pid);
	}
void *producer_1(int pid)
	{
	// Schreibt alle 3 Sek ein Zeichen in den Puffer (abc..xyz) 
	return producer(pid, &prod_1_restart, &prod_1_stopped, 'a', 'z', producer1_sleep);
	}
void *producer_2(int pid)
	{
	// Schreibt alle 3 Sek ein Zeichen in den Puffer (ABC..XYZ) 
	return producer(pid, &prod_2_restart, &prod_2_stopped, 'A', 'Z', producer2_sleep);
	} /*
void *consumer()
	{
	return 
	// Nimmt alle 2 Sek ein Zeichen aus dem Puffer und gibt es aus
	// Nach 30 zeichen Zeilenwechsel
	}*/