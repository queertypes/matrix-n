CXXFLAGS := -Wall -Wextra -std=c++0x -O2 -g
EXE := fast-slater

all: $(EXE)

$(EXE) : $(EXE).cpp
	g++ $(CXXFLAGS) $^ -o $@

clean:
	rm -f *.o $(EXE)
