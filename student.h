#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstddef>

class Student {
private:
    std::string vardas_;
    std::string pavarde_;
    double galutinisVid_{0.0};
    double galutinisMed_{0.0};

    static double mediana(std::vector<int> v) {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        const std::size_t n = v.size();
        return (n % 2) ? v[n/2] : (v[n/2 - 1] + v[n/2]) / 2.0;
    }

public:
    Student();
    Student(const std::string& v, const std::string& p);
    ~Student();

    const std::string& vardas() const;
    const std::string& pavarde() const;
    double galutinisVid() const;
    double galutinisMed() const;

    template <typename Iter>
    void skaiciuoti(Iter begin, Iter end) {
        std::vector<int> balai(begin, end);
        if (balai.size() < 2) return;

        const int egz = balai.back();
        balai.pop_back();

        const double vid = std::accumulate(balai.begin(), balai.end(), 0.0) / balai.size();
        galutinisVid_ = 0.4 * vid + 0.6 * egz;
        galutinisMed_ = mediana(balai);
    }
};

bool operator<(const Student& a, const Student& b);

#endif