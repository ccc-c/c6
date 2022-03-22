CC = gcc
CFLAGS = -w -g -DOS=LINUX
OBJS = c6 genasm

all: c6 genasm

c6: c6.c
	$(CC) $(CFLAGS) -D__C6__ $^ -o c6

genasm: genasm.c
	$(CC) $(CFLAGS) $^ -o genasm

clean:
	rm -f $(OBJS)
