//
// Created by josh reuben on 30/04/2018.
//
#include <string>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace iter_traits {

    template<typename Ran>                                              // for random-access iterators
    void sort_helper(Ran beg, Ran end, std::random_access_iterator_tag)      // we can subscript into [beg:end)
    {
        std::sort(beg,end);     // just sort it
    }
    template<typename For>                                       // for forward iterators
    void sort_helper(For beg, For end, std::forward_iterator_tag)     // we can traverse [beg:end)
    {
        std::vector<decltype(*beg)> v {beg,end};    // initialize a vector from [beg:end)
        sort(v.begin(),v.end());
        copy(v.begin(),v.end(),beg);           // copy the elements back
    }
    template<typename C>
    using Iterator_type = typename C::iterator;   // C's iterator type

    template<typename Iter>
    using Iterator_category = typename std::iterator_traits<Iter>::iterator_category;  // Iter's category

    template<typename C>
    void sort(C& c)
    {
        using Iter = Iterator_type<C>;
        sort_helper(c.begin(),c.end(), Iterator_category<Iter>{});
    }

    void test(std::vector<std::string>& v, std::forward_list<int>& lst) {
        //  sort(v);    // sort the vector
        //  error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >' if (__i == --__j)
//         sort(lst);  // sort the singly-linked list - sort requires random access iterator not forward iterator
    }
}

namespace typetraits {
    template<typename T>
    constexpr bool Is_arithmetic() {
        return std::is_arithmetic<T>::value ;
    }

    bool b1 = Is_arithmetic<int>();     // yes, int is an arithmetic type
    bool b2 = Is_arithmetic<std::string>();  // no, std::string is not an arithmetic type

    template<typename T>
    class C {
        T re, im;
    public:
        static_assert(Is_arithmetic<T>(), "Sorry, I only support  arithmetic types");
        // ...
    };

    C<int> c1;
//    C<std::string> c2; // <- cause blow up of static_assert at compile time

}
