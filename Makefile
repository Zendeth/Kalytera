################################################################################
### 					Makefile for Kalytera project					 	 ###
### 						Made by Hafid HOUSNI							 ###
################################################################################

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -O3 -g
LDLIBS=-lSDL2 -lSDL2_image
GTK=`pkg-config --cflags --libs gtk+-3.0` -export-dynamic


all: build

run: build
	./kalytera

build: setup_directories pixel_operations noisereduction binarize loader main
	$(CC) $(CFLAGS) $(LDLIBS) $(GTK) bin/*.o -o kalytera

noisereduction:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/noisereduction.o -c src/noisereduction.c

binarize:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/binarize.o -c src/binarize.c

loader:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/loader.o -c src/loader.c

pixel_operations:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/pixel_operations.o -c src/pixel_operations.c

main:
	$(CC) $(CFLAGS) $(LDLIBS) $(GTK) -o bin/main.o -c src/main.c

setup_directories:
	mkdir -p tmp
	mkdir -p bin
	mkdir -p output

clean: 
	rm kalytera
	rm -rf tmp
	rm -rf bin
	rm -rf output