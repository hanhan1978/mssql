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
```
$ ./configure  
$ make  
$ sudo make install  
```

## for Mac user
You need to install readline by yourself.  
Followings are sample installation flow on Mac OS X 10.9(Mavericks)  

1. install readline  
`brew install readline`
2. check brew installed dir  
`brew info readline`
3. run configure command with LDFLAGS set.  
`LDFLAGS=-L/usr/local/Cellar/readline/6.3.3/lib ./configure`
4. build & install  
```
$ make
$ sudo make install
```
