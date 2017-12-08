
INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc

RM = rm -rf

CC = g++

CPPFLAGS = -Wall -pedantic -ansi -std=c++11

OBJS = $(OBJ_DIR)/driver_dictionary.o

driverDictionary: clean dir $(OBJS)
	$(CC) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJS) 

$(OBJ_DIR)/driver_dictionary.o: $(SRC_DIR)/driver_dictionary.cpp $(INC_DIR)/dictionary.hpp
	$(CC) -c $(CPPFLAGS) -lm -I$(INC_DIR)/ -o $@ $<

doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

dir:
	mkdir -p bin build doc

clean: dir
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
	$(RM) $(DOC_DIR)/*

