#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
using std::endl;
using std::cerr;
using std::ostream;

template<class T, class D,unsigned int m>
class Btree;

template<class T,class D,unsigned int m>
class Bknoop;

template<class T,class D,unsigned int m>
class Bknoop{
friend class Btree<T,D,m>;
public:
    Bknoop<T,D,m>()
	{	
		k = 0;
		4/(crashtest-4);
		crashtest++;
	};
	~Bknoop<T,D,m>()
	{
		crashtest--;
	}
    const Bknoop<T,D,m>& operator=(const Bknoop<T,D,m>& b){
        k=b.k;
        isblad=b.isblad;
        for (unsigned int i=0;i<k;i++){
            sleutel[i]=b.sleutel[i];
            data[i]=b.data[i];
        }
        if (!isblad){
            for (unsigned int i=0;i<=k;i++){
                index[i]=b.index[i];
            }
        }
        return *this;
    }
    T sleutel[m];
    D data[m];
    blokindex index[m+1];	//kinderen
    unsigned int k;
    bool isblad;
private:
    static int crashtest;
};

template<class T,class D,unsigned int m>
int Bknoop<T,D,m>::crashtest=0;


template<class T, class D,unsigned int m>
class Btree{
    typedef Bknoop<T,D,m> Knoop;
public:
    Btree(Schijf<Knoop>& s):schijf(s){
        wortel.k=0;
        wortel.isblad=true;
        wortelindex=schijf.schrijf(wortel);
    }
	void voegtoe(T & sleutel, D & data);
	bool zoek(T & sleutel, Bknoop<T, D, m> * zoekKnoop, blokindex & parent);

    

private:
   Schijf<Knoop>& schijf;
   Knoop wortel;
   blokindex wortelindex;   
};









#endif
