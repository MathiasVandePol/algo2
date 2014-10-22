#include "graaf.h"
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class woordspelletje {
protected:
	typedef std::map<int, int>  Knoop;      // beeldt knoopnummer (van buur) af op verbindingsnummer
	Graaf<GERICHT> graaf;
	Graaf<GERICHT> omgekeerdeGraaf;
	map<string, int> woordenMap;			//Woorden
	vector<string> alleWoorden;
	vector<int>	componentnummer;
	std::stack<int> s;

public:

	woordspelletje(){
	}
	~woordspelletje(){
	}



	void leesWoordenIn(string bestandsnaam){
		string s = "data";
		ifstream fstream(bestandsnaam.c_str());
		int i = 0;
		if (fstream.is_open()){
			while (fstream >> s){
				woordenMap[s] = i++;;
				alleWoorden.push_back(s);
				graaf.voegKnoopToe();
				omgekeerdeGraaf.voegKnoopToe();
			}
			fstream.close();
		}
		else{
			cout << "Could not open file woordenlijst" << endl;
		}
		componentnummer.resize(graaf.aantalKnopen());
	}

	void leesVerbindingenIn(string bestandsnaam){
		string s1 = "";
		string s2 = "";
		string s3 = "";
		ifstream fstream2(bestandsnaam.c_str());
		int j;
		if (fstream2.is_open()){
			while (fstream2 >> s1 >> s2 >> s3){
				j = graaf.voegVerbindingToe(woordenMap[s1], woordenMap[s2]);
				omgekeerdeGraaf.voegVerbindingToe(woordenMap[s2], woordenMap[s1]);
			}
			fstream2.close();
		}
		else{
			cout << "Could not open file takkenlijst" << endl;
		}
	}

	void overloopPostorder(){
		for (unsigned int i = 0; i < omgekeerdeGraaf.knopen.size(); i++){
			if (componentnummer[i] == 0){
				overloopPostorder(i);
			}
		}
	}

	void overloopPostorder(int index){	//-1 = bezocht, 0 = niet bezocht , i=1-m = deel van component i
		componentnummer[index] = -1;
		for (Knoop::const_iterator i = omgekeerdeGraaf.knopen[index].begin(); i != omgekeerdeGraaf.knopen[index].end(); i++){
			if (componentnummer[i->first] == 0){
				overloopPostorder(i->first);
			}
		}
		s.push(index);
	}


	int componentnummerZoeker(){
		int componentNr = 1;
		while (!s.empty()){
			int topIndex = s.top();
			if (componentnummer[topIndex] == -1){
				componentnummerZoeker(componentNr, topIndex);
				componentNr++;
			}
			s.pop();
		}
		cout << "Aantalcomponentnummer " << componentNr << endl;
		return componentNr;
	}

	void componentnummerZoeker(int componentNr, int knoopIndex){
		componentnummer[knoopIndex] = componentNr;
		for (Knoop::const_iterator i = graaf.knopen[knoopIndex].begin(); i != graaf.knopen[knoopIndex].end(); i++){
			if (componentnummer[i->first] == -1){
				componentnummerZoeker(componentNr, i->first);
			}
		}
	}

	void printAllComponenten(ostream & out, int aantalComponenten){
		for (int i = 0; i < aantalComponenten; i++){
			printAlleWoordenVanComponent(out, i);
		}
	}

	void printAlleWoordenVanComponent(ostream & out, int nr){
		out << "Component " << nr << endl;
		int j = 0;
		for (int i = 0; i < componentnummer.size(); i++){
			if (componentnummer[i] == nr){
				j++;
				out << "      " << alleWoorden[i] << endl;
			}
		}
		out << "In totaal " << j << " knopen in deze component" << endl;
	}

	
};




int main(int argc, char** argv) {
	const string woorden = "woordenlijst.txt";
	const string takken = "takkenlijst.txt";
	woordspelletje w;
	w.leesWoordenIn(woorden);
	w.leesVerbindingenIn(takken);
	w.overloopPostorder();
	int aantalC = w.componentnummerZoeker();
	ofstream out("output.txt");
	w.printAllComponenten(out, aantalC);
	return 0;
}

