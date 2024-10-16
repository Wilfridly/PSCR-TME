#include <vector>
#include <thread>
#include <cstdio>
#include <iostream>
#include <time.h>
#include "Banque.h"
using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTES = 50;
const int SOLDEINITIAL = 1000;

void transfertthread(pr::Banque & b){
	for(int k = 0; k < 3; k++){
		int i = 0;
		int j = rand()%NB_COMPTES;
		int m = rand()%10 +1;

		while((i = rand()%NB_COMPTES) == j);
		b.transfert(i, j, m);
		int delay = rand() % 20 + 1;
		// std::this_thread::sleep_for(chrono::milliseconds(delay));
		std::cout << "Transfert de " << i << " vers " << j << " de " << m << " euros" << std::endl;
	}
}

void comptable(pr::Banque &b, int attendu, int iter){
	for(int i = 0; i < iter;i++){
		b.comptabiliser(attendu);
	}
}

int main () {
	std::vector<pr::Compte> comptes;
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	pr::Banque b = pr::Banque(NB_COMPTES ,SOLDEINITIAL);

	srand( time( NULL ) );
	std::thread t1(comptable, std::ref(b), NB_COMPTES * SOLDEINITIAL, NB_COMPTES);

	for(int i = 0; i < NB_THREAD; i++){
		threads.emplace_back(std::thread(transfertthread,std::ref(b) ));
	}

	t1.join();
	for(auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
