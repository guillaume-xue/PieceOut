# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window
MACLDFLAGS = install_name_tool -add_rpath /usr/local/lib ebaucheVue
DIRMAIN = src
CONTROLLER = $(DIRMAIN)/controllers
VIEW = $(DIRMAIN)/views
MODEL = $(DIRMAIN)/models
SOURCES = $(VIEW)/ebaucheVue.cpp $(CONTROLLER)/MouseController.cpp $(CONTROLLER)/KeyboardController.cpp
HEADERS = $(VIEW)/ebaucheVue.hpp $(CONTROLLER)/MouseController.hpp $(CONTROLLER)/KeyboardController.hpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

mac : src/Main.cpp  $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c src/Main.cpp $(SOURCES) $(HEADERS)
	g++ -o Main *.o $(LDFLAGS)
	install_name_tool -add_rpath /usr/local/lib Main
	./Main
	
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(SOURCES:.cpp=.hpp.gch) *.o test

.PHONY: all clean
