/*	____________________________________________________________________________

	          Parser Component Implementation for the Micro Compiler

	                               mparse.cpp

	                              Version 2007
 
	                           James L. Richards
	                     Last Update: August 28, 2007
			     Updated by Marty J. Wolf
			       January 4, 2016

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.3-2.4, pp. 31-40.
	____________________________________________________________________________
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
using namespace std;
//
ifstream sourceFile;
//extern ofstream outFile, listFile;

#include "mncscan.h"   // Scanner class definition
#include "mncparse.h"  // Parser class definition

Scanner scan; // global scanner declared in micro.cpp
//extern CodeGen code; // global code generator declared in micro.cpp

Parser::Parser()
{
	tokenAvailable = false;  // no token initially available to parser
}

//void Parser::Match(Token t)
//{
//	if (t != NextToken())
//		SyntaxError(t);
//	else
//		tokenAvailable = false;
//}

Token Parser::NextToken()
{
	if (!tokenAvailable)
	{
		savedToken = scan.GetNextToken();
		tokenAvailable = true;
	}
		return savedToken;
}

void Parser::SyntaxError(Token t)
{
//	cout << " *** Syntax Error Detected " << int(t) << ' '
//		<< int(savedToken);
//	listFile << " *** Syntax Error Detected " << int(t) << ' '
//		<< int(savedToken);
//	sourceFile.close();
//	listFile.close();
//	outFile.close();
//	cin.ignore(256, '\n');
//	cin.get();
//	exit(1);  // error termination
}

void Parser::SystemGoal()
{
	//ProgramProc();
	//Match(EOF_SYM);
	//code.Finish();  /*** CODE ***/

	Token t;
	while ((t = NextToken()) != NULL) {
		cout << t << '\n';
	}


}

int main() {
	a:
	cout << "enter filename: ";
	string filename = "";
	cin >> filename;
	string dir = "C:\\Users\\Josh_2.Josh-PC\\Documents\\Visual Studio 2013\\Projects\\Macc n' Cheese\\Macc n' Cheese\\Debug\\";
	sourceFile.open(dir + filename);

	if (sourceFile.is_open()) {
		Parser p;
		p.SystemGoal();
	}
	else {
		cout << "unable to open file\n";
		
		goto a;
	}

	sourceFile.close();

	_getch();

	return 0;
}

void Parser::ProgramProc()         
{
//	code.Start();  /*** CODE ***/
	//Match(BEGIN_SYM);
	//StatementList();
	//Match(END_SYM);
}

//void Parser::StatementList()
//{
//	Statement();
//	for (;;) 
//	{  // loop exited by return
//		switch (NextToken())
//		{
//		case ID:
//		case LISTEN_SYM:
//		case SHOUT_SYM:
//			Statement();
//			break;
//		default:
//			return;
//		}
//	}
//}
//
//void Parser::StatementTail(){}
//
//void Parser::Statement()
//{
////	ExprRec identifier, expr;
//
//	switch (NextToken())
//	{
//	case ID:
////		Ident(identifier);
//		Match(ASSIGN_OP);
////		Expression(expr);
////		code.Assign(identifier, expr);  /*** CODE ***/
//		Match(SEMICOLON);
//		break;
//	case LISTEN_SYM:
//		Match(LISTEN_SYM);
//		Match(LPAREN);
//		IdList();
//		Match(RPAREN);
//		Match(SEMICOLON);
//		break;
//	case SHOUT_SYM:
//		Match(SHOUT_SYM);
//		Match(LPAREN);
//		ExprList();
//		Match(RPAREN);
//		Match(SEMICOLON);
////		code.NewLine();  /*** CODE ***/
//		break;
//	default:
//		SyntaxError(NextToken());
//	}
//}
//
//void Parser::SimpleStatement(){}
//
//void Parser::AssignStatement(){}
//
//void Parser::ListenStatement(){}
//
//void Parser::VariableList(){}
//
//void Parser::VariableListTail(){}
//
//void Parser::Variable(){}
//
//void Parser::VariableTail(){}
//
//void Parser::ShoutStatement(){}
//
//void Parser::ItemList(){}
//
//void Parser::ItemListTail(){}
//
//void Parser::IdList()
//{
////	ExprRec identifier;
//
////	Ident(identifier);
////	code.ReadId(identifier);  /*** CODE ***/
//	for (;;) 
//	{  // loop exited by return
//		if (NextToken() == COMMA)
//		{
//			Match(COMMA);
////			Ident(identifier);
////			code.ReadId(identifier);  /*** CODE ***/
//		}
//		else
//			return; // exit the function
//	}
//}
//
//void Parser::ExprList()
//{
//	ExprItem();
//	for (;;) 
//	{  // loop exited by return
//		if (NextToken() == COMMA)
//		{
//			Match(COMMA);
//			ExprItem();
//		}
//		else
//			return; // exit the function
//	}
//}	
//
//void Parser::ExprItem(){
//	if (NextToken() == CHEESE_LITERAL)
//	{	
////		code.WriteString();
//	}
//	else
//	{
////		ExprRec expr;
////		Expression(expr);
////		code.WriteExpr(expr);  /*** CODE ***/	
//	}
//}
//
//void Parser::Expression(ExprRec& result)
//{
////	ExprRec leftOperand, rightOperand;
////	OpRec op;
//
//	Primary(result);
//	for (;;) 
//	{  // loop exited by return
//		if (NextToken() == PLUS_OP || NextToken() == MINUS_OP)
//		{
//			// from call to Primary of gen_infix
//			leftOperand.kind = result.kind; 
//			leftOperand.val = result.val;
//			leftOperand.name= result.name;
//			AddOp(op);
//			Primary(rightOperand);
//         /*** CODE ***/
////			code.GenInfix (leftOperand, op, rightOperand, result);
//		}
//		else
//			return; // exit loop
//	}
//}
//
//void Parser::Primary(ExprRec& result)
//{
//	switch (NextToken())
//	{
//	case LPAREN:
//		Match(LPAREN);
//		Expression(result);
//		Match(RPAREN);
//		break;
//	case ID:
//		Match(ID);
////		code.ProcessId(result);  /*** CODE ***/
//		break;
//	case INT_LITERAL:
//		Match(INT_LITERAL);
////		code.ProcessLiteral(result);  /*** CODE ***/
//		break;
//	default:
//		SyntaxError(NextToken());
//	}
//}
//
//void Parser::AddOp(OpRec& op)
//{
//	switch (NextToken())
//	{
//	case PLUS_OP:
//		Match(PLUS_OP);
////		code.ProcessOp(op);  /*** CODE ***/
//		break;
//	case MINUS_OP:
//		Match(MINUS_OP);
////		code.ProcessOp(op);  /*** CODE ***/
//		break;
//	default:
//		SyntaxError(NextToken());
//	}
//}
//
//void Parser::Ident(ExprRec& result)
//{
//	Match(ID);
////	code.ProcessId(result);  /*** CODE ***/
//}
