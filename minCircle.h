//Ben Eli 319086435
//Sahar Rofe 209275114
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;
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
//finds the minimum circle that contains all of the points.
Circle findMinCircle(Point** points,size_t size);

//calculates distance between two points.
float distanceBetweenTwoPoints(const Point& a, const Point& b);

//checks if p is inside circle or on the boundaries
bool isInside(const Circle& c, const Point& p);
//calculates circle center given
Point getCircleCenter(double bx, double by,
                      double cx, double cy);

// Function to return the smallest circle that intersects 3 points.
Circle circleFrom(const Point& A, const Point& B,
                  const Point& C);

// Function to return the smallest circle that intersects 2 points.
Circle circleFrom(const Point& A, const Point& B);

// Function to check whether a circle encloses the given points.
bool isValidCircle(const Circle& c,
                   const vector<Point>& P);

// Function to return the minimum enclosing circle for N <= 3
Circle minCircleTrivial(vector<Point>& P);

//Returns the MEC using Welzl's algorithm
Circle findMinCircleHelper(vector<Point>& P,
                           vector<Point> R, int n);

#endif /* MINCIRCLE_H_ */
