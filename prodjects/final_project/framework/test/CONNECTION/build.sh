#!/bin/bash

g++ receiver.cpp -o server -lpthread -g

g++ test_sender.cpp -o client -lpthread -g