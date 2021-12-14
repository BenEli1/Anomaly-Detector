//Ben Eli 319086435
//Sahar Rofe 209275114
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
void HybridAnomalyDetector::sortCorrelatedFeatures(float maxCor, const TimeSeries& ts, int i, int c){
    if (maxCor >= getCorrelationThreshold()) {
        SimpleAnomalyDetector::sortCorrelatedFeatures(maxCor,ts,i,c);
    }
    else if (maxCor >= getCorrelationCircleThreshold()){
        vector<string> featureList(ts.getFeatures());
        int numOfValues = ts.getSizeOfValues();
        float *x = ts.getMeasurements(featureList[i]);
        float *y = ts.getMeasurements(featureList[c]);
        Point* points[numOfValues];
        for (int i = 0; i < numOfValues; i++){
            points[i] = new Point(x[i], y[i]);
        }
        Circle enclosingCircle = findMinCircle(points,numOfValues);
        correlatedFeatures associated{
            .isHybrid = true ,.feature1 = featureList[i],
                .feature2 = featureList[c],
                .corrlation = maxCor,
                .lin_reg = Line(0,0),
                .threshold = enclosingCircle.radius*getThresholdMultiplier(),
                .minCircle = enclosingCircle};
        cf.push_back(associated);
        for (int i = 0; i < numOfValues; i++){
            delete points[i];
        }
        delete[] x;
        delete[] y;
    }
}
