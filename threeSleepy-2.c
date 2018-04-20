/**
* threeSleepy - a program using fork() to create a child process,
* the child process then fork a grandchild.
* All the parent, child and grandchild processes will sleep n seconds
* in a loop before exiting. IN each loop, print the process ID and
* its parent process ID and loop number.
* @author Junjie Wu
* @sid  47503174
* @server genuse32
* @compiler gcc
* @option -o
*/

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

int main(int argc, char *argv[]) {
        /* define the loop number */
        unsigned int count;
        int tick = 0;
        if(argc==2)
            /* convert the second string parameter
            *  getting from command line to int.
            */
            count=atoi(argv[1]);
        else
            /*  define default loop number to 5 if
            *   it doesn't provide from command line.
            */
            count=5;
        pid_t fpid;
        /* using fork() to create a child process */
        fpid = fork();
        if (fpid<0) {
            printf ("fork failed");
            exit (EXIT_FAILURE);
        }
        /* fpid == 0, child process excutes */
        else if (fpid == 0) {
            /* child process fork a grandchild process */  
            if (fpid=fork()==0) {
                while (count) {
                    sleep (1);
                    printf("Grandchild Process with PID: %d and PPID: %d; tick %d\n",
                                  getpid(), getppid(), ++tick);
                    count--;
                }
                /* grandchild process completes its loops, and sleep one second
                *  wait for child process (its parent) to complete loops
                */
                sleep(1); 
                printf("Grandchild process terminating\n");
                exit(0); // grandchild process exit
            }
            else {
                 /* child process loops */
                 while (count) {
                     sleep (1);
                     printf("Child Process with PID: %d and PPID: %d; tick %d\n",
                                  getpid(), getppid(), ++tick);
                     count--;
                 }
            }
            wait(NULL); // wait for grandchild process exit first

            /* child precess completes its loops, and sleep one second
            *  before exit(0) to wait the parent process to complete loops.
            */
            sleep(1);
            printf ("Child Process terminating\n");
            exit(0); // child process exit.
        }
        /* fpid >0, parent process excutes */
        else {
            while (count) {
                sleep (1); 
                printf("Original Process with PID: %d and PPID: %d; tick %d\n",
                          getpid(), getppid(), ++tick);
                count--;
            }
            wait(NULL); // wait child process to exit first
            printf ("Original Process terminating\n");
        }
        exit(0); // parent process exit.
}
