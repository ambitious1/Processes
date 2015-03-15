    #include<stdio.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<sys/wait.h>
    #include<sys/time.h>
    #include<termios.h>
    #include "cs451project_H.h"

    char *Ending(int, int);
    unsigned long long int fib(int); /* Function Prototype for Recursive Fibonacci Funct. */
    void PressEnterToContinue(void); /* Function Prototype for Press Enter funct. */
    int validate(int);

    int main(void)
    {
        struct timeval child_start, child_end, parent_start, parent_end, fib_start, fib_end; /* Time Variables for both child and parent  */
        long double child_time, child_secs, child_usecs, parent_time, parent_secs, parent_usecs, fib_secs, fib_usecs, fib_time;

        int status, digits = 1;
        unsigned long long int ans, tmp;
        int pid, i, n;
        int var = -1; /* This is the converted variable in which the input for the fib function will be stored in */
        int val = 0;
        char input[256]; /* The input for the fib function */
        char* cp, badc; /* Temp buffer for the input, and badc is for unwanted characters within the input */
        char *suf = "";

        gettimeofday(&parent_start, NULL); /* Get the current time of the system and store it in parent_start */
        printf("\n The program has begun...\n\n");
        pid = fork(); /* create a process */

        if (pid < 0) /* If process wasn't created Error routine is flagged */
        {
                printf("\n Error ");
                exit(1);
        }

        else if (pid == 0) /* This is if the child process was created */
        {
                gettimeofday(&child_start, NULL); /* Store the current time of the system to child_start */
                system("clear");

                for (i = 0; i < 5; ++i)
                {
                        printf("\n");
                }

                printf("\n\t\t ****************** CS451 PROJECT ******************\n");
                printf("\n Hello I am the child process\n\n");
                printf("Enter a positive number: ");

                var = validate(var);

                gettimeofday(&fib_start, NULL);
                ans = fib(var);
                gettimeofday(&fib_end, NULL);

                val = var % 10;
                suf = Ending(val, var);
                gettimeofday(&fib_end, NULL);
                fib_secs = fib_end.tv_sec - fib_start.tv_sec;
                fib_usecs = fib_end.tv_usec - fib_start.tv_usec;
                fib_time = ((fib_secs) * 1000 + (fib_usecs)/1000.0);
                printf("\n Elapsed time of fib function: %.3llf milliseconds\n", fib_time);

                char str[1000];
                sprintf(str, "%llu", ans);

                printf("\n The %d", var);
                printf("%s fibonnaci number is: ", suf);
                printf("%s.\n", str);
                gettimeofday(&child_end, NULL); /* store the current system time into child_end variable */
                child_secs = child_end.tv_sec - child_start.tv_sec;
                child_usecs = child_end.tv_usec - child_start.tv_usec;
                child_time = ((child_secs) * 1000 + (child_usecs)/1000.0);
                printf("\n My pid is %d, child process is closing...\n",getpid());
                printf("\n Elapsed Time for Child: %.3llf milliseconds\n\n", child_time);

                PressEnterToContinue();

                exit(0); /* Exit Child Process */
        }

        else
        {
                wait(&status);
                printf("\n Hello I am the parent process ");
                printf("\n My actual pid is %d \n ",getpid());
                gettimeofday(&parent_end, NULL);
                parent_secs = parent_end.tv_sec - parent_start.tv_sec;
                parent_usecs = parent_end.tv_usec - parent_start.tv_usec;
                parent_time = ((parent_secs) * 1000 + (parent_usecs)/1000.0) + 0.5;
                printf("\n Elapsed Time of the Program: %.3llf milliseconds\n\n\n", parent_time);
                exit(1); /* Exit Parent Process */
        }
    }
