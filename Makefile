CC=g++
BUILDFOLDER=build
SRCFOLDER=src
CFLAGS=-lpaho-mqttpp3 
CFLAGS+=-lpaho-mqtt3as
CFLAGS+=-g -Wall -std=c++11

.PHONY: all main clean

all: clean main

main:
	${CC} -o ${BUILDFOLDER}/main ${SRCFOLDER}/main.cpp ${CFLAGS}

clean:
	rm -f ${BUILDFOLDER}/*
