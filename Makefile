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
clean:
	$(RM) $(OBJ)/*.o $(BIN)\$(OBJ)\*.o

ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f

clean:
	$(RM) $(OBJ)/*.o $(BIN)/$(OBJ)/*.o
endif


