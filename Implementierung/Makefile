CC = gcc
CFLAGS = -g
default: all

all:
	$(CC) $(CFLAGS) src/main.c src/arsinh_series.c src/arsinh_lookup.c src/arsinh_comp.c src/runtime.c src/framework.c -o arsinh.out -lm -O2
clean:
	rm -rf *.dSYM *.out