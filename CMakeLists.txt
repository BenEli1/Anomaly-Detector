cmake_minimum_required(VERSION 3.20)
project(AdvEx2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(AdvEx2 MainTrain.cpp AnomalyDetector.h anomaly_detection_util.h anomaly_detection_util.cpp
        timeseries.h timeseries.cpp SimpleAnomalyDetector.h SimpleAnomalyDetector.cpp minCircle.cpp minCircle.h
        HybridAnomalyDetector.cpp HybridAnomalyDetector.h CLI.h CLI.cpp commands.h Server.cpp Server.h)
