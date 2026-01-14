#include "functions.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


void ivedimas(vector<Student>& studentai,vector<vector<int>>& NamuDarbuBalai,int KiekisStudentu) {
    if (KiekisStudentu == 0) return;
    size_t idx = static_cast<size_t>(KiekisStudentu - 1);
    if (idx >= studentai.size() || idx >= NamuDarbuBalai.size()) return;

    auto& balai = NamuDarbuBalai[idx];
    balai.clear();

    int EmptyCount = 0;
    string eilute;
    cout << "\nĮveskite pažymius. Norit baigti ('Enter' du kartus):\n";
    while (true) {
        cout << "Pažymys: ";
        getline(cin, eilute);
        if (eilute.empty()) {
            EmptyCount++;
            if (EmptyCount == 2) break;
            continue;
        }
        EmptyCount = 0;
        stringstream ss(eilute);
        int balas;
        if (!(ss >> balas) || balas < 0 || balas > 10) {
            cout << "\nNeteisingas pažymys. Įveskite sveiką skaičių nuo 0 iki 10.\n";
            continue;
        }
        balai.push_back(balas);
    }

    if (balai.size() < 2) {
        cout << "\nReikia bent vieno namų darbo pažymio ir egzamino pažymio.\n";
        return;
    }
    studentai[idx].skaiciuoti(balai.begin(), balai.end());
}

void duomenys_is_failo(vector<Student>& studentai,vector<vector<int>>& NamuDarbuBalai,int& KiekisStudentu, const string& failoVardas) {
    auto startRead = high_resolution_clock::now();
    ifstream in(failoVardas);
    if (!in) {
        cout << "Nepavyko atidaryti failo: " << failoVardas << "\n";
        return;
    }
    string eilute;
    int eil_nr = 0;
    while (getline(in, eilute)) {
        ++eil_nr;
        if (eilute.empty()) continue;
        stringstream ss(eilute);
        string v, p;
        ss >> v >> p;
        if (v.empty() || p.empty()) continue;

        NamuDarbuBalai.emplace_back();
        auto& balai = NamuDarbuBalai.back();

        int balas;
        while (ss >> balas) balai.push_back(balas);

        if (balai.size() < 2) {
            NamuDarbuBalai.pop_back();
            continue;
        }

        studentai.emplace_back(v, p);
        studentai.back().skaiciuoti(balai.begin(), balai.end());
        KiekisStudentu++;
    }
    auto endRead = high_resolution_clock::now();
    cout << "Failo nuskaitymo laikas: "
         << duration<double>(endRead - startRead).count() << " s\n";
}

void atsitiktiniai_pazymiai(vector<Student>& studentai, vector<vector<int>>& NamuDarbuBalai,int KiekisStudentu) {
    if (KiekisStudentu == 0) return;
    size_t idx = static_cast<size_t>(KiekisStudentu - 1);
    if (idx >= studentai.size() || idx >= NamuDarbuBalai.size()) return;

    auto& balai = NamuDarbuBalai[idx];
    balai.clear();
    int kiekis = rand() % 10 + 1; // 1..10 ND
    for (int j = 0; j < kiekis; ++j) {
        int balas = rand() % 10 + 1;
        balai.push_back(balas);
    }
    int egzaminas = rand() % 10 + 1;
    balai.push_back(egzaminas);
    studentai[idx].skaiciuoti(balai.begin(), balai.end());
}

void kategorijos(const vector<Student>& studentai, vector<Student>& NeTokieProtingi, vector<Student>& protingi) {
    auto startSort = high_resolution_clock::now();
    NeTokieProtingi.clear();
    protingi.clear();
    NeTokieProtingi.reserve(studentai.size());
    protingi.reserve(studentai.size());

    for (const auto& s : studentai) {
        if (s.galutinisVid() >= 5.0) protingi.push_back(s);
        else NeTokieProtingi.push_back(s);
    }
    auto endSort = high_resolution_clock::now();
    cout << fixed << setprecision(6) << "Rūšiavimo į kategorijas laikas: " << duration<double>(endSort - startSort).count() << " s\n";

    auto startWrite = high_resolution_clock::now();
    ofstream outMaziau("maziau.txt");
    ofstream outProtingi("protingi.txt");

    outProtingi << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n";
    outProtingi << string(62, '-') << "\n";
    for (const auto& s : protingi) {
        outProtingi << s << '\n';
    }
    outProtingi.close();

    outMaziau << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n";
    outMaziau << string(62, '-') << "\n";
    for (const auto& s : NeTokieProtingi) {
        outMaziau << s << '\n';
    }
    outMaziau.close();

    auto endWrite = high_resolution_clock::now();
    cout << "Įrašymo į failus laikas: " << duration<double>(endWrite - startWrite).count() << " s\n";
}

