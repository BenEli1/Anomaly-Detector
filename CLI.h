

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;
    Command** commandMap;
    int size;

	// you can add data members
public:
	CLI(DefaultIO* dio):dio(dio), size(7){
        commandMap = new Command*[size];
        commandMap[1] = new uploadFileCommand(dio);
        commandMap[2] = new algoSettingsCommand(dio);
        commandMap[3] = new detectAnomaliesCommand(dio);
        commandMap[4] = new displayResultsCommand(dio);
        commandMap[5] = new uploadAndAnalyzeCommand(dio);
        commandMap[6] = new exitCommand(dio);
    };
	void start();
	virtual ~CLI();
};

#endif /* CLI_H_ */
