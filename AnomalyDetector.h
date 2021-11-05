//Ben Eli 319086435
//Sahar Rofe 209275114
#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "timeseries.h"
#include "math.h"
using namespace std;


class AnomalyReport{
public:
	const string description; // feature1 - feature 2
	const long timeStep; // what line the anomaly happened on
	AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}
};

class TimeSeriesAnomalyDetector {
public:
	virtual void learnNormal(const TimeSeries& ts)=0;
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
	virtual ~TimeSeriesAnomalyDetector(){}
};

#endif /* ANOMALYDETECTOR_H_ */
