#include <cstdint>

#ifndef _FRACTION_H
#define _FRACTION_H

#include <iostream>

class Fraction {
public:
    static int gcd(int a,int b) {
        int
                r;

        a = (a >= 0) ? a : -a;
        b = (b >= 0) ? b : -b;

        while (b != 0) {
            r = a % b;
            a = b;
            b = r;
        }

        return a;
    }

    explicit Fraction(int32_t n=0,int32_t d=1){
        int
                g;

        if (d < 0) {
            n = -n;
            d = -d;
        }

        g = gcd(n,d);

        num = n / g;
        den = d / g;
    }
    ~Fraction() = default;

    Fraction& operator=(Fraction rhs){
        num = rhs.num;
        den = rhs.den;

        return *this;
    }

    Fraction operator+(Fraction rhs) const {
        int
                n,d;

        n = num * rhs.den + den * rhs.num;
        d = den * rhs.den;

        return Fraction(n,d);
    }

    Fraction operator-(Fraction rhs) const {
        int
                n,d;

        n = num * rhs.den - den * rhs.num;
        d = den * rhs.den;

        return Fraction(n,d);
    }

    Fraction operator*(Fraction rhs) const {
        int
                n,d;

        n = num * rhs.num;
        d = den * rhs.den;

        return Fraction(n,d);
    }

    Fraction operator/(Fraction rhs) const {
        int
                n,d;

        n = num * rhs.den;
        d = den * rhs.num;

        return Fraction(n,d);
    }

    bool operator==(Fraction rhs) const {
        return num == rhs.num && den == rhs.den;
    }

    bool operator!=(Fraction rhs) const {
        return num != rhs.num || den != rhs.den;
    }

    bool operator<=(Fraction rhs) const {
        return num * rhs.den <= den * rhs.num;
    }

    bool operator>=(Fraction rhs) const {
        return num * rhs.den >= den * rhs.num;
    }

    bool operator<(Fraction rhs) const {
        return num * rhs.den < den * rhs.num;
    }

    bool operator>(Fraction rhs) const {
        return num * rhs.den > den * rhs.num;
    }

    [[nodiscard]] int32_t getNum() const { return num; }
    [[nodiscard]] int32_t getDen() const { return den; }

private:
    int
            num,
            den;
};

std::istream &operator>>(std::istream &is,Fraction &f) {
    int
            n,d;
    char
            slash;

    is >> n >> slash >> d;

    f = Fraction(n,d);

    return is;
}
std::ostream &operator<<(std::ostream &os,Fraction f) {
    os << f.getNum() << " / " << f.getDen();

    return os;
}

#endif