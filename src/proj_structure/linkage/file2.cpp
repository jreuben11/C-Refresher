//
// Created by josh reuben on 16/04/2018.
//

extern int x; // defined in file1. without extern, get ld duplicate symbol
int f();
void g() { x = f(); }