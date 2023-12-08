CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = a.out
SRCS = main.c sieve.c hwe.c #tests.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
