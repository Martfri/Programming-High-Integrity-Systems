# Executable Target Name
TARGET_SO = phis.so
TARGET_BIN = phis_test

# Compiler
CC = gcc

# Compiler Options
CFLAGS += -Wall		# Enables general warnings
CFLAGS += -g		# Enables debug info
CFLAGS += -Werror	# Makes all warnings into errors
CFLAGS += -O1		# optimize for code size and execution time
CFLAGS += -pedantic # Enables warnings demanded by ISO C
CFLAGS += -fPIC

# Linker Options
#LDFLAGS += -lm		# Links Math Libraries
#LDFLAGS += -pthread	# Links POSIX threads library
LDFLAGS += -shared

.PHONY: default all build clean

default: test
all: test
build: $(TARGET_SO)

SRC=../voters.c ../distFunc.c ../sensors.c
OBJ=$(patsubst %.c, %.o, $(SRC))
HDR=$(wildcard *.h)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJ)

$(TARGET_SO): $(OBJ)
	$(CC)  $(OBJ) $(LDFLAGS) -o $@
	-rm -f ../*.o

$(TARGET_BIN):
	cd .. && make test/$(TARGET_BIN)

clean:
	-rm -f $(TARGET_SO)

test: build $(TARGET_BIN)
	python3 main.py
	-rm -f $(TARGET_BIN)
