#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include "zinduo.h"
#include <queue>
using namespace std;

char checkChar(char in){
  if(in<='Z' && in>='A'){
    return in-('Z'-'z');
  }
  else if (ispunct(in)){
  	return ' ';
  }
  return in;
} 


void leesbestand(const string bestandsnaam, vector<vector<string>> & zinnen)
{
	ifstream in(bestandsnaam);
	string regel;
	if (in.is_open()){
		while (getline(in, regel)){
			stringstream iss(regel);
			string rommel;
			for (int i = 0; i < 2; i++){	//verwijder GEN brol
				getline(iss, rommel, ' ');
			}
			getline(iss, regel);
			transform(regel.begin(), regel.end(), regel.begin(), checkChar);
			stringstream z(regel);
			string word;
			vector<string> woord;
			while (z >> word){
				woord.push_back(word);
			}
			zinnen.push_back(woord);
		}
	}
}

void maakZinDuos(priority_queue<ZinDuo>& zinDuos, vector<vector<string>>& zinnen){
	for (vector<string> zin1 : zinnen){
		for (vector<string> zin2 : zinnen){
			if (zin1 != zin2){
				ZinDuo z(zin1, zin2);
				zinDuos.push(z);
			}
		}
	}
}

int main(){
	vector<vector<string>> zinnen;
	leesbestand("bijbel.txt", zinnen);
	priority_queue<ZinDuo> zinDuos;
	maakZinDuos(zinDuos, zinnen);
	cout << zinDuos.top().score;
}