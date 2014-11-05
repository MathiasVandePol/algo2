#include <cstdlib>
#include <iostream>
#include <algorithm>
using std::ostream;
using std::max;
#include <queue>
#include <string>

using namespace std;

template <class T,class D>
class Rzwboom;

template <class T,class D>
class Rzwknoop;


template <class T,class D>
class Rzwboom{
friend class Rzwknoop<T,D>;
const static int rood,zwart;
public:
    Rzwboom<T,D>(){
        k=0;
    }
    ~Rzwboom<T,D>(){
        delete k;
    }
//gegevensveld
    Rzwknoop<T,D>* k;
	int minZD;
	int maxZD;
	bool isRoodbaar;
	//Toe te voegen code in Rzwboom header
	string csv();
	void csv(stringstream & ss);


	//controleert of een boom al dan niet kleurbaar is
	bool isKleurbaar();
	//kleurt de boom in
	void kleur();

//bottom-up toevoegen, geen duplicaten toegestaan.
//geeft false als de sleutel al in de boom zat.
//geldigeKleur=false: knoop wordt toegevoegd zonder op kleur te letten.
    bool voegtoe(const T&,const D&,bool geldigeKleur=true );
//volgende functie geeft false als de sleutel niet kan verwijderd
//worden omdat hij niet in de boom zit.
    bool verwijder(const T&);
    D* zoekdata(const T&);
    int diepte();
// << schrijft uit in level order.
    friend ostream& operator<<(ostream& os,Rzwboom<T,D>& b){
        b.schrijf(os);
        return os;
    }
//-1 is ongeldige boom; zwartediepte kan dus ook gebruikt worden
//om boom te controleren.
    int zwartediepte();
//geeft de voorganger als de linkerboom niet leeg is
    Rzwboom<T,D>* ondervoorganger(Rzwknoop<T,D>*);
    bool ouderOK();
//private:
    void schrijf(ostream&);
    int geefkleur(){
        if (k!=0)
           return k->rzw;
        else
            return zwart;
    }
//Dit hoort op het eerste gezicht bij de klasse Rzwknoop.
//Maar dit kan niet omdat kn een nulpointer mag zijn
    void schrijf(ostream& os ,Rzwknoop<T,D>* kn);
//alleen roteer oproepen als de operatie kan!
    void roteer(bool naarlinks);
//maakzwart maakt de knoop in plaats->k zwart, en laat plaats wijzen naar
//volgende boom die een probleem kan opleveren bij bottom-up toevoegen.
    void maakzwart(Rzwboom<T,D>*& plaats);
//zoekknoop: postconditie: plaats wijst naar knoop met gezochte sleutel,
//                           of naar lege boom die naar die knoop zou wijzen als hij bestond
//                         ouder heeft waarde die in het ouderveld van de knoop staat/zou moeten staan
    void zoekknoop(const T&,Rzwboom<T,D>*& plaats,Rzwboom<T,D>*& ouder);

};
template <class T,class D>
const int Rzwboom<T,D>::rood=0;
template <class T,class D>
const int Rzwboom<T,D>::zwart=1;

template <class T,class D>
class Rzwknoop{
    friend class Rzwboom<T,D>;
    public:
        T sl;
        D data;
        int rzw;
        Rzwboom<T,D>* ouder;//wijst naar de boom die naar de ouderknoop wijst
        Rzwboom<T,D> links,rechts;
        Rzwknoop<T,D>(const T& _sl,const D& _data):
                ouder(0),sl(_sl),data(_data),rzw(Rzwboom<T,D>::rood){}
};

template <class T,class D>
void Rzwboom<T,D>::roteer(bool naarlinks){
    Rzwknoop<T,D>* op;
    Rzwknoop<T,D>* neer=k;
    if (naarlinks){
        op=k->rechts.k;
        if (neer->links.k!=0)
            neer->links.k->ouder=&(op->links);
        neer->rechts.k=op->links.k;
        if (op->links.k!=0){
            Rzwknoop<T,D>* kind=op->links.k;
            kind->ouder=&(op->links);
            if (kind->links.k!=0)
                kind->links.k->ouder=&(neer->rechts);
            if (kind->rechts.k!=0)
                kind->rechts.k->ouder=&(neer->rechts);
        }
        if (op->rechts.k!=0)
            op->rechts.k->ouder=this;
        op->links.k=neer;
    }
    else{
        op=k->links.k;
        if (neer->rechts.k!=0)
            neer->rechts.k->ouder=&(op->rechts);
        neer->links.k=op->rechts.k;
        if (op->links.k!=0)
            op->links.k->ouder=this;
        if (op->rechts.k!=0)
            op->rechts.k->ouder=&(op->rechts);
        if (op->rechts.k!=0){
            Rzwknoop<T,D>* kind=op->rechts.k;
            kind->ouder=&(op->rechts);
            if (kind->links.k!=0)
                kind->links.k->ouder=&(neer->links);
            if (kind->rechts.k!=0)
                kind->rechts.k->ouder=&(neer->links);
        }
        op->rechts.k=neer;
    }
    k=op;
    op->ouder=neer->ouder;
    neer->ouder=this;
}

