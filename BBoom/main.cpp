/* jasper.commeijne@ugent.be */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <Windows.h>
#include "schijf.h"
#include "btree.h"



using namespace std;



void basicBTree()
{
	const int m = 3;
	Schijf<Bknoop<string, int, m>> s = Schijf<Bknoop<string, int, m>>();
	Btree<string, int, m> tree = Btree<string, int, m>(s);
	string h = "hello";
	int v = 54;
	tree.voegtoe(h, v);
	tree.voegtoe(h, v);
	h = "hello2youtoo";
	 v = 55;
	tree.voegtoe(h, v);
	h = "hello2youadsfasdfetoo";
	v = 55;
	tree.voegtoe(h, v);
	h = "hello2youdadsftoo";
	v = 55;
	tree.voegtoe(h, v);
	h = "hello2youdfdtoo";
	v = 55;
	tree.voegtoe(h, v);
	h = "hello2yadsoutoo";
	v = 55;
	tree.voegtoe(h, v);
	return;

}

template <class T, class D, unsigned int m>
void Btree<T, D, m>::voegtoe(T & sleutel, D & data)
{
	cout << "Voegtoe: " << sleutel << "->" << data << endl;
	blokindex index = 0;
	Bknoop<T, D, m>* knoop = &wortel;
	if (zoek(sleutel, knoop, index))
	{
		cout << "Bestaat al!" << endl;
	}
	else
	{
		cout << "Bestaat nog niet!" << endl;
		if (knoop->k == 0){	//nog geen elementen in de tree
			knoop->sleutel[knoop->k] = sleutel;
			knoop->data[knoop->k] = data;
			schijf.herschrijf(*knoop, wortelindex);
			knoop->k++;
		}
		else if (knoop->k < m){
			knoop->sleutel[knoop->k] = sleutel;
			knoop->data[knoop->k] = data;
			schijf.herschrijf(*knoop, index);
			knoop->k++;
		}
		while (knoop->k == m){
			Bknoop<T, D, m> * nieuwe = new Bknoop<T, D, m>();
			for (int i = m / 2 + 1; i < m; i++){
				nieuwe->sleutel[(i - m / 2) - 1] = knoop->sleutel[i];
				if (!knoop->isblad){
					nieuwe->index[(i - m / 2) - 1] = knoop->index[i];
				}
				knoop->k = (m / 2);
			}
			Bknoop<T, D, m> * parent = 0;
			while (index != 0){
				this->schijf.lees(*parent, index);
				if (parent->k < m)
					break;
			}
			bool isNieuwe = false;	//nieuwe root of niet
			if (parent == 0){
				isNieuwe = true;
				parent = new Bknoop<T, D, m>();
			}
			blokindex b = this->schijf.schrijf(*nieuwe);
			parent->sleutel[parent->k] = knoop->sleutel[(m / 2)];
			parent->index[parent->k] = b;
			parent->k++;	
			if (isNieuwe){
				this->wortelindex = this->schijf.schrijf(*parent);
				this->wortel = *parent;
			}
			else{
				this->schijf.herschrijf(*parent, index);
			}
			knoop = parent;
		}
	}

}

template <class T, class D, unsigned int m>
bool Btree<T, D, m>::zoek(T & sleutel, Bknoop<T, D, m> * zoekKnoop, blokindex & parentIndex)
{
	cout << "Zoek: " << sleutel << endl;
	int i = 0;
	while (i < zoekKnoop->k && zoekKnoop->sleutel[i] < sleutel)
	{
		i++;
	}
	if (i < m && zoekKnoop->sleutel[i] == sleutel)
	{
		return true;
	}
	if (zoekKnoop->isblad)
	{
		return false;
	}
	schijf.lees(*zoekKnoop, zoekKnoop->index[i]); //overschrijf de huidige zoekknoop
	return zoek(sleutel, zoekKnoop, zoekKnoop->index[i]);
}



int main()
{
	basicBTree();
}




