# Learning-Project
Course Project
A Blackjack game write in python


# sleep.c program
  Using the Unix OS environment, write a c program named sleepy that gets a loop count from the command line as in
  sleep n
  where n is the number of seconds for which the program should run. Implement this timing by using a loop that 
  iterates n times. The body of the loop will contain the statement sleep(1). This will put the program to sleep
  for one second n times before exiting. If n is not provided use a default value of 5. In each iteration print 
  out the process ID and the loop count so that particular process can be identified.
  
  
  # twoSleepy.c 
    The program will create a child process that is an exact duplicate of itself using the fork function. If fork
    returns a 0 you will need to jump to the child code. If fork returns a non-zero value you will jump to the 
    parent code. You will need to do a little research to fully understand how this works. Use the exit and wait 
    functions to ensure that the child process ends before the parent process.
    
    Both parent and child will use the same value of n to determine the number of seconds each process should run.
    In each loop print out the process ID, the parent's process ID, and the loop count so that that particular 
    process can be identified.
    
    # Part II
    Comment out the call to the sleep and wait functions in the parent. This will ensure that the parent terminates 
    before the child.
    
    # Part III
    Modify your program from Part I so that the child process calls fork to create a child of its own.
    Use exit and wait to ensure that the processes end in reverse order from which they were created.
    
    
  # Sort.c
    1. Create a pair of n-element arrays of type int and initialize each of the arrays with a differnt set of random
    numbers using the srand and rand functions defined in stdlib.h
    
    2. Create an additional pair of n-element arrays of type int and initialize them with a copy
    of the contents of the arrays created in step 1.
    
    3. Create a single 2n-element array and initialize the low half with a copy of one of the n-element arrays and the 
    upper half with a copy of the other n-element array from stem 1 above.
    
    4. Using two UNIX POSIX threads, concurrents sort(in ascending order) each of the n-element arrays create in step
    1 above. After both 'sort' threads have terminated, merge the sorted contents of the two n-element arrays into
    a single 2n-element array so that the content of the 2n-element array is in ascending orger. Calculate and dispaly
    the elapsed time from when the threads were created unitl the merge was complete. 
    
    5. Using the two n-element arrays created in step 2 above, sequentially sort each of the arrays. Merge the 
    contents of the two n-element arrays into a single 2n-element array so that the content of the 2n-element 
    array is in ascending order. Calculate and display the elapsed time from when the first sort was called
    until the merge was completed.
    
    6. Sort the single 2n-element array created in step 3 above. There is no merge involed. Calculate and display
    the elapsed time when the sort was called until the sort was completed.
    
  # msgQueue.c
    Impletement the producer/consumer problem using a UNIX message queue as the data structure shared by single
    producer and three consumers. The program is to create a child process and the child process will in turn create
    three threads. The parent process is to be the procuder and the three threads will be the consumers. The number
    of items, N, that are to be produced will be provided to the program via the command line.
    Use a default value of 10 if N is not provided.
    
    After spawing the child process the parent will enter an N-interation loop. In each iteration of the loop the 
    parent will do the following:
       1. Generate a random number, R, in the range of 0-999.
       2. Send a message containing R.
       3. Add R to a running total of all values produced.
       4. Display the string "Producer produced a R"
       5. Put the producer to sleep for 0-1 seconds using sleep(rand()%2).
       
     After the N iterations have completed display the string "Total produced = XXX" (where XXX is the sum of 
     all R values produced) and wait for the child to terminate. It is the parent's responsibility to create
     and destroy the queue.
     
     The child process will create three consumer threads, 0, 1 and 2. Each thread will enter an N/3 iteration loop
     (be careful if (N%3)!=0). In each iteration of the loop each consumer thread will do the following:
        1. Read a message containing a value, C, consumed from the queue.
        2. Add C to a running to total maintained by each consumer thread.
        3. Display the string "Consumer thread Z consumed a C" where Z is the thead number - 0,1 or 2.
        4. Put the consumer three to sleep for 1-3 seconds.
     
     
  # threadQueue.c 
    Implements the producer/consumer problem using a 5-element circular array of type unsigned int that is shared
    by a two producer threads and two consumer threads. The main thread is to create all four threads. The number of 
    items, N, that are to be produced will be provided to the program via the command line. Use a default value of 10
    if N is not provided.
    
    Each produced thread will enter an N/2 iteration loop - allow for N to be odd. Each iteration of the loop will
    do the following:
       1. Generate a random number, R, in the range of 0-999.
       2. Insert R into the shared buffer. (enforce mutual exclusion and three synchronization.)
       3. Add R to a running total of all values produced.
       4. Display the string "Producer thread Z produced a R" where Z is the thread number - 0 or 1.
       5. Put the producer to sleep for 0-1 second
       
     After the N/2 iterations have completed display the string "Total produced by producer thread
     Z= YYYY" where YYYY is the sum of all N/2 values produced.
     
     Each consumer thread will enter an N/2 iteration loop - allow for N to be odd. In each iteration of the loop
     will do the following:
        6. Read a value, C, from the shaed buffer. ( enforce mutal exclusion and thread synchronization.)
        7. Add C to a running total maintained by each consumer thread.
        8. Display the string "Consumer thread Z consumerd a C" where Z is the thread number - 0 or 1.
        9. Put the consumer thread to sleep for 0 - 1 seconds.
 
  # clockPageReplacement.c
    Implement the enhanced clock page replacement algorithm. The clock will be implemented as a 4-element
    circular array. Write your code in such a way that it is easy to change the clock size. Each clock entry 
    will contain a use bit, a modify bit and a logical page number.
    
    The program will be tested using data text file testdata.txt. Each "record" of the file contains two fields:
    a page number and read/write character that indicates if the page is to be read from or written to.
    
    The clock algorithm performs as follows:
       1. Read a record.
       2. Check to see if the page in the record is already in the clock and if it is update to appropriate flag.
          This will not reposition the next frame pointer.
       3. If step 2 fails, beginning at the current position of the next frame pointer scan the clock. During this
          scan make no changes to the use bit. The first frame encountered with (u=0; m=0) is selected for replacement
       4. If step 3 fails, scan the clock again. The first frame encoutered with (u=0,m=1) is seleced for replacement.
          During this scan, set the use bit to 0 for each frame that is bypassed.
       5. If step 4 fails, the frame pointer will have once again returned to its original position and all the frame
          will have a use bit of 0. Repeat step 3 and, if necessary, step 4. By time a frame will be found for replacement.
       6. Write the updated clock to file results.txt.
       7. Repeate 1-6 until end of testdata.txt reached.
    
