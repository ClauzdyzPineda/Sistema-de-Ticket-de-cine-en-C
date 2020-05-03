# This is a make file a comment file
# all:
# 	rm -rf main/dist/main.exe && gcc -Wall main/src/main.c -o main/dist/main

# VARIABLES
C := gcc
CFLAGS := -Wall
SRC := main/src
OBJECTS := $(SRC)/main.c $(SRC)/helpers.c $(SRC)/menus.c $(SRC)/usuario.c $(SRC)/cabeceras.c

all: $(OBJECTS)
	rm -rf main/dist/main.exe main/dist/null && $(C) $(CFLAGS) $(OBJECTS) -o main/dist/main