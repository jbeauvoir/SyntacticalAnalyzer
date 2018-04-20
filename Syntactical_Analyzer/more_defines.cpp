#include "SyntacticalAnalyzer.h"

/*******************************************************************************
Function: more_defines

Parameters: none
Return value: integer named "errors"
Description: This is rule number 3 and 4.
3. <more_defines> -> <define> <more_defines>
4. <more_defines> -> lambda 

Notes: 
- wherever there are **** that means there's a note 
at that specific area
- else statments were added with comment if the code is wrong, this means
there is a logic error because all input should be valid 
eventually we will have to delete the elses for submission
********************************************************************************/
int SyntacticalAnalyzer::more_defines()
{

	int errors = 0;
	static set<token_type> firsts = {LPAREN_T,EOF_T};
	static set<token_type> follows = {EOF_T};

	set<token_type>::iterator itr1 = firsts.find(token);
        set<token_type>::iterator itr2 = follows.find(token);

	// this should be a LPAREN
	p2file << "Entering more_defines function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	
	// LPAREN_T check
	// **** note: check logic here
	// I didn't do next token because we need it for 
	// the define() firsts

	// RULE 3
	if ( token == LPAREN_T ) {
	  p2file << "Using Rule 3" << endl;

	  token = lex->GetToken();
	  
    	  // Non-terminal check
	  errors += define();
	  errors += more_defines();
	  
	  p2file << "Exiting LPAREN_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	// RULE 4
	else if ( token == EOF_T ) {
	  p2file << "Using Rule 4" << endl;

	  token = lex->GetToken();
		
	  p2file << "Exiting EOF_T check; current token is: "
                 << lex->GetTokenName (token) << endl;

	  return errors;
	}
	// SOL
	else { 
	  cout << "no EOF_T or LPAREN" << endl;
	}
	
	// Should be EOF_T
	p2file << "Exiting more_defines function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
