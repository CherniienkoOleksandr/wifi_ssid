CFLAGS = -Wpedantic -O3 -Wextra -Wall
LDFLAGS := 
DEBUGFLAGS := -g -O0	# flags for debug builds

SRCS := $(wildcard *.c)
OUTS := $(SRCS:.c=)


#.PHONY: all clean
all: $(OUTS)
#%.out: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)


clean: 
	find . -maxdepth 1 -type f -executable -print -delete

bear:
	bear -- $(MAKE)
