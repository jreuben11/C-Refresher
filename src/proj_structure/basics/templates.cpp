//
// Created by josh reuben on 27/04/2018.
//

#include <stdexcept>
#include <list>
#include <string>
#include <iostream>
#include <complex>
#include <vector>


namespace classtemplates {

    class Negative_size {};

    template<typename T>
    class Vector {
    private:
        T* elem; // elem points to an array of sz elements of type T
        int sz;
    public:
        using value_type = T;
        Vector(int s);                  // constructor: establish invariant, acquire resources
        ~Vector() { delete[] elem; }    // destructor: release resources

        // ... copy and move operations ...

        T& operator[](int i);
        const T& operator[](int i) const;
        int size() const { return sz; }

    };

    template<typename T>
    Vector<T>::Vector(int s) {
        if (s<0) throw Negative_size{};
        elem = new T[s];
        sz = s;
    }

    template<typename T>
    const T& Vector<T>::operator[](int i) const {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }

    Vector<char> vc(200);      // vector of 200 characters
    Vector<std::string> vs(17);     // vector of 17 strings
    Vector<std::list<int>> vli(45); // vector of 45 lists of integers

    void f1(const Vector<std::string>& vs) {     // function that takes Vector of some strings
        for (int i = 0; i!=vs.size(); ++i)
            std::cout << vs[i] << '\n';
    }

    // dumb "iterators":
    template<typename T>
    const T* begin(const Vector<T>& x){
        return &x[0];          // pointer to first element
    }

    template<typename T>
    const T* end(const Vector<T>& x){
        return begin(x) + x.size(); // pointer to one-past-last element
    }

    void f2(const Vector<std::string>& vs) {     // function that takes Vector of some strings
        for(auto s = begin(vs); s != end(vs); ++s)
            std::cout << s << '\n';
    }


    void f3(const Vector<std::string>& vs) {     // function that takes Vector of some strings
        for (auto& s : vs)
            std::cout << s << '\n';
    }

    template<typename C>
    using Element_type = typename C::value_type;

    template<typename Container>
    void algo(Container& c)
    {
        Vector<Element_type<Container>> vec; // keep results here
        // ...
    }

    template<typename Key, typename Value>
    class Map {
        // ...
    };

    template<typename Value>
    using String_map = Map<std::string,Value>;

    String_map<int> m; // m is a Map<string,int>

}

namespace functemplates {
    template<typename Container, typename Value>
    Value sum(const Container& c, Value v) {
        for (auto x : c)
            v+=x;
        return v;
    }


    using classtemplates::Vector;

    void user(Vector<int>& vi, std::list<double>& ld, std::vector<std::complex<double>>& vc) {
        int x = sum(vi,0);                  // the sum of a vector of ints (add ints)
        double d = sum(vi,0.0);             // the sum of a vector of ints (add doubles)
        double dd = sum(ld,0.0);            // the sum of a list of doubles
        auto z = sum(vc, std::complex<double>{}); // the sum of a vector of complex<double>
        // the initial value is {0.0,0.0}
    }

    // functor:
    template<typename T>
    class Less_than {
        const T val;     // value to compare against
    public:
        Less_than(const T& v) :val(v) { }
        bool operator()(const T& x) const { return x < val; } // call operator
    };

    void user(int n, const std::string & s) {
        Less_than<int> lti{42};          // lti(i) will compare i to 42 using < (i<42)
        Less_than<std::string> lts{"Backus"}; // lts(s) will compare s to "Backus" using < (s<"Backus")
        bool b1 = lti(n);
        bool b2 = lts(s);
    }

    template<typename C, typename P>
    int count(const C& c, P pred) {
        int cnt = 0;
        for (const auto& x : c)
            if (pred(x))
                ++cnt;
        return cnt;
    }

    void policyFunctors(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
        std::cout << "number of values less than " << x
             << ": " << count(vec,Less_than<int>{x})
             << '\n';
        std::cout << "number of values less than " << s
             << ": " << count(lst,Less_than<std::string>{s})
             << '\n';
    }

    void policyLambdas(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
        std::cout << "number of values less than " << x
             << ": " << count(vec,[&](int a){ return a<x; })
             << '\n';
        std::cout << "number of values less than " << s
             << ": " << count(lst,[&](const std::string& a){ return a<s; })
             << '\n';
    }

}

namespace variadictemplates {
    template<typename T>
    void g(T x) {
        std::cout << x << " ";
    }
    void f() { }     // do nothing when params finish

    template<typename T, typename... Tail>
    void f(T head, Tail... tail)
    {
        g(head);    // do something to head
        f(tail...); // try again with tail - recursive
    }

    void use() {
        std::cout << "first: ";
        f(1,2.2,"hello");

        std::cout << "\nsecond: ";
        f(0.2,'c',"yuck!",0,1,2);
        std::cout << "\n";
    }
}