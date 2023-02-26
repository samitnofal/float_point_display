CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

SRCDIR = src
TESTDIR = test
BUILDDIR = build
INCLUDEDIR = include

MAIN = $(BUILDDIR)/fpn_main
TEST = $(BUILDDIR)/fpn_test

MAIN_SRC = $(wildcard $(SRCDIR)/*.c)
MAIN_OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(MAIN_SRC))

TEST_SRC = $(wildcard $(TESTDIR)/*.c) $(SRCDIR)/fpn_utils.c
TEST_OBJ = $(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%.o,$(TEST_SRC))

INCLUDES = -I$(INCLUDEDIR)

.PHONY: all main test clean

all: main test

main: $(MAIN)

test: $(TEST)

$(MAIN): $(MAIN_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@ $(INCLUDES)

$(TEST): $(TEST_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@ $(INCLUDES)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(MAIN) $(TEST)