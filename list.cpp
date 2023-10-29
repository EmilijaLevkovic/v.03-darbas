#include "my_lib_list.h"

double skaiciuoti_galutini(const list<int>& nd, int egz) {
    double suma = 0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    double vidurkis = suma / nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}
list<Studentas> nuskaityti_duomenis(const string& failo_vardas) {
    list<Studentas> studentai; 
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
void isvesti_duomenis(const string& failo_vardas, const list<Studentas>& studentai) {
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
pair<list<Studentas>, list<Studentas>> padalinti_studentus(const list<Studentas>& studentai) {
    list<Studentas> vargsiukai; 
    list<Studentas> kietiakiai; 
    for (const Studentas& s : studentai) { 
        if (s.galutinis < 5.0) { 
            vargsiukai.push_back(s); 
        } else { 
            kietiakiai.push_back(s); 
        }
    }
    return make_pair(vargsiukai, kietiakiai); 
}
void surusiuoti_studentus(list<Studentas>& studentai) {
    studentai.sort([] (const Studentas& a, const Studentas& b) {
        if (a.vardas < b.vardas) return true;
        if (a.vardas > b.vardas) return false;
        if (a.pavarde < b.pavarde) return true;
        if (a.pavarde > b.pavarde) return false;
        return a.galutinis < b.galutinis;
    });
}
int main() {
    try {
        auto start_read = high_resolution_clock::now();
        list<Studentas> studentai = nuskaityti_duomenis("studentai10000.txt");
        auto stop_read = high_resolution_clock::now();
        auto duration_read = duration_cast<microseconds>(stop_read - start_read);
        auto start_split = high_resolution_clock::now();
        pair<list<Studentas>, list<Studentas>> padalinimas = padalinti_studentus(studentai);
        auto stop_split = high_resolution_clock::now();
        auto duration_split = duration_cast<microseconds>(stop_split - start_split);
        auto start_sort = high_resolution_clock::now();
        surusiuoti_studentus(padalinimas.first);
        surusiuoti_studentus(padalinimas.second);
        auto stop_sort = high_resolution_clock::now();
        auto duration_sort = duration_cast<microseconds>(stop_sort - start_sort);
        auto start_write = high_resolution_clock::now();
        isvesti_duomenis("vargsiukai.txt", padalinimas.first);
        isvesti_duomenis("kietiakiai.txt", padalinimas.second);
        auto stop_write = high_resolution_clock::now();
        auto duration_write = duration_cast<microseconds>(stop_write - start_write);
        cout << "Programa baige darba. Rezultatai issaugoti failuose vargsiukai.txt ir kietiakiai.txt.\n";
        cout << "Duomenu nuskaitymas uztruko: " << duration_read.count() / 1000000.0 << " sek.\n";
        cout << "Studentu padalinimas uztruko: " << duration_split.count() / 1000000.0 << " sek.\n";
        cout << "Studentu rusiavimas uztruko: " << duration_sort.count() / 1000000.0 << " sek.\n";
        cout << "Duomenu isvedimas uztruko: " << duration_write.count() / 1000000.0 << " sek.\n";
    } catch (exception& e) {
        cout << "klaida: " << e.what() << "\n";
    }return 0;
}
