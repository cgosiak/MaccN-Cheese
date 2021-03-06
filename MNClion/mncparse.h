// MACC_N_CHEESE Grammar 2016
// 
// Parser Class Definition File

// SHELL GENERATED BY PARSERGEN VERSION 5.0.3

#ifndef PARSER
#define PARSER

#include <string>
using namespace std;

#include "mncscan.h" // scanner class definition

#include "mnccode.h" // code generator class definition
#include "ConditionalEntry.h"

class Parser
{
public:

	Parser();

	void SystemGoal();

    ConditionalEntry *cur_conditional;

	// A bunch of bools to keep track of conditional entries
    bool in_conditional = false;
    bool in_stmt = false;
    bool in_for_assign = false;
    bool in_condition_check = false;
	bool in_if_stmt_list = false;
	bool in_else_stmt_list = false;
	bool in_for_stmt = false;
	bool in_while = false;
	bool in_do_loop = false;

	// Just a testing fix
	string updater_lbl = "";

private:

	Token savedToken;
	bool tokenAvailable;
	bool shout_me = false;

    bool left_cond_set = false;
	std::string left_conditional = "";
	std::string right_conditional = "";
	Token comp_operator;
	DataTypes type_assigned;

	void SyntaxError(Token t, string msg);

	Token NextToken();

	void Match(Token t);

	void InitTail();

	void VarDecTail();

	void VarDecList();

	void DecTail();

	void Declaration();

	void DecList();

	void BoolLit();

	void CheeseTypeTail();

	void CheeseType();

	void Type();

	void Literal();

	void MultOp();

	void FactorTail(bool is_assign);// ExprRec& expr);

	void Primary(bool is_assign);

	void AddOp();

	void ExprTail(bool is_assign);

	void Factor(bool is_assign);// ExprRec& expr);

	void RelOp();

	void CondTail();

	void IntListTail();

	void IntList();

	void CaseListTail();

	void Case();

	void CaseList();

	void ForAssign();

	void ElseClause();

	void Condition();

	void VarDecs();

	void SelectStmt();

	void ForStmt();

	void WhileStmt();

	void LoopStmt();

	void IfStmt();

	void ItemListTail(ExprRec& expr, bool is_assign);

	void ItemList(bool is_assign);// ExprRec& expr);

	void VariableTail();

	void VarListTail();

	void VarList();

	void InitList();

	void Expression(bool is_assign);//ExprRec& expr);

	void AssignTail();

	void Variable();

	void BreakStmt();

	void ShoutStmt(const ExprRec& expr);

	void ListenStmt();

	void AssignStmt();

	void StructStmt();

	void SimpleStmt(const ExprRec& expr);

	void StmtTail();

	void Statement();

	void StmtList();

	void Program();

}; // end of Parser class

#endif
