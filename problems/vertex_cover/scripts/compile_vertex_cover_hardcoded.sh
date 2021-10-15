#!/bin/bash

g++ -DHARDCODED -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/vertex_cover_hardcoded ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/linear-geq_hardcoded.cpp ../../../constraints/linear-geq_concept.cpp ../../../constraints/linear-leq_hardcoded.cpp ../../../constraints/linear-leq_concept.cpp ../../../constraints/concept.cpp -I../../../learn/include -I../src -L../../../learn/lib -lghost_static -pthread
