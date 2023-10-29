#include "list.h"

double skaiciuoti_galutini(const list<int>& nd, int egz) {
    double suma = 0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    double vidurkis = suma / nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}
list<StudentasL> nuskaityti_duomenis_list(const string& failo_vardas) {
    list<StudentasL> studentai; 
    ifstream failas(failo_vardas); 
    if (failas.fail()) { 
        throw runtime_error("Nepavyko atidaryti failo " + failo_vardas); 
    }
    string eilute;
    getline(failas, eilute); 
    while (getline(failas, eilute)) { 
        StudentasL s; 
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
void isvesti_duomenis_list(const string& failo_vardas, const list<StudentasL>& studentai) {
    ofstream failas(failo_vardas); 
    if (failas.fail()) { 
        throw runtime_error("Nepavyko atidaryti failo " + failo_vardas);
    }
    failas << "Vardas\tPavarde\tGalutinis\n";
    for (const StudentasL& s : studentai) { 
        failas << s.vardas << "\t" << s.pavarde << "\t" << s.galutinis << "\n"; 
    }
    failas.close();
}
pair<list<StudentasL>, list<StudentasL>> padalinti_studentus_list(const list<StudentasL>& studentai) {
    list<StudentasL> vargsiukai_list; 
    list<StudentasL> kietiakiai_list; 
    for (const StudentasL& s : studentai) { 
        if (s.galutinis < 5.0) { 
            vargsiukai_list.push_back(s); 
        } else { 
            kietiakiai_list.push_back(s); 
        }
    }
    return make_pair(vargsiukai_list, kietiakiai_list); 
}
void surusiuoti_studentus_list(list<StudentasL>& studentai) {
    studentai.sort([] (const StudentasL& a, const StudentasL& b) {
        if (a.vardas < b.vardas) return true;
        if (a.vardas > b.vardas) return false;
        if (a.pavarde < b.pavarde) return true;
        if (a.pavarde > b.pavarde) return false;
        return a.galutinis < b.galutinis;
    });
}
int list_main() {
    try {
        auto start_read = high_resolution_clock::now();
        list<StudentasL> studentai = nuskaityti_duomenis_list("studentai10000.txt");
        auto stop_read = high_resolution_clock::now();
        auto duration_read = duration_cast<microseconds>(stop_read - start_read);
        auto start_split = high_resolution_clock::now();
        pair<list<StudentasL>, list<StudentasL>> padalinimas = padalinti_studentus_list(studentai);
        auto stop_split = high_resolution_clock::now();
        auto duration_split = duration_cast<microseconds>(stop_split - start_split);
        auto start_sort = high_resolution_clock::now();
        surusiuoti_studentus_list(padalinimas.first);
        surusiuoti_studentus_list(padalinimas.second);
        auto stop_sort = high_resolution_clock::now();
        auto duration_sort = duration_cast<microseconds>(stop_sort - start_sort);
        auto start_write = high_resolution_clock::now();
        isvesti_duomenis_list("vargsiukai_list.txt", padalinimas.first);
        isvesti_duomenis_list("kietiakiai_list.txt", padalinimas.second);
        auto stop_write = high_resolution_clock::now();
        auto duration_write = duration_cast<microseconds>(stop_write - start_write);
        cout << "List Programa baige darba. Rezultatai issaugoti failuose vargsiukai_list.txt ir kietiakiai_list.txt.\n";
        cout << "List Duomenu nuskaitymas: " << duration_read.count() / 1000000.0 << " sek.\n";
        cout << "List Studentu padalinimas: " << duration_split.count() / 1000000.0 << " sek.\n";
        cout << "List Studentu rusiavimas: " << duration_sort.count() / 1000000.0 << " sek.\n";
        cout << "List Duomenu isvedimas: " << duration_write.count() / 1000000.0 << " sek.\n";
    } catch (exception& e) {
        cout << "List Programa susidure su klaida: " << e.what() << "\n";
    }return 0;
}

