EXE=enigma
OBJ=main.o reflector.o plugboard.o helper.o rotor.o
CXX=g++
CXXFLAGS=-Wall -g -MMD

$(EXE):$(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)

.PHONY: clean
