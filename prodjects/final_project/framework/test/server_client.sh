#!/bin/bash

g++ test_server.cpp -o server -I ../include

g++ test_client.cpp -o client -I ../include