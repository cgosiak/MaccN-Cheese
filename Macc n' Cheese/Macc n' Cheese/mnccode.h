#ifndef CODEGEN
#define CODEGEN

#include <string>
#include <vector>
using namespace std;

#include "mncscan.h"

enum OpKind { PLUS, MINUS, MULT, DIVN };

struct OpRec // information about an operator
{
	OpKind op;
};

enum ExprKind { ID_EXPR, LITERAL_EXPR, TEMP_EXPR };

enum VarKind { INT, FLOAT, CHEESE, BOOL };

struct ExprRec // information about a constant, variable, or
	// an intermediate (temporary) result
{
	ExprKind kind;   // operand type
	VarKind	 type;	 // variable type
	string   name;   // used when kind is ID_EXPR or TEMP_EXPR
	int      val;    // used when type is LITERAL_EXPR
	string	 sval;	 // used when type is CHEESE
	float	 fval;   // used when type is FLOAT
};

class CodeGen {
	public:

	CodeGen();
	// Initializes the code generator;

	/* _____________________________________________________________________________
	*/

	void Start();
	// Initializes the compiler.

	void Finish();
	// Generates code to finish the program.

	void Assign(const ExprRec & target, const ExprRec & source);
	// Produces the assembly code for an assignment from Source to Target.

	void Listen();

	void Break();

	void NewLine();
	// Produces the assembly code for starting a new output line.

	void Shout(ExprRec& e);

	void IfThen();

	void IfElse();

	void IfEnd();

	void LoopBegin();

	void LoopEnd();

	void WhileBegin();

	void WhileEnd();


	void GenInfix(const ExprRec & e1, const OpRec & op,
		const ExprRec & e2, ExprRec& e);
	// Produces the assembly code for an infix operation.

	void DefineVar(ExprRec& e);

	void ProcessId(ExprRec& e);
	// Declares the identifier in the token buffer and builds a
	// corresponding semantic record e.

	void ProcessLiteral(ExprRec& e);
	// Converts the literal found in the token buffer into numeric form
	// and builds a corresponding semantic record e.

	void ProcessOp(OpRec& o);
	// Produces an operator descriptor O for the operator in the token
	// buffer.

	void ReadId(const ExprRec & InVar);
	// Produces the assembly code for reading a value for InVar.



	void WriteExpr(const ExprRec & OutExpr);
	// Produces the assembly code for writing the value of OutExpr.

	void WriteString();










	void ProcessVar();

	void IntAppend();

	void CaseEnd();

	void ForAssign();

	void SetCondition(const ExprRec& e1, const OpRec& op, const ExprRec& e2, ExprRec& e);

	void SelectBegin();

	void Otherwise();

	void SelectEnd();

	void ForBegin();

	void ForUpdate();
	
	void ForEnd();







	/* _____________________________________________________________________________
	*/

	private:

	vector<string> symbolTable;

	int  maxTemp;     // max temporary allocated so far; initially 0

	void CheckId(const string & s);
	// Declares s as a new variable and enters it into the symbol table when s
	// is not already in the symbol table.

	void Enter(const string & s);
	// Enters s unconditionally into the symbol table.

	void ExtractExpr(const ExprRec & e, string& s);
	// Returns an operand representation s for the expression e.

	string ExtractOp(const OpRec& o);
	// Returns a representation for the operator o.

	void Generate(const string & s1, const string & s2, const string & s3);
	// Produces the SAM assembly code for one or two operand instructions. 
	// s1 is the opcode; s2 and s3 are operands.

	string GetTemp();
	// Creates a temporary variable and returns its name.

	void IntToAlpha(int val, string& str);
	// Makes a string representation for a positive integer val.

	bool LookUp(const string &s);
	// Returns true if s is in the symbol table; otherwise,
	// false is returned.
};

#endif