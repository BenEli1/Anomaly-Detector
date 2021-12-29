

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;
    map<int, Command> commandMap;
	// you can add data members
public:
	CLI(DefaultIO* dio):dio(dio){
        commandMap = map<int, Command>();
        commandMap.insert(pair<int, Command>(1,uploadFileCommand(dio)));
        commandMap.insert(pair<int, Command>(2,algoSettingsCommand(dio)));
        commandMap.insert(pair<int, Command>(3,detectAnomaliesCommand(dio)));
        commandMap.insert(pair<int, Command>(4,displayResultsCommand(dio)));
        commandMap.insert(pair<int, Command>(5,uploadAndAnalyzeCommand(dio)));
        commandMap.insert(pair<int, Command>(6,exitCommand(dio)));
    };
	void start(){
        int size = commandMap.size();
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(int i = 1 ; i<=size ; i++){
            dio->write(commandMap[i].getDescription());
        }
    }
	virtual ~CLI();
};

#endif /* CLI_H_ */
