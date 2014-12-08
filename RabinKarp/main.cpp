#include <iostream>
#include <string>

using namespace std;


// d is the number of characters in input alphabet
#define d 256

/*  pat  -> pattern
    txt  -> text
    q    -> A prime number
*/

void search(string& pat, string& txt, int q)
{
    int M =  pat.length();
    int N = txt.length();
    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    // hash value patroon en eerste window
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }

    cout << "Hashwaarde van patroon is: "<< p << endl;
    cout << "Hashwaarde van eerste window van txt is: "<< t << endl;


    //verschuif windows steeks meer naar rechts
    for (i = 0; i <= N - M; i++)
    {

        // Vergelijk patroon en huidig window
        if ( p == t )
        {
            //Indien de hashes overeenkomen vergelijken we nog de actuele chars om zeker te zijn dat we overenkomen
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M)
            {
                cout << "Patroon gevonden op index " << i << endl;
            }
        }

        //De hashwaarde voor de volgende window berekenen
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            // Absolute waarde van t gebruiken
            if(t < 0)
              t = (t + q);
            cout << "Hashwaarde van volgend window van txt is: "<< t << endl;
        }
    }
}


int main()
{
    string txt = "Wij houden niet van pizza maar ik hou wel van pizzagangen";
    string pat = "pizza";
    int q = 101;  //priemgetal
    search(pat, txt, q);
    return 0;
}
