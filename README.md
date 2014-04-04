mssql
=========
mssql is a command line SQL Server Client.
current version provide features below :

basic crud sql execution to specific database.

prerequistes
==========

##freetds
(1) for mac  
http://www.acloudtree.com/how-to-install-freetds-and-unixodbc-on-osx-using-homebrew-for-use-with-ruby-php-and-perl/  
(2) for centos  
```
yum install freetds-devel
```

##curses
(1) for mac  
```
brew install ncurses-devel
```
(2) for centos  
```
yum install ncurses-devel
```

installation
==========
just type  
`make`  
  
executable binary will be created in bin directory.
