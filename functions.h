
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"

#include <list>
#include <vector>
#include <string>

// List dalis
void ivedimas(std::list<Student>& studentai, std::list<std::list<int>>& NamuDarbuBalai, int KiekisStudentu);
void duomenys_is_failo(std::list<Student>& studentai, std::list<std::list<int>>& NamuDarbuBalai, int& KiekisStudentu, const std::string& failoVardas);
void atsitiktiniai_pazymiai(std::list<Student>& studentai, std::list<std::list<int>>& NamuDarbuBalai, int KiekisStudentu);
void rezultatas(const std::list<Student>& studentai);
void kategorijos(const std::list<Student>& studentai, std::list<Student>& NeTokieProtingi, std::list<Student>& protingi);
void kategorijos2(std::list<Student>& studentai, std::list<Student>& vargsiukai);
void kategorijos3(const std::list<Student>& studentai, std::list<Student>& vargsiukai, std::list<Student>& protingi);

// Vector dalis
void ivedimas(std::vector<Student>& studentai, std::vector<std::vector<int>>& NamuDarbuBalai, int KiekisStudentu);
void duomenys_is_failo(std::vector<Student>& studentai, std::vector<std::vector<int>>& NamuDarbuBalai, int& KiekisStudentu, const std::string& failoVardas);
void atsitiktiniai_pazymiai(std::vector<Student>& studentai, std::vector<std::vector<int>>& NamuDarbuBalai, int KiekisStudentu);
void rezultatas(const std::vector<Student>& studentai);
void kategorijos(const std::vector<Student>& studentai, std::vector<Student>& NeTokieProtingi, std::vector<Student>& protingi);
void kategorijos2(std::vector<Student>& studentai, std::vector<Student>& vargsiukai);
void kategorijos3(const std::vector<Student>& studentai, std::vector<Student>& vargsiukai, std::vector<Student>& protingi);

#endif
