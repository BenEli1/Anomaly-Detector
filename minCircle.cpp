#include "minCircle.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// Defining infinity
const double INF = 1e18;

//Function that returns distance between 2 points.
float distanceBetweenTwoPoints(const Point& a, const Point& b)
{
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool isInside(const Circle& c, const Point& p)
{
    return distanceBetweenTwoPoints(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
Point getCircleCenter(float bx, float by,
                        float cx, float cy)
{
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return Point( (cy * B - by * C) / (2 * D),
             (bx * C - cx * B) / (2 * D) );
}

// Function to return a unique circle that
// intersects three points
Circle circleFrom(const Point& A, const Point& B,
                  const Point& C)
{
    Point I = getCircleCenter(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return {I, distanceBetweenTwoPoints(I, A) };
}

// Function to return the smallest circle that intersects 2 points.
Circle circleFrom(const Point& A, const Point& B)
{
    // Set the center to be the midpoint of A and B
    Point C = { (A.x + B.x) / 2, (A.y + B.y) / 2 };

    // Set the radius to be half the distance AB
    return {C, distanceBetweenTwoPoints(A, B) / 2};
}

// Function to check whether a circle encloses the given points.
bool isValidCircle(const Circle& c,
                   const vector<Point>& P)
{

    // Iterating through all the points
    // to check whether the points
    // lie inside the circle or not
    for (const Point& p : P)
        if (!isInside(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing circle for N <= 3
Circle minCircleTrivial(vector<Point>& P)
{
    assert(P.size() <= 3);
    if (P.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (P.size() == 1) {
        return { P[0], 0 };
    }
    else if (P.size() == 2) {
        return circleFrom(P[0], P[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circleFrom(P[i], P[j]);
            if (isValidCircle(c, P))
                return c;
        }
    }
    return circleFrom(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle findMinCircleHelper(vector<Point>& P,
                    vector<Point> R, int n)
{
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return minCircleTrivial(R);
    }

    // Pick a random point randomly
    int idx = rand() % n;
    Point p = P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = findMinCircleHelper(P, R, n - 1);

    // If d contains p, return d
    if (isInside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return findMinCircleHelper(P, R, n - 1);
}
Circle findMinCircle(Point** points,size_t size){
    vector<Point> vectorOfPoints;
    for (int i = 0; i < size; i++){
        vectorOfPoints.push_back(*(points[i]));
    }
    random_shuffle(vectorOfPoints.begin(), vectorOfPoints.end());
    return findMinCircleHelper(vectorOfPoints, {}, vectorOfPoints.size());
}

//point** = array of point* vector point*