CC=g++

INCLUDES=-I include/
CFLAGS=
LDFLAGS=  

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, obj/%.o, $(SOURCES))
EXECUTABLE=build/interpreter

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean clean_obj clean_exe clean_~

clean: clean_obj clean_exe clean_~

clean_obj:
	rm -rf obj/*.o

clean_exe:
	rm -rf $(EXECUTABLE)

clean_~:
	rm -rf *~
	rm -rf src/*~
	rm -rf include/*~
	rm -rf tests/*~
