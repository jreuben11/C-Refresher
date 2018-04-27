//
// Created by josh reuben on 16/04/2018.
//
#include "file0.h"
extern int x; // defined in file1. without extern, get ld duplicate symbol
void g() { x = f(); }