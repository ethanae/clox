# flags
CC = cc

# files
OBJS=main.o chunk.o debug.o memory.o

clox: $(OBJS)
	$(CC) -o clox $(OBJS)