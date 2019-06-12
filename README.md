# readers-writers
Simple solution of readers writers problem (POSIX) using conditional variables and mutex. Includes three solutions: optimal (without starvation), writers (with readers starvation) and readers (with writers starvation). 

# Compiling

gcc -o writers writers.c --pthread 
gcc -o readers readers.c --pthread
gcc -o optimal optimal.c --pthread 

# Usage

Same usage for every program. 

./optimal number_of_writers number_of_readers
