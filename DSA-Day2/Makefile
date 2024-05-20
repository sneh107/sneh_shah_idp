# CC = gcc
# CFLAGS = -c -g -Wall -fpic
# SRC = $(shell find src -name '*.c' ! -name 'main.c')
# OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

# all: obj out lib/libll1.so out/app run

# obj:
# 	mkdir -p obj
	
# out:
# 	mkdir -p out

# lib/libll1.so: $(OBJ)
# 	$(CC) -shared -o $@ $^

# out/app: obj/main.o
# 	$(CC) $< -lll1 -o $@

# obj/%.o: src/%.c
# 	$(CC) $(CFLAGS) $< -o $@

# .PHONY: run clean copy
# run:
# 	@out/app

# clean:
# 	rm -rf obj/ out/

# copy:
# 	sudo cp lib/libll1.so /usr/lib/

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