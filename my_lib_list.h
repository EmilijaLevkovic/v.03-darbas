#include <algorithm>
#include <chrono> 
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
using std::list;
using std::string;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::seconds;
using namespace std;
struct Studentas {
  string vardas;
  string pavarde;
  list<int> nd;  
  int egz;     
  double galutinis; 
};

list<Studentas> nuskaityti_duomenis(const string& failo_vardas);

pair<list<Studentas>, list<Studentas>> padalinti_studentus(const list<Studentas>& studentai);

void surusiuoti_studentus(list<Studentas>& studentai);

void isvesti_duomenis(const string& failo_vardas, const list<Studentas>& studentai);
