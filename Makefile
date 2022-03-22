CC = gcc
CFLAGS = -w -g -DOS=LINUX
OBJS = c6 jit

all: c6 jit

c6: c6.c
	$(CC) $(CFLAGS) -D__C6__ $^ -o c6

jit: jit.c
	$(CC) $(CFLAGS) $^ -o jit

clean:
	rm -f $(OBJS)
