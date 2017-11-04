#pragma once
// lexer.h
// This header file includes the Lexical Analyzer part of the program, as coded in Assignment 1.
// Tyler Hatzenbuhler
// Anette Ulrichsen
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>

using namespace std;

// Class that stores the type of token and the lexeme together in a vector
class Token {
public:
	string tokentype;
	string lexeme;

	Token(string x, string y) { tokentype = x; lexeme = y; }
	Token() { tokentype = ""; lexeme = ""; }

	void assign(string x, string y)
	{
		tokentype = x;
		lexeme = y;
	}

	void print()
	{
		cout << "Token Type: " << tokentype << "\tLexeme: " << lexeme << endl;
	}
};

//our function declarations
void numberFSM(string&, int &, vector<Token> &);
void letterFSM(string&, int &, vector<Token> &);
void lexer(string, vector<Token> &, int &);
bool isKeyword(string);
bool isOperator(string&, string&, int&);
bool isSeperator(string);
bool isInvalid(string);
bool isQualifier(string);

//this FSM determines if the number being read in is an int or a float
void numberFSM(string& line, int &i, vector<Token> &v)
{
	typedef int fsm_state;
	fsm_state state = 0;
	string tempString = "";
	bool isFloat = false, isInt = false;
	Token token;

	while ((line[i] >= '0') && (line[i] <= '9') || (line[i] == '.'))
	{
		switch (state)
		{
			//state 0 identifies based on number or "." if the string will be an integer or a float
			//it is legal to have a float start with "."
		case 0:
			if (line[i] >= '0' && line[i] <= '9')
			{
				tempString += line[i];
				isInt = true;
				isFloat = false;
				state = 1;
			}
			else
			{
				tempString += line[i];
				isInt = false;
				isFloat = true;
				state = 1;
			}

			break;

			//state 1 allows more integers to be read in or for the integer to become a float
		case 1:
			if (line[i] >= '0' && line[i] <= '9')
			{
				tempString += line[i];
				state = 1;
			}

			else
			{
				tempString += line[i];
				isFloat = true;
				isInt = false;
				state = 2;
			}

			break;

			//state 2 allows the number to have more integers added to the end
			//state 2 also checks to make sure there aren't multiple "." in a single digit or in a row
		case 2:
			if (line[i] >= '0' && line[i] <= '9')
			{
				tempString += line[i];
				state = 2;
			}
			else if (line[i - 1] == '.')
			{
				cout << "Input can't have 2 '.' in a row. The input has been discarded. Lexical analysis resumes at the next viable character." << endl;
				tempString = "";
				isInt = false;
				isFloat = false;
				state = 0;
			}
			else
			{
				cout << "Input can't have multiple '.' in a number. The input has been discarded. Lexical analysis resumes at the next viable character." << endl;
				tempString = "";
				isInt = false;
				isFloat = false;
				state = 0;
			}


			break;
		}

		i++;
	}

	//based on which bool is true from the FSM, our Token variable is assigned a token
	//and a lexeme
	if (isInt)
		token.assign("Integer", tempString);
	if (isFloat)
		token.assign("Real", tempString);

	//as long as there were no errors in the FSM, the Token variable is added to our vector
	if (tempString != "")
		v.push_back(token);
}

//this function reads in letters and # to identify if the string is a keyword or an identifier
void letterFSM(string &line, int &i, vector<Token> &v)
{
	typedef int fsm_state;
	fsm_state state = 0;
	string tempString = "";
	bool isId = false, isKey = true;
	Token token;
	char firstChar = line[i];


	//should never call in a # as the first letter in a sequence in this FSM
	while (((line[i] >= 'A') && (line[i] <= 'Z')) | ((line[i] >= 'a') && (line[i] <= 'z')) | (line[i] == '#'))
	{
		switch (state)
		{
			//state 0 reads in letters and checks input for validity
		case 0:
			if (((line[i] >= 'A') && (line[i] <= 'Z')) | ((line[i] >= 'a') && (line[i] <= 'z')))
			{
				tempString += line[i];
				state = 1;
			}

			else if (line[i] == firstChar)
			{
				cout << "An identifier cannot begin with a # sign. Input has been discarded. Lexical analysis will begin at the next viable character." << endl;
				tempString = "";
				state = 0;
			}
			else
			{
				cout << "An identifier cannot have 2 # signs in a row. Input has been discarded. Lexical analysis will begin at the next viable character." << endl;
				tempString = "";
				state = 0;
			}

			break;

			//state 1 reads in more characters and # signs. If a # is entered, the string is sent back to state 0 to ensure 2 # aren't in a row
		case 1:
			if (((line[i] >= 'A') && (line[i] <= 'Z')) | ((line[i] >= 'a') && (line[i] <= 'z')))
			{
				tempString += line[i];
				state = 1;
			}
			else
			{
				tempString += line[i];
				isId = true;
				isKey = false;
				state = 0;
			}
			break;

		}
		i++;
	}

	//letterFSM calls the function to isKeyword to check is the string is a keyword. If it return true
	//a Token variable will store the information
	if (isKeyword(tempString))
		token.assign("Keyword", tempString);
	//if the string is not a keyword, the Token variable will store the correct information
	else if (isQualifier(tempString))
		token.assign("Qualifier", tempString);
	else
		token.assign("Identifier", tempString);

	//as long as there were no errors in the FSM, the Token variable is added to our vector
	if (tempString != "")
		v.push_back(token);
}

