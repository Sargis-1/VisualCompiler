short x;
short x1(9 + 8 + 6);
short x2(-458);
short x3((((458))));
short x4(true);

short foo(int x, int y, bool flag = true)
{
    return x + y;
}
int main()
{
    short x5(false);
    short x6('a');
    short x7(89ULL);
    short x8(9ull);
    short x9(((5.5f)));
    short x10(-(+5));
    short x11(-(5 - 9));
    short x12(+-+8);
    if (true) {
        short y{};
        short y1{1};
        short y2{-true};
        short y3{false};
        short y4{((false))};
        short y5{'a'};
        short y6{('b')};
        short y7{(((-4875)))};
        short y8{3u};
        short y9{78ul};
        short y11{12ull};
        short y12{1 + 2};
        short y13{(4 + 4)};
        short y14{(((8 + 4 + 3)))};
        short y15{-(-(+5))};
        short y16{(((-(((-(-4)))))))};
        short y17{+-+-(-+(-8 + 2))};
     }
     if (true) {
        short z1 = -98;
        short z2 = 'a';
        short z3 = -'a';
        short z4 = false;
        short z5 = (-45);
        short z6 = {-'a'};
        short z7 = {(5)};
        short z8 = {-true};
        short z9 = {(false)};
        short z11 = {'z'};
        short z12 = {((('z')))};
        short z13 = (15.2f);
        short z14 = (12ull);
     }
     if (true) {
        short z15 = (-45u);
        short z16 = (456UL);
        short z17 = (((987LL)));
        short z18 = 4 + 5;
        short z19 = (4 + 4);
        short z20 = {1 + 3};
        short z21 = {(2 + 3)};
        short z23 = -(-(+5));
        short z24 = {-(-(+5))};
        short z25 = +-+-+(4);
    }
    if (true) {
        short a = 32;
        short b = ++a;
        short c = a++;
        short d = !a;
        short e = ~a;
    }
    if (true) {
        short f = 5;
        f = 6;
        f += ++a;
        f -= 2;
        f *= 3;
        f /= 4;
        f %= 5;
        f |= 6;
        f &= 7;
        f ^= 8;
        f <<= 9;
        f >>= 1;
    }
    if (3) {
        short k = 1;;
        k = (456UL);
        k += (((987LL)));
        k *= 4 + 5;
        k %= (4 + 4);
        k &= {1 + 3};
        k /= {(2 + 3)};
        k |= -(-(+5));
        k ^= {-(-(+5))};
        k = +-+-+(4);
   }
   if (true) {
       short x = 10;
       x = 2 + 3, (4 * 4), +-+-5;
       x = 555, ++x;
       short y = foo(1, 4);
       short z = +-+-foo(10, 10);
       y = -(-(-foo(3, 3)));
   }
}
