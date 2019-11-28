XEC_AD=all_diff_cf
EXEC_LE=linear_eq_cf
EXEC_LT=less_than_cf

# Compiler flags
CXXFIRSTFLAGS= -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter
CXXFIRSTFLAGSDEBUG= -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	CXXFLAGS= -std=c++17 $(CXXFIRSTFLAGS) $(MYFLAGS)
	CXXFLAGSDEBUG= -std=c++17 $(CXXFIRSTFLAGSDEBUG)
	LDFLAGS=-pthread -lghost
endif
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
	CXXFLAGS= -std=c++17 -stdlib=libc++ $(CXXFIRSTFLAGS)
	CXXFLAGSDEBUG= -std=c++17 -stdlib=libc++ $(CXXFIRSTFLAGSDEBUG)
	LDFLAGS=-pthread -lghost -lc++ -lc++abi
endif

# Directories
SRCDIR=.
OBJDIR=obj
BINDIR=bin

# Files
COMMON_SRC=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp)) ../constraints/concept.cpp ../utils/convert.cpp ../utils/latin.cpp ../utils/metrics.cpp ../utils/random_draw.cpp
COMMON=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(COMMON_SRC)))

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
alldiff: $(BINDIR)/$(EXEC_AD)
alldiff: CONSTRAINTFLAG=-DAD

lineareq: $(BINDIR)/$(EXEC_LE)
lineareq: CONSTRAINTFLAG=-DLE

lessthan: $(BINDIR)/$(EXEC_LT)
lessthan: CONSTRAINTFLAG=-DLT

# Executables
$(BINDIR)/$(EXEC_AD): $(COMMON) $(OBJDIR)/all-diff_concept.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(BINDIR)/$(EXEC_LE): $(COMMON) $(OBJDIR)/linear-eq_concept.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(BINDIR)/$(EXEC_LT): $(COMMON) $(OBJDIR)/less-than_concept.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

# Objects of a specific contraint
$(OBJDIR)/all-diff_concept.o: ../constraints/all-diff_concept.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/linear-eq_concept.o: ../constraints/linear-eq_concept.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/less-than_concept.o: ../constraints/less-than_concept.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Common objects
$(OBJDIR)/learn_cf_cfn.o: learn_cf_cfn.cpp
	$(CXX) $(CXXFLAGS) $(CONSTRAINTFLAG) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/concept.o: ../constraints/concept.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/convert.o: ../utils/convert.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/latin.o: ../utils/latin.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/metrics.o: ../utils/metrics.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/random_draw.o: ../utils/random_draw.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -fr core *~ $(BINDIR)/$(EXEC_AD) $(OBJDIR)/*.o
