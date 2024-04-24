cfiles = $(wildcard src/*.c)
ofiles = $(patsubst src/%.c, obj/%.o, $(cfiles))

all: obj out out/app run

obj:
	mkdir -p obj
	
out:
	mkdir -p out

out/app: $(ofiles)
	gcc $^ -o $@

obj/%.o: src/%.c
	gcc -c $< -o $@
	
run:
	@out/app

clean:
	rm -rf obj/ out/
