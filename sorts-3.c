/**
* sorts.c - a program incorporates different methods to sort and merge arrays 
* then compares the efficiency of each method.
* 1. Using two threads to concurrently sort two n-element array, then merge to 
*    a single sorted 2n-element array.
* 2. Sequentially sorting two n-element arrays then merge to a single sorted
*    2n-element array.
* 3. Sorting a single 2n-element array.
* @author Junjie Wu
* @sid  47503174
* @server genuse32
* @compiler gcc
* @option -pthread -o
*/

/**           Guess         **/
/* The selection sort algorithm runs in O(n^2)time,so for very small array
*  size n,such as n=4, I guess sorting technique 3 will be the fastest,because
*  sorting technique 3 will sort the 2n-element array in one function quickly,
*  while sorting technique 2 needs call two sort fucntions and one merge fucntion,
*  the OS needs to save local variables in its stack and after the called function 
*  return,the OS will pop out the local variable from its stack that saved before.
*  
*  For large n,such as n=1000,sorting technique 3 will sort the 2n-element array, while 
*  sorting technique 1 and sorting technique 2 will sort two n-element arrays and then
*  merge them into a single one ,the worst case for merge runs in O(n^2)time. So the total
*  runing time for sorting technique 1 and technique 2 would be O(n^2)time in the worst.
*  While sorting technique 1 uses two concurrently sorting function, I guess technique would
*  be faster than technique 2.
*/

/**          Actual results    **/
/* The sorting technique 3 is the fastest in the three sorting techniques at small n.
*  However, sorting technique 2 is much faster than sorting technique 1 in large n actually, 
*  I think OS needs allocate more resources for the additional two threads, and also the 
*  short-term scheduler will spend much time on choosing threads, especially for short CPU 
*  time slice.
*/




# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <string.h>
# include <sys/wait.h>

