#!/bin/bash

g++ -DHANDMADE -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/magic_square_handmade ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/linear-eq_handmade.cpp ../../../constraints/linear-eq_concept.cpp ../../../constraints/concept.cpp -I../../../learn/include -I../src -L../../../learn/lib -lghost_static -pthread
