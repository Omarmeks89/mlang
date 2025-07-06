# === main compiler settings
C_STD = c99
C_CMP = gcc
DEST  = clox

GCC_FLAGS = -g -Wall -Wextra -Werror -Wunused

SRC = value.c memory.c chunk.c clox_debug.c main.c
OBJS = $(SRC:.c=.o)

# === test settings
CHECK_FLAGS = -lcheck -lsubunit -lpthread -lm
TEST = tests
TEST_SRC = ./mem/mem_class.c
TEST_OBJS = $(TEST_SRC:.c=.o)
TEST_MAIN = ./test/mem_unittest/mem_class_test.c

# === lint settings (clang-tidy)
C_LINT = lint
C_TIDY = clang-tidy
C_CHECKS = 'clang-analyzer-*,bugprone-*,readability-*,performance-*'
C_CHECKS_ALL = '*'
C_HEADERS = '.*'

.PHONY: all clear $(TEST) $(C_LINT)

all: $(DEST)

# assembly
$(DEST): $(OBJS)
	@echo '> build clox...'
	@$(C_CMP) -std=$(C_STD) $(GCC_FLAGS) -o $@ $^
	@echo '> build done'

# test assembly
$(TEST): $(TEST_OBJS)
	@echo '> build tests...'
	@$(C_CMP) -std=$(C_STD) -o $@ $^ $(TEST_MAIN) $(CHECK_FLAGS)
	@echo '> done'

# linter
$(C_LINT):
	@echo '> run lint check... [clang-tidy]'
	@$(C_TIDY) -checks=$(C_CHECKS_ALL) -header-filter=$(C_HEADERS) main.c -- -Iinclude/
	@echo '> lint check done'

clear:
	rm -rf *.o tests
