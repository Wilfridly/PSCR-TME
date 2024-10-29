#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include "rsleep.h"

int life = 3;

void attaque (pid_t adversaire){
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);

    signal(SIGINT,[](){life--;});

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
    
    int vador = getpid();
    int luke = fork();

    if(luke == 0){ //Luke
        combat(vador);        
    } else{ // Vador
        combat(luke);
    }

    return 0;
}