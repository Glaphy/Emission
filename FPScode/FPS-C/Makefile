CC=gcc
CFLAGS=-Wall --std=c99
LDFLAGS=-lm
OBJ=fpstar.o fpshelper.o
EXE=fpstar.out
DBGFLAGS=-g

all: $(EXE)

debug: CFLAGS+=$(DBGFLAGS)
debug: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(LDFLAGS)

.PHONY: clean uncluttered

clean:
	rm fpstar.out
	rm *.o

uncluttered:
	rm *.o
