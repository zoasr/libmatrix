CC=g++
INCLUDE=include
BIN=bin
SRC=src
OBJ=obj
INCLUDES=$(wildcard $(INCLUDE)/*.cpp)
SRCS=$(wildcard $(SRC)/*.cpp)
INCLUDEBINS=$(patsubst $(INCLUDE)/%.cpp, $(OBJ)/%.o, $(INCLUDES))
SRCBINS=$(patsubst $(SRC)/%.cpp, $(BIN)/$(OBJ)/%.o, $(SRCS))
BINS=$(INCLUDEBINS) $(SRCBINS)
OUTPUTS=$(patsubst $(SRC)/%.cpp, %, $(SRCS))

all: $(OUTPUTS)

$(OUTPUTS): %: $(BINS)
	$(CC) $(INCLUDEBINS) $(BIN)/$(OBJ)/$@.o -o $(BIN)/$@

$(BIN)/$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $^ -o $@

$(OBJ)/%.o: $(INCLUDE)/%.cpp
	$(CC) -c $^ -o $@

ifeq ($(OS),Windows_NT)
RM = del /Q /F
CP = copy /Y
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
endif

all: main

main: main.o matrix.o _2DVector.o console_color.o
	g++ main.o matrix.o _2DVector.o console_color.o -o main

main.o: src/main.cpp
	g++ -c src/main.cpp

matrix.o: include/matrix.cpp include/matrix.h
	g++ -c include/matrix.cpp include/matrix.h

_2DVector.o: include/_2DVector.cpp include/_2DVector.h
	g++ -c include/_2DVector.cpp include/_2DVector.h

console_color.o: include/console_color.cpp include/console_color.h
	g++ -c include/console_color.cpp include/console_color.h

clean:
	$(RM) *.o *.exe main