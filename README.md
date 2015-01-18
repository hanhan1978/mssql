mssql
=========
mssql is a command line SQL Server Client.  
  
current version provide these features :  
1. basic CRUD sql execution to specific database.  
2. some of mysql query dialect (shown below)

## supported mysql dialect
show databases  
show tables  
describe [table_name]  
show processlist  

Installation
==========
./configure
make
sudo make install

## for Mac user
install readline with brew
edit Makefile.in and add following to LINE8

```
-L/usr/local/Cellar/readline/6.3.3/lib
```
readline version might be different.
