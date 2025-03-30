CC=gcc

all: main.o
	cd my_rust_lib && cargo build --release
	$(CC) main.c -o main -L ./my_rust_lib/target/release/ -lmy_rust_lib -lpthread -ldl

clean:
	rm main; rm main.o
