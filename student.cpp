#include "student.h"

Student::Student() = default;

Student::Student(const std::string& v, const std::string& p) : vardas_(v), pavarde_(p) {}

const std::string& Student::vardas() const { return vardas_; }
const std::string& Student::pavarde() const { return pavarde_; }
double Student::galutinisVid() const { return galutinisVid_; }
double Student::galutinisMed() const { return galutinisMed_; }

bool operator<(const Student& a, const Student& b) {
    if (a.pavarde() != b.pavarde()) return a.pavarde() < b.pavarde();
    return a.vardas() < b.vardas();
}
