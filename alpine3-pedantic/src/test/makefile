# Executable Target Name
TARGET = phis.so

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
build: $(TARGET)

SRC=../voters.c ../distFunc.c ../sensors.c
OBJ=$(patsubst %.c, %.o, $(SRC))
HDR=$(wildcard *.h)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJ)

$(TARGET): $(OBJ)
	$(CC)  $(OBJ) $(LDFLAGS) -o $@
	-rm -f ../*.o

clean:
	-rm -f $(TARGET)

test: build
	python3 main.py
