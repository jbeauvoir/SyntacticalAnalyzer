/**************************************************
File: action.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the action 
tag function assoc. with rules 24-49

24. <action> -> IF_T <stmt> <stmt> <else_part>
25. <action> -> COND_T LPAREN_T <stmt_pair_body>
26. <action> -> LISTOP_T <stmt>
27. <action> -> CONS_T <stmt> <stmt>
28. <action> -> AND_T <stmt_list>
29. <action> -> OR_T <stmt_list>
30. <action> -> NOT_T <stmt>
31. <action> -> NUMBERP_T <stmt>
32. <action> -> SYMBOLP_T <stmt>
33. <action> -> LISTP_T <stmt>
34. <action> -> ZEROP_T <stmt>
35. <action> -> NULLP_T <stmt>
36. <action> -> STRINGP_T <stmt>
37. <action> -> PLUS_T <stmt_list>
38. <action> -> MINUS_T <stmt> <stmt_list>
39. <action> -> DIV_T <stmt> <stmt_list>
40. <action> -> MULT_T <stmt_list>
41. <action> -> MODULO_T <stmt> <stmt>
42. <action> -> EQUALTO_T <stmt_list>
43. <action> -> GT_T <stmt_list>
44. <action> -> LT_T <stmt_list>
45. <action> -> GTE_T <stmt_list>
46. <action> -> LTE_T <stmt_list>
47. <action> -> IDENT_T <stmt_list>
48. <action> -> DISPLAY_T <stmt>
49. <action> -> NEWLINE_T
************************************************************/

#include "SyntacticalAnalyzer.h"

int SyntacticalAnalyzer::action()
{

	int errors = 0;
	static set<token_type> firsts = {IF_T,COND_T,LISTOP_T,CONS_T,AND_T,
				     OR_T,NOT_T,NUMBERP_T,SYMBOLP_T,LISTP_T,ZEROP_T,
				     NULLP_T,STRINGP_T,PLUS_T,MINUS_T,DIV_T,MULT_T,
				     MODULO_T,EQUALTO_T,GT_T,LT_T,LTE_T,GTE_T,IDENT_T,
				     DISPLAY_T,NEWLINE_T};
	static set<token_type> follows = {RPAREN_T};


	p2file << "Entering action function; current token is: " 
		<< lex->GetTokenName (token) << endl;
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
		errors += stmt();
	}
	else if(token == CONS_T){
		p2file << "Using rule 27" << endl;
		errors += stmt();
		errors += stmt();
	}
	else if(token == AND_T){
		p2file << "Using rule 28" << endl;
		errors += stmt_list();
	}
	else if(token == OR_T){
		p2file << "Using rule 29" << endl;
		errors += stmt_list();
	}
	else if(token == NOT_T){
		p2file << "Using rule 30" << endl;
		errors += stmt();
	}
	else if(token == NUMBERP_T){
		p2file << "Using rule 31" << endl;
		errors += stmt();
	}
	else if(token == SYMBOLP_T){
		p2file << "Using rule 32" << endl;
		errors += stmt();
	} 
	else if(token == LISTP_T){
		p2file << "Using rule 33" << endl;
		errors += stmt();
	}
	else if(token == ZEROP_T){
		p2file << "Using rule 34" << endl;
		errors += stmt();
	}
	else if(token == NULLP_T){
		p2file << "Using rule 35" << endl;
		errors += stmt();
	}
	else if(token == STRINGP_T){
		p2file << "Using rule 36" << endl;
		errors += stmt();
	}
	else if(token == PLUS_T){
		p2file << "Using rule 37" << endl;
		errors += stmt_list();
	}
	else if(token == MINUS_T){
		p2file << "Using rule 38" << endl;
		errors += stmt();
		errors += stmt_list();
	}
	else if(token == DIV_T){
		p2file << "Using rule 39" << endl;
		errors += stmt();
		errors += stmt_list();
	} 
	else if(token == MULT_T){
		p2file << "Using rule 40" << endl;
		errors += stmt_list();
	}
	else if(token == MODULO_T){
		p2file << "Using rule 41" << endl;
		errors += stmt();
		errors += stmt();
	}
	else if(token == EQUALTO_T){
		p2file << "Using rule 42" << endl;
		errors += stmt_list();
	}
	else if(token == GT_T){
		p2file << "Using rule 43" << endl;
		errors += stmt_list();
	}
	else if(token == LT_T){
		p2file << "Using rule 44" << endl;
		errors += stmt_list();
	}
	else if(token == GTE_T){
		p2file << "Using rule 45" << endl;
		errors += stmt_list();
	}
	else if(token == LTE_T){
		p2file << "Using rule 46" << endl;
		errors += stmt_list();
	}
	else if(token == IDENT_T){
		p2file << "Using rule 47" << endl;
		errors += stmt_list();
	}
	else if(token == DISPLAY_T){
		p2file << "Using rule 48" << endl;
		errors += stmt();
	} 
	else if{
		p2file << "Using rule 49" << endl;
		token = lex->GetToken();
	}

	p2file << "Exiting action function; current token is: " 
	       << lex->GetTokenName (token) << endl;
	return errors;
}
