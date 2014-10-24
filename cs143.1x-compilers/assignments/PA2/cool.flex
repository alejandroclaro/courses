/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr = string_buf;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

 /*
  *  Add Your own definitions here
  */

#define CHECK_STRING_SIZE()                             \
  if ((string_buf_ptr - string_buf) >= MAX_STR_CONST)   \
  {                                                     \
	BEGIN(INITIAL);                                     \
    cool_yylval.error_msg = "String constant too long"; \
	return ERROR;                                       \
  }

int  comment_level = 0;

%}

 /*
  * Define names for regular expressions here.
  */

DARROW              =>
ASSIGMENT_OPERATOR  <-
LESS_EQUALS         <=
INTEGER             [0-9]+
TYPE_IDENTIFIER     [A-Z]([a-zA-Z0-9_]*)
VARIABLE_IDENTIFIER [a-z]([a-zA-Z0-9_]*)
SIMPLE_COMMENT      --
BEGIN_COMMENT       ("(*")
END_COMMENT         ("*)")
WHITE_SPACE         [ \f\r\t\v]

%x COMMENT
%x STRING

%%

 /*
  *  Nested comments
  */

<INITIAL>{BEGIN_COMMENT} {
  comment_level = 1;
  BEGIN(COMMENT);
}

<COMMENT>{BEGIN_COMMENT} {
  comment_level++;
}

<INITIAL,COMMENT>{END_COMMENT} {
  comment_level--;

  if (comment_level == 0)
    BEGIN(INITIAL);
  else if (comment_level < 0)
  {
    cool_yylval.error_msg = "Unmatched *)";
    return (ERROR);
  }
}

<COMMENT>. {
  /* IGNORE */;
}

<COMMENT>\n {
  curr_lineno++;
}

<COMMENT><<EOF>> {
  BEGIN(INITIAL);

  cool_yylval.error_msg = "EOF in comment";
  return (ERROR);
}

<INITIAL>{SIMPLE_COMMENT}.* {
  /* IGNORE */
}

 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

 /*
  * \"(\\.|[^\\"])*\" {
  *   cool_yylval.symbol = idtable.add_string(yytext, yyleng);
  *
  *   return(STR_CONST);
  * }
  */

<INITIAL>\" {
  string_buf_ptr = string_buf;
  BEGIN(STRING);
}

<STRING>\\\0(.*)\" {
  BEGIN(INITIAL);

  cool_yylval.error_msg = "String contains escaped null character.";
  return (ERROR);
}

<STRING>\\n {
  CHECK_STRING_SIZE();

  *string_buf_ptr = '\n';
  string_buf_ptr++;
}

<STRING>\\b {
  CHECK_STRING_SIZE();

  *string_buf_ptr = '\b';
  string_buf_ptr++;
}

<STRING>\\f {
  CHECK_STRING_SIZE();

  *string_buf_ptr = '\f';
  string_buf_ptr++;
}

<STRING>\\t {
  CHECK_STRING_SIZE();

  *string_buf_ptr = '\t';
  string_buf_ptr++;
}

<STRING>\\. {
  CHECK_STRING_SIZE();

  *string_buf_ptr = yytext[1];
  string_buf_ptr++;
}

<STRING><<EOF>> {
  BEGIN(INITIAL);

  cool_yylval.error_msg = "String contains EOF character.";
  return (ERROR);
}

<STRING>\0(.*)(\"|\n) {
  BEGIN(INITIAL);

  cool_yylval.error_msg = "String contains null character.";

  string_buf_ptr = string_buf - 1;

  return (ERROR);
}

<STRING>\" {
  BEGIN(INITIAL);

  CHECK_STRING_SIZE();

  if (string_buf_ptr >= string_buf)
  {
    cool_yylval.symbol = stringtable.add_string(string_buf, string_buf_ptr - string_buf);

    return (STR_CONST);
  }
}

<STRING>. {
  CHECK_STRING_SIZE();

  *string_buf_ptr++ = yytext[0];
}

<STRING>\\\n {
  CHECK_STRING_SIZE();

  *string_buf_ptr = '\n';
  string_buf_ptr++;
  curr_lineno++;
}

<STRING>\n {
  BEGIN(INITIAL);

  cool_yylval.error_msg = "Unterminated string constant";

  string_buf_ptr = string_buf - 1;
  curr_lineno++;

  return (ERROR);
}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

 /* LET_STMT is a parser internal token */

[nN][oO][tT] {
  return (NOT);
}

[nN][eE][wW] {
  return (NEW);
}

[iI][sS][vV][oO][iI][dD] {
  return (ISVOID);
}

[cC][lL][aA][sS][sS] {
  return (CLASS);
}

[eE][lL][sS][eE] {
  return (ELSE);
}

[fF][iI] {
  return (FI);
}

[iI][fF] {
  return (IF);
}

[iI][nN] {
  return (IN);
}

[iI][nN][hH][eE][rR][iI][tT][sS] {
  return (INHERITS);
}

[lL][eE][tT] {
  return (LET);
}

[lL][oO][oO][pP] {
  return (LOOP);
}

[pP][oO][oO][lL] {
  return (POOL);
}

[tT][hH][eE][nN] {
  return (THEN);
}

[wW][hH][iI][lL][eE] {
  return (WHILE);
}

[cC][aA][sS][eE] {
  return (CASE);
}

[eE][sS][aA][cC] {
  return (ESAC);
}

[oO][fF] {
  return (OF);
}

 /*
  * Literals.
  */

{INTEGER} { 
  cool_yylval.symbol = idtable.add_string(yytext, yyleng);

  return (INT_CONST);
}

t[rR][uU][eE] { 
  cool_yylval.boolean = 1;

  return (BOOL_CONST);
}

f[aA][lL][sS][eE] { 
  cool_yylval.boolean = 0;

  return (BOOL_CONST);
}

 /*
  *  The multiple-character operators.
  */
{DARROW} { return (DARROW); }

{ASSIGMENT_OPERATOR} { return (ASSIGN); }

{LESS_EQUALS} { return (LE); }

 /*
  * Single character operators.
  */

[\.] { return ('.'); }
[\@] { return ('@'); }
[\~] { return ('~'); }
[\*] { return ('*'); }
[\/] { return ('/'); }
[\+] { return ('+'); }
[\-] { return ('-'); }
[\<] { return ('<'); }
[\=] { return ('='); }

 /*
  * Delimiters.
  */

[\,] { return (','); }
[\;] { return (';'); }
[\:] { return (':'); }
[\)] { return (')'); }
[\{] { return ('{'); }
[\}] { return ('}'); }
[\(] { return ('('); }

 /*
  * Identifiers
  */ 

{TYPE_IDENTIFIER} {
  cool_yylval.symbol = idtable.add_string(yytext, yyleng);

  return (TYPEID);
}

{VARIABLE_IDENTIFIER} {
  cool_yylval.symbol = idtable.add_string(yytext, yyleng);

  return (OBJECTID);
}

 /*
  * white spaces
  */

{WHITE_SPACE} {
  /* IGNORE */;
}

[\n] {
  curr_lineno++;
}

 /*
  * Invalid tokens
  */

^_ {
  cool_yylval.error_msg = "_";
  return ERROR;
}

. {
  cool_yylval.error_msg = yytext;
  return ERROR;   
}

%%
