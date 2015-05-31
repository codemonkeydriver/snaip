PROG = unit_test_except

SRC = except.c unit_test_except.c
OBJS = except.o unit_test_except.o
CC = gcc
CFLAGS = -Wall -g

${PROG}:${OBJS}
	${CC} -o  $@ ${OBJS}

except.o: except.c
	${CC} ${CFLAGS} -c except.c -o except.o

unit_test_except.o: unit_test_except.c
	${CC} ${CFLAGS} -c unit_test_except.c -o unit_test_except.o

clean:
	rm unit_test_except except.o unit_test_except.o
