#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

//functions declaration

/*The prototype for the fgets function is:
*/
char *fgets (char *str, int size, FILE* file);

char *strtok(char *str, const char *delim);

/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;

   //function definitions
void clear();


/*clr -- clear the screen using the system function clear --> system("clear")
*/
void clear()
{
   system("clear");
}

   
int main()
{
   //declare variables
   size_t line;
   size_t maxLine = 100;
   char *myString;
   
   char delim[] = " "; 
   char* breakline;
   char *tokenline[4];
   int n;
   //char input[20];      
   int i;
   
   //variable definition
   char **environ;
   
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
         clear();
      }
      else if(strcmp(tokenline[1], aliases[1]) == 0)
      {  
               
      }
      else if(strcmp(tokenline[2], aliases[2]) == 0)
      {
      
      }
      else if(strcmp(tokenline[3], aliases[3]) == 0)
      {
         exit(0);
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
