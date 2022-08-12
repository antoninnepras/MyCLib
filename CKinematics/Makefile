CC	= gcc
CFLAGS	= -Wall -g -O3
LSFLAGS	= -lm
TARGET	= main

CFILES  = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
HEADERS = $(wildcard src/*.h)

CFILES += $(TARGET).c 

all: $(TARGET)

objects: $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LSFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(CFILES) $(HEADERS)
	$(CC) $(CFLAGS) $(LSFLAGS) $(patsubst %.o,%.c,$@) -c
	@if [ "$@" != "$(TARGET).o" ]; then\
		mv -f $(patsubst src/%,%,$@) $@;\
	fi

clean:
	rm -rf *.o $(TARGET)
	rm -rf src/*o
	rm -rf vgcore.*
	
run:
	./$(TARGET)

val:
	valgrind ./$(TARGET)
