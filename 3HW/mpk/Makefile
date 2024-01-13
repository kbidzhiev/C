CC = gcc
CFLAGS = -g -Wall -Wextra -Werror=declaration-after-statement -Wunused-but-set-variable
CFLAGS += -pedantic
TARGET = a.out
SRCS = main.c tests.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
