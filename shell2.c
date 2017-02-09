#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>     

/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;

// -- FUNCTION PROTOTYPES --
void clear_screen();
void list_directory();
void list_environment();
void quit_program();
// -- ENDS --


/*clr -- clear the screen using the system function clear --> system("clear")
*/
void clear_screen()
{
   system("clear");
}

/*list the current directory contents (ls -al <directory>) - 
   you will need to provide some command line parsing capability to extract the target directory for listing . 
   Once you have built the replacement command line, use the system function to execute it
*/
void list_directory()             
{
   char myStringCopy[100];
   char *tokenline[100];
         
   strcpy(myStringCopy, "ls -al tokenline[1]");      //copy from directory to copy
   system(myStringCopy);                 //print out copy
}

/*list all the environment strings -- 
  environ is an array of pointers to the 
  environment strings terminated with a NULL pointer in the while loop created.
*/
void list_environment()
{
   int n = 0;
   while(environ[n]!= NULL) {
      printf("%s\n", environ[n]);
      n++;
   }
}

/*quit from the program with a zero return value. 
   Use the standard exit function.
*/
void quit_program()
{
   exit(0);
}
 
 
//main function
int main()
{
   //declare variables
   size_t line;
   size_t maxLine = 100;
   char* myString;
   
   char delim[] = " \n"; 
   char* breakline;
   char *tokenline[maxLine];
   int n;     
   int m;
   
   //actual initialization
   n = 0;

 /*notice the prototype
   arrays points at the respective functions
  */
   void (*functionArray[4])() = {&clear_screen, &list_directory, &list_environment, &quit_program};


   /*make a list of all aliases/internal controls -- declare and initailize array
     A string array is an array of characters and the use of const char tells 
     the compiler that there is no intention to change the data in aliases.
   */
   const char *aliases[]= {"clr","dir","environ","quit"};
   
   /* create a while loop
      if a character is not read by getline, then -1 will be returned
   */  
   while(1)
   {      
      printf("Enter a command line argument\n");
      
      getline (&myString, &maxLine, stdin);
            
      /*tokenize keyboard input/line using strtok using a for loop
         delimiter is a space -- hence every word to be printed ends when it comes across a space.
     */
      for(breakline = strtok(myString, " "); breakline != NULL; breakline = strtok(NULL, delim))
      {                  
         tokenline[n] = malloc(strlen(breakline)+1);        //allocate some space for new array
         
         strcpy(tokenline[n],breakline);
               
      /*Next is the comparism of the arrays aliases and tokenline 
            by calling the functions above
       */
         for(m = 0; m < sizeof(aliases); m++)    //loop through the array elements for comparison
         {   
            if(strcmp(tokenline[0], aliases[m]) == 0)
            {
               functionArray[m]();
            }           
            /* Use standard ANSI C system function to execute the line through the default system shell.
            */
            else
            {
               system(myString);
            }
         }         
         /* Deallocate allocated memory */
         free(tokenline[n]);   
      }
   }      
   return(0);
}
