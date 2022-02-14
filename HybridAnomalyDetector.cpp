#include "HybridAnomalyDetector.h"
//default builder and destructor
HybridAnomalyDetector::HybridAnomalyDetector() {
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
}

//measure the distance between point and the circle/line depending on the correlation between the features
float HybridAnomalyDetector::distanceCalc(Point p,correlatedFeatures correlatedFeature){
    if(correlatedFeature.isHybrid) {
        return distanceBetweenTwoPoints(p, correlatedFeature.minCircle.center);
    }
    else{
        SimpleAnomalyDetector::distanceCalc(p,correlatedFeature);
    }
}

//the function create hybrid correlatedFeatures depending on the correlation between the features
void HybridAnomalyDetector::sortCorrelatedFeatures(float maxCor, const TimeSeries& ts, int i, int c){
    //if the correlation > 0.9, create correlatedFeatures by calculate the line
    if (maxCor >= getCorrelationThreshold()) {
        SimpleAnomalyDetector::sortCorrelatedFeatures(maxCor,ts,i,c);
    }
    //if the correlation > 0.5, create correlatedFeatures by calculate the minimum circle
    else if (maxCor >= getCorrelationCircleThreshold()){
        //features list
        vector<string> featureList(ts.getFeatures());
        //the number of rows
        int numOfValues = ts.getSizeOfValues();
        //the measurments in feature i and feature c
        float *x = ts.getMeasurements(featureList[i]);
        float *y = ts.getMeasurements(featureList[c]);
        //create array of Point* from the measurments above
        Point* points[numOfValues];
        for (int i = 0; i < numOfValues; i++){
            points[i] = new Point(x[i], y[i]);
        }
        //create the smallest circle from the points of features x and y
        Circle enclosingCircle = findMinCircle(points,numOfValues);
        //create correlatedFeatures of x and y
        correlatedFeatures associated{
            .isHybrid = true ,.feature1 = featureList[i],
                .feature2 = featureList[c],
                .corrlation = maxCor,
                .lin_reg = Line(0,0),
                .threshold = enclosingCircle.radius*getThresholdMultiplier(),
                .minCircle = enclosingCircle};
        //add correlatedFeatures to the list
        cf.push_back(associated);
        //free memory allocations
        for (int i = 0; i < numOfValues; i++){
            delete points[i];
        }
        delete[] x;
        delete[] y;
    }
}
