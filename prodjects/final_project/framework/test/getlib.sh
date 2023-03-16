#!/bin/bash

g++ -fPIC -c CreateHandleton.cpp ../src/LogInherited.cpp ../src/LogMessage.cpp  ../src/LogTask.cpp ../src/Logger.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp  -I ../include

g++ -shared -o lib_logger.so CreateHandleton.o LogInherited.o LogMessage.o LogTask.o Logger.o ThreadPool.o WorkerThread.o ThreadMap.o

rm *.o


