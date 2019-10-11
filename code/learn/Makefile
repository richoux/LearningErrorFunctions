EXEC_AD=all_diff_cf
EXEC_LE=linear_eq_cf
EXEC_LT=less_than_cf

# Compiler flags
CXXFIRSTFLAGS= -Ofast -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter
CXXFIRSTFLAGSDEBUG= -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	CXXFLAGS= -std=c++17 $(CXXFIRSTFLAGS)
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
SRCDIR=. ../latin/
OBJDIR=obj
BINDIR=bin

# Files
COMMON_SRC=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp)) ../constraints/concept.cpp ../utils/convert.cpp
COMMON=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(COMMON_SRC)))

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
alldiff: $(BINDIR)/$(EXEC_AD)
lineareq: $(BINDIR)/$(EXEC_LE)
lessthan: $(BINDIR)/$(EXEC_LT)

# Executables
$(BINDIR)/$(EXEC_AD): $(COMMON) $(OBJDIR)/all-diff.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(BINDIR)/$(EXEC_LE): $(COMMON) $(OBJDIR)/linear-eq.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(BINDIR)/$(EXEC_LT): $(COMMON) $(OBJDIR)/less-than.o
	$(CXX) -o  $@ $^ $(LDFLAGS)

# Common objects
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Objects of a specific contraint
$(OBJDIR)/all-diff.o: ../constraints/all-diff.cpp
	$(CXX) $(CXXFLAGS) -DCFN -c $< -o $@

$(OBJDIR)/linear-eq.o: ../constraints/linear-eq.cpp
	$(CXX) $(CXXFLAGS) -DCFN -c $< -o $@

$(OBJDIR)/less-than.o: ../constraints/less-than.cpp
	$(CXX) $(CXXFLAGS) -DCFN -c $< -o $@

.PHONY: clean

clean:
	rm -fr core *~ $(BINDIR)/$(EXEC_AD) $(OBJECTS)
