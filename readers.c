#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "readers.h"

pthread_mutex_t mutex; 
pthread_cond_t turn; 

int writers, readers; 
int writing, reading; 
int writersQueue; 
int readersQueue; 

void printMessage() {
    printf("ReaderQ: %d WriterQ: %d [in: R:%d W:%d]\n", (readers-reading), (writers-writing), reading, writing);
}

void * readersHandler(void * args) {
    while(1 == 1) {
        pthread_mutex_lock(&mutex); 
        readersQueue++; 
        
        while(writing) {
            pthread_cond_wait(&turn, &mutex);
        } 

        reading++; 
        pthread_mutex_unlock(&mutex); 

        printMessage(); 

        pthread_mutex_lock(&mutex); 
        reading--; 
        readersQueue--; 
        pthread_cond_broadcast(&turn);
        pthread_mutex_unlock(&mutex); 
        usleep((rand() % 7) + 1); 
    }
}

void * writersHandler(void * args) {
    while(1 == 1) {
        pthread_mutex_lock(&mutex); 
        
        writersQueue++;
        while(reading || writing) {
            pthread_cond_wait(&turn, &mutex); 
        }

        writing++; 
        pthread_mutex_unlock(&mutex); 

        printMessage(); 

        pthread_mutex_lock(&mutex);
        writing--;
        writersQueue--; 
        pthread_cond_broadcast(&turn); 
        pthread_mutex_unlock(&mutex);
        usleep((rand() % 7) + 1); 
    }
}

int main(int argc, char ** argv) {
    srand(time(NULL));

    if(checkArguments(argc, argv) != 0) {
        exit(EXIT_FAILURE);
    }

    pthread_t writersq[writers]; 
    pthread_t readersq[readers]; 

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&turn, NULL); 
    reading = 0;
    writing = 0;
    writersQueue = 0;
    readersQueue = 0;

    int i; 
    for(i = 0; i < writers; i++) {
        if(pthread_create(&writersq[i], NULL, writersHandler, "") != 0) {
            printf("Error while creating thread!\n");
            return -1; 
        }
    }

    for(i = 0; i < readers; i++) {
        if(pthread_create(&readersq[i], NULL, readersHandler, "") != 0) {
            printf("Error while creating thread!\n");
            return -1; 
        }
    }

    for(i = 0; i < writers; i++) {
        if(pthread_join(writersq[i], NULL) != 0) {
            printf("Error while creating thread!\n");
            return -1; 
        }
    }

    for(i = 0; i < readers; i++) {
        if(pthread_join(readersq[i], NULL) != 0) {
            printf("Error while creating thread!\n");
            return -1; 
        }
    }

    pthread_mutex_destroy(&mutex); 
    pthread_cond_destroy(&turn);  

    return 0; 
}

int checkArguments(int argc, char ** argv) {
    if(argc <3) {
        printf("Invalid arguments!\n");
        return -1;
    }

    writers = atoi(argv[1]);
    readers = atoi(argv[2]); 

    if(writers == 0 || readers == 0) {
        printf("Invalid arguments!\n");
        return -1;
    }
    
    return 0;
}