/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author: Aaron Pineda, Jacques Beauvoir                                       *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function: Constructor of the syntax analyzer.                                *
*                                                                              *
* Parameters: The source code that is to be parsed                             *
* Return value: None                                                           *
* Description: This function will declare a lexical analyzer object and        *
* declare output file names. Lastly, it starts the parsing.                    *
*******************************************************************************/
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	string name = filename;
	string p2name = name.substr (0, name.length()-3) + ".p2"; 
	p2file.open (p2name.c_str());
	token = lex->GetToken();
	Program ();
}

/*******************************************************************************
* Function: Default destructor                                                 *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will delete the lexical analyzer object and close *
* the p2file.        														   *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
	p2file.close ();
}

/*******************************************************************************
* Function: Program                                                            *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will start parsing by checking if the input source*
* code is syntactically correct by checking if the scheme file starts with a   *
* left parentheses. If the first token is not a left parentheses, a diagnostic *
* message will be given.      												   *
*******************************************************************************/
int SyntacticalAnalyzer::Program()
{
	p2file << "Entering Program function; current token is: "
					<< lex->GetTokenName (token) << endl;
	int errors = 0;
	static set<token_type> firsts = {LPAREN_T};
	static set<token_type> follows = {};
	set<token_type>::iterator itr_firsts = firsts.find(token);
	set<token_type>::iterator itr_follows = follows.find(token);

	while(itr_firsts == firsts.end() && itr_follows == follows.end())
	{
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + "found in Program function.");
		errors++;
		token = lex->GetToken();
		itr_firsts = firsts.find(token);
		itr_follows = follows.find(token);
	}

	if( token == LPAREN_T ) {
	
	  p2file << "Using Rule 1" << endl;
	  errors += define();
	  errors += more_defines();
	  
	}
	else
	{
		lex->ReportError("Source code did not start with left parentheses. Found: " + lex->GetTokenName(token));
	}
	// token should be in follows of Program
	if (token != EOF_T) {
	    errors++;
	    lex->ReportError ("Missing end of file at end of program");
	  }
	p2file << "Exiting Program function; current token is: "
					<< lex->GetTokenName (token) << endl;
	return errors;
}

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

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + "found in define function.");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	
		
	// LPAREN_T
	if ( token == LPAREN_T ) {
		p2file << "Using Rule 2" << endl;
	    token = lex->GetToken();
	    p2file << "Exiting LPAREN_T check; current token is: "
		  << lex->GetTokenName (token) << endl;
	}
	else {
	  	errors++;
		lex->ReportError("Source code did not start with left parentheses. Found: " + lex->GetTokenName(token));
	}
	
    // DEFINE_T check
	if ( token == DEFINE_T ) 
	{
	  token = lex->GetToken();
	  p2file << "Exiting DEFINE_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else 
	{
		lex->ReportError("Expected DEFINE_T not found. Found: " + lex->GetTokenName(token));
		errors++;
	}
	
	// LPAREN_T 2
    if ( token == LPAREN_T ) {
        token = lex->GetToken();
        p2file << "Exiting LPAREN_T check; current token is: "
                 << lex->GetTokenName (token) << endl;
	}
    else {
		lex->ReportError("Expected LPARENT_T after DEFINE_T not found. Found: " + lex->GetTokenName(token));
		errors++;
	}


	// IDENT_T 
	if ( token == IDENT_T ) {
	  token = lex->GetToken();
	  p2file << "Exiting IDENT_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	else {
		lex->ReportError("Expected IDENT_T not found. Found: " + lex->GetTokenName(token));
		errors++;
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
		lex->ReportError("Expected RPAREN_T not found. Found: " + lex->GetTokenName(token));
		errors++;
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
		lex->ReportError("Expected RPAREN_T not found. Found: " + lex->GetTokenName(token));
		errors++;
	}
	
	
	p2file << "Exiting define function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: any_other_token                                                    *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::any_other_token()
{
	int errors = 0;
	p2file << "Entering any_other_token function; current token is: " 
		<< lex->GetTokenName (token) << endl;


	static set<token_type> firsts = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
				     NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
				     SYMBOLP_T,LISTP_T,ZEROP_T,NULLP_T,STRINGP_T,PLUS_T,MINUS_T,
				     DIV_T,MULT_T,MODULO_T,EQUALTO_T,GT_T,LT_T,GTE_T,LTE_T,
				     QUOTE_T,COND_T,ELSE_T};
	static set<token_type> follows = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
				      NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
				      SYMBOLP_T,LISTP_T,STRINGP_T,ZEROP_T,NULLP_T,PLUS_T,MINUS_T,
				      MULT_T,DIV_T,MODULO_T,EQUALTO_T,LT_T,GT_T,LTE_T,GTE_T,QUOTE_T,
				      COND_T,ELSE_T,RPAREN_T};

	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);
	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + "found in any_other_token function.");
		errors++;
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	if(token == LPAREN_T){//type1
	
	  p2file << "Using Rule 50" << endl;
	  token = lex->GetToken();
	  errors += more_tokens();
	  
	  if(token == RPAREN_T){
	    token = lex->GetToken();
	  }
	  else{
	    errors++;
	    lex->ReportError("Expected first of any_other_token; found: " + lex->GetTokenName(token));
	  }
	}
	else if(token == IDENT_T){
		p2file << "Using rule 51" << endl;
		
	}
	else if(token == NUMLIT_T){
		p2file << "Using rule 52" << endl;
		
	}
	else if(token == STRLIT_T){
		p2file << "Using rule 53" << endl;
		
	}
	else if(token == CONS_T){
		p2file << "Using rule 54" << endl;
		
	}
	else if(token == IF_T){
		p2file << "Using rule 55" << endl;
		
	}
	else if(token == DISPLAY_T){
		p2file << "Using rule 56" << endl;
		
	}
	else if(token == NEWLINE_T){
		p2file << "Using rule 57" << endl;
		
	}
	else if(token == LISTOP_T){
		p2file << "Using rule 58" << endl;
		
	}
	else if(token == AND_T){
		p2file << "Using rule 59" << endl;
		
	}
	else if(token == OR_T) {
		p2file << "Using rule 60" << endl;
		
	}
	else if(token == NOT_T){
		p2file << "Using rule 61" << endl;
		
	}
	else if(token == DEFINE_T){
		p2file << "Using rule 62" << endl;
		
	} 
	else if(token == NUMBERP_T){
		p2file << "Using rule 63" << endl;
		
	}
	else if(token == SYMBOLP_T){
		p2file << "Using rule 64" << endl;
		
	}
	else if(token == LISTP_T){
		p2file << "Using rule 65" << endl;
		
	}
	else if(token == ZEROP_T){
		p2file << "Using rule 66" << endl;
		
	}
	else if(token == NULLP_T){
		p2file << "Using rule 67" << endl;
		
	}
	else if(token == STRINGP_T){
		p2file << "Using rule 68" << endl;
		
	}
	else if(token == PLUS_T){
		p2file << "Using rule 69" << endl;
		
	} 
	else if(token == MINUS_T){
		p2file << "Using rule 70" << endl;
		
	}
	else if(token == DIV_T){
		p2file << "Using rule 71" << endl;
		
	}
	else if(token == MULT_T){
		p2file << "Using rule 72" << endl;
		
	}
	else if(token == MODULO_T){
		p2file << "Using rule 73" << endl;
		
	} 
	else if(token == EQUALTO_T){
		p2file << "Using rule 74" << endl;
		
	}
	else if(token == GT_T){
		p2file << "Using rule 75" << endl;
		
	}
	else if(token == LT_T){
		p2file << "Using rule 76" << endl;
		
	}
	else if(token == GTE_T){
		p2file << "Using rule 77" << endl;
		
	}
	else if(token == LTE_T){
		p2file << "Using rule 78" << endl;
	
	}
	else if(token == QUOTE_T){
		p2file << "Using rule 79" << endl;
		token = lex->GetToken();
		errors += any_other_token();
	}
	else if(token == COND_T){
		p2file << "Using rule 80" << endl;
		
	}
	else if(token == ELSE_T){
		p2file << "Using rule 81" << endl;
	
	}
	else
	{
		lex->ReportError("Expected firsts of any_other_token not found. Found: " + lex->GetTokenName(token));
		errors++;
	}
	token = lex->GetToken();
	p2file << "Exiting any_other_token function; current token is: " 
		<< lex->GetTokenName (token) << endl;


	return errors;


}



