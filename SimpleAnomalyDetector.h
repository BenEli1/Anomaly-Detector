//Ben Eli 319086435
//Sahar Rofe 209275114
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation; //corrlation between the 2 features
	Line lin_reg; // the line created betweeen the 2 features.
	float threshold; // the maximum allowed distance between a point to the line.
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> cf; //vector containing all correlated features in pairs.
    const float correlationThreshold; // the correlation threshold(0.8) currently.
    const float thresholdMultiplier; // the threshold multiplier(currently 1.1)
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();
    /*
     * for every feature find his associated correlative feature , calculates the line between then and max dev.
     */
	virtual void learnNormal(const TimeSeries& ts);
    /*
     * checks in every line if there is an anomaly returns a vector with the anaomalies.
     */
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
