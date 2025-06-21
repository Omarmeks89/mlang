C_STD = c99
C_CMP = gcc
DEST  = clox

GCC_FLAGS = -g -Wall -Wextra -Werror -Wunused

SRC = value.c memory.c chunk.c clox_debug.c main.c
OBJS = $(SRC:.c=.o)

.PHONY: all clear

all: $(DEST)

# assembly
$(DEST): $(OBJS)
	$(C_CMP) -std=$(C_STD) $(GCC_FLAGS) -o $@ $^

clear:
	rm -rf *.o
