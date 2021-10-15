#!/bin/bash

g++ -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/vertex_cover_csp ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/linear-geq_no-cfn.cpp ../../../constraints/linear-geq_concept.cpp ../../../constraints/linear-leq_no-cfn.cpp ../../../constraints/linear-leq_concept.cpp ../../../constraints/concept.cpp -I../../../learn_ga/include -I../src -L../../../learn_ga/lib -lghost_static -pthread
