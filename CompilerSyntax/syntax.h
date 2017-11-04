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
#include"lexer.h"

// The parser begins at the bottom function and is best understood reading from the bottom up.
// Each function needs token checking, iterator management, printing current token and path directions, and error checking.


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

void Factor(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// -
	Primary(v, iterator, linecount);
	// OR
	Primary(v, iterator, linecount);
}

void TermPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if not * or /, return
	// * or /
	Factor(v, iterator, linecount);
	TermPrime(v, iterator, linecount);
}

void Term(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attempted removal
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Factor(v, iterator, linecount);
	// if next token is term, then
	TermPrime(v, iterator, linecount);
}

void ExpressionPrime(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// If not + or -, return
	// + or -
	Term(v, iterator, linecount);
	ExpressionPrime(v, iterator, linecount);
}

void Expression(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attemped removal
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Term(v, iterator, linecount);
	// If next token is expression, then
	ExpressionPrime(v, iterator, linecount);
}

void Relop(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// check if token is =, /=, >, <, =>, <=
}

void Condition(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Expression(v, iterator, linecount);
	Relop(v, iterator, linecount);
	Expression(v, iterator, linecount);
}

void While(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: while
	// (
	Condition(v, iterator, linecount);
	// )
	Statement(v, iterator, linecount);
}

void Read(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: read
	// (
	IDs(v, iterator, linecount);
	// )
	// ;
}

void Write(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// keyword: write
	// (
	Expression(v, iterator, linecount);
	// )
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

void Assign(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// identifier
	// :=
	Expression(v, iterator, linecount);
}

void Compound(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// {
	StatementList(v, iterator, linecount);
	// }
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

void StatementList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if no more Statements, return
	Statement(v, iterator, linecount);
	StatementList(v, iterator, linecount);
}

void Identifier(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//check if token is identifier
}

void IDs(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//if no more IDs, return;
	Identifier(v, iterator, linecount);
	IDs(v, iterator, linecount);
}

void Declaration(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Qualifier(v, iterator, linecount);
	IDs(v, iterator, linecount);
}

void DeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//If finished declaration list, return
	Declaration(v, iterator, linecount);
	DeclarationList(v, iterator, linecount);
}

void OptDeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//If empty, return
	DeclarationList(v, iterator, linecount);
}

void Body(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//{
	StatementList(v, iterator, linecount);
	//}
}

void Qualifier(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// check if token == integer, boolean, or floating
}

void Parameter(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	IDs(v, iterator, linecount);
	// :
	Qualifier(v, iterator, linecount);
}

void ParameterList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// If not parameter, return;
	Parameter(v, iterator, linecount);
	ParameterList(v, iterator, linecount);
}

void OptParameterList(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//If empty, return
	ParameterList(v, iterator, linecount);
}

void Function(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	//@
	// identifier
	// (
	OptParameterList(v, iterator, linecount);
	// )
	OptDeclarationList(v, iterator, linecount);
	Body(v, iterator, linecount);
}

void FunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// If next isn't function, return
	Function(v, iterator, linecount);
	FunctionDefinitions(v, iterator, linecount);
}

void OptFunctionDefinitions(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	// if token not function definition, return
	FunctionDefinitions(v, iterator, linecount);
}

void rat17f(vector<Token> &v, int &iterator, int &linecount) {
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	OptFunctionDefinitions(v, iterator, linecount);
	// %%
	OptDeclarationList(v, iterator, linecount);
	StatementList(v, iterator, linecount);
}

bool syntax(vector<Token> &v) {
	int iterator = 0;
	int linecount = 0;
	rat17f(v, iterator, linecount);
	return true; // Essentially, if the parse reaches this line there were no errors.
}