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
//void Identifier(vector<Token> &, int &, int &);
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}

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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}

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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Opt Parameter List> ";
	//++iterator;

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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Parameter List> ";
	iterator += 2;

	if (v[iterator].tokentype == "Qualifier")
	{
		if (v[iterator + 1].lexeme == ")")
		{
			Parameter(v, iterator, linecount);
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Parameter> ";

	cout << "<IDs> : <Qualifier>\n";
	cout << v[iterator - 2].lexeme << " : " << v[iterator].lexeme << endl;

	//IDs(v, iterator, linecount);
	// :
	//Qualifier(v, iterator, linecount);
}

//needs work
void Qualifier(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Qualifier> ";
	if (v[iterator].tokentype == "Qualifier")
		iterator++;
	else
	{
		cout << "Error on line " << linecount << ", expected qualifier" << endl;
		//exit(1);
		return; //break out
	}
}

void Body(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Body> ";

	if (v[iterator].lexeme == "}")
	{
		cout << " } ";
		rat17f(v, iterator, linecount);
	}

	cout << " { ";
	++iterator;
	StatementList(v, iterator, linecount);
}

void OptDeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
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

//needs work
void DeclarationList(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }

	Qualifier(v, iterator, linecount);
	++iterator;
	IDs(v, iterator, linecount);
	
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
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <IDs> ";

	if (v[iterator].tokentype == "Identifier" && v[iterator + 1].lexeme == ",")
	{
		cout << " <Identifier> ";
		iterator += 2;
		IDs(v, iterator, linecount);
	}

	if (v[iterator].tokentype == "Identifier" && v[iterator + 1].lexeme != ",")
	{
		cout << " <Identifier> ";
		++iterator;
	}
	
}

//need end of file indicator
void StatementList(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Statement List> ";
	//cout << endl << iterator << endl;

	if (v[iterator].lexeme == "{" | v[iterator].tokentype == "Identifier" | v[iterator].tokentype == "Keyword")
		Statement(v, iterator, linecount);
	else if (v[iterator].lexeme == "}")
	{
		++iterator;
		StatementList(v, iterator, linecount);
	}
	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a statement";
		return; ///break out
	}
	//StatementList(v, iterator, linecount);
}

//this may be wrong
void Statement(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Statement> ";

	if (v[iterator].lexeme == "{")
	{
		cout << " { ";
		++iterator;
		Compound(v, iterator, linecount);
	}
	
	if (v[iterator].tokentype == "Identifier")
		Assign(v, iterator, linecount);

	if (v[iterator].lexeme == "if")
	{
		++iterator;
		//seenIF = true;
		If(v, iterator, linecount);
	}

	if (v[iterator].lexeme == "else")
	{
		//++iterator;
		//Statement(v, iterator, linecount);
		//meant to return this function without finishing the other conditionals
		return;
	}

	if (v[iterator].lexeme == "fi")
		If(v, iterator, linecount);

	if (v[iterator].lexeme == "return")	
		Return(v, iterator, linecount);

	if (v[iterator].lexeme == "write")
	{
		//seenWrite = true;
		Write(v, iterator, linecount);
	}

	if (v[iterator].lexeme == "read")	
		Read(v, iterator, linecount);

	if (v[iterator].lexeme == "while")	
		While(v, iterator, linecount);

}

void Compound(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Compound> ";
	
	if (v[iterator].lexeme == "}")
	{
		cout << " } ";
		++iterator;
	}

	StatementList(v, iterator, linecount);
	
}

void Assign(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Assign> ";

	if (v[iterator + 1].lexeme != ":=")
	{
		cout << "Error on line " << linecount << endl <<
			"Expected an assignment operator";
		exit(1); //break out
	}
	
	iterator += 2;
	Expression(v, iterator, linecount);
}

// this may be wrong
void If(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <If> ";

	if (v[iterator].lexeme == "(")
	{
		++iterator;
		Condition(v, iterator, linecount);

		if (v[iterator].lexeme == ")")
		{
			++iterator;
			Statement(v, iterator, linecount);
		}
		else
		{
			cout << "Error on line " << linecount << endl <<
				"Expected a ) after condition";
			exit(1);
		}
	}

	if (v[iterator].lexeme == "fi" && v[iterator - 1].lexeme == ")")
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a statement before fi";
		exit(1);
	}
	else
	{
		++iterator;
		Statement(v, iterator, linecount);
	}

	if (v[iterator].lexeme == "else")
	{
		++iterator;
		Statement(v, iterator, linecount);
		/*cout << "Error on line " << linecount << endl <<
			"Can not have else without an if statement";
		exit(1);*/
	}
	
}

void Return(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Return> ";
	++iterator;
	//cout << endl << v[iterator + 3].lexeme << endl;
	
	if (((v[iterator].lexeme == "true") | (v[iterator].lexeme == "false"))
		&& v[iterator + 1].lexeme == ";" && v[iterator + 2].lexeme == "}")
	{
		iterator += 3;
		Body(v, iterator, linecount);
	}
	else if (((v[iterator].lexeme == "true") | (v[iterator].lexeme == "false"))
		&& v[iterator + 1].lexeme == ";" && v[iterator + 3].lexeme != "}")
	{
		cout << "Error on line " << linecount << endl <<
			"Expected } after return value";
		return; ///break out
	}
	else if (v[iterator + 1].lexeme == ";" && v[iterator + 3].lexeme == "}")
	{
		iterator += 3;
		Body(v, iterator, linecount);
	}
	else if (v[iterator + 1].lexeme == ";" && v[iterator + 3].lexeme != "}")
	{
		cout << "Error on line " << linecount << endl <<
			"Expected a } after ;";
		//exit(1);
		return; //break out
	}
	else
		Expression(v, iterator, linecount);
	
}

