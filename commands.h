

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
    TimeSeries uploadFile(string path);

	// you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
	DefaultIO* dio;
    string description;
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
        setDescription("1. upload a time series csv file\n");
    }

private:
    void execute(){
        return;
}
};

class algoSettingsCommand: public Command{
public:
    algoSettingsCommand(DefaultIO *dio) : Command(dio) {
        setDescription("2. algorithm settings\n");
    }

private:
    void execute(){
        return;

    }
};

class detectAnomaliesCommand: public Command{
public:
    detectAnomaliesCommand(DefaultIO *dio) : Command(dio) {
        setDescription("3. detect anomalies\n");
    }

private:
    void execute(){
        return;

    }
};

class displayResultsCommand: public Command{
public:
    displayResultsCommand(DefaultIO *dio) : Command(dio) {
        setDescription("4. display results\n");
    }

private:
    void execute(){
        return;

    }
};

class uploadAndAnalyzeCommand: public Command{
public:
    uploadAndAnalyzeCommand(DefaultIO *dio) : Command(dio) {
        setDescription("5. upload anomalies and analyze results\n");
    }

private:
    void execute(){
        return;

    }
};

class exitCommand: public Command{
public:
    exitCommand(DefaultIO *dio) : Command(dio) {
        setDescription("6. exit");
    }

private:
    void execute(){
        return;

    }
};


#endif /* COMMANDS_H_ */
