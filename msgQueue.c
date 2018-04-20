/** msgQueue.c - a program implements the procucer/consumer problem
*** using a UNIX message queue as the data stucture shared by single
*** producer and three consumers.
*** 1. parent process create a child process, and child process creates
***    three threads.
*** 2. parent process is the producer,and three threads are the consumers.
*** @author 47503174
*** @server genuse32
*** @compiler gcc
*** @option -pthread -o
**/

/****  explanation of  mututal exclusion and sysnthronization ****/
/* this program uses the System V IPC Message Queue, the queue is FIFO.The producer
* uses msgsnd() to unblockingly send message to the queue until the queue is full.
* If the queue is full, the msgsnd() will be blocked that controlled by the IPC_NOWAIT
* flag until there is sufficient space or the queue has been destroyed or the process
* has been interrupted.
*
* The consumer uses msgrcv() to blockingly read a message from the queue, if the queue
* is empty, the msgrcv() willl be blocked until there is a message in the queue or the
* queue has been destroyed or the process has been interrupted.
*/


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/msg.h>
# include <string.h>
# include <time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <errno.h>
# include <sys/wait.h>

# define MAX  1000
# define NUMBER_THREAD 3

/* declare default items 10,otherwise get it from user */
unsigned int N = 10;

/* sum of consumed values by all thread consumers
*  should be the same produced total values by producer */
static int sum = 0;

/* define message sturcture in the queue */
struct my_msg  {
    long mtype;
    int num;
};

int main(int argc, char *argv[]) {
     if(argc==2)
        N=atoi(argv[1]);
     /* declare thread function */
     void *thr_fn(void *arg);
     pid_t fpid;
     fpid = fork();
     if (fpid<0) {
         perror("fork failed");
         exit (1);
     }
     else if (fpid>0) {
         struct my_msg  msg;
         int msqid;
         key_t key;
         if ((key = ftok("./msgQueue.c",'A'))==-1) {
            perror("ftok failed");
            exit(1);
         }
         /* parent process creates and connects to the queue */
         if ((msqid = msgget(key,0644|IPC_CREAT))==-1) {
            perror("msgget failed");
            exit(1);
         }
         srand((unsigned) time(NULL));
         int total=0;
         while(N) {
             int R;
             R = rand()%MAX;
             msg.mtype=1;
             msg.num = R;
             msgsnd(msqid,&msg,sizeof msg.num,0);
             printf("Producer produced a %d\n", R);
             total = total + R;
             sleep(rand()%2);
             N--;
         }
         printf("Total produced = %d\n", total);
         /* parent process waits for child process exit first */
         wait(NULL);
         /* parent process destroys the queue */
         if (msgctl(msqid,IPC_RMID,NULL)==-1) {
             perror("msgctl failed");
             exit(1);
         }
         return 0;
    }
    /* child process creats threads */
    else {
        pthread_t thread[NUMBER_THREAD];
        int i;
        for(i=0;i<NUMBER_THREAD;i++) {
          int err;
          err= pthread_create(&thread[i],NULL,thr_fn,(void *)(unsigned long)i);
          if (err!=0) {
              perror("thread[i] Error");
          }
        }
        /* child process waits all theads to exit first */
        for(int j=0;j<NUMBER_THREAD;j++) {
           pthread_join(thread[j],NULL);
        }
        printf("sum of consumed values by all thread consumers = %d\n",sum);
        return 0;
    }
}

void * thr_fn (void *arg) {
   int i = (int)(unsigned long)arg;
   struct my_msg  msg;
   int msqid;
   key_t key;
   if ((key = ftok("./msgQueue.c",'A'))==-1) {
      perror("ftok failed");
      exit(1);
   }
   /* connect to the same queue that producer creates */
   if ((msqid = msgget(key,0644))==-1) {
      ("msgget failed");
      exit(1);
   }
   /* the last thread will do more loops than other thread
   ** in case of (N%NUMBER_THREAD)!=0
   */
   if (i==(NUMBER_THREAD-1)) {
      int j;
      int total = 0;
      for (j=0;j<(N/NUMBER_THREAD + N%NUMBER_THREAD);j++) {
          /* thread consumer reads a value from the queue */
          msgrcv(msqid,&msg,sizeof msg.num,1,0);
          printf("Consumer thread %d consumed a %d\n", i,msg.num);
          total = total + msg.num;
          sleep((rand()%3)+1);
      }
      printf("Total consumed by consumer thread %d = %d\n", i,total);
      sum += total;
   }
   else {
      int j;
      int total = 0;
      for (j=0;j<N/NUMBER_THREAD;j++) {
          /* thread consumer reads a value from the queue */
          msgrcv(msqid,&msg,sizeof msg.num,1,0);
          printf("Consumer thread %d consumed a %d\n", i,msg.num);
          total = total + msg.num;
          sleep((rand()%3)+1);
      }
      printf("Total consumed by consumer thread %d = %d\n", i,total);
      sum += total;
   }
}
