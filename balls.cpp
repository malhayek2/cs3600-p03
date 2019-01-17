#include "balls.h"
/*sets the windows width and res HERE*/
Balls::Balls()
{
    _screenX = 700;
    _screenY = 500;
}
/*indexing all cricles in a vector */
std::vector<Circle *> Balls::getCircles()
{
    return _circles;
}

void Balls::addCircle(Circle *circle)
{
    _circles.push_back(circle);
}

double Balls::getScreenX()
{
    return _screenX;
}

double Balls::getScreenY()
{
    return _screenY;
}

void Balls::setScreenX(double screenX)
{
    _screenX = screenX;
}

void Balls::setScreenY(double screenY)
{
    _screenY = screenY;
}
