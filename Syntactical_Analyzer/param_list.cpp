/************************************************************
File: param_list.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the param_list 
non-terminal function assoc. with rule 16 and 17.

16. <param_list> -> IDENT_T <param_lit>
17. <param_list> -> lamda

notes: check my lambda logic 
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::param_list()
{

	int errors = 0;
	static set<token_type> firsts = {IDENT_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};

	p2file << "Entering param_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;

	// RULE 16
	if ( token == IDENT_T ) {
	  p2file << "Using Rule 16" << endl;

	  token = lex->GetToken();

	  p2file << "Exiting IDENT_T check in param_list function; current token is: "
		 << lex->GetTokenName (token) << endl;
	  
	  // Non-terminal check 
	  errors += param_list();
	}

	// RULE 17???

	p2file << "Exiting param_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
