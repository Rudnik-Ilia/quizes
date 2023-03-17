#!/bin/bash

# g++ -fPIC -c CreateHandleton.cpp ../src/Logger.cpp ../src/LogInherited.cpp ../src/LogMessage.cpp  ../src/LogTask.cpp  ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp  -I ../include

# g++ -shared CreateHandleton.o  Logger.o  LogInherited.o LogMessage.o LogTask.o ThreadPool.o WorkerThread.o ThreadMap.o -o lib_logger.so 

# rm *.o

g++ -shared -fPIC -o lib_logger.so ../src/*.cpp -I ../include


