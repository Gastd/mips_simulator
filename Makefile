# @file Makefile
#
# @author Gabriel F P Araujo
#

#########
# Setup #
#########

# Default driver
# DRIVER ?= FSMDriver3

# Compiler & flags
CC       = g++
CXXFLAGS = -Wall -std=c++11 -g

# Target [folder(s)]
BIN_DIR = bin
OBJ_DIR = obj
TARGET  = $(BIN_DIR)/main

# Include directories
INC_DIR    = include/

# Source
# CLIENT_SRC_DIR = src/
# CLIENT_SRC     = WrapperBaseDriver.cpp SimpleParser.cpp CarState.cpp CarControl.cpp
SRC         = simulator.cpp
MAIN        = main
SRC_DIR     = src
MAIN_SRC    = main.cpp
# SRC         = $(notdir $(wildcard $(SRC_DIR)/*.cpp))

############
# Organize #
############
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))
MAIN_OBJ = $(OBJ_DIR)/$(MAIN).o

FLAGS      = $(CXXFLAGS) $(EXTFLAGS)
HEADERS    = $(addprefix -I,$(INC_DIR))
OBJECTS    = $(OBJ)

###########
# Targets #
###########
all: $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) -I$(INC_DIR)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CC) -c -o $@ $< $(CXXFLAGS) -I$(INC_DIR)

$(OBJ): $(SRC_DIR)/$(SRC) $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(HEADERS)

$(MAIN_OBJ): $(SRC_DIR)/$(MAIN_SRC) 
	$(CC) -c -o $@ $< $(CXXFLAGS) -I$(INC_DIR)

$(TARGET): dirs $(OBJ) $(MAIN_OBJ) $(BIN_DIR)
	$(CC) $(FLAGS) -o $(TARGET) $(MAIN_OBJ) $(HEADERS) $(OBJECTS)

clean:
	@rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* 
