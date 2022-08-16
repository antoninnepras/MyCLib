CC	= gcc
CFLAGS	= -Wall -g
LSFLAGS	= -lm
TARGETS	= main

CFILES  = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
HEADERS = $(wildcard src/*.h)

all: $(TARGETS)

objects: $(OBJECTS)

$(TARGETS): $(OBJECTS) $(addsuffix .c,$(TARGETS))
	$(CC) $(CFLAGS) $(LSFLAGS) $@.c -c
	$(CC) $(CFLAGS) $(LSFLAGS) $(OBJECTS) $@.o -o $@

$(OBJECTS): $(CFILES) $(HEADERS)
	$(CC) $(CFLAGS) $(LSFLAGS) $(patsubst %.o,%.c,$@) -c
	mv -f $(patsubst src/%,%,$@) $@

clean:
	rm -rf *.o $(TARGETS) src/*o
