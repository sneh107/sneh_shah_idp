SRCS = $(shell find . -name '*.c' ! -name 'test.c')
OBJS = $(patsubst %.c, obj/%.o, $(notdir $(SRCS)))
CC = gcc
CFLAGS = -Wall -Wextra
# dirs = $(shell find ./src -type d ! -name "src")
# finaldirs = $(patsubst %, %/%.c, $(dirs))

# print:
# 	@echo "$(SRCS)"
# 	@echo "$(OBJS)"
# 	@echo "$(dirs)"
# 	@echo "$(finaldirs)"

all: out obj out/userPhoneDikhao run

obj:
	mkdir -p obj

out:
	mkdir -p out

run:
	out/userPhoneDikhao

out/userPhoneDikhao: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

obj/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ./src/buy/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ./src/common/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ./src/search/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj out

.PHONY: all clean