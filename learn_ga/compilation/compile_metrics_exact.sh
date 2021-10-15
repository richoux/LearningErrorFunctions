#!/bin/bash

g++ -O3 metrics_exact.cpp ../utils/metrics.cpp ../utils/convert.cpp -Iinclude -o bin/metrics_exact
