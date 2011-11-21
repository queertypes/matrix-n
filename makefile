CXXFLAGS := -Wall -Wextra -std=c++0x -O2 -g -I.
EXE := fast-slater

all: $(EXE)

$(EXE) : $(EXE).cpp numerical/matrix.cpp
	g++ $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o $(EXE)
