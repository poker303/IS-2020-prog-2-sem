#include "polynomial.h"

Polynomial::Polynomial() {

    coefss_of_polynomial = new int[1]{0};
    degs_of_polynomial = new int[1]{0};
    size_of_polynomial = 1;
}

Polynomial::Polynomial(int min, int max, int* coefs) {

    int size = max - min + 1;
    int pendingDegree = min;

    degs_of_polynomial = new int[size];
    coefss_of_polynomial = new int[size];
    size_of_polynomial = size;

    for (int i = 0; i < size; i++) {

        degs_of_polynomial[i] = pendingDegree;
        coefss_of_polynomial[i] = coefs[i];
        pendingDegree++;
    }
}

Polynomial Polynomial::defining_sign(Polynomial& new1, const Polynomial& new2, int num) const {

    int pending_min_deg = min(new1.degs_of_polynomial[0], new2.degs_of_polynomial[0]);
    int pending_max_deg = max(new1.degs_of_polynomial[new1.size_of_polynomial - 1],
        new2.degs_of_polynomial[new2.size_of_polynomial - 1]);

    int  pendingSize = pending_max_deg - pending_min_deg + 1;
    int* pendingcoefs = new int[pendingSize];
    int check_point = pending_min_deg;

    for (int i = 0; i < pendingSize; i++) {
        pendingcoefs[i] = 0;

        for (int j = 0; j < new1.size_of_polynomial; j++) {

            if (new1.degs_of_polynomial[j] == check_point)
                pendingcoefs[i] += new1.coefss_of_polynomial[j];

        }

        for (int j = 0; j < new2.size_of_polynomial; j++) {

            if (new2.degs_of_polynomial[j] == check_point)
                pendingcoefs[i] += new2.coefss_of_polynomial[j] * num;

        }
        check_point++;
    }

    new1 = Polynomial(pending_min_deg, pending_max_deg, pendingcoefs);

    return new1;
}

Polynomial::Polynomial(const Polynomial& another) {

    size_of_polynomial = another.size_of_polynomial;

    coefss_of_polynomial = new int[size_of_polynomial];
    degs_of_polynomial = new int[size_of_polynomial];

    for (int i = 0; i < size_of_polynomial; i++) {
        degs_of_polynomial[i] = another.degs_of_polynomial[i];
        coefss_of_polynomial[i] = another.coefss_of_polynomial[i];
    }
}

Polynomial::~Polynomial() {

    delete[] coefss_of_polynomial;
    delete[] degs_of_polynomial;
}

Polynomial& Polynomial::operator=(const Polynomial& another) {

    if (&another == this) return *this;

    delete[] coefss_of_polynomial;
    delete[] degs_of_polynomial;

    size_of_polynomial = another.size_of_polynomial;
    coefss_of_polynomial = new int[size_of_polynomial];
    degs_of_polynomial = new int[size_of_polynomial];

    for (int i = 0; i < size_of_polynomial; i++) {

        coefss_of_polynomial[i] = another.coefss_of_polynomial[i];
        degs_of_polynomial[i] = another.degs_of_polynomial[i];
    }

    return *this;
}

bool operator==(const Polynomial& new1, const Polynomial& new2) {

    stringstream pol1, pol2;
    pol1 << new1; pol2 << new2;

    return pol1.str() == pol2.str();
}

bool operator!=(const Polynomial& new1, const Polynomial& new2) {

    return !(new1 == new2);
}

Polynomial operator+(const Polynomial& new1, const Polynomial& new2) {

    Polynomial pending = new1;
    pending += new2;

    return pending;
}

Polynomial Polynomial::operator-() const {

    Polynomial pending = *this;

    for (int i = 0; i < size_of_polynomial; i++) {
        pending.coefss_of_polynomial[i] = -coefss_of_polynomial[i];
    }

    return pending;
}

Polynomial operator-(const Polynomial& new1, const Polynomial& new2) {

    Polynomial pending = new1;
    pending -= new2;

    return pending;
}

Polynomial Polynomial::operator+=(const Polynomial& another) {
    return defining_sign(*this, another, 1);
}

Polynomial Polynomial::operator-=(const Polynomial& another) {
    return defining_sign(*this, another, -1);
}

Polynomial operator*(const Polynomial& another, int num) {

    int* pendingcoefs = new int[another.size_of_polynomial];

    for (int i = 0; i < another.size_of_polynomial; i++) {
        pendingcoefs[i] = another.coefss_of_polynomial[i] * num;
    }

    return Polynomial(another.degs_of_polynomial[0], 
        another.degs_of_polynomial[another.size_of_polynomial - 1], pendingcoefs);
}

