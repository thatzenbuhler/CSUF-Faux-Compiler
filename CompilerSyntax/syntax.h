#pragma once
// lexer.h
// This header file includes the Syntax Analyzer part of the program, as coded in Assignment 2.
// Tyler Hatzenbuhler
// Anette Ulrichsen
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>

// The parser begins at the top function and is best understood reading from the top down.
// Each function needs token checking, iterator management, printing current token and path directions, and error checking.

bool syntax(vector<Token> &v);
void rat17f(vector<Token> &, int &, int &);
void OptFunctionDefinitions(vector<Token> &, int &, int &);
void FunctionDefinitions(vector<Token> &, int &, int &);
void Function(vector<Token> &, int &, int &);
void OptParameterList(vector<Token> &, int &, int &);
void ParameterList(vector<Token> &, int &, int &);
void Parameter(vector<Token> &, int &, int &);
void Qualifier(vector<Token> &, int &, int &);
void Body(vector<Token> &, int &, int &);
void OptDeclarationList(vector<Token> &, int &, int &);
void DeclarationList(vector<Token> &, int &, int &);
void Declaration(vector<Token> &, int &, int &);
void IDs(vector<Token> &, int &, int &);
void StatementList(vector<Token> &, int &, int &);
void Statement(vector<Token> &, int &, int &);
void Compound(vector<Token> &, int &, int &);
void Assign(vector<Token> &, int &, int &);
void If(vector<Token> &, int &, int &);
void Return(vector<Token> &, int &, int &);
void Write(vector<Token> &, int &, int &);
void Read(vector<Token> &, int &, int &);
void While(vector<Token> &, int &, int &);
void Condition(vector<Token> &, int &, int &);
void Relop(vector<Token> &v, int &, int &);
void Expression(vector<Token> &, int &, int &);
void ExpressionPrime(vector<Token> &, int &, int &);
void Term(vector<Token> &, int &, int &);
void TermPrime(vector<Token> &, int &, int &);
void Factor(vector<Token> &, int &, int &);
void Primary(vector<Token> &, int &, int &);

bool syntax(vector<Token> &v) {
	int iterator = 0;
	int linecount = 1;

	rat17f(v, iterator, linecount);

	return true; // Essentially, if the parse reaches this line there were no errors.
}

void rat17f(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}

	cout << iterator << " " << v.size() << endl;
	if (v[iterator].lexeme == "@")
	{
		v[iterator].print();
		OptFunctionDefinitions(v, iterator, linecount);
	}
		

	if (v[iterator].lexeme == "%%") {
		iterator++;
		if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
		OptDeclarationList(v, iterator, linecount);
		StatementList(v, iterator, linecount);
	}
	else { cout << "Error on line " << linecount << ", program needs %% to run and it is missing."; exit(1); }
	
}

void OptFunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Opt Function Definitions> ";
	FunctionDefinitions(v, iterator, linecount);

}

void FunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Function Definitions> ";
	if (v[iterator].lexeme == "@") {
		iterator++;
		Function(v, iterator, linecount);
		FunctionDefinitions(v, iterator, linecount);
	}
}

void Function(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Function> ";
	
	if (v[iterator].tokentype == "Identifier") iterator++;
	else cout << "Error on line " << linecount << ", expected identifier" << endl;
	if (v[iterator].lexeme == "(") iterator++;
	else cout << "Error on line " << linecount << ", expected (" << endl;
	OptParameterList(v, iterator, linecount);
	if (v[iterator].lexeme == ")") iterator++;
	else cout << "Error on line " << linecount << ", expected )" << endl;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	OptDeclarationList(v, iterator, linecount);
	Body(v, iterator, linecount);
}

void OptParameterList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Opt Parameter List> ";
	if (v[iterator].lexeme != ")")
		ParameterList(v, iterator, linecount);
	
}

void ParameterList(vector<Token> &v, int &iterator, int &linecount) {

	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Parameter List> ";
	if (v[iterator].lexeme != ")")
	{
		Parameter(v, iterator, linecount);
		if (v[iterator].lexeme == ",") iterator++;
		ParameterList(v, iterator, linecount);
	}
}

void Parameter(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Parameter> ";

	IDs(v, iterator, linecount);
	if (v[iterator].lexeme == ":") iterator++;
	Qualifier(v, iterator, linecount);
}

void Qualifier(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Qualifier> ";

	if (v[iterator].tokentype == "Qualifier")
		iterator++;
}

void Body(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Body> ";

	if (v[iterator].lexeme == "{") iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	StatementList(v, iterator, linecount);
	if (v[iterator].lexeme == "}") iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
}

void OptDeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Opt Declaration List> ";
	if (v[iterator].lexeme == "{") return;
	else
	{
		DeclarationList(v, iterator, linecount);
	}
}

void DeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Declaration List> ";
	if (v[iterator].lexeme != "{")
	{
		Declaration(v, iterator, linecount);
		if (v[iterator].lexeme == ";") iterator++;
		if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
		if (v[iterator].lexeme != "Qualifier") return;
		DeclarationList(v, iterator, linecount);
	}
}

void Declaration(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Declaration> ";
	
	Qualifier(v, iterator, linecount);
	IDs(v, iterator, linecount);
}

void IDs(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <IDs> ";

	if (v[iterator].tokentype == "Identifier" && v[iterator + 1].lexeme == ",")
	{
		cout << " <Identifier> ";
		iterator += 2;
		IDs(v, iterator, linecount);
	}

	else if (v[iterator].tokentype == "Identifier" && v[iterator + 1].lexeme != ",")
	{
		cout << " <Identifier> ";
		++iterator;
	}
}

