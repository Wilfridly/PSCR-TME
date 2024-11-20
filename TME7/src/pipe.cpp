#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

int main(int argc, char** argv){
    
    char* arg1[argc];
    char* arg2[argc];

    std::memset(arg1, 0, argc*sizeof(char*));
    std::memset(arg2, 0, argc*sizeof(char*));

    int i = 0;

    
    // for(i = 1; i < argc; i++){
    //     if(argv[i] == "|"){
    //         break;
    //     }
    //     arg1[i-1] = argv[i];
    // }
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i],"|") == 0) 
            break;
        arg1[i-1] = argv[i];
    }

    for(int j = i + 1; j < argc; j++){
        arg2[j-i-1] = argv[j];
    } 

    int pi[2];

    pipe(pi);

    for(int j = 0; j < argc; j++){
        std::cout << arg1[j] << " "<< arg2[j] << " : " << std::endl; 

    }

    if(fork() == 0){ // fils
        dup2(pi[1],STDOUT_FILENO);
        close(pi[1]); close(pi[0]);
        execv (arg1[0], arg1);
        perror(" ERROR EXEC");
    }
    else if(fork() == 0){
        dup2(pi[0],STDIN_FILENO);
        close(pi[1]); close(pi[0]);
        execv (arg2[0],arg2);
        perror(" ERROR EXEC");

    }else{
        close(pi[1]); close(pi[0]);
        wait(nullptr);
        wait(nullptr);
    }
    return (EXIT_SUCCESS);
}