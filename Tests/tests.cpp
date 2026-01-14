#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../student.h"
#include <vector>

TEST_CASE("Student::skaiciuoti teisingai apskaiciuoja galutini pagal vidurki") {
    Student s("Jonas", "Jonaitis");

    // ND: 8, 6, 10; egz: 9 (paskutinis skaicius - egzaminas)
    std::vector<int> balai = {8, 6, 10, 9};
    s.skaiciuoti(balai.begin(), balai.end());

    // ND vid = (8+6+10)/3 = 8.0
    // galutinisVid = 0.4*8 + 0.6*9 = 8.6
    CHECK(s.galutinisVid() == doctest::Approx(8.6));
}
