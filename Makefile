
CC = gcc
CFLAGS = -Wall -g # -Wall enables all warnings, -g includes debug info
TARGET = a

# Define the object files
# $(patsubst %.c,%.o,$(wildcard *.c)) can automatically find all .c files
# and convert their names to .o (e.g., main.c -> main.o)
OBJ_FILES = menu.o task.o main.o

# Default target: builds the executable
# This rule says that $(TARGET) depends on all $(OBJ_FILES)
# Ifmenue is newer, the linking command will run.
main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
# Rule for compiling main.o from main.c
# This rule says main.o depends on main.c and utils.h
# If main.c or utils.h is newer than main.o, the command will run.
task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c -o task.o

# Rule for compiling utils.o from utils.c
# This rule says utils.o depends on utils.c and utils.h
# If utils.c or utils.h is newer than utils.o, the command will run.
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c -o menu.o

$(TARGET): $(OBJ_FILES)
	gcc $(OBJ_FILES) -o $(TARGET)
# Phony target for cleaning up compiled files
# .PHONY declares 'clean' as a phony target, meaning it's not a real file.
# This ensuresmenulways runs, even if a file named 'clean' exists.
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJ_FILES)

# Phony target for running the program
.PHONY: run
run: $(TARGET)
	./$(TARGET)
