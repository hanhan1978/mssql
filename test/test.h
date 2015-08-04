
//////// queryfilter.c
//public
char * trans_dialect(const char *);




//////// utils.c
//public
int is_pretty(const char * input);
char * normalize(const char * input);

//private
char * remove_consective_blank(const char *);  
char * rtrim(const char * input);
char * ltrim(const char * input);
char * trim(const char * input);
char * replaceSpace(const char * input);
