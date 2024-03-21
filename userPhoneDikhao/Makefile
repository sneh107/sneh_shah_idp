srcs = $(shell find . -name '*.c' ! -name 'test.c')
ofs = $(patsubst %.c, obj/%.o, $(notdir $(srcs)))
dirs = $(shell find ./src -type d ! -name "src")
finaldirs = $(patsubst %, %/%.c, $(dirs))

# print:
# 	@echo "$(srcs)"
# 	@echo "$(ofs)"
# 	@echo "$(dirs)"
# 	@echo "$(finaldirs)"

all: out obj out/userPhoneDikhao

obj:
	mkdir -p obj

out:
	mkdir -p out

out/userPhoneDikhao: $(ofs)
	gcc $^ -o $@

obj/%.o: ./src/%.c
	gcc -c $< -o $@

obj/%.o: ./src/buy/%.c
	gcc -c $< -o $@

obj/%.o: ./src/common/%.c
	gcc -c $< -o $@

obj/%.o: ./src/search/%.c
	gcc -c $< -o $@

clean:
	rm -rf obj out

.PHONY: all clean