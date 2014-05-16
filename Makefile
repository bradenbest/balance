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

remove: 
	rm /usr/local/bin/$(TARGET)

uninstall: remove
	@echo Make sure to remove the file .balance_data from your ~/ directory!
# I don't have it remove it automatically, because the user might want to keep the data. For that, use purge.

purge: remove
	rm ~/$(DATA_FILE)

build: all
	mv $(TARGET) installer/build
	tar zcf installer.tar.gz installer/
	zip -r installer installer/
	

.PHONY: all clean install uninstall remove purge
