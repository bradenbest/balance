flags=-Wall -std=c99 -DVERSION='"2.0.1"' -DUSE_COLOR=0
cfiles=balance.c ui.c input.c calc.c main.c history.c

balance: $(cfiles)
	gcc $^ $(flags) -o $@

clean:
	rm balance

.PHONY: clean
