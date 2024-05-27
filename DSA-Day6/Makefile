CC = gcc
CFLAGS = -c -g -Wall -Wextra
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: obj out out/app run

obj:
	mkdir -p obj
	
out:
	mkdir -p out

out/app: $(OBJ)
	$(CC) $^ -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@
	
run:
	@out/app

clean:
	rm -rf obj/ out/