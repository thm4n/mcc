SRC_DIR := ./src
BIN_DIR := ./bin
LOGS_DIR := ./logs

C_SRC     := $(shell find ./src -type f -name "*.c")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_SRC))

CXX := gcc
C_FLAGS := -Wall -Werror
DBGFLAGS := -g3 -fsanitize=address -static-libasan
INC_FLAGS := -I$(SRC_DIR)

CXXFLAGS := $(C_FLAGS) $(DBGFLAGS) $(INC_FLAGS)

TARGET := $(BIN_DIR)/mcc

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(CXXFLAGS)

build: ${TARGET}
rebuild: clean build
clean:
	-@ rm -rf $(BIN_DIR)
	-@ rm -rf $(LOGS_DIR)

debug:
	@echo "NOT IMPLEMENTED YET"

run: build

rerun: clean run
