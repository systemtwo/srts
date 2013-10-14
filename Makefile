SFML_INCLUDE="../../SFML2-master/SFML-master/include"
SFML_LIBS="../../SFML2-master/build/lib"

CC=g++
CFLAGS=-c -Wall -I$(SFML_INCLUDE) -DSFML_DYNAMIC
LDFLAGS=-L$(SFML_LIBS) -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXEC=main.exe

all: $(EXEC) 

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	del obj\*.o
	del $(EXEC)
