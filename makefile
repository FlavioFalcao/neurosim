#
# NeuroSim Library Makefile
# Colby Horn
#

# detect operating system and select appropriate build toolchain
OS=$(shell uname)
ifeq ($(OS),Linux)
CC=g++
CFLAGS=-std=c++11 -Iinclude -Wall
else ifeq ($(OS),Darwin)
CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -Iinclude -Wall
LDFLAGS=-lc++
else
$(error unknown operating system detected '$(OS)')
endif

# general build rules and data
HEAD=$(wildcard include/*.hpp)

SRCDIR=src
OBJDIR=obj

all: binary library python

# build rules for NeuronSim binary executable
BINDIR=bin
BINSRC=$(wildcard $(SRCDIR)/*.cpp)
BINOBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(BINSRC))
BIN=$(BINDIR)/neurosim

binary: library $(BIN)

$(BIN): $(BINOBJ)
	@ mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -Wl,-rpath=lib -Llib -lneurosim $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# build rules for NeuroSim C++ dynamic library
LIBDIR=lib
LIBSRC=$(wildcard $(SRCDIR)/$(LIBDIR)/*.cpp)
LIBOBJ=$(patsubst $(SRCDIR)/$(LIBDIR)/%.cpp,$(OBJDIR)/$(LIBDIR)/%.o,$(LIBSRC))
LIB=$(LIBDIR)/libneurosim.so

library: $(LIB)

$(LIB): $(LIBOBJ)
	@ mkdir -p $(LIBDIR)
	$(CC) $(LDFLAGS) -shared $^ -o $@

$(OBJDIR)/$(LIBDIR)/%.o: $(SRCDIR)/$(LIBDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)/$(LIBDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# build rules for NeuroSim python module
PYTHON=python2.7
PYINC=-I/usr/include/$(PYTHON)
PYLD=-lboost_python -l$(PYTHON)

PYDIR=python
PYSRC=$(wildcard $(SRCDIR)/$(PYDIR)/*.cpp)
PYOBJ=$(patsubst $(SRCDIR)/$(PYDIR)/%.cpp,$(OBJDIR)/$(PYDIR)/%.o,$(PYSRC))
PYLIB=$(PYDIR)/neurosim.so

python: $(PYLIB)

$(PYLIB): $(LIBOBJ) $(PYOBJ)
	@ mkdir -p $(PYDIR)
	$(CC) $(LDFLAGS) $(PYLD) -shared -Wl,--export-dynamic $^ -o $@

$(OBJDIR)/$(PYDIR)/%.o: $(SRCDIR)/$(PYDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)/$(PYDIR)
	$(CC) $(CFLAGS) $(PYINC) -fPIC -c $< -o $@

# cleanup rules
clean:
	- rm $(BIN)
	- rmdir $(BINDIR)
	- rm $(LIB)
	- rmdir $(LIBDIR)
	- rm $(PYLIB)
	- rmdir $(PYDIR)
	- rm $(BINOBJ)
	- rm $(LIBOBJ)
	- rm $(PYOBJ)
	- rmdir $(OBJDIR)/$(LIBDIR)
	- rmdir $(OBJDIR)/$(PYDIR)
	- rmdir $(OBJDIR)

