#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

double skaiciuoti_galutini(const vector<int>& nd, int egz) {
    double suma = 0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    double vidurkis = suma / nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}


vector<Studentas> nuskaityti_duomenis(const string& failo_vardas) {
    vector<Studentas> studentai; 
    ifstream failas(failo_vardas); 
    if (failas.fail()) { 
        throw runtime_error("Nepavyko atidaryti failo " + failo_vardas); 
    }
    string eilute;
    getline(failas, eilute); 
    while (getline(failas, eilute)) { 
        Studentas s; 
        stringstream ss(eilute); 
        ss >> s.vardas >> s.pavarde; 
        int pazymys;
        while (ss >> pazymys) { 
            s.nd.push_back(pazymys);
        }
        s.egz = s.nd.back(); 
        s.nd.pop_back(); 
        s.galutinis = skaiciuoti_galutini(s.nd, s.egz); 
        studentai.push_back(s); 
    }
    failas.close(); 
    return studentai; 
}
void isvesti_duomenis(const string& failo_vardas, const vector<Studentas>& studentai) {
    ofstream failas(failo_vardas); 
    if (failas.fail()) { 
        throw runtime_error("Nepavyko atidaryti failo " + failo_vardas);
    }
    failas << "Vardas\tPavarde\tGalutinis\n";
    for (const Studentas& s : studentai) { 
        failas << s.vardas << "\t" << s.pavarde << "\t" << s.galutinis << "\n"; 
    }
    failas.close();
}


pair<vector<Studentas>, vector<Studentas>> padalinti_studentus(const vector<Studentas>& studentai) {
    vector<Studentas> vargsiukai; 
    vector<Studentas> kietiakiai; 
    for (const Studentas& s : studentai) { 
        if (s.galutinis < 5.0) { 
            vargsiukai.push_back(s); 
        } else { 
            kietiakiai.push_back(s); 
        }
    }
    return make_pair(vargsiukai, kietiakiai); 
}
void surusiuoti_studentus(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(),[] (const Studentas& a, const Studentas& b) {
        if (a.vardas < b.vardas) return true;
        if (a.vardas > b.vardas) return false;
        if (a.pavarde < b.pavarde) return true;
        if (a.pavarde > b.pavarde) return false;
        return a.galutinis < b.galutinis;
    });
}

int main() {
    try { 
        vector<Studentas> studentai = nuskaityti_duomenis("studentai10000.txt");
        pair<vector<Studentas>, vector<Studentas>> padalinimas = padalinti_studentus(studentai); 
        surusiuoti_studentus(padalinimas.first); 
      surusiuoti_studentus(padalinimas.second);
      isvesti_duomenis("vargsiukai.txt", padalinimas.first);
      isvesti_duomenis("kietiakiai.txt", padalinimas.second);
      cout << "Programa baige darba. Rezultatai issaugoti failuose vargsiukai.txt ir kietiakiai.txt.\n"; 
          } catch (exception& e) { 
              cout << "Programa susidure su klaida: " << e.what() << "\n"; 
          }
          return 0;
}
