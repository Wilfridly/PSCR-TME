#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include "rsleep.h"

void attaque (pid_t adversaire){
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);

    signal(SIGINT,[](int ){sig--;});

}

void defense (){
    //
    randsleep()
}

void combat (pid_t adversaire){
    while(true){
        defense();

        attaque(adversaire);
    }
}


int main(){ //
    int life = 3;

    if(fork() == 0){ //Luke
        
    }else{ // Vador

    }
}