CC = gcc
CFLAGS = -Wall -Wextra
TARGET = my_cpu
SRCS = main.c alu.c cpu_initialize.c encode.c execute.c load_from_file.c print.c register.c 
OBJS = $(SRCS:.c=.o)
HEADERS = alu.h cpu.h registers.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
