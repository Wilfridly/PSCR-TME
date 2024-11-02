#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
// #include <csignal>
#include <signal.h>
#include "rsleep.h"

int life = 3;
bool who;
void sighandler(int sig) {
    life--;
    if(who){
        std::cout << "La vie de Vador est de " << life << std::endl;;
    }else{
        std::cout << "La vie de Luke est de " << life << std::endl;;
    }
}

void attaque (pid_t adversaire){

    struct sigaction sa;
    sigemptyset(&sa.sa_mask); //set à 0, on ne l'utilise pas
    sa.sa_flags=0; //set à 0
    sa.sa_handler = sighandler;

    if (life <= 0){
        std::cout << "Le processus se termine " << std::endl;
        // if(!who){
        wait(nullptr);
        // }
        exit(1);
    }
    
    int invocation = sigaction(SIGINT, &sa, NULL);
    kill(adversaire, SIGINT);
    
    if (invocation == EXIT_FAILURE){
        exit(0);
    }
    
    randsleep();
}

void defense (){
    struct sigaction sa;
    sa.sa_flags=0;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);

    if(who){
        std::cout << "Esquive de la loutre de Vador" << std::endl;;
    }else{
        std::cout << "Esquive de la loutre de Luke " << std::endl;;
    }
    randsleep();
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
    srand(time(NULL));

    if(luke == 0){ //Luke
        who = 0;
        combat(vador);    
    } else{ // Vador
        who = 1;
        combat(luke);
    }

    return 0;
}