
/*
Write a small program that loops reading a line from standard input and checks the first word of the input line. 
If the first word is one of the following internal commands (or aliases) perform the designated task. 
Otherwise use the standard ANSI C system function to execute the line through the default system shell.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;


//global variable 
const int NUM_FUNCS = 5;
size_t maxLine = 1000;
   
// -- FUNCTION PROTOTYPES --
void clear_screen();
void list_directory(char **tokenline,int numTokens);
void list_environment();
void quit_program();
void change_defaultDirectory(char **tokenline,int numTokens);

//arrays are made to point at the respective void functions
void (*functionArray[NUM_FUNCS])() = {&clear_screen, &list_directory, &list_environment, &quit_program, &change_defaultDirectory};


extern int errno;        // system error number 
 
void syserr(char* );     // error report and abort routine 
// -- ENDS --



//wait can block the caller until a child process terminates
//pid_t wait(int *statloc);

//waitpid has an option that prevents it from blocking
//pid_t waitpid(pid_t pid, int *statloc, int options);

void syserr(char * msg)                   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   abort();
}

//fork function
void forkSystem()
{
   pid_t PID, fork_pid;                 //represents the data type of procee ID
   int *status;
   
   PID = getpid();                     //call getpid() then assign it to PID to get parents ID
   printf("Parents PID before calling fork: %d\n\n", PID);
   
   //fork creates a nnew process by cloning the parents PID
   fork_pid = fork();
   
   //verify result from fork()
   if(fork_pid == -1 )
   {
      perror("Clone Unsuccessful");
   }   
      /*pid < -1
         waits for any process whose process group id equals the absolute value of pid.   
      */
   else if(fork_pid == 0)
   {
      PID = getpid();                  //call getpid() then assign it to PID again to CONFIRM cloned/Child's PID
      printf("Fork() successful.......... Child's PID: %d\n\n", PID);
      //excute the sleepy file using execlp
      execlp("sleepy", "sleepy", "10", NULL);
      perror("execl() failure \n\n");
   }
   /*pid > 0
         waits for the process with process ID pid -- 
   
         parent process
   */
   else
   {
      //suspend parent process wait until child comletes usiong wait system
      wait(NULL);
      
      printf("childs process completed terminated \n\n");
   }
}


/*clr -- clear the screen using the system function clear --> system("clear")
*/
void clear_screen()
{
   
   char *argv[3] = {" ", "clear", NULL};

   //int execvp(const char *file, char *const argv[])
   execvp("/bin/sh", argv);
}

/* A directory is a storage for organized files with detailed information on both the object names and their attributes
   list the current directory contents (ls -al <directory>) - provide some command line parsing capability to extract the target directory for listing . 
   use the system function to execute it
*/
void list_directory(char **tokenline,int numTokens)             
{
   //create an array of 500 characters 
   char direct[500];
      
   //copy String ls -al into array direct
   strcpy(direct, "ls -al ");
   
   //check if number of token 
   if(numTokens > 1)
   {
      //get the second string from tokenline[] then concatenate
      strcat(direct, tokenline[1]);
   }

      //call system or exec on direct    
      //system(direct);
   execl("ls","-c","ls",tokenline[1]);            
}

/*environment stores information about the terminal type, current locale, user’s home directory, name of curent file and more.
  list all the environment strings -- 
  environ is an array of pointers to the 
  environment strings terminated with a NULL pointer in the while loop created.
  NULL pointer represents the end of environment
*/
void list_environment()
{
   int n = 0;
   
   while(environ[n]!= NULL)
   {
      printf("%s\n", environ[n]);
      
      //increment n after each print until the environment is exhausted
      n++;
   }
}

/* quit puts the program to an end. 
   quit the program with a zero return value. 
   Use the standard exit function.
*/
void quit_program()
{
   exit(0);
}

