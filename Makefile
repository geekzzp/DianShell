CC = gcc
CFLAGES = -g -std=c2x -Wall -Werror
# CFLAGES = -g -Wall -Werror

S = src
U = user
B = bin
SHELL = sh

ifeq ($(wildcard $B),)
    # bin/ directory does not exist
    $(info Creating directory '$B')
    $(shell mkdir -p $B)
endif

USRC = $(wildcard $S/$U/*.c)
UPROG = $(USRC:$S/$U/%.c=%)

all: shell user_program

user_program: $(UPROG)

%: $S/$U/%.c
	$(CC) $(CFLAGES) -o $B/$@ $^

shell: $S/main.c $S/$(SHELL)/*.c
	$(CC) $(CFLAGES) -o $B/shell $S/main.c $S/$(SHELL)/*.c

.PHONY: clean
clean:
	rm bin/* -rf