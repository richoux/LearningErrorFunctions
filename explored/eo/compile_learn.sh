#!/bin/bash

g++ learn_with_ga.cpp ../all-diff.cpp ../increment.cpp ../subghost/domain.cpp ../subghost/variable.cpp ../subghost/constraint.cpp -Iinclude -Llib -leo -leoutils -o learn_with_ga
