srcs = $(shell find . -name '*.c' ! -name 'test.c')
ofs = $(patsubst %.c, obj/%.o, $(notdir $(srcs)))
dirs = $(shell find ./src -type d ! -name "src")
finaldirs = $(patsubst %, %/%.c, $(dirs))

# print:
# 	@echo "$(srcs)"
# 	@echo "$(ofs)"
# 	@echo "$(dirs)"
# 	@echo "$(finaldirs)"

all: out obj out/adminPhoneDikhao

obj:
	mkdir -p obj

out:
	mkdir -p out

out/adminPhoneDikhao: $(ofs)
	gcc $^ -o $@

obj/%.o: ./src/%.c  ./inc/struct.h  ./inc/main.h ./inc/utils.h
	gcc -c $< -o $@

obj/%.o: ./src/addMobile/%.c ./inc/struct.h ./inc/utils.h ./inc/addMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/deleteMobile/%.c ./inc/struct.h ./inc/utils.h
	gcc -c $< -o $@

obj/%.o: ./src/searchMobile/%.c ./inc/struct.h ./inc/utils.h ./inc/searchMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/editMobile/%.c ./inc/struct.h ./inc/utils.h ./inc/searchMobile.h ./inc/editMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/common/%.c ./inc/struct.h ./inc/utils.h 
	gcc -c $< -o $@
	
clean:
	rm -rf obj out

.PHONY: all clean