all: balance

install: balance
	mv $^ /usr/local/bin

uninstall: 
	rm /usr/local/bin/balance -i

balance:
	cd src && $(MAKE)
	mv src/balance ./ -i

clean:
	rm balance

.PHONY: all install uninstall clean
