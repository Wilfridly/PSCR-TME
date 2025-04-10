#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <cstdio>
#include "hashmap.h"

template <typename iterator>
size_t countp(iterator begin, iterator end){
	size_t count = 0;
	for(begin ; begin != end; begin++,count++);// for(;begin != end;begin++ , count++); 
	return count;
};

template <typename iterator, typename T>
size_t count_if_equal (iterator begin, iterator end, const T & val){
	size_t count = 0;
	for(begin; begin !=end; begin++){
		if(*begin == val){
			count++;
		}
	}
	return count;
}

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
	int *a = hashmap.get("war");
	int *b = hashmap.get("peace");
	int *c = hashmap.get("toto");
	
	// if((!c)){
	// 	cout << "Le nombre d'occurence de toto est 0" << endl;

	// }
	// cout << "Le nombre d'occurence de peace est " << *b << endl;
	// cout << "Le nombre d'occurence de war est " << *a << endl;

	std::vector<pair<std::string,int>> hashmapcopie; //(hashmap.getbuckets() , hashmap.getbuckets().end());
	std::vector<pair<std::string,int>> hashmapcopie2; //(hashmap.getbuckets() , hashmap.getbuckets().end());
	
	
	for(auto &bucket: hashmap.getbuckets()){ //Première copie 
		for(auto &entry: bucket){
			hashmapcopie.push_back({entry.key,entry.value});
		}
	}
	
	// sort(hashmapcopie.begin(),hashmapcopie.end(),[](pair<std::string,int> &a,pair<std::string,int> &b){ return a.second > b.second;});
	// int equal10 = 0;
	// for (auto it = hashmapcopie.begin(); (it < hashmapcopie.end() && equal10 < 100); ++it) {
	// 	std::cout << it->first << ":" << it->second << endl;
	// 	++equal10;
	// }

    for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
        hashmapcopie2.push_back({it->key, it->value}); // Utilisation de l'opérateur -> pour accéder à key et value
    }

	sort(hashmapcopie2.begin(),hashmapcopie2.end(),[](pair<std::string,int> &a,pair<std::string,int> &b){ return a.second > b.second;});
	int equal10 = 0;
	for (auto it = hashmapcopie2.begin(); (it < hashmapcopie2.end() && equal10 < 10); ++it) {
		std::cout << it->first << ":" << it->second << endl;
		++equal10;
	}

	std::string mote = "war";
	size_t compteur = countp(vect.begin() , vect.end());
	cout << compteur << endl;
	size_t compteur2 = count_if_equal(vect.begin() , vect.end(), "war");
    cout << compteur2 << endl;
	return 0;
}