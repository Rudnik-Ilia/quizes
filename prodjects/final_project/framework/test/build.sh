#!/bin/bash


g++ test_server.cpp -o server -lpthread -I ../include -g

g++ test_sender.cpp -o client -lpthread -I ../include -g

