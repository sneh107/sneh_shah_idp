CC = gcc
CFLAGS = -g -Wall -Wextra -pthread
SERVERSRC = $(wildcard server/*.c)
CLIENTSRC = $(wildcard client/*.c)

# print:
# 	@echo $(SERVERSRC)
# 	@echo $(CLIENTSRC)

all: out out/server out/client

out:
	mkdir -p out

out/server: $(SERVERSRC) inc/server.h inc/common.h
	gcc $(CFLAGS) $^ -o $@

out/client: $(CLIENTSRC) inc/client.h inc/common.h
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -rf out/
