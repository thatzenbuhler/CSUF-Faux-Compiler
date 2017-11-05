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
void Identifier(vector<Token> &, int &, int &);
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
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	if (v[iterator].lexeme == "@")
		OptFunctionDefinitions(v, iterator, linecount);

	if (v[iterator].lexeme == "%%")
	{
		if (v[iterator + 1].lexeme != "Endline")
		{
			cout << "Error on line " << linecount << endl
				<< "Can not have text on same line as \"%%\"";
			return; /////meant to break out of syntax analyzer
		}

		if (v[iterator + 2].tokentype == "Qualifier")
			OptDeclarationList(v, iterator, linecount);

	}
		//if (v[iterator + 2].lexeme == "{" | v[iterator + 2].tokentype == "Keyword")
		StatementList(v, iterator, linecount);
	
}

void OptFunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Opt Function Definitions> ";
	++iterator;

	if (v[iterator].tokentype == "Identifier")
		FunctionDefinitions(v, iterator, linecount);

	// if token not function definition, return
	else
	{
		cout << "Error on line " << linecount << endl
			<< "Expected an identifier after @";
		return; //break out of syntax analyzer
	}
}

void FunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Function Definitions> ";
	++iterator;

	// If next isn't function, return
	if (v[iterator].lexeme == "(")
		Function(v, iterator, linecount);

	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a ( after identifier";
		return; ///break out
	}
	//FunctionDefinitions(v, iterator, linecount);
}

void Function(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Function> ";
	++iterator;

	if (v[iterator].tokentype == "Identifier")
		OptParameterList(v, iterator, linecount);

	if (v[iterator].lexeme == ")")
	{
		if ((v[iterator + 1].lexeme == "Endline" && v[iterator + 2].lexeme == "{") |
			(v[iterator + 2].lexeme == "Endline" && v[iterator + 1].lexeme == "{"))
			iterator += 2;
		Body(v, iterator, linecount);

		if (v[iterator + 2].tokentype == "Qualifier")
			OptDeclarationList(v, iterator, linecount);
	}

	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected identifier or ) after (";
		return; ///break out
	}

}

void OptParameterList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Opt Parameter List> ";
	++iterator;

	if (v[iterator + 1].lexeme != ":")
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a : after " << v[iterator].lexeme;
		return; ///break out
	}
	else
		ParameterList(v, iterator, linecount);
}

void ParameterList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Parameter List> ";
	iterator += 2;

	if (v[iterator].tokentype == "Qualifier")
	{
		if (v[iterator + 1].lexeme == ")")
		{
			Parameter(v, iterator, linecount);
			iterator++;
			Function(v, iterator, linecount);
		}

		if ((v[iterator + 1].lexeme == ",") && (v[iterator + 2].tokentype == "Identifier")
			&& (v[iterator + 3].lexeme == ":"))
		{
			Parameter(v, iterator, linecount);
			iterator += 2;
			ParameterList(v, iterator, linecount);
		}

	}

	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a qualifier after :";
		return; //break out

	}

}

//may have made this function unneccessary when i defined parameter list??
void Parameter(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Parameter> ";

	cout << "<IDs> : <Qualifier>\n";
	cout << v[iterator - 3].lexeme << " : " << v[iterator - 1].lexeme << endl;

	//IDs(v, iterator, linecount);
	// :
	//Qualifier(v, iterator, linecount);
}

//needs work
void Qualifier(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Qualifier> ";
}

void Body(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Body> ";

	StatementList(v, iterator, linecount);

	if (v[iterator].lexeme == "}")
		rat17f(v, iterator, linecount);
}

void OptDeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Opt Declaration List> ";

	if (v[iterator].tokentype == "Qualifier")
		DeclarationList(v, iterator, linecount);
	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected qualifier at beginning of list";
		return; ///break out
	}
}

void DeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Declaration List> ";

	if (v[iterator + 1].tokentype == "Identifier" && v[iterator + 2].lexeme == ";" &&
		v[iterator + 3].tokentype != "Qualifier")
		Declaration(v, iterator, linecount);
	else if (v[iterator + 1].tokentype == "Identifier" && v[iterator + 2].lexeme == ";" &&
		v[iterator + 3].tokentype == "Qualifier")
	{
		iterator += 2;
		DeclarationList(v, iterator, linecount);
	}
	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a qualifier and identifier";
		return; //break out
	}
}

void Declaration(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Qualifier(v, iterator, linecount);
	++iterator;
	IDs(v, iterator, linecount);
	++iterator;
	
	if (v[iterator].lexeme == "Endline")
		++iterator;

	if (v[iterator].lexeme == "{")
	{
		++iterator;
		Body(v, iterator, linecount);
	}
	else
	{
		++iterator;
		rat17f(v, iterator, linecount);
	}
}

void IDs(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//if no more IDs, return;
	Identifier(v, iterator, linecount);
	IDs(v, iterator, linecount);
}

void Identifier(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//check if token is identifier
}

void StatementList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if no more Statements, return
	Statement(v, iterator, linecount);
	StatementList(v, iterator, linecount);
}

void Statement(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// For this function, checking the token should point us to which of these functions to call. 
	Compound(v, iterator, linecount);
	// or
	Assign(v, iterator, linecount);
	// or
	If(v, iterator, linecount);
	// or
	Return(v, iterator, linecount);
	// or
	Write(v, iterator, linecount);
	// or
	Read(v, iterator, linecount);
	// or
	While(v, iterator, linecount);

}

void Compound(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// {
	StatementList(v, iterator, linecount);
	// }
}

void Assign(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// identifier
	// :=
	Expression(v, iterator, linecount);
}

void If(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if
	// (
	Condition(v, iterator, linecount);
	// )
	Statement(v, iterator, linecount);
	// if "fi", finish, if "else", continue
	Statement(v, iterator, linecount);
	// fi

}

void Return(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: return
	// ;

	// OR

	// return
	Expression(v, iterator, linecount);
	// ;
}

void Write(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: write
	// (
	Expression(v, iterator, linecount);
	// )
}

void Read(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: read
	// (
	IDs(v, iterator, linecount);
	// )
	// ;
}

void While(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: while
	// (
	Condition(v, iterator, linecount);
	// )
	Statement(v, iterator, linecount);
}

void Condition(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Expression(v, iterator, linecount);
	Relop(v, iterator, linecount);
	Expression(v, iterator, linecount);
}

void Relop(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// check if token is =, /=, >, <, =>, <=
}

void Expression(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attemped removal
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Term(v, iterator, linecount);
	// If next token is expression, then
	ExpressionPrime(v, iterator, linecount);
}

void ExpressionPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// If not + or -, return
	// + or -
	Term(v, iterator, linecount);
	ExpressionPrime(v, iterator, linecount);
}

void Term(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attempted removal
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Factor(v, iterator, linecount);
	// if next token is term, then
	TermPrime(v, iterator, linecount);
}

void TermPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if not * or /, return
	// * or /
	Factor(v, iterator, linecount);
	TermPrime(v, iterator, linecount);
}

void Factor(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// -
	Primary(v, iterator, linecount);
	// OR
	Primary(v, iterator, linecount);
}

void Primary(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// For this function, checking the token should point us to which function to call
	Identifier(v, iterator, linecount);
	// or
	// token: integer
	// or
	Identifier(v, iterator, linecount);
	// [
	IDs(v, iterator, linecount);
	// ]
	// or
	// (
	Expression(v, iterator, linecount);
	// )
	// or
	// token: real
	// or
	// keyword: true or keyword: false
}