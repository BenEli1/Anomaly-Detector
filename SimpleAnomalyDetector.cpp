//Ben Eli 319086435
//Sahar Rofe 209275114
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(): correlationThreshold(0.5), thresholdMultiplier(1.1) {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
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
        if(c != -1){
            float* x = ts.getMeasurements(featureList[i]);
            float* y = ts.getMeasurements(featureList[c]);
            Line line = linear_reg(x, y, numOfValues);
            float maxThreshold = maxDev(x, y, numOfValues, line)*thresholdMultiplier;
            correlatedFeatures associated{.feature1 = featureList[i],
                    .feature2 = featureList[c],
                    .corrlation = maxCor,
                    .lin_reg = line,
                    .threshold = maxThreshold};
            cf.push_back(associated);
            delete [] x;
            delete [] y;
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> anomalies;
	int sizeOfValues = ts.getSizeOfValues();
    for(int i = 0; i < sizeOfValues; i++){
        for(correlatedFeatures colleateFeature : cf){
            float valueOfFeature1 = ts.getSpecificValue(colleateFeature.feature1 , i);
            float valueOfFeature2 = ts.getSpecificValue(colleateFeature.feature2 , i);
            Point p(valueOfFeature1, valueOfFeature2);
            float distance = dev(p, colleateFeature.lin_reg);
            if (distance > colleateFeature.threshold){
                string description = colleateFeature.feature1 + "-" + colleateFeature.feature2;
                AnomalyReport report(description, i+1);
                anomalies.push_back(report);
            }
        }
    }
    return anomalies;
}

