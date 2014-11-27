#include "thompsonna.h"
#include "na.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::cout;
using std::endl;

void leesBestand(vector<string>& zinnen, const string bestandsnaam){
	ifstream in(bestandsnaam);
	if (in.is_open()){
		string zin;
		while (getline(in, zin)){
			zinnen.push_back(zin);
		}
		in.close();
	}
}


void verwerkZinnen(vector<string>& zinnen, Na & na){
	for (string zin : zinnen){
		for (char c : zin){
			if (na.verwerkKarakter(c)){
				cout << zin << endl;
				break;
			}
		}
	}
}


int main(){
	Regexp regexp = Regexp("ni(et|s)");
	ThompsonNA thompson = ThompsonNA(regexp);
	thompson.schrijf(cout);
	Na na(thompson);
	//cout << "verbinding 3: " << thompson[3] << endl;
	cout << na;
	vector<string> zinnen;
	leesBestand(zinnen,"lorem.txt");
	verwerkZinnen(zinnen, na);
	return 0;
}