/** declare a static global variabl to save the array size provided by user */
static unsigned n; 
/** We need to receive the array size n from user, so we cannot declare static
*   global arrays here, one solution is to declare two global integer pointers 
*   that can be used for thread function to point to the arrays in main thread
*/
int *p1=NULL;
int *p2=NULL;
int main(int argc, char *argv[]) {
        /** declare two thread functions,each sort a single array*/
        void *selectSort1(void *arg);  
        void *selectSort2(void *arg);
        /** declare the merge function which merges two sorted arrays 
        *   to a single array
        */   
        void merge(int c[],int nc,int a[],int na,int b[],int nb);
        /** declare the ordinary sort function */
        void sort(int a[],int na);
        if(argc==2)
            n=atoi(argv[1]);
        else
            n=30; 
        /** set the upper bound value of arrays to be 1000 for printing */              
        int MAX=1000;
        int err=0;
        int array1[n],array2[n];
        int array3[n],array4[n];
        int singleArray[2*n];
        int mergedArray1[2*n];
        int mergedArray2[2*n];

        pthread_t thread[2];
        clock_t start_t1,end_t1,total_t1; 
        clock_t start_t2,end_t2,total_t2;
        clock_t start_t3,end_t3,total_t3;
        double cpu_time_used1,cpu_time_used2,cpu_time_used3; 
        /* filling array1 and array2 with random numbers */ 
        srand((unsigned) time(NULL));
        for (int i=0;i<n;i++) {
            array1[i]= rand()%MAX;
            array2[i]= rand()%MAX;
        }
        /* copy array1 to array3 */
        memcpy(array3, array1, sizeof(array1));
        /* copy array2 to array4 */
        memcpy(array4, array2, sizeof(array2));
        /* copy array1 to the low half of singleArray */
        memcpy(singleArray, array1, sizeof(array1));
        /* copy array2 to the upper half of singleArray */
        memcpy((singleArray+n), array2, sizeof(array2));

        printf("Part I:\n");
        printf("Print out %d-element initial array1 and array2\n",n);   
        for (int i=0;i<n;i++) {
            printf("%5d ", array1[i]);
        }
        printf("\nEnd of array1\n");
        for (int i=0;i<n;i++) {
            printf("%5d ", array2[i]);
        }
        printf("\nEnd of array2\n"); 
        /* set global pointer p1 and p2 point to array1 and array2,respectively,
        *  so that thread function can operate arrays in main thread
        */         
        p1=array1;
        p2=array2;
       
        /* start to create thread[0],record the clock time */
        start_t1=clock(); 
        /* Creating thread[0] to sort array1 */       
        err= pthread_create(&thread[0],NULL,selectSort1,NULL);
        if(err!=0) {
           printf("thread[0] Error");
        }
        /* Creating thread[1] to sort array2 */ 
        err=pthread_create(&thread[1],NULL,selectSort2,NULL);
        if(err!=0) {
           printf("thread[1] Error");
        } 
        /* main thread waits the two threads to exit */
        pthread_join(thread[0],NULL);
        pthread_join(thread[1],NULL);
        /* after the two threads exit, main thread merges array1 and array2 
        *  to a sinlge sorted array named mergedArray1
        */
        merge(mergedArray1,2*n,array1,n,array2,n); 
        /* main thread ends of merging, record the clock time */ 
        end_t1=clock();
        total_t1=end_t1-start_t1;
        cpu_time_used1=(double)total_t1/CLOCKS_PER_SEC;
        printf("Print out %d-element sorted arrays for array1, array2:\n",n);
        for (int i=0;i<n;i++) {
            printf("%5d ", array1[i]);
        }
        printf("\nEnd of sorted array1\n");
        for (int i=0;i<n;i++) {
            printf("%5d ", array2[i]);
        }
        printf("\nEnd of sorted array2\n");
        printf("Print out %d-element sorted array for mergedArray1:\n",2*n);
        for (int i=0;i<2*n;i++) {
            printf("%5d ", mergedArray1[i]);
        }
        printf("\nEnd of sorted mergedArray1\n");
        printf("\nBegining concurrently sort using two threads at clock time:%ld\n",start_t1);
        printf("End of merging at clock:%ld\n",end_t1);
        printf("The total elapsed cpu time is: %f\n", cpu_time_used1); 

        printf("\nPart II: Uncomment the bolok to see the initial and sorted arrays\n");

        /**   printf("Print out %d-element initial array3 and array4\n",n);   
              for (int i=0;i<n;i++) {
                 printf("%5d ", array3[i]);
              }
              printf("\nEnd of array3\n");
              for (int i=0;i<n;i++) {
              printf("%5d ", array4[i]);
              }
              printf("\nEnd of array4\n"); 
        */
        /* main thread starts to sequentially sort array3 and array4,record the clock time */
        start_t2=clock();
        sort(array3,n);
        sort(array4,n);
        /* main thread merges array3 and array4 to a single sorted array named mergedArray2 */
        merge(mergedArray2,2*n,array3,n,array4,n); 
        /* ends of merging, record the clock time */        
        end_t2=clock();
        total_t2=end_t2-start_t2;
        cpu_time_used2=(double)total_t2/CLOCKS_PER_SEC;

        /**    printf("\nPrint out %d-element sorted array for mergedArray2:\n",2*n);
               for (int i=0;i<2*n;i++) {
                  printf("%5d ", mergedArray2[i]);
               } 
               printf("\nEnd of sorted mergedArray2\n");  
        */
        printf("\nBegining sequentially sort at clock time:%ld\n",start_t2);
        printf("End of merging at clock:%ld\n",end_t2);
        printf("The total elapsed cpu time is: %f\n", cpu_time_used2); 

        printf("\nPart III: Uncomment the block to see the initial and sorted arrays\n");

        /**    printf("\nPrint out initial %d-element singleArray:\n",2*n);
               for (int i=0;i<2*n;i++) {
                   printf("%5d ", singleArray[i]);
               }
               printf("\nEnd of singleArray\n"); 
        */
        start_t3=clock();
        sort(singleArray,2*n);
        end_t3=clock();
        total_t3=end_t3-start_t3;
        cpu_time_used3=(double)total_t3/CLOCKS_PER_SEC;

        /**  printf("\nPrint out %d-element sorted array for singleArray:\n",2*n);
             for (int i=0;i<2*n;i++) {
                printf("%5d ", singleArray[i]); 
             } 
             printf("\nEnd of sorted singleArray\n"); 
        */
        printf("\nBegining sort at clock time:%ld\n",start_t3);
        printf("End of sorting at clock:%ld\n",end_t3);
        printf("The total elapsed cpu time is: %f\n", cpu_time_used3);        
}

/**  Thread function uses selection sort algorithm */     
void *selectSort1(void *arg) {
        int i,j,k;          
        for (i=0;i<n;i++) { 
           int k=i;
           for (j=i+1;j<n;j++) {
              if(*(p1+k)> *(p1+j)) 
              k=j;                      
           }
           if(k!=i) {
              int temp= *(p1+i);
              *(p1+i)= *(p1+k);
              *(p1+k)= temp;
           }
        }
}
/** Thread function use selection sort algorithm */ 
void *selectSort2(void *arg) {            
        int i,j,k;
        for (i=0;i<n;i++) {
            int k=i;
            for (j=i+1;j<n;j++) {
               if(*(p2+k)> *(p2+j))
               k=j;                       
            }
            if(k!=i) {
               int temp= *(p2+i);
               *(p2+i)= *(p2+k);
               *(p2+k)= temp;
            }
        }
}
/** Merge function combines two sorted arrays to a single sorted array */     
void merge(int c[],int nc,int a[],int na,int b[],int nb) {
        int i,j,k;
        i=j=k=0;
        while (i<na && j<nb) {
             if(a[i]<=b[j])
                c[k++]=a[i++];
             else
                c[k++]=b[j++];
        }
        while(i<na)
             c[k++]=a[i++];
        while(j<nb)
             c[k++]=b[j++];
}

/* Ordinary sort function use selection sort algorithm */  
void sort(int a[],int na) {
        int i,j,k;
        for (i=0;i<na;i++) {
            int k=i;
            for (j=i+1;j<na;j++) {
               if(a[k]> a[j])
               k=j;                       
            }
            if(k!=i) {
               int temp= a[i];
               a[i]= a[k];
               a[k]= temp;
            }
        }
}                  

