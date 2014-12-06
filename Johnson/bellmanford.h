#ifndef BELLMANFORD_H
#define BELLMANFORD_H
#include "graaf.h"
#include <queue>
#include <vector>
#include <climits>
#include <ostream>
using namespace std;

struct WegOnderdeel{
    int knoopNr;
    int via;
    int afstand ;

    WegOnderdeel(int _knoopNr, int _via = -1, int _afstand=INT_MAX):knoopNr(_knoopNr), via(_via), afstand(_afstand){

    }

};

class BellmanFord{


public:
    BellmanFord(GraafMetTakdata<GERICHT,int> _gr):gr(_gr){
        for (int i = 0; i < gr.aantalKnopen() ;i++){
           WegOnderdeel w(i);
           wegOnderdelen.push_back(w);
        }
    }
    void bepaalKorstePad(int naar);
    void bepaalKorstePad(queue<WegOnderdeel*>& q, int gewicht, int via);
    vector<WegOnderdeel> wegOnderdelen;
    GraafMetTakdata<GERICHT,int> gr;

private:
    friend ostream& operator<<(ostream& os, const BellmanFord& w);
};

void BellmanFord::bepaalKorstePad(int van = 0){
    queue<WegOnderdeel*> q;
    q.push(&wegOnderdelen[van]);
    bepaalKorstePad(q, 0, van);
}

void BellmanFord::bepaalKorstePad(queue<WegOnderdeel*>& q, int gewicht, int via){
    WegOnderdeel* w  = q.front();
    q.pop();
    if (w->afstand > gewicht){
        w->afstand = gewicht;
        w->via = via;
        map<int, int>::iterator it = gr[w->knoopNr].begin();
        while (it != gr[w->knoopNr].end()){
            q.push(&wegOnderdelen[it->first]);
            bepaalKorstePad(q, *gr.geefTakdata(w->knoopNr, it->first) + w->afstand, w->knoopNr);
            it++;
        }
    }
}

ostream& operator<<(ostream& os, const BellmanFord& b){
    for (WegOnderdeel w : b.wegOnderdelen){
        os << "Knoop " << w.knoopNr << "  via knoop:" << w.via << "  totale afstand:" << w.afstand << endl;
    }
    return os;
}


#endif // BELLMANFORD_H
