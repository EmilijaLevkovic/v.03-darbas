
#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
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
