
CC=gcc


mssql: mssql.o prompt.o
	${CC} -o mssql mssql.o prompt.o -lncurses


mssql.o: mssql.c
	${CC} -c mssql.c

prompt.o: prompt.c
	${CC} -c prompt.c



.PHONY: clean
clean:
	rm *.o
