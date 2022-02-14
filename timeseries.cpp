#include "timeseries.h"

//return float* to measurements of specific feature
float *TimeSeries::getMeasurements(string feature)const{
    int size = this->getSizeOfValues();
    //create an array
    float* measurments = new float[size];
    //create the vector with all the relevant data
    vector<float> vec(this->data.at(feature));
    //copy the vector to the array
    for (int i = 0; i < size; i++){
        measurments[i] = vec[i];
    }
    return measurments;
}

vector<string> TimeSeries::getFeatures()const{
    return vector<string>(this->featureList);
}

int TimeSeries::getSizeOfValues()const {
    return this->data.at(this->featureList.front()).size();
}

int TimeSeries::getSizeOfFeatures()const{
    return this->featureList.size();
}

float TimeSeries::getSpecificValue(string feature, int location)const{
    return this->data.at(feature).at(location);
}

TimeSeries::~TimeSeries() {
    data.clear();
    featureList.clear();
}

const map<string, vector<float>> &TimeSeries::getData() const {
    return data;
}

const vector<string> &TimeSeries::getFeatureList() const {
    return featureList;
}


