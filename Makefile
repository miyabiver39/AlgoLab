CC=gcc
CFLAGS=-Iinclude
LDFLAGS=
SRC_DIR=src
OUT_DIR=build
OBJ_DIR=obj
TEST_DIR=tests
EXAMPLE_DIR=example
INCLUDE_DIR=include

DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

all: $(OUT_DIR) $(OBJ_DIR) $(OUT_DIR)/example
	$(OUT_DIR)/example

$(OUT_DIR)/example: $(EXAMPLE_DIR)/main.c $(OBJ_DIR)/hello.o $(OBJ_DIR)/Welford.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(OUT_DIR) $(OBJ_DIR) $(OUT_DIR)/test_hello $(OUT_DIR)/example
	$(OUT_DIR)/test_hello

$(OUT_DIR)/test_hello: $(TEST_DIR)/test_hello.c $(OBJ_DIR)/hello.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/hello.o: $(SRC_DIR)/hello.c $(INCLUDE_DIR)/hello.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Welford.o: $(SRC_DIR)/Welford.c $(INCLUDE_DIR)/Welford.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR) $(OBJ_DIR):
	@[ -d $@ ] || mkdir $(subst /,\,$@)

clean:
	rm -f $(OUT_DIR)/*
	rmdir $(OUT_DIR)
	rm -f $(OBJ_DIR)/*
	rmdir $(OBJ_DIR)
