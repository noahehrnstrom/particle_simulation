CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wextra -pedantic -march=native -O3 -ffast-math -ftree-vectorize -funroll-loops
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
OMP_FLAG := -fopenmp

TARGET := simulation

SRC := src/main.cpp src/helper.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(SFML_LIBS) $(OMP_FLAG)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(OMP_FLAG)

clean:
	rm -f $(TARGET) $(OBJ)
