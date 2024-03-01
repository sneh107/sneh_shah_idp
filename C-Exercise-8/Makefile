SDIR = ./src
ODIR = ./obj
OUT = ./out

CFILES = $(wildcard $(SDIR)/*.c)
OFILES = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(CFILES))
EXEFILES = $(patsubst $(SDIR)/%.c,$(OUT)/%,$(CFILES))
TMPFILES = $(patsubst %.c,%,$(CFILES))

all: $(OFILES) $(EXEFILES)

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p obj out
	gcc -c $< -o $@

$(OUT)/%: $(ODIR)/%.o
	gcc $< -o $@
	
clean:
	rm -rf $(ODIR) $(OUT)
	rm -f $(TMPFILES)
	
	
.PHONY: all clean
