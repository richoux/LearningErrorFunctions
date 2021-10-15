#!/bin/bash

g++ -DFASTFORWARD -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/vertex_cover_fastforward ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/linear-geq.cpp ../../../constraints/linear-geq_concept.cpp ../../../constraints/linear-leq.cpp ../../../constraints/linear-leq_concept.cpp ../../../constraints/concept.cpp ../../../learn_ga/function_to_learn_icn.cpp -I../../../learn_ga/include -I../src -L../../../learn_ga/lib -lghost_static -pthread
