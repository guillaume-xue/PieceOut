# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 
SOURCES = Main.cpp Piece.cpp PieceOperateur.cpp
HEADERS = Piece.hpp PieceOperateur.hpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean