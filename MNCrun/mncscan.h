/*	____________________________________________________________________________

	                 Scanner Component for the Micro Compiler

	                                mscan.h

	                              Version 2007
 
	                           James L. Richards
	                         Updated by Jeff Arthur
	                     Last Update: January 28th, 2016

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.2, pp. 25-29.
	____________________________________________________________________________
*/

#ifndef SCANNER
#define SCANNER
#include <string>

const int ID_STRING_LEN = 32;

// *******************
// **     Tokens    **
// *******************
//RESERVED WORD		  TOKEN             NAMING CONVENTION		SCANNER DONE
//"$eof$"             EOF_SYM.			-Done					-Done
//"bool"              BOOL_SYM.			-Done					-Done
//"break"             BREAK_SYM.		-Done					-Done
//"case"              CASE_SYM.			-Done					-Done
//"cheese"            CHEESE_SYM.		-Done					-Done
//"decs"              DECS_SYM.			-Done					-Done
//"do"                DO_SYM.			-Done					-Done
//"else"              ELSE_SYM.			-Done					-Done
//"end"               END_SYM.			-Done					-Done
//"false"             FALSE_SYM.		-Done					-Done
//"float"             FLOAT_SYM.		-Done					-Done
//"for"               FOR_SYM.			-Done					-Done
//"hiphip"            HIPHIP_SYM.		-Done					-Done
//"if"                IF_SYM.			-Done					-Done
//"int"               INT_SYM.			-Done					-Done
//"listen"            LISTEN_SYM.		-Done					-Done
//"otherwise"         OTHERWISE_SYM.	-Done					-Done
//"select"            SELECT_SYM.		-Done					-Done
//"shout"             SHOUT_SYM.		-Done					-Done
//"then"              THEN_SYM.			-Done					-Done
//"true"              TRUE_SYM.			-Done					-Done
//"while"             WHILE_SYM.		-Done					-Done
//"["                 LSTAPLE.			-Done					-Done
//"]"                 RSTAPLE.			-Done					-Done
//"("                 LBANANA.			-Done					-Done
//")"                 RBANANA.			-Done					-Done
//"{"                 LMUSTACHE.		-Done					-Done
//"}"                 RMUSTACHE.		-Done					-Done
//":"                 COLON.			-Done					-Done
//";"                 SEMICOLON.		-Done					-Done
//","                 COMMA.			-Done					-Done
//"="                 ASSIGN_OP.		-Done					-Done
//"+"                 PLUS_OP.			-Done					-Done
//"-"                 MINUS_OP.			-Done					-Done
//"*"                 MULT_OP.			-Done					-Done
//"/"                 DIV_OP.			-Done					-Done
//"<"                 LT_OP.			-Done					-Done
//"<="                LE_OP.			-Done					-Done
//">"                 GT_OP.			-Done					-Done
//">="                GE_OP.			-Done					-Done
//"=="                EQ_OP1.			-Done					-Done
//"!!"                EQ_OP2.			-Done					-Done
//"!="                NE_OP.			-Done					-Done
//"ID"                ID.				-Done					-Done
//"BOOL_LIT"          BOOL_LIT.			-Done					-Done
//"INT_LIT"           INT_LIT.			-Done					-Done
//"FLOAT_LIT"         FLOAT_LIT.		-Done					-Done
//"CHEESE_LIT"        CHEESE_LIT.		-Done					-Done

/*
enum Token  { BEGIN_SYM, END_SYM, EOF_SYM,
				LISTEN_SYM, SHOUT_SYM,
				LPAREN, RPAREN, SEMICOLON, COMMA,
				ASSIGN_OP, PLUS_OP, MINUS_OP,
				ID, INT_LITERAL, CHEESE_LITERAL };
*/
enum Token  { EOF_SYM,BOOL_SYM,BREAK_SYM,CASE_SYM,
	CHEESE_SYM,DECS_SYM,DO_SYM,ELSE_SYM,END_SYM,
	FALSE_SYM,FLOAT_SYM,FOR_SYM,HIPHIP_SYM,IF_SYM,
	INT_SYM,LISTEN_SYM,OTHERWISE_SYM,SELECT_SYM,SHOUT_SYM,
	THEN_SYM,TRUE_SYM,WHILE_SYM,LSTAPLE,RSTAPLE,
	LBANANA,RBANANA,LMUSTACHE,RMUSTACHE,COLON,
	SEMICOLON,COMMA,ASSIGN_OP,PLUS_OP,MINUS_OP,MULT_OP,
	DIV_OP,LT_OP,LE_OP,GT_OP,GE_OP,EQ_OP1,EQ_OP2,
	NE_OP,ID,BOOL_LIT,INT_LIT,FLOAT_LIT,CHEESE_LIT};

class Scanner
{
public:

	string	tokenBuffer, // current token
			lineBuffer,  // current line
			stringBuffer; // buffer to hold string
	int		lineNumber;  // line counter

	Scanner();
	// Initializes the scanner object.

	Token GetNextToken();
	// Retrieves the next token available in the input stream.

private:

   void BufferChar(char c);
   // Appends character c to the end of the token buffer provided that the
   // buffer is not full.

   Token CheckReserved();
   // Checks the identifier in the token buffer to see if it is a reserved word
   // or a user-defined identifier and returns the appropriate token.

   void ClearBuffer();
   // Erases the contents of the tokenBuffer.

   void LexicalError(char& c);
   // Processes a lexical error at character c by ignoring that character and 
   // getting the next character.

   char NextChar();
   // Gets next available character from the source file.
};
#endif
