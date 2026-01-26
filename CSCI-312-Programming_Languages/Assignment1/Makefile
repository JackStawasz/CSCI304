CC=gcc
CFLAGS=-ll

scanner: lex.l
	lex $<
	$(CC) -o $@ lex.yy.c $(CFLAGS) 
