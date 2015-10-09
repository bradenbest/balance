flags=-Wall -std=c99 -DVERSION='"2.0.0"' -DUSE_COLOR=1
cfiles=balance.c ui.c input.c calc.c main.c

balance: $(cfiles)
	gcc $^ $(flags) -o $@

clean:
	rm balance

.PHONY: clean
