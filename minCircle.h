
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
    const Point &getCenter() const {
        return center;
    }

    float getRadius() const {
        return radius;
    }
};
// --------------------------------------
Circle findMinCircle(Point** points,size_t size);
float dist(const Point& a, const Point& b);
bool is_inside(const Circle& c, const Point& p);
Point get_circle_center(double bx, double by,
                        double cx, double cy);
Circle circle_from(const Point& A, const Point& B,
                   const Point& C);
Circle circle_from(const Point& A, const Point& B);
bool is_valid_circle(const Circle& c,
                     const vector<Point>& P);
Circle min_circle_trivial(vector<Point>& P);
Circle findMinCircleHelper(vector<Point>& P,
                           vector<Point> R, int n);
#endif /* MINCIRCLE_H_ */
