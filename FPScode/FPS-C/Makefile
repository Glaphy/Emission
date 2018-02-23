CC=gcc
CFLAGS=-Wall --std=gnu99
LDFLAGS= /usr/lib64/libsuperlu.so.5.1 /usr/lib64/atlas/libsatlas.so.3.10 -lm
OBJ=fpstar.o fpshelper.o csparse.o
EXE=fpstar.out
DBGFLAGS=-g

all: $(EXE)

debug: CFLAGS+=$(DBGFLAGS)
debug: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean uncluttered

clean:
	rm fpstar.out
	rm *.o
	rm *.dat

uncluttered:
	rm *.o

#gcc -Wall -std=c99 -o fpstar.out fpstar.c fpshelper.c csparse.c /usr/local/lib64/libsuperlu.a /usr/lib64/OpenBLAS/lib/libopenblas_haswellp-r0.3.0.dev.so -lm
