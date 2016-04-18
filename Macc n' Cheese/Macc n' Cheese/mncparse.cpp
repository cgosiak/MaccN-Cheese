// MACC_N_CHEESE Grammar 2016
// 
// Parser Class Implementation File

// SHELL GENERATED BY PARSERGEN VERSION 5.0.3

//#define PRINT_TOKENS

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "mncparse.h"
#include "mnccode.h"
#include "mncscan.h"

float str_to_float(string str) {
	stringstream s(str);
	float ret;
	s >> ret;
	return ret;
}

#pragma region gettokentext

#define X(x) { x, #x },
struct Tokens {
	int id;
	char* pname;
} Tokens[] =
{
	X(EOF_SYM)X(BOOL_SYM)X(BREAK_SYM)X(CASE_SYM)X(CHEESE_SYM)X(DECS_SYM)X(DO_SYM)X(ELSE_SYM)X(END_SYM)X(FALSE_SYM)X(FLOAT_SYM)X(FOR_SYM)
	X(HIPHIP_SYM)X(IF_SYM)X(INT_SYM)X(LISTEN_SYM)X(OTHERWISE_SYM)X(SELECT_SYM)X(SHOUT_SYM)X(THEN_SYM)X(TRUE_SYM)X(WHILE_SYM)X(UNTIL_SYM)
	X(LSTAPLE)X(RSTAPLE)X(LBANANA)X(RBANANA)X(LMUSTACHE)X(RMUSTACHE)X(COLON)X(SEMICOLON)X(COMMA)X(ASSIGN_OP)X(PLUS_OP)X(MINUS_OP)X(MULT_OP)
	X(DIV_OP)X(LT_OP)X(LE_OP)X(GT_OP)X(GE_OP)X(EQ_OP1)X(EQ_OP2)X(NE_OP)X(ID)X(INT_LIT)X(FLOAT_LIT)X(CHEESE_LIT)
};
#undef X
std::string getTokenText(int token) {
	int size = (sizeof(Tokens) / sizeof(*Tokens));
	for (int i = 0; i < size; i++) {
		if (token == Tokens[i].id)
			return Tokens[i].pname;
	}
	return "";
}

#pragma endregion

extern CodeGen code;
extern Scanner scan;

Parser::Parser()
{
	tokenAvailable = false;
}

void Parser::SyntaxError(Token t, string msg)
{
	cout << "Syntax Error: " + msg << endl;
	exit(1); // abort on any syntax error
}

Token Parser::NextToken()
{
	if (!tokenAvailable)
	{
		savedToken = scan.GetNextToken();
		tokenAvailable = true;
	}
	return savedToken;
}

void Parser::Match(Token t)
{
	if (t != NextToken())
		SyntaxError(t, "");
	else
		tokenAvailable = false;
}