void Write(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Write> ";

	if (v[iterator + 1].lexeme == "(")
	{
		iterator += 2;
		Expression(v, iterator, linecount);

		if (v[iterator].lexeme != ")")
		{
			cout << "Error on line " << linecount << endl <<
				"Expected a ) after expression";
			return; //break out
			//exit(1);
		}
		else if (v[iterator].lexeme == ")" && v[iterator + 1].lexeme != ";")
		{
			cout << "Error on line " << linecount << endl <<
				"Expected a ; after )";
			return; //break out
			//exit(1);
		}
		else if (v[iterator].lexeme == ")" && v[iterator + 1].lexeme == ";")
		{
			iterator += 2;
			Statement(v, iterator, linecount);
		}
	}
	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected ( after write";
		//exit(1);
		return; //break out
	}
	
}

void Read(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Read> ";

	if (v[iterator + 1].lexeme == "(")
	{
		iterator += 2;
		IDs(v, iterator, linecount);

		if (v[iterator].lexeme != ")")
		{
			cout << "Error on line " << linecount << endl <<
				"Expected a ) after identifiers";
			//exit(1);
			return; //break out
		}
		else if (v[iterator].lexeme == ")" && v[iterator + 1].lexeme != ";")
		{
			cout << "Error on line " << linecount << endl <<
				"Expected a ; after )";
			//exit(1);
			return; //break out
		}
		else if (v[iterator].lexeme == ")" && v[iterator + 1].lexeme == ";")
		{
			iterator += 2;
			Statement(v, iterator, linecount);
		}
		
	}
	else
	{
		cout << "Error on line " << linecount << endl <<
			"Expected ( after read";
		//exit(1);
		return; //break out
	}	
}

void While(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <While> ";

	if (v[iterator + 1].lexeme == "(")
	{
		iterator += 2;
		Condition(v, iterator, linecount);

		if (v[iterator].lexeme == ")")
		{
			++iterator;
			Statement(v, iterator, linecount);
		}
		else
		{
			cout << "Error on line " << linecount << endl 
			 	 << "Expected a ) after condition" << endl;
			//exit(1);
			return; //break out
		}

	}
}

void Condition(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Condition> ";

	if (v[iterator].lexeme == ")" && v[iterator - 1].lexeme == "(")
	{
		cout << "Error on line " << linecount << endl <<
			"Must have condition between ()";
		//exit(1);
		return; //break out
	}
	else if (v[iterator].lexeme == ")")
		return;

	Expression(v, iterator, linecount);
	//Relop(v, iterator, linecount);
	//Expression(v, iterator, linecount);
}

void Relop(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Relop> ";

	if (v[iterator].lexeme == "=" | v[iterator].lexeme == "/=" || v[iterator].lexeme == ">" || v[iterator].lexeme == "<" || v[iterator].lexeme == "=>" || v[iterator].lexeme == "<=")
	{
		iterator++;
		return;
	}

	else
	{
		cout << "Error on line " << linecount << endl
			<< "Expected relational operator token" << endl;
		//exit(1);
		return; //break out
	}
}

void Expression(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attemped removal
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Expression> ";

	if(v[iterator].tokentype == "Integer" | v[iterator].tokentype == "Real" | 
		v[iterator].lexeme == "[" | v[iterator].lexeme == "(")
	ExpressionPrime(v, iterator, linecount);

	/*
	Term(v, iterator, linecount);
	// If next token is expression, then
	if (v[iterator].lexeme == "+" | v[iterator].lexeme == "-")
	{
		ExpressionPrime(v, iterator, linecount);
	}
	*/
}

void ExpressionPrime(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Expression Prime> ";

	if (v[iterator].lexeme != "+" && v[iterator].lexeme != "-")
	{
		iterator++;
		return;
	}

	else
	{
		Term(v, iterator, linecount);
		ExpressionPrime(v, iterator, linecount);
	}
}

void Term(vector<Token> &v, int &iterator, int &linecount) { // LEFT RECURSION, attempted removal
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Term> ";

	Factor(v, iterator, linecount);
	// if next token is term, then
	if (v[iterator].lexeme == "*" || v[iterator].lexeme == "/")
	{
		TermPrime(v, iterator, linecount);
	}
	
}

void TermPrime(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Term Prime> ";

	if (v[iterator].lexeme == "*" || v[iterator].lexeme == "/")
	{
		iterator++;
		return;
	}
	else
	{
		Factor(v, iterator, linecount);
		TermPrime(v, iterator, linecount);
	}
}

void Factor(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Factor> ";

	if (v[iterator].lexeme == "-")
		iterator++;
	Primary(v, iterator, linecount);
	
}

void Primary(vector<Token> &v, int &iterator, int &linecount) {
	if ((iterator - 1) == v.size())
	{
		cout << "You have reached end of file";
		system("pause");
		exit(0);
	}
	
	if (v[iterator].lexeme == "Endline") { ++iterator; ++linecount; }
	cout << " <Primary> ";

	//cout << endl << iterator << endl;

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
		Expression(v, iterator, linecount);
		if (v[iterator].lexeme == ")")
		{
			iterator++;
			return;
		}
		else
		{
			cout << "Error on line " << linecount << ", expected closing )" << endl;
			//exit(1);
			return; //break out
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
			//exit(1);
			return; //break out
		}
	}
	
	
	// For this function, checking the token should point us to which function to call
	//Identifier(v, iterator, linecount);
	// or
	// token: integer
	// or
	//Identifier(v, iterator, linecount);
	// [
	
	// ]
	// or
	// (
	
	// )
	// or
	// token: real
	// or
	// keyword: true or keyword: false
}