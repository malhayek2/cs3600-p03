
#ifndef _BALLS_H
#define _BALLS_H

#include <iostream>
#include <vector>
#include "circle.h"
/*mainly used to book keep the circle in a vector*/
class Balls
{
public:
    Balls();
    std::vector<Circle *> getCircles();
    double getScreenX();
    double getScreenY();
    void setScreenX(double screenX);
    void setScreenY(double screenY);
    void addCircle(Circle *circle);

private:
    std::vector<Circle *>_circles;
    double _screenX;
    double _screenY;
};

#endif /* _BALLS_H */
