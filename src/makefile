
CC=gcc

all: mssql makedir move clean

mssql: mssql.o usage.o option.o slre.o db.o
	${CC} -o mssql mssql.o usage.o option.o slre.o db.o -L/usr/local/Cellar/readline/6.3.3/lib -lreadline -lsybdb

#	${CC} -o mssql option.o mssql.o history.o prompt.o db.o usage.o -lncurses -lsybdb

mssql.o: 
	${CC} -c mssql.c

slre.o: 
	${CC} -c slre.c

db.o: 
	${CC} -c db.c

usage.o:
	${CC} -c usage.c

option.o: 
	${CC} -c option.c

move:
	mv mssql ../bin/

makedir:
	if [ ! -d ../bin ]; \
		then mkdir ../bin; \
	fi

.PHONY: clean
clean:
	rm *.o



