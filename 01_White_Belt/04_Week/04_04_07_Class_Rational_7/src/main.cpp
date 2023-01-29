#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <exception>
using namespace std;

class Rational
{
public:
    Rational()
    {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator)
    {
        p = numerator;
        q = denominator;
        if (q == 0)
        {
            throw invalid_argument("Invalid argument");
        }
        int gcd = GCD(p, q);
        p /= gcd;
        q /= gcd;
        if (q < 0)
        {
            p = -p;
            q = -q;
        }
    }

    int Numerator() const
    {
        return p;
    }

    int Denominator() const
    {
        return q;
    }

private:
    int p;
    int q;

    int GCD(int a, int b)
    {
        return b ? GCD(b, a % b) : a;
    }
};

Rational operator+(const Rational &a, const Rational &b)
{
    return Rational(a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
}

Rational operator-(const Rational &a, const Rational &b)
{
    return Rational(a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
}

bool operator==(const Rational &a, const Rational &b)
{
    return (a.Denominator() == b.Denominator() && a.Numerator() == b.Numerator()) ? (true) : false;
}

Rational operator*(const Rational &a, const Rational &b)
{
    return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
}

Rational operator/(const Rational &a, const Rational &b)
{
    if (b.Numerator() == 0)
    {
        throw domain_error("Division by zero");
    }
    return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
}

ostream &operator<<(ostream &stream, const Rational &a)
{
    stream << a.Numerator() << '/' << a.Denominator();
    return stream;
}

istream &operator>>(istream &stream, Rational &a)
{
    if (stream)
    {
        int p = a.Numerator();
        int q = a.Denominator();
        char s;
        stream >> p >> s >> q;
        if (s == '/')
        {
            a = Rational(p, q);
        }
    }
    return stream;
}

bool operator<(const Rational &a, const Rational &b)
{
    return (a - b).Numerator() < 0;
}

int main()
{
    Rational a, b, rez;
    char c;
    try
    {
        cin >> a >> c >> b;
    }
    catch (invalid_argument &ex)
    {
        cout << ex.what();
        return 0;
    }
    switch (c)
    {
    case '+':
        rez = a + b;
        break;

    case '-':
        rez = a - b;
        break;

    case '*':
        rez = a * b;
        break;

    case '/':
        try
        {
            rez = a / b;
        }
        catch (domain_error &ex)
        {
            cout << ex.what();
            return 0;
        }
        break;

    default:
        break;
    }

    cout << rez;
    return 0;
}
