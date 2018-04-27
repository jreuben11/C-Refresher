//
// Created by josh reuben on 27/04/2018.
//

#include <iostream>

namespace structs {

    struct Vector {
        int sz;     // number of elements
        double *elem; // pointer to elements
    };

    void vector_init(Vector &v, int s) {    // - note: ref param
        v.elem = new double[s]; // allocate an array of s doubles
        v.sz = s;
    }

    double read_and_sum(int s) {
        // read s integers from cin and return their sum; s is assumed to be positive
        Vector v;
        vector_init(v, s);       // allocate s elements for v
        for (int i = 0; i != s; ++i)
            std::cin >> v.elem[i];    // read into elements

        double sum = 0;
        for (int i = 0; i != s; ++i)
            sum += v.elem[i];
        return sum;
    }

    void f(Vector v, Vector &rv, Vector *pv) {
        int i1 = v.sz;     // access through name
        int i2 = rv.sz;    // access through reference
        int i4 = pv->sz;   // access through pointer
    }
}

namespace classes {
    class Vector { // handle
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
    private:
        double* elem; // pointer to the elements
        int sz;       // the number of elements
    };

    Vector::Vector(int s) :elem{new double[s]}, sz{s} { }  // - note: init lists

    double &Vector::operator[](int i)  // - note: operator returns ref
    {
        if (i<0 || size()<=i) throw std::out_of_range{"Vector::operator[]"};
        return elem[i]; // element access operator: subscripting
    }

    int Vector::size() { return sz; }

    double read_and_sum(int s){
        Vector v(s);                     // make a vector of s elements
        for (int i=0; i!=v.size(); ++i)
            std::cin>>v[i];                 // read into elements

        double sum = 0;
        for (int i=0; i!=v.size(); ++i)
            sum+=v[i];                 // take the sum of the elements
        return sum;
    }

    void f(Vector& v) {
        try {

            v[v.size()] = 7; // try to access beyond the end of v
        } catch (std::out_of_range) {
            // ... handle range error ...
        }
        // ...
    }
}

namespace enums {
    enum class Color { red, blue, green };
    enum class Traffic_light { green, yellow, red };

    Color col = Color::red;
    Traffic_light light = Traffic_light::red;

    Traffic_light& operator++(Traffic_light& t) { // prefix increment: ++ - note: takes a ref and returns a ref
        switch (t) {
            case Traffic_light::green:    return t=Traffic_light::yellow;
            case Traffic_light::yellow:   return t=Traffic_light::red;
            case Traffic_light::red:      return t=Traffic_light::green;
        }
    }

    Traffic_light next = ++light;       // next becomes Traffic_light::green
}