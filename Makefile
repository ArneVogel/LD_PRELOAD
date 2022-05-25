lib.so: interceptor.c
	gcc -shared -o lib.so interceptor.c -fPIC -ldl

example: main.c
	gcc main.c -o example

run: example lib.so
	LD_PRELOAD=$(shell pwd)/lib.so ./example

clean:
	rm *.so example

tcp_app/target/release/tcp_app: tcp_app/src/main.rs
	cd tcp_app; cargo build --release

run-tcp: tcp_app/target/release/tcp_app lib.so
	LD_PRELOAD=$(shell pwd)/lib.so ./tcp_app/target/release/tcp_app

cat: lib.so
	LD_PRELOAD=$(shell pwd)/lib.so cat Makefile
