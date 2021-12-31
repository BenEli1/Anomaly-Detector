//Ben Eli 319086435
//Sahar Rofe 209275114
#include "CLI.h"

void CLI::start(){
   while(true) {
       dio->write("Welcome to the Anomaly Detection Server.\n");
       dio->write("Please choose an option:\n");
       for (int i = 1; i < size; i++) {
           dio->write(commandMap[i]->getDescription());
       }
       int option = atoi( dio->read().c_str() );

       if (option == 6){
           break;
       }
       if (option == 0){
           continue;
       }
           commandMap[option]->execute();
   }
}


CLI::~CLI() {
    for(int i = 0; i < size; i++) {
        delete commandMap[i];
    }
    delete[] commandMap;
}

