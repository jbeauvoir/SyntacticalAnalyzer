/************************************************************
File: more_tokens.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the more_tokens.cpp 
non-terminal function assoc. with rule 14 and 15.

14. <more_tokens> -> <any_other_tokens> <more_tokens>
15. <more_tokens> -> lambda


note: Check my logic for the lambda
************************************************************/
#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::more_tokens()
{
     
        // Variable Declaration
	int errors = 0;
	static set<token_type> firsts = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
                                     NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
                                     SYMBOLP_T,LISTP_T,STRINGP_T,ZEROP_T,NULLP_T,PLUS_T,MINUS_T,
                                     MULT_T,DIV_T,MODULO_T,EQUALTO_T,LT_T,GT_T,LTE_T,GTE_T,QUOTE_T,
                                     COND_T,ELSE_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	// set for any_other_token firsts
	static set<token_type> AOT = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
				     NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
				     SYMBOLP_T,LISTP_T,ZEROP_T,NULLP_T,STRINGP_T,PLUS_T,MINUS_T,
				     DIV_T,MULT_T,MODULO_T,EQUALTO_T,GT_T,LT_T,GTE_T,LTE_T,
				     QUOTE_T,COND_T,ELSE_T};

	set<string>::iterator itr1 = firsts.find(token);
	set<string>::iterator itr2 = follows.find(token);
	set<string>::iterator itr3 = AOT.find(token);

	p2file << "Entering more_tokens function; current token is: " 
		<< lex->GetTokenName (token) << endl;

	// RULE 14 
	if( itr3 != AOT.end() ) {
	  p2file << "Using Rule 14" << endl;

	  token = lex->GetToken();
	  p2file << "Inside Rule 14; current token is: " 
		 << lex->GetTokenName (token) << endl;	 
		
	  // Non-terminal checks
	  errors += any_other_token();
	  errors += more_tokens();
	}

	// RULE 15?
	

	p2file << "Exiting more_tokens function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
