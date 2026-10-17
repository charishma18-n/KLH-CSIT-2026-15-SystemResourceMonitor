
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = build/readers_writers
SOURCE = src/main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean

