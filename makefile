#
# NeuroSim Library Makefile
# Colby Horn
#

############################################################
# general build rules and data
############################################################
CC=g++
CFLAGS=-std=c++11 -Iinclude -Wall -c

OS=$(shell uname)
ifeq ($(OS),Linux)
$(info operating system detected as '$(OS)')
else ifeq ($(OS),Darwin)
$(info operating system detected as '$(OS)')
else
$(error unknown operating system detected '$(OS)')
endif

HEAD=$(wildcard include/*.hpp)

SRCDIR=src
OBJDIR=obj

all: binary library python

############################################################
# build rules for NeuroSim C++ dynamic library
############################################################

ifeq ($(OS),Linux)
LIBLDFLAGS=-shared
else ifeq ($(OS),Darwin)
LIBLDFLAGS=-dynamiclib
endif

LIBDIR=lib
LIBSRC=$(wildcard $(SRCDIR)/$(LIBDIR)/*.cpp)
LIBOBJ=$(patsubst $(SRCDIR)/$(LIBDIR)/%.cpp,$(OBJDIR)/$(LIBDIR)/%.o,$(LIBSRC))
ifeq ($(OS),Linux)
LIB=$(LIBDIR)/libneurosim.so
else ifeq ($(OS),Darwin)
LIB=$(LIBDIR)/libneurosim.dylib
endif

library: $(LIB)

$(LIB): $(LIBOBJ)
	@ mkdir -p $(LIBDIR)
	$(CC) -shared $^ -o $@

$(OBJDIR)/$(LIBDIR)/%.o: $(SRCDIR)/$(LIBDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)/$(LIBDIR)
	$(CC) $(CFLAGS) -fPIC $< -o $@

############################################################
# build rules for NeuroSim python module	
############################################################

PYTHON=python2.7
PYINC=-I/usr/include/$(PYTHON)
ifeq ($(OS),Linux)
# TODO check if -Wl,--export-dynamic is needed under Linux
PYLDFLAGS=-lboost_python -l$(PYTHON) -Wl,--export-dynamic
else ifeq ($(OS),Darwin)
# TODO find a more robust way to locate the python dynamic libraries for linking
PYLDFLAGS=-lboost_python -L/Library/Frameworks/Python.framework/Versions/2.7/lib/ -l$(PYTHON)
endif

PYDIR=python
PYSRC=$(wildcard $(SRCDIR)/$(PYDIR)/*.cpp)
PYOBJ=$(patsubst $(SRCDIR)/$(PYDIR)/%.cpp,$(OBJDIR)/$(PYDIR)/%.o,$(PYSRC))
PYLIB=$(PYDIR)/neurosim.so

python: $(PYLIB)

$(PYLIB): $(LIBOBJ) $(PYOBJ)
	@ mkdir -p $(PYDIR)
	$(CC) $(PYLDFLAGS) -shared $^ -o $@

$(OBJDIR)/$(PYDIR)/%.o: $(SRCDIR)/$(PYDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)/$(PYDIR)
	$(CC) $(CFLAGS) $(PYINC) -fPIC $< -o $@

############################################################
# build rules for NeuronSim binary executable
############################################################

ifeq ($(OS),Linux)
BINLDFLAGS=-Wl,-rpath=lib -Llib -lneurosim
else ifeq ($(OS),Darwin)
BINLDFLAGS=lib/libneurosim.dylib
endif

BINDIR=bin
BINSRC=$(wildcard $(SRCDIR)/*.cpp)
BINOBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(BINSRC))
BIN=$(BINDIR)/neurosim

binary: library $(BIN)

$(BIN): $(BINOBJ)
	@ mkdir -p $(BINDIR)
	$(CC) $(BINLDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

############################################################
# cleanup rules
############################################################

clean-library:
	- rm $(LIB)
	- rmdir $(LIBDIR)
	- rm $(LIBOBJ)
	- rmdir $(OBJDIR)/$(LIBDIR)

clean-python:
	- rm $(PYLIB)
	- rmdir $(PYDIR)
	- rm $(PYOBJ)
	- rmdir $(OBJDIR)/$(PYDIR)

clean: clean-library clean-python
	- rm $(BIN)
	- rmdir $(BINDIR)
	- rm $(BINOBJ)
	- rmdir $(OBJDIR)
