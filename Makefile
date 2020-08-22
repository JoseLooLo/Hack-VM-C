CC=gcc
CFLAGS=-I.
DEPS=commands.h
OBJ = VMTranslator.o parser.o codewriter.o


VMTranslator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o