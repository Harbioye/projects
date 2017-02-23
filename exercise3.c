
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


/*EXTERN is used to declare a global variable or function in another file.
*/   
extern char **environ;


//global variable 
const int NUM_FUNCS = 5;
size_t maxLine = 1000;
char *buffer;
   
// -- FUNCTION PROTOTYPES --
void clear_screen();
void list_directory(char **tokenline,int numTokens);
void list_environment();
void quit_program();
void change_defaultDirectory(char **tokenline,int numTokens);

//arrays are made to point at the respective void functions
void (*functionArray[NUM_FUNCS])() = {&clear_screen, &list_directory, &list_environment, &quit_program, &change_defaultDirectory};

// -- ENDS --


/*clr -- clear the screen using the system function clear --> system("clear")
*/
void clear_screen()
{
   system("clear");
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
   
   //call system on direct    
   system(direct);                 
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
   //local variable
   char *cwd;
   char *newDirectory = "/tokenline[1]";
   char *pwd;
   
   //get current directory
   cwd = getcwd(buffer, maxLine);
   printf("the current working directory = %s \n", cwd);
   
   /*change current directory
      if successsful then return 0
      else return -1
      
      new directory
   */
   if(chdir(newDirectory) == 0)
   {
      getcwd(buffer, maxLine);
      printf("the current working directory is %s \n", buffer);
      
      //make pwd const char *
      //set pwd to buffer
      pwd = buffer;
      printf("pwd %s\n", pwd);
      
      //call setenv(takes three arguments)
      //int setenv(const char *var_name, const char *new_value, int val);
      
      /*This is kept by the shell in order to switch back to your previous directory by running cd -.
         
         var_name is a pointer to a character string that contains 
         the name of the environment variable to be added, changed, or deleted. 
         
         new_value is a pointer to a character string that contains 
         the value of the environment variable named in var_name.
         If new_value is a NULL pointer, it indicates that all occurrences 
         of the environment variable named in var_name be deleted.
         
         If the environment variable named by var_name already exists and 
         i)     the value of val is non-zero, the function shall return success and 
                  the environment shall be updated. 
         ii)    if the value of val is zero, the function shall return success and 
                  the environment shall remain unchanged.


      */
         int ret_val;
         ret_val = setenv("cwd","pwd",0);
         
         //debug
         printf("ret_val = %d\n",ret_val);
      
   }
   else
   {
      printf("Error %s \n", buffer);
            //return -1;
   }
}

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
    
   //change_defaultDirectory();
  
   /* create a while loop
   */  
   while(1)
   {      
      // prompt for user input
      printf(">>");
         
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
         //store each token in cpy_token[]
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
            
            //if compared elements are not found, then foundmatch is reassigned as 1
            foundMatch = 1;
         }
      }
         
      /* where the first element in cpy_token[0] is not same as any of the elemnts in aliases array,
         call system function on the entire line of user input---------
         Use standard ANSI C system function to execute the line through the default system shell.
      */
      if(!foundMatch)
      {
         //call the duplicated and unmodified copy of myString.
         system(line);
      }       
      
      /* Deallocate each allocated memory used as extra storage for the tokenized strings
            using a while loop to decrement n after each deallocattion until n = 0
      */
      while(n > 0)
      {
         n--;
         free(cpy_token[n]);   
      }
   }
   
   //reassign foundmatch to 0
   foundMatch = 0;
   
   //deallocate the entire array of cpy_token[] allocated to hold an extra copy of the tokenized word.
   free(cpy_token);
       
   return(0);
}
