#include <cstdlib>
#include <ios>

#include "graaf.h"
#include <string>
#include <fstream>

using namespace std;
using std::pair;
using std::cout;
using std::endl;


/*
 * 
 */
int main(int argc, char** argv) {
	Graaf<GERICHT> graaf;
	Graaf<GERICHT> omgekeerdeGraaf;
	const string woordne = "woordenlijst.txt";

	map<string, int> woordenMap;			//Woorden
	//map<string, vector<int>> verbindingMap;			//Verbindingen

	string s = "data";
	ifstream fstream(woordne);
	int i = 0;
	if (fstream.is_open()){
		while (fstream >> s){
			woordenMap[s] = i++;;
			graaf.voegKnoopToe();
			omgekeerdeGraaf.voegKnoopToe();
		}
		fstream.close();
	}
	else{
		cout << "Could not open file woordenlijst" << endl;
		return 1;
	}


	const string takken = "takkenlijst.txt";

	string s1 = "";
	string s2 = "";
	string s3 = "";
	ifstream fstream2(takken);
	int j ;
	if (fstream2.is_open()){
		while (fstream2 >> s1 >> s2 >> s3){
			j = graaf.voegVerbindingToe(woordenMap[s1], woordenMap[s2]);
			omgekeerdeGraaf.voegVerbindingToe(woordenMap[s2], woordenMap[s1]);
			//verbindingMap[s3].push_back(j);
		}
		fstream2.close();
	}
	else{
		cout << "Could not open file takkenlijst" << endl;
		return 1;
	}
	graaf.schrijf(cout);
	omgekeerdeGraaf.schrijf(cout);

	

    return 0;
}