INCLUDES = -Iinclude -I/usr/local/include
LIBRARIES = -lglfw3 -framework Cocoa -framework IOKit -framework CoreVideo

demo: glad.o
	clang++ -Wall $(LIBRARIES) $(INCLUDES) src/Display.cpp src/main.cpp glad.o -o demo
	rm glad.o

glad.o:
	clang -Iinclude -c src/glad.c 

.PHONY: clean
clean: 
	rm demo *.o
