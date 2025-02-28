CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
DEBUGFLAGS = -g
TARGET = runRRT
SRC = runRRT.cpp RRT.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)