# C-Projects
A collection of various projects I completed using the C programming language.

Most of these projects have a readme document that outline their usage instructions.

Project Descriptions:

Pascal's Triangle - a C program that implements a utility function to print an associated array; a
function that calculates a specified row of the Pascal’s Triangle in an iterative manner and returns that row in an integer array, and a function that calculates a specified row of the Pascal’s Triangle in a recursive manner and returns that row in an integer array.

Linked-List and File I:O - a C program that utilizes a linked list to store data read from a file stream.

Source Arrays - a C project that implements some functions in a separate source file, and compiles with multiple
source files to build a program. Essentially organizing functions in separate source files. 

buffer - a C project that provides a programming solution to a bounded-buffer problem using producer and consumer processes. The solution uses three semaphores: empty and full, which count the number of empty and full slots in the buffer, and mutex, which is a binary (or mutually exclusive) semaphore that protects the actual insertion or removal of items in the buffer. For this project, standard counting semaphores will be used for empty and full, and, rather than a binary semaphore, a mutex lock will be used to represent mutex. The producer and consumer—running as separate threads—will move items to and from a buffer that is synchronized with these empty, full, and mutex structures. The Pthreads package was a crucial tool used in solving this problem.

matrix - a C project centered in thread-level parallelism. It provides an algorithmic solution for matrix multiplication that exploit multiple threads executing in parallel.

shell - a C project that builds a simple shell interface that accepts user commands, creates a child process, and executes the user commands in the child process. The shell interface provides users a prompt after which the next command is entered. 

shell2 - a C project that serves as a continuation of shell. This time, a history feature is added to the UNIX shell. The history feature allows users to access up to ten most recently entered commands. These commands will be numbered starting at 1 and will continue to grow larger even past 10 (e.g., if the user has entered 35 commands, the ten most recent commands are numbered 26 to 35).

shell3 - a C project that serves as a continuation of shell2. The history feature introduced in shell2 is not persistent (i.e., the shell program does not maintain the command history across different runs). To make it persistent, I modified the shell program to save the contents of the history buffer into a file before it exits. In addition, at the start of the shell program, the previous commands from the saved history file are reloaded.
