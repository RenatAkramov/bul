SHELL := /bin/bash

CFLAGS := -std=gnu17 -O3 -march=native -Wall -Wextra -pedantic \
          -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
          -fPIE -flto -g -fno-omit-frame-pointer -D_DEBUG

LDFLAGS := -pie -Wl,-z,relro,-z,now

SRCS := main.c lexical_analysis.c syntax_analysis.c grafdump.c \
        calculation_functions.c par.c create_dnf_knf.c simplify.c print_tree.c

OBJS := $(SRCS:.c=.o)


.PHONY: all
all: bul_func.out


bul_func.out: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -f *.o *.out *.png *.dot 

