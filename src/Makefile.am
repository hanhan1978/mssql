CFLAGS = --pedantic -Wall -std=c99 -O2 -g -O0

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# # the previous manual Makefile
bin_PROGRAMS = mssql 
mssql_SOURCES = datasource.c mssql.c mssql.h option.c usage.c utils.c queryfilter.c output.c dbresult.c services/service.c
mssql_LDFLAGS = $(LDFLAGS)
