#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>

void sighandler(int);

//function called when ctrl-c is sent to program
void sighandler(int signalInt)
{
   //
   printf("A signal is Caught because there was an interruption.. \n\tMaybe you hit the ctrl-c button. \n\t\tReturn value =  %d\n", signalInt);
   
   //terminate the program
   exit(0);
}
int main(int argc, char* argv[])
{  
   int count;
   int n;
   
   //isdigit works only on chars
   //atoi converts a string to an integer.
   if(argc>1 && isdigit(argv[1][0]))      
   {
      n = atoi(argv[1]);          
      printf("argv[1] = %d \n", n);
   }
   else{
      printf("Enter a valid integer \n");
      return(1);
   }  
   
   //register signal and signal handler
   signal(SIGINT, sighandler);
   
   for(count=0;count<n;count++)
   {      
      time_t t;
      //keeps track of sleep start time.
      time(&t);
      printf("\nStart sleep --> : %s",ctime(&t));
      
      //program sleeps for one second
      sleep(1);
      
      //keeps track sleep end time.
      time(&t);
      printf("End sleep --> : %s", ctime(&t));   
      
      //In each loop print out the process ID and the loop count so that that particular process can be identified.
      printf("PID = %d, COUNT = %d\n",getpid(),count);
   }
   return(0); 
}
