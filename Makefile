SFML_INCLUDE="../../SFML-2.1-sources/SFML-2.1/include"
SFML_LIBS="../../SFML-2.1-sources/build/lib"

CC=g++
#CFLAGS=-c -Wall -I$(SFML_INCLUDE) -DSFML_DYNAMIC 
CFLAGS=-c -I$(SFML_INCLUDE) -DSFML_DYNAMIC 
LDFLAGS=-L$(SFML_LIBS) -lsfml-graphics -lsfml-window -lsfml-system

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXEC=main.exe

all: $(EXEC) 

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	del obj\*.o
	del $(EXEC)


#Dependancy Generation

#See 
#http://stackoverflow.com/questions/97338/gcc-dependency-generation-for-a-different-output-directory/97374#97374
#http://stackoverflow.com/questions/2394609/makefile-header-dependencies
#http://stackoverflow.com/questions/297514/how-can-i-have-a-makefile-automatically-rebuild-source-files-that-include-a-modi/297543#297543

#depend: .depend

#.depend: $(SOURCES)
#	del .depend
#	$(CC) $(CFLAGS) -MM $^ -MF .depend
#
#include .depend

