CC=g++

INCLUDES=-I src/include/
CFLAGS=
LDFLAGS=  

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, obj/%.o, $(SOURCES))
EXECUTABLE=bin/as

all: make_dirs $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean clean_obj clean_exe clean_tests clean_~ make_dirs

make_dirs:
	mkdir -p bin
	mkdir -p obj

clean: clean_obj clean_exe clean_tests clean_~

clean_obj: 
	rm -rf obj/*.o

clean_exe:
	rm -rf $(EXECUTABLE)

clean_~:
	rm -rf *~
	rm -rf src/*~
	rm -rf include/*~
	rm -rf tests/*~
clean_test: 
	rm -rf tests/*.o
