#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(): correlationThreshold(0.9), thresholdMultiplier(1.1),
correlationCircleThreshold(0.5) {
}
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	vector<string> featureList(ts.getFeatures());
    int numOfFeatures = ts.getSizeOfFeatures();
    float maxCor, c;
    int numOfValues = ts.getSizeOfValues();
    float pearsonBetweenTwo;
    for(int i = 0; i < numOfFeatures; i++){
        maxCor = 0;
        c = -1;
        for(int j = i+1; j < numOfFeatures; j++){
            float* x = ts.getMeasurements(featureList[i]);
            float* y = ts.getMeasurements(featureList[j]);
            pearsonBetweenTwo = abs(pearson(x,y, ts.getSizeOfValues()));
            delete [] x;
            delete [] y;
            if(pearsonBetweenTwo > maxCor){
                c = j;
                maxCor = pearsonBetweenTwo;
            }
        }
        if(c != -1) {
            sortCorrelatedFeatures(maxCor, ts, i, c);
        }
    }
}
//
void SimpleAnomalyDetector::sortCorrelatedFeatures(float maxCor, const TimeSeries& ts, int i, int c){
    //if the correlation > 0.9 create correlatedFeatures
    if (maxCor >= this->correlationThreshold) {
        //feature list
        vector<string> featureList(ts.getFeatures());
        //number of rows (measurments)
        int numOfValues = ts.getSizeOfValues();
        float *x = ts.getMeasurements(featureList[i]);
        float *y = ts.getMeasurements(featureList[c]);
        //crate the line from the measurments
        Line line = linear_reg(x, y, numOfValues);
        //calculate the max valid threshold
        float maxThreshold = maxDev(x, y, numOfValues, line) * thresholdMultiplier;
        //create correlatedFeatures
        correlatedFeatures associated{
            .isHybrid = false,
            .feature1 = featureList[i],
                .feature2 = featureList[c],
                .corrlation = maxCor,
                .lin_reg = line,
                .threshold = maxThreshold,
                .minCircle =Circle(Point(0,0),0)};
        //add correlatedFeatures to the list
        cf.push_back(associated);
        delete[] x;
        delete[] y;
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    //anomaly report list
    vector<AnomalyReport> anomalies;
    //number of rows
	int sizeOfValues = ts.getSizeOfValues();
    for(int i = 0; i < sizeOfValues; i++){
        //for each correlatedFeature in each row
        for(correlatedFeatures correlatedFeature : cf){
            //create point from the measurments in the relevant row
            float valueOfFeature1 = ts.getSpecificValue(correlatedFeature.feature1 , i);
            float valueOfFeature2 = ts.getSpecificValue(correlatedFeature.feature2 , i);
            Point p(valueOfFeature1, valueOfFeature2);
            //
            float distance = distanceCalc(p,correlatedFeature);
            if (distance > correlatedFeature.threshold){
                string description = correlatedFeature.feature1 + "-" + correlatedFeature.feature2;
                AnomalyReport report(description, i+1);
                anomalies.push_back(report);
            }
        }
    }
    return anomalies;
}

float SimpleAnomalyDetector::distanceCalc(Point p,correlatedFeatures correlatedFeature){
    return dev(p, correlatedFeature.lin_reg);
}
//getters:
const vector<correlatedFeatures> &SimpleAnomalyDetector::getCf() const {
    return cf;
}

const float SimpleAnomalyDetector::getCorrelationThreshold() const {
    return correlationThreshold;
}

const float SimpleAnomalyDetector::getCorrelationCircleThreshold() const {
    return correlationCircleThreshold;
}

const float SimpleAnomalyDetector::getThresholdMultiplier() const {
    return thresholdMultiplier;
}

void SimpleAnomalyDetector::setCorrelationThreshold(float correlationThreshold) {
    SimpleAnomalyDetector::correlationThreshold = correlationThreshold;
}

void correlatedFeatures::setThreshold(float threshold) {
    correlatedFeatures::threshold = threshold;
}
