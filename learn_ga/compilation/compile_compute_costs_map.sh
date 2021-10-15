#!/bin/bash

g++ -O3 compute_costs_map.cpp ../utils/metrics.cpp ../utils/convert.cpp -I./include -o bin/compute_costs_map
