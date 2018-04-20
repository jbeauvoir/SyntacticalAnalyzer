/************************************************************
File: stmt_pair.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the stmt_pair  
non-terminal function assoc. with rule 20 and 21.

20. <stmt_pair> -> LPAREN_T <stmt_pait_body>
21. <stmt_pair> -> lambda

Note: check rule 21 logic for the lambda 
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::stmt_pair()
{
        // Variable Declaration
	int errors = 0;
	static set<token_type> firsts = {LPAREN_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	
	p2file << "Entering stmt_pair function; current token is: " 
	       << lex->GetTokenName (token) << endl;

	// RULE 20
	if( token == LPAREN_T ) {
	  p2file << "Using Rule 20" << endl;
	  errors += stmt_pair_body();
	}
	// RULE 21
	else if () {

	}
	else {
	  cout << "error in stmt_pair no firsts" << endl;
	}

	p2file << "Exiting stmt_pair function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
