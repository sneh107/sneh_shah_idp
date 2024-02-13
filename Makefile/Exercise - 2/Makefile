cfiles = $(wildcard ./*.c)
ofiles = $(patsubst ./%.c, build/%.o, $(cfiles))
hfiles = sampleAdd.h sampleLib.h
denable = 1
dflag = 

ifeq ($(denable), 1)
	dflag += -DDECORATE
endif

all: out/app

out/app: $(ofiles)
	gcc $^ -o $@ -L../Exercise3/ExtLib -lSample
	out/app

build/%.o: ./%.c $(hfiles)
	gcc -c $< -o $@ $(dflag)
	
clean:
	rm -rf build/* out/*

