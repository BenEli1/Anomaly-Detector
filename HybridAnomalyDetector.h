

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void sortCorrelatedFeatures(float maxCor, const TimeSeries& ts, int i, int c);
    virtual float distanceCalc(Point p,correlatedFeatures correlatedFeature);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
