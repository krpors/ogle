CC=g++
CFLAGS=-O0 -ggdb -Wall -c
LDFLAGS=-lsfml-system -lsfml-window

SRC=./src
BIN=./bin
DOC=./doc

# Object files
OBJECTS=$(BIN)/ogle.o $(BIN)/core.o

# Following targets build the source files.
.PHONY: all
all: init $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BIN)/ogle

$(BIN)/ogle.o: $(SRC)/ogle.cpp $(SRC)/ogle.hpp
	$(CC) $(CFLAGS) $(SRC)/ogle.cpp -o $@
	
$(BIN)/core.o: $(SRC)/core.cpp $(SRC)/core.hpp
	$(CC) $(CFLAGS) $(SRC)/core.cpp -o $@

.PHONY: init
init:
	@mkdir -p $(BIN)

# Target: clean
# Purpose: cleans up generated binaries
#
.PHONY: clean
clean:
	rm -rf $(BIN)/*
