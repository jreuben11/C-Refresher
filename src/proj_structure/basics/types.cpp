//
// Created by josh reuben on 27/04/2018.
//

#include <vector>
#include <complex>
#include <iostream>

using namespace std;

namespace Initializations {
    double d1 = 2.3;
    double d2 {2.3};

    complex<double> z = 1;              // a complex number with double-precision floating-point scalars
    complex<double> z2 {d1,d2};
    complex<double> z3 = {1,2};         // the = is optional with { ... }

    vector<int> v {1,2,3,4,5,6};


    //int i1 = 7.2;       // warning: implicit conversion -  i1 becomes 7
    //int i2 {7.2};       // error: floating-point to integer conversion
    //int i3 = {7.2};     // error: floating-point to integer conversion (the = is redundant)

    auto k = 5.5;
}

namespace ConstExpressions {
    double square(double x)  {
        return x*x;
    }
    constexpr double constSquare(double x) {
        return x*x;
    }

    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4 * constSquare(dmv);    // OK - constsquare(17) is a constant expression
//    constexpr double max2 = 1.4 * square(var);    // error: var is not a constant expression
    const double max3 = 1.4 * square(var);
    double sum(const vector<double>&);          // sum will not modify its argument (§2.2.5)
    vector<double> v {1.2, 3.4, 4.5};
//    const double s1 = sum(v);                   // OK: evaluated at run time, but linker: undefined-internal
//    constexpr double s2 = sum(v);               // error: sum(v) not constant expression
    auto ii = constSquare(5);                     //OK
}

namespace PointerArrays {
    char v[6];          // array of 6 characters
    char* p = &v[3];    // p points to address-of v's fourth element
    char x = *p;        // x is contents-of

    void print() {
        int v[] = {0,1,2,3,4,5,6,7,8,9};
        for (auto& x : v)            // for each x in v
            cout << x << '\n';
        for (auto& x : {10,21,32,43,54,65}) // literal array
            cout << x << '\n';

    }
}

namespace assertions {
    constexpr double C = 299792.458;                        // km/s

    void f(double speed)
    {
        constexpr double local_max = 160.0/(60*60);            // 160 km/h
        // static_assert(speed < C, "can't go that fast");       // error: speed must be a constexpr, not variable or constant
        static_assert(C > local_max, "can't go that fast");   // OK
        // ...
    }
}






