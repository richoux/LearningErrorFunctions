#!/bin/bash

g++ -O3 estimate_hamming.cpp ../utils/metrics.cpp ../utils/convert.cpp -Iinclude -o bin/estimate_hamming
