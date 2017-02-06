#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

/*The prototype for the fgets function is:
*/
char *fgets (char *str, int size, FILE* file);

/*The extern storage class is used to give a reference of a 
global variable that is visible to ALL the program files.
the variable cannot be initialized however, it points the 
variable name at a storage location that has been previously defined.
EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;

int main(int argc, char* argv[])
{
   
   //declare variables
   char input[20];      
   int i;
   char **environ;
   
   /*make a list of all aliases/internal controls -- declare and initailize array
     A string array is an array of characters and the use of const char tells 
     the compiler that there is no intention to change the data in aliases.
   */
   
   //an array of strings
   const char *aliases[]= {"clr","dir","environ","quit"};
   
   //check for command lline arguments 
   if(argc < 2)
   {
      printf("Enter a command line argument\n");
      
      /*Strings are useful for holding all types of long input. 
      If you want the user to input his or her name, you must use a string. 
      Using scanf() to input a string works, but it will terminate the string after it reads the first space, 
      and moreover, because scanf doesn't know how big the array is, it can lead to "buffer overflows" 
      when the user inputs a string that is longer than the size of the string (which acts as an input "buffer").
      */
      //fgets(input, 20, stdin);
      
      //while reading a string, scanf() stops reading as soon as it encounters a space
      scanf("User input = %s/n",input);
      printf( 
   }
   else
   {
      //fgets(input, 20, stdin);
      scanf("User input = %s\n",input);
   }
    
   //creat a loop
   for(i =0;i < argc;++i)
   {      
      /*clr -- clear the screen using the system function clear:    
       system("clear")
      */
      if(strcmp(input, aliases[0]) == 0)
      {
         system("clear");
      }
         
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