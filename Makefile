lib.so: interceptor.c
	gcc -shared -o lib.so interceptor.c -fPIC -ldl

example: main.c
	gcc main.c -o example

run: example lib.so
	LD_PRELOAD=$(shell pwd)/lib.so ./example

clean:
	rm *.so example

cat: lib.so
	LD_PRELOAD=$(shell pwd)/lib.so cat Makefile
