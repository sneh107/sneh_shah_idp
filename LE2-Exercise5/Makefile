SDIR = ./src
ODIR = ./obj
OUT = ./out

CFILES = $(wildcard $(SDIR)/*.c)
OFILES = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(CFILES))
EXEFILES = $(patsubst $(SDIR)/%.c,$(OUT)/%,$(CFILES))
TMPFILES = $(patsubst %.c,%,$(CFILES))
CFLAGS = -g -Wall -Wextra

all: $(ODIR) $(OUT) $(OFILES) $(EXEFILES)

$(ODIR):
	mkdir -p $(ODIR)

$(OUT):
	mkdir -p $(OUT)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $< -o $@

$(OUT)/%: $(ODIR)/%.o
	gcc $(CFLAGS) $< -o $@
	
clean:
	rm -rf $(ODIR) $(OUT)
	@rm -f $(TMPFILES)
	
.PHONY: all clean