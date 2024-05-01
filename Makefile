CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lglut -lGLU -lGL -lm
BUILD_DIR = build

SRCS = $(wildcard src/*.cpp)
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

TARGET = $(BUILD_DIR)/main

# Build target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Compile source files
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build and run target
run: clean $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)