#include "RZB.cpp"
#include <math.h>
#include <iostream>
#include <sstream>


using namespace std;

const bool VERBOSE = false;

template <class T,class D>
int Rzwboom<T,D>::diepte(){

	int d = (k != NULL ? mijnDiepte(*this) : 0);
	if (VERBOSE)
		cout << "Diepte van de boom is "<< d << "\n";
	return d;
}

template <class T,class D>
int mijnDiepte(const Rzwboom<T, D> & n){
	int lDiepte = 0;
	if (n.k->links.k != NULL)
		lDiepte = mijnDiepte(n.k->links);
	int rDiepte = 0;
	if (n.k->rechts.k != NULL)
		rDiepte = mijnDiepte(n.k->rechts);
	int diepte = 1 + fmax(lDiepte,rDiepte);
	return diepte;
}

template <class T,class D>
int Rzwboom<T,D>::zwartediepte(){
	int d = (k != NULL ? mijnZwarteDiepte(*this) : 0);
	if (VERBOSE)
		cout << "Zwarte diepte van de boom is " << d << "\n";
	return d;
}

template <class T, class D>
int mijnZwarteDiepte(Rzwboom<T, D> & n){
	int lDiepte = 0;
	if (n.k != NULL){
		lDiepte = mijnZwarteDiepte(n.k->links);
		if (lDiepte == -1)
			return -1;
	}
	int rDiepte = 0;
	if (n.k != NULL){
		rDiepte = mijnZwarteDiepte(n.k->rechts);
		if (rDiepte == -1)
			return -1;
	}
	if (lDiepte != rDiepte){
		if (VERBOSE)
			cout << "ERROR bij knoop: " << n.k->sl << " linker ZwartDiepte is " << lDiepte << " rechter ZwartDiepte is  " << rDiepte << "\n";
		return -1;
	}
	int diepte = lDiepte; // = rDiepte
	if (VERBOSE && n.k != NULL)
		cout << "Knoop: " << n.k->sl << " linker zd is " << lDiepte << " rechter zd is  " << rDiepte << "\n";
	if (n.k == NULL || (n.k->ouder != NULL && n.geefkleur() == 1)){
		diepte += 1;
	}
	return diepte;
}

void visualization(string csv)
{
	stringstream stream;
	stream << "C:\\Users\\Mathias\\Desktop\\Treevis.exe" << " " << csv;
	system(stream.str().c_str());
}



template <class T, class D>
bool Rzwboom<T, D>::isKleurbaar(){
	bool kl = (k != NULL ? mijnIsKleurbaar(*this) : false);
	if (VERBOSE && kl)
		cout << "Goede RZW boom \n";
	else if (VERBOSE)
		cout << "Geen goede RZW boom \n";
			
	return kl;
}

template <class T, class D>
bool mijnIsKleurbaar(Rzwboom<T, D> & n){

	if (VERBOSE)
		cout << "Knoop " << n.k->sl << "\n";

	if (n.k->links.k != 0)
		if (!mijnIsKleurbaar(n.k->links)) return false;
	if (n.k->rechts.k != 0)
		if (!mijnIsKleurbaar(n.k->rechts)) return false;
	if (n.k->links.k == 0 && n.k->rechts.k == 0){	//BLADparent
		n.minZD = 1;
		n.maxZD = 1;
		n.isRoodbaar = true;
	}
	else if (n.k->links.k == 0 && n.k->rechts.k != 0){	//1 kind aan rechtse kant
		n.maxZD = 1; // links = 0 !
		n.minZD = n.k->rechts.minZD + !n.k->rechts.isRoodbaar;

		if (n.minZD > 1){	//omdat linkse kant leaf is : minimum van rechtse boom kan maximum 1 zijn
			if (VERBOSE)
				cout << "Fout bij knoop " << n.k->sl << "\n";
			return false;
		}
	}
	else if (n.k->links.k != 0 && n.k->rechts.k == 0){  //1 kind aan linkse kant
		n.maxZD = 1; // rechts = 0!
		n.minZD = n.k->links.minZD + !n.k->links.isRoodbaar;
		if (n.minZD > 1){	//omdat rechtse kant leaf is : minimum van linkse boom kan maximum 1 zijn
			if (VERBOSE)
				cout << "Fout bij knoop " << n.k->sl << "\n";
			return false;
		}
	}
	else if (n.k->links.maxZD + 1 >= n.k->rechts.minZD + !n.k->rechts.isRoodbaar 
		  && n.k->rechts.maxZD + 1 >= n.k->links.minZD + !n.k->links.isRoodbaar ){ // min-max waardes kloppen

		n.maxZD = fmin(n.k->links.maxZD + 1, n.k->rechts.maxZD + 1);
		int linksMin = n.k->links.minZD + !n.k->links.isRoodbaar;
		int rechtsMin = n.k->rechts.minZD + !n.k->rechts.isRoodbaar;
		n.minZD = fmax(linksMin, rechtsMin);

		if (linksMin < rechtsMin) {
			n.k->links.isRoodbaar = false;
			if (VERBOSE)
				cout << "Knoop " << n.k->links.k->sl << " MIN " << n.k->links.minZD << " | MAX " << n.k->links.maxZD << "  |  " << (n.k->links.isRoodbaar ? "Roodbaar" : "Niet roodbaar") << "\n";
		}
		else if (rechtsMin < linksMin) {
			n.k->rechts.isRoodbaar = false;
			if (VERBOSE)
				cout << "Knoop " << n.k->rechts.k->sl << " MIN " << n.k->rechts.minZD << " | MAX " << n.k->rechts.maxZD << "  |  " << (n.k->rechts.isRoodbaar ? "Roodbaar" : "Niet roodbaar") << "\n";
		}
	}
	else {
		if (VERBOSE)
			cout << "Fout bij knoop " << n.k->sl << "\n";
		return false;
	}
	if (!n.k->links.isRoodbaar && !n.k->rechts.isRoodbaar){ // enkel zwarte kinderen
		n.isRoodbaar = true;
	}
	if (VERBOSE){
		cout << "Knoop " << n.k->sl << " MIN " << n.minZD << " | MAX " << n.maxZD << "  |  " << (n.isRoodbaar ? "Roodbaar" : "Niet roodbaar") << "\n";
	}
	return true;
}


