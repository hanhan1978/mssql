[![Build Status](https://travis-ci.org/hanhan1978/mssql.svg?branch=master)](https://travis-ci.org/hanhan1978/mssql)

# mssql
mssql is a command line SQL Server Client.  
  
current version provide these features :  
1. basic CRUD sql execution to specific database.  
2. some of mysql query dialect (shown below)


## supported mysql dialect
- show databases  
- show tables  
- desc(ribe) [tableName]  
- show processlist  

# Installation
```
$ ./configure  
$ make  
$ sudo make install  
```

## for Mac user
install via homebrew

```
$ brew tap hanhan1978/homebrew-mssql 
$ brew instal mssql
```

### trouble shoot
+ if error occured with `./configure`  
Run `autoreconf -ivf .` at project root, and run `configure` again.