void Parser::InitTail()
{
	switch (NextToken())
	{
	case COMMA:{
		Match(COMMA);
		ExprRec expr;
		Expression(expr);
		InitTail();
		break;
	}
	case RMUSTACHE:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecTail(ExprRec& expr)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Match(ID);
		code.DefineVar(expr);
		VarDecTail(expr);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecList(ExprRec& expr)
{
	Match(ID);
	code.DefineVar(expr);
	VarDecTail(expr);
}

void Parser::DecTail()
{
	switch (NextToken())
	{
	case BOOL_SYM:
	case CHEESE_SYM:
	case FLOAT_SYM:
	case HIPHIP_SYM:
	case INT_SYM:
		Declaration();
		DecTail();
		break;
	case RMUSTACHE:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Declaration()
{
	ExprRec expr;

	switch (NextToken())
	{
	case BOOL_SYM:
	case CHEESE_SYM:
	case FLOAT_SYM:
	case INT_SYM:
		Type(expr);
		Match(COLON);
		VarDecList(expr);
		Match(SEMICOLON);
		break;
	case HIPHIP_SYM:
		Match(HIPHIP_SYM);
		Match(LSTAPLE);
		Match(INT_LIT);
		Match(RSTAPLE);
		Type(expr);
		VarDecList(expr);
		Match(SEMICOLON);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::DecList()
{
	Declaration();
	DecTail();
}

void Parser::BoolLit()
{
	switch (NextToken())
	{
	case FALSE_SYM:
		Match(FALSE_SYM);
		break;
	case TRUE_SYM:
		Match(TRUE_SYM);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::CheeseTypeTail()
{
	switch (NextToken())
	{
	case LSTAPLE:
		Match(LSTAPLE);
		Match(INT_LIT);
		Match(RSTAPLE);
		break;
	case COLON:
	case ID:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::CheeseType()
{
	Match(CHEESE_SYM);
	CheeseTypeTail();
}

void Parser::Type(ExprRec& expr)
{
	switch (NextToken())
	{
	case BOOL_SYM:
		Match(BOOL_SYM);
		break;
	case INT_SYM:
		Match(INT_SYM);
		break;
	case FLOAT_SYM:
		Match(FLOAT_SYM);
		break;
	case CHEESE_SYM:
		CheeseType();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Literal()
{
	switch (NextToken())
	{
	case FALSE_SYM:
	case TRUE_SYM:
		BoolLit();
		break;
	case INT_LIT:
		Match(INT_LIT);
		break;
	case FLOAT_LIT:
		Match(FLOAT_LIT);
		break;
	case CHEESE_LIT:
		Match(CHEESE_LIT);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::MultOp()
{
	switch (NextToken())
	{
	case MULT_OP:
		Match(MULT_OP);
		break;
	case DIV_OP:
		Match(DIV_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::FactorTail(ExprRec& expr)
{
	ExprRec leftOp, rightOp;
	OpRec op;

	switch (NextToken())
	{
	case MULT_OP:
	case DIV_OP:
		leftOp.kind = expr.kind;
		leftOp.type = expr.type;
		leftOp.name = expr.name;
		leftOp.val = expr.val;
		leftOp.fval = expr.fval;

		MultOp();
		code.ProcessOp(op); 
		Primary(rightOp);
		code.GenInfix(leftOp, op, rightOp, expr);
		FactorTail(expr);

		break;
	case RSTAPLE:
	case RBANANA:
	case RMUSTACHE:
	case SEMICOLON:
	case COMMA:
	case PLUS_OP:
	case MINUS_OP:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP1:
	case EQ_OP2:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Primary(ExprRec& expr)
{
	switch (Token t = NextToken())
	{
	case FALSE_SYM:
	case TRUE_SYM:
	case INT_LIT:
	case FLOAT_LIT:
	case CHEESE_LIT:{
		Literal();

		switch (t) {
			case FALSE_SYM:
			case TRUE_SYM:
				expr.type = BOOL;
				break;
			case INT_LIT:
				expr.type = INT;
				expr.val = atoi(scan.tokenBuffer.data());
				break;
			case FLOAT_LIT:
				expr.type = FLOAT;
				expr.fval = str_to_float(scan.tokenBuffer);
				break;
			case CHEESE_LIT:
				expr.type = CHEESE;
				expr.sval = scan.stringBuffer;
				break;
		}

		code.ProcessLiteral(expr);
		break;
	}
	case ID:
		Variable(expr);
		code.ProcessVar();
		break;
	case LBANANA:
		Match(LBANANA);
		Expression(expr);
		Match(RBANANA);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::AddOp()
{
	switch (NextToken())
	{
	case PLUS_OP:
		Match(PLUS_OP);
		break;
	case MINUS_OP:
		Match(MINUS_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::ExprTail(ExprRec& expr)
{
	ExprRec leftOp, rightOp;
	OpRec op;

	switch (NextToken())
	{
	case PLUS_OP:
	case MINUS_OP:
		leftOp.kind = expr.kind;
		leftOp.type = expr.type;
		leftOp.name = expr.name;
		leftOp.val = expr.val;
		leftOp.fval = expr.fval;

		AddOp();
		code.ProcessOp(op);
		Factor(rightOp);
		code.GenInfix(leftOp, op, rightOp, expr);
		ExprTail(expr);

		break;
	case RSTAPLE:
	case RBANANA:
	case RMUSTACHE:
	case SEMICOLON:
	case COMMA:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP1:
	case EQ_OP2:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Factor(ExprRec& expr)
{
	Primary(expr);
	FactorTail(expr);
}

void Parser::RelOp()
{
	switch (NextToken())
	{
	case LT_OP:
		Match(LT_OP);
		break;
	case LE_OP:
		Match(LE_OP);
		break;
	case GT_OP:
		Match(GT_OP);
		break;
	case GE_OP:
		Match(GE_OP);
		break;
	case EQ_OP1:
		Match(EQ_OP1);
		break;
	case EQ_OP2:
		Match(EQ_OP2);
		break;
	case NE_OP:
		Match(NE_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::CondTail(OpRec& op, ExprRec& expr)
{
	switch (NextToken())
	{
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP1:
	case EQ_OP2:
	case NE_OP:
		RelOp();
		code.ProcessOp(op);
		Expression(expr);
		break;
	case RBANANA:
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::IntListTail()
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Match(INT_LIT);
		code.IntAppend();
		IntListTail();
		break;
	case COLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::IntList()
{
	Match(INT_LIT);
	code.IntAppend();
	IntListTail();
}

void Parser::CaseListTail()
{
	switch (NextToken())
	{
	case CASE_SYM:
		Case();
		CaseListTail();
		break;
	case OTHERWISE_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Case()
{
	Match(CASE_SYM);
	IntList();
	Match(COLON);
	StmtList();
	code.CaseEnd();
}

void Parser::CaseList()
{
	Case();
	CaseListTail();
}

void Parser::ForAssign()
{
	ExprRec expr;

	Variable(expr);
	code.ProcessVar();
	Match(ASSIGN_OP);
	Expression(expr);
	code.ForAssign();
}

void Parser::ElseClause()
{
	switch (NextToken())
	{
	case ELSE_SYM:
		Match(ELSE_SYM);
		code.IfElse();
		StmtList();
		break;
	case END_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Condition(ExprRec& expr)
{
	ExprRec leftOp, rightOp;
	OpRec op;

	Expression(leftOp);
	CondTail(op, rightOp);
	code.SetCondition(leftOp, op, rightOp, expr);
}

void Parser::VarDecs()
{
	Match(DECS_SYM);
	Match(LMUSTACHE);
	DecList();
	Match(RMUSTACHE);
}

void Parser::SelectStmt()
{
	ExprRec expr;

	Match(SELECT_SYM);
	Match(LBANANA);
	Expression(expr);
	Match(RBANANA);
	code.SelectBegin();
	CaseList();
	Match(OTHERWISE_SYM);
	code.Otherwise();
	Match(COLON);
	StmtList();
	code.CaseEnd();
	Match(END_SYM);
	code.SelectEnd();
}

void Parser::ForStmt()
{
	ExprRec expr;

	Match(FOR_SYM);
	Match(LBANANA);
	ForAssign();
	Match(SEMICOLON);
	Condition(expr);
	code.ForBegin();
	Match(SEMICOLON);
	ForAssign();
	code.ForUpdate();
	Match(RBANANA);
	StmtList();
	Match(END_SYM);
	code.ForEnd();
}

void Parser::WhileStmt()
{
	ExprRec expr;

	Match(WHILE_SYM);
	Match(LBANANA);
	Condition(expr);
	Match(RBANANA);
	code.WhileBegin();
	StmtList();
	Match(END_SYM);
	code.WhileEnd();
}

void Parser::LoopStmt()
{
	ExprRec expr;

	Match(DO_SYM);
	code.LoopBegin();
	StmtList();
	Match(UNTIL_SYM);
	Match(LBANANA);
	Condition(expr);
	Match(RBANANA);
	code.LoopEnd();
	Match(SEMICOLON);
}

void Parser::IfStmt()
{
	ExprRec expr;

	Match(IF_SYM);
	Match(LBANANA);
	Condition(expr);
	Match(RBANANA);
	code.IfThen();
	StmtList();
	ElseClause();
	Match(END_SYM);
	code.IfEnd();
}

void Parser::ItemListTail(ExprRec& expr)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Expression(expr);
		code.Shout(expr);
		ItemListTail(expr);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::ItemList()//ExprRec& expr) 
{
	ExprRec expr;

	Expression(expr);
	code.Shout(expr);
	ItemListTail(expr);
}

void Parser::VariableTail()
{
	ExprRec expr;

	switch (NextToken())
	{
	case LSTAPLE:
		Match(LSTAPLE);
		Expression(expr);
		Match(RSTAPLE);
		break;
	case RSTAPLE:
	case RBANANA:
	case RMUSTACHE:
	case SEMICOLON:
	case COMMA:
	case ASSIGN_OP:
	case PLUS_OP:
	case MINUS_OP:
	case MULT_OP:
	case DIV_OP:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP1:
	case EQ_OP2:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarListTail(ExprRec& expr)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Variable(expr);
		code.ProcessVar();
		code.Listen();
		VarListTail(expr);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarList()
{
	ExprRec expr;

	Variable(expr);
	code.ProcessVar();
	code.Listen();
	VarListTail(expr);
}

void Parser::InitList()
{
	ExprRec expr;

	Expression(expr);
	InitTail();
}

void Parser::Expression(ExprRec& expr)// ExprRec& expr)
{
	Factor(expr);
	ExprTail(expr);
}

void Parser::AssignTail(ExprRec& expr)
{
	switch (NextToken())
	{
	case FALSE_SYM:
	case TRUE_SYM:
	case LBANANA:
	case ID:
	case INT_LIT:
	case FLOAT_LIT:
	case CHEESE_LIT:
		Expression(expr);
		break;
	case LMUSTACHE:
		Match(LMUSTACHE);
		InitList();
		Match(RMUSTACHE);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Variable(ExprRec& expr)
{
	Match(ID);
	VariableTail();
}

void Parser::BreakStmt()
{
	Match(BREAK_SYM);
	code.Break();
	Match(SEMICOLON);
}

void Parser::ShoutStmt(ExprRec& expr)
{
	Match(SHOUT_SYM);
	ItemList(/*expr*/);
	code.NewLine();
	Match(SEMICOLON);
}

void Parser::ListenStmt()
{
	Match(LISTEN_SYM);
	VarList();
	Match(SEMICOLON);
}

void Parser::AssignStmt()
{
	ExprRec expr, expr2;

	Variable(expr);
	code.ProcessVar();
	Match(ASSIGN_OP);
	AssignTail(expr2);
	code.Assign(expr, expr2);
	Match(SEMICOLON);
}

void Parser::StructStmt()
{
	switch (NextToken())
	{
	case IF_SYM:
		IfStmt();
		break;
	case DO_SYM:
		LoopStmt();
		break;
	case WHILE_SYM:
		WhileStmt();
		break;
	case FOR_SYM:
		ForStmt();
		break;
	case SELECT_SYM:
		SelectStmt();
		break;
	case DECS_SYM:
		VarDecs();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::SimpleStmt(ExprRec& expr)
{
	switch (NextToken())
	{
	case ID:
		AssignStmt();
		break;
	case LISTEN_SYM:
		ListenStmt();
		break;
	case SHOUT_SYM:
		ShoutStmt(expr);
		break;
	case BREAK_SYM:
		BreakStmt();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::StmtTail()
{
	switch (NextToken())
	{
	case BREAK_SYM:
	case DECS_SYM:
	case DO_SYM:
	case FOR_SYM:
	case IF_SYM:
	case LISTEN_SYM:
	case SELECT_SYM:
	case SHOUT_SYM:
	case WHILE_SYM:
	case ID:
		Statement();
		StmtTail();
		break;
	case EOF_SYM:
	case CASE_SYM:
	case ELSE_SYM:
	case END_SYM:
	case OTHERWISE_SYM:
	case UNTIL_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Statement() {
	switch (NextToken()) {
		case BREAK_SYM:
		case LISTEN_SYM:
		case SHOUT_SYM:
		case ID:{
			ExprRec expr;
			SimpleStmt(expr);
			break;
		}
		case DECS_SYM:
		case DO_SYM:
		case FOR_SYM:
		case IF_SYM:
		case SELECT_SYM:
		case WHILE_SYM:
			StructStmt();
			break;
		default:
			SyntaxError(NextToken(), "");
	}
}

void Parser::StmtList()
{
	Statement();
	StmtTail();
}

void Parser::Program()
{
	code.Start();
	StmtList();
	code.Finish();
}

void Parser::SystemGoal() {
#ifdef PRINT_TOKENS
	cout << '\n';
	int a;
	while ((a = NextToken()) != EOF_SYM){
		tokenAvailable = false;
		scan.tokenBuffer;
		cout << getTokenText(a) << " -> " << scan.tokenBuffer << '\n';
	}
	cin.get();
#else

	Program();
	Match(EOF_SYM);
#endif

}
