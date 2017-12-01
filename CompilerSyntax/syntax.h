#pragma once
// lexer.h
// This header file includes the Syntax Analyzer part of the program, as coded in Assignment 2.
// Tyler Hatzenbuhler
// Anette Ulrichsen
#include"assembly.h"

// These compiler directives handle extremely repetitive code and allow easier reading
#define ARGS vector<Token> &v, int &iterator, int &linecount, bool &endfile
#define ARGSD vector<Token> &, int &, int &, bool &
#define ARGS_CALL v, iterator, linecount, endfile
#define ENDLINE_CHECK if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; if(endfile) return;}
#define ENDFILE_CHECK if ((iterator + 1) == v.size()){endfile = true; return;}
#define PRINTTOKEN cout << endl; v[iterator].print(); cout << endl;

// The parser begins at the top function and is best understood reading from the top down.
// Each function needs token checking, iterator management, printing current token and path directions, and error checking.

bool syntax(vector<Token> &v);
void rat17f(ARGSD);
void OptFunctionDefinitions(ARGSD);
void FunctionDefinitions(ARGSD);
void Function(ARGSD);
void OptParameterList(ARGSD);
void ParameterList(ARGSD);
void Parameter(ARGSD);
void Qualifier(ARGSD);
void Body(ARGSD);
void OptDeclarationList(ARGSD);
void DeclarationList(ARGSD);
void Declaration(ARGSD);
void IDs(ARGSD);
void dIDs(ARGSD);
void StatementList(ARGSD);
void Statement(ARGSD);
void Compound(ARGSD);
void Assign(ARGSD);
void If(ARGSD);
void Return(ARGSD);
void Write(ARGSD);
void Read(ARGSD);
void While(ARGSD);
void Condition(ARGSD);
void Relop(ARGSD);
void Expression(ARGSD);
void ExpressionPrime(ARGSD);
void Term(ARGSD);
void TermPrime(ARGSD);
void Factor(ARGSD);
void Primary(ARGSD);

bool syntax(vector<Token> &v) {
	int iterator = 0;
	int linecount = 1;
	bool endfile = false;

	rat17f(ARGS_CALL);

	return true; // Essentially, if the parse reaches this line there were no errors.
}

void rat17f(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK

	if (v[iterator].lexeme == "@")
	{
		PRINTTOKEN
		OptFunctionDefinitions(ARGS_CALL);
	}

	if (v[iterator].lexeme == "%%") {
		PRINTTOKEN
		iterator++;
		ENDLINE_CHECK
		OptDeclarationList(ARGS_CALL);
		StatementList(ARGS_CALL);
	}
	else { cout << "Error on line " << linecount << ", program needs %% to run and it is missing."; exit(1); }
}

void OptFunctionDefinitions(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Opt Function Definitions> ";

	FunctionDefinitions(ARGS_CALL);
}

void FunctionDefinitions(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Function Definitions> ";

	if (v[iterator].lexeme == "@") {
		iterator++;
		Function(ARGS_CALL);
		FunctionDefinitions(ARGS_CALL);
	}
}

void Function(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Function> ";
	
	if (v[iterator].tokentype == "Identifier") { PRINTTOKEN iterator++; }
	else cout << "Error on line " << linecount << ", expected identifier" << endl;
	if (v[iterator].lexeme == "(") { PRINTTOKEN iterator++; }
	else cout << "Error on line " << linecount << ", expected (" << endl;
	OptParameterList(ARGS_CALL);
	if (v[iterator].lexeme == ")") { PRINTTOKEN iterator++; }
	else cout << "Error on line " << linecount << ", expected )" << endl;
	ENDLINE_CHECK
	OptDeclarationList(ARGS_CALL);
	Body(ARGS_CALL);
}

void OptParameterList(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Opt Parameter List> ";

	if (v[iterator].lexeme != ")")
		ParameterList(ARGS_CALL);
}

void ParameterList(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Parameter List> ";

	if (v[iterator].lexeme != ")")
	{
		Parameter(ARGS_CALL);
		if (v[iterator].lexeme == ",") { PRINTTOKEN iterator++; }
		ParameterList(ARGS_CALL);
	}
}

