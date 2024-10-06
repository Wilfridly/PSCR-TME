#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <cstdio>
#include <unordered_map>

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
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;
	
	size_t nombre_lu = 0;
	// prochain mot lu
	string word;

    std::unordered_map<std::string,int> hashmap;
	// Hashmap<std::string,int> hashmap;

	std::vector<std::string> vect;	
	std::vector<pair<std::string,int>> vectpair;

	int count = 1;
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

		vect.push_back(word); //Vecteur 1 avec tous les mots

        hashmap[word]++;
        

	}
	input.close();


	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Vecteur size : " << count << endl;

    // for(auto &p : hashmap){
    //     std::cout << p.first << " => " << p.second << std::endl;
    // }

    cout << hashmap.find("war")->second << endl;    
    
    return 0;
}