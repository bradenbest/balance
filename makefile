install: balance
	mv $^ /usr/local/bin

uninstall: 
	rm /usr/local/bin/balance -i

balance:
	cd src && $(MAKE)
	mv src/balance ./ -i

.PHONY: install uninstall
