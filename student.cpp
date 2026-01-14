#include "student.h"

#include <iostream>
#include <iomanip>

Student::Student() = default;

Student::Student(const std::string& v, const std::string& p)
    : Zmogus(v, p) {}

double Student::galutinisVid() const { return galutinisVid_; }
double Student::galutinisMed() const { return galutinisMed_; }

bool operator<(const Student& a, const Student& b) {
    if (a.pavarde() != b.pavarde()) return a.pavarde() < b.pavarde();
    return a.vardas() < b.vardas();
}


Student::Student(const Student& other)
    : Zmogus(other.vardas_, other.pavarde_),
      galutinisVid_(other.galutinisVid_),
      galutinisMed_(other.galutinisMed_) {}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    vardas_ = other.vardas_;
    pavarde_ = other.pavarde_;
    galutinisVid_ = other.galutinisVid_;
    galutinisMed_ = other.galutinisMed_;
    return *this;
}

Student::~Student() = default;

void Student::spausdinti(std::ostream& out) const {
    out << std::left << std::setw(14) << pavarde()
        << std::left << std::setw(14) << vardas()
        << std::fixed << std::setprecision(2)
        << std::setw(19) << galutinisVid()
        << std::setw(16) << galutinisMed();
}

std::istream& operator>>(std::istream& in, Student& s) {
    in >> s.vardas_ >> s.pavarde_;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    s.spausdinti(out); 
    return out;
}