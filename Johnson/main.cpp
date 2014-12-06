#include <iostream>
#include "johnson.h"
#include "Dijkstra.h"
using namespace std;

int main()
{
    /*GraafMetTakdata <ONGERICHT,int>	 d(7);
    d.voegVerbindingToe(0,1,4);
    d.voegVerbindingToe(0,2,3);
    d.voegVerbindingToe(0,4,7);
    d.voegVerbindingToe(2,1,6);
    d.voegVerbindingToe(2,4,8);
    d.voegVerbindingToe(2,3,11);
    d.voegVerbindingToe(3,1,5);
    d.voegVerbindingToe(3,4,2);
    d.voegVerbindingToe(3,5,2);
    d.voegVerbindingToe(3,6,10);
    d.voegVerbindingToe(6,4,5);
    d.voegVerbindingToe(6,5,3);
    Dijkstra ds(d);
    ds.berekenKorstePad(0)*/;
    GraafMetTakdata <GERICHT,int>	 gr(6);
    gr.voegVerbindingToe(0,1,-2);
    gr.voegVerbindingToe(1,2,-1);
    gr.voegVerbindingToe(2,0,4);
    gr.voegVerbindingToe(2,3,-3);
    gr.voegVerbindingToe(2,4,2);
    gr.voegVerbindingToe(5,3,-4);
    gr.voegVerbindingToe(5,4,1);
    Johnson j(gr);
    return 0;
}

