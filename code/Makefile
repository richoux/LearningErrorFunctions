EXEC_ALLDIFF=all-diff
EXEC_LESS=less_than

# Compiler flags
CXXFIRSTFLAGS= -Ofast -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter
CXXFIRSTFLAGSDEBUG= -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	CXXFLAGS= -std=c++14 $(CXXFIRSTFLAGS)
	CXXFLAGSDEBUG= -std=c++14 $(CXXFIRSTFLAGSDEBUG)
endif
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
	CXXFLAGS= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGS)
	CXXFLAGSDEBUG= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGSDEBUG)
	LDFLAGS=-pthread -lghost -lc++ -lc++abi
endif

# Directories
SRCDIR=. subghost
OBJDIR=obj
BINDIR=bin

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp))
SOURCES_ALLDIFF=$(filter-out ./less_than.cpp ./main_less_than.cpp, $(SOURCES))
SOURCES_LESS=$(filter-out ./all-diff.cpp ./main_all-diff.cpp, $(SOURCES))

OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))
OBJECTS_ALLDIFF=$(filter-out $(OBJDIR)/less_than.o $(OBJDIR)/main_less_than.o, $(OBJECTS))
OBJECTS_LESS=$(filter-out $(OBJDIR)/all-diff.o $(OBJDIR)/main_all-diff.o, $(OBJECTS))

# For rm
SOURCESTILDE=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp~))

vpath %.cpp $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
all: $(BINDIR)/$(EXEC_ALLDIFF) $(BINDIR)/$(EXEC_LESS)

debug: CXXFLAGS= $(CXXFLAGSDEBUG)
debug: $(BINDIR)/$(EXEC_ALLDIFF) $(BINDIR)/$(EXEC_LESS)

alldiff: $(BINDIR)/$(EXEC_ALLDIFF)

lessthan: $(BINDIR)/$(EXEC_LESS)

$(BINDIR)/$(EXEC_ALLDIFF): $(OBJECTS_ALLDIFF)
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(BINDIR)/$(EXEC_LESS): $(OBJECTS_LESS)
	$(CXX) -o  $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -fr core *~ $(BINDIR)/$(EXEC_ALLDIFF) $(BINDIR)/$(EXEC_LESS) $(OBJECTS) $(SOURCESTILDE) 
