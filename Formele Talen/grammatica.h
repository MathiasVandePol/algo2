#ifndef __GRAMMATICA_H
#define __GRAMMATICA_H
#include "symbool.h"
#include "regexp.h"
#include <iostream>

using std::endl;



class Grammatica
{
	public:
		Grammatica(const Regexp& regex);
		Grammatica(const Regexp &regexp, Symbool &symbool);
		string geefLetter() { return this->letter; }
		Symbool geefNiet_terminaal() { return this->niet_terminaal; }
		Regexp::opcode geefOpcode() { return this->code; }
		void schrijf(ostream & os) const;
		void schrijfHTML(ostream & os) const;
	private:
		Symbool niet_terminaal;
		string letter;
		Grammatica *gr1,*gr2;
		void init(const Regexp &regexp, Symbool &symbool);
		Regexp::opcode code;
		void schrijfHTML_rec(ostream & os) const;
};

Grammatica::Grammatica(const Regexp &regexp){
	Symbool s = Symbool();
	init(regexp, s);
}

Grammatica::Grammatica(const Regexp &regexp, Symbool &symbool ){
	init(regexp, symbool);
}

void Grammatica::init(const Regexp &regexp, Symbool &symbool) {
	niet_terminaal = symbool;
	code = regexp.geefOpcode();
	++symbool;

	if(regexp.geefOpcode() == Regexp::letter) {
		letter = regexp.geefLetter();
	} else {
		gr1 = new Grammatica(*(regexp.geefEersteOperand()), symbool);

		if(!regexp.geefOpcode() == Regexp::ster) {
			gr2 = new Grammatica(*(regexp.geefTweedeOperand()), symbool);
		}
	}
}


void Grammatica::schrijfHTML(ostream& os) const {
	os << "<!DOCTYPE html>" << endl;
	os << "<html><head></head><body>" << endl;
	os << "<table><tbody>" << endl;
	this->schrijfHTML_rec(os);
	os << "</tbody></table>" << endl;
	os << "</body></html>" << endl;
}

void Grammatica::schrijfHTML_rec(ostream& os) const {
	os << "	<tr>" << endl;
	os << "		<td>&lt;<strong>" + this->niet_terminaal + "</strong>&gt;</td>" << endl;
	os << "		<td>&nbsp;::=&nbsp;</td>" << endl;
	if(this->code == Regexp::letter) {
		os << "		<td>" + letter;
	} else {
		os << "		<td>&lt;<strong>" + gr1->niet_terminaal +"</strong>&gt;";

		if(!this->code == Regexp::ster) {
			os <<  "&lt;<strong>Y</strong>&gt;";
		}

	}
	os << "</td>" << endl;
	os << "	</tr>" << endl;
	if(this->code != Regexp::letter) {
		this->gr1->schrijfHTML_rec(os);

		if(!this->code == Regexp::ster) {
			this->gr2->schrijfHTML_rec(os);
		}
	}
}

#endif