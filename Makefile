HDR = $(shell find ./src -type f -name *.h)
SRC = $(shell find ./src -type f -name *.c)
OBJ = $(SRC:.c=.o)

CC = gcc
GDB = gdb

CC_INCS  = -I./src -I./src/ext
CC_DBG   = -g3 -fsanitize=address -static-libasan
CC_WARNS = -Wall

CC_FLAGS = ${CC_INCS} ${CC_DBG} ${CC_WARNS}

.PHONY: rmlogs clean rebuild

test: mcc
	./mcc ./tests/stage_01/valid/return_2.c
# @echo $(TESTS)
# ./test_compiler.sh ./mcc $(TESTS)

run: mcc
	@./mcc

rerun: clean mcc
	@./mcc

build: mcc

rebuild: clean mcc

rmlogs:
	@rm -f ./logs/*

clean: rmlogs
	@rm -rf $(shell find . -type f -name *.o)
	@rm -rf ./mcc

mcc: ${OBJ}
	${CC} -o $@ $^ ${CC_FLAGS}

%.o: %.c
	${CC} -o $@ -c $^ ${CC_FLAGS}
