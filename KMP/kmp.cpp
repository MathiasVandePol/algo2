#include "knuthmorrispratt.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using std::istream_iterator;
using std::ifstream;
using std::vector;
using std::queue;
typedef unsigned int uint;
typedef unsigned char uchar;

int main(){
	ifstream in("bijbel.txt");
	vector<unsigned char> bijbel;
	ifstream file1("bijbel.txt", std::ios_base::in | std::ios_base::binary);
	unsigned char ch = file1.get();
	while (file1.good())
	{
		bijbel.push_back(ch);
		ch = file1.get();
	}
	size_t size = bijbel.size();
	uchar* b = &bijbel[0];
	const uchar pattern[6] = "aarde";
	KnuthMorrisPratt kmp(pattern, 5);
	queue<const uint *> q;
	kmp.zoek(q, b, size);
}