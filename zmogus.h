#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;
    Zmogus(const std::string& v, const std::string& p) : vardas_(v), pavarde_(p) {}

    virtual ~Zmogus() = default;

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }

    virtual void spausdinti(std::ostream& out) const = 0;
};

#endif
