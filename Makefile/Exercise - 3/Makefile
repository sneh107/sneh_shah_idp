srcs = $(shell find . -name '*.c')
ofs = $(patsubst %.c, build/%.o, $(notdir $(srcs)))

denable = 1
dflag = 

ifeq ($(denable), 1)
	dflag += -DDECORATE
endif

all: out/app

out/app: $(ofs)
	gcc $^ -o $@
	@echo "-------------------------------"
	@out/app
	
build/%.o: ./%.c $(hfiles)
	gcc -c $< -o $@ $(dflag)
	
build/%.o: ./commonMod1/%.c
	gcc -c $< -o $@
	
build/%.o: ./commonMod2/%.c
	gcc -c $< -o $@
	
clean:
	rm -rf build/* out/*
