# Architecture

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

+ [done] Filter (queryfilter.c)
 + [done] filter sql & convert if needed

+ Datasource (datasource.c)
 + execute login
 + execute sql

 - Data => db login info struct (create & use)
 - Data => resultset

+ OutputCreator (output.c)
  - create csv (stdout)
  - create cli result style => regular, \G\G

  - Data => resultset (input)
