ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

all: main.c target.c
	gcc -c main.c
	gcc -pthread -o main main.o -L$(ROOT_DIR) -Wl,-Bstatic -l:./tcc_local/libtcc.a -Wl,-Bdynamic -ldl

clean:
	rm main main.o
