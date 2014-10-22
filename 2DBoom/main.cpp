#include <cstdlib>
#include <ios>

#include "zoekboom.h"
#include "punt2.h"
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
	Zoekboom boom;
	const string puntenFile = "puntenverz.txt";

	vector<punt2> v;
	string s = "data";
	ifstream fstream(puntenFile);
	if (fstream.is_open()){
		int x = 0;
		while (fstream >> x){
			int y = 0;
			fstream >> y;
			punt2 punt(x, y);
			boom.voegtoe(punt, s);
			v.push_back(punt);
		}
		fstream.close();
	}
	else{
		cout << "Could not open file" << endl;
		return 1;
	}

	punt2 puntNA(1, 1);
	punt2 punt(1, 2);

	//Zoeken
	cout << (boom.zoek(punt) ? "Aanwezig" : "Afwezig") << endl;
	cout << (boom.zoek(puntNA) ? "Aanwezig" : "Afwezig") << endl;
	ofstream out("output.txt");
	for (punt2 p : v){
		int aantal = 0;
		punt2* b = boom.buur(p, &aantal);
		out << "punt2(" << p.x << ", " << p.y << ") heeft als dichtste buur punt ("	 << b->x << ", " << b->y << ") " << aantal << " knopen bezocht" << endl;
		cout << "punt2(" << p.x << ", " << p.y << ") heeft als dichtste buur punt (" << b->x << ", " << b->y << ") " << aantal << " knopen bezocht" << endl;
	}

	out.close();
    //cout << boom << endl;

    return 0;
}