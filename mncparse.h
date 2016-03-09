/*	____________________________________________________________________________

	                Parser Component for the Micro Compiler

	                                mparse.h

	                              Version 2007
 
	                           James L. Richards
	                     Last Update: August 28, 2007

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.3-2.4, pp. 31-40.
	____________________________________________________________________________

						 M I C R O   G R A M M A R

	<program>        -> #Start begin <statement list> end

	<statement list> -> <statement> { <statement> }

	<statement>      -> <ident> := <expression> #Assign ;
					 | read ( <id list> ) ;
					 | write ( <expr list> ) #NewLine ;

	<id list>        -> <ident> #ReadId { , <ident> #ReadId }

	<expr list>      -> <expr item> { , <expr item> }
	
	<expr item> 	 -> <expression> #WriteExpr
					    STR_LITERAL #WriteString

	<expression>     -> <primary> { <add op> <primary> #GenInfix }

	<primary>        -> ( <expression> )
					 | <ident>
					 | INT_LITERAL #ProcessLiteral

	<add op>         -> PLUS_OP #ProcessOp
					 | MINUS_OP #ProcessOp

	<ident>          -> ID #ProcessId

	<system goal>    -> <program> EOF_SYM #Finish
	____________________________________________________________________________
*/

#ifndef PARSER
#define PARSER

#include "mnccode.h"

class Parser
{
public:

	Parser();
	// Initializes the parser object.

	void SystemGoal();
	// Checks <system goal> syntax and semantics.

private:

	Token savedToken;
	bool tokenAvailable;

/* _____________________________________________________________________________
*/
	void SyntaxError(Token t);
	// Processes a syntax error and aborts compilation.

	Token NextToken();
	// Gets the next token and saves it.

	void Match(Token t);
	// Returns successfully if the next token matches t; otherwise, a syntax 
	// error occurs and compilation is aborted.

/* _____________________________________________________________________________
*/
	void ProgramProc();
	// Checks <program> syntax and semantics.

	void StatementList();
	// Checks <statement list> syntax and semantics.

	void StatementTail();

	void Statement();
	// Checks <statement> syntax and semantics.

	void SimpleStatement();

	void AssignStatement();

	void ListenStatement();

	void VariableList();

	void VariableListTail();

	void Variable();

	void VariableTail();

	void ShoutStatement();

	void ItemList();

	void ItemListTail();

	void BreakStatement();

	void StructStatment();

	void IfStmt();

	void ElseClause();

	void LoopStmt();

	void WhileStmt();

	void ForStmt();

	void SelectStmt();

	void CaseList();

	void CaseListTail();

	void Case();

	void IntList();

	void IntListTail();

	void CaseListEnd();

	void CondTail();

	void Expression();

	void ExprTail();

	void Factor();

	void FactorTail();

	void Primary();

	void Type();

	void BoolLit();

	void Literal();

	void MultOp();

	void AddOp();

	void RelOp();

	void VarDecs();

	void DecList();

	void DecTail();

	void Declaration();

	void VarDecList();

	void VarDecTail();

	void Init();

	void InitList();

	void InitTail();

	void IdList();
	// Checks <id list> syntax and semantics.

	void ExprList();
	// Checks <expr list> syntax and semantics.
	
	void ExprItem();
	// string modified

	void Expression(ExprRec& result);
	// Checks <expression> syntax and semantics.

	void Primary(ExprRec& result);
	// Checks <primary> syntax and semantics.

	void AddOp(OpRec& op);
	// Attempts to match an operator and process it.

	void Ident(ExprRec& result);
	// Attempts to match an identifier and process it.
};

#endif
