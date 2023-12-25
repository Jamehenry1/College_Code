/*
  Name: Nghia Lam
  ID: 1001699317
*/

// The MIT License (MIT)
// 
// Copyright (c) 2016 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 11     // Mav shell only supports four arguments

int main()
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );
  int count = 0;
  char historyName[15][MAX_COMMAND_SIZE]; 
  int over14 = 0; //holds the number 15 if there has already been 15 inputs into history
  int pidHistory[15];
  int pidCount = 0; //the placement in the pidHistory
  int pidOver14 = 0;  //holds the number 15 if there has already been 15 inputs into pidHistory
  for(count = 0; count < 15; count++) //make sure there is nothing when creating the array
  {
    memset( historyName[count], 0, 15 );
  }
  
  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
    int c = 0;                                 
    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;                  

    // replace here 
    //printf("%d\n", strlen(command_string));
    if( command_string[0] == '!')
    {
      int index = ((int)command_string[1]) - 48;  //calculate the number for the first intvalue
      int index2 = ((int)command_string[2]) - 48; //calculate the number for the second int value
      //printf("test: %d\n", index2);
      // copy from pidhistory on top of command_string and checks for pid number
      if(index2 >= 0)
      {
        index = 10 + index2;
      }
      //checks if it is valid by the amount of how many are already in index 
      //and comparing if the value of index is doable via index over14
      if((index <= (over14-1)) && (index < 15))
      {
        strcpy(command_string, historyName[index]);

        //printf("%s\n", command_string);
      }
      else if((historyName[index] == NULL) || (index > 14))
      {
        printf("Command not in history\n");
      }
      else 
      {
        printf("Command not in history\n");
      }
      //printf("test1: %s\n",historyName[index]);
    }                       
                                                           
    char *working_string  = strdup( command_string );                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_string, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
      token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality

    pid_t pid;
    int status = 0;
    if(token[0] != NULL) //checks if any value is inputed
    {

      if(over14 > 15) //make sure the count is no more than 15 index
      {
        over14 = 15;
      }
      if(count > 14)  //restarts the placement of the array if it goes over 14
      {
        count = 0;
      }
      strcpy(historyName[count],command_string); 
      count++;
      over14++;

      //test to see if quit and exit was entered and if it was then exit the process
      if((!strcmp("quit",token[0])) || (!strcmp("exit",token[0])))
      {
        //printf("area 1\n");
        exit(0);
      }
      //changes directory up
      //else if((!strcmp(token[0],"cd")) && (!strcmp(token[1],"..")))
      //{
      //  chdir(token[1]);
      //}
      //changes directory 
      else if(!strcmp(token[0],"cd")) 
      {
        chdir(token[1]);
      }
      //check if pidhistory was entered and if it was then run through each input up to 15
      else if(!strcmp(token[0],"history"))
      {
        //printf("broke here1\n");
        //printf("amount: %d\n", over14);
        for(c = 0; (c < over14) && (c != 15); c++)
        {
          printf("%d:%s",c,historyName[c]);
        }
      }
      else if(!strcmp(token[0],"pidhistory"))
      {
        int p = 0;
        if(pidOver14 >= 15) //makes sure when the pid goes over 15 it still shows 15 pids
        {
          pidOver14 = 15;
        }
        
        for(p = 0;p < pidOver14;p++)  //showing pids based on how many are avaliabe 
        {
          printf("%d: %d\n",p,pidHistory[p]);
        }
      }
      //test to see if the process is a real process to fork and forks it
      else
      {
        pid = fork();
        //printf("test1\n");
        if(pid == 0) //if it is the child execute
        {
          execvp(token[0],&token[0]);
          printf("command not found\n");
          exit(0);
        }
        else //if parent
        {       
          wait(&status);
          pidHistory[pidCount] = pid; // input pid number into pidarray
          //printf("%d\n", pidHistory[pidCount]);
          pidCount++;
          pidOver14++;
          if(pidCount > 14)
          {
            pidCount = 0;
          }
          //waitpid(pid, &status, 0);
          //printf("testing2\n");
        }
      }
    }
  
    free( head_ptr );
  }
  return 0;
  // e2520ca2-76f3-11ec-90d6-0242ac120003

}


