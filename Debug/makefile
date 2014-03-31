
CC=gcc

all:mssql move clean

mssql: mssql.o prompt.o db.o history.o option.o
	${CC} -o mssql mssql.o history.o prompt.o db.o option.o -lncurses -lsybdb


mssql.o: 
	${CC} -c ../mssql.c

prompt.o: 
	${CC} -c ../prompt.c

db.o: 
	${CC} -c ../db.c -lsybdb

history.o: 
	${CC} -c ../history.c

option.o:
	${CC} -c ../option.c

move:
	mv mssql ../bin/

.PHONY: clean
clean:
	rm *.o



# gcc db.c -lsybdb
