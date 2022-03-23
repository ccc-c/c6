CC = gcc
CFLAGS = -w -g -m32
OBJS = c6 genasm jit

all: c6 genasm jit

c6: c6.c
	$(CC) $(CFLAGS) $^ -o c6

genasm: genasm.c
	$(CC) $(CFLAGS) $^ -o genasm

jit: jit.c
	$(CC) $(CFLAGS) $^ -o jit -ldl

clean:
	rm -f $(OBJS)
