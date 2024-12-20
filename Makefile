# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -g
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window
MACLDFLAGS = install_name_tool -add_rpath /usr/local/lib ebaucheVue
DIRMAIN = src
SOURCES = $(wildcard $(DIRMAIN)/**/*.cpp) $(wildcard $(DIRMAIN)/*.cpp)
HEADERS = $(wildcard $(DIRMAIN)/**/*.hpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = main

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

mac: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(SOURCES)
	g++ -o Main *.o $(LDFLAGS)
	install_name_tool -add_rpath /usr/local/lib Main
	./Main
	
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DIRMAIN)/*.o *.o

.PHONY: all clean
