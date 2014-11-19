#incluce <pthread.h>
#include <stdio.h>

// Gobales
int version = 1;
char* Author = {"JanBartels","PatrickSteinhauer"};
int thread_id[] = {0,1,2,3};
int thread_count = 4;
pthread_t 	threads[thread_count];

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
	for(int i=1; i<argc,i++)
		{
		switch(0)
			{
			case strcmp(argv[i],"-h"):
			case strcmp(argv[i],"--help"):
				showHelp();
				goto Ende; // Sprünge sind unschön aber in diesem Fall sinnvoll
				break;
			// ToDO Add more options..
			
			}
		}
		
	// Threads erstellen
	pthread_create(&threads[0], NULL, controller, (void *)&thread_id[0]);
	pthread_create(&threads[1], NULL, producer_1, (void *)&thread_id[1]);
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
	{
	printf("BS Aufgabe 2\n");
	printf("############\n\n");
	printf("Bearbeiter:\n%s",Author);
	printf("Version: %d",version);
	}

void showHelp()
	{
	// ToDO add Help..
	}
	
void* controller()
	{
	// read input, do something!
	}
void* producer_1()
	{
	// Schreibt alle 3 Sek ein Zeichen in den Puffer (abc..xyz) 
	}
void* producer_2()
	{
	// Schreibt alle 3 Sek ein Zeichen in den Puffer (ABC..XYZ) 
	}
void* consumer()
	{
	// Nimmt alle 2 Sek ein Zeichen aus dem Puffer und gibt es aus
	// Nach 30 zeichen Zeilenwechsel
	}