template <class T, class D>
void Rzwboom<T, D>::kleur(){
	bool kl = isKleurbaar();
	if (VERBOSE && !kl)
		cout << "Geen goede RZB, kon dus bijgevolg niet inkleuren \n";
	else if (kl)
		mijnKleur(*this);
}

template <class T, class D>
void mijnKleur(Rzwboom<T, D> & n){

	if (n.k->links.k != 0)
		mijnKleur(n.k->links);
	if (n.k->rechts.k != 0)
		mijnKleur(n.k->rechts);
	int zdLinks = mijnZwarteDiepte(n.k->links);
	int zdRechts = mijnZwarteDiepte(n.k->rechts);
	if (zdLinks == zdRechts){
		if (n.isRoodbaar){
			n.k->rzw = 0;
		}
		else{
			n.k->rzw = 1;
		}
	}
	else if (zdRechts > zdLinks && n.k->rechts.isRoodbaar){
		n.k->rechts.k->rzw = 0;
	}
	else if (zdLinks > zdRechts && n.k->links.isRoodbaar){
		n.k->links.k->rzw = 0;
	}
	else if (zdLinks < zdRechts && n.k->links.k != 0){
		n.k->links.k->rzw = 1;
	}
	else if (zdRechts < zdLinks && n.k->rechts.k != 0){
		n.k->rechts.k->rzw = 1;
	}	
}






int main(){
	Rzwboom<int, char> boom;
	/*
	boom.voegtoe(6, 'A');
	boom.voegtoe(2, 'B');
	boom.voegtoe(1, 'C');
	boom.voegtoe(8, 'D');
	boom.voegtoe(4, 'E');
	boom.voegtoe(9, 'F');
	boom.voegtoe(12, 'G');
	boom.voegtoe(5, 'H');
	boom.voegtoe(10, 'I');
	boom.voegtoe(15, 'J');
	boom.voegtoe(7, 'K');
	boom.voegtoe(17, 'K');*/

	// Complete boom
	/*
	boom.voegtoe(10, 'A', false);
	boom.voegtoe(5, 'A', false);
	boom.voegtoe(15, 'A', false);
	boom.voegtoe(3, 'A', false);
	boom.voegtoe(7, 'A', false);
	boom.voegtoe(13, 'A', false);
	boom.voegtoe(17, 'A', false);
	boom.voegtoe(1, 'A', false);
	boom.voegtoe(4, 'A', false);
	boom.voegtoe(6, 'A', false);
	boom.voegtoe(9, 'A', false);
	boom.voegtoe(11, 'A', false);
	boom.voegtoe(14, 'A', false);
	boom.voegtoe(16, 'A', false);
	boom.voegtoe(19, 'A', false);
	*/

	// Complexe boom
	/*
boom.voegtoe(5, 'A', false);
	boom.voegtoe(3, 'B', false);
	boom.voegtoe(7, 'C', false);
	boom.voegtoe(1, 'D', false);
	boom.voegtoe(6, 'F', false);
	boom.voegtoe(9, 'G', false);
	boom.voegtoe(8, 'H', false);*/


	vector<int> keys;
	for (int i = 0; i < 100; i++) keys.push_back(i);
	std::random_shuffle(keys.begin(), keys.end());
	for (int i = 0; i < 100; i++) boom.voegtoe(keys[i], i, true);

	cout << "Dit is de boom: " << endl;
	boom.schrijf(cout);

	cout << endl << "Boom is kleurbaar ? " << (boom.isKleurbaar() ? "Ja" : "Nee") << endl;

	cout << endl << "Inkleuren boom..." << endl;
	boom.kleur();

	cout << endl << "Diepte: " << boom.diepte();
	cout << endl << "Zwarte diepte: " << boom.zwartediepte() << endl;

	cout << endl << "Eindresultaat: " << endl;
	boom.schrijf(cout);
	visualization(boom.csv());

}
