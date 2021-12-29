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
           commandMap[option]->execute();
   }
}


CLI::~CLI() {
}

