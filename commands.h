

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include <iomanip>
#include "HybridAnomalyDetector.h"

using namespace std;

class Report{
public:
    int start;
    int finish;
    int size;
    Report(int start, int finish): start(start), finish(finish) {
        size = finish - start + 1;
    }
};

class DefaultIO{
public:
	virtual string read()=0;
    HybridAnomalyDetector* hybridDetector;
    DefaultIO() {
        hybridDetector = new HybridAnomalyDetector();
    }
    virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){
        delete csvFileTest;
        delete csvFileLearn;
        delete hybridDetector;
    }
    TimeSeries* csvFileLearn = nullptr;//file that we get from the client
    TimeSeries* csvFileTest = nullptr;//file that we get from the client
    vector<AnomalyReport> reports;
    float threshold = 0.9;

    void setCsvFileLearn(TimeSeries *csvFileLearn) {
        DefaultIO::csvFileLearn = csvFileLearn;
    }

    void setCsvFileTest(TimeSeries *csvFileTest) {
        DefaultIO::csvFileTest = csvFileTest;
    }

    void setThreshold(float threshold) {
        DefaultIO::threshold = threshold;
    }
    void readAndWriteToFile(string fileName) {
        std::ofstream outfile(fileName);
        string line = "";
        while ((line = read()) != "done") {
            outfile << line << endl;
        }
        outfile.close();
    }

    float getThreshold() {
        return DefaultIO::threshold;
    }
    // you may add additional methods here
};
// you may add here helper classes


// you may edit this class
class Command{
    string description;
protected:
    DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;

    void setDescription(const string &description) {
        Command::description = description;
    }

    const string &getDescription() const {
        return description;
    }

    virtual ~Command(){}
};

// implement here your command classes
class uploadFileCommand: public Command{

public:
    uploadFileCommand(DefaultIO *dio) : Command(dio) {
        setDescription("1.upload a time series csv file\n");
    }

    void execute(){
        const char* csvFileName = "output.txt";
        dio->write("Please upload your local train CSV file.\n");
        dio->readAndWriteToFile("anomalyTrain.csv");
        dio->setCsvFileLearn(new TimeSeries("anomalyTrain.csv"));
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readAndWriteToFile("anomalyTest.csv");
        dio->setCsvFileTest(new TimeSeries("anomalyTest.csv"));
        dio->write("Upload complete.\n");
    }

};

class algoSettingsCommand: public Command{
public:
    algoSettingsCommand(DefaultIO *dio) : Command(dio) {
        setDescription("2.algorithm settings\n");
    }

    void execute(){
        float newThreshold;
        while(true) {
            dio->write("The current correlation threshold is ");
            dio->write(dio->getThreshold());
            dio->write("\n");
            dio->write("Type a new threshold\n");
            dio->read(&newThreshold);
            if (0 <= newThreshold && newThreshold <= 1) {
                dio->setThreshold(newThreshold);
                dio->hybridDetector->setCorrelationThreshold(newThreshold);
                break;
            }
            //if the threshold is not valid.
            dio->write("please choose a value between 0 and 1.\n");
            //wait for enter
            dio->read();
        }
    }
};

class detectAnomaliesCommand: public Command{
public:
    detectAnomaliesCommand(DefaultIO *dio) : Command(dio) {
        setDescription("3.detect anomalies\n");
    }

    void execute(){
        dio->hybridDetector->learnNormal(*(dio->csvFileLearn));
        dio->reports = dio->hybridDetector->detect(*(dio->csvFileTest));
        dio->write("anomaly detection complete.\n");
    }
};

class displayResultsCommand: public Command{
public:
    displayResultsCommand(DefaultIO *dio) : Command(dio) {
        setDescription("4.display results\n");
    }

    void execute(){
        for(AnomalyReport anomaly : dio->reports){
            dio->write(anomaly.timeStep);
            dio->write("\t");
            dio->write(anomaly.description);
            dio->write("\n");
        }
        dio->write("Done.\n");
    }
};

class uploadAndAnalyzeCommand: public Command{
public:
    float P = 0;
    float TP = 0;
    float FP = 0;
    float N = 0;
    int counter = 0;
    vector<Report> reportVector;

    uploadAndAnalyzeCommand(DefaultIO *dio) : Command(dio) {
        setDescription("5.upload anomalies and analyze results\n");
    }

    void execute() {
        int start,finish;
        calculateReports();
        N = dio->csvFileTest->getSizeOfValues();
        string currentDescription;
        dio->write("Please upload your local anomalies file.\n");
        string line = "";
        while ((line = dio->read()) != "done") {
            P++;
            start = std::stoi(line.substr(0, line.find(',')));
            finish = std::stoi(line.substr(line.find(',') + 1, line.size()));
            N -= (finish - start + 1);
            for(Report report: reportVector){
                if(!(report.start > finish || report.finish <start)) {
                    TP++;
                    break;
                }
            }
//            float tpDivP = (float)((int)((TP/P)*1000))/1000;
//            float fpDivN = (float)((int)((FP/N)*1000))/1000;
        }
        FP = reportVector.size() - TP;
        float tpDivP = TP/P;
        float fpDivN = FP/N;
        dio->write("Upload complete.\n");
        dio->write("True Positive Rate: ");
        dio->write((tpDivP));
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(fpDivN);
        dio->write("\n");
    }

    void calculateReports(){
        int start, finish, counter = 0;
        int currentTimeStep = dio->reports[counter].timeStep;
        string currenDescription = dio->reports[counter].description;
        start = dio->reports[counter].timeStep;
        while(counter < dio->reports.size()-1){
            counter++;
            if (dio->reports[counter].timeStep - 1 == currentTimeStep
            && dio->reports[counter].description == currenDescription)
                currentTimeStep += 1;
            else{
                currenDescription = dio->reports[counter].description;
                reportVector.push_back(Report(start, currentTimeStep));
                currentTimeStep = dio->reports[counter].timeStep;
                start = currentTimeStep;
            }
        }
    }
};

class exitCommand: public Command{
public:
    exitCommand(DefaultIO *dio) : Command(dio) {
        setDescription("6.exit\n");
    }


    void execute(){
        return;
    }
};

class StandartDefaultIO: public DefaultIO{
    ifstream in;
    ofstream out;
public:
    StandartDefaultIO(string inputFile, string outputFile){
        in.open(inputFile);
        out.open(outputFile);
    }
    virtual string read(){
        string s;
        in>>s;
        return s;
    }
    virtual void write(string text){
        out<<text;
    }

    virtual void write(float f){
        out<<f;
    }

    virtual void read(float* f){
        in>>*f;
    }

    void close(){
        if(in.is_open())
            in.close();
        if(out.is_open())
            out.close();
    }
    ~StandartDefaultIO(){
        close();
    }
};



#endif /* COMMANDS_H_ */
