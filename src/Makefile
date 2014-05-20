balance: main.o config.o
	gcc $^ -o $@

%.o: %.c
	gcc -c -std=c99 $^ -o $@ -Wall -O2

clean:
	rm *.o

.PHONY: clean
