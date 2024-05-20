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

# CC = gcc
# CFLAGS = -fpic -c -g -Wall
# LDFLAGS = -L./lib
# LDLIBS = -lll
# SRC = $(shell find src -name '*.c' ! -name 'main.c')
# OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

# all: obj out lib/libll.so out/app run

# obj:
# 	mkdir -p obj
	
# out:
# 	mkdir -p out

# lib/libll.so: $(OBJ)
# 	$(CC) -shared -o $@ $^

# out/app: obj/main.o lib/libll.so
# 	$(CC) $< $(LDFLAGS) $(LDLIBS) -o $@

# obj/main.o: src/main.c
# 	gcc -c -g $< -o $@

# obj/%.o: src/%.c
# 	$(CC) $(CFLAGS) $< -o $@

# .PHONY: run clean
# run:
# 	@out/app

# clean:
# 	rm -rf obj/ out/

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