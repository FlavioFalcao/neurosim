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

SRCDIR=src
OBJDIR=obj
BINDIR=bin

HEAD=$(wildcard include/*.hpp)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
BIN=$(BINDIR)/neurosim

all : $(BIN)

$(BIN) : $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEAD)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(BIN)
	rmdir $(BINDIR)
	rm $(OBJ)
	rmdir $(OBJDIR)

