/*	____________________________________________________________________________

	         Scanner Component Implementation for the Micro Compiler

	                               mscan.cpp

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

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern ifstream sourceFile;
extern ofstream outFile, listFile;

#include "mascan.h"

// *******************
// **     Tokens    **
// *******************
//RESERVED WORD		  TOKEN             NAMING CONVENTION		SCANNER DONE
//"$eof$"             EOF_SYM.			-Done
//"bool"              BOOL_SYM.
//"break"             BREAK_SYM.
//"case"              CASE_SYM.
//"cheese"            CHEESE_SYM.
//"decs"              DECS_SYM.
//"do"                DO_SYM.
//"else"              ELSE_SYM.
//"end"               END_SYM.			-Done
//"false"             FALSE_SYM.
//"float"             FLOAT_SYM.
//"for"               FOR_SYM.
//"hiphip"            HIPHIP_SYM.
//"if"                IF_SYM.
//"int"               INT_SYM.
//"listen"            LISTEN_SYM.		-Done
//"otherwise"         OTHERWISE_SYM.
//"select"            SELECT_SYM.
//"shout"             SHOUT_SYM.		-Done
//"then"              THEN_SYM.
//"true"              TRUE_SYM.
//"while"             WHILE_SYM.
//"["                 LSTAPLE.
//"]"                 RSTAPLE.
//"("                 LBANANA.			-Done
//")"                 RBANANA.			-Done
//"{"                 LMUSTACHE.
//"}"                 RMUSTACHE.
//":"                 COLON.
//";"                 SEMICOLON.		-Done
//","                 COMMA.			-Done
//"="                 ASSIGN_OP.		-Done
//"+"                 PLUS_OP.			-Done
//"-"                 MINUS_OP.			-Done
//"*"                 MULT_OP.
//"/"                 DIV_OP.
//"<"                 LT_OP.
//"<="                LE_OP.
//">"                 GT_OP.
//">="                GE_OP.
//"=="                EQ_OP1.
//"!!"                EQ_OP2.
//"!="                NE_OP.
//"ID"                ID.				-Done
//"BOOL_LIT"          BOOL_LIT.
//"INT_LIT"           INT_LIT.			-Done
//"FLOAT_LIT"         FLOAT_LIT.
//"CHEESE_LIT"        CHEESE_LIT.		-Done

int x = 0; // Get rid of later

// *******************
// **  Constructor  **
// *******************

Scanner::Scanner()
{
	tokenBuffer = "";
	lineBuffer = "";
	stringBuffer = "";
	lineNumber = 0;
}

// ********************************
// **  Private Member Functions  **
// ********************************

void Scanner::BufferChar(char c)
{
	if (tokenBuffer.length() < ID_STRING_LEN)
		tokenBuffer += toupper(c);
}

Token Scanner::CheckReserved()
{
	//if (tokenBuffer == "BEGIN") return BEGIN_SYM;
	if (tokenBuffer == "END") return END_SYM;
	if (tokenBuffer == "LISTEN") return LISTEN_SYM;
	if (tokenBuffer == "SHOUT") return SHOUT_SYM;
	return ID;
}

void Scanner::ClearBuffer()
{
	tokenBuffer = "";
	stringBuffer = "";
}

void Scanner::LexicalError(char& c)
{
	cout << " *** Lexical Error: '" << c
		<< "' ignored at position " << int(lineBuffer.size())
		<< " on line #" << lineNumber+1 << '.' << endl;
	listFile << " *** Lexical Error: '" << c
		<< "' ignored at position " << int(lineBuffer.size())
		<< " on line #" << lineNumber+1 << '.' << endl;
	c = NextChar();
}

char Scanner::NextChar()
{
	char c;

	sourceFile.get(c);
	if (c == '\n')
	{
		listFile.width(6);
		listFile << ++lineNumber << "  " << lineBuffer << endl;
		lineBuffer = "";
	}
	else
		lineBuffer += c;
	return c;
}

// *******************************
// **  Public Member Functions  **
// *******************************

Token Scanner::GetNextToken()
{
	char currentChar, c;

	ClearBuffer();
	currentChar = NextChar();
	while (!sourceFile.eof())
	{
		if (isspace(currentChar))
			currentChar = NextChar();     // do nothing
		else if (isalpha(currentChar))
		{                                // identifier
			BufferChar(currentChar);
			c = sourceFile.peek();
			while (isalnum(c) || c == '_')
			{
				currentChar = NextChar();
				BufferChar(currentChar);
				c = sourceFile.peek();
			}
			return CheckReserved();
		}
		else if (isdigit(currentChar))
		{                                // integer literal
			BufferChar(currentChar);
			c = sourceFile.peek();
			while (isdigit(c))
			{
				currentChar = NextChar();
				BufferChar(currentChar);
				c = sourceFile.peek();
			}
			return INT_LIT;
		}
		else if (currentChar == '(')
			return LBANANA;
		else if (currentChar == ')')
			return RBANANA;
		else if (currentChar == ';')
			return SEMICOLON;
		else if (currentChar == ',')
			return COMMA;
		else if (currentChar == '+')
		{
			BufferChar(currentChar);
			return PLUS_OP;
		}
		else if (currentChar == ':')
			if (sourceFile.peek() == '=')
			{                             // := operator
				currentChar = NextChar();
				return ASSIGN_OP;
			}
			else
				LexicalError(currentChar);
		else if (currentChar == '-')  
			if (sourceFile.peek() == '-') // comment
				do  // skip comment
					currentChar = NextChar();
				while (currentChar != '\n');
			else
			{
				BufferChar(currentChar);      // minus operator
				return MINUS_OP;
			}
		else if (currentChar == '"')		// string character
			do {
				currentChar = NextChar();
				c = sourceFile.peek();
				if (currentChar == '"' && c == '"'){
					currentChar = NextChar();
				}
				else if (currentChar == '"' && c != '"'){
					return CHEESE_LIT;
				}
				stringBuffer += currentChar;
			}
			while (c != '\n');
		else
			LexicalError(currentChar);
	} // end while
	return EOF_SYM;
}
