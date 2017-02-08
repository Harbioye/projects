#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

//functions declaration
/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;

   //function definitions
void clear_clear();
void list_directory();
void list_environment(int n);
void quit_program();

/*clr -- clear the screen using the system function clear --> system("clear")
*/
void clear_Screen()
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
void list_environment(int n)
{
   char **environ;
   n = 0;
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
 
int main()
{
   //declare variables
   size_t line;
   size_t maxLine = 100;
   char *myString;
   
   char delim[] = " "; 
   char* breakline;
   char *tokenline[maxLine];
   int n;     
   
   int i;
   char **environ;
   char myStringCopy[maxLine];
   
   //actual initialization
   i = -1;
   n = 0;
   
   /*make a list of all aliases/internal controls -- declare and initailize array
     A string array is an array of characters and the use of const char tells 
     the compiler that there is no intention to change the data in aliases.
   */
   const char *aliases[]= {"clr","dir","environ","quit"};

   /* create a while loop
      if a character is not read by getline, then -1 will be returned
   */  
   while(i == -1)
   {      
      printf("Enter a command line argument\n");
      
      /* These 2 lines are the heart of the program.
         Firstly, the char cast operator will be a character pointer and that 1 is added to maxLine for the malloc function i.e. 
         the last character read by getline should be a null character and one is added to account for the last null character that will be read
      */
      myString = (char *) malloc (maxLine + 1); 
   
      //the value of line will be determined by the return of your getline function
      line = getline (&myString, &maxLine, stdin);
      
      /*tokenize keyboard input/line using strtok using a for loop
      /delimiter is a space -- hence every word to be printed ends when it comes across a space.
     */
      for(breakline = strtok(myString, " "); breakline != NULL; breakline = strtok(NULL, delim))
      {
         tokenline[n] = breakline;
         printf("tokenline[%d] = %s\n",n, tokenline[n]);
         n++;
      }
      
      /*Next is the comparism of the arrays aliases and tokenline 
         by calling the functions above
      */
      if(strcmp(tokenline[0], aliases[0]) == 0)
      {
         clear_Screen();
      }
      else if(strcmp(tokenline[1], aliases[1]) == 0)
      {  
         list_directory();     
      }
      else if(strcmp(tokenline[2], aliases[2]) == 0)
      {
         list_environment(n);
      }
      else if(strcmp(tokenline[3], aliases[3]) == 0)
      {
         quit_program();
      }
      
      /* Use standard ANSI C system function to execute the line through the default system shell.
      */
      else
      {
         system(myString);
      }   
   }      
   return(0);
}
