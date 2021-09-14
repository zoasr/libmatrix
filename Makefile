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