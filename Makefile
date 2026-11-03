CC     = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = sync_car
SRCS   = sync_car.c sync_car-runner.c

all: $(TARGET)

$(TARGET): $(SRCS) sync_car.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
