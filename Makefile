# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Isrc

# Source and build directories
SRC_DIR = src
BUILD_DIR = build
PUBLIC_DIR = webserver/public

# Find cpp files in src/app directory and main.cpp
SOURCES = $(wildcard $(SRC_DIR)/app/*.cpp) $(SRC_DIR)/main.cpp
# Object files to build, mirrored in build directory
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

# Target executable name
TARGET = $(BUILD_DIR)/myapp.exe

# Default rule to build the project
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@

# Rule to compile object files, creating directories as needed
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

# A phony target to avoid conflict with files of the same name
.PHONY: all clean
