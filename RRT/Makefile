CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 

OPENCV_CFLAGS  = $(shell pkg-config --cflags opencv4)
OPENCV_LDFLAGS = $(shell pkg-config --libs opencv4)

DEBUGFLAGS = -g
TARGET = runRRT
SRC = runRRT.cpp RRT.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(OPENCV_LDFLAGS) -o $(TARGET)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