void Parameter(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Parameter> ";

	IDs(ARGS_CALL);
	if (v[iterator].lexeme == ":") { PRINTTOKEN iterator++; }
	Qualifier(ARGS_CALL);
}

void Qualifier(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Qualifier> ";

	if (v[iterator].tokentype == "Qualifier")
	{
		PRINTTOKEN iterator++;
	}
}

void Body(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Body> ";

	if (v[iterator].lexeme == "{") { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
	StatementList(ARGS_CALL);
	if (v[iterator].lexeme == "}") { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void OptDeclarationList(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Opt Declaration List> ";

	if (v[iterator].tokentype != "Qualifier") return;
	else
	{
		DeclarationList(ARGS_CALL);
	}
}

void DeclarationList(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Declaration List> ";

	if (v[iterator].lexeme != "{")
	{
		Declaration(ARGS_CALL);
		if (v[iterator].lexeme == ";") { PRINTTOKEN iterator++; }
		ENDLINE_CHECK
		if (v[iterator].lexeme != "Qualifier") return;
		DeclarationList(ARGS_CALL);
	}
}

void Declaration(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Declaration> ";
	
	Qualifier(ARGS_CALL);
	dIDs(ARGS_CALL);
}

void dIDs(ARGS) {
	ENDLINE_CHECK
		ENDFILE_CHECK
		cout << " <IDs> ";

	if (v[iterator].tokentype == "Identifier") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ",")
	{
		PRINTTOKEN
			iterator++;
		IDs(ARGS_CALL);
	}
}

void IDs(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <IDs> ";

	if (v[iterator].tokentype == "Identifier") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ",")
	{
		PRINTTOKEN 
		iterator++;
		IDs(ARGS_CALL);
	}
}

void StatementList(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Statement List> ";

	if (v[iterator].lexeme != "}") {
		Statement(ARGS_CALL);
		StatementList(ARGS_CALL);
	}
}

void Statement(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Statement> ";

	if (v[iterator].lexeme == "{")
		Compound(ARGS_CALL);
	
	else if (v[iterator].tokentype == "Identifier")
		Assign(ARGS_CALL);

	else if (v[iterator].lexeme == "if")
		If(ARGS_CALL);

	else if (v[iterator].lexeme == "return")	
		Return(ARGS_CALL);

	else if (v[iterator].lexeme == "write")
		Write(ARGS_CALL);

	else if (v[iterator].lexeme == "read")	
		Read(ARGS_CALL);

	else if (v[iterator].lexeme == "while")	
		While(ARGS_CALL);
	else { cout << "Error on line " << linecount << ", statement error" << endl; exit(1); }
}

void Compound(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Compound> ";

	if (v[iterator].lexeme == "{") { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
	StatementList(ARGS_CALL);
	if (v[iterator].lexeme == "}") { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void Assign(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Assign> ";

	if (v[iterator].tokentype == "Identifier") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ":=") { PRINTTOKEN iterator++; }
	Expression(ARGS_CALL);
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK;
}

void If(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <If> ";

	if (v[iterator].lexeme == "if") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == "(") { PRINTTOKEN iterator++; }
	Condition(ARGS_CALL);
	if (v[iterator].lexeme == ")") { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
	Statement(ARGS_CALL);
	if (v[iterator].lexeme == "fi") { PRINTTOKEN iterator++; }
	else if (v[iterator].lexeme == "else")
	{
		PRINTTOKEN 
		iterator++;
		ENDLINE_CHECK
		Statement(ARGS_CALL);
		if (v[iterator].lexeme == "fi") { PRINTTOKEN iterator++; }
		if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
		ENDLINE_CHECK
	}
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void Return(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Return> ";
	
	if (v[iterator].lexeme == "return") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
	else
	{
		Expression(ARGS_CALL);
		if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
		ENDLINE_CHECK
	}
}

void Write(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Write> ";

	if (v[iterator].lexeme == "write") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == "(") { PRINTTOKEN iterator++; } 
	Expression(ARGS_CALL);
	if (v[iterator].lexeme == ")") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void Read(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Read> ";

	if (v[iterator].lexeme == "read") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == "(") { PRINTTOKEN iterator++; }
	IDs(ARGS_CALL);
	if (v[iterator].lexeme == ")") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void While(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <While> ";

	if (v[iterator].lexeme == "while") { PRINTTOKEN iterator++; }
	if (v[iterator].lexeme == "(") { PRINTTOKEN iterator++; }
	Condition(ARGS_CALL);
	if (v[iterator].lexeme == ")") { PRINTTOKEN iterator++; }
	Statement(ARGS_CALL);
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) { PRINTTOKEN iterator++; }
	ENDLINE_CHECK
}

void Condition(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Condition> ";

	Expression(ARGS_CALL);
	Relop(ARGS_CALL);
	Expression(ARGS_CALL);
}

void Relop(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Relop> ";

	if (v[iterator].lexeme == "=" | v[iterator].lexeme == "/=" || v[iterator].lexeme == ">" || v[iterator].lexeme == "<" || v[iterator].lexeme == "=>" || v[iterator].lexeme == "<=")
	{
		PRINTTOKEN
		iterator++;
		return;
	}
	else { cout << "Error on line "<< linecount << ", expected relational operator" << endl; exit(1); }
}

void Expression(ARGS) { // LEFT RECURSION, attemped removal
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Expression> ";

	Term(ARGS_CALL);
	ExpressionPrime(ARGS_CALL);
}

void ExpressionPrime(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Expression Prime> ";

	
	if (v[iterator].lexeme == "+" || v[iterator].lexeme == "-")
	{
		PRINTTOKEN
		iterator++;
		Term(ARGS_CALL);
		ExpressionPrime(ARGS_CALL);
	}
}

void Term(ARGS) { // LEFT RECURSION, attempted removal
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Term> ";

	Factor(ARGS_CALL);
	TermPrime(ARGS_CALL);
}

void TermPrime(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Term Prime> ";

	if (v[iterator].lexeme == "*" || v[iterator].lexeme == "/")
	{
		PRINTTOKEN
		iterator++;
		Factor(ARGS_CALL);
		TermPrime(ARGS_CALL);
	}
	else if (v[iterator].lexeme == "(")
		Expression(ARGS_CALL);
}

void Factor(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Factor> ";

	if (v[iterator].lexeme == "-") { PRINTTOKEN iterator++; }
	Primary(ARGS_CALL);
}

void Primary(ARGS) {
	ENDLINE_CHECK
	ENDFILE_CHECK
	cout << " <Primary> ";

	if (v[iterator].lexeme == "{")
		Compound(ARGS_CALL);
	if (v[iterator].tokentype == "Integer" || v[iterator].tokentype == "Real")
	{
		PRINTTOKEN
		iterator++;
		return;
	}
	if (v[iterator].lexeme == "true" || v[iterator].lexeme == "false")
	{
		PRINTTOKEN
		iterator++;
		return;
	}
	if (v[iterator].lexeme == "(")
	{
		PRINTTOKEN
		iterator++;
		Expression(ARGS_CALL);
		if (v[iterator].lexeme == ")")
		{
			PRINTTOKEN
			iterator++;
			return;
		}
		else
		{
			cout << "Error on line " << linecount << ", expected closing )" << endl;
			exit(1);
		}
	}
	if (v[iterator].tokentype == "Identifier" && v[iterator + 1].lexeme == "[") {
		PRINTTOKEN iterator++;
		PRINTTOKEN iterator++;
		IDs(ARGS_CALL);
		if (v[iterator].lexeme == "]")
		{
			PRINTTOKEN
			iterator++;
			return;
		}
		else
		{
			cout << "Error on line " << linecount << ", expected closing ]" << endl;
			exit(1);
		}
	}
	 if (v[iterator].tokentype == "Identifier")
	{
		IDs(ARGS_CALL);
		return;
	}
	cout << endl << "Error on line " << linecount << ", expected primary" << endl;
	exit(1);
}