#ifndef _NA_H
#define _NA_H
#include "regexp.h"
#include "thompsonna.h"
#include <vector>
#include <set>
#include <map>
using std::vector;
using std::map;
using std::endl;

class Na {
	public:
		Na(const ThompsonNA& tna) {	

			buren.resize(tna.geefAantalVerbindingen());	
			staten.resize(tna.geefAantalVerbindingen(), false);	
			for(int v_nr = 0; v_nr < tna.geefAantalVerbindingen(); v_nr++) {
				Verbinding v = tna[v_nr];
				buren[v.geefBron()][(uchar)v.geefKarakter()].push_back(v.geefDoel());
			}
			zetBeginStaten();
		}

		friend ostream& operator<<(ostream& os, const Na& na);
		bool verwerkKarakter(const uchar c);





	private:
		vector<map<uchar, vector<int> > > buren;
		vector<bool> staten;
		void zet_toestand_status(int knoopNr, bool status);
		void zetBeginStaten();


};


ostream& operator<<(ostream& os, const Na& na) {
	int i = 0;
    for (map<uchar, vector<int>  > knopen : na.buren){
    	map<uchar, vector<int>  >::iterator it = knopen.begin();
    	os << endl<< "KNOOP:" << i << "  STATUS: " << na.staten[i] << endl;
    	while (it != knopen.end()){
    		os << it->first << ": ";
    		for (int naarKnoop : it->second){
    			os << naarKnoop << ", ";
    		}
    		os << endl;
    		it++;
    	}
    	i++;
    }
    return os;
}

void Na::zet_toestand_status(int knoopNr, bool status) {
	staten[knoopNr] = status;
	for (int b : buren[knoopNr][epsilon]){
		zet_toestand_status(b, true);
	}
}

bool Na::verwerkKarakter(const uchar c){	//geeft true terug indien aan eindknoop
	vector<bool> _oude_staten = staten;
	zetBeginStaten();
	for (int i = 0; i < _oude_staten.size(); i++){
		if (_oude_staten[i]){
			for (int buur : buren[i][c]){
				zet_toestand_status(buur, true);
			}
		}
	}	
	if (staten[staten.size() - 1]){
		zetBeginStaten();
		return true;
	}
	return false;
}

void Na::zetBeginStaten(){
	staten = vector<bool>(staten.size(), false);
	zet_toestand_status(0, true);
}



#endif
