CC = gcc
CFLAGS = -w -g
OBJS = c6 jit/jit

all: c6 jit/jit

c6: c6.c
	$(CC) $(CFLAGS) -D__C6__ $^ -o c6

qvm: jit/jit.c
	$(CC) $(CFLAGS) $^ -o qvm

clean:
	rm -f $(OBJS)