void rezultatas(const vector<Student>& studentai) {
    cout << "\nPavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n";
    cout << string(62, '-') << "\n";

    vector<Student> sorted = studentai;
    sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b){
        if (a.pavarde() != b.pavarde()) return a.pavarde() < b.pavarde();
        return a.vardas() < b.vardas();
    });

    vector<Student> NeTokieProtingi, protingi;
    kategorijos(sorted, NeTokieProtingi, protingi);

    for (const auto& s : sorted) {
        cout << s << '\n';
    }
}

void kategorijos2(vector<Student>& studentai, vector<Student>& vargsiukai)
{
    const auto startSort = high_resolution_clock::now();
    vargsiukai.clear();
    vargsiukai.reserve(studentai.size());

    auto isProtingas = [](const Student& s) noexcept {
        return s.galutinisVid() >= 5.0;
    };

    auto mid = partition(studentai.begin(), studentai.end(), isProtingas);
    move(mid, studentai.end(), back_inserter(vargsiukai));
    studentai.erase(mid, studentai.end());

    const auto endSort = high_resolution_clock::now();
    cout << fixed << setprecision(6) << "Rūšiavimo į kategorijas laikas: " << duration<double>(endSort - startSort).count() << " s\n";

    const auto startWrite = high_resolution_clock::now();
    ofstream OutMaziau("maziau.txt");
    ofstream OutDaugiau("protingi.txt");

    OutMaziau << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n" << string(62, '-') << "\n";
    for (const auto& s : vargsiukai) {
        OutMaziau << s << '\n';
    }

    OutDaugiau << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n" << string(62, '-') << "\n";
    for (const auto& s : studentai) {
        OutDaugiau << s << '\n';
    }

    auto endWrite = high_resolution_clock::now();
    cout << "Įrašymo į failus laikas: " << duration<double>(endWrite - startWrite).count() << " s\n";
}


void kategorijos3(const vector<Student>& studentai,vector<Student>& vargsiukai,vector<Student>& protingi)
{
    const auto startSort = high_resolution_clock::now();

    vargsiukai.clear();
    protingi.clear();
    vargsiukai.reserve(studentai.size());
    protingi.reserve(studentai.size());

    auto isProtingas = [](const Student& s) noexcept {
        return s.galutinisVid() >= 5.0;
    };

    copy_if(studentai.begin(), studentai.end(), back_inserter(protingi), isProtingas);
    remove_copy_if(studentai.begin(), studentai.end(),back_inserter(vargsiukai), isProtingas);

    const auto endSort = high_resolution_clock::now();
    cout << fixed << setprecision(6) << "Rūšiavimo į kategorijas laikas: " << duration<double>(endSort - startSort).count() << " s\n";

    const auto startWrite = high_resolution_clock::now();
    ofstream OutMaziau("maziau.txt");
    ofstream OutDaugiau("protingi.txt");

    OutMaziau << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n" << string(62, '-') << "\n";
    for (const auto& s : vargsiukai) {
        OutMaziau << s << '\n';
    }

    OutDaugiau << "Pavardė Vardas Galutinis (Vid.) Galutinis (Med.)\n" << string(62, '-') << "\n";
    for (const auto& s : protingi) {
        OutDaugiau << s << '\n';
    }

    auto endWrite = high_resolution_clock::now();
    cout << "Įrašymo į failus laikas: " << duration<double>(endWrite - startWrite).count() << " s\n";
}
