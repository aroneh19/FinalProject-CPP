# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Directories
SRC_DIR = src
BIN_DIR = bin

# Target executable
TARGET = $JRPG

# Find all .cpp source files automatically
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")

# Generate .o file paths in bin/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))

# Default rule: Build the game
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # ✅ Ensure the bin/ directory exists
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  # ✅ Link all object files

# Compile each .cpp file into .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # ✅ Ensure necessary subdirectories exist
	$(CXX) $(CXXFLAGS) -c $< -o $@  # ✅ Compile the .cpp file

# Clean compiled files
clean:
	@rm -rf $(BIN_DIR)/*  # ✅ Remove all object files & the executable

.PHONY: all clean