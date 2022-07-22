SRC_DIR=src
INCL_DIR =include
OBJ_DIR=obj
BUILD_DIR=build

CC=cc
CFLAGS=-I$(INCL_DIR)

_DEPS = chunk.h memory.h common.h debug.h value.h
DEPS = $(patsubst %,$(INCL_DIR)/%,$(_DEPS))

_OBJ = main.o chunk.o memory.o debug.o value.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

$(OBJ_DIR)/%.o: src/%.c $(DEPS)
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/clox: $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(INCL_DIR)/*~ 