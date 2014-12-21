
CC=gcc

all: mssql makedir move clean

mssql: mssql.o 
	${CC} -o mssql mssql.o -L/usr/local/Cellar/readline/6.3.3/lib -lreadline


#	${CC} -o mssql option.o mssql.o history.o prompt.o db.o usage.o -lncurses -lsybdb

mssql.o: 
	${CC} -c mssql.c

#prompt.o: 
#	${CC} -c prompt.c

#db.o: 
#	${CC} -c db.c -lsybdb

#usage.o:
#	${CC} -c usage.c	

move:
	mv mssql bin/

makedir:
	if [ ! -d bin ]; \
		then mkdir bin; \
	fi

.PHONY: clean
clean:
	rm *.o



