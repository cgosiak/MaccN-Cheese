// MACC_N_CHEESE Grammar 2016
// 
// Parser Class Implementation File

// SHELL GENERATED BY PARSERGEN VERSION 5.0.3

// #define PRINT_TOKENS

#include <iostream>
#include <string>
using namespace std;

#include "mncparse.h"
#include "mnccode.h"
#include "mncscan.h"
#include "SymbolTable.h"

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

DataTypes currentType;
std::string currentVar;
std::string assign_to_var;

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
extern SymbolTable symbolTable;


Parser::Parser()
{
	tokenAvailable = false;
}

void Parser::SyntaxError(Token t, string msg)
{
	cerr << "Syntax Error: " << getTokenText(t) << endl;
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
	case COMMA:
		Match(COMMA);
		Expression(false);
		InitTail();
		break;
	case RMUSTACHE:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecTail()
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Match(ID);
		// code.DefineVar();
		symbolTable.AddEntry(scan.tokenBuffer.data(),currentType);
		VarDecTail();
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecList()
{
	Match(ID);
	symbolTable.AddEntry(scan.tokenBuffer.data(),currentType);
	// code.DefineVar();
	VarDecTail();
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
	switch (NextToken())
	{
	case BOOL_SYM:
	case CHEESE_SYM:
	case FLOAT_SYM:
	case INT_SYM:
		Type();
		Match(COLON);
		VarDecList();
		Match(SEMICOLON);
		break;
	case HIPHIP_SYM:
		Match(HIPHIP_SYM);
		Match(LSTAPLE);
		Match(INT_LIT);
		Match(RSTAPLE);
		Type();
		VarDecList();
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

void Parser::Type()
{
	switch (NextToken())
	{
	case BOOL_SYM:
		Match(BOOL_SYM);
		currentType = TYPE_BOOL_LIT;
		break;
	case INT_SYM:
		Match(INT_SYM);
		currentType = TYPE_INT_LIT;
		break;
	case FLOAT_SYM:
		Match(FLOAT_SYM);
		currentType = TYPE_FLOAT_LIT;
		break;
	case CHEESE_SYM:
		CheeseType();
		currentType = TYPE_CHEESE_LIT;
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

void Parser::FactorTail(bool is_assign)//ExprRec& expr)
{
    string old_label;
    Token t = NextToken();
	switch (t)
	{
	case MULT_OP:
	case DIV_OP:
        MultOp();
        // code.ProcessOp();
        old_label =  symbolTable.GetDataObject(currentVar).GetCurrentTempVar();
        Primary(is_assign);
        code.ProcessOperation_SymbolTable(currentVar,old_label,t);
        // code.GenInfix();
        FactorTail(is_assign);
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

void Parser::Primary(bool is_assign)
{
    if (is_assign) {
        switch (NextToken()) {
            case FALSE_SYM:
            case TRUE_SYM:
            case INT_LIT:
            case FLOAT_LIT: {
                symbolTable.UpdateEntry(currentVar, scan.tokenBuffer.data());
                Literal();
                ExprRec e;
                code.ProcessLiteral(e);
                break;
            }
            case CHEESE_LIT: {
                symbolTable.UpdateEntry(currentVar, scan.stringBuffer.data());
                Literal();
                ExprRec t;
                code.ProcessLiteral(t);
                break;
            }
            case ID:
				assign_to_var = currentVar;
                Variable();
				// Assign last accessed var with current var
				code.Assign_Var2Var(assign_to_var,currentVar);
                break;
            case LBANANA:
                Match(LBANANA);
                Expression(is_assign);
                Match(RBANANA);
                break;
            default:
                SyntaxError(NextToken(), "");
        }
    }
    else {
        Token nex_token = NextToken();
        switch (nex_token) {
            case FALSE_SYM:
            case TRUE_SYM:
            case INT_LIT:
            case FLOAT_LIT:
            case CHEESE_LIT: {
                Literal();
                code.Shout(nex_token);
                break;
            }
            case ID: {
                Variable();
                code.Shout_Variable(currentVar);
                break;
            }
            case LBANANA:
                Match(LBANANA);
                Expression(is_assign);
                Match(RBANANA);
                break;
            default:
                SyntaxError(NextToken(), "");
        }
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

void Parser::ExprTail(bool is_assign)
{
    string old_label;
    Token t = NextToken();
	switch (t)
	{
	case PLUS_OP:
	case MINUS_OP:
		AddOp();
		// code.ProcessOp();
        old_label =  symbolTable.GetDataObject(currentVar).GetCurrentTempVar();
		Factor(is_assign);
        code.ProcessOperation_SymbolTable(currentVar,old_label,t);
		// code.GenInfix();
		ExprTail(is_assign);
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

void Parser::Factor(bool is_assign)// ExprRec& expr)
{
	Primary(is_assign);
	FactorTail(is_assign);
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

void Parser::CondTail()
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
		// code.ProcessOp();
		Expression(false);
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
		// code.IntAppend();
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
	// code.IntAppend();
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
	// code.CaseEnd();
}

void Parser::CaseList()
{
	Case();
	CaseListTail();
}

void Parser::ForAssign()
{
	Variable();
	// code.ProcessVar();
	Match(ASSIGN_OP);
	Expression(false);
	// code.ForAssign();
}

void Parser::ElseClause()
{
	switch (NextToken())
	{
	case ELSE_SYM:
		Match(ELSE_SYM);
		// code.IfElse();
		StmtList();
		break;
	case END_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Condition()
{
	Expression(false);
	CondTail();
	// code.SetCondition();
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
	Match(SELECT_SYM);
	Match(LBANANA);
	Expression(false);
	Match(RBANANA);
	// code.SelectBegin();
	CaseList();
	Match(OTHERWISE_SYM);
	// code.Otherwise();
	Match(COLON);
	StmtList();
	// code.CaseEnd();
	Match(END_SYM);
	// code.SelectEnd();
}

void Parser::ForStmt()
{
	Match(FOR_SYM);
	Match(LBANANA);
	ForAssign();
	Match(SEMICOLON);
	Condition();
	// code.ForBegin();
	Match(SEMICOLON);
	ForAssign();
	// code.ForUpdate();
	Match(RBANANA);
	StmtList();
	Match(END_SYM);
	// code.ForEnd();
}

void Parser::WhileStmt()
{
	Match(WHILE_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.WhileBegin();
	StmtList();
	Match(END_SYM);
	// code.WhileEnd();
}

void Parser::LoopStmt()
{
	Match(DO_SYM);
	// code.LoopBegin();
	StmtList();
	Match(UNTIL_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.LoopEnd();
	Match(SEMICOLON);
}

void Parser::IfStmt()
{
	Match(IF_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.IfThen();
	StmtList();
	ElseClause();
	Match(END_SYM);
	// code.IfEnd();
}

void Parser::ItemListTail(ExprRec& expr, bool is_assign)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Expression(is_assign);
		ItemListTail(expr, is_assign);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::ItemList(bool is_assign)//ExprRec& expr)
{
	ExprRec expr;


	Expression(is_assign);

    cout << "ITEM LIST" << endl;
	ItemListTail(expr, is_assign);
}

void Parser::VariableTail()
{
	switch (NextToken())
	{
	case LSTAPLE:
		Match(LSTAPLE);
		Expression(false);
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

void Parser::VarListTail()
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Variable();
        code.Listen(currentVar);
		VarListTail();
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarList()
{
	Variable();
    code.Listen(currentVar);
	VarListTail();
}

void Parser::InitList()
{
	Expression(false);
	InitTail();
}

void Parser::Expression(bool is_assign)
{
	Factor(is_assign);
	ExprTail(is_assign);
}

void Parser::AssignTail()
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
		Expression(true);
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

void Parser::Variable()
{
	Match(ID);
	currentVar = scan.tokenBuffer.data();
	VariableTail();
}

void Parser::BreakStmt()
{
	Match(BREAK_SYM);
	// code.Break();
	Match(SEMICOLON);
}

void Parser::ShoutStmt(const ExprRec& expr)
{
	Match(SHOUT_SYM);
	ItemList(false);
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
	Variable(); // update current var
	Match(ASSIGN_OP);
	AssignTail();
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

void Parser::SimpleStmt(const ExprRec& expr)
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

void Parser::Statement()
{
	ExprRec expr;

	switch (NextToken())
	{
	case BREAK_SYM:
	case LISTEN_SYM:
	case SHOUT_SYM:
	case ID:
		SimpleStmt(expr);
		break;
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
