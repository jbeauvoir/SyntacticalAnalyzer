/***********************************************************
File: literal.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the literal 
non-terminal function assoc. with rule 10, 11, 12

10. <literal> -> NUMLIT_T
11. <literal> -> STRLIT_T
12. <literal> -> QUOTE_T <quoted_lit>
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::literal()
{
        // Variable Declarations
        int errors = 0;
	static set<token_type> firsts = {NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,
				      RPAREN_T};
	  
	p2file << "Entering literal function; current token is: " 
		<< lex->GetTokenName (token) << endl;

	// RULE 10 
	if ( token == NUMLIT_T ) {
	  p2file << "Using Rule 10" << endl;

	  token = lex->GetToken();
	  
          p2file << "Exiting NUMLIT_T check in stmt function; current token is: "
	         << lex->GetTokenName (token) << endl;
	}
	// RULE 11
	else if ( token == STRLIT_T ) {
		
	  p2file << "Using Rule 11" << endl;

	  token = lex->GetToken();
	  
          p2file << "Exiting STRLIT_T check in stmt function; current token is: "
	         << lex->GetTokenName (token) << endl;
	}
	// RULE 12 
	else if ( token == QUOTE_T ) {
	  p2file << "Using Rule 12" << endl;
	  
	  token = lex->GetToken();
	  
	  errors += quoted_lit();
	} 
	// no valid first
	else {
	  cout << "problem in literal firsts" << endl;
	}
	 
	p2file << "Exiting literal function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
