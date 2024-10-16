
#include "classes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of Object

Object:: Object(Point& p, char t) : pos(p), type(t) {}

Object:: ~Object(){}

Point Object:: get_pos() const { return pos; }

char Object:: get_type() const { return type; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
