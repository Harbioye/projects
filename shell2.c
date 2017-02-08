#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

//functions declaration

/*The prototype for the fgets function is:
*/
char *fgets (char *str, int size, FILE* file);

/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;

int main()
{
   
   //declare variables
   size_t line;
   size_t maxLine = 100;
   char *my_string;
   
   char input[20];      
   int i;
   
   //variable definition
   char **environ;
   
   /* These 2 lines are the heart of the program.
   
   Firstly, the char cast operator will be a character pointer and that 1 is added to maxLine for the malloc function i.e. 
   the last character read by getline should be a null character and one is added to account for the last null character that will be read
   */
   my_string = (char *) malloc (maxLine + 1); 
   
   /*the value of line will be determined by the return of your getline function*/
   line = getline (&my_string, &maxLine, stdin);   

   /*make a list of all aliases/internal controls -- declare and initailize array
     A string array is an array of characters and the use of const char tells 
     the compiler that there is no intention to change the data in aliases.
   */
   
   //an array of strings
   const char *aliases[]= {"clr","dir","environ","quit"};

   /* create a while loop
      if a character is not read by getline, then -1 will be returned
   */  
   while(line == -1)
   {      
      printf("Enter a command line argument\n");
   
   
               
      /*list the current directory contents (ls -al <directory>) - 
         you will need to provide some command line parsing capability to extract the target directory for listing . 
          Once you have built the replacement command line, use the system function to execute it
      */
      else if(strcmp(input, aliases[1]) == 0)
      {
         char copy[100];
         
         strcpy( copy, "ls -l" );      //copy from directory to copy
         system(copy);                 //print out copy
      
         return(0);
      }
      
      /*list all the environment strings -- 
       environ is an array of pointers to the 
       environment strings terminated with a NULL pointer in the while loop created.
      */
      else if(strcmp(input, aliases[2]) == 0)
      {
         // int n = 0;
      //          while(environ[n]!= NULL) {
      //             printf("%s\n", environ[n++]);
        // } 
         printf("cool");
      }
      
      /*quit from the program with a zero return value. 
      Use the standard exit function.
      */
      else if(strcmp(input, aliases[3]) == 0)
      {
         exit(0);
      }
      
      /* Use standard ANSI C system function to execute the line through the default system shell.
      */
      else
      {
         system(input);
      }
   }
   return(0);
}
