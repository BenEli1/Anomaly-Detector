//Ben Eli 319086435
//Sahar Rofe 209275114
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "anomaly_detection_util.h"

float expectedValue(float* x, int size){
    if (size <= 0)
        return 0;
    float sum = 0;
    for (int i = 0; i < size; i++){
        sum += x[i];
    }
    return sum/(float) size;
}

// returns the variance of X and Y
float var(float* x, int size){
    if(size <= 0 || x == nullptr){
        return 0;
    }
    float xPow[size];
    for (int i = 0; i < size; i++){
        xPow[i] = x[i]*x[i];
    }
    return expectedValue(xPow, size) - expectedValue(x, size) * expectedValue(x, size);
}
//NEED TO CHECK NULL EXCEPTION
// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    if(size <= 0 || x == nullptr){
        return 0;
    }
    float xyMul[size];
    for (int i = 0; i < size; i++){
        xyMul[i] = x[i]*y[i];
    }
    return expectedValue(xyMul, size) - expectedValue(x, size) * expectedValue(y, size);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    if (size == 0)
        return 0;
    return cov(x, y, size) / (sqrt(var(x, size))* sqrt(var(y,size)));
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size){
    if (size <= 0){
        return Line(0,0);
    }
    float y[size],x[size];
    float a,b;
    for(int i = 0; i < size; i++){
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    if (var(x, size) == 0){
        a = 0;
    }else {
        a = cov(x, y, size) / var(x, size);
    }
    b = expectedValue(y, size) - a * expectedValue(x, size);
    return Line(a, b);
}

Line linear_reg(float* x, float* y, int size){
    Point* pointsArray[size];
    for(int i = 0; i < size; i++){
        pointsArray[i] = new Point(x[i], y[i]);
    }
    Line line = linear_reg(pointsArray, size);
    for(int i = 0; i < size; i++){
        delete pointsArray[i];
    }
    return line;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    if (size <= 0){
        return 0;
    }
    Line l = linear_reg(points, size);
    return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
 float yPoint = p.y;
 float yLine = l.f(p.x);
 float x = yLine - yPoint;
 if(x > 0) {
     return x;
 }
 return -x;
}

//returns the maximum dev between a line and all the points that created the line.
float maxDev(float* x, float* y, int size, Line l){
    float maxDev = 0;
    float currentDev;
    for(int i = 0; i < size; i++){
        Point p(x[i], y[i]);
        currentDev = dev(p, l);
        if(currentDev > maxDev){
            maxDev = currentDev;
        }
    }
    return maxDev;
}


