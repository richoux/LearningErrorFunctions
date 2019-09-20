EXEC=sudoku

# Compiler flags
MYFLAGS=
CXXFIRSTFLAGS= -Ofast -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter
CXXFIRSTFLAGSDEBUG= -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	CXXFLAGS= -std=c++14 $(CXXFIRSTFLAGS) $(MYFLAGS)
	CXXFLAGSDEBUG= -std=c++14 $(CXXFIRSTFLAGSDEBUG) $(MYFLAGS)
	LDFLAGS=-pthread -lghost
endif
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
	CXXFLAGS= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGS) $(MYFLAGS)
	CXXFLAGSDEBUG= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGSDEBUG) $(MYFLAGS)
	LDFLAGS=-pthread -lghost -lc++ -lc++abi
endif

# Directories
SRCDIR=. ../constraints/
HPPDIR=../constraints/
OBJDIR=obj
BINDIR=bin

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp))
OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

# For rm
SOURCESTILDE=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp~))

vpath %.cpp $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules

all: $(BINDIR)/$(EXEC)

debug: CXXFLAGS=$(CXXFLAGSDEBUG)
debug: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CXX) -I$(HPPDIR) -o  $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -fr core *~ $(BINDIR)/$(EXEC) $(OBJECTS) $(SOURCESTILDE) 
