#!/bin/bash


g++ test_server.cpp -o server -lpthread -I ../include -g

g++ test_sender.cpp -o client -lpthread -I ../include -g

g++ test_minion.cpp -o minion  ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp -lpthread -I ../include -g

