#include <iostream>
#include "bellmanford.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    GraafMetTakdata <GERICHT,int>	 gr(5);
    gr.voegVerbindingToe(0,1,-1);
    gr.voegVerbindingToe(0,2,4);
    gr.voegVerbindingToe(1,2,3);
    gr.voegVerbindingToe(1,3,2);
    gr.voegVerbindingToe(1,4,2);
    gr.voegVerbindingToe(3,2,5);
    gr.voegVerbindingToe(3,1,1);
    gr.voegVerbindingToe(4,3,-3);
    BellmanFord b(gr);
    b.bepaalKorstePad(0);
    cout << b;
    return 0;
}

