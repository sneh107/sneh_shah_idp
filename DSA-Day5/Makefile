CC = gcc
CFLAGS = -fpic -c -Wall -g
SRC = $(shell find src -name '*.c' ! -name 'main.c')
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: obj out lib lib/lib_linked_list5.so out/app run

obj:
	mkdir -p obj
	
out:
	mkdir -p out

lib:
	mkdir -p lib

lib/lib_linked_list5.so: $(OBJ)
	$(CC) -shared -o $@ $^
	sudo cp lib/lib_linked_list5.so /usr/lib/

out/app: src/main.c
	$(CC) $< -l_linked_list5 -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: run clean
run:
	@out/app

clean:
	rm -rf obj/ out/ lib/