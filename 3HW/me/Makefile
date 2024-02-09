CC = gcc
CFLAGS = -Wall -Wextra -Werror=declaration-after-statement -Wunused-but-set-variable
CFLAGS += -pedantic
CFLAGS += -g
#CLFAGS += -DNDEBUG
#CFLAGS += -O2
TARGET = a.out
SRCS = main.c me.c 
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm  $(OBJS) $(TARGET)
