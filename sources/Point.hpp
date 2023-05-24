#pragma once
#include <string>

class Point
{   
    private:
        double x, y;
    public:
        Point(double xpos, double ypos);
        double distance(Point point);      
        std::string print();
    
    friend bool operator==(const Point& p1_, const Point& p2_);

    static Point moveTowards(Point start, Point end, double dist);
};