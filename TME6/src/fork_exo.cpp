#include <sys/wait.h>
#include <iostream>
#include <unistd.h>


int main () {
	const int N = 3;
	int cpt = 0;
	int pid;
	int mainpid = getpid();
	std::cout << "main pid =" << mainpid << std::endl;

	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if(fork() == 0){
			cpt = 0;
		}else{
			std::cout << " i:j " << i << ":" << j << std::endl;
			cpt++;
			break;
		}

		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				cpt= 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}else{
				cpt++;
			}
		}
	}
	
	
	for (int i=0; i < cpt; i++) {
		// wait(nullptr);
		int status;
		int pid = wait(&status);
	}
	std::cout << "Fin du processus " << getpid() << std::endl;
	if(mainpid == getpid()){
		std::cout << "ouuiiii le père attend ses fils" << std::endl;
	}
	
	return 0;
}
