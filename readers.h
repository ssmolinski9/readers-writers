/**
 * @file readers.h 
 * @brief Solution for writers-readers problem with writers starvation.
 * @author Michał Fiłończuk
 * @author Sebastian Smoliński
 * @author Ernest Stachelski
 * @version 1.3.
 */
#ifndef READERS_H
#define READERS_H

/**
 * @brief Prints actual state of writers and readers inside the library and in the queue.
 * 
 */
void printMessage();

/**
 * @brief Handles state of readers.
 * 
 * @param args unused
 * @return void* unused
 */
void * readersHandler(void * args);

/**
 * @brief Handles state of writers.
 * 
 * @param args unused.
 * @return void* unused.
 */
void * writersHandler(void * args);

/**
 * @brief Checks if arguments are valid.
 * 
 * @param argc number of arguments.
 * @param argv array of arguments.
 * @return int -1 on error or 0 otherwise.
 */
int checkArguments(int argc, char ** argv);

#endif