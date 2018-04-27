//
// Created by josh reuben on 17/04/2018.
//
#ifdef __cplusplus      // for C++ compilers only (§15.2.5)
namespace std {         // the standard library is defined in namespace std (§4.1.2)
extern "C" {            // stdio functions have C linkage (§15.2.5)
#endif
    /* ... */
    int printf(const char*, ...);
    /* ... */
#ifdef __cplusplus
}
}
// ...
using std::printf; // make printf available in global namespace
// ...
#endif

//const char *ss = "xxx";
//printf(ss);