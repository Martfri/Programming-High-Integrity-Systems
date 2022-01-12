# Executable Target Name
TARGET = phis
TARGET_TEST = phis_test

# Compiler
CC = gcc
CDEFINES = gcc-defines.h

# Linter
LINT = flint
LINTOUT = results_linter.txt

# Compiler Options
CFLAGS += -Wall# Enables general warnings
CFLAGS += -g# Enables debug info
CFLAGS += -Werror# Makes all warnings into errors
CFLAGS += -O1# optimize for code size and execution time
CFLAGS += -pedantic# Enables warnings demanded by ISO C

# Linker Options
LDFLAGS += -lm# Links Math Libraries
LDFLAGS += -pthread# Links POSIX threads library

# Linter Options
LINTFLAGS += -cgnu# tell flint that gcc is used for compiling
LINTFLAGS += -i'/usr/lib/gcc/x86_64-alpine-linux-musl/10.3.1/include;/usr/include'# add gcc headers include path
LINTFLAGS += -'header($(CDEFINES))'# add gcc default defines
LINTFLAGS += +'libh($(CDEFINES))'# set as library
LINTFLAGS += +'libclass(angle, ansi)'# make sure only external headers are viewed as libraries
LINTFLAGS += -'wlib(1)'# only output errors for library files
LINTFLAGS += -'elib(1*)'# get rid of remaining library errors
LINTFLAGS += +v# enable output to stdout and stderr

# Test directory
TESTDIR = test/

.PHONY: default all clean lint test

default: lint build
all: lint test build
build: $(TARGET)
	@echo "------------------------------------------------------------------"
	@echo "                  Build Finished Successfully..."
	@echo "------------------------------------------------------------------"

OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
TESTOBJ=$(patsubst %.c, $(TESTDIR)%.o, $(wildcard *.c))
HDR=$(wildcard *.h)
SRC=$(wildcard *.c)

compile_print:
	@echo "------------------------------------------------------------------"
	@echo "                            Compiling..."
	@echo "------------------------------------------------------------------"
%.o:  %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJ)

$(TARGET): compile_print $(OBJ)
	@echo "------------------------------------------------------------------"
	@echo "                            Linking..."
	@echo "------------------------------------------------------------------"
	$(CC)  $(OBJ) $(LDFLAGS) -o $@
	-rm -f *.o

# Builing binary for testing
$(TESTDIR)%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) -DTEST -c $< -o $@

.PRECIOUS: $(TARGET) $(TESTOBJ)

$(TESTDIR)$(TARGET_TEST): $(TESTOBJ)
	$(CC)  $(TESTOBJ) $(LDFLAGS) -o $@
	-rm -f $(TESTDIR)*.o

test:
	@echo "------------------------------------------------------------------"
	@echo "                            Testing..."
	@echo "------------------------------------------------------------------"
	cd $(TESTDIR) && make all
	-rm -f $(TARGET_TEST)


clean:
	@echo "------------------------------------------------------------------"
	@echo "                            Cleaning..."
	@echo "------------------------------------------------------------------"
	-rm -f $(TARGET) $(LINTOUT) $(CDEFINES)

lint:
	@echo "------------------------------------------------------------------"
	@echo "                            Linting..."
	@echo "------------------------------------------------------------------"
	$(shell echo "" | gcc -dM -E - > $(CDEFINES))
	$(LINT) $(LINTFLAGS) $(SRC) > $(LINTOUT)
