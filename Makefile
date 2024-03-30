CXX = g++
CXXFLAGS = -Wall -std=c++11 -Isrc

SRC_DIR = src
BUILD_DIR = build
PUBLIC_DIR = webserver/public

SOURCES = $(wildcard $(SRC_DIR)/app/*.cpp) $(SRC_DIR)/main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

TARGET = $(BUILD_DIR)/myapp.exe

.PHONY: clean rebuild run

rebuild: clean $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: rebuild
	./$(TARGET)
