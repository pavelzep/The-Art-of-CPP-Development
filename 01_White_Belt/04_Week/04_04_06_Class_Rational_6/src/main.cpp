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
            throw invalid_argument("denominator is null");
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

    try
    {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument &)
    {
    }

    try
    {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error &)
    {
    }

    /*
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3)
        {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs)
        {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}})
        {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2)
        {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
*/
    /*
    Rational r ,t;
    cin >> r >> t;
    cout << r << ' '<< t << endl;
    */

    /*
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4")
        {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal)
        {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

*/

    /*
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
    */
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
/*
{
    set<Rational> rationals;
    rationals.insert(Rational(1, 2));
    rationals.insert(Rational(1, 3));

    map<Rational, string> name;
    name[Rational(1, 2)] = "одна вторая";
}
*/

cout << "OK" << endl;
return 0;
}
