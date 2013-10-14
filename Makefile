SFML_INCLUDE="../../SFML-2.1-sources/SFML-2.1/include"
SFML_LIBS="../../SFML-2.1-sources/build/lib"

CC=g++
CFLAGS=-c -Wall -I$(SFML_INCLUDE) -DSFML_DYNAMIC 
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
