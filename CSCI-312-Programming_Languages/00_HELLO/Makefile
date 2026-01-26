CC=gcc
CFLAGS=-Wall -g -O0
LDFLAGS=
EXE=hello.out
SRC=$(EXE:.out=.c)
OBJ=$(SRC:.c=.o)

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ)
	-@echo "==========Linking=========="
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ): $(SRC)
	-@echo "==========Compiling=========="
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: run
run: $(EXE)
	-@echo "==========Running=========="
	./$(EXE)

.PHONY: clean
clean:
	-@echo "==========Cleaning=========="
	rm -f $(EXE) $(OBJ)

.PHONY: help
help:
	-@echo "make: Build the executable"
	-@echo "make run: Build and run the executable"
	-@echo "make clean: Clean up generated files"

