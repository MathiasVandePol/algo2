#ifndef __VERS_H
#define __VERS_H
#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::string;

#include <map>

#include <sstream>

#include <math.h>

using namespace std;


class Vers {
	public:
		Vers(string tekst);
		void schrijf();
		double afstand(Vers& versnaar);
		int get_aantalWoorden();
		friend ostream& operator<<(ostream& os, const Vers& vers);

	private:
		map<string, int> wdbk;
		string _tekst;
		int aantalWoorden = 0;
};

bool my_predicate(char c) {
	char chars[] = "azertyuiopqsdfghjklmwxcvbn ";

	for(int i = 0; i < 27; i++) {
		if(c == chars[i]) {
			return false;
		}
	}

	return true;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

Vers::Vers(string tekst) {
	std::transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
	tekst.erase(std::remove_if(tekst.begin(), tekst.end(), my_predicate), tekst.end());

    vector<string> elems;
    split(tekst, ' ', elems);

    for(string el : elems) {
    	if(el != "") {
    		wdbk[el]++;
    		aantalWoorden++;
    	}
    }
}

void Vers::schrijf() {
	map<string,int>::iterator it = wdbk.begin();
	while(it != wdbk.end()) {
		cout << it->first << " " << it->second << endl;
		it++;
	}
}

double Vers::afstand(Vers& versnaar) {
	int aantalOvereenkomende = 0;

	map<string, int>::iterator itZin1 = this->wdbk.begin();
	map<string, int>::iterator itZin2 = versnaar.wdbk.begin();

	while (itZin1 != this->wdbk.end() && itZin2 != versnaar.wdbk.end()){
		if (itZin2->first == itZin1->first){
			int kleinste = itZin2->second > itZin1->second ? itZin1->second : itZin2->second;
			aantalOvereenkomende+=kleinste;
			itZin2++;
		} else if (itZin2->first > itZin1->first) {
			itZin1++;
		} else {
			itZin2++;
		}
	}

	return log((double)(this->aantalWoorden + versnaar.get_aantalWoorden()) / (double)(2 * aantalOvereenkomende));
}

int Vers::get_aantalWoorden() {
	return aantalWoorden;
}

ostream& operator<<(ostream& os, const Vers& vers) {
	map<string,int>::const_iterator it = vers.wdbk.begin();

	while(it != vers.wdbk.end()) {
		os << it->first << " " << it->second << endl;
		it++;
	}

	return os;
}
#endif