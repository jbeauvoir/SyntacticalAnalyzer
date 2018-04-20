/************************************************************
File: quoted_lit.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the quoted_lit
non-terminal function assoc. with rule 13.
 
13. <quoted_lit> -> <any_other_token>

************************************************************/
#include "SyntacticalAnalyzer.h"


int SyntacticalAnalyzer::quoted_lit()
{
         // Variable Declrations 
	int errors = 0;
	static set<token_type> firsts = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
				     NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
				     SYMBOLP_T,LISTP_T,STRINGP_T,ZEROP_T,NULLP_T,PLUS_T,MINUS_T,
				     MULT_T,DIV_T,MODULO_T,EQUALTO_T,LT_T,GT_T,LTE_T,GTE_T,QUOTE_T,
				     COND_T,ELSE_T,RPAREN_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,RPAREN_T};

	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	p2file << "Entering quoted_lit function; current token is: " 
	       << lex->GetTokenName (token) << endl;

	// Singular rule means we can just use the set instead of the if-else blocks
	// RULE 13
	if( itr1 != firsts.end() ) {
	  p2file << "Using Rule 13" << endl;
	 
	  token = lex->GetToken();
		
	  p2file << "Exiting rule 13 function; current token is: " 
	       << lex->GetTokenName (token) << endl;

          // Non-terminal check
	  errors += any_other_token();
	}

	
	p2file << "Exiting quoted_lit function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