//Implementatie in Rzwboom
template <class T, class D>
string Rzwboom<T, D>::csv()
{
	stringstream ss;
	csv(ss);
	return ss.str();
}

template <class T, class D>
void Rzwboom<T, D>::csv(stringstream & ss)
{
	if (k == 0) return;
	ss << k->sl << ";";
	if (k->links.k != 0) ss << k->links.k->sl;
	ss << ";";
	if (k->rechts.k != 0) ss << k->rechts.k->sl;
	ss << ";";
	ss << k->rzw << ";";
	k->links.csv(ss);
	k->rechts.csv(ss);
}


template <class T,class D>
void Rzwboom<T,D>::zoekknoop(const T& sl,Rzwboom<T,D>*& plaats,
                                         Rzwboom<T,D>*& ouder){
    plaats=this;
    ouder=0;
    while (plaats->k!=0 && plaats->k->sl!=sl){
        ouder=plaats;
        if (sl<plaats->k->sl)
            plaats=&(plaats->k->links);
        else
            plaats=&(plaats->k->rechts);
    }
}
        
template <class T,class D>
D* Rzwboom<T,D>::zoekdata(const T& sl){
    Rzwboom<T,D>* plaats;
    Rzwboom<T,D>* ouder;//dummy, eigenlijk overbodig bij zoekdata
    zoekknoop(sl,plaats,ouder);
    if (plaats->k==0)
        return 0;
    else return &(plaats->k->data);
}

template <class T,class D>
void Rzwboom<T,D>::maakzwart(Rzwboom<T,D>*& plaats){
    Rzwboom<T,D>* kind=plaats;
    Rzwboom<T,D>* ouder=kind->k->ouder;
    Rzwboom<T,D>* grootouder=ouder->k->ouder;
    if (grootouder->k->links.geefkleur()==rood && grootouder->k->rechts.geefkleur()==rood){
        grootouder->k->rzw=rood;
        grootouder->k->links.k->rzw=zwart;
        grootouder->k->rechts.k->rzw=zwart;
    }
    else {//geval 1
        bool ouderlinks=(ouder==&(grootouder->k->links));
        bool kindlinks=(kind==&(ouder->k->links));
        if (kindlinks!=ouderlinks){//geval 1b
            if (ouderlinks)
                grootouder->k->links.roteer(true);
            else
                grootouder->k->rechts.roteer(false);
        };
        //geval 1a
        grootouder->k->rzw=rood;
        ouder->k->rzw=zwart;
        grootouder->roteer(!ouderlinks);
    }
    plaats=grootouder;
}

//bottom up
template <class T,class D>
bool Rzwboom<T,D>::voegtoe(const T& sl,const D& data, bool geldigeKleur){
    Rzwboom<T,D>* plaats;
    Rzwboom<T,D>* ouder;
    zoekknoop(sl,plaats,ouder);
    bool nietgevonden=plaats->k==0;
    if (nietgevonden){
        plaats->k=new Rzwknoop<T,D>(sl,data);
        plaats->k->ouder=ouder;
//noot: ouder wijst nooit naar een ledige boom.
        if (geldigeKleur){
            bool dubbelrood=(ouder!=0 && ouder->k->rzw==rood);
            while (dubbelrood){
                if (sl==18){
                    std::cout<<"plaats->k->sl== "<<plaats->k->sl;
                    std::cout<<"ouder->k->sl== "<<ouder->k->sl;
                    std::cout<<'\n';
                }
                maakzwart(plaats);
                //assert(plaats->k!=0);
                ouder=plaats->k->ouder;
                dubbelrood=(plaats->k->rzw==rood && ouder !=0
                                              && ouder->k->rzw==rood);
            }
            k->rzw=zwart;//eventueel wortel zwart maken.
        }
    }
    return nietgevonden;
}


template <class T,class D>
void Rzwboom<T,D>::schrijf(ostream& os){
    if (k!=0){
       std::queue<Rzwknoop<T,D>*, std::deque<Rzwknoop<T,D>*> > q;
       q.push(k);
       while(!q.empty()){
           Rzwknoop<T,D>* nu=q.front();
           schrijf(os,nu);
           os<<" links: ";
           schrijf(os,nu->links.k);
           os<<" rechts: ";
           schrijf(os,nu->rechts.k);
           os<<" ouder: ";
           if (nu->ouder==0)
               schrijf(os,0);
           else
               schrijf(os,nu->ouder->k);
           os<<std::endl;
           if (nu->links.k!=0)
               q.push(nu->links.k);
           if (nu->rechts.k!=0)
               q.push(nu->rechts.k);
           q.pop();
       }
    }
    else{
        schrijf(os,k);
    }
}

template <class T,class D>
void Rzwboom<T,D>::schrijf(ostream& os ,Rzwknoop<T,D>* kn){
    if (kn!=0)
        os<<
        (kn->rzw==rood?
            "rood ":"zwart")
        <<"("<<kn->sl<<","<<kn->data<<")";
    else
        os<<"---";
}


