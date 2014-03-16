
CC=gcc


mssql: mssql.o prompt.o db.o
	${CC} -o mssql mssql.o prompt.o db.o -lncurses -lsybdb


mssql.o: mssql.c
	${CC} -c mssql.c

prompt.o: prompt.c
	${CC} -c prompt.c

db.o: db.c
	${CC} -c db.c -lsybdb

.PHONY: clean
clean:
	rm *.o



# gcc db.c -lsybdb
