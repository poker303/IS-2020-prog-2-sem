#pragma once

#include "cmath"
#include "sstream"
#include <algorithm>

using namespace std;

class Polynomial {

private:

    int* coefss_of_polynomial;
    int* degs_of_polynomial;
    int size_of_polynomial;

public:

    Polynomial();

    Polynomial(int min, int max, int* coefs);

    Polynomial defining_sign(Polynomial& new1, const Polynomial& new2, int num) const;

    Polynomial(const Polynomial& another);

    ~Polynomial();

    Polynomial& operator=(const Polynomial& another);

    friend bool operator==(const Polynomial& new1, const Polynomial& new2);

    friend bool operator!=(const Polynomial& new1, const Polynomial& new2);

    friend Polynomial operator+(const Polynomial& new1, const Polynomial& new2);

    Polynomial operator-() const;

    friend Polynomial operator-(const Polynomial& new1, const Polynomial& new2);

    Polynomial operator+=(const Polynomial& another);

    Polynomial operator-=(const Polynomial& another);

    friend Polynomial operator*(const Polynomial& another, int num);

    friend Polynomial operator*(int num, const Polynomial& another);

    friend Polynomial operator*(const Polynomial& new1, const Polynomial& new2);

    Polynomial operator/(int num);

    Polynomial operator*=(const Polynomial& another);

    Polynomial operator/=(int num);

    int operator[](int num) const;

    int& operator[](int num);

    friend stringstream& operator<<(stringstream& conclusion, const Polynomial& another);

    double get(int num);
};