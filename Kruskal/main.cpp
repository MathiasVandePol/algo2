#include "unionfind.h"
#include "graaf.h"
#include <iostream>
using std::cout;
using std::endl;



int main () {
	Unionfind uf(8);
	GraafMetTakdata <ONGERICHT,int> gr(8);
    gr.voegVerbindingToe(1,2,7 );
    gr.voegVerbindingToe(7,1,2 );
    gr.voegVerbindingToe(7,3,6 );
    gr.voegVerbindingToe(3,4,7 );
    gr.voegVerbindingToe(4,5,1 );
    gr.voegVerbindingToe(2,5,4 );
    gr.voegVerbindingToe(1,0,9 );
    gr.voegVerbindingToe(0,2,3 );
    gr.voegVerbindingToe(0,7,5 );
    gr.voegVerbindingToe(0,6,6 );
    gr.voegVerbindingToe(5,6,6 );
    gr.voegVerbindingToe(6,3,2 );
    gr.voegVerbindingToe(6,4,8 );
    vector<Verbinding<int>> MOB;
	while (gr.alle_verbindingen.size() > 0){
		Verbinding<int> v = gr.alle_verbindingen.top();
		if (uf.find(v.van) != uf.find(v.naar)){
			uf.uni(v.van, v.naar);	
			MOB.push_back(v);
		}
		gr.alle_verbindingen.pop();	
	}
	for (Verbinding<int> v : MOB){
		cout << v << endl;
	}
	return 0;
}