/*Add the capability to change the current directory and set and change environment strings:

      cd <directory>

      Change the current default directory to <directory>. 
      If the <directory> argument is not present, report the current directory. 
      This command should also change the PWD environment string. 
      For this you will need to study the chdir, getcwd and putenv functions.
*/
void change_defaultDirectory(char **tokenline,int numTokens)
{   
   // //local variable
   char buffer[100];
   char *cwd;
   

   //check if number of token 
   if(numTokens > 1)
   {
      //call chdir -- change directory on tokenline[1]    
      if(chdir(tokenline[1]) == 0)
      {
         cwd = getcwd(buffer, 100);
         printf("the current working directory PWD = %s \n", cwd);
      
         setenv("PWD",cwd,1);
         printf("changed current working directory to: %s\n", buffer);
      }
      //report the current directory
      else
      {
         perror("chdir(tokenline[1]) \n");
        
                 
         //system("ls -al");
         //int execlp(const char *file, const char *arg0, ..., const char *argn, (char *)0);
         execl("/bin/sh","-c","cd",tokenline[1]);
      }
   }
   
   //if numTokens is 1 print out current working directory
   else
   {
      //report the current directory.
      //system("ls -al");
      execl("/bin/sh","-c","cd",tokenline[1]);
   }
   
}



/*echo <comment> - display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space)
   */
   
   
// -- ENDS --

//main function
int main(int argc , char *argv[])
{
   //declare variables

   char *myString;                //used to store user input
   
   char delim[] = " \n";         //delimiter is a space and next line -- hence every word to be printed ends when it comes across a space.
   
   char* line;
   
   char* token;                  //a pointer used to store each tokenized string

   char *cpy_token[maxLine];     //copy each token into an array of maxLine character pointer for further use
   
   int n = 0;
   
   int m;
   
      
    /*make a list of all aliases/internal controls -- declare and initailize array
     A string array is an array of characters and the use of const char tells 
     the compiler that there is no intention to change the data in aliases.
   */
   const char *aliases[]= {"clr","dir","environ","quit","cd"};
      
   //an array of integers used to determine when to call the array of void functions with or without arguments 
   int needargs[] = {0,1,0,0,1};
   
   //This is used to keep track of of the comparison between the tokenized user input and aliases array 
   int foundMatch = 0;      
      
   //call fork() exec() before at the start of program
   forkSystem();
   
   /* create a while loop
   */  
   while(1)
   {      
      // prompt for user input
      printf("\n>>");
         
      //read the operator input/line using stdin
      getline(&myString,&maxLine,stdin);
      
      // make a duplicate of myString before you use the tokenizer
      line = strdup(myString);
      
      /*tokenize keyboard input/line using strtok using a for loop
     */
      token = strtok(myString,delim);  
     
      /*use a while loop if the above token is not empty
      */
      while(token != NULL)
      {
         //create a duplicate of token in cpy_token[]
         cpy_token[n] = strdup(token);
         
         //check inbetween each token to ensure that delimiters are assigned \0 and next string is considered if any
         token = strtok(NULL, delim);                
      
         n++;
      }  
   
      /*Next is the comparison of the arrays aliases and tokenline 
            loop through the array elements for comparison using a for loop
       */
      for(m = 0; m < NUM_FUNCS; m++)    
      {   
         //compare the first token with every element in the predefined array of aliases
         if(strcmp(cpy_token[0],aliases[m]) == 0)
         {
            /*confirm if the function to be called requires an argument or not using same index as that 
               of the aliases found.
               if the needargs[] == 0, call functionArray without arguments 
               else call functioArray with arguments.
            */
            if(foundMatch == 0)
            {
               if(needargs[m] == 0)
               {
                  functionArray[m]();
               }
               else
               {
                  functionArray[m](cpy_token,n);
               }
            }
         }
      }
      
      //if compared elements are not found, then foundmatch is reassigned as 1
      foundMatch = 1; 
         
      /* where the first element in cpy_token[0] is not same as any of the elemnts in aliases array,
         call system function on the entire line of user input---------
         Use standard ANSI C system function to execute the line through the default system shell.
      */
      if(foundMatch == 1)
      {
         //call the duplicated and unmodified copy of myString.
         //execv("/bin/bash",line);
         
         // char *argv[3] = {"line", "", NULL};
         //       
         //          //int execvp(const char *file, char *const argv[])
         //          execvp("/bin/sh", argv);
         system(line);
         printf("%s is not in the array \n", line);
    
      }       
   
      /* Deallocate each allocated memory used as extra storage for the tokenized strings
            using a while loop to decrement n after each deallocattion until n = 0
      */
      while(n > 0)
      {
         n--;
         free(cpy_token[n]);   
      }
   
      //reassign foundmatch to 0
      foundMatch = 0;
   }

   //deallocate the entire array of cpy_token[] allocated to hold an extra copy of the tokenized word.
   free(cpy_token);
   
   return(0);
}