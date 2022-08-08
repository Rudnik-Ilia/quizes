



/*Func that copy a string to another string */
char *StrCpy(char *,  char *); 


/* Func that copy a string to another string since Num*/
char *StrCpyNum(char *dest,  char *src, int num);

char *StrCpyNum_2(char *dest,  char *src, int num) ;

/*Compare first NUM ch. of two strings  */
int StrCmpNum(const char *first_word, const char *second_word, size_t num ); 

/* Func that compare two string without a case*/
int StrCaseCmp( char *first_word,  char *second_word);

/* Find a first char in string adn returns the pointer to it*/
char *StrChar(char *word, char x);

/*Returns a duplicate string of given string*/
char *StrDup(const char *string);

/*Add str_src to str_dest */
char *StrCat(const char *str_src, char *str_dest);
/* Second var. of previos func*/
char *StrCat_2(char *str_dest, char *str_src);