//The lexer starts with the first character in the line and calls functions based on the character
//if those functions are not a match, the lexer calls the FSMs
void lexer(string line, vector<Token> &v, int &i) {
	Token token;
	string tempString = "";
	int len;

	len = line.length();

	while (i < len) {

		tempString += line[i];

		if (isInvalid(tempString))
		{
			cout << "The character: " << tempString << " is an invalid. The character will be discarded." << endl;
			i++;
		}
		else if (tempString == "\t")
		{
			i++;
		}
		else if (isOperator(tempString, line, i))
		{
			token.assign("Operator", tempString);
			v.push_back(token);
			tempString.clear();
		}
		else if (isSeperator(tempString))
		{
			token.assign("Seperator", tempString);
			v.push_back(token);
			tempString.clear();
			i++;
		}
		else if (tempString == " ")
		{
			tempString.clear();
			i++;
		}
		else
		{
			numberFSM(line, i, v);
			if (i == len)
				continue;
			letterFSM(line, i, v);
		}
		tempString.clear();
	}
	i = 0;
}

//This function compares the string passed to it to the known keywords and returns true if the string is a keyword
bool isKeyword(string key)
{
	bool isKey = false;
	string keyArr[79] = { "alignas", "alignof", "and", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "class", "compl",
		"concept", "const", "constexpr", "continue", "decltype", "default", "delete", "do", "double", "else", "enum", "explicit", "export",
		"extern", "false", "float", "for", "friend", "goto", "if", "import", "inline", "int", "long", "module", "mutable", "namespace", "new",
		"noexcept", "not", "nullptr", "operator", "or", "private", "protected", "public", "register", "requires", "return", "short", "signed",
		"sizeof", "static", "struct", "switch", "synchronized", "template", "this", "throw", "true", "try", "typedef", "typeid", "typename",
		"union", "unsigned", "floating", "virtual", "void", "real", "while", "boolean", "fi", "read", "write" };

	for (int i = 0; i < 79; i++)
	{
		if (key == keyArr[i])
			isKey = true;
	}

	return isKey;
}

//this function compares the string passed to the known operators (1 character and 2 character) and returns true if the
//characters are a known operator
bool isOperator(string &oper, string &line, int &i)
{
	bool isOp = false;
	string opArr[16] = { "<", ">", "*","/","+","-", "=","@", "%%", "=>", "<=", ":=", "/=", "+=", "-=", "*=" };

	string oneCharCase = ""; oneCharCase += line[i];
	string twoCharCase = ""; twoCharCase += line[i]; twoCharCase += line[i + 1];

	for (int j = 0; j < 8; j++) // One Char
	{
		if (opArr[j] == oneCharCase)
		{
			isOp = true;
			oper = oneCharCase;
			i++;
		}
	}
	for (int j = 8; j < 16; j++) // Two Chars
	{
		if (opArr[j] == twoCharCase)
		{
			isOp = true;
			oper = twoCharCase;
			i += 2;
		}
	}

	return isOp;
}

//this function compares the string passed to the known seperators and returns true if the
//characters are a seperator
bool isSeperator(string sep)
{
	bool isSep = false;
	string sepArr[9] = { "(", ")", "[", "]", "{", "}", ";", ",", ":" };

	for (int i = 0; i < 9; i++)
	{
		if (sep == sepArr[i])
			isSep = true;
	}

	return isSep;
}

bool isQualifier(string qual)
{
	bool isQual = false;
	string qualArr[] = { "integer", "boolean", "floating" };

	for (int i = 0; i < 3; i++)
	{
		if (qual == qualArr[i])
			isQual = true;
	}

	return isQual;
}
//this function identifies whether the character passed to it is unknown or not. The function returns true if the
//character is invalid
bool isInvalid(string known)
{
	bool isValid = false;
	string invalidArr[7] = { "$", "&", "_", "?", "^", "`", "~" };

	for (int i = 0; i < 7; i++)
	{
		if (known == invalidArr[i])
			isValid = true;
	}

	return isValid;
}