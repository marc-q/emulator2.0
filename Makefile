CC = gcc
OBJECTS = src/emulator_alu.c emulator.c
LIBS =
CFLAGS = -Wall -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = emulator

emulator: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm $(NAME)
