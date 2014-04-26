#
# NeuroSim Library Makefile
# Colby Horn
#

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

HEAD=$(wildcard include/*.hpp)

SRCDIR=src
OBJDIR=obj

LIBDIR=lib
LIBSRC=$(wildcard $(SRCDIR)/$(LIBDIR)/*.cpp)
LIBOBJ=$(patsubst $(SRCDIR)/$(LIBDIR)/%.cpp,$(OBJDIR)/$(LIBDIR)/%.o,$(LIBSRC))
LIB=$(LIBDIR)/libneurosim.so

BINDIR=bin
BINSRC=$(wildcard $(SRCDIR)/*.cpp)
BINOBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(BINSRC))
BIN=$(BINDIR)/neurosim

all: binary library

binary: library $(BIN)

$(BIN): $(BINOBJ)
	@ mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -Wl,-rpath=lib -Llib -lneurosim $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

library: $(LIB)

$(LIB): $(LIBOBJ)
	@ mkdir -p $(LIBDIR)
	$(CC) $(LDFLAGS) -shared $^ -o $@

$(OBJDIR)/$(LIBDIR)/%.o: $(SRCDIR)/$(LIBDIR)/%.cpp $(HEAD)
	@ mkdir -p $(OBJDIR)/$(LIBDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	- rm $(LIB)
	- rmdir $(LIBDIR)
	- rm $(LIBOBJ)
	- rmdir $(OBJDIR)/$(LIBDIR)
	- rm $(BIN)
	- rmdir $(BINDIR)
	- rm $(BINOBJ)
	- rmdir $(OBJDIR)


