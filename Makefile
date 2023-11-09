CC        = gcc
CFLAGS    = -Wall -g
SOURCEDIR = src
BUILDDIR  = build

SOURCES  = $(shell find $(SOURCEDIR) -name '*.c')
BINARIES = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.bin, $(SOURCES))

.PHONY: all clean

all: compile

compile: $(BINARIES)

$(BUILDDIR)/%.bin: $(SOURCEDIR)/%.c $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(SOURCEDIR) $< -o $(basename $@)

$(BUILDDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)
