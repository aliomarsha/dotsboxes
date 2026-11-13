CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = dotsboxes
OBJS    = main.o game.o board.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c board.h game.h
	$(CC) $(CFLAGS) -c $< -o $@

# Install on Alpine (run as root)
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)
	install -m 755 startgame.sh /usr/local/bin/startgame

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean install
