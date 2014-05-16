balance: main.o data.o wagecalc.o interface.o version.o config.o get_home.o
	gcc $^ -o $@

%.o: %.c
	gcc -c $^ -o $@ -Wall -O2

clean:
	rm *.o

.PHONY: clean