void StatementList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Statement List> ";
	if (v[iterator].lexeme != "}") {
		Statement(v, iterator, linecount);
		StatementList(v, iterator, linecount);
	}
}

void Statement(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Statement> ";

	if (v[iterator].lexeme == "{")
		Compound(v, iterator, linecount);
	
	else if (v[iterator].tokentype == "Identifier")
		Assign(v, iterator, linecount);

	else if (v[iterator].lexeme == "if")
		If(v, iterator, linecount);

	else if (v[iterator].lexeme == "return")	
		Return(v, iterator, linecount);

	else if (v[iterator].lexeme == "write")
		Write(v, iterator, linecount);

	else if (v[iterator].lexeme == "read")	
		Read(v, iterator, linecount);

	else if (v[iterator].lexeme == "while")	
		While(v, iterator, linecount);
	else { cout << "Error on line " << linecount << ", unknown type" << endl; exit(1); }

}

void Compound(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Compound> ";

	if (v[iterator].lexeme == "{") iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	StatementList(v, iterator, linecount);
	if (v[iterator].lexeme == "}") iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
}

void Assign(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "You have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Assign> ";

	if (v[iterator].tokentype == "Identifier") iterator++;
	if (v[iterator].lexeme == ":=") iterator++;
	Expression(v, iterator, linecount);
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
}

void If(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <If> ";
	if (v[iterator].lexeme == "if") iterator++;
	if (v[iterator].lexeme == "(") iterator++;
	Condition(v, iterator, linecount);
	if (v[iterator].lexeme == ")") iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	Statement(v, iterator, linecount);
	if (v[iterator].lexeme == "fi") ++iterator;
	else if (v[iterator].lexeme == "else")
	{
		iterator++;
		if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
		Statement(v, iterator, linecount);
		if (v[iterator].lexeme == "fi") iterator++;
		if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
		if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	}
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	
	
}

void Return(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Return> ";
	
	if (v[iterator].lexeme == "return") iterator++;
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	else
	{
		Expression(v, iterator, linecount);
		if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
		if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	}
	
}

void Write(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator - 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Write> ";

	if (v[iterator].lexeme == "write") iterator++;
	if (v[iterator].lexeme == "(") iterator++;
	Expression(v, iterator, linecount);
	if (v[iterator].lexeme == ")") iterator++;
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }

}

void Read(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator - 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Read> ";

	if (v[iterator].lexeme == "read") iterator++;
	if (v[iterator].lexeme == "(") iterator++;
	IDs(v, iterator, linecount);
	if (v[iterator].lexeme == ")") iterator++;
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
}

void While(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <While> ";

	if (v[iterator].lexeme == "while") iterator++;
	if (v[iterator].lexeme == "(") iterator++;
	Condition(v, iterator, linecount);
	if (v[iterator].lexeme == ")") iterator++;
	Statement(v, iterator, linecount);
	if (v[iterator].lexeme == ";" && iterator + 1 < v.size()) iterator++;
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }

}

void Condition(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Condition> ";

	Expression(v, iterator, linecount);
	Relop(v, iterator, linecount);
	Expression(v, iterator, linecount);
}

void Relop(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Relop> ";

	if (v[iterator].lexeme == "=" | v[iterator].lexeme == "/=" || v[iterator].lexeme == ">" || v[iterator].lexeme == "<" || v[iterator].lexeme == "=>" || v[iterator].lexeme == "<=")
	{
		iterator++;
		return;
	}
	else { cout << "Error on line "<< linecount << ", expected relational operator" << endl; exit(1); }
}

void Expression(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attemped removal
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Expression> ";

	Term(v, iterator, linecount);
	ExpressionPrime(v, iterator, linecount);
}

void ExpressionPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Expression Prime> ";

	if (v[iterator].lexeme == "+" || v[iterator].lexeme == "-")
	{
		iterator++;
		Term(v, iterator, linecount);
	}
	Term(v, iterator, linecount);
}

void Term(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attempted removal
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Term> ";

	Factor(v, iterator, linecount);
	TermPrime(v, iterator, linecount);
}

void TermPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Term Prime> ";

	if (v[iterator].lexeme == "*" || v[iterator].lexeme == "/")
	{
		iterator++;
		Factor(v, iterator, linecount);
	}
}

void Factor(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Factor> ";

	if (v[iterator].lexeme == "-")
		iterator++;
	Primary(v, iterator, linecount);
	
}

void Primary(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline" && (iterator + 1) != v.size()) { ++iterator; ++linecount; }
	if ((iterator + 1) == v.size())
	{
		cout << "\nYou have reached end of file\n";
		system("pause");
		exit(0);
	}
	cout << " <Primary> ";
	if (v[iterator].lexeme == "{")
		Compound(v, iterator, linecount);
	if (v[iterator].tokentype == "Integer" || v[iterator].tokentype == "Real" || v[iterator].tokentype == "Identifier")
	{
		iterator++;
		return;
	}
	if (v[iterator].lexeme == "true" || v[iterator].lexeme == "false")
	{
		iterator++;
		return;
	}
	if (v[iterator].lexeme == "(")
	{
		iterator++;
		Expression(v, iterator, linecount);
		if (v[iterator].lexeme == ")")
		{
			iterator++;
			return;
		}
		else
		{
			cout << "Error on line " << linecount << ", expected closing )" << endl;
			exit(1);
		}
	}
	if (v[iterator].lexeme == "[") {
		iterator++;
		IDs(v, iterator, linecount);
		if (v[iterator].lexeme == "]")
		{
			iterator++;
			return;
		}
		else
		{
			cout << "Error on line " << linecount << ", expected closing ]" << endl;
			exit(1);
		}
	}
}