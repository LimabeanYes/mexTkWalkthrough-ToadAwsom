#include "mex.h"
// ^ Include the mex.h file to get access to all of the mextk headers and functions
// This isn't something you need to fully understand when starting to make code mods so
// just include it for now and take it step by step


// Function signatures for the functions that are defined in special_lw.c
// This is so that the files know that the functions exist and it helps the compiler
void specialLw_iasaCallback(GOBJ* gobj);
void specialAirLw_iasaCallback(GOBJ* gobj);
