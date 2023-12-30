#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define N 1200
#define M 1000
#define P 500
#define MAX 5 // Maximum of 5 threads (Extra credit)

/* Global Variables */
/* Matrix(N x M) x (M x P) = C1(N x P) */
int a[N][M], b[M][P], c[N][P], C1[N][P], threadCount, status;

/* function prototypes */
void c1Matrix();
void print_matrix(int c[N][P]);
void matrix_A(int a[N][M]);
void matrix_B(int b[M][P]);
/* multiplication thread */
void *multiply(void *param);

/* main function */
int main(int argc, char *argv[]){
    /* defining max number of threads (5),
    including thread attributes for the matrix, and setting time variables */
    struct timeval start, finish;
    pthread_t tid_matrix[MAX];
    pthread_attr_t attr_matrix; 
    
    /* checking if the correct number of arguments is passed. */
    if(argc != 2) {
        printf("Error: pass only 1 argument. \n");
        // terminate program if more or less than 1 argument is passed
        exit(1); 
    }
    
    /* get user input and begin running threads */
    int input = atoi(argv[1]); 
    threadCount = 2; 
    pthread_attr_init(&attr_matrix);
    
    /* initialize matrices */
    matrix_A(a); 
    matrix_B(b); 
    
    /* set start/finish times for C1 and run multiplication */
    gettimeofday(&start, NULL); 
    c1Matrix();                
    gettimeofday(&finish, NULL);
    /* print C1 (first thread) calc time */
    printf("Threads	Seconds Errors\n");
    printf("1       %.2f    ",((finish.tv_sec * 1000000 + finish.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
    if(status == 0){
            printf("No errors\n");
        }
    

    /* create multiplication threads */
    while(threadCount <= input){
    int k; // declare variables
    long j;
    
        gettimeofday(&start, NULL);
        // loop through threadCount
        for(j = 0; j < threadCount; j++) {
            status = pthread_create(&tid_matrix[j],&attr_matrix,multiply,(void*)j);
            if(status!=0){
                // print error if the status isn't 0
                printf("Error: cannot create thread");
                exit(-1);
            }
        }
        /* wait for other threads to finish executing */
        for(k = 0; k < threadCount; k++) {
            pthread_join(tid_matrix[k],NULL);
        }
        /* Print results */
        gettimeofday(&finish, NULL);
        printf("%d       %.2f    ",threadCount,((finish.tv_sec * 1000000 + finish.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
        // check if there are any errors
        if(status == 0){
            printf("No errors\n");
        }
        threadCount++;
    }
    
    exit(0);
}

/* initializing matrix A */
void matrix_A(int a[N][M]){
    int i;
    int k;
    for(i = 0; i < N; i++){
        for(k = 0; k < M; k++){
            a[i][k] = i + 1;
        }
    }
}

/* initializing matrix B */
void matrix_B(int b[M][P]){
    int i;
    int k;
    for(i = 0; i < M; i++){
        for(k = 0; k < P; k++){
            b[i][k] = i + k;
        }
    }
}

/*  initializing matrix C1 */
void c1Matrix(){
    int i;
    int j;
    int k;
    for(i = 0; i < N; i++){
        for(j = 0; j < P; j++){
            C1[i][j]=0;
            for(k = 0; k < M; k++){
                C1[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
}

/* multiplication function definition */
void *multiply(void *param){
    int i, j; // declaring variables
    long k;
    long thread = (long)param, firstInRow = (thread* N)/threadCount, lastInRow = ((thread+1)* N)/threadCount;

    /* multiplcation algorithm */
    /* A x B = C */
    for(k = firstInRow; k < lastInRow; k++){
        for(i =0; i < P; i++){
            // defining matrix C
            c[i][j]=0;
            for(j = 0; j < M; j++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return 0; 
}
