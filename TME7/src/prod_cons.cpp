#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>  


using namespace std;
using namespace pr;

#define N 10
#define M 10

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

std::vector<pid_t> tokill;
void killen(int){
	for(auto &p : tokill){
		kill(p,SIGINT);
	}
}

int main () {
	size_t shmsize = sizeof(Stack<char>);
	int fd;
	void *addr;

	bool useAnonymous = false;
	
	if(useAnonymous){
		addr == mmap(nullptr,shmsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		if(addr == MAP_FAILED){
			perror("map anonymous error");
			exit(1);
		}
	} else {
		fd = shm_open("/monshm", O_CREAT | O_EXCL | O_RDWR, 0666);
		if(fd < 0){
			perror("shm open error");
			exit(1);
		}
		if(ftruncate(fd,shmsize) != 0 ){
			perror("ftruncate error");
			exit(1);
		}
		addr = mmap(nullptr, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if(addr == MAP_FAILED){
			perror("mmap error");
			exit(1);
		}
	}

	Stack<char> * s = new (addr) Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		for(int i = 0; i < N ;i++){
			producteur(s);
		}
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		for(int i = 0; i < M ; i++){
			consomateur(s);
		}
		return 0;
	}
	else{
		tokill.push_back(pc);
	}
	signal(SIGINT,killen);

	wait(0);
	wait(0);

	s->~Stack();

	if(munmap(addr,shmsize) != 0){
		perror("munmap error");
		exit(1);
	}
	if(!useAnonymous){
		if(shm_unlink("/monshm") != 0){
			perror("munmap error");
			exit(1);
		}
	}
	return 0;
}

