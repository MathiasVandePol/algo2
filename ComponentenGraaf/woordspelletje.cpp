#include "graaf.h"
#include <string>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class woordspelletje {
protected:
	typedef std::map<int, int>  Knoop;      // beeldt knoopnummer (van buur) af op verbindingsnummer
	Graaf<GERICHT> graaf;
	Graaf<GERICHT> omgekeerdeGraaf;
	Graaf<GERICHT> componentenGraaf;
	map<string, int> woordenMap;			//Woorden
	vector<string> alleWoorden;
	vector<string> alleVerbindingen;
	vector<int>	componentnummer;
	std::stack<int> s;

public:

	woordspelletje(string woorden, string takken){
		leesWoordenIn(woorden);
		leesVerbindingenIn(takken);
		overloopPostorder();
		int aantalC = componentnummerZoeker();
		ofstream out("output.txt");
		printAllComponenten(out, aantalC);

		vector<int> lus;

		vector<int> geldigeWoorden;
		bepaalGeldigeWoorden(geldigeWoorden);

		for (int i = 0; i < geldigeWoorden.size(); i++)
		{
			lus.clear();
			zoekLus(geldigeWoorden[i], lus);
			printLus(lus);
		}
	}
	~woordspelletje(){
	}



	void bepaalGeldigeWoorden(vector<int> & geldigeWoorden)
	{
		map<int, int> componentGroottes;
		stack<int> geldigeComponenten;
		for (int i = 0; i < componentnummer.size(); i++)
		{
			componentGroottes[componentnummer[i]]++;
		}
		for (map<int, int>::iterator it = componentGroottes.begin(); it != componentGroottes.end(); it++)
		{
			if (1 < it->second) geldigeComponenten.push(it->first);
		}
		while (0 < geldigeComponenten.size())
		{
			for (int i = 0; i < componentnummer.size(); i++)
			{
				if (componentnummer[i] == geldigeComponenten.top())
				{
					geldigeWoorden.push_back(i);
				}
			}
			geldigeComponenten.pop();
		}
	}



	void printLus(vector<string> & woorden,  vector<int> & lus)
	{
		if (lus.size() == 0)
		{
			cout << "!!!!!!!!!!!!!!!!!!!" << endl;
			return;
		}
		int van, naar, via;
		cout << "--- " << woorden[lus[0]] << " ---" << endl;
		for (int i = 0; i < lus.size(); i++)
		{
			van = lus[i];
			naar = lus[(i + 1) % lus.size()];
			via = graaf[van][naar];
			cout << woorden[van] << " -> " << woorden[naar] << " via " << alleVerbindingen[via] << endl;
		}

	}


	void leesWoordenIn(string bestandsnaam){
		string s = "data";
		ifstream fstream(bestandsnaam.c_str());
		int i = 0;
		if (fstream.is_open()){
			while (fstream >> s){
				woordenMap[s] = i++;;
				alleWoorden.push_back(s);
				graaf.voegKnoopToe();
				omgekeerdeGraaf.voegKnoopToe();
			}
			fstream.close();
		}
		else{
			cout << "Could not open file woordenlijst" << endl;
		}
		componentnummer.resize(graaf.aantalKnopen());
	}

	void leesVerbindingenIn(string bestandsnaam){
		string s1 = "";
		string s2 = "";
		string s3 = "";
		ifstream fstream2(bestandsnaam.c_str());
		int j;
		if (fstream2.is_open()){
			while (fstream2 >> s1 >> s2 >> s3){
				j = graaf.voegVerbindingToe(woordenMap[s1], woordenMap[s2]);
				omgekeerdeGraaf.voegVerbindingToe(woordenMap[s2], woordenMap[s1]);
				alleVerbindingen.push_back(s3);
			}
			fstream2.close();
		}
		else{
			cout << "Could not open file takkenlijst" << endl;
		}
	}

	void overloopPostorder(){
		for (unsigned int i = 0; i < omgekeerdeGraaf.knopen.size(); i++){
			if (componentnummer[i] == 0){
				overloopPostorder(i);
			}
		}
	}

	void overloopPostorder(int index){	//-1 = bezocht, 0 = niet bezocht , i=1-m = deel van component i
		componentnummer[index] = -1;
		for (Knoop::const_iterator i = omgekeerdeGraaf.knopen[index].begin(); i != omgekeerdeGraaf.knopen[index].end(); i++){
			if (componentnummer[i->first] == 0){
				overloopPostorder(i->first);
			}
		}
		s.push(index);
	}


	int componentnummerZoeker(){
		int componentNr = 1;
		while (!s.empty()){
			int topIndex = s.top();
			if (componentnummer[topIndex] == -1){
				componentnummerZoeker(componentNr, topIndex);
				componentNr++;
			}
			s.pop();
		}
		cout << "Aantalcomponentnummer " << componentNr << endl;
		return componentNr;
	}

	void componentnummerZoeker(int componentNr, int knoopIndex){
		componentnummer[knoopIndex] = componentNr;
		for (Knoop::const_iterator i = graaf.knopen[knoopIndex].begin(); i != graaf.knopen[knoopIndex].end(); i++){
			if (componentnummer[i->first] == -1){
				componentnummerZoeker(componentNr, i->first);
			}
		}
	}

	void printAllComponenten(ostream & out, int aantalComponenten){
		for (int i = 0; i < aantalComponenten; i++){
			printAlleWoordenVanComponent(out, i);
		}
	}

	void printAlleWoordenVanComponent(ostream & out, int nr){
		out << "Component " << nr << endl;
		int j = 0;
		for (int i = 0; i < componentnummer.size(); i++){
			if (componentnummer[i] == nr){
				j++;
				out << "      " << alleWoorden[i] << endl;
			}
		}
		out << "In totaal " << j << " knopen in deze component" << endl;
	}


	void zoekLus(int index, vector<int> & lus)
	{
		vector<bool> seen(graaf.knopen.size());
		map<int, int> previous;
		queue<int> q;
		int component = componentnummer[index];
		q.push(index);
		while (0 < q.size())
		{
			for (Knoop::iterator it = graaf.knopen[q.front()].begin(); it != graaf.knopen[q.front()].end(); it++)
			{
				if (component = componentnummer[it->first] && !seen[it->first])
				{
					if (it->first == index)
					{

						int knoop = q.front();
						while (knoop != index)
						{
							lus.push_back(knoop);
							knoop = previous[knoop];
						}
						lus.push_back(knoop);
						reverse(lus.begin(), lus.end());
						return;
					}
					seen[it->first] = true;
					previous[it->first] = q.front();
					q.push(it->first);
				}
			}
			q.pop();

		}
		return;


	}


	void printLus( vector<int> & lus)
	{
		if (lus.size() == 0)
		{
			cout << "!!!!!!!!!!!!!!!!!!!" << endl;
			return;
		}
		int van, naar, via;
		cout << "--- " << alleWoorden[lus[0]] << " ---" << endl;
		for (int i = 0; i < lus.size(); i++)
		{
			van = lus[i];
			naar = lus[(i + 1) % lus.size()];
			via = graaf[van][naar];
			cout << alleWoorden[van] << " -> " << alleWoorden[naar] << " via " << alleVerbindingen[via] << endl;
		}

	}

};




int main(int argc, char** argv) {
	const string woorden = "woordenlijst.txt";
	const string takken = "takkenlijst.txt";
	woordspelletje w(woorden,takken);
	
	return 0;
}

