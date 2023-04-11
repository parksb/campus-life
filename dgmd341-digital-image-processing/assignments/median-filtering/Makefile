PKGS = `pkg-config --cflags --libs opencv4`
STD = c++20
FLAGS = -std=$(STD) $(PKGS) -Wno-deprecated-anon-enum-enum-conversion
CC = clang++ $(FLAGS)
SRC = main.cpp
TARGET = output

build:
	$(CC) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
