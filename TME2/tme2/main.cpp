#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "hashmap.h"
#include <cstdio>

int main () {
	using namespace std;
	using namespace pr;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;
	
	size_t nombre_lu = 0;
	// prochain mot lu
	string word;

	pr::Hashmap<std::string,int> hashmap;

	std::vector<std::string> vect;	
	std::vector<pair<std::string,int>> vectpair;
	int count = 0;
	int u = 1;
	int p,count2 = 1;
	int i = 1;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		// if (nombre_lu % 100 == 0)
		// 	// on affiche un mot "propre" sur 100
		// 	cout << nombre_lu << ": "<< word << endl;
		// nombre_lu++;

		vect.push_back(word); //Vecteur 1 avec tous les mots
		hashmap.put(word, 1);
	}
	input.close();

	sort(vect.begin(),vect.end());

	for(auto i = 1; i < vect.size();i++){
		if(vect[i] != vect[i - 1]){
			count ++;
			vectpair.push_back(make_pair(vect[i-1],count2+1));
			count2 = 0;	
		}
		else{
			count2++;
		}
	}

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Vecteur size : " << count << endl;
	
	// for (auto p : vectpair) {
	// 	std::cout << "mot : " << p.first << ", qté: " << p.second << std::endl;
    // }

	for (auto p : vectpair) {
		if (p.first == "war"){
			cout << "war a " << p.second << " occurence" << endl;
		}
		if (p.first == "peace"){
			cout << "peace a " << p.second << " occurence" << endl;
		}
		if (p.first == "toto"){
			cout << "toto a " << p.second << " occurence" << endl;
		}
	}
	int* a = hashmap.get("war");
	cout << "La valeur de war est " << *a << endl;
	// printf("%d \n",hashmap.get("war"));
    return 0;
}