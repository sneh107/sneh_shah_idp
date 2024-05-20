CC = gcc
CFLAGS = -c -g -Wall
SRC = $(shell find src -name '*.c' ! -name 'main.c')
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: obj out lib lib/libll.a out/app run

obj:
	mkdir -p obj
	
out:
	mkdir -p out

lib:
	mkdir -p lib

lib/libll.a: $(OBJ)
	ar -rcs $@ $?

out/app: obj/main.o lib/libll.a
	$(CC) $< -L./lib -lll -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: run clean
run:
	@out/app

clean:
	rm -rf obj/ out/ lib/