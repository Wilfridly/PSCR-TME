#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;
	
	size_t nombre_lu = 0;
	// prochain mot lu
	string word;

	std::vector<std::string> vect;
	int count = 0;

	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

		vect.push_back(word); //Vecteur 1 avec tous les mots


		// for(std::string i:vect){
		// 	if(i == word){
		// 		break;
		// 	}
		// 	vect.push_back(word);
		// }
	}
	input.close();

	sort(vect.begin(),vect.end());

	for(auto i = 1; i < vect.size();i++){
		if(vect[i] != vect[i -1]){
			count ++;
		}
	}

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Vecteur size : " << count << endl;
    return 0;
}


