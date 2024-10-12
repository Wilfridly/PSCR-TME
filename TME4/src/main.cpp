#include <vector>
#include <thread>
#include <cstdio>
#include <iostream>
#include <time.h>
#include "Banque.h"
using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTES = 3;
// const int JP = 10000;

const int SOLDEINITIAL = 1000;

void transfertthread(pr::Banque & b){
	for(int k = 0; k < 3; k++){
		int i = 0;
		int j = rand()%NB_COMPTES;
		int m = rand()%10 +1;

		while((i = rand()%NB_COMPTES) == j);
		// std::cout << "TransfertCom : "<< i <<" j : "<< j << std::endl;
		b.transfert(i, j, m);
		int delay = rand() % 20 + 1;
		std::this_thread::sleep_for(chrono::milliseconds(delay));
		std::cout << "Transfert de " << i << " vers " << j << " de " << m << " euros" << std::endl;
	}
}

int main () {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	pr::Banque b = pr::Banque(NB_COMPTES ,SOLDEINITIAL);
	srand( time( NULL ) );
	for(int i = 0; i < NB_THREAD; i++){
		threads.emplace_back(std::thread(transfertthread,std::ref(b) ));
	}

	for(auto & t : threads) {
		t.join();
	}
	// threads.emplace_back(std::thread())
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
