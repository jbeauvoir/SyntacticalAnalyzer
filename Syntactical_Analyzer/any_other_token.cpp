/**************************************************
File: any_other_token.cpp
Author: Jacques Beauvoir & Aaron Pineda
Description: This file has the any_other_token 
tag function assoc. with rules 50-81

50. <any_other_token> -> LPAREN_T <more_tokens> RPAREN_T
51. <any_other_token> -> IDENT_T
52. <any_other_token> -> NUMLIT_T
53. <any_other_token> -> STRLIT_T
54. <any_other_token> -> CONS_T
55. <any_other_token> -> IF_T
56. <any_other_token> -> DISPLAY_T
57. <any_other_token> -> NEWLINE_T
58. <any_other_token> -> LISTOP_T
59. <any_other_token> -> AND_T
60. <any_other_token> -> OR_T
61. <any_other_token> -> NOT_T
62. <any_other_token> -> DEFINE_T
63. <any_other_token> -> NUMBERP_T
64. <any_other_token> -> SYMBOLP_T
65. <any_other_token> -> LISTP_T
66. <any_other_token> -> ZEROP_T
67. <any_other_token> -> NULLP_T
68. <any_other_token> -> STRINGP_T
69. <any_other_token> -> PLUS_T
70. <any_other_token> -> MINUS_T
71. <any_other_token> -> DIV_T
72. <any_other_token> -> MULT_T
73. <any_other_token> -> MODULO_T
74. <any_other_token> -> EQUALTO_T
75. <any_other_token> -> GT_T
76. <any_other_token> -> LT_T
77. <any_other_token> -> GTE_T
78. <any_other_token> -> LTE_T
79. <any_other_token> -> QUOTE_T <any_other_token>
80. <any_other_token> -> COND_T
81. <any_other_token> -> ELSE_T
************************************************************/

#include "SyntacticalAnalyzer.h"

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

	if(token == LPAREN_T){//type1
	
	p2file << "Using Rule 50" << endl;
	token = lex->GetToken();
	errors += more_tokens();
	if(token == RPAREN_T){
		token = lex->GetToken();
	}else{
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
	token = lex->GetToken();
	p2file << "Exiting any_other_token function; current token is: " 
		<< lex->GetTokenName (token) << endl;


	return errors;
}
