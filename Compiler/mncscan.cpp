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
//"otherwise"         OTHERWISE_SYM.		-Done					-Done
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
//"ID"                ID.			-Done					-Done
//"BOOL_LIT"          BOOL_LIT.			-Done					-Done
//"INT_LIT"           INT_LIT.			-Done					-Done
//"FLOAT_LIT"         FLOAT_LIT.		-Done					-Done
//"CHEESE_LIT"        CHEESE_LIT.		-Done					-Done

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
	//if (tokenBuffer == "BEGIN") return BEGIN_SYM; // no "begin" token
	if (tokenBuffer == "END") return END_SYM;
	if (tokenBuffer == "LISTEN") return LISTEN_SYM;
	if (tokenBuffer == "SHOUT") return SHOUT_SYM;
	if (tokenBuffer == "$eof$") return EOF_SYM;
	if (tokenBuffer == "BOOL") return BOOL_SYM;
	if (tokenBuffer == "BREAK") return BREAK_SYM;
	if (tokenBuffer == "CASE") return CASE_SYM;
	if (tokenBuffer == "CHEESE") return CHEESE_SYM;
	if (tokenBuffer == "DECS") return DECS_SYM;
	if (tokenBuffer == "DO") return DO_SYM;
	if (tokenBuffer == "ELSE") return ELSE_SYM;
	if (tokenBuffer == "END") return END_SYM;
	if (tokenBuffer == "FALSE") return FALSE_SYM;
	if (tokenBuffer == "FLOAT") return FLOAT_SYM;
	if (tokenBuffer == "FOR") return FOR_SYM;
	if (tokenBuffer == "HIPHIP") return HIPHIP_SYM;
	if (tokenBuffer == "IF") return IF_SYM;
	if (tokenBuffer == "INT") return INT_SYM;
	if (tokenBuffer == "LISTEN") return LISTEN_SYM;
	if (tokenBuffer == "OTHERWISE") return OTHERWISE_SYM;
	if (tokenBuffer == "SELECT") return SELECT_SYM;
	if (tokenBuffer == "SHOUT") return SHOUT_SYM;
	if (tokenBuffer == "THEN") return THEN_SYM;
	if (tokenBuffer == "TRUE") return TRUE_SYM;
	if (tokenBuffer == "WHILE") return WHILE_SYM;
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
				if (c == ".") {
					currentChar = NextChar();
					BufferChar(currentChar);
					c = sourceFile.peek();
					while (isdigit(c))
					{
						currentChar = NextChar();
						BufferChar(currentChar);
						c = sourceFile.peek();
					}
					return FLOAT_LIT;
				}
			}
			return INT_LIT;
		}
		// Added section here: start
		else if (currentChar == '[')
			return LSTAPLE;
		else if (currentChar == ']')
			return RSTAPLE;
		else if (currentChar == '{')
			return LMUSTACHE;
		else if (currentChar == '}')
			return RMUSTACHE;
		// Added section here: end
		else if (currentChar == '(')
			return LBANANA;
		else if (currentChar == ')')
			return RBANANA;
		else if (currentChar == ';')
			return SEMICOLON;
		else if (currentChar == ',')
			return COMMA;
		else if (currentChar == ':') {
			return COLON;
		}
		else if (currentChar == '*') {
			BufferChar(currentChar);
			return MULT_OP;
		}
		else if (currentChar == '/') {
			BufferChar(currentChar);
			return DIV_OP;
		}
		else if (currentChar == '+')
		{
			BufferChar(currentChar);
			return PLUS_OP;
		}
		else if (currentChar == '<')
		{
			if (sourceFile.peek() == '=')
			{                             // := operator
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				return LE_OP;
			}
			else {
				BufferChar(currentChar);
				return LT_OP;
			}
		}
		else if (currentChar == '>')
		{
			if (sourceFile.peek() == '=')
			{                             // := operator
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				return GE_OP;
			}
			else {
				BufferChar(currentChar);
				return GT_OP;
			}
		}
		else if (currentChar == '!')
		{
			if (sourceFile.peek() == '!')
			{                             // := operator
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				return EQ_OP2;
			}
			else if (sourceFile.peek() == '='){
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				return NE_OP;
			}
			else {
				LexicalError(currentChar);
			}
		}
		else if (currentChar == 'F' || currentChar == 'T')
		{
			if (sourceFile.peek() == 'A')
			{                             // := operator
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				if (sourceFile.peek() == 'L') {
					BufferChar(currentChar);
					currentChar = NextChar();
					BufferChar(currentChar);
					if (sourceFile.peek() == 'S') {
						BufferChar(currentChar);
						currentChar = NextChar();
						BufferChar(currentChar);
						if (sourceFile.peek() == 'E') {
							BufferChar(currentChar);
							currentChar = NextChar();
							BufferChar(currentChar);
							return BOOL_LIT;
						}
						else {
							LexicalError(currentChar);
						}
					}
					else {
						LexicalError(currentChar);
					}
				}
				else {
					LexicalError(currentChar);
				}
			}
			else if (sourceFile.peek() == 'R'){
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				if (sourceFile.peek() == 'U') {
					BufferChar(currentChar);
					currentChar = NextChar();
					BufferChar(currentChar);
					if (sourceFile.peek() == 'E') {
						BufferChar(currentChar);
						currentChar = NextChar();
						BufferChar(currentChar);
						return BOOL_LIT;
					}
					else {
						LexicalError(currentChar);
					}
				}
				else {
					LexicalError(currentChar);
				}
			}
			else {
				LexicalError(currentChar);
			}
		}
		else if (currentChar == '=')
		{
			if (sourceFile.peek() == '=')
			{                             // := operator
				BufferChar(currentChar);
				currentChar = NextChar();
				BufferChar(currentChar);
				return EQ_OP1;
			}
			else {
				return ASSIGN_OP;
			}
		}
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
