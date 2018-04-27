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

    private:
        double *elem; // pointer to the elements
        unsigned int sz;       // the number of elements
    };

}
#endif //LANGUAGE_FEATURES_USERDEFINEDTYPES_H
