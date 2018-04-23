#include "SyntacticalAnalyzer.h"


/*******************************************************************************
Function: stmt_list

Parameters: none 
Return value: an integer value called "errors"
Description: This is rule number 5 and 6
5. <stmt_list> -> <stmt> <stmt_list>
6. <stmt_list> -> lambda

Notes:                                                                                 
- wherever there are **** that means there's a note                                    
at that specific area                                                                 
- else statments were added with comment if the code is wrong, this means 
there is a logic error because all input should be valid  
eventually we will have to delete the elses for submission
- check my logic for the lambda
- what ways can we use sets to solve problems?
********************************************************************************/

int SyntacticalAnalyzer::stmt_list()
{
  
        // VARIABLE DECLARATIONS 
	int errors = 0;
	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
        set<token_type>::iterator itr2 = follows.find(token);

	p2file << "Entering stmt_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	
	// RULE 5
	if( itr1 != follows.end() ) {
	  p2file << "Using Rule 5" << endl;

	  errors += stmt();
	  errors += stmt_list();
	}
	else {
	  cout << "rule 5 no first" << endl;
	}
	
	// RULE 6???


	p2file << "Exiting stmt_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