Polynomial operator*(int num, const Polynomial& another) {
    return another * num;
}

Polynomial operator*(const Polynomial& new1, const Polynomial& new2) {

    int pendingSize = new1.size_of_polynomial * new2.size_of_polynomial;
    int* pendingcoefs = new int[pendingSize], *pendingDegree = new int[pendingSize];

    int ordinal_num = 0;

    for (int i = 0; i < new1.size_of_polynomial; i++) {

        for (int j = 0; j < new2.size_of_polynomial; j++) {

            pendingcoefs[ordinal_num] = new1.coefss_of_polynomial[i] * new2.coefss_of_polynomial[j];
            pendingDegree[ordinal_num] = new1.degs_of_polynomial[i] + new2.degs_of_polynomial[j];
            ordinal_num++;
        }
    }

    int size = pendingDegree[pendingSize - 1] - pendingDegree[0] + 1;
    int* resultDegree = new int[size], *resultcoefs = new int[size];
    ordinal_num = pendingDegree[0];

    for (int i = 0; i < size; i++) {

        resultDegree[i] = ordinal_num;
        resultcoefs[i] = 0;
        ordinal_num++;
    }

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < pendingSize; j++) {

            if (pendingDegree[j] == resultDegree[i])
                resultcoefs[i] += pendingcoefs[j];
        }
    }

    return Polynomial(pendingDegree[0], pendingDegree[pendingSize - 1], resultcoefs);
}

Polynomial Polynomial::operator/(int num) {

    auto pending = *this;

    for_each(pending.coefss_of_polynomial, 
        pending.coefss_of_polynomial + pending.size_of_polynomial,      
        [&](int& n) { n /= num; });

    return pending;
}

Polynomial Polynomial::operator*=(const Polynomial& another) {

    *this = *this * another;

    return *this;
}

Polynomial Polynomial::operator/=(int num) {

    *this = *this / num;

    return *this;
}

int Polynomial::operator[](int num) const {

    if (num >= degs_of_polynomial[0] && num <= degs_of_polynomial[size_of_polynomial - 1]) {

        int ordinal_num = 0;

        for (int i = 0; i < size_of_polynomial; i++) {

            if (num == degs_of_polynomial[i]) {
                ordinal_num = i;
                break;
            }

        }

        return coefss_of_polynomial[ordinal_num];
    }

    else return 0;
}

int& Polynomial::operator[](int num) {

    if (num > degs_of_polynomial[0] && num < degs_of_polynomial[size_of_polynomial - 1]) {

        Polynomial other = *this;

        return other[num];
    }

    else if (num < degs_of_polynomial[0]) {

        int max = degs_of_polynomial[size_of_polynomial - 1];
        int min = num;
        int pendingSize = max - min + 1;

        int* pendingcoefs = new int[pendingSize];

        for (int i = 0; i < pendingSize; i++)
            pendingcoefs[i] = 0;

        for (int i = 1; i < size_of_polynomial; i++)
            pendingcoefs[pendingSize - i] = coefss_of_polynomial[size_of_polynomial - i];

        *this = Polynomial(min, max, pendingcoefs);

        return coefss_of_polynomial[0];
    }
    else {

        int max = num;
        int min = degs_of_polynomial[0];
        int pendingSize = max - min + 1;

        int* pendingcoefs = new int[pendingSize];

        for (int i = 0; i < pendingSize; i++)
            pendingcoefs[i] = 0;

        for (int i = 0; i < size_of_polynomial; i++)
            pendingcoefs[i] = coefss_of_polynomial[i];

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

                if (i < pendingSize - 1 && another.coefss_of_polynomial[i] > 0 
                    && !conclusion.str().empty() && conclusion.str().back() != '\n')
                    conclusion << "+";

                if (another.coefss_of_polynomial[i] == -1 && another.degs_of_polynomial[i] != 0)
                    conclusion << "-";

                else if (another.coefss_of_polynomial[i] == 1 && another.degs_of_polynomial[i] != 0) {}

                else
                    conclusion << another.coefss_of_polynomial[i];

                if (another.degs_of_polynomial[i] != 0) {
                    conclusion << "x";

                    if (another.degs_of_polynomial[i] != 1)
                        conclusion << "^" << another.degs_of_polynomial[i];
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

    double pending = coefss_of_polynomial[0] * pow(num, degs_of_polynomial[0]);
    double result = pending;

    for (int i = 1; i < size_of_polynomial; i++) {

        pending *= num;
        result += coefss_of_polynomial[i] * pending;
    }

    return result;
}