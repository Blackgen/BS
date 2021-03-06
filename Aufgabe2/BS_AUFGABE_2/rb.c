#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "rb.h"
#define MAX 16

pthread_mutex_t rb_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty_condvar = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full_condvar = PTHREAD_COND_INITIALIZER;
int thread_id[4] = {0,1,2,3};

typedef struct {
    int buffer[MAX];
    int *p_in;
    int *p_out;
    int count;
}rb;
rb x = {{0}, NULL, NULL, 0};
rb *p_rb = &x;


/*
void * write_c(void * pid) {
        int i = 0;
        int z_var = 0;
        // kein static erforderlich, da jeder Thread seinen eigenen  Kontext hat
        printf("Start Schreiben; %d: \n", * (int * ) pid);
        while (1) {
            i++;
            z_var++;
            if (z_var > 9) z_var = 0;
            pthread_mutex_lock( & rb_mutex);
            while (p_rb - > p_in == p_rb - > p_out && p_rb - > count == MAX) {
                printf("Full: wait\n");
                pthread_cond_wait( & not_full_condvar, & rb_mutex);
                printf("Aufgewacht: count %d, Thread_Nr. %d\n",
                    p_rb - > count, * (int * ) pid);
            } 
			* (p_rb - > p_in) = z_var;
            (p_rb - > p_in) ++;
            if ((p_rb - > p_in) > p_end) {
                p_rb - > p_in = p_start;
            }
            (p_rb - > count) ++;
            if (p_rb - > count != 0) {
                printf("Buffer nicht leer, signalisiert\n");
                pthread_cond_signal( & not_empty_condvar);
            }
            pthread_mutex_unlock( & rb_mutex);
            sleep(1);
        }
        return (NULL);
	}
	
void * read_rb(void * pid) {
    int i = 0;
    printf("Start Lesen; %d: \n", * (int * ) pid);
    while (1) {
        i++;
        pthread_mutex_lock( & rb_mutex);
        while (p_rb - > count == 0) {
            printf("Empty: wait\n");
            pthread_cond_wait( & not_empty_condvar, & rb_mutex);
            printf("Aufgewacht: count %d, Thread_Nr. %d\n",
                p_rb - > count, * (int * ) pid);
        }
        (p_rb - > count) --;
        printf("Ältestes Zeichen ausgeben: %d:\n", * (p_rb - > p_out));
        (p_rb - > p_out) ++;
        if ((p_rb - > p_out) > p_end) {
            p_rb - > p_out = p_start;
        }
        if (p_rb - > count <= MAX) {
            printf("Buffer nicht voll, signalisiert\n");
            pthread_cond_signal( & not_full_condvar);
        }
        pthread_mutex_unlock( & rb_mutex);
        sleep(1);
    }
    return (NULL);
}
*/