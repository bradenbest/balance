TARGET=balance
DATA_FILE=.balance_data

all:
	cd src && $(MAKE)
	mv src/$(TARGET) ./

clean:
	cd src && $(MAKE) clean

install: all
	mv $(TARGET) /usr/local/bin
	@./copy

remove: uninstall
	rm /usr/local/bin/$(TARGET)

uninstall: remove
	@echo Make sure to remove the file .balance_data from your ~/ directory!
# I don't have it remove it automatically, because the user might want to keep the data.

purge: remove
	rm ~/$(DATA_FILE)

.PHONY: all clean install uninstall remove purge
