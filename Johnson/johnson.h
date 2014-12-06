#ifndef JOHNSON_H
#define JOHNSON_H

#include "bellmanford.h"
#include <queue>
#include <vector>
#include <climits>
#include <ostream>
#include "Dijkstra.h"
using namespace std;



class Johnson{


public:
    Johnson(GraafMetTakdata<GERICHT,int>& gr){
       GraafMetTakdata<GERICHT,int> unattended = gr;    //kopieer originele graaf
       gr.voegKnoopToe();   //knoop s
       for (int i = 0; i < gr.aantalKnopen() - 1 ;i++){ //verbinding van knoop s naar alle knopen met gewicht 0
           gr.voegVerbindingToe(gr.aantalKnopen() - 1, i,0);
       }

       BellmanFord metS(gr);
       metS.bepaalKorstePad(gr.aantalKnopen() - 1);
       pasWaardenAan(metS, unattended);

       for (int i = 0; i < unattended.aantalKnopen(); i++){
           Dijkstra originele(unattended);
           cout << "Korste paden vanuit " << i << endl;
           originele.berekenKorstePad(i);
           cout << originele;
       }
    }
private:
    void pasWaardenAan(BellmanFord& metS, GraafMetTakdata<GERICHT,int>& origineel);
    friend ostream& operator<<(ostream& os, const BellmanFord& w);
};

void Johnson::pasWaardenAan(BellmanFord& metS, GraafMetTakdata<GERICHT,int>& origineel){
    for (unsigned int knoopNr = 0; knoopNr < metS.wegOnderdelen.size() - 1; knoopNr++){
        map<int,int>::iterator it = origineel[knoopNr].begin();
        while (it != origineel[knoopNr].end()){
            int* takdata = origineel.geefTakdata(knoopNr, it->first);
            int nieuweData = *takdata + metS.wegOnderdelen[knoopNr].afstand - metS.wegOnderdelen[it->first].afstand;
            *takdata = nieuweData;
            it++;
        }
    }
}


#endif // JOHNSON_H
