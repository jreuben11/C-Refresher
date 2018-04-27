//
// Created by josh reuben on 27/04/2018.
//

#ifndef LANGUAGE_FEATURES_USERDEFINEDTYPES_H
#define LANGUAGE_FEATURES_USERDEFINEDTYPES_H
namespace classes {
    class Vector { // handle for use in RAII
    public:
        Vector(unsigned int s);
        ~Vector();

        double &operator[](int i);
        unsigned int size() const;

        Vector(const Vector& a);             // copy constructor
        Vector& operator=(const Vector& a);  // copy assignment

        Vector(Vector&& a);               // move constructor
        Vector& operator=(Vector&& a);          // move assignment

    private:
        unsigned int sz;       // the number of elements
        double *elem; // pointer to the elements
    };

}
#endif //LANGUAGE_FEATURES_USERDEFINEDTYPES_H
