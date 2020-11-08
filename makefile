CFLAGS := -Wall -Werror -std=c99

BINAME := ccollection
BINDIR := bin
OBJDIR := obj
INCDIR := inc
SRCDIR := src

OBJ := coop_object.o coop_string.o coop_list.o private/singlylinkedlist.o

OBJS := $(patsubst %, $(OBJDIR)/%, $(OBJ))

all: main
.PHONY: all

main: $(OBJS)
	$(CC) $(SRCDIR)/main.c $(OBJS) -o $(BINDIR)/$(BINAME) -I$(INCDIR) -O3 $(CFLAGS)

debug: $(OBJS)
	$(CC) $(SRCDIR)/main.c $(OBJS) -o $(BINDIR)/$(BINAME)_debug -I$(INCDIR) -g $(CFLAGS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/private/*.o
	rm -f $(BINDIR)/$(BINAME)
	rm -f $(BINDIR)/$(BINAME)_debug

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $< -c -o $@ -I$(INCDIR) $(CFLAGS)

$(OBJDIR)/private/%.o: $(SRCDIR)/private/%.c
	$(CC) $< -c -o $@ -I$(INCDIR) $(CFLAGS)
