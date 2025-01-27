# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
OBJ_DIR = obj
TARGET = perceptron

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build files
clean:
    rm -f $(OBJ_DIR)/*.o $(TARGET)

# Create object directory if not exists
$(shell mkdir -p $(OBJ_DIR))

.PHONY: all clean
