#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <climits>
#include "graaf.h"
#include <queue>

using namespace std;

struct KnoopMetGewicht{

    int gewicht;
    int knoopNr;

    KnoopMetGewicht(int gew, int k):gewicht(gew),knoopNr(k){}
    friend bool operator<(const KnoopMetGewicht & a,const KnoopMetGewicht & b){
        return a.gewicht > b.gewicht;
    }
};

class Dijkstra{
public:
    Dijkstra(GraafMetTakdata<GERICHT,int>& _gr):gr(_gr){
        visited = vector<int>(gr.aantalKnopen(),0);
        for (int i = 0; i < gr.aantalKnopen(); i++){
            knopenMetGewicht.push_back(KnoopMetGewicht(INT_MAX, i));
        }
    }
    vector<KnoopMetGewicht> berekenKorstePad(int naar);
    void berekenKorstePad(priority_queue<KnoopMetGewicht>& teBehandelKnopen);

private:
    friend ostream& operator<<(ostream& os, const Dijkstra& w);
    GraafMetTakdata<GERICHT,int> gr;
    vector<KnoopMetGewicht> knopenMetGewicht;
    vector<int> visited;
};

vector<KnoopMetGewicht> Dijkstra::berekenKorstePad(int naar){
    priority_queue<KnoopMetGewicht> teBehandelKnopen;
    teBehandelKnopen.push(knopenMetGewicht[naar]);
    knopenMetGewicht[naar].gewicht = 0;
    berekenKorstePad(teBehandelKnopen);
    return knopenMetGewicht;
}

void Dijkstra::berekenKorstePad(priority_queue<KnoopMetGewicht>& teBehandelKnopen){
    int huidigeKnoop = teBehandelKnopen.top().knoopNr;
    teBehandelKnopen.pop();
    visited[huidigeKnoop] = 1;
    map<int,int>::iterator it = gr[huidigeKnoop].begin();
    while (it != gr[huidigeKnoop].end()){
        if (visited[it->first] != 1){
            int nieuwGewicht = knopenMetGewicht[huidigeKnoop].gewicht + *gr.geefTakdata(huidigeKnoop, it->first);
            if (nieuwGewicht < knopenMetGewicht[it->first].gewicht){
                knopenMetGewicht[it->first].gewicht = nieuwGewicht;
                teBehandelKnopen.push(knopenMetGewicht[it->first]);
            }
        }
        it++;
    }
    if (teBehandelKnopen.size() != 0)
        berekenKorstePad(teBehandelKnopen);
}

ostream& operator<<(ostream& os, const Dijkstra& b){
    for (KnoopMetGewicht w : b.knopenMetGewicht){
        if( w.gewicht == INT_MAX )
            os << "Naar Knoop " << w.knoopNr << "  gewicht: geen pad"  << endl;
        else
            os << "Naar Knoop " << w.knoopNr << "  gewicht:" << w.gewicht << endl;

    }
    return os;
}


#endif // DIJKSTRA_H
