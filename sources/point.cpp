#include <Point.hpp>
#include <iostream>
#include <math.h>

using namespace std;

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Point::distance(Point p)
{
    double xdiff = (x - p.x);
    double ydiff = (y - p.y);
    double ans2 = xdiff * xdiff + ydiff * ydiff;
    return sqrt(ans2);
}

string Point::print()
{
    //remove leading zeros
    std::string strx = std::to_string (x);
    strx.erase(strx.find_last_not_of('0') + 1, std::string::npos);
    strx.erase(strx.find_last_not_of('.') + 1, std::string::npos);

    std::string stry = std::to_string (y);
    stry.erase(stry.find_last_not_of('0') + 1, std::string::npos);
    stry.erase(stry.find_last_not_of('.') + 1, std::string::npos);

    return "{" + strx + ", " + stry + "}";
}

Point Point::moveTowards(Point start, Point end, double dist)
{
    if(dist < 0){
        throw std::invalid_argument("");
    }

    double xdiff = end.x - start.x;
    double ydiff = end.y - start.y;

    double len = start.distance(end);

    double per = dist / len;
    if(per > 1) per = 1;

    double xmove = xdiff * per + start.x;
    double ymove = ydiff * per + start.y;

    return Point(xmove, ymove);
}

bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}
