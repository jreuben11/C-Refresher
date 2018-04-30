//
// Created by josh reuben on 28/04/2018.
//
#include <stdexcept>
#include <list>
#include <forward_list>

#include <string>
#include <iostream>
#include <complex>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <utility>
#include <regex>
#include <numeric>
#include <random>
#include <valarray>


class Record;

using namespace std;

namespace strings {
    string compose(const string& name, const string& domain) {
        return name + '@' + domain;
    }
    auto addr = compose("dmr","bell-labs.com");

    void m2(string& s1, string& s2) {
        s1 = s1 + '\n';   // append newline
        s2 += '\n';       // append newline
    }

    string name = "Niels Stroustrup";

    void m3() {
        string s = name.substr(6,10);    // s = "Stroustrup"
        name.replace(0,5,"nicholas");    // name becomes "nicholas Stroustrup"
        name[0] = toupper(name[0]);      // name becomes "Nicholas Stroustrup"
    }
}

namespace streams {

    struct Entry {
        string name;
        int number;
        bool operator< (const Entry& rhs) const { // required for sort !
            return this->number < rhs.number;
        }
        bool operator== (const Entry& rhs) const { // required for unique_copy !
            return this->number == rhs.number && this->name == rhs.name;
        }
    };

    ostream &operator<<(ostream &os, const Entry &e)  {
        return os << "{\"" << e.name << "\", " << e.number << "}";
    }

    istream &operator>>(istream &is, Entry &e) {
        // read { "name" , number } pair. Note: formatted with { " " , and }
        char c, c2;
        if (is >> c && c == '{' && is >> c2 && c2 == ' ') { // start with a { "
            string name;                   // the default value of a string is the empty string: ""
            while (is.get(c) && c != '"')    // anything before a " is part of the name
                name += c;

            if (is >> c && c == ',') {
                int number = 0;
                if (is >> number >> c && c == '}') { // read the number and a }
                    e = {name, number};      // assign to the entry
                    return is;
                }
            }
        }
        is.setf(ios_base::failbit);     // register the failure in the stream
        return is;
    }

    void f() {
        for (Entry ee; cin >> ee;)  // read from cin into ee
            cout << ee << '\n';   // write ee to cout
    }



    void print_book(const vector<Entry>& book) {
        for (int i = 0; i!=book.size(); ++i)
            cout << book[i] << '\n';
    }

    void print_book2(const vector<Entry>& book) {
        for (const auto& x : book)
            cout << x << '\n';
    }

    int interatorStreams() {
        string from, to;
        cin >> from >> to;                     // get source and target file names


        ifstream is {from};                    // input stream for file "from"
        istream_iterator<string> ii {is};      // input iterator for stream
        istream_iterator<string> eos {};       // input sentinel


        ofstream os{to};                       // output stream for file "to"
        ostream_iterator<string> oo {os,"\n"}; // output iterator for stream

        vector<string> b {ii,eos};             // b is a vector initialized from input [ii:eos)
        sort(b.begin(),b.end());               // sort the buffer


        unique_copy(b.begin(),b.end(),oo);     // copy buffer to output, discard replicated values
        return !is.eof() || !os;               // return error state (§2.2.1, §38.3)
    }
}

namespace containers {
    using streams::Entry;

    vector<Entry> v_phone_book = {
            {"David Hume",123456},
            {"Karl Popper",234567},
            {"Bertrand Arthur William Russell",345678}
    };

    list<Entry> l_phone_book = {
            {"David Hume",123456},
            {"Karl Popper",234567},
            {"Bertrand Arthur William Russell",345678}
    };

    map<string,int> m_phone_book {
            {"David Hume",123456},
            {"Karl Popper",234567},
            {"Bertrand Arthur William Russell",345678}
    };

    int get_number(const string& s) {
        for (auto p = l_phone_book.begin(); p!=l_phone_book.end(); ++p)
            if (p->name==s)
                return p->number;
        return 0; // use 0 to represent "number not found"
    }

    int get_number2(const string& s) {
        return m_phone_book[s];
    }

    void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q) {
        l_phone_book.insert(p,ee);       // add ee before the element referred to by p
        l_phone_book.erase(q);           // remove the element referred to by q
    }

    list<Entry> f(vector<Entry>& vec) {
        list<Entry> res;
        sort(vec.begin(),vec.end());        // requires bool operator< (const Entry& rhs) const;
        unique_copy(vec.begin(),vec.end(),back_inserter(res));  // requires bool operator== (const Entry& rhs) const
        return res;
    }

    bool has_c(const string& s, char c) {    // does s contain the character c?
        return find(s.begin(),s.end(),c)!=s.end();
    }


    template<typename C, typename V>
    vector<typename C::iterator> find_all(C& c, V v)     // find all occurrences of v in c
    {
        vector<typename C::iterator> res;
        for (auto p = c.begin(); p!=c.end(); ++p) {
            if (*p==v) {
                res.push_back(p);
            }
        }
        return res;

    }

    template<typename T>
    using Iterator = typename T::iterator;

    template<typename C, typename V>
    vector<Iterator<C>> find_all2(C& c, V v)     // find all occurrences of v in c
    {
        vector<Iterator<C>> res;
        for (auto p = c.begin(); p!=c.end(); ++p)
            if (*p==v)
                res.push_back(p);
        return res;
    }

    void test() {
        string m {"Mary had a little lamb"};
        for (auto p : find_all2(m,'a'))
            if (*p!='a')
                cerr << "a bug!\n";
        auto a = {1,2,3,4,5};
        for (auto p : find_all2(a,6))
            if (*p!='a')
                cerr << "a bug!\n";
    }
}

