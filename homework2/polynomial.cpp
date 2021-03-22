#include "polynomial.h"

Polynomial::Polynomial() {

    coefss_of_polynomial = new int[1]{0};
    degree_of_polynomial = new int[1]{0};
    size_of_polynomial = 1;
}

Polynomial::Polynomial(int min, int max, int* coefs) {

    int size = max - min + 1;
    int pendingDegree = min;

    degree_of_polynomial = new int[size];
    coefss_of_polynomial = new int[size];
    size_of_polynomial = size;

    for (int i = 0; i < size; i++) {
        degree_of_polynomial[i] = pendingDegree;
        coefss_of_polynomial[i] = *coefs;
        pendingDegree++;
        coefs++;
    }
}

Polynomial::Polynomial(const Polynomial& another) {

    size_of_polynomial = another.size_of_polynomial;

    coefss_of_polynomial = new int[size_of_polynomial];
    degree_of_polynomial = new int[size_of_polynomial];

    for (int i = 0; i < size_of_polynomial; i++) {

        degree_of_polynomial[i] = another.degree_of_polynomial[i];
        coefss_of_polynomial[i] = another.coefss_of_polynomial[i];
    }
}

Polynomial::~Polynomial() = default;

Polynomial& Polynomial::operator=(const Polynomial & another) = default;

bool operator==(const Polynomial & another1, const Polynomial & another2) {

    stringstream ss1, ss2;
    ss1 << another1;
    ss2 << another2;
    return ss1.str() == ss2.str();
}

bool operator!=(const Polynomial & another1, const Polynomial & another2) {

    return !(another1 == another2);
}

Polynomial operator+(const Polynomial & another1, const Polynomial & another2) {

    int pending_min_deg = min(another1.degree_of_polynomial[0], another2.degree_of_polynomial[0]);

    int pending_max_deg = max(another1.degree_of_polynomial[another1.size_of_polynomial - 1], 
        another2.degree_of_polynomial[another2.size_of_polynomial - 1]);

    int pendingSize = pending_max_deg - pending_min_deg + 1;
    int *pendingcoefs = new int [pendingSize];
    int pendingDegree = pending_min_deg;

    for (int i = 0; i < pendingSize; i++) {
        pendingcoefs[i] = 0;

        for (int j = 0; j < another1.size_of_polynomial; j++) {

            if (another1.degree_of_polynomial[j] == pendingDegree)
                pendingcoefs[i] += another1.coefss_of_polynomial[j];
        }

        for (int j = 0; j < another2.size_of_polynomial; j++) {

            if (another2.degree_of_polynomial[j] == pendingDegree)
                pendingcoefs[i] += another2.coefss_of_polynomial[j];
        }

        pendingDegree++;
    }

    return Polynomial(pending_min_deg, pending_max_deg, pendingcoefs);
}

Polynomial operator-(const Polynomial & another) {

    Polynomial pending = another;
    for (int i = 0; i < pending.size_of_polynomial; i++) {

        pending.coefss_of_polynomial[i] = -another.coefss_of_polynomial[i];
    }
    return pending;
}

Polynomial operator-(const Polynomial & another1, const Polynomial & another2) {
    return another1 + (-another2);
}

Polynomial operator+=(Polynomial & another1, const Polynomial & another2) {

    another1 = another1 + another2;
    return another1;
}

Polynomial operator-=(Polynomial & another1, const Polynomial & another2) {

    another1 = another1 - another2;
    return another1;
}

Polynomial operator*(const Polynomial & another, int num) {

    int* pendingcoefs = new int[another.size_of_polynomial];

    for (int i = 0; i < another.size_of_polynomial; i++) {

        pendingcoefs[i] = another.coefss_of_polynomial[i] * num;
    }

    return Polynomial(another.degree_of_polynomial[0], 
        another.degree_of_polynomial[another.size_of_polynomial - 1], pendingcoefs);
}

Polynomial operator*(int num, const Polynomial & another) {
    return another * num;
}

Polynomial operator*(const Polynomial & another1, const Polynomial & another2) {

    int pendingSize = another1.size_of_polynomial * another2.size_of_polynomial;
    int* pendingcoefs = new int[pendingSize], *pendingDegree = new int [pendingSize];
    int ordinal_number = 0;

    for (int i = 0; i < another1.size_of_polynomial; i++) {

        for (int j = 0; j < another2.size_of_polynomial; j++) {

            pendingcoefs[ordinal_number] = another1.coefss_of_polynomial[i] * another2.coefss_of_polynomial[j];
            pendingDegree[ordinal_number] = another1.degree_of_polynomial[i] + another2.degree_of_polynomial[j];
            ordinal_number++;
        }
    }

    int size = pendingDegree[pendingSize - 1] - pendingDegree[0] + 1;
    int *resultDegree = new int[size], *resultcoefs = new int[size];
    ordinal_number = pendingDegree[0];

    for (int i = 0; i < size; i++) {

        resultDegree[i] = ordinal_number;
        resultcoefs[i] = 0;
        ordinal_number++;
    }

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < pendingSize; j++) {

            if (pendingDegree[j] == resultDegree[i])
                resultcoefs[i] += pendingcoefs[j];
        }
    }

    return Polynomial(pendingDegree[0], pendingDegree[pendingSize - 1], resultcoefs);
}

