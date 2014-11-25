#include <queue>
#include <iostream>

typedef unsigned int uint;
typedef unsigned char uchar;

using std::cout;
using std::endl;

class KnuthMorrisPratt{
private:
	const uchar* naald;
	uint naaldlengte;
	uint* failure;

public:
	KnuthMorrisPratt(const uchar* naald, uint _naaldlengte);	//naald = pattern
	void zoek(std::queue<const uint>& plaats,
		const uchar* hooiberg, uint hooiberglengte);
};

KnuthMorrisPratt::KnuthMorrisPratt(const uchar* _naald, uint _naaldlengte){
	naald = _naald;
	failure = new uint[_naaldlengte];
	naaldlengte = _naaldlengte;
	uint i = 1;
	uint j = 0;
	failure[0] = 0;
	while (i < _naaldlengte){
		if (naald[i] == naald[j]){
			failure[i] = j + 1;
			i++;
			j++;
		}
		else if (j != 0){
			j = failure[j - 1];
		}
		else{
			failure[i] = 0;
			i++;
		}
	}
	for (uint z = 0; z < naaldlengte; z++){
		cout << failure[z] << " - ";
	}
}

void KnuthMorrisPratt::zoek(std::queue<const uint>& plaats,
	const uchar* hooiberg, uint hooiberglengte){
	uint j = 0;
	for (int i = 0; i < hooiberglengte; i++){
		while (true){	//loop tot break
			if (hooiberg[i] == naald[j]){	//matches?
				//cout << hooiberg[i] << "==" << naald[j] << endl;
				j++;	//ja, ga naar volgende staat
				if (j == naaldlengte){	//mss laatste?
					cout << "Gevonden op positie: " << i - j << endl;
					const uint pl = i - j;
					plaats.push(pl);
					j = failure[j - 1];	//terug naar laatste overlap
				}
				break;
			}
			else if (j > 0){
				j = failure[j - 1]; //probeer kleinere overlap
			}
			else{	//geen overeenkomst in status j == 0, geef op
				break;
			}
		}
	}
}