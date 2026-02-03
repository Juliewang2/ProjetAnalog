CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++17

EXEC = analog
SRC = main.cpp LogStream.cpp Stats.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) -lstdc++ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

mrproper: clean

.PHONY: all clean mrproper
