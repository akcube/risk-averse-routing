IDIR=include
SDIR=src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=$(SDIR)/obj
LDIR =lib

LIBS=-lm

_DEPS = heaps.h 

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = routing.o heaps.o 

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

routing: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 