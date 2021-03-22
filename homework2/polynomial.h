#pragma once
#include "cmath"
#include "sstream"

using namespace std;

class Polynomial {

private:

    int* degree_of_polynomial;
    int* coefss_of_polynomial;
    int size_of_polynomial;

public:

    Polynomial();

    Polynomial(int min, int max, int* coefs);

    Polynomial(const Polynomial& another);

    ~Polynomial();

    friend stringstream& operator<<(stringstream& out, const Polynomial& another);

    Polynomial& operator=(const Polynomial& another);

    friend bool operator==(const Polynomial& another1, const Polynomial& another2);

    friend bool operator!=(const Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator+(const Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator-(const Polynomial& another);

    friend Polynomial operator-(const Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator+=(Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator-=(Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator*(const Polynomial& another, int num);

    friend Polynomial operator*(int num, const Polynomial& another);

    friend Polynomial operator*(const Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator/(const Polynomial& another, int num);

    friend Polynomial operator*=(Polynomial& another1, const Polynomial& another2);

    friend Polynomial operator/=(Polynomial& another, int num);

    int& operator[](int i);

    int& operator[](int num) const;

    double get(int num);
};