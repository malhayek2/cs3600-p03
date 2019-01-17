
#ifndef _CIRCLE_H
#define _CIRCLE_H

#include <iostream>
#include <vector>
#include <GL/freeglut.h>

class Circle
{

public:
    Circle(double x, double y, double radius, double dx, double dy, double red, double green, double blue);
    void update(int i, double screenX, double screenY, std::vector<Circle *>circles);
    void draw();
    double getx();
	double gety();
	double getradius();
	double getr();
	double getg();
	double getb();
	double getdx();
	double getdy();
	double getnextx();
	double getnexty();
	void setdx(double dx);
	void setdy(double dy);
    //bool _isRed;

private:
    double x, y, radius, dx, dy, red, green, blue;
    bool colliding;
};

#endif /*_CIRCLE_H */
