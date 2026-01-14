#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../student.h"
#include "../functions.h"

#include <vector>
#include <cmath>

static bool approx(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) < eps;
}

TEST_CASE("Student::skaiciuoti teisingai apskaiciuoja galutini pagal vidurki") {
    Student s("Jonas", "Jonaitis");

    // ND: 8, 6, 10; egz: 9 (paskutinis skaicius - egzaminas)
    std::vector<int> balai = {8, 6, 10, 9};
    s.skaiciuoti(balai.begin(), balai.end());

    // ND vid = (8+6+10)/3 = 8.0
    // galutinisVid = 0.4*8 + 0.6*9 = 8.6
    CHECK(s.galutinisVid() == doctest::Approx(8.6));
}

TEST_CASE("2) Student::skaiciuoti teisingai skaiciuoja ND mediana (lyginis ND kiekis)") {
    Student s("Ona", "Onaitė");

    // ND: 6, 8, 10, 2; egz: 9
    // ND surikiavus: 2, 6, 8, 10 => mediana = (6+8)/2 = 7.0
    std::vector<int> balai = {6, 8, 10, 2, 9};
    s.skaiciuoti(balai.begin(), balai.end());

    CHECK(s.galutinisMed() == doctest::Approx(7.0));
}

TEST_CASE("3) Student Copy constructor: kopija islaiko varda/pavarde ir galutinius pazymius") {
    Student a("Petras", "Petraitis");
    std::vector<int> balai = {10, 9, 8, 10}; // ND:10,9,8 ; egz:10
    a.skaiciuoti(balai.begin(), balai.end());

    Student b = a; 

    CHECK(b.vardas() == a.vardas());
    CHECK(b.pavarde() == a.pavarde());
    CHECK(b.galutinisVid() == doctest::Approx(a.galutinisVid()));
    CHECK(b.galutinisMed() == doctest::Approx(a.galutinisMed()));
}

TEST_CASE("4) Student operator=: priskyrimas perraso reiksmes teisingai") {
    Student a("A", "A");
    std::vector<int> balaiA = {5, 5, 5, 5}; // ND:5,5,5 ; egz:5
    a.skaiciuoti(balaiA.begin(), balaiA.end());

    Student b("B", "B");
    std::vector<int> balaiB = {10, 10, 10, 10}; // ND:10,10,10 ; egz:10
    b.skaiciuoti(balaiB.begin(), balaiB.end());

    b = a;

    CHECK(b.vardas() == "A");
    CHECK(b.pavarde() == "A");
    CHECK(b.galutinisVid() == doctest::Approx(a.galutinisVid()));
    CHECK(b.galutinisMed() == doctest::Approx(a.galutinisMed()));
}

TEST_CASE("5) kategorijos(vector): teisingai suskirsto i protingi ir neTokie (>=5.0)") {
    std::vector<Student> st;

    Student s1("Jonas", "Jonaitis"); // protingas
    std::vector<int> b1 = {10, 10, 10, 10}; // galutinisVid = 10
    s1.skaiciuoti(b1.begin(), b1.end());

    Student s2("Ona", "Onaitė"); // ne toks protingas
    std::vector<int> b2 = {1, 1, 1, 1}; // galutinisVid = 1
    s2.skaiciuoti(b2.begin(), b2.end());

    Student s3("Ieva", "Ievaitė"); // riba - protingas
    std::vector<int> b3 = {5, 5, 5, 5}; // ND vid=5, egz=5 => galutinisVid=5
    s3.skaiciuoti(b3.begin(), b3.end());

    st.push_back(s1);
    st.push_back(s2);
    st.push_back(s3);

    std::vector<Student> neTokie, protingi;
    kategorijos(st, neTokie, protingi);

    // Patikrina ar tikrai 2 protingi ir 1 neTokie
    CHECK(protingi.size() == 2);
    CHECK(neTokie.size() == 1);

    // Patikrinam, kad neTokie yra Ona
    CHECK(neTokie[0].vardas() == "Ona");
}