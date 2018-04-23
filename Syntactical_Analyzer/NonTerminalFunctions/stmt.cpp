/***********************************************************
File: stmt.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: Contains the stmt non-terminal assoc. with 
rules 7, 8, and 9.

notes:
  - Put in p2file rule notificaiton in proper place
  - check nested loop for rule 9 
  - check if statement check for firsts 
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::stmt()
{
        // Variable Declaration 
        int errors = 0;
  	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,
				      RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
        set<token_type>::iterator itr2 = follows.find(token);

	p2file << "Entering stmt function; current token is: " 
		<< lex->GetTokenName (token) << endl;


	// RULE 7
	if ( token == NUMLIT_T || token == QUOTE_T || token == STRLIT_T ) {
	  p2file << "Using Rule 7" << endl;
	
	  token = lex->GetToken();
		
	  p2file << "Exiting rule 8 IDENT_T in stmt; current token is: " 
		 << lex->GetTokenName (token) << endl;
	  
	  errors += literal();
	}
	// RULE 8
	else if ( token == IDENT_T ) {
	  p2file << "Using Rule 8" << endl;

	  token = lex->GetToken();
		
	  p2file << "Exiting rule 8 IDENT_T in stmt; current token is: " 
		 << lex->GetTokenName (token) << endl;

		
	}

	// RULE 9
	else if ( token == LPAREN_T ) {
	  p2file << "Using Rule 9" << endl;
	
	  token = lex->GetToken();
		
          // Non-terminal check
	  errors += action();

	  if ( token == RPAREN_T ) {
	    lex->GetTokenName (token);
	    p2file << "Exiting rule 9 RPAREN_T check in stmt function; current token is: "
		   << lex->GetTokenName (token) << endl;
	  }
	  else {
	    cout << "no RPAREN_T" << endl;
	  }
	}
	else {
	  cout << "no firsts" << endl;
	}

	p2file << "Exiting stmt function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
