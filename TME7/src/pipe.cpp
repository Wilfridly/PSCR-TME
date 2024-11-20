#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main(int argc, char** argv){
    
    int pipe[2];
    int i;

    
    for(i = 0; i < argc; i++){
        if(argv[i] == "|"){
            break;
        }
    }

    char* arg1[i+1];
    char* arg2[argc - i +1];
    i++;

    for(int j = 0 ; j < i; j++, i++){
        arg1[j]= argv[i];
    }

    
    for(int j = 0 ; i < argc; j++){
        arg2[j]= argv[i];
    }

    std::cout << arg1 << " : " << std::endl;
    if(fork() == 0){ // fils
        dup2(pipe[1],STDOUT_FILENO);
        close(pipe[0]); close(pipe[1]);
        execv (arg1[0], arg1);
    }
    else if(fork() == 0){
        dup2(pipe[0],STDIN_FILENO);
        close(pipe[0]); close(pipe[1]);
        execv (arg2[0],arg2);
    }else{
        close(pipe[0]); close(pipe[1]);
        wait(nullptr);
        wait(nullptr);
    }

}