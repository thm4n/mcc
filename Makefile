HDR = $(shell find ./src -type f -name *.h)
SRC = $(shell find ./src -type f -name *.c)
OBJ = $(SRC:.c=.o)

TESTS_01 = $(shell find ./tests/stage_01 -type f -name *.c)
TESTS_02 = $(shell find ./tests/stage_02 -type f -name *.c)
TESTS_03 = $(shell find ./tests/stage_03 -type f -name *.c)
TESTS_04 = $(shell find ./tests/stage_04 -type f -name *.c)
TESTS_05 = $(shell find ./tests/stage_05 -type f -name *.c)
TESTS_06 = $(shell find ./tests/stage_06 -type f -name *.c)
TESTS_07 = $(shell find ./tests/stage_07 -type f -name *.c)
TESTS_08 = $(shell find ./tests/stage_08 -type f -name *.c)
TESTS_09 = $(shell find ./tests/stage_09 -type f -name *.c)
TESTS_10 = $(shell find ./tests/stage_10 -type f -name *.c)
TESTS = ${TESTS_01} ${TESTS_02} ${TESTS_03} ${TESTS_04} ${TESTS_05} ${TESTS_06} ${TESTS_07} ${TESTS_08} ${TESTS_09} ${TESTS_10}

CC = gcc
GDB = gdb

CC_INCS  = -I./src -I./src/ext
CC_DBG   = -g3 -fsanitize=address -static-libasan
CC_WARNS = -Wall

CC_FLAGS = ${CC_INCS} ${CC_DBG} ${CC_WARNS}

.PHONY: rmlogs clean rebuild

test: mcc
	./mcc ./tests/stage_01/valid/return_2.c

test01: mcc
	./mcc ${TESTS_01}
test02: mcc
	./mcc ${TESTS_02}
test03: mcc
	./mcc ${TESTS_03}
test04: mcc
	./mcc ${TESTS_04}
test05: mcc
	./mcc ${TESTS_05}
test06: mcc
	./mcc ${TESTS_06}
test07: mcc
	./mcc ${TESTS_07}
test08: mcc
	./mcc ${TESTS_08}
test09: mcc
	./mcc ${TESTS_09}
test10: mcc
	./mcc ${TESTS_10}

test-all: mcc
	./mcc ${TESTS}
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