/*******************************************************************************
* Function: action                                                             *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::action()
{
  	int errors = 0;
	p2file << "Entering action function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {IF_T,COND_T,LISTOP_T,CONS_T,AND_T,
				     OR_T,NOT_T,NUMBERP_T,SYMBOLP_T,LISTP_T,ZEROP_T,
				     NULLP_T,STRINGP_T,PLUS_T,MINUS_T,DIV_T,MULT_T,
				     MODULO_T,EQUALTO_T,GT_T,LT_T,LTE_T,GTE_T,IDENT_T,
				     DISPLAY_T,NEWLINE_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + "found at beginning of action");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}


	if(token == IF_T){
		p2file << "Using rule 24" << endl;
		token = lex->GetToken();
		errors += stmt();
		errors += stmt();
		errors += else_part();
	}
	else if(token == COND_T){
		p2file << "Using rule 25" << endl;
		token = lex->GetToken();
		lex->GetTokenName(token);
		if(token == LPAREN_T){
			p2file << "Using rule 25" << endl;
			token = lex->GetToken();
			errors += stmt_pair_body();
		}
	}
	else if(token == LISTOP_T){
		p2file << "Using rule 26" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == CONS_T){
		p2file << "Using rule 27" << endl;
		token = lex->GetToken();
		errors += stmt();
		errors += stmt();
	}
	else if(token == AND_T){
		p2file << "Using rule 28" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == OR_T){
		p2file << "Using rule 29" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == NOT_T){
		p2file << "Using rule 30" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == NUMBERP_T){
		p2file << "Using rule 31" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == SYMBOLP_T){
		p2file << "Using rule 32" << endl;
		token = lex->GetToken();
		errors += stmt();
	} 
	else if(token == LISTP_T){
		p2file << "Using rule 33" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == ZEROP_T){
		p2file << "Using rule 34" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == NULLP_T){
		p2file << "Using rule 35" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == STRINGP_T){
		p2file << "Using rule 36" << endl;
		token = lex->GetToken();
		errors += stmt();
	}
	else if(token == PLUS_T){
		p2file << "Using rule 37" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == MINUS_T){
		p2file << "Using rule 38" << endl;
		token = lex->GetToken();
		errors += stmt();
		errors += stmt_list();
	}
	else if(token == DIV_T){
		p2file << "Using rule 39" << endl;
		token = lex->GetToken();
		errors += stmt();
		errors += stmt_list();
	} 
	else if(token == MULT_T){
		p2file << "Using rule 40" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == MODULO_T){
		p2file << "Using rule 41" << endl;
		token = lex->GetToken();
		errors += stmt();
		errors += stmt();
	}
	else if(token == EQUALTO_T){
		p2file << "Using rule 42" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == GT_T){
		p2file << "Using rule 43" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == LT_T){
		p2file << "Using rule 44" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == GTE_T){
		p2file << "Using rule 45" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == LTE_T){
		p2file << "Using rule 46" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == IDENT_T){
		p2file << "Using rule 47" << endl;
		token = lex->GetToken();
		errors += stmt_list();
	}
	else if(token == DISPLAY_T){
		p2file << "Using rule 48" << endl;
		token = lex->GetToken();
		errors += stmt();
	} 
	else if(token == NEWLINE_T){
		p2file << "Using rule 49" << endl;
		token = lex->GetToken();
		
	}
	else{
		errors++;
		lex->ReportError("Expected firsts of action not found. Found: " + lex->GetTokenName(token));

	}

	p2file << "Exiting action function; current token is: " 
	       << lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: else_part                                                          *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::else_part()
{
        // Variable Declaration
 	int errors = 0;
	p2file << "Entering else_part function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + " found at beginning of else_part");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	
	// RULE 18
	// one of the firsts terminals is present
	//	if ( itr1 != firsts.end() ) {
	//  p2file << "Using Rule 18" << endl;
	//  errors += stmt(); 
	//	}
	if(token == IDENT_T || token == LPAREN_T || token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T){
	  p2file << "Using rule 18" << endl;
	  errors += stmt();
	}
	// RULE 19 
	else if( token == RPAREN_T ) {
	  p2file << "Using Rule 19" << endl; 
	}
	else
	{
		errors++;
		lex->ReportError("Firsts of else_part not found. Found " + lex->GetTokenName(token));
	}

	p2file << "Exiting else_part function; current token is: " 
           << lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: literal                                                            *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::literal()
{
          // Variable Declarations
    int errors = 0;
	p2file << "Entering literal function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,
				      RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + " found at beginning of literal.");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}  

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
		errors++;
		lex->ReportError("Firsts of literal not found. Found: " + lex->GetTokenName(token));

	}
	 
	p2file << "Exiting literal function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: more_defines                                                       *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::more_defines()
{
  	int errors = 0;
	  // this should be a LPAREN
	p2file << "Entering more_defines function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {LPAREN_T,EOF_T};
	static set<token_type> follows = {EOF_T};
	set<token_type>::iterator itr1 = firsts.find(token);
    set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at beginning of more_defines.");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	
	// LPAREN_T check
	// **** note: check logic here
	// I didn't do next token because we need it for 
	// the define() firsts

	// RULE 3
	if ( token == LPAREN_T ) {
	  	p2file << "Using Rule 3" << endl;

	  	// token = lex->GetToken();
	  
        // Non-terminal check
	  	errors += define();
	  	errors += more_defines();
	  
	 	p2file << "Exiting LPAREN_T check; current token is: "
		 << lex->GetTokenName (token) << endl;
	}
	// RULE 4
	else if ( token == EOF_T ) {
	  p2file << "Using Rule 4" << endl;

	  //token = lex->GetToken();
		
	  //p2file << "Exiting EOF_T check; current token is: "
	  //     << lex->GetTokenName (token) << endl;
	}
	// SOL
	else { 
		errors++;
		lex->ReportError("Firsts of more_defines not found. Found: " + lex->GetTokenName(token));
	}
	
	// Should be EOF_T
	p2file << "Exiting more_defines function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: more_tokens                                                        *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::more_tokens()
{
          // Variable Declaration
	int errors = 0;
	p2file << "Entering more_tokens function; current token is: " 
		<< lex->GetTokenName (token) << endl;
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

	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);
	set<token_type>::iterator itr3 = AOT.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpcted " + lex->GetTokenName(token) + " at beginning of more_tokens");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}

	// RULE 14 
	if( itr3 != AOT.end() ) {
	  p2file << "Using Rule 14" << endl;

	  token = lex->GetToken();
	 

	  // Non-terminal checks
	  errors += any_other_token();
	  errors += more_tokens();
	}
	else if( token == RPAREN_T ){
	  p2file << "Using Rule 15" << endl;
	}
	// RULE 15?
	
	else{
		errors++;
		lex->ReportError("Firsts of more_tokens not found. Found: " + lex->GetTokenName(token));
	}
	p2file << "Exiting more_tokens function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: param_list                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::param_list()
{
  
	int errors = 0;
	p2file << "Entering param_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {IDENT_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at beginning of param_list");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	

	// RULE 16
	if ( token == IDENT_T ) {
	  	p2file << "Using Rule 16" << endl;
	  	token = lex->GetToken();
	  	// Non-terminal check 
	  	errors += param_list();
	}
	// RULE 17
	else if( token == RPAREN_T ) {
	  p2file << "Using Rule 17" << endl;
	}
	else
	{
		errors++;
		lex->ReportError("Firsts of param_list not found. Found " + lex->GetTokenName(token));
	}
	p2file << "Exiting param_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: quoted_lit                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::quoted_lit()
{
           // Variable Declrations 
	int errors = 0;
	p2file << "Entering quoted_lit function; current token is: " 
	       << lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {LPAREN_T,IDENT_T,NUMLIT_T,STRLIT_T,CONS_T,IF_T,DISPLAY_T,
				     NEWLINE_T,LISTOP_T,AND_T,OR_T,NOT_T,DEFINE_T,NUMBERP_T,
				     SYMBOLP_T,LISTP_T,STRINGP_T,ZEROP_T,NULLP_T,PLUS_T,MINUS_T,
				     MULT_T,DIV_T,MODULO_T,EQUALTO_T,LT_T,GT_T,LTE_T,GTE_T,QUOTE_T,
				     COND_T,ELSE_T,RPAREN_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,RPAREN_T};

	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Unexpected " + lex->GetTokenName(token) + " found at the beginning of quoted_lit");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	

	
	
		
	  p2file << "Using rule 13 function; current token is: " 
	       << lex->GetTokenName (token) << endl;

          // Non-terminal check
	  errors += any_other_token();
	

	
	p2file << "Exiting quoted_lit function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: stmt_list                                                          *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_list()
{
  //        cout << "inside stmt list" << endl;
        // VARIABLE DECLARATIONS 
	int errors = 0;
	p2file << "Entering stmt_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
    set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at beginning of stmt_list");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	
	//	cout << "before rule 5 in stmtnt list" << endl;
	// RULE 5
	if( token == IDENT_T || token == LPAREN_T || token == NUMLIT_T || 
	    token == STRLIT_T || token == QUOTE_T ) {
	  p2file << "Using Rule 5" << endl;
 
	  errors += stmt();
	  errors += stmt_list();
	}
	// RULE 6
	else if ( token == RPAREN_T ){
	  p2file << "Using Rule 6" << endl;
	}
	else
	{
		errors++;
		lex->ReportError("Expected firsts of stmt_list not found. Found: " + lex->GetTokenName(token));
	}


	p2file << "Exiting stmt_list function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: stmt_pair_body                                                     *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair_body()
{
          // Variable Declaration
	int errors = 0;
	p2file << "Entering stmt_pair_body function; current token is: " 
	       << lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {ELSE_T,IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);
	
	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at beginning of stmt_pair_body");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}

	// So for the next few if-else blocks you'll notice
	// that rule 23 precedes 22. I did this because I 
	// didn't want to type out a long OR ||  statement. By 
	// checking for ELSE_T first, I can simply do a set check
	// with stmt_pair_body's firsts.

	// RULE 23
	if( token == ELSE_T ) {
	  	p2file << "Using Rule 23" << endl;
	  	token = lex->GetToken();
	  	// Non-terminal checks
	  	errors += stmt();

	  	// Terminal after <stmt>
	  	if( token == RPAREN_T ) {
	    	token = lex->GetToken();
	  	}
	  	else {
	    	errors++;
			lex->ReportError("Firsts of stmt_pair_body not found. Found: " + lex->GetTokenName(token));
	  	}
	  	errors += stmt_pair();
	}
	// RULE 22 
	else if ( itr1 != firsts.end() ) {
	  	p2file << "Using Rule 22" << endl;
	  
	  	// Non-terminal checks
	  	errors += stmt();
	  	errors += stmt();
	  
	  	// Non-terminal check after <stmt>
	  	if ( token == RPAREN_T ) {
	   		token = lex->GetToken();
	  	}
	  	else{
		  	errors++;
		  	lex->ReportError("Firsts of stmt_pair_body not found. Found: " + lex->GetTokenName(token));
	  	}
	}
	
	p2file << "Exiting stmt_pair_body function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: stmt_pair                                                          *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair()
{
          // Variable Declaration
	int errors = 0;
	p2file << "Entering stmt_pair function; current token is: " 
	       << lex->GetTokenName (token) << endl;
	static set<token_type> firsts = {LPAREN_T,RPAREN_T};
	static set<token_type> follows = {RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
	set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at beginning of stmt_pair");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}
	

	// RULE 20
	if( token == LPAREN_T ) {
	  p2file << "Using Rule 20" << endl;
	  token = lex->GetToken();
	  errors += stmt_pair_body();
	}
	// RULE 21
	else if ( token == RPAREN_T ) {
	  p2file << "Using Rule 21" << endl;
	}
	
	else {
		errors++;
		lex->ReportError("Firsts of stmt_pair not found. Found: " + lex->GetTokenName(token));
	}
	
	p2file << "Exiting stmt_pair function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}


/*******************************************************************************
* Function: stmt                                                               *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will ouptut which rule is used depending on which *
* token is gathered.														   *
*******************************************************************************/
int SyntacticalAnalyzer::stmt()
{
          // Variable Declaration 
    int errors = 0;
	p2file << "Entering stmt function; current token is: " 
			<< lex->GetTokenName (token) << endl;
  	static set<token_type> firsts = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T};
	static set<token_type> follows = {IDENT_T,LPAREN_T,NUMLIT_T,STRLIT_T,QUOTE_T,
				      RPAREN_T};
	set<token_type>::iterator itr1 = firsts.find(token);
    set<token_type>::iterator itr2 = follows.find(token);

	while(itr1 == firsts.end() && itr2 == follows.end())
	{
		errors++;
		lex->ReportError("Found unexpected " + lex->GetTokenName(token) + " at the beginning of stmt");
		token = lex->GetToken();
		itr1 = firsts.find(token);
		itr2 = follows.find(token);
	}


	// RULE 7
	if ( token == NUMLIT_T || token == QUOTE_T || token == STRLIT_T ) {
	  	p2file << "Using Rule 7" << endl;
	
	  	errors += literal();
	}
	// RULE 8
	else if ( token == IDENT_T ) {
	  	p2file << "Using Rule 8" << endl;

	  	token = lex->GetToken();
	}

	// RULE 9
	else if ( token == LPAREN_T ) {
	  	p2file << "Using Rule 9" << endl;
	
	  	token = lex->GetToken();
		
        // Non-terminal check
	  	errors += action();

	  	if ( token == RPAREN_T ) {
	    	lex->GetTokenName (token);
	    
	  	}
	  	else {
	    	errors++; 
			lex->ReportError("RPARENT not found after rule 9. Found: " + lex->GetTokenName(token));
	  	}
	}
	else {
	 	errors++;
		 lex->ReportError("Firsts of stmt not found. Found: " + lex->GetTokenName(token));
	}

	p2file << "Exiting stmt function; current token is: " 
		<< lex->GetTokenName (token) << endl;
	return errors;
}
