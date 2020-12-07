CC=g++
BUILDFOLDER=build
SRCFOLDER=src
CFLAGS=-lpaho-mqttpp3 
CFLAGS+=-lpaho-mqtt3as
CFLAGS+=-g -Wall -std=c++11

.PHONY: all mqtt main clean

all: clean mqtt main

main:
	${CC} -o ${BUILDFOLDER}/main ${BUILDFOLDER}/*.o ${SRCFOLDER}/main.cpp ${CFLAGS}

mqtt: 
	${CC} -o ${BUILDFOLDER}/my_mqtt.o -c ${SRCFOLDER}/my_mqtt.cpp ${CFLAGS}

clean:
	rm -f ${BUILDFOLDER}/*
