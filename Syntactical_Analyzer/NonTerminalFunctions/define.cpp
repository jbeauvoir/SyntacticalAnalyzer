//#include "SyntacticalAnalyzer.h"

/************************************************************
File: Define.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the define 
non-terminal function assoc. with rule 2.

<define> -> LPAREN_T DEFINE_T LPAREN_T IDENT_T <param_list> 
RPAREN_T <stmt> <stmt_list> RPAREN_T
************************************************************/


int SyntacticalAnalyzer::define()
{
        // VARIABLE DECLARATION
	int errors = 0;	
	static set<token_type> firsts = {LPAREN_T};
	static set<token_type> follows = {LPAREN_T,EOF_T};
	
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);
	
	p2file << "Entering define function; current token is: " 
	       << lex->GetTokenName (token) << endl;

	p2file << "Using Rule 2" << endl;
	// DEFINE_T check
	if ( token == DEFINE_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting DEFINE_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
	  cout << "no define" << endl;
	}
	
	// LPAREN_T
	if ( token == LPAREN_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting LPAREN_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
	  cout << "no LPAREN" << endl;
	}

	// IDENT_T 
	if ( token == IDENT_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting IDENT_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
	  cout << "no ident_T" << endl;
	}

	// <param_list>
	errors += param_list();
	
	// RPAREN_T 
	if ( token == RPAREN_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting RPAREN_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
	  cout << "no RPAREN_T" << endl;
	}
	// nonterminals
	errors += stmt();
	errors += stmt_list();
	
	// RPAREN_T
	if ( token == RPAREN_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting RPAREN_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
	  cout << "no RPAREN_T" << endl;
	}
	

	p2file << "Exiting define function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
