#ifndef _ZINDUO_H
#define _ZINDUO_H
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class ZinDuo
{
public:
	ZinDuo(vector<string>& _zin1, vector<string>& _zin2):zin1(_zin1),zin2(_zin2){
		score = berekenScore();
		cout << "Score berekend: " << score << endl;
	}
	double score;

	bool operator < (const ZinDuo &duo2) const
	{
	    return this->score < duo2.score;
	}

	const ostream& operator << (ostream &os) 
	{
	   os << zin1[0] << " - "  << zin2[0] << " : " << score << endl;
	   return os;
	}


private:
	vector<string> zin1, zin2;
	double berekenScore();


};


double ZinDuo::berekenScore(){
	int aantalOvereenkomende = 0;
	int grootteZin1 = zin1.size();
	int grootteZin2 = zin2.size();
	vector<string>::iterator itZin1 = zin1.begin();
	while (itZin1 != zin1.end()){
	vector<string>::iterator itZin2 = zin2.begin();
		while (itZin2 != zin2.end()){
			if (*itZin2 == *itZin1){	//woorden komen overen
				aantalOvereenkomende++;
			}
			itZin2++;
		}
		itZin1++;
	}
	if (aantalOvereenkomende == 0){
		return -1;
	}
	return log(grootteZin1 + grootteZin2) / (2 * aantalOvereenkomende);
}

#endif