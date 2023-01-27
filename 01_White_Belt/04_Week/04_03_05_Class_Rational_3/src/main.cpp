#include <iostream>
#include <iomanip>
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
    return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
}


int main()

{
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal)
        {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal)
        {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }
    /*
        {
            Rational r1(4, 6);
            Rational r2(2, 3);
            bool equal = r1 == r2;
            if (!equal)
            {
                cout << "4/6 != 2/3" << endl;
                return 1;
            }
        }

        {
            Rational a(2, 3);
            Rational b(4, 3);
            Rational c = a + b;
            bool equal = c == Rational(2, 1);
            if (!equal)
            {
                cout << "2/3 + 4/3 != 2" << endl;
                return 2;
            }
        }

        {
            Rational a(5, 7);
            Rational b(2, 9);
            Rational c = a - b;
            bool equal = c == Rational(31, 63);
            if (!equal)
            {
                cout << "5/7 - 2/9 != 31/63" << endl;
                return 3;
            }
        }
        */
    /*
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10)
        {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3)
        {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3)
        {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3)
        {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1)
        {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1)
        {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }
    */
    /*
        {
            const Rational r(-2, -3);
            if (r.Numerator() != 2 || r.Denominator() != 3)
            {
                cout << "Rational(-2, -3) != 2/3" << endl;
                return 6;
            }
        }

        {

            int p = -2;
            int q = 1;
            cout << endl <<setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
        {

            int p = -2;
            int q = -3;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }

        {

            int p = 1;
            int q = -3;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }

        {

            int p = 0;
            int q = -3;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
        {

            int p = 0;
            int q = 3;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
        {

            int p = 10;
            int q = 2;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
        {

            int p = 8;
            int q = -2;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }

        {
            int p = 45;
            int q = 90;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }

        {
            int p = 24;
            int q = 48;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
        {
            int p = 11;
            int q = 121;
            cout << setw(5) << p << setw(5) << q << endl;
            const Rational r(p, q);
            cout << setw(5) << r.Numerator() << setw(5) << r.Denominator() << endl << endl;
        }
    */
    cout << "OK" << endl;
    return 0;
}
