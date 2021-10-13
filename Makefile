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

build: setup_directories pixel_operations loader main
	$(CC) $(CFLAGS) $(LDLIBS) $(GTK) bin/*.o -o kalytera



loader:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/loader.o -c src/loader.c

pixel_operations:
	$(CC) $(CFLAGS) $(LDLIBS) -o bin/loader.o -c src/loader.c

main:
	$(CC) $(CFLAGS) $(LDLIBS) $(GTK) -o bin/main.o -c src/main.c

setup_directories: clean_dir
	mkdir tmp
	mkdir bin
	mkdir output

clean: clean_dir
	rm kalytera

clean_dir:
	rm -rf tmp
	rm -rf bin
	rm -rf output