#include "grammatica.h"
#include <iostream>

using namespace std;


int main(int argc, char** argv){
	Regexp r("(x)((a)|(c))(d)");
	Grammatica g(r);
	g.schrijfHTML(cout);
	return 0;
}