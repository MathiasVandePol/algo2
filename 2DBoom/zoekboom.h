#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H
#include <cstdlib>
#include <string>
#include "punt2.h"
#include <iostream>
   using std::cout;
   using std::endl;
#include <queue>
    using std::ostream;
#include <utility>
    using std::pair;
    using std::make_pair;
    using std::string;
#include <queue>
#include <cassert>

/**********************************************************************

   Klasse: Binboom met Binknoop: binaire boom
   
   beschrijving: Domme klasse om de gegevens van een boom te bevatten
                 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
                 alles publiek staan. Ze mag dan ook nooit buiten een
                 wrapper gebruikt worden!
   
***************************************************************************/

class Binknoop;

class Binboom{
    public:
    	Binknoop* k;

        Binboom():k(0){}
        ~Binboom();

        void schrijf(ostream&);
        void schrijf(ostream& os ,Binknoop* kn);
		punt2* buur(const punt2&, punt2*, int*);
		bool zoek(const punt2&);
    	void voegtoe(const punt2& punt,const string& data, Binknoop*); 
};

class Binknoop{
    public:
        punt2 sl;
        string data;
        bool sorteer_x;
        Binboom links,rechts;
        Binknoop(const punt2& _sl,const string& _data):sl(_sl),data(_data){}
        Binknoop* ouderknoop;
};

/**********************************************************************

   klasse: Zoekboom
   
   beschrijving: Dit is een wrapper voor een Binboom,
                 die ervoor zorgt dat de sleutels in de Binboom
                 op volgorde staan
   
***************************************************************************/

class Zoekboom{
    public:
        void voegtoe(const punt2&,const string&);
        bool zoek(const punt2&);
		punt2* buur(const punt2&, int* aantal);
        friend ostream& operator<<(ostream& os,Zoekboom& b){
            b.deBinboom.schrijf(os);
            return os;
        };

    protected:
        //De binaire boom die de data bevat
        Binboom deBinboom;
};


void Binboom::schrijf(ostream& os){
    if (k!=0){
       std::queue<Binknoop*, std::deque<Binknoop*> > q;
       q.push(k);
       while(!q.empty()){
           Binknoop* nu=q.front();
           schrijf(os,nu);
           os<<" links: ";
           schrijf(os,nu->links.k);
           os<<" rechts: ";
           schrijf(os,nu->rechts.k);
           os<<" sorteer_x: " << nu->sorteer_x;
           os<<endl;
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

void Binboom::schrijf(ostream& os ,Binknoop* kn){
    if (kn!=0)
        os <<"("<<kn->sl<<","<<kn->data<<")";
    else
        os<<"---";
}

Binboom::~Binboom(){
            delete k;
}



void Zoekboom::voegtoe(const punt2& punt,const string& data) {
	this->deBinboom.voegtoe(punt, data, 0);
}

void Binboom::voegtoe(const punt2& punt,const string& data, Binknoop* ouderk) {
	if(this->k == 0) {
		this->k = new Binknoop(punt, data);
		if(ouderk != 0) {
			this->k->sorteer_x = !ouderk->sorteer_x;
		} else {
			this->k->sorteer_x = true;
		}
		this->k->ouderknoop = ouderk;
		return;
	}

	// vergelijk sleutel
	bool steek_hem_links;
	if(this->k->sorteer_x) {
		if(punt.x < this->k->sl.x) {
			steek_hem_links = true;
		} else {
			steek_hem_links = false;
		}
	} else {
		if(punt.y < this->k->sl.y) {
			steek_hem_links = true;
		} else {
			steek_hem_links = false;
		}
	}

	//steek hem op de juiste plaats
	if(steek_hem_links) {
		this->k->links.voegtoe(punt,data, this->k);
	} else {
		this->k->rechts.voegtoe(punt,data, this->k);
	}
}


bool Zoekboom::zoek(const punt2& punt) {
	return this->deBinboom.zoek(punt);
}


bool Binboom::zoek(const punt2& punt){
	if (this->k == 0) {
		return false;
	}
	if (this->k->sl.x == punt.x && this->k->sl.y == punt.y){
		return true;
	}
	bool zoek_links;
	if (this->k->sorteer_x) {
		if (punt.x < this->k->sl.x) {
			zoek_links = true;
		}
		else {
			zoek_links = false;
		}
	}
	else {
		if (punt.y < this->k->sl.y) {
			zoek_links = true;
		}
		else {
			zoek_links = false;
		}
	}

	//steek hem op de juiste plaats
	if (zoek_links) {
		return this->k->links.zoek(punt);
	}
	else {
		return this->k->rechts.zoek(punt);
	}
}

punt2* Zoekboom::buur(const punt2& punt, int* aantal){
	return this->deBinboom.buur(punt, 0, aantal);
}

punt2* Binboom::buur(const punt2& van, punt2* dichtste, int* aantalKnopen){
	if ((dichtste == 0 || this->k->sl.kwadafstand(van) < dichtste->kwadafstand(van)) && this->k->sl.kwadafstand(van) != 0){
		dichtste = &this->k->sl;
	}
	(*aantalKnopen)++;
	if (this->k->sorteer_x){
		if (van.x < this->k->sl.x && this->k->links.k != 0){
			return this->k->links.buur(van, dichtste, aantalKnopen);
		}
		else if (this->k->rechts.k != 0){
			return this->k->rechts.buur(van, dichtste, aantalKnopen);
		}
	}
	else{
		if (van.y < this->k->sl.y && this->k->links.k != 0){
			return this->k->links.buur(van, dichtste, aantalKnopen);
		}
		else if (this->k->rechts.k != 0){
			return this->k->rechts.buur(van, dichtste, aantalKnopen);
		}
	}
	return dichtste;
}


#endif
