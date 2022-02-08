CC=g++
INCLUDE=include
BIN=bin
SRC=src
OBJ=obj
SHARED=shared
STATIC=static
FOLDERS=$(BIN) $(BIN)/$(OBJ) $(OBJ)
INCLUDES=$(wildcard $(INCLUDE)/*.cpp)
SRCS=$(wildcard $(SRC)/*.cpp)
INCLUDEBINS=$(patsubst $(INCLUDE)/%.cpp, $(OBJ)/%.o, $(INCLUDES))
SRCBINS=$(patsubst $(SRC)/%.cpp, $(BIN)/$(OBJ)/%.o, $(SRCS))
BINS=$(INCLUDEBINS) $(SRCBINS)
OUTPUTS=$(patsubst $(SRC)/%.cpp, %, $(SRCS))

all: $(FOLDERS) $(OUTPUTS)


$(OUTPUTS): %: $(BINS)
	$(CC) $(INCLUDEBINS) $(BIN)/$(OBJ)/$@.o -o $(BIN)/$@

$(BIN)/$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $^ -o $@

$(OBJ)/%.o: $(INCLUDE)/%.cpp
	$(CC) -c $^ -o $@ -fPIC

ifeq ($(OS),Windows_NT)
RM = del /Q /F
CP = copy /Y

$(FOLDERS):
	@if not exist "$@" mkdir "$@"

shared: libmatrix.dll

static: libmatrix.a


libmatrix.dll: $(INCLUDEBINS)
	@if not exist "$(SHARED)/windows" mkdir "$(SHARED)/windows"
	$(CC) -shared $^ -o shared/windows/$@ -fPIC

libmatrix.a: $(INCLUDEBINS)
	@if not exist "$(STATIC)/windows" mkdir "$(STATIC)/windows"
	ar rcs $(STATIC)/windows/$@ $^
clean:
	@if exist $(OBJ)\*.o $(RM) $(OBJ)\*.o $(BIN)\$(OBJ)\*.o
	@if exist $(BIN) $(RM) $(BIN)\*
	@if exist $(SHARED) $(RM) $(SHARED)\windows\*.dll
	@if exist $(STATIC) $(RM) $(STATIC)\windows\*.a

ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f

$(FOLDERS):
	@if [ ! -d $@ ]; then\
		mkdir "$@";\
	fi\

shared: libmatrix.so

static: libmatrix.a


libmatrix.so: $(INCLUDEBINS)
	@if [ ! -d $(SHARED) ] && [ ! -d $(SHARED)/linux ]; then\
		mkdir "$(SHARED)";\
		mkdir "$(SHARED)/linux";\
	fi\
	$(CC) -shared $^ -o shared/linux/$@ -fPIC

libmatrix.a: $(INCLUDEBINS)
	@if [ ! -d $(STATIC) ]; then\
		mkdir "$(STATIC)";\
	fi\

	@if [ ! -d $(STATIC)/linux ]; then\
		mkdir "$(STATIC)/linux";\
	fi\

	ar rcs $(STATIC)/linux/$@ $^
clean:
	@if [ -d $(OBJ) ]; then\
		$(RM) $(OBJ)/*.o;\
	fi\

	@if [ -d $(BIN) ]; then\
		$(RM) $(BIN)/*;\
	fi\

	@if [ -d $(SHARED) ]; then\
		$(RM) $(SHARED)/linux/*.so;\
	fi\

	@if [ -d $(STATIC) ]; then\
		$(RM) $(STATIC)/linux/*.a;\
	fi\

endif