Polynomial operator/(const Polynomial & another, int num) {

    int* pendingcoefs = new int[another.size_of_polynomial];

    for (int i = 0; i < another.size_of_polynomial; i++) {

        pendingcoefs[i] = another.coefss_of_polynomial[i] / num;
    }

    return Polynomial(another.degree_of_polynomial[0], 
        another.degree_of_polynomial[another.size_of_polynomial - 1], pendingcoefs);
}

Polynomial operator*=(Polynomial & another1, const Polynomial & another2) {

    another1 = another1 * another2;
    return another1;
}

Polynomial operator/=(Polynomial & another, int num) {

    another = another / num;
    return another;
}

int& Polynomial::operator[](int num) const {

    if (num > degree_of_polynomial[0] && num < degree_of_polynomial[size_of_polynomial - 1]) {
        int ordinal_number = 0;
        for (int i = 0; i < size_of_polynomial; i++) {

            if (num == degree_of_polynomial[i]) {
                break;
            }
            ordinal_number++;
        }
        return coefss_of_polynomial[ordinal_number];
    }
    else {
        int* resultcoefs = new int[1]{ 0 };
        return *resultcoefs;
    }
}

int& Polynomial::operator[](int num) {

    if (num > degree_of_polynomial[0] && num < degree_of_polynomial[size_of_polynomial - 1]) {
        const Polynomial another = *this;
        return another[num];
    }

    else if (num < degree_of_polynomial[0]) {

        int max = degree_of_polynomial[size_of_polynomial - 1];
        int min = num;
        int pendingSize = max - min + 1;
        int* pendingcoefs = new int[pendingSize];

        for (int i = 0; i < pendingSize; i++) {
            pendingcoefs[i] = 0;
        }

        for (int i = 1; i < size_of_polynomial; i++) {
            pendingcoefs[pendingSize - i] = coefss_of_polynomial[size_of_polynomial - i];
        }

        *this = Polynomial(min, max, pendingcoefs);
        return coefss_of_polynomial[0];
    }
    else {

        int max = num;
        int min = degree_of_polynomial[0];
        int pendingSize = max - min + 1;
        int* pendingcoefs = new int[pendingSize];

        for (int i = 0; i < pendingSize; i++) {
            pendingcoefs[i] = 0;
        }

        for (int i = 0; i < size_of_polynomial; i++) {
            pendingcoefs[i] = coefss_of_polynomial[i];
        }

        *this = Polynomial(min, max, pendingcoefs);
        return coefss_of_polynomial[size_of_polynomial - 1];
    }
}

stringstream& operator<<(stringstream& conclusion, const Polynomial& another) {

    int pendingSize = another.size_of_polynomial;

    if (pendingSize == 1 && another.coefss_of_polynomial[0] == 0) {
        conclusion << "0";
    }

    else {

        for (int i = pendingSize - 1; i >= 0; i--) {

            if (another.coefss_of_polynomial[i] != 0) {

                if (i < pendingSize - 1 && another.coefss_of_polynomial[i] > 0 &&
                    !conclusion.str().empty() && conclusion.str().back() != '\n')
                    conclusion << "+";

                if (another.coefss_of_polynomial[i] == -1 && another.degree_of_polynomial[i] != 0)
                    conclusion << "-";

                else if (another.coefss_of_polynomial[i] == 1 && another.degree_of_polynomial[i] != 0) {}

                else
                    conclusion << another.coefss_of_polynomial[i];

                if (another.degree_of_polynomial[i] != 0) {
                    conclusion << "x";
                    if (another.degree_of_polynomial[i] != 1)
                        conclusion << "^" << another.degree_of_polynomial[i];
                }
            }
        }
    }

    int pending = 0;

    for (int i = 0; i < another.size_of_polynomial; i++) {

        if (another.coefss_of_polynomial[i] == 0)
            pending++;
    }

    if (pending == another.size_of_polynomial && conclusion.str().empty())
        conclusion << "0";
    return conclusion;
}

double Polynomial::get(int num) {

    double result = 0;

    for (int i = 0; i < size_of_polynomial; i++) {
        result += coefss_of_polynomial[i] * pow(num, degree_of_polynomial[i]);
    }

    return result;
}