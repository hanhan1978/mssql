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

# Architecture

Layerd

+ UserInterface(userinput.c)
 + get commandline arguments
 + fill input variable struct with args

 - Input => commandline arguments, stdin
 - Data => Input valiable struct

+ Application(validate.c, main.c)
 - Validate Input Variables
 - call service with service invoker  (do not decide anything)

 - Data => Input valiable struct (validated)

+ Service (service.c)
 + Servie Invoker
  - call stdout service or Cli service (depends on input)

 + Stdout Service (function stdout)
  - execute command 
  - call stdout printer
 + CLI Service (function cli)
  - use readeline, history
  - execute command if input
  - call cli printer

+ Filter (queryfilter.c)
 + filter sql & convert if needed

+ Datasource (datasource.c)
 + execute login
 + execute sql

 - Data => db login info struct (create & use)
 - Data => resultset

+ OutputCreator (output.c)
  - create csv (stdout)
  - create cli result style => regular, \G\G

  - Data => resultset (input)


