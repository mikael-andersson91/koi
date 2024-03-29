/* parser.c -- without the optimizations */

#include "global.h"

int lookahead;

void match(int);
void start(), list(), expr(), moreterms(), term(), morefactors(), factor(), assignment(), exponent(), moreexponent();

void parse()  /*  parses and translates expression list  */
{
  lookahead = lexan();
  start();
}

void start ()
{
  /* Just one production for start, so we don't need to check lookahead */
  list(); match(DONE);
}

void list()
{
if (lookahead == '(' || lookahead == ID || lookahead == NUM) {
    //expr(); match(';'); list();
    assignment();match(';'); list();
  }
  //else if(lookahead == '=')
  else {
    /* Empty */
  }
}

void assignment()
{
	emit(ID, tokenval);
	match(ID);
	if(lookahead == '='){
		match('=');expr();emit('=', tokenval);
	}


}

void expr ()
{
  /* Just one production for expr, so we don't need to check lookahead */
  term(); moreterms();
}

void moreterms()
{
  if (lookahead == '+') {
    match('+'); term(); emit('+', tokenval); moreterms();
  }
  else if (lookahead == '-') {
    match('-'); term(); emit('-', tokenval); moreterms();
  }
  else {
    /* Empty */
  }
}

void term ()
{
  /* Just one production for term, so we don't need to check lookahead */
  factor(); morefactors();
}

void morefactors ()
{
  if (lookahead == '*') {
    match('*'); factor(); emit('*', tokenval); morefactors();
  }
  else if (lookahead == '/') {
    match('/'); factor(); emit('/', tokenval); morefactors();
  }
  else if (lookahead == DIV) {
    match(DIV); factor(); emit(DIV, tokenval); morefactors();
  }
  else if (lookahead == MOD) {
    match(MOD); factor(); emit(MOD, tokenval); morefactors();
  }
  else {
    /* Empty */
  }
}

void factor ()
{
  exponent();moreexponent();
}

void moreexponent(){

	 if (lookahead == '^') {
	    match('^'); exponent(); emit('^', tokenval); moreexponent();
	}

}

void exponent()
{
	if (lookahead == '(') {
	    match('('); expr(); match(')');
	}
	else if (lookahead == ID) {
		int id_lexeme = tokenval;
		match(ID);
		emit(ID, id_lexeme);
	}
	else if (lookahead == NUM) {
		int num_value = tokenval;
		match(NUM);
		emit(NUM, num_value);
	}
	else{
		/*Empty*/
	}

}

void match(int t)
{
  if (lookahead == t)
    lookahead = lexan();
  else
    error ("syntax error in match");
}
