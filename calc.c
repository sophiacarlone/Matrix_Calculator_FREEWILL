//WORKING ONE?

/* A small sample program for an arithmetic calculator.
 * Supports only addition and multiplication on integers. Allows brackets to override precedence.
 * Author: CS445 class, Spring 2023.
 * Bug status:
 *  0. Error reporting is an adhoc (hackish).
 *  1. Failed on double brackets (Matthew). Fixed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "const.h"
#include "tree.h"

/* globals for communication between parser and scanner */
int current_token;
int current_attribute;

/* prototypes */
tree_t *expr();
tree_t *term();
tree_t *factor();
int get_token();
void match( int );

///////////////////////////////////////////////////////////

/* home work:
 * codegen function from class
 * will probably be in tree.c/h
 */


/* main driver */
int main()
{
	tree_t *value;
	
	/* initialize first token */
	current_token = get_token();

	/* unleash the parser (start the derivation) */
	value = expr();
	
	/* evaluation"*/
	fprintf(stderr, "evaluated to: %d\n", eval_tree( value ));

	//fprintf(stderr, "rank: %d\n", rank(value, 1));

	gencode_start(value);

	/* check that EOS is there */
	if ( current_token == EOS ) {
		fprintf( stderr, "\nPRINTING TREE:\n\n" );
		print_tree( value ); /* no classes in c */
		//fprintf( stderr, "Value = %d\n", eval_tree( value ) );
	}
	else exit(1);

	return 0;
}


/* parser 
 * using the basic ambiguous grammar: 
 *  E -> E+E | E*E | (E) | NUM 
 * but revised to handle precedence and associative rules:
 *  E -> E+T | T, T -> T*F | F, F -> (E) | NUM
 * adjusted again to remove left-recursion (but not left-factoring):
 *  E -> TE', E' -> +TE' | empty
 *  T -> FT', T' -> *FT' | empty
 *  F -> (E) | NUM
 * the coroutines of the parser consists of expr(), term(), factor()
 */

/* E -> TE', E' -> +TE' | empty */
tree_t *expr()
{
	tree_t * value = term();
	while ( (current_token == '+') || (current_token == '-') ) { //will leave the case of +- to error out
		if(current_token == '+'){
			match( '+' );
			value = make_tree( '+', value, term(), current_attribute );
		}
		else{
			match( '-' );
			value = make_tree( '-', value, factor() , current_attribute);
		}
	}
	return value;
}

/* T -> FT', T' -> *FT' | empty */
tree_t *term()
{
	tree_t *value = factor();
	while ( (current_token == '*') || (current_token == '/') ) { //will leave the case of */ to error out
		if( current_token == '*'){
			match( '*' );
			value = make_tree( '*', value, factor() , current_attribute);
		}
		else{
			match( '/' );
			value = make_tree( '/', value, factor() , current_attribute);
		}
	}
	return value;
}

/* F -> (E) | NUM */
tree_t *factor()
{
	tree_t *value;
	if ( current_token == '(' ) {
		match( '(' );
		value = expr();
		match( ')' );
	}
	else if ( current_token == NUM ) {
		match( NUM );
		value = make_tree( NUM, NULL, NULL, current_attribute);
	}
	else {
		fprintf( stderr, "Error in factor: %d\n", current_token );
		exit(1);
	}
	return value;
}


/* get_token(): the scanner
 * responsible to tokenize a string according to token types: 
 *  types are +, *, (, ), NUM
 * example: "(278+312)*4659" ==> [(][NUM][+][NUM][)][*][NUM] 
 */
int get_token()
{
/* STEP 4: 
 * This is the output of the program
 * this is where it should print out assembly to a file
 * what is NUM?
 */
	int c, value;
	while ( (c=getchar()) != EOF ) {
		switch (c) {
		case '+': case '*': case '/': case '-': /* OPERATORS */
			fprintf( stderr, "[OP:%c]", c );
			return c;
		case '(': case ')': /* BRACKETS*/ 
			fprintf( stderr, "[%c]", c );
			return c;
		case ' ': case '\t': /*tab*/
			continue;
		default:
			if ( isdigit(c) ) { /* NUM */
				value = 0;
				do {
					value = 10*value + (c - '0');
				} while ( isdigit( c=getchar() ));
				ungetc( c, stdin );
				fprintf( stderr, "[NUM:%d]", current_attribute = value );
				return NUM;
			}
			else if ( c == '\n' ) {	/* EOS */
				fprintf(stderr, "[EOS]\n" ); 
				return EOS;
			}
			else {
				fprintf( stderr, "ERROR: unknown token {%c}\n", c );
				assert(0);
				return -1;
			}
		}
	}
}

/* match(): helper for scanner
 * advances to next token only if token is the expected one.
 */
void match( int expected_token )
{
	if ( current_token == expected_token ) {
		current_token = get_token();
	}
	else {
		fprintf( stderr, "Error in match: current = %d, expected = %d\n", current_token, expected_token );
		exit(1);
	}
}