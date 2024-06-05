double d1 = (8, 1, 0.05);
double d2{false};
double d3((((0), 0), 0, (8.5)));
double d4('a');
double d5{'a'};
double d6{('b')};
double d7 = -'a';
double d8 = ++d7;

double foo(double k, int x)
{
    int t = x++;
    return k;
}

double funk()
{
    double d = 3.14;
    return d;
}

int main()
{
    double d9(foo(2.5, 5));
    double d10{};
    double d11;
    double d12 = 5;
    double d13 = false;
    double d14 = '\0';
    double d15 = (false);
    double d16{true};
    double d17('\0');
    double d18(true);

    if (5 < 6) {
        double d19(5);
        double d20(-458);
        double d21(((458)));
        double d22(false);
        double d23('\x2a');
        double d24{1};
        double d25{-true};
        double d26{((false))};
        double d27{('b')};
        double d28{(((-4875)))};
        double d29 = 789.50000;
    }

    if (7 == 7)
    {
        double d30 = -98.3;
        double d31 = (-45);
        double d32 = {-'a'};
        double d33 = {(5)};
        double d34 = {-true};
        double d35 = {(false)};
        double d36 = {'z'};
        double d37 = {((('z')))};
        double d38{foo(1.67, 6)};
        double d39 = funk();
        double d42 = 42e2;
        double d43 = 43e-2;
        double d44 = 44e0;
        double d45 = (1, 2, 3, 4, 5, 5.67f);
        double d46 = '\xa';
        double d47 = '\x7A';
        double d48 = '\21';
        double d49{'\33'};
        foo(25.5, 7);
    }
    if ()
    {
        double d50(50e3);
        double d51(-.51);
        double d52 = -.52;
        double d53 = .53;
        double d54 = +-+-+-+-+54.54000;
        double d55 = 1.7E309;
        double d56 = 000000000.56;
        double d57 = d56;
        double d58 = d58;
        double d59 = (5 + 2 * (5 * (5 + 4)));
        double d60 = -(60);
        double d61(4 + 6 * 3);
        double d62{4 + 6 * 3};
    }
    if (9 < 15) {
        double f = 5;
        f = 7;
        f += 1;
        f -= 2;
        f *= 3;
        f /= 4;
    }
    if ()
    {
        double a = 6;
        double d = !a;
        a = (45UL);
        a -= 9;
        a /= 3 + 3;
        a *= 4 - 2;
        a = 6, 7, 8;
    }

    return 0;
}
