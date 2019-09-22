CC = gcc
CFLAGS = -Wall -pedantic -Werror -std=c11
sources = $(wildcard *.c)
objs = $(patsubst %.c,%.o,$(sources))
lib = libutf8.a

all: $(lib)

$(lib): $(objs)
	$(AR) rcs $@ $^

clean:
	rm -rf $(objs) $(lib)

.PHONY: all clean