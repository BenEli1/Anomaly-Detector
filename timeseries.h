//Ben Eli 319086435
//Sahar Rofe 209275114
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <map>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

class TimeSeries{
    //map with all the data from the file, strings and float vectors
    map<string , vector<float>> data;
    //list with all the feature names
    vector<string> featureList;
public:
	TimeSeries(const char* CSVfileName){
        //create and open ifstream
        ifstream file(CSVfileName);
        string line;
        //read the first line from the file
        getline(file, line);
        stringstream firstLine(line);
        string feature;
        //read the featureList from the first line and insert to the map
        while(getline(firstLine, feature, ',')) {
            data.insert(pair<string, vector<float>>(feature, vector<float>()));
            featureList.push_back(feature);
        }
        string measurement;
        map<string, vector<float>>::iterator it;
        bool thereIsAnotherLine = true;
        //if there is another line, read the line and insert the measurements to the map
        while(thereIsAnotherLine){
            //each line we begin again with the first feature
            for(it = data.begin(); it != data.end(); it++){
                getline(file, measurement, ',');
                //if there is no data to read stop the loops
                if(measurement.empty()){
                    thereIsAnotherLine = false;
                    break;
                }
                it->second.push_back(stof(measurement));
            }
        }
        //close the file
        file.close();
	}
    float* getMeasurements(string feature) const;

    /*
     * returns the amount of values in any feature.
     */
    int getSizeOfValues()const;
    /*
     * returns the number of featureList in total.
     */
    int getSizeOfFeatures()const;
    /*
     * returns specific location given a feature and location.
     */
    float getSpecificValue(string feature, int location)const;
    /*
     * returns list with the features
     */
    vector<string> getFeatures()const;
};
#endif /* TIMESERIES_H_ */
