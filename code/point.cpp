
#include "classes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of a 2D point 

Point:: Point(int a, int b) : x(a) , y(b) {}

Point:: ~Point() {}

void Point:: set_x(int a){ x = a; }

int Point:: get_x() const { return x;}

void Point:: set_y(int b) { y = b;}

int Point:: get_y() const { return y;}

void Point:: set_point(int a , int b) {
	x=a;
	y=b;
}

void Point:: set_point(Point& p) {
	x = p.get_x();
	y = p.get_y();
}

void Point:: print_point() const { cout <<"("<< x << "," << y << ")" ; }

//Overloading the "==" operator so we can use it between two objects of the point class
//to see if they are the same

bool operator==(Point const& p1, Point const& p2) {

	if ( (p1.get_x() == p2.get_x()) && (p1.get_y() == p2.get_y()) )
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
