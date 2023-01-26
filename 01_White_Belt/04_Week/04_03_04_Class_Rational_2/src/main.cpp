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

        /*
                // если числитель и знаменатель отрицательные
                if (p < 0 && q < 0)
                {
                    p = -p;
                    q = -q;
                }
                // если числитель отрицательный
                else if (p < 0 && q > 0)
                {
                    p = -p;
                    negativ = true;
                }
                // если знаменатель отрицательный
                else if (p > 0 && q < 0)
                {
                    q = -q;
                    negativ = true;
                }

                if (p == 0)
                {
                    q = 1;
                }
                else if (q % p == 0)
                {
                    q = q / p;
                    p = 1;
                }
                else
                {
                    for (int i = 2; i < q / 2; i++)
                    {
                        while ((p % i == 0) && (q % i == 0))
                        {
                            p /= i;
                            q /= i;
                        }
                    }
                }

                if (negativ)
                {
                    p = -p;
                }
                */
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

int main()
{
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
