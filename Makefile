CC = gcc
CFLAGS = -Wall
LDFLAGS = `pkg-config --libs allegro-5 allegro_dialog-5 allegro_primitives-5`

ifeq ($(DEBUG), yes)
	CFLAGS += -g
else
	CFLAGS += -O3
endif

EXEC = bin/snake
SRC= $(wildcard src/*.c)
OBJ= $(subst src,obj, $(SRC:.c=.o))


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm obj/*

mrproper: clean
	rm bin/*