OBJS=main.o data.o wagecalc.o interface.o version.o config.o
FLAGS=-Wall -O2

all: $(OBJS)
	gcc $(OBJS) -o balance

main.o: main.c
	gcc -c main.c $(FLAGS)
data.o: data.c data.h 
	gcc -c data.c $(FLAGS) 
wagecalc.o: wagecalc.c wagecalc.h 
	gcc -c wagecalc.c $(FLAGS) 
interface.o: interface.c interface.h
	gcc -c interface.c $(FLAGS) 
version.o: version.c version.h
	gcc -c version.c $(FLAGS)
config.o: config.c config.h
	gcc -c config.c $(FLAGS)

clean:
	rm $(OBJS)

.PHONY: all clean