namespace algos {
    struct Greater_than { // functor
        int val;
        Greater_than(int v) : val{v} { }
        bool operator()(const pair<string,int>& r) { return r.second>val; }
    };

    void predicates(map<string,int>& m) {
        auto p = find_if(m.begin(),m.end(), Greater_than{42}); //take functor
        int cxx = count_if(m.begin(), m.end(), [](const pair<string,int>& r) { return r.second>42; }); // take lambda
    }
}

namespace smartpointers {
    using namespace std;
    class No_file {};
    void f(shared_ptr<fstream>){}
    void g(shared_ptr<fstream>){}

    void user(const string& name, ios_base::openmode mode)
    {
        shared_ptr<fstream> fp {new fstream(name,mode)};
        if (!*fp) throw No_file{}; // make sure the file was properly opened

        f(fp);
        g(fp);
        // ...
    }
}

namespace utils {
    void stopwatch(){
        using namespace std::chrono;      // see §35.2
        auto t0 = high_resolution_clock::now();
        // do_work();
        auto t1 = high_resolution_clock::now();
        cout << duration_cast<milliseconds>(t1-t0).count() << "msec\n";
    }

    void typefuncs(){
        constexpr float min = numeric_limits<float>::min();    // smallest positive float (§40.2)
        constexpr int szi = sizeof(int);
    }

    void f() {
        regex pat(R"(\w{2}\s*\d{5}(-\d{4})?)"); // ZIP code pattern: XXddddd-dddd and variants
        int lineno = 0;
        for (string line; getline(cin,line);) {           // read into line buffer
            ++lineno;
            smatch matches;                             // matched strings go here
            if (regex_search(line,matches,pat))         // search for pat in line
                cout << lineno << ": " << matches[0] << '\n';
        }
    }
}

namespace pairAndTuple {
    class Record {
    public:
        string name;
    };

    ostream &operator<<(ostream &os, const Record &e)  { // required for equal_range
        return os <<  e.name ;
    }

    auto rec_eq = [](const Record& r1, const Record& r2) { return r1.name<r2.name;};// define a lambda to compare names

    void f(const vector<Record>& v)     // assume that v is sorted on its "name" field
    {
        auto er = std::equal_range(v.begin(),v.end(),Record{"Reg"},rec_eq);
        for (auto p = er.first; p!=er.second; ++p)    // print all equal records
            cout << *p;                             // assume that << is defined for Record
    }

    pair<vector<string>::iterator,int> f(vector<string>& v) {
        auto pp = make_pair(v.begin(),2);
        // ...
        return pp;
    }

    void f(){
        tuple<string,int,double> t2("Sild",123, 3.14); // the type is explicitly specified

        auto t = make_tuple(string("Herring"),10, 1.23); // the type is deduced as a tuple<string,int,double>

        string s = get<0>(t); // get first element of tuple
        int x = get<1>(t);
        double d = get<2>(t);
    }
}

namespace numerics {
    void f() {
        list<double> lst {1, 2, 3, 4, 5, 9999.99999};
        auto s = accumulate(lst.begin(),lst.end(),0.0); // calculate the sum
        cout << s << '\n';                              // print 10014.9999
    }

    void f(complex<double> c1, complex<double> c2) {
        complex<long double> ld {c1 + sqrt(c2)};
        c2 += c1 * 3.;
        c1 = pow(1. / c1, 2.);
        // ...
    }

    auto die = bind(uniform_int_distribution<>{1,6}, default_random_engine{}); // random

    class Rand_int {
    public:
        Rand_int(int low, int high) :dist{low,high} { }
        int operator()() { return dist(re); }     // draw an int
    private:
        default_random_engine re;
        uniform_int_distribution<> dist;
    };

    Rand_int rnd {1,10};               // make a random number generator for [1:10]
    int x = rnd();      // x is a number in [1:10]

    void f(valarray<double>& a1, valarray<double>& a2) {
        valarray<double> a = a1 * 3.14 + a2 / a1;      // numeric array operators *, +, /, and =
        a2 += a1 * 3.14;
        a = abs(a);
        double d = a2[7];
        // ...
    }
}




