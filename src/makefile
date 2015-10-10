include config.mk

flags=-Wall -std=c99 -DVERSION=$(VERSION) -DUSE_COLOR=$(USE_COLOR)
cfiles=balance.c ui.c input.c calc.c main.c history.c

balance: $(cfiles)
	gcc $^ $(flags) -o $@

clean:
	rm balance

.PHONY: clean
