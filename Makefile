# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++23 -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin
TARGET = main

# Source and object files
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst %.cpp, %.o, $(subst $(SRC_DIR)/, $(BIN_DIR)/, $(SRCS)))

# Default rule
all: $(TARGET)

# Ensure bin directory exists
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Build final executable
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	@rm -rf $(BIN_DIR)
	@rm -f $(TARGET)

.PHONY: all clean
