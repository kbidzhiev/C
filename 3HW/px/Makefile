CC = gcc
CFLAGS = -Wall -Wextra -Werror=declaration-after-statement -Wunused-but-set-variable
CFLAGS += -pedantic
CFLAGS += -g
#CFLAGS += -O2 -DNDEBUG
TARGET = a.out
SRCS = main.c px.c  
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm  $(OBJS) $(TARGET)
