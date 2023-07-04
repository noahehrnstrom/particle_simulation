CXX := g++
CXXFLAGS := -O2 -march=native -Wall -Werror -Wextra -pedantic -std=c++23 -ffast-math
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := particle_simulation

SRC := main.cpp

all: $(TARGET)

$(TARGET):
	$(CXX) -o $@ $(SRC) $(SFML_LIBS) $(CXXFLAGS)

clean:
	rm -f $(TARGET)
