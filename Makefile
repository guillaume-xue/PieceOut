# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -g
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window
DIRMAIN = src
DIRTEST = test
SOURCES = $(wildcard $(DIRMAIN)/**/*.cpp) $(wildcard $(DIRMAIN)/*.cpp)
SOURCESTEST = $(wildcard $(DIRTEST)/**/*.cpp) $(wildcard $(DIRTEST)/*.cpp)
HEADERS = $(wildcard $(DIRMAIN)/**/*.hpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = main

# Règles
all: $(EXECUTABLE)
	./$(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

mac: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(SOURCES)
	g++ -o main *.o $(LDFLAGS)
	install_name_tool -add_rpath /usr/local/lib Main
	./main

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DIRMAIN)/*.o *.o $(DIRTEST)/**/*.o Main Main_test

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXECUTABLE)

.PHONY: all clean
