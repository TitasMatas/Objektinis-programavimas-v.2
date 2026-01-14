#include "functions.h"

#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <list>
#include <limits>
using namespace std;
using namespace std::chrono;

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "lt_LT.UTF-8");

    // List strategijos konteineriai
    list<Student> studentai;
    list<list<int>> NamuDarbuBalai;
    list<Student> NeTokieProtingi, protingi;
    int KiekisStudentu = 0;

    // Vector strategijos konteineriai
    vector<Student> studentaiV;
    vector<vector<int>> NamuDarbuBalaiV;
    vector<Student> NeTokieProtingiV, protingiV;
    int KiekisStudentuV = 0;

    {
        Student a("Jonas", "Jonaitis");
        Student b = a;  
        Student c;
        c = a;          

        cout << "\n[Rule of Three demonstracija]\n";
        cout << a << '\n';
        cout << b << '\n';
        cout << c << '\n';
    }

    while (true) {
        int pasirinkimas;
        cout << "\nPasirinkimai:\n"
             << "0 - Naujas studentas (LIST)\n"
             << "1 - Įvesti pažymius ranka (LIST)\n"
             << "2 - Įvedami atsitiktiniai pažymiai (LIST)\n"
             << "3 - Įvedami duomenys iš failo (LIST)\n"
             << "4 - Laiko testas \"1 Strategija\" - LIST\n"
             << "5 - Laiko testas \"1 Strategija\" - VECTOR\n"
             << "6 - Laiko testas \"2 Strategija\" - LIST\n"
             << "7 - Laiko testas \"2 Strategija\" - VECTOR\n"
             << "8 - Laiko testas \"3 Strategija\" - LIST\n"
             << "9 - Laiko testas \"3 Strategija\" - VECTOR\n"
             << "10 - Spausdinti rezultatus (LIST)\n"
             << "11 - Išeiti\n"
             << "Pasirinkimas: ";
        if (!(cin >> pasirinkimas)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkimas == 0) {
            Student s;
            cout << "\nĮveskite vardą ir pavardę: ";
            cin >> s; 
            studentai.emplace_back(s);
            NamuDarbuBalai.emplace_back();
            cout << "\nStudentas (LIST) pridėtas.\n";
            KiekisStudentu++;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        else if (pasirinkimas == 1) {
            if (KiekisStudentu == 0) {
                cout << "\nNėra studentų. Pirmiausia pridėkite studentą.\n";
            } else {
                ivedimas(studentai, NamuDarbuBalai, KiekisStudentu);
            }
        }
        else if (pasirinkimas == 2) {
            atsitiktiniai_pazymiai(studentai, NamuDarbuBalai, KiekisStudentu);
        }
        else if (pasirinkimas == 3) {
            string file;
            cout << "\nĮveskite failo vardą: ";
            getline(cin, file);
            duomenys_is_failo(studentai, NamuDarbuBalai, KiekisStudentu, file);
        }
        else if (pasirinkimas == 4) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test LIST - 1 strategija] Failas: " << file << "\n";
                list<Student> testStudentai;
                list<list<int>> testBalai;
                int testKiekis = 0;
                auto startTotal = high_resolution_clock::now();
                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                kategorijos(testStudentai, NeTokieProtingi, protingi);
                auto endTotal = high_resolution_clock::now();
                cout << "Bendras laikas (List - 1 strategija): " << duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
        else if (pasirinkimas == 5) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test Vector - 1 strategija] Failas: " << file << "\n";
                vector<Student> testStudentai;
                vector<vector<int>> testBalai;
                int testKiekis = 0;
                auto startTotal = high_resolution_clock::now();

                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                kategorijos(testStudentai, NeTokieProtingiV, protingiV);
                auto endTotal = high_resolution_clock::now();

                cout << "Bendras laikas (Vector - 1 strategija): " << duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
        else if (pasirinkimas == 6) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test LIST - 2 strategija] Failas: " << file << "\n";
                list<Student> testStudentai;
                list<list<int>> testBalai;
                int testKiekis = 0;

                auto startTotal = high_resolution_clock::now();

                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                list<Student> vargsiukai;
                kategorijos2(testStudentai, vargsiukai);

                auto endTotal = high_resolution_clock::now();
                cout << "Bendras laikas (LIST - 2 strategija): " << duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
        else if (pasirinkimas == 7) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test VECTOR - 2 strategija] Failas: " << file << "\n";
                vector<Student> testStudentai;
                vector<vector<int>> testBalai;
                int testKiekis = 0;

                auto startTotal = high_resolution_clock::now();

                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                vector<Student> vargsiukai;
                kategorijos2(testStudentai, vargsiukai);

                auto endTotal = high_resolution_clock::now();
                cout << "Bendras laikas (VECTOR - 2 strategija): "<< duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
         else if (pasirinkimas == 8) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test LIST - 3 strategija] Failas: " << file << "\n";
                list<Student> testStudentai;
                list<list<int>> testBalai;
                int testKiekis = 0;

                auto startTotal = high_resolution_clock::now();

                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                list<Student> vargsiukai, protingi;
                kategorijos3(testStudentai, vargsiukai, protingi);

                auto endTotal = high_resolution_clock::now();
                cout << "Bendras laikas (LIST - 3 strategija): "<< duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
         else if (pasirinkimas == 9) {
            vector<string> files = {
                "Test_failai/studentai10.txt",
                "Test_failai/studentai100.txt",
                "Test_failai/studentai1000.txt",
                "Test_failai/studentai10000.txt",
                "Test_failai/studentai100000.txt"
            };
            for (const auto& file : files) {
                cout << "\n[Test Vector - 3 strategija] Failas: " << file << "\n";
                vector<Student> testStudentai;
                vector<vector<int>> testBalai;
                int testKiekis = 0;

                auto startTotal = high_resolution_clock::now();

                duomenys_is_failo(testStudentai, testBalai, testKiekis, file);
                vector<Student> vargsiukai, protingi;
                kategorijos3(testStudentai, vargsiukai, protingi);

                auto endTotal = high_resolution_clock::now();
                cout << "Bendras laikas (Vector - 3 strategija): "<< duration<double>(endTotal - startTotal).count() << " s\n";
            }
        }
        else if (pasirinkimas == 10) {
            rezultatas(studentai);
        }
        else if (pasirinkimas == 11) {
            break;
        }
        else {
            cout << "\nNeteisingas pasirinkimas. Bandykite dar kartą.\n";
        }
    }
    return 0;
}
