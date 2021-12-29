# Executable Target Name
TARGET = phis

# Compiler
CC = gcc

# Linter
LINT = flint

# Compiler Options
CFLAGS += -Wall		# Enables general warnings
CFLAGS += -g		# Enables debug info
CFLAGS += -Werror	# Makes all warnings into errors
CFLAGS += -O1		# optimize for code size and execution time
CFLAGS += -pedantic # Enables warnings demanded by ISO C

# Linker Options
LDFLAGS += -lm		# Links Math Libraries
LDFLAGS += -pthread	# Links POSIX threads library

.PHONY: default all clean lint

default: $(TARGET)
all: default

OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
HDR=$(wildcard *.h)
SRC=$(wildcard *.c)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJ)

$(TARGET): $(OBJ)
	$(CC)  $(OBJ) $(LDFLAGS) -o $@
	-rm -f *.o

clean:
	-rm -f $(TARGET)
	
lint:
	$(LINT) $(SRC) $(HDR)
