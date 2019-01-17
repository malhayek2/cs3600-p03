/* Collision handling code, for CS 3600 project 3, January, 2002. @
thanks to Bart for the collide code 
*/

#include "circle.h"
#include <vector>
#include <math.h>

double GRAVITY = .1;
double AIR_FRICTION = .999;
const double COLLISION_FRICTION = 1;

//
// Collision Detection
//
struct vectortype
{
	double x;
	double y;
};

void Collide(int p1, int p2, std::vector<Circle *>particles)
{
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif=particles[p1]->getnextx() - particles[p2]->getnextx();
	double ydif=particles[p1]->getnexty() - particles[p2]->getnexty();

	// set Center of Mass coordinate system
	size=sqrt(xdif*xdif + ydif*ydif);
	xdif/=size; ydif/=size; // normalize
	en.x=xdif;
	en.y=ydif;
	et.x=ydif;
	et.y=-xdif;

	// set u values
	u[0].x=particles[p1]->getdx();
	u[0].y=particles[p1]->getdy();
	m[0]=particles[p1]->getradius()*particles[p1]->getradius();
	u[1].x=particles[p2]->getdx();
	u[1].y=particles[p2]->getdy();
	m[1]=particles[p2]->getradius()*particles[p2]->getradius();

	// set M and V
	M=m[0]+m[1];
	V.x=(u[0].x*m[0] + u[1].x*m[1])/M;
	V.y=(u[0].y*m[0] + u[1].y*m[1])/M;

	// set um values
	um[0].x=m[1]/M * (u[0].x-u[1].x);
	um[0].y=m[1]/M * (u[0].y-u[1].y);
	um[1].x=m[0]/M * (u[1].x-u[0].x);
	um[1].y=m[0]/M * (u[1].y-u[0].y);

	// set umt and umn values
	for(i=0;i<2;i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for(i=0;i<2;i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	particles[p1]->setdx(v[0].x*COLLISION_FRICTION);
	particles[p1]->setdy(v[0].y*COLLISION_FRICTION);
	particles[p2]->setdx(v[1].x*COLLISION_FRICTION);
	particles[p2]->setdy(v[1].y*COLLISION_FRICTION);
    
} /* Collide */






/*Cricle Class helper functions*/
/*gets the x_1 , y_1 r_1 & x_2, y_2, r_2 and if the distance is less than the radius of both combine then its coliding*/


bool circlesCollide(Circle *circle1, Circle *circle2)
{
    double d = sqrt(pow(circle2->getnextx() - circle1->getnextx(), 2) + pow(circle2->getnexty() - circle1->getnexty(), 2));
    return d <= circle1->getradius() + circle2->getradius();
}

/*Draw Cricle Directly copied from the graphics01.cpp */
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

Circle::Circle(double x, double y, double radius, double dx, double dy, double red, double green, double blue)
{
    this->x = x;
	this->y = y;
	this->radius = radius;
	this->dx = dx;
	this->dy = dy;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->colliding = false;
    //_isRed = isRed;
}
/*update method that checks for balls position & collison with other balls*/
void Circle::update(int i, double screenX, double screenY, std::vector<Circle *>circles)
{
    this->dy -= GRAVITY;
	this->dy *= AIR_FRICTION;
	this->dx *= AIR_FRICTION;

    /* wall collisions with added friction */
    if (this->y - this->radius <= 0){
		this->dy = abs(this->dy) == 0 ? COLLISION_FRICTION : abs(this->dy);
    }
    else if (this->y + this->radius >= screenY){
		this->dy = -abs(this->dy) == 0 ? -COLLISION_FRICTION : -abs(this->dy);
    }

    if (this->x - this->radius <= 0){
		this->dx = abs(this->dx) == 0 ? COLLISION_FRICTION : abs(this->dx);
    }
    else if (this->x + this->radius >= screenX){
		this->dx = -abs(this->dx) == 0 ? -COLLISION_FRICTION : -abs(this->dx);
    }

    /*ball-ball collisions*/
    
    for (unsigned int k = i+1; k < (circles.size()); k++){
    	if(circlesCollide(circles[i], circles[k])){
    		Collide(i,k,circles);
    	}
    }

    // update position
	this->x += this->dx;
	this->y += this->dy;
	/*After updating position we need to test again for */

}
/*since we merge the RGB.h into the cricle class the draw has to be updated*/
void Circle::draw()
{
    glColor3ub(this->red, this->green, this->blue);
    DrawCircle(this->x, this->y, this->radius);
}
/*Getters */
double Circle::getx() { return this->x; }
double Circle::gety() { return this->y; }
double Circle::getradius() { return this->radius; }
double Circle::getr() { return this->red; }
double Circle::getg() {return this->green;}
double Circle::getb() { return this->blue; }
double Circle::getdx() { return this->dx; }
double Circle::getdy() { return this->dy; }
double Circle::getnextx() { return this->x + this->dx; }
double Circle::getnexty() { return this->y + this->dy; }
/*Setters*/
void Circle::setdx(double dx) { this->dx = dx; }
void Circle::setdy(double dy) { this->dy = dy; }
