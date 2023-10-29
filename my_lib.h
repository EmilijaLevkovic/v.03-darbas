
#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using std::vector;
using std::string;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::seconds;
using namespace std;
struct Studentas {
  string vardas;
  string pavarde;
  vector<int> nd;
  int egz; 
  double galutinis;
};

vector<Studentas> nuskaityti_duomenis(const string& failo_vardas);

pair<vector<Studentas>, vector<Studentas>> padalinti_studentus(const vector<Studentas>& studentai);

void surusiuoti_studentus(vector<Studentas>& studentai);

void isvesti_duomenis(const string& failo_vardas, const vector<Studentas>& studentai);
