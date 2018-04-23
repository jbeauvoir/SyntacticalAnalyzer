/************************************************************
File: else_part.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the else_part 
non-terminal function assoc. with rule 18 and 19.

18. <else_part> -> <stmt>
19. <else_part> -> lambda

Note: check rule 19 for lambda rule 
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::else_part()
{
        // Variable Declaration
 	int errors = 0;
	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	p2file << "Entering else_part function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	
	// RULE 18
	// one of the firsts terminals is present
	if ( itr1 != firsts.end() ) {
	  p2file << "Using Rule 18" << endl;
	  errors += stmt(); 
	}
	// RULE 19 
	else if() {
	  p2file << "Using Rule 19" << endl; 
	}
	

	p2file << "Exiting else_part function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
