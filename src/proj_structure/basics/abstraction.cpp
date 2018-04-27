//
// Created by josh reuben on 27/04/2018.
//

#include <initializer_list>
#include <list>
#include <algorithm>
#include <iostream>
#include "userdefinedtypes.h"

namespace concretetypes {
    namespace arithmatic {
        class complex {
            double re, im; // representation: two doubles
        public:
            complex(double r, double i) : re{r}, im{i} {}  // construct complex from two scalars
            complex(double r) : re{r}, im{0} {}            // construct complex from one scalar
            complex() : re{0}, im{0} {}                    // default complex: {0,0}

            // accessors
            double real() const { return re; }

            void real(double d) { re = d; }

            double imag() const { return im; }

            void imag(double d) { im = d; }

            complex &operator+=(complex z) {
                re += z.re, im += z.im;
                return *this;
            } // add to re and im and return the result
            complex &operator-=(complex z) {
                re -= z.re, im -= z.im;
                return *this;
            }

            complex &operator*=(complex);    // defined out-of-class somewhere
            complex &operator/=(complex);    // defined out-of-class somewhere
        };

        complex &complex::operator*=(complex) {
            // TODO:
            return *this;
        }

        complex &complex::operator/=(complex) {
            // TODO:
            return *this;
        }

        // these utils dont need access to class internals
        complex operator+(complex a, complex b) { return a += b; }

        complex operator-(complex a, complex b) { return a -= b; }

        complex operator-(complex a) { return {-a.real(), -a.imag()}; }    // unary minus
        complex operator*(complex a, complex b) { return a *= b; }

        complex operator/(complex a, complex b) { return a /= b; }

        bool operator==(complex a, complex b) {         // equal
            return a.real() == b.real() && a.imag() == b.imag();
        }

        bool operator!=(complex a, complex b) {       // not equal
            return !(a == b);
        }

        complex sqrt(complex);  // a function definition
        void f(complex z) {
            complex a{2.3};       // construct {2.3,0.0} from 2.3
            complex b{1 / a};
            complex c{a + z * complex{1, 2.3}};
            // ...
            if (c != b)
                c = -(b / a) + 2 * b;
        }
    }

    namespace initializingcontainer {
        class Vector {
        public:
            Vector(std::initializer_list<double>);     // initialize with a list
            ~Vector() { delete[] elem; }

            void push_back(double);    // add element at end increasing the size by one - note: cant use backing array pointer with this!
        private:
            double *elem; // pointer to the elements
            size_t sz;
        };

        Vector::Vector(std::initializer_list<double> lst) :
                elem{new double[lst.size()]},
                sz{lst.size()} {
            std::copy(lst.begin(), lst.end(), elem);          // copy from lst into elem
        }

        Vector v1 = {1, 2, 3, 4, 5};            // v1 has 5 elements
        Vector v2 = {1.23, 3.45, 6.7, 8};   // v2 has 4 elements


//        Vector read(std::istream& is) {
//            Vector v; // TODO: define ctor that doesnt take initialization list
//            for (double d; is >> d) {    // read floating-point values into d
//                v.push_back(d);      // add d to v
//            }
//            return v;
//        }


    }
}
namespace abstracttypes { // without generics
    class Container {
    public:
        virtual double& operator[](int) = 0;     // pure virtual function
        virtual int size() const = 0;
        virtual ~Container() {}
    };

    void use(Container& c) {
        const int sz = c.size();

        for (int i=0; i!=sz; ++i)
            std::cout << c[i] << '\n';
    }

    class Vector_container : public Container {
        classes::Vector v; // RAII - its dtor is implicitly invoked by container dtor
    public:
        Vector_container(unsigned int s) : v(s) { }  // Vector of s elements
        ~Vector_container() {} // overrides the base dtor

        // must overide the pure virtual functions:
        double& operator[](int i) { return v[i]; }
        int size() const { return v.size(); }
    };

    void g(){
        Vector_container vc {10};
        use(vc);
    }

    class List_container : public Container { // List_container implements Container
        std::list<double> ld;
    public:
        List_container() {}      // empty List
        List_container(std::initializer_list<double> il) : ld{il} { }
        ~List_container() {}
        double& operator[](int i);
        int size() const { return ld.size(); }
    };

    double& List_container::operator[](int i)
    {
        for (auto& x : ld) { // interesting: iterate through list, decrementing counter until ith item
            if (i==0) return x;
            --i;
        }
        throw std::out_of_range("List container");
    }

    void h() {
        List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        use(lc);
    }

}