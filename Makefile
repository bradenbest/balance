all:
	cd src && $(MAKE)
	mv src/balance ./

clean:
	cd src && $(MAKE) clean

install: all
	sudo mv balance /usr/local/bin
	@./copy

uninstall:
	sudo rm /usr/local/bin/balance
	@echo Make sure to remove the file .balance_data from your ~/ directory!

.PHONY: all clean install uninstall
