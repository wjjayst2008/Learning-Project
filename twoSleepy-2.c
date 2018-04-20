/**
* twoSleepy - a program using fork() to create a child process,
* and both the parent and child process will sleep n seconds
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
        /* after fork(), the parent process created a new child process,
        * and the state of child process is New, Linux kernal builds the
        * data structure and allocates address space in main memory
        * for this child process, and the child process's
        * status moved to Ready. The scheduler will choose the child
        * process to Run (Running state) in the CPU at proper time.
        * After calling sleep function,the Child process moved to
        * Blocked state. After sleep one second, the child process moved
        * from Blocked state to Ready state. Again, the scheduler will
        * moved it to Running state at proper CPU time. The calling exit(0)
        * function changed the child process from Running state to Exit state.
        */
        /* fpid == 0, child process excutes */
        else if (fpid == 0) {
            while (count) {
                sleep (1);
                printf("Child Process with PID: %d and PPID: %d; tick %d\n",
                                  getpid(), getppid(), ++tick);
                count--;
            }
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
                /* parent process moved to Blocked state from Running After
                * calling sleep function. After sleep(1), parent process moved
                * from Blocked state to Ready state. Scheduler will move it
                * to Running state at proper CPU time. Calling wait function
                * will Block itself, the parent process then wait for the
                * child process to exit first. The parent process will receive
                * the exit status of its child process, and then moved to
                * Ready state. Eventually, the parent process will moved from
                * Running state to Exit state after calling exit(0) functiuon.
                */
                sleep (1); // at Part II, comment out sleep and wait functions
                printf("Original Process with PID: %d and PPID: %d; tick %d\n",
                          getpid(), getppid(), ++tick);
                count--;
            }
            wait(NULL); // wait child process to exit first
            /* At Part I, both the parent and child process will calling
            * sleep(1) function in the loops. If one of the two process moves
            * from Running state to Blocked state, then the scheduler will
            * choose another process from the Ready quene to run. It is highly
            * possible that either of parent and child process is Running,
            * while the other process is in the Ready quene. So that's why
            * the output is so evenly interleaved between parent and
            * child process.
            */
            /* At Part II, comment out sleep and wait function in the parent
            * process. Without calling sleep function,the parent process
            * will first complete the loops.The parent process doesn't
            * call wait function, thus it will exit first. When the child
            * process eventually exit, it will find that it become an orphan
            * process, that means the parent process dies before the child
            * process,however, the linux kernal will appint init (process ID 1)
            * process to adopt the orphan process. That's why we can see that
            * the PPID in the child process changed to 1 before it exit.
            */
            printf ("Original Process terminating\n");
        }
        exit(0); // parent process exit.
}
