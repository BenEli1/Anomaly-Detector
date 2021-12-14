//Ben Eli 319086435
//Sahar Rofe 209275114
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
        maxCor = this->correlationThreshold;
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

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> anomalies;
	int sizeOfValues = ts.getSizeOfValues();
    for(int i = 0; i < sizeOfValues; i++){
        for(correlatedFeatures correlatedFeature : cf){
            float valueOfFeature1 = ts.getSpecificValue(correlatedFeature.feature1 , i);
            float valueOfFeature2 = ts.getSpecificValue(correlatedFeature.feature2 , i);
            Point p(valueOfFeature1, valueOfFeature2);
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

