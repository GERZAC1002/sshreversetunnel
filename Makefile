CC = gcc
CFLAGS = -Wall -ffast-math -Os
ADD = -static

ssh-rt:
	$(CC) $(CFLAGS) -o ssh-rtc ssh-rtc.c $(ADD)


clean:
	rm -f ssh-rtc
