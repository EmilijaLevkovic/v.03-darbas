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

struct StudentasL {
  string vardas;
  string pavarde;
  list<int> nd;
  int egz;
  double galutinis; 
}; 
list<StudentasL> nuskaityti_duomenis_list(const string& failo_vardas);

pair<list<StudentasL>, list<StudentasL>> padalinti_studentus_list(const list<StudentasL>& studentai);

void surusiuoti_studentus_list(list<StudentasL>& studentai);

void isvesti_duomenis_list(const string& failo_vardas, const list<StudentasL>& studentai);
