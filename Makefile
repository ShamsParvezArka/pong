CC = gcc
CFLAGS = -Wall -Wextra -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm

output: main.c
	$(CC) -o pong main.c $(CFLAGS)

clean:
	rm pong
