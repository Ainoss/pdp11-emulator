
CFLAGS=-I./include -g

OBJS=main.o decoder.o executer.o emulator.o

test: $(OBJS)
	gcc $(CFLAGS) $^ -o $@

main.o: main.c include/emulator.h
	gcc $(CFLAGS) -c $< -o $@

emulator.o: src/emulator.c include/emulator.h
	gcc $(CFLAGS) -c $< -o $@

decoder.o: src/decoder.c include/decoder.h
	gcc $(CFLAGS) -c $< -o $@

executer.o: src/executer.c include/executer.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o test

