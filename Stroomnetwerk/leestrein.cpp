#include "tinyxml.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <map>
#include "stroomnet.h"
using std::map;
using std::string;
using std::cout;
using std::endl;


//volgende zou eigenlijk een lidfunctie van de klasse TiXmlElement moeten zijn,
//er zou opportuniteitsovererving kunnen worden toegepast.
//hier losse functie gebruikt om gebruik van tinyxml beter te illustreren.
void schrijfAttributen(map <string, int> &knoopPuntIndexen, TiXmlElement* el, int& index){
    TiXmlAttribute* attr=el->FirstAttribute();
    while (attr!=0){
        cout<<attr->Name()<<" "<<attr->Value()<<"  ";
        attr=attr->Next();
		if (attr->Name()== "nummer"){
			knoopPuntIndexen[attr->Value()] = index++;
		}
    }
    cout<<endl;
}

void schrijfVerbindingen(int knoopNr, vector<string>& knoopNamen, GraafMetTakdata<GERICHT, double>& gr){
	for (map<int, int>::iterator it = gr.knopen[knoopNr].begin(); it != gr.knopen[knoopNr].end(); it++){			//print alle verbindingen van 1 knoop
		cout << "Van: " << knoopNamen[knoopNr] << "   Naar:" << knoopNamen[it->first] << endl;
	}
}

void ontdubbelKnoop(int knoopNr, GraafMetTakdata<GERICHT, double>& gr){
	map<int, int> knoop = gr.knopen[knoopNr];
	gr.voegKnoopToe();
	int nieuweKnoopNr = gr.aantalKnopen() - 1;
	gr.voegVerbindingToe(knoopNr, nieuweKnoopNr,1);
	for (map<int, int>::iterator it = knoop.begin(); it != knoop.end(); it++){			//print alle verbindingen van 1 knoop
		gr.voegVerbindingToe(nieuweKnoopNr, it->first, 1);
		gr.verwijderVerbinding(knoopNr, it->first);
	}

}

int main()
{
        TiXmlDocument doc( "treingraaf.xml" );
        bool loadOkay = doc.LoadFile();
        assert(loadOkay);
        TiXmlNode* netwerk;
        netwerk = doc.RootElement();
        assert( netwerk );
		map <string, int> knoopPuntIndexen;
		vector<string> knoopNamen;
        cout<<netwerk->Value()<<"\n";
		GraafMetTakdata <GERICHT, double> gr;
//Alternatief:
//        for (TiXmlElement* knooppunt=netwerk->FirstChildElement();
//                   knooppunt!=0;knooppunt=knooppunt->NextSiblingElement()){
		int i = 0;
        for (TiXmlNode* knooppunt=netwerk->FirstChild(); knooppunt!=0;knooppunt=knooppunt->NextSibling()){
			TiXmlAttribute* nummer = (dynamic_cast<TiXmlElement*>(knooppunt))->FirstAttribute();
			if (knoopPuntIndexen.find(nummer->Value()) == knoopPuntIndexen.end()){
				knoopPuntIndexen[nummer->Value()] = i++;
				knoopNamen.push_back(nummer->Value());
				gr.voegKnoopToe();
			}
			for (TiXmlNode* route = knooppunt->FirstChild(); route != 0; route = route->NextSibling()){
              //  cout<<route->Value()<<"\n";
				TiXmlAttribute* doel = (dynamic_cast<TiXmlElement*>(route))->FirstAttribute();
				if (knoopPuntIndexen.find(doel->Value()) == knoopPuntIndexen.end()){
					knoopPuntIndexen[doel->Value()] = i++;
					knoopNamen.push_back(doel->Value());
					gr.voegKnoopToe();
				}
				TiXmlAttribute* afstand = doel->Next();
			//	cout << "Van: " << knoopPuntIndexen[nummer->Value()] << " Naar:" << knoopPuntIndexen[doel->Value()] << endl;
				gr.voegVerbindingToe(knoopPuntIndexen[nummer->Value()], knoopPuntIndexen[doel->Value()],1);
				gr.voegVerbindingToe(knoopPuntIndexen[doel->Value()], knoopPuntIndexen[nummer->Value()], 1);
            }
        }
		
		cout << knoopPuntIndexen["Ffarquhar"] << endl; //geeft 80
		cout << knoopPuntIndexen["Tidmouth"] << endl; // geeft 58
		int start = 80;
		int eind = 58;
		//schrijfVerbindingen(80, knoopNamen, gr);
		int aantalKnopenOrigineel = gr.aantalKnopen();
		for (int i = 0; i < aantalKnopenOrigineel; i++){
			if (i != start && i!=eind)
				ontdubbelKnoop(i, gr);
		}
		Stroomnetwerk<double> sn(gr,80, 58);

		int capaciteit = sn.geefCapaciteit();
		cout << "Aantal knopen te verwijderen: " << capaciteit << endl;
        return 0;
}

