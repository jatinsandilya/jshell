#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#define MAX_ARGS 64


int main(){

  std::string input;
  std::vector<const char *> tokens; // tokenized arguments

  while(true){

    std::cout << getcwd(NULL,0) <<":$ ";
    std::getline(std::cin,input);
    std::stringstream ss;
    ss << input;

    char * args[MAX_ARGS];
    char ** next = args;
    const char * str = input.c_str();
    const char * delim =  " " ;
    char * token = std::strtok(const_cast < char *> (str)," ");

    while(token){
      tokens.push_back(token);
      *next++ = token;
      // std::cout<< token << std::endl; // Debug
      token = std::strtok(NULL,delim);
    }
    *next = NULL; // Null terminated.
    if(strcmp(tokens[0],"cd") != 0 ){
      pid_t ppid = getpid();
      pid_t pid = fork();
      if(pid == -1){
        // std::cout<<" Failed to fork: " << std::endl;
        // Error failed to fork.
      }
      else if(pid > 0){
        // Parent process.
        // std::cout<<" Parent Process: " << std::endl;
        int status;
        waitpid(pid,&status,0);
      }
      else{
          // std::cout<<" Child Process: " << std::endl;
          execvp(args[0],args);
          exit(1); // exec does not returns unless its an error.
      }
    }
    else{
      int ret = chdir(args[1]);
    }
    // Resume here.
    tokens.clear();
  }

  return 0;
}
