#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::mutex m;
	mutable std::recursive_mutex m2;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const ;
	std::recursive_mutex & getMutex() const;
};

}
