srcs = $(shell find . -name '*.c' ! -name 'test.c')
ofs = $(patsubst %.c, obj/%.o, $(notdir $(srcs)))
dirs = $(shell find ./src -type d ! -name "src")
finaldirs = $(patsubst %, %/%.c, $(dirs))

# print:
# 	@echo "$(srcs)"
# 	@echo "$(ofs)"
# 	@echo "$(dirs)"
# 	@echo "$(finaldirs)"

all: out obj out/adminPhoneDikhao run

obj:
	mkdir -p obj

out:
	mkdir -p out

run:
	out/adminPhoneDikhao

out/adminPhoneDikhao: $(ofs)
	gcc $^ -o $@

obj/%.o: ./src/%.c ./inc/main.h ./inc/common/utils.h
	gcc -c $< -o $@

obj/%.o: ./src/addMobile/%.c ./inc/common/utils.h ./inc/addMobile/addMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/deleteMobile/%.c ./inc/common/utils.h
	gcc -c $< -o $@

obj/%.o: ./src/searchMobile/%.c ./inc/common/utils.h ./inc/searchMobile/searchMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/editMobile/%.c ./inc/common/utils.h ./inc/searchMobile/searchMobile.h ./inc/editMobile/editMobile.h
	gcc -c $< -o $@

obj/%.o: ./src/common/%.c ./inc/common/utils.h 
	gcc -c $< -o $@
	
clean:
	rm -rf obj out

.PHONY: all clean