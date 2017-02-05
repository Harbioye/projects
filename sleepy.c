#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <signal.h>

void sighandler(int);

//function called when ctrl-c is sent to program
void sighandler(int signalInt)
{
   //
   printf("A signal is Caught because there was an interruption.. Maybe you hit the ctrl-c button  %d\n", signalInt);
   
   //terminate the program
   exit(signalInt)
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
   
   //register dignal and signal handler
   signal(SIGINT, sighandler);
   
   for(count=0;count<n;count++)
   {      
      time_t t;
      time(&t);
      printf("Start sleep --> : %s",ctime(&t));
      sleep(1);
      time(&t);
      printf("End sleep --> : %s\n", ctime(&t));   
      printf("COUNT = %d,PID = %d\n",count, getpid());
   }
   return(0); 
}
