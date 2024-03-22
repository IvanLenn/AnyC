# Define the compiler
CXX=g++

# Define compiler flags
CXXFLAGS=-O3 -Wall -g -std=c++17 -DDEBUG

# Define the name of the executable
TARGET=any

# Specify the source files
SOURCES=any.cpp main.cpp

# Define the object files from the source files
OBJECTS=$(SOURCES:.cpp=.o)

# The first rule is the default, building the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Rule for compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -f $(TARGET) $(OBJECTS)
