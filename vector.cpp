#include "vector.h"


double skaiciuoti_galutini(const vector<int>& nd, int egz) {
    double suma = 0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    double vidurkis = suma / nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}

vector<Studentas> nuskaityti_duomenis_vector(const string& failo_vardas) {
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

void isvesti_duomenis_vector(const string& failo_vardas, const vector<Studentas>& studentai) {
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

pair<vector<Studentas>, vector<Studentas>> padalinti_studentus_vector(const vector<Studentas>& studentai) {
    vector<Studentas> vargsiukai_vector;
    vector<Studentas> kietiakiai_vector; 
    for (const Studentas& s : studentai) { 
        if (s.galutinis < 5.0) { 
            vargsiukai_vector.push_back(s); 
        } else { 
            kietiakiai_vector.push_back(s); 
        }
    }
    return make_pair(vargsiukai_vector, kietiakiai_vector); 
}
void surusiuoti_studentus_vector(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(),[] (const Studentas& a, const Studentas& b) {
        if (a.vardas < b.vardas) return true;
        if (a.vardas > b.vardas) return false;
        if (a.pavarde < b.pavarde) return true;
        if (a.pavarde > b.pavarde) return false;
        return a.galutinis > b.galutinis;
    });
}


int vector_main() {
    try {
        auto start_read = high_resolution_clock::now();
        vector<Studentas> studentai = nuskaityti_duomenis_vector("studentai10000.txt");
        auto stop_read = high_resolution_clock::now();
        auto duration_read = duration_cast<microseconds>(stop_read - start_read);

        auto start_split = high_resolution_clock::now();
        pair<vector<Studentas>, vector<Studentas>> padalinimas = padalinti_studentus_vector(studentai);
        auto stop_split = high_resolution_clock::now();
        auto duration_split = duration_cast<microseconds>(stop_split - start_split);

        auto start_sort = high_resolution_clock::now();
        surusiuoti_studentus_vector(padalinimas.first);
        surusiuoti_studentus_vector(padalinimas.second);
        auto stop_sort = high_resolution_clock::now();
        auto duration_sort = duration_cast<microseconds>(stop_sort - start_sort);

        auto start_write = high_resolution_clock::now();
        isvesti_duomenis_vector("vargsiukai_vector.txt", padalinimas.first);
        isvesti_duomenis_vector("kietiakiai_vector.txt", padalinimas.second);
        auto stop_write = high_resolution_clock::now();
        auto duration_write = duration_cast<microseconds>(stop_write - start_write);

        cout << "Programa baige darba. Rezultatai issaugoti failuose vargsiukai_vector.txt ir kietiakiai_v ector.txt.\n";

        cout << "Vector Duomenu nuskaitymas uztruko: " << duration_read.count() / 1000000.0 << " sek.\n";
        cout << "Vector Studentu padalinimas uztruko: " << duration_split.count() / 1000000.0 << " sek.\n";
        cout << "Vector Studentu rusiavimas uztruko: " << duration_sort.count() / 1000000.0 << " sek.\n";
        cout << "Vector Duomenu isvedimas uztruko: " << duration_write.count() / 1000000.0 << " sek.\n";
    } catch (exception& e) {
        cout << "Vector Programa susidure su klaida: " << e.what() << "\n";
    }
    return 0;
}
