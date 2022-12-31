PKGS = `pkg-config --cflags --libs glfw3 glm`
LIBS = -I include
STD = c++20
FLAGS = -std=$(STD) $(PKGS) $(LIBS) -framework OpenGL -Wno-deprecated-declarations
CC = clang++ $(FLAGS)
SRC = main.cpp j3a.cpp
TARGET = output

build:
	$(CC) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
