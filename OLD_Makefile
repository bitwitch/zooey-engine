INCLUDES = -Iinclude -I/usr/local/include
LIBRARIES = -lglfw3 -framework Cocoa -framework IOKit -framework CoreVideo
FLAGS = -Wall -std=c++11

demo: glad.o
	clang++ $(FLAGS) $(LIBRARIES) $(INCLUDES) src/*.cpp glad.o -o demo
	rm glad.o

glad.o:
	clang -Iinclude -c src/glad.c 

.PHONY: clean
clean: 
	rm demo *.o
