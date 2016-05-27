COPTS= -I. -Iexternal

CXX := g++
CXXFLAGS := -g -Wall -Wextra -std=c++11 -fdiagnostics-color  $(COPTS)
LDFLAGS :=

# Rule for building .o from .cpp with dependency generation
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS)  -MD $*.cpp -o $*.o

default: autotype

AUTOTYPE_SRC =\
	src/class.h src/class.cpp\
	src/code.h src/code.cpp\
	src/enum.h src/enum.cpp\
	src/parser.h src/parser.cpp\
	src/type.h src/type.cpp\
	src/typedef.h src/typedef.cpp\
	src/utility.h src/utility.cpp\
	src/ast.h src/ast.cpp\
	src/options.h src/options.cpp\
	src/main.cpp

AUTOTYPE_CPP = $(filter %.cpp,$(AUTOTYPE_SRC))
AUTOTYPE_OBJ = $(AUTOTYPE_CPP:.cpp=.o)

autotype: $(AUTOTYPE_OBJ) $(AUTOTYPE_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o autotype $(AUTOTYPE_OBJ)

clean:
	-rm -f autotype $(AUTOTYPE_OBJ)
	-find -iname "*.d" -exec rm -f {} \; -print

-include $(AUTOTYPE_OBJ:.o=.d)
