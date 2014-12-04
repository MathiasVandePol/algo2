#include "unionfind.h"
#include "boek.h"
#include <iostream>
using std::cout;
using std::endl;



int main () {
	// Unionfind uf = Unionfind(5);
	// cout << "find 1: " << uf.find(1) << endl;
	// uf.uni(4,0);
	// cout << "find na uni 4,0: " << uf.find(4) << " " << uf.find(0) << endl;
	// uf.uni(2,0);
	// cout << "find na uni 2,0: " << uf.find(2) << " " << uf.find(0) << endl;

	// Vers v1 = Vers("In the beginning God created the heaven and the earth.");
	// Vers v2 = Vers("And God set them in the firmament of the heaven to give light upon the earth,");
	// int aantal_verzen = 2;
	// GraafMetTakdata<ONGERICHT, int> graaf(aantal_verzen);



	// Vers v3 = Vers("the the the");
	// Vers v4 = Vers("the the the");
	// Vers v5 = Vers("merlijn is stom");
	// v1.schrijf();

	// cout << "afstand tss v1 en v2: " << v1.afstand(v2) << " " << v2.afstand(v1) << endl;
	// cout << "afstand tss v1 en v2: " << v3.afstand(v3) << " " << v3.afstand(v3) << endl;


	Boek boek("bijbel.txt");
	cout << boek << endl;




	return 0;
}